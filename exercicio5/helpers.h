#ifndef HELPERS_H
#define HELPERS_H


#include "../exercicio3/users.h"
#include "../exercicio3/products.h"
#include "../exercicio3/cart.h"

typedef struct{
    int id;
    size_t quantity;
} My_Product;

typedef struct {
    int user_id;
    size_t n_products;
    My_Product *products[];
} My_Cart;


void free_my_cart(My_Cart *cart);
void reset_my_cart(My_Cart *cart);
Cart *my_cart_convert(My_Cart *my_cart);
int ascend_cmp(const void *a, const void *b);
int descend_cmp(const void *a, const void *b);
void swap(const void *a, const void *b, size_t elem_size);
void sort(const void *products, size_t products_size, size_t elem_size,
		int (*compare)(const void *, const void *) );
float get_product_price(int id, Products *products);
const char *get_product_description(int id, Products *products);


#endif 