CC = gcc
CFLAGS = -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Werror
LDLIBS = -lpthread

TEST_BIN = test_runner
SRCS = spsc_queue.c tests.c

.PHONY: test clean

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(SRCS) spsc_queue.h
	$(CC) $(CFLAGS) $(SRCS) -o $(TEST_BIN) $(LDLIBS)

clean:
	rm -f $(TEST_BIN) *.o
