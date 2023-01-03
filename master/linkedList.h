#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
   char *data;
   int key;
   struct Node *next;
};
void printList(struct Node *head);
void insertFirst(struct Node *head, int key, char *data);