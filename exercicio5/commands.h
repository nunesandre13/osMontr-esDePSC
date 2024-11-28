#ifndef COMMANDS_H
#define COMMANDS_H





void list_users(Users *users);
void identify_user(char* input_id,My_Cart *cart);
void list_specified_products(char* input_category, char *input_critery, Products *products);
void list_products_in_cart(My_Cart *cart, Products *products);
void buy_product(char *input_product_id, char *input_product_quantity, My_Cart *cart);
void end_shopping(My_Cart *cart, Products *products);

#endif 
