#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "help.h"
#include "list.h"

json_t *http_get_json(const char *url);

typedef struct {
        int id;
        float price;
        const char *description;
        const char *category;
} Product;

typedef struct {
    int id;
    const char *name;
} User;

typedef struct {
    int user_id;
    size_t n_products;
    struct {
        int id;
        size_t quantity;
    } products[];
} Cart;

//--------------------------------------------------------------------//

typedef struct{
    Node *head;
} Products;


Products *products_get(){
    char *url = "https://dummyjson.com/products";
    json_t *root = http_get_json(url);
    if (!root) {
        fprintf(stderr, "Failed to fetch JSON data\n");
        return NULL;
    }

    json_t *array_products = json_object_get(root, "products");
    if (!array_products || !json_is_array(array_products)) {
        fprintf(stderr, "Invalid or missing 'products' array\n");
        json_decref(root); // Libera a memória do JSON raiz
        return NULL;
    }

    Products *products = node_products(array_products);

    json_decref(root);

    return products;
}

Products *node_products(json_t *array_products){
    //cria a head
    Node *product_head = createHead();

    //obtem o tamanho do array
    size_t array_size = json_array_size(array_products);

    for(int index = 0; index < array_size; index++){
        json_t *product_json = json_array_get(array_products, index)
        Product *new_product = malloc(sizeof(Product));
        if (!product) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        new_product->id = json_integer_value(json_object_get(product_json, "id"));
        new_product->price = json_real_value(json_object_get(product_json, "price"));
        new_product->description = strdup(json_string_value(json_object_get(product_json, "description")));
        new_product->category = strdup(json_string_value(json_object_get(product_json, "category")));

        insert(product_head, new_product);
    }
    return products_head;
}

//---------------------------------------------------------------------------------//

typedef struct {
    Node
} Users;


Users *user_get(){
    char *url = "https://dummyjson.com/users";
    json_t *root = http_get_json(url);
    if (!root) {
        fprintf(stderr, "Failed to fetch JSON data\n");
        return NULL;
    }
    json_t *array_users = json_object_get(root, "users");
    if (!array_users || !json_is_array(array_users)) {
        fprintf(stderr, "Invalid or missing 'products' array\n");
        json_decref(root); 
        return NULL;
    }

    Users *users = node_users(array_users);

    json_decref(root);

    return users;
}


Users *node_users(json_t *array_users){
    //cria a head
    Node *user_head = createHead();

    //obtem o tamanho do array
    size_t array_size = json_array_size(array_users);

    for(int index = 0; index < array_size; index++){
        json_t *user_json = json_array_get(array_users, index)
        User *new_user = malloc(sizeof(User));
        if (!user) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        new_user->id = json_integer_value(json_object_get(user_json, "id"));
        new_user->name = json_string_value(json_object_get(user_json, "name"));

        insert(user_head, new_user);
    }
    return user_head;
}




int main(){
    char *url = "https://dummyjson.com/products";
    json_t *root = http_get_json(url);

    if (root) {
        json_dumpf(root, stdout, JSON_INDENT(4)); 
        fprintf(stderr, "Failed to get JSON\n");
    }
    if (root != NULL)
        printf("OK\n");
}
