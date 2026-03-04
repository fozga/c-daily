# Day 04 - Arrays, decay, and pointer arithmetic

## 1) Title + Goal

Today you will build a safe fixed-buffer parser while practicing array decay and pointer arithmetic in C. The goal is to traverse contiguous memory explicitly and safely, without relying on automatic bounds checks.

## 2) What you will build

You will implement a small buffer reader API that safely traverses and extracts bytes from a contiguous memory region without ever walking off the edge.

## 3) Task (45-60 min)

1. Review `buffer.h` to understand parser state and API contracts.
2. Implement the functions in `buffer.c`.
3. Never access memory outside `[data, data + capacity)`.
4. Run `make test` until all provided assertions pass.
5. Run `make asan` to catch subtle off-by-one errors during traversal.

## 4) Acceptance criteria

- `make test` passes (0 warnings, all tests green).
- Clean ASan run (no buffer overflows).
- Answers to all knowledge questions provided in `solution/README.md`.

## 5) Knowledge check

There are 8 questions in `solution/README.md` to answer.

## 6) Stretch goals

- Implement a function `buf_read_until(buffer_t* b, uint8_t delimiter, uint8_t* out_arr, size_t max_len)` that copies bytes until it hits a specific value or the end of the buffer.
