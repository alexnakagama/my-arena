#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;

Arena *arena_create(size_t size);
void *arena_alloc(Arena *arena, size_t size);
void arena_destroy(Arena *arena);

#endif
