#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "treeprinter.h"

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
    printSyntaxTree(syntaxTree);
    return 0;
}
