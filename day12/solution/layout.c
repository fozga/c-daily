#include "layout.h"

int layout_write(FILE* fp, const padded_record_t* rec) {
    if (fp == NULL || rec == NULL) {
        return -1;
    }
    /* TODO: intentionally raw fwrite of struct for now (bug source). */
    /* TODO: learner should inspect sizeof/offsetof and replace with stable layout handling. */
    return (fwrite(rec, sizeof(*rec), 1, fp) == 1) ? 0 : -1;
}

int layout_read(FILE* fp, padded_record_t* out_rec) {
    if (fp == NULL || out_rec == NULL) {
        return -1;
    }
    /* TODO: intentionally raw fread of struct for now (bug source). */
    /* TODO: learner should validate deterministic layout assumptions. */
    return (fread(out_rec, sizeof(*out_rec), 1, fp) == 1) ? 0 : -1;
}
