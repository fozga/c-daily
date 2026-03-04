#include "line_parser.h"

lp_err_t lp_read_line(FILE* fp, char* buf, size_t buf_size) {
    (void)fp;
    (void)buf;
    (void)buf_size;
    /* TODO: read one full line with fgets(), strip newline, and map EOF vs I/O errors. */
    return LP_ERR_IO;
}

lp_err_t lp_parse_record(const char* line, lp_record_t* rec) {
    (void)line;
    (void)rec;
    /* TODO: parse "id,name,score" with robust validation and error code mapping. */
    return LP_ERR_INVALID_FMT;
}
