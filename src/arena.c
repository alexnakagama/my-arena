#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arena/arena.h"

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

    arena->capacity = size;
    arena->offset = 0;

    return arena;
}

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

    return arena->capacity;
}

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

    printf("---Arena---\n");
    printf("Buffer: %p\n", arena->buffer);
    printf("Used: %zu bytes\n", arena->offset);
    printf("Capacity: %zu bytes\n", arena->capacity);
    printf("Available: %zu bytes\n", available);
    printf("Usage: %.2f%%\n", usage);
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

    size_t total = count * size;

    void *ptr = arena_alloc(arena, total);
    if (!ptr) {
        return NULL;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] calloc a total of %zu bytes\n", total);
#endif

    memset(ptr, 0, total);

    return ptr;
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

    for (size_t i = 0; i < arena->offset; i++) {
        printf("%02x\n", buffer[i]);
    }
}

/*
 * Duplicates a null terminated string into the arena
 * 
 * Allocates enough memory to store the string including the null terminator
 * Copies the conent into the arena, and returns a pointer to the dup string
 *
 * @param arena Arena allocator
 * @param str Null-terminated string to duplicate
 *
 * @return Pointer to the dup string, or NULL if arena is NULL, the input string is NULL, or allocation fails
*/
char *arena_strdup(arena_t *arena, const char *str) {
    if (!arena) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: arena is NULL\n");
#endif
        return NULL;
    }

    if (!str) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: string literal is NULL\n");
#endif
        return NULL;
    }
    
    size_t str_len = strlen(str) + 1;

    char *str_ptr = arena_alloc(arena, str_len);
    if (!str_ptr) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation to allocate %zu bytes for string\n", str_len);
#endif
        return NULL;
    }

    memcpy(str_ptr, str, str_len);

    return str_ptr;
}

