#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;

Arena *arena_create(size_t size);
void *arena_alloc(Arena *arena, size_t size);
void arena_reset(Arena *arena);
void arena_destroy(Arena *arena);

#endif

/*
 * An arena in C is a custom memory allocator that manages larges blocks of memory and gives smaller pieces of it to the program
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

