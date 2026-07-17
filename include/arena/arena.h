#ifndef BT_ARENA_H
#define BT_ARENA_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef BT_ARENA_DEBUG
#define BT_ARENA_DEBUG 0
#endif 

#ifndef BT_ARENA_MALLOC
#define BT_ARENA_MALLOC malloc
#endif

#ifndef BT_ARENA_FREE
#define BT_ARENA_FREE free
#endif

typedef struct arena_t arena_t;

arena_t *arena_create(size_t size);
void *arena_alloc(arena_t *arena, size_t size);
void arena_reset(arena_t *arena);
void arena_destroy(arena_t *arena);
void *arena_calloc(arena_t *arena, size_t count, size_t size);

size_t arena_used(const arena_t *arena);
size_t arena_available(const arena_t *arena);
size_t arena_capacity(const arena_t *arena);

void arena_info(const arena_t *arena);
void arena_dump(const arena_t *arena);

char *arena_strdup(arena_t *arena, const char *str);

bool arena_is_empty(const arena_t *arena);

#endif

/*
 * An arena in C is a custom memory allocator that manages larges blocks of memory and gives smaller pieces of it to the program
 * It doesnt frees individual objects, it all stays there until the arena is destroyed or reset
 *
 * How it works internally?
 * Memory looks internally:
 *
 * Arena buffer
    +------------------------------------------------+
    | used | used | used |        free space         |
    +------------------------------------------------+
                        ^
                      offset
 *
 * When we request memory it returns buffer + offset, the offset goes moving
 * Its pointer aritmetic
 * Arena is like renting the whole building, using rooms when needed, demolishing building when its done
*/ 

