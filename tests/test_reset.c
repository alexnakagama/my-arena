#include "arena/arena.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);

    int *n = arena_alloc(arena, sizeof(int));
    assert(n != NULL);

    *n = 40;
    assert(*n == 40);
    assert(arena_available(arena) == 1024 - sizeof(int));
    assert(arena_capacity(arena) == 1024);

    arena_reset(arena);
    assert(arena_capacity(arena) == 1024);
    assert(arena_available(arena) == 1024);
    assert(arena_used(arena) == 0);

    arena_destroy(arena);

    printf("test_reset.c PASSED\n");

    return 0;
}
