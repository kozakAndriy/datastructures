#include "vector.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define REALLOC_ADD 5

void ensure_capacity(vector* vec, size_t capacity) {
    if (vec->bytes_capacity < capacity) {
        size_t new_cap = vec->bytes_capacity + (REALLOC_ADD * vec->bytes_per_element);

        vec->data = realloc(vec->data, new_cap);
        vec->bytes_capacity = new_cap;
    }
}

void free_vec(vector* vec) {

    if (vec->free_element != NULL) {
        for (int i = 0; i < vec->length; i++) {
            vec->free_element(get(vec, i));
        }
    }

    free(vec->data);
    vec->length = 0;
}

