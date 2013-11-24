               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN            5.5                             i
            ASSIGN            5.6                             j
               VAR                                           t0
               ADD              i              j             t0
            APARAM                                           t0
              CALL        writeln                              
            RETURN                                             
