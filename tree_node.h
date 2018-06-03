#ifndef TREE_NODE_H_INCLUDED
#define TREE_NODE_H_INCLUDED
#include "token.h"
#include "rules.h"
#include "grammar_attributes.h"

typedef struct SyntaxTreeNode
{
    RuleType ruleType;
    SemanticType semanticType;
    union
    {
        int integerVal;
        float floatVal;
    } value;

    struct SyntaxTreeNode* expression;
    struct SyntaxTreeNode* ifPart;
    struct SyntaxTreeNode* elsePart;
    struct SyntaxTreeNode* blockStatements;
    struct SyntaxTreeNode* operand1;
    struct SyntaxTreeNode* operand2;
    struct SyntaxTreeNode* varList;
    Token* dataType;
    Token* identifier;
    Token* integer;
    Token* realNumber;
    Token* sign;
    Token* constString;

    struct SyntaxTreeNode* next;

} SyntaxTreeNode;


#endif // TREE_NODE_H_INCLUDED
