#include "arena/arena.h"
#include <stddef.h>

struct Arena {
    void *buffer;
    size_t capacity;
    size_t offset;
};
