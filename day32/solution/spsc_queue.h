#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>

typedef struct {
    int* data;
    size_t capacity;
    _Atomic size_t head; // written by producer, read by consumer
    _Atomic size_t tail; // written by consumer, read by producer
} spsc_queue_t;

void sq_init(spsc_queue_t* q, int* buffer, size_t capacity);

/* Attempts to push a value. Returns false if full. */
bool sq_push(spsc_queue_t* q, int value);

/* Attempts to pop a value. Returns false if empty. */
bool sq_pop(spsc_queue_t* q, int* out_value);
