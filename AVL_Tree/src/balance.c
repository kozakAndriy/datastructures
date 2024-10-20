#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// This file is perfectly balanced. As all things should be


Node* rightLeftRotation(Node* P) {
    P->right = rightRotation(P->right);
    return leftRotation(P);
}
Node* leftRightRotation(Node* P) {
    P->left = leftRotation(P->left);
    return rightRotation(P);
}

Node* rightRotation(Node* P) {
    Node* L = P->left;
    
    P->left = L->right;
    L->right = P;
    balance(P);
    balance(L);
    return L;
}
Node* leftRotation(Node* P) {
    Node* R = P->right;

    P->right = R->left;
    R->left = P;
    balance(P);
    balance(R);
    return R;
}


int updateHeight(Node* node) {
    Node* a = node->left;
    Node* b = node->right;

    int height = 0;
    if (a != NULL && a->height > height) {
        height = a->height;
    }
    if (b != NULL && b->height > height) {
        height = b->height;
    }
    node->height = height + 1;
    return height + 1;
}
int getBalance(Node* node) {
    int left = 0;
    if (node->left != NULL) {
        left = node->left->height;
    }
    int right = 0;
    if (node->right != NULL) {
        right = node->right->height;
    }
    return left - right;
}

Node* balance(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    updateHeight(node);

    int bal = getBalance(node);
    
    if (bal > 1) { // left heavy
        Node* C = node->left;
        Node* CR = C->right;
        Node* CL = C->left;

        if (CR != NULL && (CL == NULL || CR->height > CL->height)) {
            return leftRightRotation(node);
        }
        else return rightRotation(node);
    } 
    else if (bal < -1) {
        Node* C = node->right;
        Node* CR = C->right;
        Node* CL = C->left;

        if (CL != NULL && (CR == NULL || CL->height > CR->height)) {
            return rightLeftRotation(node);
        }
        else return leftRotation(node);
    }

    return node;
}