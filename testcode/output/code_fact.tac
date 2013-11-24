               VAR                                            j
               VAR                                            n
              GOTO                                      example
   fact:    FPARAM                                            n
               VAR                                            k
               VAR                                           t0
                LT              n              1           lab2
            ASSIGN              0                            t0
              GOTO                                         lab3
   lab2:    ASSIGN              1                            t0
   lab3:        EQ             t0              0           lab1
            ASSIGN              1                          fact
              GOTO                                         lab0
   lab1:       VAR                                           t1
               SUB              n              1             t1
            APARAM                                           t1
              CALL           fact                              
            ASSIGN           fact                             k
               VAR                                           t2
              MULT              n              k             t2
            ASSIGN             t2                          fact
   lab0:    RETURN                                             
example:    ASSIGN              5                             j
   lab4:       VAR                                           t3
                GT              j              0           lab6
            ASSIGN              0                            t3
              GOTO                                         lab7
   lab6:    ASSIGN              1                            t3
   lab7:        EQ             t3              0           lab5
            APARAM                                            j
              CALL           fact                              
            ASSIGN           fact                             n
            APARAM                                            n
              CALL        writeln                              
               VAR                                           t4
               SUB              j              1             t4
            ASSIGN             t4                             j
              GOTO                                         lab4
   lab5:    RETURN                                             
