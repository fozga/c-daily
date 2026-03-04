#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum {
    PARSE_OK = 0,
    PARSE_ERR_NULL_PTR = -1,
    PARSE_ERR_EMPTY_STR = -2,
    PARSE_ERR_INVALID_FMT = -3,
    PARSE_ERR_OUT_OF_RANGE = -4
} parser_err_t;

/* Parses a base-10 integer from the string 'str'.
   Returns PARSE_OK on success and writes the result to *out_val.
   If 'str' or 'out_val' is NULL, returns PARSE_ERR_NULL_PTR.
   If 'str' contains non-numeric characters, returns PARSE_ERR_INVALID_FMT.
   If the parsed value exceeds the bounds of int32_t, returns PARSE_ERR_OUT_OF_RANGE
   and explicitly sets errno to ERANGE. */
parser_err_t parse_i32(const char* str, int32_t* out_val);

/* Extracts a key-value pair separated by '=' (e.g., "timeout=30").
   Modifies 'out_key' and 'out_val' to point to the respective parts.
   This function does NOT allocate memory; it assumes 'str' is mutable and replaces '=' with '\0'.
   Returns PARSE_OK on success.
   Returns PARSE_ERR_NULL_PTR if any argument is NULL.
   Returns PARSE_ERR_INVALID_FMT if no '=' is found. */
parser_err_t parse_kvp(char* str, char** out_key, char** out_val);
