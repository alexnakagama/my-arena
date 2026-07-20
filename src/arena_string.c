#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arena/arena.h"

char *arena_strndup(arena_t *arena, const char *str, size_t n) {
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

    size_t str_len = 0;

    while (str_len < n && str[str_len] != '\0') {
        str_len++;
    }

    char *str_ptr = arena_alloc(arena, str_len + 1);

    if (!str_ptr) {
#if BT_ARENA_DEBUG
    printf("[ARENA] allocation failed: not enough space in arena\n");
#endif
        return NULL;
    }

#if BT_ARENA_DEBUG
    printf("[ARENA] arena_strndup succeded\n");
#endif

    memcpy(str_ptr, str, str_len);

    str_ptr[str_len] = '\0';

    return str_ptr;
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

#if BT_ARENA_DEBUG
    printf("[ARENA] arena_strdup succeded\n");
#endif

    return arena_strndup(arena, str, strlen(str));
}


