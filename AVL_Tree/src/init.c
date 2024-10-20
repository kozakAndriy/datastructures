#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

AVL_Tree* initTree() {
    AVL_Tree* tree = malloc(sizeof(AVL_Tree));
    tree->height = 0;
    tree->size = 0;
    tree->root = NULL;

    return tree;
}

Node* node(int val, Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->left = left;
    node->right = right;
    return balance(node);
}