#include "vec.h"

typedef struct Person {
    char* name;
    int age;
    float salary;
} Person;

typedef char* string;

VEC_DEFINE(int)
VEC_DEFINE(float)
VEC_DEFINE(long)
VEC_DEFINE(string)
VEC_DEFINE(Person)

int compare_ints(const void* a, const void* b) {
    int* x = (int*)a;
    int* y = (int*)b;
    return *x - *y;
}

int comparator_charptr(const void* a, const void* b) {
#include <string.h>
    const char* const* pa = (const char* const*)a;
    const char* const* pb = (const char* const*)b;
    return strcmp(*pa, *pb);
}

int main() {
    // Test with int
    Vec_int* vi;
    vector_init_int(&vi);
    vector_push_back_int(vi, 1);
    vector_push_back_int(vi, 3);
    vector_push_back_int(vi, 2);
    vector_push_back_int(vi, 7);
    vector_push_back_int(vi, 4);

    vector_sort_int(vi, compare_ints);

    // Print the values in the vector
    for (int i = 0; i < vi->size; i++) {
        printf("%d\n", vi->data[i]);
    }

    // Free the memory used by the vector
    vector_free_int(&vi);

    // Test with float
    Vec_float* vf;
    vector_init_float(&vf);
    vector_push_back_float(vf, 3.14159f);
    vector_push_back_float(vf, 2.71828f);
    vf->data[2] = 45.8;

    // Print the values in the vector
    for (int i = 0; i < vf->size; i++) {
        printf("%f\n", vf->data[i]);
    }

    // Free the memory used by the vector
    vector_free_float(&vf);

    // Test with long
    Vec_long* vl;
    vector_init_long(&vl);
    vector_push_back_long(vl, 1234567890L);
    vector_push_back_long(vl, -9876543210L);

    // Print the values in the vector
    for (int i = 0; i < vl->size; i++) {
        printf("%ld\n", vl->data[i]);
    }

    // Free the memory used by the vector
    vector_free_long(&vl);

    // Test with Person
    Vec_Person* vp;
    vector_init_Person(&vp);

    Person p1 = {.name = "Abiira", .age = 30, .salary = 40};
    Person p2 = {.name = "Dan", .age = 25, .salary = 50};
    Person p3 = {.name = "Joseph", .age = 12, .salary = 80};
    Person p0 = {.name = "Atwiine", .age = 34, .salary = 800};

    vector_push_back_Person(vp, p1);
    vector_push_back_Person(vp, p2);
    vector_push_back_Person(vp, p3);
    vector_insert_Person(vp, 0, p0);

    Person p;
    if (vector_pop_back_Person(vp, &p)) {
        printf("Popped person: %s\n", p.name);
    };

    Person p_ret = {0};
    vector_get_Person(vp, 10, &p_ret);

    // Print the values in the vector
    for (int i = 0; i < vp->size; i++) {
        printf("Name: %s, Age: %d, Salary: %.2f\n",
               vp->data[i].name, vp->data[i].age, vp->data[i].salary);
    }

    printf("Got: %s\n", p_ret.name);

    vector_free_Person(&vp);

    // Test with string
    Vec_string* vs;
    vector_init_string(&vs);
    vector_push_back_string(vs, "Owoyine Jo");
    vector_push_back_string(vs, "Aine E");
    vector_push_back_string(vs, "Abiira Nathan");
    vector_push_back_string(vs, "Kakura Nahason");
    vector_sort_string(vs, comparator_charptr);

    for (int i = 0; i < vs->size; i++) {
        printf("%s\n", vs->data[i]);
    }

    vector_free_string(&vs);
    return 0;
}
