#include <curl/curl.h>
#include <json-c/json.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Headers struct curl_slist
#define BASE_URL "https://localhost:8089/api/v1"
#define MAX_ERROR_SIZE 256
#define TOKEN_LENGTH 120
#define ACTUAL_TOKEN_LENGTH 116
#define AUTH_HEADER_LENGTH (TOKEN_LENGTH + 22)
#define MAX_URL_SIZE 128
#define LOGIN_FILE ".eclinicrc"

static char AUTH_TOKEN[TOKEN_LENGTH] = "";

typedef struct Response {
    char *buffer;  // pointer to memory holding the response buffer
    size_t size;   // Size of each element
    long status;   // HTTP status code
    char error[MAX_ERROR_SIZE];
} Response;

typedef struct Permission {
    int id;
    int code;
    int user_id;
    char name[30];
} Permission;

typedef struct User {
    int id;
    char first_name[25];
    char last_name[25];
    char username[25];
    char email[50];
    char created_at[30];
    bool is_superuser;
    bool active;
    int nperms;
    Permission permissions[40];
} User;

typedef struct LoginResponse {
    User user;
    char token[ACTUAL_TOKEN_LENGTH];
} LoginResponse;

typedef struct Request {
    CURL *curl;
    Headers *headers;
    Response *res;
} Request;

/**
 * Safe strncpy.
 * Copy at most dest_len bytes from src to dest.
 * dest_len is the buffer size of the destination. String is guaranteed to be
 * null-terminated.
 **/
char *sstrncpy(char *dest, const char *src, size_t dest_len) {
    size_t n = dest_len - 1;
    strncpy(dest, src, n);
    dest[n] = '\0';
    return dest;
}

void print_user(User *user) {
    printf("%s %s<%s>\n", user->first_name, user->last_name, user->email);
}

void print_user_permissions(Permission *permissions, int count) {
    printf("────────────────────────────────────────────────────────────");
    printf("\n%-30s%-10s%-10s%-10s\n", "Permission Name", "ID", "UserID",
           "Code");
    printf("────────────────────────────────────────────────────────────");
    for (int i = 0; i < count; i++) {
        Permission p = permissions[i];
        printf("\n%-30s%-11d%-11d%-11d\n", p.name, p.id, p.user_id, p.code);
        printf("────────────────────────────────────────────────────────────");
    }

    printf("\n");
}

void user_fromjson(json_object *userobj, User *user) {
    json_object *id, *username, *first_name, *last_name, *email, *created_at,
        *is_superuser, *active, *perms;

    id = json_object_object_get(userobj, "id");
    username = json_object_object_get(userobj, "username");
    first_name = json_object_object_get(userobj, "first_name");
    last_name = json_object_object_get(userobj, "last_name");
    email = json_object_object_get(userobj, "email");
    created_at = json_object_object_get(userobj, "created_at");
    is_superuser = json_object_object_get(userobj, "is_superuser");
    active = json_object_object_get(userobj, "active");
    perms = json_object_object_get(userobj, "permissions");

    user->id = json_object_get_int(id);
    sstrncpy(user->first_name, json_object_get_string(first_name), 25);
    sstrncpy(user->last_name, json_object_get_string(last_name), 25);
    sstrncpy(user->username, json_object_get_string(username), 25);
    sstrncpy(user->email, json_object_get_string(email), 50);
    sstrncpy(user->created_at, json_object_get_string(created_at), 30);
    user->is_superuser = json_object_get_boolean(is_superuser);
    user->active = json_object_get_boolean(active);
    user->nperms = json_object_array_length(perms);

    size_t i;
    for (i = 0; i < json_object_array_length(perms); i++) {
        json_object *permObj = json_object_array_get_idx(perms, i);
        Permission perm;
        json_object *id, *user_id, *code, *name;

        id = json_object_object_get(permObj, "id");
        user_id = json_object_object_get(permObj, "user_id");
        code = json_object_object_get(permObj, "code");
        name = json_object_object_get(permObj, "name");

        perm.id = json_object_get_int(id);
        perm.code = json_object_get_int(code);
        perm.user_id = json_object_get_int(user_id);
        sstrncpy(perm.name, json_object_get_string(name), 30);

        user->permissions[i] = perm;
    }
}

void json_to_login_response(char *json, LoginResponse *loginRes) {
    json_object *jobj = json_tokener_parse(json);
    json_object *userobj = json_object_object_get(jobj, "user");
    json_object *token = json_object_object_get(jobj, "token");

    sstrncpy(loginRes->token, json_object_get_string(token),
             ACTUAL_TOKEN_LENGTH);

    user_fromjson(userobj, &loginRes->user);
    json_object_put(jobj);
}

void absurl(char *dest, char *pathname) {
    strncat(dest, BASE_URL, strlen(BASE_URL) + 1);
    strncat(dest, pathname, MAX_URL_SIZE - strlen(BASE_URL) + 1);
}

int write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    Response *mem = (Response *)userp;

    char *ptr = realloc(mem->buffer, mem->size + realsize + 1);

    if (ptr == NULL) {
        fprintf(stdout, "realloc() failed to allocate more memory\n");
        return 0;
    }

    // Copy response into the buffer.
    mem->buffer = ptr;
    memmove(&(mem->buffer[mem->size]), contents, realsize);

    // update size of http response
    mem->size += realsize;
    mem->buffer[mem->size] = 0;
    return realsize;
}

