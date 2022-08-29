#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char arr[3][100] = {"apple", "orange", "programmer"};

    char input[100];

    printf("Input a word: ");
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;

    // Find input in our array
    int i;

    for (i = 0; i < 3; i++) {
        // ignore case by lowercasing input
        // toLower() in ctype.h

        if (strcmp(arr[i], input) == 0) {
            printf("Found input string at index %d\n", i);
            break;
        }
    }

    if (i >= 3) printf("The input string was not found\n");

    // Find a word in a string
    char str[] = "Apples are good for your health";
    char to_find[] = "good";

    if (strstr(str, to_find)) {
        printf("The word has been found\n");
    }

    return 0;
}