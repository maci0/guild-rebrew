# MSVC6 C shapes

Use native instructions to choose a source hypothesis, then compare the complete
compiled function with canonical whole-TU flags. These patterns depend on compiler context.
[Measurement](measure-traps.md) defines the proof limits;
[register allocation](msvc6-allocator.md) covers registers and stack slots.

## Diagnose before rewriting

| Difference | Check first |
| --- | --- |
| Wrong addressing scale | Declared element type, byte offset versus element index, native stride |
| Load versus address calculation | Pointer object versus array/object address |
| Wrong byte/word extension | Access width and each consumer's signedness |
| Extra or missing call/store | Native CFG and reaching definitions, including failure paths |
| Different jump | Signedness, flags and unordered FP behavior |
| Shifted frame/arguments | Saved registers, pending pushes and reused argument slots |
| Different x87 operation | Operand order, stack depth, store/reload rounding and helper contract |
| Different switch | Raw index/jump tables, guard bias and default target |
| Different epilogue | Actual return sites, loop exits and cleanup paths |
| Register-only difference | Live ranges and original TU context before expression variations |

A declaration change can alter addressing, aliasing, induction or register liveness.
A change that preserves bytes at one call site may change them elsewhere.
Likewise, algebraic equality does not establish equivalence under signed overflow,
FP rounding or observable reloads.

## Common traps

- An uninitialized C local may indicate missing recovery or native indeterminate
  data. Trace every producer before adding an initializer.
- A `float` memory operand does not prove that an x87 intermediate was rounded to
  float. A store/reload boundary is separate evidence.
- `__ftol` can serve both narrow and wide source conversions. Its qword temporary
  and EDX:EAX output do not prove the caller's declared return type.
- Unused declarations and definition order can affect code generation. Preserve
  the original TU context during probes.
- A `return` inside a loop can trigger epilogue merging. Check return placement
  before treating shared epilogues as a compiler limit. In the
  [November 5 archive](goal-history.md#full-notebooks), read `docs/codegen-walls.md`
  section 2 together with its correction in `docs/msvc6-c-shapes.md` section 200.
- Keep logging literals, argument order and even native API-format mismatches
  faithful. Correcting the game is a different task from reconstructing it.

Check [negative results](codegen-walls.md) before reopening an exhausted probe family.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
