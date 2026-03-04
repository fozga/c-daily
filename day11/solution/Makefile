CC = gcc
CFLAGS = -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror
ASAN_FLAGS = -fsanitize=address

TEST_BIN = test_runner
ASAN_BIN = test_runner_asan
SRCS = safe_ops.c tests.c

.PHONY: test asan valgrind clean

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(SRCS) safe_ops.h macros.h
	$(CC) $(CFLAGS) $(SRCS) -o $(TEST_BIN)

asan: $(ASAN_BIN)
	./$(ASAN_BIN)

$(ASAN_BIN): $(SRCS) safe_ops.h macros.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(SRCS) -o $(ASAN_BIN) $(ASAN_FLAGS)

valgrind: $(TEST_BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN) $(ASAN_BIN) *.o
