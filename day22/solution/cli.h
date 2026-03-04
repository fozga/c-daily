#pragma once
#include <stdbool.h>

typedef struct {
    bool        flag_n;         /* -n: print line numbers */
    bool        flag_i;         /* -i: case-insensitive */
    const char* pattern;        /* required positional argument */
    const char* const* files;   /* pointer to first FILE in argv; count in files_count */
    int         files_count;    /* 0 means read from stdin */
} cli_opts_t;

/* Parses argc/argv into opts.
   On success returns 0.
   On -h: prints usage to stdout and exits with 0.
   On bad args: prints error to stderr and exits with 2.
   Caller must not free opts — it holds pointers into argv directly. */
int cli_parse(int argc, char* const argv[], cli_opts_t* opts);

/* Prints usage to the given FILE stream. */
void cli_print_usage(const char* prog_name);
