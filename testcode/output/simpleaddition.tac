               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              1                             i
            ASSIGN              2                             j
               VAR                                           t1
               ADD              i              j             t1
            APARAM                                           t1
              CALL        writeln                              
            RETURN                                             
