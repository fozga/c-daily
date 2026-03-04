#include "buffer.h"

#include <stdint.h>
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

static void assert_u8_eq(uint8_t actual, uint8_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s (expected=%u, actual=%u)\n",
                test_name,
                detail,
                (unsigned)expected,
                (unsigned)actual);
    }
}

static void assert_size_eq(size_t actual, size_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr, "[FAIL] %s: %s (expected=%zu, actual=%zu)\n",
                test_name,
                detail,
                expected,
                actual);
    }
}

static void test_init_null_handling(void) {
    uint8_t data[2] = {1u, 2u};
    buffer_t b;

    assert_true(buf_init(NULL, data, 2u) == -1, "test_init_null_handling", "NULL buffer must fail");
    assert_true(buf_init(&b, NULL, 2u) == -1, "test_init_null_handling", "NULL data must fail");
}

static void test_init_success_sets_state(void) {
    uint8_t data[3] = {10u, 20u, 30u};
    buffer_t b = {0};
    int rc = buf_init(&b, data, 3u);

    assert_true(rc == 0, "test_init_success_sets_state", "valid init should succeed");
    if (rc != 0) {
        return;
    }

    assert_true(b.data == data, "test_init_success_sets_state", "data pointer should be set");
    assert_size_eq(b.capacity, 3u, "test_init_success_sets_state", "capacity should be set");
    assert_size_eq(b.cursor, 0u, "test_init_success_sets_state", "cursor should start at 0");
}

static void test_read_sequential_until_end(void) {
    uint8_t data[3] = {7u, 8u, 9u};
    buffer_t b;
    uint8_t out = 0u;

    if (buf_init(&b, data, 3u) != 0) {
        assert_true(0, "test_read_sequential_until_end", "init failed unexpectedly");
        return;
    }

    assert_true(buf_read_byte(&b, &out) == 0, "test_read_sequential_until_end", "first read should succeed");
    assert_u8_eq(out, 7u, "test_read_sequential_until_end", "first byte mismatch");
    assert_size_eq(b.cursor, 1u, "test_read_sequential_until_end", "cursor after first read");

    assert_true(buf_read_byte(&b, &out) == 0, "test_read_sequential_until_end", "second read should succeed");
    assert_u8_eq(out, 8u, "test_read_sequential_until_end", "second byte mismatch");
    assert_size_eq(b.cursor, 2u, "test_read_sequential_until_end", "cursor after second read");

    assert_true(buf_read_byte(&b, &out) == 0, "test_read_sequential_until_end", "third read should succeed");
    assert_u8_eq(out, 9u, "test_read_sequential_until_end", "third byte mismatch");
    assert_size_eq(b.cursor, 3u, "test_read_sequential_until_end", "cursor after third read");
}

static void test_read_past_capacity_fails_and_cursor_stable(void) {
    uint8_t data[1] = {42u};
    buffer_t b;
    uint8_t out = 0u;

    if (buf_init(&b, data, 1u) != 0) {
        assert_true(0, "test_read_past_capacity_fails_and_cursor_stable", "init failed unexpectedly");
        return;
    }

    assert_true(buf_read_byte(&b, &out) == 0, "test_read_past_capacity_fails_and_cursor_stable", "first read should succeed");
    assert_u8_eq(out, 42u, "test_read_past_capacity_fails_and_cursor_stable", "byte mismatch");
    assert_size_eq(b.cursor, 1u, "test_read_past_capacity_fails_and_cursor_stable", "cursor should be at end");

    assert_true(buf_read_byte(&b, &out) == -1, "test_read_past_capacity_fails_and_cursor_stable", "read past end must fail");
    assert_size_eq(b.cursor, 1u, "test_read_past_capacity_fails_and_cursor_stable", "cursor must not advance on failed read");
}

