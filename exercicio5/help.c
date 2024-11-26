#include <stdio.h>      // Para printf, fprintf e outras funções de I/O
#include <stdlib.h>     // Para funções como exit()
#include <string.h>     // Caso precise de funções de manipulação de strings
#include <jansson.h>    // Para trabalhar com JSON
#include <curl/curl.h>  // Para usar a biblioteca libcurl, que é usada na função get_uri

#include "help.h"

#define BUFFER_CHUNK (4 * 1024)


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

json_t *http_get_json(const char *url) {
	char *json_string = get_uri(url);
	if (json_string == NULL) {
		fprintf(stderr, "***error: \"%s\" not found\n", url);
		exit(EXIT_FAILURE);
	}
	json_error_t error;
	json_t *root = json_loads(json_string, JSON_DECODE_ANY, &error);
	if (!json_is_object(root)) {
		fprintf(stderr, "***error: on line %d: %s\n", error.line, error.text);
		exit(EXIT_FAILURE);
	}
	return root;
}


static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
	struct write_buffer *result = (struct write_buffer *)stream;

	while (result->current + size * nmemb >= result->max - 1) {
		result->buffer = realloc(result->buffer, result->max + BUFFER_CHUNK);
		if (NULL == result->buffer) {
			fprintf(stderr, "Out of memory\n");
			return 0;
		}
		result->max += BUFFER_CHUNK;
	}
	memcpy(result->buffer + result->current, ptr, size * nmemb);
	result->current += size * nmemb;
	return size * nmemb;
}


static size_t read_callback(char *dest, size_t size, size_t nmemb, void *userp)
{
  struct read_buffer *rd = (struct read_buffer *)userp;
  size_t buffer_size = size * nmemb;
 
  if(rd->current < rd->max) {
	/* copy as much as possible from the source to the destination */
	size_t copy_this_much = rd->max - rd->current;
	if (copy_this_much > buffer_size)
		copy_this_much = buffer_size;
	memcpy(dest, rd->buffer + rd->current, copy_this_much);
 
	rd->current -= copy_this_much;
	return copy_this_much; /* we copied this many bytes */
  }
   return 0; /* no more data left to deliver */
}

char *http_post(const char *uri, char *data) {

	curl_global_init(CURL_GLOBAL_DEFAULT);

	CURL *curl = curl_easy_init();

	if (curl != NULL) {

		struct curl_slist *list = NULL;
		list = curl_slist_append(list, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		curl_easy_setopt(curl, CURLOPT_URL, uri);

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

		char *buffer = malloc(BUFFER_CHUNK);
		if (NULL == buffer)
			goto error;

		struct read_buffer read_data = {
			.buffer = buffer,
			.current = 0,
			.max = BUFFER_CHUNK
		};

		read_data.max = strlen(data);
		memcpy(read_data.buffer, data, read_data.max);

		curl_easy_setopt(curl, CURLOPT_READDATA, &read_data);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 3L);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)read_data.max);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

		buffer = malloc(BUFFER_CHUNK);
		if (NULL == buffer)
			goto error;

		struct write_buffer write_result = {
			.buffer = buffer,
			.current = 0,
			.max = BUFFER_CHUNK
		};

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

		CURLcode curl_result = curl_easy_perform(curl);
		free(read_data.buffer);

		curl_easy_cleanup(curl);

		if (CURLE_OK != curl_result) {
			fprintf(stderr, "curl told us %d\n", curl_result);
			goto error;
		}

		write_result.buffer[write_result.current] = '\0';

		return write_result.buffer;
	}
error:
	curl_global_cleanup();
	return NULL;
}



char *get_uri(const char *uri) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL *curl = curl_easy_init();
	if (curl != NULL) {
		curl_easy_setopt(curl, CURLOPT_URL, uri);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		char *buffer = malloc(BUFFER_CHUNK);
		if (NULL == buffer)
			goto error;
		struct write_buffer write_result = {
			.buffer = buffer,
			.current = 0,
			.max = BUFFER_CHUNK
		};
		
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 3L);

		CURLcode curl_result = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		if (CURLE_OK != curl_result) {
			fprintf(stderr, "curl told us %d\n", curl_result);
			goto error;
		}
		write_result.buffer[write_result.current] = '\0';
		return write_result.buffer;
	}
error:
	curl_global_cleanup();
	return NULL;
}


Users *user_get(){
    char *url = "https://dummyjson.com/users";
    json_t *root = http_get_json(url);
    if (!root) {
        fprintf(stderr, "Failed to fetch JSON data\n");
        return NULL;
    }
    json_t *array_users = json_object_get(root, "users");
    if (!array_users || !json_is_array(array_users)) {
        fprintf(stderr, "Invalid or missing 'users' array\n");
        json_decref(root); 
        return NULL;
    }
    
    //cria a head
    Node *head = createHead();

    //ponteiro para o retorno
    Users *head_users = malloc(sizeof(Users));

    head_users -> head = head;

    node_users(head_users,array_users);

    json_decref(root);

    return head_users;
}


 void node_users(Users * users, json_t *array_users){

    //obtem o tamanho do array
    size_t array_size = json_array_size(array_users);

    for(int index = 0; index < array_size; index++){
        json_t *user_json = json_array_get(array_users, index);
        User *new_user = malloc(sizeof(User));
        if (!new_user) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        new_user->id = json_integer_value(json_object_get(user_json, "id"));
        const char *first_name = json_string_value(json_object_get(user_json, "firstName"));
        new_user->name = strdup(first_name);

        insert(users ->head, new_user);
    }
}
