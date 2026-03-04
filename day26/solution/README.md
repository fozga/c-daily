# Day 26 Solution Workspace

## Build and run

- `make build` - build `mini-grep` from integrated project sources.
- `make test` - run integration matrix script.
- `make clean` - remove built binary.

Direct invocation:
- `bash test_matrix.sh ./mini-grep`

## Answers

**Q1: Your unit tests for `matcher_match_line` all pass, but the shell matrix reveals that `mini-grep -n "foo" a.txt` prints line numbers starting from `0` instead of `1`. Why couldn't the unit test catch this, and why does the integration test catch it?**

> Your answer here...

---

**Q2: A test case runs `"$GREP" "foo" fixtures/simple.txt` and checks `$?`. Another developer changes the fixture file to add a matching line. The test now fails. Is this a problem with the test or with the fixture? How should fixtures be managed?**

> Your answer here...

---

**Q3: Describe a test case that validates the multi-file filename prefix: what fixture files do you need, what command do you run, and what exact stdout output do you assert?**

> Your answer here...

---

**Q4: Your test script checks stdout with `diff` but never captures stderr. mini-grep is accidentally printing an extra blank line to stderr on every run. Would this test matrix catch that bug? What change fixes the gap?**

> Your answer here...

---

**Q5: A golden output snapshot test for `-i "HELLO" file.txt` starts failing after you fix a bug where `-i` was also lowercasing the *output* line (it should preserve the original case). Is updating the golden output correct here? Justify your answer.**

> Your answer here...

---

**Q6: `test_matrix.sh` tests `mini-grep "foo" nofile.txt` and expects exit code `2`. After the Day 25 changes, the exit code is actually `1` because `any_match` stays false but `any_error` is true and there are no other files. Is the test wrong or the implementation wrong — trace through the exit-code logic.**

> Your answer here...

---

**Q7: Your matrix currently runs `bash test_matrix.sh ./mini-grep` manually. Name two things you would need to change to make it run reliably in a CI pipeline.**

> Your answer here...

---

**Q8: Explain why testing `mini-grep -h` requires asserting both stdout content AND exit code — and why asserting only the exit code would be insufficient.**

> Your answer here...

---
