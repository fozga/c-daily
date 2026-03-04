#include "strview.h"

#include <stdbool.h>
#include <stddef.h>
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

static void assert_size_eq(size_t actual, size_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s (expected=%zu, actual=%zu)\n", test_name, detail, expected, actual);
    }
}

static void assert_int_eq(int actual, int expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s (expected=%d, actual=%d)\n", test_name, detail, expected, actual);
    }
}

static void assert_sv_eq(strview actual,
                         const char* expected_data,
                         size_t expected_len,
                         const char* test_name,
                         const char* detail) {
    ++g_assertions;

    bool ok = true;
    if (actual.length != expected_len) {
        ok = false;
    }

    if (ok) {
        for (size_t i = 0; i < expected_len; ++i) {
            if (actual.data == NULL || actual.data[i] != expected_data[i]) {
                ok = false;
                break;
            }
        }
    }

    if (!ok) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s (expected_len=%zu, actual_len=%zu)\n",
                test_name,
                detail,
                expected_len,
                actual.length);
    }
}

static void test_sv_from_cstr_null_and_empty(void) {
    strview n = sv_from_cstr(NULL);
    assert_true(n.data == NULL, "test_sv_from_cstr_null_and_empty", "NULL input should produce NULL data");
    assert_size_eq(n.length, 0u, "test_sv_from_cstr_null_and_empty", "NULL input should have length 0");

    strview e = sv_from_cstr("");
    assert_true(e.data != NULL, "test_sv_from_cstr_null_and_empty", "empty string data pointer should be non-NULL literal pointer");
    assert_size_eq(e.length, 0u, "test_sv_from_cstr_null_and_empty", "empty string length should be 0");
}

static void test_sv_equals_cases(void) {
    char a1[] = {'a', 'b', 'c', '\0'};
    char a2[] = {'a', 'b', 'c', '\0'};
    char b1[] = {'a', 'b', '\0'};
    char c1[] = {'a', 'b', 'd', '\0'};

    strview va1 = sv_from_cstr(a1);
    strview va2 = sv_from_cstr(a2);
    strview vb1 = sv_from_cstr(b1);
    strview vc1 = sv_from_cstr(c1);

    assert_true(sv_equals(va1, va2), "test_sv_equals_cases", "identical content at different addresses should be equal");
    assert_true(!sv_equals(va1, vb1), "test_sv_equals_cases", "different lengths should not be equal");
    assert_true(!sv_equals(va1, vc1), "test_sv_equals_cases", "different contents should not be equal");
    assert_true(sv_equals(va1, va1), "test_sv_equals_cases", "same view should be equal to itself");
}

static void test_sv_trim_variants(void) {
    strview no_ws = sv_from_cstr("alpha");
    strview all_ws = sv_from_cstr(" \t\n\r");
    strview lead_ws = sv_from_cstr("\n\tbeta");
    strview trail_ws = sv_from_cstr("gamma  \r\n");

    strview t1 = sv_trim(no_ws);
    assert_sv_eq(t1, "alpha", 5u, "test_sv_trim_variants", "no-whitespace input should be unchanged");

    strview t2 = sv_trim(all_ws);
    assert_size_eq(t2.length, 0u, "test_sv_trim_variants", "all-whitespace input should trim to empty view");

    strview t3 = sv_trim(lead_ws);
    assert_sv_eq(t3, "beta", 4u, "test_sv_trim_variants", "leading whitespace should be removed");

    strview t4 = sv_trim(trail_ws);
    assert_sv_eq(t4, "gamma", 5u, "test_sv_trim_variants", "trailing whitespace should be removed");
}

static void test_sv_find_cases(void) {
    strview s = sv_from_cstr("xyz");
    strview e = sv_from_cstr("");

    assert_int_eq(sv_find(s, 'x'), 0, "test_sv_find_cases", "find first character");
    assert_int_eq(sv_find(s, 'z'), 2, "test_sv_find_cases", "find last character");
    assert_int_eq(sv_find(s, 'q'), -1, "test_sv_find_cases", "missing character should return -1");
    assert_int_eq(sv_find(e, 'a'), -1, "test_sv_find_cases", "empty string should return -1");
}

static void test_sv_split_once_cases(void) {
    strview l = {NULL, 0u};
    strview r = {NULL, 0u};
    static const char left_sentinel[] = "sentinel";
    static const char right_sentinel[] = "sentinel";

    strview middle = sv_from_cstr("left:right");
    assert_true(sv_split_once(middle, ':', &l, &r), "test_sv_split_once_cases", "delimiter in middle should split");
    assert_sv_eq(l, "left", 4u, "test_sv_split_once_cases", "left side middle split");
    assert_sv_eq(r, "right", 5u, "test_sv_split_once_cases", "right side middle split");

    strview at_start = sv_from_cstr(":tail");
    assert_true(sv_split_once(at_start, ':', &l, &r), "test_sv_split_once_cases", "delimiter at start should split");
    assert_size_eq(l.length, 0u, "test_sv_split_once_cases", "left side at start should be empty");
    assert_sv_eq(r, "tail", 4u, "test_sv_split_once_cases", "right side at start split");

    strview at_end = sv_from_cstr("head:");
    assert_true(sv_split_once(at_end, ':', &l, &r), "test_sv_split_once_cases", "delimiter at end should split");
    assert_sv_eq(l, "head", 4u, "test_sv_split_once_cases", "left side at end split");
    assert_size_eq(r.length, 0u, "test_sv_split_once_cases", "right side at end should be empty");

    strview missing = sv_from_cstr("nodelem");
    l.data = left_sentinel;
    l.length = 8u;
    r.data = right_sentinel;
    r.length = 8u;
    assert_true(!sv_split_once(missing, ':', &l, &r), "test_sv_split_once_cases", "missing delimiter should return false");
    assert_true(l.data == left_sentinel && l.length == 8u,
                "test_sv_split_once_cases",
                "out_left should remain unchanged when split fails");
    assert_true(r.data == right_sentinel && r.length == 8u,
                "test_sv_split_once_cases",
                "out_right should remain unchanged when split fails");
}

int main(void) {
    test_sv_from_cstr_null_and_empty();
    test_sv_equals_cases();
    test_sv_trim_variants();
    test_sv_find_cases();
    test_sv_split_once_cases();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
