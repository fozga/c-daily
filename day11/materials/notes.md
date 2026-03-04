# Day 11 Notes - Preprocessor discipline in C

## 1) How the preprocessor works

The C preprocessor runs before compilation and performs text substitution.

Important consequences:
- No type checking in macros.
- Expansion is token-based text rewriting.
- Bugs can be subtle because generated code differs from what you read.

Typical directives:
- `#define` for macros/constants
- `#include` for file inclusion
- `#if`, `#ifdef`, `#ifndef` for conditional compilation

## 2) Classic macro pitfalls

### Double evaluation

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* BUG: i++ is evaluated twice if i < j; j++ is evaluated twice if j < i */
int result = MAX(i++, j++);
/* expands to: ((i++) > (j++) ? (i++) : (j++))
   — one of the two variables is incremented an extra time */
```

Problem: one argument can be evaluated more than once, producing unexpected
increments and side effects.

### Operator precedence bugs

```c
#define SQUARE(x) x * x          /* BAD: no parentheses */

int a = SQUARE(1 + 2);
/* expands to: 1 + 2 * 1 + 2  ==  5, not 9 */

#define SQUARE_SAFE(x) ((x) * (x))  /* parenthesize argument AND result */

int b = SQUARE_SAFE(1 + 2);
/* expands to: ((1 + 2) * (1 + 2))  ==  9 */
```

Always parenthesize both parameters and the full replacement body when
appropriate.

### Multi-statement macro hazards

```c
/* BAD: only the first statement is conditional */
#define LOG_AND_FAIL(msg) \
    log_error(msg);       \
    return -1;

if (cond)
    LOG_AND_FAIL("oops");   /* return -1 executes unconditionally! */
else
    do_other();

/* SAFE: do-while wraps both statements into one syntactic unit */
#define LOG_AND_FAIL(msg)     \
    do {                      \
        log_error(msg);       \
        return -1;            \
    } while (0)

if (cond)
    LOG_AND_FAIL("oops");   /* now the else is not orphaned */
else
    do_other();
```

Wrap multi-statement macro bodies in `do { ... } while (0)` so the macro
behaves like a single statement everywhere.

## 3) Safer macro patterns

### Prefer `static inline` for function-like logic

Advantages over macros:
- Type checking
- Single evaluation of arguments
- Easier debugging

Use macros mainly when needed for:
- generic compile-time constructs
- conditional compilation
- token/string generation features

### Parentheses discipline

If using expression-like macros:
- parenthesize each argument use
- parenthesize full expression result

### Single-evaluation design

For macros that must avoid double evaluation, use local temporary variables via
compiler extensions only if portability allows, or better: move logic into
`static inline` functions.

### Example

```c
/* Prefer this over the MAX macro for typed, side-effect-safe comparisons */
static inline int max_int(int a, int b) { return a > b ? a : b; }
static inline double max_double(double a, double b) { return a > b ? a : b; }

/* Legitimate use of a macro: compile-time type size assertion */
#define STATIC_ASSERT_SIZE(type, expected_bytes) \
    _Static_assert(sizeof(type) == (expected_bytes), \
                   "unexpected size for " #type)

STATIC_ASSERT_SIZE(uint32_t, 4);  /* caught at compile time if wrong */

/* Legitimate use: stringification and token-pasting */
#define STRINGIFY(x)  #x
#define CONCAT(a, b)  a##b

const char *name = STRINGIFY(my_var);   /* "my_var" */
int CONCAT(prefix_, value) = 42;        /* prefix_value = 42 */
```

## 4) Include guards vs `#pragma once`

### Include guards

```c
/* foo.h */
#ifndef FOO_H
#define FOO_H

/* declarations here — included any number of times, compiled once */
void foo_init(void);

#endif /* FOO_H */
```

Portable and standard C practice.

### `#pragma once`

```c
#pragma once   /* non-standard, but widely supported shorthand */
void foo_init(void);
```

Concise and widely supported, but technically non-standard.

Tradeoff: convenience vs strict portability guarantees.

## 5) Conditional compilation

Tools:
- `#ifdef NAME`
- `#ifndef NAME`
- `#if defined(NAME)`
- `#if` with numeric expressions

Common use cases:
- debug logging toggles
- platform-specific code
- feature flags

Use sparingly and keep branches tested; dead conditional branches rot quickly.

## Common mistakes

- Macro parameters not parenthesized.
- Macro result not parenthesized.
- Side-effecting arguments passed into unsafe macros.
- Multi-line macros without `do { } while (0)`.
- Missing include guards causing duplicate definitions.
- Overusing macros where `static inline` is clearer.
- Deep `#ifdef` trees that hide untested code paths.

## C vs C++

- C++ templates/`constexpr` provide safer metaprogramming than many C macros.
- C++ inline functions and templates often replace function-like macros cleanly.
- In C, preprocessor remains essential but requires strict conventions.
- C++ still uses preprocessor for feature flags/platform gates, but less for
  typed logic.
