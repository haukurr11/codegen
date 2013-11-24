               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              3                             i
            ASSIGN              2                             j
               VAR                                           t1
              MULT              i              j             t1
            APARAM                                           t1
              CALL        writeln                              
            RETURN                                             
