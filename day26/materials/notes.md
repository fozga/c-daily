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

A single self-contained test case for mini-grep checks three things:
1. stdout content, 2. stderr content, 3. exit code.

```bash
#!/usr/bin/env bash
# test_matrix.sh - mini-grep integration test helpers

PASS=0; FAIL=0

check() {
    local desc="$1" expected_out="$2" expected_err="$3" expected_exit="$4"
    shift 4

    actual_out=$(   "$@" 2>/tmp/mg_err); actual_exit=$?
    actual_err=$(cat /tmp/mg_err)

    if [ "$actual_out"  != "$expected_out"  ] ||
       [ "$actual_err"  != "$expected_err"  ] ||
       [ "$actual_exit" != "$expected_exit" ]; then
        echo "FAIL: $desc"
        [ "$actual_out"  != "$expected_out"  ] && echo "  stdout: got '$actual_out' want '$expected_out'"
        [ "$actual_err"  != "$expected_err"  ] && echo "  stderr: got '$actual_err' want '$expected_err'"
        [ "$actual_exit" != "$expected_exit" ] && echo "  exit:   got $actual_exit want $expected_exit"
        FAIL=$((FAIL+1))
    else
        echo "PASS: $desc"
        PASS=$((PASS+1))
    fi
}

# Example test cases for mini-grep
GREP="$1"   # path to mini-grep binary passed as first argument

check "literal match - single file" \
      "hello world" "" 0 \
      "$GREP" "hello" fixtures/simple.txt

check "no match exits 1" \
      "" "" 1 \
      "$GREP" "zzznomatch" fixtures/simple.txt

check "missing file diagnostic" \
      "" "mini-grep: nofile.txt: No such file or directory" 2 \
      "$GREP" "foo" nofile.txt

check "line numbers with -n" \
      "2:hello world" "" 0 \
      "$GREP" -n "hello" fixtures/numbered.txt

echo "Results: $PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]
```

Key patterns:
- capture stderr to a temp file (`2>/tmp/mg_err`) then read it back
- compare `$?` immediately after the command
- use `diff` for multi-line golden output comparisons

## 3) Regression testing essentials

A strong regression test is:
- small
- deterministic
- focused on one previously broken behavior
- fast enough for frequent execution

Avoid giant mixed-purpose tests that are hard to diagnose when failing.

## 4) Coverage dimensions for mini-grep

A complete test matrix covers these axes:

| Axis              | Cases to test                                              |
|-------------------|------------------------------------------------------------|
| Pattern type      | literal, dot wildcard, empty pattern                       |
| File count        | stdin only, single file, multiple files                    |
| Flags             | none, `-n`, `-i`, `-ni`, `-h`                              |
| Error paths       | missing file, unreadable file, missing PATTERN arg         |
| Exit codes        | 0 (match), 1 (no match), 1 (partial fail), 2 (all error)  |
| Output format     | no prefix, filename prefix, line number prefix, combined   |

Each cell in this matrix is one test case.  Start with the happy path
(literal match, single file, no flags), then systematically add error paths.

## 5) Golden-output tradeoffs

Pros:
- easy to read and compare
- catches formatting regressions quickly

Cons:
- brittle when formatting intentionally changes
- can hide semantic intent if snapshots are too large

Keep golden expectations minimal and purposeful.

## Common mistakes

- Checking stdout but forgetting to capture and assert stderr separately.
- Using non-deterministic fixtures (e.g., generated at test time with `date`
  or random content); fixture files should be committed and static.
- Mixing multiple behavioural assertions into one opaque test block — when it
  fails you can't tell which assertion failed.
- Not testing error paths: missing file, bad flags, missing PATTERN.
- Assuming unit tests for `matcher_match_line` cover the full CLI behaviour
  (they don't — exit codes and output formatting require integration tests).
- Hardcoding the binary path; accept it as `$1` so CI can override.

## C vs C++

- Regardless of implementation language, CLI integration behaviour is
  validated externally as process-level black-box tests.
- C++ projects can use BATS, pytest subprocess tests, or Google Test's
  `Process` fixtures; shell scripts work just as well and have zero
  additional dependencies.
- The three-stream contract (stdout/stderr/exit code) is language-agnostic
  and should be tested for any compiled CLI tool.
