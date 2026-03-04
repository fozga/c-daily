# Day 33 Notes - Finite State Machines

## 1) Why use an FSM?

A finite state machine models reactive behaviour as:

- a **finite set of states** (what the system currently is)
- a **finite set of events** (what can happen)
- a **transition function**: `(current_state, event) → next_state + action`

Compared to ad-hoc nested `if/else` or `switch` chains:

- all valid transitions are enumerated and visible in one place
- invalid transitions are *detected* rather than silently ignored
- adding a new state or event means adding one row/column, not hunting through
  branching code

TCP connection management, UI navigation, parser tokenisers, and embedded
device controllers all use FSM structure because their correctness depends on
being in a *known* state.

## 2) Switch-based vs table-driven FSM

### Switch-based

```c
switch (state) {
    case CLOSED:
        if (event == CMD_LISTEN) { state = LISTEN; on_listen(); }
        break;
    case LISTEN:
        if (event == RCV_SYN)  { state = SYN_RCVD; on_syn(); }
        break;
    /* ... */
}
```

Problems at scale:

- every new state adds another `case` block
- coverage of all `(state, event)` pairs is hard to audit visually
- action logic and transition logic become interleaved

### Table-driven

All transitions are encoded as **data**; the dispatch engine is a tiny, generic
function that never changes as the state machine grows.

```
transitions[NUM_STATES][NUM_EVENTS]  — 2D array of Transition structs
```

Adding a new state = adding one row.  Auditing coverage = scanning the table.

## 3) Transition table design in C

### Example: TCP-like FSM implementation

```c
#include <stdbool.h>
#include <stddef.h>

typedef enum { CLOSED, LISTEN, SYN_RCVD, ESTABLISHED, NUM_STATES } State;
typedef enum { CMD_LISTEN, RCV_SYN, RCV_ACK, CMD_CLOSE, NUM_EVENTS } Event;

typedef struct Fsm Fsm;
typedef void (*ActionFn)(Fsm *fsm);

typedef struct {
    State    next_state;
    ActionFn action;      /* NULL means no side effect */
    bool     valid;       /* false = illegal transition */
} Transition;

struct Fsm {
    State current;
    void *user_ctx;       /* caller-owned state for action callbacks */
};

/* --- Static transition table --- */
static const Transition transitions[NUM_STATES][NUM_EVENTS] = {
/*              CMD_LISTEN              RCV_SYN                 RCV_ACK              CMD_CLOSE         */
/* CLOSED    */ { {LISTEN,   on_listen,  true},  {0,0,false},           {0,0,false},         {0,0,false} },
/* LISTEN    */ { {0,0,false},           {SYN_RCVD, on_syn, true},      {0,0,false},         {CLOSED, on_close, true} },
/* SYN_RCVD  */ { {0,0,false},           {0,0,false},           {ESTABLISHED,on_ack,true},   {CLOSED, on_close, true} },
/* ESTABLISHED*/{ {0,0,false},           {0,0,false},           {0,0,false},          {CLOSED, on_close, true} },
};

bool fsm_dispatch(Fsm *fsm, Event event) {
    /* Bounds-check both dimensions before indexing */
    if ((unsigned)fsm->current >= NUM_STATES ||
        (unsigned)event         >= NUM_EVENTS)
        return false;

    const Transition *t = &transitions[fsm->current][event];
    if (!t->valid) return false;      /* reject illegal transition */

    fsm->current = t->next_state;     /* update state BEFORE calling action */
    if (t->action) t->action(fsm);    /* optional side effect */
    return true;
}
```

Key design decisions visible in this code:

1. State is updated *before* the action callback fires — the callback sees the
   new state, which is the more common requirement.
2. `action` is a nullable pointer — not every transition needs a side effect.
3. Bounds checking happens at the top of `fsm_dispatch`, not scattered through
   the table entries.

## 4) Handling invalid transitions safely

Invalid events happen in real systems: a retransmitted packet, a user double-
clicking, noise on a serial line.  A robust FSM must survive them.

Recommended behaviour:

- return a failure code (`false`)
- leave `fsm->current` unchanged
- optionally log a diagnostic

**Never** index arrays with unchecked enum values.  An out-of-range event
passed to `transitions[state][event]` is undefined behaviour if `event >=
NUM_EVENTS`.

## 5) Action callbacks

Callbacks decouple *what happens* from *when it happens*:

- `fsm_dispatch` is generic and knows nothing about application logic
- action functions (`on_listen`, `on_syn`, etc.) know the application but
  nothing about dispatch mechanics
- `fsm->user_ctx` allows action callbacks to reach caller-owned state without
  global variables

This is the same inversion-of-control principle that makes event-driven
frameworks composable.

## 6) Stretch: logging macro

```c
#define FSM_LOG(fsm, event, next)                                      \
    fprintf(stderr, "[FSM] state=%d + event=%d -> state=%d\n",        \
            (fsm)->current, (event), (next))
```

Insert before the state assignment inside `fsm_dispatch`.  This produces a
human-readable audit trail without touching action callback code.

## Common mistakes

- Not checking `(unsigned)event >= NUM_EVENTS` before table indexing —
  triggers undefined behaviour with malformed input.
- Forgetting to define behaviour for every `(state, event)` pair — undefined
  entries default to zero/NULL, which may accidentally look like a valid
  transition to `state 0`.
- Updating state *after* the action callback — the callback then acts on the
  old state, which is usually wrong and hard to debug.
- Assuming the action callback is always non-NULL; always NULL-check before
  calling.
- Mixing side effects directly into `fsm_dispatch` instead of delegating to
  callbacks — destroys the generality of the engine.

## C vs C++ callout

| Approach | C | C++ |
|---|---|---|
| State representation | `enum` + `int` (zero-overhead) | `enum class` or `std::variant` |
| Transition table | `const Transition[N][M]` static array | Same, or `std::map` / `std::unordered_map` |
| Action callbacks | Function pointers + `void* ctx` | `std::function` with captures, or virtual methods |
| Invalid state | Return `false`, caller checks | Can throw `std::logic_error` |

Table-driven FSMs in C are excellent in embedded firmware: zero heap
allocation, predictable data-cache footprint, and the table is visible as a
readable `.rodata` section.  C++ abstractions are more ergonomic but carry
overhead that can matter in constrained environments.
