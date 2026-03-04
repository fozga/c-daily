#include "parser.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
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

static void assert_i32_eq(int32_t actual, int32_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%d, actual=%d)\n",
                test_name,
                detail,
                (int)expected,
                (int)actual);
    }
}

static void assert_err_eq(parser_err_t actual, parser_err_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%d, actual=%d)\n",
                test_name,
                detail,
                (int)expected,
                (int)actual);
    }
}

static void test_parse_i32_valid_numbers(void) {
    int32_t out = 0;

    errno = 0;
    assert_err_eq(parse_i32("0", &out), PARSE_OK, "test_parse_i32_valid_numbers", "parse zero should succeed");
    assert_i32_eq(out, 0, "test_parse_i32_valid_numbers", "parsed zero");

    errno = 0;
    assert_err_eq(parse_i32("12345", &out), PARSE_OK, "test_parse_i32_valid_numbers", "parse positive should succeed");
    assert_i32_eq(out, 12345, "test_parse_i32_valid_numbers", "parsed positive value");

    errno = 0;
    assert_err_eq(parse_i32("-77", &out), PARSE_OK, "test_parse_i32_valid_numbers", "parse negative should succeed");
    assert_i32_eq(out, -77, "test_parse_i32_valid_numbers", "parsed negative value");
}

static void test_parse_i32_null_ptrs(void) {
    int32_t out = 0;

    errno = 0;
    assert_err_eq(parse_i32(NULL, &out), PARSE_ERR_NULL_PTR, "test_parse_i32_null_ptrs", "NULL string should fail");

    errno = 0;
    assert_err_eq(parse_i32("10", NULL), PARSE_ERR_NULL_PTR, "test_parse_i32_null_ptrs", "NULL out pointer should fail");
}

static void test_parse_i32_invalid_format(void) {
    int32_t out = 0;

    errno = 0;
    assert_err_eq(parse_i32("123abc", &out), PARSE_ERR_INVALID_FMT, "test_parse_i32_invalid_format", "trailing junk should fail");

    errno = 0;
    assert_err_eq(parse_i32("hello", &out), PARSE_ERR_INVALID_FMT, "test_parse_i32_invalid_format", "nonnumeric should fail");
}

static void test_parse_i32_overflow_sets_errno(void) {
    int32_t out = 0;

    errno = 0;
    assert_err_eq(parse_i32("9999999999999", &out),
                  PARSE_ERR_OUT_OF_RANGE,
                  "test_parse_i32_overflow_sets_errno",
                  "overflow should report out-of-range");
    assert_true(errno == ERANGE,
                "test_parse_i32_overflow_sets_errno",
                "overflow must set errno to ERANGE");
}

static void test_parse_kvp_valid_split(void) {
    char input[] = "timeout=30";
    char* key = NULL;
    char* val = NULL;

    errno = 0;
    assert_err_eq(parse_kvp(input, &key, &val), PARSE_OK, "test_parse_kvp_valid_split", "valid key=value should succeed");
    assert_true(key == input, "test_parse_kvp_valid_split", "key should point to input start");
    assert_true(val == &input[8], "test_parse_kvp_valid_split", "value should point after '='");
    assert_true(input[7] == '\0', "test_parse_kvp_valid_split", "split should write NUL over delimiter");
}

static void test_parse_kvp_missing_delimiter(void) {
    char input[] = "timeout30";
    char* key = NULL;
    char* val = NULL;

    errno = 0;
    assert_err_eq(parse_kvp(input, &key, &val),
                  PARSE_ERR_INVALID_FMT,
                  "test_parse_kvp_missing_delimiter",
                  "missing '=' should fail");
}

static void test_parse_kvp_null_ptrs(void) {
    char input[] = "a=b";
    char* key = NULL;
    char* val = NULL;

    errno = 0;
    assert_err_eq(parse_kvp(NULL, &key, &val), PARSE_ERR_NULL_PTR, "test_parse_kvp_null_ptrs", "NULL str should fail");

    errno = 0;
    assert_err_eq(parse_kvp(input, NULL, &val), PARSE_ERR_NULL_PTR, "test_parse_kvp_null_ptrs", "NULL out_key should fail");

    errno = 0;
    assert_err_eq(parse_kvp(input, &key, NULL), PARSE_ERR_NULL_PTR, "test_parse_kvp_null_ptrs", "NULL out_val should fail");
}

int main(void) {
    test_parse_i32_valid_numbers();
    test_parse_i32_null_ptrs();
    test_parse_i32_invalid_format();
    test_parse_i32_overflow_sets_errno();

    test_parse_kvp_valid_split();
    test_parse_kvp_missing_delimiter();
    test_parse_kvp_null_ptrs();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
