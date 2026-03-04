#pragma once
#include <stdbool.h>
#include <stdint.h>

#define RB_CAPACITY 16

typedef struct {
    uint8_t buffer[RB_CAPACITY];
    int head; // Write index
    int tail; // Read index
} ringbuf_t;

void rb_init(ringbuf_t* rb);
bool rb_is_empty(const ringbuf_t* rb);
bool rb_is_full(const ringbuf_t* rb);

/* Pushes a byte. Returns false if full. */
bool rb_push(ringbuf_t* rb, uint8_t data);

/* Pops a byte. Returns false if empty. */
bool rb_pop(ringbuf_t* rb, uint8_t* out_data);
