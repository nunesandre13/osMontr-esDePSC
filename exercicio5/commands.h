#ifndef COMMANDS_H
#define COMMANDS_H


void list_users(char *unused_first_input, char *unused_second_input, Users *users, Products *unused_products, My_Cart **unused_cart);
void identify_user(char* input_id, char *unused_second_input, Users *unused_users, Products *unused_products, My_Cart **cart);
void list_specified_products(char* input_category, char *input_critery, Users *unused_users, Products *product, My_Cart **unused_cart);
void list_products_in_cart(char *unused_first_input, char *unused_second_input, Users *unused_users, Products *products, My_Cart **cart);
void buy_product(char *input_product_id, char *input_product_quantity,  Users *unused_users, Products *unused_products, My_Cart **cart);
void end_shopping(char *unused_first_input, char *unused_second_input, Users *unused_users, Products *products, My_Cart **cart);

#endif 
