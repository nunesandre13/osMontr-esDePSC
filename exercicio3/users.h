#ifndef USERS_H
#define USERS_H

#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <stdbool.h>
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "list.h"

typedef struct {
    int id;
    const char *name;
} User;

typedef struct {
    Node *head;
} Users;

Users *user_get();
void node_users(Users * users, json_t *array_users);
void convert_users_to_csv(Users *users, char *filename);
void free_users(Users *users);
void free_single_user(void *data);
#endif // USERS_H