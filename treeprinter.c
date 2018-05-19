#include "treeprinter.h"

static FILE* outFd;

void printSyntaxTree(SyntaxTreeNode* initial)
{
    outFd = fopen("salida.txt", "w");
    if (initial != NULL)
    {
        fprintf(outFd, "<PROGRAMA>\n");

        SyntaxTreeNode* aux;
        for (aux = initial; aux != NULL; aux = aux->next)
            printStatement(aux);

        fprintf(outFd, "</PROGRAMA>\n");
    }
    fclose(outFd);
}

void printStatement(SyntaxTreeNode* statement)
{
    int statementType = statement->ruleType;
    switch(statementType)
    {
    case IF_STATEMENT_NODE:
        fprintf(outFd, "<SI>\n");
        printExpression(statement->expression);
        fprintf(outFd, "<BLOQUE>\n");
        printBlock(statement->ifPart);
        fprintf(outFd, "</BLOQUE>\n");
        fprintf(outFd, "<OTRO>\n");
        printBlock(statement->elsePart);
        fprintf(outFd, "</OTRO>\n");
        fprintf(outFd, "</SI>\n");
        break;
    case WHILE_STATEMENT_NODE:
        fprintf(outFd, "<MIENTRAS>\n");
        printExpression(statement->expression);
        fprintf(outFd, "<BLOQUE>\n");
        printBlock(statement->blockStatements);
        fprintf(outFd, "</BLOQUE>\n");
        fprintf(outFd, "</MIENTRAS>\n");
        break;
    case PRINT_CONST_STRING_NODE:
        //TODO: print const string node
        fprintf(outFd, "<IMPRIME>\n");
        fprintf(outFd, "</IMPRIME>\n");
        break;
    case PRINT_EXPRESSION_STATEMENT_NODE:
        fprintf(outFd, "<IMPRIME>\n");
        fprintf(outFd, "<EXPRESION>\n");
        printExpression(statement->expression);
        fprintf(outFd, "</EXPRESION>\n");
        fprintf(outFd, "</IMPRIME>\n");
        break;
    case ASSIGNMENT_STATEMENT_NODE:
        fprintf(outFd, "<ASIGNACION>\n");
        fprintf(outFd, "<ID>");
        fprintf(outFd, "%s", statement->identfier->symbol);
        fprintf(outFd, "</ID>\n");
        printExpression(statement->expression);
        fprintf(outFd, "</ASIGNACION>\n");
    }
}

void printExpression(SyntaxTreeNode* expression)
{
    int expressionType = expression->ruleType;
    switch(expressionType)
    {
    case ADDITION_OPERATION_NODE:
        fprintf(outFd, "<SUMA value=\"%s\">\n", expression->sign->symbol);
        printExpression(expression->operand1);
        printExpression(expression->operand2);
        fprintf(outFd, "</SUMA>\n");
        break;
    case MULTIPLICATION_OPERATION_NODE:
        fprintf(outFd, "<MULT value=\"%s\">\n", expression->sign->symbol);
        printExpression(expression->operand1);
        printExpression(expression->operand2);
        fprintf(outFd, "</MULT>\n");
        break;
    case EQUALS_COMPARISON_OPERATION_NODE:
        fprintf(outFd, "<IGUALDAD value=\"%s\">\n", expression->sign->symbol);
        printExpression(expression->operand1);
        printExpression(expression->operand2);
        fprintf(outFd, "</IGUALDAD>\n");
        break;
    case UNARY_OPERATION_NODE:
        fprintf(outFd, "<SIGNO value=\"%s\">\n", expression->sign->symbol);
        printExpression(expression->expression);
        fprintf(outFd, "</SIGNO>\n");
        break;
    case NEGATION_OPERATION_NODE:
        fprintf(outFd, "<NEGACION>\n");
        printExpression(expression->expression);
        fprintf(outFd, "</NEGACION>\n");
        break;
    case RELATIONAL_OPERATION_NODE:
        printRelationalExpression(expression);
        break;
    case AND_OPERATION_NODE:
        if (strcmp(expression->sign->symbol, "&&") == 0)
            fprintf(outFd, "<AND value=\"and\">\n");
        else
            fprintf(outFd, "<AND value=\"or\">\n");

        printExpression(expression->operand1);
        printExpression(expression->operand2);
        fprintf(outFd, "</AND>\n");
        break;
    case IDENTIFIER_NODE:
        fprintf(outFd, "<ID>");
        fprintf(outFd, "%s", expression->identfier->symbol);
        fprintf(outFd, "</ID>\n");
        break;
    case INTEGER_NODE:
        fprintf(outFd, "<ENTERO>");
        fprintf(outFd, "%s", expression->integer->symbol);
        fprintf(outFd, "</ENTERO>\n");
        break;
    case REAL_NUMBER_NODE:
        fprintf(outFd, "<REAL>");
        fprintf(outFd, "%s", expression->realNumber->symbol);
        fprintf(outFd, "</REAL>\n");
    }
}

void printRelationalExpression(SyntaxTreeNode* relationalExpression)
{
    char* relOperator = relationalExpression->sign->symbol;
    if (strcmp(relOperator, "<") == 0)
        fprintf(outFd, "<EXPRESION value=\"&lt;\">\n");
    else if (strcmp(relOperator, "<=") == 0)
        fprintf(outFd, "<EXPRESION value=\"&lt;=\">\n");
    else if (strcmp(relOperator, ">") == 0)
        fprintf(outFd, "<EXPRESION value=\"&gt;\">\n");
    else
        fprintf(outFd, "<EXPRESION value =\"&gt;=\">\n");

    printExpression(relationalExpression->operand1);
    printExpression(relationalExpression->operand2);

    fprintf(outFd, "</EXPRESION>\n");
}

void printBlock(SyntaxTreeNode* block)
{
    SyntaxTreeNode* aux;
    for (aux = block; aux != NULL; aux = aux->next)
        printStatement(aux);
}
