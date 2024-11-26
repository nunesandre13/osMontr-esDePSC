#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "list.h"

typedef struct {
    int id;
    float price;
    const char *description;
    const char *category;
} Product;

typedef struct {
    Node *head;
} Products;


Products *products_get();
void node_products(Products *products ,json_t *array_products);
void convert_products_to_csv(Products *products,char *filename);
void free_products(Products *products);
void free_single_product(void *data);
#endif // PRODUCTS_H

