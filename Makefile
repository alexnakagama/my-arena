CC = clang

CFLAGS = -std=c11 \
          -Wall \
          -Wextra \
          -Wpedantic \
          -Werror \
          -g \
          -O0 \
          -Iinclude

LIB_SRC = $(wildcard src/*.c)

EXAMPLE_SRC = examples/basic.c
EXAMPLE = build/examples/basic

TEST_SRCS = $(wildcard tests/*.c)

TESTS = $(patsubst tests/%.c,build/tests/%,$(TEST_SRCS))

all: example

example: $(EXAMPLE)

$(EXAMPLE):
	mkdir -p build/examples
	$(CC) $(CFLAGS) $(LIB_SRC) $(EXAMPLE_SRC) -o $@

build/tests/%: tests/%.c
	mkdir -p build/tests
	$(CC) $(CFLAGS) $(LIB_SRC) $< -o $@

test: $(TESTS)
	@for test in $(TESTS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

clean:
	rm -rf build
