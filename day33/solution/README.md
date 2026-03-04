# Day 33 Solution Workspace

## Build and run

From this directory:

```bash
make test
make asan
make valgrind
make clean
```

## Answers

1. What is the main advantage of a table-driven FSM over a switch-based one?  
   *Hint: think scalability, readability, and transition coverage visibility.*  
   > TODO: write your answer here.

2. How do you map an enum State and enum Event to a 2D array index?  
   *Hint: enum integer values directly index transitions[state][event].*  
   > TODO: write your answer here.

3. What should the FSM do if the table entry for [current_state][event] is empty/NULL?  
   *Hint: reject safely and keep current state unchanged.*  
   > TODO: write your answer here.

4. Why are FSMs heavily used in embedded systems instead of blocking threads?  
   *Hint: deterministic event handling and non-blocking control flow.*  
   > TODO: write your answer here.

5. What is the purpose of the action callback in a transition table?  
   *Hint: separate side effects from transition logic.*  
   > TODO: write your answer here.

6. Why should event/state values be bounds-checked before table indexing?  
   *Hint: prevent undefined behavior from out-of-range access.*  
   > TODO: write your answer here.

7. Why is explicit handling of invalid transitions important in production code?  
   *Hint: unexpected inputs occur and must not corrupt FSM state.*  
   > TODO: write your answer here.

8. What type of bugs appear when transition rules are scattered across many `if` branches?  
   *Hint: missing branches, duplicated logic, and inconsistent behavior.*  
   > TODO: write your answer here.
