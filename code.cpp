// **************************************************************
// *                                                            *
// *  C O D E     (code)                                      *
// *                                                            *
// *  CLASSES:    Quadruple, QuadrupleList, Code              *
// *                                                            *
// **************************************************************

#include "code.h"
#include <sstream>

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
  m_qList.push_back(Quadruple(op,arg1,arg2,result));
}

void Code::generateCall(SymbolTableEntry* entry, EntryList& eList)
{
  EntryList::iterator it;
  for(it = eList.begin(); it != eList.end(); it++)
    generate(cd_APARAM,NULL,NULL,*it);
  generate(cd_CALL,entry,NULL,NULL);
}

void Code::generateFormals(EntryList& entrylist)
{
  EntryList::iterator it;
  for(it = entrylist.begin(); it != entrylist.end(); it++)
    generate(cd_FPARAM,NULL,NULL,*it);
}

void Code::generateVariables(EntryList& entrylist)
{
  EntryList::iterator it;
  for(it = entrylist.begin(); it != entrylist.end(); it++)
    generate(cd_VAR,NULL,NULL,*it);
}

std::string Code::newLabel()
{
  std::stringstream ss;
  ss << CodeLabelPrefix << m_labelCounter;
  m_labelCounter++;
  return ss.str();
}

std::string Code::newTemp()
{
  std::stringstream ss;
  ss << CodeTempVarPrefix << m_tempCounter;
  m_tempCounter++;
  return ss.str();
}

void Code::print()
{
  QuadrupleList::iterator it;
  for(it = m_qList.begin(); it != m_qList.end(); it++)
    it->print(*it);
}

