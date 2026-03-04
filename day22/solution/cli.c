#include "cli.h"

#include <stdio.h>

void cli_print_usage(const char* prog_name) {
    const char* prog = (prog_name != NULL) ? prog_name : "mini-grep";
    printf("Usage: %s [OPTIONS] PATTERN [FILE...]\n", prog);
    printf("Options:\n");
    printf("  -n    print line numbers in output\n");
    printf("  -i    case-insensitive matching (ASCII only)\n");
    printf("  -h    print this help and exit\n");
}

int cli_parse(int argc, char* const argv[], cli_opts_t* opts) {
    (void)argc;
    (void)argv;
    (void)opts;
    /* TODO: implement option and positional argument parsing.
       Requirements:
       - support -n, -i, -h
       - set pattern and files/files_count
       - unknown option => stderr + exit(2)
       - missing pattern => usage + exit(1)
       - tokens after pattern are files, even if they begin with '-' */
    return 0;
}
