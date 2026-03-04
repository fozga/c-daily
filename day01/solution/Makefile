CC := gcc

STD := -std=c11
WARN := -Wall -Wextra -Wpedantic -Werror
DEBUG := -O0 -g
ASAN := -fsanitize=address

CFLAGS := $(STD) $(WARN) $(DEBUG)
LDFLAGS :=

SRCS := $(wildcard *.c)
BIN := app

.PHONY: all test asan valgrind clean

all: test

test:
ifeq ($(strip $(SRCS)),)
	@echo "No .c files found. Add your solution first."
else
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS)
	./$(BIN)
endif

asan:
ifeq ($(strip $(SRCS)),)
	@echo "No .c files found. Add your solution first."
else
	$(CC) $(CFLAGS) $(ASAN) $(SRCS) -o $(BIN)-asan $(LDFLAGS) $(ASAN)
	./$(BIN)-asan
endif

valgrind:
ifeq ($(strip $(SRCS)),)
	@echo "No .c files found. Add your solution first."
else
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(BIN)
endif

clean:
	rm -f $(BIN) $(BIN)-asan *.o
