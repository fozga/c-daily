# Day 07 - API contracts and error model

## 1) Title + Goal

Today you will design robust C APIs with explicit contracts using return codes and `errno`. The goal is to make failure behavior predictable, testable, and safe for callers.

## 2) What you will refactor/build

You will build a text parsing utility that handles malformed input through specific custom error codes and uses standard `errno` values for system-style failures (such as range overflow).

## 3) Task (45-60 min)

1. Review `parser.h` to understand the exact error contract for each function.
2. Implement parsing logic in `parser.c`.
3. Use `<errno.h>` codes (`EINVAL`, `ERANGE`) where specified, and return your own enum codes where appropriate.
4. Run `make test` to verify both successful parsing and failure paths.
5. Run `make asan` and `make valgrind`.

## 4) Acceptance criteria

- `make test` passes (0 warnings).
- Functions correctly set `errno` on specific failures.
- Functions never crash on `NULL` inputs when contract requires an error return.
- Answers to all knowledge questions are provided in `solution/README.md`.

## 5) Knowledge check

There are 7 questions in `solution/README.md` to answer.

## 6) Stretch goals

- Implement `const char* parser_strerror(parser_err_t err)` that maps custom enum errors to readable strings.
