#include <stdio.h>

#include "cli.h"

int main(int argc, char* argv[]) {
    cli_opts_t opts;
    cli_parse(argc, argv, &opts);
    printf("Pattern: %s\n", opts.pattern);
    printf("Files: %d\n", opts.files_count);
    printf("Flags: -n=%d -i=%d\n", opts.flag_n, opts.flag_i);
    return 0;
}
