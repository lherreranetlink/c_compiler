#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "asm_generator.h"

int main()
{
    char filename[] = "entrada.txt";
    FILE* fd;
    if ((fd = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "%s no such file or directory\n", filename);
        exit(1);
    }

    SyntaxTreeNode* syntaxTree = parse(fd);
    SymbolTableNode* symbolTable;
    analyzeSemantics(&syntaxTree, &symbolTable);
    generate_asm(&syntaxTree, &symbolTable);

    return 0;
}
