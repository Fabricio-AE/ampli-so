#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utility/list.h"

typedef struct slave {
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