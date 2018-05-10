#include "parser.h"

static Token* currentToken;
static FILE* file;

SyntaxTreeNode* parse(FILE* fileToAnalyze)
{
    file = fileToAnalyze;
    currentToken = getNextToken(fileToAnalyze);

    return program();
}

SyntaxTreeNode* program()
{
    SyntaxTreeNode* initialStatement, *aux;

    initialStatement = singleStatement();
    aux = initialStatement;
    while (currentToken->type != EOF_SIGN)
    {
        aux->next = singleStatement();
        aux = aux->next;
    }

    match(EOF_SIGN);

    return initialStatement;
}

SyntaxTreeNode* singleStatement()
{
    SyntaxTreeNode* statement = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
    statement->next = NULL;
    int tokenType = currentToken->type;
    switch(tokenType)
    {
    case IF_KEYWORD:
        statement->ruleType = IF_STATEMENT_NODE;
        match(IF_KEYWORD);
        match(LEFT_PARENTHESIS);
        statement->expression = expression();
        match(RIGHT_PARENTHESIS);
        statement->ifPart = blockStatement();
        statement->elsePart = elsePart();
        break;
    case WHILE_KEYWORD:
        statement->ruleType = WHILE_STATEMENT_NODE;
        match(WHILE_KEYWORD);
        match(LEFT_PARENTHESIS);
        statement->expression = expression();
        match(RIGHT_PARENTHESIS);
        statement->blockStatements = blockStatement();
        break;
    case PRINT_KEYWORD:
        statement = printableStatement();
        break;
    case IDENTIFIER:
        statement = assignment();
        break;
    default:
        return NULL;
    }
    return statement;
}

SyntaxTreeNode* expression()
{
    SyntaxTreeNode* temp = equalsComparisonExpression();
    while (currentToken->type == LOGIC_AND_OPERATOR || currentToken->type == LOGIC_OR_OPERATOR)
    {
        SyntaxTreeNode* temp2 = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
        temp2->ruleType = AND_OPERATION_NODE;
        temp2->operand1 = temp;
        temp2->sign = currentToken;
        match(currentToken->type);
        temp2->operand2 =  equalsComparisonExpression();
        temp = temp2;
    }
    return temp;
}

SyntaxTreeNode* equalsComparisonExpression()
{
    SyntaxTreeNode* temp = relationalExpression();
    while (currentToken->type == EQUALS_COMPARISON_OPERATOR)
    {
        SyntaxTreeNode* temp2 = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
        temp2->ruleType = EQUALS_COMPARISON_OPERATION_NODE;
        temp2->operand1 = temp;
        temp2->sign = currentToken;
        match(EQUALS_COMPARISON_OPERATOR);
        temp2->operand2 = relationalExpression();
        temp = temp2;
    }
    return temp;
}

SyntaxTreeNode* relationalExpression()
{
    SyntaxTreeNode* temp = addition();
    while (currentToken->type == RELATIONAL_OPERATOR)
    {
        SyntaxTreeNode* temp2 = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
        temp2->ruleType = RELATIONAL_OPERATION_NODE;
        temp2->operand1 = temp;
        temp2->sign = currentToken;
        match(RELATIONAL_OPERATOR);
        temp2->operand2 = addition();
        temp = temp2;
    }
    return temp;
}

SyntaxTreeNode* addition()
{
    SyntaxTreeNode* temp = multiplication();
    while (currentToken->type == ADD_OPERATOR)
    {
        SyntaxTreeNode* temp2 = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
        temp2->ruleType = ADDITION_OPERATION_NODE;
        temp2->operand1 = temp;
        temp2->sign = currentToken;
        match(ADD_OPERATOR);
        temp2->operand2 = multiplication();
        temp = temp2;
    }
    return temp;
}

