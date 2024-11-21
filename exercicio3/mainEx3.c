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

//----------------------------------------------//

typedef struct{
    Products *next;
    Product *data;
} Products;


#if 1
Products *products_get(){
    char *url = "https://dummyjson.com/products";
    json_t *root = http_get_json(url);
    json_t *array_products = json_object_get(root, "products")

    Products *products = node_products(array_products);
}
#endif 

Products *node_products(json_t *products){
    Node *product_head = createHead();
    size_t array_size = json_array_size(products);
    for(int index = 0; index < array_size; index++){
        json_t *product = json_array_get(products, index)
        int id = json_integer_value(json_object_get(product,"id"));
        float price = json_real_value(json_object_get(product,"price"));
        char *description = json_string_value(json_object_get(product,"description"));
        char *category = json_string_value(json_object_get(product,"category"));
        Product *product = malloc(sizeof (Product));
        product->id = id;
        product->price = price ;
        product->description = description; 
        product->category = category;
        insert(product_head, product);
    }
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
