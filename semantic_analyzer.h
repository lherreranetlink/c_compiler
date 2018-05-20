#ifndef SEMANTIC_ANALYZER_H_INCLUDED
#define SEMANTIC_ANALYZER_H_INCLUDED
#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "symbol_table.h"
#include "semantic_type.h"
#include "semantic_analyzer.h"

void analyzeSemantics(SyntaxTreeNode** treeRoot);
void calculateTypeForStatement(SyntaxTreeNode* statement);
void calculateTypeForRelationalExpression(SyntaxTreeNode* relationalExpression);
void calculateTypeForBlock(SyntaxTreeNode* block);
void semantic_error();

#endif // SEMANTIC_ANALYZER_H_INCLUDED
