# Day 35 Notes - Callbacks, Event Dispatchers, and Interrupt Flags

## 1) Function pointers and callbacks in C

A **callback** is a function pointer supplied by the caller so that a
framework can invoke it at the right time — without the framework knowing the
concrete function in advance.

General event-callback signature used in this day:

```c
typedef void (*EventHandler)(int event_id, int event_data, void *ctx);
```

- `event_id` — which event fired
- `event_data` — event-specific payload (a counter value, a byte, a status code)
- `ctx` — caller-owned opaque pointer

Because C has no closures, `void *ctx` is the idiomatic way to bind state to a
callback.  The dispatcher stores it; the callback casts it back to the
concrete type.

```c
/* Example: callback that counts how many times EVT_TICK fires */
typedef struct { int ticks; } TickCounter;

static void on_tick(int id, int data, void *ctx) {
    (void)id; (void)data;
    TickCounter *tc = ctx;
    tc->ticks++;
}

/* Registration: */
TickCounter tc = {0};
dispatch_register(&disp, EVT_TICK, on_tick, &tc);
```

## 2) Event dispatcher pattern (Observer in C)

The dispatcher maintains a fixed-size registry of `(event_id, handler, ctx)`
slots.  When `dispatch_fire_event` is called, it iterates the registry and
invokes every handler whose registered `event_id` matches.

```c
#define MAX_HANDLERS 16

typedef struct {
    int          event_id;
    EventHandler handler;
    void        *ctx;
    bool         active;
} HandlerSlot;

typedef struct {
    HandlerSlot slots[MAX_HANDLERS];
    int         count;
} Dispatcher;

int dispatch_register(Dispatcher *d, int event_id,
                      EventHandler handler, void *ctx) {
    if (d->count >= MAX_HANDLERS) return -1;   /* registry full */
    d->slots[d->count++] = (HandlerSlot){
        .event_id = event_id,
        .handler  = handler,
        .ctx      = ctx,
        .active   = true,
    };
    return 0;
}

void dispatch_fire_event(Dispatcher *d, int event_id, int event_data) {
    for (int i = 0; i < d->count; i++) {
        HandlerSlot *s = &d->slots[i];
        if (s->active && s->event_id == event_id)
            s->handler(event_id, event_data, s->ctx);
    }
}
```

### Example: wiring up the exit callback

```c
#include <signal.h>

static volatile sig_atomic_t g_exit_requested = 0;

static void on_shutdown(int id, int data, void *ctx) {
    (void)id; (void)data; (void)ctx;
    g_exit_requested = 1;
}

int main(void) {
    Dispatcher disp = {0};
    dispatch_register(&disp, EVT_SHUTDOWN, on_shutdown, NULL);

    while (!g_exit_requested) {
        /* poll hardware, process events, etc. */
        dispatch_fire_event(&disp, EVT_TICK, get_tick_count());
        /* ... */
    }
    return 0;
}
```

## 3) ISR context and main loop cooperation

In embedded systems, Interrupt Service Routines (ISRs) preempt the main loop
at any instruction.  The ISR must execute quickly and safely:

```
ISR fires → sets flag → returns
Main loop → polls flag → processes deferred work
```

This is called **deferred processing** or a **bottom-half handler**.  The ISR
(top half) does the minimum safe work; the main loop (bottom half) does the
rest.

Keep ISR code to an absolute minimum:

```c
/* DO:   minimal, fast */
static void uart_isr(void) {
    rb_push(&uart_rx_buf, UART->DR);   /* one ring-buffer push */
}

/* DON'T: heavy work inside ISR */
static void uart_isr_bad(void) {
    process_full_packet();             /* may block, allocate, or re-enable IRQ */
}
```

## 4) `volatile` and `sig_atomic_t`

### Why `volatile` is required

The compiler may determine that a loop variable never changes within the loop
body and hoist the read outside the loop — or eliminate it entirely.  If an
ISR or signal handler modifies the variable, the main loop never observes the
change.

```c
/* Without volatile: compiler may optimise to infinite loop */
int running = 1;
while (running) { /* loop body that doesn't write running */ }

/* With volatile: each iteration re-reads from memory */
volatile int running = 1;
while (running) { /* now sees ISR writes */ }
```

### Why `sig_atomic_t` matters

`volatile` prevents caching but does not guarantee that the read or write is
atomic at the hardware level.  On some architectures, writing a multi-byte
integer may require multiple bus cycles.  If an ISR fires between those cycles,
it may read a half-written value.

`sig_atomic_t` (from `<signal.h>`) is guaranteed by the C standard to be
readable and writable atomically in signal/interrupt contexts.

### Correct declaration

```c
static volatile sig_atomic_t g_exit_requested = 0;
```

Both qualifiers work together: `volatile` forces the read, `sig_atomic_t`
guarantees it is safe to read in an interrupt context.

### Relationship to C11 atomics

For full multi-threaded code, prefer `_Atomic` from `<stdatomic.h>` over
`volatile sig_atomic_t`.  The latter is designed for POSIX signal handlers;
the former is designed for multi-core thread safety with explicit memory
ordering.  They solve related but distinct problems.

## 5) Dispatcher safety properties

**Registry overflow** — `dispatch_register` must check `count < MAX_HANDLERS`
before writing.  Exceeding the fixed array is undefined behaviour.

**NULL handler** — `dispatch_fire_event` must guard: `if (s->handler) ...`.
A NULL function pointer dereference is undefined behaviour.

**Event ID mismatch** — always compare `s->event_id == event_id` before
calling.  Firing a handler for the wrong event corrupts application state.

**Modifying registry while iterating** — if a callback calls
`dispatch_register` on the same dispatcher, the slot array may grow (if using
a dynamic variant) or the iteration may process newly added slots.  Document
whether re-entrancy is supported.

## Common mistakes

- Forgetting `volatile` on the exit flag — the compiler eliminates the check.
- Using `bool` or plain `int` (without `sig_atomic_t`) for an ISR-set flag —
  may be non-atomic on some architectures.
- Calling `printf`, `malloc`, or any non-async-signal-safe function inside an
  ISR-like callback — these functions are not reentrant and may deadlock.
- Not checking the callback pointer for NULL before invoking it.
- Exceeding `MAX_HANDLERS` without a bounds check — silent array overrun.
- Assuming event IDs match without an explicit comparison — fires wrong handler.

## C vs C++ callout

| Feature | C | C++ |
|---|---|---|
| Callback | Function pointer + `void* ctx` | `std::function<void(int,int,void*)>`, lambda capture |
| Exit flag | `volatile sig_atomic_t` | `std::atomic<bool>` (preferred in threads) |
| Registry | Fixed array of structs | `std::vector<std::function<...>>` |
| ISR safety | Same strict rules apply | Same; `std::function` itself is **not** signal-safe |
| Observer pattern | Manual dispatcher table | `sigslot`, Qt signals/slots, or custom |

C's explicit function pointer + `void* ctx` pattern forces you to understand
precisely what state each callback captures and how it is passed.  C++ lambdas
with captures are more convenient but obscure the same lifetime and ownership
questions — understanding the C model first makes C++ usage safer.
