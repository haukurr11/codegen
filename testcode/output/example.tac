               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              1                             i
               VAR                                           t0
            UMINUS              1                            t0
            ASSIGN             t0                             j
               VAR                                           t1
                GT              i              0           lab2
            ASSIGN              0                            t1
              GOTO                                         lab3
   lab2:    ASSIGN              1                            t1
   lab3:        EQ             t1              0           lab1
               VAR                                           t2
              MULT              j              3             t2
               VAR                                           t3
               SUB              1             t2             t3
            ASSIGN             t3                             i
              GOTO                                         lab0
   lab1:       VAR                                           t4
               ADD              i              1             t4
            ASSIGN             t4                             i
   lab0:    APARAM                                            i
              CALL        writeln                              
            RETURN                                             
