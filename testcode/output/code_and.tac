               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              0                             i
            ASSIGN              6                             j
               VAR                                           t0
                LT              i              1           lab2
            ASSIGN              0                            t0
              GOTO                                         lab3
   lab2:    ASSIGN              1                            t0
   lab3:       VAR                                           t1
                GT              j              5           lab4
            ASSIGN              0                            t1
              GOTO                                         lab5
   lab4:    ASSIGN              1                            t1
   lab5:       VAR                                           t2
               AND             t0             t1             t2
                EQ             t2              0           lab1
               VAR                                           t3
               ADD              j              1             t3
            ASSIGN             t3                             j
              GOTO                                         lab0
   lab1:       VAR                                           t4
               SUB              i              1             t4
            ASSIGN             t4                             i
   lab0:    APARAM                                            i
              CALL        writeln                              
            APARAM                                            j
              CALL        writeln                              
            RETURN                                             
