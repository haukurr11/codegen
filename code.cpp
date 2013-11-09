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

}

Quadruple::Quadruple(CodeOp op, SymbolTableEntry* arg1, SymbolTableEntry* arg2, SymbolTableEntry* result)
{

}

CodeOp Quadruple::getOp()
{

}

void Quadruple::set(CodeOp op, SymbolTableEntry* arg1, SymbolTableEntry* arg2, SymbolTableEntry* result)
{

}

Code::Code()
{

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
