               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              0                             i
            ASSIGN              6                             j
               VAR                                           t0
                EQ              i              0           lab2
            ASSIGN              0                            t0
              GOTO                                         lab3
   lab2:    ASSIGN              1                            t0
   lab3:       VAR                                           t1
                GT              j              6           lab4
            ASSIGN              0                            t1
              GOTO                                         lab5
   lab4:    ASSIGN              1                            t1
   lab5:       VAR                                           t2
                OR             t0             t1             t2
                EQ             t2              0           lab1
            ASSIGN           1337                             j
              GOTO                                         lab0
   lab1:       VAR                                           t3
            UMINUS              1                            t3
            ASSIGN             t3                             j
   lab0:       VAR                                           t4
                EQ              j           1336           lab8
            ASSIGN              0                            t4
              GOTO                                         lab9
   lab8:    ASSIGN              1                            t4
   lab9:       VAR                                           t5
               NOT             t4                            t5
                EQ             t5              0           lab7
               VAR                                           t6
               ADD              j              1             t6
            ASSIGN             t6                             j
              GOTO                                         lab6
   lab7:    ASSIGN              0                             j
   lab6:       VAR                                           t7
                NE              j              0          lab12
            ASSIGN              0                            t7
              GOTO                                        lab13
  lab12:    ASSIGN              1                            t7
  lab13:        EQ             t7              0          lab11
               VAR                                           t8
               ADD              j              2             t8
            ASSIGN             t8                             j
              GOTO                                        lab10
  lab11:    ASSIGN              1                             j
  lab10:       VAR                                           t9
                LE              j           1339          lab16
            ASSIGN              0                            t9
              GOTO                                        lab17
  lab16:    ASSIGN              1                            t9
  lab17:        EQ             t9              0          lab15
            ASSIGN              2                             j
              GOTO                                        lab14
  lab15:       VAR                                          t10
               ADD              j              5            t10
               VAR                                          t11
            DIVIDE            t10              2            t11
            ASSIGN            t11                             j
  lab14:       VAR                                          t12
                GE              j            600          lab20
            ASSIGN              0                           t12
              GOTO                                        lab21
  lab20:    ASSIGN              1                           t12
  lab21:        EQ            t12              0          lab19
               VAR                                          t13
              MULT              j              8            t13
            ASSIGN            t13                             j
              GOTO                                        lab18
  lab19:    ASSIGN              3                             j
  lab18:    APARAM                                            j
              CALL        writeln                              
            RETURN                                             
