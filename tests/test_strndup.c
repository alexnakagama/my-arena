#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);

    const char *my_str = "Hello World!";

    char *str = arena_strndup(arena, my_str, 4);
    assert(str != NULL);
    assert(strcmp(str, "Hell") == 0);

    printf("[TEST] arena_strndup PASSED\n");

    arena_destroy(arena);

    return 0;
}
