#pragma once

typedef struct {
    char* name;
    int*  data;
    int   count;
} task_t;

/* Creates a task. Allocates memory for the task and its internal data. */
task_t* task_create(const char* name, int count);

/* Processes the task. Returns a new allocated string summarizing the result. */
char* task_process(task_t* task);

/* Cleans up the task. */
void task_destroy(task_t* task);

/* Global init and cleanup for the workflow subsystem. */
void workflow_init(void);
void workflow_shutdown(void);
