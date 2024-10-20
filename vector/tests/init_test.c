#include "../implementation/vector.h"
#include "tests.h"

#include <stdio.h>
#include <stdbool.h>

void test_init() {
    current_test = "-----------INIT------------";
    vector* my_vec = new_vec(sizeof(int), NULL);

    assert_true(my_vec->length == 0);
    assert_true(my_vec->bytes_per_element == sizeof(int));
    assert_true(my_vec->print_element == NULL);
    assert_true(my_vec->free_element == NULL);
    assert_true(my_vec->data != NULL);

    print_result();
}