Request *new_request(CURL *curl, const char *url) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    Response *res = calloc(1, sizeof(Response));
    if (res == NULL) {
        fprintf(stderr, "%s\n",
                "unable to allocated enough memory for response");
        return NULL;
    }

    // printf("[request]: %s\n", url);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, res);

    Request *req = malloc(sizeof(Request));
    req->curl = curl;
    req->headers = NULL;
    req->res = res;
    return req;
}

void free_request(Request *request) {
    free(request->res->buffer);
    free(request->res);
    request->res = NULL;
    curl_slist_free_all(request->headers);
    curl_easy_cleanup(request->curl);
    free(request);
    request = NULL;
}

bool perform_request(Request *req, char *method, char *data) {
    if (data != NULL) {
        curl_easy_setopt(req->curl, CURLOPT_POSTFIELDS, data);
    }

    if (strlen(AUTH_TOKEN) > 1) {
        char buf[AUTH_HEADER_LENGTH] = "";
        snprintf(buf, AUTH_HEADER_LENGTH, "Authorization: Bearer %s",
                 AUTH_TOKEN);
        req->headers = curl_slist_append(req->headers, buf);
    }

    curl_easy_setopt(req->curl, CURLOPT_HTTPHEADER, req->headers);
    curl_easy_setopt(req->curl, CURLOPT_CUSTOMREQUEST, method);

    int status;

    CURLcode curlCode = curl_easy_perform(req->curl);
    curl_easy_getinfo(req->curl, CURLINFO_RESPONSE_CODE, &status);
    req->res->status = status;

    if (curlCode != CURLE_OK) {
        sstrncpy(req->res->error, (char *)curl_easy_strerror(curlCode),
                 MAX_ERROR_SIZE);
        return false;
    }

    if (status < 200 || status >= 300) {
        sstrncpy(req->res->error, req->res->buffer, MAX_ERROR_SIZE);
        return false;
    }
    return true;
}

void to_login_payload(char *body, char *username, char *password) {
    json_object *json = json_object_new_object();
    json_object_object_add(json, "username", json_object_new_string(username));
    json_object_object_add(json, "password", json_object_new_string(password));
    sstrncpy(body, json_object_to_json_string(json), 255);
    json_object_put(json);
}

Headers *eclinic_settoken(Headers *headers, char *buf) {
    snprintf(buf, AUTH_HEADER_LENGTH, "Authorization: Bearer %s", AUTH_TOKEN);
    return curl_slist_append(headers, buf);
}

bool eclinic_login(LoginResponse *login, char *username, char *password) {
    CURL *curl = curl_easy_init();
    char body[255] = "";
    char url[MAX_URL_SIZE] = "";
    absurl(url, "/auth/login");

    Request *req = new_request(curl, url);
    to_login_payload(body, username, password);
    bool success = perform_request(req, "POST", body);

    if (success) {
        json_to_login_response(req->res->buffer, login);
    } else {
        fprintf(stderr, "%s\n", req->res->error);
    }

    free_request(req);
    return success;
}

bool getUser(User *user) {
    CURL *curl = curl_easy_init();
    char url[MAX_URL_SIZE] = "";
    absurl(url, "/users/auth/getuser");

    Request *req = new_request(curl, url);
    bool success = perform_request(req, "GET", NULL);

    if (success) {
        json_object *jobj = json_tokener_parse(req->res->buffer);
        user_fromjson(jobj, user);
        json_object_put(jobj);
    } else {
        fprintf(stderr, "%s\n", req->res->error);
    }

    free_request(req);
    return success;
}

int main(int argc, char const *argv[]) {
    FILE *fp;
    LoginResponse login;

    fp = fopen(LOGIN_FILE, "r+");
    if (fp == NULL) {
        fp = fopen(LOGIN_FILE, "w+");
        if (!fp) {
            perror("fopen");
            return EXIT_FAILURE;
        }
    }

    User user;
    int readBytes;

    readBytes = fread(&login.token, ACTUAL_TOKEN_LENGTH, sizeof(char), fp);
    int authenticated;

    if (readBytes > 0 && (strlen(login.token) > 0)) {
        sstrncpy(AUTH_TOKEN, login.token, TOKEN_LENGTH);
        authenticated = getUser(&user);
        if (!authenticated) {
            remove(LOGIN_FILE);
        }

    } else {
        char username[25], password[25];

        do {
            printf("Username: ");
        } while (scanf("%s", username) <= 0);

        fgetc(stdin);

        printf("Password: ");
        if (fgets(password, 25, stdin) == NULL) {
            return EXIT_FAILURE;
        };

        password[strlen(password) - 1] = 0;
        if (strlen(password) == 0) {
            fprintf(stdout, "Password can not be empty\n");
            return EXIT_FAILURE;
        }

        authenticated = eclinic_login(&login, username, password);
        if (authenticated) {
            user = login.user;
            sstrncpy(AUTH_TOKEN, login.token, TOKEN_LENGTH);
            fwrite(login.token, strlen(login.token) + 1, sizeof(char), fp);
        }
    }

    fclose(fp);

    if (system("clear") == 0)
        ;

    if (authenticated) {
        print_user(&user);
        print_user_permissions(user.permissions, user.nperms);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}