#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include "data.h"
#include "string.h"
#include "calculator.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void initSocket();
void listenClients(int *params);

int main(int argc, char **argv)
{
    // initSocket();

    char buffer[100];
    char buffer2[1024] = {};
    /*
    snprintf(buffer, 100, "%d", num);
    strcat(buffer2,operation);
    strcat(buffer2,buffer);
    //strcpy(buffer2, strcat(buffer2,operation));
    printf("\n%s\n", buffer2);
    */

    int **matrixA = getMatrix("A.txt");
    int **matrixB = getMatrix("B.txt");
    

    char ***operations = getMatrixOperations(matrixA, matrixB);

    int rowsA = sizeRows("A.txt");
    int columnsB = sizeColumns("B.txt");
    /*
    int columnsA = sizeColumns("A2.txt");
    int rowsB = sizeRows("B2.txt");

    int **result = (int **)malloc(rowsA * sizeof(int *));
    for (int i = 0; i < rowsA; i++)
        result[i] = (int *)malloc(columnsB * sizeof(int));

    char ***operations = (char ***)malloc(rowsA * sizeof(char **));
    for (int i = 0; i < rowsA; i++){
        operations[i] = (char **)malloc(columnsB * sizeof(char*));
        for (int j = 0; j < columnsB; j++)
        {
            operations[i][j] = (char *)malloc(100* sizeof(char));
        }
    }
    
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < columnsB; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < columnsA; k++)
            {
                snprintf(buffer, 100, "%d*%d", matrixA[i][k], matrixB[k][j]);
                if (k + 1 != columnsA)
                    strcat(buffer, "+");
                strcat(buffer2, buffer);
                strcpy(operations[i][j], buffer2);
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
            printf("%s \t", buffer2);
            strcpy(buffer2, "");
        }
        printf("\n");
    }
    */
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < columnsB; j++)
            printf("%s \t", operations[i][j]);
        printf("\n");
    }
    return 0;
}
/*
void initSocket()
{
    int socketFd, connectionFd, len;
    struct sockaddr_in addressServer, cli;

    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&addressServer, sizeof(addressServer));
    addressServer.sin_family = AF_INET;
    addressServer.sin_addr.s_addr = htonl(INADDR_ANY);
    addressServer.sin_port = htons(PORT);

    if ((bind(socketFd, (SA *)&addressServer, sizeof(addressServer))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    if ((listen(socketFd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server Listening..\n");
    len = sizeof(cli);

    while (1)
    {

        // Accept the data packet from client and verification
        connectionFd = accept(socketFd, (SA *)&cli, &len);
        if (connectionFd < 0)
        {
            printf("server accept failed...\n");
            exit(0);
        }
        else
            printf("server accept the client %i - %d\n", socketFd, &cli.sin_addr.s_addr);

        int params[] = {&connectionFd, &socketFd};

        pthread_t threadListe;
        pthread_create(&threadListe, NULL, listenClients, params);
    }
}

void listenClients(int *params)
{
    int connectionFd = params[0];
    int socketFd = params[1];
    char buff[MAX];
    int n;
    // infinite loop for chat
    while (1)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(connectionFd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(connectionFd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
    close(socketFd);
}
*/