#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const **argv) {
    int id;
    char message[256];

    while (1) {
        printf("Input ID: ");
        scanf("%d", &id);  // leaves \n in input buffer
        fgetc(stdin);      // clears the stdin input buffer

        printf("Input message: ");
        fgets(message, 256, stdin);  // Terminates on \n or EOF
        // Remove \n from message
        message[strlen(message) - 1] = 0;

        printf("(%d) Sent message: %s\n", id, message);
    }

    return 0;
}
