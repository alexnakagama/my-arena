#include "arena/arena.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
 * Allocates big memory region that will be used to store data
 * Pass the total size of the arena. arena->capacity = size
*/ 
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

    return arena->capacity - arena->offset;
}

size_t arena_capacity(const arena_t *arena) {
    if (!arena) {
        return 0;
    }

    return arena->capacity;
}

void arena_info(const arena_t *arena) {
    if (!arena) {
        return;
    }

    size_t available = arena->capacity - arena->offset;
    double usage = ((double)arena->offset / arena->capacity) * 100.0;

    printf("---Arena---\n");
    printf("Buffer: %p\n", arena->buffer);
    printf("Used: %zu bytes\n", arena->offset);
    printf("Capacity: %zu bytes\n", arena->capacity);
    printf("Available: %zu bytes\n", available);
    printf("Usage: %.2f%%\n", usage);
}

void *arena_calloc(arena_t *arena, size_t count, size_t size) {
    size_t total = count * size;

    void *ptr = arena_alloc(arena, total);
    if (!ptr) {
        return NULL;
    }

    memset(ptr, 0, total);

    return ptr;
}

void arena_dump(const arena_t *arena) {
    if (!arena) {
        return;
    }

    unsigned char *buffer = arena->buffer;

    for (size_t i = 0; i < arena->offset; i++) {
        printf("%02x ", buffer[i]);
    }
}

