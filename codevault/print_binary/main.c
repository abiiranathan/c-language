#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int a = 13;

    // Print x in binary
    long long i, j;

    for (i = 0; i < sizeof(int); i++) {
        // char byte = *((char *)&a + i);
        char byte = (((char *)&a)[i]);

        for (j = 8; j >= 0; j--) {
            // take the bit out of the byte
            // 1101 >> 1 => 110
            // 1101 & 1  => 0001
            char bit = (byte >> j) & 1;

            printf("%hhd", bit);
        }

        printf(" ");
    }

    return 0;
}