#include "arena/arena.h"

#include <stddef.h>
#include <stdlib.h>

struct Arena {
    void *buffer;
    size_t capacity;
    size_t offset;
};

Arena *arena_create(size_t size) {
    Arena *arena = malloc(sizeof(Arena));

    return arena;
}
