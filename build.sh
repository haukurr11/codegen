flex compiler.lex
g++ *.cpp -o codegen -g
./codegen < testcode/code_func.prg
python tests.py
