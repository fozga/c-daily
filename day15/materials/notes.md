# Day 15 Notes - GDB workflow for C bugs

## 1) GDB basics

### Compile for debugging

Build with debug symbols:
- `-g` to include symbol and line information
- `-O0` to reduce optimization-induced surprises while learning

Debugging optimized binaries (`-O2` or `-O3`) is possible, but variables may be
optimized out and control flow can be harder to follow.

### Start GDB

- `gdb ./test_runner`

Then run program:
- `run`

Core execution controls:
- `continue` (`c`) - continue until next breakpoint or crash
- `step` (`s`) - step into function calls
- `next` (`n`) - execute current line without entering called functions

### Breakpoints

Set breakpoint by function:
- `break list_reverse`

Set breakpoint by file/line:
- `break broken_pointers.c:42`

Conditional breakpoint:
- `break list_reverse if head_ref == 0`

## 2) Post-mortem analysis after Segmentation Fault

When your program crashes with `SIGSEGV`, GDB pauses at the faulting
instruction and lets you inspect call state.

Most useful first command:
- `bt`

Extended stack detail:
- `bt full`

`bt full` includes local variable values in each visible frame, which often
reveals invalid pointers and missing edge-case checks quickly.

## 3) Navigating stack frames

Every function call creates a stack frame.

Frame navigation commands:
- `up` - move to caller frame
- `down` - move to callee frame
- `frame N` - jump to specific frame number

Important rule: local variables are frame-specific. If you are in the wrong
frame, the variable you want may appear unavailable or misleading.

## 4) Inspecting state in GDB

Single expression:
- `print var`
- `p ptr`
- `p *ptr`
- `p ptr->field`

Continuous display after each stop:
- `display var`
- `undisplay N`

Inspect memory:
- `x/16xb ptr` (show 16 bytes in hex)

For pointer bugs, always check:
- whether pointer is NULL
- whether pointer points to valid object lifetime
- whether list links are consistent (`curr`, `next`, `prev`)

## 5) Watchpoints

Watchpoints stop execution when memory changes or is read.

Commands:
- `watch expr`  : break when expression value changes (write watchpoint)
- `rwatch expr` : break on read access
- `awatch expr` : break on read or write access

Use watchpoints when:
- a variable gets corrupted "somewhere earlier"
- a pointer unexpectedly changes value
- count/length fields drift from actual structure state

Hardware watchpoints are usually precise but limited in number by CPU support.

## 6) Example GDB session

Suppose `broken_pointers.c` crashes inside `list_reverse`. Here is a realistic
debugging session from start to root cause.

### Triggering the crash

```
$ gdb ./test_runner
(gdb) run
Starting program: /home/user/day15/test_runner

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555279 in list_reverse (head_ref=0x555555559260)
    at broken_pointers.c:34
34              curr->next = prev;
```

### Reading the backtrace

```
(gdb) bt
#0  0x0000555555555279 in list_reverse (head_ref=0x555555559260)
    at broken_pointers.c:34
#1  0x0000555555555430 in test_list_reverse () at test_runner.c:97
#2  0x0000555555555510 in main () at test_runner.c:148
```

Frame `#0` is the deepest call (crash site). Frame `#1` is the direct caller.
`main` is frame `#2`.

### Inspecting the crash frame

```
(gdb) frame 0
(gdb) print curr
$1 = (node_t *) 0x0
(gdb) print prev
$2 = (node_t *) 0x555555559260
```

`curr` is `NULL`, yet line 34 attempts `curr->next = prev`.
Dereferencing a null pointer is undefined behavior (UB); the OS raises SIGSEGV.

### Moving to the caller to find the root cause

```
(gdb) frame 1
(gdb) print head
$3 = (node_t *) 0x0
```

The test passed an empty list (`head == NULL`). The root cause is a missing
guard: `list_reverse` must return immediately when the list is empty or has a
single node.

This illustrates the key principle: **the crash site is the symptom; the root
cause is usually visible one or more frames higher in the backtrace.**

## Common mistakes

- Debugging an optimized build first (`-O2`) and assuming missing variables are
  logic bugs instead of optimization artifacts.
- Looking only at the top frame and ignoring callers in `bt`.
- Forgetting to inspect pointer values before dereferencing in GDB.
- Using `next` when you should use `step`, then missing function internals.
- Assuming crash line is always the true root cause (it may be earlier memory
  corruption).

## C vs C++ notes

- C stack traces show raw C symbol names directly.
- C++ often shows mangled names unless demangled.
- C++ debugging may involve templates and overload resolution complexity.
- C pointer bugs are often simpler syntactically but severe in runtime impact.
