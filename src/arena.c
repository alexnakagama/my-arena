#include "arena/arena.h"

#include <stddef.h>
#include <stdlib.h>

/*
    * void *buffer (points to the large block of memory that we allocated, here the arena starts)
    * size_t capacity (indicates how many bytes has the block in total)
    * size_t offset (indicates how many bytes were already utilized)
*/
struct arena_t {
    void *buffer;
    size_t capacity;
    size_t offset;
};

arena_t *arena_create(size_t s) {
    arena_t *arena = malloc(sizeof(arena_t));
    if (!arena) {
        return NULL;
    }

    arena->buffer = malloc(s);
    if (!arena->buffer) {
        free(arena);
        return NULL;
    }

    arena->capacity = s;
    arena->offset = 0;

    return arena;
}
