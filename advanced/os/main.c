#define OS_SUPPORT_LOCKING

#include "os.h"
#include "string.h"

// compile with SUPPORT_LOCKING flag
// gcc -DOS_SUPPORT_LOCKING main.c os.c
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    File* file = file_open(argv[1], "r");
    if (!file) {
        return 1;
    }

    ssize_t size = file_size(file);
    char buf[size + 1];
    memset(buf, 0, size + 1);

    if (file_read(file, buf, sizeof(buf)) == 0) {
        printf("%s\n", buf);
    }

    struct stat stats;
    if (file_get_stats(file, &stats) != 0) {
        return 1;
    }
    printf("File size: %lld bytes\n", (long long)stats.st_size);

    // Perform file operations
    File* copy = file_open("sample.txt", "w");
    if (!copy) {
        file_free(file);
        return 1;
    }

    file_copy(file, copy);
    char* data = "Hello from Uganda\n";
    int status = file_write(copy, data, strlen(data));
    printf("write_file: status: %d\n", status);

    if (file_move(copy, "/tmp/clanguage") != 0) {
        return 1;
    }

    if (file_truncate(copy, 0) != 0) {
        return 1;
    }

    file_free(copy);
    file_free(file);

    // Test file locking
    file = file_open("example.txt", "w+");

    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    // Lock the file before making changes
    if (file_lock(file, 0, 0) == -1) {
        printf("Error locking file\n");
        file_free(file);
        return 1;
    }

    // Write some data to the file
    char* data2 = "Hello, world!";
    if (file_write(file, data2, strlen(data2)) == -1) {
        printf("Error writing to file\n");
        file_unlock(file, 0, 0);
        file_free(file);
        return 1;
    }

    // Unlock the file after making changes
    if (file_unlock(file, 0, 0) == -1) {
        printf("Error unlocking file\n");
        file_free(file);
        return 1;
    }

    // Free the file pointer
    file_free(file);
    return 0;
}
