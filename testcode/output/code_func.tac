               VAR                                            x
               VAR                                            y
              GOTO                                         test
    add:    FPARAM                                            x
            FPARAM                                            y
               VAR                                           t0
               ADD              x              y             t0
            ASSIGN             t0                           add
            RETURN                                             
   mult:    FPARAM                                            x
            FPARAM                                            y
               VAR                                           t1
              MULT              x              y             t1
            ASSIGN             t1                          mult
            RETURN                                             
toscreen:    FPARAM                                            x
               VAR                                            y
            ASSIGN              x                             y
            APARAM                                            y
              CALL        writeln                              
            RETURN                                             
   test:    ASSIGN              3                             x
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
