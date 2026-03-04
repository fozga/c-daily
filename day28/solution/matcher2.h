#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char* pattern;
    bool  case_insensitive;
} matcher2_t;

bool matcher2_init(matcher2_t* m, const char* pattern, bool case_insensitive);
void matcher2_destroy(matcher2_t* m);

/* Matches literal, '.', '[...]', '[^...]', and '\' escapes. */
bool matcher2_match_line(const matcher2_t* m, const char* line);
