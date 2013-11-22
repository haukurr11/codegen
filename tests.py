import os

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

#progs = ["code_and","code_func","code_while", "code_fact","code_if"]
progs = ["code_if"]


print "TESTING...\n"
for prog in progs:
  print "Testing " + prog + "..."
  result = testprog(prog)
  if result[0] == result[1]:
     print "test PASSED: " + prog
  else:
     print "test FAILED!"
     print "correct output:\n" \
           + str(result[1]) \
           + "\nreceived output:\n" \
           + str(result[0])
  print "\n"
