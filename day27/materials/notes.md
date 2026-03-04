# Day 27 Notes - Benchmarking C workloads

## 1) Wall-clock vs CPU time

Wall-clock time:
- elapsed real time experienced by user
- includes scheduling delays and I/O waits

CPU time:
- processor time consumed by the process
- excludes waiting periods (I/O, sleep)

For mini-grep throughput on a 1M-line file, wall-clock is the primary metric
because the user experiences end-to-end latency.

**Recommended timer — `CLOCK_MONOTONIC`:**

### Example

```c
#include <time.h>

static double elapsed_ms(struct timespec a, struct timespec b) {
    return (b.tv_sec  - a.tv_sec)  * 1000.0
         + (b.tv_nsec - a.tv_nsec) / 1e6;
}

struct timespec t0, t1;
clock_gettime(CLOCK_MONOTONIC, &t0);
scanner_run(fp, ...);
clock_gettime(CLOCK_MONOTONIC, &t1);
printf("%.2f ms\n", elapsed_ms(t0, t1));
```

`CLOCK_MONOTONIC` never jumps backward (unlike `gettimeofday` which is
affected by NTP adjustments), making it reliable for intervals.

## 2) Benchmark methodology

Good process:
- warm-up run first
- collect multiple samples
- report median, not a single run
- keep environment stable (CPU load, thermal state, background jobs)

Why median:
- robust to outliers/spikes from scheduler noise

## 3) Micro-benchmark pitfalls

- dead-code elimination (compiler removes unused work)
- timing overhead larger than tested work
- measuring setup cost rather than hot loop
- unrealistic input patterns

Always ensure benchmark result depends on computed output.

## 4) I/O bottlenecks in C

For line scanning tools, I/O can dominate runtime.

Potential factors:
- `fgets` buffer size (4 KB vs 64 KB can make a measurable difference)
- libc buffering mode (`setvbuf`) — default is fully buffered for files
- repeated costly operations per line (`strlen`, allocations, conversions)
- OS page cache warmth (first run reads from disk; subsequent runs from cache)

**Useful profiling tools:**

```bash
# Shell timing — simplest approach
time ./mini-grep "pattern" bigfile.txt > /dev/null

# perf stat — hardware counters (Linux only)
perf stat ./mini-grep "pattern" bigfile.txt > /dev/null

# perf record + report — call-graph hotspot finding
perf record -g ./mini-grep "pattern" bigfile.txt > /dev/null
perf report

# Valgrind callgrind — instruction-level profiling (slower)
valgrind --tool=callgrind ./mini-grep "pattern" bigfile.txt > /dev/null
callgrind_annotate callgrind.out.*
```

Small loop-level improvements (avoiding redundant `strlen`, increasing buffer
size) can yield 10–30% gains at million-line scale.

## 5) Optimization-level impact

- `-O0` is for debugging and clarity, not realistic performance.
- `-O2` is standard for production-like benchmarks and is what mini-grep
  should be built with for Day 27 timing.
- `-O3` adds aggressive loop transformations; valid but can be harder to
  profile because inlining obscures call sites.

Benchmarking with `-O0` can lead to optimising code paths the compiler would
have eliminated entirely at `-O2`.

## Common mistakes

- Comparing a `-O0` before-run to a `-O2` after-run (flags differ).
- Reporting a single best-case run instead of the median of 5+.
- Changing the workload (fixture file content or size) between before/after.
- Optimising a path that `perf` shows is NOT the hotspot (wasted effort).
- Not warming up — first run may be I/O-bound from disk; only subsequent
  runs hit the page cache and measure CPU performance.
- Redirecting output to terminal (console I/O overhead) vs `/dev/null` —
  always benchmark with `> /dev/null` to isolate compute from display.

## C vs C++

- Benchmarking principles are identical: stable methodology, median of
  multiple runs, identical workload, same compiler flags.
- C++ STL abstractions (streams, `std::regex`) can introduce hidden
  allocation overhead; C tends to expose lower-level costs more directly.
- `perf` and Valgrind callgrind work equally well for C and C++ binaries;
  the annotation output may be more cluttered for heavily-inlined C++ code.
