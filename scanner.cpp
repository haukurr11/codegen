#include "scanner.h"
#include "lex.yy.cc"


using namespace std;

SymbolTable* Scanner::getSymbolTable(void)
{
	return m_symbolTable;
}

// sets the corresponding fields in m_currentToken
void Scanner::setCurrentToken(TokenCode tc, DataType dt, OpType op)
{
	m_currentToken.setTokenCode(tc);
	m_currentToken.setDataType(dt);
	m_currentToken.setOpType(op);
}
// sets the corresponding fields in m_currentToken
void Scanner::setCurrentToken(TokenCode tc, DataType dt, const std::string& lexeme)
{
	m_currentToken.setTokenCode(tc);
	m_currentToken.setDataType(dt);
	m_currentToken.setOpType(op_NONE);
	m_currentToken.setSymTabEntry(m_symbolTable->insert(lexeme));
} 
											
Scanner::Scanner(SymbolTable* symbols, std::istream& input, std::ostream& output) :
m_symbolTable(symbols)
{
	m_lexer = new yyFlexLexer(&input, &output);
}
Scanner::~Scanner()
{
	
	delete m_lexer;
}
// returns the next token from FlexLexer
Token* Scanner::nextToken(void)
{
	TokenCode tCode = static_cast<TokenCode>(m_lexer->yylex());
	while(tCode == tc_NEWLINE || tCode == tc_TAB || tCode == tc_SPACE || tCode == tc_COMMENT)
	{
		switch (tCode) 
		{
			case tc_NEWLINE:
				flushSourceLine();
				break;
			case tc_TAB:
				m_sourceLine.buildLine("     ");
				break;
			case tc_SPACE:
				m_sourceLine.buildLine(" ");
				break;
			default:
				m_sourceLine.buildLine(m_lexer->YYText());
				break;
		}
		tCode = static_cast<TokenCode>(m_lexer->yylex());
	}	
	m_sourceLine.buildLine(m_lexer->YYText());

	if(tCode == tc_ID || tCode == tc_NUMBER)
		setCurrentToken(tCode, Type, m_lexer->YYText());
	else
		setCurrentToken(tCode, Type, Oper);
	
	if(tCode == tc_EOF)
		flushSourceLine();
	return &m_currentToken;
}

void Scanner::addError(std::string error)
{
	m_sourceLine.addError(error);
}
void Scanner::flushSourceLine()
{
	if(m_sourceLine.hasError())
		m_sourceLine.printLine();
	m_sourceLine.newLine();
}
