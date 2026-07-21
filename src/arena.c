// if you want debug mode type:
//#define BT_ARENA_DEBUG 1

#include <stdio.h>
#include <stdlib.h>

#include "arena/arena.h"

/*
 * Creates a new arena
 * 
 * @param size Number of bytes to reserve.
 *
 * @return pointer to the arena, or NULL if it fails.
*/ 
arena_t *arena_create(size_t size) {
    arena_t *arena = BT_ARENA_MALLOC(sizeof(arena_t));

    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return NULL;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] creating arena with %zu bytes\n", size);
#endif

    arena->buffer = BT_ARENA_MALLOC(size);

    if (!arena->buffer) {
#if BT_ARENA_DEBUG
    printf("[ARENA] buffer allocation failed: buffer is NULL\n");
#endif
        BT_ARENA_FREE(arena);
        return NULL;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] arena creating\n");
#endif

    arena->capacity = size;
    arena->offset = 0;

    return arena;
}

/*
 * Resets the arena.
 *
 * @param arena Arena allocator
 *
 * @return void
*/
void arena_reset(arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] resetting\n");
#endif

    arena->offset = 0;
}

/*
 * Destroys the arena
 *
 * @param arena Arena allocator
 *
 * @return void
*/
void arena_destroy(arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] destroyed arena: used=%zu/%zu bytes\n", arena->offset, arena->capacity);
#endif

    BT_ARENA_FREE(arena->buffer);
    BT_ARENA_FREE(arena);
}

