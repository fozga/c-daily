#include "records.h"

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

static void assert_str_eq(const char* actual, const char* expected, const char* test_name, const char* detail) {
    ++g_assertions;
    if (strcmp(actual, expected) != 0) {
        ++g_failures;
        fprintf(stderr,
                "[FAIL] %s: %s (expected=\"%s\", actual=\"%s\")\n",
                test_name,
                detail,
                expected,
                actual);
    }
}

static bool is_sorted_by_id(const record_t* arr, size_t count) {
    if (arr == NULL || count < 2) {
        return true;
    }
    for (size_t i = 1; i < count; ++i) {
        if (arr[i - 1].id > arr[i].id) {
            return false;
        }
    }
    return true;
}

static void test_sort_by_id_already_sorted(void) {
    record_t arr[] = {
        {.id = 1, .name = "A", .score = 1.0},
        {.id = 2, .name = "B", .score = 2.0},
        {.id = 3, .name = "C", .score = 3.0},
    };

    records_sort_by_id(arr, 3);

    assert_i32_eq(arr[0].id, 1, "test_sort_by_id_already_sorted", "first id remains smallest");
    assert_i32_eq(arr[1].id, 2, "test_sort_by_id_already_sorted", "second id remains middle");
    assert_i32_eq(arr[2].id, 3, "test_sort_by_id_already_sorted", "third id remains largest");
}

static void test_sort_by_id_reversed(void) {
    record_t arr[] = {
        {.id = 30, .name = "Z", .score = 1.0},
        {.id = 20, .name = "Y", .score = 2.0},
        {.id = 10, .name = "X", .score = 3.0},
    };

    records_sort_by_id(arr, 3);

    assert_i32_eq(arr[0].id, 10, "test_sort_by_id_reversed", "smallest id should move to index 0");
    assert_i32_eq(arr[1].id, 20, "test_sort_by_id_reversed", "middle id should move to index 1");
    assert_i32_eq(arr[2].id, 30, "test_sort_by_id_reversed", "largest id should move to index 2");
}

static void test_sort_by_id_single_element(void) {
    record_t arr[] = {
        {.id = 42, .name = "Only", .score = 9.9},
    };

    records_sort_by_id(arr, 1);
    assert_i32_eq(arr[0].id, 42, "test_sort_by_id_single_element", "single element should remain unchanged");
}

static void test_sort_by_name_alphabetical(void) {
    record_t arr[] = {
        {.id = 1, .name = "zeta", .score = 0.0},
        {.id = 2, .name = "alpha", .score = 0.0},
        {.id = 3, .name = "delta", .score = 0.0},
        {.id = 4, .name = "beta", .score = 0.0},
    };

    records_sort_by_name(arr, 4);

    assert_str_eq(arr[0].name, "alpha", "test_sort_by_name_alphabetical", "name[0]");
    assert_str_eq(arr[1].name, "beta", "test_sort_by_name_alphabetical", "name[1]");
    assert_str_eq(arr[2].name, "delta", "test_sort_by_name_alphabetical", "name[2]");
    assert_str_eq(arr[3].name, "zeta", "test_sort_by_name_alphabetical", "name[3]");
}

static void test_find_by_id_found_first(void) {
    record_t arr[] = {
        {.id = 5, .name = "E", .score = 1.0},
        {.id = 1, .name = "A", .score = 1.0},
        {.id = 3, .name = "C", .score = 1.0},
    };
    records_sort_by_id(arr, 3);
    assert_true(is_sorted_by_id(arr, 3), "test_find_by_id_found_first", "array must be sorted before bsearch");

    const record_t* rec = records_find_by_id(arr, 3, 1);
    assert_true(rec != NULL, "test_find_by_id_found_first", "should find first id");
    if (rec != NULL) {
        assert_i32_eq(rec->id, 1, "test_find_by_id_found_first", "matched id");
    }
}

static void test_find_by_id_found_middle(void) {
    record_t arr[] = {
        {.id = 30, .name = "C", .score = 0.0},
        {.id = 10, .name = "A", .score = 0.0},
        {.id = 20, .name = "B", .score = 0.0},
    };
    records_sort_by_id(arr, 3);
    assert_true(is_sorted_by_id(arr, 3), "test_find_by_id_found_middle", "array must be sorted before bsearch");

    const record_t* rec = records_find_by_id(arr, 3, 20);
    assert_true(rec != NULL, "test_find_by_id_found_middle", "should find middle id");
    if (rec != NULL) {
        assert_i32_eq(rec->id, 20, "test_find_by_id_found_middle", "matched id");
    }
}

static void test_find_by_id_found_last(void) {
    record_t arr[] = {
        {.id = 2, .name = "B", .score = 0.0},
        {.id = 1, .name = "A", .score = 0.0},
        {.id = 9, .name = "I", .score = 0.0},
    };
    records_sort_by_id(arr, 3);
    assert_true(is_sorted_by_id(arr, 3), "test_find_by_id_found_last", "array must be sorted before bsearch");

    const record_t* rec = records_find_by_id(arr, 3, 9);
    assert_true(rec != NULL, "test_find_by_id_found_last", "should find last id");
    if (rec != NULL) {
        assert_i32_eq(rec->id, 9, "test_find_by_id_found_last", "matched id");
    }
}

static void test_find_by_id_not_found(void) {
    record_t arr[] = {
        {.id = 4, .name = "D", .score = 0.0},
        {.id = 1, .name = "A", .score = 0.0},
        {.id = 2, .name = "B", .score = 0.0},
    };
    records_sort_by_id(arr, 3);
    assert_true(is_sorted_by_id(arr, 3), "test_find_by_id_not_found", "array must be sorted before bsearch");

    const record_t* rec = records_find_by_id(arr, 3, 7);
    assert_true(rec == NULL, "test_find_by_id_not_found", "unknown id should not be found");
}

static void test_find_by_id_empty_array(void) {
    const record_t* rec = records_find_by_id(NULL, 0, 1);
    assert_true(rec == NULL, "test_find_by_id_empty_array", "empty array should not produce a match");
}

int main(void) {
    test_sort_by_id_already_sorted();
    test_sort_by_id_reversed();
    test_sort_by_id_single_element();

    test_sort_by_name_alphabetical();

    test_find_by_id_found_first();
    test_find_by_id_found_middle();
    test_find_by_id_found_last();
    test_find_by_id_not_found();
    test_find_by_id_empty_array();

    if (g_failures != 0) {
        fprintf(stderr, "\nAssertions: %d, Failures: %d\n", g_assertions, g_failures);
        return 1;
    }

    printf("All tests passed. Assertions: %d\n", g_assertions);
    return 0;
}
