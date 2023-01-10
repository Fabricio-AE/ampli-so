#include "socket.h"

#define COM_MAXLINE 512

int socketFd;
int peticiones = 0;
int action = -1;
char *actions[] = {
    "Matrix",
    "Pi",
    "ToResolve",
    "SALIR"};
int actionsSize = 4;

Slave *slave;

bool connectSocket(char *ip, int port)
{
    slave = initSlave();

    struct sockaddr_in addr;
    int sd, status;
    pthread_t listenServerThread;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if ((sd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Error al crear el socket\n");
        exit(0);
    }
    if (connect(sd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("Error al conectar\n");
        exit(0);
    }
    else
    {
        if ((status = pthread_create(&listenServerThread, NULL, listenServer, NULL)))
        {
            printf("Error al crear hilo para recibir\n");
            close(sd);
            exit(0);
        }
        socketFd = sd;
        pthread_join(listenServerThread, NULL);
    }
}

void *listenServer(void *data)
{
    printf("Up!\n");
    int activo = 1;
    char buffer[COM_MAXLINE];
    while (activo)
    {
        recv(socketFd, buffer, COM_MAXLINE, 0);
        sendMessage("Recibido");
        printf("Buffer -> %s\n", buffer);
        action = getAction(buffer);
        printf("Action -> %d\n", action);
        if (action == 0)
        {

            pthread_t hilo_tarea;
            pthread_create(&hilo_tarea, NULL, doMatrix, (void *)buffer);
            pthread_join(hilo_tarea, NULL);
        }
        if (action == 3)
        {
            activo = 0;
            printf("Saliendo...\n");
            for (int i = 0; i < slave->operations->size; i++)
            {
                Operation *temp = ((Operation *)get(slave->operations, i));
                printf("|%s| -> ", (char *)((Operation *)get(slave->operations, i))->strOperation);
            }
            printf("NULL\n");

            close(socketFd);
            continue;
        }
    }
}

int getAction(char *data)
{
    char *token = strtok(strdup(data), "|");
    for (int i = 0; i < actionsSize; i++)
        if (strcmp(actions[i], token) == 0)
            return i;
    return -1;
}

bool sendMessage(char *message)
{
    char temp[COM_MAXLINE];
    snprintf(temp, COM_MAXLINE, "%s", message);
    send(socketFd, temp, COM_MAXLINE, 0);
    return true;
}

Operation *resolveOperation(Operation *operation)
{
    int tamanio = getSizeNumbers((char *)operation->strOperation);
    int vector[tamanio];
    int result = 0;

    char *token = strtok(strdup((char *)operation->strOperation), "+*");
    printf("oper: %s\n", (char *)operation->strOperation);
    int count = 0;

    while (token != NULL)
    {
        vector[count++] = atoi(token);
        token = strtok(NULL, "+*");
    }

    for (int i = 0; i < tamanio - 1; i = i + 2)
    {
        result += vector[i] * vector[i + 1];
    }

    Operation *temp = (Operation *)malloc(sizeof(Operation));
    temp->i = operation->i;
    temp->j = operation->j;
    temp->strOperation = (void *)result;
    
    printf("Resultado: %d\n", (int) temp->strOperation);
    return temp;
}

void *doMatrix(void *input)
{
    char *token = strtok(strdup(input), "|");
    int i = atoi(strtok(NULL, "|"));
    int j = atoi(strtok(NULL, "|"));
    char *operation = strtok(NULL, "|");

    Operation *response = (Operation *)malloc(sizeof(Operation));
    response->i = i;
    response->j = j;
    response->strOperation = (void *)operation;

    response = resolveOperation(response);

    insert(slave->operations, (void *)response);

    printf("Operation R: %d, %d -> %d\n", response->i, response->j, (int) response->strOperation);
    
    char message[COM_MAXLINE];
    snprintf(message, COM_MAXLINE, "%s|%d|%d|%d", "Matrix", response->i, response->j, (int*) response->strOperation);
    sendMessage(message);
    
    return;
}

void *doPi(void *input)
{
}

int getSizeNumbers(char *operation)
{
    char *token = strtok(strdup(operation), "+*");
    int count = 0;

    while (token != NULL)
    {
        count++;
        token = strtok(NULL, "+*");
    }

    return count;
}

int getSocket()
{
    return socketFd;
}