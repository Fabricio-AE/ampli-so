#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int **getMatrix(char *fileName);
int *getRow(char *row);
int sizeRows(char *fileName);
int sizeColumns(char *fileName);
int isMultiply(int *sizeA, int *sizeB);
int existsFile(char *fileName);