#include "socket.h"

#define COM_MAXLINE 512
#define MAXTEXT 450

bool conexion_activa = false;
Socket *sock = NULL;
pthread_t *listenToSlavesThread;
List *slaves;
int **matrixResults1;
int *sizeMatrixResults;

char *actions[] = {
    "Matrix",
    "Pi",
    "SALIR"};
int actionsSize = 3;

void initServer(char *ip, int serverPort)
{
    sock = (Socket *)malloc(sizeof(Socket));

    // int i, status, id;

    // Open TCP internet STREAM socket
    if ((sock->socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("server: Can't open stream socket");
    else
        printf("Socket created!\n");

    // Bind local address to allow the client to connect
    bzero((char *)&sock->server_addr, sizeof(sock->server_addr));
    sock->server_addr.sin_family = AF_INET;
    sock->server_addr.sin_addr.s_addr = inet_addr(ip);
    sock->server_addr.sin_port = htons(serverPort);
    if (bind(sock->socketfd, (struct sockaddr *)&sock->server_addr,
             sizeof(sock->server_addr)) < 0)
    {
        perror("server: can't bind local address");
        exit(1);
    }
    listen(sock->socketfd, 8); // la función listen habilita el socket para recibir conexiones
    conexion_activa = true;

    listenToSlavesThread = (pthread_t *)malloc(sizeof(pthread_t));
    pthread_create(&listenToSlavesThread, NULL, insertSlave, NULL);
}

void initMatrix(int *sizeMatrix){
    sizeMatrixResults = sizeMatrix;
    matrixResults1 = (int **)malloc(sizeMatrix[0] * sizeof(int *));
    for (int i = 0; i < sizeMatrix[1]; i++)
        matrixResults1[i] = (int *)malloc(sizeMatrix[1] * sizeof(int));
}

void *insertSlave(void *arg)
{
    slaves = createList();
    int num_esclavos = 0;

    while (1)
    {
        sock->client_len = sizeof(sock->client_addr);

        // se intenta aceptar la conexión, y es almacenada en el atributo new_sd del socket
        sock->new_sd = accept(sock->socketfd, (struct sockaddr *)&sock->client_addr, &sock->client_len);
        if (sock->new_sd < 0)
        {
            printf("Error aceptando peticiones\n");
            exit(0);
        }
        else
        {
            // Se añade el esclavo al sistema:
            Slave *new_slave = initSlave();
            new_slave->id = num_esclavos;
            new_slave->socketFd = sock->new_sd;
            new_slave->isConnected = true;

            insert(slaves, new_slave);
            printf("Esclavo añadido\n");
            pthread_t *listenSlavesThread = (pthread_t *)malloc(sizeof(pthread_t));
            pthread_create(&listenSlavesThread, NULL, listenSlaves, (void *)new_slave);
            fflush(stdout);
            num_esclavos++;
        }
    }
}


void* listenSlaves(void* data){
    Slave *slave = (Slave *) data;
    char buffer[COM_MAXLINE];
    int action = -1;
    while(slave->isConnected){
        recv(slave->socketFd, buffer, COM_MAXLINE, 0);
        action = getAction(buffer);
        if(action == 0){
            setToMatrixResult(buffer);
        } else if(action == 2){
            slave->isConnected = false;
            continue;
        }
        //doTask(buffer);
    }
    close(slave->socketFd);
    return;
}

void doTask(char * message){
    printf("Message: %s\n", message);
    char *token = strtok(strdup(message), " | ");
    if(strcmp(message, "Matrix") == 0){
        
    }
}

void sendToSlaves(List *slaves, char *action)
{
    char message[COM_MAXLINE];
    for (int i = 0; i < getSize(slaves); i++)
    {
        Slave *temp = ((Slave *)get(slaves, i));
        for (int j = 0; j < getSize(temp->operations); j++)
        {
            Operation *aux = ((Operation *)get(temp->operations, j));
            snprintf(message, COM_MAXLINE, "%s|%d|%d|%s", action, aux->i, aux->j, aux->strOperation);
            sendMessage(temp, message);
            printf("%s del slave %d\n", message, temp->id);
        }
    }
}

bool sendMessage(Slave *slave, char *message)
{
    send(slave->socketFd, message, COM_MAXLINE, 0);
    //recv(slave->socketFd, message, COM_MAXLINE, 0);
    return true;
}

List *getSlaves()
{
    return slaves;
}

void closeConnection(Slave *slave)
{
    slave->isConnected = false;
    close(slave->socketFd);
}

void closeServer(){
    char message[COM_MAXLINE];
    snprintf(message, COM_MAXLINE, "%s|0", "SALIR");
    for (int i = 0; i < slaves->size; i++)
    {
        sendMessage(((Slave *)get(slaves, i)), message);
    }
    
    close(sock->socketfd);
}

int getAction(char *data){
    char *token = strtok(strdup(data), "|");
    for (int i = 0; i < actionsSize; i++)
        if (strcmp(actions[i], token) == 0)
            return i;
    return -1;
}

void setToMatrixResult(char * input){
    char *token = strtok(strdup(input), "|");
    int i = atoi(strtok(NULL, "|"));
    int j = atoi(strtok(NULL, "|"));
    int result = atoi(strtok(NULL, "|"));
    matrixResults1[i][j] = result;
}

int **getMatrixResults() {
    return matrixResults1;
}