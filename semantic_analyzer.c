#include "semantic_analyzer.h"

static FILE* outFd;

void analyzeSemantics(SyntaxTreeNode* treeRoot)
{
    outFd = fopen("salida.txt", "w");
    if (treeRoot != NULL)
    {
        SyntaxTreeNode* aux;
        for (aux = treeRoot; aux != NULL; aux = aux->next)
            calculateTypeForStatemment(aux);
    }
    fprintf(outFd, "1");
    fclose(outFd);
}

void calculateTypeForStatemment(SyntaxTreeNode* statement)
{
int statementType = statement->ruleType;
    switch(statementType)
    {
    case IF_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        calculateTypeForBlock(statement->ifPart);
        calculateTypeForBlock(statement->elsePart);
        break;
    case WHILE_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        calculateTypeForBlock(statement->blockStatements);
        break;
    case PRINT_CONST_STRING_NODE:
        //TODO: print const string node
        break;
    case PRINT_EXPRESSION_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        break;
    case ASSIGNMENT_STATEMENT_NODE:
        /*TODO: validate symbol table verifications and insertions*/
        fprintf(outFd, "%s", statement->identfier->symbol);
        printExpression(statement->expression);
    }
}

void calculateTypeForRelationalExpression(SyntaxTreeNode* relationalExpression)
{

}

void calculateTypeForBlock(SyntaxTreeNode* block)
{

}

void calculateTypeForExpression(SyntaxTreeNode* expression)
{

}

void semantic_error()
{
    fprintf(outFd, "0");
    fclose(outFd);
    exit(1);
}
