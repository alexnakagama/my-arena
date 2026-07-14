#include "arena/arena.h"
#include <stdio.h>

int main(void) {
    arena_t *arena = arena_create(1024);

    int *number = arena_alloc(arena, sizeof(int));

    *number = 42;

    char *name = arena_strdup(arena, "Alex");

    arena_info(arena);

    arena_dump(arena);

    printf("%s\n", name);

    arena_destroy(arena);

    return 0;
}
