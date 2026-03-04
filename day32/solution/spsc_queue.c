#include "spsc_queue.h"

#include <stdatomic.h>

void sq_init(spsc_queue_t* q, int* buffer, size_t capacity) {
    if (!q) {
        return;
    }

    q->data = buffer;
    q->capacity = capacity;
    atomic_store(&q->head, 0U);
    atomic_store(&q->tail, 0U);
}

bool sq_push(spsc_queue_t* q, int value) {
    (void)q;
    (void)value;
    /* TODO:
     * 1) load head and tail atomically
     * 2) compute next_head = (head + 1) % capacity
     * 3) if next_head == tail => full, return false
     * 4) store payload into data[head]
     * 5) atomic_store new head
     */
    return false;
}

bool sq_pop(spsc_queue_t* q, int* out_value) {
    (void)q;
    (void)out_value;
    /* TODO:
     * 1) load head and tail atomically
     * 2) if head == tail => empty, return false
     * 3) read payload from data[tail] into *out_value
     * 4) advance tail with modulo and atomic_store
     */
    return false;
}
