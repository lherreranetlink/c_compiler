#include "symbol_table.h"

void insertNode(SymbolTableNode** tableHeader, SemanticType type, Token* identifier)
{
    if (*tableHeader != NULL)
    {
        SymbolTableNode* aux;
        for (aux = *tableHeader; aux->next != NULL; aux = aux->next);

        SymbolTableNode* symbol = (SymbolTableNode*) malloc(sizeof(SymbolTableNode));
        symbol->identifier = identifier;
        symbol->type = type;
        symbol->next= NULL;

        aux->next = symbol;
    }
}

int existsNode(SymbolTableNode** tableHeader, char* identifier)
{
    SymbolTableNode* aux;

    for (aux = *tableHeader; aux != NULL; aux = aux->next)
        if (strcmp(identifier, aux->identifier->symbol) == 0)
            return 1;

    return 0;
}

SemanticType getType(SymbolTableNode** tableHeader, char* identifier)
{
    SymbolTableNode* aux;

    for (aux = *tableHeader; aux != NULL; aux = aux->next)
        if (strcmp(identifier, aux->identifier->symbol) == 0)
            return aux->type;

    return ERROR_SYMBOL;
}
