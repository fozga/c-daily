#pragma once
#include <stdint.h>
#include <stdio.h>

/* BUG: field ordering introduces padding — binary layout is not what you expect */
typedef struct {
    uint8_t  flags;
    uint32_t id;
    uint8_t  status;
    uint16_t code;
} padded_record_t;

/* TODO: define fixed_record_t with the same fields reordered to eliminate
   unnecessary padding and match the on-disk format exactly. */

/* Writes one record to fp in raw binary form (no conversion). */
int layout_write(FILE* fp, const padded_record_t* rec);

/* Reads one record from fp into out_rec. */
int layout_read(FILE* fp, padded_record_t* out_rec);
