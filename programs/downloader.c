#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int download(char *url, char *fn) {
    CURL *curl = NULL;
    FILE *fp;

    fp = fopen(fn, "wb");
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(result));
        return EXIT_FAILURE;
    }

    fclose(fp);
    curl_easy_cleanup(curl);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <url> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return download(argv[1], argv[2]);
}