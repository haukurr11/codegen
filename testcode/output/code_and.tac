               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              0                             i
            ASSIGN              6                             j
               VAR                                           t1
                LT              i              1           lab1
            ASSIGN              0                            t1
              GOTO                                         lab2
   lab1:    ASSIGN              1                            t1
   lab2:        EQ             t1              0           lab2
               VAR                                           t2
                GT              j              5           lab3
            ASSIGN              0                            t2
              GOTO                                         lab4
   lab3:    ASSIGN              1                            t2
   lab4:        EQ             t2              0           lab4
               VAR                                           t3
              MULT              i              j             t3
               VAR                                           t4
               ADD              j              1             t4
            ASSIGN             t4                             j
   lab5:       VAR                                           t5
               SUB              i              1             t5
            ASSIGN             t5                             i
              GOTO                                         lab6
   lab6:    APARAM                                            i
              CALL        writeln                              
            APARAM                                            j
              CALL        writeln                              
            RETURN                                             
