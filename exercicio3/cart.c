#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "cart.h"
#include "help.h"


bool cart_put(Cart *cart){
    char *url = "https://dummyjson.com/carts/add";
    // criar o json para mandar
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
    // visualizar no terminal
    char *formatted_json = json_dumps(json_cart, JSON_INDENT(4));
    printf("JSON:\n%s\n", formatted_json);
    json_decref(json_cart);
    return request;
}

Cart *read_cart(char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        fprintf(stderr, "Error opening %s\n", filename);
        return NULL;
    }

    Cart *cart = malloc(sizeof(Cart));
    if(!cart){
        fprintf(stderr, "Error on allocation memory\n");
        fclose(file);
        return NULL;
    }

    char ignore_buffer[100];
    fscanf(file, "%s,%s\n", ignore_buffer, ignore_buffer);
    fscanf(file, "%d,%ld\n", &cart->user_id, &cart->n_products);
    fscanf(file, "%s,%s\n", ignore_buffer, ignore_buffer);

    cart = realloc(cart, sizeof(Cart) + cart->n_products * sizeof(*cart->products));

    if (!cart->products) {
        perror("Error on allocation memory\n");
        free(cart);
        fclose(file);
        return NULL;
    }

    for(int i = 0; i < cart->n_products; i++){
        fscanf(file, "%d,%ld\n", &cart->products[i].id, &cart->products[i].quantity);
    }

    fclose(file);
    return cart;
}

void free_cart(Cart *cart){
    free(cart);
}