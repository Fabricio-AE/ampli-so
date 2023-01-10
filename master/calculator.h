#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _CALCULATOR_
#define _CALCULATOR_

#include "utility/list.h"
#include "domain/slave.h"

char ***getMatrixOperations(int **matrixA, int **matrixB, int *sizeA, int *sizeB);
void distributeMatrix(char ***operations, int *size, List *slaves, int sizeSlaves);

#endif