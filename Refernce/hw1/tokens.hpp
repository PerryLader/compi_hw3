#ifndef TOKENS_HPP_
#define TOKENS_HPP_
  enum tokentype
  {
    UNPRINTABLE_CHAR = -3,
    UNRECOGNIZED_SYMBOL = -2,
    UNCLOSED_STRING = -1,
    END_OF_FILE = 0,

    VOID = 1,
    INT = 2,
    BYTE = 3,
    B = 4,
    BOOL = 5,
    AND = 6,
    OR = 7,
    NOT = 8,
    TRUE = 9,
    FALSE = 10,
    RETURN = 11,
    IF = 12,
    ELSE = 13,
    WHILE = 14,
    BREAK = 15,
    CONTINUE = 16, 
    SC = 17,
    LPAREN = 18,
    RPAREN = 19,
    LBRACE = 20,
    RBRACE = 21,
    ASSIGN = 22,
    RELOP = 23,
    BINOP = 24,
    COMMENT = 25,
    ID = 26,
    NUM = 27,
    STRING = 28,

    STRING_START = 29,
    STRING_END = 30,
    STRING_ESCAPE_N = 31,
    STRING_ESCAPE_R = 32,
    STRING_ESCAPE_T = 33,
    STRING_ESCAPE_BACKSLASH = 34,
    STRING_ESCAPE_QUOTES = 35,
    STRING_ESCAPE_HEX = 36,
    STRING_ESCAPE_0 = 37,
    STRING_CHAR = 38
  };
  extern int yylineno;
  extern char* yytext;
  extern int yyleng;
  extern int yylex();
#endif /* TOKENS_HPP_ */
