#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef _OPERATION_
#define _OPERATION_

typedef struct operation {
    int i;
    int j;
    void *strOperation;
}Operation;

Operation *initOperation(int, int, void*);

#endif