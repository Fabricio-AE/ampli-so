#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include "data.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void initSocket();
void listenClients(int *params);

int main(int argc, char **argv)
{
    //initSocket();
    int rows = sizeColumns("A.txt");
    printf("Columns size: %d\n", rows);
    int sizeA[] = {3,2};
    int sizeB[] = {2,3};
    int multi= isMultiply( &sizeA, &sizeB);
    printf("Es multiplicable: %d", multi);
    return 0;
}

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