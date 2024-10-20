#ifndef heap_h
#define heap_h

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../vector/implementation/vector.h"

typedef bool (*cmp_func)(void*, void*);

typedef struct {
    vector* container;
    int size;
    cmp_func cmp;
} Heap;


void* nodeValue(Heap* heap, int i);
void heapswap(Heap* heap, int i1, int i2);
bool hasChildren(Heap* heap, int i);

Heap* heapinit(size_t element_size, cmp_func cmp);
bool heapIsEmpty(Heap* heap);

int parentIndex(int i);
bool hasParent(Heap* heap, int i);
void* parent(Heap* heap, int i);

int leftChildIndex(int i);
bool hasLeftChild(Heap* heap, int i);
void* leftChild(Heap* heap, int i);

int rightChildIndex(int i);
bool hasRightChild(Heap* heap, int i);
void* rightChild(Heap* heap, int i);

//void heap_push(Heap* heap, void* val);
void* heappop(Heap* heap);
void* top(Heap* heap);
void bubbleDown(Heap* heap, int i);
void bubbleUp(Heap* heap, int i);
void heapprint(Heap* heap);

#define heappush(heap, value) ({ \
    typeof(value) *tmp = malloc(sizeof(typeof(value))); \
    *tmp = value; \
    push(heap->container, tmp); \
    heap->size++; \
    free(tmp); \
    bubbleUp(heap, heap->size - 1); \
})


#endif