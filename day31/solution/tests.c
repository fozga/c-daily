#include "mempool.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test, const char* msg) {
    g_assertions++;
    if (!cond) {
        g_failures++;
        printf("[FAIL] %s: %s\n", test, msg);
    }
}

static void assert_ptr_ne(const void* a, const void* b, const char* test, const char* msg) {
    g_assertions++;
    if (a == b) {
        g_failures++;
        printf("[FAIL] %s: %s\n", test, msg);
    }
}

static void test_init_invalid_args(void) {
    const char* t = "init_invalid_args";
    mempool_t p;
    uint8_t buffer[64];

    assert_true(pool_init(NULL, buffer, 16, 4) == -1, t, "NULL pool should fail");
    assert_true(pool_init(&p, NULL, 16, 4) == -1, t, "NULL buffer should fail");
    assert_true(pool_init(&p, buffer, 0, 4) == -1, t, "zero block_size should fail");
    assert_true(pool_init(&p, buffer, 16, 0) == -1, t, "zero block_count should fail");
}

static void test_init_valid_and_exhaustion(void) {
    const char* t = "init_valid_and_exhaustion";
    mempool_t p;
    uint8_t buffer[3 * 16];

    assert_true(pool_init(&p, buffer, 16, 3) == 0, t, "valid init should pass");
    assert_true(p.buffer == buffer, t, "buffer pointer should be stored");
    assert_true(p.block_size == 16, t, "block_size should be stored");
    assert_true(p.block_count == 3, t, "block_count should be stored");

    void* a = pool_alloc(&p);
    void* b = pool_alloc(&p);
    void* c = pool_alloc(&p);
    void* d = pool_alloc(&p);

    assert_true(a != NULL, t, "first alloc should succeed");
    assert_true(b != NULL, t, "second alloc should succeed");
    assert_true(c != NULL, t, "third alloc should succeed");
    assert_true(d == NULL, t, "fourth alloc should fail (exhausted)");

    assert_ptr_ne(a, b, t, "allocated blocks should be distinct");
    assert_ptr_ne(b, c, t, "allocated blocks should be distinct");
    assert_ptr_ne(a, c, t, "allocated blocks should be distinct");
}

static void test_free_reuse(void) {
    const char* t = "free_reuse";
    mempool_t p;
    uint8_t buffer[2 * 32];

    assert_true(pool_init(&p, buffer, 32, 2) == 0, t, "valid init should pass");

    void* a = pool_alloc(&p);
    void* b = pool_alloc(&p);
    assert_true(a != NULL && b != NULL, t, "both allocations should succeed");

    pool_free(&p, a);
    void* c = pool_alloc(&p);
    assert_true(c == a, t, "freed block should be reusable");

    pool_free(&p, b);
    void* d = pool_alloc(&p);
    assert_true(d == b, t, "freed block should be reusable");
}

static void test_small_block_rejected(void) {
    const char* t = "small_block_rejected";
    mempool_t p;
    uint8_t buffer[64];

    size_t tiny = sizeof(void*) - 1U;
    assert_true(pool_init(&p, buffer, tiny, 4) == -1, t,
                "block smaller than pointer should fail");
}

static void test_memory_write_sanity(void) {
    const char* t = "memory_write_sanity";
    mempool_t p;
    uint8_t buffer[2 * 24];
    assert_true(pool_init(&p, buffer, 24, 2) == 0, t, "init should pass");

    uint8_t* a = (uint8_t*)pool_alloc(&p);
    uint8_t* b = (uint8_t*)pool_alloc(&p);
    assert_true(a != NULL && b != NULL, t, "allocations should succeed");

    memset(a, 0xAA, 24);
    memset(b, 0x55, 24);
    assert_true(a[0] == 0xAA && a[23] == 0xAA, t, "first block should be writable");
    assert_true(b[0] == 0x55 && b[23] == 0x55, t, "second block should be writable");
}

int main(void) {
    test_init_invalid_args();
    test_init_valid_and_exhaustion();
    test_free_reuse();
    test_small_block_rejected();
    test_memory_write_sanity();

    if (g_failures == 0) {
        printf("[OK] all tests passed (%d assertions)\n", g_assertions);
        return 0;
    }

    printf("[FAIL] %d/%d assertions failed\n", g_failures, g_assertions);
    return 1;
}
