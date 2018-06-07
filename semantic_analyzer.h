#ifndef SEMANTIC_ANALYZER_H_INCLUDED
#define SEMANTIC_ANALYZER_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "parser.h"
#include "symbol_table.h"
#include "grammar_attributes.h"
#include "semantic_analyzer.h"

void analyzeSemantics(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTableHeader);
void calculateAttributesForStatement(SyntaxTreeNode* statement);
void calculateAttributesForExpression(SyntaxTreeNode* expression);
void calculateAttributesForBlock(SyntaxTreeNode* block);
SemanticType getOperationDataType(SemanticType type1, SemanticType type2);
void semantic_error(char* msg);

#endif // SEMANTIC_ANALYZER_H_INCLUDED
