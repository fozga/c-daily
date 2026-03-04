# Day 27 Notes - Benchmarking C workloads

## 1) Wall-clock vs CPU time

Wall-clock time:
- elapsed real time experienced by user
- includes scheduling delays and I/O waits

CPU time:
- processor time consumed by process
- excludes some waiting periods

For CLI throughput benchmarking, wall-clock is usually primary metric.

Recommended timer:
- `clock_gettime(CLOCK_MONOTONIC, ...)`

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
- `fgets` buffer size
- libc buffering mode (`setvbuf`)
- repeated costly operations per line (`strlen`, allocations, conversions)

Small loop-level improvements can matter at million-line scale.

## 5) Optimization-level impact

- `-O0` is for debugging and clarity, not realistic performance.
- `-O2` is better for production-like benchmarks.

Benchmarking with `-O0` can mislead optimization choices.

## Common mistakes

- comparing runs built with different optimization flags unintentionally
- reporting best-case single run instead of distribution
- changing workload between before/after tests
- optimizing without confirming hotspot location

## C vs C++

- principles are the same: stable methodology and measurable deltas.
- C++ may bring additional abstraction overheads and inlining effects; C tends
  to expose lower-level costs more directly.
