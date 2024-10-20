#include "./heap.h"

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>


void bubbleUp(Heap* heap, int i) {
    while (hasParent(heap, i) && 
    heap->cmp(nodeValue(heap, i), parent(heap, i))) {
        heapswap(heap, i, parentIndex(i));
        i = parentIndex(i);
    }
}

void bubbleDown(Heap* heap, int i) {
    while (hasChildren(heap, i)) { 
        int maxChildI;
        if (hasRightChild(heap, i)) {
            if (!hasLeftChild(heap, i)) {
                fprintf(stderr, "Error: Heap not a complete tree\n");
                exit(EXIT_FAILURE);
            }
            if (heap->cmp(rightChild(heap, i), leftChild(heap, i))) {
                // right child has greater priority
                maxChildI = rightChildIndex(i);
            }
            else {
                maxChildI = leftChildIndex(i);
            }
        }
        else {
            maxChildI = leftChildIndex(i);
        }
        if (heap->cmp(nodeValue(heap, i), nodeValue(heap, maxChildI))) break;
        heapswap(heap, i, maxChildI);
        i = maxChildI;
    }
}

void* heappop(Heap* heap) {
    if (heap->size == 0) {
        fprintf(stderr, "Error: Popping from empty heap\n");
        exit(EXIT_FAILURE);
    }
    void* retVal = malloc(heap->container->bytes_per_element);
    memcpy(retVal, top(heap), heap->container->bytes_per_element);

    set(heap->container, 0, last(heap->container));
    pop(heap->container);
    heap->size--;
    
    bubbleDown(heap, 0);

    return retVal;
}
void* top(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }
    return nodeValue(heap, 0);
}
void heapfree(Heap* heap) {
    free_vec(heap->container);
    free(heap);
}