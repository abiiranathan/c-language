#include <stdbool.h>
#include <stdlib.h>

// Generic set implementation.
typedef struct Set {
    void** elements;
    size_t size;
    size_t capacity;
} Set;

// Creates a new heap-allocated set.
Set* set_create(size_t initialCapacity) {
    Set* set = malloc(sizeof(Set));
    set->elements = malloc(initialCapacity * sizeof(void*));
    set->size = 0;
    set->capacity = initialCapacity;
    return set;
}

// Free heap memory used by set and its elements.
void set_free(Set* set) {
    free(set->elements);
    free(set);
}

// Returns true if set contains element.
bool set_contains(Set* set, void* element) {
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return true;
        }
    }
    return false;
}

// Add element to the set. returns true if added successfully.
bool set_add(Set* set, void* element) {
    if (set_contains(set, element)) {
        return false;
    }

    if (set->size >= set->capacity) {
        set->capacity *= 2;
        set->elements = realloc(set->elements, set->capacity * sizeof(void*));
        if (set->elements == NULL) {
            return false;
        }
    }

    set->elements[set->size++] = element;  // NOLINT
    return true;
}

// Remove element from the set. Returns true if successful.
bool set_remove(Set* set, void* element) {
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            set->elements[i] = set->elements[--set->size];
            return true;
        }
    }
    return false;
}

// Returns number of elements in the set.
size_t set_size(Set* set) {
    return set->size;
}

// returns true if size is 0.
bool set_isempty(Set* set) {
    return set->size == 0;
}

// Clear the set.
void set_clear(Set* set) {
    for (size_t i = 0; i < set->size; i++) {
        set->elements[i] = NULL;
    }
    set->size = 0;
}

// Computes the union of two sets A and B, and returns a new set containing all elements in A and B.
Set* set_union(Set* setA, Set* setB) {
    Set* unionSet = set_create(setA->size + setB->size);
    for (size_t i = 0; i < setA->size; i++) {
        set_add(unionSet, setA->elements[i]);
    }
    for (size_t i = 0; i < setB->size; i++) {
        set_add(unionSet, setB->elements[i]);
    }
    return unionSet;
}

// Computes the intersection of two sets A and B, and returns a new set containing elements that are in both A and B.
Set* set_intersection(Set* setA, Set* setB) {
    Set* intersectionSet = set_create(setA->size < setB->size ? setA->size : setB->size);
    for (size_t i = 0; i < setA->size; i++) {
        if (set_contains(setB, setA->elements[i])) {
            set_add(intersectionSet, setA->elements[i]);
        }
    }
    return intersectionSet;
}

// Computes the difference of two sets A and B, and returns a new set containing elements that are in A but not in B.
Set* set_difference(Set* setA, Set* setB) {
    Set* differenceSet = set_create(setA->size);
    for (size_t i = 0; i < setA->size; i++) {
        if (!set_contains(setB, setA->elements[i])) {
            set_add(differenceSet, setA->elements[i]);
        }
    }
    return differenceSet;
}

// Computes the symmetric difference of two sets A and B, and returns a new set containing elements that are in A or B but not in both.
Set* set_symmetric_difference(Set* setA, Set* setB) {
    Set* symmetricDifferenceSet = set_create(setA->size + setB->size);
    for (size_t i = 0; i < setA->size; i++) {
        if (!set_contains(setB, setA->elements[i])) {
            set_add(symmetricDifferenceSet, setA->elements[i]);
        }
    }
    for (size_t i = 0; i < setB->size; i++) {
        if (!set_contains(setA, setB->elements[i])) {
            set_add(symmetricDifferenceSet, setB->elements[i]);
        }
    }
    return symmetricDifferenceSet;
}

// Determines if setA is a subset of setB, and returns true if all elements in setA are also in setB.
bool set_isSubset(Set* setA, Set* setB) {
    for (size_t i = 0; i < setA->size; i++) {
        if (!set_contains(setB, setA->elements[i])) {
            return false;
        }
    }
    return true;
}

// Determines if setA is a proper subset of setB, and returns true if all elements in setA are also in setB but setA and setB are not equal.
bool set_isProperSubset(Set* setA, Set* setB) {
    return set_isSubset(setA, setB) && setA->size < setB->size;
}

#include <stdio.h>

int main() {
    // Create two sets
    Set* setA = set_create(5);
    Set* setB = set_create(5);

    // Add some elements to setA and setB
    set_add(setA, "apple");
    set_add(setA, "banana");
    set_add(setA, "orange");

    set_add(setB, "banana");
    set_add(setB, "kiwi");

    // Print the elements of setA and setB
    printf("setA: ");
    for (size_t i = 0; i < setA->size; i++) {
        printf("%s ", (char*)setA->elements[i]);
    }
    printf("\n");

    printf("setB: ");
    for (size_t i = 0; i < setB->size; i++) {
        printf("%s ", (char*)setB->elements[i]);
    }
    printf("\n");

    // Compute the union of setA and setB
    Set* unionSet = set_union(setA, setB);
    printf("Union: ");
    for (size_t i = 0; i < unionSet->size; i++) {
        printf("%s ", (char*)unionSet->elements[i]);
    }
    printf("\n");

    // Compute the intersection of setA and setB
    Set* intersectionSet = set_intersection(setA, setB);
    printf("Intersection: ");
    for (size_t i = 0; i < intersectionSet->size; i++) {
        printf("%s ", (char*)intersectionSet->elements[i]);
    }
    printf("\n");

    // Compute the difference of setA and setB
    Set* differenceSet = set_difference(setA, setB);
    printf("Difference: ");
    for (size_t i = 0; i < differenceSet->size; i++) {
        printf("%s ", (char*)differenceSet->elements[i]);
    }
    printf("\n");

    // Compute the symmetric difference of setA and setB
    Set* symmetricDifferenceSet = set_symmetric_difference(setA, setB);
    printf("Symmetric Difference: ");
    for (size_t i = 0; i < symmetricDifferenceSet->size; i++) {
        printf("%s ", (char*)symmetricDifferenceSet->elements[i]);
    }
    printf("\n");

    // Determine if setA is a subset of setB
    bool isSubsetResult = set_isSubset(setA, setB);
    printf("Is setA a subset of setB? %s\n", isSubsetResult ? "true" : "false");

    // Determine if setA is a proper subset of setB
    bool isProperSubsetResult = set_isProperSubset(setA, setB);
    printf("Is setA a proper subset of setB? %s\n", isProperSubsetResult ? "true" : "false");

    // Clean up memory
    set_free(setA);
    set_free(setB);
    set_free(unionSet);
    set_free(intersectionSet);
    set_free(differenceSet);
    set_free(symmetricDifferenceSet);

    return 0;
}
