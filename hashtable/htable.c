#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"

unsigned int hash(char *name)
{
  int length = strnlen(name, MAX_NAME);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++)
  {
    hash_value += name[i];
    hash_value = (hash_value * name[i]) % TABLE_SIZE;
  }
  return hash_value;
}

void htable_init()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hash_table[i] = NULL;
  }
}

void htable_print()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    if (hash_table[i] == NULL)
    {
      printf("\t%i\t---\n", i);
    }
    else
    {
      printf("\t%i\t", i);
      person *tmp = hash_table[i];

      while (tmp != NULL)
      {
        printf("%s -", tmp->name);
        tmp = tmp->next;
      }

      printf("\n");
    }
  }
}

bool hash_table_insert(person *p)
{
  if (p == NULL)
    return false;

  int index = hash(p->name);
  p->next = hash_table[index];
  hash_table[index] = p;
  return true;
}

person *hash_table_lookup(char *name)
{
  int index = hash(name);
  // Get a temporary pointer to the head of the linked list
  person *tmp = hash_table[index];
  while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0)
  {
    tmp = tmp->next;
  }

  return tmp;
}

person *hash_table_delete(char *name)
{
  int index = hash(name);

  // Get a temporary pointer to the head of the linked list
  person *tmp = hash_table[index];
  person *prev = NULL;

  while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0)
  {
    prev = tmp;
    tmp = tmp->next;
  }

  // No match found
  if (tmp == NULL)
    return NULL;

  if (prev == NULL)
    // Delete the head of the list
    hash_table[index] = tmp->next;
  else
    // No somewhere in the middle or end of the list
    prev->next = tmp->next;

  return tmp;
}

int main(void)
{
  htable_init();
  htable_print();

  person jacob = {.name = "Jacob", .age = 256};
  person kate = {.name = "Kate", .age = 27};
  person mpho = {.name = "Mpho", .age = 14};
  person jane = {.name = "Jane", .age = 23};
  person jacob2 = {.name = "Jacob2", .age = 256};
  person kate2 = {.name = "Kate2", .age = 27};
  person mpho2 = {.name = "Mpho2", .age = 14};
  person george = {.name = "George", .age = 23};

  hash_table_insert(&jacob);
  hash_table_insert(&kate);
  hash_table_insert(&mpho);
  hash_table_insert(&jane);
  hash_table_insert(&jacob2);
  hash_table_insert(&kate2);
  hash_table_insert(&mpho2);
  hash_table_insert(&george);

  htable_print();

  person *tmp = hash_table_lookup("Mpho");
  if (tmp == NULL)
  {
    printf("Not found\n");
  }
  else
  {
    printf("Found: %s\n", tmp->name);
  }
  hash_table_delete("Mpho");
  htable_print();
}
