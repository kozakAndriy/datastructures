
#include "../src/heap.h"
#include <stdio.h>
#include <stdbool.h>

int passed = 0;
int failed = 0;

void assert_eq(int val1, int val2) {
    if (val1 != val2) {
        printf("TEST #%d FAILED: %d != %d\n", passed + failed, val1, val2);
        failed++;
    }
    else passed++;
}
void newSection(char* sectionName) {
    if (passed != 0 || failed != 0) {
        printf(" - PASSED: %d\n - FAILED: %d\n", passed, failed);
    }
    passed = 0;
    failed = 0;
    printf(" ----- %s ----- \n", sectionName);
}


int main() {
    newSection("Init tests");
    Heap* heap = heapinit(sizeof(int), NULL);
    assert_eq(heap->container->length, 0);

    newSection("Push tests");

    heappush(heap, 1);
    assert_eq(heap->container->length, 1);
    assert_eq(heap->size, 1);
    assert_eq(*(int*)top(heap), 1);

    heappush(heap, 2);
    assert_eq(*(int*)top(heap), 2);

    heappush(heap, 0);
    assert_eq(*(int*)top(heap), 2);

    heappush(heap, 10);
    assert_eq(*(int*)top(heap), 10);

    heappush(heap, 3);
    assert_eq(*(int*)top(heap), 10);
    assert_eq(heap->size, heap->container->length);

    assert_eq(*(int*)heappop(heap), 10);
    assert_eq(heap->size, heap->container->length);

    assert_eq(*(int*)heappop(heap), 3);
    assert_eq(*(int*)heappop(heap), 2);
    assert_eq(*(int*)heappop(heap), 1);
    assert_eq(*(int*)heappop(heap), 0);

    

    newSection("TESTS OUT. CARRY ON");

    return 0;
}