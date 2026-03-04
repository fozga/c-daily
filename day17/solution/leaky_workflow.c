#include "leaky_workflow.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* g_workflow_buf = NULL;

static char* dup_cstr(const char* s) {
    size_t n = 0;
    char* out = NULL;
    if (s == NULL) {
        return NULL;
    }
    n = strlen(s) + 1;
    out = (char*)malloc(n);
    if (out == NULL) {
        return NULL;
    }
    memcpy(out, s, n);
    return out;
}

void workflow_init(void) {
    if (g_workflow_buf == NULL) {
        g_workflow_buf = (char*)malloc(256); /* INTENTIONAL STILL-REACHABLE LEAK */
        if (g_workflow_buf != NULL) {
            strcpy(g_workflow_buf, "workflow-ready");
        }
    }
}

void workflow_shutdown(void) {
    /* INTENTIONAL BUG: does not free g_workflow_buf. */
}

task_t* task_create(const char* name, int count) {
    task_t* task = NULL;
    int i = 0;

    if (name == NULL || count < 0) {
        return NULL;
    }

    task = (task_t*)malloc(sizeof(*task));
    if (task == NULL) {
        return NULL;
    }

    task->name = dup_cstr(name);
    task->data = (int*)malloc((size_t)count * sizeof(int));
    task->count = count;

    if (task->name == NULL || (count > 0 && task->data == NULL)) {
        free(task->name);
        free(task->data);
        free(task);
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        task->data[i] = i + 1;
    }

    return task;
}

char* task_process(task_t* task) {
    int sum = 0;
    int i = 0;
    char* tmp = NULL;
    char* out = NULL;

    if (task == NULL) {
        return NULL;
    }

    for (i = 0; i < task->count; ++i) {
        sum += task->data[i];
    }

    tmp = (char*)malloc(128);
    if (tmp == NULL) {
        return NULL;
    }

    (void)snprintf(tmp, 128, "task=%s count=%d sum=%d", task->name, task->count, sum);

    out = dup_cstr(tmp);
    if (out == NULL) {
        /* Intentional leak of tmp in all paths below. */
        return NULL;
    }

    /* INTENTIONAL BUG: tmp should be freed here; currently definitely lost. */
    return out;
}

void task_destroy(task_t* task) {
    if (task == NULL) {
        return;
    }

    /* INTENTIONAL BUG: forget to free task->name and task->data first. */
    free(task);
}
