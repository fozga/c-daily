# Day 30 Notes - Stress testing and release hardening

## 1) Fuzzing and stress-testing mindset

Deterministic unit tests confirm that *known* inputs produce *known* outputs.
Stress tests probe the unknown — the inputs you did not think to write a test
for.

Three complementary strategies:

| Technique | What it finds |
|---|---|
| Structured stress testing | Logic errors under load, race conditions |
| Random/fuzz input | Unexpected edge conditions, buffer overruns |
| Boundary sweeping | Off-by-one errors, empty/max-size inputs |

Random data generators (`/dev/urandom`, `dd`) are an easy first step.  More
advanced fuzz frameworks (AFL++, libFuzzer) instrument the binary to guide
mutation toward unexplored code paths.

### Example: minimal stress test shell loop

```bash
#!/usr/bin/env bash
# stress_test.sh  — run BINARY against hostile inputs and check exit codes.
BINARY=${1:?usage: stress_test.sh <binary>}
PASS=0
FAIL=0

run() {
    local desc="$1"; shift
    "$@"
    local code=$?
    if [ $code -eq 139 ] || [ $code -eq 134 ]; then
        echo "CRASH ($code): $desc"
        FAIL=$((FAIL + 1))
    else
        echo "OK    ($code): $desc"
        PASS=$((PASS + 1))
    fi
}

# 1. Empty pattern
run "empty pattern"          "$BINARY" "" /dev/null

# 2. Very long pattern (> typical stack buffer)
run "long pattern"           "$BINARY" "$(python3 -c 'print("A"*8192)')" /dev/null

# 3. Binary stream as input
run "binary stdin"           "$BINARY" "hello" <(dd if=/dev/urandom bs=4096 count=1 2>/dev/null)

# 4. Nonexistent file
run "missing file"           "$BINARY" "pattern" /tmp/no_such_file_xyz

# 5. Pattern with special regex chars
run "special chars"          "$BINARY" '.*[' /dev/null

# 6. No arguments
run "no args"                "$BINARY"

echo "---"
echo "passed: $PASS  failed: $FAIL"
[ $FAIL -eq 0 ]
```

Exit codes 0, 1, and 2 are **acceptable** (match/no-match/usage error).
Exit code 139 (segfault) and 134 (abort/assertion) are **failures**.

## 2) Binary data and C string APIs

If raw binary bytes include `\0`, C string functions (`strlen`, `strstr`)
treat that byte as end-of-string.  This can shorten apparent input, but
the program must still remain memory-safe.

Key principle:
- semantic oddity is acceptable
- memory unsafety is not

Specific checks to harden:

```c
/* Validate pattern is not unreasonably long before copying */
if (strlen(pattern) > MAX_PATTERN_LEN) {
    fprintf(stderr, "error: pattern too long\n");
    return 2;
}

/* Guard fgets buffer size — never pass 0 */
while (fgets(line, sizeof(line), fp)) {
    /* process partial lines when line > sizeof(line)-1 safely */
}
```

## 3) Very long lines

`fgets(buf, N, fp)` reads at most `N-1` bytes per call.  When a line exceeds
the buffer, `fgets` returns a partial line without a `\n` at the end.  A
robust scanner must handle this gracefully:

- Either skip extra bytes with a loop until `\n` or EOF is reached.
- Or treat each partial chunk independently (acceptable for grep-style tools
  where any match inside the chunk still counts).

Silently assuming one `fgets` call equals one logical line causes missed
matches and potential double-counting bugs.

## 4) ASan + GDB crash hardening workflow

Typical crash-fix loop:

```
1. Compile with: -fsanitize=address,undefined -g
2. Run stress_test.sh
3. When ASan or a signal fires, read the stack trace
4. Use GDB: run with same args, `bt` after crash to get exact line
5. Fix root cause — validate inputs, add NULL checks, bound buffers
6. Re-run stress_test.sh until all cases show exit 0/1/2
7. Re-run under Valgrind to confirm no residual leaks
```

Never strip the binary before resolving all crashes — you will lose symbol
names and line numbers.

## 5) Release build posture

Typical release adjustments:

```bash
# Optimised release build
gcc -O2 -DNDEBUG -o mini-grep *.c

# Strip symbols to reduce binary size (AFTER all crashes are resolved)
strip mini-grep

# Quick sanity check after strip
./mini-grep "hello" /etc/hostname
```

Flags to be aware of:

- `-O2`: enables safe-and-useful optimisations without breaking standard code.
- `-DNDEBUG`: disables `assert()` calls — only safe after thorough testing.
- `strip`: removes debug symbols, shrinks binary, makes post-crash GDB sessions
  much harder.

## 6) Release notes and retrospectives

A useful retrospective documents:

- top bugs found late and their root causes
- which tool (ASan / Valgrind / GDB) found what, and when
- architecture trade-offs made during the project
- what would be improved in a second pass

Writing a retrospective makes tacit knowledge explicit and transferable.

## Common mistakes

- Treating stress failures as "rare edge cases" and shipping anyway.
- Equating "no crash" with correctness — silent wrong results also matter.
- Running the stress script only once (race conditions are timing-dependent).
- Stripping the binary before all crashes are resolved.
- Passing `NULL` to string functions without prior NULL checks.
- Using `assert` for user-input validation — assertions are disabled in
  release builds and should never guard external input.

## C vs C++

C and C++ share the same stress-testing philosophy, but C provides fewer
runtime safety rails:

| Concern | C | C++ |
|---|---|---|
| Buffer overflows | Manual bounds checking required | `std::string`, `std::vector` with `.at()` throw exceptions |
| NULL dereference | Undefined behaviour; relies on tooling | Same UB, but smart pointers reduce frequency |
| Assertion safety | `assert` silently removed with `-DNDEBUG` | Same; but `std::terminate` / exceptions may catch more |
| Fuzz coverage | Same exposure for both | RAII reduces leak surface |

Because C has fewer automatic protections, stress testing and sanitizer
passes are even more valuable in C codebases than in C++ ones.
