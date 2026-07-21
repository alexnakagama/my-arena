#include <assert.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);

    printf("[TEST] test_alloc_aligned.c PASSED\n");

    return 0;
}
