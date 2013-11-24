               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN            100                             i
            ASSIGN             26                             j
               VAR                                           t0
               MOD              i              j             t0
            APARAM                                           t0
              CALL        writeln                              
            RETURN                                             
