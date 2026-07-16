#include <assert.h>
#include <stdio.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);

    arena_destroy(arena);

    printf("test_destroy.c PASSED\n");

    return 0;
}
