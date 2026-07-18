#include <assert.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);
    assert(arena_is_empty(arena) == true);

    int *number = arena_alloc(arena, sizeof(int));
    assert(number != NULL);

    *number = 42;
    assert(*number == 42);

    assert(arena_used(arena) == sizeof(int));
    assert(arena_available(arena) == 1024 - sizeof(int));
    assert(arena_is_empty(arena) == false);

    arena_destroy(arena);

    printf("[TEST] test_empty.c PASSED\n");
    
    return 0;
}
