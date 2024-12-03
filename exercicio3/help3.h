#include <stdbool.h>



struct write_buffer {
	char *buffer;
	int current, max;
};

struct read_buffer {
	char *buffer;
	int current, max;
};


bool http_post_json(const char *url, json_t *data);
json_t *http_get_json(const char *url);
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream);
static size_t read_callback(char *dest, size_t size, size_t nmemb, void *userp);
char *http_post(const char *uri, char *data);
char *get_uri(const char *uri);



