#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Definição da struct para os elementos da lista
typedef struct Node {
    struct Node *next;  // Ponteiro para o próximo nó na lista
    void *data;  // Ponteiro genérico para armazenar dados
} Node;


Node* creatHead();

Node* createNode(void *data) ;

// Função para inserir um novo nó no final da lista
void insert(Node *head, void *data);

// Função para percorrer a lista e aplicar uma função para cada elemento
void forEach(Node *head, void (*func)(void *));

// Função para obter o dado de um nó específico (pela posição)
void* get(Node *head, int index);