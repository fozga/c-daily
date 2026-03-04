# Day 35 Solution Workspace

## Build and run

From this directory:

```bash
make test
make asan
make valgrind
make clean
```

## Answers

1. Why do C callback APIs almost always include a `void* ctx` or `void* userdata` parameter?  
   *Hint: C lacks captured lambdas; context pointer carries caller state.*  
   > TODO: write your answer here.

2. What happens if a while-loop checks a global boolean flag that is NOT marked volatile, but is changed by an interrupt?  
   *Hint: compiler may optimize repeated reads and miss external updates.*  
   > TODO: write your answer here.

3. What specific guarantee does `sig_atomic_t` provide?  
   *Hint: think atomic read/write behavior for signal-safe scalar access.*  
   > TODO: write your answer here.

4. What is the Observer pattern and how does the dispatcher implement it?  
   *Hint: publisher notifies registered subscribers without direct coupling.*  
   > TODO: write your answer here.

5. Why can't you safely call `printf` or `malloc` inside a real hardware ISR?  
   *Hint: ISR context has strict timing and async-signal-safety constraints.*  
   > TODO: write your answer here.

6. Why should dispatcher registration guard against exceeding maximum slots?  
   *Hint: fixed arrays need bounds protection to avoid memory corruption.*  
   > TODO: write your answer here.

7. What bug appears if dispatcher invokes callbacks without checking event ID match?  
   *Hint: unrelated handlers may execute and corrupt application state.*  
   > TODO: write your answer here.

8. Why is synchronous event dispatch often enough in small embedded loops?  
   *Hint: deterministic order and low overhead can simplify design.*  
   > TODO: write your answer here.
