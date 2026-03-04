# Day 21 Notes - Defensive and testable C

## 1) Defensive programming in C

Two major tools:
- assertions for developer/invariant bugs
- error codes for runtime/environment/input failures

Use assertions when "this should never happen if code is correct".
Use return values when failures are expected and recoverable (e.g., OOM, bad input).

## 2) `assert()` and `NDEBUG`

`assert(cond)` aborts the program with a diagnostic message when `cond` is
false in debug builds. When `NDEBUG` is defined (e.g. with `-DNDEBUG`), the
preprocessor replaces every `assert(...)` with `((void)0)` — the expression
is not evaluated at all.

### Example — side-effect hazard

```c
/* BUG: do_work() is never called in release builds */
assert(do_work() == 0);

/* CORRECT: call is unconditional; assert only checks the return value */
int rc = do_work();
assert(rc == 0);
```

When `NDEBUG` is defined, the first form silently skips `do_work()` entirely,
while the second form still executes `do_work()` (the assert just becomes
`((void)rc)`).

Compiling with assertions disabled: `gcc -DNDEBUG -O2 ...`

## 3) Data structure invariants

An invariant is a condition that must be true for a data structure to be in a
valid state. Violations indicate a programming error (not a runtime condition).

For linked lists, typical invariants:
- `count` equals the number of nodes reachable from `head`
- `head == NULL` iff `count == 0`
- The list is acyclic (no node's `next` points back into the chain)

### Example — invariant checker

```c
void slist_verify_invariants(const slist_t *list) {
    assert(list != NULL);

    size_t traversed = 0;
    const slist_node_t *curr = list->head;
    while (curr != NULL) {
        traversed++;
        /* Safety: bail out rather than loop forever on a cycle */
        assert(traversed <= list->count + 1 && "cycle detected");
        curr = curr->next;
    }

    assert(traversed == list->count && "count mismatch");
    if (list->count == 0) assert(list->head == NULL && "stale head");
}
```

Call `slist_verify_invariants` at the end of every mutating function during
debug builds. Catching corruption at the mutation site pinpoints the real bug;
catching it later (at a read) only reveals the symptom.

## 4) Test seams for fault injection

A seam is an indirection point that lets tests substitute behavior without
modifying production code.

### Example — MALLOC_SEAM

```c
/* seam.h — included by both production code and test harness */
#ifdef TESTING
    /* Test path: use the controllable allocator */
    void *test_malloc(size_t size);
    #define MALLOC_SEAM(sz)  test_malloc(sz)
#else
    /* Production path: direct call */
    #define MALLOC_SEAM(sz)  malloc(sz)
#endif

/* seam.c — test-only implementation */
static int g_fail_at   = -1;   /* -1 = never fail */
static int g_alloc_count = 0;

void test_set_malloc_fail_at(int n) {
    g_fail_at    = n;
    g_alloc_count = 0;
}

void *test_malloc(size_t size) {
    if (g_fail_at >= 0 && g_alloc_count++ == g_fail_at) return NULL;
    return malloc(size);
}
```

Usage in a test:

```c
test_set_malloc_fail_at(0);        /* fail on 1st allocation */
slist_node_t *n = slist_append(&list, 42);
assert(n == NULL);                 /* must handle OOM cleanly */
test_set_malloc_fail_at(-1);       /* restore normal behavior */
```

Always reset the seam state between tests to avoid order-dependent failures.

- production path: `MALLOC_SEAM(size)` expands to `malloc(size)` — no overhead.
- test path: expands to `test_malloc(size)` — controllable failure injection.

## 5) Why fault injection matters

OOM branches are hard to hit naturally but critical for robustness.
Without seam-based tests, code may silently crash/leak on rare allocation failures.

## Common mistakes

- Putting side effects in assertions.
- Treating user input errors as assertion failures.
- Forgetting to run invariant checks after mutating operations.
- Writing OOM tests that depend on global machine memory pressure.
- Not resetting seam state between tests.

## C vs C++

- C++ often uses exceptions/RAII to handle failures and cleanup.
- C APIs typically expose explicit success/failure returns.
- Defensive C requires deliberate contracts and test hooks.
