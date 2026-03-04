#include "macros.h"
#include "safe_ops.h"

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

static void test_max_side_effect_once_each(void) {
    int i = 1;
    int j = 2;
    int m = MAX(i++, j++);
    (void)m;

    /* A safe MAX design should ensure each side-effecting argument is evaluated once. */
    assert_i_eq(i, 2, "test_max_side_effect_once_each", "left argument should increment once");
    assert_i_eq(j, 3, "test_max_side_effect_once_each", "right argument should increment once");
}

static void test_square_precedence_bug(void) {
    int v = SQUARE(2 + 1);
    assert_i_eq(v, 9, "test_square_precedence_bug", "SQUARE(x+1) should expand with correct parentheses");
}

static int maybe_swap_and_sum(int do_swap, int* a, int* b) {
    int sum = 0;
    if (do_swap) {
        SWAP_INT(*a, *b);
    } else {
        sum = *a + *b;
    }
    return sum;
}

static void test_swap_macro_conditional_context(void) {
    int a = 3;
    int b = 7;
    int sum = maybe_swap_and_sum(0, &a, &b);
    assert_i_eq(sum, 10, "test_swap_macro_conditional_context", "else branch should execute correctly");
    assert_i_eq(a, 3, "test_swap_macro_conditional_context", "a unchanged when not swapping");
    assert_i_eq(b, 7, "test_swap_macro_conditional_context", "b unchanged when not swapping");
}

static void test_so_clamp_boundaries(void) {
    assert_i_eq(so_clamp(5, 0, 10), 5, "test_so_clamp_boundaries", "in-range value");
    assert_i_eq(so_clamp(-2, 0, 10), 0, "test_so_clamp_boundaries", "below lower bound");
    assert_i_eq(so_clamp(99, 0, 10), 10, "test_so_clamp_boundaries", "above upper bound");
}

static void test_so_min_basic(void) {
    assert_i_eq(so_min(3, 9), 3, "test_so_min_basic", "minimum of distinct positives");
    assert_i_eq(so_min(-5, -1), -5, "test_so_min_basic", "minimum of negatives");
}

static void test_so_swap_basic(void) {
    int a = 11;
    int b = 22;
    so_swap(&a, &b);
    assert_i_eq(a, 22, "test_so_swap_basic", "a should become old b");
    assert_i_eq(b, 11, "test_so_swap_basic", "b should become old a");
}

int main(void) {
    assert_true(true, "main", "assert_true helper is wired");

    test_max_side_effect_once_each();
    test_square_precedence_bug();
    test_swap_macro_conditional_context();
    test_so_clamp_boundaries();
    test_so_min_basic();
    test_so_swap_basic();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
