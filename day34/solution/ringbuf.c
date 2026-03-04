#include "ringbuf.h"

void rb_init(ringbuf_t* rb) {
    if (!rb) {
        return;
    }
    rb->head = 0;
    rb->tail = 0;
}

bool rb_is_empty(const ringbuf_t* rb) {
    if (!rb) {
        return true;
    }
    /* TODO: empty when head == tail */
    return rb->head == rb->tail;
}

bool rb_is_full(const ringbuf_t* rb) {
    if (!rb) {
        return false;
    }
    /* TODO: full when (head + 1) % RB_CAPACITY == tail */
    return false;
}

bool rb_push(ringbuf_t* rb, uint8_t data) {
    (void)data;
    if (!rb) {
        return false;
    }
    /* TODO:
     * - check full
     * - write data at buffer[head]
     * - advance head with modulo
     */
    return false;
}

bool rb_pop(ringbuf_t* rb, uint8_t* out_data) {
    if (!rb || !out_data) {
        return false;
    }
    /* TODO:
     * - check empty
     * - read from buffer[tail]
     * - advance tail with modulo
     */
    return false;
}
