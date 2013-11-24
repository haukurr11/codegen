               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              3                             i
            ASSIGN              2                             j
               VAR                                           t0
              MULT              i              j             t0
            APARAM                                           t0
              CALL        writeln                              
            RETURN                                             
