               VAR                                       result
              GOTO                                      example
fibonacci:    FPARAM                                            n
               VAR                                     firstval
               VAR                                    secondval
            ASSIGN              0                     fibonacci
               VAR                                           t1
                EQ              n              1           lab3
            ASSIGN              0                            t1
              GOTO                                         lab4
   lab3:    ASSIGN              1                            t1
   lab4:       VAR                                           t2
                EQ              n              2           lab5
            ASSIGN              0                            t2
              GOTO                                         lab6
   lab5:    ASSIGN              1                            t2
   lab6:       VAR                                           t3
                OR             t1             t2             t3
                EQ             t3              0           lab2
            ASSIGN              1                     fibonacci
              GOTO                                         lab1
   lab2:       VAR                                           t4
               SUB              n              1             t4
            APARAM                                           t4
              CALL      fibonacci                              
            ASSIGN      fibonacci                      firstval
               VAR                                           t5
               SUB              n              2             t5
            APARAM                                           t5
              CALL      fibonacci                              
            ASSIGN      fibonacci                     secondval
               VAR                                           t6
               ADD       firstval      secondval             t6
            ASSIGN             t6                     fibonacci
   lab1:    RETURN                                             
example:    APARAM                                           20
              CALL      fibonacci                              
            ASSIGN      fibonacci                        result
            APARAM                                       result
              CALL        writeln                              
            RETURN                                             
