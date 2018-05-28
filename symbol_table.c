#include "symbol_table.h"

void insertNode(SymbolTableNode** tableHeader, SyntaxTreeNode* node)
{
    SymbolTableNode* symbol = (SymbolTableNode*) malloc(sizeof(SymbolTableNode));
    symbol->data = node;
    symbol->next= NULL;

    if (*tableHeader != NULL)
    {
        SymbolTableNode* aux;
        for (aux = *tableHeader; aux->next != NULL; aux = aux->next);

        aux->next = symbol;

    }
    else
        *tableHeader = symbol;
}

int existsNode(SymbolTableNode** tableHeader, char* identifier)
{
    SymbolTableNode* aux;

    for (aux = *tableHeader; aux != NULL; aux = aux->next)
        if (strcmp(identifier, aux->data->identifier->symbol) == 0)
            return 1;

    return 0;
}

SyntaxTreeNode* getNode(SymbolTableNode** tableHeader, char* identifier)
{
    SymbolTableNode* aux;

    for (aux = *tableHeader; aux != NULL; aux = aux->next)
        if (strcmp(identifier, aux->data->identifier->symbol) == 0)
            return aux->data;

    return NULL;
}

void updateNode(SymbolTableNode** tableHeader, SyntaxTreeNode* node)
{
    SymbolTableNode* aux;
    for (aux = *tableHeader; aux != NULL; aux = aux->next)
        if (strcmp(node->identifier->symbol, aux->data->identifier->symbol) == 0)
        {
            aux->data = node;
            break;
        }
}
