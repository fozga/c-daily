#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} dyn_string_t;

/* Initializes the dynamic string with an initial capacity.
   Allocates memory for 'data'. The string starts empty (length = 0).
   Always guarantees space for a NUL terminator within 'capacity'.
   Returns true on success, false if allocation fails. */
bool dstr_init(dyn_string_t* ds, size_t initial_capacity);

/* Frees the underlying memory and resets length/capacity to 0.
   Safe to call on an already destroyed or zero-initialized dyn_string_t. */
void dstr_destroy(dyn_string_t* ds);

/* Appends a single character to the string.
   Grows the underlying buffer via realloc if necessary.
   Returns true on success, false if allocation fails. */
bool dstr_append_char(dyn_string_t* ds, char c);

/* Appends a NUL-terminated C-string to the dynamic string.
   Grows the underlying buffer if necessary.
   Returns true on success, false if allocation fails. */
bool dstr_append_str(dyn_string_t* ds, const char* str);

/* Returns a pointer to the NUL-terminated string data.
   The returned pointer is valid ONLY until the next append or destroy operation.
   The caller MUST NOT free the returned pointer. */
const char* dstr_get_cstr(const dyn_string_t* ds);
