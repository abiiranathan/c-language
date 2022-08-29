#include <stdio.h>
#include <uuid/uuid.h>

static const char *hex = "0123456789abcdef";

int main(int argc, char **argv) {
    // generate a new UUID v4
    uuid_t uuid;
    uuid_generate_random(uuid);
    char uuid_str[37];
    uuid_unparse(uuid, uuid_str);

    printf("%s\n", uuid_str);
}