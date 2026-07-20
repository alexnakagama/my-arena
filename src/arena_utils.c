#include <stdio.h>
#include "arena/arena.h"

/*
 * It shows how much the arena is used
 *
 * @param arena Arena allocator
 *
 * @return size_t
*/
size_t arena_used(const arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return 0;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] arena_used succeded\n");
#endif

    return arena->offset;
}

/*
 * Shows how much bytes left are available on the arena
 *
 * @param arena Arena allocator 
 *
 * @return size_t
*/
size_t arena_available(const arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return 0;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] arena_available succeded\n");
#endif

    return arena->capacity - arena->offset;
}

/*
 * Shows the arena capacity
 *
 * @param arena Arena allocator 
 *
 * @return size_t
*/
size_t arena_capacity(const arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return 0;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] arena_capacity succeded\n");
#endif

    return arena->capacity;
}

/*
 * Checks whether the arena contains no allocated data.
 *
 * @param arena Arena allocator.
 *
 * @return true if the arena is empty, false otherwise.
 */
bool arena_is_empty(const arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return false;
    }

    if (arena->offset != 0) {
#if BT_ARENA_DEBUG
    printf("[ARENA] arena is empty\n");
#endif
        return false;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] is not empty\n");
#endif

    return true;
}

