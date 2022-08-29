// Hashtable implementation with external chaining.

#ifndef HTABLE_H
#define HTABLE_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define MAX_NAME 255

typedef struct person
{
  char name[MAX_NAME];
  int age;

  struct person *next;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name);
void htable_init();
void htable_print();
bool hash_table_insert(person *p);
person *hash_table_lookup(char *name);
person *hash_table_delete(char *name);

#endif /* HTABLE_H */
