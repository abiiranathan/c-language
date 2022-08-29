// Hashtable implementation with external chaining.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define KEY_LENGTH 255

/** A node in the linked list. */
typedef struct hashtable_node
{
  char key[KEY_LENGTH];        // The key of the node.
  void *data;                  // void pointer to any data type
  struct hashtable_node *next; // Pointer to the next node in the chain.
} hashtable_node;

/** A hash table. */
hashtable_node *hashtable[TABLE_SIZE];

/** Hash function for the hashtable */
unsigned int hash(char *name);

/** Initialize the hashtable */
void hashtable_init();

/** Print the hashtable */
void hashtable_print();

/** Insert a node into the hashtable */
bool hashtable_insert(hashtable_node *p);

/** Lookup a node in the hashtable by key*/
hashtable_node *hashtable_lookup(char *key);

/** Delete a node from the hashtable by key */
hashtable_node *hashtable_delete(char *key);

#endif /* HASHTABLE_H */
