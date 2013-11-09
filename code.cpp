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
  delete m_arg1;
  delete m_arg2;
  delete m_result;
}

void Code::generate(CodeOp op, SymbolTableEntry* arg1, SymbolTableEntry* arg2, SymbolTableEntry* result)
{
  Quadruple quad(op,arg1,arg2,result);
  m_qList.push_back(quad);
}

void Code::generateCall(SymbolTableEntry* entry, EntryList& eList)
{
  EntryList::iterator it;
  for(it = eList.begin(); it != eList.end(); ++it)
    generate(cd_APARAM,NULL,NULL,*it);
  generate(cd_CALL,entry,NULL,NULL);
}

void Code::generateFormals(EntryList& entrylist)
{
  EntryList::iterator it;
  for(it = entrylist.begin(); it != entrylist.end(); ++it)
    generate(cd_FPARAM,NULL,NULL,*it);
}

void Code::generateVariables(EntryList& entrylist)
{
  EntryList::iterator it;
  for(it = entrylist.begin(); it != entrylist.end(); ++it)
    generate(cd_VAR,NULL,NULL,*it);
}

std::string Code::newLabel()
{
  m_labelCounter++;
  return CodeLabelPrefix + m_labelCounter;
}

std::string Code::newTemp()
{
  m_tempCounter++;
  return CodeTempVarPrefix + m_tempCounter;
}

void Code::print()
{
  QuadrupleList::iterator it;
  for(it = m_qList.begin(); it != m_qList.end(); ++it)
    it->print(*it);
}

