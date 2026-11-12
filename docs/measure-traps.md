# What a measurement proves

Choose the artifact that decides the claim. Keep the compile inputs, native extent,
operand bindings and receipt together. Current status belongs in managed metadata,
not a copied score table.

| Evidence | Establishes | Does not establish |
| --- | --- | --- |
| Complete native CFG/data-flow review | The reviewed semantics and contracts | Original C spelling or byte identity |
| Complete object EXACT | Object bytes agree | Linked placement or full image identity |
| Object RELOC | Agreement under the applied relocation policy | Correct unresolved operands or selected providers |
| Bounded semantic proof/fixtures | Agreement under modeled inputs, calls and bounds | Unmodeled runtime behavior or byte identity |
| Raw linked EXACT | Function bytes at the native VA agree | Every other function/data record agrees |
| Whole-file comparison | Complete file bytes agree | Original source ownership or C recovery |
| Layout/data metadata | Recorded extents, roles and ownership evidence | New allocations or verified bytes |

## Comparison scope

Use the complete native function, including all reachable blocks and embedded
switch data. Separate following alignment only with boundary evidence. A matching
prefix or first-return scan can omit later cases, callbacks or cleanup.

Compare exact operands and literal payloads. Relocation masking, structural scores
and matching symbol names can hide the wrong target. Resolve each module/VA
identity; a shared spelling does not make two definitions interchangeable.

Different file sizes count as differences. A same-offset score can fall when
artificial filler or copied data is removed; that is not a reason to restore them.
A residue count is not a count of independent semantic errors.

## Stack arithmetic

