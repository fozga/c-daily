#include "buffer.h"

int buf_init(buffer_t* buf, const uint8_t* data, size_t capacity) {
    // TODO: Validate pointers and initialize parser state.
    (void)buf;
    (void)data;
    (void)capacity;
    return -1;
}

int buf_read_byte(buffer_t* buf, uint8_t* out) {
    // TODO: Check bounds and update cursor.
    (void)buf;
    (void)out;
    return -1;
}

int buf_read_bytes(buffer_t* buf, size_t n, uint8_t* out_arr) {
    // TODO: Validate remaining capacity before reading n bytes.
    (void)buf;
    (void)n;
    (void)out_arr;
    return -1;
}

size_t buf_remaining(const buffer_t* buf) {
    // TODO: Return remaining bytes safely.
    (void)buf;
    return 0;
}

int buf_peek(const buffer_t* buf, uint8_t* out) {
    // TODO: Check bounds without moving cursor.
    (void)buf;
    (void)out;
    return -1;
}
