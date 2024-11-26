
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
Users *user_get();
void node_users(Users * users, json_t *array_users);

