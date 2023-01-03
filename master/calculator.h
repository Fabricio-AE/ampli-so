#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

char ***getMatrixOperations(int **matrixA, int **matrixB, int *sizeA, int *sizeB);
char **distributeMatrix(char ***operations, int sizeSlaves);