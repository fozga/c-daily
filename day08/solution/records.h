#pragma once
#include <stddef.h>
#include <stdint.h>

#define RECORD_NAME_MAX 64

typedef struct {
    int32_t id;
    char    name[RECORD_NAME_MAX];
    double  score;
} record_t;

/* Sorts records in-place by id (ascending). */
void records_sort_by_id(record_t* arr, size_t count);

/* Sorts records in-place by name (ascending, lexicographic). */
void records_sort_by_name(record_t* arr, size_t count);

/* Binary-searches for a record with matching id in a sorted (by id) array.
   Returns a pointer to the matching record, or NULL if not found.
   Precondition: arr must be sorted by id. */
const record_t* records_find_by_id(const record_t* arr, size_t count, int32_t id);
