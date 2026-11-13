# MSVC6 register allocation

Register and stack assignments depend on live ranges, uses, calls and the full
translation unit. A source experiment measures that context, not a general rule.
Expression-level differences belong in [C shapes](msvc6-c-shapes.md).

## Read the native value flow

For ordinary x86 C conventions, EAX, ECX and EDX are caller-saved; EBX, ESI, EDI
and EBP are callee-saved. Check unusual helpers rather than assuming their ABI.

Trace a value from its definition through every reaching path. Record partial
register writes, calls, spills, reloads and the exact consumer width. A register
name alone does not establish which source variable it holds.

## What affects allocation

- A constant used across several operations may become a register candidate.
  A single-use constant may remain immediate.
- Keeping an index live can preserve a native induction form. Returning the
  equivalent pointer may make the index dead and change the whole loop.
- Loop exits and shared return blocks can change save/restore placement.
- Address-taking, aliasing, declarations and definition order can change spills.
- Equal access counts do not establish a unique stack-slot assignment.

Declaration reordering, renaming, `register` and `volatile` are not reliable
controls for a desired register. `volatile` also changes observable accesses;
use it only with evidence for those accesses, not to improve a score.

## Stack slots

Track entry ESP and every push, pop, stack adjustment and callee cleanup.
Resolve each displacement at that instruction. Compilers can reuse dead parameter
or saved-register slots; reserved frame bytes do not prove a local array or struct.
A diagnostic sentinel can identify a slot, but must not become production state.

Compare complete objects after a type or context change. Keep rejected variants
bounded and consult [negative results](codegen-walls.md) before repeating them.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
