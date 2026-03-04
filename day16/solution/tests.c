#include "faulty_heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

static void test_make_string_of_As_basic(void) {
    char* s = make_string_of_As(8);
    assert_true(s != NULL, "test_make_string_of_As_basic", "allocation should return non-NULL");
    if (s == NULL) {
        return;
    }

    assert_i_eq((int)strlen(s), 8, "test_make_string_of_As_basic", "length should match request");
    assert_true(s[0] == 'A', "test_make_string_of_As_basic", "first character should be A");
    assert_true(s[7] == 'A', "test_make_string_of_As_basic", "last payload character should be A");

    free(s);
}

static void test_replace_chars_path(void) {
    char* s = make_string_of_As(6);
    int replaced = 0;

    assert_true(s != NULL, "test_replace_chars_path", "input string should be allocated");
    if (s == NULL) {
        return;
    }

    replaced = replace_chars(s, 'A', 'B');
    assert_true(replaced >= 1, "test_replace_chars_path", "at least one replacement expected");

    /* INTENTIONAL: do not free(s) here because function may already free it in buggy implementation. */
}

static void test_get_greeting_path(void) {
    const char* msg = get_greeting("ASan");
    assert_true(msg != NULL, "test_get_greeting_path", "greeting pointer should be non-NULL");
    if (msg != NULL) {
        /* Keep verification lightweight: this path should execute, while ASan catches lifetime bugs. */
        assert_true(strstr(msg, "Hello") != NULL || msg[0] != '\0',
                    "test_get_greeting_path",
                    "greeting should look non-empty");
    }
}

int main(void) {
    test_make_string_of_As_basic();
    test_replace_chars_path();
    test_get_greeting_path();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
