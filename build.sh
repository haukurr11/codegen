flex compiler.lex
g++ *.cpp -o codegen -g
./codegen < testcode/code_while.prg
python tests.py
