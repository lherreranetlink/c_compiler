#include "asm_generator.h"

static FILE* outFd;
static SymbolTableNode* symbolTableHeader;
static int trueLabelCount, genericLabelCount, endLabelCount;

void generate_asm(SyntaxTreeNode** treeRoot, SymbolTableNode** symbolTable)
{
    outFd = fopen("salida.asm", "w");
    symbolTableHeader = *symbolTable;
    generateDependencies();
    if (*treeRoot != NULL)
    {
        generateDataSection();
        fprintf(outFd, ".code\n");
        fprintf(outFd, "begin:\n");
        SyntaxTreeNode* aux;
        for (aux = *treeRoot; aux != NULL; aux = aux->next)
            generateStatementCode(aux);
        fprintf(outFd, "exit\n");
        fprintf(outFd, "end begin\n");
    }
    fclose(outFd);
}

void generateDependencies()
{
    fprintf(outFd, ".386\n");
    fprintf(outFd, ".model flat, stdcall\n");
    fprintf(outFd, "option casemap:none\n");
    fprintf(outFd, "include \\masm32\\macros\\macros.asm\n");
    fprintf(outFd, "include \\masm32\\include\\masm32.inc\n");
    fprintf(outFd, "include \\masm32\\include\\kernel32.inc\n");
    fprintf(outFd, "include \\masm32\\macros\\macros.asm\n");
    fprintf(outFd, "includelib \\masm32\\lib\\masm32.lib\n");
    fprintf(outFd, "includelib \\masm32\\lib\\kernel32.lib\n\n");
}

void generateDataSection()
{
    /*fprintf(outFd, ".data\n");
    SymbolTableNode* aux;
    for (aux = symbolTableHeader; aux != NULL; aux = aux->next)
        fprintf(outFd, "_%s dword 0\n", aux->identifier->symbol);
    fprintf(outFd, "\n");*/
}

void generateStatementCode(SyntaxTreeNode* statement)
{
    int statementType = statement->ruleType;
    switch(statementType)
    {
    case IF_STATEMENT_NODE:
    {
        int elsePartLabel = genericLabelCount++, endIfLabel = genericLabelCount++;
        generateExpressionCode(statement->expression);
        fprintf(outFd, "pop eax\n");
        fprintf(outFd, "cmp eax, 1\n");
        fprintf(outFd, "jne L%d\n", elsePartLabel);
        generateBlockCode(statement->ifPart);
        fprintf(outFd, "jmp E%d\n", endIfLabel);
        fprintf(outFd, "L%d:\n", elsePartLabel);
        generateBlockCode(statement->elsePart);
        fprintf(outFd, "E%d:\n", endIfLabel);
    }
    break;
    case WHILE_STATEMENT_NODE:
    {
        int beginWhileLabel = genericLabelCount++, endWhileLabel = genericLabelCount++;
        fprintf(outFd, "B%d:\n", beginWhileLabel);
        generateExpressionCode(statement->expression);
        fprintf(outFd, "pop eax \n");
        fprintf(outFd, "cmp eax, 1\n");
        fprintf(outFd, "jne E%d\n", endWhileLabel);
        generateBlockCode(statement->blockStatements);
        fprintf(outFd, "jmp B%d\n", beginWhileLabel);
        fprintf(outFd, "E%d:\n", endWhileLabel);
    }
    break;
    case PRINT_CONST_STRING_NODE:
        //TODO: Generate code to const string node
        break;
    case PRINT_EXPRESSION_STATEMENT_NODE:
        generateExpressionCode(statement->expression);
        fprintf(outFd, "pop eax\nprint str$(eax), 13, 10\n");
        break;
    case ASSIGNMENT_STATEMENT_NODE:
        generateExpressionCode(statement->expression);
        fprintf(outFd, "pop _%s\n", statement->identifier->symbol);
    }
}

void generateExpressionCode(SyntaxTreeNode* expression)
{
    int expressionType = expression->ruleType;
    switch(expressionType)
    {
    case ADDITION_OPERATION_NODE:
    case MULTIPLICATION_OPERATION_NODE:
        generateExpressionCode(expression->operand1);
        generateExpressionCode(expression->operand2);
        if (strcmp(expression->sign->symbol, "+") == 0)
            fprintf(outFd, "pop ebx\npop eax\nadd eax, ebx\npush eax\n");
        else if(strcmp(expression->sign->symbol, "-") == 0)
            fprintf(outFd, "pop ebx\npop eax\nsub eax, ebx\npush eax\n");
        else if(strcmp(expression->sign->symbol, "*") == 0)
            fprintf(outFd, "pop ebx\npop eax\nmul ebx\npush eax\n");
        else if(strcmp(expression->sign->symbol, "/") == 0)
            fprintf(outFd, "pop ebx\npop eax\ndiv ebx\npush eax\n");
        break;
    case UNARY_OPERATION_NODE:
        generateExpressionCode(expression->expression);
        if (strcmp(expression->sign->symbol, "-") == 0)
            fprintf(outFd, "pop eax\nimul -1\npush eax\n");
        break;
    case NEGATION_OPERATION_NODE:
        generateExpressionCode(expression->expression);
        fprintf(outFd, "pop eax\n not eax\n push eax\n");
        break;
    case RELATIONAL_OPERATION_NODE:
    case EQUALS_COMPARISON_OPERATION_NODE:
        generateExpressionCode(expression->operand1);
        generateExpressionCode(expression->operand2);
        char relationalOp[BUFSIZ];
        setConditionString(expression->sign->symbol, relationalOp);
        fprintf(outFd, "pop ebx\npop eax\ncmp eax, ebx\n");
        fprintf(outFd, "%s T%d\n", relationalOp, trueLabelCount);
        fprintf(outFd, "push 0\n");
        fprintf(outFd, "jmp E%d\n", endLabelCount);
        fprintf(outFd, "T%d:\n", trueLabelCount++);
        fprintf(outFd, "push 1\n");
        fprintf(outFd, "E%d:\n", endLabelCount++);
        break;
    case AND_OPERATION_NODE:
        generateExpressionCode(expression->operand1);
        generateExpressionCode(expression->operand2);
        if (strcmp(expression->sign->symbol, "&&") == 0)
            fprintf(outFd, "pop ebx\npop eax\nand eax, ebx\npush eax\n");
        else
            fprintf(outFd, "pop ebx\npop eax\nor eax, ebx\npush eax\n");
        break;
    case IDENTIFIER_NODE:
        fprintf(outFd, "push _%s\n", expression->identifier->symbol);
        break;
    case INTEGER_NODE:
        fprintf(outFd, "push %s\n", expression->integer->symbol);
        break;
    case REAL_NUMBER_NODE:
        fprintf(outFd, "push %s\n", expression->realNumber->symbol);
    }
}

void generateBlockCode(SyntaxTreeNode* block)
{
    SyntaxTreeNode* aux;
    for (aux = block; aux != NULL; aux = aux->next)
        generateStatementCode(aux);
}

void setConditionString(char* relationalOp, char* symbol)
{
    if (strcmp(relationalOp, "<") == 0)
        strcpy(symbol, "jl");
    else if(strcmp(relationalOp, ">") == 0)
        strcpy(symbol, "jg");
    else if(strcmp(relationalOp, "<=") == 0)
        strcpy(symbol, "jle");
    else if(strcmp(relationalOp, ">=") == 0)
        strcpy(symbol, "jge");
    else if(strcmp(relationalOp, "==") == 0)
        strcpy(symbol, "je");
    else if(strcmp(relationalOp, "!=") == 0)
        strcpy(symbol, "jne");
}
