#include "slist_defensive.h"

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

static void test_normal_operation(void) {
    slist_t list;
    slist_init(&list);

    test_set_malloc_fail_at(-1);
    assert_true(slist_push_front(&list, 10), "test_normal_operation", "push 10");
    assert_true(slist_push_front(&list, 20), "test_normal_operation", "push 20");
    assert_true(list.count == 2, "test_normal_operation", "count should be 2");
    assert_true(list.head != NULL, "test_normal_operation", "head should exist");
    if (list.head != NULL) {
        assert_true(list.head->value == 20, "test_normal_operation", "head value should be latest push");
    }

    slist_destroy(&list);
    assert_true(list.count == 0, "test_normal_operation", "count reset after destroy");
    assert_true(list.head == NULL, "test_normal_operation", "head reset after destroy");
}

static void test_fault_injection_oom(void) {
    slist_t list;
    slist_init(&list);

    test_set_malloc_fail_at(0);
    assert_true(!slist_push_front(&list, 1),
                "test_fault_injection_oom",
                "push should fail cleanly on injected OOM");
    assert_true(list.count == 0,
                "test_fault_injection_oom",
                "count should remain 0 after failed push");
    assert_true(list.head == NULL,
                "test_fault_injection_oom",
                "head should remain NULL after failed push");

    test_set_malloc_fail_at(-1);
    slist_destroy(&list);
}

/*
Manual invariant corruption check idea (not automated here):
1) build list with two nodes
2) set list.count = 999 manually
3) call slist_verify_invariants(&list)
Expected once learner implements assert-based verification: program aborts.
*/

int main(void) {
    test_normal_operation();
    test_fault_injection_oom();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
