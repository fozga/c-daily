#include "dyn_string.h"

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

static void assert_char_eq(char actual, char expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected='%c' [%d], actual='%c' [%d])\n",
                test_name,
                detail,
                expected,
                (int)expected,
                actual,
                (int)actual);
    }
}

static void test_init_and_destroy_basic(void) {
    dyn_string_t ds = {0};

    assert_true(dstr_init(&ds, 8u), "test_init_and_destroy_basic", "init should succeed for small capacity");
    assert_true(ds.data != NULL, "test_init_and_destroy_basic", "data must be allocated");
    assert_size_eq(ds.length, 0u, "test_init_and_destroy_basic", "length should start at 0");
    assert_true(ds.capacity >= 1u, "test_init_and_destroy_basic", "capacity must allow terminator");

    dstr_destroy(&ds);
    assert_true(ds.data == NULL, "test_init_and_destroy_basic", "destroy should clear data pointer");
    assert_size_eq(ds.length, 0u, "test_init_and_destroy_basic", "destroy should reset length");
    assert_size_eq(ds.capacity, 0u, "test_init_and_destroy_basic", "destroy should reset capacity");
}

static void test_append_char_and_growth(void) {
    dyn_string_t ds = {0};

    if (!dstr_init(&ds, 2u)) {
        assert_true(false, "test_append_char_and_growth", "init failed unexpectedly");
        return;
    }

    size_t old_cap = ds.capacity;

    assert_true(dstr_append_char(&ds, 'A'), "test_append_char_and_growth", "append A should succeed");
    assert_true(dstr_append_char(&ds, 'B'), "test_append_char_and_growth", "append B should succeed");
    assert_true(dstr_append_char(&ds, 'C'), "test_append_char_and_growth", "append C should trigger growth and succeed");

    assert_size_eq(ds.length, 3u, "test_append_char_and_growth", "length after 3 appends");
    assert_true(ds.capacity > old_cap, "test_append_char_and_growth", "capacity should grow after exceeding initial space");

    const char* s = dstr_get_cstr(&ds);
    assert_true(s != NULL, "test_append_char_and_growth", "cstr pointer should not be NULL");
    if (s != NULL) {
        assert_char_eq(s[0], 'A', "test_append_char_and_growth", "char 0");
        assert_char_eq(s[1], 'B', "test_append_char_and_growth", "char 1");
        assert_char_eq(s[2], 'C', "test_append_char_and_growth", "char 2");
        assert_char_eq(s[3], '\0', "test_append_char_and_growth", "must be NUL-terminated");
    }

    dstr_destroy(&ds);
}

static void test_append_str_and_empty_string(void) {
    dyn_string_t ds = {0};

    if (!dstr_init(&ds, 4u)) {
        assert_true(false, "test_append_str_and_empty_string", "init failed unexpectedly");
        return;
    }

    assert_true(dstr_append_str(&ds, "hi"), "test_append_str_and_empty_string", "append 'hi' should succeed");
    assert_true(dstr_append_str(&ds, ""), "test_append_str_and_empty_string", "append empty string should succeed");
    assert_true(dstr_append_str(&ds, " there"), "test_append_str_and_empty_string", "append second piece should succeed");

    assert_size_eq(ds.length, 8u, "test_append_str_and_empty_string", "length after multi-append");

    const char* s = dstr_get_cstr(&ds);
    assert_true(s != NULL, "test_append_str_and_empty_string", "cstr pointer should be valid");
    if (s != NULL) {
        assert_char_eq(s[0], 'h', "test_append_str_and_empty_string", "char 0");
        assert_char_eq(s[1], 'i', "test_append_str_and_empty_string", "char 1");
        assert_char_eq(s[2], ' ', "test_append_str_and_empty_string", "char 2");
        assert_char_eq(s[7], 'e', "test_append_str_and_empty_string", "char 7");
        assert_char_eq(s[8], '\0', "test_append_str_and_empty_string", "must be NUL-terminated");
    }

    dstr_destroy(&ds);
}

static void test_destroy_multiple_times(void) {
    dyn_string_t ds = {0};

    assert_true(dstr_init(&ds, 1u), "test_destroy_multiple_times", "init should succeed");
    dstr_destroy(&ds);
    dstr_destroy(&ds);

    assert_true(ds.data == NULL, "test_destroy_multiple_times", "data stays NULL after repeated destroy");
    assert_size_eq(ds.length, 0u, "test_destroy_multiple_times", "length remains 0");
    assert_size_eq(ds.capacity, 0u, "test_destroy_multiple_times", "capacity remains 0");
}

static void test_append_with_null_inputs(void) {
    dyn_string_t ds = {0};

    assert_true(!dstr_append_char(NULL, 'x'), "test_append_with_null_inputs", "append_char on NULL ds should fail");
    assert_true(!dstr_append_str(NULL, "abc"), "test_append_with_null_inputs", "append_str on NULL ds should fail");

    if (dstr_init(&ds, 2u)) {
        assert_true(!dstr_append_str(&ds, NULL), "test_append_with_null_inputs", "append_str NULL source should fail");
        dstr_destroy(&ds);
    }
}

int main(void) {
    test_init_and_destroy_basic();
    test_append_char_and_growth();
    test_append_str_and_empty_string();
    test_destroy_multiple_times();
    test_append_with_null_inputs();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
