#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 50

typedef struct node {
    int value;
    struct node* next;
} node;

node* hash_set[TABLE_SIZE];

void init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_set[i] = NULL;
    }
}
void print() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_set[i] == NULL) {
            printf("\t%d\t---\n", i);
        }
        else {
            printf("\t%d\t", i);
            node* tmp = hash_set[i];
            while (tmp != NULL) {
                printf("%d, ", tmp->value);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}
int hash(int num) {
    return num % TABLE_SIZE;
}
void insert(int val) {
    int index = hash(val);
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return;
    }
    new_node->value = val;
    new_node->next = NULL;

    if (hash_set[index] == NULL) {
        hash_set[index] = new_node;
        return;
    }
    node* tmp = hash_set[index];
    while (tmp->next != NULL) {
        if (tmp->value == val) {
            return;
        }
        tmp = tmp->next;
    }
    if (tmp->value != val) {
        tmp->next = new_node;
    }
} 
void delete(int val) {
    int index = hash(val);

    if (hash_set[index] == NULL) {
        return;
    }
    node* tmp = hash_set[index];
    node* prev = NULL;

    while (tmp != NULL) {
        if (tmp->value == val) {
            if (prev == NULL) {
                hash_set[index] = tmp->next;  
            }
            else {
                prev->next = tmp->next;
            }
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
        
    }
}
bool contains(int val) {
    int index = hash(val);
    if (hash_set[index] == NULL) {
        return false;
    }
    node* tmp = hash_set[index];

    while (tmp != NULL) {
        if (tmp->value == val) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}
void clear() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_set[i] == NULL) {
            continue;
        }
        node* tmp = hash_set[i];
        while (tmp != NULL) {
            node* next = tmp->next;
            free(tmp);
            tmp = next;
        }
        hash_set[i] = NULL;
    }
}

int main() {
    init();
    insert(5);
    insert(25);
    insert(50);
    delete(25);
    delete(5);
    insert(20);


    bool has_5 = contains(5);
    bool has_25 = contains(25);
    bool has_50 = contains(50);

    printf("has 5: %d; has 25: %d; has 50: %d", has_5, has_25, has_50);

    return 0;
}