// Minimal version of grep.
// Usage: getopt [options] [file ...]
// Options:
// -f, --file: file to read
// -q --query: query to search
// -p --pattern: pattern to search using regex

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int c;
    int option_index = 0;
    char *query = NULL;
    char *file = NULL;
    int use_regex = 0;

    static struct option long_options[] = {
        {"query", required_argument, 0, 'q'},
        {"file", required_argument, 0, 'f'},
        {"pattern", optional_argument, 0, 'p'},
        {0, 0, 0, 0}};

    while ((c = getopt_long(argc, argv, "q:f:p::", long_options,
                            &option_index)) != -1) {
        switch (c) {
            case 'q':
                query = optarg;
                break;
            case 'f':
                file = optarg;
                break;
            case 'p':
                use_regex = 1;
                break;
            case '?':
                printf("unknown option: %c\n", c);
                break;
            case ':':
                printf("missing argument for option: %s\n", optarg);
                break;
            default:
                printf("unknown error\n");
                break;
        }
    }

    if (query == NULL || file == NULL) {
        printf("missing argument for -f or -q\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char line[1024];
    int line_num = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_num++;

        if (strstr(line, query) != NULL) {
            printf("%d: %s", line_num, line);
        }
    }

    fclose(fp);
    return EXIT_SUCCESS;
}