SyntaxTreeNode* multiplication()
{
    SyntaxTreeNode* temp = factor();
    while (currentToken->type == MULT_OPERATOR)
    {
        SyntaxTreeNode* temp2 = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
        temp2->ruleType = MULTIPLICATION_OPERATION_NODE;
        temp2->operand1 = temp;
        temp2->sign = currentToken;
        match(MULT_OPERATOR);
        temp2->operand2 = factor();
        temp = temp2;
    }
    return temp;
}

SyntaxTreeNode* factor()
{
    SyntaxTreeNode* temp = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
    int tokenType = currentToken->type;
    switch (tokenType)
    {
    case NEGATION_OPERATOR:
        match(NEGATION_OPERATOR);
        temp->ruleType = NEGATION_OPERATION_NODE;
        temp->expression = expression();
    break;
    case LEFT_PARENTHESIS:
        match(LEFT_PARENTHESIS);
        temp = expression();
        match(RIGHT_PARENTHESIS);
    break;
    case ADD_OPERATOR:
        temp->ruleType = UNARY_OPERATION_NODE;
        temp->sign = currentToken;
        match(ADD_OPERATOR);
        temp->expression = expression();
        break;
    case INTEGER:
        temp->ruleType = INTEGER_NODE;
        temp->integer = currentToken;
        match(INTEGER);
        break;
    case REAL_NUMBER:
        temp->ruleType = REAL_NUMBER_NODE;
        temp->realNumber = currentToken;
        match(REAL_NUMBER);
        break;
    case IDENTIFIER:
        temp->ruleType = IDENTIFIER_NODE;
        temp->identfier = currentToken;
        match(IDENTIFIER);
        break;
    default:
        error();
    }
    return temp;
}

SyntaxTreeNode* blockStatement()
{
    return (currentToken->type == LEFT_BRACE) ? block() : singleStatement();
}

SyntaxTreeNode* elsePart()
{
    SyntaxTreeNode* temp = NULL;
    if (currentToken->type == ELSE_KEYWORD)
    {
        match(ELSE_KEYWORD);
        if (currentToken->type == LEFT_BRACE)
        {
            match(LEFT_BRACE);

            SyntaxTreeNode* aux;
            temp = singleStatement();
            aux = temp;
            while (currentToken->type != RIGHT_BRACE)
            {
                aux->next = singleStatement();
                aux = aux->next;
            }

            match(RIGHT_BRACE);
        }
        else
            temp = singleStatement();
    }

    return temp;
}

SyntaxTreeNode* block()
{
    SyntaxTreeNode* temp, *aux;

    match(LEFT_BRACE);

    temp = singleStatement();
    aux = temp;
    while (currentToken->type != RIGHT_BRACE)
    {
        aux->next = singleStatement();
        aux = aux->next;
    }

    match(RIGHT_BRACE);

    return temp;
}

SyntaxTreeNode* printableStatement()
{
    SyntaxTreeNode* temp = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
    match(PRINT_KEYWORD);
    match(LEFT_PARENTHESIS);

    if (currentToken->type == CONST_STRING)
    {
        temp->ruleType = PRINT_CONST_STRING_NODE;
        temp->constString = currentToken;
        match(CONST_STRING);
    }
    else
    {
        temp->ruleType = PRINT_EXPRESSION_STATEMENT_NODE;
        temp->expression = expression();
    }

    match(RIGHT_PARENTHESIS);
    match(SEMICOLON);

    return temp;
}

SyntaxTreeNode* assignment()
{
    SyntaxTreeNode* assignment = (SyntaxTreeNode*) malloc(sizeof(SyntaxTreeNode));
    assignment->ruleType = ASSIGNMENT_STATEMENT_NODE;

    assignment->identfier = currentToken;

    match(IDENTIFIER);
    match(ASSIGNMENT_OPERATOR);

    assignment->expression = expression();

    match(SEMICOLON);

    return assignment;
}

void match(TokenType tokenType)
{
    if (currentToken->type == tokenType)
        currentToken = getNextToken(file);
    else
        error();
}

void error()
{
    fprintf(stderr, "Unexpected token %s\n", currentToken->symbol);
    exit(1);
}
