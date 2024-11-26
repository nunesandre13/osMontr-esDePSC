#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri


#include "../exercicio3/users.h"
#include "../exercicio3/products.h"
#include "../exercicio3/cart.h"

Cart *create_cart(size_t n_products){
    Cart *cart = malloc(sizeof(Cart) + sizeof(cart->products[0]) * n_products);

    cart->user_id = -1;
    cart->n_products = n_products;

    for (size_t i = 0; i < n_products; i++) {
        cart->products[i].id = 0;
        cart->products[i].quantity = 0;
    }

    return cart;
}
void list_users(Users *users) { 
    printf("\n");
    Node *new_head = users->head;
    for(Node *user = new_head->next; user != NULL; user = user->next){
        User* data = (User *)user->data;
        if(data != NULL){
            printf("%s\n", data->name);
        }
    }
    printf("\n");
}

void identify_user(char* input_id, Cart *cart){
    printf("\n");
    int id = atoi(input_id);
    if(id == 0){
        printf("Error\n");
    } else {
        cart->user_id = id;
        printf("Carrinho com ID %d inicializado\n", id);
    }
    printf("\n");
}

void list_specified_products(char* input_category, char *critery, Products *products){
    printf("\n");
    int category_chosed = false; // flag 
    if (strcmp(critery, "<") != 0 && strcmp(critery, ">") != 0) {
        printf("Erro: critério inválido. Use '<' ou '>'.\n");
        return; 
    }
    Node *new_head = products->head;
    for(Node *product = new_head->next; product != NULL; product = product->next){
        Product* data = (Product *)product->data;
        if(strcmp(data->category, input_category) == 0){
            category_chosed = true;
            break;
        }
    }
    if(!category_chosed){
        printf("Nºao foi reconhecida a categoria\n");
        printf("\n");
        for (Node *product = new_head->next; product != NULL; product = product->next) {
            Product *data = (Product *)product->data;
            printf("ID do produto: %d, Categoria: %s, Preço: %.2f\n", data->id, data->category, data->price);
        }
    } else {
        for (Node *product = new_head->next; product != NULL; product = product->next) {
            Product *data = (Product *)product->data;
            if(strcmp(data->category,input_category) == 0){
                printf("ID do produto: %d, Categoria: %s, Preço: %.2f\n", data->id, data->category, data->price);
            }
        }
    }
    printf("\n");

    //TODO(), falta fazer o sort
}



int main(){
    Users *users = user_get();
    Products *products = products_get();
    Cart *cart = create_cart(5);
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
            /*
			case 'C':
            case 'c':
                list_products_in_cart();
				break;
			case 'O':
            case 'o':
                if(first_option == NULL || second_option == NULL) {
                    printf("Erro: Tem de user o formato Produtos <categoria> <critério>.\n");
                } else {
                    buy_product(first_option,second_option);
                }
				break;
            
			case 'F':
            case 'f':
				end_shopping();
				break;
            */
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