#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char str1[100] = "My name is ";
    char str2[] = "Nathan Abiira";

    // *strcat* is Unsafe: is insecure as it does not provide bounding of the
    //* memory buffer. Liable to buffer overflow. strcat(str1, str2);

    strncat(str1, str2, 100 - strlen(str1) - 1);
    printf("%s\n", str1);
    return 0;
}