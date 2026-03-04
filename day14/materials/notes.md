# Day 14 Notes - Static library integration and CLI wiring

## 1) Static libraries vs shared libraries

### Static library (`.a`)
- Archive of object files (`.o`) built with `ar`.
- Linked into final executable at link time.
- Increases executable size but simplifies deployment.

### Shared library (`.so`)
- Loaded at runtime by dynamic linker.
- Smaller executables and shared code in memory.
- Requires runtime library availability and ABI compatibility management.

When static linking is useful:
- simple deployment environments
- reproducible toolchains
- educational projects and self-contained binaries

## 2) How `ar` works

Typical command:
- `ar rcs libcdrills.a file1.o file2.o ...`

Flags:
- `r`: insert/replace members
- `c`: create archive if missing
- `s`: write index (symbol table) for faster linking

### Example

```makefile
# Compile each module to an object file
line_parser.o: line_parser.c line_parser.h
	$(CC) $(CFLAGS) -c line_parser.c

store.o: store.c store_internal.h store.h
	$(CC) $(CFLAGS) -c store.c

binrec.o: binrec.c binrec.h
	$(CC) $(CFLAGS) -c binrec.c

# Archive all objects into a static library
libcdrills.a: line_parser.o store.o binrec.o
	ar rcs $@ $^            # r=replace, c=create, s=write symbol index

# Link the CLI — object files BEFORE the library reference
cdrills: cli.o libcdrills.a
	$(CC) $(CFLAGS) cli.o -L. -lcdrills -o $@

# Link the test runner the same way
test_runner: tests.o libcdrills.a
	$(CC) $(CFLAGS) tests.o -L. -lcdrills -o $@

.PHONY: test clean lib cli
test: test_runner
	./test_runner

clean:
	rm -f *.o *.a cdrills test_runner
```

## 3) Link order matters

GNU linker resolves symbols left-to-right.

If library appears before objects that reference it, unresolved symbols can
remain unresolved.

```bash
# Correct: objects that USE the library come before the -l flag
gcc cli.o -L. -lcdrills -o cdrills

# Wrong: linker resolves -lcdrills first, finds no references yet,
#        discards its symbols, then hits cli.o which needs them
gcc -L. -lcdrills cli.o -o cdrills
# → undefined reference to 'lp_read_line', etc.
```

## 4) Umbrella headers

An umbrella header (like `cdrills_lib.h`) re-exports multiple module headers.

Benefits:
- one include for consumers
- clear top-level API surface

Tradeoffs:
- broader recompilation when umbrella changes
- may expose more APIs than a minimal consumer needs
- module boundaries can blur if overused

## 5) CLI dispatch in C

Typical flow:
1. validate `argc`
2. read `argv[1]` as command
3. route via `strcmp`
4. return standard exit codes (`0` success, nonzero failure)

Keep each subcommand in a helper function for readability and testing.

```c
/* cli.c */
#include "cdrills_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int cmd_parse(int argc, char **argv) {
    if (argc < 3) { fprintf(stderr, "usage: cdrills parse <file>\n"); return 1; }
    /* ... call lp_read_line / lp_parse_record from libcdrills ... */
    return 0;
}

static int cmd_store(int argc, char **argv) {
    (void)argc; (void)argv;
    /* ... demo store_create / store_set / store_get / store_destroy ... */
    return 0;
}

/* Dispatch table — easy to extend without growing if/else chains */
typedef struct { const char *name; int (*fn)(int, char **); } cmd_t;
static const cmd_t commands[] = {
    { "parse", cmd_parse },
    { "store", cmd_store },
};

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: cdrills <command> [args]\n");
        return 1;
    }
    for (size_t i = 0; i < sizeof commands / sizeof *commands; i++) {
        if (strcmp(argv[1], commands[i].name) == 0)
            return commands[i].fn(argc, argv);
    }
    fprintf(stderr, "unknown command: %s\n", argv[1]);
    return 1;
}
```

## 6) Integration tests vs unit tests

Unit tests:
- isolate one function/module

Integration smoke tests:
- exercise cross-module behavior
- catch link issues, API mismatches, and boundary contract bugs

For library assembly day, smoke tests are essential because build/link contracts
are part of correctness.

## Common mistakes

- Forgetting to include all required object files in the archive.
- Wrong link order when building CLI/tests.
- Missing `.PHONY` declarations for non-file targets.
- Coupling tests to private headers instead of public API.
- Assuming integration works because unit tests passed independently.

## C vs C++

- C often uses Make + `ar` directly for small libraries.
- C++ projects often use larger build systems with richer dependency modeling.
- Fundamentals are the same: archive objects, expose stable headers, link in
  correct order, and test integration end-to-end.
