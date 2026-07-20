#include <stdio.h>
#include "arena/arena.h"

/*
 * Prints the arena information
 *
 * @param arena Arena allocator, const because it state doesnt change
 *
 * @return void
*/
void arena_info(const arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return;
    }

    size_t available = arena->capacity - arena->offset;
    double usage = ((double)arena->offset / arena->capacity) * 100.0;

#if BT_ARENA_DEBUG
    printf("[ARENA] arena_info printing\n");
#endif

    printf("---Arena---\n");
    printf("Buffer: %p\n", arena->buffer);
    printf("Used: %zu bytes\n", arena->offset);
    printf("Capacity: %zu bytes\n", arena->capacity);
    printf("Available: %zu bytes\n", available);
    printf("Usage: %.2f%%\n", usage);
}

/*
 * Prints the content of the used portion of the arena as hexadecimal bytes
 *
 * @param arena Arena allocator
 *
 * @return void
*/
void arena_dump(const arena_t *arena) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return;
    }

    unsigned char *buffer = arena->buffer;

#if BT_ARENA_DEBUG
    printf("[ARENA] arena dump succeded\n");
#endif

    for (size_t i = 0; i < arena->offset; i++) {
        printf("%02x\n", buffer[i]);
    }
}


