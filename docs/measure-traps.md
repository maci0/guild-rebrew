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

Resolve ESP-relative addresses with the pushes still pending at that instruction.
Keep decimal and hexadecimal arithmetic explicit. At GoldTL `0x004fdfe0`, let B
be ESP before five pending pushes. They subtract 20 decimal bytes, or `0x14`.
The later displacement `0x2c` reaches `B - 0x14 + 0x2c = B + 0x18`, the original
buffer.

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

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

Original notebook: `docs/measure-traps.md` in the [documentation archive](goal-history.md#full-notebooks).

| Historical section | Referenced hex values |
| --- | --- |
| <a id="measurement-traps"></a>Measurement traps | - |
| <a id="index"></a>Index | - |
| <a id="recent-findings"></a>Recent findings | - |
| <a id="diagnostic-compilers-can-change-floating-point-observations-2026-10-14"></a>Diagnostic compilers can change floating-point observations (2026-10-14) | `0x005722ef`, `0x0066419c`, `0x3fa66666` |
| <a id="a-literal-value-change-can-retain-function-reloc-2026-10-14"></a>A literal-value change can retain function RELOC (2026-10-14) | `0x004b6b10`, `0x005eb8a8` |
| <a id="actual-compiler-fixtures-need-input-and-boundary-controls-2026-10-14"></a><a id="1-only-the-linked-residue-decides"></a>Actual compiler fixtures need input and boundary controls (2026-10-14) | `0x0041e1d0`, `0x00422a20`, `0x00499a50` |
| <a id="1-use-the-artifact-that-decides-the-claim"></a>1. Use the artifact that decides the claim | - |
| <a id="2-one-candidate-one-full-rebuild-one-number"></a>2. One candidate, one full rebuild, one number | - |
| <a id="3-relocation-accounting-makes-the-object-metrics-lie-about-what-is-left"></a>3. Relocation accounting makes the object metrics lie about what is left | - |
| <a id="4-a-residue-number-is-not-the-size-of-the-error"></a>4. A residue number is not the size of the error | - |
| <a id="5-tool-traps-that-produced-wrong-readings"></a>5. Tool traps that produced wrong readings | - |
| <a id="6-three-audit-shapes-that-generate-only-false-positives"></a>6. Three audit shapes that generate only false positives | `0x1000c6a0`, `0x1000fc9c`, `0x1000fe76`, `0x1000fe86`, `0x1000fe8a`, `0x1000fea0`, `0x10015542`, `0x1001700f`, `0x10017130`, `0x1001ad4b`, `0x1001cfd2`, `0x10031aac`, `0x10031ab0`, `0x10031ad0`, `0x10031ae0`, `0x10031af0`, `0x10031b6c`, `0x10035448`, `0x10035449`, `0x100358a0`, `0x10035a04`, `0x10035a05`, `0x11766560`, `0x11766564` |
| <a id="6b-function_structurejson-sizes-are-16-byte-padded-the-tomls-are-real-round-866"></a>6b. `function_structure.json` sizes are 16-byte-padded; the toml's are real (round 866) | - |
| <a id="6c-object-size-can-move-toward-the-target-while-the-link-moves-away-round-868"></a>6c. Object size can move toward the target while the link moves away (round 868) | `0x10016f80` |
| <a id="6d-28-objects-are-over-the-composition-budget-and-that-is-what-makes-source-edits-collapse-round-870"></a>6d. 28 objects are over the composition budget, and that is what makes source edits collapse (round 870) | `0x10006ec0`, `0x10008800` |
| <a id="6e-cflags-in-the-metadata-can-crash-the-compiler-on-a-cmake-flag-pinned-file-round-877"></a>6e. `cflags` in the metadata can crash the compiler on a CMake-flag-pinned file (round 877) | `0x100128f0` |
| <a id="6f-a-dropped-per-file-flag-produces-a-normal-looking-measurement-rounds-879-880"></a>6f. A dropped per-file flag produces a normal-looking measurement (rounds 879-880) | - |
| <a id="6f-bis-compile_options-replaces-a-sources-option-list-adding-a-flag-can-silently-drop-a-pin-round-942"></a>6f-bis. `COMPILE_OPTIONS` REPLACES a source's option list: adding a flag can silently drop a pin (round 942) | - |
| <a id="6f-ter-oy-is-a-prefix-of-oy--a-flag-grep-with-plain-substring-matching-reads-the-opposite-round-944"></a>6f-ter. `/Oy` is a prefix of `/Oy-`: a flag grep with plain substring matching reads the opposite (round 944) | - |
| <a id="6f-quater-a-real-definition-beats-a-coff-common-silently-the-lnk4006-rule-cannot-see-it-round-945"></a>6f-quater. A real definition beats a COFF COMMON silently: the `LNK4006` rule cannot see it (round 945) | - |
| <a id="6f-quinquies-defined-in-two-objects-is-normal-c-not-a-defect-list-round-946"></a>6f-quinquies. "Defined in two objects" is normal C, not a defect list (round 946) | - |
| <a id="6f-sexies-object_span_checkpys-one-over-result-is-an-artifact-of-untracked-functions-round-949"></a>6f-sexies. `object_span_check.py`'s one "OVER" result is an artifact of untracked functions (round 949) | `0x1001d036`, `0x1001d097` |
| <a id="6g-two-ways-a-whole-image-instruction-census-lies-and-both-look-like-a-finding-round-923"></a>6g. Two ways a whole-image instruction census lies, and both look like a finding (round 923) | `0x3aeffe89` |
| <a id="7-the-size-rule-has-two-branches-and-mixing-them-discards-good-work"></a>7. The size rule has two branches, and mixing them discards good work | - |
| <a id="8-probe-span-vs-test-real-two-rulers-one-truth"></a>8. probe-span vs test-real: two rulers, one truth | - |
| <a id="9-build-and-verify-side-effects-that-burn"></a>9. Build and verify side effects that burn | - |
| <a id="10-how-to-check-any-claim-in-this-document"></a>10. How to check any claim in this document | - |
| <a id="6h-an-undefined-symbol-in-this-tree-usually-is-not-one-check-link_stubsc-first-round-924"></a>6h. An "undefined symbol" in this tree usually is not one: check `link_stubs.c` first (round 924) | `0x1002cc8c`, `0x10031004`, `0x11766604` |
| <a id="11-a-stale-operand-can-be-a-consequence-not-a-cause-read-the-fixer-before-chasing-it-round-932"></a>11. A stale operand can be a *consequence*, not a cause: read the fixer before chasing it (round 932) | `0x101de450`, `0x11766664` |
| <a id="12-after-a-flag-change-the-cmake-objects-are-stale-even-when-split_poc-is-not-round-941"></a>12. After a flag change, the CMake *objects* are stale even when `split_poc` is not (round 941) | - |
| <a id="13-a-positional-comparator-cannot-classify-a-divergence-rounds-927-955-963"></a>13. A positional comparator cannot classify a divergence (rounds 927, 955, 963) | - |
| <a id="14-an-apparent-missing-instruction-can-be-a-compiler-proved-dead-block-round-963"></a>14. An apparent missing instruction can be a compiler-proved-dead block (round 963) | - |
| <a id="15-espn-is-not-comparable-between-two-images-without-normalising-esp-depth-round-969"></a>15. `[esp+N]` is not comparable between two images without normalising esp depth (round 969) | `0x1000d986`, `0x1000d993` |
| <a id="16-compare-branch-targets-not-instructions-when-a-loop-diverges-rounds-970-971"></a><a id="17-cmake---build-build-failing-at-postlink-is-the-designed-state-not-a-broken-tree-round-976"></a>16. Compare branch TARGETS, not instructions, when a loop diverges (rounds 970-971) | `0x10011cdb`, `0x10011d77` |
| <a id="17-a-postlink-failure-was-not-a-healthy-tree-round-976"></a>17. A postlink failure was not a healthy tree (round 976) | - |
| <a id="18-a-raw-dword-scan-and-a-disassembler-op_str-scan-disagree-neither-alone-is-proof-of-absence-round-977"></a>18. A raw dword scan and a disassembler op_str scan disagree: neither alone is proof of absence (round 977) | `0x10014239`, `0x10015d82`, `0x10015d89`, `0x10015f2e`, `0x10035450`, `0x100a8c30` |
| <a id="19-rebrew-todos-roi-score-is-flat-across-start-data-so-its-ordering-carries-no-signal-round-977"></a><a id="20-raw-link-data-is-a-size-only-filler-and-cannot-reach-zero-the-ceiling-is-the-right-check-round-980"></a>19. `rebrew todo`'s ROI score is flat across `start-data`, so its ordering carries no signal (round 977) | `0x10024000` |
| <a id="20-a-copied-data-ceiling-is-not-acceptance-round-980"></a>20. A copied-data ceiling is not acceptance (round 980) | - |
| <a id="21-disassembling-text-from-its-start-gives-wrong-instruction-boundaries-every-statistic-built-on-it-is-junk-round-988"></a>21. Disassembling `.text` from its start gives wrong instruction boundaries: every statistic built on it is junk (round 988) | - |
| <a id="22-object_span_checkpy-reads-cmakes-object-but-linktestsh-recompiles-elsewhere-round-989"></a>22. `object_span_check.py` reads CMake's object, but `linktest.sh` recompiles elsewhere (round 989) | - |
| <a id="23-counting-instructions-from-the-shipped-image-measures-postlinks-output-not-the-object-round-990"></a>23. Counting instructions from the shipped image measures postlink's output, not the object (round 990) | `0x10018850` |
| <a id="24-instruction-counts-across-two-images-are-not-comparable-the-decoders-stop-rule-decides-the-answer-round-991"></a>24. Instruction counts across two images are not comparable: the decoder's stop rule decides the answer (round 991) | `0x10002e9c`, `0x100196b8`, `0xfe811004` |
| <a id="25-instr_diffpys-default---built-reads-the-postlink-composition-not-the-object-round-1000"></a>25. `instr_diff.py`'s default `--built` reads the postlink composition, not the object (round 1000) | `0x10002770`, `0x1000aac0`, `0x1000e140`, `0x100128f0` |
| <a id="26-spiel622c-holds-16-functions-in-one-object-a-per-function-span-reader-must-pick-the-right-comdat-round-1001"></a>26. `spiel622.c` holds 16 functions in one object: a per-function span reader must pick the right COMDAT (round 1001) | `0x10019720`, `0x100198b0` |
| <a id="27-branch_censuspys-targetdiff-counts-polarity-swaps-and-1-drift-as-structural-difference-round-1005"></a>27. `branch_census.py`'s "targetdiff" counts polarity swaps and ±1 drift as structural difference (round 1005) | `0x100097c5`, `0x100098e3`, `0x100098e5`, `0x100098e7`, `0x100098e9`, `0x10009919`, `0x1000991a` |
| <a id="28-how-not-to-compare-two-control-flow-graphs-five-rejected-formulations-round-1006"></a>28. How NOT to compare two control-flow graphs: five rejected formulations (round 1006) | `0x100098e3` |
| <a id="29-round-1006s-cfg-verdict-was-wrong-the-coarse-canonical-form-could-not-see-it-round-1007"></a>29. Round 1006's CFG verdict was wrong; the coarse canonical form could not see it (round 1007) | `0x100098e3` |
| <a id="30-validating-a-cfg-against-the-linear-decode-before-trusting-its-verdicts-round-1008"></a>30. Validating a CFG against the linear decode before trusting its verdicts (round 1008) | `0x100196b9` |
| <a id="31-exact-isomorphism-over-addresses-answers-the-wrong-question-establish-correspondence-first-round-1012"></a>31. Exact isomorphism over ADDRESSES answers the wrong question: establish correspondence first (round 1012) | `0x100097c5`, `0x100098e3`, `0x100098e5`, `0x100098e7`, `0x100098e9`, `0x10009919`, `0x1000991a` |
| <a id="32-an-ordinal-correspondence-is-only-valid-when-the-two-streams-have-equal-length-round-1013"></a>32. An ordinal correspondence is only valid when the two streams have equal length (round 1013) | - |
| <a id="33-a-raw-link-data-diff-attributed-to-a-game-tu-is-still-displacement-not-wrong-content-round-1015"></a>33. A raw-link `.data` diff attributed to a GAME TU is still displacement, not wrong content (round 1015) | `0x10029d00`, `0x10029d9c` |
| <a id="34-both-decoders-reaching-the-span-end-proves-there-is-no-hidden-slack-round-1017"></a>34. Both decoders reaching the span end proves there is no hidden slack (round 1017) | `0x100196b8`, `0x100196c0` |
| <a id="35-the-shipped-text-reads-byte-perfect-wherever-postlink-rewrote-the-operands-round-1022"></a>35. The shipped `.text` reads byte-perfect wherever postlink rewrote the operands (round 1022) | - |
| <a id="36-a-carriers-va-is-not-guessable-from-its-neighbours-resolve-it-from-the-annotation-round-1025"></a>36. A carrier's VA is not guessable from its neighbours: resolve it from the annotation (round 1025) | `0x1000d8a0`, `0x1000d930`, `0x10011bf0`, `0x10011c00`, `0x10019e60`, `0x10019e80` |
| <a id="37-the-graded-residue-and-the-raw-link-residue-form-a-clean-partition-8628--5081-zero-overlap-round-1026"></a>37. The graded residue and the raw-link residue form a clean partition: 8628 + 5081, zero overlap (round 1026) | `0x10015f80`, `0x10016f80`, `0x10016f86`, `0x10016f8a`, `0x1014d8c0`, `0x11766ae8` |
| <a id="38-the-residues-displacement-profile-is-measurable-and-most-carriers-are-a-single-cliff-round-1031"></a>38. The residue's displacement profile is measurable, and most carriers ARE a single cliff (round 1031) | - |
| <a id="39-one-displacement-run-does-not-mean-one-shifted-byte-check-context-presence-too-round-1032"></a>39. "One displacement run" does not mean "one shifted byte": check context presence too (round 1032) | - |
| <a id="40-a-carrier-has-two-first-divergences-the-raw-links-and-the-shipped-files-round-1033"></a>40. A carrier has TWO first divergences: the raw link's and the shipped file's (round 1033) | `0x10035434`, `0x117665e4` |
| <a id="41-a-call-target-multiset-comparison-inherits-every-desync-and-a-shifted-stream-invents-wrong-callees-round-1035"></a>41. A call-target multiset comparison inherits every desync, and a shifted stream invents wrong callees (round 1035) | `0x10003640`, `0x100122e0`, `0x1001a299`, `0x1001b0c0`, `0x1002387d` |
| <a id="42-compare-the-data-operands-gives-0-707-or-9855-depending-on-the-offset-filter-round-1036"></a>42. "Compare the data operands" gives 0, 707 or 9,855 depending on the offset filter (round 1036) | `0x10024000`, `0x1009aca0`, `0x1009aca2`, `0x1009b762`, `0x10139820`, `0x11768000` |
| <a id="43-a-header-records-history-so-a-claim-extraction-regex-finds-rejected-variants-not-current-state-round-1042"></a>43. A header records *history*, so a claim-extraction regex finds rejected variants, not current state (round 1042) | - |
| <a id="44-byte-level-displacement-tests-and-instruction-level-ones-answer-different-questions-round-1047"></a>44. Byte-level displacement tests and instruction-level ones answer different questions (round 1047) | - |
| <a id="45-difflibsequencematcher-reports-100-equal-on-streams-that-differ-at-instruction-21-round-1048"></a>45. `difflib.SequenceMatcher` reports 100% equal on streams that differ at instruction 21 (round 1048) | `0x1000aac0`, `0x1000ab38`, `0x1000ad08` |
| <a id="46-the-residue-is-10000-instruction-aligned-every-differing-byte-lies-inside-a-reference-instruction-round-1072"></a>46. The residue is 100.00% instruction-aligned: every differing byte lies inside a reference instruction (round 1072) | - |
| <a id="47-the-residue-table-silently-hid-every-carrier-under-9-bytes-18-rows-summing-to-8623-against-a-8628-total-round-1073"></a>47. The residue table silently hid every carrier under 9 bytes: 18 rows summing to 8623 against a 8628 total (round 1073) | `0x1000aaf7` |
| <a id="48-audited-every-table-and-counter-the-project-quotes-against-its-own-arithmetic-all-reconcile-round-1074"></a>48. Audited every table and counter the project quotes against its own arithmetic: all reconcile (round 1074) | - |
| <a id="49-auditing-docs-for-missing-evidence-by-regex-measures-word-choice-not-evidence-round-1075"></a>49. Auditing docs for "missing evidence" by regex measures word choice, not evidence (round 1075) | - |
| <a id="50-the-per-carrier-table-is-stable-across-a-full-object-rebuild-and-the-deliverable-is-bit-identical-round-1076"></a>50. The per-carrier table is stable across a full object rebuild, and the deliverable is bit-identical (round 1076) | - |
| <a id="51-a-0-mismatched-data-verdict-measured-37-of-the-metadata-and-said-nothing-about-it-round-1078"></a>51. A "0 mismatched" data verdict measured 37% of the metadata, and said nothing about it (round 1078) | `0x10035000` |
| <a id="52-decoding-a-function-by-its-inventory-span-swallows-inter-function-padding-and-fabricates-instructions-round-1084"></a>52. Decoding a function by its INVENTORY SPAN swallows inter-function padding and fabricates instructions (round 1084) | `0x10002770`, `0x10002aaf`, `0x10002f4c`, `0x10002f4e`, `0x10002fc0`, `0x100272b4` |
| <a id="53-the-raw-link-is-the-wrong-artifact-for-a-data-addressed-operand-comparison-round-1086"></a>53. The raw link is the wrong artifact for a `.data`-addressed operand comparison (round 1086) | - |
| <a id="54-a-whole-section-idiom-census-cannot-use-the-raw-links-text-and-cannot-compare-rates-at-all-round-1088"></a>54. A whole-section idiom census cannot use the raw link's `.text`, and cannot compare rates at all (round 1088) | - |
| <a id="55-postlink_residualpy-measures-the-raw-link-so-a-stale-composition-reports-a-fake-residue-of-81229-round-1101"></a>55. `postlink_residual.py` measures the raw link, so a stale composition reports a fake residue of 81,229 (round 1101) | - |
| <a id="56-verify---data---built--rewrites-verified-statuses-to-drift-in-the-tool-owned-toml-round-1102"></a>56. `verify --data --built <raw link>` rewrites VERIFIED statuses to DRIFT in the tool-owned toml (round 1102) | - |
| <a id="57-a-relative-include-deeper-than-the-tools-staging-depth-compiles-unpacked-silently-round-1103"></a>57. A relative include deeper than the tool's staging depth compiles unpacked, silently (round 1103) | - |
| <a id="58-a-lower-byte-count-from-a-spelling-that-changes-a-stored-value"></a>58. A lower byte count from a spelling that changes a stored value | `0x10018c28`, `0x7fffffff` |
| <a id="pair-copy-byte-score-hides-an-overlapping-buffer-mismatch-2026-10-04"></a>Pair-copy byte score hides an overlapping-buffer mismatch (2026-10-04) | `0x00407760` |
| <a id="explicit-donor-identity-does-not-remove-inventory-span-noise-2026-10-04"></a>Explicit donor identity does not remove inventory-span noise (2026-10-04) | - |
| <a id="indexed-displacement-can-be-a-biased-base-in-unrelated-data-2026-10-04"></a>Indexed displacement can be a biased base in unrelated data (2026-10-04) | - |
| <a id="stock-body-membership-does-not-select-a-unique-crt-member"></a>Stock-body membership does not select a unique CRT member | - |
| <a id="comparison-width-resolves-the-case-conversion-tie"></a>Comparison width resolves the case-conversion tie | - |
| <a id="coff-zero-filled-literal-sections-need-semantic-bytes"></a>COFF zero-filled literal sections need semantic bytes | - |
| <a id="resolving-an-unknown-callee-changes-mismatch-scores-without-changing-code-2026-10-04"></a>Resolving an unknown callee changes mismatch scores without changing code (2026-10-04) | - |
| <a id="a-trailing-nop-can-hide-a-wrong-cross-target-call-binding"></a>A trailing NOP can hide a wrong cross-target call binding | `0x005b1b10`, `0x005b1eb0`, `0x006628a0`, `0x00774a78` |
| <a id="undefined-external-string-labels-need-complete-payload-proof"></a>Undefined external string labels need complete payload proof | - |
| <a id="compiler-local-label-counters-are-not-relocation-identity-2026-10-04"></a>Compiler-local label counters are not relocation identity (2026-10-04) | - |
| <a id="padding-scores-donor-gaps-and-the-installed-cli-2026-10-10"></a>Padding scores, donor gaps and the installed CLI (2026-10-10) | `0x00405970`, `0x00406510` |
| <a id="a-source-rename-can-leave-a-live-linker-anchor-2026-10-11"></a>A source rename can leave a live linker anchor (2026-10-11) | - |
| <a id="a-shared-import-verdict-can-carry-the-wrong-identity-or-inputs-2026-10-11"></a>A shared import verdict can carry the wrong identity or inputs (2026-10-11) | - |
| <a id="retire-a-shared-source-only-after-its-last-owner-moves-2026-10-11"></a>Retire a shared source only after its last owner moves (2026-10-11) | - |
| <a id="discovery-overlap-can-hide-an-already-correct-source-extent-2026-10-15"></a>Discovery overlap can hide an already-correct source extent (2026-10-15) | - |
| <a id="immediate-callback-stores-were-missing-from-upstream-xrefs-2026-10-15"></a>Immediate callback stores were missing from upstream xrefs (2026-10-15) | `0x0050d350`, `0x005107f0` |
| <a id="a-probe-object-name-can-be-a-windows-device-name-2026-10-15"></a>A probe object name can be a Windows device name (2026-10-15) | - |
| <a id="keep-rotations-executable-extent-separate-from-alignment-2026-10-15"></a>Keep rotation's executable extent separate from alignment (2026-10-15) | - |
| <a id="inspect-each-targets-fixed-bytes-before-a-shared-drift-point-2026-10-15"></a>Inspect each target's fixed bytes before a shared drift point (2026-10-15) | - |
| <a id="a-masked-diff-can-conceal-an-ambiguous-call-binding-2026-10-15"></a>A masked diff can conceal an ambiguous call binding (2026-10-15) | `0x004297c0`, `0x005012b0`, `0x005392a0` |
| <a id="registration-extents-and-type-counts-are-separate-measurements-2026-10-16"></a>Registration, extents and type counts are separate measurements (2026-10-16) | - |
| <a id="native-cutscene-allocation-failure-rejoins-a-pointer-read-goal67"></a>Native cutscene allocation failure rejoins a pointer read (Goal67) | - |
| <a id="a-matching-loop-prefix-omitted-com-shutdown-goal76-2026-10-17"></a>A matching loop prefix omitted COM shutdown (Goal76, 2026-10-17) | `0x00422d90`, `0x00422db6`, `0x00422dc0`, `0x0046bc60`, `0x005de8c0`, `0x005eb36c`, `0x00f8f080` |
| <a id="copied-assembly-hid-a-fifth-dialog-argument-goal77-2026-10-17"></a>Copied assembly hid a fifth dialog argument (Goal77, 2026-10-17) | `0x0041c830`, `0x0041cf60`, `0x0041d0d8`, `0x00435f13` |

</details>
