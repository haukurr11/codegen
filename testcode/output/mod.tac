               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN            100                             i
            ASSIGN             26                             j
               VAR                                           t1
               MOD              i              j             t1
            APARAM                                           t1
              CALL        writeln                              
            RETURN                                             
