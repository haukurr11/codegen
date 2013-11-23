#include "parser.h"
#include "types.h"

Parser::Parser(std::istream& input, std::ostream& output)
{
  m_symbolTable = new SymbolTable();
  m_lexan = new Scanner(m_symbolTable, std::cin, std::cout);
  getToken();
  m_parserError = false;
  m_totalErrors = 0;
  m_code = new Code();
}

Parser::~Parser()
{
  delete m_lexan;
  delete m_symbolTable;
}

void Parser::parse()
{
  m_totalErrors = 0;
  m_parserError = false;
  parseProgram();
  if(totalErrors())
    std::cerr << std::endl << "Number of errors: " << totalErrors() << "." << std::endl;
  else {
    m_code->print();
  }
}

SymbolTable* Parser::getSymbolTable()
{
  return m_symbolTable;
}

int Parser::totalErrors()
{
  return m_totalErrors;
}

bool Parser::tokenCodeIn(TokenCode tc, const TokenCode list[]) // Is the given tokencode in the list
{
  if(list == NULL)
    return false;
  int counter = 0;
  while(list[counter] != tc_NONE)
  {
    if(tc == list[counter++])
      return true;
  }
  return false;
}

#define Recover(x)   if(m_parserError)recover(x)
#define RecoverReturn(x)   if(m_parserError){recover(x);return;}
void Parser::recover(const TokenCode list[]) // keep asking for tokens until token is found in the list
{
  while(!tokenCodeIn(m_currentToken->getTokenCode(), list) && m_currentToken->getTokenCode() != tc_EOF)
  {
    getToken();
  }
  m_parserError = false;
}

void Parser::getToken() // ask lexical analyzer for next token
{
  m_currentToken = m_lexan->nextToken();
  if(m_currentToken->getTokenCode() == tc_ERROR)
  {
    setError("Illegal character.");
    getToken(); // Recursive while
  }
  else if(m_currentToken->getTokenCode() == tc_ERROR2)
  {
    setError("Identifier too long.");
    getToken(); // Recursive while
  }
}

void Parser::match(TokenCode tc) // Walk over tokencode tc.  If not a match; report an error
{
  if(tc != m_currentToken->getTokenCode())
    expectedTokenCode(tc);
  else
    getToken();
}

void Parser::setError(const std::string& err) // sets an appropriate error message
{
  m_parserError = true;
  m_lexan->addError(err);
  m_totalErrors++;
}

void Parser::expectedTokenCode(TokenCode tc)
{
  std::string err;
  switch(tc)
  {
    case tc_ID:
      err = "an identifier";
      break;
    case tc_NUMBER:
      err = "a number";
      break;
    case tc_ASSIGNOP:
    case tc_RELOP:
    case tc_ADDOP:
    case tc_MULOP:
      err = "an operator";
      break;
    case tc_SEMICOL:
      err = "';'";
      break;
    case tc_COLON:
      err = "':'";
      break;
    case tc_COMMA:
      err = "','";
      break;
    case tc_DOT:
      err = "'.'";
      break;
    case tc_DOTDOT:
      err = "'..'";
      break;
    case tc_LPAREN:
      err = "'('";
      break;
    case tc_LBRACKET:
      err = "'['";
      break;
    case tc_RPAREN:
      err = "')'";
      break;
    case tc_RBRACKET:
      err = "']'";
      break;
    case tc_EOF:
      err = "end of file";
      break;
    case tc_INTEGER:
    case tc_REAL:
      err = "a type";
      break;
    case tc_PROGRAM:
    case tc_VAR:
    case tc_ARRAY:
    case tc_OF:
    case tc_FUNCTION:
    case tc_PROCEDURE:
    case tc_BEGIN:
    case tc_END:
    case tc_IF:
    case tc_THEN:
    case tc_ELSE:
    case tc_WHILE:
    case tc_DO:
    case tc_NOT:
      err = tokenCodeStrings[tc];
      break;
    default:
      err = "something else";
      break;
  }
  err = "Expected " + err;
  err += ".";
  setError(err);
}

bool Parser::isNext(TokenCode tc)
{
  return tc == m_currentToken->getTokenCode();
}

void Parser::parseProgram()
{
  match(tc_PROGRAM);                Recover(programSync);
  match(tc_ID);                  Recover(programSync);
  SymbolTableEntry* pname = m_currentToken->getSymTabEntry();
  match(tc_SEMICOL);                Recover(programSync);
  parseDeclarations();
  m_code->generate(cd_GOTO,NULL,NULL,pname);
  m_code->generate(cd_LABEL,NULL,NULL,pname);
  parseSubprogramDeclarations();
  parseCompoundStatement();
  m_code->generate(cd_RETURN,NULL,NULL,NULL);
  match(tc_DOT);                  Recover(programSync);
}

