#include "semantic_analyzer.h"

static SymbolTableNode* symbolTableHeader;

void analyzeSemantics(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTable)
{
    if (*treeRoot != NULL)
    {
        int errorExists = 0;
        SyntaxTreeNode* aux;
        for (aux = *treeRoot; aux != NULL; aux = aux->next)
        {
            calculateTypeForStatement(aux);
            if (aux->semanticType == ERROR_SYMBOL)
                errorExists = 1;
        }
        if (errorExists)
            semantic_error();

        *symbolTable = symbolTableHeader;
    }
}

void calculateTypeForStatement(SyntaxTreeNode* statement)
{
    int statementType = statement->ruleType;
    switch(statementType)
    {
    case IF_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        calculateTypeForBlock(statement->ifPart);
        calculateTypeForBlock(statement->elsePart);

        statement->semanticType = ((statement->expression->semanticType != ERROR_SYMBOL)
                                   && (statement->ifPart == NULL || statement->ifPart->semanticType == VOID_SYMBOL)
                                   && (statement->elsePart == NULL || statement->elsePart->semanticType == VOID_SYMBOL))
                                  ? VOID_SYMBOL : ERROR_SYMBOL;
        break;
    case WHILE_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        calculateTypeForBlock(statement->blockStatements);

        statement->semanticType = ((statement->expression->semanticType != ERROR_SYMBOL)
                                   && (statement->blockStatements == NULL || statement->blockStatements->semanticType == VOID_SYMBOL))
                                   ? VOID_SYMBOL : ERROR_SYMBOL;
        break;
    case PRINT_CONST_STRING_NODE:
        //TODO: print const string node
        break;
    case PRINT_EXPRESSION_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        statement->semanticType = (statement->expression->semanticType != ERROR_SYMBOL) ? VOID_SYMBOL : ERROR_SYMBOL;
        break;
    case ASSIGNMENT_STATEMENT_NODE:
        calculateTypeForExpression(statement->expression);
        if (statement->expression->semanticType != ERROR_SYMBOL)
        {
            if (existsNode(&symbolTableHeader, statement->identfier->symbol))
                updateType(&symbolTableHeader, statement->expression->semanticType, statement->identfier->symbol);
            else
                insertNode(&symbolTableHeader, statement->expression->semanticType, statement->identfier);
            statement->semanticType = VOID_SYMBOL;
        }
        else
            statement->semanticType = ERROR_SYMBOL;
    }
}

void calculateTypeForExpression(SyntaxTreeNode* expression)
{
    int expressionType = expression->ruleType;
    switch(expressionType)
    {
    case ADDITION_OPERATION_NODE:
    case MULTIPLICATION_OPERATION_NODE:
    case EQUALS_COMPARISON_OPERATION_NODE:
    case RELATIONAL_OPERATION_NODE:
    case AND_OPERATION_NODE:
        calculateTypeForExpression(expression->operand1);
        calculateTypeForExpression(expression->operand2);

        if (expression->operand1->semanticType == INTEGER_SYMBOL && expression->operand2->semanticType == INTEGER_SYMBOL)
            expression->semanticType = INTEGER_SYMBOL;
        else if (expression->operand2->semanticType == REAL_SYMBOL && expression->operand2->semanticType == REAL_SYMBOL)
            expression->semanticType = REAL_SYMBOL;
        else
            expression->semanticType = ERROR_SYMBOL;

        break;
    case UNARY_OPERATION_NODE:
    case NEGATION_OPERATION_NODE:
        calculateTypeForExpression(expression->expression);
        expression->semanticType = (expression->expression->semanticType != ERROR_SYMBOL) ? expression->expression->semanticType : ERROR_SYMBOL;
        break;
    case IDENTIFIER_NODE:
        expression->semanticType = (existsNode(&symbolTableHeader, expression->identfier->symbol)) ? getType(&symbolTableHeader, expression->identfier->symbol) : ERROR_SYMBOL;
        break;
    case INTEGER_NODE:
        expression->semanticType = INTEGER_SYMBOL;
        break;
    case REAL_NUMBER_NODE:
        expression->semanticType = REAL_SYMBOL;
    }
}

void calculateTypeForBlock(SyntaxTreeNode* block)
{
    if (block != NULL)
    {
        int errorExists = 0;
        SyntaxTreeNode* aux;
        for (aux = block; aux != NULL; aux = aux->next)
        {
            calculateTypeForStatement(aux);
            if (aux->semanticType == ERROR_SYMBOL)
                errorExists = 1;
        }

        block->semanticType = (!errorExists) ? VOID_SYMBOL : ERROR_SYMBOL;
    }

}

void semantic_error()
{
    fprintf(stderr, "semantic error: incompatible data types\n");
    exit(1);
}
