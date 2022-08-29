// doublylinkedlist.c

// Language: c
// Path: doublylinkedlist.c
// Compare this snippet from linkedlist.c:

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *next;
  struct node *prev;
} node;

node *create_node(int data)
{
  node *new_node = (node *)malloc(sizeof(node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;
  return new_node;
}

void insert_node(node **head, int data)
{
  node *new_node = create_node(data);
  new_node->next = *head;
  *head = new_node;
}

void insert_node_at(node **head, int data, int position)
{
  node *new_node = create_node(data);
  node *temp = *head;
  int i = 0;
  while (i < position - 1)
  {
    temp = temp->next;
    i++;
  }
  new_node->next = temp->next;
  new_node->prev = temp;
  temp->next = new_node;
}

void insert_last(node **head, int data)
{
  node *new_node = create_node(data);
  node *temp = *head;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = new_node;
  new_node->prev = temp;
}

void insert_first(node **head, int data)
{
  node *new_node = create_node(data);
  new_node->next = *head;
  *head = new_node;
}

void print_list(node *head)
{
  while (head != NULL)
  {
    printf("%d ", head->data);
    head = head->next;
  }
}

int get_node(node *head, int position)
{
  int i = 0;
  while (i < position)
  {
    head = head->next;
    i++;
  }
  return head->data;
}

void delete_node_at(node **head, int position)
{
  node *temp = *head;
  int i = 0;
  while (i < position - 1)
  {
    temp = temp->next;
    i++;
  }
  temp->next = temp->next->next;
}

void delete_node(node **head, int data)
{
  node *temp = *head;
  node *prev = NULL;
  while (temp != NULL)
  {
    if (temp->data == data)
    {
      if (prev == NULL)
      {
        *head = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }
      free(temp);
      return;
    }
    prev = temp;
    temp = temp->next;
  }
}

int main(void)
{
  node *head = NULL;
  insert_node(&head, 1);
  insert_node(&head, 2);
  insert_node(&head, 3);
  insert_node(&head, 4);
  insert_node(&head, 5);
  insert_node(&head, 6);
  insert_node(&head, 7);
  insert_node(&head, 8);
  insert_node(&head, 9);
  insert_node(&head, 10);
  insert_node(&head, 11);
  insert_node(&head, 12);
  insert_node(&head, 13);
  insert_node(&head, 14);
  insert_node(&head, 15);
  insert_node(&head, 16);
  insert_node(&head, 17);
  insert_node(&head, 18);
  insert_node(&head, 19);
  insert_node(&head, 20);
  insert_node(&head, 21);
  insert_node(&head, 22);
  insert_node(&head, 23);
  insert_node(&head, 24);
  insert_node(&head, 25);
  insert_node(&head, 26);
  insert_node(&head, 27);
  insert_node(&head, 28);
  insert_node(&head, 29);
  insert_node(&head, 30);
  insert_node(&head, 31);
  insert_node(&head, 32);
  insert_node(&head, 33);
  insert_node(&head, 34);
  insert_node(&head, 35);
  insert_node(&head, 36);
  insert_node(&head, 37);
  insert_node(&head, 38);
  insert_node(&head, 39);
  insert_node(&head, 40);
  insert_node(&head, 41);
  insert_node(&head, 42);
  insert_node(&head, 43);
  insert_node(&head, 44);
  insert_node(&head, 45);
  insert_node(&head, 46);
  insert_node(&head, 47);
  insert_node(&head, 48);
  insert_node(&head, 49);

  print_list(head);

  printf("\n");

  printf("%d\n", get_node(head, 3));

  printf("\n");

  insert_node_at(&head, 100, 3);
  printf("%d\n", get_node(head, 3));

  // delete
  delete_node_at(&head, 3);
  printf("%d\n", get_node(head, 3));

  return 0;
}