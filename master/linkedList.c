#include "linkedList.h"

void printList(struct Node *head) {
   struct Node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%s) ",ptr->key,ptr->data);
      ptr = ptr->next;
   }
	
   printf(" ]\n");
}

void insertFirst(struct Node *head, int key, char *data) {
   //create a link
   struct Node *link = (struct Node*) malloc(sizeof(struct Node));
	
   link->key = key;
   link->data = data;
	
   //point it to old first Node
   link->next = head;
	
   //point first to new first Node
   head = link;
}