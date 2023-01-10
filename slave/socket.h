#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "string.h"


#ifndef _SOCKET_
#define _SOCKET_

#include "slave.h"
#include "operation.h"

typedef struct Socket
{
    int socketfd, new_sd;
    socklen_t client_len;
    struct sockaddr_in server_addr, client_addr;
} Socket;

bool connectSocket(char *, int);
void *listenServer(void *);
bool sendMessage(char *message);
void *doMatrix(void *);
void *doPi(void *);
Operation *resolveOperation(Operation *);
int getSizeNumbers(char *);
int getSocket();
int getAction(char *);

#endif