#include "symtab.h"
#include "code.h"

SymbolTable::SymbolTable(void)
{
  insert(CodeFalse);
  insert(CodeTrue);
}

SymbolTable::~SymbolTable(void)
{
  for(std::size_t n = 0 ; n < m_table.size() ; n++)
  {
    delete m_table[n]; 
  }
}

SymbolTableEntry* SymbolTable::insert(std::string lexeme)
{
  std::transform(lexeme.begin(), lexeme.end(), lexeme.begin(), ::tolower);
  SymbolTableEntry* entry = lookup(lexeme);
  if(entry)
    return entry;

  // Not found, create
  entry = new SymbolTableEntry();
  entry->lexeme = lexeme;
  m_table.push_back(entry);
  return entry;
}
SymbolTableEntry* SymbolTable::lookup(std::string lexeme)
{
  std::transform(lexeme.begin(), lexeme.end(), lexeme.begin(), ::tolower);
  SymbolTableEntry* entry = NULL;
  for(std::size_t n = 0 ; n < m_table.size() ; n++)
  {
    if(m_table[n]->lexeme == lexeme)
    {
      entry = m_table[n];
      break;
    }
  }
  return entry;
}
