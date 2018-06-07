#include "semantic_analyzer.h"

static SymbolTableNode* symbolTableHeader;

void analyzeSemantics(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTable)
{
    if (*treeRoot != NULL)
    {
        SyntaxTreeNode* aux;
        for (aux = *treeRoot; aux != NULL; aux = aux->next)
            calculateAttributesForStatement(aux);

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
    {
        calculateAttributesForExpression(statement->expression);
        if (!existsNode(&symbolTableHeader, statement->identifier->symbol))
        {
            statement->semanticType = ERROR_SYMBOL;
            semantic_error("Variable does not exists");
        }
        else
            statement->semanticType = (statement->expression->semanticType != ERROR_SYMBOL) ? VOID_SYMBOL : ERROR_SYMBOL;

    }
    break;
    case VAR_DECLARATION_STATEMENT_NODE:
    {
        SyntaxTreeNode* aux;

        int duplicatedVar = 0;
        for (aux = statement->varList; aux != NULL; aux = aux->next)
        {
            if (existsNode(&symbolTableHeader, aux->identifier->symbol))
            {
                aux->semanticType = ERROR_SYMBOL;
                duplicatedVar = 1;
                semantic_error("Duplicated variable name");
            }
            else
            {
                if (strcmp(statement->dataType->symbol, "int") == 0)
                {
                    insertNode(&symbolTableHeader, INTEGER_SYMBOL, aux->identifier);
                    aux->semanticType = INTEGER_SYMBOL;
                }
                else if(strcmp(statement->dataType->symbol, "float") == 0)
                {
                    insertNode(&symbolTableHeader, REAL_SYMBOL, aux->identifier);
                    aux->semanticType = REAL_SYMBOL;
                }
            }
        }
        statement->semanticType = (duplicatedVar) ? ERROR_SYMBOL : VOID_SYMBOL;
    }
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
        expression->semanticType = getOperationDataType(expression->operand1->semanticType, expression->operand2->semanticType);
        break;
    case UNARY_OPERATION_NODE:
    case NEGATION_OPERATION_NODE:
        calculateAttributesForExpression(expression->expression);
        expression->semanticType = (expression->expression->semanticType != ERROR_SYMBOL) ? expression->expression->semanticType : ERROR_SYMBOL;
        break;
    case IDENTIFIER_NODE:
        //expression->semanticType = (existsNode(&symbolTableHeader, expression->identifier->symbol)) ? getType(&symbolTableHeader, expression->identifier->symbol) : ERROR_SYMBOL;
        if (existsNode(&symbolTableHeader, expression->identifier->symbol))
            expression->semanticType = getType(&symbolTableHeader, expression->identifier->symbol);
        else
        {
            semantic_error("Undefined variable");
            expression->semanticType = ERROR_SYMBOL;
        }
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

SemanticType getOperationDataType(SemanticType type1, SemanticType type2)
{
    if (type1 == INTEGER_SYMBOL && type2 == INTEGER_SYMBOL)
        return INTEGER_SYMBOL;
    else if (type1 == REAL_SYMBOL && type2 == REAL_SYMBOL)
        return REAL_SYMBOL;
    else if (type1 == REAL_SYMBOL && type2 == INTEGER_SYMBOL)
        return REAL_SYMBOL;
    else if (type1 == INTEGER_SYMBOL && type2 == REAL_SYMBOL)
        return INTEGER_SYMBOL;
    else
        return ERROR_SYMBOL;
}

void semantic_error(char* msg)
{
    fprintf(stderr, "Semantic error: %s\n", msg);
}
