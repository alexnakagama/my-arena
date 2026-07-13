# Arena Allocator

A simple and lightweight arena allocator written in C.

An arena allocator is a custom memory allocator that manages a large block of memory and provides fast sequential allocations from that block. Instead of allocating and freeing each object individually, memory is released all at once when the arena is destroyed or reset.

## Features

- Fast sequential memory allocation
- Single allocation / single cleanup model
- No individual `free()` calls required
- Support for zero-initialized allocations (`arena_calloc`)
- Memory usage statistics
- Raw memory inspection with arena dump
- Opaque API design
- Written in standard C11

## How It Works

The arena reserves a large chunk of memory:

```
+--------------------------------+
|                                |
|          Arena Buffer          |
|                                |
+--------------------------------+
```

Allocations consume memory sequentially by moving an internal offset:

```
Before:

+--------------------------------+
|            Free                |
+--------------------------------+
^

offset = 0


After allocating 32 bytes:

+----------------+---------------+
|  32 bytes used |     Free      |
+----------------+---------------+
                 ^

              offset = 32
```

The arena does not know what type of data is stored. It only manages raw memory. The user decides how to interpret the allocated memory.

## Example Usage

```c
#include "arena/arena.h"

int main(void)
{
    arena_t *arena = arena_create(1024);

    int *number = arena_alloc(arena, sizeof(int));

    *number = 42;

    printf("%d\n", *number);

    arena_info(arena);

    arena_destroy(arena);

    return 0;
}
```

Output:

```
42

--- Arena ---
Capacity: 1024
Used: 4
Available: 1020
```

## API

### Create an Arena

```c
arena_t *arena_create(size_t size);
```

Creates an arena with the given capacity.

---

### Allocate Memory

```c
void *arena_alloc(arena_t *arena, size_t size);
```

Allocates a block of memory from the arena.

Example:

```c
int *value = arena_alloc(arena, sizeof(int));
```

---

### Allocate Zeroed Memory

```c
void *arena_calloc(arena_t *arena, size_t count, size_t size);
```

Allocates memory and initializes it to zero.

Example:

```c
int *numbers = arena_calloc(arena, 10, sizeof(int));
```

---

### Reset Arena

```c
void arena_clear(arena_t *arena);
```

Resets the arena by moving the offset back to zero.

Previously allocated memory becomes available again.

---

### Destroy Arena

```c
void arena_destroy(arena_t *arena);
```

Releases all memory owned by the arena.

---

### Debug Information

```c
void arena_info(const arena_t *arena);
```

Prints arena statistics.

```c
void arena_dump(const arena_t *arena);
```

Prints the raw bytes stored inside the arena.

## Project Structure

```
arena-allocator/
│
├── include/
│   └── arena/
│       └── arena.h
│
├── src/
│   └── arena.c
│
├── examples/
│   └── main.c
│
├── tests/
│
├── Makefile
└── README.md
```

## Build

Compile the project:

```bash
make
```

Run the example:

```bash
./build/examples/main
```

## Design Goals

This project was built to explore:

- Manual memory management in C
- Pointers and pointer arithmetic
- Memory layout
- Allocation strategies
- Writing reusable C libraries
- Low-level debugging

## Future Improvements

- Memory alignment support
- Arena markers and rewinding
- Allocation statistics
- Debug allocation tracking
- Bounds checking
- Unit tests
- Thread-safe variants

