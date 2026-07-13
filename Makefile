CC = clang

CFLAGS = -std=c11 \
         -Wall \
         -Wextra \
         -Wpedantic \
         -Werror \
         -g \
         -O0 \
         -Iinclude

TARGET = build/basic

SRC = src/arena.c examples/basic.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
