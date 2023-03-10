#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _SLAVE_
#define _SLAVE_

#include "../utility/list.h"

typedef struct slave {
    int id;
    int socketFd;
    bool isConnected;
    List *operations;
}Slave;

typedef struct operation {
    int i;
    int j;
    char *strOperation;
}Operation;


Slave *initSlave();
Slave **createArraySlaves(int);
Operation *initOperation(int, int, char*);

#endif