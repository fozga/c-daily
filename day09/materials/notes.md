# Day 09 Notes - Robust text input parsing in C

## 1) `fgets` vs `scanf`

For line-oriented input, `fgets` is usually safer than scanning directly with
`scanf`.

### Why `fgets` is safer

- You provide a fixed buffer size.
- It avoids classic overflow mistakes like unbounded `%s`.
- You get the full line (or a bounded prefix), which you can validate yourself.

### Newline behavior

If a newline fits in the buffer, `fgets` stores it. You often strip trailing
`\n` before parsing fields.

### Why direct `scanf` on `stdin` is risky

- Harder to recover from malformed tokens.
- Leaves unread input behind in surprising ways.
- Blends I/O and parsing, which complicates precise error reporting.

Recommended flow:
1. Read one whole line with `fgets`.
2. Parse the in-memory string.
3. Return specific parse errors.

## 2) `strtol` / `strtod` correct pattern

String-to-number conversion must be done defensively.

### Safe conversion sequence

1. Set `errno = 0`.
2. Call `strtol` (or `strtod`) with `endptr`.
3. Check if any characters were consumed (`endptr != start`).
4. Check trailing garbage (`*endptr == '\0'` after trimming rules).
5. Check range errors (`errno == ERANGE`).
6. Check target-type bounds when narrowing (e.g., `long` to `int32_t`).

### Why set `errno = 0` first?

`errno` is sticky; it keeps old values until overwritten. Clearing it first
lets you attribute `ERANGE` to this conversion call.

### Example

```c
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

/* Returns 0 on success and stores the int32_t in *out.
   Returns -1 on any parse or range error. */
int parse_int32(const char *str, int32_t *out) {
    if (!str || *str == '\0') return -1;   /* reject empty string */

    char *end;
    errno = 0;                             /* step 1: clear sticky errno    */
    long val = strtol(str, &end, 10);      /* step 2: convert               */

    if (end == str)       return -1;       /* step 3: no digits consumed     */
    if (*end != '\0')     return -1;       /* step 4: trailing garbage       */
    if (errno == ERANGE)  return -1;       /* step 5: out of long range      */
    if (val < INT32_MIN || val > INT32_MAX) return -1; /* step 6: narrow    */

    *out = (int32_t)val;
    return 0;
}

/* Recommended line-oriented flow */
void parse_line_example(FILE *fp) {
    char buf[256];
    if (!fgets(buf, sizeof buf, fp)) {
        if (feof(fp))   { /* normal end-of-file */ }
        else            { /* I/O error via ferror(fp) */ }
        return;
    }
    /* Strip trailing newline before parsing fields */
    buf[strcspn(buf, "\n")] = '\0';

    int32_t id;
    if (parse_int32(buf, &id) != 0) {
        /* report specific error, don't silently accept bad data */
    }
}
```

## 3) `sscanf` usage and limits

`sscanf` can be useful for simple structured parsing of an in-memory line.

### Strengths

- Concise for known formats.
- Can split and parse in one call for some tasks.

### Limitations

- Weak partial-failure diagnostics.
- Hard to distinguish nuanced malformed cases.
- Easy to accidentally accept trailing garbage unless explicitly checked.

For robust systems, tokenization + `strtol`/`strtod` often provides clearer
error handling.

## 4) Input validation strategy

Robust parsing checks both structure and semantic validity.

### Structural validation

- Required delimiters exist.
- Required fields are present (not missing).
- No unexpected extra separators if format forbids them.

### Semantic validation

- Numeric fields are valid numbers.
- Values are in allowed range.
- Optional policy checks (e.g., non-empty name).

### Complete vs partial parsing

A common bug: accepting `123abc` as `123`. Always verify that conversion
consumed all intended characters.

## 5) `FILE*` error handling

I/O needs explicit end-of-file vs error distinction.

### Key checks

- `fgets(...) == NULL` means either EOF or error.
- Use `feof(fp)` to detect EOF.
- Use `ferror(fp)` to detect I/O errors.

These are different outcomes and should map to different return codes.

## Common mistakes

- Using `scanf("%s", buf)` without width limits.
- Forgetting to clear `errno` before `strtol`.
- Not checking `endptr`.
- Treating empty field as valid number.
- Ignoring trailing junk after parsed number.
- Confusing EOF with I/O error.
- Returning a single generic error for all malformed cases.

## C vs C++

- C approach: `fgets` + manual tokenization + `strtol`/`strtod`.
- C++ approach: `std::getline` + stream or explicit conversions.
- C++ offers safer string abstractions; C requires careful buffer discipline.
- In both languages, strict validation is required to avoid silent data bugs.
