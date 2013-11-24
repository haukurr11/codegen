#include "parser.h"
#include "code.h"

int main(int argc, char** argv)
{
  Parser* parser = new Parser(std::cin, std::cout);
  parser->parse();
  delete parser;
  return 0;
}

