               VAR                                            j
               VAR                                            i
              GOTO                                      example
example:    ASSIGN              0                             i
            ASSIGN              1                             j
               VAR                                           t1
                LT              i             10           lab1
            ASSIGN              0                            t1
              GOTO                                         lab2
   lab1:    ASSIGN              1                            t1
   lab2:        EQ             t1              0           lab2
               VAR                                           t2
               ADD              i              j             t2
            ASSIGN             t2                             j
               VAR                                           t3
               ADD              i              1             t3
            ASSIGN             t3                             i
            APARAM                                            i
              CALL        writeln                              
            APARAM                                            j
              CALL        writeln                              
            RETURN                                             
