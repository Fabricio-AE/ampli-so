#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain/slave.h"

char ***getMatrixOperations(int **matrixA, int **matrixB, int *sizeA, int *sizeB);
Slave **distributeMatrix(char ***operations, int *size, int sizeSlaves);