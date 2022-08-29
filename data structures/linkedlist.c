#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *create_node(int data) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_node(node **head, int data) {
    node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

void insert_node_at(node **head, int data, int position) {
    node *new_node = create_node(data);
    node *temp = *head;
    int i = 0;
    while (i < position - 1) {
        temp = temp->next;
        i++;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

void insert_last(node **head, int data) {
    node *new_node = create_node(data);
    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void insert_first(node **head, int data) {
    node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

void print_list(node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int get_node(node *head, int position) {
    int i = 0;
    while (i < position) {
        head = head->next;
        i++;
    }
    return head->data;
}

int get_last(node *head) {
    while (head->next != NULL) {
        head = head->next;
    }
    return head->data;
}

int node_exists(node *head, int data) {
    while (head != NULL) {
        if (head->data == data) return 1;
        head = head->next;
    }
    return 0;
}

void delete_node(node **head, int data) {
    node *temp = *head;
    node *prev = NULL;

    while (temp != NULL) {
        if (temp->data == data) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

int main(void) {
    node *head = NULL;
    insert_node(&head, 1);
    insert_node(&head, 2);
    insert_node(&head, 3);
    insert_node(&head, 4);
    insert_node(&head, 5);
    print_list(head);
    delete_node(&head, 3);

    print_list(head);

    insert_node_at(&head, 6, 2);
    print_list(head);

    insert_last(&head, 7);
    print_list(head);

    insert_first(&head, 8);
    print_list(head);

    printf("%d\n", get_node(head, 3));
    printf("%d\n", get_last(head));
    printf("%d\n", node_exists(head, 10));
    return 0;
}
