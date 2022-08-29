#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Point {
    int x, y;
} Point;

void printPoint(Point p) { printf("Point(%d, %d)\n", p.x, p.y); }

int main(int argc, char const *argv[]) {
    Point p1 = {.x = 13, .y = -5};
    Point p2;

    FILE *in;
    FILE *out;

    out = fopen("point.bin", "wb");  // preview: hexdump -C point.bin
    if (out == NULL) {
        return 1;
    }

    // Write point p1 to the file
    size_t elements_written = fwrite(&p1, sizeof(Point), 1, out);
    fclose(out);

    if (elements_written == 0) {
        return 2;
    }

    // ---  READ ------
    in = fopen("point.bin", "rb");
    if (in == NULL) {
        return 3;
    }

    size_t elements_read = fread(&p2, sizeof(Point), 1, in);
    fclose(in);

    if (elements_read == 0) {
        return 4;
    }

    printPoint(p2);
    return 0;
}