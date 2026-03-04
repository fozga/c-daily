# Day 28 Notes - Character classes and escapes

## 1) Token-dispatch parsing

A simple pattern parser reads characters left-to-right and dispatches behaviour
by the current token type:
- literal character
- wildcard `.`
- escape sequence `\n`, `\t`, `\\`
- character class `[ ... ]`

The iterative `match_here2` loop advances two cursors simultaneously: one
through the pattern (`pi`) and one through the subject line (`li`):

```c
/* matcher2.c - pattern token dispatcher */
static int match_here2(const char *pat, size_t pi,
                       const char *line, size_t li, int icase) {
    while (pat[pi] != '\0') {
        if (line[li] == '\0') return 0;   /* line exhausted before pattern */

        if (pat[pi] == '\\') {
            /* escape sequence: consume two pattern chars, match one line char */
            char decoded = decode_escape(pat[pi + 1]);
            if (!char_eq(decoded, line[li], icase)) return 0;
            pi += 2; li++; continue;
        }
        if (pat[pi] == '[') {
            /* class: scan to ']', check membership */
            int neg = (pat[pi + 1] == '^');
            size_t class_end;
            int hit = match_class(pat, pi + 1 + neg, &class_end, line[li], icase);
            if (neg ? hit : !hit) return 0;
            pi = class_end + 1; li++; continue;
        }
        if (pat[pi] != '.' && !char_eq(pat[pi], line[li], icase)) return 0;
        pi++; li++;
    }
    return 1;   /* all pattern tokens consumed */
}
```

The key invariant is **deterministic forward progress**: every branch must
advance `pi` by at least one position to prevent infinite loops.

## 2) Character class parsing

When the parser sees `[`, it must scan forward until the matching `]`.

```c
/* Returns 1 if line[li] is in the class starting at pat[ci], sets *end_idx. */
static int match_class(const char *pat, size_t ci, size_t *end_idx,
                       char c, int icase) {
    int hit = 0;
    while (pat[ci] != '\0' && pat[ci] != ']') {
        if (pat[ci + 1] == '-' && pat[ci + 2] != ']' && pat[ci + 2] != '\0') {
            /* range: [a-z] */
            char lo = icase ? (char)tolower((unsigned char)pat[ci])     : pat[ci];
            char hi = icase ? (char)tolower((unsigned char)pat[ci + 2]) : pat[ci + 2];
            char ch = icase ? (char)tolower((unsigned char)c)           : c;
            if (ch >= lo && ch <= hi) hit = 1;
            ci += 3;
        } else {
            if (char_eq(pat[ci], c, icase)) hit = 1;
            ci++;
        }
    }
    *end_idx = ci;   /* points at ']' or '\0' */
    return hit;
}
```

Rules:
- `-` denotes a range **only** when between two class characters and not
  at the start or end of the class body.
- A missing `]` — advance to `\0` and return "no match" without crashing.

## 3) Negated classes

`[^ ... ]` is negated only when `^` is the **first** character after `[`.

Examples:
- `[^abc]` — matches any char that is NOT `a`, `b`, or `c`
- `[a^b]`  — `^` is literal, matches `a`, `^`, or `b`
- `[^a-z]` — (stretch goal) negated range: matches anything not in `a`–`z`

Implementation: read the negation flag, then call the same `match_class`
helper, then invert its result.

## 4) Escapes in pattern language vs C literals

CLI pattern input `\n` (two bytes: `\` and `n`) must be interpreted at
**runtime** by the matcher parser as a newline token, not by the C compiler.

```c
static char decode_escape(char c) {
    switch (c) {
    case 'n':  return '\n';
    case 't':  return '\t';
    case '\\': return '\\';
    default:   return c;    /* unknown escape: treat literally */
    }
}
```

Important distinction:
- C compile-time: `"\n"` in source → byte `0x0A` stored in the binary.
- Runtime: the user types `\n` as two characters on the command line → the
  matcher receives `'\'` then `'n'` and must decode them itself.

## 5) Backward compatibility principle

New features must not regress old behavior:
- literals still match as before
- `.` wildcard semantics unchanged
- case-insensitive mode applied consistently to class ranges too
- all Day 23 test cases must pass without modification

This mirrors real tool evolution: additive features with stable contracts.
The safest implementation strategy is to add the new token branches **before**
the existing literal comparison so the fall-through path is unchanged.

## Common mistakes

- Infinite loops when scanning a malformed class: `[abc` never finds `]`,
  so `ci` must advance to `\0` and the outer loop must terminate.
- Treating every `-` as a range operator regardless of position — `[a-]`
  should include literal `-`, not crash.
- Applying negation when `^` is not the first character after `[`.
- Not propagating the `icase` flag into `match_class` range comparisons.
- Using raw `char` comparisons in range check (`ch >= lo`) without ensuring
  both sides are cast to `unsigned char` first.
- Breaking Day 23 test cases by changing how `.` or literals are handled in
  the shared dispatch path.
- Forgetting to advance `pi` by 2 (not 1) after consuming an escape sequence.

## C vs C++

- In C, parser state is explicit indices (`pi`, `ci`) into `const char*`
  arrays; all branching is manual.
- C++ can use `std::variant` for typed tokens, `std::string_view` for
  slices, or `std::regex` as a reference implementation to validate against.
- Regardless of language, bracket-class grammar edge cases (`[-abc]`,
  `[]]`, `[^]`) require exhaustive unit tests — they are the most
  common source of correctness bugs in hand-rolled matchers.
