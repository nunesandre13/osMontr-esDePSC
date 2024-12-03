#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri
#include <errno.h>
#include <dlfcn.h>

#include "../exercicio5/helpers.h"
#include "../exercicio5/commands.h"


//-----------------------------------COMMANDS----------------------------------------------------//

struct command {
	void (*f) (char *, char*, Users *, Products *, My_Cart **);
	char c;
	char *desc;
	struct command *next;
};

static struct command *commands = NULL;

void command_insert(char c, char *desc, void (*f)(char *, char *, Users *, Products *, My_Cart **)){
	struct command *new_command = malloc(sizeof (struct command));
	new_command->c = c;
	new_command->desc = strdup(desc);
	new_command->f = f;
	new_command->next = commands;
	commands = new_command;
}

void command_execute(char command_letter, char *first_input_param, char *second_input_param, Users *users, Products *products, My_Cart **cart){
	for (struct command *p = commands; p != NULL; p = p->next)
		if (p->c == command_letter) {
			p->f(first_input_param, second_input_param, users, products, cart);
			return;
		}
	printf("Infelizmente esse comando não existe\n");
}

void command_list(char *unused_first_input, char *unused_second_input, Users *unused_users, Products *unused_products, My_Cart **unused_cart){
	for (struct command *p = commands; p != NULL; p = p->next)
		printf("%c%s\n", p->c, p->desc);
}

static void *handle;

static void command_new(char *input_lib, char *unused_second_input, Users *unused_users, Products *unused_products, My_Cart **unused_cart){
	void *handle = dlopen(input_lib, RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	void (*f)(char *, char *, Users *, Products *, My_Cart **) = dlsym(handle, "list_product_category");
	if (f == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	char *c = dlsym(handle, "command_letter");
	if (c == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	char **desc = dlsym(handle, "command_description");
	if (desc == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	command_insert(*c, *desc, f);
}


void leave_program(char *unused_first_input, char *unused_second_input, Users *unused_users, Products *unused_products, My_Cart **cart){
	void *next;
	free_my_cart(*cart);
	for (struct command *p = commands; p != NULL; p = next) {
		next = p->next;
		free(p->desc);
		free(p);
	}
	if (handle != NULL)
		dlclose(handle);
	printf("Adeeuusss\n");
	exit(EXIT_SUCCESS);
}



int main(){
    Users *users = user_get();
    Products *products = products_get();
    My_Cart *cart = malloc(sizeof(My_Cart) * 3);
    cart->user_id = -1;
    cart->n_products = 0;
    char line[100];
    command_insert('e', "            - Terminar", leave_program);
	command_insert('h', "            - Listar comandos existentes", command_list);
	command_insert('n', " <libxx.so> - Incorporar novo comando", command_new);
    command_insert('u', "            - Listar os utilizadores", list_users);
    command_insert('t', " <ID> - Identificar um utilizador", identify_user);
    command_insert('p', " <categoria> <quantidade> - Listar os produtos pretendidos", list_specified_products);
    command_insert('c', "            - Listar os produtos presentes no carrinho", list_products_in_cart);
    command_insert('o', " <ID do produto> <quantidade> - Comprar um certo produto x vezes", buy_product);
    command_insert('f', "            - Finalizar a compra e começar com um novo carrinho", end_shopping);
    printf("//-------------------------------------------------------//\n");
    printf("Pode começar...\n");
    putchar('\n');
	while (1) {
		putchar('>');
		if (fgets(line, sizeof(line), stdin) == NULL)
			return EXIT_FAILURE;
		char *command = strtok(line, " \n");
		if (command == NULL)
			continue;
		char *first_option = strtok(NULL, " \n");
        char *second_option = strtok(NULL, " \n");
		command_execute(*command, first_option, second_option, users, products, &cart);
		}
    free_my_cart(cart);
    return 0;
}
