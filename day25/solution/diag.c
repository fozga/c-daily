#include "diag.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

FILE* diag_open_file(const char* prog_name, const char* path) {
    (void)prog_name;
    (void)path;
    /* TODO: call fopen(path, "r"), and on failure print:
       "<prog_name>: <path>: <strerror(errno)>" to stderr. */
    return NULL;
}

int diag_exit_code(int matched_count, int error_count) {
    (void)matched_count;
    (void)error_count;
    /* TODO: implement mapping:
       0 -> matches>0 and errors==0
       1 -> matches==0 or errors>0
       2 -> errors>0 and matches==0 */
    return 0;
}
