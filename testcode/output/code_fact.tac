               VAR                                            n
               VAR                                            j
              GOTO                                      example
example:       VAR                                            k
               VAR                                           t1
                LT              n              1           lab1
            ASSIGN              0                            t1
              GOTO                                         lab2
   lab1:    ASSIGN              1                            t1
   lab2:        EQ             t1              0           lab2
            ASSIGN              1                          fact
   lab3:       VAR                                           t2
               SUB              n              1             t2
            APARAM                                           t2
              CALL           fact                              
            ASSIGN           fact                             k
               VAR                                           t3
              MULT              n              k             t3
            ASSIGN             t3                          fact
              GOTO                                         lab4
   lab4:    ASSIGN              5                             j
               VAR                                           t4
                GT              j              0           lab5
            ASSIGN              0                            t4
              GOTO                                         lab6
   lab5:    ASSIGN              1                            t4
   lab6:        EQ             t4              0           lab6
            APARAM                                            j
              CALL           fact                              
            ASSIGN           fact                             n
            APARAM                                            n
              CALL        writeln                              
               VAR                                           t5
               SUB              j              1             t5
            ASSIGN             t5                             j
            RETURN                                             
