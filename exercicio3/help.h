

char *get_uri(const char *uri);
json_t *http_get_json(const char *url);
char *http_post(const char *uri, char *data);
bool http_post_json(const char *url, json_t *data);