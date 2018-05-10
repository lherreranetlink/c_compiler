#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED
#include "token.h"

typedef enum {IF_STATEMENT_NODE, WHILE_STATEMENT_NODE, ASSIGNMENT_STATEMENT_NODE, PRINT_EXPRESSION_STATEMENT_NODE,
              PRINT_CONST_STRING_NODE, IDENTIFIER_NODE, INTEGER_NODE, REAL_NUMBER_NODE, ADDITION_OPERATION_NODE,
              MULTIPLICATION_OPERATION_NODE, EQUALS_COMPARISON_OPERATION_NODE, UNARY_OPERATION_NODE, NEGATION_OPERATION_NODE,
              RELATIONAL_OPERATION_NODE, AND_OPERATION_NODE
             } RuleType;

typedef struct SyntaxTreeNode
{
    RuleType ruleType;

    struct SyntaxTreeNode* expression;
    struct SyntaxTreeNode* ifPart;
    struct SyntaxTreeNode* elsePart;
    struct SyntaxTreeNode* blockStatements;
    struct SyntaxTreeNode* operand1;
    struct SyntaxTreeNode* operand2;
    Token* identfier;
    Token* integer;
    Token* realNumber;
    Token* sign;
    Token* constString;

    struct SyntaxTreeNode* next;

} SyntaxTreeNode;


#endif // RULES_H_INCLUDED
