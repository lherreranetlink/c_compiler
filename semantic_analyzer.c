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
            calculateAttributesForStatement(aux);
            if (aux->semanticType == ERROR_SYMBOL)
                errorExists = 1;
        }
        if (errorExists)
            semantic_error();

        *symbolTable = symbolTableHeader;
    }
}

void calculateAttributesForStatement(SyntaxTreeNode* statement)
{
    int statementType = statement->ruleType;
    switch(statementType)
    {
    case IF_STATEMENT_NODE:
        calculateAttributesForExpression(statement->expression);
        calculateAttributesForBlock(statement->ifPart);
        calculateAttributesForBlock(statement->elsePart);

        statement->semanticType = ((statement->expression->semanticType != ERROR_SYMBOL)
                                   && (statement->ifPart == NULL || statement->ifPart->semanticType == VOID_SYMBOL)
                                   && (statement->elsePart == NULL || statement->elsePart->semanticType == VOID_SYMBOL))
                                  ? VOID_SYMBOL : ERROR_SYMBOL;
        break;
    case WHILE_STATEMENT_NODE:
        calculateAttributesForExpression(statement->expression);
        calculateAttributesForBlock(statement->blockStatements);

        statement->semanticType = ((statement->expression->semanticType != ERROR_SYMBOL)
                                   && (statement->blockStatements == NULL || statement->blockStatements->semanticType == VOID_SYMBOL))
                                   ? VOID_SYMBOL : ERROR_SYMBOL;
        break;
    case PRINT_CONST_STRING_NODE:
        //TODO: print const string node
        break;
    case PRINT_EXPRESSION_STATEMENT_NODE:
        calculateAttributesForExpression(statement->expression);
        statement->semanticType = (statement->expression->semanticType != ERROR_SYMBOL) ? VOID_SYMBOL : ERROR_SYMBOL;
        break;
    case ASSIGNMENT_STATEMENT_NODE:
        calculateAttributesForExpression(statement->expression);
        if (statement->expression->semanticType != ERROR_SYMBOL)
        {
            if (existsNode(&symbolTableHeader, statement->identifier->symbol))
                updateType(&symbolTableHeader, statement->expression->semanticType, statement->identifier->symbol);
            else
                insertNode(&symbolTableHeader, statement->expression->semanticType, statement->identifier);
            statement->semanticType = VOID_SYMBOL;
        }
        else
            statement->semanticType = ERROR_SYMBOL;
    }
}

void calculateAttributesForExpression(SyntaxTreeNode* expression)
{
    int expressionType = expression->ruleType;
    switch(expressionType)
    {
    case ADDITION_OPERATION_NODE:
    case MULTIPLICATION_OPERATION_NODE:
    case EQUALS_COMPARISON_OPERATION_NODE:
    case RELATIONAL_OPERATION_NODE:
    case AND_OPERATION_NODE:
        calculateAttributesForExpression(expression->operand1);
        calculateAttributesForExpression(expression->operand2);
        expression->semanticType = getNumericType(expression->operand1->semanticType, expression->operand2->semanticType);
        break;
    case UNARY_OPERATION_NODE:
    case NEGATION_OPERATION_NODE:
        calculateAttributesForExpression(expression->expression);
        expression->semanticType = (expression->expression->semanticType != ERROR_SYMBOL) ? expression->expression->semanticType : ERROR_SYMBOL;
        break;
    case IDENTIFIER_NODE:
        expression->semanticType = (existsNode(&symbolTableHeader, expression->identifier->symbol)) ? getType(&symbolTableHeader, expression->identifier->symbol) : ERROR_SYMBOL;
        break;
    case INTEGER_NODE:
        expression->semanticType = INTEGER_SYMBOL;
        break;
    case REAL_NUMBER_NODE:
        expression->semanticType = REAL_SYMBOL;
    }
}

void calculateAttributesForBlock(SyntaxTreeNode* block)
{
    if (block != NULL)
    {
        int errorExists = 0;
        SyntaxTreeNode* aux;
        for (aux = block; aux != NULL; aux = aux->next)
        {
            calculateAttributesForStatement(aux);
            if (aux->semanticType == ERROR_SYMBOL)
                errorExists = 1;
        }

        block->semanticType = (!errorExists) ? VOID_SYMBOL : ERROR_SYMBOL;
    }

}

void semantic_error()
{
    fprintf(stderr, "semantic error\n");
    exit(1);
}
