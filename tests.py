import os
import sys

def default_test(progname):
  os.system('./codegen < testcode/' + progname
          + '.prg > testcode/output/' + progname + '.tac')
  output = os.popen('java -jar tac/JTacInt.jar testcode/output/' 
                    + progname + '.tac').read()
  output = (output.replace("TacInt. Version (1.0)","").strip())
  correct = os.popen('java -jar tac/JTacInt.jar testcode/' 
                    + progname + '.tac').read()
  correct = (correct.replace("TacInt. Version (1.0)","").strip())
  return (output,correct)

progs = ["code_if","code_and","code_while","code_func","code_fact"]

print "TESTING DEFAULT PROGRAMS...\n"
for prog in progs:
  sys.stdout.write("Testing " + prog + "...")
  result = default_test(prog)
  if result[0] == result[1]:
     print "PASSED (" + ",".join(result[0].split("\n")) + ")"
  else:
     print "FAILED!"
     print "correct output:\n" \
           + str(result[1]) \
           + "\nreceived output:\n" \
           + str(result[0])

progs = {"simpleaddition":3,
         "simplemultiplication":6,
         "operatortest" : 5376,
         "mod" : 22,
         "real" : 11.1,
         "fibonacci" : 6765 }
def custom_test(progname):
   correct = progs[progname]
   os.system('./codegen < testcode/extra/' + progname
          + '.prg > testcode/output/' + progname + '.tac')
   output = os.popen('java -jar tac/JTacInt.jar testcode/output/'
                    + progname + '.tac').read()
   output = (output.replace("TacInt. Version (1.0)","").strip())
   return (str(output),str(correct))


print "\nTESTING CUSTOM PROGRAMS...\n"
for prog in progs:
  sys.stdout.write("Testing " + prog + "...")
  result = custom_test(prog)
  if result[0] == result[1]:
     print "PASSED (" + ",".join(result[0].split("\n")) + ")"
  else:
     print "FAILED!"
     print "correct output:\n" \
           + str(result[1]) \
           + "\nreceived output:\n" \
           + str(result[0])
