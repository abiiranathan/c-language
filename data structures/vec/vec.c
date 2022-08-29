#include "vec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implementation for the Vec opaque struct */
typedef struct Vec {
    size_t size;      // size of each element
    size_t capacity;  // size of allocated memory
    size_t length;    // number of elements in the vector
    void *buffer;     // pointer to the allocated heap memory storing the items
} Vec;

static void _ensure_capacity(Vec *self, size_t n);

// implements vec_new
Vec *vec_new(size_t capacity, size_t size) {
    Vec *vec = malloc(sizeof(Vec));
    vec->capacity = capacity;
    vec->size = size;
    vec->length = 0;
    vec->buffer = calloc(capacity, size);
    return vec;
}

// implements vec_free
void vec_free(Vec *vec) {
    // make sure vec is a valid pointer
    if (vec == NULL || vec->buffer == NULL) {
        return;
    }

    free(vec->buffer);
    vec->buffer = NULL;
    vec->length = 0;
    vec->capacity = 0;
    free(vec);
}

void vec_push(Vec *vec, void *data) { vec_set(vec, vec->length, data); }

void vec_delete(Vec *vec, size_t index) {
    // make sure there is data to delete and index is valid
    if (vec->length == 0 || index >= vec->length) return;

    // delete the element at index and maintain order
    void *data = vec->buffer + (index * vec->size);
    size_t new_mem = vec->size * (vec->length - index);
    memmove(data, data + vec->size, new_mem);

    // decrement length
    vec->length--;
}

void *vec_get(const Vec *vec, size_t index) {
    return vec->buffer + (index * vec->size);
}

void vec_set(Vec *vec, size_t index, const void *element) {
    _ensure_capacity(vec, index + 1);
    memcpy(vec_get(vec, index), element, vec->size);

    if (index >= vec->length) vec->length = index + 1;
}

size_t vec_length(const Vec *self) { return self->length; }

void vec_clear(Vec *self) {
    self->length = 0;
    free(self->buffer);
    self->buffer = NULL;
    self->buffer = calloc(self->capacity, self->size);
}

size_t vec_memory(const Vec *self) { return self->length * self->size; }

int sort_int_asc(const void *a, const void *b) {
    // Cast void pointers to int pointers & dereference them
    // sort ascending.
    return (*(int *)a) - (*(int *)b);
}

int sort_int_desc(const void *a, const void *b) {
    return (*(int *)b) - (*(int *)a);
}

int sort_str_asc(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int sort_str_desc(const void *a, const void *b) {
    return strcmp((const char *)b, (const char *)a);
}

void vec_sort(Vec *self, const __compar_fn_t compare_func) {
    qsort(self->buffer, self->length, self->size, compare_func);
}

/**
 * Resizes the Vec if n is greater than the Vec capacity.
 */
static void _ensure_capacity(Vec *self, size_t n) {
    if (n > self->capacity) {
        size_t new_cap = n * 2;
        self->buffer = realloc(self->buffer, new_cap * self->size);
        self->capacity = new_cap;
    }
}
