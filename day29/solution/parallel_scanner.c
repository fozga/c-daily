#include "parallel_scanner.h"

#include <threads.h>
#include <time.h>

typedef struct {
    const char* const* files;
    int files_count;
    int next_index;
    int total_matches;
    mtx_t lock;
} shared_ctx_t;

static int worker_main(void* arg) {
    (void)arg;
    /* TODO: worker loop:
       1) lock and claim next file index
       2) unlock
       3) call scan_file_dummy(file)
       4) lock and add to total_matches
       5) unlock */
    return 0;
}

int scan_file_dummy(const char* filepath) {
    struct timespec tiny = {0, 1000000}; /* 1ms */
    (void)filepath;
    thrd_sleep(&tiny, NULL);
    return 1;
}

int parallel_scan(const char* const* files, int files_count, int num_threads) {
    (void)files;
    (void)files_count;
    (void)num_threads;
    (void)worker_main;
    /* TODO: initialize shared context, create N threads, join threads,
       destroy mutex, and return total match count. */
    return 0;
}
