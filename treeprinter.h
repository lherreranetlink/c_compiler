#ifndef TREEPRINTER_H_INCLUDED
#define TREEPRINTER_H_INCLUDED
#include "rules.h"
#include <stdio.h>
#include <string.h>

void printSyntaxTree(SyntaxTreeNode* initial);
void printStatement(SyntaxTreeNode* statement);
void printRelationalExpression(SyntaxTreeNode* relationalExpression);
void printBlock(SyntaxTreeNode* block);
void printExpression(SyntaxTreeNode* expression);

#endif // TREEPRINTER_H_INCLUDED
