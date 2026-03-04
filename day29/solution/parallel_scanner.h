#pragma once
#include <stdbool.h>

/* Simulates scanning a single file.
   Returns the number of matches found (dummy logic for testing). */
int scan_file_dummy(const char* filepath);

/* Spawns 'num_threads' to process 'files_count' files from the 'files' array.
   Returns the total number of matches found across all files. */
int parallel_scan(const char* const* files, int files_count, int num_threads);
