#ifndef tests
#define tests

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

extern int passed;
extern int failed;
extern char* current_test;

void assert_true(bool expression);
void print_result();

void test_init();
void test_print();
void test_memory();
void test_operations();

#endif