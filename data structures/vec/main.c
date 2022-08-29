#include <stdio.h>

#include "vec.h"

void print_vec_int(Vec *vec);
void print_vec_str(Vec *vec);

int main() {
    Vec *vec;
    vec = vec_new(10, sizeof(int));
    for (int i = 1; i < 10; i++) {
        vec_push(vec, &i);
    }

    vec_sort(vec, sort_int_asc);
    print_vec_int(vec);
    int target = 5;

    for (int j; j < vec_length(vec); j++) {
        int val = *(int *)vec_get(vec, j);
        if (val == target) {
            printf("Element found: %d, index: %d\n", val, j);
        }
    }

    vec_free(vec);
    const size_t MAX_NAME_LEN = 25;
    Vec *vec2 = vec_new(5, sizeof(char) * MAX_NAME_LEN);
    vec_set(vec2, 0, "Abiira Nathan");
    vec_set(vec2, 1, "Kwikiriza Dan");
    vec_set(vec2, 2,
            "Akatukunda Precious Kyarugahi");  // will get truncated at 25 chars
    vec_set(vec2, 3, "Abaho Ferguson");
    vec_set(vec2, 4, "Muhanguzi Nelly");
    vec_push(vec2, "Owoyiine Joseph");
    vec_sort(vec2, sort_str_desc);
    vec_delete(vec2, 2);
    print_vec_str(vec2);
    printf("Len: %ld, Size: %ld\n", vec_length(vec2), vec_memory(vec2));
    vec_free(vec2);

    // Vector of structs
    typedef struct Person {
        char *name;
        int age;
    } Person;

    Person abiira, dan;
    abiira.name = "Abiira Nathan";
    abiira.age = 33;
    dan.name = "Kwikiriza Dan";
    dan.age = 45;

    Vec *vec3 = vec_new(5, sizeof(Person));
    vec_push(vec3, &abiira);
    vec_push(vec3, &dan);

    for (int i = 0; i < vec_length(vec3); i++) {
        Person *p = (Person *)vec_get(vec3, i);
        printf("%s is %d years old.\n", p->name, p->age);
    }
}

void print_vec_int(Vec *vec) {
    for (int i = 0; i < vec_length(vec); i++) {
        printf("%d\n", *(int *)vec_get(vec, i));
    }
}

void print_vec_str(Vec *vec) {
    for (int i = 0; i < vec_length(vec); i++) {
        printf("%s\n", (char *)vec_get(vec, i));
    }
}
