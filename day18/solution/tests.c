#include "slist.h"

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

static void test_push_front_and_back_mix(void) {
    slist_t list;
    int v = 0;
    slist_init(&list);

    assert_true(slist_push_front(&list, 2), "test_push_front_and_back_mix", "push_front 2");
    assert_true(slist_push_front(&list, 1), "test_push_front_and_back_mix", "push_front 1");
    assert_true(slist_push_back(&list, 3), "test_push_front_and_back_mix", "push_back 3");
    assert_true(slist_push_back(&list, 4), "test_push_front_and_back_mix", "push_back 4");

    assert_true(slist_get_at(&list, 0, &v), "test_push_front_and_back_mix", "get index 0");
    assert_i_eq(v, 1, "test_push_front_and_back_mix", "index 0 should be 1");
    assert_true(slist_get_at(&list, 3, &v), "test_push_front_and_back_mix", "get index 3");
    assert_i_eq(v, 4, "test_push_front_and_back_mix", "index 3 should be 4");
    slist_destroy(&list);
}

static void test_get_at_bounds(void) {
    slist_t list;
    int v = -1;
    slist_init(&list);

    assert_true(!slist_get_at(&list, 0, &v), "test_get_at_bounds", "empty list out-of-bounds");
    assert_true(slist_push_back(&list, 10), "test_get_at_bounds", "push one element");
    assert_true(slist_get_at(&list, 0, &v), "test_get_at_bounds", "index 0 valid");
    assert_i_eq(v, 10, "test_get_at_bounds", "index 0 value");
    assert_true(!slist_get_at(&list, 1, &v), "test_get_at_bounds", "index 1 out-of-bounds");
    assert_true(!slist_get_at(&list, 100, &v), "test_get_at_bounds", "far out-of-bounds");
    slist_destroy(&list);
}

static void seed_12345(slist_t* list) {
    slist_push_back(list, 1);
    slist_push_back(list, 2);
    slist_push_back(list, 3);
    slist_push_back(list, 4);
    slist_push_back(list, 5);
}

static void test_remove_head_tail_middle(void) {
    slist_t list;
    int v = 0;
    slist_init(&list);
    seed_12345(&list);

    assert_true(slist_remove(&list, 1), "test_remove_head_tail_middle", "remove head");
    assert_true(slist_get_at(&list, 0, &v), "test_remove_head_tail_middle", "new head exists");
    assert_i_eq(v, 2, "test_remove_head_tail_middle", "head should now be 2");

    assert_true(slist_remove(&list, 5), "test_remove_head_tail_middle", "remove tail");
    assert_true(slist_get_at(&list, 2, &v), "test_remove_head_tail_middle", "new tail index check");
    assert_i_eq(v, 4, "test_remove_head_tail_middle", "tail predecessor remains 4");

    assert_true(slist_remove(&list, 3), "test_remove_head_tail_middle", "remove middle");
    assert_true(slist_get_at(&list, 1, &v), "test_remove_head_tail_middle", "middle collapsed");
    assert_i_eq(v, 4, "test_remove_head_tail_middle", "value after middle removal");

    slist_destroy(&list);
}

static void test_remove_nonexistent(void) {
    slist_t list;
    slist_init(&list);
    seed_12345(&list);

    assert_true(!slist_remove(&list, 999), "test_remove_nonexistent", "remove missing value should fail");
    slist_destroy(&list);
}

static void test_destroy_resets_list(void) {
    slist_t list;
    slist_init(&list);
    seed_12345(&list);
    slist_destroy(&list);

    assert_true(list.head == NULL, "test_destroy_resets_list", "head should be NULL after destroy");
    assert_true(list.count == 0, "test_destroy_resets_list", "count should be 0 after destroy");
}

int main(void) {
    test_push_front_and_back_mix();
    test_get_at_bounds();
    test_remove_head_tail_middle();
    test_remove_nonexistent();
    test_destroy_resets_list();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
