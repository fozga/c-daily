#pragma once
#include <stdbool.h>
#include <stdio.h>

#include "matcher.h"

typedef struct {
    bool print_filename;   /* prepend filename to output lines */
    bool print_lineno;     /* -n flag: prepend line number */
    const char* filename;  /* label to use in output (NULL for stdin) */
} scan_opts_t;

/* Scans 'fp' line by line, printing lines that match 'm' to stdout.
   Returns the count of matched lines.
   Returns -1 on I/O error. */
int scanner_run(FILE* fp, const matcher_t* m, const scan_opts_t* opts);
