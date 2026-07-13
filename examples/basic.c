#include "arena/arena.h"

int main(void) {
    arena_t *arena = arena_create(1024);

    int *number = arena_alloc(arena, sizeof(int));

    *number = 42;

    arena_info(arena);

    arena_dump(arena);

    arena_destroy(arena);

    return 0;
}
