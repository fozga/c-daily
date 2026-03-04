#include "hashmap.h"

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

static void test_insert_and_get(void) {
    hashmap_t hm;
    int out = 0;

    assert_true(hm_init(&hm, 16), "test_insert_and_get", "hm_init should succeed");
    assert_true(hm_put(&hm, "alpha", 1), "test_insert_and_get", "put alpha");
    assert_true(hm_put(&hm, "beta", 2), "test_insert_and_get", "put beta");

    assert_true(hm_get(&hm, "alpha", &out), "test_insert_and_get", "get alpha");
    assert_i_eq(out, 1, "test_insert_and_get", "alpha value");
    assert_true(hm_get(&hm, "beta", &out), "test_insert_and_get", "get beta");
    assert_i_eq(out, 2, "test_insert_and_get", "beta value");

    hm_destroy(&hm);
}

static void test_overwrite_existing_key(void) {
    hashmap_t hm;
    int out = 0;

    assert_true(hm_init(&hm, 16), "test_overwrite_existing_key", "hm_init should succeed");
    assert_true(hm_put(&hm, "k", 10), "test_overwrite_existing_key", "initial insert");
    assert_true(hm_put(&hm, "k", 99), "test_overwrite_existing_key", "overwrite insert");
    assert_true(hm_get(&hm, "k", &out), "test_overwrite_existing_key", "lookup overwritten key");
    assert_i_eq(out, 99, "test_overwrite_existing_key", "updated value should be visible");
    assert_true(hm_count(&hm) == 1, "test_overwrite_existing_key", "count should remain 1 for overwrite");

    hm_destroy(&hm);
}

static void test_missing_keys(void) {
    hashmap_t hm;
    int out = 0;

    assert_true(hm_init(&hm, 8), "test_missing_keys", "hm_init should succeed");
    assert_true(!hm_get(&hm, "missing", &out), "test_missing_keys", "missing key should not be found");
    assert_true(!hm_get(&hm, "other", NULL), "test_missing_keys", "missing with NULL out still false");

    hm_destroy(&hm);
}

static void test_resize_and_reachability(void) {
    hashmap_t hm;
    int out = 0;
    int i = 0;
    char keybuf[32];

    assert_true(hm_init(&hm, 4), "test_resize_and_reachability", "hm_init should succeed");

    for (i = 0; i < 40; ++i) {
        (void)snprintf(keybuf, sizeof(keybuf), "k%d", i);
        assert_true(hm_put(&hm, keybuf, i * 10), "test_resize_and_reachability", "bulk insert");
    }

    assert_true(hm_count(&hm) == 40, "test_resize_and_reachability", "count should reflect all inserts");

    for (i = 0; i < 40; ++i) {
        (void)snprintf(keybuf, sizeof(keybuf), "k%d", i);
        assert_true(hm_get(&hm, keybuf, &out), "test_resize_and_reachability", "bulk get");
        assert_i_eq(out, i * 10, "test_resize_and_reachability", "bulk value check");
    }

    hm_destroy(&hm);
}

static void test_destroy_clears_memory_state(void) {
    hashmap_t hm;
    assert_true(hm_init(&hm, 16), "test_destroy_clears_memory_state", "hm_init should succeed");
    assert_true(hm_put(&hm, "x", 1), "test_destroy_clears_memory_state", "insert x");
    hm_destroy(&hm);

    assert_true(hm.slots == NULL, "test_destroy_clears_memory_state", "slots reset to NULL");
    assert_true(hm.capacity == 0, "test_destroy_clears_memory_state", "capacity reset to 0");
    assert_true(hm.count == 0, "test_destroy_clears_memory_state", "count reset to 0");
}

int main(void) {
    test_insert_and_get();
    test_overwrite_existing_key();
    test_missing_keys();
    test_resize_and_reachability();
    test_destroy_clears_memory_state();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
