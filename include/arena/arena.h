#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct arena_t arena_t;

arena_t *arena_create(size_t size);
void *arena_alloc(arena_t *arena, size_t size);
void arena_clear(arena_t *arena);
void arena_destroy(arena_t *arena);

size_t arena_used(const arena_t *arena);
size_t arena_available(const arena_t *arena);
size_t arena_capacity(const arena_t *arena);
void arena_print(const arena_t *arena);

void *arena_calloc(arena_t *arena, size_t size);

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

