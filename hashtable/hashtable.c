#include <stdio.h>
#include "hashtable.h"

unsigned int hash(char *name)
{
  int length = strnlen(name, KEY_LENGTH);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++)
  {
    hash_value += name[i];
    hash_value = (hash_value * name[i]) % TABLE_SIZE;
  }
  return hash_value;
}

void hashtable_init()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hashtable[i] = NULL;
  }
}

void hashtable_print()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    if (hashtable[i] == NULL)
    {
      printf("\t%i\t---\n", i);
    }
    else
    {
      printf("\t%i\t", i);
      hashtable_node *tmp = hashtable[i];

      while (tmp != NULL)
      {
        printf("%s -", tmp->key);
        tmp = tmp->next;
      }

      printf("\n");
    }
  }
}

bool hashtable_insert(hashtable_node *p)
{
  if (p == NULL)
    return false;

  int index = hash(p->key);
  p->next = hashtable[index];
  hashtable[index] = p;
  return true;
}

hashtable_node *hashtable_lookup(char *key)
{
  int index = hash(key);
  hashtable_node *tmp = hashtable[index];

  while (tmp != NULL)
  {
    if (strncmp(tmp->key, key, KEY_LENGTH) == 0)
    {
      return tmp;
    }
    tmp = tmp->next;
  }

  return NULL;
}

hashtable_node *hashtable_delete(char *key)
{
  int index = hash(key);
  hashtable_node *tmp = hashtable[index];
  hashtable_node *prev = NULL;

  while (tmp != NULL && strncmp(tmp->key, key, KEY_LENGTH) != 0)
  {
    prev = tmp;
    tmp = tmp->next;
  }

  if (tmp == NULL)
  {
    return NULL;
  }

  if (prev == NULL)
  {
    hashtable[index] = tmp->next;
  }
  else
  {
    prev->next = tmp->next;
  }

  return tmp;
}

// Hashtable implementation with external chaining.

int main()
{

  hashtable_init();
  hashtable_print();

  hashtable_node *p1 = (hashtable_node *)malloc(sizeof(hashtable_node));
  strncpy(p1->key, "John", KEY_LENGTH);
  p1->data = "John Doe";
  hashtable_insert(p1);

  hashtable_node *p2 = (hashtable_node *)malloc(sizeof(hashtable_node));
  strncpy(p2->key, "Jane", KEY_LENGTH);
  p2->data = "Jane Doe";
  hashtable_insert(p2);

  hashtable_node *p3 = (hashtable_node *)malloc(sizeof(hashtable_node));
  strncpy(p3->key, "Ben", KEY_LENGTH);
  p3->data = "Sunna Ben";
  hashtable_insert(p3);

  hashtable_print();

  hashtable_node *p4 = hashtable_lookup("John");
  printf("%s\n", (char *)p4->data);

  hashtable_node *p5 = hashtable_delete("John");
  printf("%s\n", (char *)p5->data);

  hashtable_print();

  // Store integers from 0 to 9 in the hash table.
  for (int i = 0; i < 10; i++)
  {
    hashtable_node *p = (hashtable_node *)malloc(sizeof(hashtable_node));
    sprintf(p->key, "%d", i);
    p->data = (void *)&i;
    hashtable_insert(p);

    // retrieve the integer from the hash table.
    hashtable_node *tmp = hashtable_lookup(p->key);
    printf("%d\n", *(int *)tmp->data);
  }

  hashtable_print();

  return 0;
}
