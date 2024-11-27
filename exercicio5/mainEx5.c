#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri


#include "../exercicio3/users.h"
#include "../exercicio3/products.h"
#include "../exercicio3/cart.h"

int ascend_cmp(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    if (productA->price < productB->price) return -1;
    if (productA->price > productB->price) return 1;
    return 0;
}

// Função de comparação para ordenar por preço (decrescente)
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


void sort(const void *array, size_t array_size, size_t elem_size,
		int (*compare)(const void *, const void *) ) {
	for (int i = 0; i < array_size - 1; ++i)
		for (int j = 0; j < array_size - 1 - i; ++j)
			if (compare(array + j * elem_size,
					array + (j + 1) * elem_size) > 0)
				swap(array + j * elem_size,
					array + (j + 1) * elem_size, elem_size);
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

void identify_user(char* input_id, Cart *cart){
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
        return; 
    }
    Node *new_head = products->head;
    int index = 0;
    Product array_products[40];

    for (Node *product = new_head->next; product != NULL; product = product->next) {
        Product* data = (Product *)product->data;
        if(strcmp(data->category, input_category) == 0) category_chosed = true;
        array_products[index] = *data;
        index++;
    }

    if(strcmp(input_critery, "<") == 0) {
        sort(array_products, index, sizeof(Product), descend_cmp);
    } else if (strcmp(input_critery, ">") == 0) {
        sort(array_products, index, sizeof(Product), ascend_cmp);
    }

    if(!category_chosed){
        for (int i = 0; i < index; i++) {
            printf("ID do produto: %d, Categoria: %s, Preço: %.2f\n",
                   array_products[i].id,
                   array_products[i].category,
                   array_products[i].price
            );
        }
    } else {
        for (int i = 0; i < index; i++) {
            if(strcmp(array_products[i].category, input_category) == 0)
            printf("ID do produto: %d, Categoria: %s, Preço: %.2f\n",
                   array_products[i].id,
                   array_products[i].category,
                   array_products[i].price
            );
        }
    }
    putchar('\n');
}




void list_products_in_cart(Cart *cart, Products *products){
    putchar('\n');
    if(cart->n_products == 0){
        printf("O carrinho ainda não tem produtos. Compra algo!\n");
        return;
    }
    printf("Produtos presentes no carrinho:\n");

    for(int i = 0; i < cart->n_products; i++){
        int product_id = cart->products[i].id;
        size_t product_quantity = cart->products[i].quantity;

        float product_price = get_product_price(product_id, products);
        const char *product_description = get_product_description(product_id, products);

        printf("Preço: %.2f, Quantidade: %zu, Descrição: %s\n", product_price, product_quantity, product_description);
        putchar('\n');
    }
    putchar('\n');
}

void buy_product(char *input_product_id, char *input_product_quantity, Cart *cart){
    
    int product_id = atoi(input_product_id);
    size_t product_quantity = (size_t) atoi(input_product_quantity);
    if(product_id == 0 || product_quantity == 0){
        printf("Erro ao comprar\n");
    }
    bool product_exists = false;
    for(int i = 0; i < cart->n_products; i++){
        if(cart->products[i].id == product_id){
            cart->products[i].quantity += product_quantity;
            product_exists = true;
            printf("Ainda queres mais desse produto?\n");
            break;
        }
    }
    if(!product_exists){
        cart = realloc(cart, sizeof(Cart) + (cart->n_products + 1) * sizeof(Product));

        cart->products[cart->n_products].id = product_id;
        cart->products[cart->n_products].quantity = product_quantity;

        cart->n_products++;
        printf("Novo produto adicionado!\n");
    }
    putchar('\n');
}

void end_shopping(Cart *cart, Products *products){
    putchar('\n');
    if(cart->n_products == 0){
        printf("Não existe compra com carrinho vazio...\n");
        return;
    }
    float total_price = 0.0;

    for(int i = 0; i < cart->n_products; i++){
        int product_id = cart->products[i].id;
        size_t product_quantity = cart->products[i].quantity;
        float product_price = get_product_price(product_id, products);

        total_price += (product_price * product_quantity);
    }
    printf("Preço total: %.2f\n", total_price);
    printf("Até à próxima carrinho com ID %d\n", cart->user_id);
    exit(0);
}




int main(){
    Users *users = user_get();
    Products *products = products_get();
    Cart *cart = malloc(sizeof(Cart));
    printf("//-------------------------------------------------------//\n");
    printf("Now you can start\n");
	char line[100];
	while (1) {
		if (fgets(line, sizeof(line), stdin) == NULL)
			return EXIT_FAILURE;
		char *command = strtok(line, " \n");
		if (command == NULL)
			continue;
		char *first_option = strtok(NULL, " \n");
        char *second_option = strtok(NULL, " \n");
		switch (command[0]) {
			case 'U':
            case 'u':
                list_users(users);
                break;
			case 'T':
            case 't':
                if(first_option == NULL){
                    printf("Erro: Tem de indicar o id\n");
                } else { 
				    identify_user(first_option, cart);
                }
				break;
			case 'P':
            case 'p':
                if(first_option == NULL || second_option == NULL){
                    printf("Erro: Tem de user o formato Produtos <categoria> <critério>.\n");
                } else {
                    list_specified_products(first_option, second_option, products);
                }
				break;
			case 'C':
            case 'c':
                list_products_in_cart(cart, products);
				break;
			case 'O':
            case 'o':
                if(first_option == NULL || second_option == NULL) {
                    printf("Erro: Tem de user o formato Produtos <categoria> <critério>.\n");
                } else {
                    buy_product(first_option, second_option, cart);
                }
				break;
			case 'F':
            case 'f':
				end_shopping(cart, products);
				break;
            case 'E':
            case 'e':
                printf("Bye Byee!\n");
                free_cart(cart);
                exit(0);
                break;
            default:
                printf("Não temos esse comando...\n");
                break;
		}
	}
    free_cart(cart);
    return 0;
}