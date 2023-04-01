#include "chttp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Supported http methods
typedef enum HttpMethod
{
    GET,
    POST,
    PUT,
    PATCH,
    DELETE
} HttpMethod;

// Http methods as an array
const static char methods[][6] = {"GET", "POST", "PUT", "PATCH", "DELETE"};

// Headers to be applied to all requests.
// Allow for authentication, setting content-type for all requests etc.
static struct curl_slist *GLOBAL_HEADERS = NULL;

// Opaque data type representing the Reesponse.
typedef struct ResponseWriter
{
    char *buffer;     // stores the rw body, if error will be NULL
    size_t size;      // size of each item in the rw
    long status_code; // rw status code from the server
    char *error;      // The error returned from server, if no error should be NULL
} ResponseWriter;

// Represents an http request
typedef struct Request
{
    char *url;                  // URL for the request
    struct curl_slist *headers; // Headers for this request
    ResponseWriter *rw;         // Where to write the response
    char *body;                 // Request body, may be NULL for GET requests

    // callback function allows you to customize the request
    // and manipulate the headers before they are set.
    void (*callback)(CURL *);
} Request;

Request *request_new(char *url)
{
    Request *req = malloc(sizeof(Request));
    if (!req)
    {
        printf("unable to initialize request\n");
        return NULL;
    }

    // Allocate memory for the rw
    ResponseWriter *res = calloc(1, sizeof(ResponseWriter));
    if (!res)
    {
        printf("unable to initialize rw\n");
        return NULL;
    }

    // Initialise request members
    req->url = url;
    req->body = NULL;
    req->callback = NULL;
    req->headers = NULL;

    // Attach rw to request
    req->rw = res;

    return req;
}

void request_free(Request *req)
{
    if (req == NULL)
    {
        return;
    }

    // Free the heap allocated rw buffer
    free(req->rw->buffer);
    req->rw->buffer = NULL;

    // Free the reponse
    free(req->rw);

    // Free the request itself, url or body not freed(even if heap allocated)
    free(req);
}

// Frees memory held by request headers after the request.
void free_headers(struct curl_slist *headers)
{
    curl_slist_free_all(headers);
}

void request_global_cleanup()
{
    curl_slist_free_all(GLOBAL_HEADERS);
}

// Helper function to print the headers to stdout
void print_headers(struct curl_slist *headers)
{
    struct curl_slist *current_header = headers;
    while (current_header != NULL)
    {
        printf("%s\n", current_header->data);
        current_header = current_header->next;
    }
}

/* Function to get the origin from a URL */
bool get_origin_from_url(char *url, char *origin)
{
    /* Parse URL */
    CURLU *url_handle = curl_url();
    if (curl_url_set(url_handle, CURLUPART_URL, url, 0) == CURLUE_OK)
    {
        /* Get scheme and host */
        char *scheme, *host;
        if (curl_url_get(url_handle, CURLUPART_SCHEME, &scheme, 0) == CURLUE_OK &&
            curl_url_get(url_handle, CURLUPART_HOST, &host, 0) == CURLUE_OK)
        {
            /* Get port */
            char *port;
            curl_url_get(url_handle, CURLUPART_PORT, &port, 0L);

            /* Build origin */
            sprintf(origin, "%s://%s", scheme, host);
            if (port && strcmp(port, "80") != 0 && strcmp(port, "443"))
            {
                sprintf(origin + strlen(origin), ":%s", port);
            }

            // Free resources
            curl_free(scheme);
            curl_free(host);
            curl_free(port);
        }
        else
        {
            return false;
        }
    }

    /* Clean up url_handle */
    curl_url_cleanup(url_handle);
    return true;
}

// Gets origin from the url and append it to headers and then appends global headers
// to these headers.
// Must be called for each request especially if you want to deal with CORS!!
struct curl_slist *prepare_headers(char *url, struct curl_slist *headers)
{
    // Extract the origin from the URL
    char origin_header[256];
    char origin[255];
    get_origin_from_url(url, origin);

    // Add the Origin header to the list
    snprintf(origin_header, sizeof(origin_header), "Origin: %s", origin);
    headers = curl_slist_append(headers, origin_header);

    // Append global headers since each request.
    struct curl_slist *current_header = GLOBAL_HEADERS;
    while (current_header != NULL)
    {
        headers = curl_slist_append(headers, current_header->data);
        current_header = current_header->next;
    }
    return headers;
}

