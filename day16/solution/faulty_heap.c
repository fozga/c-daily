#include "faulty_heap.h"

#include <stdio.h>
#include <stdlib.h>

char* make_string_of_As(size_t len) {
    char* s = (char*)malloc(len); /* INTENTIONAL BUG: should allocate len + 1 */
    size_t i = 0;

    if (s == NULL) {
        return NULL;
    }

    for (i = 0; i < len; ++i) {
        s[i] = 'A';
    }
    s[len] = '\0'; /* INTENTIONAL BUG: heap-buffer-overflow by 1 byte */
    return s;
}

int replace_chars(char* str, char target, char replacement) {
    int count = 0;
    size_t i = 0;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] == target) {
            str[i] = replacement;
            ++count;
            if (count == 1) {
                free(str); /* INTENTIONAL BUG: freeing mid-loop */
            }
        }
        /* INTENTIONAL BUG: loop continues using freed memory (use-after-free). */
    }

    return count;
}

const char* get_greeting(const char* name) {
    char buf[128];
    static const char* escaped_ptr = NULL;

    if (name == NULL) {
        name = "guest";
    }

    (void)snprintf(buf, sizeof(buf), "Hello, %s!", name);

    /* INTENTIONAL BUG: returning pointer to stack memory via escaped alias. */
    escaped_ptr = buf;
    return escaped_ptr;
}
