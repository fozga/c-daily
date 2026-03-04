#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int contains_literal(const char* line, const char* pat) {
    size_t n = strlen(line);
    size_t m = strlen(pat);
    size_t i = 0;
    size_t j = 0;

    if (m == 0) {
        return 1;
    }
    if (m > n) {
        return 0;
    }

    for (i = 0; i + m <= n; ++i) {
        for (j = 0; j < m; ++j) {
            if (line[i + j] != pat[j]) {
                break;
            }
        }
        if (j == m) {
            return 1;
        }
    }
    return 0;
}

static double elapsed_ms(const struct timespec* a, const struct timespec* b) {
    double sec = (double)(b->tv_sec - a->tv_sec);
    double nsec = (double)(b->tv_nsec - a->tv_nsec);
    return sec * 1000.0 + nsec / 1000000.0;
}

int main(int argc, char* argv[]) {
    const char* filename = NULL;
    const char* pattern = NULL;
    FILE* fp = NULL;
    char buf[4096];
    long total_lines = 0;
    long matches = 0;
    struct timespec t0;
    struct timespec t1;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <pattern>\n", argv[0]);
        return 2;
    }

    filename = argv[1];
    pattern = argv[2];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open '%s': %s\n", filename, strerror(errno));
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &t0) != 0) {
        fprintf(stderr, "clock_gettime(start) failed\n");
        fclose(fp);
        return 1;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        size_t len = strlen(buf);
        ++total_lines;
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
        if (contains_literal(buf, pattern)) {
            ++matches;
        }
    }

    if (ferror(fp)) {
        fprintf(stderr, "Read error while scanning '%s'\n", filename);
        fclose(fp);
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &t1) != 0) {
        fprintf(stderr, "clock_gettime(end) failed\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    printf("Total lines: %ld\n", total_lines);
    printf("Matches: %ld\n", matches);
    printf("Elapsed: %.3f ms\n", elapsed_ms(&t0, &t1));
    return 0;
}
