#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_replace(char *source, size_t source_size, char *substring,
                     char *with) {
    // get pointer of substring in source
    char *substr_source = strstr(source, substring);
    if (substr_source == NULL) {
        return NULL;
    }

    if (source_size < strlen(source) + (strlen(with) - strlen(substring)) + 1) {
        printf("Buffer size is too small\n");
        return NULL;
    }

    memmove(substr_source + strlen(with), substr_source + strlen(substring),
            strlen(substr_source) - strlen(substring) + 1);

    memcpy(substr_source, with, strlen(with));
    return substr_source + strlen(with);
}

int main(int argc, char const *argv[]) {
    char str[100] = "The apples are delicious. apples, apples wow!";

    printf("%s\n", str);

    // replace all occurences
    while (string_replace(str, 100, "apples", "hamburgers"))
        ;

    printf("%s\n", str);
    return 0;
}