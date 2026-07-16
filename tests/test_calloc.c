#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);

    int *numbers = arena_calloc(arena, 5, sizeof(int));
    assert(numbers != NULL);

    size_t count = 5;

    for (size_t i = 0; i < count; i++) {
        assert(numbers[i] == 0);
    }

    numbers[0] = 10; 
    assert(numbers[0] == 10);

    arena_destroy(arena);

    printf("test_calloc.c PASSED\n");

    return 0;
}
