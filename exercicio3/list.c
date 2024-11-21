#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Definição da struct para os elementos da lista
typedef struct Node {
    struct Node *next;  // Ponteiro para o próximo nó na lista
    void *data;  // Ponteiro genérico para armazenar dados
} Node;



Node* createHead(){
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = NULL;
        newNode->next = NULL;
    }
    return newNode;
}


Node* createNode(void *data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Função para inserir um novo nó a seguir a HEAD
void insert(Node *head, void *data) {
    Node *newNode = createNode(data);
    if (head-> next == NULL) {
        head -> next = newNode; 
    } else {
        Node *dummy = head -> next;
        head -> next = newNode;
        newNode -> next = dummy;
    }

}




// Função para percorrer a lista e aplicar uma função para cada elemento
void forEach(Node *head, void (*func)(void *)) {
    Node *temp = head;
    while (temp != NULL) {
        func(temp->data);  // Aplica a função nos dados do nó
        temp = temp->next;  // Move para o próximo nó
    }
}

// Função para obter o dado de um nó específico (pela posição)
void* get(Node *head, int index) {
    Node *temp = head;
    int currentIndex = 0;
    while (temp != NULL) {
        if (currentIndex == index) {
            return temp->data;  // Retorna os dados do nó na posição indicada
        }
        currentIndex++;
        temp = temp->next;
    }
    return NULL;  // Retorna NULL se a posição for inválida
}

void freeList(Node *head, void (*free_data)(void *)) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;

        if (current->data != NULL && free_data != NULL) {
            free_data(current->data); 
        }

        free(current); 
        current = next;
    }
}
