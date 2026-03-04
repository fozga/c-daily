# Day 25 Notes - Diagnostics and exit-code design

## 1) `strerror(errno)` basics

`errno` holds error code from failed system/library calls.
`strerror(errno)` converts it to human-readable message.

Important: capture/use `errno` immediately after failure, before calling other
functions that might overwrite it.

## 2) Partial-failure workflows

CLI tools often process many inputs where some can fail:
- missing file
- permission denied
- transient I/O error

Best practice:
- report failure for each input
- continue remaining inputs when possible
- return final status summarizing overall result

## 3) Exit code conventions

POSIX grep defines a precise three-value scheme:

| Code | Standard grep meaning       | mini-grep mapping                         |
|------|-----------------------------|-------------------------------------------|
| `0`  | At least one match found    | ≥1 match, no file-open errors             |
| `1`  | No lines matched            | No matches **or** partial file failure    |
| `2`  | An error occurred           | All files failed to open (only errors)    |

Mini-grep collapses "no matches" and "partial failure" both to `1`.  This
follows the principle that a non-zero exit from `grep` means "you should not
rely on the output", regardless of the exact reason.

```c
/* main.c - exit-code aggregation after scanning all files */
int any_match  = 0;
int any_error  = 0;

for (int i = 0; i < opts.files_count; i++) {
    FILE *fp = diag_open_file(opts.files[i]);
    if (!fp) { any_error = 1; continue; }
    int rc = scanner_run(fp, opts.files[i], print_fname, &m, opts.line_numbers);
    fclose(fp);
    if (rc > 0) any_match = 1;
    if (rc < 0) any_error = 1;
}

if (any_match && !any_error) exit(0);
if (!any_match && !any_error) exit(1);   /* clean run, no matches */
if (any_error  && !any_match) exit(2);   /* only errors */
exit(1);                                  /* partial: some ok, some failed */
```

Consistency matters for shell scripts that branch on `$?`.

## 4) Diagnostic message format

Good UX format:
- `prog_name: context: reason`

Example:
- `mini-grep: foo.txt: No such file or directory`

This format is compact, grep-like, and easy to parse visually.

## 5) `perror` vs explicit `fprintf` + `strerror`

`perror("mini-grep")` is quick but only prepends a fixed prefix and always
prints to stderr — you cannot include the filename in the standard way.

Prefer explicit `fprintf` + `strerror` for mini-grep's per-file errors:

```c
/* diag.c */
FILE *diag_open_file(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        /* capture errno before any intervening call can overwrite it */
        int saved_errno = errno;
        fprintf(stderr, "mini-grep: %s: %s\n", path, strerror(saved_errno));
    }
    return fp;   /* NULL on failure; caller checks */
}
```

This produces the familiar `mini-grep: foo.txt: No such file or directory`
format that matches real grep and is easy to parse in scripts.

## Common mistakes

- Reading `errno` too late — a successful `fprintf` call can reset it to `0`.
- Printing error messages to stdout instead of stderr.
- Calling `exit` immediately on the first file-open failure instead of
  continuing to process remaining files.
- Returning `0` when some files failed or no matches were found.
- Inconsistent diagnostic prefix formatting (`prog: file: reason` vs
  other orderings).
- Confusing "no matches" (exit `1`, semantic) with "error" (exit `2`,
  operational) — scripts branch on `$?` and need the distinction.

## C vs C++

- C uses errno-centric APIs (`errno`, `strerror`) and `fprintf` for
  diagnostics; error propagation is manual (return codes, flags).
- C++ can use exceptions or `std::error_code` / `std::filesystem::path`
  abstractions, but CLI tools still need clear stderr output and
  deterministic exit codes regardless of language.
- `std::filesystem::path` in C++17 provides cross-platform open-error
  messages without raw `errno` handling.
