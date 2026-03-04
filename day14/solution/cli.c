#include <stdio.h>
#include <string.h>

#include "cdrills_lib.h"

static void usage(const char* prog) {
    fprintf(stderr, "Usage: %s <command> [args]\n", prog);
    fprintf(stderr, "Commands:\n");
    fprintf(stderr, "  parse <file>   Parse a text record file\n");
    fprintf(stderr, "  store          Interactive key-value demo\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "parse") == 0) {
        if (argc < 3) {
            fprintf(stderr, "parse requires a file path argument\n");
            usage(argv[0]);
            return 1;
        }
        /* TODO: Wire day09 parser module to process argv[2]. */
        fprintf(stderr, "TODO: parse command not implemented yet for file: %s\n", argv[2]);
        return 1;
    }

    if (strcmp(argv[1], "store") == 0) {
        /* TODO: Wire day13 store module interactive demo. */
        fprintf(stderr, "TODO: store command not implemented yet\n");
        return 1;
    }

    fprintf(stderr, "Unknown command: %s\n", argv[1]);
    usage(argv[0]);
    return 1;
}
