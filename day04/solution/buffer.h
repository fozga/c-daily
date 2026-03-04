#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct {
    const uint8_t* data;
    size_t capacity;
    size_t cursor; // current read position
} buffer_t;

/* Initializes the buffer state.
   Returns 0 on success, -1 if buf or data is NULL. */
int buf_init(buffer_t* buf, const uint8_t* data, size_t capacity);

/* Reads a single byte and advances the cursor.
   Stores the byte in *out.
   Returns 0 on success, -1 if buf is NULL, out is NULL, or cursor is at capacity. */
int buf_read_byte(buffer_t* buf, uint8_t* out);

/* Reads 'n' bytes into 'out_arr' and advances the cursor by 'n'.
   Returns 0 on success.
   Returns -1 if any pointer is NULL, or if there are less than 'n' bytes remaining. */
int buf_read_bytes(buffer_t* buf, size_t n, uint8_t* out_arr);

/* Returns the number of bytes remaining to be read.
   Returns 0 if buf is NULL. */
size_t buf_remaining(const buffer_t* buf);

/* Peeks at the next byte without advancing the cursor.
   Stores the byte in *out.
   Returns 0 on success, -1 if buf/out is NULL or no bytes remain. */
int buf_peek(const buffer_t* buf, uint8_t* out);
