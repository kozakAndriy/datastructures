#include "../src/avl.h"
#include <stdio.h>

int main() {
    
    printf("------ TESTS ------\n");
    
    AVL_Tree* tree = initTree();
    push(tree, node(5, NULL, NULL));
    push(tree, node(8, NULL, NULL));
    push(tree, node(6, NULL, NULL));
    print(tree);
    
    AVL_Tree* tree2 = initTree();
    push(tree2, node(5, NULL, NULL));
    push(tree2, node(2, NULL, NULL));
    push(tree2, node(6, NULL, NULL));
    push(tree2, node(8, NULL, NULL));
    push(tree2, node(1, NULL, NULL));
    push(tree2, node(9, NULL, NULL));
    push(tree2, node(7, NULL, NULL));
    delete(tree2, 8);
    delete(tree2, 9);
    delete(tree2, 5);

    print(tree2);

    printf("----  Success! ----\n");

    return 0;
}