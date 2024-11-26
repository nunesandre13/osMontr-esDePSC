#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "help.h"
#include "list.h"

typedef struct {
        int id;
        float price;
        const char *description;
        const char *category;
} Product;

typedef struct {
    int id;
    const char *name;
} User;

typedef struct {
    int user_id;
    size_t n_products;
    struct {
        int id;
        size_t quantity;
    } products[];
} Cart;

typedef struct {
    Node *head;
} Users;

typedef struct{
    Node *head;
} Products;

//------------------------------------------------------------//

void list_users() { 
    Users *users = users_get();
    for(Node *head = Users->head; head != NULL; head = head->next){
        User *data = (User *)head->data;
        printf("%s\n", data->name);
    }
}


int main(){
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
                list_users();
                break;
            /*
			case 'T':
            case 't':
                if(first_option == NULL){
                    printf("Erro: Tem de indicar o id\n");
                } else { 
				    identify_user(first_option);
                }
				break;
			case 'P':
            case 'p':
                if(first_option == NULL || second_option == NULL){
                    printf("Erro: Tem de user o formato Produtos <categoria> <critério>.\n");
                } else {
                    list_specified_products(first_option, second_option);
                }
				break;
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
                exit(0);
                break;
            default:
                printf("Não temos esse comando...\n");
                break;
		}
	}
    return 0;
}