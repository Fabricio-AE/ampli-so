#include "slave.h"

Slave *initSlave(){
    Slave *response = (Slave *)malloc(sizeof(Slave));
    response->operations = createList();
    return response;
}

Slave **createArraySlaves(int size){
    Slave **response = (Slave **)malloc(size * sizeof(Slave*));
    for (int i = 0; i < size; i++){
        response[i] = (Slave *)malloc(size * sizeof(Slave));
        response[i]->operations = createList();
    }
    return response;
}

Operation *initOperation(int i, int j, char* strOperation){
    Operation *response = (Operation*) malloc(sizeof(Operation));
    response->i = i;
    response->j = j;
    response->strOperation = strOperation;
    return response;
}