Resolve ESP-relative addresses with every pending push and stack adjustment at
that instruction. [Register allocation](msvc6-allocator.md#stack-slots) covers
stack-slot tracking.

## x87 conditions

FCOM/FCOMP encode the comparison bits in `AH & 0x45`: greater=`0x00`, less=`0x01`,
equal=`0x40`, unordered=`0x45`. PF reports even parity of the masked byte.

| Idiom | Branch taken for |
| --- | --- |
| TEST AH,0x05; JP | Greater, equal, unordered |
| TEST AH,0x44; JP | Greater, less, unordered |
| AND AX,0x4100; JNE | Less, equal, unordered |

Trace ST0/ST1 order, pops and branch destinations separately. Memory operand widths do not
prove intermediate rounding or a source type. Signed zero and unordered values
can distinguish expressions that agree on ordinary inputs.

## Failures and freshness

A timeout, stale context, failed build or missing receipt supplies no byte verdict.
Cached results require current source/header/compiler/binary and binding inputs.
`verify --no-cache` bypasses verdict caching, not necessarily object caching.
An unchanged byte result does not validate a changed native identity or provider.

Write corrections as new provenance entries. Do not overwrite a failed receipt or
restore a verdict merely to recover an aggregate count.

## Archived techniques

Original notebook: `docs/measure-traps.md` in the [documentation archive](goal-history.md#full-notebooks).

- Measurement traps
- Index
- Recent findings
- Diagnostic compilers can change floating-point observations (2026-10-14) (`0x005722ef`, `0x0066419c`, `0x3fa66666`)
- A literal-value change can retain function RELOC (2026-10-14) (`0x004b6b10`, `0x005eb8a8`)
- Actual compiler fixtures need input and boundary controls (2026-10-14) (`0x0041e1d0`, `0x00422a20`, `0x00499a50`)
- 1. Use the artifact that decides the claim
- 2. One candidate, one full rebuild, one number
- 3. Relocation accounting makes the object metrics lie about what is left
- 4. A residue number is not the size of the error
- 5. Tool traps that produced wrong readings
- 6. Three audit shapes that generate only false positives (`0x1000c6a0`, `0x1000fc9c`, `0x1000fe76`, `0x1000fe86`, `0x1000fe8a`, `0x1000fea0`, `0x10015542`, `0x1001700f`, `0x10017130`, `0x1001ad4b`, `0x1001cfd2`, `0x10031aac`, `0x10031ab0`, `0x10031ad0`, `0x10031ae0`, `0x10031af0`, `0x10031b6c`, `0x10035448`, `0x10035449`, `0x100358a0`, `0x10035a04`, `0x10035a05`, `0x11766560`, `0x11766564`)
- 6b. `function_structure.json` sizes are 16-byte-padded; the toml's are real (round 866)
- 6c. Object size can move toward the target while the link moves away (round 868) (`0x10016f80`)
- 6d. 28 objects are over the composition budget, and that is what makes source edits collapse (round 870) (`0x10006ec0`, `0x10008800`)
- 6e. `cflags` in the metadata can crash the compiler on a CMake-flag-pinned file (round 877) (`0x100128f0`)
- 6f. A dropped per-file flag produces a normal-looking measurement (rounds 879-880)
- 6f-bis. `COMPILE_OPTIONS` REPLACES a source's option list: adding a flag can silently drop a pin (round 942)
- 6f-ter. `/Oy` is a prefix of `/Oy-`: a flag grep with plain substring matching reads the opposite (round 944)
- 6f-quater. A real definition beats a COFF COMMON silently: the `LNK4006` rule cannot see it (round 945)
- 6f-quinquies. "Defined in two objects" is normal C, not a defect list (round 946)
- 6f-sexies. `object_span_check.py`'s one "OVER" result is an artifact of untracked functions (round 949) (`0x1001d036`, `0x1001d097`)
- 6g. Two ways a whole-image instruction census lies, and both look like a finding (round 923) (`0x3aeffe89`)
- 7. The size rule has two branches, and mixing them discards good work
- 8. probe-span vs test-real: two rulers, one truth
- 9. Build and verify side effects that burn
- 10. How to check any claim in this document
- 6h. An "undefined symbol" in this tree usually is not one: check `link_stubs.c` first (round 924) (`0x1002cc8c`, `0x10031004`, `0x11766604`)
- 11. A stale operand can be a *consequence*, not a cause: read the fixer before chasing it (round 932) (`0x101de450`, `0x11766664`)
- 12. After a flag change, the CMake *objects* are stale even when `split_poc` is not (round 941)
- 13. A positional comparator cannot classify a divergence (rounds 927, 955, 963)
- 14. An apparent missing instruction can be a compiler-proved-dead block (round 963)
- 15. `[esp+N]` is not comparable between two images without normalising esp depth (round 969) (`0x1000d986`, `0x1000d993`)
- 16. Compare branch TARGETS, not instructions, when a loop diverges (rounds 970-971) (`0x10011cdb`, `0x10011d77`)
- 17. A postlink failure was not a healthy tree (round 976)
- 18. A raw dword scan and a disassembler op_str scan disagree: neither alone is proof of absence (round 977) (`0x10014239`, `0x10015d82`, `0x10015d89`, `0x10015f2e`, `0x10035450`, `0x100a8c30`)
- 19. `rebrew todo`'s ROI score is flat across `start-data`, so its ordering carries no signal (round 977) (`0x10024000`)
- 20. A copied-data ceiling is not acceptance (round 980)
- 21. Disassembling `.text` from its start gives wrong instruction boundaries: every statistic built on it is junk (round 988)
- 22. `object_span_check.py` reads CMake's object, but `linktest.sh` recompiles elsewhere (round 989)
- 23. Counting instructions from the shipped image measures postlink's output, not the object (round 990) (`0x10018850`)
- 24. Instruction counts across two images are not comparable: the decoder's stop rule decides the answer (round 991) (`0x10002e9c`, `0x100196b8`, `0xfe811004`)
- 25. `instr_diff.py`'s default `--built` reads the postlink composition, not the object (round 1000) (`0x10002770`, `0x1000aac0`, `0x1000e140`, `0x100128f0`)
- 26. `spiel622.c` holds 16 functions in one object: a per-function span reader must pick the right COMDAT (round 1001) (`0x10019720`, `0x100198b0`)
- 27. `branch_census.py`'s "targetdiff" counts polarity swaps and ±1 drift as structural difference (round 1005) (`0x100097c5`, `0x100098e3`, `0x100098e5`, `0x100098e7`, `0x100098e9`, `0x10009919`, `0x1000991a`)
- 28. How NOT to compare two control-flow graphs: five rejected formulations (round 1006) (`0x100098e3`)
- 29. Round 1006's CFG verdict was wrong; the coarse canonical form could not see it (round 1007) (`0x100098e3`)
- 30. Validating a CFG against the linear decode before trusting its verdicts (round 1008) (`0x100196b9`)
- 31. Exact isomorphism over ADDRESSES answers the wrong question: establish correspondence first (round 1012) (`0x100097c5`, `0x100098e3`, `0x100098e5`, `0x100098e7`, `0x100098e9`, `0x10009919`, `0x1000991a`)
- 32. An ordinal correspondence is only valid when the two streams have equal length (round 1013)
- 33. A raw-link `.data` diff attributed to a GAME TU is still displacement, not wrong content (round 1015) (`0x10029d00`, `0x10029d9c`)
- 34. Both decoders reaching the span end proves there is no hidden slack (round 1017) (`0x100196b8`, `0x100196c0`)
- 35. The shipped `.text` reads byte-perfect wherever postlink rewrote the operands (round 1022)
- 36. A carrier's VA is not guessable from its neighbours: resolve it from the annotation (round 1025) (`0x1000d8a0`, `0x1000d930`, `0x10011bf0`, `0x10011c00`, `0x10019e60`, `0x10019e80`)
- 37. The graded residue and the raw-link residue form a clean partition: 8628 + 5081, zero overlap (round 1026) (`0x10015f80`, `0x10016f80`, `0x10016f86`, `0x10016f8a`, `0x1014d8c0`, `0x11766ae8`)
- 38. The residue's displacement profile is measurable, and most carriers ARE a single cliff (round 1031)
- 39. "One displacement run" does not mean "one shifted byte": check context presence too (round 1032)
- 40. A carrier has TWO first divergences: the raw link's and the shipped file's (round 1033) (`0x10035434`, `0x117665e4`)
- 41. A call-target multiset comparison inherits every desync, and a shifted stream invents wrong callees (round 1035) (`0x10003640`, `0x100122e0`, `0x1001a299`, `0x1001b0c0`, `0x1002387d`)
- 42. "Compare the data operands" gives 0, 707 or 9,855 depending on the offset filter (round 1036) (`0x10024000`, `0x1009aca0`, `0x1009aca2`, `0x1009b762`, `0x10139820`, `0x11768000`)
- 43. A header records *history*, so a claim-extraction regex finds rejected variants, not current state (round 1042)
- 44. Byte-level displacement tests and instruction-level ones answer different questions (round 1047)
- 45. `difflib.SequenceMatcher` reports 100% equal on streams that differ at instruction 21 (round 1048) (`0x1000aac0`, `0x1000ab38`, `0x1000ad08`)
- 46. The residue is 100.00% instruction-aligned: every differing byte lies inside a reference instruction (round 1072)
- 47. The residue table silently hid every carrier under 9 bytes: 18 rows summing to 8623 against a 8628 total (round 1073) (`0x1000aaf7`)
- 48. Audited every table and counter the project quotes against its own arithmetic: all reconcile (round 1074)
- 49. Auditing docs for "missing evidence" by regex measures word choice, not evidence (round 1075)
- 50. The per-carrier table is stable across a full object rebuild, and the deliverable is bit-identical (round 1076)
- 51. A "0 mismatched" data verdict measured 37% of the metadata, and said nothing about it (round 1078) (`0x10035000`)
- 52. Decoding a function by its INVENTORY SPAN swallows inter-function padding and fabricates instructions (round 1084) (`0x10002770`, `0x10002aaf`, `0x10002f4c`, `0x10002f4e`, `0x10002fc0`, `0x100272b4`)
- 53. The raw link is the wrong artifact for a `.data`-addressed operand comparison (round 1086)
- 54. A whole-section idiom census cannot use the raw link's `.text`, and cannot compare rates at all (round 1088)
- 55. `postlink_residual.py` measures the raw link, so a stale composition reports a fake residue of 81,229 (round 1101)
- 56. `verify --data --built <raw link>` rewrites VERIFIED statuses to DRIFT in the tool-owned toml (round 1102)
- 57. A relative include deeper than the tool's staging depth compiles unpacked, silently (round 1103)
- 58. A lower byte count from a spelling that changes a stored value (`0x10018c28`, `0x7fffffff`)
- Pair-copy byte score hides an overlapping-buffer mismatch (2026-10-04) (`0x00407760`)
- Explicit donor identity does not remove inventory-span noise (2026-10-04)
- Indexed displacement can be a biased base in unrelated data (2026-10-04)
- Stock-body membership does not select a unique CRT member
- Comparison width resolves the case-conversion tie
- COFF zero-filled literal sections need semantic bytes
- Resolving an unknown callee changes mismatch scores without changing code (2026-10-04)
- A trailing NOP can hide a wrong cross-target call binding (`0x005b1b10`, `0x005b1eb0`, `0x006628a0`, `0x00774a78`)
- Undefined external string labels need complete payload proof
- Compiler-local label counters are not relocation identity (2026-10-04)
- Padding scores, donor gaps and the installed CLI (2026-10-10) (`0x00405970`, `0x00406510`)
- A source rename can leave a live linker anchor (2026-10-11)
- A shared import verdict can carry the wrong identity or inputs (2026-10-11)
- Retire a shared source only after its last owner moves (2026-10-11)
- Discovery overlap can hide an already-correct source extent (2026-10-15)
- Immediate callback stores were missing from upstream xrefs (2026-10-15) (`0x0050d350`, `0x005107f0`)
- A probe object name can be a Windows device name (2026-10-15)
- Keep rotation's executable extent separate from alignment (2026-10-15)
- Inspect each target's fixed bytes before a shared drift point (2026-10-15)
- A masked diff can conceal an ambiguous call binding (2026-10-15) (`0x004297c0`, `0x005012b0`, `0x005392a0`)
- Registration, extents and type counts are separate measurements (2026-10-16)
- Native cutscene allocation failure rejoins a pointer read (Goal67)
- A matching loop prefix omitted COM shutdown (Goal76, 2026-10-17) (`0x00422d90`, `0x00422db6`, `0x00422dc0`, `0x0046bc60`, `0x005de8c0`, `0x005eb36c`, `0x00f8f080`)
- Copied assembly hid a fifth dialog argument (Goal77, 2026-10-17) (`0x0041c830`, `0x0041cf60`, `0x0041d0d8`, `0x00435f13`)
