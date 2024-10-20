#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* serialize(AVL_Tree* tree) {
    char* result = malloc(sizeof(char) * SIZE_LIMIT);
    int i = 0;
    
    if (tree->size == 0) {
        result[i] = 'N';
        result[i+1] = '\n';
        i += 2;

        result = realloc(result, sizeof(char) * i);
        return result;
    }
    size_t queue_size = sizeof(Node*) * SIZE_LIMIT;
    Node** queue = malloc(queue_size);
    Node** newQueue = malloc(queue_size);

    int layer = 1;

    queue[0] = tree->root;
    bool added = true;
    while (added) {
        added = false;
        int newQueueI = 0;

        for (int l = 0; l < layer; l++) {
            if (queue[l] == NULL) {
                result[i] = 'N';
                result[i+1] = ' ';

                newQueue[newQueueI] = NULL;
                newQueue[newQueueI + 1] = NULL;
                newQueueI += 2;
                
                i += 2;
            }
            else {
                if (queue[l]->left != NULL || queue[l]->right != NULL) {
                    added = true;
                }
                newQueue[newQueueI] = queue[l]->left;
                newQueue[newQueueI + 1] = queue[l]->right;
                newQueueI += 2;

                result[i] = '0' + queue[l]->val;
                result[i+1] = ' ';
                i += 2;
            }
        }
        result[i] = '\n';
        i++;

        layer *= 2;

        Node** t = queue;
        queue = newQueue;
        newQueue = t;
        memset(newQueue, 0, queue_size);
    }
    free(queue);
    free(newQueue);
    
    result = realloc(result, i * sizeof(char));
    return result;
}
void print(AVL_Tree* tree) {
    printf("Size: %d\n", tree->size);
    char* serialized = serialize(tree);
    printf("<Tree>\n %s</Tree>\n", serialized);
}