               VAR                                       result
              GOTO                                      example
fibonacci:    FPARAM                                            n
               VAR                                     firstval
               VAR                                    secondval
            ASSIGN              0                     fibonacci
               VAR                                           t0
                EQ              n              1           lab2
            ASSIGN              0                            t0
              GOTO                                         lab3
   lab2:    ASSIGN              1                            t0
   lab3:       VAR                                           t1
                EQ              n              2           lab4
            ASSIGN              0                            t1
              GOTO                                         lab5
   lab4:    ASSIGN              1                            t1
   lab5:       VAR                                           t2
                OR             t0             t1             t2
                EQ             t2              0           lab1
            ASSIGN              1                     fibonacci
              GOTO                                         lab0
   lab1:       VAR                                           t3
               SUB              n              1             t3
            APARAM                                           t3
              CALL      fibonacci                              
            ASSIGN      fibonacci                      firstval
               VAR                                           t4
               SUB              n              2             t4
            APARAM                                           t4
              CALL      fibonacci                              
            ASSIGN      fibonacci                     secondval
               VAR                                           t5
               ADD       firstval      secondval             t5
            ASSIGN             t5                     fibonacci
   lab0:    RETURN                                             
example:    APARAM                                           20
              CALL      fibonacci                              
            ASSIGN      fibonacci                        result
            APARAM                                       result
              CALL        writeln                              
            RETURN                                             
