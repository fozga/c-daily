# Day 10 Notes - Binary I/O and deterministic layouts

## 1) `fopen` modes and why binary mode matters

Use explicit binary modes for binary files:
- `"rb"` for reading
- `"wb"` for writing
- `"ab"` for appending

On Linux, text and binary modes behave similarly for most streams. On Windows,
text mode can translate line endings (`\n` <-> `\r\n`), which corrupts binary
payloads. Using binary mode everywhere is a good cross-platform habit.

## 2) `fread` / `fwrite` semantics

### Signatures
- `size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);`
- `size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);`

### Return values

They return number of **items**, not bytes (unless `size == 1`).

If you request `nmemb = 8` and receive `5`, only 5 complete elements were
processed.

### Error detection

When short read/write occurs:
- check `feof(stream)` to detect end-of-file on read
- check `ferror(stream)` for I/O errors

Never assume a single call fully succeeds without checking return count.

## 3) Fixed-width integer types for file formats

Binary formats must be explicit about field size. Use `<stdint.h>` types:
- `uint32_t`
- `int32_t`
- `uint16_t`, etc.

Avoid plain `int`, `long`, `unsigned long` in format definitions because their
sizes vary by ABI and platform.

If field width changes across builds, your file format silently breaks.

## 4) Endianness basics

Multi-byte integers are byte sequences; byte order differs by architecture:
- little-endian: least-significant byte first
- big-endian: most-significant byte first

If you write raw host-order bytes and read on opposite-endian systems, numeric
fields decode incorrectly.

### Common solutions

- Standard network helpers (`htonl`, `ntohl`) for 32-bit values.
- Manual byte-swapping helpers.
- Define file format as little-endian (or big-endian) and convert at boundaries.

## 5) Format versioning and validation

A robust binary format starts with:
- magic bytes / magic number to identify file type
- version field to support future evolution
- record count and other bounds needed for sanity checks

On read:
1. Validate magic first.
2. Validate supported version.
3. Validate declared counts and prevent truncated overreads.

Reject unknown versions rather than guessing interpretation. This prevents
silent data corruption.

## Common mistakes

- Using text mode (`"w"`/`"r"`) for binary payloads.
- Assuming `fread` returns bytes.
- Failing to handle truncated files.
- Writing structs with non-portable fields (`int`, padding-sensitive layouts).
- Ignoring endianness when defining portable formats.
- Skipping magic/version checks.
- Trusting file-declared counts without sanity limits.

## C vs C++

- C typically uses raw `FILE*`, `fread`, `fwrite`.
- C++ often uses `std::istream`/`std::ostream` and serialization abstractions.
- C gives minimal abstraction and maximal control; correctness depends on strict
  manual checks.
- Regardless of language, binary format specs must define field sizes and byte
  order explicitly.
