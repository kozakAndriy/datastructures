#include "../implementation/vector.h"
#include "tests.h"

#include <stdio.h>
#include <stdbool.h>

void test_memory() {
    current_test = "-----------MEMORY----------";
    vector* my_vec = new_vec(sizeof(int), NULL);

    print_result();
}