#include "operation.h"

Operation *initOperation(int i, int j, void* strOperation){
    Operation *response = (Operation*) malloc(sizeof(Operation));
    response->i = i;
    response->j = j;
    response->strOperation = strOperation;
    return response;
}