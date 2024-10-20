#include "../implementation/vector.h"
#include "./tests.h"
#include <stdbool.h>
#include <stdio.h>

int passed = 0;
int failed = 0;
char* current_test = "                       26";

int main() {
    printf("-----------TESTS----------\n\n");

    test_init();
    test_memory();
    test_print();
    test_operations();

    return 0;
}