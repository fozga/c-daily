# Day 07 Notes - API Contracts and Error Models in C

This day focuses on designing C APIs that fail clearly and consistently. Good error contracts are part of API design, not an afterthought.

## 1) Error handling in C vs C++

C does not provide language-level exceptions. Most C APIs communicate failure through:

- return status codes
- output parameters
- optional `errno` values for more detail

In C++, exceptions and RAII can propagate errors and unwind resources automatically (if designed that way). In C, caller and callee must both perform explicit checks and cleanup.

### Example

```c
int parse_port(const char* s, int* out_port) {
    if (s == NULL || out_port == NULL) {
        return -1;
    }
    /* parse... */
    return 0;
}
```

### Common mistakes

- Ignoring return codes and using out-parameters anyway.
- Mixing styles (sometimes return value is data, sometimes status) without documentation.
- Assuming downstream callers will "just know" how failures are encoded.

> **C vs C++:** C++ may use exceptions or `std::expected`-style APIs; C usually relies on explicit status checks after each call.

## 2) The `<errno.h>` mechanism

`errno` is a thread-local integer used by many libc/POSIX functions to provide additional error detail. It is meaningful only when a function indicates failure.

For conversions like `strtol`, clear `errno = 0` before the call, then inspect both return value and `errno` after call.

### Example

```c
#include <errno.h>
#include <stdlib.h>

errno = 0;
char* end = NULL;
long v = strtol(s, &end, 10);
if (errno == ERANGE) {
    /* out of representable range */
}
```

### Common mistakes

- Reading stale `errno` from an earlier failure.
- Checking `errno` when the function did not report failure.
- Forgetting that successful calls do not always reset `errno` to 0.

> **C vs C++:** `errno`-based signaling is uncommon in modern C++ application code, where exceptions or typed result objects are often preferred.

## 3) Out-parameters vs return codes

A common C pattern:

- return status (`0`/enum/int)
- place actual parsed value in `*out`

This avoids ambiguous return values (for example, parsed `0` vs error `0`) and makes error propagation explicit.

### Example

```c
typedef enum { PARSE_OK = 0, PARSE_ERR = -1 } parse_err_t;

parse_err_t parse_count(const char* s, int* out_count);
```

### Common mistakes

- Writing to out-parameter on failure, creating partial/garbage state.
- Not validating `out` pointer before dereference.
- Returning success while leaving out-value uninitialized.

> **C vs C++:** C++ can return richer value objects directly; C typically separates status and payload through out-parameters.

## 4) Enums for custom error codes

Enums provide a typed, self-documenting error domain:

- easier to read than raw numeric literals
- easier to map to diagnostics
- can coexist with `errno` for system-level detail

### Example

```c
typedef enum {
    PARSE_OK = 0,
    PARSE_ERR_NULL_PTR = -1,
    PARSE_ERR_INVALID_FMT = -2,
    PARSE_ERR_OUT_OF_RANGE = -3
} parser_err_t;
```

### Common mistakes

- Returning inconsistent codes for same failure class.
- Overloading one generic error code for every case.
- Forgetting to document whether `errno` is set for each enum error.

> **C vs C++:** Similar idea to strongly typed error enums in modern C++, but in C there is no type-safe sum type (`variant`/`expected`) to enforce handling at compile time.

## 5) API contracts and defensive programming

A C API contract should specify:

- required non-NULL arguments
- what is modified on success/failure
- exact return codes for malformed data, range issues, and null pointers
- whether `errno` is set, and for which failures

Defensive programming means checking preconditions and failing predictably instead of invoking undefined behavior.

### Example

```c
/* Contract:
 * - str and out must be non-NULL
 * - returns PARSE_ERR_NULL_PTR for NULL args
 * - returns PARSE_ERR_INVALID_FMT if trailing junk remains
 * - returns PARSE_ERR_OUT_OF_RANGE and sets errno=ERANGE on overflow
 */
```

### Common mistakes

- Treating contract docs as optional commentary.
- Dereferencing NULL because caller "should not pass it".
- Not defining what happens to outputs on failure.

> **C vs C++:** C++ abstractions can encode some invariants in types; C relies more heavily on clear docs + tests to enforce contracts.

## 6) `atoi` vs `strtol`: why `atoi` is unsuitable for production input

`atoi(s)` converts a string to `int` but provides no error signal:

- returns `0` for both `"0"` and for `""` and for `"garbage"` — caller cannot distinguish valid zero from failure.
- has no overflow detection; out-of-range input produces implementation-defined behavior.

`strtol` and `strtoul` are the correct alternatives:

```c
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int parse_int(const char* s, int* out) {
    if (!s || !out) return -1;
    errno = 0;
    char* end = NULL;
    long v = strtol(s, &end, 10);
    if (end == s)         return -1; /* no digits consumed */
    if (*end != '\0')     return -1; /* trailing garbage */
    if (errno == ERANGE)  return -1; /* out of long range */
    if (v < INT_MIN || v > INT_MAX) return -1; /* out of int range */
    *out = (int)v;
    return 0;
}
```

Key points: check `end == s` for empty/non-numeric input; check `*end != '\0'` for trailing junk; check `errno` for range; then validate the `long` fits in `int`.

### Common mistakes

- Using `atoi` for any input that could be invalid or user-supplied.
- Checking only `errno` but not `end == s` (empty string returns 0 with `errno` still 0).
- Treating trailing whitespace in `"42 "` as valid without an explicit policy.

> **C vs C++:** C++17 `std::from_chars` provides a single, safe, locale-independent API with explicit error codes. In C, the multi-step `strtol` idiom must be written out each time.

## 7) Surfacing errors to users: `strerror` and `perror`

`errno` values encode technical error categories. To produce human-readable text:

- `strerror(errno)` returns a pointer to a locale-specific description string. The string is valid until the next call to `strerror`.
- `perror("prefix")` writes `"prefix: <errno description>\n"` to `stderr` automatically.

```c
#include <errno.h>
#include <stdio.h>
#include <string.h>

FILE* f = fopen("data.bin", "rb");
if (!f) {
    fprintf(stderr, "open failed: %s\n", strerror(errno));
    /* or equivalently: perror("open failed"); */
    return -1;
}
```

Use these only immediately after the failing system call, before any intervening call might overwrite `errno`.

### Common mistakes

- Calling `strerror` or `perror` after another function has already changed `errno`.
- Storing the `strerror` return pointer across calls (it may be overwritten).
- Using `perror` when `stderr` is unavailable (e.g., daemon processes); prefer `strerror` with a logger instead.

> **C vs C++:** C++ `std::system_error` wraps `errno` in an exception with message text. In C, always capture `errno` into a local variable immediately if you need it after additional calls.

---

Practical rule for today: every failure path should be testable and deterministic. If a caller cannot reliably branch on your API result, the contract is incomplete.
