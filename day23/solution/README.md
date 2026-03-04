# Day 23 Solution Workspace

## Build and run

- `make test` - build and run matcher tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: When matching pattern `"a.b"` against line `"xaab"`, list every start position the outer loop tries and explain at which position the inner loop succeeds — or state why it never does.**

> Your answer here...

---

**Q2: Why can't you replace `matcher_match_line` with a single call to `strstr(3)` when the pattern contains `.` wildcards?**

> Your answer here...

---

**Q3: Your `matcher_match_line` returns `1` for every line when pattern is `""` (empty string). Is this correct for mini-grep? What does real POSIX grep do with an empty pattern?**

> Your answer here...

---

**Q4: Scanning line `"aaab"` for pattern `"aab"`: how many iterations of the outer loop execute before a match is found? Trace it step by step.**

> Your answer here...

---

**Q5: The outer loop guard is `i <= llen - plen`. What happens if you change `<=` to `<`, and can you construct a test case that exposes the bug?**

> Your answer here...

---

**Q6: In the inner `match_here` loop, why must `.` be checked before the character comparison, not as a fallback after a mismatch?**

> Your answer here...

---

**Q7: Why is `tolower((unsigned char)c)` required rather than just `tolower(c)`, even though `char` and `unsigned char` hold the same bits on most platforms?**

> Your answer here...

---

**Q8: `matcher_match_line` takes `const char *line`. If the function were instead declared with `char *line` (non-const), what concrete problem could arise for mini-grep's scanner loop?**

> Your answer here...

---
