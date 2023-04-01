#ifndef __CHTTP_H__
#include <curl/curl.h>
#include <stdbool.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#ifndef MAX_HEADER_SIZE
#define MAX_HEADER_SIZE 255
#endif

#ifndef MAX_ERROR_LENGTH
#define MAX_ERROR_LENGTH 255
#endif

typedef struct Response {
    int status_code;  // status code
    char *body;       // body of the response
    char *error;      // error from the request
} Response;

// Represents an http request
typedef struct Request Request;

// Initializes a new request with given url.
Request *request_new(char *url);

// Free the memory used by request nut not the url or body
void request_free(Request *req);

// Global clean up of global headers and temporary buffers
void request_global_cleanup();

// Set request headers
void request_set_headers(Request *req, struct curl_slist *headers);

// Set request body
void request_set_body(Request *req, char *body);

// Set request callback function that provides you with a curl handle to modify the request.
void request_set_callback(Request *req, void (*callback)(CURL *curl));

// Append headers to global headers. count is the number of headers.
void request_set_global_headers(char headers[][MAX_HEADER_SIZE], int count);

void request_get_response(Request *req, Response *info);

// prints curl headers.
void print_headers(struct curl_slist *headers);

/* Function to parse the origin from a URL */
bool get_origin_from_url(char *url, char *origin);

/**
 * Function to set content type.
 * @returns new headers with it appended.
 */
struct curl_slist *set_content_type(char *content_type, struct curl_slist *headers);

/* Sets authorization header with the token */
struct curl_slist *append_authtoken_header(char *token, struct curl_slist *headers);

/* Function to perform a GET request using CURL */
void client_get(Request *req);

/* Function to perform a POST request using CURL */
void client_post(Request *req);

/* Function to perform a PUT request using CURL */
void client_put(Request *req);

/* Function to perform a PATCH request using CURL */
void client_patch(Request *req);

/* Function to perform a DELETE request using CURL */
void client_delete(Request *req);

#endif /* __CHTTP_H__ */
