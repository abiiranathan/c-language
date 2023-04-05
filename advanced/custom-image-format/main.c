#include <png.h>  // part of libpng-dev
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t magic_number;  // 2 bytes
    uint16_t width;         // 2 bytes
    uint16_t height;        // 2 bytes
    uint8_t color_depth;    // 1 byte
} ImageHeader;

typedef struct
{
    uint8_t red;    // 1 byte
    uint8_t green;  // 1 byte
    uint8_t blue;   // 1 byte
} Pixel;

#pragma pack(pop)

void write_image(const char *filename, const uint16_t width,
                 const uint16_t height, uint16_t const color_depth, const Pixel *pixels) {
    ImageHeader header = {
        .magic_number = 0xDEAD,
        .width = width,
        .height = height,
        .color_depth = color_depth,
    };

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file %s for writing\n", filename);
        perror("fopen");
        return;
    }

    // Write header to the file
    size_t written = 0;
    if (written = (fwrite(&header, sizeof(header), 1, fp)) != 1) {
        fprintf(stderr, "Error: could write image header to the file");
        perror("fwrite");
        fclose(fp);
        return;
    };

    // Write pixel data to the file.
    for (int i = 0; i < width * height; i++) {
        size_t written = 0;
        written = fwrite(&pixels[i], sizeof(Pixel), 1, fp);
        if (written != 1) {
            fprintf(stderr, "Error: could write image pixel(index: %d) to the file", i);
            perror("fwrite");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

Pixel *read_image(const char *filename, uint16_t *width, uint16_t *height, uint8_t *color_depth) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error: could not open file %s for reading\n", filename);
        perror("fopen");
        return NULL;
    }

    // Read the header from the file
    ImageHeader header = {0};
    size_t n = fread(&header, sizeof(header), 1, fp);
    if (n != 1) {
        fprintf(stderr, "Error reading header from image\n");
        fclose(fp);
        return NULL;
    }

    if (header.magic_number != 0xDEAD) {
        fprintf(stderr, "Invalid file format\n");
        fclose(fp);
        return NULL;
    }

    // Set output parameters
    *width = header.width;
    *height = header.height;
    *color_depth = header.color_depth;

    // Allocate memory for the pixel data
    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * header.width * header.height);
    if (!pixels) {
        fprintf(stderr, "Error: unable to allocate memory for pixel data");
        fclose(fp);
        return NULL;
    }

    // Read pixel data from file
    for (int i = 0; i < header.width * header.height; i++) {
        size_t n = fread(&pixels[i], sizeof(Pixel), 1, fp);
        if (n != 1) {
            fprintf(stderr, "Error reading pixels from file");
            fclose(fp);
            return NULL;
        }
    }

    fclose(fp);
    return pixels;
}

void write_png(const char *filename, const uint16_t width, const uint16_t height, Pixel *pixels) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "error opening file %s for writing", filename);
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    png_bytep row_pointers[height];
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_bytep)&pixels[y * width];
    }

    png_set_rows(png_ptr, info_ptr, row_pointers);

    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

void print_pixels(const Pixel *pixels, const uint16_t width, const uint16_t height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("(%d, %d, %d)",
                   pixels[y * width + x].red,
                   pixels[y * width + x].green,
                   pixels[y * width + x].blue);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    // Generate test image data
    const uint16_t width = 256, height = 256;
    const uint8_t color_space = 24;
    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * width * height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y * width + x].red = x * 16;
            pixels[y * width + x].green = y * 16;
            pixels[y * width + x].blue = (x + y) * 8;
        }
    }

    // Write image to file
    write_image("test.img", width, height, color_space, pixels);

    // Read test.img from file.
    uint16_t read_width, read_height;
    uint8_t read_color_depth;

    Pixel *read_pixels = read_image("test.img", &read_width, &read_height, &read_color_depth);
    if (pixels != NULL) {
        printf("Image width: %d\n", read_width);
        printf("Image height: %d\n", read_height);
        printf("Image color depth: %d\n", read_color_depth);
        printf("Image pixel data: \n");
        print_pixels(read_pixels, read_width, read_height);
        free(read_pixels);
    }

    // Convert custom image format to PNG and write it to disk.
    write_png("test.png", width, height, pixels);
    free(pixels);
    return 0;
}
