#include "spsc_queue.h"

#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <threads.h>

enum {
    QUEUE_CAPACITY = 1024,
    TOTAL_ITEMS = 100000
};

typedef struct {
    spsc_queue_t* q;
    atomic_int* error_flag;
} thread_ctx_t;

static int producer_main(void* arg) {
    thread_ctx_t* ctx = (thread_ctx_t*)arg;

    for (int value = 1; value <= TOTAL_ITEMS; ++value) {
        while (!sq_push(ctx->q, value)) {
            if (atomic_load(ctx->error_flag) != 0) {
                return 1;
            }
            thrd_yield();
        }
    }

    return 0;
}

static int consumer_main(void* arg) {
    thread_ctx_t* ctx = (thread_ctx_t*)arg;
    int expected = 1;

    while (expected <= TOTAL_ITEMS) {
        int got = 0;
        if (!sq_pop(ctx->q, &got)) {
            thrd_yield();
            continue;
        }

        if (got != expected) {
            atomic_store(ctx->error_flag, 1);
            return 1;
        }
        expected++;
    }

    return 0;
}

int main(void) {
    int backing[QUEUE_CAPACITY];
    spsc_queue_t q;
    atomic_int error_flag;
    thrd_t producer;
    thrd_t consumer;
    int prod_rc = 0;
    int cons_rc = 0;

    atomic_init(&error_flag, 0);
    sq_init(&q, backing, QUEUE_CAPACITY);

    thread_ctx_t ctx = { .q = &q, .error_flag = &error_flag };

    if (thrd_create(&producer, producer_main, &ctx) != thrd_success) {
        fprintf(stderr, "failed to create producer thread\n");
        return 1;
    }

    if (thrd_create(&consumer, consumer_main, &ctx) != thrd_success) {
        fprintf(stderr, "failed to create consumer thread\n");
        return 1;
    }

    if (thrd_join(producer, &prod_rc) != thrd_success) {
        fprintf(stderr, "failed to join producer thread\n");
        return 1;
    }

    if (thrd_join(consumer, &cons_rc) != thrd_success) {
        fprintf(stderr, "failed to join consumer thread\n");
        return 1;
    }

    if (prod_rc != 0 || cons_rc != 0 || atomic_load(&error_flag) != 0) {
        fprintf(stderr, "SPSC validation failed\n");
        return 1;
    }

    printf("SPSC threaded test passed\n");
    return 0;
}
