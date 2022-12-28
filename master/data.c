#include "data.h"

char *readFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", fileName);
        return "Error: could not open file";
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            printf("Salto de linea");
        }
    }
    // putchar(ch);

    // close the file
    fclose(fp);
    return "Hola";
}

int sizeRows(char *fileName)
{
    if (!existsFile(fileName))
        return 0;
    FILE *fp = fopen(fileName, "r");
    char ch;
    int size;
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n')
            size++;
    return size + 1;
}

int sizeColumns(char *fileName)
{
    if (!existsFile(fileName))
        return 0;
    FILE *fp = fopen(fileName, "r");
    char ch;
    int size;
    while ((ch = fgetc(fp)) != '\n')
        if (ch == ',')
            size++;
    return size + 1;
}

int isMultiply(int *sizeA, int *sizeB){    
    return sizeA[1]==sizeB[0];
}

int existsFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL)
        return 0;
    fclose(fp);
    return 1;
}