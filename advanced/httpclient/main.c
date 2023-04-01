#include "../defer/defer.h"
#include "chttp.h"

int main() {
    Deferral;

    char headers[][MAX_HEADER_SIZE] = {"Content-Type: text/html"};
    request_set_global_headers(headers, ARRAY_SIZE(headers));

    struct curl_slist *h = append_authtoken_header("xxx.xxxxx.zzz", NULL);
    Response res;
    Request *req;
    req = request_new("http://localhost:8000/sample.txt");
    if (req == NULL) {
        fprintf(stderr, "unable to create request");
        return 1;
    }

    // defer freeing request memory
    Defer({
        request_free(req);
        request_global_cleanup();
    });

    request_set_headers(req, h);

    client_get(req);
    request_get_response(req, &res);

    if (res.error) {
        printf("error: %s\n", res.error);
        Return 1;
    }

    printf("%s\n", res.body);
    Return 0;
}
