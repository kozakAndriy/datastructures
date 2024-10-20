#include <stdlib.h>
#include "vector.h"
#include <stddef.h>

#define INITIAL_ELEMENTS_CAPACITY 3

vector* new_vec(size_t bytes_per_element, VectorOptions* options) {

    vector* created_vector = malloc(sizeof(vector));
    
    created_vector->length = 0;
    created_vector->bytes_per_element = bytes_per_element;
    created_vector->bytes_capacity = INITIAL_ELEMENTS_CAPACITY * bytes_per_element;
    created_vector->print_element = options ? options->print_element : NULL;
    created_vector->free_element = options ? options->free_element : NULL;
    created_vector->data = malloc(INITIAL_ELEMENTS_CAPACITY * bytes_per_element);

    return created_vector;
}