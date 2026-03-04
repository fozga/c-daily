# Day 05 - C strings without std::string

## 1) Title + Goal

Today you will work with text safely in C using pointer+length semantics instead of relying on implicit NUL termination. The goal is to understand copying/searching contracts that prevent out-of-bounds reads.

## 2) What you will build

You will implement a `strview` module that parses and manipulates text via `const char*` plus `size_t length`, without depending on a trailing `\0`.

## 3) Task (45-60 min)

1. Review `strview.h`. Notice how a "string" is now just a `const char*` and a `size_t`.
2. Implement the `strview` functions in `strview.c`.
3. Never assume the text is NUL-terminated (so never loop until `\0`, only loop up to `length`).
4. Run `make test` to verify your logic.
5. Run `make asan` to ensure no out-of-bounds reads.

## 4) Acceptance criteria

- `make test` passes (0 warnings, all tests green).
- Clean ASan run.
- Answers to all knowledge questions provided in `solution/README.md`.

## 5) Knowledge check

There are 7 questions in `solution/README.md` to answer.

## 6) Stretch goals

- Implement `sv_parse_int(strview sv, int* out)` that safely converts a view to an integer without using `atoi` (since `atoi` requires a NUL terminator).
