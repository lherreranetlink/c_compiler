#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED
#include <stdlib.h>
#include "grammar_attributes.h"
#include "token.h"
#include "string.h"

typedef struct SymbolTableNode
{
    SemanticType type;
    Token* identifier;
    struct SymbolTableNode* next;
} SymbolTableNode;

void insertNode(SymbolTableNode** tableHeader, SemanticType type, Token* identifier);
int existsNode(SymbolTableNode** tableHeader, char* identifier);
SemanticType getType(SymbolTableNode** tableHeader, char* identifier);
void updateType(SymbolTableNode** tableHeader, SemanticType type, char* key);

#endif // SYMBOL_TABLE_H_INCLUDED
