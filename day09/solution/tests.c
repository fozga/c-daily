#include "line_parser.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test_name, const char* detail) {
    ++g_assertions;
    if (!cond) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s\n", test_name, detail);
    }
}

static void assert_err_eq(lp_err_t actual, lp_err_t expected, const char* test_name, const char* detail) {
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

static void assert_double_eq(double actual, double expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%.6f, actual=%.6f)\n",
                test_name,
                detail,
                expected,
                actual);
    }
}

static void test_parse_record_valid_positive_id(void) {
    lp_record_t rec = {0};
    lp_err_t err = lp_parse_record("42,alice,99.5", &rec);
    assert_err_eq(err, LP_OK, "test_parse_record_valid_positive_id", "valid line should parse");
    assert_i32_eq(rec.id, 42, "test_parse_record_valid_positive_id", "id parsed");
    assert_double_eq(rec.score, 99.5, "test_parse_record_valid_positive_id", "score parsed");
}

static void test_parse_record_valid_negative_score(void) {
    lp_record_t rec = {0};
    lp_err_t err = lp_parse_record("7,bob,-3.25", &rec);
    assert_err_eq(err, LP_OK, "test_parse_record_valid_negative_score", "negative score should parse");
    assert_i32_eq(rec.id, 7, "test_parse_record_valid_negative_score", "id parsed");
    assert_double_eq(rec.score, -3.25, "test_parse_record_valid_negative_score", "negative score parsed");
}

static void test_parse_record_valid_spaces_in_name(void) {
    lp_record_t rec = {0};
    lp_err_t err = lp_parse_record("11,Jane Doe,1.0", &rec);
    assert_err_eq(err, LP_OK, "test_parse_record_valid_spaces_in_name", "name with spaces should parse");
    assert_i32_eq(rec.id, 11, "test_parse_record_valid_spaces_in_name", "id parsed");
}

static void test_parse_record_null_args(void) {
    lp_record_t rec = {0};
    assert_err_eq(lp_parse_record(NULL, &rec), LP_ERR_NULL, "test_parse_record_null_args", "NULL line");
    assert_err_eq(lp_parse_record("1,a,2", NULL), LP_ERR_NULL, "test_parse_record_null_args", "NULL output");
}

static void test_parse_record_missing_fields(void) {
    lp_record_t rec = {0};
    assert_err_eq(lp_parse_record("1,onlyname", &rec),
                  LP_ERR_INVALID_FMT,
                  "test_parse_record_missing_fields",
                  "missing score should fail");
}

static void test_parse_record_extra_commas(void) {
    lp_record_t rec = {0};
    assert_err_eq(lp_parse_record("1,a,2,extra", &rec),
                  LP_ERR_INVALID_FMT,
                  "test_parse_record_extra_commas",
                  "extra field should fail");
}

static void test_parse_record_non_numeric_id(void) {
    lp_record_t rec = {0};
    assert_err_eq(lp_parse_record("abc,a,2.0", &rec),
                  LP_ERR_INVALID_FMT,
                  "test_parse_record_non_numeric_id",
                  "id must be numeric");
}

static void test_parse_record_score_overflow(void) {
    lp_record_t rec = {0};
    assert_err_eq(lp_parse_record("1,a,1e9999", &rec),
                  LP_ERR_OUT_OF_RANGE,
                  "test_parse_record_score_overflow",
                  "overflowing score should fail with range error");
}

static void test_read_line_null_args(void) {
    char buf[LP_LINE_MAX];
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_read_line_null_args", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    assert_err_eq(lp_read_line(NULL, buf, sizeof(buf)),
                  LP_ERR_NULL,
                  "test_read_line_null_args",
                  "NULL file pointer should fail");
    assert_err_eq(lp_read_line(fp, NULL, sizeof(buf)),
                  LP_ERR_NULL,
                  "test_read_line_null_args",
                  "NULL buffer should fail");
    assert_err_eq(lp_read_line(fp, buf, 0),
                  LP_ERR_NULL,
                  "test_read_line_null_args",
                  "zero-sized buffer should fail");
    fclose(fp);
}

static void test_read_line_success_and_strip_newline(void) {
    char buf[LP_LINE_MAX];
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_read_line_success_and_strip_newline", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    fputs("123,abc,9.0\n", fp);
    rewind(fp);

    assert_err_eq(lp_read_line(fp, buf, sizeof(buf)),
                  LP_OK,
                  "test_read_line_success_and_strip_newline",
                  "first read should succeed");
    assert_true(strcmp(buf, "123,abc,9.0") == 0,
                "test_read_line_success_and_strip_newline",
                "newline should be stripped");
    fclose(fp);
}

static void test_read_line_eof(void) {
    char buf[LP_LINE_MAX];
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_read_line_eof", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    rewind(fp);
    assert_err_eq(lp_read_line(fp, buf, sizeof(buf)),
                  LP_ERR_EOF,
                  "test_read_line_eof",
                  "empty stream should return EOF");
    fclose(fp);
}

static void test_read_line_two_lines(void) {
    char buf[LP_LINE_MAX];
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_read_line_two_lines", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    fputs("1,a,1.0\n2,b,2.0\n", fp);
    rewind(fp);

    assert_err_eq(lp_read_line(fp, buf, sizeof(buf)),
                  LP_OK,
                  "test_read_line_two_lines",
                  "first line read should succeed");
    assert_true(strcmp(buf, "1,a,1.0") == 0,
                "test_read_line_two_lines",
                "first line content");

    assert_err_eq(lp_read_line(fp, buf, sizeof(buf)),
                  LP_OK,
                  "test_read_line_two_lines",
                  "second line read should succeed");
    assert_true(strcmp(buf, "2,b,2.0") == 0,
                "test_read_line_two_lines",
                "second line content");
    fclose(fp);
}

int main(void) {
    test_parse_record_valid_positive_id();
    test_parse_record_valid_negative_score();
    test_parse_record_valid_spaces_in_name();
    test_parse_record_null_args();
    test_parse_record_missing_fields();
    test_parse_record_extra_commas();
    test_parse_record_non_numeric_id();
    test_parse_record_score_overflow();

    test_read_line_null_args();
    test_read_line_success_and_strip_newline();
    test_read_line_eof();
    test_read_line_two_lines();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
