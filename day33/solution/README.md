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

**Q1: Compare a switch-based FSM and a table-driven FSM for a machine with 10 states and 8 events. How many explicit `case` clauses does the switch version need vs. how many table entries? Which is easier to audit for missing transitions?**  

> Your answer here...

---

**Q2: In `fsm_dispatch`, should the state be updated before or after the action callback is invoked? Justify your answer by describing a concrete bug that occurs if you choose the wrong order.**  

> Your answer here...

---

**Q3: What undefined behaviour is triggered if `event` is not bounds-checked before indexing `transitions[state][event]`, and why can a compiler exploit it?**  

> Your answer here...

---

**Q4: A `Transition` struct has `action` as a `NULL` function pointer and `valid = true`. Is this a valid transition? What should `fsm_dispatch` do with it?**  

> Your answer here...

---

**Q5: Explain how `fsm->user_ctx` allows multiple FSM instances to share the same action callbacks without using global variables. Give an example use case.**  

> Your answer here...

---

**Q6: Why are FSMs preferred over blocking threads in deeply embedded systems? Name two resource constraints that make the FSM approach attractive.**  

> Your answer here...

---

**Q7: Uninitialized `Transition` structs in C zero-initialize to `{next_state=0, action=NULL, valid=false}` when declared `static`. Why is relying on this zero-init dangerous for invalid entries in the transition table?**  

> Your answer here...

---

**Q8: Sketch the state-transition diagram for the four-state TCP-like machine (CLOSED, LISTEN, SYN_RCVD, ESTABLISHED) and identify which `(state, event)` pair represents the longest valid sequence to reach ESTABLISHED. How many `fsm_dispatch` calls does it take?**  

> Your answer here...

---
