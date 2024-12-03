#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <stdbool.h>
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri



typedef struct {
    int user_id;
    size_t n_products;
    struct {
        int id;
        size_t quantity;
    } products[];
} Cart;

bool cart_put(Cart *cart);
Cart *read_cart(char *filename);
void free_cart(Cart *cart);
    