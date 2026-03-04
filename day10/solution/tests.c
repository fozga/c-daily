#include "binrec.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
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

static void assert_err_eq(binrec_err_t actual, binrec_err_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%d, actual=%d)\n",
                test_name,
                detail,
                (int)expected,
                (int)actual);
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
                expected,
                actual);
    }
}

static void assert_i32_eq(int32_t actual, int32_t expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (actual != expected) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=%d, actual=%d)\n",
                test_name,
                detail,
                (int)expected,
                (int)actual);
    }
}

static void test_round_trip_records(void) {
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_round_trip_records", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    binrec_entry_t in[] = {
        {.id = 1, .value = 10, .flags = 0u},
        {.id = 2, .value = -5, .flags = 3u},
        {.id = 42, .value = 99, .flags = 7u},
    };
    binrec_entry_t out[3] = {{0}};
    size_t out_count = 0;

    assert_err_eq(binrec_write(fp, in, 3), BINREC_OK, "test_round_trip_records", "write should succeed");
    rewind(fp);
    assert_err_eq(binrec_read(fp, out, &out_count), BINREC_OK, "test_round_trip_records", "read should succeed");

    assert_true(out_count == 3, "test_round_trip_records", "record count should match");
    for (size_t i = 0; i < 3; ++i) {
        assert_i32_eq(out[i].id, in[i].id, "test_round_trip_records", "id round-trip");
        assert_i32_eq(out[i].value, in[i].value, "test_round_trip_records", "value round-trip");
        assert_u32_eq(out[i].flags, in[i].flags, "test_round_trip_records", "flags round-trip");
    }
    fclose(fp);
}

static void test_empty_record_array(void) {
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_empty_record_array", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    size_t out_count = 777;
    assert_err_eq(binrec_write(fp, NULL, 0), BINREC_OK, "test_empty_record_array", "write empty should succeed");
    rewind(fp);
    assert_err_eq(binrec_read(fp, NULL, &out_count), BINREC_OK, "test_empty_record_array", "read empty should succeed");
    assert_true(out_count == 0, "test_empty_record_array", "count should be zero");
    fclose(fp);
}

static void test_bad_magic_detection(void) {
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_bad_magic_detection", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    binrec_entry_t in[] = {{.id = 1, .value = 1, .flags = 1u}};
    binrec_entry_t out[1] = {{0}};
    size_t out_count = 0;

    assert_err_eq(binrec_write(fp, in, 1), BINREC_OK, "test_bad_magic_detection", "baseline write should succeed");
    rewind(fp);

    {
        uint32_t bad_magic = 0x11111111u;
        size_t n = fwrite(&bad_magic, sizeof(bad_magic), 1, fp);
        assert_true(n == 1, "test_bad_magic_detection", "must overwrite magic bytes");
    }

    rewind(fp);
    assert_err_eq(binrec_read(fp, out, &out_count),
                  BINREC_ERR_BAD_MAGIC,
                  "test_bad_magic_detection",
                  "bad magic must be rejected");
    fclose(fp);
}

static void test_bad_version_detection(void) {
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_bad_version_detection", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    binrec_entry_t in[] = {{.id = 5, .value = 6, .flags = 7u}};
    binrec_entry_t out[1] = {{0}};
    size_t out_count = 0;

    assert_err_eq(binrec_write(fp, in, 1), BINREC_OK, "test_bad_version_detection", "baseline write should succeed");

    rewind(fp);
    {
        uint32_t header[2] = {0u, 0u};
        size_t n = fread(header, sizeof(uint32_t), 2, fp);
        assert_true(n == 2, "test_bad_version_detection", "must read header prefix");
        header[1] = 999u;
        rewind(fp);
        n = fwrite(header, sizeof(uint32_t), 2, fp);
        assert_true(n == 2, "test_bad_version_detection", "must overwrite version");
    }

    rewind(fp);
    assert_err_eq(binrec_read(fp, out, &out_count),
                  BINREC_ERR_BAD_VER,
                  "test_bad_version_detection",
                  "unsupported version must be rejected");
    fclose(fp);
}

static void test_truncated_file_detection(void) {
    FILE* fp = tmpfile();
    assert_true(fp != NULL, "test_truncated_file_detection", "tmpfile should be created");
    if (fp == NULL) {
        return;
    }

    uint32_t header_magic = BINREC_MAGIC;
    uint32_t header_ver = BINREC_VERSION;
    uint32_t header_count = 2u;
    binrec_entry_t out[2] = {{0}};
    size_t out_count = 0;

    assert_true(fwrite(&header_magic, sizeof(header_magic), 1, fp) == 1,
                "test_truncated_file_detection",
                "write magic");
    assert_true(fwrite(&header_ver, sizeof(header_ver), 1, fp) == 1,
                "test_truncated_file_detection",
                "write version");
    assert_true(fwrite(&header_count, sizeof(header_count), 1, fp) == 1,
                "test_truncated_file_detection",
                "write count");

    {
        binrec_entry_t partial = {.id = 1, .value = 2, .flags = 3u};
        assert_true(fwrite(&partial, sizeof(partial), 1, fp) == 1,
                    "test_truncated_file_detection",
                    "write only one entry to force truncation");
    }

    rewind(fp);
    assert_err_eq(binrec_read(fp, out, &out_count),
                  BINREC_ERR_TRUNC,
                  "test_truncated_file_detection",
                  "partial payload must be reported as truncation");
    fclose(fp);
}

int main(void) {
    test_round_trip_records();
    test_empty_record_array();
    test_bad_magic_detection();
    test_bad_version_detection();
    test_truncated_file_detection();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
