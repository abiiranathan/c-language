#ifndef VEC
#define VEC
#include <stddef.h>
#include <stdlib.h>

/** Vec opaque data type.
 *
 * It's implementation is somewhere else.
 * */
typedef struct Vec Vec;

/**
 * Construct a new Vec value. Owner is responsible for
 * calling vec_free when its life time expires.
 *
 * @param capacity - initial number of items it can store
 * @param size - size sizeof an individual item e.g sizeof(int)
 * @return initialized Vec value.
 *
 */
Vec *vec_new(size_t capacity, size_t size);

/**
 * Free a vector
 * Owner must call to expire a Vec value's life-time.
 *
 */
void vec_free(Vec *self);

/**
 * Add an element to the end of the vector
 */
void vec_push(Vec *self, void *element);

/* Delete the element at the given index */
void vec_delete(Vec *self, size_t index);

/* Get the element at the given index */
void *vec_get(const Vec *self, size_t index);

/* Set the element at the given index */
void vec_set(Vec *self, size_t index, const void *element);

/**
 * Returns the number of items in the Vec.
 */
size_t vec_length(const Vec *self);

/**
 * Returns the amount of heap memory consumed by the items in Vec.
 */
size_t vec_memory(const Vec *self);

int sort_int_asc(const void *a, const void *b);
int sort_int_desc(const void *a, const void *b);
int sort_str_asc(const void *a, const void *b);
int sort_str_desc(const void *a, const void *b);

/**
 *  Sort Vec elements in ascending order.
 *  Uses qsort from stdlib.h
 *  @param compare_func - The function that compares 2 elements
 */
void vec_sort(Vec *self, const __compar_fn_t compare_func);

// Delete all items in Vec
void vec_clear(Vec *self);

#endif /* VEC */
