               VAR                                            i
               VAR                                            j
              GOTO                                      example
example:    ASSIGN              0                             i
            ASSIGN              6                             j
               VAR                                           t1
                EQ              i              0           lab3
            ASSIGN              0                            t1
              GOTO                                         lab4
   lab3:    ASSIGN              1                            t1
   lab4:       VAR                                           t2
                GT              j              6           lab5
            ASSIGN              0                            t2
              GOTO                                         lab6
   lab5:    ASSIGN              1                            t2
   lab6:       VAR                                           t3
                OR             t1             t2             t3
                EQ             t3              0           lab2
            ASSIGN           1337                             j
              GOTO                                         lab1
   lab2:       VAR                                           t4
            UMINUS              1                            t4
            ASSIGN             t4                             j
   lab1:       VAR                                           t5
                EQ              j           1336           lab9
            ASSIGN              0                            t5
              GOTO                                        lab10
   lab9:    ASSIGN              1                            t5
  lab10:       VAR                                           t6
               NOT             t5                            t6
                EQ             t6              0           lab8
               VAR                                           t7
               ADD              j              1             t7
            ASSIGN             t7                             j
              GOTO                                         lab7
   lab8:    ASSIGN              0                             j
   lab7:       VAR                                           t8
                NE              j              0          lab13
            ASSIGN              0                            t8
              GOTO                                        lab14
  lab13:    ASSIGN              1                            t8
  lab14:        EQ             t8              0          lab12
               VAR                                           t9
               ADD              j              2             t9
            ASSIGN             t9                             j
              GOTO                                        lab11
  lab12:    ASSIGN              1                             j
  lab11:       VAR                                          t10
                LE              j           1339          lab17
            ASSIGN              0                           t10
              GOTO                                        lab18
  lab17:    ASSIGN              1                           t10
  lab18:        EQ            t10              0          lab16
            ASSIGN              2                             j
              GOTO                                        lab15
  lab16:       VAR                                          t11
               ADD              j              5            t11
               VAR                                          t12
            DIVIDE            t11              2            t12
            ASSIGN            t12                             j
  lab15:    APARAM                                            j
              CALL        writeln                              
            RETURN                                             
