#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

void print_in_base(int num, int base) {
    char buffer[MAX_LENGTH];
    char *str = buffer + sizeof(buffer);

    *--str = '\0';

    do {
        int digit = num % base;
        if (digit < 10)
            *--str = digit + '0';
        else
            *--str = digit - 10 + 'A';
    } while ((num /= base) != 0);

    printf("%s", str);
}

int parse_int(char *str) {
    int base = 10;
    char *endptr;

    if (strlen(str) >= 2 && str[0] == '0') {
        if (str[1] == 'x' || str[1] == 'X') {
            base = 16;
            str += 2;
        } else if (str[1] == 'b' || str[1] == 'B') {
            base = 2;
            str += 2;
        } else {
            base = 8;
        }
    }

    return strtol(str, &endptr, base);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number> <base>\n", argv[0]);
        return 1;
    }

    int num = parse_int(argv[1]);
    int base = atoi(argv[2]);

    printf("Decimal: %d\n", num);
    printf("Binary: ");
    print_in_base(num, 2);
    printf("\n");
    printf("Octal: 0%o\n", num);
    printf("Hexadecimal: 0x%x\n", num);
    if (base != 2) {
        printf("Base %d: ", base);
        print_in_base(num, base);
        printf("\n");
    }
    return 0;
}
