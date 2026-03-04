#!/bin/bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <path-to-mini-grep>" >&2
  exit 2
fi

BIN="$1"
PASS=0
FAIL=0

run_case() {
  local desc="$1"
  shift

  local out_file err_file rc
  out_file="$(mktemp)"
  err_file="$(mktemp)"

  set +e
  "$@" >"$out_file" 2>"$err_file"
  rc=$?
  set -e

  if [ "$rc" -eq 139 ] || [ "$rc" -eq 134 ]; then
    echo "FAIL: $desc (crash exit=$rc)"
    echo "  stdout: [$(cat "$out_file")]"
    echo "  stderr: [$(cat "$err_file")]"
    FAIL=$((FAIL + 1))
  else
    echo "PASS: $desc (exit=$rc)"
    PASS=$((PASS + 1))
  fi

  rm -f "$out_file" "$err_file"
}

# 1) Extremely long pattern
LONG_PAT="$(head -c 100000 /dev/urandom | base64 | tr -d '\n' | cut -c1-100000)"
run_case "extremely long pattern" "$BIN" "$LONG_PAT" /etc/hosts

# 2) Binary input file
run_case "binary input file /usr/bin/env" "$BIN" "pattern" /usr/bin/env

# 3) Continuous random stream via stdin
set +e
head -c 5000000 /dev/urandom | "$BIN" "match" >/tmp/day30_stream_out.txt 2>/tmp/day30_stream_err.txt
RC_STREAM=$?
set -e
if [ "$RC_STREAM" -eq 139 ] || [ "$RC_STREAM" -eq 134 ]; then
  echo "FAIL: continuous stream random input (crash exit=$RC_STREAM)"
  echo "  stderr: [$(cat /tmp/day30_stream_err.txt)]"
  FAIL=$((FAIL + 1))
else
  echo "PASS: continuous stream random input (exit=$RC_STREAM)"
  PASS=$((PASS + 1))
fi
rm -f /tmp/day30_stream_out.txt /tmp/day30_stream_err.txt

# 4) Missing arguments
run_case "missing arguments" "$BIN"

# 5) Over 1000 file arguments
ARGS=()
for i in $(seq 1 1000); do
  ARGS+=("$i")
done
run_case "over 1000 file arguments" "$BIN" "pattern" "${ARGS[@]}"

echo
echo "Summary: PASS=$PASS FAIL=$FAIL"

if [ "$FAIL" -eq 0 ]; then
  echo "PASS: stress suite found no crashes."
  exit 0
fi
echo "FAIL: stress suite detected crash exits."
exit 1
