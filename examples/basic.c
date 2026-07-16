#include "arena/arena.h"
#include <stdio.h>

int main(void) {
    arena_t *arena = arena_create(1024);

    int *number = arena_alloc(arena, sizeof(int));

    *number = 42;

    char *name = arena_strdup(arena, "Alex");
    char *city = arena_strdup(arena, "Buenos Aires");

    arena_info(arena);

    arena_dump(arena);

    printf("Name: %s\n", name);
    printf("City: %s\n", city);

    arena_destroy(arena);

    return 0;
}
