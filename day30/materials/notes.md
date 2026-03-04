# Day 30 Notes - Stress testing and release hardening

## 1) Fuzzing and stress-testing mindset

Stress tests intentionally feed unexpected or hostile input to expose latent
crashes:
- malformed arguments
- very long patterns
- binary content
- huge input streams

Random data generators (`/dev/urandom`) are useful for uncovering unhandled
edge conditions that deterministic unit tests miss.

## 2) Binary data and C string APIs

If raw binary bytes include `\0`, C string functions like `strlen` treat that
as end-of-string. This can alter matching behavior, but should still remain
memory-safe as long as bounds are respected.

Key principle:
- semantic oddity is acceptable
- memory unsafety is not

## 3) Very long lines

`fgets(buf, 4096, fp)` reads chunks when line exceeds buffer capacity.
Robust scanners should process continuation chunks safely without assuming one
`fgets` call equals one logical line in extreme cases.

## 4) Release build posture

Typical release adjustments:
- `-O2` for optimized performance
- optional `-DNDEBUG` to disable assertions
- `strip` to reduce binary size

But reliability checks must happen before stripping symbols if debugging is
expected.

## 5) Release notes and retrospectives

A useful retrospective documents:
- top bugs found late and root causes
- tooling impact (ASan/Valgrind/GDB)
- architecture trade-offs made during implementation
- what would be improved next

## Common mistakes

- Treating stress failures as "rare" and ignoring them.
- Equating non-crash with correctness (silent wrong behavior still matters).
- Running stress tests only once.
- Stripping binary before debugging unresolved crashes.

## C vs C++

- Same reliability principles apply in both languages.
- C gives fewer runtime safety rails, so stress testing is especially valuable.
