#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person {
    char name[MAX_NAME];
    int age;
    struct person* next;
} person;

person* hash_table[TABLE_SIZE];

void init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}
void print() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%d\t---\n", i);
        }
        else {
            printf("\t%d\t", i);
            person* tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%s, ", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}
int hash(char* name) {
    int hash_value = 0;
    int len = strlen(name);
    for (int i = 0; i < len; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}
bool insert(person* element) {
    // find the index to insert person* to:
    int index = hash(element->name);

    // if the slot is empty
    if (hash_table[index] == NULL) {
        hash_table[index] = element;
        return true;
    }
    // traversing the linkedList to find the last element
    person* tmp = hash_table[index];
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = element;


    return true;
}
person* delete(char* name) {
    int index = hash(name);

    // traverse the linked list at that index in the hash table:
    person* tmp = hash_table[index];
    person* prev = NULL;

    while (strcmp(tmp->name, name) != 0) {
        if (tmp->next == NULL) {
            return NULL;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    // if we are deleting the head of the list, we need to point the hash table at index "index" to the second element in the linked list.
    if (prev == NULL) {
        hash_table[index] = tmp->next;
    }
    else {
        prev->next = tmp->next;
    }
    
    return tmp;
}
int main()
{
    init();

    person jacob = {.name="Jacob", .age=26};
    person kate = {.name="Kate", .age=24};
    person mpho = {.name="Mpho", .age=40};
    person sarah = {.name="Sarah", .age=19};
    person edna = {.name="Edna", .age=15};
    person maren = {.name="Maren", .age=13};
    person eliza = {.name="Eliza", .age=25};
    person robert = {.name="Robert", .age=65};
    person jane = {.name="Jane", .age=31};

    insert(&jacob);
    insert(&kate);
    insert(&sarah);
    insert(&edna);
    insert(&maren);
    insert(&eliza);
    insert(&robert);
    insert(&jane);
    
    print();
    
    return 0;
}