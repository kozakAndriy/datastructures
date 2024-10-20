#include "tests.h"
#include <stdlib.h>
#include <stdio.h>

void print_lines() {
    
}
void print_current_test() {
    for (int i = 0; i < 25; i++) {
        printf("%c", current_test[i]);
    }
    printf("\n");
}
void print_result() {
    print_current_test();
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);

    passed = 0;
    failed = 0;
}

void assert_true(bool expression) {
    if (expression == false) {
        failed++;
    }
    else {
        passed++;
    }
}