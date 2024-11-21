#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "help.h"
#include "list.h"


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

    //cria a head
    Node *head = createHead();

    //ponteiro para o retorno
    Products *head_products = malloc(sizeof(Products));

    head_products -> head = head;

    node_products(head_products,array_products);

    json_decref(root);

    return head_products;
}

void node_products(Products *products ,json_t *array_products){
 
    //obtem o tamanho do array
    size_t array_size = json_array_size(array_products);

    for(int index = 0; index < array_size; index++){
        json_t *product_json = json_array_get(array_products, index);
        Product *new_product = malloc(sizeof(Product));
        if (!new_product) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        new_product->id = json_integer_value(json_object_get(product_json, "id"));
        new_product->price = json_real_value(json_object_get(product_json, "price"));
        new_product->description = strdup(json_string_value(json_object_get(product_json, "description")));
        new_product->category = strdup(json_string_value(json_object_get(product_json, "category")));

        insert(products -> head, new_product);
    }
}

//--------------------------------------------------------------------------------------------------------//

typedef struct {
    Node *head;
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
        new_user->name = json_string_value(json_object_get(user_json, "name"));

        insert(users ->head, new_user);
    }
}


//-----------------------------------------------------------------------------------------------//
bool cart_put(Cart *cart){
    char *url = "https://dummyjson.com/carts/ahfweifhwer";
    json_t *json_cart = json_object();
    if (!json_cart) {
        fprintf(stderr, "Failed to create JSON object\n");
        return false;
    }

    int result1 = json_object_set_new(json_cart, "userId", json_integer(cart->user_id));
    int result2 = json_object_set_new(json_cart, "totalProducts", json_integer(cart->n_products));
    if(result1 != 0 || result2 != 0){
        json_decref(json_cart);
        return false;
    } 

    // criar array
    json_t *products_array = json_array();
    if (!products_array) {
        fprintf(stderr, "Failed to create JSON object\n");
        json_decref(json_cart);
        return false;
    }

    for(int i = 0; i < cart->n_products;i++){
        json_t *json_single_product = json_object();
        if (!json_single_product) {
            fprintf(stderr, "Failed to create JSON object for product\n");
            json_decref(products_array);
            json_decref(json_cart);
            return false;
        }
        int result1 = json_object_set_new(json_single_product, "id", json_integer(cart->products[i].id));
        int result2 = json_object_set_new(json_single_product, "quantity", json_integer(cart->products[i].quantity));
        if (result1 != 0 || result2 != 0) {
            json_decref(json_single_product);
            json_decref(products_array);
            json_decref(json_cart);
            return false;
        }
        json_array_append_new(products_array,json_single_product);
    }

    int result3 = json_object_set_new(json_cart, "products", products_array);
    if(result3 != 0) {
        fprintf(stderr, "Failed to create JSON object\n");
        json_decref(json_cart);
        return false;
    }

    bool request = http_post_json(url, json_cart);
    char *formatted_json = json_dumps(json_cart, JSON_INDENT(4));
    printf("JSON:\n%s\n", formatted_json);
    json_decref(json_cart);
    return request;
}



#if 0
int main() {
    // Definir o número de produtos
    size_t n_products = 2;

    // Alocar memória para a estrutura Cart e seus produtos
    Cart *cart = (Cart *)malloc(sizeof(Cart) + n_products * sizeof(cart->products[0]));

    // Inicializar os campos
    cart->user_id = 33;
    cart->n_products = n_products;

    // Inicializar os produtos
    cart->products[0].id = 1;
    cart->products[0].quantity = 3;
    
    cart->products[1].id = 2;
    cart->products[1].quantity = 5;

    // Testar a função cart_put
    if (cart_put(cart)) {
        printf("Carrinho enviado com sucesso!\n");
    } else {
        printf("Falha ao enviar o carrinho.\n");
    }

    // Liberar memória alocada para a estrutura Cart
    free(cart);

    return 0;
}
#endif