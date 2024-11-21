#include "list.h"

// Implementação das funções associadas à lista
Node* createHead() {
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

void insert(Node *head, void *data) {
    Node *newNode = createNode(data);
    if (head->next == NULL) {
        head->next = newNode;
    } else {
        Node *dummy = head->next;
        head->next = newNode;
        newNode->next = dummy;
    }
}

void forEach(Node *head, void (*func)(void *)) {
    Node *temp = head;
    while (temp != NULL) {
        func(temp->data);
        temp = temp->next;
    }
}

void* get(Node *head, int index) {
    Node *temp = head;
    int currentIndex = 0;
    while (temp != NULL) {
        if (currentIndex == index) {
            return temp->data;
        }
        currentIndex++;
        temp = temp->next;
    }
    return NULL;
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
