#include "cli.h"

#include <stdbool.h>
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

static void assert_i_eq(int actual, int expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%d, actual=%d)\n",
                test_name,
                detail,
                expected,
                actual);
    }
}

static void assert_str_eq(const char* actual, const char* expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual == NULL || expected == NULL || strcmp(actual, expected) != 0) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=\"%s\", actual=\"%s\")\n",
                test_name,
                detail,
                expected ? expected : "(null)",
                actual ? actual : "(null)");
    }
}

static int parse_synth(int argc, char* argv[], cli_opts_t* out) {
    memset(out, 0, sizeof(*out));
    return cli_parse(argc, argv, out);
}

static void test_pattern_only(void) {
    char* argv[] = {"mg", "PATTERN"};
    cli_opts_t o;
    assert_i_eq(parse_synth(2, argv, &o), 0, "test_pattern_only", "cli_parse returns 0");
    assert_true(!o.flag_n, "test_pattern_only", "-n should be false");
    assert_true(!o.flag_i, "test_pattern_only", "-i should be false");
    assert_str_eq(o.pattern, "PATTERN", "test_pattern_only", "pattern parsed");
    assert_i_eq(o.files_count, 0, "test_pattern_only", "files_count should be 0");
}

static void test_pattern_with_files(void) {
    char* argv[] = {"mg", "PATTERN", "f1", "f2"};
    cli_opts_t o;
    assert_i_eq(parse_synth(4, argv, &o), 0, "test_pattern_with_files", "cli_parse returns 0");
    assert_str_eq(o.pattern, "PATTERN", "test_pattern_with_files", "pattern parsed");
    assert_i_eq(o.files_count, 2, "test_pattern_with_files", "two files");
    assert_str_eq(o.files[0], "f1", "test_pattern_with_files", "file 0");
    assert_str_eq(o.files[1], "f2", "test_pattern_with_files", "file 1");
}

static void test_all_flags_then_pattern(void) {
    char* argv[] = {"mg", "-n", "-i", "PATTERN", "f1"};
    cli_opts_t o;
    assert_i_eq(parse_synth(5, argv, &o), 0, "test_all_flags_then_pattern", "cli_parse returns 0");
    assert_true(o.flag_n, "test_all_flags_then_pattern", "-n set");
    assert_true(o.flag_i, "test_all_flags_then_pattern", "-i set");
    assert_str_eq(o.pattern, "PATTERN", "test_all_flags_then_pattern", "pattern parsed");
    assert_i_eq(o.files_count, 1, "test_all_flags_then_pattern", "one file");
    assert_str_eq(o.files[0], "f1", "test_all_flags_then_pattern", "file parsed");
}

static void test_flags_after_pattern_treated_as_file(void) {
    char* argv[] = {"mg", "PATTERN", "-n"};
    cli_opts_t o;
    assert_i_eq(parse_synth(3, argv, &o), 0, "test_flags_after_pattern_treated_as_file", "cli_parse returns 0");
    assert_str_eq(o.pattern, "PATTERN", "test_flags_after_pattern_treated_as_file", "pattern parsed");
    assert_true(!o.flag_n, "test_flags_after_pattern_treated_as_file", "flag_n should remain false");
    assert_i_eq(o.files_count, 1, "test_flags_after_pattern_treated_as_file", "one trailing token file");
    assert_str_eq(o.files[0], "-n", "test_flags_after_pattern_treated_as_file", "-n treated as file");
}

static void test_flag_n_only(void) {
    char* argv[] = {"mg", "-n", "x"};
    cli_opts_t o;
    assert_i_eq(parse_synth(3, argv, &o), 0, "test_flag_n_only", "cli_parse returns 0");
    assert_true(o.flag_n, "test_flag_n_only", "flag_n true");
    assert_true(!o.flag_i, "test_flag_n_only", "flag_i false");
    assert_str_eq(o.pattern, "x", "test_flag_n_only", "pattern x");
}

/* Manual tests (not automated here):
   - Unknown flag, e.g. ./mg -z PATTERN -> expect stderr error and exit(2)
   - Missing pattern, e.g. ./mg -n       -> expect usage and exit(1)
   - Help, e.g. ./mg -h                  -> expect usage and exit(0) */

int main(void) {
    test_pattern_only();
    test_pattern_with_files();
    test_all_flags_then_pattern();
    test_flags_after_pattern_treated_as_file();
    test_flag_n_only();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
