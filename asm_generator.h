#ifndef ASM_GENERATOR_H_INCLUDED
#define ASM_GENERATOR_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "semantic_analyzer.h"

void generate_asm(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTable);
void generateDependencies();
void generateDataSection();
void generateStatementCode(SyntaxTreeNode* statement);
void generateExpressionCode(SyntaxTreeNode* expression);
void generateBlockCode(SyntaxTreeNode* block);
void setConditionString(char* relationalOp, char* symbol);


#endif // ASM_GENERATOR_H_INCLUDED
