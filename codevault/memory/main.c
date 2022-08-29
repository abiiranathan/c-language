#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int arr1[] = {1, 2};
    int arr2[] = {3, 4};  // 0003 0004

    // memcmp -> memory compare
    if (memcmp(arr1, arr2, 2 * sizeof(int)) == 0) {
        printf("Arrays are the same\n");
    } else {
        printf("Arrays are not the same\n");
    };

    // memcpy -> Memory copy (dest, src, no_bytes)
    memcpy(arr1, arr2, 2 * sizeof(int));
    printf("%d, %d\n", arr1[0], arr1[1]);

    // memset -> Set every single byte in array to some value
    memset(arr1, 0, 2 * sizeof(int));

    // memchr -> find a single byte inside a place in memory
    // returns a pointer to where the byte was found or NULL.
    if (memchr(arr1, 0, 2 * sizeof(int)) != NULL) {
        printf("Found the byte\n");
    }

    // memcpy vs memmove
    char str[] = "Start Stop";
    memcpy(str, str + 6, 4 * sizeof(char));
    printf("%s\n", str);  // Stopt Stop

    // memmove -> safe with overlapping places in memory
    // first copies src into a temporary buffer
    char str2[] = "Start Stop";
    memmove(str2, str2 + 2, 3 * sizeof(char));
    printf("%s\n", str2);  // artrt Stop
    return 0;
}