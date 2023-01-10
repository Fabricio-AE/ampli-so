#include "calculator.h"

char ***getMatrixOperations(int **matrixA, int **matrixB, int *sizeA, int *sizeB)
{
    int rowsA = sizeA[0];
    int columnsA = sizeA[1];
    int columnsB = sizeB[1];
    char product[1024] = {};
    char equation[1024] = {};

    char ***operations = (char ***)malloc(rowsA * sizeof(char **));
    for (int i = 0; i < rowsA; i++)
    {
        operations[i] = (char **)malloc(columnsB * sizeof(char *));
        for (int j = 0; j < columnsB; j++)
        {
            operations[i][j] = (char *)malloc(100 * sizeof(char));
        }
    }

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < columnsB; j++)
        {
            strcpy(operations[i][j], "");
            for (int k = 0; k < columnsA; k++)
            {
                snprintf(product, 100, "%d*%d", matrixA[i][k], matrixB[k][j]);
                if (k + 1 != columnsA)
                    strcat(product, "+");
                strcat(equation, product);
                strcpy(operations[i][j], equation);
            }
            strcpy(equation, "");
        }
    }
    return operations;
}

void distributeMatrix(char ***operations, int *size, List *slaves, int sizeSlaves)
{
    Operation *operationTemp;
    int indexSlave = 0;
    for (int i = 0; i < size[0]; i++)
    {
        for (int j = 0; j < size[1]; j++)
        {
            operationTemp = initOperation(i, j, operations[i][j]);
            insert(((Slave *)get(slaves, indexSlave))->operations, (void *)operationTemp);
            indexSlave = ((indexSlave + 1) % sizeSlaves);
        }
    }
}