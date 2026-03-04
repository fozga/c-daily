#pragma once
#include <stdbool.h>
#include <stdio.h>

/* Opens 'path' for reading. On failure, prints a formatted error to stderr:
   "<prog_name>: <path>: <strerror(errno)>" and returns NULL. */
FILE* diag_open_file(const char* prog_name, const char* path);

/* Determines the correct exit code based on scan results:
   matched_count: total lines matched across all files.
   error_count:   number of files that failed to open.
   Returns: 0 if matches>0 and errors==0.
            1 if matches==0 or errors>0.
            2 if error_count>0 and matched_count==0. */
int diag_exit_code(int matched_count, int error_count);
