#include "matcher.h"

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

static void test_literal_found_positions(void) {
    matcher_t m;
    assert_true(matcher_init(&m, "ana", false), "test_literal_found_positions", "init matcher");
    assert_true(matcher_match_line(&m, "banana"), "test_literal_found_positions", "found in middle");
    assert_true(matcher_match_line(&m, "analogy"), "test_literal_found_positions", "found at start");
    assert_true(matcher_match_line(&m, "cabana"), "test_literal_found_positions", "found at end-ish");
    assert_true(!matcher_match_line(&m, "xyz"), "test_literal_found_positions", "not found");
    matcher_destroy(&m);
}

static void test_dot_wildcard(void) {
    matcher_t m;
    assert_true(matcher_init(&m, "a.c", false), "test_dot_wildcard", "init matcher");
    assert_true(matcher_match_line(&m, "abc"), "test_dot_wildcard", "a.c matches abc");
    assert_true(matcher_match_line(&m, "axc"), "test_dot_wildcard", "a.c matches axc");
    assert_true(!matcher_match_line(&m, "ac"), "test_dot_wildcard", "a.c does not match ac");
    matcher_destroy(&m);
}

static void test_case_insensitive(void) {
    matcher_t m;
    assert_true(matcher_init(&m, "FOO", true), "test_case_insensitive", "init matcher");
    assert_true(matcher_match_line(&m, "foobar"), "test_case_insensitive", "FOO matches foobar in -i");
    assert_true(matcher_match_line(&m, "xxFoOy"), "test_case_insensitive", "mixed-case match");
    matcher_destroy(&m);
}

static void test_empty_pattern_and_line_sizes(void) {
    matcher_t m_empty;
    matcher_t m_long;
    assert_true(matcher_init(&m_empty, "", false), "test_empty_pattern_and_line_sizes", "init empty pattern");
    assert_true(matcher_match_line(&m_empty, ""), "test_empty_pattern_and_line_sizes", "empty pattern matches empty line");
    assert_true(matcher_match_line(&m_empty, "anything"), "test_empty_pattern_and_line_sizes", "empty pattern matches any line");
    matcher_destroy(&m_empty);

    assert_true(matcher_init(&m_long, "longpattern", false), "test_empty_pattern_and_line_sizes", "init long pattern");
    assert_true(!matcher_match_line(&m_long, "short"),
                "test_empty_pattern_and_line_sizes",
                "pattern longer than line should not match");
    assert_true(!matcher_match_line(&m_long, ""),
                "test_empty_pattern_and_line_sizes",
                "non-empty pattern should not match empty line");
    matcher_destroy(&m_long);
}

int main(void) {
    test_literal_found_positions();
    test_dot_wildcard();
    test_case_insensitive();
    test_empty_pattern_and_line_sizes();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
