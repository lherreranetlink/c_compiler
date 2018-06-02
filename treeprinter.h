#ifndef TREEPRINTER_H_INCLUDED
#define TREEPRINTER_H_INCLUDED
#include "rules.h"
#include "tree_node.h"
#include <stdio.h>
#include <string.h>

void printSyntaxTree(SyntaxTreeNode* initial);
void printStatement(SyntaxTreeNode* statement);
void printExpression(SyntaxTreeNode* expression);
void printBlock(SyntaxTreeNode* block);
void printRelationalExpression(SyntaxTreeNode* relationalExpression);
void printVarDeclaration(SyntaxTreeNode* varDecl);
void printVarList(SyntaxTreeNode* varList);

#endif // TREEPRINTER_H_INCLUDED
