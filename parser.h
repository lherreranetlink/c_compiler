#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "tree_node.h"
#include "token.h"
#include "lex.h"

SyntaxTreeNode* parse(FILE* fileToAnalyze);
SyntaxTreeNode* program();
SyntaxTreeNode* singleStatement();
SyntaxTreeNode* expression();
SyntaxTreeNode* equalsComparisonExpression();
SyntaxTreeNode* relationalExpression();
SyntaxTreeNode* addition();
SyntaxTreeNode* multiplication();
SyntaxTreeNode* factor();
SyntaxTreeNode* blockStatement();
SyntaxTreeNode* elsePart();
SyntaxTreeNode* block();
SyntaxTreeNode* printableStatement();
SyntaxTreeNode* assignment();
SyntaxTreeNode* varDeclaration();
SyntaxTreeNode* varList();
void match(TokenType type);
void error();

#endif // PARSER_H_INCLUDED
