#include <stdio.h>

int main(int argc, char const *argv[]) {
    // getch -> Windows-only (conio.h)
    // fgetc vs getc, getchar()=getc(stdin)

    int c = fgetc(stdin);
    printf("Printed char: %c\n", c);
    return 0;
}
