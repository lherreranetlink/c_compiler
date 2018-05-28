#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include "tree_node.h"

typedef struct SymbolTableNode
{
    SemanticType type;
    SyntaxTreeNode* data;

    struct SymbolTableNode* next;
} SymbolTableNode;

void insertNode(SymbolTableNode** tableHeader, SyntaxTreeNode* node);
int existsNode(SymbolTableNode** tableHeader, char* identifier);
SyntaxTreeNode* getNode(SymbolTableNode** tableHeader, char* identifier);
void updateNode(SymbolTableNode** tableHeader, SyntaxTreeNode* node);

#endif // SYMBOL_TABLE_H_INCLUDED
