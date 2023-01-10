#include "list.h"

List* createList() {
    List* lista = (List*) calloc(1, sizeof (List));
    lista->head = NULL;
    lista->size = 0;
    return lista;
}

void destroyList(List* lista) {
    while (lista->head) {
        Node* eliminado = lista->head;
        lista->head = lista->head->next;
        --lista->size;
        destroyNode(eliminado);
    }
    free(lista);
}

void insert(List* lista, void* data) {
    if (lista == NULL || data == NULL) {
        printf("ERROR: datos de entrada nulos\n");
        exit(-1);
    }
    Node* nodo = createNode(data);
    Node* puntero = lista->head;

    if (lista->head == NULL) {
        lista->head = nodo;
    } else {
        while (puntero->next != NULL) {
            puntero = puntero->next;
        }
        puntero->next = nodo;
    }
    lista->size += 1;
}

void* get(List* lista, int n) {
    if (lista->head == NULL) {
        return NULL;
    }
    Node* puntero = lista->head;
    int c = 0;
    while (c < n && puntero->next) {
        puntero = puntero->next;
        ++c;
    }
    if (c != n) {
        return NULL;
    }
    return puntero->data;
}

int getSize(List* lista) {
    return lista->size;
}

void delete(List* lista, int n) {
    if (n < 0 || n >= lista->size) {
        printf(">> ERROR: índice del nodo a eliminar fuera de los extremos de la lista");
    }


    if (lista->head) {
        --lista->size;
        if (n == 0) {
            Node* eliminado = lista->head;
            lista->head = lista->head->next;
            destroyNode(eliminado);
        } else if (n < lista->size) {
            Node* puntero = lista->head;
            int c;
            for (c = 0; c < n - 1; c++)
                puntero = puntero->next;

            Node* eliminado = puntero->next;
            puntero->next = eliminado->next;

            destroyNode(eliminado);

        }
    }
}

bool isEmpty(List* lista) {
    return lista->head == NULL;
}
