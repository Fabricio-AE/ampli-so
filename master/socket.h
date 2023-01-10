#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <stdbool.h>
#include "string.h"

#ifndef _SOCKET_
#define _SOCKET_

#include "domain/slave.h"
#include "utility/list.h"

typedef struct Socket
{
    int socketfd, new_sd;
    socklen_t client_len;
    struct sockaddr_in server_addr, client_addr;
} Socket;

void closeConnection(Slave *);
void closeServer();
void* insertSlave(void*);
void* listenSlaves(void*);
void initServer(char*, int);
void initMatrix(int *);
void sendToSlaves(List *, char *);
bool sendMessage(Slave *, char *);
void doTask(char *);
List* getSlaves();
int getAction(char*);
void setToMatrixResult(char *);
int **getMatrixResults();

#endif