#include "binrec.h"

binrec_err_t binrec_write(FILE* fp, const binrec_entry_t* entries, size_t count) {
    (void)fp;
    (void)entries;
    (void)count;
    /* TODO: write magic/version/count header, then write entries with fwrite(). */
    return BINREC_ERR_IO;
}

binrec_err_t binrec_read(FILE* fp, binrec_entry_t* out_entries, size_t* out_count) {
    (void)fp;
    (void)out_entries;
    (void)out_count;
    /* TODO: read/validate header and read entries, mapping bad magic/version/truncation errors. */
    return BINREC_ERR_IO;
}
