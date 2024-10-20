#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isLeaf(Node* node) {
    if (node == NULL) {
        printf("Bad state. isLeaf(node) == NULL\n");
        return false;
    }
    return node->left == NULL && node->right == NULL;
}

DeleteResult* deleteResult(Node* returnNode, int deletedVal) {
    DeleteResult* result = malloc(sizeof(DeleteResult));
    result->returnNode = returnNode;
    result->deletedVal = deletedVal;
    return result;
}

void push(AVL_Tree* tree, Node* node) {
    if (tree->root == NULL) {
        tree->root = node;
        tree->size++;
        return;
    }
    tree->root = insert(tree, tree->root, node);
}

Node* insert(AVL_Tree* tree, Node* cur, Node* node) {
    if (cur->val > node->val) {
        if (cur->left == NULL) {
            tree->size++;
            cur->left = node;
        }
        else {
            cur->left = insert(tree, cur->left, node);
        }
    }
    else if (cur->val < node->val) {
        if (cur->right == NULL) {
            tree->size++;
            cur->right = node;
        }
        else {
            cur->right = insert(tree, cur->right, node);
        }
    }
    return balance(cur);
}

DeleteResult* deleteSmallest(AVL_Tree* tree, Node* node) {
    if (node->left != NULL) {
        DeleteResult* child = deleteSmallest(tree, node->left);
        node->left = child->returnNode;

        return deleteResult(balance(node), child->deletedVal);
    }
    else {
        return deleteResult(balance(node->right), node->val);
    }
}
Node* deleteNode(AVL_Tree* tree, Node* node, int val) {
    if (node == NULL) {
        return NULL;
    }
    if (node->val > val) {
        if (node->left == NULL) return node;
        node->left = deleteNode(tree, node->left, val);
        balance(node);
        return node;
    }
    else if (node->val < val) {
        if (node->right == NULL) return NULL;
        node->right = deleteNode(tree, node->right, val);
        balance(node);
        return node;
    }

    // 0 children: just remove the node
    if (isLeaf(node)) {
        tree->size--;
        free(node);
        return NULL;
    }
    // 2 children:
    else if (node->left != NULL && node->right != NULL) {
        DeleteResult* result = deleteSmallest(tree, node->right);
        node->val = result->deletedVal;
        node->right = result->returnNode;
        balance(node);
    }
    // 1 child: just replace the node with only child:
    else {
        tree->size--;
        Node* result;
        if (node->left != NULL) {
            result = node->left;
            free(node);
        }
        else {
            result = node->right;
            free(node);
        }
        balance(result);
        return result;
    }
}
void delete(AVL_Tree* tree, int val) {
    tree->root = deleteNode(tree, tree->root, val);
}