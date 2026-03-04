#include "parallel_scanner.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

static void test_parallel_count_accuracy(void) {
    enum { FILES_N = 1000 };
    const char** files = (const char**)malloc(sizeof(*files) * FILES_N);
    char** names = (char**)malloc(sizeof(*names) * FILES_N);
    int total = 0;
    int i = 0;

    assert_true(files != NULL, "test_parallel_count_accuracy", "files array allocated");
    assert_true(names != NULL, "test_parallel_count_accuracy", "names array allocated");
    if (files == NULL || names == NULL) {
        free(files);
        free(names);
        return;
    }

    for (i = 0; i < FILES_N; ++i) {
        names[i] = (char*)malloc(32u);
        assert_true(names[i] != NULL, "test_parallel_count_accuracy", "filename allocated");
        if (names[i] == NULL) {
            continue;
        }
        snprintf(names[i], 32u, "file_%d", i);
        files[i] = names[i];
    }

    total = parallel_scan(files, FILES_N, 4);
    assert_i_eq(total, FILES_N, "test_parallel_count_accuracy", "parallel total must equal file count");

    for (i = 0; i < FILES_N; ++i) {
        free(names[i]);
    }
    free(names);
    free(files);
}

int main(void) {
    test_parallel_count_accuracy();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
