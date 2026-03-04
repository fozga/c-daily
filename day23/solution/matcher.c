#include "matcher.h"

#include <stdlib.h>

bool matcher_init(matcher_t* m, const char* pattern, bool case_insensitive) {
    (void)m;
    (void)pattern;
    (void)case_insensitive;
    /* TODO: allocate and copy pattern into matcher-owned storage. */
    return false;
}

void matcher_destroy(matcher_t* m) {
    (void)m;
    /* TODO: free owned pattern and reset matcher state. */
}

bool matcher_match_line(const matcher_t* m, const char* line) {
    (void)m;
    (void)line;
    /* TODO: implement naive substring search with '.' wildcard and optional
       ASCII case-insensitive comparison. */
    return false;
}