static void test_peek_does_not_advance_but_read_does(void) {
    uint8_t data[2] = {11u, 22u};
    buffer_t b;
    uint8_t out = 0u;

    if (buf_init(&b, data, 2u) != 0) {
        assert_true(0, "test_peek_does_not_advance_but_read_does", "init failed unexpectedly");
        return;
    }

    assert_true(buf_peek(&b, &out) == 0, "test_peek_does_not_advance_but_read_does", "peek should succeed");
    assert_u8_eq(out, 11u, "test_peek_does_not_advance_but_read_does", "peeked byte mismatch");
    assert_size_eq(b.cursor, 0u, "test_peek_does_not_advance_but_read_does", "peek must not advance cursor");

    assert_true(buf_read_byte(&b, &out) == 0, "test_peek_does_not_advance_but_read_does", "read after peek should succeed");
    assert_u8_eq(out, 11u, "test_peek_does_not_advance_but_read_does", "read byte mismatch");
    assert_size_eq(b.cursor, 1u, "test_peek_does_not_advance_but_read_does", "read must advance cursor");
}

static void test_read_bytes_exact_capacity(void) {
    uint8_t data[4] = {1u, 3u, 5u, 7u};
    uint8_t out[4] = {0u, 0u, 0u, 0u};
    buffer_t b;

    if (buf_init(&b, data, 4u) != 0) {
        assert_true(0, "test_read_bytes_exact_capacity", "init failed unexpectedly");
        return;
    }

    assert_true(buf_read_bytes(&b, 4u, out) == 0, "test_read_bytes_exact_capacity", "read_bytes should succeed");
    assert_u8_eq(out[0], 1u, "test_read_bytes_exact_capacity", "out[0]");
    assert_u8_eq(out[1], 3u, "test_read_bytes_exact_capacity", "out[1]");
    assert_u8_eq(out[2], 5u, "test_read_bytes_exact_capacity", "out[2]");
    assert_u8_eq(out[3], 7u, "test_read_bytes_exact_capacity", "out[3]");
    assert_size_eq(b.cursor, 4u, "test_read_bytes_exact_capacity", "cursor should be at end");
}

static void test_read_bytes_capacity_plus_one_fails_safely(void) {
    uint8_t data[3] = {9u, 8u, 7u};
    uint8_t out[4] = {0u, 0u, 0u, 0u};
    buffer_t b;

    if (buf_init(&b, data, 3u) != 0) {
        assert_true(0, "test_read_bytes_capacity_plus_one_fails_safely", "init failed unexpectedly");
        return;
    }

    assert_true(buf_read_bytes(&b, 4u, out) == -1,
                "test_read_bytes_capacity_plus_one_fails_safely",
                "requesting capacity+1 bytes must fail");
    assert_size_eq(b.cursor, 0u,
                   "test_read_bytes_capacity_plus_one_fails_safely",
                   "cursor must stay unchanged on failed chunk read");
}

static void test_remaining_and_null_behavior(void) {
    uint8_t data[2] = {4u, 6u};
    buffer_t b;
    uint8_t out = 0u;

    assert_size_eq(buf_remaining(NULL), 0u, "test_remaining_and_null_behavior", "NULL buffer should report 0 remaining");

    if (buf_init(&b, data, 2u) != 0) {
        assert_true(0, "test_remaining_and_null_behavior", "init failed unexpectedly");
        return;
    }

    assert_size_eq(buf_remaining(&b), 2u, "test_remaining_and_null_behavior", "initial remaining");
    (void)buf_read_byte(&b, &out);
    assert_size_eq(buf_remaining(&b), 1u, "test_remaining_and_null_behavior", "remaining after one read");
}

int main(void) {
    test_init_null_handling();
    test_init_success_sets_state();
    test_read_sequential_until_end();
    test_read_past_capacity_fails_and_cursor_stable();
    test_peek_does_not_advance_but_read_does();
    test_read_bytes_exact_capacity();
    test_read_bytes_capacity_plus_one_fails_safely();
    test_remaining_and_null_behavior();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
