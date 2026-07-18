#include <assert.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);

    int *number = arena_alloc(arena, sizeof(int));
    assert(number != NULL);

    *number = 40;
    assert(*number == 40);

    assert(arena_used(arena) == sizeof(int));
    assert(arena_available(arena) == 1024 - sizeof(int));
    assert(arena_capacity(arena) == 1024);

    arena_destroy(arena);

    printf("[TEST] test_alloc.c PASSED\n");

    return 0;
}
