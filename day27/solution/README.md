# Day 27 Solution Workspace

## Build and run

- `make gen` - build fixture generator.
- `make bench` - build benchmark binary (release flags).
- `make run_bench` - generate dataset and run benchmark once.
- `make clean` - remove binaries and generated large fixture.

## Benchmark Results

| Run | Before (ms) | After (ms) | Change |
|-----|-------------|------------|--------|
| 1   | —           | —          | —      |
| 2   | —           | —          | —      |
| 3   | —           | —          | —      |
| 4   | —           | —          | —      |
| 5   | —           | —          | —      |

## Answers

**Q1: You benchmark mini-grep compiled with `-O0` before your change and `-O2` after, and report a 40% speedup. Why is this result meaningless, and what should you do instead?**

> Your answer here...

---

**Q2: The `time` command reports `real 2.1s user 1.8s sys 0.3s` for a mini-grep run. Which value is wall-clock time, and why might `user + sys` be less than `real` in this scenario?**

> Your answer here...

---

**Q3: You run the benchmark 5 times and get: 210 ms, 198 ms, 205 ms, 312 ms, 201 ms. What is the median, and why is it a better summary than the mean or the minimum?**

> Your answer here...

---

**Q4: Describe one concrete change to mini-grep's `scanner_run` that could improve throughput on a 1M-line file, explain which bottleneck it addresses, and describe how you would confirm it actually helped.**

> Your answer here...

---

**Q5: Your benchmark binary has a loop that calls `matcher_match_line` but discards the return value. At `-O2`, the compiler might remove the call entirely. How can you prevent this while keeping the benchmark realistic?**

> Your answer here...

---

**Q6: Run 1 of your benchmark takes 450 ms; runs 2–5 average 210 ms. You discard run 1. Is this valid? What is the technical reason for the first-run anomaly?**

> Your answer here...

---

**Q7: `perf stat` shows `instructions per cycle (IPC) = 0.4` for mini-grep on a 1M-line file. What does this low IPC suggest about where time is being spent?**

> Your answer here...

---

**Q8: After applying your optimisation, the median drops from 210 ms to 195 ms (7% improvement). Is this a meaningful result worth keeping? What would make you confident the improvement is real rather than noise?**

> Your answer here...

---
