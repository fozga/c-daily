# Day 29 Notes - Parallel scan with C11 threads

## 1) C11 Threads overview

`<threads.h>` is the C11 standard threading API and a portable alternative to
raw pthreads for common use cases.  It ships with GCC/Clang when targeting a
C11 platform; link with `-lpthread` on Linux.

Core types and functions:

| Symbol | Role |
|---|---|
| `thrd_t` | Thread handle |
| `thrd_create(t, fn, arg)` | Launch a thread; returns `thrd_success` |
| `thrd_join(t, &ret)` | Wait for thread, collect return value |
| `mtx_t` | Mutual-exclusion lock |
| `mtx_init(m, type)` | Initialise mutex (`mtx_plain` for simple use) |
| `mtx_lock(m)` / `mtx_unlock(m)` | Acquire / release |
| `mtx_destroy(m)` | Release OS resources |

Always check every return code.  `thrd_create` can return `thrd_nomem` or
`thrd_error` and those paths must not be silently ignored.

## 2) Thread lifecycle

Typical worker flow:

1. `main` prepares a **shared context** (struct on the stack or heap).
2. `main` creates N threads, each receiving a pointer to that context.
3. Workers pull work from a shared queue protected by a mutex.
4. Workers write partial results back through the shared context.
5. `main` **joins** all threads before reading the final aggregate.

Joining is mandatory: a thread not joined is a resource leak, and reading
shared state before join is a data race.

### Example: thread creation with a shared context

```c
#include <threads.h>
#include <stdio.h>

typedef struct {
    const char **files;   /* read-only: array of file paths       */
    int          nfiles;  /* read-only: total file count           */
    int          next;    /* shared: index of next unprocessed file */
    long         total;   /* shared: accumulated match count       */
    mtx_t        mu;      /* guards next + total                   */
} WorkCtx;

static int worker(void *arg) {
    WorkCtx *ctx = arg;
    for (;;) {
        /* --- critical section: claim one file index --- */
        mtx_lock(&ctx->mu);
        if (ctx->next >= ctx->nfiles) {
            mtx_unlock(&ctx->mu);
            break;
        }
        int idx = ctx->next++;
        mtx_unlock(&ctx->mu);
        /* --- slow I/O outside the lock --- */
        long matches = scan_file(ctx->files[idx]);
        /* --- critical section: accumulate result --- */
        mtx_lock(&ctx->mu);
        ctx->total += matches;
        mtx_unlock(&ctx->mu);
    }
    return 0;
}

int main(void) {
    WorkCtx ctx = { .files = ..., .nfiles = N, .next = 0, .total = 0 };
    mtx_init(&ctx.mu, mtx_plain);

    thrd_t threads[4];
    for (int i = 0; i < 4; i++)
        if (thrd_create(&threads[i], worker, &ctx) != thrd_success)
            /* handle failure */;

    for (int i = 0; i < 4; i++)
        thrd_join(threads[i], NULL);

    printf("total matches: %ld\n", ctx.total);
    mtx_destroy(&ctx.mu);
}
```

Key points: file I/O happens *outside* the lock; only the index update and
the result accumulation are inside the critical section.

## 3) Data races and mutex necessity

`count++` is not atomic:

1. load old value from memory
2. add one in a register
3. store new value back

When two threads execute these three steps concurrently, one increment can be
silently lost.  On some CPUs the window is sub-microsecond, which is why races
feel "rare" in testing and then appear in production.

Under C11, a data race on a non-atomic variable is **undefined behaviour**.
The compiler may assume races never happen and optimise accordingly, producing
results that are wrong in ways that cannot be reproduced under a debugger.

Mutex around shared updates ensures mutually exclusive access and provides the
memory-visibility guarantee that makes the updated value visible to other cores.

## 4) Work partitioning with shared index

The pattern in the example above is a dynamic work queue:

```
lock → read next_index → increment next_index → unlock → do slow work
```

Benefits over static partitioning (splitting the file list evenly upfront):

- Files differ in size; static partitioning can leave some threads idle while
  others still scan large files.
- No pre-pass needed to estimate sizes.

The lock hold time is minimal (two integer ops), so threads spend almost no
time waiting and parallelism is close to ideal.

## 5) Deterministic output concerns

Concurrent calls to `printf` on the same `FILE*` can interleave at the byte
level.  For this drill we focus on **deterministic aggregate counts**, not
ordered line-by-line output.

If ordered output is required:

- Collect each worker's lines into a thread-local buffer.
- After joining, merge-sort the buffers by filename and line number.

## 6) Atomics as an alternative (stretch goal)

`<stdatomic.h>` lets you replace the mutex-guarded `total` with:

```c
_Atomic long total;
/* in worker: */
atomic_fetch_add(&ctx->total, matches);
```

`atomic_fetch_add` is a single CPU instruction on x86; it removes the second
lock/unlock pair.  The index, however, still needs a mutex (or a compare-and-
swap loop) because it is a read-modify-check-write triplet.

## Common mistakes

- Holding the lock during file I/O (serialises all workers; kills the parallel
  benefit entirely).
- Updating the shared index without any synchronisation.
- Forgetting to join all threads before reading the final total.
- Passing a pointer to a loop variable that goes out of scope while the thread
  is still running.
- Treating data-race bugs as "intermittent" — they are undefined behaviour and
  can be exploited by the optimiser in unexpected ways.
- Calling `mtx_destroy` before all threads have been joined.

## C vs C++

| Aspect | C (`<threads.h>`) | C++ (`<thread>`, `<mutex>`) |
|---|---|---|
| Thread type | `thrd_t` | `std::thread` |
| Mutex type | `mtx_t` | `std::mutex` |
| Lock safety | manual lock/unlock | `std::lock_guard` (RAII) |
| Atomic counter | `_Atomic long` / `atomic_fetch_add` | `std::atomic<long>` |
| Join | `thrd_join` | `.join()` or `.detach()` |

In C, forgetting to call `mtx_unlock` (e.g., on an early-return path) is a
silent deadlock.  C++ RAII guards make this class of bug impossible.  Always
apply the C equivalent: a single return point, or a `goto cleanup` pattern.
