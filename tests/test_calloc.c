#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);

    size_t count = 5;

    int *numbers = arena_calloc(arena, count, sizeof(int));
    assert(numbers != NULL);

    for (size_t i = 0; i < count; i++) {
        assert(numbers[i] == 0);
    }

    size_t total = count * sizeof(int);
    assert(arena_used(arena) == total);
    assert(arena_available(arena) == 1024 - total);

    numbers[0] = 10; 
    assert(numbers[0] == 10);

    arena_destroy(arena);

    printf("[TEST] test_calloc.c PASSED\n");

    return 0;
}
