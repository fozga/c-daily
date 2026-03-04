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

### Manual parsing loop

Pros:
- Full control over parsing behavior.
- Very transparent for learning and custom grammar.

Cons:
- Easy to introduce edge-case bugs.
- More boilerplate for combined flags, operands, diagnostics.

### `getopt` / `getopt_long`

Pros:
- Standardized option handling.
- Built-in support for common CLI style.

Cons:
- Some portability nuances and API quirks.
- Can be less explicit for educational exercises.

For this day, manual parser logic builds fundamentals for later project days.

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
- stop parsing options once positional pattern is found
- support missing operands gracefully with clear diagnostics

## Common mistakes

- Dereferencing `argv[i]` without checking range.
- Parsing flags after positional pattern when not intended.
- Printing all messages to stdout (including errors).
- Returning exit code `0` on malformed usage.
- Treating `-` prefixed filenames as flags in wrong parse phase.

## C vs C++

- C uses raw pointers and `strcmp` for argument matching.
- C++ often uses wrappers (`std::string`, parsing libraries).
- C has no built-in optional types, so explicit boolean flags are common.
