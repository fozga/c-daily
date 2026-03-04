#pragma once
#include <stddef.h>

/* Allocates a string of length 'len', fills it with 'A', and NUL-terminates it. */
char* make_string_of_As(size_t len);

/* Modifies the string in-place by replacing 'target' with 'replacement'.
   Returns the number of replacements made. */
int replace_chars(char* str, char target, char replacement);

/* Returns a pointer to a formatted greeting string for the given name.
   The caller does not need to free the returned pointer (hint: static/stack issue). */
const char* get_greeting(const char* name);
