#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "string.h"
#include "calculator.h"
#include "socket.h"

void initSocket();
void listenClients(int *params);

int main(int argc, char **argv)
{

    /*
        Pruebas para obtener matriz
    */
    int **matrixA = getMatrix("A2.txt");
    int **matrixB = getMatrix("B2.txt");

    int rowsA = sizeRows("A2.txt");
    int rowsB = sizeRows("B2.txt");
    int columnsA = sizeColumns("A2.txt");
    int columnsB = sizeColumns("B2.txt");

    int sizeA[] = {rowsA, columnsA};
    int sizeB[] = {rowsB, columnsB};

    /*
        Obtener la matriz de operaciones que van a ser repartidas a los
        esclavos
    */
    char ***operations = getMatrixOperations(matrixA, matrixB, sizeA, sizeB);

    /*
        Se imprime la matriz de operaciones
    */
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < columnsB; j++)
            printf("%s \t", operations[i][j]);
        printf("\n");
    }

    /*
        Método que va a asignar las operaciones a los esclavos
        Devuelve una lista con las operaciones de cada esclavo así:
        |slave1| : |1*5+-1*2+3*0| -> ...
        |slave2| : |1*-3+-1*1+3*3| -> ...
        ...
    */
    int sizeOperations[] = {rowsA, columnsB};
    int sizeSlaves = 2;
    Slave **slaves = distributeMatrix(operations, sizeOperations, sizeSlaves);
/*
    for (int i = 0; i < sizeSlaves; i++)
    {
        printf("|slave-%d| : ", i);
        for (int j = 0; j < getSize(slaves[i]->operations); j++)
            printf("|%s| -> ", ((Operation *)get(slaves[i]->operations, j))->strOperation);
        printf("NULL\n");
    }
*/
    return 0;
}
