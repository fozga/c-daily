#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char*  pattern;        /* owned copy of the pattern string */
    bool   case_insensitive;
} matcher_t;

/* Initializes a matcher. Copies the pattern.
   Returns false on allocation failure. */
bool matcher_init(matcher_t* m, const char* pattern, bool case_insensitive);

/* Frees the pattern copy. */
void matcher_destroy(matcher_t* m);

/* Returns true if the pattern (as a literal substring with `.` wildcard)
   is found anywhere in 'line'. Line must be NUL-terminated. */
bool matcher_match_line(const matcher_t* m, const char* line);
