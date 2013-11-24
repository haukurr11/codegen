               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              0                             i
            ASSIGN              1                             j
   lab0:       VAR                                           t0
                LT              i             10           lab2
            ASSIGN              0                            t0
              GOTO                                         lab3
   lab2:    ASSIGN              1                            t0
   lab3:        EQ             t0              0           lab1
               VAR                                           t1
               ADD              i              j             t1
            ASSIGN             t1                             j
               VAR                                           t2
               ADD              i              1             t2
            ASSIGN             t2                             i
              GOTO                                         lab0
   lab1:    APARAM                                            i
              CALL        writeln                              
            APARAM                                            j
              CALL        writeln                              
            RETURN                                             
