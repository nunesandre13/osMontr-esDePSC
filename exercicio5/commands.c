#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri


#include "helpers.h"
#include "commands.h"


void list_users(Users *users) { 
    putchar('\n');
    Node *new_head = users->head;
    for(Node *user = new_head->next; user != NULL; user = user->next){
        User* data = (User *)user->data;
        if(data != NULL){
            printf("%s---ID:%d\n", data->name, data->id);
        }
    }
    putchar('\n');
}

void identify_user(char* input_id,My_Cart *cart){
    putchar('\n');
    int id = atoi(input_id);
    if(id == 0){
        printf("Error with ID\n");
    } else {
        cart->user_id = id;
        printf("Carrinho com ID %d inicializado\n", id);
    }
    putchar('\n');
}

void list_specified_products(char* input_category, char *input_critery, Products *products){
    putchar('\n');
    int category_chosed = false; // flag 
    if (strcmp(input_critery, "<") != 0 && strcmp(input_critery, ">") != 0) {
        printf("Erro: critério inválido. Use '<' ou '>'.\n");
        putchar('\n');
        return; 
    }
    Node *new_head = products->head;
    int index = 0;
    Product products_products[40];

    for (Node *product = new_head->next; product != NULL; product = product->next) {
        Product* data = (Product *)product->data;
        if(strcmp(data->category, input_category) == 0) category_chosed = true;
        products_products[index] = *data;
        index++;
    }

    if(strcmp(input_critery, "<") == 0) {
        sort(products_products, index, sizeof(Product), descend_cmp);
    } else if (strcmp(input_critery, ">") == 0) {
        sort(products_products, index, sizeof(Product), ascend_cmp);
    }

    if(!category_chosed){
        for (int i = 0; i < index; i++) {
            printf("ID do produto: %d, Categoria: %s, Preço: %.2f\n",
                   products_products[i].id,
                   products_products[i].category,
                   products_products[i].price
            );
        }
    } else {
        for (int i = 0; i < index; i++) {
            if(strcmp(products_products[i].category, input_category) == 0)
            printf("ID do produto: %d, Categoria: %s, Preço: %.2f\n",
                   products_products[i].id,
                   products_products[i].category,
                   products_products[i].price
            );
        }
    }
    putchar('\n');
}




void list_products_in_cart(My_Cart *cart, Products *products){
    if(cart->user_id == -1){
        printf("Não se esqueça de inserir o ID antes de sequer olhar para dentro do carrinho\n");
        putchar('\n');
        return;
    }
    putchar('\n');
    if(cart->n_products == 0){
        printf("O carrinho ainda não tem produtos. Compra algo!\n");
        putchar('\n');
        return;
    }
    printf("Produtos presentes no carrinho:\n");

    for(int i = 0; i < cart->n_products; i++){
        int product_id = cart->products[i]->id;
        size_t product_quantity = cart->products[i]->quantity;

        float product_price = get_product_price(product_id, products);
        const char *product_description = get_product_description(product_id, products);

        printf("Preço: %.2f, Quantidade: %zu, Descrição: %s\n", product_price, product_quantity, product_description);
        putchar('\n');
    }
    putchar('\n');
}

void buy_product(char *input_product_id, char *input_product_quantity, My_Cart *cart){
    if(cart->user_id == -1){
        printf("Não se esqueça de inserir o ID antes de comprar algo\n");
        putchar('\n');
        return;
    }
    int product_id = atoi(input_product_id);
    size_t product_quantity = (size_t) atoi(input_product_quantity);
    if(product_id == 0 || product_quantity == 0){
        printf("Erro ao comprar\n");
    }
    bool product_exists = false;
    for(int i = 0; i < cart->n_products; i++){
        if(cart->products[i]->id == product_id){
            cart->products[i]->quantity += product_quantity;
            product_exists = true;
            printf("Ainda queres mais desse produto?\n");
            break;
        }
    }
    if(!product_exists){
        cart->products = realloc(cart->products, sizeof(cart) * (cart->n_products + 4));
        if (cart->products == NULL) {
            printf("Erro ao alocar memória para o novo produto\n");
            return;
        }
        cart->products[cart->n_products] = malloc(sizeof(My_Product));
        if (cart->products[cart->n_products] == NULL) {
            printf("Erro ao alocar memória para o novo produto\n");
            return;
        }
        cart->products[cart->n_products]->id = product_id;
        cart->products[cart->n_products]->quantity = product_quantity;

        cart->n_products++;
        printf("Novo produto adicionado!\n");
    }
    putchar('\n');
}

void end_shopping(My_Cart *cart, Products *products){
    putchar('\n');
    if(cart->n_products == 0){
        printf("Não existe compra com carrinho vazio...\n");
        putchar('\n');
        return;
    }
    float total_price = 0.0;
    
    for(int i = 0; i < cart->n_products; i++){
        int product_id = cart->products[i]->id;
        size_t product_quantity = cart->products[i]->quantity;
        float product_price = get_product_price(product_id, products);

        total_price += (product_price * product_quantity);
    }

    printf("Preço total: %.2f\n", total_price);
    printf("Até à próxima carrinho com ID %d\n", cart->user_id);
    putchar('\n');

    Cart *cart_to_send = my_cart_convert(cart);
    bool result = cart_put(cart_to_send);
    free_cart(cart_to_send); //Apagar depois de enviar;
    if(!result){
        printf("Falha ao enviar carrinho!");
        return;
    }
    printf("Carrinho enviado com sucesso!\n");
    printf("Novo carrinho retirado, insira o ID e comece as compras!\n");

    reset_my_cart(cart);

    putchar('\n');
}
