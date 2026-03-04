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

Macro:
- `#define MAX(a, b) ((a) > (b) ? (a) : (b))`

Call:
- `MAX(i++, j++)`

Problem: one argument can be evaluated more than once, producing unexpected
increments and side effects.

### Operator precedence bugs

Macro:
- `#define SQUARE(x) x * x`

`SQUARE(1 + 2)` expands to `1 + 2 * 1 + 2`, not `(1 + 2) * (1 + 2)`.

Always parenthesize both parameters and the full replacement body when
appropriate.

### Multi-statement macro hazards

Macro bodies with several statements can break control flow:
- dangling `else`
- partial block execution

Wrap in:
- `do { ... } while (0)`

This makes macro use behave like a single statement.

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

## 4) Include guards vs `#pragma once`

### Include guards

Pattern:
- `#ifndef FOO_H`
- `#define FOO_H`
- `...`
- `#endif`

Portable and standard C practice.

### `#pragma once`

Concise and widely supported, but technically non-standard.

Tradeoff:
- convenience vs strict portability guarantees.

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
