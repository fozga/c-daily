CC = gcc
AR = ar
CFLAGS = -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror
ASAN_FLAGS = -fsanitize=address

LIB_NAME = libcdrills.a
CLI_BIN = cdrills
TEST_BIN = test_runner
ASAN_BIN = test_runner_asan

# TODO: Replace placeholder sources with actual working module files from earlier days.
# TODO: Example candidates:
# TODO:   ../day09/solution/line_parser.c
# TODO:   ../day10/solution/binrec.c
# TODO:   ../day13/solution/store.c
LIB_SRCS =
LIB_OBJS = $(LIB_SRCS:.c=.o)

.PHONY: lib test cli run asan valgrind clean

lib: $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJS)
	$(AR) rcs $(LIB_NAME) $(LIB_OBJS)

test: lib tests.c
	$(CC) $(CFLAGS) tests.c -L. -lcdrills -o $(TEST_BIN)
	./$(TEST_BIN)

cli: lib cli.c cdrills_lib.h
	$(CC) $(CFLAGS) cli.c -L. -lcdrills -o $(CLI_BIN)

run: cli
	./$(CLI_BIN) store

asan: lib tests.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) tests.c -L. -lcdrills -o $(ASAN_BIN) $(ASAN_FLAGS)
	./$(ASAN_BIN)

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_BIN)

clean:
	rm -f $(CLI_BIN) $(TEST_BIN) $(ASAN_BIN) $(LIB_NAME) *.o
