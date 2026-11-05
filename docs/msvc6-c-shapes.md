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
A byte-neutral result at one call site does not make it neutral everywhere.
Likewise, algebraic equality does not establish equivalence under signed overflow,
FP rounding or observable reloads.

## Common traps

- An uninitialized C local may indicate missing recovery or native indeterminate
  data. Trace every producer before adding an initializer.
- A `float` memory operand does not prove that an x87 intermediate was rounded to
  float. A store/reload boundary is separate evidence.
- `__ftol` can serve both narrow and wide source conversions. Its qword temporary
  and EDX:EAX output do not prove the caller's declared return type.
- A source rewrite that kills an index can remove the native induction form.
- Unused declarations and definition order can affect code generation. Preserve
  the original TU context during probes.
- Keep logging literals, argument order and even native API-format mismatches
  faithful. Correcting the game is a different task from reconstructing it.

Use [negative results](codegen-walls.md) before reopening an exhausted probe family.
A failed search grants no [assembly exception](assembly-audit.md).


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/msvc6-c-shapes.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/msvc6-c-shapes.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="msvc-60-c-shapes"></a>MSVC 6.0: C shapes | - |
| <a id="index-by-symptom"></a>Index by symptom | - |
| <a id="how-to-probe-a-hypothesis"></a>How to probe a hypothesis | - |
| <a id="1-global-array-element-type-sets-the-addressing-scale"></a>1. Global array element type sets the addressing scale | `0x1000d8a0`, `0x100111b0`, `0x100113b0`, `0x100196c0`, `0x10035439` |
| <a id="2-pointer-vs-array-mov-load-against-lea"></a>2. Pointer vs array: `mov` load against `lea` | `0x100181a0`, `0x10019ae0` |
| <a id="3-uninitialized-locals-from-decompilation"></a>3. Uninitialized locals from decompilation | `0x100180d0`, `0x10019a20` |
| <a id="4-wrong-global-in-a-guard"></a>4. Wrong global in a guard | `0x100035c0`, `0x10034610`, `0x10034680` |
| <a id="5-an-explicit-pointer-local-defeats-the-induction-variable-rewrite"></a>5. An explicit pointer local defeats the induction-variable rewrite | `0x10014ee0` |
| <a id="6-local-variable-width"></a>6. Local variable width | - |
| <a id="7-branch-polarity-merge-sequential-returns"></a>7. Branch polarity: merge sequential returns | - |
| <a id="8-loop-shape-for-with-early-return-vs-dowhile-with-a-tail-return"></a>8. Loop shape: `for(;;)` with early return vs `do/while` with a tail return | - |
| <a id="8a-x87-memory-operand-forms-fimulfidiv-vs-fild--fmulpfdivp"></a>8a. x87 memory-operand forms: `fimul`/`fidiv` vs `fild` + `fmulp`/`fdivp` | `0x10019720` |
| <a id="pick-the-weaker-lever-when-the-targets-schedule-is-looser"></a>Pick the weaker lever when the target's schedule is looser | - |
| <a id="8b-a-folded-cmp-hides-a-load-the-target-keeps-in-a-register"></a>8b. A folded `cmp` hides a load the target keeps in a register | `0x10019720` |
| <a id="8c-a-volatile-read-pins-load-order-between-two-field-reads"></a>8c. A volatile read pins load order between two field reads | `0x10019720` |
| <a id="9-register-roles-follow-order-of-first-use"></a>9. Register roles follow order of first use | `0x10010fa0` |
| <a id="9a-shorten-a-live-range-to-break-an-esiedi-tie"></a>9a. Shorten a live range to break an esi/edi tie | `0x10012470` |
| <a id="10-load-scheduling-between-adjacent-field-reads"></a>10. Load scheduling between adjacent field reads | - |
| <a id="11-inline-memset-expansion-partial-result-no-byte-match"></a>11. Inline memset expansion (partial result, no byte match) | `0x100068e0` |
| <a id="12-cflags-are-per-file-in-practice-not-per-function"></a>12. CFLAGS are per-file in practice, not per-function | `0x10006820` |
| <a id="13-per-function-frame-pointer-without-a-cflags-header"></a>13. Per-function frame pointer without a CFLAGS header | `0x10006820`, `0x100068e0` |
| <a id="14-homing-a-value-in-the-incoming-parameter-slot"></a>14. Homing a value in the incoming parameter slot | `0x1000691b`, `0x10006924` |
| <a id="15-_ftolexpr-pushes-a-double-a-plain-int-cast-does-not"></a>15. `_ftol(expr)` pushes a double; a plain `(int)` cast does not | `0x10018850` |
| <a id="16-compare-the-call-skeleton-before-chasing-instruction-diffs"></a>16. Compare the call skeleton before chasing instruction diffs | `0x10019228`, `0x100192b3` |
| <a id="17-out-of-line-block-placement-is-not-steerable-from-source"></a>17. Out-of-line block placement is not steerable from source | `0x10002770`, `0x100093a0`, `0x10009657`, `0x1000973a`, `0x10009756` |
| <a id="18-byte-width-levers-move-encodings-not-always-the-score"></a>18. Byte-width levers move encodings, not always the score | - |
| <a id="19-match_count-is-positional-so-one-size-delta-hides-a-good-match"></a>19. `match_count` is positional, so one size delta hides a good match | `0x100093a0` |
| <a id="20-statement-order-does-not-move-stores-into-the-same-buffer"></a>20. Statement order does not move stores into the same buffer | - |
| <a id="19a-match_count-is-a-positional-byte-compare-same-rule-as-19"></a>19a. `match_count` is a positional byte compare (same rule as §19) | - |
| <a id="21-fold-the-offset-into-the-pointer-before-the-access"></a>21. Fold the offset into the pointer before the access | `0x10003820`, `0x1000eb70` |
| <a id="21a-hoisting-a-field-load-out-of-an-argument-list-breaks-an-esiedi-tie"></a>21a. Hoisting a field load out of an argument list breaks an esi/edi tie | `0x100198b0` |
| <a id="22-volatile-on-the-store-target-pins-a-store-against-loop-scheduling"></a>22. `volatile` on the store target pins a store against loop scheduling | `0x1000c600` |
| <a id="23-a-shared-clamp-value-needs-a-32-bit-temp-assigned-in-both-arms"></a>23. A shared clamp value needs a 32-bit temp assigned in both arms | `0x10010140` |
| <a id="24-two-volatile-reads-pick-both-the-register-form-and-the-schedule"></a>24. Two volatile reads pick both the register form and the schedule | `0x1000a340` |
| <a id="25-ecxedx-naming-residue-is-usually-a-first-read-or-a-hoisted-temp-bug"></a>25. ecx/edx naming residue is usually a first-read or a hoisted-temp bug | `0x1000b4d0`, `0x1000c710`, `0x1000e7d0` |
| <a id="26-spelling-a-clamp-as-setledecand-decides-the-loads-before-it"></a>26. Spelling a clamp as `setle`/`dec`/`and` decides the loads before it | `0x10011790` |
| <a id="27-a-volatile-byte-read-defeats-the-bytedword-load-merge-on-one-slot"></a>27. A volatile byte read defeats the byte/dword load merge on one slot | `0x10018450` |
| <a id="28-constant-cse-in-a-straight-line-store-block-has-no-source-lever"></a>28. Constant CSE in a straight-line store block has no source lever | `0x100170e0` |
| <a id="29-hoist-a-common-addend-out-of-a-select-and-let-the-select-assign-the-result"></a>29. Hoist a common addend out of a select, and let the select assign the result | `0x1000eaa0` |
| <a id="30-volatile-at-the-load-site-defeats-displacement-folding"></a>30. `volatile` at the load site defeats displacement folding | `0x100104a0`, `0x10015460` |
| <a id="31-a-pointer-sweep-with-a-separate-index-beats-an-indexed-walk"></a>31. A pointer sweep with a separate index beats an indexed walk | `0x100358a0`, `0x100358a2`, `0x1009aca2` |
| <a id="32-proven-is-not-a-byte-match-and-it-hides-tractable-work"></a>32. PROVEN is not a byte match, and it hides tractable work | - |
| <a id="33-statement-order-decides-which-register-holds-a-value"></a>33. Statement order decides which register holds a value | `0x1000c710` |
| <a id="34-reloc-can-hide-a-wrong-global-check--operands-against-the-symbol"></a>34. RELOC can hide a wrong global: check `~~` operands against the symbol | `0x100100a0`, `0x100256a4`, `0x100256cc` |
| <a id="35-row-multiply-vs-offset-accumulation-decides-strength-reduction-fallout"></a>35. Row multiply vs offset accumulation decides strength-reduction fallout | `0x1000b4d0`, `0x10015950`, `0x10035a6c`, `0x1009ae6c` |
| <a id="36-the-outer-calls-argument-form-can-fix-a-whole-function-register-swap"></a>36. The outer call's argument form can fix a whole-function register swap | `0x100198b0` |
| <a id="37-a-dead-parameter-slot-can-home-more-than-one-byte"></a>37. A dead parameter slot can home more than one byte | `0x1000b290` |
| <a id="38-msvc6-shrink-wraps-and-the-lever-is-loop-register-demand"></a>38. msvc6 shrink-wraps, and the lever is loop register demand | `0x10016290`, `0x10016f80` |
| <a id="161-sib-baseindex-roles-follow-the-induction-variables-form"></a>161. SIB base/index roles follow the induction variable's form | `0x10010850`, `0x10015950` |
| <a id="160-proven-status-is-lost-by-a-stub-result-and-that-is-a-real-regression"></a>160. PROVEN status is lost by a STUB result, and that is a real regression | - |
| <a id="162-relocation-masking-can-hide-a-wrong-symbol-the-false-reloc-same-rule-as-34"></a>162. Relocation masking can hide a wrong symbol: the false RELOC (same rule as §34) | `0x100100a0`, `0x10015950`, `0x100256a4`, `0x100256cc`, `0x100311f0`, `0x10031204` |
| <a id="39-a-volatile-argument-read-defers-a-parameter-load-past-the-prologue-pushes"></a>39. A volatile argument read defers a parameter load past the prologue pushes | `0x10010710`, `0x10017c40` |
| <a id="40-a-struct-assignment-breaks-a-register-tie-without-changing-a-byte"></a>40. A struct assignment breaks a register tie without changing a byte | `0x2641f8`, `0x2641fc`, `0x1000a080`, `0x10012470`, `0x1002d4f0` |
| <a id="41-two-levers-that-each-regress-can-be-exact-together"></a>41. Two levers that each regress can be exact together | `0x10017c40` |
| <a id="42-the-number-of-reaching-definitions-decides-loadstore-scheduling"></a>42. The number of reaching definitions decides load/store scheduling | `0x132154`, `0x2641f8`, `0x2641fc`, `0x264264`, `0x1000a080`, `0x101deb00`, `0x114ffe20` |
| <a id="43-and-eax0xff-is-one-byte-shorter-than-the-same-mask-on-any-other-register"></a>43. `and eax,0xff` is one byte shorter than the same mask on any other register | - |
| <a id="44-pragma-optimizea-on-reorders-a-field-read-against-a-store"></a>44. `#pragma optimize("a", on)` reorders a field read against a store | `0x100155c0` |
| <a id="45-merging-duplicated-tail-stores-sinks-a-loop-store-below-the-decrement"></a>45. Merging duplicated tail stores sinks a loop store below the decrement | - |
| <a id="46-the-x87-fxch-slot-and-a-folded-byte-compare-are-set-by-one-type-choice"></a>46. The x87 `fxch` slot and a folded byte compare are set by one type choice | `0x10019720`, `0x100257d0` |
| <a id="47-a-loops-form-not-its-text-decides-where-c2-puts-its-cold-exit-block"></a>47. A loop's form, not its text, decides where C2 puts its cold exit block | `0x100093a0` |
| <a id="48-msvc6-folds-a-compared-variable-into-a-later-store-and-no-spelling-keeps-it-in-the-register"></a>48. msvc6 folds a compared variable into a later store, and no spelling keeps it in the register | `0x100093a0`, `0x10009846`, `0x101deac0`, `0xffffffff` |
| <a id="49-a-cflags-sweep-on-one-function-inert-negative-and-one-near-miss"></a>49. A CFLAGS sweep on one function: inert, negative, and one near miss | `0x10018850`, `0x1001A0F0` |
| <a id="50-the-residual-codegen-classes-as-instructions"></a>50. The residual codegen classes, as instructions | `0x100097fb`, `0x1000984b`, `0x100098e3`, `0x10009baf`, `0xffffffff` |
| <a id="51-volatile-on-a-local-is-a-scheduling-barrier-qualify-at-the-use-site"></a>51. `volatile` on a local is a scheduling barrier; qualify at the use site | `0x10008a90` |
| <a id="52-the-16-bit-zero-extend-idiom-is-selected-by-volatile-not-by-c-spelling"></a>52. The 16-bit zero-extend idiom is selected by `volatile`, not by C spelling | `0x10009020`, `0x10011bf0`, `0x10018850`, `0xffffff86` |
| <a id="53-switch-case-bodies-are-laid-out-in-source-order"></a>53. `switch` case bodies are laid out in source order | `0x100174d0` |
| <a id="54-a-guard-inversion-moves-which-site-falls-through-and-with-it-the-branch-histogram"></a>54. A guard inversion moves which site falls through, and with it the branch histogram | `0x1000d930`, `0x1000e00e` |
| <a id="55-comparison-rewrites-must-keep-the-strictnon-strict-boundary"></a>55. Comparison rewrites must keep the strict/non-strict boundary | - |
| <a id="56-a-missing-exit-epilogue-is-a-return-that-hands-back-a-register"></a>56. A missing exit epilogue is a `return` that hands back a register | `0x10008a90` |
| <a id="57-loop-shape-is-a-lever-only-when-the-divergence-is-not-register-pressure"></a>57. Loop shape is a lever only when the divergence is not register pressure | `0x10002770`, `0x1000bdf0`, `0x1000e140` |
| <a id="58-ox-versus-o2-is-per-file-and-load-bearing"></a>58. `/Ox` versus `/O2` is per-file and load-bearing | `0x10018850` |
| <a id="59-if-cond-goto-l-compiles-to-if-cond--body--cold-handlers-are-placed-by-block-creation-order"></a>59. `if (cond) goto L;` compiles to `if (cond) { body }`; cold handlers are placed by block *creation* order | `0x10002770`, `0x10002db3`, `0x10002de9`, `0x10002e1b`, `0x10002e29`, `0x10002e35`, `0x10002e4d` |
| <a id="60-a-volatile-stores-position-is-a-dependency-fixed-point-not-a-statement-order-choice"></a>60. A volatile store's position is a dependency fixed point, not a statement-order choice | `0x1000e140`, `0x101de450` |
| <a id="61a-the-aliasing-lever-is-a-wall-when-the-function-has-more-than-the-one-transposition-round-1020"></a>61a. The aliasing lever is a wall when the function has more than the one transposition (round 1020) | `0x1000e140`, `0x1000e20c` |
| <a id="61-a-shared-guard-the-reference-falls-into-cannot-be-reached-by-fall-through-from-c"></a>61. A shared guard the reference falls into cannot be reached by fall-through from C | `0x1000aac0` |
| <a id="62-a-literal-shared-by-several-comparisons-is-not-a-lever-for-register-residence"></a>62. A literal shared by several comparisons is not a lever for register residence | `0x1000ec00`, `0x1000edc0`, `0x100358a0`, `0x10035ab0` |
| <a id="63-a-clamps-winning-arm-order-is-per-site-not-per-function"></a>63. A clamp's winning arm order is per-site, not per-function | `0x1000ec00` |
| <a id="64-for---if-x-break---is-normalised-to-the-dowhile-form"></a>64. `for (;;) { if (x) break; ... }` is normalised to the `do/while` form | `0x1000ec00` |
| <a id="65-an-ifelse-if-chain-and-a-real-switch-emit-their-jump-tables-in-opposite-order"></a>65. an if/else-if chain and a real `switch` emit their jump tables in OPPOSITE order | `0x10002770`, `0x10002a43`, `0x10002e9c`, `0x10002f1c`, `0x100128f0`, `0xc0000025`, `0xc000008f` |
| <a id="66-a-dead-store-in-the-source-appears-as-a-store-in-the-reference-comparing-stores-is-a-dead-code-oracle"></a>66. a dead store in the source appears as a store in the reference: comparing stores is a dead-code oracle | `0x10002770`, `0x100029f7`, `0x10002a02`, `0xc000008e` |
| <a id="67-msvc6-does-not-reorder-calls-so-call-order-in-the-source-is-recoverable-from-the-reference"></a>67. msvc6 does not reorder calls, so call order in the source is recoverable from the reference | `0x10002770`, `0x100028fb`, `0x10002901`, `0x10002923`, `0x1000294c`, `0x10024028`, `0x1002402c` |
| <a id="68-a-redundant-null-test-after-a-search-loop-is-not-eliminated-and-its-width-matters"></a>68. a redundant null test after a search loop is NOT eliminated, and its width matters | `0x100174d0` |
| <a id="69-an-__asm-block-is-a-scheduling-barrier-and-this-projects-c-only-constraint-forbids-using-it-as-one"></a>69. an `__asm` block is a scheduling barrier, and this project's C-only constraint forbids using it as one | `0x100174d0` |
| <a id="70-operand-order-in-a-commutative-address-expression-is-inert-only-the-nesting-steers"></a>70. operand order in a commutative address expression is inert; only the *nesting* steers | `0x100128f0` |
| <a id="71-memsetp-0-n-is-an-intrinsic-that-is-not-value-tracked-so-it-beats-p00-p01"></a>71. `memset(p, 0, N)` is an intrinsic that is not value-tracked, so it beats `p[0]=0; p[0]\|=1` | `0x100128f0` |
| <a id="72-a-callee-saved-sentinel-and-a-cse-can-be-one-mechanism-not-two"></a>72. a callee-saved sentinel and a CSE can be one mechanism, not two | `0x100128f0`, `0xffffffff` |
| <a id="72b-a-locally-exact-nesting-fix-can-still-lose-to-the-cascade-it-triggers"></a>72b. a locally exact nesting fix can still lose to the cascade it triggers | `0xffffffff` |
| <a id="73-base--idx0x40--idx-always-folds-to-one-regreg-operand"></a>73. `base + idx*0x40 + idx` always folds to one `[reg+reg]` operand | `0x100174d0` |
| <a id="74-msvc6-folds-byte-identical-early-return-epilogues-unconditionally-the-reference-folds-none"></a>74. msvc6 folds byte-identical early-return epilogues unconditionally; the reference folds none | `0x10016f80`, `0x100170d2` |
| <a id="75-a-prologue-fidelity-lever-and-a-past-climb-win-that-cost-it"></a>75. A prologue-fidelity lever, and a past "climb win" that cost it | `0x10016f80` |
| <a id="76-a-volatile-read-at-a-post-loop-test-blocks-the-loops-entry-guard-fold"></a>76. A `volatile` read at a *post*-loop test blocks the loop's entry-guard fold | `0x10008a90`, `0x10008b0f`, `0x10008c51`, `0x10008c59` |
| <a id="77-group-same-kind-memory-operations-to-match-the-references-store-sequence"></a>77. Group same-kind memory operations to match the reference's store sequence | `0x1000d930`, `0x1000ddc8`, `0x1000de10`, `0x100128f0`, `0x10018850` |
| <a id="78-a-one-token-guard-reorder-can-be-worth-one-linked-byte"></a>78. A one-token guard reorder can be worth one linked byte | `0x10006580`, `0x1000d930`, `0x10018850` |
| <a id="79-position-beats-alignment-repeatedly"></a>79. Position beats alignment, repeatedly | - |
| <a id="80-xor-xor-rmw-beats-xor-then-or-when-the-scheduler-prefers-it"></a>80. xor-xor RMW beats xor-then-or when the scheduler prefers it | `0x10009020` |
| <a id="81-crashdump-frame-rule-every-0x280-path-costs-50-bytes"></a>81. CrashDump frame rule: every 0x280 path costs ~50 bytes | `0x10002770`, `0x1000277d`, `0x1000277e`, `0x1000281d`, `0x1000282c`, `0x1000282d`, `0x10002931`, `0x10002c5c`, `0x10002c87`, `0x10002cb8`, `0x10002cc8`, `0x10002ccd`, `0x10002d5d`, `0x10002dac`, `0x10002dad`, `0x10002e6b`, `0x10002e6e` |
| <a id="82-fimul-needs-an-int-memory-home-and-a-live-st0-supplied-by-two-separate-constructs"></a>82. `fimul` needs an int memory home AND a live ST(0), supplied by two separate constructs | `0x10018850`, `0x10018f4c` |
| <a id="83-a-measurement-pipeline-must-refuse-stale-inputs-or-it-will-report-the-last-good-number"></a>83. A measurement pipeline must refuse stale inputs, or it will report the last good number | - |
| <a id="84-sink-a-values-definition-into-the-guard-that-uses-it-and-let-the-other-region-keep-its-own-register"></a>84. Sink a value's definition into the guard that uses it, and let the other region keep its own register | `0x1000de10`, `0x1000df0a` |
| <a id="85-the-boundary-of-section-84-it-moves-a-values-definition-not-a-constant"></a>85. The boundary of section 84: it moves a value's definition, not a constant | `0x1000ec00`, `0x1000edc0`, `0x10011bf0`, `0x100128f0` |
| <a id="86-a-join-block-is-exiled-when-its-fall-through-predecessor-must-end-in-a-reload--jmp"></a>86. A join block is exiled when its fall-through predecessor must end in a reload + `jmp` | `0x100092bc`, `0x1000d930`, `0x1000df2a`, `0x1000df97`, `0x1000dfc1`, `0x100174d0`, `0x10017530`, `0x10018c23`, `0x10018c28` |
| <a id="86b-store-order-is-a-lever-through-a-fresh-pointer-inert-through-a-stack-buffer"></a>86b. Store order IS a lever through a fresh pointer, inert through a stack buffer | `0x10006580`, `0x100066bc`, `0x100066cb`, `0x1001904d`, `0x10019052`, `0x10019056`, `0x1001905c`, `0x1001906e` |
| <a id="87-audit-a-functions-own-header-notes-before-trusting-them-six-for-six"></a>87. Audit a function's own header notes before trusting them: six for six | `0x1000dd2a`, `0x1000dd33`, `0x100189c4`, `0x100189f4` |
| <a id="88-a-span-deficit-is-code-bytes-plus-alignment-round-up-separate-them-before-hunting"></a>88. A "span deficit" is code bytes plus alignment round-up: separate them before hunting | `0x10006580`, `0x100067d8`, `0x100067da`, `0x100067dd`, `0x100067df`, `0x100067e1`, `0x100067e4` |
| <a id="89-attribute-residue-by-comdat-extent-not-body-size-msvc6-emits-tables-past-the-body"></a>89. Attribute residue by COMDAT extent, not body size: msvc6 emits tables past the body | `0x10009020`, `0x10009056`, `0x100092ba`, `0x100092bb`, `0x100092bc`, `0x100092cf`, `0x100092d0`, `0x100092dc`, `0x100092dd`, `0x100092df` |
| <a id="90-some-compiler-fixed-points-are-service-pack-decisions-sp5-pp-as-an-oracle"></a>90. Some "compiler fixed points" are service-pack decisions: sp5-pp as an oracle | - |
| <a id="91-the-sp5-pp-oracle-applied-to-the-whole-residue-table-14-source-bound-4-scheduler-bound"></a>91. The sp5-pp oracle, applied to the whole residue table: 14 source-bound, 4 scheduler-bound | `0x1000bee6`, `0x1000c01e`, `0x10012b9f`, `0x10012bc4`, `0x100170bb` |
| <a id="92-three-closures-and-the-codegen-facts-they-establish"></a>92. Three closures, and the codegen facts they establish | - |
| <a id="the-image-sweep-is-nine-images-but-only-three-generators"></a>The image sweep is nine IMAGES but only three GENERATORS | - |
| <a id="cm_processcommandqueue-tail-sharing-not-arm-order-and-a-greedy-layout-pass"></a>`cm_ProcessCommandQueue`: tail-sharing, not arm order, and a greedy layout pass | - |
| <a id="gm_objectsavailble-a-downstream-reschedule-can-be-a-renames-shadow"></a>`gm_ObjectsAvailble`: a downstream reschedule can be a rename's shadow | `0x100160d3` |
| <a id="ahm_exallocalchemist-faddp-is-unreachable-from-any-c-expression"></a>`ahm_ExAllocAlchemist`: `faddp` is unreachable from any C expression | `0x1000c034` |
| <a id="93-proven-is-not-a-byte-match-and-the-headline-number-hid-that"></a>93. PROVEN is not a byte match, and the headline number hid that | - |
| <a id="the-117-lint-warnings-were-all-rebrews-own-false-positives-round-193"></a>The 117 lint warnings were all rebrew's own false positives (round 193) | `0x1000d92d`, `0x1000d930`, `0x10012440` |
| <a id="94-volatile-wins-the-alignment-ruler-and-loses-the-link-three-for-three"></a>94. `volatile` wins the alignment ruler and loses the link: three for three | - |
| <a id="95-a-jcc-width-difference-is-a-readout-of-stub-distance-never-a-source-lever"></a>95. A jcc width difference is a readout of stub distance, never a source lever | `0x10016f80` |
| <a id="96-four-rulers-one-object-always-state-which-convention-a-number-used"></a>96. Four rulers, one object: always state which convention a number used | - |
| <a id="97-spec-audit-every-live-__asm-block-is-inside-the-original-used-asm-carve-out"></a>97. Spec audit: every live `__asm` block is inside the "original used asm" carve-out | `0x10006580`, `0x100068e0`, `0x10006d20`, `0x10008e40`, `0x10008f0c`, `0x1000b040`, `0x100174d0` |
| <a id="98-byte-identical-outside-text-means-copied-outside-text"></a>98. "Byte-identical outside `.text`" means *copied* outside `.text` | `0x174059c`, `0x10024040`, `0x404015ff` |
| <a id="99-the-measuring-script-and-the-shipping-pipeline-had-drifted-apart"></a>99. The measuring script and the shipping pipeline had drifted apart | `0x10139820`, `0x117f65b4` |
| <a id="100-data-is-placement-bound-msvc6-puts-every-string-literal-in-its-own-comdat"></a>100. `.data` is placement-bound: MSVC6 puts every string literal in its own COMDAT | `0x10027448` |
| <a id="101-data-placement-was-dominated-by-the-link-order-of-the-length-pad-not-by-comdats"></a>101. `.data` placement was dominated by the link-order of the length pad, not by COMDATs | `0x10027030`, `0x10028940`, `0x1002e4d0`, `0x10030268` |
| <a id="102-fold-priority-only-needs-to-beat-the-first-member-comdat-not-the-whole-link"></a>102. Fold priority only needs to beat the first *member* COMDAT, not the whole link | - |
| <a id="103-rdatas-whole-residue-is-the-import-table-and-the-symbol-order-is-already-correct"></a>103. `.rdata`'s whole residue is the import table, and the symbol order is already correct | `0x025000`, `0x026000`, `0x00026acc`, `0x00026bb2`, `0x029000`, `0x02c000`, `0x031000`, `0x033000`, `0x034000` |
| <a id="104-inlining-is-not-the-residue-call-counts-already-match"></a>104. Inlining is not the residue: call counts already match | `0x10003640`, `0x1000bd50`, `0x1000c600`, `0x100122e0`, `0x10018130`, `0x10018150`, `0x10024008` |
| <a id="the-related-question-does-emitting-missing-data-content-help-text"></a>The related question: does emitting missing `.data` content help `.text`? | - |
| <a id="105-the-ga-flag-sweep-finally-run-and-why-it-says-nothing-new"></a>105. The GA flag sweep, finally run, and why it says nothing new | - |
| <a id="106-the-flag-landscape-is-flat-on-every-walled-row-five-for-five"></a>106. The flag landscape is flat on every walled row: five for five | - |
| <a id="107-the-ga-finds-nothing-either-and-stagnates-immediately"></a>107. The GA finds nothing either, and stagnates immediately | - |
| <a id="108-near-diags-verdict-is-a-different-ruler-reconcile-it-before-believing-it"></a>108. `near-diag`'s verdict is a different ruler: reconcile it before believing it | - |
| <a id="109-gm_allocspielers-first-fault-is-a-scheduler-sink-not-a-statement-order"></a>109. `gm_AllocSpieler`'s first fault is a scheduler sink, not a statement order | `0x10018850`, `0x10018918`, `0x100358a0`, `0x100358fc` |
| <a id="round-216-the-lea-split-is-not-source-reachable-either"></a>Round 216: the `lea` split is not source-reachable either | `0x1001896f`, `0x100358fc` |
| <a id="110-a-deliberate-semantic-bug-is-shipped-in-gm_allocspieler-state-it-plainly"></a>110. A deliberate semantic bug is shipped in `gm_AllocSpieler`: state it plainly | `0x10018cd4`, `0x10018cdb`, `0x10018cde`, `0x10018ce0`, `0x10018ce1`, `0x10018ce9`, `0x10018cec`, `0x1003542c` |
| <a id="round-214-correction-the-size-match-is-an-accident-of-the-bug"></a>Round 214 correction: the size match is an accident of the bug | - |
| <a id="round-215-half-the-deficit-was-the-argument-cast-not-the-store"></a>Round 215: half the deficit was the argument cast, not the store | `0x10018cd4`, `0x10035434` |
| <a id="111-count-calls-by-encoding-not-by-grep-and-what-it-shows-on-crashdumpunhandledexceptionfilter"></a>111. Count calls by ENCODING, not by grep, and what it shows on `CrashDumpUnhandledExceptionFilter` | `0x10002770`, `0x10024010`, `0x10024024`, `0x10024038`, `0x100272f8` |
| <a id="112-the-reference-does-not-cross-jump-identical-cleanup-arms-and-neither-should-we"></a>112. The reference does not cross-jump identical cleanup arms, and neither should we | `0x10002d96`, `0x10002d9f`, `0x10002da6`, `0x10002dc9`, `0x10002dd8`, `0x10002ddf`, `0x10002e02`, `0x10002e0a`, `0x10002e11` |
| <a id="round-219-count-call-sites-per-import-not-adjacent-call-pairs"></a>Round 219: count call sites per IMPORT, not adjacent-call "pairs" | `0x1002400c`, `0x10024010` |
| <a id="round-220-that-rule-is-also-wrong-a-relocation-is-not-a-call"></a>Round 220: that rule is ALSO wrong: a relocation is not a call | `0x10002770`, `0x10002b2a`, `0x10002b7f`, `0x10002b80`, `0x10002bab`, `0x10002c40`, `0x10003640` |
| <a id="113-tree-wide-call-inventory-sweep-exactly-one-row-has-a-real-defect"></a>113. Tree-wide call-inventory sweep: exactly one row has a real defect | - |
| <a id="114-the-last-call-defect-two-switch-tails-the-reference-keeps-and-we-merge"></a>114. The last call defect: two switch tails the reference keeps and we merge | `0x10002b31`, `0x10002b7f`, `0x10002bb2`, `0x10002c22`, `0x10002c40`, `0x10002c51`, `0x10002e9c`, `0x10002f1c`, `0x10027278` |
| <a id="why-the-references-spill-reloads-are-not-a-storage-signal"></a>Why the reference's spill reloads are not a storage signal | `0x10002da6`, `0x10002dac`, `0x10002dad`, `0x10002dae`, `0x10002e66`, `0x10024010` |
| <a id="115-the-sp5-pp-toolchain-axis-finally-measured-a-real-gain-that-cannot-ship"></a>115. The sp5-pp toolchain axis, finally measured: a real gain that cannot ship | `0x10016cd0`, `0x10016de0`, `0x10016ea0`, `0x10016f80` |
| <a id="117-the-two-tails-at-0x10002770-are-a-register-pressure-artefact-not-a-source-shape"></a>117. The two tails at 0x10002770 are a register-pressure artefact, not a source shape | `0x10002931`, `0x10002b7f`, `0x10002c40`, `0x10002c51`, `0x10002c6c`, `0x10027208`, `0x3fffff71`, `0x3fffffdb`, `0x80000003`, `0x80000004`, `0xc0000005`, `0xc0000006`, `0xc000001d`, `0xc0000025`, `0xc0000026`, `0xc000008c`, `0xc000008d`, `0xc000008e`, `0xc000008f`, `0xc0000096`, `0xc00000fd` |
| <a id="116-a-10-win-on-crashdump-hoist-the-stack-walk-setup-to-the-references-computation-point"></a>116. A +10 win on CrashDump: hoist the stack-walk setup to the reference's computation point | `0x10002931`, `0x1000293a` |
| <a id="118-scope-of-the-hoist-lever-when-it-applies-and-where-it-is-already-satisfied"></a>118. Scope of the hoist lever: when it applies, and where it is already satisfied | `0x1000a570`, `0x1000a57c`, `0x1000e140`, `0x10015f70`, `0x101deb00` |
| <a id="the-gm_allocspieler-near-miss-settled-at-the-link"></a>The `gm_AllocSpieler` near-miss, settled at the link | `0x10018990`, `0x100189c4`, `0x100a8c30` |
| <a id="119-linktestsh-already-existed-the-gap-was-that-nobody-was-told"></a>119. `linktest.sh` already existed: the gap was that nobody was told | - |
| <a id="120-two-dead-ends-on-gm_allocspieler-and-a-caution-about-shared-worktree-probing"></a>120. Two dead ends on `gm_AllocSpieler`, and a caution about shared-worktree probing | - |
| <a id="121-cm_exsellobjekts-one-byte-gap-is-a-zero-extension-and-the-cast-is-load-bearing"></a>121. `cm_ExSellObjekt`'s one-byte gap is a zero-extension, and the cast is load-bearing | `0x1000d930`, `0x1000db66`, `0x1000db69`, `0x1000db6f`, `0x1000db70`, `0x1000db71` |
| <a id="122-bounding-a-missing-byte-with-a-jump-displacement"></a>122. Bounding a missing byte with a jump displacement | `0x100128f0`, `0x10012b9f`, `0x10012ba2`, `0x10012ba4`, `0x10012ba5`, `0x10012ba7`, `0x10012ba9`, `0x10012bab` |
| <a id="123-drift_windowspy-localise-a-byte-fault-without-reading-the-bytes"></a>123. `drift_windows.py`: localise a byte fault without reading the bytes | - |
| <a id="124-drift-sweep-across-the-remaining-rows-and-a-build-state-trap"></a>124. Drift sweep across the remaining rows, and a build-state trap | `0x1000ed4d`, `0x1000ed4f`, `0x1000ed56`, `0x1000ed5b`, `0x1000ed5d`, `0x1000ed62`, `0xffffff81` |
| <a id="125-guarding-the-composition-collapse"></a>125. Guarding the composition collapse | - |
| <a id="126-servermainthreads-3-window-a-rematerialised-constant-the-reference-carries-in-a-register"></a>126. `ServerMainThread`'s +3 window: a rematerialised constant the reference carries in a register | `0x100097fb`, `0xffffffff` |
| <a id="127-guarding-the-silent-no-op-and-locating-servermainthreads--2"></a>127. Guarding the silent no-op, and locating `ServerMainThread`'s -2 | `0x10009838`, `0x10009858`, `0x101deae8`, `0xffffffff` |
| <a id="128-drift_windowspy-was-wrong-on-backward-jumps"></a>128. `drift_windows.py` was wrong on backward jumps | - |
| <a id="129-re-sweep-after-the-backward-jump-fix-and-why-the-graveyard-reload-cannot-be-cached"></a>129. Re-sweep after the backward-jump fix, and why the Graveyard reload cannot be cached | `0x10011f27`, `0x10011f2b` |
| <a id="130-the-register-pressure-cascade-is-one-rows-fact-not-the-trees"></a>130. The register-pressure cascade is one row's fact, not the tree's | - |
| <a id="131-the-graveyard-zero-extend-is-closed-four-spellings-none-reaches-xormov-r16"></a>131. The Graveyard zero-extend is closed: four spellings, none reaches `xor`+`mov r16` | `0x10011f27`, `0x10011f2b`, `0x10011f2f` |
| <a id="132-what-surrounds-the-graveyard-read-an-addressing-mode-choice-also-not-source-selectable"></a>132. What surrounds the Graveyard read: an addressing-mode choice, also not source-selectable | `0x10011f2f`, `0x10011f39`, `0x10011f3f`, `0x100a9820`, `0x1014d8e0` |
| <a id="133-the-reg--absolute-pattern-is-common-but-its-cost-is-not"></a>133. The `[reg + absolute]` pattern is common, but its cost is not | - |
| <a id="134-the-zero-extend-gap-is-not-caused-by-addressing-a-controlled-comparison"></a>134. The zero-extend gap is not caused by addressing: a controlled comparison | `0x100190fc`, `0x10019100`, `0x10019104`, `0x1001910e`, `0x1014d8e0` |
| <a id="135-why-the-references-register-is-free-counter-assignment-not-pressure"></a>135. Why the reference's register is free: counter assignment, not pressure | `0x100190e5`, `0x100190ea`, `0x10019104`, `0x10019129`, `0x10019136`, `0x1001913c` |
| <a id="136-a-window-where-we-are-shorter-and-why-that-constrains-the-whole-function"></a>136. A window where we are *shorter*, and why that constrains the whole function | `0x10019013`, `0x1001901a`, `0x10019020`, `0x1001902b` |
| <a id="137-reading-window-signs-across-the-tree-and-a-surplus-with-no-positive-window"></a>137. Reading window signs across the tree, and a surplus with no positive window | - |
| <a id="138-nested-subtraction-automated"></a>138. Nested subtraction, automated | - |
| <a id="139-verification-checkpoint-what-is-actually-true-at-residue-8652"></a>139. Verification checkpoint: what is actually true at residue 8,652 | - |
| <a id="140-srv_loadbuf-49-bytes-zero-length-difference-nine-push-scheduling-clusters"></a>140. `srv_LoadBuf`: 49 bytes, zero length difference, nine push-scheduling clusters | `0x1000a570`, `0x10029a70`, `0xffffff7f` |
| <a id="141-what-8652-bytes-actually-is-15-instructions-of-difference"></a>141. What 8,652 bytes actually is: 15 instructions of difference | - |
| <a id="142-the-sp5-pp-pin-lands-residue-8652---8641"></a>142. The sp5-pp pin lands: residue 8,652 -> 8,641 | `0x10016cd0`, `0x10016de0`, `0x10016ea0`, `0x10016f80` |
| <a id="143-sweeping-the-toolchain-axis-a-second-pin-and-the-limit-of-the-technique"></a>143. Sweeping the toolchain axis: a second pin, and the limit of the technique | - |
| <a id="144-the-complete-toolchain-sweep-and-a-correction"></a>144. The complete toolchain sweep, and a correction | - |
| <a id="145-the-toolchain-sweep-enumerated-from-the-residue-table"></a>145. The toolchain sweep, enumerated from the residue table | - |
| <a id="146-file-splitting-would-unlock-nothing-the-pin-granularity-was-never-the-constraint"></a>146. File splitting would unlock nothing: the pin granularity was never the constraint | - |
| <a id="147-the-flag-landscape-checked-on-a-sixth-row"></a>147. The flag landscape, checked on a sixth row | - |
| <a id="148-the-data-segment-tooling-was-blind-and-what-it-sees-now-round-1-of-the-data-pass"></a>148. The data-segment tooling was blind, and what it sees now (round 1 of the data pass) | - |
| <a id="the-non-text-identity-is-still-copied-measured-again-honestly"></a>The non-`.text` identity is still copied, measured again, honestly | - |
| <a id="data-and-rdata-are-placement-bound-restated-with-current-numbers"></a>`.data` and `.rdata` are placement-bound, restated with current numbers | - |
| <a id="what-the-repaired-tooling-immediately-showed-rebrew-data-layout-audit"></a>What the repaired tooling immediately showed: `rebrew data layout audit` | `0x10027078`, `0x100270e8`, `0x100270f8`, `0x100270fc`, `0x10027314`, `0x10027328`, `0x1002735c`, `0x10028888`, `0x1002c3f0`, `0x10030b6c`, `0x10030b84`, `0x10030b98`, `0x10030b9e`, `0x10031538`, `0x10031aac`, `0x10034624`, `0x10034634`, `0x1003467c`, `0x11766204` |
| <a id="one-more-defect-the-repaired-scan-caught-an-rva-where-a-va-belongs"></a>One more defect the repaired scan caught: an RVA where a VA belongs | `0x00024000`, `0x10024000` |
| <a id="149-per-symbol-data-what-39-wrong-symbols-actually-are-round-2-of-the-data-pass"></a>149. Per-symbol `.data`: what 39 wrong symbols actually are (round 2 of the data pass) | - |
| <a id="rebrew-verify---data-was-comparing-nothing-and-reporting-success"></a>`rebrew verify --data` was comparing nothing, and reporting success | - |
| <a id="the-39-classified"></a>The 39, classified | - |
| <a id="a-real-type-bug-a-correct-fix-and-why-it-was-reverted-anyway"></a>A real type bug, a correct fix, and why it was reverted anyway | `0x10030b84`, `0x10030b94` |
| <a id="two-latent-defects-this-uncovered"></a>Two latent defects this uncovered | - |
| <a id="150-the-first-data-win-a-declared-size-that-was-four-times-too-large-round-3-of-the-data-pass"></a>150. The first `.data` win: a declared size that was four times too large (round 3 of the data pass) | - |
| <a id="read-map-not-the-bytes"></a>Read `/MAP`, not the bytes | `0x10027074`, `0x10027078`, `0x10027084`, `0x100270a4`, `0x100270e4`, `0x100270e8`, `0x10027104`, `0x10027108` |
| <a id="the-bug"></a>The bug | `0x10027084` |
| <a id="why-a-36-byte-fix-pays-231-bytes-when-149s-37-byte-fix-cost-236"></a>Why a 36-byte fix pays 231 bytes, when §149's 37-byte fix cost 236 | `0x10030b84` |
| <a id="what-it-costs-and-the-baseline-that-had-to-move"></a>What it costs, and the baseline that had to move | - |
| <a id="the-gate-could-not-see-data-at-all-fixed"></a>The gate could not see `.data` at all: fixed | - |
| <a id="the-remaining-4-traced-but-not-closed"></a>The remaining −4, traced but not closed | `0x10027030`, `0x10034f1c` |
| <a id="151-a-symbol-defined-twice-8-duplicated-bytes-cost-1350-round-4-of-the-data-pass"></a>151. A symbol defined twice: 8 duplicated bytes cost 1,350 (round 4 of the data pass) | - |
| <a id="the-per-object-delta-spread-is-the-whole-triage"></a>The per-object delta spread is the whole triage | - |
| <a id="the-bug-a-symbol-that-exists-twice"></a>The bug: a symbol that exists twice | `0x10027104`, `0x10027314`, `0x10027328`, `0x1002733c` |
| <a id="8-bytes-removed-1350-recovered-and-why-that-is-not-a-paradox"></a>8 bytes removed, 1,350 recovered: and why that is not a paradox | - |
| <a id="quirk-a-text-byte-that-is-not-codegen"></a>Quirk: a `.text` byte that is not codegen | - |
| <a id="quirk-the-gap-blob-overlaps-40-real-symbols-and-that-is-correct"></a>Quirk: the gap blob overlaps ~40 real symbols, and that is correct | - |
| <a id="152-the-predictor-ask-whether-the-bytes-after-the-edit-want-to-move-round-5-of-the-data-pass"></a>152. The predictor: ask whether the bytes *after* the edit want to move (round 5 of the data pass) | - |
| <a id="the-trap-walked-into-deliberately-and-then-understood"></a>The trap, walked into deliberately and then understood | `0x10002692`, `0x100026C3`, `0x100033F3`, `0x100270f8`, `0x100270fc` |
| <a id="the-measurement-that-would-have-vetoed-it"></a>The measurement that would have vetoed it | `0x10027360`, `0x100273e0` |
| <a id="what-it-found-next-a-global-nothing-defined"></a>What it found next: a global nothing defined | `0x10028938`, `0x1002893c`, `0x100366dc` |
| <a id="quirk-link_stubsc-hides-missing-data-as-successfully-linked-zeros"></a>Quirk: `link_stubs.c` hides missing data as successfully-linked zeros | `0x1002c3f0`, `0x11766204` |
| <a id="153-a-named-array-lands-first-a-literal-lands-last-round-6-of-the-data-pass"></a>153. A named array lands first; a literal lands last (round 6 of the data pass) | - |
| <a id="the-ordering-bug-in-152s-own-fix"></a>The ordering bug in §152's own fix | `0x100288e0`, `0x100288f8`, `0x10028938`, `0x10028940` |
| <a id="five-truncated-stubs-that-duplicated-comdat-literals"></a>Five truncated stubs that duplicated COMDAT literals | `0x10028888`, `0x10028aec`, `0x10028b04`, `0x10028b60`, `0x10028b78` |
| <a id="quirk-the-probes-28-and-a-64-shrink-are-not-a-contradiction"></a>Quirk: the probe's +28 and a −64 shrink are not a contradiction | `0x10028bf0` |
| <a id="text-1-is-placement-again"></a>`.text` +1 is placement again | - |
| <a id="154-data-only-tus-beat-text-ordered-link-for-data-placement-round-7-of-the-data-pass"></a>154. Data-only TUs beat text-ordered link for .data placement (round 7 of the data pass) | `0x10006ec0`, `0x10009d30`, `0x1000ad40`, `0x10028bdc` |
| <a id="the-fix-a-data-only-tu-ordered-between-m_alloc2-and-trees"></a>The fix: a data-only TU ordered between m_alloc2 and trees | `0x10006c00`, `0x10006c80`, `0x10006ec0`, `0x10028bdc`, `0x10029408` |
| <a id="result"></a>Result | `0x10028bdc`, `0x10029408` |
| <a id="quirk-cmake-object-order-is-text-va-not-data-va"></a>Quirk: CMake object order is `.text` VA, not `.data` VA | - |
| <a id="next-miss"></a>Next miss | `0x1002944c` |
| <a id="155-twelve-bytes-of-fopen-mode--gzip-magic-before-the-vfs-path-round-8-of-the-data-pass"></a>155. Twelve bytes of fopen mode + gzip magic before the vfs path (round 8 of the data pass) | `0x1002944c` |
| <a id="the-fix"></a>The fix | - |
| <a id="result-1"></a>Result | `0x1002944c`, `0x100294a0` |
| <a id="next-miss-1"></a>Next miss | `0x100294a4` |
| <a id="156-a-raw-address-cast-emits-no-data-a-named-array-in-the-right-tu-does-round-9-of-the-data-pass"></a>156. A raw address cast emits no data; a named array in the right TU does (round 9 of the data pass) | `0x100294a4` |
| <a id="the-fix-1"></a>The fix | `0x100294a4` |
| <a id="result-2"></a>Result | `0x100294a4`, `0x100294d4` |
| <a id="quirk-raw-address--data"></a>Quirk: raw address ≠ data | - |
| <a id="next-miss-2"></a>Next miss | `0x10024620`, `0x10024f50`, `0x100294d4` |
| <a id="157-explicit-zero-pad-arrays-are-redundant-under-msvc6-4-byte-alignment-round-10-of-the-data-pass"></a>157. Explicit zero-pad arrays are redundant under MSVC6 4-byte alignment (round 10 of the data pass) | `0x10034f00` |
| <a id="the-fix-2"></a>The fix | `0x10028bdc`, `0x10029408` |
| <a id="result-3"></a>Result | `0x10034620`, `0x10034f00`, `0x10034f50` |
| <a id="next-miss-3"></a>Next miss | `0x1002733c`, `0x10027538` |
| <a id="158-named-dword-before-first-string-comdat-round-11-of-the-data-pass"></a>158. Named dword before first string COMDAT (round 11 of the data pass) | `0x10027030`, `0x10027100`, `0x10027104`, `0x10027534`, `0x10027538`, `0xffffffff` |
| <a id="the-fix-3"></a>The fix | `0xffffffff` |
| <a id="result-4"></a>Result | `0x10027030`, `0x1002706c`, `0x10027538` |
| <a id="failed-approaches-do-not-retry-without-new-evidence"></a>Failed approaches (do not retry without new evidence) | - |
| <a id="next-miss-4"></a>Next miss | `0x1002733c` |
| <a id="159-gm_allocspielers-interpolation-loop-the-reference-caches-two-floats-in-locals-round-985"></a>159. `gm_AllocSpieler`'s interpolation loop: the reference caches two floats in locals (round 985) | `0x10018bc8`, `0x10018bcb`, `0x10018bcd`, `0x10018bdd` |
| <a id="163-msvc6-canonicalises-independent-operations-the-order-of-two-independent-statements-is-inert-round-1105"></a>163. msvc6 canonicalises independent operations: the ORDER of two independent statements is inert (round 1105) | `0x10002c5c` |
| <a id="164-msvc6-sinks-a-load-past-an-intervening-store-and-hoists-it-back-when-the-value-is-used-first-round-1106"></a>164. msvc6 SINKS a load past an intervening store, and hoists it back when the value is USED first (round 1106) | `0x1000e21d` |
| <a id="173-a-pointer-comparison-against-a-constant-is-unsigned-an-int-cast-makes-it-jl"></a>173. A pointer comparison against a constant is unsigned; an int cast makes it `jl` | `0x4e7390`, `0x53f8f0`, `0x14d0020`, `0x14d0c20` |
| <a id="165-nan-safe-fcom-vs-fcomp-test-ah5--jp-is-a--not-a-"></a>165. NaN-safe `fcom` vs `fcomp`: `test ah,5 / jp` is a `<`, not a `<=` | `0x4514d0`, `0x6628c8`, `0x6628f8` |
| <a id="174-a-constant-size-struct-assignment-is-rep-movsd-memcpy-of-the-same-size-is-not"></a>174. A constant-size struct assignment is `rep movsd`; `memcpy` of the same size is not | `0x4c5b00`, `0x4c62c0`, `0x4c6360`, `0x4c63f0`, `0x4c6b60`, `0x4ce210`, `0x4ce260` |
| <a id="175-fld-dword-ptr-g--call--with-no-stack-store-is-a-floatint-cast"></a>175. `fld dword ptr [g]` + `call <helper>` with no stack store is a float→int cast | `0x4c54c0`, `0x64d228`, `0x67db50`, `0x67db54` |
| <a id="176-push-imm32-of-a-data-address-is-push-offset-g-not-push-g"></a>176. `push imm32` of a data address is `push offset g`, not `push [g]` | `0x4c5700`, `0x7f4c00` |
| <a id="177-a-destination-struct-with-internal-gaps-spell-the-offsets-not-the-struct"></a>177. A destination struct with internal gaps: spell the offsets, not the struct | `0x4c64b0` |
| <a id="178-locals-whose-only-use-is-an-escaping-pointer-are-dead-store-eliminated-group-them"></a>178. Locals whose only use is an escaping pointer are dead-store-eliminated: group them | `0x403040` |
| <a id="179-esp--n-argument-reads-count-every-push-that-is-still-on-the-stack"></a>179. `[esp + N]` argument reads: count every push that is still on the stack | `0x4f7740`, `0x5b2810`, `0x5b33a0` |
| <a id="180-an-early-int-i--0-puts-the-loop-counter-in-esi-for-i--0--drops-it-to-eax"></a>180. An early `int i = 0;` puts the loop counter in `esi`; `for (i = 0; …)` drops it to `eax` | `0x4029c0`, `0x403200` |
| <a id="181-a-look-ahead-gi-scan-is-the-only-spelling-that-rotates-the-free-slot-loop"></a>181. A look-ahead `g[++i]` scan is the only spelling that rotates the free-slot loop | - |
| <a id="182-k--c--3--0-fuses-into-an-lea-c--k3--k-does-not"></a>182. `K + (c ? 3 : 0)` fuses into an LEA; `c ? K+3 : K` does not | - |
| <a id="183-one-source-for-two-targets-only-data-addresses-need-per-target-markers"></a>183. One source for two targets: only data addresses need per-target markers | `0x4e7150`, `0x4e8d10`, `0x4ea8e0`, `0x4ec660`, `0x517700`, `0x51af00`, `0x53e000`, `0x545d40`, `0x60f188`, `0x68deb8` |
| <a id="184-a-bound-spelled-base--constant-still-encodes-as-one-immediate"></a>184. A bound spelled `base + constant` still encodes as one immediate | `0x4ea560`, `0x770b84`, `0x7d5f84`, `0x7f4ca4`, `0x85a0a4` |
| <a id="185-servermainthreads-transfer-size-packet-dropping-volatile-fixes-the-push-order-and-costs-4-linked-bytes"></a>185. `ServerMainThread`'s transfer-size packet: dropping `volatile` fixes the push order and costs 4 linked bytes | `0x100093a0`, `0x101deac0`, `0xffffffff` |
| <a id="186-gm_allocspieler-has-unreversed-client-twins-the-same-compiler-with-the-processor-pack-code-generator"></a>186. `gm_AllocSpieler` has unreversed client twins: the same compiler with the Processor Pack code generator | `0x507690`, `0x507f63`, `0x50a7e0`, `0x50b0b3`, `0x10018850`, `0x1001911b` |
| <a id="187-a-raw-integer-address-is-not-a-symbol-msvc6-keeps-loads-through-it-across-calls"></a>187. A raw integer address is not a symbol: msvc6 keeps loads through it across calls | `0x10018850`, `0x10035434`, `0x100358a0`, `0x100a8c30` |
| <a id="188-read-a-parameter-load-net-of-the-pushes-still-on-the-stack"></a>188. Read a parameter load net of the pushes still on the stack | `0x10018d2d`, `0x10018d35`, `0x10019572` |
| <a id="189-double-on-one-factor-of-a-float--float-product-decides-which-operand-loads"></a>189. `(double)` on one factor of a `float * float` product decides which operand loads | - |
| <a id="190-in-an-x87-loop-the-order-the-locals-were-initialised-sets-the-evaluation-order"></a>190. In an x87 loop, the order the locals were initialised sets the evaluation order | - |
| <a id="191-a-pointer-local-keeps-an-address-apart-from-the-load-or-store-through-it"></a>191. A pointer local keeps an address apart from the load or store through it | - |
| <a id="192-unsigned-short-for-a-16-bit-draw-one-mask-and-fild-before-the-product"></a>192. `unsigned short` for a 16-bit draw: one mask, and `fild` before the product | - |
| <a id="193-byte-arithmetic-in-a-char-temporary-index-expressions-without-an-index-local"></a>193. Byte arithmetic in a `char` temporary; index expressions without an index local | - |
| <a id="194-table-reads-through-a-symbol-emit-r2disp-a-raw-integer-base-emits-rrdisp"></a>194. Table reads through a symbol emit `[r*2+disp]`; a raw integer base emits `[r+r+disp]` | `0x10030ba5` |
| <a id="195-symbolising-only-some-constants-can-flip-an-unrelated-fpu-arm"></a>195. Symbolising only some constants can flip an unrelated FPU arm | `0x100256b0`, `0x10025714` |
| <a id="196-servermainthread-to-byte-exact-symbols-plain-memory-reads-a-promoted-flag-and-a-while"></a>196. `ServerMainThread` to byte-exact: symbols, plain memory reads, a promoted flag, and a `while` | `0x100093a0`, `0xffffffff` |
| <a id="197-a-fill-loop-is-not-a-memset-the-destination-keeps-its-own-register"></a>197. A fill loop is not a `memset`: the destination keeps its own register | `0x1000bdf0`, `0x1000bef4`, `0x100188fa`, `0x10019455`, `0x100358fc` |
| <a id="198-gm_allocspieler-from-515-to-17-linked-bytes-temporaries-and-variable-identity"></a>198. `gm_AllocSpieler` from 515 to 17 linked bytes: temporaries and variable identity | `0x10018c28`, `0x10018c38` |
| <a id="199-a-two-constant-ternary-of-the-spellings-tried-only-c--a--b-gives-setcc-dec-and-a-b-add-b-with-a-dword-add"></a>199. A two-constant ternary: of the spellings tried, only `c ? A : B` gives `setcc; dec; and A-B; add B` with a dword add | `0x10018bb7`, `0x10019245`, `0x1001928a` |
| <a id="200-carrier-wave-round-1145-the-documented-walls-that-were-source-shapes"></a>200. Carrier wave, round 1145: the documented walls that were source shapes | `0x1000bebb`, `0x1000bf38`, `0x1000d930`, `0x1000dd46`, `0x1000dec7`, `0x1002cd14`, `0x1002cd48`, `0x10035434` |
| <a id="201-gv_exallocgraveyardworker-0x10011bf0-closes-under-plain-o2-the-ow-flag-was-the-wall"></a>201. `gv_ExAllocGraveyardWorker` (0x10011bf0) closes under plain `/O2`: the `/Ow` flag was the wall | `0x10011dd2`, `0x10011df5`, `0x10011dff`, `0x1071f7b3`, `0x10727977` |
| <a id="202-goldtl-near-misses-closed-by-source-shape-processor-pack-client"></a>202. GOLDTL near misses closed by source shape (Processor Pack client) | `0x402090`, `0x41c190`, `0x41f8f0`, `0x43a3f0`, `0x4af050`, `0x4af800`, `0x4afb60`, `0x4c8a30`, `0x4dc5f0`, `0x4ee6d0`, `0x4f0cc0`, `0x4f45b0`, `0x4f58b0`, `0x4fc280`, `0x4fc2e0`, `0x4fc3a0`, `0x4ff080`, `0x5a89a0`, `0x5b1e20`, `0x5b4f70`, `0x5c80f0`, `0x5c8400`, `0x5d63e0`, `0x5dc990`, `0x6628a8`, `0x1015f40`, `0x1016198` |
| <a id="203-a-separate-product-local-preserves-the-field-first-x87-load-with-a-shared-constant"></a>203. A separate product local preserves the field-first x87 load with a shared constant | `0x1000bdf0`, `0x100256b8` |
| <a id="204-extern-float-reads-can-change-scheduling-even-when-the-value-and-width-agree"></a>204. Extern float reads can change scheduling even when the value and width agree | `0x10011bf0`, `0x41400000` |
| <a id="205-recover-a-native-address-operand-without-changing-its-scale-or-access-width"></a>205. Recover a native address operand without changing its scale or access width | `0x1000b4d0`, `0x100151b0`, `0x10017330`, `0x100174d0`, `0x10017fb0`, `0x10029bb8`, `0x10029bc0`, `0x10029bc8`, `0x1002da30`, `0x10030860`, `0x10030b6a`, `0x10035880` |
| <a id="206-an-unused-extern-declaration-can-affect-another-functions-emitted-schedule"></a>206. An unused extern declaration can affect another function's emitted schedule | - |
| <a id="207-inline-pointer-tables-can-cause-a-false-instruction-diff-despite-a-full-byte-match"></a>207. Inline pointer tables can cause a false instruction diff despite a full byte match | - |
| <a id="208-multidimensional-struct-arrays-nest-declarators-in-the-c-ast"></a>208. Multidimensional struct arrays nest declarators in the C AST | - |
| <a id="209-a-masked-call-match-does-not-establish-the-callees-identity"></a>209. A masked call match does not establish the callee's identity | `0x10003b90`, `0x10003bc5`, `0x1001a931`, `0x1001aa6a`, `0x1001b200`, `0x1001eab0` |
| <a id="210-zero-code-crt-aliases-belong-in-library-identity-candidates"></a>210. Zero-code CRT aliases belong in library identity candidates | `0x1002377b` |
| <a id="211-change-the-other-readers-to-literals-when-symbolizing-a-literal-breaks-scheduling"></a>211. Change the other readers to literals when symbolizing a literal breaks scheduling | `0x10018850`, `0x10019720`, `0x100252e8`, `0x100252f4` |
| <a id="212-literal-doubles-can-preserve-memory-operands-and-share-the-stock-crt-pool"></a>212. Literal doubles can preserve memory operands and share the stock CRT pool | `0x1000e9c0`, `0x10011bf0`, `0x10018850`, `0x1001f1d0`, `0x1001f2bb`, `0x10025698`, `0x100257d8`, `0x100260b0`, `0x100260f0` |
| <a id="213-a-pooled-empty-string-can-occupy-writable-bss"></a>213. A pooled empty string can occupy writable BSS | `0x100294d0`, `0x100294d4`, `0x100294d8`, `0x100294dc`, `0x100294f4`, `0x100294f8`, `0x10034620`, `0x117650c8`, `0xc0301080` |
| <a id="214-data-only-selectany-makes-readonly-owners-independently-orderable"></a>214. Data-only `selectany` makes readonly owners independently orderable | `0x100241a0`, `0x1002469c`, `0x10024a04`, `0x10025fc0`, `0x40301040`, `0x40401040`, `0xffff0000` |
| <a id="215-a-shared-initialized-string-can-replace-a-displaced-compiler-pool-without-changing-code"></a>215. A shared initialized string can replace a displaced compiler pool without changing code | `0x1001426e`, `0x10015a7c`, `0x10015b4b`, `0x1002944c`, `0x1002d7b0`, `0xc0300040` |
| <a id="216-unused-named-copies-do-not-replace-the-compilers-live-string-literals"></a>216. Unused named copies do not replace the compiler's live string literals | `0x1002a10c`, `0x1002a140`, `0x1002a168`, `0x1002a19c`, `0xc0300040` |
| <a id="217-a-real-character-array-before-a-static-pointer-restores-shared-version-storage"></a>217. A real character array before a static pointer restores shared version storage | `0x10001346`, `0x100057d4`, `0x10009139`, `0x100091f9`, `0x1002706c`, `0x10027070`, `0x10027074`, `0xc0300040` |
| <a id="218-explicit-zero-selectany-globals-become-independently-orderable-bss-comdats"></a>218. Explicit-zero selectany globals become independently orderable BSS COMDATs | `0x100294dc`, `0x100294f8`, `0x10034610`, `0x10034614`, `0x10034618`, `0x1003461c`, `0x10034620`, `0x10034624`, `0x10034628`, `0x1003462c`, `0x10034630`, `0x10034634`, `0x10034638`, `0x1003463c`, `0x10034640`, `0x10034643`, `0xc0300080`, `0xc0301080` |
| <a id="219-bss_seg-applies-to-tentative-globals-an-explicit-zero-can-bypass-it"></a>219. bss_seg applies to tentative globals; an explicit zero can bypass it | `0x10001000`, `0x10001004`, `0x10001008`, `0x1000100c`, `0xc0300040`, `0xc0300080`, `0xc0301080` |
| <a id="220-a-stock-archive-member-can-retain-private-storage-without-appearing-in-map-owners"></a>220. A stock archive member can retain private storage without appearing in MAP owners | `0x10033bc8`, `0x10033ef8`, `0xc0300040` |
| <a id="221-native-order-rejects-ordinary-initialized-data-as-well-as-ordinary-bss"></a>221. Native ORDER rejects ordinary initialized data as well as ordinary BSS | `0xc0300040` |
| <a id="222-native-build-clocks-change-cls-builtins-and-coff-stamp-preserving-this-full-code-shape"></a>222. Native build clocks change CL's builtins and COFF stamp, preserving this full code shape | `0x60501020`, `0xc0300040` |
| <a id="223-removing-stale-size-comments-and-wrapping-tables-preserves-complete-native-contributions"></a>223. Removing stale size comments and wrapping tables preserves complete native contributions | `0x1000e7d0`, `0x1000eb70`, `0x60501020` |
| <a id="224-five-late-server-globals-become-common-without-changing-their-complete-code"></a>224. Five late server globals become COMMON without changing their complete code | `0x264264`, `0x1585584`, `0x11762e84`, `0x11762e94`, `0x11764084`, `0x11764094`, `0x60501020` |
| <a id="225-splitting-gm_opens-six-zero-definitions-does-not-establish-their-placement"></a>225. Splitting gm_Open's six zero definitions does not establish their placement | `0x10034624`, `0x1003463c`, `0x10034640`, `0x10034670`, `0x10034678`, `0x1003467c`, `0x60501020`, `0xc0301080` |
| <a id="226-eight-real-allocator-globals-form-one-ordinary-32-byte-bss-block"></a>226. Eight real allocator globals form one ordinary 32-byte BSS block | `0x10034624`, `0x10034628`, `0x1003462c`, `0x10034630`, `0x10034634`, `0x10034638`, `0x1003463c`, `0x10034640`, `0x117663a8`, `0x60501020`, `0xc0300080` |
| <a id="227-a-live-common-request-can-select-a-hidden-member-before-its-code-is-discarded"></a>227. A live COMMON request can select a hidden member before its code is discarded | `0x10033bc8`, `0x10034110`, `0xc0300040` |
| <a id="228-data-roots-can-preserve-code-while-moving-alignment-or-move-existing-code-too"></a>228. Data roots can preserve CODE while moving alignment, or move existing CODE too | `0x173f820`, `0x10034034`, `0x1003403c`, `0x100340a0`, `0x100340a8`, `0x10034260`, `0x101dd920`, `0xc0300040`, `0xc0400040` |
| <a id="229-redundant-import-retention-pragmas-do-not-determine-this-winsock-iat"></a>229. Redundant import retention pragmas do not determine this WinSock IAT | - |
| <a id="230-eliminated-function-address-expressions-do-not-seed-vc6-undefined-symbols"></a>230. Eliminated function-address expressions do not seed VC6 undefined symbols | - |
| <a id="231-tentative-globals-have-stable-coff-order-independent-of-their-textual-declaration-order"></a>231. Tentative globals have stable COFF order independent of their textual declaration order | - |
| <a id="232-removing-the-inherited-border-word-preserves-all-four-complete-zlib-functions"></a>232. Removing the inherited border word preserves all four complete zlib functions | `0x1002469c`, `0x100246a0`, `0x40301040`, `0xffff0000` |
| <a id="233-removing-unreferenced-common-placeholders-leaves-the-native-image-unchanged"></a>233. Removing unreferenced COMMON placeholders leaves the native image unchanged | `0x100241a0` |
| <a id="234-an-empty-stock-data-section-still-contributes-native-alignment"></a>234. An empty stock data section still contributes native alignment | `0x10034018`, `0xc0300040`, `0xc0400040`, `0xc0500040` |
| <a id="235-an-unused-stock-duplicate-can-change-the-native-icf-survivor"></a>235. An unused stock duplicate can change the native ICF survivor | `0x1001f855`, `0x1002350a`, `0x10023812`, `0x60101020` |
| <a id="236-a-tentative-pointer-and-an-initialized-pointer-use-different-native-storage"></a>236. A tentative pointer and an initialized pointer use different native storage | `0x173f7e0`, `0x173f800`, `0x10034610`, `0x10035408`, `0x1014c6c4` |
| <a id="237-a-preceding-common-array-can-consume-an-apparent-alignment-gap"></a>237. A preceding COMMON array can consume an apparent alignment gap | `0x173f7f0`, `0x10034614`, `0x10034620`, `0x10034660`, `0x1003466c`, `0x10034680` |
| <a id="238-one-real-common-provider-preserves-storage-sizes-but-changes-physical-order"></a>238. One real COMMON provider preserves storage sizes but changes physical order | `0x173f81c`, `0x10034b00` |
| <a id="239-debug-records-can-change-coff-without-changing-the-runtime-dll"></a>239. Debug records can change COFF without changing the runtime DLL | - |
| <a id="240-live-common-extent-can-change-relocation-reservation-without-changing-code"></a>240. Live COMMON extent can change relocation reservation without changing code | - |
| <a id="241-actual-allocator-commons-can-occupy-the-reference-run-without-moving-bulk-arrays"></a>241. Actual allocator COMMONs can occupy the reference run without moving bulk arrays | `0x173f7d0`, `0x10034620`, `0x10034624`, `0x10034640` |
| <a id="242-pool-root-access-does-not-establish-an-ida-array-extent-a-separate-flag-can-be-common"></a>242. Pool-root access does not establish an IDA array extent; a separate flag can be COMMON | - |
| <a id="243-uninitialized-section-roots-affect-common-placement-and-can-split-data"></a>243. Uninitialized section roots affect COMMON placement and can split `.data` | `0xc0300080` |
| <a id="244-real-game-definitions-can-move-into-native-data-archives-without-changing-their-readers"></a>244. Real game definitions can move into native data archives without changing their readers | `0xc0400080` |
| <a id="245-rva-shaped-raw-words-can-be-instruction-bytes-rather-than-address-operands"></a>245. RVA-shaped raw words can be instruction bytes rather than address operands | `0x10009020`, `0x100093a0`, `0x10012000`, `0x10012440`, `0x10012eb0`, `0x1001321d`, `0x10034684`, `0x10035408` |
| <a id="246-an-import-only-translation-unit-has-no-runtime-contribution"></a>246. An import-only translation unit has no runtime contribution | - |
| <a id="247-the-tools-crt-can-change-import-layout-without-changing-c-contributions"></a>247. The tool's CRT can change import layout without changing C contributions | - |
| <a id="248-link-only-runtime-selection-preserves-every-existing-compiler-input"></a>248. Link-only runtime selection preserves every existing compiler input | - |
| <a id="249-an-int-formal-narrowed-to-a-local-byte-preserves-msvc6-dispatch-code"></a>249. An int formal narrowed to a local byte preserves MSVC6 dispatch code | - |
| <a id="250-live-literals-restore-the-original-pool-and-permit-the-complete-error-tu"></a>250. Live literals restore the original pool and permit the complete Error TU | `0x10027078`, `0x100274a8`, `0x4662de1a` |
| <a id="251-compiler-equivalent-zlib-code-does-not-identify-the-original-producer"></a>251. Compiler-equivalent zlib code does not identify the original producer | - |
| <a id="252-a-shared-source-cohort-can-preserve-server-code-and-conflict-with-gold-ordering"></a>252. A shared-source cohort can preserve server code and conflict with Gold ordering | `0x10010530`, `0x10014ca0` |
| <a id="253-adjacent-compatible-command-cohorts-preserve-code-and-shared-annotation-order"></a>253. Adjacent compatible command cohorts preserve code and shared annotation order | - |
| <a id="254-available-alternate-crt-archives-do-not-supply-the-missing-original-producer"></a>254. Available alternate CRT archives do not supply the missing original producer | - |
| <a id="255-a-real-array-comdat-removes-common-alignment-but-displaces-a-correct-neighbor"></a>255. A real array COMDAT removes COMMON alignment but displaces a correct neighbor | `0x10034658`, `0x10034660`, `0x10034678`, `0x10034680`, `0x10035478`, `0xc0301080` |
| <a id="256-an-indexed-table-load-can-numerically-coincide-with-another-global"></a>256. An indexed table load can numerically coincide with another global | `0x10016420`, `0x1013869c`, `0x1013989c` |
| <a id="257-track-ecx-definitions-before-assigning-a-thiscall-signature"></a>257. Track ECX definitions before assigning a thiscall signature | `0x10006e30`, `0x10006e65`, `0x10008e1d`, `0x10008e1f`, `0x10008e2a`, `0x10008e2f`, `0x1000921a`, `0x1000921b`, `0x10009220`, `0x10009225`, `0x10034670`, `0x10034674`, `0x10034677`, `0x1003467f` |
| <a id="258-preserve-the-stream-handle-when-its-argument-slot-becomes-the-read-count"></a>258. Preserve the stream handle when its argument slot becomes the read count | `0x004013b0`, `0x004013f0` |
| <a id="259-early-pointer-return-and-ordered-copy-setup-recover-the-animation-builder"></a>259. Early pointer return and ordered copy setup recover the animation builder | `0x405970`, `0x00406510`, `0x0040d7f7` |
| <a id="260-compare-operand-order-in-the-task-removal-owner-guard"></a>260. Compare operand order in the task-removal owner guard | `0x004050c0` |
| <a id="261-keep-the-sound-scale-temporary-double-until-its-final-float-store"></a>261. Keep the sound scale temporary double until its final float store | `0x418c80`, `0x4193f0`, `0x5eba10`, `0x662b40` |
| <a id="262-separate-float-distance-assignment-from-the-positional-sound-scale"></a>262. Separate float distance assignment from the positional sound scale | - |
| <a id="263-typed-directinput-prefix-calls-preserve-indexed-vtable-code"></a>263. Typed DirectInput prefix calls preserve indexed-vtable code | - |
| <a id="biased-table-displacement-from-a-zero-based-read-view"></a>Biased table displacement from a zero-based read view | `0x662ba8`, `0x662bf8` |
| <a id="pointer-typed-conditional-crt-tail-wrapper"></a>Pointer-typed conditional CRT tail wrapper | - |
| <a id="additional-unused-crt-prototypes-can-disturb-a-large-server-function"></a>Additional unused CRT prototypes can disturb a large server function | - |
| <a id="typed-table-view-retains-signed-integer-address-iteration"></a>Typed table view retains signed integer address iteration | - |
| <a id="byte-parameter-suppresses-integer-extension-at-the-call-boundary"></a>Byte parameter suppresses integer extension at the call boundary | - |
| <a id="existing-byteconstant-callers-can-share-a-byte-width-prototype"></a>Existing byte/constant callers can share a byte-width prototype | - |
| <a id="random-helper-return-declarations-affect-copies-before-widening-2026-10-04"></a>Random-helper return declarations affect copies before widening (2026-10-04) | `0x4a9000`, `0x4ad1c0`, `0x4faa90` |
| <a id="random-helper-return-width-changes-both-epilogues-2026-10-04"></a>Random-helper return width changes both epilogues (2026-10-04) | - |
| <a id="slot-byte-signedness-changes-equality-promotion-2026-10-04"></a>Slot byte signedness changes equality promotion (2026-10-04) | `0x005be320`, `0x005ca560` |
| <a id="unused-named-variadic-parameter-does-not-establish-a-prototype-2026-10-04"></a>Unused named variadic parameter does not establish a prototype (2026-10-04) | - |
| <a id="empty-helper-knowledge-changes-calls-not-just-register-allocation-2026-10-10"></a>Empty helper knowledge changes calls, not just register allocation (2026-10-10) | - |
| <a id="mode-check-ordering-shares-failure-returns-2026-10-10"></a>Mode-check ordering shares failure returns (2026-10-10) | - |
| <a id="prototype-consolidation-can-change-line-constants-2026-10-11"></a>Prototype consolidation can change line constants (2026-10-11) | - |
| <a id="narrow-helper-formals-control-partial-register-argument-loads-2026-10-11"></a>Narrow helper formals control partial-register argument loads (2026-10-11) | - |
| <a id="prototype-only-headers-preserve-msvc6-translation-unit-context-2026-10-11"></a>Prototype-only headers preserve MSVC6 translation-unit context (2026-10-11) | - |
| <a id="shared-prototype-position-preserves-commutative-integer-register-roles-2026-10-14"></a>Shared prototype position preserves commutative integer register roles (2026-10-14) | - |
| <a id="six-element-array-loops-reduce-to-native-display-counter-address-loops-2026-10-14"></a>Six-element array loops reduce to native display-counter address loops (2026-10-14) | - |
| <a id="typed-scene-draw-data-cleanup-preserves-both-137-byte-bodies-2026-10-15"></a>Typed scene draw-data cleanup preserves both 137-byte bodies (2026-10-15) | - |
| <a id="auxiliary-record-cleanup-shares-one-typed-133-byte-algorithm-2026-10-15"></a>Auxiliary-record cleanup shares one typed 133-byte algorithm (2026-10-15) | - |
| <a id="full-spielc-context-and-allocator-byte-condition-residue-2026-10-15"></a>Full spiel.c context and allocator byte-condition residue (2026-10-15) | `0x500190` |
| <a id="character-model-flag-word-emits-the-native-high-byte-or-2026-10-15"></a>Character model flag word emits the native high-byte OR (2026-10-15) | `0x403070`, `0x40342a`, `0x403880` |
| <a id="a-forwarded-stack-dword-does-not-establish-an-int-parameter-2026-10-15"></a>A forwarded stack DWORD does not establish an int parameter (2026-10-15) | `0x404a00`, `0x418b40`, `0x44c620`, `0x44e1e0`, `0x44e309`, `0x44e32d`, `0x44e4a0`, `0x44f8b0`, `0x44f9d9`, `0x44f9fd` |
| <a id="implicit-final-row-in-a-local-string-matrix-2026-10-16"></a>Implicit final row in a local string matrix (2026-10-16) | - |
| <a id="character-camera-script-exits-and-separation-probe-2026-10-16"></a>Character camera script exits and separation probe (2026-10-16) | `0x402d00`, `0x40ca60`, `0x40d980` |
| <a id="six-participant-event-validator-2026-10-16"></a>Six-participant event validator (2026-10-16) | `0x4daf80`, `0x4dc7d0` |
| <a id="court-decision-source-and-stateful-sum-2026-10-16"></a>Court decision source and stateful sum (2026-10-16) | `0x4dd960`, `0x4df1b0` |
| <a id="goal59-participant-reset-cursor-bias-and-unreachable-runner-test"></a>Goal59: participant-reset cursor bias and unreachable runner test | - |
| <a id="goal60-one-texture-loop-two-native-backends"></a>Goal60: one texture loop, two native backends | - |
| <a id="goal61-typed-periodic-callbacks-without-changing-timer-behavior"></a>Goal61: typed periodic callbacks without changing timer behavior | - |
| <a id="goal62-resolver-output-locals-can-reuse-a-dead-id-argument"></a>Goal62: resolver output locals can reuse a dead ID argument | - |
| <a id="method-registrations-explicit-memcpy-goal66-2026-10-16"></a>Method registration's explicit memcpy (Goal66, 2026-10-16) | - |
| <a id="script-animation-options-ordering-goal67-2026-10-16"></a>Script animation options ordering (Goal67, 2026-10-16) | - |
| <a id="list-search-result-after-the-loop-goal75-2026-10-17"></a>List-search result after the loop (Goal75, 2026-10-17) | `0x423720`, `0x423740`, `0x6323a4` |
| <a id="declared-globals-preserve-cursordialog-scheduling-goal78-2026-10-17"></a>Declared globals preserve cursor/dialog scheduling (Goal78, 2026-10-17) | `0x4113f0`, `0x41cf60` |
| <a id="gui-pool-loads-need-declarations-not-assembly-goal79-2026-10-17"></a>GUI pool loads need declarations, not assembly (Goal79, 2026-10-17) | `0x472640`, `0x472770`, `0x475e30`, `0x475f30` |
| <a id="scene-command-tests-al-and-always-returns-one-goal80-2026-10-17"></a>Scene command tests AL and always returns one (Goal80, 2026-10-17) | `0x40ddf0`, `0x40ed00`, `0x50d6d0`, `0x50d725`, `0x50d730` |
| <a id="vfs-closer-needs-the-named-counter-object-goal81-2026-10-17"></a>VFS closer needs the named counter object (Goal81, 2026-10-17) | `0x430580`, `0x43068f`, `0x522e30`, `0x525b40`, `0x6b7fe4`, `0x10034670` |
| <a id="opaque-stream-boundary-preserves-target-objects-goal82-2026-10-17"></a>Opaque stream boundary preserves target objects (Goal82, 2026-10-17) | `0x41cf55`, `0x41cf60`, `0x522510`, `0x522abe`, `0x522ac0`, `0x524605`, `0x524610` |
| <a id="conditional-com-release-through-an-inline-helper"></a>Conditional COM release through an inline helper | `0x460e40`, `0x460e9a` |
| <a id="tail-wrapper-contracts-before-instruction-scheduling-searches"></a>Tail wrapper contracts before instruction-scheduling searches | `0x4c24c0` |

</details>
