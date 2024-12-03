#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri


#include "../exercicio3/users.h"
#include "../exercicio3/products.h"
#include "../exercicio3/cart.h"
#include "../exercicio3/list.h"
#include "../exercicio3/help3.h"


//Escrita dos produtos para o ficheiro products.csv
#if 1
int main() {
    
    Products *products = products_get();
    if (!products) {
        fprintf(stderr, "Failed to fetch products.\n");
        return 1;
    }

    convert_products_to_csv(products, "libraryProducts.csv");

    free_products(products);

    return 0;
}
#endif 


//Escrita dos users para o ficheiro users.csv
#if 0
int main(){
    Users *users = user_get();
    if(!users) {
        fprintf(stderr, "Failed to fetch users. \n");
        return 1;
    }
    convert_users_to_csv(users, "libraryUsers.csv");

    free_users(users); 

    return 0;
}
#endif


//Leitura do ficheiro cart.csv e realização de HTTP POST
#if 0
int main(){
    char *file = "libraryCarts.csv";
    Cart *cart = read_cart(file);

    if (cart_put(cart)) {
        printf("Carrinho enviado com sucesso!\n");
    } else {
        printf("Falha ao enviar o carrinho.\n");
    }
    free_cart(cart);
}
#endif

