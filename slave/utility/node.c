#include "node.h"

Node* createNode(void* data){
    Node* node = calloc(1, sizeof(Node));
    node->data = data; //It could be NULL
    node->previous = NULL;
    node->next = NULL;
    return node;
}

void destroyNode(Node* node){
    node->data = NULL;
    node->next = node->previous = NULL;
    free(node);
}

