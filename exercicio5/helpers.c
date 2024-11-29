#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri


#include "helpers.h"


void free_my_cart(My_Cart *cart) {
    if (cart == NULL) return;

    for (int i = 0; i < cart->n_products; i++) {
        free(cart->products[i]); 
    }

    free(cart);
}

void reset_my_cart(My_Cart *cart){
    cart->user_id = -1;
    cart->n_products = 0;
    
    for (int i = 0; i < cart->n_products; i++) {
        free(cart->products[i]); 
    }

}

Cart *my_cart_convert(My_Cart *my_cart) {
    Cart *cart = malloc(sizeof(Cart) + my_cart->n_products * sizeof(*cart->products));
    if (cart == NULL) {
        printf("Erro ao alocar memória para Cart\n");
        return NULL;
    }

    
    cart->user_id = my_cart->user_id;
    cart->n_products = my_cart->n_products;

    for (size_t i = 0; i < my_cart->n_products; i++) {
        cart->products[i].id = my_cart->products[i]->id;
        cart->products[i].quantity = my_cart->products[i]->quantity;
    }

    return cart;
}



int ascend_cmp(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    if (productA->price < productB->price) return -1;
    if (productA->price > productB->price) return 1;
    return 0;
}

int descend_cmp(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    if (productA->price > productB->price) return -1;
    if (productA->price < productB->price) return 1;
    return 0;
}

void swap(const void *a, const void *b, size_t elem_size) {
	char tmp[elem_size];
	memcpy(tmp, a, elem_size);
	memcpy((void *)a, b, elem_size);
	memcpy((void *)b, tmp, elem_size);
}


void sort(const void *products, size_t products_size, size_t elem_size,
		int (*compare)(const void *, const void *) ) {
	for (int i = 0; i < products_size - 1; ++i)
		for (int j = 0; j < products_size - 1 - i; ++j)
			if (compare(products + j * elem_size,
					products + (j + 1) * elem_size) > 0)
				swap(products + j * elem_size,
					products + (j + 1) * elem_size, elem_size);
}

float get_product_price(int id, Products *products){
    Node *new_head = products->head;
    for(Node *product = new_head->next; product != NULL; product = product->next){
        Product* data = (Product *)product->data;
        if(data->id == id) {
            return data->price;
        } 
    }
}

const char *get_product_description(int id, Products *products){
    Node *new_head = products->head;
    for(Node *product = new_head->next; product != NULL; product = product->next){
        Product* data = (Product *)product->data;
        if(data->id == id) {
            return data->description;
        } 
    }
}
