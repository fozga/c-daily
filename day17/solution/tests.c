#include "leaky_workflow.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

static void test_workflow_roundtrip(void) {
    task_t* task = NULL;
    char* summary = NULL;

    workflow_init();

    task = task_create("alpha", 4);
    assert_true(task != NULL, "test_workflow_roundtrip", "task_create should succeed");
    if (task == NULL) {
        workflow_shutdown();
        return;
    }

    summary = task_process(task);
    assert_true(summary != NULL, "test_workflow_roundtrip", "task_process should return summary");
    if (summary != NULL) {
        assert_true(strstr(summary, "task=alpha") != NULL,
                    "test_workflow_roundtrip",
                    "summary should contain task name");
        assert_true(strstr(summary, "count=4") != NULL,
                    "test_workflow_roundtrip",
                    "summary should contain task count");
    }

    free(summary);
    task_destroy(task);
    workflow_shutdown();
}

int main(void) {
    test_workflow_roundtrip();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
