#include "parser.h"

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
  match(tc_SEMICOL);                Recover(programSync);
  parseDeclarations();
  parseSubprogramDeclarations();
  parseCompoundStatement();
  match(tc_DOT);                  Recover(programSync);
}

void Parser::parseIdentifierList(EntryList& idList)
{
  match(tc_ID);                  Recover(identifierListSync);
  parseIdentifierListPrime(idList);
}

void Parser::parseIdentifierListPrime(EntryList& idList)
{
  if(isNext(tc_COMMA))
  {
    match(tc_COMMA);
    match(tc_ID);                Recover(identifierListSync);
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
    match(tc_ELSE);                  Recover(statementSync);
    parseStatement();
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
    match(tc_ID);                  Recover(statementSync);
    parseStatementPrime(NULL);
  }
}

void Parser::parseStatementPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_LBRACKET) || isNext(tc_ASSIGNOP))
  {
    parseVariablePrime(NULL);
    match(tc_ASSIGNOP);
    parseExpression();
  }
  else
  {
    parseProcedureStatementPrime(NULL);
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
  return NULL;
}

void Parser::parseProcedureStatement()
{
  match(tc_ID);
  parseProcedureStatementPrime(NULL);
}

void Parser::parseProcedureStatementPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_LPAREN))
  {
    match(tc_LPAREN);
    parseExpressionList(NULL);
    match(tc_RPAREN);
  }
}

void Parser::parseExpressionList(SymbolTableEntry* prevEntry)
{
  EntryList expressions;
  parseExpression();
  parseExpressionListPrime(expressions);
}

void Parser::parseExpressionListPrime(EntryList& expList)
{
  if(isNext(tc_COMMA))
  {
    match(tc_COMMA);
    parseExpression();
    parseExpressionListPrime(expList);
  }
  // else epsilon
}

SymbolTableEntry* Parser::parseExpression()
{
  parseSimpleExpression();
  parseExpressionPrime(NULL);
  return NULL;
}

SymbolTableEntry* Parser::parseExpressionPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_RELOP))
  {
    match(tc_RELOP);
    parseSimpleExpression();
  }
  // else epsilon
  return NULL;
}

SymbolTableEntry* Parser::parseSimpleExpression()
{
  if(isNext(tc_ADDOP))
  {
    parseSign();
    parseTerm();
    parseSimpleExpressionPrime(NULL);
  }
  else
  {
    parseTerm();
    parseSimpleExpressionPrime(NULL);
  }
  return NULL;
}

SymbolTableEntry* Parser::parseSimpleExpressionPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_ADDOP))
  {
    match(tc_ADDOP);
    parseTerm();
    parseSimpleExpressionPrime(NULL);
  }
  // else epsilon
  return NULL;
}

SymbolTableEntry* Parser::parseTerm()
{
  parseFactor();
  parseTermPrime(NULL);
  return NULL;
}

SymbolTableEntry* Parser::parseTermPrime(SymbolTableEntry* prevEntry)
{
  if(isNext(tc_MULOP))
  {
    match(tc_MULOP);
    parseFactor();
    parseTermPrime(NULL);
  }
  // else epsilon
  return NULL;
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
    parseExpressionList(NULL);
    match(tc_RPAREN);                Recover(factorSync);
  }
  else
  {
    parseVariablePrime(NULL);
  }
  return NULL;
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
  m_code->generate(cd_LABEL,NULL,NULL,entry);
  return entry;
}

CodeOp Parser::opToCode(OpType op)
{
  // Implement
  return cd_NOOP;
}

Code* Parser::getCode()
{
  // Implement
  return NULL;
}
