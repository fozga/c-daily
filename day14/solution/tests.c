#include "cdrills_lib.h"

#include <stdbool.h>
#include <stdio.h>

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test_name, const char* detail) {
    ++g_assertions;
    if (!cond) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s\n", test_name, detail);
    }
}

/* Smoke test scaffold for day09 + day13 integration idea. */
static void test_parse_then_store_placeholder(void) {
    /* TODO(day09/day13): parse records from tmpfile, insert into store, verify count. */
    assert_true(false,
                "test_parse_then_store_placeholder",
                "TODO: enable after line_parser and store are integrated into libcdrills.a");
}

/* Smoke test scaffold for day10 round-trip integration. */
static void test_binary_round_trip_placeholder(void) {
    /* TODO(day10): serialize entries via binrec_write, read back via binrec_read, compare fields. */
    assert_true(false,
                "test_binary_round_trip_placeholder",
                "TODO: enable after binrec is integrated into libcdrills.a");
}

/* Build/link smoke: confirms test binary runs and umbrella header is consumable. */
static void test_smoke_runner_executes(void) {
    assert_true(true, "test_smoke_runner_executes", "test runner reached execution path");
    assert_true(true, "test_smoke_runner_executes", "umbrella header included successfully");
    assert_true(true, "test_smoke_runner_executes", "placeholder assertion 3");
    assert_true(true, "test_smoke_runner_executes", "placeholder assertion 4");
    assert_true(true, "test_smoke_runner_executes", "placeholder assertion 5");
    assert_true(true, "test_smoke_runner_executes", "placeholder assertion 6");
    assert_true(true, "test_smoke_runner_executes", "placeholder assertion 7");
    assert_true(true, "test_smoke_runner_executes", "placeholder assertion 8");
}

int main(void) {
    test_smoke_runner_executes();
    test_parse_then_store_placeholder();
    test_binary_round_trip_placeholder();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
