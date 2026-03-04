CC = gcc
CFLAGS = -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror
ASAN_FLAGS = -fsanitize=address

TEST_BIN = test_runner
ASAN_BIN = test_runner_asan
APP_BIN = mini-grep

.PHONY: test build asan valgrind clean

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): cli.c tests.c cli.h
	$(CC) $(CFLAGS) cli.c tests.c -o $(TEST_BIN)

build: $(APP_BIN)

$(APP_BIN): cli.c main.c cli.h
	$(CC) $(CFLAGS) cli.c main.c -o $(APP_BIN)

asan: $(ASAN_BIN)
	./$(ASAN_BIN)

$(ASAN_BIN): cli.c tests.c cli.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) cli.c tests.c -o $(ASAN_BIN) $(ASAN_FLAGS)

valgrind: $(TEST_BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN) $(ASAN_BIN) $(APP_BIN) *.o
