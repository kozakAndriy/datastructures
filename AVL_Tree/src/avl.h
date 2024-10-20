#ifndef avl_h
#define avl_h

#include <stddef.h>
#include <stdbool.h>

#define SIZE_LIMIT 10000

typedef struct Node {
    int val;
    int height;
    struct Node* left;
    struct Node* right;

} Node;

typedef struct {
    int height;
    int size;
    struct Node* root;
} AVL_Tree;

AVL_Tree* initTree();
Node* node(int val, Node* left, Node* right);

void push(AVL_Tree* root, Node* node);
void delete(AVL_Tree* tree, int val);

char* serialize(AVL_Tree* tree);
void print(AVL_Tree* tree);

// Insert/Delete

typedef struct {
    int deletedVal;
    Node* returnNode;
} DeleteResult;
DeleteResult* deleteResult(Node* returnNode, int deletedVal);

// Utils
bool isLeaf(Node* node);

DeleteResult* deleteSmallest(AVL_Tree* tree, Node* node);
Node* deleteNode(AVL_Tree* tree, Node* node, int val);

Node* insert(AVL_Tree* tree, Node* cur, Node* node);

// Balance
Node* balance(Node* node);
int updateHeight(Node* node);
Node* rightRotation(Node* P);
Node* leftRotation(Node* P);
Node* rightLeftRotation(Node* P);
Node* leftRightRotation(Node* P);

#endif