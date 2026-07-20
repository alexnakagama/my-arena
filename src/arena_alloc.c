#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "arena/arena.h"

/*
 * Allocates memory on the arena
 *
 * @param arena Arena allocator.
 * @param size Number of bytes to allocate.
 *
 * @return pointer to void
*/
void *arena_alloc(arena_t *arena, size_t size) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return NULL;
    }

    if (size > arena->capacity - arena->offset) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: not enough memory (requested: %zu, available: %zu)\n", size, arena->capacity - arena->offset);
#endif
        return NULL;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] allocating %zu bytes\n", size);
#endif

    void *address = (unsigned char *)arena->buffer + arena->offset;

    arena->offset += size;

    return address;
}

/*
 * Allocates memory for an array of 'count' elements, each 'size' bytes
 * and initializes all bytes to zero
 *
 * @param arena Arena allocator
 * @param count Number of elements
 * @param size Size of each element in bytes
 *
 * @return Pointer to the allocated memory or NULL if it fails
*/
void *arena_calloc(arena_t *arena, size_t count, size_t size) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return NULL;
    }

    if (count != 0 && size > SIZE_MAX / count) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: size overflow\n");
#endif
        return NULL;
    }

    size_t total = count * size;

    void *ptr = arena_alloc(arena, total);

    if (!ptr) {
#if BT_ARENA_DEBUG
    printf("[ARENA] failed: pointer is NULL\n");
#endif
        return NULL;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] calloc: allocated and zeroed a total of %zu bytes\n", total);
#endif

    memset(ptr, 0, total);

    return ptr;
}

/*
 * @param size How many bytes you want
 * @param alignment Alignment requirement (1, 2, 4, 8, 16)
 *
 * @return void* Address of the allocated memory
*/
void *arena_alloc_aligned(arena_t *arena, size_t size, size_t alignment) {
    if (!arena || size == 0) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: undefined arguments\n");
#endif
        return NULL;
    }

    if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: alignemnt must be power of two\n");
#endif
        return NULL;
    }
    
    // padding = number of bytes we will skip before allocating
    size_t padding = 0;

    while ((arena->offset + padding) % alignment != 0) {
        padding++;
    }

    if (padding > arena->capacity - arena->offset || 
        size > arena->capacity - arena->offset - padding) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: not enough memory\n");
#endif
        return NULL;
    }

    arena->offset += padding;

    void *ptr = arena->buffer + arena->offset;

    arena->offset += size;

#if BT_ARENA_DEBUG
    printf("[ARENA] allocated %zu bytes with alignment %zu\n", size, alignment);
#endif

    return ptr;
}

