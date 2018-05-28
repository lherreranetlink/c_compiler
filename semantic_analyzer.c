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
    {
        calculateAttributesForExpression(expression->operand1);
        calculateAttributesForExpression(expression->operand2);
        expression->semanticType = getNumericType(expression->operand1->semanticType, expression->operand2->semanticType);

        if (expression->semanticType != ERROR_SYMBOL)
        {
            if (expression->semanticType == INTEGER_SYMBOL)
            {
                expression->value.integerVal = (strcmp(expression->sign->symbol, ADDITION_SIGN) == 0)
                                               ? expression->operand1->value.integerVal + expression->operand2->value.integerVal
                                               : expression->operand1->value.integerVal - expression->operand2->value.integerVal;
            }
            else
            {
                expression->value.floatVal = (strcmp(expression->sign->symbol, ADDITION_SIGN) == 0)
                                             ? expression->operand1->value.floatVal + expression->operand2->value.floatVal
                                             : expression->operand1->value.floatVal - expression->operand2->value.floatVal;
            }
        }
    }
    break;
    case MULTIPLICATION_OPERATION_NODE:
    {
        calculateAttributesForExpression(expression->operand1);
        calculateAttributesForExpression(expression->operand2);
        expression->semanticType = getNumericType(expression->operand1->semanticType, expression->operand2->semanticType);

        if (expression->semanticType != ERROR_SYMBOL)
        {
            if (expression->semanticType == INTEGER_SYMBOL)
            {
                expression->value.integerVal = (strcmp(expression->sign->symbol, MULT_SIGN) == 0)
                                               ? expression->operand1->value.integerVal * expression->operand2->value.integerVal
                                               : expression->operand1->value.integerVal / expression->operand2->value.integerVal;
            }
            else
            {
                expression->value.floatVal = (strcmp(expression->sign->symbol, MULT_SIGN) == 0)
                                             ? expression->operand1->value.floatVal * expression->operand2->value.floatVal
                                             : expression->operand1->value.floatVal / expression->operand2->value.floatVal;
            }
        }
    }
    break;
    case EQUALS_COMPARISON_OPERATION_NODE:
    {
        calculateAttributesForExpression(expression->operand1);
        calculateAttributesForExpression(expression->operand2);
        int tempType = getNumericType(expression->operand1->semanticType, expression->operand2->semanticType);

        if (tempType != ERROR_SYMBOL)
        {
            if (expression->semanticType == INTEGER_SYMBOL)
            {
                expression->value.booleanVal = (strcmp(expression->sign->symbol, EQ_COMPARISON_SIGN) == 0)
                                               ? expression->operand1->value.integerVal == expression->operand2->value.integerVal
                                               : expression->operand1->value.integerVal == expression->operand2->value.integerVal;
            }
            else
            {
                expression->value.booleanVal = (strcmp(expression->sign->symbol, NE_COMPARISON_SIGN) == 0)
                                               ? expression->operand1->value.floatVal != expression->operand2->value.floatVal
                                               : expression->operand1->value.floatVal != expression->operand2->value.floatVal;
            }
            expression->semanticType = BOOLEAN_SYMBOL;
        }
    }
    break;
    case RELATIONAL_OPERATION_NODE:
    {
        calculateAttributesForExpression(expression->operand1);
        calculateAttributesForExpression(expression->operand2);
        int tempType = getNumericType(expression->operand1->semanticType, expression->operand2->semanticType);

        if (tempType != ERROR_SYMBOL)
        {
            if (tempType == INTEGER_SYMBOL)
            {
                if (strcmp(expression->sign->symbol, LT_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.integerVal < expression->operand2->value.integerVal;
                else if (strcmp(expression->sign->symbol, LTE_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.integerVal <= expression->operand2->value.integerVal;
                else if (strcmp(expression->sign->symbol, GT_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.integerVal > expression->operand2->value.integerVal;
                else if (strcmp(expression->sign->symbol, GTE_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.integerVal >= expression->operand2->value.integerVal;
            }
            else if (tempType == REAL_SYMBOL)
            {
                if (strcmp(expression->sign->symbol, LT_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.floatVal < expression->operand2->value.floatVal;
                else if (strcmp(expression->sign->symbol, LTE_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.floatVal <= expression->operand2->value.floatVal;
                else if (strcmp(expression->sign->symbol, GT_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.floatVal > expression->operand2->value.floatVal;
                else if (strcmp(expression->sign->symbol, GTE_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.floatVal >= expression->operand2->value.floatVal;
            }
            else if (tempType == BOOLEAN_SYMBOL)
            {
                if (strcmp(expression->sign->symbol, LT_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.booleanVal < expression->operand2->value.booleanVal;
                else if (strcmp(expression->sign->symbol, LTE_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.booleanVal <= expression->operand2->value.booleanVal;
                else if (strcmp(expression->sign->symbol, GT_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.booleanVal > expression->operand2->value.booleanVal;
                else if (strcmp(expression->sign->symbol, GTE_SIGN) == 0)
                    expression->value.booleanVal = expression->operand1->value.booleanVal >= expression->operand2->value.booleanVal;
            }
            expression->semanticType = BOOLEAN_SYMBOL;
        }
    }
    break;
    case AND_OPERATION_NODE:
    {
        calculateAttributesForExpression(expression->operand1);
        calculateAttributesForExpression(expression->operand2);
        int tempType = getNumericType(expression->operand1->semanticType, expression->operand2->semanticType);

        if (tempType != BOOLEAN_SYMBOL)
        {
            if (strcmp(expression->sign->symbol, LT_SIGN) == 0)
                expression->value.booleanVal = expression->operand1->value.booleanVal < expression->operand2->value.booleanVal;
            else if (strcmp(expression->sign->symbol, LTE_SIGN) == 0)
                expression->value.booleanVal = expression->operand1->value.booleanVal <= expression->operand2->value.booleanVal;
            expression->semanticType = BOOLEAN_SYMBOL;
        }
    }
    break;
    case UNARY_OPERATION_NODE:
    {
        calculateAttributesForExpression(expression->expression);
        expression->semanticType = (expression->expression->semanticType != ERROR_SYMBOL) ? expression->expression->semanticType : ERROR_SYMBOL;

        if (expression->semanticType != ERROR_SYMBOL)
        {
            if (expression->semanticType == INTEGER_SYMBOL)
                expression->value.integerVal = (strcmp(expression->sign->symbol, "-") == 0) ? expression->expression->value.integerVal * -1 : expression->expression->value.integerVal;
            else
                expression->value.floatVal = (strcmp(expression->sign->symbol, "-") == 0) ? expression->expression->value.floatVal * -1.0 : expression->expression->value.floatVal;
        }
    }
    break;
    case NEGATION_OPERATION_NODE:
    {
        calculateAttributesForExpression(expression->expression);
        int tempType = (expression->expression->semanticType != ERROR_SYMBOL) ? expression->expression->semanticType : ERROR_SYMBOL;

        if (tempType == BOOLEAN_SYMBOL)
        {
            expression->value.booleanVal = !expression->expression->value.booleanVal;
            expression->semanticType = BOOLEAN_SYMBOL;
        }
    }
    break;
    case IDENTIFIER_NODE:
        expression->semanticType = (existsNode(&symbolTableHeader, expression->identifier->symbol)) ? getType(&symbolTableHeader, expression->identifier->symbol) : ERROR_SYMBOL;
        break;
    case INTEGER_NODE:
        expression->semanticType = INTEGER_SYMBOL;
        expression->value.integerVal = atoi(expression->integer->symbol);
        break;
    case REAL_NUMBER_NODE:
        expression->semanticType = REAL_SYMBOL;
        expression->value.floatVal = atof(expression->realNumber->symbol);
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

void castValues(SyntaxTreeNode *operand1, SyntaxTreeNode* operand2)
{
    if (operand1->semanticType == INTEGER_SYMBOL && operand2->semanticType == INTEGER_SYMBOL)
        //return INTEGER_SYMBOL;
    else if (operand1->semanticType == INTEGER_SYMBOL && operand2->semanticType == REAL_SYMBOL)
        //return INTEGER_SYMBOL;
    else if (operand1->semanticType == REAL_SYMBOL && operand2->semanticType == INTEGER_SYMBOL)
        //return INTEGER_SYMBOL;
    else if (operand1->semanticType == REAL_SYMBOL && operand2->semanticType == REAL_SYMBOL)
        //return REAL_SYMBOL;
    else if (operand1->semanticType == BOOLEAN_SYMBOL && operand2->semanticType == BOOLEAN_SYMBOL)
        //return BOOLEAN_SYMBOL;
    else if (operand1->semanticType == BOOLEAN_SYMBOL && operand2->semanticType == INTEGER_SYMBOL)
        //return BOOLEAN_SYMBOL;
    else if (operand1->semanticType == INTEGER_SYMBOL && operand2->semanticType == BOOLEAN_SYMBOL)
        //return BOOLEAN_SYMBOL;
    else
        //return ERROR_SYMBOL;
}

void semantic_error()
{
    fprintf(stderr, "semantic error\n");
    exit(1);
}
