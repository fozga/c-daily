# Day 01 Reference Notes - GCC and Make Workflow

This document is a compact but complete reference for Day 01. Keep it open while building `main.c`, `util.c`, `util.h`, and `tests.c`.

## 1) Compilation Pipeline

C builds are a 4-stage pipeline:

1. **Preprocessing**: expands `#include`, macros, and conditionals into one preprocessed source.
2. **Compilation**: converts preprocessed C into assembly, performing syntax/semantic checks.
3. **Assembly**: turns assembly into machine code inside an object file (`.o`).
4. **Linking**: resolves symbols across object files/libraries and produces an executable.

A **translation unit** is one `.c` file *after preprocessing*. If you have `main.c` and `util.c`, you get two translation units, then two object files, then one linked binary.

An **object file** contains machine instructions, symbol tables (defined/undefined names), and relocation information used by the linker to patch addresses.

- **Compile-time error**: detected before linking (syntax error, type mismatch, undeclared identifiers).
- **Link-time error**: source compiled, but final symbol resolution failed (e.g., `undefined reference`).

### Example

```bash
# 1) Preprocess only
gcc -E main.c -o main.i

# 2) Compile to assembly
gcc -S main.c -o main.s

# 3) Compile+assemble to object
gcc -c main.c -o main.o
gcc -c util.c -o util.o

# 4) Link objects to executable
gcc main.o util.o -o app
```

### Common mistakes

- Compiling only `main.c` and forgetting `util.c`, then getting `undefined reference`.
- Treating a link error as if it were a syntax problem in the current `.c` file.
- Circular include design that forces fragile header dependencies.

> **C vs C++:** C has no template instantiation step and typically simpler symbol naming behavior than C++. For interop with C++ code, `extern "C"` disables C++ name mangling for C-callable symbols.

## 2) Header files and include discipline

Headers (`.h`) define interfaces: function declarations, types, macro constants, and optional `static inline` helpers. They should not contain normal function definitions with external linkage.

Use include guards in every project header:

- `#ifndef UTIL_H`
- `#define UTIL_H`
- header contents
- `#endif`

`#pragma once` is widely supported and convenient, but classic include guards are fully portable and explicit.

Include style:

- `#include <stdio.h>` for system/standard headers.
- `#include "util.h"` for project-local headers.

What belongs in headers:

- Function declarations
- `typedef` declarations and struct declarations
- Macro constants and compile-time configuration
- `static inline` helpers (small, header-only)

What should not be in headers:

- Non-inline function definitions with external linkage
- Mutable global variable definitions

### Example

```c
/* util.h */
#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

void util_reverse_string(char *s, size_t len);

#endif
```

```c
/* util.c */
#include "util.h"

void util_reverse_string(char *s, size_t len) {
    for (size_t i = 0; i < len / 2; ++i) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}
```

### Common mistakes

- Defining a regular function in a header included by many `.c` files, causing multiple definitions.
- Omitting include guards, causing duplicate declarations and redefinition errors.
- Putting mutable globals in headers instead of declaring `extern` in header and defining once in a `.c`.

> **C vs C++:** C has no classes/namespaces for encapsulation. In C, hide implementation with opaque struct pointers plus a clear API boundary in headers.

## 3) GCC warning flags explained

Treat warnings as design feedback, not noise.

- `-Wall`: enables a broad baseline of common warnings.
- `-Wextra`: adds stricter checks beyond `-Wall`.
- `-Wpedantic`: warns on non-standard extensions and strict conformance issues.
- `-Werror`: promotes warnings to errors (prevents warning debt).
- `-Wshadow`: warns when a declaration shadows another name.
- `-Wvla`: warns when variable-length arrays are used.
- `-Wstrict-prototypes`: warns if function declarations omit explicit parameter lists (e.g., `int f();`).

### Example

```bash
gcc -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror -Wshadow -Wvla -Wstrict-prototypes -c tests.c
```

```c
int util_do_work();   /* triggers -Wstrict-prototypes in C */

int main(void) {
    int i = 0;
    if (1) {
        int i = 42;   /* triggers -Wshadow */
        (void)i;
    }
    return 0;
}
```

### Common mistakes

- Assuming `-Wall` means *all* warnings (it does not).
- Ignoring warnings because program is "small" or "temporary."
- Enabling `-Werror` too late, after warning debt accumulates.

> **C vs C++:** Modern C requires visible declarations before use; implicit undeclared function calls are not valid C11. Keep prototypes explicit and strict.

## 4) Debug symbols and the `-g` flag

Debug symbols (typically DWARF data) map machine code back to source files, line numbers, function names, and variable metadata. GDB uses this map to show source-level stack traces and inspect state.

`-O0 -g` is ideal for debugging:

- `-O0` keeps execution closer to source order.
- `-g` preserves debug metadata.

With optimized builds (`-O2`), debugging can become confusing due to inlining, dead-code elimination, variable coalescing, and instruction reordering.

### Example

```bash
gcc -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror util.c tests.c -o test_runner
gdb ./test_runner
```

### Common mistakes

- Trying to debug a binary built without `-g`.
- Stepping through an `-O2` binary and expecting exact source correspondence.
- Stripping symbols before debugging (`strip` or aggressive packaging settings).

