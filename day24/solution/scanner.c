#include "scanner.h"

#include <stdio.h>
#include <string.h>

#include "matcher.h"

int scanner_run(FILE* fp, const matcher_t* m, const scan_opts_t* opts) {
    (void)fp;
    (void)m;
    (void)opts;
    /* TODO: read lines with fgets(), strip trailing newline, run matcher_match_line,
       print formatted output with optional filename/line number prefixes.
       Return match count, or -1 on I/O error. */
    return -1;
}
