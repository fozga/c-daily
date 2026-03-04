# Day 27 Solution Workspace

## Build and run

- `make gen` - build fixture generator.
- `make bench` - build benchmark binary (release flags).
- `make run_bench` - generate dataset and run benchmark once.
- `make clean` - remove binaries and generated large fixture.

## Benchmark Results

| Run | Before (ms) | After (ms) | Change |
|-----|-------------|------------|--------|
| 1   | TODO        | TODO       | TODO   |
| 2   | TODO        | TODO       | TODO   |
| 3   | TODO        | TODO       | TODO   |
| 4   | TODO        | TODO       | TODO   |
| 5   | TODO        | TODO       | TODO   |

## Answers

1. Why should benchmarks use `-O2` instead of `-O0`?  
   *Hint: debug builds distort instruction mix and throughput.*  
   > TODO: write your answer here.

2. What is the difference between wall-clock time and CPU time?  
   *Hint: one includes waiting/scheduling effects; the other tracks compute usage.*  
   > TODO: write your answer here.

3. Why should you take the median of multiple runs rather than the minimum?  
   *Hint: robustness against outlier jitter.*  
   > TODO: write your answer here.

4. What does `setvbuf` do and how might it affect I/O performance?  
   *Hint: buffering policy/size changes number of syscalls and flush behavior.*  
   > TODO: write your answer here.

5. Why does the compiler sometimes eliminate code in benchmarks (dead code elimination)?  
   *Hint: computations with unused results may be optimized away.*  
   > TODO: write your answer here.

6. Why keep benchmark input fixed between before/after runs?  
   *Hint: isolate code-change impact from workload variance.*  
   > TODO: write your answer here.

7. Why should you warm up before collecting timing samples?  
   *Hint: cache/state effects and one-time initialization can skew first run.*  
   > TODO: write your answer here.

8. What is a hotspot, and why optimize it first?  
   *Hint: biggest total-time contributor yields largest potential gain.*  
   > TODO: write your answer here.
