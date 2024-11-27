#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "users.h"
#include "help3.h"


Users *user_get(){
    char *url = "https://dummyjson.com/users";
    json_t *root = http_get_json(url);
    if (!root) {
        fprintf(stderr, "Failed to fetch JSON data\n");
        return NULL;
    }
    json_t *array_users = json_object_get(root, "users");
    if (!array_users || !json_is_array(array_users)) {
        fprintf(stderr, "Invalid or missing 'users' array\n");
        json_decref(root); 
        return NULL;
    }
    
    //cria a head
    Node *head = createHead();

    //ponteiro para o retorno
    Users *head_users = malloc(sizeof(Users));

    head_users -> head = head;

    node_users(head_users,array_users);

    json_decref(root);

    return head_users;
}


 void node_users(Users * users, json_t *array_users){

    //obtem o tamanho do array
    size_t array_size = json_array_size(array_users);

    for(int index = 0; index < array_size; index++){
        json_t *user_json = json_array_get(array_users, index);
        User *new_user = malloc(sizeof(User));
        if (!new_user) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        new_user->id = json_integer_value(json_object_get(user_json, "id"));
        const char *first_name = json_string_value(json_object_get(user_json, "firstName"));
        new_user->name = strdup(first_name);

        insert(users ->head, new_user);
    }
}

void convert_users_to_csv(Users *users, char *filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }
    
    fprintf(file, "ID\tName\n");

    Node *current = users->head->next;
    while(current != NULL){
        User *single_user = current->data;
        fprintf(file, "%d\t\"%s\"\n",
                single_user->id,
                single_user->name
        );
        current = current->next;
    }
    fclose(file);
}


void free_users(Users *users){
    free_list(users->head, free_single_user);
}

void free_single_user(void *data){
    User *user = (User *)data;
    free(user);
}
