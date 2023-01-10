
#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node{
    struct Node* next;
    struct Node* previous;
    void* data;
}Node;

Node* createNode(void* data);

void destroyNode(Node* node);



#endif