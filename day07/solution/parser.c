#include "parser.h"

#include <errno.h>

parser_err_t parse_i32(const char* str, int32_t* out_val) {
    // TODO: Check inputs, implement parsing, set errno on overflow.
    if (str == NULL || out_val == NULL) {
        errno = EINVAL;
        return PARSE_ERR_NULL_PTR;
    }

    // TODO: Implement empty-string handling and format validation.
    (void)str;
    (void)out_val;
    return PARSE_ERR_INVALID_FMT;
}

parser_err_t parse_kvp(char* str, char** out_key, char** out_val) {
    // TODO: Check inputs and split in-place on first '='.
    if (str == NULL || out_key == NULL || out_val == NULL) {
        errno = EINVAL;
        return PARSE_ERR_NULL_PTR;
    }

    // TODO: Implement delimiter search and output assignment.
    (void)str;
    (void)out_key;
    (void)out_val;
    return PARSE_ERR_INVALID_FMT;
}
