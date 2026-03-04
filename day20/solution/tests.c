#include "bitset.h"

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

static void test_first_block_ops(void) {
    bitset_t bs;
    assert_true(bs_init(&bs, 128), "test_first_block_ops", "init");

    assert_true(bs_set(&bs, 0), "test_first_block_ops", "set bit 0");
    assert_true(bs_set(&bs, 1), "test_first_block_ops", "set bit 1");
    assert_true(bs_set(&bs, 63), "test_first_block_ops", "set bit 63");

    assert_true(bs_test(&bs, 0), "test_first_block_ops", "bit 0 set");
    assert_true(bs_test(&bs, 1), "test_first_block_ops", "bit 1 set");
    assert_true(bs_test(&bs, 63), "test_first_block_ops", "bit 63 set");

    assert_true(bs_clear(&bs, 1), "test_first_block_ops", "clear bit 1");
    assert_true(!bs_test(&bs, 1), "test_first_block_ops", "bit 1 cleared");

    bs_destroy(&bs);
}

static void test_second_block_ops(void) {
    bitset_t bs;
    assert_true(bs_init(&bs, 256), "test_second_block_ops", "init");

    assert_true(bs_set(&bs, 64), "test_second_block_ops", "set bit 64");
    assert_true(bs_set(&bs, 127), "test_second_block_ops", "set bit 127");
    assert_true(bs_test(&bs, 64), "test_second_block_ops", "bit 64 set");
    assert_true(bs_test(&bs, 127), "test_second_block_ops", "bit 127 set");

    assert_true(bs_toggle(&bs, 64), "test_second_block_ops", "toggle bit 64");
    assert_true(!bs_test(&bs, 64), "test_second_block_ops", "bit 64 toggled off");
    assert_true(bs_toggle(&bs, 64), "test_second_block_ops", "toggle bit 64 again");
    assert_true(bs_test(&bs, 64), "test_second_block_ops", "bit 64 toggled on");

    bs_destroy(&bs);
}

static void test_out_of_bounds(void) {
    bitset_t bs;
    assert_true(bs_init(&bs, 10), "test_out_of_bounds", "init");

    assert_true(!bs_set(&bs, 10), "test_out_of_bounds", "set out-of-bounds");
    assert_true(!bs_clear(&bs, 11), "test_out_of_bounds", "clear out-of-bounds");
    assert_true(!bs_toggle(&bs, 12), "test_out_of_bounds", "toggle out-of-bounds");
    assert_true(!bs_test(&bs, 99), "test_out_of_bounds", "test out-of-bounds returns false");

    bs_destroy(&bs);
}

static void test_large_bitset(void) {
    bitset_t bs;
    assert_true(bs_init(&bs, 10000), "test_large_bitset", "init 10k bits");

    assert_true(bs_set(&bs, 9999), "test_large_bitset", "set top valid bit");
    assert_true(bs_test(&bs, 9999), "test_large_bitset", "top valid bit is set");
    assert_true(!bs_set(&bs, 10000), "test_large_bitset", "setting 10000 out-of-bounds fails");

    bs_destroy(&bs);
}

int main(void) {
    test_first_block_ops();
    test_second_block_ops();
    test_out_of_bounds();
    test_large_bitset();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