> **C vs C++:** Debug symbol behavior is fundamentally the same; the toolchain treatment of `-g` and optimization tradeoffs is equivalent.

## 5) Make targets and Makefile basics

A Make rule has:

- **Target**: file or logical action to build.
- **Prerequisites**: files needed before target can run.
- **Recipe**: shell commands (must start with a tab).

Automatic variables:

- `$@` target name
- `$^` all prerequisites
- `$<` first prerequisite

Use `.PHONY` for non-file targets like `test`, `clean`, `asan`, `valgrind`, so Make does not confuse them with files of the same name.

Pattern rules (e.g., `%.o: %.c`) prevent repetitive compile commands and support incremental rebuilds. Dependency tracking matters because Make should rebuild only what changed.

### Example

```make
CC = gcc
CFLAGS = -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror

.PHONY: test clean

test_runner: util.o tests.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: test_runner
	./$<

clean:
	rm -f *.o test_runner
```

### Common mistakes

- Using spaces instead of a tab at recipe start.
- Forgetting `.PHONY` for logical targets.
- Omitting required prerequisites, causing stale or inconsistent builds.

> **C vs C++:** Make is language-agnostic. The C-specific nuance is accurate header dependency handling so changed headers trigger correct recompilation.

## 6) AddressSanitizer (ASan)

ASan is compiler/runtime instrumentation that detects memory safety bugs at runtime, including:

- heap buffer overflow
- stack buffer overflow
- use-after-free
- use-after-scope

Enable ASan on both compile and link steps using `-fsanitize=address`.

ASan reports typically include:

- error class (e.g., `heap-use-after-free`)
- stack trace for faulting access
- allocation/free stack traces
- memory region diagnostics (shadow memory hints)

ASan aborts on first detected error by default, which makes failures loud and actionable.

Overhead is expected (~1.5-2x slowdown and roughly ~2x memory), acceptable for testing/CI but usually not for production binaries.

### Example

```bash
gcc -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror -fsanitize=address util.c tests.c -o test_runner_asan
./test_runner_asan
```

### Common mistakes

- Passing ASan flag during compilation but not during linking (or vice versa).
- Running symbol-stripped binaries and getting unreadable stack traces.
- Treating ASan-only runs as a replacement for logic tests.

> **C vs C++:** Usage and diagnostics are effectively identical across C and C++ when using ASan-enabled toolchains.

## 7) Valgrind Memcheck

Valgrind Memcheck is dynamic binary instrumentation that reports:

- memory leaks
- invalid reads/writes
- use of uninitialized values

Useful flags:

- `--leak-check=full`: detailed leak report with stack traces
- `--show-leak-kinds=all`: show all leak categories
- `--track-origins=yes`: trace origin of uninitialized values

Leak categories:

- **definitely lost**: no pointer to block remains; must fix.
- **indirectly lost**: leaked via another leaked owner; fix the root owner leak.
- **possibly lost**: uncertain reachability (e.g., interior pointer); investigate.
- **still reachable**: memory reachable at exit; often tolerated in short-lived apps, but should be avoided in libraries/long-running services.

Valgrind is much slower than native execution (commonly 10-50x). Run it on a normal debug build, not an ASan-instrumented binary.

### Example

```bash
gcc -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror util.c tests.c -o test_runner
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_runner
```

### Common mistakes

- Running Valgrind on ASan binaries (tools interfere and results are noisy/unreliable).
- Ignoring "still reachable" in reusable library code.
- Accepting leak summaries without reading stack traces to find ownership bugs.

> **C vs C++:** In C there is no destructor-based automatic cleanup, so explicit ownership discipline is essential and leak risk is higher.

## 8) GDB basics

GDB (GNU Debugger) lets you run a program under controlled conditions, pause execution, inspect state, and step through code line by line. It relies on debug symbols produced by `-g`.

Core workflow:

1. Start the binary under GDB: `gdb ./test_runner`.
2. Set a breakpoint before the code of interest: `break util_reverse_string` or `break main.c:14`.
3. Run the program: `run` (optionally followed by command-line arguments).
4. When execution pauses, inspect locals: `print x`, `info locals`.
5. Step one source line (enter function calls): `step`.
6. Step over one source line (skip function body): `next`.
7. Continue to next breakpoint: `continue`.
8. Print a backtrace: `backtrace` (or `bt`).
9. Quit: `quit`.

GDB also supports watching memory (`watch`), conditional breakpoints (`break f if x == 0`), and examining raw memory (`x/8xb ptr`).

### Example

```bash
# Build with debug symbols
gcc -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror util.c tests.c -o test_runner

# Start GDB
gdb ./test_runner
(gdb) break util_reverse_string
(gdb) run
(gdb) info locals
(gdb) print s
(gdb) next
(gdb) backtrace
(gdb) quit
```

### Common mistakes

- Forgetting to rebuild with `-g` before launching GDB (stale binary shows wrong lines).
- Stepping into library internals instead of using `next` to stay in your own code.
- Not setting a breakpoint and accidentally running the program to completion.

> **C vs C++:** GDB commands are the same for C and C++. C++ adds `info vtbl` and demangled names, but the core workflow is identical.
