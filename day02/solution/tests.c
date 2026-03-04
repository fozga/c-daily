#include "buggy_numeric.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int failures = 0;

static void fail_msg(const char* name, const char* msg) {
    ++failures;
    fprintf(stderr, "[FAIL] %s: %s\n", name, msg);
}

static void expect_true(const char* name, int condition, const char* msg) {
    if (!condition) {
        fail_msg(name, msg);
    }
}

static void test_add_positive_overflow(void) {
    int32_t out = 0;
    int rc = bn_add_int32_checked(INT32_MAX, 1, &out);
    expect_true("test_add_positive_overflow", rc != 0, "expected overflow error");
}

static void test_add_negative_overflow(void) {
    int32_t out = 0;
    int rc = bn_add_int32_checked(INT32_MIN, -1, &out);
    expect_true("test_add_negative_overflow", rc != 0, "expected underflow error");
}

static void test_mean_large_values_case1(void) {
    const int32_t xs[] = {INT32_MAX, INT32_MAX};
    int32_t mean = 0;
    int rc = bn_mean_i32(xs, 2u, &mean);
    expect_true("test_mean_large_values_case1", rc == 0, "mean should succeed");
    expect_true("test_mean_large_values_case1", mean == INT32_MAX, "mean mismatch for large equal values");
}

static void test_mean_large_values_case2(void) {
    const int32_t xs[] = {INT32_MAX, INT32_MAX, 2};
    int32_t mean = 0;
    int rc = bn_mean_i32(xs, 3u, &mean);
    expect_true("test_mean_large_values_case2", rc == 0, "mean should succeed");
    expect_true("test_mean_large_values_case2", mean == 1431655765, "mean mismatch when naive sum overflows");
}

static void test_parse_invalid_trailing_garbage(void) {
    uint32_t out = 0;
    int rc = bn_parse_u32("123abc", &out);
    expect_true("test_parse_invalid_trailing_garbage", rc != 0, "expected parse failure for trailing garbage");
}

static void test_parse_invalid_plus_sign(void) {
    uint32_t out = 0;
    int rc = bn_parse_u32("+42", &out);
    expect_true("test_parse_invalid_plus_sign", rc != 0, "expected parse failure for '+' prefix");
}

static void test_parse_valid_zero(void) {
    uint32_t out = 999u;
    int rc = bn_parse_u32("0", &out);
    expect_true("test_parse_valid_zero", rc == 0, "expected success for 0");
    expect_true("test_parse_valid_zero", out == 0u, "expected parsed value 0");
}

static void test_parse_valid_uint32_max(void) {
    uint32_t out = 0u;
    int rc = bn_parse_u32("4294967295", &out);
    expect_true("test_parse_valid_uint32_max", rc == 0, "expected success for UINT32_MAX");
    expect_true("test_parse_valid_uint32_max", out == UINT32_MAX, "expected UINT32_MAX parsed value");
}

int main(void) {
    test_add_positive_overflow();
    test_add_negative_overflow();

    test_mean_large_values_case1();
    test_mean_large_values_case2();

    test_parse_invalid_trailing_garbage();
    test_parse_invalid_plus_sign();

    test_parse_valid_zero();
    test_parse_valid_uint32_max();

    /* Add at least 6 more tests. */

    if (failures != 0) {
        fprintf(stderr, "\nTotal failures: %d\n", failures);
        return 1;
    }

    printf("All tests passed.\n");
    return 0;
}
