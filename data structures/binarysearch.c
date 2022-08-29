// binarysearch.c

#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
} tree;

tree *create_tree(int data) {
    tree *t = (tree *)malloc(sizeof(tree));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void print_tree(tree *t) {
    if (t == NULL) {
        return;
    }
    printf("%d ", t->data);
    print_tree(t->left);
    print_tree(t->right);
}

int main() {
    tree *t = create_tree(1);
    t->left = create_tree(2);
    t->right = create_tree(3);
    t->left->left = create_tree(4);
    t->left->right = create_tree(5);
    t->right->left = create_tree(6);
    t->right->right = create_tree(7);
    print_tree(t);

    free(t->left);
    free(t->right);  // all nodes not freed here
    free(t);
    return 0;
}
