# Day 23 Notes - Literal and wildcard matching

## 1) Naive substring search (O(N*M))

For line length `N` and pattern length `M`, a straightforward approach checks
every possible start position and compares characters.

Worst-case complexity:
- `O(N * M)`

For this project stage, naive search is sufficient and easier to reason about.

## 2) Dot wildcard implementation

Pattern character rules:
- literal char must equal line char
- `.` matches any single char

Inner loop condition for mismatch:
- mismatch when `pattern[j] != '.'` and chars differ

When mismatch occurs, advance start position in line and retry.

## 3) ASCII case folding

Case-insensitive comparison can use `tolower()` from `<ctype.h>`:
- compare `tolower((unsigned char)a)` vs `tolower((unsigned char)b)`

This is ASCII-oriented behavior. Full Unicode case folding is much more complex
and intentionally out of scope for this tool.

## 4) Search vs match semantics

- **Search**: pattern appears anywhere in line (this project behavior).
- **Match**: entire line must satisfy pattern (not used today).

Be explicit about this distinction in implementation and tests.

## 5) Input hygiene and edge cases

Important cases:
- empty pattern -> should match every line
- pattern longer than line -> no match, no crash
- empty line with non-empty pattern -> no match
- empty line with empty pattern -> match

Always guard against out-of-bounds indexing in nested loops.

## Common mistakes

- Off-by-one errors in outer loop bounds.
- Treating `.` as literal when wildcard should apply.
- Forgetting to cast to `unsigned char` before `tolower`.
- Handling empty pattern inconsistently.
- Reading past NUL when pattern longer than remaining line segment.

## C vs C++

- C typically uses manual loops and `char*` logic for matchers.
- C++ might use higher-level utilities or regex facilities.
- In C, explicit control gives clarity but requires stricter boundary checks.
