#include "token.h"

Token::Token(void):
m_tokenCode(tc_NONE),
m_symtabEntry(NULL)
{
}
Token::~Token()
{
}
// Get Operations
TokenCode Token::getTokenCode(void) const
{
	return m_tokenCode;
}
DataType Token::getDataType(void) const
{
	return m_dataType;
}
OpType Token::getOpType(void) const
{
	return m_opType;
}
SymbolTableEntry* Token::getSymTabEntry(void) const
{
	return m_symtabEntry;
}
void Token::setTokenCode(TokenCode tc)
{
	m_tokenCode = tc;
}
void Token::setDataType(DataType dt)
{
	m_dataType = dt;
}
void Token::setOpType(OpType op)
{
	m_opType = op;
}
void Token::setSymTabEntry(SymbolTableEntry* entry)
{
	m_symtabEntry = entry;
}

std::string Token::opTypeToString(void)
{
	return OpTypeToString(this->getOpType());
}
std::string Token::tokenCodeToString(void)
{
	return TokenCodeToString(this->getTokenCode());
}

