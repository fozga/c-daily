# Day 28 Notes - Character classes and escapes

## 1) Recursive-descent mindset

A simple parser reads pattern left-to-right and dispatches behavior by current
token type:
- literal
- wildcard `.`
- escape `\x`
- class `[ ... ]`

You can implement this with recursive-descent or equivalent iterative scanner
helpers. The key is deterministic forward progress.

## 2) Character class parsing

When parser sees `[`, it must scan until matching `]`.

Rules:
- `-` denotes range only when between two valid class characters
- otherwise treat `-` literally
- missing closing `]` must not crash (define safe fail behavior)

## 3) Negated classes

`[^ ... ]` is negated only when `^` is the first char after `[`.

Examples:
- `[^abc]` matches anything except `a`, `b`, `c`
- `[a^b]` includes literal `^` (not negation)

## 4) Escapes in pattern language vs C literals

CLI pattern input `\\n` (two chars: backslash + n) should be interpreted by
matcher parser as newline token in pattern language.

Important distinction:
- C compiler escape processing happens in source literals.
- matcher escape processing happens at runtime on pattern bytes.

## 5) Backward compatibility principle

New features must not regress old behavior:
- literals still match as before
- `.` wildcard unchanged
- case-insensitive mode semantics preserved

This mirrors real tool evolution: additive features with stable contracts.

## Common mistakes

- infinite loops when scanning malformed classes
- treating every `-` as range operator regardless of position
- applying negation logic when `^` is not first class char
- not handling escaped `]` or `\` safely
- breaking old tests while adding new syntax

## C vs C++

- In C, parser state is often explicit pointers and indices.
- C++ might use parser combinators/objects; C keeps control-flow manual.
- Regardless of language, grammar edge cases require exhaustive tests.
