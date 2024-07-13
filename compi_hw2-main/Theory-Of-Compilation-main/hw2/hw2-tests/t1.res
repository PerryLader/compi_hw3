16: Type -> INT
23: Exp -> NUM
6: Statement -> Type ID ASSIGN Exp SC
2: Statements -> Statement
17: Type -> BYTE
24: Exp -> NUM B
6: Statement -> Type ID ASSIGN Exp SC
3: Statements -> Statements Statement
21: Exp -> ID
21: Exp -> ID
31: Exp -> Exp RELOP Exp
25: Exp -> STRING
15: Call -> ID LPAREN Exp RPAREN
8: Statement -> Call SC
10: Statement -> IF LPAREN Exp RPAREN Statement
3: Statements -> Statements Statement
16: Type -> INT
5: Statement -> Type ID SC
3: Statements -> Statements Statement
1: Program -> Statements
