#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

typedef struct list
{
   Node *head;
   Node *tail;
   int size;
} List;

List *createList();
void destroyList(List *);
void insert(List *, void *);
void *get(List *, int);
void eleminarInicio(List *);
void eliminarFinal(List *);
void delete(List *, int);
int getSize(List *);
bool isEmpty(List *);