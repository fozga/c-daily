# Day 24 Notes - File traversal and line scanning

## 1) `fgets` semantics

`fgets(buf, n, fp)`:
- reads up to `n - 1` chars
- always NUL-terminates on success
- includes newline in buffer if it fit
- returns `NULL` on EOF or I/O error

This makes it suitable for safe line-based scanning with bounded buffers.

## 2) stdin is just `FILE*`

`stdin` can be passed to the same scanner function as regular file handles.
Designing `scanner_run(FILE* fp, ...)` keeps traversal logic reusable and avoids
duplicated code paths.

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
- with multiple files, prefix matched lines with filename for disambiguation

This reduces output noise while preserving context in multi-file scans.

## Common mistakes

- Forgetting to strip trailing newline before matching/comparing.
- Treating EOF and I/O error as the same outcome.
- Printing diagnostics to stdout.
- Incrementing line number only on match.
- Always printing filename even for single input stream.

## C vs C++

- C uses `FILE*` and `fgets` for buffered text scanning.
- C++ often uses `std::getline` on iostreams.
- In C, explicit buffer handling offers control but requires careful boundary
  and newline management.
