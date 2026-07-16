#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "arena/arena.h"

int main(void){
    arena_t *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);

    char *my_str = arena_strdup(arena, "hello");
    assert(my_str != NULL);

    size_t str_length = strlen("hello") + 1;
    assert(arena_used(arena) == str_length);
    assert(arena_available(arena) == 1024 - str_length);

    arena_destroy(arena);

    printf("test_strdup.c PASSED\n");

    return 0;
}
