#ifndef SEMANTIC_ANALYZER_H_INCLUDED
#define SEMANTIC_ANALYZER_H_INCLUDED
#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "symbol_table.h"
#include "grammar_attributes.h"
#include "semantic_analyzer.h"

void analyzeSemantics(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTableHeader);
void calculateTypeForStatement(SyntaxTreeNode* statement);
void calculateTypeForExpression(SyntaxTreeNode* expression);
void calculateTypeForBlock(SyntaxTreeNode* block);
void semantic_error();
SemanticType getType(SemanticType type1, SemanticType type2);

#endif // SEMANTIC_ANALYZER_H_INCLUDED
