#include "heap.h"
#include <stdio.h>
#include <stdbool.h>


void heapprint(Heap* heap) {
    vector* c = heap->container;
    
    for (int i = 0; i < c->length; i++) {
        printf("%d, ", *(int*)get(c, i));
    }
    printf("\n");
}