#include "store.h"

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

static void test_create_and_destroy(void) {
    store_t* s = store_create(8);
    assert_true(s != NULL, "test_create_and_destroy", "store_create should succeed");
    store_destroy(s);
    store_destroy(NULL);
    assert_true(true, "test_create_and_destroy", "destroy(NULL) should be safe");
}

static void test_insert_and_retrieve(void) {
    store_t* s = store_create(8);
    int out = 0;
    assert_true(s != NULL, "test_insert_and_retrieve", "store_create should succeed");
    if (s == NULL) {
        return;
    }

    assert_true(store_put(s, "alpha", 10), "test_insert_and_retrieve", "put alpha");
    assert_true(store_put(s, "beta", 20), "test_insert_and_retrieve", "put beta");
    assert_true(store_get(s, "alpha", &out), "test_insert_and_retrieve", "get alpha");
    assert_i_eq(out, 10, "test_insert_and_retrieve", "alpha value");
    assert_true(store_get(s, "beta", &out), "test_insert_and_retrieve", "get beta");
    assert_i_eq(out, 20, "test_insert_and_retrieve", "beta value");
    store_destroy(s);
}

static void test_overwrite_existing_key(void) {
    store_t* s = store_create(8);
    int out = 0;
    assert_true(s != NULL, "test_overwrite_existing_key", "store_create should succeed");
    if (s == NULL) {
        return;
    }

    assert_true(store_put(s, "k", 1), "test_overwrite_existing_key", "initial put");
    assert_true(store_put(s, "k", 99), "test_overwrite_existing_key", "overwrite put");
    assert_true(store_get(s, "k", &out), "test_overwrite_existing_key", "get overwritten key");
    assert_i_eq(out, 99, "test_overwrite_existing_key", "overwritten value should be visible");
    store_destroy(s);
}

static void test_lookup_missing_key(void) {
    store_t* s = store_create(4);
    int out = -1;
    assert_true(s != NULL, "test_lookup_missing_key", "store_create should succeed");
    if (s == NULL) {
        return;
    }

    assert_true(!store_get(s, "nope", &out), "test_lookup_missing_key", "missing key should not be found");
    store_destroy(s);
}

static void test_remove_key(void) {
    store_t* s = store_create(8);
    int out = 0;
    assert_true(s != NULL, "test_remove_key", "store_create should succeed");
    if (s == NULL) {
        return;
    }

    assert_true(store_put(s, "x", 7), "test_remove_key", "put x");
    assert_true(store_remove(s, "x"), "test_remove_key", "remove existing key");
    assert_true(!store_get(s, "x", &out), "test_remove_key", "removed key should not be found");
    assert_true(!store_remove(s, "x"), "test_remove_key", "removing again should return false");
    store_destroy(s);
}

static void test_count_accuracy(void) {
    store_t* s = store_create(8);
    assert_true(s != NULL, "test_count_accuracy", "store_create should succeed");
    if (s == NULL) {
        return;
    }

    assert_i_eq(store_count(s), 0, "test_count_accuracy", "initial count");
    assert_true(store_put(s, "a", 1), "test_count_accuracy", "put a");
    assert_i_eq(store_count(s), 1, "test_count_accuracy", "count after 1 insert");
    assert_true(store_put(s, "b", 2), "test_count_accuracy", "put b");
    assert_i_eq(store_count(s), 2, "test_count_accuracy", "count after 2 inserts");
    assert_true(store_put(s, "a", 3), "test_count_accuracy", "overwrite a");
    assert_i_eq(store_count(s), 2, "test_count_accuracy", "count should not grow on overwrite");
    assert_true(store_remove(s, "b"), "test_count_accuracy", "remove b");
    assert_i_eq(store_count(s), 1, "test_count_accuracy", "count after remove");
    store_destroy(s);
}

int main(void) {
    test_create_and_destroy();
    test_insert_and_retrieve();
    test_overwrite_existing_key();
    test_lookup_missing_key();
    test_remove_key();
    test_count_accuracy();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
