#include "vector.h"
#include "stdlib.h"
#include <string.h>

#include <stdio.h>

void* get(vector* vec, int index) {
    return ((char*)vec->data) + vec->bytes_per_element * index;
}
void set(vector* vec, int index, void* element) {
    memcpy(get(vec, index), element, vec->bytes_per_element);
}

void swap(vector* vec, int i1, int i2) {
    set(vec, vec->length, get(vec, i1));
    set(vec, i1, get(vec, i2));
    set(vec, i2, get(vec, vec->length));
}

void push(vector* vec, void* element) {
    size_t cur_size = vec->bytes_per_element * vec->length;
    ensure_capacity(vec, cur_size + 2*vec->bytes_per_element);

    set(vec, vec->length, element);
    vec->length++;
}

vector* for_each(vector* vec, void (*fn)(void*, size_t)) {
    for (size_t i = 0; i < vec->length; i++) {
        fn(get(vec, i), i);
    }
    return vec;
}

vector* map(vector* vec, void* (*fn)(void*, size_t)) {
    for (size_t i = 0; i < vec->length; i++) {
        set(vec, i, fn(get(vec, i), i));
    }
    return vec;
}

void* pop(vector* vec) {
    if (vec->length == 0) {
        return NULL;
    }
    vec->length--;
    return get(vec, vec->length);
}

void* last(vector* vec) {
    if (vec->length == 0) {
        return NULL;
    }
    return get(vec, vec->length - 1);
}
void* first(vector* vec) {
    if (vec->length == 0) {
        return NULL;
    }
    return get(vec, 0);
}