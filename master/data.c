#include "data.h"
#include <math.h>

int **getMatrix(char *fileName)
{
    int **response = (int **)malloc(0 * sizeof(int *));
    response[0] = (int *)malloc(0 * sizeof(int));
    if (!existsFile(fileName))
        return response;

    int rows = sizeRows(fileName);
    int columns = sizeColumns(fileName);
    response = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        response[i] = (int *)malloc(columns * sizeof(int));

    FILE *fp = fopen(fileName, "r");

    char *row = NULL;
    size_t len = 0;
    while (getline(&row, &len, fp) > 0)
    {
    }
    getline(&row, &len, fp);
    int *arrayRow = getRow(row);
        printf("- %d\n", columns);
    for (int i = 0; i < columns; i++)
    {
    }
    
    // putchar(ch);

    // close the file
    fclose(fp);
    return response;
}

int *getRow(char *row)
{
    int n = strlen(row);
    int sizeNumbers = ceil((double)n / 2);
    int *response = malloc(sizeNumbers * sizeof(int));
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (row[i] != ','){
            response[count] = row[i] - '0';
            count++;
        }
    }
    return response;
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

int isMultiply(int *sizeA, int *sizeB)
{
    return sizeA[1] == sizeB[0];
}

int existsFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL)
        return 0;
    fclose(fp);
    return 1;
}