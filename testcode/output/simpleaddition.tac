               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              1                             i
            ASSIGN              2                             j
               VAR                                           t0
               ADD              i              j             t0
            APARAM                                           t0
              CALL        writeln                              
            RETURN                                             
