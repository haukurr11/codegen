               VAR                                            x
               VAR                                            y
              GOTO                                         test
   test:       VAR                                           t1
               ADD              x              y             t1
            ASSIGN             t1                           add
               VAR                                           t2
              MULT              x              y             t2
            ASSIGN             t2                          mult
               VAR                                            y
            ASSIGN              x                             y
            APARAM                                            y
              CALL        writeln                              
            ASSIGN              3                             x
            APARAM                                            x
              CALL       toscreen                              
            APARAM                                            x
            APARAM                                            2
              CALL            add                              
            ASSIGN            add                             x
            APARAM                                            x
              CALL       toscreen                              
            APARAM                                            x
            APARAM                                            3
              CALL           mult                              
            ASSIGN           mult                             x
            APARAM                                            x
              CALL       toscreen                              
            RETURN                                             
