CC = gcc

CFLAGS_DEBUG = -std=c11 -D_POSIX_C_SOURCE=200809L -O0 -g -Wall -Wextra -Wpedantic -Werror
CFLAGS_RELEASE = -std=c11 -D_POSIX_C_SOURCE=200809L -O2 -Wall -Wextra

.PHONY: gen bench run_bench clean

gen: gen_fixture

gen_fixture: gen_fixture.c
	$(CC) $(CFLAGS_DEBUG) gen_fixture.c -o gen_fixture

bench: bench.c
	$(CC) $(CFLAGS_RELEASE) bench.c -o bench

run_bench: gen bench
	./gen_fixture large.txt 1000000 && time ./bench large.txt match

clean:
	rm -f gen_fixture bench large.txt
