#include <assert.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);

    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);
    assert(arena_used(arena) == 0);
    assert(arena_available(arena) == 1024);

    arena_destroy(arena);

    printf("test_create.c passed.\n");

    return 0;
}
