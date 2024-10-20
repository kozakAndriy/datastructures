#include "heap.h"

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>


bool defaultcmp(void* a, void* b) {
    return (*(int*)a) > (*(int*)b);
}

Heap* heapinit(size_t bytes_per_element, cmp_func cmp) {
    Heap* heap = malloc(sizeof(Heap));
    heap->container = new_vec(bytes_per_element, NULL);
    if (cmp == NULL) {
        heap->cmp = defaultcmp;
    }
    else heap->cmp = cmp;

    return heap;
}
bool heapIsEmpty(Heap* heap) {
    return heap->size == 0;
}
void* nodeValue(Heap* heap, int i) {
    return get(heap->container, i);
}
void heapswap(Heap* heap, int i1, int i2) {
    swap(heap->container, i1, i2);
}
bool hasChildren(Heap* heap, int i) {
    return hasRightChild(heap, i) || hasLeftChild(heap, i);
}

int leftChildIndex(int i) {
    return (i*2)+1;
}
bool hasLeftChild(Heap* heap, int i) {
    int index = leftChildIndex(i);
    if (index >= heap->size) {
        return false;
    }
    return true;
}
void* leftChild(Heap* heap, int i) {
    if (!hasLeftChild(heap, i)) {
        fprintf(stderr, "Error: Tried getting a left child of heap element out of bounds\n");
        exit(EXIT_FAILURE);
    }

    return get(heap->container, leftChildIndex(i));
}

int rightChildIndex(int i) {
    return (i*2)+2;
}
bool hasRightChild(Heap* heap, int i) {
    int index = rightChildIndex(i);
    if (index >= heap->size) {
        return false;
    }
    return true;
}
void* rightChild(Heap* heap, int i) {
    if (!hasRightChild(heap, i)) {
        fprintf(stderr, "Error: Tried getting a right child of heap element out of bounds\n");
        exit(EXIT_FAILURE);
    }

    return get(heap->container, rightChildIndex(i));
}

int parentIndex(int i) {
    return (i-1) / 2;
}
bool hasParent(Heap* heap, int i) {
    return i != 0;
}
void* parent(Heap* heap, int i) {
    if (!hasParent) {
        fprintf(stderr, "Error: Tried getting a right child of heap element out of bounds\n");
        exit(EXIT_FAILURE);
    }

    return get(heap->container, parentIndex(i));
}




