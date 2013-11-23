import os
import sys

def testprog(progname):
  os.system('./codegen < testcode/' + progname
          + '.prg > testcode/output/' + progname + '.tac')
  output = os.popen('java -jar tac/JTacInt.jar testcode/output/' 
                    + progname + '.tac').read()
  output = (output.replace("TacInt. Version (1.0)","").strip())
  correct = os.popen('java -jar tac/JTacInt.jar testcode/' 
                    + progname + '.tac').read()
  correct = (correct.replace("TacInt. Version (1.0)","").strip())
  return (output,correct)

#progs = ["code_func","code_while", "code_fact"]
progs = ["code_if","code_and","code_while"]


print "TESTING...\n"
for prog in progs:
  sys.stdout.write("Testing " + prog + "...")
  result = testprog(prog)
  if result[0] == result[1]:
     print "PASSED"
  else:
     print "FAILED!"
     print "correct output:\n" \
           + str(result[1]) \
           + "\nreceived output:\n" \
           + str(result[0])
