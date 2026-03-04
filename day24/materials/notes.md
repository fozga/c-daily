# Day 24 Notes - File traversal and line scanning

## 1) `fgets` semantics

`fgets(buf, n, fp)`:
- reads up to `n - 1` chars
- always NUL-terminates on success
- includes newline in buffer **if it fit** — when the line is longer than
  `n - 1` bytes the remaining content stays in the stream for the next call
- returns `NULL` on EOF or I/O error (use `feof`/`ferror` to distinguish)

This makes it suitable for safe line-based scanning with bounded buffers.

**Newline stripping idiom** — strip the trailing `\n` (and optional `\r` for
CRLF files) before matching so that pattern `"foo"` does not fail to match a
line that ends in `"foo\n"`:

### Example

```c
size_t len = strlen(buf);
if (len > 0 && buf[len - 1] == '\n') buf[--len] = '\0';
if (len > 0 && buf[len - 1] == '\r') buf[--len] = '\0';
```

## 2) Scanner pipeline design

`stdin` can be passed to the same scanner function as a regular file handle.
Designing `scanner_run(FILE *fp, const char *filename, const matcher_t *m, ...)`
keeps traversal logic reusable and avoids duplicated code paths:

```c
/* scanner.c - core pipeline: read → strip → match → print */
int scanner_run(FILE *fp, const char *filename, int print_filename,
                const matcher_t *m, int line_numbers) {
    char buf[4096];
    int  lineno  = 0;
    int  matched = 0;

    while (fgets(buf, sizeof buf, fp)) {
        lineno++;
        /* strip trailing newline */
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[--len] = '\0';

        if (!matcher_match_line(m, buf)) continue;
        matched = 1;

        if (print_filename) printf("%s:", filename);
        if (line_numbers)   printf("%d:", lineno);
        printf("%s\n", buf);
    }

    if (ferror(fp)) return -1;   /* I/O error — signal to caller */
    return matched;
}
```

The caller decides whether `fp` came from `fopen` or is `stdin`; the scanner
doesn't know and doesn't need to.

## 3) stdout vs stderr responsibilities

- Matching data output -> `stdout`
- Diagnostics/errors -> `stderr`

This enables redirection and scripting workflows:
- `mini-grep PATTERN file >matches.txt`
- while still seeing errors in terminal.

## 4) Line number tracking

Line numbers should increment per line read, not per match found.
Even non-matching lines contribute to line index progression.

## 5) Filename prefix logic

POSIX-style behavior:
- with only one file (or stdin), no filename prefix by default
- with multiple files, prefix matched lines with `filename:` for disambiguation

This reduces output noise while preserving context in multi-file scans.
In mini-grep, `opts->files_count` determines the threshold: `> 1` triggers
prefix printing.  When `files_count == 0`, mini-grep reads `stdin` with no
prefix.

Output format summary:

| Mode                    | With `-n`                         | Without `-n`       |
|-------------------------|-----------------------------------|--------------------|
| stdin / single file     | `<lineno>:<content>`              | `<content>`        |
| multiple files          | `<filename>:<lineno>:<content>`   | `<filename>:<content>` |

## Common mistakes

- Forgetting to strip the trailing `\n` (and `\r` for CRLF) before matching.
- Treating `fgets` returning `NULL` as always meaning EOF — check `ferror(fp)`.
- Printing diagnostics to stdout (breaks pipelines like `mini-grep PAT f | wc -l`).
- Incrementing line number only on match instead of on every line read.
- Always printing the filename prefix even for single-file or stdin input.
- Closing `stdin` after scanning it (never call `fclose(stdin)`).

## C vs C++

- C uses `FILE*` and `fgets` for buffered text scanning; the newline
  stripping must be done manually.
- C++ uses `std::getline` which strips `\n` automatically and grows the
  buffer dynamically (no fixed 4096-byte limit).
- In C, explicit buffer handling gives control at the cost of careful
  boundary and newline management on every read loop.
- Error detection: C requires `feof`/`ferror` after a `NULL` return; C++
  `std::ifstream` exposes `fail()` and `bad()` state bits directly.
