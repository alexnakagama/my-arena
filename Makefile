CC = clang

CFLAGS = -std=c11 \
          -Wall \
          -Wextra \
          -Wpedantic \
          -Werror \
          -g \
          -O0 \
          -Iinclude

LIB_SRC = src/arena.c

EXAMPLE_SRC = examples/basic.c
TEST_CREATE_SRC = tests/test_create.c

EXAMPLE = build/examples/basic
TEST_CREATE = build/tests/test_create

all: example

example: $(EXAMPLE)

$(EXAMPLE):
	mkdir -p build/examples
	$(CC) $(CFLAGS) $(LIB_SRC) $(EXAMPLE_SRC) -o $(EXAMPLE)

test: $(TEST_CREATE)
	./$(TEST_CREATE)

$(TEST_CREATE):
	mkdir -p build/tests
	$(CC) $(CFLAGS) $(LIB_SRC) $(TEST_CREATE_SRC) -o $(TEST_CREATE)

clean:
	rm -rf build
