#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allow user to customize map size
#ifndef MAP_SIZE
#define MAP_SIZE 1000
#endif

typedef struct node {
    void* key;
    void* value;
    struct node* next;
} node;

typedef struct {
    node* buckets[MAP_SIZE];
    unsigned long (*hash)(void*);
} map;

unsigned long default_hash(void* key) {
    // Default hash function
    return (unsigned long)key % MAP_SIZE;
}

void map_set(map* m, void* key, void* value) {
    unsigned long index = m->hash(key);
    node* head = m->buckets[index];
    while (head != NULL) {
        if (head->key == key) {
            head->value = value;
            return;
        }
        // Seperate chaining
        head = head->next;
    }

    node* new_node = malloc(sizeof(node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = m->buckets[index];
    m->buckets[index] = new_node;
}

void* map_get(map* m, void* key) {
    unsigned long index = m->hash(key);
    node* head = m->buckets[index];
    while (head != NULL) {
        if (head->key == key) {
            return head->value;
        }
        head = head->next;
    }
    return NULL;
}

void map_remove(map* m, void* key) {
    unsigned long index = m->hash(key);
    node* head = m->buckets[index];
    node* prev = NULL;
    while (head != NULL) {
        if (head->key == key) {
            if (prev == NULL) {
                m->buckets[index] = head->next;
            } else {
                prev->next = head->next;
            }
            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }
}

void map_set_hash(map* m, unsigned long (*hash)(void*)) {
    m->hash = hash;
}

int main() {
    map m = {0};
    map_set_hash(&m, default_hash);

    int key1 = 1;
    int val1 = 10;
    map_set(&m, &key1, &val1);
    int* result1 = (int*)map_get(&m, &key1);
    printf("result1: %d\n", *result1);

    char key2[] = "key2";
    char* val2 = "value2";
    map_set(&m, key2, val2);

    char* result2 = (char*)map_get(&m, key2);
    printf("result2: %s\n", result2);

    map_remove(&m, &key1);
    int* result3 = (int*)map_get(&m, &key1);
    printf("result3: %p\n", result3);
    return 0;
}
