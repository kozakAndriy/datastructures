#include "../implementation/vector.h"
#include "tests.h"

#include <stdio.h>
#include <stdbool.h>


int increment_operations;
void increment(void* element, size_t i) {
    increment_operations++;
    (*(int*)element)++;
}

void test_operations() {
    current_test = "--------OPERATIONS---------";
    
    vector* pushpop = new_vec(sizeof(int), NULL);
    assert_true(pushpop->bytes_per_element == 4);

    // push & pop
    vecpush(pushpop, 2);

    assert_true(*(int*)get(pushpop, 0) == 2);
    assert_true(pushpop->length == 1);

    assert_true(*(int*)pop(pushpop) == 2);
    assert_true(pushpop->length == 0);
 
    // set
    vector* setTest = new_vec(sizeof(int), NULL);
    vecpush(setTest, 1); // error: lvalue required as unary ‘&’ operand
    vecpush(setTest, 2);
    vecpush(setTest, 3);

    vecset(setTest, 0, 3);
    vecset(setTest, 1, 4);
    vecset(setTest, 2, 5);
    assert_true(*(int*)get(setTest, 0) == 3);
    assert_true(*(int*)get(setTest, 1) == 4);
    assert_true(*(int*)get(setTest, 2) == 5);
    free_vec(setTest);


    // forEach
    
    vector* forEach = new_vec(sizeof(int), NULL);
    vecpush(forEach, 2);
    vecpush(forEach, 1);
    vecpush(forEach, 9);
    vecpush(forEach, 3);
    vecpush(forEach, 4);

    assert_true(forEach->length == 5);
    assert_true(for_each(forEach, increment) == forEach);
    assert_true(*(int*)get(forEach, 2) == 10);

    assert_true(increment_operations == forEach->length);

    // swap
    vector* swapTest = new_vec(sizeof(int), NULL);

    vecpush(swapTest, 2);
    vecpush(swapTest, 3);

    assert_true(*(int*)get(swapTest, 0) == 2);
    assert_true(*(int*)get(swapTest, 0) == 2 && *(int*)get(swapTest, 1) == 3);

    swap(swapTest, 0, 1);
    assert_true(*(int*)get(swapTest, 0) == 3 && *(int*)get(swapTest, 1) == 2); 

    print_result(); 
}