/* Callback function to write rw data to struct */
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userdata)
{
    ResponseWriter *rw = (ResponseWriter *)userdata;
    size_t data_size = size * nmemb;

    char *ptr = realloc(rw->buffer, rw->size + data_size + 1);
    if (ptr == NULL)
    {
        fprintf(stderr, "realloc() failed to allocated more memory\n");
        return 0;
    }

    /* Copy data to buffer */
    rw->buffer = ptr;
    memcpy(rw->buffer + rw->size, contents, data_size);

    // Update size of http response
    rw->size += data_size;
    // Null terminate the buffer
    rw->buffer[rw->size] = 0;

    return data_size;
}

/**
 * Function to set content type.
 * @returns new headers with it appended.
 */
struct curl_slist *set_content_type(char *content_type, struct curl_slist *headers)
{
    char header[64];
    sprintf(header, "Content-Type: %s", content_type);
    headers = curl_slist_append(headers, header);
    return headers;
}

/* Sets authorization header with the token */
struct curl_slist *append_authtoken_header(char *token, struct curl_slist *headers)
{
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", token);
    headers = curl_slist_append(headers, auth_header);
    return headers;
}

// Helper function to process error after each request.
void handle_error(Request *req, CURLcode curl_code)
{
    if (curl_code == CURLE_OK)
    {
        req->rw->error = NULL;
        return;
    }

    if (req->rw->status_code < 200 || req->rw->status_code >= 300)
    {
        if (req->rw->buffer != NULL)
        {
            strncpy(req->rw->error, req->rw->buffer, MAX_ERROR_LENGTH);
        }
        else
        {
            strncpy(req->rw->error, curl_easy_strerror(curl_code), MAX_ERROR_LENGTH);
        }
    }
    else
    {
        strncpy(req->rw->error, curl_easy_strerror(curl_code), MAX_ERROR_LENGTH);
    }
}

// Helper function that performs the actual request
// and handles errors. Returns true if OK, otherwise returns false.
void perform_request(CURL *curl, Request *req, HttpMethod method)
{
    if (method > DELETE)
    {
        fprintf(stderr, "invalid http method: %d\n", method);
        return;
    }

    // Set Origin and global headers.
    req->headers = prepare_headers(req->url, req->headers);

    curl_easy_setopt(curl, CURLOPT_URL, req->url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, req->rw);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

    // Run callback to allow for user customization of curl before setting the headers
    // and performing the request.
    if (req->callback != NULL)
    {
        req->callback(curl);
    }

    // Set the correct http method after customizing the request.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, methods[method]);
    if (method != GET)
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req->body);
    }

    // Apply the headers
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, req->headers);

    // Perform the request
    CURLcode curl_code;
    curl_code = curl_easy_perform(curl);

    // Get status code
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &req->rw->status_code);

    // Free request headers
    free_headers(req->headers);

    // Free memory held by curl
    curl_easy_cleanup(curl);

    // handle errors
    handle_error(req, curl_code);
}

/* Function to perform a GET request using CURL */
void client_get(Request *req)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "unable to initialize curl");
        return;
    }
    perform_request(curl, req, GET);
}

/* Function to perform a POST request using CURL */
void client_post(Request *req)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "unable to initialize curl");
        return;
    }
    perform_request(curl, req, POST);
}

/* Function to perform a PUT request using CURL */
void client_put(Request *req)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "unable to initialize curl");
        return;
    }
    perform_request(curl, req, PUT);
}

/* Function to perform a DELETE request using CURL */
void client_delete(Request *req)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "unable to initialize curl");
        return;
    }
    perform_request(curl, req, DELETE);
}

/* Function to perform a PATCH request using CURL */
void client_patch(Request *req)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "unable to initialize curl");
        return;
    }
    perform_request(curl, req, PATCH);
}

// Append headers to global headers.
void request_set_global_headers(char headers[][MAX_HEADER_SIZE], int count)
{
    for (int i = 0; i < count; i++)
    {
        GLOBAL_HEADERS = curl_slist_append(GLOBAL_HEADERS, headers[i]);
    }
}

// Reads the rw body into ResponseWriter info struct.
void request_get_response(Request *req, Response *info)
{
    info->status_code = req->rw->status_code;
    info->error = req->rw->error;
    info->body = req->rw->buffer;
}

void request_set_headers(Request *req, struct curl_slist *headers)
{
    req->headers = headers;
}

void request_set_body(Request *req, char *body)
{
    req->body = body;
}

void request_set_callback(Request *req, void (*callback)(CURL *curl))
{
    req->callback = callback;
}

// sudo apt-get install libcurl4-openssl-dev
