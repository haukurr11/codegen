// **************************************************************
// *                                                            *
// *  C O D E     (code)                                      *
// *                                                            *
// *  CLASSES:    Quadruple, QuadrupleList, Code              *
// *                                                            *
// **************************************************************

#include "code.h"

Quadruple::Quadruple()
{
  m_op = cd_NOOP;
  m_arg1 = NULL;
  m_arg2 = NULL;
  m_result = NULL;
}

Quadruple::Quadruple(CodeOp op, SymbolTableEntry* arg1, SymbolTableEntry* arg2, SymbolTableEntry* result)
{
  m_op = op;
  m_arg1 = arg1;
  m_arg2 = arg2;
  m_result = result;
}

CodeOp Quadruple::getOp()
{
  return m_op;
}

void Quadruple::set(CodeOp op, SymbolTableEntry* arg1, SymbolTableEntry* arg2, SymbolTableEntry* result)
{
  m_op = op;
  m_arg1 = arg1;
  m_arg2 = arg2;
  m_result = result;
}

Code::Code()
{
  m_tempCounter = 0;
  m_labelCounter = 0;
}

Code::~Code()
{
}

void Code::generate(CodeOp op, SymbolTableEntry* arg1, SymbolTableEntry* arg2, SymbolTableEntry* result)
{

}

void Code::generateCall(SymbolTableEntry* entry, EntryList& eList)
{

}

void Code::generateFormals(EntryList& entrylist)
{

}

void Code::generateVariables(EntryList& entrylist)
{

}

std::string Code::newLabel()
{

}

std::string Code::newTemp()
{

}

void Code::print()
{

}
