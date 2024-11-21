#include <stdio.h>
#include <stdlib.h>


// Definição da struct para os elementos da lista
typedef struct Node {
    struct Node *next;  // Ponteiro para o próximo nó na lista
    void *data;  // Ponteiro genérico para armazenar dados
} Node;

Node* createHead();
Node* createNode(void *data) ;
void insert(Node *head, void *data);
void forEach(Node *head, void (*func)(void *));
void* get(Node *head, int index);
void freeList(Node *head, void (*free_data)(void *));