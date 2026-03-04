#include "strview.h"

strview sv_from_cstr(const char* cstr) {
    // TODO: compute length by walking bytes until '\0'.
    strview out;
    if (cstr == NULL) {
        out.data = NULL;
        out.length = 0u;
        return out;
    }

    out.data = cstr;
    out.length = 0u;
    return out;
}

bool sv_equals(strview a, strview b) {
    // TODO: compare lengths first, then compare byte-by-byte up to length.
    (void)a;
    (void)b;
    return false;
}

strview sv_trim(strview sv) {
    // TODO: iterate without relying on '\0' and trim leading/trailing whitespace.
    (void)sv;
    strview out;
    out.data = NULL;
    out.length = 0u;
    return out;
}

int sv_find(strview sv, char target) {
    // TODO: scan within [0, sv.length) only.
    (void)sv;
    (void)target;
    return -1;
}

bool sv_split_once(strview sv, char delimiter, strview* out_left, strview* out_right) {
    // TODO: find delimiter and write two views without copying bytes.
    (void)sv;
    (void)delimiter;
    (void)out_left;
    (void)out_right;
    return false;
}
