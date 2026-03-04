#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define LP_LINE_MAX 256

typedef enum {
    LP_OK              = 0,
    LP_ERR_NULL        = -1,
    LP_ERR_EOF         = -2,
    LP_ERR_IO          = -3,
    LP_ERR_INVALID_FMT = -4,
    LP_ERR_OUT_OF_RANGE= -5
} lp_err_t;

typedef struct {
    int32_t id;
    char    name;
    double  score;
} lp_record_t;

/* Reads one line from 'fp' into 'buf' (max 'buf_size' bytes including NUL).
   Strips the trailing newline if present.
   Returns LP_OK, LP_ERR_EOF, LP_ERR_IO, or LP_ERR_NULL. */
lp_err_t lp_read_line(FILE* fp, char* buf, size_t buf_size);

/* Parses a line of the form "id,name,score" into 'rec'.
   Returns LP_OK, LP_ERR_NULL, LP_ERR_INVALID_FMT, or LP_ERR_OUT_OF_RANGE. */
lp_err_t lp_parse_record(const char* line, lp_record_t* rec);
