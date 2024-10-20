#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

void print_vec(vector* vec) {
    if (vec->print_element == NULL) {
        return;
    }
    printf("Printing vector with length %d and capacity %zu!\n", vec->length, vec->bytes_capacity);
    
    printf("[");
    for(int i = 0; i < vec->length; i++) {
        void* element = get(vec, i);
        
        vec->print_element(element, i);

        if (i != vec->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
