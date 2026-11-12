# MSVC6 C shapes

Use native instructions to choose a source hypothesis, then compare the complete
object with canonical whole-TU flags. These are measured patterns, not guarantees
about every compiler context. [Measurement](measure-traps.md) defines the proof
limits; [register allocation](msvc6-allocator.md) covers homes and slots.

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
  before treating shared epilogues as a compiler limit. See the later
  [loop-context controls](codegen-walls.md#archived-techniques).
- Keep logging literals, argument order and even native API-format mismatches
  faithful. Correcting the game is a different task from reconstructing it.

Use [negative results](codegen-walls.md) before reopening an exhausted probe family.
A failed search grants no [assembly exception](assembly-audit.md).

## Archived techniques

Original notebook: `docs/msvc6-c-shapes.md` in the [documentation archive](goal-history.md#full-notebooks).

- MSVC 6.0: C shapes
- Index by symptom
- How to probe a hypothesis
- 1. Global array element type sets the addressing scale (`0x1000d8a0`, `0x100111b0`, `0x100113b0`, `0x100196c0`, `0x10035439`)
- 2. Pointer vs array: `mov` load against `lea` (`0x100181a0`, `0x10019ae0`)
- 3. Uninitialized locals from decompilation (`0x100180d0`, `0x10019a20`)
- 4. Wrong global in a guard (`0x100035c0`, `0x10034610`, `0x10034680`)
- 5. An explicit pointer local defeats the induction-variable rewrite (`0x10014ee0`)
- 6. Local variable width
- 7. Branch polarity: merge sequential returns
- 8. Loop shape: `for(;;)` with early return vs `do/while` with a tail return
- 8a. x87 memory-operand forms: `fimul`/`fidiv` vs `fild` + `fmulp`/`fdivp` (`0x10019720`)
- Pick the weaker lever when the target's schedule is looser
- 8b. A folded `cmp` hides a load the target keeps in a register (`0x10019720`)
- 8c. A volatile read pins load order between two field reads (`0x10019720`)
- 9. Register roles follow order of first use (`0x10010fa0`)
- 9a. Shorten a live range to break an esi/edi tie (`0x10012470`)
- 10. Load scheduling between adjacent field reads
- 11. Inline memset expansion (partial result, no byte match) (`0x100068e0`)
- 12. CFLAGS are per-file in practice, not per-function (`0x10006820`)
- 13. Per-function frame pointer without a CFLAGS header (`0x10006820`, `0x100068e0`)
- 14. Homing a value in the incoming parameter slot (`0x1000691b`, `0x10006924`)
- 15. `_ftol(expr)` pushes a double; a plain `(int)` cast does not (`0x10018850`)
- 16. Compare the call skeleton before chasing instruction diffs (`0x10019228`, `0x100192b3`)
- 17. Out-of-line block placement is not steerable from source (`0x10002770`, `0x100093a0`, `0x10009657`, `0x1000973a`, `0x10009756`)
- 18. Byte-width levers move encodings, not always the score
- 19. `match_count` is positional, so one size delta hides a good match (`0x100093a0`)
- 20. Statement order does not move stores into the same buffer
- 19a. `match_count` is a positional byte compare (same rule as §19)
- 21. Fold the offset into the pointer before the access (`0x10003820`, `0x1000eb70`)
- 21a. Hoisting a field load out of an argument list breaks an esi/edi tie (`0x100198b0`)
- 22. `volatile` on the store target pins a store against loop scheduling (`0x1000c600`)
- 23. A shared clamp value needs a 32-bit temp assigned in both arms (`0x10010140`)
- 24. Two volatile reads pick both the register form and the schedule (`0x1000a340`)
- 25. ecx/edx naming residue is usually a first-read or a hoisted-temp bug (`0x1000b4d0`, `0x1000c710`, `0x1000e7d0`)
- 26. Spelling a clamp as `setle`/`dec`/`and` decides the loads before it (`0x10011790`)
- 27. A volatile byte read defeats the byte/dword load merge on one slot (`0x10018450`)
- 28. Constant CSE in a straight-line store block has no source lever (`0x100170e0`)
- 29. Hoist a common addend out of a select, and let the select assign the result (`0x1000eaa0`)
- 30. `volatile` at the load site defeats displacement folding (`0x100104a0`, `0x10015460`)
- 31. A pointer sweep with a separate index beats an indexed walk (`0x100358a0`, `0x100358a2`, `0x1009aca2`)
- 32. PROVEN is not a byte match, and it hides tractable work
- 33. Statement order decides which register holds a value (`0x1000c710`)
- 34. RELOC can hide a wrong global: check `~~` operands against the symbol (`0x100100a0`, `0x100256a4`, `0x100256cc`)
- 35. Row multiply vs offset accumulation decides strength-reduction fallout (`0x1000b4d0`, `0x10015950`, `0x10035a6c`, `0x1009ae6c`)
- 36. The outer call's argument form can fix a whole-function register swap (`0x100198b0`)
- 37. A dead parameter slot can home more than one byte (`0x1000b290`)
- 38. msvc6 shrink-wraps, and the lever is loop register demand (`0x10016290`, `0x10016f80`)
- 161. SIB base/index roles follow the induction variable's form (`0x10010850`, `0x10015950`)
- 160. PROVEN status is lost by a STUB result, and that is a real regression
- 162. Relocation masking can hide a wrong symbol: the false RELOC (same rule as §34) (`0x100100a0`, `0x10015950`, `0x100256a4`, `0x100256cc`, `0x100311f0`, `0x10031204`)
- 39. A volatile argument read defers a parameter load past the prologue pushes (`0x10010710`, `0x10017c40`)
- 40. A struct assignment breaks a register tie without changing a byte (`0x002641f8`, `0x002641fc`, `0x1000a080`, `0x10012470`, `0x1002d4f0`)
- 41. Two levers that each regress can be exact together (`0x10017c40`)
- 42. The number of reaching definitions decides load/store scheduling (`0x00132154`, `0x002641f8`, `0x002641fc`, `0x00264264`, `0x1000a080`, `0x101deb00`, `0x114ffe20`)
- 43. `and eax,0xff` is one byte shorter than the same mask on any other register
- 44. `#pragma optimize("a", on)` reorders a field read against a store (`0x100155c0`)
- 45. Merging duplicated tail stores sinks a loop store below the decrement
- 46. The x87 `fxch` slot and a folded byte compare are set by one type choice (`0x10019720`, `0x100257d0`)
- 47. A loop's form, not its text, decides where C2 puts its cold exit block (`0x100093a0`)
- 48. msvc6 folds a compared variable into a later store, and no spelling keeps it in the register (`0x100093a0`, `0x10009846`, `0x101deac0`, `0xffffffff`)
- 49. A CFLAGS sweep on one function: inert, negative, and one near miss (`0x10018850`, `0x1001a0f0`)
- 50. The residual codegen classes, as instructions (`0x100097fb`, `0x1000984b`, `0x100098e3`, `0x10009baf`, `0xffffffff`)
- 51. `volatile` on a local is a scheduling barrier; qualify at the use site (`0x10008a90`)
- 52. The 16-bit zero-extend idiom is selected by `volatile`, not by C spelling (`0x10009020`, `0x10011bf0`, `0x10018850`, `0xffffff86`)
- 53. `switch` case bodies are laid out in source order (`0x100174d0`)
- 54. A guard inversion moves which site falls through, and with it the branch histogram (`0x1000d930`, `0x1000e00e`)
- 55. Comparison rewrites must keep the strict/non-strict boundary
- 56. A missing exit epilogue is a `return` that hands back a register (`0x10008a90`)
- 57. Loop shape is a lever only when the divergence is not register pressure (`0x10002770`, `0x1000bdf0`, `0x1000e140`)
- 58. `/Ox` versus `/O2` is per-file and load-bearing (`0x10018850`)
- 59. `if (cond) goto L;` compiles to `if (cond) { body }`; cold handlers are placed by block *creation* order (`0x10002770`, `0x10002db3`, `0x10002de9`, `0x10002e1b`, `0x10002e29`, `0x10002e35`, `0x10002e4d`)
- 60. A volatile store's position is a dependency fixed point, not a statement-order choice (`0x1000e140`, `0x101de450`)
- 61a. The aliasing lever is a wall when the function has more than the one transposition (round 1020) (`0x1000e140`, `0x1000e20c`)
- 61. A shared guard the reference falls into cannot be reached by fall-through from C (`0x1000aac0`)
- 62. A literal shared by several comparisons is not a lever for register residence (`0x1000ec00`, `0x1000edc0`, `0x100358a0`, `0x10035ab0`)
- 63. A clamp's winning arm order is per-site, not per-function (`0x1000ec00`)
- 64. `for (;;) { if (x) break; ... }` is normalised to the `do/while` form (`0x1000ec00`)
- 65. an if/else-if chain and a real `switch` emit their jump tables in OPPOSITE order (`0x10002770`, `0x10002a43`, `0x10002e9c`, `0x10002f1c`, `0x100128f0`, `0xc0000025`, `0xc000008f`)
- 66. a dead store in the source appears as a store in the reference: comparing stores is a dead-code oracle (`0x10002770`, `0x100029f7`, `0x10002a02`, `0xc000008e`)
- 67. msvc6 does not reorder calls, so call order in the source is recoverable from the reference (`0x10002770`, `0x100028fb`, `0x10002901`, `0x10002923`, `0x1000294c`, `0x10024028`, `0x1002402c`)
- 68. a redundant null test after a search loop is NOT eliminated, and its width matters (`0x100174d0`)
- 69. an `__asm` block is a scheduling barrier, and this project's C-only constraint forbids using it as one (`0x100174d0`)
- 70. operand order in a commutative address expression is inert; only the *nesting* steers (`0x100128f0`)
- 71. `memset(p, 0, N)` is an intrinsic that is not value-tracked, so it beats `p[0]=0; p[0]\|=1` (`0x100128f0`)
- 72. a callee-saved sentinel and a CSE can be one mechanism, not two (`0x100128f0`, `0xffffffff`)
- 72b. a locally exact nesting fix can still lose to the cascade it triggers (`0xffffffff`)
- 73. `base + idx*0x40 + idx` always folds to one `[reg+reg]` operand (`0x100174d0`)
- 74. Superseded claim: msvc6 folds byte-identical early-return epilogues unconditionally; the reference folds none (`0x10016f80`, `0x100170d2`)
- 75. A prologue-fidelity lever, and a past "climb win" that cost it (`0x10016f80`)
- 76. A `volatile` read at a *post*-loop test blocks the loop's entry-guard fold (`0x10008a90`, `0x10008b0f`, `0x10008c51`, `0x10008c59`)
- 77. Group same-kind memory operations to match the reference's store sequence (`0x1000d930`, `0x1000ddc8`, `0x1000de10`, `0x100128f0`, `0x10018850`)
- 78. A one-token guard reorder can be worth one linked byte (`0x10006580`, `0x1000d930`, `0x10018850`)
- 79. Position beats alignment, repeatedly
- 80. xor-xor RMW beats xor-then-or when the scheduler prefers it (`0x10009020`)
- 81. CrashDump frame rule: every 0x280 path costs ~50 bytes (`0x10002770`, `0x1000277d`, `0x1000277e`, `0x1000281d`, `0x1000282c`, `0x1000282d`, `0x10002931`, `0x10002c5c`, `0x10002c87`, `0x10002cb8`, `0x10002cc8`, `0x10002ccd`, `0x10002d5d`, `0x10002dac`, `0x10002dad`, `0x10002e6b`, `0x10002e6e`)
- 82. `fimul` needs an int memory home AND a live ST(0), supplied by two separate constructs (`0x10018850`, `0x10018f4c`)
- 83. A measurement pipeline must refuse stale inputs, or it will report the last good number
- 84. Sink a value's definition into the guard that uses it, and let the other region keep its own register (`0x1000de10`, `0x1000df0a`)
- 85. The boundary of section 84: it moves a value's definition, not a constant (`0x1000ec00`, `0x1000edc0`, `0x10011bf0`, `0x100128f0`)
- 86. A join block is exiled when its fall-through predecessor must end in a reload + `jmp` (`0x100092bc`, `0x1000d930`, `0x1000df2a`, `0x1000df97`, `0x1000dfc1`, `0x100174d0`, `0x10017530`, `0x10018c23`, `0x10018c28`)
- 86b. Store order IS a lever through a fresh pointer, inert through a stack buffer (`0x10006580`, `0x100066bc`, `0x100066cb`, `0x1001904d`, `0x10019052`, `0x10019056`, `0x1001905c`, `0x1001906e`)
- 87. Audit a function's own header notes before trusting them: six for six (`0x1000dd2a`, `0x1000dd33`, `0x100189c4`, `0x100189f4`)
- 88. A "span deficit" is code bytes plus alignment round-up: separate them before hunting (`0x10006580`, `0x100067d8`, `0x100067da`, `0x100067dd`, `0x100067df`, `0x100067e1`, `0x100067e4`)
- 89. Attribute residue by COMDAT extent, not body size: msvc6 emits tables past the body (`0x10009020`, `0x10009056`, `0x100092ba`, `0x100092bb`, `0x100092bc`, `0x100092cf`, `0x100092d0`, `0x100092dc`, `0x100092dd`, `0x100092df`)
- 90. Some "compiler fixed points" are service-pack decisions: sp5-pp as an oracle
- 91. The sp5-pp oracle, applied to the whole residue table: 14 source-bound, 4 scheduler-bound (`0x1000bee6`, `0x1000c01e`, `0x10012b9f`, `0x10012bc4`, `0x100170bb`)
- 92. Three closures, and the codegen facts they establish
- The image sweep is nine IMAGES but only three GENERATORS
- `cm_ProcessCommandQueue`: tail-sharing, not arm order, and a greedy layout pass
- `gm_ObjectsAvailble`: a downstream reschedule can be a rename's shadow (`0x100160d3`)
- `ahm_ExAllocAlchemist`: `faddp` is unreachable from any C expression (`0x1000c034`)
- 93. PROVEN is not a byte match, and the headline number hid that
- The 117 lint warnings were all rebrew's own false positives (round 193) (`0x1000d92d`, `0x1000d930`, `0x10012440`)
- 94. `volatile` wins the alignment ruler and loses the link: three for three
- 95. A jcc width difference is a readout of stub distance, never a source lever (`0x10016f80`)
- 96. Four rulers, one object: always state which convention a number used
- 97. Spec audit: every live `__asm` block is inside the "original used asm" carve-out (`0x10006580`, `0x100068e0`, `0x10006d20`, `0x10008e40`, `0x10008f0c`, `0x1000b040`, `0x100174d0`)
- 98. "Byte-identical outside `.text`" means *copied* outside `.text` (`0x0174059c`, `0x10024040`, `0x404015ff`)
- 99. The measuring script and the shipping pipeline had drifted apart (`0x10139820`, `0x117f65b4`)
- 100. `.data` is placement-bound: MSVC6 puts every string literal in its own COMDAT (`0x10027448`)
- 101. `.data` placement was dominated by the link-order of the length pad, not by COMDATs (`0x10027030`, `0x10028940`, `0x1002e4d0`, `0x10030268`)
- 102. Fold priority only needs to beat the first *member* COMDAT, not the whole link
- 103. `.rdata`'s whole residue is the import table, and the symbol order is already correct (`0x00025000`, `0x00026000`, `0x00026acc`, `0x00026bb2`, `0x00029000`, `0x0002c000`, `0x00031000`, `0x00033000`, `0x00034000`)
- 104. Inlining is not the residue: call counts already match (`0x10003640`, `0x1000bd50`, `0x1000c600`, `0x100122e0`, `0x10018130`, `0x10018150`, `0x10024008`)
- The related question: does emitting missing `.data` content help `.text`?
- 105. The GA flag sweep, finally run, and why it says nothing new
- 106. The flag landscape is flat on every walled row: five for five
- 107. The GA finds nothing either, and stagnates immediately
- 108. `near-diag`'s verdict is a different ruler: reconcile it before believing it
- 109. `gm_AllocSpieler`'s first fault is a scheduler sink, not a statement order (`0x10018850`, `0x10018918`, `0x100358a0`, `0x100358fc`)
- Round 216: the `lea` split is not source-reachable either (`0x1001896f`, `0x100358fc`)
- 110. A deliberate semantic bug is shipped in `gm_AllocSpieler`: state it plainly (`0x10018cd4`, `0x10018cdb`, `0x10018cde`, `0x10018ce0`, `0x10018ce1`, `0x10018ce9`, `0x10018cec`, `0x1003542c`)
- Round 214 correction: the size match is an accident of the bug
- Round 215: half the deficit was the argument cast, not the store (`0x10018cd4`, `0x10035434`)
- 111. Count calls by ENCODING, not by grep, and what it shows on `CrashDumpUnhandledExceptionFilter` (`0x10002770`, `0x10024010`, `0x10024024`, `0x10024038`, `0x100272f8`)
- 112. The reference does not cross-jump identical cleanup arms, and neither should we (`0x10002d96`, `0x10002d9f`, `0x10002da6`, `0x10002dc9`, `0x10002dd8`, `0x10002ddf`, `0x10002e02`, `0x10002e0a`, `0x10002e11`)
- Round 219: count call sites per IMPORT, not adjacent-call "pairs" (`0x1002400c`, `0x10024010`)
- Round 220: that rule is ALSO wrong: a relocation is not a call (`0x10002770`, `0x10002b2a`, `0x10002b7f`, `0x10002b80`, `0x10002bab`, `0x10002c40`, `0x10003640`)
- 113. Tree-wide call-inventory sweep: exactly one row has a real defect
- 114. The last call defect: two switch tails the reference keeps and we merge (`0x10002b31`, `0x10002b7f`, `0x10002bb2`, `0x10002c22`, `0x10002c40`, `0x10002c51`, `0x10002e9c`, `0x10002f1c`, `0x10027278`)
- Why the reference's spill reloads are not a storage signal (`0x10002da6`, `0x10002dac`, `0x10002dad`, `0x10002dae`, `0x10002e66`, `0x10024010`)
- 115. The sp5-pp toolchain axis, finally measured: a real gain that cannot ship (`0x10016cd0`, `0x10016de0`, `0x10016ea0`, `0x10016f80`)
- 117. The two tails at 0x10002770 are a register-pressure artefact, not a source shape (`0x10002931`, `0x10002b7f`, `0x10002c40`, `0x10002c51`, `0x10002c6c`, `0x10027208`, `0x3fffff71`, `0x3fffffdb`, `0x80000003`, `0x80000004`, `0xc0000005`, `0xc0000006`, `0xc000001d`, `0xc0000025`, `0xc0000026`, `0xc000008c`, `0xc000008d`, `0xc000008e`, `0xc000008f`, `0xc0000096`, `0xc00000fd`)
- 116. A +10 win on CrashDump: hoist the stack-walk setup to the reference's computation point (`0x10002931`, `0x1000293a`)
- 118. Scope of the hoist lever: when it applies, and where it is already satisfied (`0x1000a570`, `0x1000a57c`, `0x1000e140`, `0x10015f70`, `0x101deb00`)
- The `gm_AllocSpieler` near-miss, settled at the link (`0x10018990`, `0x100189c4`, `0x100a8c30`)
- 119. `linktest.sh` already existed: the gap was that nobody was told
- 120. Two dead ends on `gm_AllocSpieler`, and a caution about shared-worktree probing
- 121. `cm_ExSellObjekt`'s one-byte gap is a zero-extension, and the cast is load-bearing (`0x1000d930`, `0x1000db66`, `0x1000db69`, `0x1000db6f`, `0x1000db70`, `0x1000db71`)
- 122. Bounding a missing byte with a jump displacement (`0x100128f0`, `0x10012b9f`, `0x10012ba2`, `0x10012ba4`, `0x10012ba5`, `0x10012ba7`, `0x10012ba9`, `0x10012bab`)
- 123. `drift_windows.py`: localise a byte fault without reading the bytes
- 124. Drift sweep across the remaining rows, and a build-state trap (`0x1000ed4d`, `0x1000ed4f`, `0x1000ed56`, `0x1000ed5b`, `0x1000ed5d`, `0x1000ed62`, `0xffffff81`)
- 125. Guarding the composition collapse
- 126. `ServerMainThread`'s +3 window: a rematerialised constant the reference carries in a register (`0x100097fb`, `0xffffffff`)
- 127. Guarding the silent no-op, and locating `ServerMainThread`'s -2 (`0x10009838`, `0x10009858`, `0x101deae8`, `0xffffffff`)
- 128. `drift_windows.py` was wrong on backward jumps
- 129. Re-sweep after the backward-jump fix, and why the Graveyard reload cannot be cached (`0x10011f27`, `0x10011f2b`)
- 130. The register-pressure cascade is one row's fact, not the tree's
- 131. The Graveyard zero-extend is closed: four spellings, none reaches `xor`+`mov r16` (`0x10011f27`, `0x10011f2b`, `0x10011f2f`)
- 132. What surrounds the Graveyard read: an addressing-mode choice, also not source-selectable (`0x10011f2f`, `0x10011f39`, `0x10011f3f`, `0x100a9820`, `0x1014d8e0`)
- 133. The `[reg + absolute]` pattern is common, but its cost is not
- 134. The zero-extend gap is not caused by addressing: a controlled comparison (`0x100190fc`, `0x10019100`, `0x10019104`, `0x1001910e`, `0x1014d8e0`)
- 135. Why the reference's register is free: counter assignment, not pressure (`0x100190e5`, `0x100190ea`, `0x10019104`, `0x10019129`, `0x10019136`, `0x1001913c`)
- 136. A window where we are *shorter*, and why that constrains the whole function (`0x10019013`, `0x1001901a`, `0x10019020`, `0x1001902b`)
- 137. Reading window signs across the tree, and a surplus with no positive window
- 138. Nested subtraction, automated
- 139. Verification checkpoint: what is actually true at residue 8,652
- 140. `srv_LoadBuf`: 49 bytes, zero length difference, nine push-scheduling clusters (`0x1000a570`, `0x10029a70`, `0xffffff7f`)
- 141. What 8,652 bytes actually is: 15 instructions of difference
- 142. The sp5-pp pin lands: residue 8,652 -> 8,641 (`0x10016cd0`, `0x10016de0`, `0x10016ea0`, `0x10016f80`)
- 143. Sweeping the toolchain axis: a second pin, and the limit of the technique
- 144. The complete toolchain sweep, and a correction
- 145. The toolchain sweep, enumerated from the residue table
- 146. File splitting would unlock nothing: the pin granularity was never the constraint
- 147. The flag landscape, checked on a sixth row
- 148. The data-segment tooling was blind, and what it sees now (round 1 of the data pass)
- The non-`.text` identity is still copied, measured again, honestly
- `.data` and `.rdata` are placement-bound, restated with current numbers
- What the repaired tooling immediately showed: `rebrew data layout audit` (`0x10027078`, `0x100270e8`, `0x100270f8`, `0x100270fc`, `0x10027314`, `0x10027328`, `0x1002735c`, `0x10028888`, `0x1002c3f0`, `0x10030b6c`, `0x10030b84`, `0x10030b98`, `0x10030b9e`, `0x10031538`, `0x10031aac`, `0x10034624`, `0x10034634`, `0x1003467c`, `0x11766204`)
- One more defect the repaired scan caught: an RVA where a VA belongs (`0x00024000`, `0x10024000`)
- 149. Per-symbol `.data`: what 39 wrong symbols actually are (round 2 of the data pass)
- `rebrew verify --data` was comparing nothing, and reporting success
- The 39, classified
- A real type bug, a correct fix, and why it was reverted anyway (`0x10030b84`, `0x10030b94`)
- Two latent defects this uncovered
- 150. The first `.data` win: a declared size that was four times too large (round 3 of the data pass)
- Read `/MAP`, not the bytes (`0x10027074`, `0x10027078`, `0x10027084`, `0x100270a4`, `0x100270e4`, `0x100270e8`, `0x10027104`, `0x10027108`)
- The bug (`0x10027084`)
- Why a 36-byte fix pays 231 bytes, when §149's 37-byte fix cost 236 (`0x10030b84`)
- What it costs, and the baseline that had to move
- The gate could not see `.data` at all: fixed
- The remaining −4, traced but not closed (`0x10027030`, `0x10034f1c`)
- 151. A symbol defined twice: 8 duplicated bytes cost 1,350 (round 4 of the data pass)
- The per-object delta spread is the whole triage
- The bug: a symbol that exists twice (`0x10027104`, `0x10027314`, `0x10027328`, `0x1002733c`)
- 8 bytes removed, 1,350 recovered: and why that is not a paradox
- Quirk: a `.text` byte that is not codegen
- Quirk: the gap blob overlaps ~40 real symbols, and that is correct
- 152. The predictor: ask whether the bytes *after* the edit want to move (round 5 of the data pass)
- The trap, walked into deliberately and then understood (`0x10002692`, `0x100026c3`, `0x100033f3`, `0x100270f8`, `0x100270fc`)
- The measurement that would have vetoed it (`0x10027360`, `0x100273e0`)
- What it found next: a global nothing defined (`0x10028938`, `0x1002893c`, `0x100366dc`)
- Quirk: `link_stubs.c` hides missing data as successfully-linked zeros (`0x1002c3f0`, `0x11766204`)
- 153. A named array lands first; a literal lands last (round 6 of the data pass)
- The ordering bug in §152's own fix (`0x100288e0`, `0x100288f8`, `0x10028938`, `0x10028940`)
- Five truncated stubs that duplicated COMDAT literals (`0x10028888`, `0x10028aec`, `0x10028b04`, `0x10028b60`, `0x10028b78`)
- Quirk: the probe's +28 and a −64 shrink are not a contradiction (`0x10028bf0`)
- `.text` +1 is placement again
- 154. Data-only TUs beat text-ordered link for .data placement (round 7 of the data pass) (`0x10006ec0`, `0x10009d30`, `0x1000ad40`, `0x10028bdc`)
- The fix: a data-only TU ordered between m_alloc2 and trees (`0x10006c00`, `0x10006c80`, `0x10006ec0`, `0x10028bdc`, `0x10029408`)
- Result (`0x10028bdc`, `0x10029408`)
- Quirk: CMake object order is `.text` VA, not `.data` VA
- Next miss (`0x1002944c`)
- 155. Twelve bytes of fopen mode + gzip magic before the vfs path (round 8 of the data pass) (`0x1002944c`)
- The fix
- Result (`0x1002944c`, `0x100294a0`)
- Next miss (`0x100294a4`)
- 156. A raw address cast emits no data; a named array in the right TU does (round 9 of the data pass) (`0x100294a4`)
- The fix (`0x100294a4`)
- Result (`0x100294a4`, `0x100294d4`)
- Quirk: raw address ≠ data
- Next miss (`0x10024620`, `0x10024f50`, `0x100294d4`)
- 157. Explicit zero-pad arrays are redundant under MSVC6 4-byte alignment (round 10 of the data pass) (`0x10034f00`)
- The fix (`0x10028bdc`, `0x10029408`)
- Result (`0x10034620`, `0x10034f00`, `0x10034f50`)
- Next miss (`0x1002733c`, `0x10027538`)
- 158. Named dword before first string COMDAT (round 11 of the data pass) (`0x10027030`, `0x10027100`, `0x10027104`, `0x10027534`, `0x10027538`, `0xffffffff`)
- The fix (`0xffffffff`)
- Result (`0x10027030`, `0x1002706c`, `0x10027538`)
- Failed approaches (do not retry without new evidence)
- Next miss (`0x1002733c`)
- 159. `gm_AllocSpieler`'s interpolation loop: the reference caches two floats in locals (round 985) (`0x10018bc8`, `0x10018bcb`, `0x10018bcd`, `0x10018bdd`)
- 163. msvc6 canonicalises independent operations: the ORDER of two independent statements is inert (round 1105) (`0x10002c5c`)
- 164. msvc6 SINKS a load past an intervening store, and hoists it back when the value is USED first (round 1106) (`0x1000e21d`)
- 173. A pointer comparison against a constant is unsigned; an int cast makes it `jl` (`0x004e7390`, `0x0053f8f0`, `0x014d0020`, `0x014d0c20`)
- 165. NaN-safe `fcom` vs `fcomp`: `test ah,5 / jp` is a `<`, not a `<=` (`0x004514d0`, `0x006628c8`, `0x006628f8`)
- 174. A constant-size struct assignment is `rep movsd`; `memcpy` of the same size is not (`0x004c5b00`, `0x004c62c0`, `0x004c6360`, `0x004c63f0`, `0x004c6b60`, `0x004ce210`, `0x004ce260`)
- 175. `fld dword ptr [g]` + `call <helper>` with no stack store is a float→int cast (`0x004c54c0`, `0x0064d228`, `0x0067db50`, `0x0067db54`)
- 176. `push imm32` of a data address is `push offset g`, not `push [g]` (`0x004c5700`, `0x007f4c00`)
- 177. A destination struct with internal gaps: spell the offsets, not the struct (`0x004c64b0`)
- 178. Locals whose only use is an escaping pointer are dead-store-eliminated: group them (`0x00403040`)
- 179. `[esp + N]` argument reads: count every push that is still on the stack (`0x004f7740`, `0x005b2810`, `0x005b33a0`)
- 180. An early `int i = 0;` puts the loop counter in `esi`; `for (i = 0; ...)` drops it to `eax` (`0x004029c0`, `0x00403200`)
- 181. A look-ahead `g[++i]` scan is the only spelling that rotates the free-slot loop
- 182. `K + (c ? 3 : 0)` fuses into an LEA; `c ? K+3 : K` does not
- 183. One source for two targets: only data addresses need per-target markers (`0x004e7150`, `0x004e8d10`, `0x004ea8e0`, `0x004ec660`, `0x00517700`, `0x0051af00`, `0x0053e000`, `0x00545d40`, `0x0060f188`, `0x0068deb8`)
- 184. A bound spelled `base + constant` still encodes as one immediate (`0x004ea560`, `0x00770b84`, `0x007d5f84`, `0x007f4ca4`, `0x0085a0a4`)
- 185. `ServerMainThread`'s transfer-size packet: dropping `volatile` fixes the push order and costs 4 linked bytes (`0x100093a0`, `0x101deac0`, `0xffffffff`)
- 186. `gm_AllocSpieler` has unreversed client twins: the same compiler with the Processor Pack code generator (`0x00507690`, `0x00507f63`, `0x0050a7e0`, `0x0050b0b3`, `0x10018850`, `0x1001911b`)
- 187. A raw integer address is not a symbol: msvc6 keeps loads through it across calls (`0x10018850`, `0x10035434`, `0x100358a0`, `0x100a8c30`)
- 188. Read a parameter load net of the pushes still on the stack (`0x10018d2d`, `0x10018d35`, `0x10019572`)
- 189. `(double)` on one factor of a `float * float` product decides which operand loads
- 190. In an x87 loop, the order the locals were initialised sets the evaluation order
- 191. A pointer local keeps an address apart from the load or store through it
- 192. `unsigned short` for a 16-bit draw: one mask, and `fild` before the product
- 193. Byte arithmetic in a `char` temporary; index expressions without an index local
- 194. Table reads through a symbol emit `[r*2+disp]`; a raw integer base emits `[r+r+disp]` (`0x10030ba5`)
- 195. Symbolising only some constants can flip an unrelated FPU arm (`0x100256b0`, `0x10025714`)
- 196. `ServerMainThread` to byte-exact: symbols, plain memory reads, a promoted flag, and a `while` (`0x100093a0`, `0xffffffff`)
- 197. A fill loop is not a `memset`: the destination keeps its own register (`0x1000bdf0`, `0x1000bef4`, `0x100188fa`, `0x10019455`, `0x100358fc`)
- 198. `gm_AllocSpieler` from 515 to 17 linked bytes: temporaries and variable identity (`0x10018c28`, `0x10018c38`)
- 199. A two-constant ternary: of the spellings tried, only `c ? A : B` gives `setcc; dec; and A-B; add B` with a dword add (`0x10018bb7`, `0x10019245`, `0x1001928a`)
- 200. Carrier wave, round 1145: the documented walls that were source shapes (`0x1000bebb`, `0x1000bf38`, `0x1000d930`, `0x1000dd46`, `0x1000dec7`, `0x1002cd14`, `0x1002cd48`, `0x10035434`)
- 201. `gv_ExAllocGraveyardWorker` (0x10011bf0) closes under plain `/O2`: the `/Ow` flag was the wall (`0x10011dd2`, `0x10011df5`, `0x10011dff`, `0x1071f7b3`, `0x10727977`)
- 202. GOLDTL near misses closed by source shape (Processor Pack client) (`0x00402090`, `0x0041c190`, `0x0041f8f0`, `0x0043a3f0`, `0x004af050`, `0x004af800`, `0x004afb60`, `0x004c8a30`, `0x004dc5f0`, `0x004ee6d0`, `0x004f0cc0`, `0x004f45b0`, `0x004f58b0`, `0x004fc280`, `0x004fc2e0`, `0x004fc3a0`, `0x004ff080`, `0x005a89a0`, `0x005b1e20`, `0x005b4f70`, `0x005c80f0`, `0x005c8400`, `0x005d63e0`, `0x005dc990`, `0x006628a8`, `0x01015f40`, `0x01016198`)
- 203. A separate product local preserves the field-first x87 load with a shared constant (`0x1000bdf0`, `0x100256b8`)
- 204. Extern float reads can change scheduling even when the value and width agree (`0x10011bf0`, `0x41400000`)
- 205. Recover a native address operand without changing its scale or access width (`0x1000b4d0`, `0x100151b0`, `0x10017330`, `0x100174d0`, `0x10017fb0`, `0x10029bb8`, `0x10029bc0`, `0x10029bc8`, `0x1002da30`, `0x10030860`, `0x10030b6a`, `0x10035880`)
- 206. An unused extern declaration can affect another function's emitted schedule
- 207. Inline pointer tables can cause a false instruction diff despite a full byte match
- 208. Multidimensional struct arrays nest declarators in the C AST
- 209. A masked call match does not establish the callee's identity (`0x10003b90`, `0x10003bc5`, `0x1001a931`, `0x1001aa6a`, `0x1001b200`, `0x1001eab0`)
- 210. Zero-code CRT aliases belong in library identity candidates (`0x1002377b`)
- 211. Change the other readers to literals when symbolizing a literal breaks scheduling (`0x10018850`, `0x10019720`, `0x100252e8`, `0x100252f4`)
- 212. Literal doubles can preserve memory operands and share the stock CRT pool (`0x1000e9c0`, `0x10011bf0`, `0x10018850`, `0x1001f1d0`, `0x1001f2bb`, `0x10025698`, `0x100257d8`, `0x100260b0`, `0x100260f0`)
- 213. A pooled empty string can occupy writable BSS (`0x100294d0`, `0x100294d4`, `0x100294d8`, `0x100294dc`, `0x100294f4`, `0x100294f8`, `0x10034620`, `0x117650c8`, `0xc0301080`)
- 214. Data-only `selectany` makes readonly owners independently orderable (`0x100241a0`, `0x1002469c`, `0x10024a04`, `0x10025fc0`, `0x40301040`, `0x40401040`, `0xffff0000`)
- 215. A shared initialized string can replace a displaced compiler pool without changing code (`0x1001426e`, `0x10015a7c`, `0x10015b4b`, `0x1002944c`, `0x1002d7b0`, `0xc0300040`)
- 216. Unused named copies do not replace the compiler's live string literals (`0x1002a10c`, `0x1002a140`, `0x1002a168`, `0x1002a19c`, `0xc0300040`)
- 217. A real character array before a static pointer restores shared version storage (`0x10001346`, `0x100057d4`, `0x10009139`, `0x100091f9`, `0x1002706c`, `0x10027070`, `0x10027074`, `0xc0300040`)
- 218. Explicit-zero selectany globals become independently orderable BSS COMDATs (`0x100294dc`, `0x100294f8`, `0x10034610`, `0x10034614`, `0x10034618`, `0x1003461c`, `0x10034620`, `0x10034624`, `0x10034628`, `0x1003462c`, `0x10034630`, `0x10034634`, `0x10034638`, `0x1003463c`, `0x10034640`, `0x10034643`, `0xc0300080`, `0xc0301080`)
- 219. bss_seg applies to tentative globals; an explicit zero can bypass it (`0x10001000`, `0x10001004`, `0x10001008`, `0x1000100c`, `0xc0300040`, `0xc0300080`, `0xc0301080`)
- 220. A stock archive member can retain private storage without appearing in MAP owners (`0x10033bc8`, `0x10033ef8`, `0xc0300040`)
- 221. Native ORDER rejects ordinary initialized data as well as ordinary BSS (`0xc0300040`)
- 222. Native build clocks change CL's builtins and COFF stamp, preserving this full code shape (`0x60501020`, `0xc0300040`)
- 223. Removing stale size comments and wrapping tables preserves complete native contributions (`0x1000e7d0`, `0x1000eb70`, `0x60501020`)
- 224. Five late server globals become COMMON without changing their complete code (`0x00264264`, `0x01585584`, `0x11762e84`, `0x11762e94`, `0x11764084`, `0x11764094`, `0x60501020`)
- 225. Splitting gm_Open's six zero definitions does not establish their placement (`0x10034624`, `0x1003463c`, `0x10034640`, `0x10034670`, `0x10034678`, `0x1003467c`, `0x60501020`, `0xc0301080`)
- 226. Eight real allocator globals form one ordinary 32-byte BSS block (`0x10034624`, `0x10034628`, `0x1003462c`, `0x10034630`, `0x10034634`, `0x10034638`, `0x1003463c`, `0x10034640`, `0x117663a8`, `0x60501020`, `0xc0300080`)
- 227. A live COMMON request can select a hidden member before its code is discarded (`0x10033bc8`, `0x10034110`, `0xc0300040`)
- 228. Data roots can preserve CODE while moving alignment, or move existing CODE too (`0x0173f820`, `0x10034034`, `0x1003403c`, `0x100340a0`, `0x100340a8`, `0x10034260`, `0x101dd920`, `0xc0300040`, `0xc0400040`)
- 229. Redundant import retention pragmas do not determine this WinSock IAT
- 230. Eliminated function-address expressions do not seed VC6 undefined symbols
- 231. Tentative globals have stable COFF order independent of their textual declaration order
- 232. Removing the inherited border word preserves all four complete zlib functions (`0x1002469c`, `0x100246a0`, `0x40301040`, `0xffff0000`)
- 233. Removing unreferenced COMMON placeholders leaves the native image unchanged (`0x100241a0`)
- 234. An empty stock data section still contributes native alignment (`0x10034018`, `0xc0300040`, `0xc0400040`, `0xc0500040`)
- 235. An unused stock duplicate can change the native ICF survivor (`0x1001f855`, `0x1002350a`, `0x10023812`, `0x60101020`)
- 236. A tentative pointer and an initialized pointer use different native storage (`0x0173f7e0`, `0x0173f800`, `0x10034610`, `0x10035408`, `0x1014c6c4`)
- 237. A preceding COMMON array can consume an apparent alignment gap (`0x0173f7f0`, `0x10034614`, `0x10034620`, `0x10034660`, `0x1003466c`, `0x10034680`)
- 238. One real COMMON provider preserves storage sizes but changes physical order (`0x0173f81c`, `0x10034b00`)
- 239. Debug records can change COFF without changing the runtime DLL
- 240. Live COMMON extent can change relocation reservation without changing code
- 241. Actual allocator COMMONs can occupy the reference run without moving bulk arrays (`0x0173f7d0`, `0x10034620`, `0x10034624`, `0x10034640`)
- 242. Pool-root access does not establish an IDA array extent; a separate flag can be COMMON
- 243. Uninitialized section roots affect COMMON placement and can split `.data` (`0xc0300080`)
- 244. Real game definitions can move into native data archives without changing their readers (`0xc0400080`)
- 245. RVA-shaped raw words can be instruction bytes rather than address operands (`0x10009020`, `0x100093a0`, `0x10012000`, `0x10012440`, `0x10012eb0`, `0x1001321d`, `0x10034684`, `0x10035408`)
- 246. An import-only translation unit has no runtime contribution
- 247. The tool's CRT can change import layout without changing C contributions
- 248. Link-only runtime selection preserves every existing compiler input
- 249. An int formal narrowed to a local byte preserves MSVC6 dispatch code
- 250. Live literals restore the original pool and permit the complete Error TU (`0x10027078`, `0x100274a8`, `0x4662de1a`)
- 251. Compiler-equivalent zlib code does not identify the original producer
- 252. A shared-source cohort can preserve server code and conflict with Gold ordering (`0x10010530`, `0x10014ca0`)
- 253. Adjacent compatible command cohorts preserve code and shared annotation order
- 254. Available alternate CRT archives do not supply the missing original producer
- 255. A real array COMDAT removes COMMON alignment but displaces a correct neighbor (`0x10034658`, `0x10034660`, `0x10034678`, `0x10034680`, `0x10035478`, `0xc0301080`)
- 256. An indexed table load can numerically coincide with another global (`0x10016420`, `0x1013869c`, `0x1013989c`)
- 257. Track ECX definitions before assigning a thiscall signature (`0x10006e30`, `0x10006e65`, `0x10008e1d`, `0x10008e1f`, `0x10008e2a`, `0x10008e2f`, `0x1000921a`, `0x1000921b`, `0x10009220`, `0x10009225`, `0x10034670`, `0x10034674`, `0x10034677`, `0x1003467f`)
- 258. Preserve the stream handle when its argument slot becomes the read count (`0x004013b0`, `0x004013f0`)
- 259. Early pointer return and ordered copy setup recover the animation builder (`0x00405970`, `0x00406510`, `0x0040d7f7`)
- 260. Compare operand order in the task-removal owner guard (`0x004050c0`)
- 261. Keep the sound scale temporary double until its final float store (`0x00418c80`, `0x004193f0`, `0x005eba10`, `0x00662b40`)
- 262. Separate float distance assignment from the positional sound scale
- 263. Typed DirectInput prefix calls preserve indexed-vtable code
- Biased table displacement from a zero-based read view (`0x00662ba8`, `0x00662bf8`)
- Pointer-typed conditional CRT tail wrapper
- Additional unused CRT prototypes can disturb a large server function
- Typed table view retains signed integer address iteration
- Byte parameter suppresses integer extension at the call boundary
- Existing byte/constant callers can share a byte-width prototype
- Random-helper return declarations affect copies before widening (2026-10-04) (`0x004a9000`, `0x004ad1c0`, `0x004faa90`)
- Random-helper return width changes both epilogues (2026-10-04)
- Slot byte signedness changes equality promotion (2026-10-04) (`0x005be320`, `0x005ca560`)
- Unused named variadic parameter does not establish a prototype (2026-10-04)
- Empty helper knowledge changes calls, not just register allocation (2026-10-10)
- Mode-check ordering shares failure returns (2026-10-10)
- Prototype consolidation can change line constants (2026-10-11)
- Narrow helper formals control partial-register argument loads (2026-10-11)
- Prototype-only headers preserve MSVC6 translation-unit context (2026-10-11)
- Shared prototype position preserves commutative integer register roles (2026-10-14)
- Six-element array loops reduce to native display-counter address loops (2026-10-14)
- Typed scene draw-data cleanup preserves both 137-byte bodies (2026-10-15)
- Auxiliary-record cleanup shares one typed 133-byte algorithm (2026-10-15)
- Full spiel.c context and allocator byte-condition residue (2026-10-15) (`0x00500190`)
- Character model flag word emits the native high-byte OR (2026-10-15) (`0x00403070`, `0x0040342a`, `0x00403880`)
- A forwarded stack DWORD does not establish an int parameter (2026-10-15) (`0x00404a00`, `0x00418b40`, `0x0044c620`, `0x0044e1e0`, `0x0044e309`, `0x0044e32d`, `0x0044e4a0`, `0x0044f8b0`, `0x0044f9d9`, `0x0044f9fd`)
- Implicit final row in a local string matrix (2026-10-16)
- Character camera script exits and separation probe (2026-10-16) (`0x00402d00`, `0x0040ca60`, `0x0040d980`)
- Six-participant event validator (2026-10-16) (`0x004daf80`, `0x004dc7d0`)
- Court decision source and stateful sum (2026-10-16) (`0x004dd960`, `0x004df1b0`)
- Goal59: participant-reset cursor bias and unreachable runner test
- Goal60: one texture loop, two native backends
- Goal61: typed periodic callbacks without changing timer behavior
- Goal62: resolver output locals can reuse a dead ID argument
- Method registration's explicit memcpy (Goal66, 2026-10-16)
- Script animation options ordering (Goal67, 2026-10-16)
- List-search result after the loop (Goal75, 2026-10-17) (`0x00423720`, `0x00423740`, `0x006323a4`)
- Declared globals preserve cursor/dialog scheduling (Goal78, 2026-10-17) (`0x004113f0`, `0x0041cf60`)
- GUI pool loads need declarations, not assembly (Goal79, 2026-10-17) (`0x00472640`, `0x00472770`, `0x00475e30`, `0x00475f30`)
- Scene command tests AL and always returns one (Goal80, 2026-10-17) (`0x0040ddf0`, `0x0040ed00`, `0x0050d6d0`, `0x0050d725`, `0x0050d730`)
- VFS closer needs the named counter object (Goal81, 2026-10-17) (`0x00430580`, `0x0043068f`, `0x00522e30`, `0x00525b40`, `0x006b7fe4`, `0x10034670`)
- Opaque stream boundary preserves target objects (Goal82, 2026-10-17) (`0x0041cf55`, `0x0041cf60`, `0x00522510`, `0x00522abe`, `0x00522ac0`, `0x00524605`, `0x00524610`)
- Conditional COM release through an inline helper (`0x00460e40`, `0x00460e9a`)
- Tail wrapper contracts before instruction-scheduling searches (`0x004c24c0`)
