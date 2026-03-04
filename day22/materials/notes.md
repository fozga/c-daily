# Day 22 Notes - CLI argument parsing fundamentals

## 1) `argc` and `argv`

Program entry:
- `int main(int argc, char* argv[])`

Key facts:
- `argc` is the number of arguments.
- `argv` is an array of pointers to NUL-terminated strings.
- `argv[0]` is program name (conventionally).
- `argv[argc]` is guaranteed to be `NULL`.

This allows safe bounded loops over arguments.

## 2) Manual parsing vs `getopt`

### Manual parsing loop for mini-grep

Mini-grep has three flags (`-n`, `-i`, `-h`) followed by a mandatory PATTERN
and zero or more FILE arguments. A hand-rolled loop keeps this explicit:

### Example

```c
/* cli.c - manual option parsing for mini-grep */
int i = 1;
while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0') {
    if      (strcmp(argv[i], "-n") == 0) opts->line_numbers = 1;
    else if (strcmp(argv[i], "-i") == 0) opts->ignore_case  = 1;
    else if (strcmp(argv[i], "-h") == 0) { print_usage(stdout); exit(0); }
    else {
        fprintf(stderr, "mini-grep: unknown option: %s\n", argv[i]);
        exit(2);
    }
    i++;
}
/* argv[i] is now PATTERN (if it exists) */
if (i >= argc) { print_usage(stderr); exit(1); }
opts->pattern     = argv[i++];
opts->files       = argv + i;
opts->files_count = argc - i;   /* 0 means read stdin */
```

Pros:
- Full control; immediately obvious what each branch does.
- No global state to reset between test calls.

Cons:
- Does not support combined flags like `-ni` (two separate `-n -i` required).
- More boilerplate as flag set grows.

### `getopt` / `getopt_long`

`getopt(3)` handles POSIX short-option parsing automatically.
Key globals set after each call:

| Symbol   | Meaning                                                      |
|----------|--------------------------------------------------------------|
| `optarg` | Pointer to the argument string for options declared with `:` |
| `optind` | Index of the next `argv` element not yet processed           |
| `opterr` | Set to `0` to suppress auto-printed error messages           |
| `optopt` | The unknown option character when `getopt` returns `'?'`     |

```c
/* Equivalent using getopt */
int ch;
while ((ch = getopt(argc, argv, ":nih")) != -1) {
    switch (ch) {
    case 'n': opts->line_numbers = 1;           break;
    case 'i': opts->ignore_case  = 1;           break;
    case 'h': print_usage(stdout); exit(0);
    case '?':
        fprintf(stderr, "mini-grep: unknown option: -%c\n", optopt);
        exit(2);
    }
}
/* After getopt, optind points to the first non-option argument (PATTERN). */
opts->pattern     = (optind < argc) ? argv[optind++] : NULL;
opts->files       = argv + optind;
opts->files_count = argc - optind;
```

Pros:
- Standardized option handling; supports combined flags like `-ni` for free.
- Less boilerplate for large flag sets.

Cons:
- Uses global mutable state (`optarg`, `optind`); must reset `optind = 1`
  before calling `getopt` again in unit tests.
- Portability nuances between glibc and BSD `getopt`.

For Day 22 the manual loop is used; understanding `getopt` prepares you for
projects with larger flag surfaces.

## 3) Exit code conventions

Common POSIX-oriented CLI conventions:
- `0` success
- `1` general error / no-match style result
- `2` command misuse (invalid arguments)
- `127` command not found (shell-level, not app-level)

For this CLI:
- invalid flags should exit with `2`
- usage/help path can exit with `0` (`-h`) or `1` (missing pattern)

## 4) Usage message quality

A good usage message includes:
- synopsis line
- option list with short descriptions
- at least one quick example

Output stream choice:
- Help requested by user (`-h`) -> stdout
- Usage due to error -> stderr

This preserves shell composability and proper scripting behavior.

## 5) Defensive argv parsing

Never trust user input shape.

Defensive checks:
- validate `argc` bounds before indexing
- treat unknown `-x` flags as explicit errors
- stop parsing options once positional PATTERN is found
- support missing operands gracefully with clear diagnostics

Once PATTERN is consumed from `argv`, every remaining token is a FILE — even
if it starts with `-` (e.g., a file called `-log.txt`).  Parsing must not
re-enter flag mode after the positional boundary is crossed.

## Common mistakes

- Dereferencing `argv[i]` without checking range.
- Parsing flags after the positional PATTERN has been consumed.
- Printing all messages to stdout (including errors).
- Returning exit code `0` on malformed usage (missing PATTERN should be `1`).
- Treating `-` prefixed filenames as flags after the positional boundary.
- Forgetting to reset `optind = 1` before re-invoking `getopt` in unit tests.

## C vs C++

- C uses raw pointers and `strcmp` for argument matching; `getopt` relies on
  mutable global state (`optarg`, `optind`) which is not re-entrant.
- C++ libraries like `cxxopts` or `CLI11` provide type-safe, re-entrant
  parsing with `std::string` and structured option objects.
- C has no built-in optional types, so explicit boolean flags (`int`) in a
  struct like `cli_opts_t` are the idiomatic pattern.
- Thread safety: `getopt` globals make it unsafe in multi-threaded contexts;
  `getopt_r` (non-standard) or manual parsing is required there.
