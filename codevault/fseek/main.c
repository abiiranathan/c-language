#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    FILE *out;

    out = fopen("numbers.dat", "w");
    if (out == NULL) {
        return 1;
    }

    fprintf(out, "20");
    fseek(out, 0, SEEK_SET);   // rewinds the cursor to the beginning // 19
    fseek(out, 1, SEEK_CUR);   // add one space from current curpos. // 20 19
    fseek(out, -2, SEEK_END);  // add one space from current curpos. // 19
    fprintf(out, "19");

    return 0;
}