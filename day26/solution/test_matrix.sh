#!/bin/bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <path-to-mini-grep>" >&2
  exit 2
fi

BIN="$1"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
FIX="$SCRIPT_DIR/fixtures"

PASS=0
FAIL=0

check() {
  local desc="$1"
  local expected_exit="$2"
  local expected_output="$3"
  shift 3

  if [ "${1:-}" != "--" ]; then
    echo "Internal error: missing -- separator in check() for '$desc'" >&2
    exit 99
  fi
  shift

  local out_file
  local err_file
  local rc
  local actual_output

  out_file="$(mktemp)"
  err_file="$(mktemp)"

  set +e
  "$@" >"$out_file" 2>"$err_file"
  rc=$?
  set -e

  actual_output="$(cat "$out_file")"

  if [ "$rc" -eq "$expected_exit" ] && [ "$actual_output" = "$expected_output" ]; then
    echo "PASS: $desc"
    PASS=$((PASS + 1))
  else
    echo "FAIL: $desc"
    echo "  expected exit: $expected_exit"
    echo "  actual exit  : $rc"
    echo "  expected out : [$expected_output]"
    echo "  actual out   : [$actual_output]"
    echo "  stderr       : [$(cat "$err_file")]"
    FAIL=$((FAIL + 1))
  fi

  rm -f "$out_file" "$err_file"
}

check_help_contains_usage() {
  local desc="$1"
  local out_file
  local err_file
  local rc

  out_file="$(mktemp)"
  err_file="$(mktemp)"

  set +e
  "$BIN" -h >"$out_file" 2>"$err_file"
  rc=$?
  set -e

  if [ "$rc" -eq 0 ] && grep -q "Usage:" "$out_file"; then
    echo "PASS: $desc"
    PASS=$((PASS + 1))
  else
    echo "FAIL: $desc"
    echo "  expected exit: 0 and usage text on stdout"
    echo "  actual exit  : $rc"
    echo "  stdout       : [$(cat "$out_file")]"
    echo "  stderr       : [$(cat "$err_file")]"
    FAIL=$((FAIL + 1))
  fi

  rm -f "$out_file" "$err_file"
}

check_nonexistent_file_error() {
  local desc="$1"
  local out_file
  local err_file
  local rc
  local missing="$SCRIPT_DIR/fixtures/does_not_exist.txt"

  out_file="$(mktemp)"
  err_file="$(mktemp)"

  set +e
  "$BIN" "apple" "$missing" >"$out_file" 2>"$err_file"
  rc=$?
  set -e

  if { [ "$rc" -eq 1 ] || [ "$rc" -eq 2 ]; } && grep -q "$missing" "$err_file"; then
    echo "PASS: $desc"
    PASS=$((PASS + 1))
  else
    echo "FAIL: $desc"
    echo "  expected exit: 1 or 2 with stderr mentioning missing file"
    echo "  actual exit  : $rc"
    echo "  stdout       : [$(cat "$out_file")]"
    echo "  stderr       : [$(cat "$err_file")]"
    FAIL=$((FAIL + 1))
  fi

  rm -f "$out_file" "$err_file"
}

# 1) Pattern found in single_line.txt
check "single file exact match" 0 "hello world" -- "$BIN" "hello" "$FIX/single_line.txt"

# 2) Pattern not found
check "single file no match" 1 "" -- "$BIN" "zzz" "$FIX/single_line.txt"

# 3) Multiple matches in multiline.txt
check "multiline case-sensitive banana" 0 "banana split" -- "$BIN" "banana" "$FIX/multiline.txt"

# 4) Case-insensitive match
check "multiline case-insensitive banana" 0 $'Banana\nbanana split' -- "$BIN" "-i" "banana" "$FIX/multiline.txt"

# 5) -n flag single match line number
check "-n line numbers" 0 "4:banana split" -- "$BIN" "-n" "banana" "$FIX/multiline.txt"

# 6) -n + -i combined
check "-n -i combined" 0 $'2:Banana\n4:banana split' -- "$BIN" "-n" "-i" "banana" "$FIX/multiline.txt"

# 7) Pattern found at first line in multiline
check "first-line match" 0 "apple" -- "$BIN" "apple" "$FIX/multiline.txt"

# 8) Case-insensitive APPLE across two lines
check "apple with -i" 0 $'apple\nAPPLE PIE' -- "$BIN" "-i" "apple" "$FIX/multiline.txt"

# 9) Empty file no output
check "empty file no match" 1 "" -- "$BIN" "apple" "$FIX/empty.txt"

# 10) ASCII fixture match
check "unicode_safe ascii word" 0 "cafe" -- "$BIN" "cafe" "$FIX/unicode_safe.txt"

# 11) Pattern not found in ascii fixture
check "unicode_safe miss" 1 "" -- "$BIN" "jalapeno" "$FIX/unicode_safe.txt"

# 12) stdin mode match
check "stdin single match" 0 "apple" -- bash -c "printf 'x\napple\ny\n' | \"$BIN\" apple"

# 13) stdin mode no match
check "stdin no match" 1 "" -- bash -c "printf 'x\ny\n' | \"$BIN\" apple"

# 14) No pattern argument should be usage error
check "missing pattern arg" 2 "" -- "$BIN"

# 15) Help output
check_help_contains_usage "help option prints usage"

# 16) Nonexistent file must report stderr and non-zero exit
check_nonexistent_file_error "nonexistent file diagnostics"

echo
echo "Summary: PASS=$PASS FAIL=$FAIL"

if [ "$FAIL" -eq 0 ]; then
  exit 0
fi
exit 1
