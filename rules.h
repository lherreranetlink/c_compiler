#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

typedef enum { IF_STATEMENT_NODE, WHILE_STATEMENT_NODE, ASSIGNMENT_STATEMENT_NODE, PRINT_EXPRESSION_STATEMENT_NODE,
               PRINT_CONST_STRING_NODE, VAR_DECLARATION_STATEMENT_NODE, IDENTIFIER_NODE, INTEGER_NODE, REAL_NUMBER_NODE,
               ADDITION_OPERATION_NODE, MULTIPLICATION_OPERATION_NODE, EQUALS_COMPARISON_OPERATION_NODE, UNARY_OPERATION_NODE,
               NEGATION_OPERATION_NODE, RELATIONAL_OPERATION_NODE, AND_OPERATION_NODE
             } RuleType;

#endif // RULES_H_INCLUDED
