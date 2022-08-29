#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// %[^,]: Read all characters except ,

// tuple formats
// const char *PERSON_FORMAT_IN = "(%[^,], %d, %c)\n";
// const char *PERSON_FORMAT_OUT = "(%s, %d, %c)\n";

// JSON formats
const char *PERSON_FORMAT_IN =
    "{\"name\":\"%[^\"]\", \"age\":%d, \"gender\":\"%c\"}\n";
const char *PERSON_FORMAT_OUT =
    "{\"name\":\"%s\", \"age\":%d, \"gender\":\"%c\"}\n";

typedef struct Person {
    char name[20];
    int age;
    char gender;
} Person;

void printPerson(Person p) {
    printf(PERSON_FORMAT_OUT, p.name, p.age, p.gender);
}

int main(int argc, char const *argv[]) {
    Person p1 = {.name = "Andrew", .age = 22, .gender = 'M'};
    Person p2;  // memory allocated on the stack

    FILE *file;

    file = fopen("people.dat", "w+");  // preview: hexdump -C point.bin
    if (file == NULL) {
        return 1;
    }

    // Write point p1 to the file
    fprintf(file, PERSON_FORMAT_OUT, p1.name, p1.age, p1.gender);

    // ---  READ ------
    fseek(file, 0, SEEK_SET);
    fscanf(file, PERSON_FORMAT_IN, p2.name, &p2.age, &p2.gender);
    fclose(file);

    printPerson(p2);
    return 0;
}
