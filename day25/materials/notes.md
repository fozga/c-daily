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

Common command-line conventions:
- `0` success (useful matches, no critical failures)
- `1` no matches or partial failure
- `2` usage/configuration/fatal misuse tier (project-specific mapping here for all-error case)

Consistency matters for scripts and automation.

## 4) Diagnostic message format

Good UX format:
- `prog_name: context: reason`

Example:
- `mini-grep: foo.txt: No such file or directory`

This format is compact, grep-like, and easy to parse visually.

## 5) `perror` vs explicit `fprintf` + `strerror`

`perror("mini-grep")` is quick but less flexible.
`fprintf(stderr, "%s: %s: %s\n", prog, path, strerror(errno))` gives explicit
context and consistent formatting for per-file errors.

## Common mistakes

- Reading `errno` too late.
- Printing errors to stdout.
- Exiting on first file error instead of continuing.
- Returning `0` when some files failed.
- Inconsistent diagnostic prefix formatting.

## C vs C++

- C uses errno-centric APIs and explicit error-string mapping.
- C++ can use exceptions or richer error abstractions, but CLI tools still need
  clear stderr diagnostics and deterministic exit codes.
