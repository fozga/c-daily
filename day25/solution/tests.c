#define _POSIX_C_SOURCE 200809L

#include "diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

static char* create_tmp_path_for_openable_file(void) {
    char tmpl[] = "/tmp/day25_diag_XXXXXX";
    int fd = mkstemp(tmpl);
    FILE* fp = NULL;
    char* out = NULL;

    if (fd < 0) {
        return NULL;
    }
    fp = fdopen(fd, "w");
    if (fp == NULL) {
        close(fd);
        unlink(tmpl);
        return NULL;
    }
    fputs("hello\n", fp);
    fclose(fp);

    out = (char*)malloc(sizeof(tmpl));
    if (out == NULL) {
        unlink(tmpl);
        return NULL;
    }
    snprintf(out, sizeof(tmpl), "%s", tmpl);
    return out;
}

static void test_diag_open_file_nonexistent(void) {
    FILE* fp = diag_open_file("mini-grep", "/definitely/not/existing/day25_file.txt");
    assert_true(fp == NULL, "test_diag_open_file_nonexistent", "nonexistent path should return NULL");
}

static void test_diag_open_file_valid_path(void) {
    char* path = create_tmp_path_for_openable_file();
    FILE* fp = NULL;

    assert_true(path != NULL, "test_diag_open_file_valid_path", "temp path setup");
    if (path == NULL) {
        return;
    }

    fp = diag_open_file("mini-grep", path);
    assert_true(fp != NULL, "test_diag_open_file_valid_path", "valid path should open");
    if (fp != NULL) {
        fclose(fp);
    }
    unlink(path);
    free(path);
}

static void test_diag_exit_code_mapping(void) {
    assert_i_eq(diag_exit_code(5, 0), 0, "test_diag_exit_code_mapping", "matches>0, errors=0 => 0");
    assert_i_eq(diag_exit_code(0, 0), 1, "test_diag_exit_code_mapping", "no matches, no errors => 1");
    assert_i_eq(diag_exit_code(5, 2), 1, "test_diag_exit_code_mapping", "matches with errors => 1");
    assert_i_eq(diag_exit_code(0, 2), 2, "test_diag_exit_code_mapping", "only errors => 2");
    assert_i_eq(diag_exit_code(1, 1), 1, "test_diag_exit_code_mapping", "mixed success/error => 1");
    assert_i_eq(diag_exit_code(0, 1), 2, "test_diag_exit_code_mapping", "no matches with errors => 2");
}

/* Manual stderr diagnostic content test idea:
   run in subprocess with stderr redirected to a temp file and assert it contains:
   "mini-grep: <path>: <reason>" */

int main(void) {
    test_diag_open_file_nonexistent();
    test_diag_open_file_valid_path();
    test_diag_exit_code_mapping();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
