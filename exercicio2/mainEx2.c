#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

char *http_post(const char *uri, char *data);

bool http_post_json(const char *url, json_t *data){

    char *string_data = json_dumps(data, 0);
    if(!string_data){
        fprintf(stderr,"Erro ao converter");
        return false;
    }

    char *result = http_post(url,string_data);

    if(result == NULL){
        fprintf(stderr, "Erro no resposta");
        return false;
    }

    printf(" Response: %s\n", result);

    return true;
}

int main(int argc, char *argv[]){
    json_t *json_data = json_load_file(argv[2], 0, NULL);
    if (json_data == NULL) {
        fprintf(stderr, "Erro ao ler o arquivo JSON\n");
        return 0;
    }

    bool result = http_post_json(argv[1], json_data);

    // Envia o POST com o JSON
    if (!result) {
        fprintf(stderr, "Erro ao realizar o POST\n");
        json_decref(json_data);  // Liberar a memória do JSON
        return 1;
    }

    printf("-----------------------------------------------------\n");
    printf("Carrinho Criado de userId: %lld\n", json_integer_value(json_object_get(json_data, "userId")));

    json_decref(json_data);
    return 0;
}
