#include "arena/arena.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_used(arena) == 0);
    assert(arena_capacity(arena) == 1024);
    assert(arena_available(arena) == 1024);

    int *n = arena_alloc(arena, sizeof(int));
    assert(n != NULL);

    *n = 40;
    assert(*n == 40);
    assert(arena_available(arena) == 1024 - sizeof(int));

    arena_reset(arena);
    assert(arena_available(arena) == 1024);
    assert(arena_used(arena) == 0);

    int *num = arena_alloc(arena, sizeof(int));
    assert(num != NULL);

    *num = 41;
    assert(*num == 41);
    assert(arena_available(arena) == 1024 - sizeof(int));

    arena_destroy(arena);

    printf("[TEST] test_reset.c PASSED\n");

    return 0;
}

