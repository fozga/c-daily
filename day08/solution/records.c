#include "records.h"

void records_sort_by_id(record_t* arr, size_t count) {
    (void)arr;
    (void)count;
    /* TODO: implement comparator for id and call qsort(). */
}

void records_sort_by_name(record_t* arr, size_t count) {
    (void)arr;
    (void)count;
    /* TODO: implement comparator for name and call qsort(). */
}

const record_t* records_find_by_id(const record_t* arr, size_t count, int32_t id) {
    (void)arr;
    (void)count;
    (void)id;
    /* TODO: prepare key and call bsearch() with id comparator. */
    return NULL;
}
