#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    unsigned int a = 5;
    printf("Left shifted by 1: %d\n", a << 1);
    printf("Left shifted by 2: %d\n", a << 2);
    printf("Left shifted by 3: %d\n", a << 3);

    // Left shift: x << n == x * 2^n
    // Right shift: x >> n == x / 2^n

    unsigned int b = 100000;
    printf("Left shifted by 1: %d\n", b << 1);
    printf("Left shifted by 2: %d\n", b << 2);
    printf("Left shifted by 3: %d\n", b << 3);

    // Storing flags in a single bit
    unsigned int flags = 1;

    if ((flags & 1) != 0) {
        printf("First feature is on\n");
    }

    if ((flags & 2) != 0) {
        printf("Second feature is on\n");
    }

    if ((flags & 3) != 0) {
        printf("Both features are on\n");
    }

    return 0;
}