# Day 29 Notes - Parallel scan with C11 threads

## 1) C11 Threads overview

`<threads.h>` is the C11 standard threading API and portable alternative to
raw pthread APIs for common use cases.

Core types/functions:
- `thrd_t`
- `thrd_create`
- `thrd_join`
- `mtx_t`
- `mtx_init`, `mtx_lock`, `mtx_unlock`, `mtx_destroy`

## 2) Thread lifecycle

Typical worker flow:
1. main prepares shared context
2. main creates N threads with same entry function
3. workers process work until queue is exhausted
4. main joins all threads
5. main reads final deterministic aggregate

Always check thread creation return codes and join results.

## 3) Data races and mutex necessity

`count++` is not atomic:
- read old value
- add one
- write new value

Interleaving between threads can drop increments unless synchronized.

Mutex around shared updates ensures mutually exclusive access and prevents
undefined behavior caused by races.

## 4) Work partitioning with shared index

Common pattern:
- lock
- read `next_index`
- increment `next_index`
- unlock
- perform slow work outside lock

This minimizes lock hold time and improves concurrency.

## 5) Deterministic output concerns

Concurrent printing to stdout can interleave fragments unpredictably.
For this drill, we focus only on deterministic aggregate counts, not ordered
line output formatting.

If ordered output is required, use buffering or post-sort merge phase.

## Common mistakes

- Holding lock during file I/O (kills parallel benefit).
- Updating shared index without synchronization.
- Forgetting to join threads before reading final total.
- Reusing local stack context that goes out of scope before threads finish.
- Assuming race conditions are "rare bugs" rather than undefined behavior.

## C vs C++

- C uses `thrd_t` + `mtx_t`; C++ uses `std::thread` + `std::mutex`.
- Patterns are similar, but ergonomics differ (`std::lock_guard`, RAII).
- In C, manual initialization/cleanup discipline is critical.
