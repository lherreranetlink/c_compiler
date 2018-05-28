#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#define ADDITION_SIGN "+"
#define SUBSTRACTION_SIGN "-"
#define MULT_SIGN "*"
#define DIV_SIGN "/"
#define AND_SIGN "&&"
#define OR_SIGN "||"
#define EQ_COMPARISON_SIGN "=="
#define NE_COMPARISON_SIGN "!="
#define LT_SIGN "<"
#define LTE_SIGN "<="
#define GT_SIGN ">"
#define GTE_SIGN ">="

typedef enum TokenType {IDENTIFIER, INTEGER, REAL_NUMBER, CONST_STRING, DATA_TYPE, ADD_OPERATOR, MULT_OPERATOR,
                        RELATIONAL_OPERATOR, EQUALS_COMPARISON_OPERATOR, LOGIC_OR_OPERATOR, LOGIC_AND_OPERATOR,
                        NEGATION_OPERATOR, SEMICOLON, COMA, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, LEFT_BRACE, RIGHT_BRACE,
                        ASSIGNMENT_OPERATOR, IF_KEYWORD, WHILE_KEYWORD, RETURN_KEYWORD, ELSE_KEYWORD, PRINT_KEYWORD, EOF_SIGN
                       } TokenType;

typedef struct Token
{
    char* symbol;
    TokenType type;
} Token;

#endif // TOKEN_H_INCLUDED
