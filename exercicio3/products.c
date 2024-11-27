#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "products.h"
#include "help3.h"

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

void convert_products_to_csv(Products *products,char *filename) {
    FILE *file = fopen(filename, "w");

    fprintf(file, "ID\tPrice\tDescription\tCategory\n");

    Node *current = products->head->next;
    while(current != NULL){
        Product *single_product = current->data;
        fprintf(file,"%d\t%.2f\t\"%s\"\t\"%s\"\n",
                single_product->id,
                single_product->price,
                single_product->description,
                single_product->category
        );
        current = current->next;
    }
    fclose(file);
}


void free_products(Products *products){
    free_list(products->head, free_single_product);
}

void free_single_product(void *data){
    Product *product = (Product *)data;
    free(product);
}

