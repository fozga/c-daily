#include "broken_pointers.h"

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

static void test_append_and_free(void) {
    node_t* head = NULL;

    assert_i_eq(list_append(&head, 10), 0, "test_append_and_free", "append 10 succeeds");
    assert_i_eq(list_append(&head, 20), 0, "test_append_and_free", "append 20 succeeds");
    assert_i_eq(list_append(&head, 30), 0, "test_append_and_free", "append 30 succeeds");

    assert_true(head != NULL, "test_append_and_free", "head should be initialized");
    if (head != NULL) {
        assert_i_eq(head->value, 10, "test_append_and_free", "head value remains first appended");
    }

    list_free(head);
}

static void test_reverse_empty_list(void) {
    node_t* head = NULL;
    list_reverse(&head);
    assert_true(head == NULL, "test_reverse_empty_list", "reversing empty list keeps NULL");
}

static void test_reverse_crashes_in_broken_build(void) {
    node_t* head = NULL;

    assert_i_eq(list_append(&head, 1), 0, "test_reverse_crashes_in_broken_build", "append 1");
    assert_i_eq(list_append(&head, 2), 0, "test_reverse_crashes_in_broken_build", "append 2");
    assert_i_eq(list_append(&head, 3), 0, "test_reverse_crashes_in_broken_build", "append 3");

    /* This call is expected to segfault in the intentionally broken implementation. */
    list_reverse(&head);

    /* These checks are intended for after learner fixes the bug. */
    assert_true(head != NULL, "test_reverse_crashes_in_broken_build", "head should not be NULL after reverse");
    if (head != NULL) {
        assert_i_eq(head->value, 3, "test_reverse_crashes_in_broken_build", "new head should be former tail");
        if (head->next != NULL) {
            assert_i_eq(head->next->value, 2, "test_reverse_crashes_in_broken_build", "middle value should be 2");
        }
    }

    list_free(head);
}

int main(void) {
    test_append_and_free();
    test_reverse_empty_list();
    test_reverse_crashes_in_broken_build();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
