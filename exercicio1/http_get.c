#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

#define BUFFER_CHUNK (4 * 1024)

struct write_buffer {
	char *buffer;
	int current, max;
};

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


