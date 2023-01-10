#include "project.h"

int isExit = false;
int **matrixA;
int **matrixB;
int **matrixResults;
char ***operations;
int sizeA[2];
int sizeB[2];

void init()
{
    char *ip = "127.0.0.1";
    int port = 6000;
    initServer(ip, port);
    menu();
}

void menu()
{
    int option = 0;
    while (!isExit)
    {
        printf("\n------------------------------\n");
        printf("Ingrese una opción:\n");
        printf("1: Insertar matrices\n");
        printf("2: Ver matriz de multiplicaciones\n");
        printf("3: Enviar matriz multiplicaciones a esclavos\n");
        printf("4: Mostrar resultado multiplicación de matrices\n");
        printf("5: Calcular PI\n");
        printf("6: Información del servidor\n");
        printf("7: Salir\n");
        printf("\n------------------------------\n");
        scanf("%d", &option);
        task(option);
    }
    closeServer();
    printf("Servidor cerrado...\n");
}

int task(int option)
{
    system("clear");
    char pathA[50];
    char pathB[50];
    switch (option)
    {
    case 1:
        printf("Nombre de la matriz 'A':\n");
        scanf("%s", pathA);
        matrixA = getMatrix(pathA);
        int rowsA = sizeRows(pathA);
        int columnsA = sizeColumns(pathA);
        printf("|Datos de 'A'\n");
        printf("|->Tamaño: %d*%d\n", rowsA, columnsA);

        printf("Nombre de la matriz 'B':\n");
        scanf("%s", pathB);
        matrixB = getMatrix(pathB);
        int rowsB = sizeRows(pathB);
        int columnsB = sizeColumns(pathB);
        printf("|Datos de 'B'\n");
        printf("|->Tamaño: %d*%d\n", rowsB, columnsB);

        sizeA[0] = rowsA;
        sizeA[1] = columnsA;
        sizeB[0] = rowsB;
        sizeB[1] = columnsB;
        break;

    case 2:
        operations = getMatrixOperations(matrixA, matrixB, sizeA, sizeB);
        printf("Matriz de multiplicaciones:\n\n");
        for (int i = 0; i < sizeA[0]; i++)
        {
            for (int j = 0; j < sizeB[1]; j++)
                printf("%s \t", operations[i][j]);
            printf("\n");
        }
        break;

    case 3:
        operations = getMatrixOperations(matrixA, matrixB, sizeA, sizeB);
        List *slaves3 = getSlaves();
        int size[] = {sizeA[0], sizeB[1]};
        distributeMatrix(operations, size, slaves3, slaves3->size);
        for (int i = 0; i < slaves3->size; i++)
        {
            Slave *slave3 = (Slave *)get(slaves3, i);
            printf("|slave-%d| : ", slave3->id);
            for (int j = 0; j < slave3->operations->size; j++)
                printf("|%s| -> ", ((Operation *)get(slave3->operations, j))->strOperation);
            printf("NULL\n");
        }
        int sizeMatrix[] = {sizeA[0], sizeB[1]};
        initMatrix(sizeMatrix);
        sendToSlaves(slaves3, "Matrix");

        break;

    case 4:
        int **temp = getMatrixResults();
        printf("Matriz de resuldado : %d \n\n");
        for (int i = 0; i < sizeA[0]; i++)
        {
            for (int j = 0; j < sizeB[1]; j++)
                printf("%d \t", temp[i][j]);
            printf("\n");
        }
        
        break;

    case 6:
        List *slaves = getSlaves();
        printf("Slaves\n");
        printf("_____________\n");
        printf("| ID | Sock |\n");
        printf("_____________\n");
        for (int i = 0; i < getSize(slaves); i++)
        {
            Slave *slave = (Slave *)get(slaves, i);
            printf("| %d |  %d  |\n", slave->id, slave->socketFd);
        }

        break;
    case 7:
        isExit = true;
        break;
    default:
        break;
    }
}