               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN            5.5                             i
            ASSIGN            5.6                             j
               VAR                                           t1
               ADD              i              j             t1
            APARAM                                           t1
              CALL        writeln                              
            RETURN                                             
