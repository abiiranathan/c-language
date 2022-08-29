#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char str1[] = "abcd4";
    char str2[] = "abcd1";

    // string compare
    // return 1, -1 or 0
    if (strcmp(str1, str2) == 0) {
        printf("The strings are similar\n");
    };

    // Compare N(bytes) characters of S1 and S2.
    if (strncmp(str1, str2, 4) == 0) {
        printf("The strings are similar\n");
    };

    return 0;
}