#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <stdbool.h>

#include "socket.h"

void func(int sockfd);

int main()
{
    int SOCKET_PORT = 6000;
    // char ip[20];
    char *ip = "127.0.0.1";
    printf("Digite la direccion ip para conectar:\n");
    // scanf("%s",ip);

    connectSocket(ip, SOCKET_PORT);
    char message[512];
    bool isSended = false;
}