void Parser::parseIdentifierList(EntryList& idList)
{
  match(tc_ID);                  Recover(identifierListSync);
  SymbolTableEntry* entry = m_currentToken->getSymTabEntry();
  idList.push_back(entry);
  parseIdentifierListPrime(idList);
}

void Parser::parseIdentifierListPrime(EntryList& idList)
{
  if(isNext(tc_COMMA))
  {
    match(tc_COMMA);
    match(tc_ID);                Recover(identifierListSync);
    SymbolTableEntry* entry = m_currentToken->getSymTabEntry();
    idList.push_back(entry);
    parseIdentifierListPrime(idList);
  }
  // else epsilon
}

void Parser::parseDeclarations()
{
  EntryList variables;
  if(isNext(tc_VAR))
  {
    match(tc_VAR);
    parseIdentifierList(variables);
    match(tc_COLON);              RecoverReturn(declarationsSync);
    parseType();
    match(tc_SEMICOL);              Recover(declarationsSync);
    parseDeclarations();
    m_code->generateVariables(variables);
  }
  // else epsilon
}

void Parser::parseType()
{
  if(isNext(tc_ARRAY))
  {
    match(tc_ARRAY);              RecoverReturn(standardTypeSync);
    match(tc_LBRACKET);              RecoverReturn(standardTypeSync);
    match(tc_NUMBER);              RecoverReturn(standardTypeSync);
    match(tc_DOTDOT);              RecoverReturn(standardTypeSync);
    match(tc_NUMBER);              RecoverReturn(standardTypeSync);
    match(tc_RBRACKET);              RecoverReturn(standardTypeSync);
    match(tc_OF);                RecoverReturn(standardTypeSync);
    parseStandardType();
  }
  else //(isNext(tc_INTEGER) || isNext(tc_REAL))
  {
    parseStandardType();
  }
}

void Parser::parseStandardType()
{
  if(isNext(tc_REAL))
  {
    match(tc_REAL);
  }
  else
  {
    match(tc_INTEGER);
  }
  Recover(standardTypeSync);
}

void Parser::parseSubprogramDeclarations()
{
  if(isNext(tc_FUNCTION) || isNext(tc_PROCEDURE))
  {
    parseSubprogramDeclaration();
    match(tc_SEMICOL);              Recover(declarationsSync);
    parseSubprogramDeclarations();
  }
  // else epsilon
}

void Parser::parseSubprogramDeclaration()
{
  parseSubprogramHead();
  parseDeclarations();
  parseCompoundStatement();
}

void Parser::parseSubprogramHead()
{
  if(isNext(tc_FUNCTION))
  {
    match(tc_FUNCTION);
    match(tc_ID);                Recover(subProgramHeadSync);
    parseArguments();
    match(tc_COLON);              Recover(subProgramHeadSync);
    parseStandardType();
    match(tc_SEMICOL);              Recover(subProgramHeadSync);
  }
  else
  {
    match(tc_PROCEDURE);            Recover(subProgramHeadSync);
    match(tc_ID);                Recover(subProgramHeadSync);
    parseArguments();
    match(tc_SEMICOL);              Recover(subProgramHeadSync);
  }
}

void Parser::parseArguments()
{
  if(isNext(tc_LPAREN))
  {
    match(tc_LPAREN);
    parseParameterList();
    match(tc_RPAREN);              Recover(argumentsSync);
  }
  // else epsilon
}

void Parser::parseParameterList()
{
  EntryList parameters;
  parseIdentifierList(parameters);
  match(tc_COLON);                Recover(parameterListSync);
  parseType();
  parseParameterListPrime();
}

void Parser::parseParameterListPrime()
{
  EntryList parameters;
  if(isNext(tc_SEMICOL))
  {
    match(tc_SEMICOL);
    parseIdentifierList(parameters);
    match(tc_COLON);              Recover(parameterListSync);
    parseType();
    parseParameterListPrime();
  }
  // else epsilon
  Recover(parameterListSync);
}

void Parser::parseCompoundStatement()
{
  match(tc_BEGIN);                RecoverReturn(compoundStatementSync);
  parseOptionalStatements();
  match(tc_END);                  Recover(compoundStatementSync);
}

void Parser::parseOptionalStatements()
{
  if(isNext(tc_ID) || tc_BEGIN || tc_IF || tc_WHILE)
  {
    parseStatementList();
  }
  // else epsilon
}

