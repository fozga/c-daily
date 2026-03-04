# Day 26 Notes - Integration test matrices for CLI tools

## 1) Integration vs unit testing

Unit tests:
- validate isolated functions/modules
- fast and precise for algorithm correctness

Integration tests:
- validate full behavior across modules, I/O, exit codes, and formatting
- catch wiring issues that unit tests miss

For CLI tools, both levels are required.

## 2) Shell test script techniques

Useful shell patterns:
- inspect exit code via `$?`
- compare output with exact expected strings
- use temporary files for stdout/stderr capture
- use `diff` or string equality checks for golden outputs

Portable fixture generation:
- `printf` for controlled content
- checked-in fixture files for deterministic runs

## 3) Regression testing essentials

A strong regression test is:
- small
- deterministic
- focused on one previously broken behavior
- fast enough for frequent execution

Avoid giant mixed-purpose tests that are hard to diagnose when failing.

## 4) Coverage dimensions for grep-like tools

Include matrix across:
- empty/single/multi-line files
- flag combinations (`-n`, `-i`, `-h`)
- missing args and invalid flags
- missing files / permission errors
- stdin vs file mode

## 5) Golden-output tradeoffs

Pros:
- easy to read and compare
- catches formatting regressions quickly

Cons:
- brittle when formatting intentionally changes
- can hide semantic intent if snapshots are too large

Keep golden expectations minimal and purposeful.

## Common mistakes

- Checking stdout but forgetting stderr and exit code.
- Using non-deterministic fixtures in tests.
- Mixing multiple assertions into one opaque test case.
- Not testing error paths (missing file, bad args).
- Assuming unit tests imply CLI UX correctness.

## C vs C++

- Regardless of implementation language, CLI integration behavior is validated
  externally as process-level black-box tests.
- C++ projects may use richer test frameworks, but shell-based matrix testing is
  still highly effective for command-line contracts.
