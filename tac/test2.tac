               VAR                                            i
              GOTO                                      example
 caller:    FPARAM                                            a
            FPARAM                                            b
               VAR                                            x
               VAR                                           t1
               SUB              a              b             t1
            ASSIGN             t1                             x
            ASSIGN              x                        caller
            RETURN                                             
example:       VAR                                           t2
              MULT              2              3             t2
               VAR                                           t3
               ADD              1             t2             t3
               VAR                                           t4
              MULT              2              5             t4
               VAR                                           t5
            UMINUS             t4                            t5
            APARAM                                           t3
            APARAM                                           t5
              CALL         caller                              
            ASSIGN         caller                             i
            APARAM                                            i
              CALL        writeln                              
            RETURN                                             
