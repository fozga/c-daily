#include "matcher2.h"

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

static void test_day23_literal_and_dot_compat(void) {
    matcher2_t m1;
    matcher2_t m2;
    matcher2_t m3;

    assert_true(matcher2_init(&m1, "ana", false), "test_day23_literal_and_dot_compat", "init literal");
    assert_true(matcher2_match_line(&m1, "banana"), "test_day23_literal_and_dot_compat", "literal middle");
    assert_true(!matcher2_match_line(&m1, "xyz"), "test_day23_literal_and_dot_compat", "literal not found");
    matcher2_destroy(&m1);

    assert_true(matcher2_init(&m2, "a.c", false), "test_day23_literal_and_dot_compat", "init dot wildcard");
    assert_true(matcher2_match_line(&m2, "abc"), "test_day23_literal_and_dot_compat", "dot matches abc");
    assert_true(matcher2_match_line(&m2, "axc"), "test_day23_literal_and_dot_compat", "dot matches axc");
    assert_true(!matcher2_match_line(&m2, "ac"), "test_day23_literal_and_dot_compat", "dot requires one char");
    matcher2_destroy(&m2);

    assert_true(matcher2_init(&m3, "FOO", true), "test_day23_literal_and_dot_compat", "init ci");
    assert_true(matcher2_match_line(&m3, "foobar"), "test_day23_literal_and_dot_compat", "ci literal");
    matcher2_destroy(&m3);
}

static void test_class_set_abc(void) {
    matcher2_t m;
    assert_true(matcher2_init(&m, "[abc]", false), "test_class_set_abc", "init [abc]");
    assert_true(matcher2_match_line(&m, "a"), "test_class_set_abc", "class matches a");
    assert_true(matcher2_match_line(&m, "b"), "test_class_set_abc", "class matches b");
    assert_true(matcher2_match_line(&m, "c"), "test_class_set_abc", "class matches c");
    assert_true(!matcher2_match_line(&m, "d"), "test_class_set_abc", "class does not match d");
    matcher2_destroy(&m);
}

static void test_class_range_az(void) {
    matcher2_t m;
    assert_true(matcher2_init(&m, "[a-z]", false), "test_class_range_az", "init [a-z]");
    assert_true(matcher2_match_line(&m, "m"), "test_class_range_az", "range matches lowercase");
    assert_true(!matcher2_match_line(&m, "M"), "test_class_range_az", "range excludes uppercase");
    assert_true(!matcher2_match_line(&m, "7"), "test_class_range_az", "range excludes digit");
    matcher2_destroy(&m);
}

static void test_negated_class(void) {
    matcher2_t m;
    assert_true(matcher2_init(&m, "[^abc]", false), "test_negated_class", "init negated");
    assert_true(!matcher2_match_line(&m, "a"), "test_negated_class", "negated excludes a");
    assert_true(!matcher2_match_line(&m, "b"), "test_negated_class", "negated excludes b");
    assert_true(!matcher2_match_line(&m, "c"), "test_negated_class", "negated excludes c");
    assert_true(matcher2_match_line(&m, "d"), "test_negated_class", "negated matches d");
    matcher2_destroy(&m);
}

static void test_escapes(void) {
    matcher2_t m_tab;
    matcher2_t m_nl;
    assert_true(matcher2_init(&m_tab, "\\t", false), "test_escapes", "init tab escape");
    assert_true(matcher2_match_line(&m_tab, "\t"), "test_escapes", "tab escape matches tab");
    matcher2_destroy(&m_tab);

    assert_true(matcher2_init(&m_nl, "\\n", false), "test_escapes", "init newline escape");
    assert_true(matcher2_match_line(&m_nl, "\n"), "test_escapes", "newline escape matches newline");
    matcher2_destroy(&m_nl);
}

static void test_malformed_class_no_closing_bracket(void) {
    matcher2_t m;
    assert_true(matcher2_init(&m, "[abc", false), "test_malformed_class_no_closing_bracket", "init malformed class");
    /* Defined behavior for this exercise: malformed class should not crash and should not match. */
    assert_true(!matcher2_match_line(&m, "a"),
                "test_malformed_class_no_closing_bracket",
                "malformed class returns no match");
    matcher2_destroy(&m);
}

int main(void) {
    test_day23_literal_and_dot_compat();
    test_class_set_abc();
    test_class_range_az();
    test_negated_class();
    test_escapes();
    test_malformed_class_no_closing_bracket();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
