#ifndef vector_h
#define vector_h
#include <stddef.h>

typedef struct {
    void* data;
    int length;

    size_t bytes_capacity;
    size_t bytes_per_element;
    
    void (*print_element)(void*, int);
    void (*free_element)(void*);
} vector;

typedef struct {
    void (*print_element)(void*, int);
    void (*free_element)(void*);
} VectorOptions;

vector* new_vec(size_t bytes_per_element, VectorOptions* options);

void print_vec(vector* vec);

void ensure_capacity(vector* vec, size_t new_size);
void free_vec(vector* vec);

void* get(vector* vec, int index);
void set(vector* vec, int index, void* element);

void push(vector* vec, void* element);
void* pop(vector* vec);
void swap(vector* vec, int i1, int i2);
void* last(vector* vec);
void* first(vector* vec);

#define vecpush(vec, value) ({ \
    typeof(value) *tmp = malloc(sizeof(typeof(value))); \
    *tmp = value; \
    push(vec, tmp); \
    free(tmp); \
})

#define vecset(vec, index, value) ({ \
    typeof(value) *tmp = malloc(sizeof(typeof(value))); \
    *tmp = value; \
    set(vec, index, tmp); \
    free(tmp); \
})

vector* map(vector* vec, void* (*fn)(void*, size_t));
vector* for_each(vector* vec, void (*fn)(void*, size_t));

#endif