void Parser::parseStatementList()
{
  parseStatement();
  parseStatementListPrime();
}

void Parser::parseStatementListPrime()
{
  if(isNext(tc_SEMICOL))
  {
    match(tc_SEMICOL);
    parseStatement();
    parseStatementListPrime();
  }
  // else epsilon
}

void Parser::parseStatement()
{
  if(isNext(tc_BEGIN))
  {
    parseCompoundStatement();
  }
  else if(isNext(tc_IF))
  {
    match(tc_IF);
    parseExpression();
    match(tc_THEN);                  Recover(statementSync);
    parseStatement();
    SymbolTableEntry* jump = newLabel();
    m_code->generate(cd_GOTO, NULL, NULL,jump);
    match(tc_ELSE);                  Recover(statementSync);
    m_code->generate(cd_LABEL, NULL, NULL, newLabel());
    parseStatement();
    m_code->generate(cd_LABEL, NULL, NULL, jump);
  }
  else if(isNext(tc_WHILE))
  {
    match(tc_WHILE);
    parseExpression();
    match(tc_DO);                  Recover(statementSync);
    parseStatement();
  }
  else //(isNext(tc_ID))
  {
    SymbolTableEntry* entry = m_currentToken->getSymTabEntry();
    match(tc_ID);                  Recover(statementSync);
    parseStatementPrime(entry);
  }
}

void Parser::parseStatementPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_LBRACKET) || isNext(tc_ASSIGNOP))
  {
    parseVariablePrime(prevEntry);
    match(tc_ASSIGNOP);
    SymbolTableEntry* entry = parseExpression();
    m_code->generate(cd_ASSIGN,entry,NULL,prevEntry);
  }
  else
  {
    parseProcedureStatementPrime(prevEntry);
  }
}

SymbolTableEntry* Parser::parseVariable()
{
  match(tc_ID);
  parseVariablePrime(NULL);
  return NULL;
}

SymbolTableEntry* Parser::parseVariablePrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_LBRACKET))
  {
    match(tc_LBRACKET);
    parseExpression();
    match(tc_RBRACKET);
  }
  // else epsilon
  return prevEntry;
}

void Parser::parseProcedureStatement()
{
  SymbolTableEntry* entry = m_currentToken->getSymTabEntry();
  match(tc_ID);
  parseProcedureStatementPrime(entry);
}

void Parser::parseProcedureStatementPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_LPAREN))
  {
    match(tc_LPAREN);
    parseExpressionList(prevEntry);
    match(tc_RPAREN);
  }
}

void Parser::parseExpressionList(SymbolTableEntry* prevEntry)
{
  EntryList expressions;
  expressions.push_back(parseExpression());
  parseExpressionListPrime(expressions);
  m_code->generateCall(prevEntry,expressions);
}

void Parser::parseExpressionListPrime(EntryList& expList)
{
  if(isNext(tc_COMMA))
  {
    match(tc_COMMA);
    expList.push_back(parseExpression());
    parseExpressionListPrime(expList);
  }
  // else epsilon
}

SymbolTableEntry* Parser::parseExpression()
{
  SymbolTableEntry* resultEntry = parseSimpleExpression();
  resultEntry = parseExpressionPrime(resultEntry);
  return resultEntry;
}

SymbolTableEntry* Parser::parseExpressionPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_RELOP))
  {
    SymbolTableEntry *f = m_symbolTable->lookup(CodeFalse);
    SymbolTableEntry *t = m_symbolTable->lookup(CodeTrue);
    CodeOp codeop = opToCode(m_currentToken->getOpType());
    match(tc_RELOP);
    SymbolTableEntry* expression = parseSimpleExpression();
    SymbolTableEntry* temp = newTemp();
    SymbolTableEntry* settrue = newLabel();
    SymbolTableEntry* eq = newLabel();
    m_code->generate(codeop,prevEntry,expression,settrue);
    m_code->generate(cd_ASSIGN,f,NULL,temp);
    m_code->generate(cd_GOTO,NULL,NULL,eq);
    m_code->generate(cd_LABEL,NULL,NULL,settrue);
    m_code->generate(cd_ASSIGN,t,NULL,temp);
    m_code->generate(cd_LABEL,NULL,NULL,eq);
    m_code->generate(cd_EQ,temp,f,eq);
    return temp;
  }
  // else epsilon
  return prevEntry;
}

