#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../exercicio5/helpers.h"
#include "../exercicio5/commands.h"


void list_product_category(char *unused_first_input, char *unused_second_input, Users *unused_users, Products *products, My_Cart **unused_cart){
    putchar('\n');

    if (products->head == NULL) {
        printf("Nenhum produto disponível.\n");
        return;
    }

    Node *new_head = products->head;

    const char *category_buffer[100];  
    int buffer_index = 0; 

    for(Node *product = new_head->next; product != NULL; product = product->next){
        Product* data = (Product *)product->data;
        bool exists = false;
        for(int i = 0; i < buffer_index; i++){
            if(strcmp(category_buffer[i], data->category) == 0){
                exists = true;
                break;
            }
        }
        if(!exists){
            printf("- %s\n", data->category);
            category_buffer[buffer_index] = data->category;
            buffer_index++;
        }
    }
    putchar('\n');
}


char command_letter = 'b';

char *command_description = "\t - listar as categorias dos produtos";