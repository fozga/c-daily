# Day 28 Solution Workspace

## Build and run

- `make test` - build and run matcher2 tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Pattern `"[a-z]+"` is a valid POSIX regex but NOT valid in mini-grep's regex-lite. What subset does Day 28 actually implement, and why does the parser not need a `+` quantifier branch?**

> Your answer here...

---

**Q2: Pattern `[b-a]` contains a reversed range (`b` > `a` in ASCII). What should your `match_class` do — match nothing, match everything, or crash — and why?**

> Your answer here...

---

**Q3: `[^abc]` and `[abc]` share identical `match_class` internals. Walk through exactly which lines of code differ between the two and how the negation flag is applied.**

> Your answer here...

---

**Q4: A user passes pattern `[xyz` (no closing `]`) on the command line. Trace what your `match_class` does when `pat[ci]` reaches `\0`, and confirm no infinite loop is possible.**

> Your answer here...

---

**Q5: You add character class support and then run the Day 23 test suite. Test `"a.b matches xaab"` fails. What is the most likely cause, and in which part of `match_here2` would you look first?**

> Your answer here...

---

**Q6: Pattern `[A-Z]` is used with `-i` flag. Should it match lowercase `a`–`z` as well? Trace through `match_class` to show exactly where the case-folding must be applied.**

> Your answer here...

---

**Q7: The CLI receives pattern `\n` as two bytes `0x5C 0x6E` (backslash + n). Show the path through `match_here2` and `decode_escape` that turns this into a newline comparison — and explain why `strcmp(pat, "\n")` would NOT work here.**

> Your answer here...

---

**Q8: After processing escape `\n` at `pat[pi]` and `pat[pi+1]`, why must `pi` advance by `2` rather than `1`? What is the symptom if you advance by `1` only?**

> Your answer here...

---
