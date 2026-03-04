#include "ringbuf.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test, const char* msg) {
    g_assertions++;
    if (!cond) {
        g_failures++;
        printf("[FAIL] %s: %s\n", test, msg);
    }
}

static void assert_u8(uint8_t expected, uint8_t actual, const char* test, const char* msg) {
    g_assertions++;
    if (expected != actual) {
        g_failures++;
        printf("[FAIL] %s: %s (expected=%u actual=%u)\n",
               test, msg, (unsigned)expected, (unsigned)actual);
    }
}

static void test_empty_on_init(void) {
    const char* t = "empty_on_init";
    ringbuf_t rb;
    rb_init(&rb);

    assert_true(rb_is_empty(&rb), t, "buffer must be empty after init");
    assert_true(!rb_is_full(&rb), t, "buffer must not be full after init");
}

static void test_push_until_full_capacity_minus_one(void) {
    const char* t = "push_until_full";
    ringbuf_t rb;
    rb_init(&rb);

    for (int i = 0; i < RB_CAPACITY - 1; ++i) {
        assert_true(rb_push(&rb, (uint8_t)i), t, "push should succeed before full");
    }

    assert_true(rb_is_full(&rb), t, "buffer should report full at N-1 elements");
    assert_true(!rb_push(&rb, 0xEE), t, "push must fail when full");
}

static void test_fifo_pop_all(void) {
    const char* t = "fifo_pop_all";
    ringbuf_t rb;
    rb_init(&rb);

    for (int i = 0; i < RB_CAPACITY - 1; ++i) {
        assert_true(rb_push(&rb, (uint8_t)(i + 1)), t, "prepare push should succeed");
    }

    for (int i = 0; i < RB_CAPACITY - 1; ++i) {
        uint8_t got = 0;
        assert_true(rb_pop(&rb, &got), t, "pop should succeed");
        assert_u8((uint8_t)(i + 1), got, t, "popped value must preserve FIFO order");
    }

    assert_true(rb_is_empty(&rb), t, "buffer should be empty after popping all");
    {
        uint8_t dummy = 0;
        assert_true(!rb_pop(&rb, &dummy), t, "pop should fail on empty");
    }
}

static void test_wraparound_push_pop(void) {
    const char* t = "wraparound_push_pop";
    ringbuf_t rb;
    rb_init(&rb);

    for (int i = 0; i < 10; ++i) {
        assert_true(rb_push(&rb, (uint8_t)(100 + i)), t, "initial push should succeed");
    }
    for (int i = 0; i < 10; ++i) {
        uint8_t got = 0;
        assert_true(rb_pop(&rb, &got), t, "initial pop should succeed");
        assert_u8((uint8_t)(100 + i), got, t, "initial pop values should match");
    }

    for (int i = 0; i < 10; ++i) {
        assert_true(rb_push(&rb, (uint8_t)(200 + i)), t, "second push should succeed");
    }
    for (int i = 0; i < 10; ++i) {
        uint8_t got = 0;
        assert_true(rb_pop(&rb, &got), t, "second pop should succeed");
        assert_u8((uint8_t)(200 + i), got, t, "second pop values should match");
    }

    assert_true(rb_is_empty(&rb), t, "buffer should end empty after wraparound cycle");
}

int main(void) {
    test_empty_on_init();
    test_push_until_full_capacity_minus_one();
    test_fifo_pop_all();
    test_wraparound_push_pop();

    if (g_failures == 0) {
        printf("[OK] all tests passed (%d assertions)\n", g_assertions);
        return 0;
    }

    printf("[FAIL] %d/%d assertions failed\n", g_failures, g_assertions);
    return 1;
}
