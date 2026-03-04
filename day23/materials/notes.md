# Day 23 Notes - Literal and wildcard matching

## 1) Naive substring search (O(N*M))

For line length `N` and pattern length `M`, a straightforward approach checks
every possible start position and compares characters.

Worst-case complexity: `O(N * M)` — e.g., pattern `"aaab"` on line `"aaa…aab"`.
For grep-sized inputs (lines up to ~4 KB, patterns up to ~256 B) this is fast
enough and much easier to reason about than KMP or Boyer-Moore.

For mini-grep this is the intended algorithm; resist premature optimisation.

## 2) Dot wildcard implementation

Pattern character rules:
- literal char must equal line char
- `.` matches any single character (including space, but not used past `\0`)

The key insight is that wildcard logic lives inside the **inner** comparison
loop at each candidate start position, not as a preprocessing step.

### Example

```c
/* matcher.c - naive search with dot wildcard support */
int match_here(const char *pat, const char *line, int icase) {
    for (int j = 0; pat[j] != '\0'; j++) {
        if (line[j] == '\0') return 0;           /* line too short */
        if (pat[j] == '.') continue;             /* dot: any char */
        char p = icase ? (char)tolower((unsigned char)pat[j])  : pat[j];
        char l = icase ? (char)tolower((unsigned char)line[j]) : line[j];
        if (p != l)   return 0;                  /* mismatch */
    }
    return 1;   /* all pattern chars satisfied */
}

int matcher_match_line(const matcher_t *m, const char *line) {
    if (m->pattern[0] == '\0') return 1;         /* empty pattern → always match */
    size_t plen = strlen(m->pattern);
    size_t llen = strlen(line);
    if (plen > llen) return 0;
    for (size_t i = 0; i <= llen - plen; i++)
        if (match_here(m->pattern, line + i, m->ignore_case))
            return 1;
    return 0;
}
```

When mismatch occurs inside `match_here`, the caller advances `i` and retries
from the next position in the line.

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

- Off-by-one errors in outer loop bounds (`<=` vs `<` when computing last
  valid start position `llen - plen`).
- Treating `.` as a literal period instead of a wildcard.
- Forgetting to cast to `unsigned char` before `tolower` (signed `char`
  values > 127 produce undefined behaviour with ctype functions).
- Handling empty pattern inconsistently — mini-grep should match every line.
- Reading past `\0` when the pattern is longer than the remaining line slice
  (guard with `if (line[j] == '\0') return 0` before comparing).
- Using `strstr(3)` as a shortcut — it does not understand `.` wildcards.
- Modifying `line` or `pattern` in-place (breaks const-correctness and
  will corrupt caller's buffers).

## C vs C++

- C uses manual loops and `char*` for all matcher logic; boundary checks are
  the programmer's responsibility.
- C++ `std::string_view` can express slices without copying; `<regex>` or
  third-party libraries provide full regex matching.
- In C the explicit control makes every `.` decision visible; in C++ the same
  logic is often hidden inside library abstractions.
- Performance: both compile to roughly equivalent machine code for this
  simple O(N·M) inner loop when optimised.
