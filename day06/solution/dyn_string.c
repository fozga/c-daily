#include "dyn_string.h"

#include <stddef.h>
#include <stdlib.h>

bool dstr_init(dyn_string_t* ds, size_t initial_capacity) {
    // TODO: Use malloc and check for NULL. Ensure space for terminator.
    (void)ds;
    (void)initial_capacity;
    return false;
}

void dstr_destroy(dyn_string_t* ds) {
    // TODO: Free owned memory and reset fields safely.
    (void)ds;
}

bool dstr_append_char(dyn_string_t* ds, char c) {
    // TODO: Grow with realloc when needed and keep data NUL-terminated.
    (void)ds;
    (void)c;
    return false;
}

bool dstr_append_str(dyn_string_t* ds, const char* str) {
    // TODO: Append full C-string content and preserve invariants.
    (void)ds;
    (void)str;
    return false;
}

const char* dstr_get_cstr(const dyn_string_t* ds) {
    // TODO: Return internal borrowed pointer.
    (void)ds;
    return NULL;
}
