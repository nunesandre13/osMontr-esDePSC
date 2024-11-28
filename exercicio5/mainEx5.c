#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri


#include "helpers.h"
#include "commands.h"

int main(){
    Users *users = user_get();
    Products *products = products_get();
    //Cart *cart = malloc(sizeof(Cart));
    My_Cart *cart = malloc(sizeof(My_Cart));
    cart->user_id = -1;
    cart->n_products = 0;
    cart->products = malloc(sizeof(cart));
    printf("//-------------------------------------------------------//\n");
    printf("Pode começar...\n");
    putchar('\n');
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
                    putchar('\n');
                } else { 
				    identify_user(first_option, cart);
                }
				break;
			case 'P':
            case 'p':
                if(first_option == NULL || second_option == NULL){
                    printf("Erro: Tem de user o formato Produtos <categoria> <critério>.\n");
                    putchar('\n');
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
                    putchar('\n');
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
                free_my_cart(cart);
                exit(0);
                break;
            default:
                printf("Não temos esse comando...\n");
                putchar('\n');
                break;
		}
	}
    free_my_cart(cart);
    return 0;
}