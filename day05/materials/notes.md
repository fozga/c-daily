# Day 05 Notes - C Strings Without `std::string`

This day shifts from "NUL-terminated strings" to explicit "pointer + length" views. The key idea: a byte sequence can be valid text even if it is not terminated by `\0`.

## 1) C-string format

A classic C string is a contiguous array of `char` ending with a NUL byte (`'\0'`). Functions such as `strlen`, `strcmp`, and `%s` formatting assume this convention.

The terminator is part of the storage contract, not the logical text payload. If the terminator is missing, consumers keep reading memory until they accidentally hit `\0` somewhere else.

### Example

```c
char ok[] = {'c', 'a', 't', '\0'};
char not_c_string[] = {'c', 'a', 't'}; /* no terminator */
```

`ok` is a C-string, `not_c_string` is just 3 bytes of character data.

### Common mistakes

- Treating any `char*` as a valid C-string.
- Forgetting space for the terminator when building buffers.
- Assuming byte arrays from files/sockets are always NUL-terminated.

> **C vs C++:** `std::string` tracks size and can contain embedded NUL bytes. C-strings rely on sentinel termination and cannot represent embedded NUL as ordinary content for many APIs.

## 2) Vulnerabilities of C-strings

C-string APIs are convenient but fragile:

- **Buffer over-read** when terminator is missing.
- **Terminator bugs** from incorrect copying or truncation.
- **`strlen` cost** is O(N), because it scans bytes until `\0`.

Repeated calls to `strlen` in loops can become an accidental performance bug.

### Example

```c
/* bad: strlen is recomputed each iteration, O(N^2) pattern in some contexts */
for (size_t i = 0; i < strlen(s); ++i) {
    /* ... */
}
```

### Common mistakes

- Passing unterminated memory to `%s`, `strlen`, `strcmp`, etc.
- Forgetting that `strlen` is linear, not constant time.
- Assuming truncation routines always leave a terminator.

> **C vs C++:** C++ string APIs expose `.size()` in O(1). C-string length is discovered by scanning, so callers pay traversal cost repeatedly unless they cache it.

## 3) String View pattern (`pointer` + `length`)

A string view stores:

- `data` pointer to first byte
- `length` number of bytes in view

This gives explicit bounds and O(1) length access. Substrings become cheap: adjust pointer and length, no copy needed.

### Example

```c
typedef struct {
    const char* data;
    size_t length;
} strview;

strview full = {"alpha,beta", 10};
strview left = {full.data, 5};
strview right = {full.data + 6, 4};
```

No reallocation, no scanning for `\0`, and views can reference larger buffers safely if bounds are respected.

### Common mistakes

- Calling C-string APIs on `view.data` without ensuring termination.
- Forgetting to preserve/validate `length` after slicing.
- Creating views to memory that goes out of lifetime scope.

> **C vs C++:** This mirrors `std::string_view` conceptually. In C, you implement the struct and contracts yourself; safety depends on discipline and API design.

## 4) Comparing memory: `memcmp` vs `strcmp` (conceptually)

`strcmp` compares two NUL-terminated strings and stops at `\0`.

`memcmp` compares exactly `n` bytes and does not care about terminators.

With views, equality should be:

1. lengths equal,
2. each byte equal for `0..length-1`.

That is "length-aware memory comparison," conceptually closer to `memcmp` than `strcmp`.

### Example

```c
/* conceptual logic for view equality */
if (a.length != b.length) return false;
for (size_t i = 0; i < a.length; ++i) {
    if (a.data[i] != b.data[i]) return false;
}
return true;
```

### Common mistakes

- Using terminator-based comparison for non-terminated buffers.
- Comparing pointers instead of bytes (`a.data == b.data` is not content equality).
- Forgetting length check before byte-by-byte compare.

> **C vs C++:** `std::string_view` equality is length-aware and content-aware. Raw C pointers do not encode either property without an accompanying length.

## 5) Pointer arithmetic with `char`

For `char* p`, `p + k` advances by `k` bytes (because `sizeof(char) == 1`).

When you have two pointers into the same array/object region, `end - start` yields the element distance (`ptrdiff_t`). For `char*`, that distance is byte count.

This is useful for view slicing:

- `left.length = (size_t)(delim_ptr - start_ptr)`
- `right.data = delim_ptr + 1`
- `right.length = total_len - left.length - 1`

### Example

```c
const char* s = "key:value";
const char* colon = s + 3;
size_t left_len = (size_t)(colon - s); /* 3 */
```

### Common mistakes

- Subtracting pointers from unrelated arrays (undefined behavior).
- Failing to validate that delimiter pointer lies within view bounds.
- Mixing signed pointer differences with unsigned lengths carelessly.

> **C vs C++:** Arithmetic rules are similar, but C APIs expose this style directly far more often than C++ container interfaces.

---

Practical rule for this day: any loop over text must use explicit bounds (`i < length`), never sentinel-based traversal unless the API explicitly guarantees NUL termination.