SymbolTableEntry* Parser::parseSimpleExpression()
{
  SymbolTableEntry* resultEntry = NULL;
  if(isNext(tc_ADDOP))
  {
    parseSign();
    SymbolTableEntry* term = parseTerm();
    resultEntry = newTemp();
    CodeOp co;
    m_code->generate(cd_UMINUS,term,NULL,resultEntry);
    parseSimpleExpressionPrime(resultEntry);
  }
  else
  {
    resultEntry = parseTerm();
    resultEntry = parseSimpleExpressionPrime(resultEntry);
  }
  return resultEntry;
}

SymbolTableEntry* Parser::parseSimpleExpressionPrime(SymbolTableEntry* prevEntry)
{
  SymbolTableEntry* resultEntry = prevEntry;
  if(isNext(tc_ADDOP))
  {
    CodeOp co = opToCode(m_currentToken->getOpType());
    match(tc_ADDOP);
    SymbolTableEntry* term = parseTerm();
    SymbolTableEntry* temp = newTemp();
    resultEntry = parseSimpleExpressionPrime(temp);
    m_code->generate(co,prevEntry,term,temp);
  }
  // else epsilon
  return resultEntry;
}

SymbolTableEntry* Parser::parseTerm()
{
  SymbolTableEntry* resultEntry = parseFactor();
  resultEntry = parseTermPrime(resultEntry);
  return resultEntry;
}

SymbolTableEntry* Parser::parseTermPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_MULOP))
  {
    SymbolTableEntry *f = m_symbolTable->lookup(CodeFalse);
    SymbolTableEntry *t = m_symbolTable->lookup(CodeTrue);
    CodeOp op = opToCode(m_currentToken->getOpType());
    match(tc_MULOP);
    SymbolTableEntry* factor = parseFactor();
    parseTermPrime(factor);
    SymbolTableEntry* temp = newTemp();
    m_code->generate(op,prevEntry,factor,temp);
    m_code->generate(cd_EQ,temp,f,f);
    prevEntry = temp;
  }
  // else epsilon
  return prevEntry;
}

SymbolTableEntry* Parser::parseFactor()
{
  SymbolTableEntry *factor = NULL;
  SymbolTableEntry *resultEntry = m_symbolTable->lookup(CodeFalse);
  if(isNext(tc_NUMBER))
  {
    resultEntry = m_currentToken->getSymTabEntry();
    match(tc_NUMBER);
  }
  else if(isNext(tc_LPAREN))
  {
    match(tc_LPAREN);
    resultEntry = parseExpression();
    match(tc_RPAREN);                Recover(factorSync);
  }
  else if(isNext(tc_NOT))
  {
    match(tc_NOT);
    factor = parseFactor();
    resultEntry = newTemp();
    m_code->generate(cd_NOT,factor,NULL,resultEntry);
  }
  else //if(isNext(tc_ID))
  {
    factor = m_currentToken->getSymTabEntry();
    match(tc_ID);                  Recover(factorSync);
    resultEntry = parseFactorPrime(factor);
  }
  return resultEntry;
}

SymbolTableEntry* Parser::parseFactorPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_LPAREN))
  {
    match(tc_LPAREN);
    parseExpressionList(prevEntry);
    match(tc_RPAREN);                Recover(factorSync);
  }
  else
  {
    parseVariablePrime(prevEntry);
  }
  return prevEntry;
}

void Parser::parseSign()
{
  match(tc_ADDOP);
}

SymbolTableEntry* Parser::newTemp()
{
  std::string name = m_code->newTemp();
  SymbolTableEntry* entry = m_symbolTable->insert(name);
  m_code->generate(cd_VAR,NULL,NULL,entry);
  return entry;
}

SymbolTableEntry* Parser::newLabel()
{
  std::string name = m_code->newLabel();
  SymbolTableEntry* entry = m_symbolTable->insert(name);
  return entry;
}

CodeOp Parser::opToCode(OpType op)
{
  switch(op) {
    case op_PLUS:
     return cd_ADD;
    case op_MINUS:
     return cd_SUB;
    case op_OR:
     return cd_OR;
    case op_MULT:
     return cd_MULT;
    case op_DIV:
     return cd_DIV;
    case op_AND:
     return cd_AND;
    case op_DIVIDE:
     return cd_DIVIDE;
    case op_MOD:
     return cd_MOD;
    case op_LT:
     return cd_LT;
    case op_GT:
     return cd_GT;
    case op_LE:
     return cd_LE;
    case op_GE:
     return cd_GE;
    case op_EQ:
     return cd_EQ;
    case op_NE:
     return cd_NE;
  }
  return cd_NOOP;
}

Code* Parser::getCode()
{
  return m_code;
}
