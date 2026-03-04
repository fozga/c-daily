#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* words[] = {
    "alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel",
    "india", "juliet", "kilo", "lima", "mango", "nectar", "omega", "pixel",
    "query", "rocket", "sigma", "tango", "ultra", "vector", "whiskey", "xray",
    "yankee", "zulu", "binary", "kernel", "buffer", "stream"
};

static size_t rand_in_range(size_t lo, size_t hi) {
    if (hi <= lo) {
        return lo;
    }
    return lo + (size_t)(rand() % (int)(hi - lo + 1u));
}

int main(int argc, char* argv[]) {
    const char* out_path = NULL;
    long count = 0;
    FILE* fp = NULL;
    long i = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <output-file> <line-count>\n", argv[0]);
        return 2;
    }

    out_path = argv[1];
    count = strtol(argv[2], NULL, 10);
    if (count <= 0) {
        fprintf(stderr, "line-count must be > 0\n");
        return 2;
    }

    fp = fopen(out_path, "w");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open '%s': %s\n", out_path, strerror(errno));
        return 1;
    }

    srand(12345u);

    for (i = 0; i < count; ++i) {
        size_t target_len = rand_in_range(10u, 80u);
        size_t cur_len = 0;
        int include_match = ((i % 10) == 0); /* roughly 10% */

        while (cur_len < target_len) {
            const char* w = words[rand() % (int)(sizeof(words) / sizeof(words[0]))];
            size_t wl = strlen(w);
            if (cur_len + wl + 1u > target_len) {
                break;
            }
            if (cur_len > 0) {
                fputc(' ', fp);
                ++cur_len;
            }
            fputs(w, fp);
            cur_len += wl;
        }

        if (include_match) {
            fputs(" match", fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
    printf("Generated %ld lines into %s\n", count, out_path);
    return 0;
}
