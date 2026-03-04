# Day 08 Notes - qsort, bsearch, and function pointers

## 1) Function pointers in C

Function pointers let you pass behavior to other functions. The C standard
library uses this heavily for generic algorithms.

### Declaration basics

Function:
- `int cmp(const void* a, const void* b);`

Pointer to that function type:
- `int (*cmp_fn)(const void*, const void*);`

Use:
- `cmp_fn fn = cmp;`
- `int result = fn(pa, pb);`

### Read declarations from inside out

`int (*f)(double)` means:
- `f` is a pointer (`*f`)
- to a function taking `double`
- returning `int`

Parentheses are required. Without them, you would declare a function returning
a pointer, which is different.

### Passing function pointers as callbacks

Typical callback-style APIs:
- sorting: comparator callback
- searching: comparator callback
- event systems: handler callback

This pattern decouples algorithm code from data-specific comparison rules.

### Storing function pointers in structs

You can bundle behavior with data:

- Strategy-style structs
- Dispatch tables
- Mini plugin systems

Example idea:
- `struct sorter { int (*cmp)(const void*, const void*); };`

This keeps code modular and testable.

## 2) `qsort`

### Signature

`void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));`

- `base`: start of array memory
- `nmemb`: number of elements
- `size`: bytes per element
- `compar`: callback to compare two elements

### Comparator contract

Comparator must return:
- negative if first element is "less than" second
- zero if equal
- positive if first element is "greater than" second

The exact negative/positive value is not important; only sign matters.

### Why `const void*`?

`qsort` is generic. It cannot know your element type. It only sees raw bytes,
so elements are provided as `const void*`. Inside comparator, cast carefully:

- cast to pointer-to-element type
- keep `const`
- avoid violating strict aliasing rules

For an array of `record_t`, cast like:
- `const record_t* ra = (const record_t*)a;`
- `const record_t* rb = (const record_t*)b;`

### Safety tips

- Handle ties consistently.
- Do not mutate elements in comparator.
- Do not depend on comparator side effects.

## 3) `bsearch`

### Signature

`void* bsearch(const void* key, const void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));`

### Core precondition

The array **must already be sorted** according to the same ordering used by the
comparator for search.

If this precondition is broken, result is undefined from an algorithmic
standpoint: the function may miss existing elements or return nonsense.

### Return behavior

- Returns pointer to matching element on success.
- Returns `NULL` when not found.

If duplicates exist, which one you get is not specified.

## 4) Comparator design rules

Comparators should define a coherent ordering.

### Consistency properties

- **Transitivity**: if `a < b` and `b < c`, then `a < c`
- **Antisymmetry** (for strict order): signs should invert when args swap
- **Totality** (for total order): any pair must be comparable

Broken comparator logic can cause incorrect sorting/search behavior.

### Integer subtraction pitfall

Common buggy comparator:
- `return x - y;`

For signed integers, subtraction can overflow. Signed overflow is undefined
behavior in C. Safer pattern:

- compare with relational operators and return -1/0/+1

Example approach:
- if `x < y` return -1
- if `x > y` return 1
- else return 0

This avoids overflow and is explicit.

## 5) Stability and why it matters

`qsort` in C is **not guaranteed to be stable**.

Stable sort means equal keys keep original relative order. Unstable sort may
reorder equal-key elements.

When this matters:
- multi-key sorting in passes
- preserving insertion chronology for equal keys
- reproducible output requirements

If you need stability, implement or use a stable algorithm yourself.

## Common mistakes

- Casting comparator arguments to wrong type.
- Returning boolean (`0/1`) instead of negative/zero/positive.
- Using `return a - b` on signed types.
- Calling `bsearch` before sorting.
- Using one comparator for sorting and a different logical order for search.
- Assuming `qsort` is stable.
- Forgetting that `bsearch` returns `NULL` when not found.

## C vs C++

- C: `qsort` + function pointers + `void*` casting.
- C++: `std::sort` with typed iterators and lambdas.
- C++ comparators are type-safe and inline-friendly.
- C callbacks are runtime-indirect and less type-checked.
- C code needs extra care with casts and comparator contracts.

For C learners with C++ background: concept is similar, but C gives less safety
and more responsibility for correctness.
