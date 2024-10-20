#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stddef.h>

#define MEM_SIZE 4096

typedef struct {
    int size;
    bool in_use;
} header;

void* heap_alloc(header* heap_head, size_t size) {
    header* cur = heap_head;
    

    while (cur->in_use || cur->size < size) {
        //printf("Current chunk is in use, so move on to the next one.\n");
        cur = (header*)( (char*)cur + cur->size + 2*sizeof(header) );
        if ((char*)cur >= (char*)heap_head + MEM_SIZE) {
            return NULL;
        }
        
    }
    // we don't want to have chunks less than 32 bytes lol. add them to current size instead of creating 2 new headers with miserable payload
    int free_chunk_size = cur->size;
    int chunk_size_actual = free_chunk_size - size < 32 ? free_chunk_size : size;
    int leftover_chunk_size = free_chunk_size - chunk_size_actual - 2*sizeof(header);
    
    // first header
    cur->size = chunk_size_actual;
    cur->in_use = true;
    void* return_pointer = (void*)( (char*)cur + sizeof(header) );

    // second header
    cur = (header*)( (char*)cur + cur->size + sizeof(header) );
    cur->size = chunk_size_actual;
    cur->in_use = true;

    // first header of the next chunk
    cur = (header*)( (char*)cur + sizeof(header) );
    cur->in_use = false;
    cur->size = leftover_chunk_size;

    // update the previous second header of the first chunk (second header of the new chunk)
    cur = (header*)( (char*)cur + cur->size + sizeof(header) );
    cur->size = leftover_chunk_size;
    cur->in_use = false; // No need to mark it as unused, as it was already

    return return_pointer;
}

void heap_free(header* heap_head, void* ptr) {
    header* chunk_header = (header*)( (char*)ptr - sizeof(header) );
    void* heap_boundary = (void*)( (char*)heap_head + MEM_SIZE );

    header* leftmost_header = chunk_header;
    header* rightmost_header = (header*)( (char*)chunk_header + chunk_header->size + sizeof(header) );

    header* previous_header_second = (header*)( (char*)chunk_header - sizeof(header) );
    if (previous_header_second >= heap_head && previous_header_second->in_use == false) {
        leftmost_header = (header*)( (char*)previous_header_second - previous_header_second->size - sizeof(header) );
    }

    header* next_header_first = (header*)( (char*)chunk_header + chunk_header->size + 2*sizeof(header) );
    if ((void*)next_header_first < heap_boundary && next_header_first->in_use == false) {
        rightmost_header = (header*)( (char*)next_header_first + next_header_first->size + sizeof(header) );
    }

    char* ptr_rtm_header = (char*)rightmost_header;
    char* ptr_ltm_header = (char*)leftmost_header;

    int new_chunk_size = (ptr_rtm_header - ptr_ltm_header) - sizeof(header);
    printf("New chunk size after coalescing: %d\n", new_chunk_size);

    rightmost_header->in_use = false;
    leftmost_header->in_use = false; 

    leftmost_header->size = new_chunk_size;
    rightmost_header->size = new_chunk_size;
}

int main() {
    header* heap_head = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (heap_head == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    
    // first header of the chunk
    heap_head->size = MEM_SIZE - 2*sizeof(header);
    heap_head->in_use = false;

    // second header of the chunk
    header* second_header = (header*)( (char*)heap_head + MEM_SIZE - 2*sizeof(header) );
    second_header->size = MEM_SIZE - 2*sizeof(header);
    heap_head->in_use = false;

    void* my_memory_1 = heap_alloc(heap_head, 32);
    printf("My memory 1 address is: %p\n", my_memory_1);

    void* my_memory_2 = heap_alloc(heap_head, 32);
    printf("My memory 2 address is: %p\n", my_memory_2);

    void* my_memory_3 = heap_alloc(heap_head, 32);
    printf("My memory 3 address is: %p\n", my_memory_3);


    heap_free(heap_head, my_memory_1);
    heap_free(heap_head, my_memory_2);
    heap_free(heap_head, my_memory_3);

    void* my_memory_4 = heap_alloc(heap_head, 64);
    heap_free(heap_head, my_memory_4);


    // Unmap the memory
    if (munmap(heap_head, MEM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    return 0;
}