CC = gcc
CFLAGS = -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror

BIN = mini-grep

# TODO: adjust source paths below to your integrated day22-25 implementation files.
# Example integration set:
#   ../day22/solution/main.c ../day22/solution/cli.c
#   ../day23/solution/matcher.c
#   ../day24/solution/scanner.c
#   ../day25/solution/diag.c
SRC_PATHS = \
	../../day22/solution/main.c \
	../../day22/solution/cli.c

.PHONY: build test clean

build: $(BIN)

$(BIN):
	$(CC) $(CFLAGS) $(SRC_PATHS) -o $(BIN)

test: $(BIN) test_matrix.sh
	bash test_matrix.sh ./$(BIN)

clean:
	rm -f $(BIN)
