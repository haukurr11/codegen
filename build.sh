flex compiler.lex
g++ *.cpp -o codegen -g
./codegen < testcode/code_and.prg
python tests.py
