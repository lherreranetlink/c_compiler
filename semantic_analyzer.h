#ifndef SEMANTIC_ANALYZER_H_INCLUDED
#define SEMANTIC_ANALYZER_H_INCLUDED
#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "symbol_table.h"
#include "grammar_attributes.h"
#include "semantic_analyzer.h"

void analyzeSemantics(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTableHeader);
void calculateAttributesForStatement(SyntaxTreeNode* statement);
void calculateAttributesForExpression(SyntaxTreeNode* expression);
void calculateAttributesForBlock(SyntaxTreeNode* block);
void semantic_error();

#endif // SEMANTIC_ANALYZER_H_INCLUDED
