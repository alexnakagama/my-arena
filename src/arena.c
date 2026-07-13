#include "arena/arena.h"

#include <stddef.h>
#include <stdio.h>
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

arena_t *arena_create(size_t size) {
    arena_t *arena = malloc(sizeof(arena_t));
    if (!arena) {
        return NULL;
    }

    arena->buffer = malloc(size);
    if (!arena->buffer) {
        free(arena);
        return NULL;
    }

    arena->capacity = size;
    arena->offset = 0;

    return arena;
}

void *arena_alloc(arena_t *arena, size_t size) {
    if (!arena) {
        return NULL;
    }

    if (arena->offset + size > arena->capacity) {
        return NULL;
    }

    void *address = (unsigned char *)arena->buffer + arena->offset;
    arena->offset += size;

    return address;
}

void arena_reset(arena_t *arena) {
    if (!arena) {
        return;
    }

    arena->offset = 0;
}

void arena_destroy(arena_t *arena) {
    if (!arena) {
        return;
    }
    
    free(arena->buffer);
    free(arena);
}

size_t arena_used(const arena_t *arena) {
    if (!arena) {
        return 0;
    }

    return arena->offset;
}

size_t arena_available(const arena_t *arena) {
    if (!arena) {
        return 0;
    }

    size_t available = arena->capacity - arena->offset;

    return available;
}
