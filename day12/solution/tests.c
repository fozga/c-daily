#include "layout.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
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

static void assert_u8_eq(uint8_t actual, uint8_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%u, actual=%u)\n",
                test_name,
                detail,
                (unsigned)expected,
                (unsigned)actual);
    }
}

static void assert_u16_eq(uint16_t actual, uint16_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%u, actual=%u)\n",
                test_name,
                detail,
                (unsigned)expected,
                (unsigned)actual);
    }
}

static void assert_u32_eq(uint32_t actual, uint32_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%u, actual=%u)\n",
                test_name,
                detail,
                (unsigned)expected,
                (unsigned)actual);
    }
}

static void test_print_layout_info(void) {
    printf("sizeof(padded_record_t) = %zu\n", sizeof(padded_record_t));
    printf("offsetof(flags)  = %zu\n", offsetof(padded_record_t, flags));
    printf("offsetof(id)     = %zu\n", offsetof(padded_record_t, id));
    printf("offsetof(status) = %zu\n", offsetof(padded_record_t, status));
    printf("offsetof(code)   = %zu\n", offsetof(padded_record_t, code));

    assert_true(sizeof(padded_record_t) >= sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint16_t),
                "test_print_layout_info",
                "struct size should be at least sum of fields");
}

static void test_round_trip_buggy_struct_silent_pass(void) {
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_round_trip_buggy_struct_silent_pass", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    padded_record_t in = {
        .flags = 0xAAu,
        .id = 0x11223344u,
        .status = 0x55u,
        .code = 0x7788u
    };
    padded_record_t out = {0};

    assert_true(layout_write(fp, &in) == 0, "test_round_trip_buggy_struct_silent_pass", "write should report success");
    rewind(fp);
    assert_true(layout_read(fp, &out) == 0, "test_round_trip_buggy_struct_silent_pass", "read should report success");

    assert_u8_eq(out.flags, in.flags, "test_round_trip_buggy_struct_silent_pass", "flags round-trip");
    assert_u32_eq(out.id, in.id, "test_round_trip_buggy_struct_silent_pass", "id round-trip");
    assert_u8_eq(out.status, in.status, "test_round_trip_buggy_struct_silent_pass", "status round-trip");
    assert_u16_eq(out.code, in.code, "test_round_trip_buggy_struct_silent_pass", "code round-trip");
    fclose(fp);
}

/* These checks are intended for after fixed_record_t is added by the learner. */
static void test_fixed_record_expectations_placeholder(void) {
#ifdef FIXED_RECORD_READY
    assert_true(sizeof(fixed_record_t) <= sizeof(padded_record_t),
                "test_fixed_record_expectations_placeholder",
                "fixed layout should be no larger than padded layout");
    assert_true(offsetof(fixed_record_t, id) >= 0,
                "test_fixed_record_expectations_placeholder",
                "offset checks should compile and be deterministic");
#else
    assert_true(true,
                "test_fixed_record_expectations_placeholder",
                "fixed_record_t not defined yet (expected at this stage)");
#endif
}

int main(void) {
    test_print_layout_info();
    test_round_trip_buggy_struct_silent_pass();
    test_fixed_record_expectations_placeholder();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
