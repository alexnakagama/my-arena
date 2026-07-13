#include "arena/arena.h"

int main(void) {
    arena_t *arena;

    arena = arena_create(1024);

    arena_alloc(arena, 20);

    arena_print(arena);

    return 0;
}
