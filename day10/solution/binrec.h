#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BINREC_MAGIC   0x52454342U  /* "RECB" */
#define BINREC_VERSION 1

typedef struct {
    int32_t  id;
    int32_t  value;
    uint32_t flags;
} binrec_entry_t;

typedef enum {
    BINREC_OK            = 0,
    BINREC_ERR_NULL      = -1,
    BINREC_ERR_IO        = -2,
    BINREC_ERR_BAD_MAGIC = -3,
    BINREC_ERR_BAD_VER   = -4,
    BINREC_ERR_TRUNC     = -5
} binrec_err_t;

/* Writes header + 'count' entries to 'fp'.
   Returns BINREC_OK on success. */
binrec_err_t binrec_write(FILE* fp, const binrec_entry_t* entries, size_t count);

/* Reads and validates the header, then reads 'count' entries into 'out_entries'.
   '*out_count' is set to the number of records declared in the file header.
   Caller must ensure out_entries has space for '*out_count' records.
   Returns BINREC_OK on success. */
binrec_err_t binrec_read(FILE* fp, binrec_entry_t* out_entries, size_t* out_count);
