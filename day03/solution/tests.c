#include "pointers.h"

#include <stddef.h>
#include <stdio.h>

static int g_failures = 0;
static int g_assertions = 0;

static void assert_true(int cond, const char* test_name, const char* detail) {
    ++g_assertions;
    if (!cond) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s\n", test_name, detail);
    }
}

static void assert_int_eq(int actual, int expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s (expected=%d, actual=%d)\n", test_name, detail, expected, actual);
    }
}

static void test_swap_null_rejected(void) {
    int x = 1;
    assert_int_eq(ptr_swap(NULL, &x), -1, "test_swap_null_rejected", "NULL first arg should fail");
    assert_int_eq(ptr_swap(&x, NULL), -1, "test_swap_null_rejected", "NULL second arg should fail");
}

static void test_swap_two_values(void) {
    int a = 10;
    int b = 99;
    assert_int_eq(ptr_swap(&a, &b), 0, "test_swap_two_values", "swap should succeed");
    assert_int_eq(a, 99, "test_swap_two_values", "a should become old b");
    assert_int_eq(b, 10, "test_swap_two_values", "b should become old a");
}

static void test_swap_self(void) {
    int v = 42;
    assert_int_eq(ptr_swap(&v, &v), 0, "test_swap_self", "self-swap should succeed");
    assert_int_eq(v, 42, "test_swap_self", "value should remain unchanged");
}

static void test_reverse_null_rejected(void) {
    assert_int_eq(ptr_reverse(NULL, 3u), -1, "test_reverse_null_rejected", "NULL array should fail");
}

static void test_reverse_even_length(void) {
    int arr[4] = {1, 2, 3, 4};
    assert_int_eq(ptr_reverse(arr, 4u), 0, "test_reverse_even_length", "reverse should succeed");
    assert_int_eq(arr[0], 4, "test_reverse_even_length", "arr[0]");
    assert_int_eq(arr[1], 3, "test_reverse_even_length", "arr[1]");
    assert_int_eq(arr[2], 2, "test_reverse_even_length", "arr[2]");
    assert_int_eq(arr[3], 1, "test_reverse_even_length", "arr[3]");
}

static void test_reverse_odd_length(void) {
    int arr[5] = {9, 7, 5, 3, 1};
    assert_int_eq(ptr_reverse(arr, 5u), 0, "test_reverse_odd_length", "reverse should succeed");
    assert_int_eq(arr[0], 1, "test_reverse_odd_length", "arr[0]");
    assert_int_eq(arr[1], 3, "test_reverse_odd_length", "arr[1]");
    assert_int_eq(arr[2], 5, "test_reverse_odd_length", "arr[2]");
    assert_int_eq(arr[3], 7, "test_reverse_odd_length", "arr[3]");
    assert_int_eq(arr[4], 9, "test_reverse_odd_length", "arr[4]");
}

static void test_reverse_length_one(void) {
    int arr[1] = {123};
    assert_int_eq(ptr_reverse(arr, 1u), 0, "test_reverse_length_one", "n==1 should succeed");
    assert_int_eq(arr[0], 123, "test_reverse_length_one", "single element unchanged");
}

static void test_reverse_length_zero(void) {
    int arr[3] = {8, 8, 8};
    assert_int_eq(ptr_reverse(arr, 0u), 0, "test_reverse_length_zero", "n==0 should succeed");
    assert_int_eq(arr[0], 8, "test_reverse_length_zero", "arr unchanged when n==0");
}

static void test_max_null_rejected(void) {
    int arr[2] = {1, 2};
    const int* out = NULL;
    assert_int_eq(ptr_max(NULL, 2u, &out), -1, "test_max_null_rejected", "NULL arr should fail");
    assert_int_eq(ptr_max(arr, 2u, NULL), -1, "test_max_null_rejected", "NULL out_max should fail");
    assert_int_eq(ptr_max(arr, 0u, &out), -1, "test_max_null_rejected", "n==0 should fail");
}

static void test_max_first_position(void) {
    int arr[4] = {50, 4, 3, 2};
    const int* out = NULL;
    assert_int_eq(ptr_max(arr, 4u, &out), 0, "test_max_first_position", "max should succeed");
    assert_true(out == &arr[0], "test_max_first_position", "out should point to first element");
}

static void test_max_middle_position(void) {
    int arr[5] = {-10, 7, 99, 8, 9};
    const int* out = NULL;
    assert_int_eq(ptr_max(arr, 5u, &out), 0, "test_max_middle_position", "max should succeed");
    assert_true(out == &arr[2], "test_max_middle_position", "out should point to middle max element");
}

static void test_max_last_position_and_negative_values(void) {
    int arr[4] = {-9, -7, -3, -1};
    const int* out = NULL;
    int rc = ptr_max(arr, 4u, &out);
    assert_int_eq(rc, 0, "test_max_last_position_and_negative_values", "max should succeed");
    assert_true(out == &arr[3], "test_max_last_position_and_negative_values", "out should point to last element");
    if (out != NULL) {
        assert_int_eq(*out, -1, "test_max_last_position_and_negative_values", "value check");
    }
}

static void test_copy_slice_null_rejected(void) {
    int dst[3] = {0, 0, 0};
    const int src[3] = {1, 2, 3};
    assert_int_eq(ptr_copy_slice(NULL, dst, 3u), -1, "test_copy_slice_null_rejected", "NULL src should fail");
    assert_int_eq(ptr_copy_slice(src, NULL, 3u), -1, "test_copy_slice_null_rejected", "NULL dst should fail");
}

static void test_copy_slice_basic(void) {
    const int src[5] = {5, 4, 3, 2, 1};
    int dst[5] = {0, 0, 0, 0, 0};
    assert_int_eq(ptr_copy_slice(src, dst, 5u), 0, "test_copy_slice_basic", "copy should succeed");
    assert_int_eq(dst[0], 5, "test_copy_slice_basic", "dst[0]");
    assert_int_eq(dst[1], 4, "test_copy_slice_basic", "dst[1]");
    assert_int_eq(dst[2], 3, "test_copy_slice_basic", "dst[2]");
    assert_int_eq(dst[3], 2, "test_copy_slice_basic", "dst[3]");
    assert_int_eq(dst[4], 1, "test_copy_slice_basic", "dst[4]");
}

int main(void) {
    test_swap_null_rejected();
    test_swap_two_values();
    test_swap_self();

    test_reverse_null_rejected();
    test_reverse_even_length();
    test_reverse_odd_length();
    test_reverse_length_one();
    test_reverse_length_zero();

    test_max_null_rejected();
    test_max_first_position();
    test_max_middle_position();
    test_max_last_position_and_negative_values();

    test_copy_slice_null_rejected();
    test_copy_slice_basic();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
