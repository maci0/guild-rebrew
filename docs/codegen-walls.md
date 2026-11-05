# Bounded negative results

A failed set of C variants is evidence about those variants under those inputs.
It is not proof that C cannot reproduce the reference, that the residue is a floor,
or that the original used assembly. [Assembly evidence](assembly-audit.md) has a
separate acceptance rule.

## Before reopening a probe

Check the address index below, current source, native body and original TU context.
A new attempt needs a specific new fact: corrected call/field/stack evidence,
a different original compilation context, a missing definition, or a controlled
compiler result. Renaming locals or repeating exhausted permutations is not one.

Prior negative families include declaration/initializer permutations, forced
register homes, broad volatile changes, return folding and fill/copy preludes.
Several earlier impossibility claims were later withdrawn after source or context
corrections. Their full controls remain archived.

## Record a useful negative result

State the target/VA, exact inputs, variants tried, observed effect, limits and replay
receipt. Keep one record per experiment family. Do not repeat whole-project status
or label a byte delta as its own cause.

Use [C shapes](msvc6-c-shapes.md) for expression hypotheses and
[register allocation](msvc6-allocator.md) for value/slot analysis. Preserve canonical
whole-TU game flags; diagnostic overrides do not become production policy.


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/codegen-walls.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/codegen-walls.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="codegen-walls"></a>Codegen walls | - |
| <a id="index"></a>Index | - |
| <a id="1-register-allocation-and-scheduling-are-not-steerable-from-c"></a><a id="2-msvc6-merges-byte-identical-early-return-epilogues-unconditionally"></a>1. Register allocation and scheduling are not steerable from C | `0x10016090`, `0x10017a70` |
| <a id="2-early-return-epilogue-merging-follows-a-return-inside-a-loop-round-1145"></a>2. Early-return epilogue merging follows a return inside a loop (round 1145) | `0x10011cdb`, `0x10011d77`, `0x10016f80` |
| <a id="3-the-volatile-idiom-has-a-direction-and-a-per-site-wall"></a>3. The `volatile` idiom has a direction, and a per-site wall | - |
| <a id="4-address-folding-and-strength-reduction"></a>4. Address folding and strength reduction | - |
| <a id="5-flags-are-not-a-general-lever"></a>5. Flags are not a general lever | - |
| <a id="6-the-largest-measured-win-was-forbidden-by-the-constraints"></a>6. The largest measured win was forbidden by the constraints | - |
| <a id="6b-the-inline-asm-zero-fillmemcpy-prelude-measured-cost-of-the-constraint"></a><a id="7-what-would-actually-move-the-needle"></a>6b. The inline-asm zero-fill/memcpy prelude: measured cost of the constraint | `0x1000b040`, `0x1000b057`, `0x1000b05a`, `0x1000b05d`, `0x1000b05f`, `0x1000b061` |
| <a id="7-withdrawn-the-source-axis-was-not-exhausted"></a><a id="8-the-measured-floor-of-this-constraint-set"></a>7. Withdrawn: the source axis was not exhausted | - |
| <a id="8-withdrawn-the-measured-residue-was-not-a-floor"></a>8. Withdrawn: the measured residue was not a floor | - |
| <a id="11-the-residues-shape-quantified-and-why-the-small-carriers-are-not-a-shortcut-round-939"></a>11. The residue's shape, quantified: and why the small carriers are not a shortcut (round 939) | - |
| <a id="12-only-one-residue-carrier-has-room-to-grow-round-950"></a>12. Only one residue carrier has room to grow (round 950) | - |
| <a id="12b-every-one-of-the-19-carriers-divergence-sites-is-already-documented-round-978"></a>12b. Every one of the 19 carriers' divergence sites is already documented (round 978) | `0x1000bebb`, `0x1000bebc` |
| <a id="13-the-residue-is-fully-attributed-and-classified-round-973"></a>13. The residue is fully attributed and classified (round 973) | `0x10009827`, `0x1000982a`, `0x1000ab04`, `0x1000ab08`, `0x1000ed8c`, `0x1000ed8e`, `0x10011cdb`, `0x10011d77`, `0x10012de8`, `0x10012dea`, `0x10019ee3`, `0x10030b6c`, `0x100358fc`, `0x101de450` |
| <a id="9-the-residue-is-not-a-code-shape-deficit-anywhere-round-923"></a>9. The residue is not a code-shape deficit anywhere (round 923) | `0x100174d0` |
| <a id="9b-byte-identical-outside-text-is-true-of-the-shipped-file-not-of-what-the-build-produces-round-936"></a>9b. "Byte-identical outside `.text`" is true of the *shipped file*, not of what the build produces (round 936) | - |
| <a id="10-a-function-argument-that-was-an-undefined-stub-found-by-reading-the-emitted-operand-round-924"></a>10. A function-argument that was an undefined stub, found by reading the emitted operand (round 924) | `0x1000e12a`, `0x1002cc8c`, `0x11766604` |
| <a id="14-the-data-axis-is-closed-the-shipped-files-non-text-bytes-already-match-exactly-round-977"></a>14. The `.data` axis is closed: the shipped file's non-`.text` bytes already match exactly (round 977) | - |
| <a id="12c-the-fault-versus-symptom-split-and-the-tool-that-makes-it-mechanical-round-979"></a>12c. The fault-versus-symptom split, and the tool that makes it mechanical (round 979) | `0x10002770`, `0x10002772`, `0x10006591`, `0x10008b2a`, `0x10009056`, `0x1000a5c0`, `0x1000aaf6`, `0x1000bebb`, `0x1000d959`, `0x1000e20c`, `0x1000e20d`, `0x1000ec2e`, `0x10011cf6`, `0x1001292a`, `0x1001607c`, `0x10016f86`, `0x10017530`, `0x100188fa`, `0x10019804`, `0x10019ee3`, `0x100358fc`, `0x101de450` |
| <a id="12d-the-12b12c-coverage-table-partly-counted-itself-round-982"></a>12d. The 12b/12c coverage table partly counted itself (round 982) | `0x10002770`, `0x10006591`, `0x10008b2a`, `0x10009056`, `0x100096a8`, `0x1000a5c0`, `0x1000aaf6`, `0x1000bebb`, `0x1000d959`, `0x1000e20c`, `0x1000ec2e`, `0x10011cf6`, `0x1001292a`, `0x1001607c`, `0x10016f86`, `0x10017530`, `0x100188fa`, `0x10019804`, `0x10019ee3` |
| <a id="2-addendum-a-fourth-instance-with-branch-counts-cm_excopyentitydata-round-995"></a>2 addendum: a fourth instance, with branch counts: `cm_ExCopyEntityData` (round 995) | `0x1000eda8`, `0x1000edb4`, `0x1000ee48`, `0x1000ef7b`, `0x1000ef84` |
| <a id="5-addendum-the-pragma-optimize-axis-swept-on-ls_loadbuildingentitystate-round-996"></a>5 addendum: the `#pragma optimize` axis, swept on `ls_LoadBuildingEntityState` (round 996) | - |
| <a id="15-the-asm-clause-has-no-applicant-among-the-19-carriers-round-999"></a>15. The asm clause has no applicant among the 19 carriers (round 999) | `0x1000e140`, `0x100128f0` |
| <a id="16-the-residue-quantified-by-lever-availability-675-register-role-325-placement-round-1003"></a>16. The residue quantified by lever availability: 67.5% register-role, 32.5% placement (round 1003) | - |
| <a id="17-several-of-the-13-differing-cfg-carriers-differ-only-by-branch-polarity-round-1009"></a>17. Several of the 13 "differing CFG" carriers differ only by branch POLARITY (round 1009) | `0x10019f4c`, `0x10019f4f`, `0x10019f51`, `0x10019f52`, `0x10019f53`, `0x10019f54`, `0x10019f56`, `0x10019f57`, `0x10019f59`, `0x10019f5b`, `0x10019f5d`, `0x10019f5f`, `0x10019f64` |
| <a id="18-all-13-non-isomorphic-carriers-differ-in-arity-or-merge-never-in-polarity-alone-round-1011"></a>18. All 13 non-isomorphic carriers differ in ARITY or MERGE, never in polarity alone (round 1011) | `0x100097c5`, `0x100098e3`, `0x100098e5`, `0x100098e7`, `0x100098e9`, `0x10009919`, `0x1000991a` |
| <a id="19-loop-condition-polarity-follows-the-loop-form-not-the-conditions-spelling-solved"></a>19. Loop-condition polarity follows the loop FORM, not the condition's spelling (solved) | `0x100097c5`, `0x100098e1`, `0x100098e3`, `0x100098e5`, `0x100098e7`, `0x100098e9`, `0x10009919`, `0x1000991a` |
| <a id="20-the-whole-raw-link-data-divergence-is-postlink-supplied-so-no-data-content-is-missing-round-1016"></a>20. The whole raw-link `.data` divergence is postlink-supplied: so no `.data` content is missing (round 1016) | - |
| <a id="21-gm_findnextfilteredentitys-entry-order-moves-the-fault-instruction-but-scores-6-round-1027"></a>21. `gm_FindNextFilteredEntity`'s entry order moves the fault instruction but scores +6 (round 1027) | `0x10016f80`, `0x100170d6`, `0x100a8c30`, `0x1014d8c0` |
| <a id="22-m_alloctrackeds-prologue-is-a-pure-2-instruction-swap-and-both-source-levers-cost-round-1028"></a>22. `m_AllocTracked`'s prologue is a pure 2-instruction swap, and both source levers cost (round 1028) | `0x10006580`, `0x10034640` |
| <a id="23-the-18-carriers-fail-individually-not-from-a-shared-cause-file-mates-are-byte-identical-round-1040"></a>23. The 18 carriers fail individually, not from a shared cause: file-mates are byte-identical (round 1040) | `0x10016cd0`, `0x10016de0`, `0x10016ea0`, `0x10016f80`, `0x100196c0`, `0x10019720`, `0x100198b0`, `0x10019a20`, `0x10019a70`, `0x10019ae0`, `0x10019b40`, `0x10019b80`, `0x10019be0`, `0x10019c60`, `0x10019cd0`, `0x10019d00`, `0x10019d30`, `0x10019ed0`, `0x1001a060`, `0x1001a0d0` |
| <a id="24-gm_allocspielers-0xaa-fault-three-further-spellings-none-lands-round-1044"></a>24. `gm_AllocSpieler`'s +0xaa fault: three further spellings, none lands (round 1044) | `0x100358a4`, `0x100358fc` |
| <a id="25-gm_allocspielers-2823-bytes-are-four-clusters-and-they-are-not-displaced-code-round-1046"></a>25. `gm_AllocSpieler`'s 2,823 bytes are FOUR clusters, and they are not displaced code (round 1046) | - |
| <a id="26-three-per-file-toolchain-pins-to-msvc-60-sp5-pp-are-load-bearing-and-uniquely-optimal-round-1051"></a>26. Three per-file toolchain pins to `msvc-6.0-sp5-pp` are load-bearing and uniquely optimal (round 1051) | - |
| <a id="27-the-residue-does-not-correlate-with-x87-density-branch-count-or-call-count-round-1063"></a>27. The residue does not correlate with x87 density, branch count, or call count (round 1063) | - |
| <a id="28-m_alloctrackeds-inlined-strcpy-differs-from-the-reference-in-two-ways-at-0x100066a0-round-1066"></a>28. `m_AllocTracked`'s inlined `strcpy` differs from the reference in TWO ways at 0x100066a0 (round 1066) | `0x100066a0`, `0x100066a1`, `0x100066a2`, `0x100066a3`, `0x100066a4`, `0x100066a5`, `0x100066a6`, `0x100066a7`, `0x100066a9`, `0x100066ab`, `0x100066ad`, `0x100066af`, `0x100066b0`, `0x100066b7`, `0x100066b9` |
| <a id="29-the-references-inlined-strcpy-carries-a-cld-our-msvc6-never-emits-positive-evidence-for-the-asm-clause"></a>29. The reference's inlined `strcpy` carries a `cld` our msvc6 never emits: positive evidence for the asm clause | `0x100066a0` |
| <a id="30-the-cld-at-0x100066a0-is-a-one-off-in-the-reference-1-of-18-repne-scasb-sites"></a>30. The `cld` at `0x100066a0` is a ONE-OFF in the reference: 1 of 18 `repne scasb` sites | `0x10002730`, `0x10002ad7`, `0x100066a1`, `0x10006a95`, `0x10009d70`, `0x10009d96`, `0x10009da5`, `0x100110f3`, `0x1001111a`, `0x10011eae`, `0x10011ed5`, `0x1001717e`, `0x10018a6e`, `0x10018a91`, `0x10018ab4`, `0x1001a54c`, `0x1001a556`, `0x10021214` |
| <a id="31-the-missing-cld-does-not-explain-m_alloctrackeds-other-eleven-clusters-round-1069"></a>31. The missing `cld` does NOT explain `m_AllocTracked`'s other eleven clusters (round 1069) | `0x100066a0` |
| <a id="32-std-before-a-rep-sequence-appears-11-times-and-we-match-all-11-the-cld-miss-is-specific-not-a-prefix-gap"></a>32. `std` before a rep sequence appears 11 times and we match all 11: the `cld` miss is specific, not a prefix gap | `0x100066a0`, `0x10011dad`, `0x100188e8`, `0x1001a555`, `0x1001b3b3`, `0x1001b40a`, `0x1001b434`, `0x1001b466`, `0x1001ec63`, `0x1001ed16` |
| <a id="33-all-19-first-divergences-in-one-table-independently-reproduced-round-1071"></a>33. All 19 first divergences in one table, independently reproduced (round 1071) | `0x10009827`, `0x1000ab08`, `0x1000ed8e`, `0x10011d77`, `0x10012dea`, `0x10030b6c`, `0x100358fc`, `0x101de450` |
| <a id="34-gm_allocspielers-2823-bytes-are-dominated-by-one-159-instruction-run-and-it-is-a-register-swap-the-volatile-qualifier-fixes-in-place-round-1082"></a>34. `gm_AllocSpieler`'s 2,823 bytes are dominated by ONE 159-instruction run, and it is a register swap the `volatile` qualifier fixes in place (round 1082) | `0x1001910e`, `0x10019113`, `0x10019115`, `0x10019119`, `0x1001911b`, `0x1001911d`, `0x10019123`, `0x10019124`, `0x100a9820`, `0x1014d8e0` |
| <a id="35-the-sympathy-loop-wall-is-a-mid-argument-register-choice-four-type-and-structure-spellings-are-measured-and-none-lands-round-1083"></a>35. The sympathy-loop wall is a mid-argument register choice; four type and structure spellings are measured and none lands (round 1083) | `0x10019342` |
| <a id="36-no-carrier-is-one-wall-the-largest-run-holds-17-83-of-a-carriers-differing-instructions-and-25-across-all-ten-measured-round-1087"></a>36. No carrier is one wall: the largest run holds 17-83% of a carrier's differing instructions, and 25% across all ten measured (round 1087) | `0x10018ee6`, `0x10018f29`, `0x10018fd9`, `0x10019361` |
| <a id="37-a-register-rename-post-pass-has-a-measured-ceiling-of-16-of-the-residue-and-the-other-84-is-structural-round-1090"></a>37. A register-rename post-pass has a measured ceiling of ~16% of the residue, and the other 84% is structural (round 1090) | - |
| <a id="38-the-lever-that-was-missing-the-residue-contains-109-instructions-the-reference-has-and-we-do-not-emit-at-all-round-1094"></a>38. THE LEVER THAT WAS MISSING: the residue contains 109 instructions the reference has and we do not emit at all (round 1094) | - |
| <a id="39-gm_findnextfilteredentity-the-three-epilogues-are-not-merged-in-the-reference-and-the-merge-is-what-shifts-every-later-byte-round-1095"></a>39. `gm_FindNextFilteredEntity`: the three epilogues are NOT merged in the reference, and the merge is what shifts every later byte (round 1095) | `0x10016f99`, `0x10016fa9`, `0x10016ff7`, `0x10016ff9`, `0x10016ffd`, `0x100170d6` |
| <a id="40-the-epilogue-merge-class-three-carriers-one-mechanism-and-it-is-the-same-mechanism-in-all-three-round-1096"></a>40. The epilogue-merge class: three carriers, one mechanism, and it is the SAME mechanism in all three (round 1096) | - |
| <a id="41-cm_excopyentitydata-the-third-epilogue-is-a-duplicated-shared-exit-and-two-structural-probes-are-both-905-vs-912-round-1097"></a>41. `cm_ExCopyEntityData`: the third epilogue is a *duplicated shared exit*, and two structural probes are both 905 vs 912 (round 1097) | - |
| <a id="42-correcting-384041-the-missing-instruction-counts-were-inflated-by-jump-table-decoding-and-the-real-exit-path-gap-is-4-round-1098"></a>42. Correcting §38/§40/§41: the missing-instruction counts were inflated by jump-table decoding, and the real exit-path gap is 4 (round 1098) | `0x10002e9c`, `0x10002f1f` |
| <a id="43-the-missing-early-exits-resist-three-further-spellings-the-mechanism-is-backend-block-placement-round-1099"></a>43. The missing early exits resist three further spellings; the mechanism is backend block placement (round 1099) | `0x10016f80`, `0x10016f9a`, `0x10016faa`, `0x10016ff8`, `0x100170c5`, `0x100170d5`, `0x100170d9` |
| <a id="44-what-the-8628-bytes-actually-are-938-differing-instructions-567-of-them-a-different-mnemonic-round-1100"></a>44. WHAT THE 8,628 BYTES ACTUALLY ARE: 938 differing instructions, 567 of them a different mnemonic (round 1100) | `0x10035434`, `0x117665e4` |
| <a id="45-most-of-the-residual-difference-is-pairs-of-swapped-instructions-not-different-code-round-1103-fresh-eyes-survey"></a>45. Most of the residual difference is PAIRS OF SWAPPED INSTRUCTIONS, not different code (round 1103, fresh-eyes survey) | - |
| <a id="46-per-difference-attribution-the-residue-is-split-evenly-across-three-mechanisms-and-45-overstated-the-scheduler-round-1104"></a>46. Per-difference attribution: the residue is split evenly across THREE mechanisms, and §45 overstated the scheduler (round 1104) | - |
| <a id="47-the-four-backend-mechanisms-named-and-separated-round-1105"></a>47. The four backend mechanisms, named and separated (round 1105) | - |
| <a id="48-the-objektnr2-literal-wall-0x101dd8e0-is-load-bearing-at-three-sites-rounds-1108-1109-judgement"></a>48. The ObjektNr2 literal wall: `0x101dd8e0` is load-bearing at three sites (rounds 1108-1109, judgement) | `0x101dd8e0` |
| <a id="49-gm_allocspieler-two-ordering-differences-with-identical-instructions-17-linked-bytes"></a>49. `gm_AllocSpieler`: two ordering differences with identical instructions (17 linked bytes) | `0x10018c28`, `0x10018c38`, `0x10727977`, `0x10727d01`, `0x7fffffff` |
| <a id="50-character-sitting-queries-byte-zero-extension-still-unmatched"></a>50. Character sitting queries: byte zero extension still unmatched | `0x0040df00`, `0x0040e110` |
| <a id="51-task-removal-memset-setup-two-scheduling-ties-remain"></a>51. Task-removal memset setup: two scheduling ties remain | `0x004050c0` |
| <a id="52-sound-request-rotation-resolved-in-a-later-staged-candidate"></a>52. Sound request: rotation resolved in a later staged candidate | `0x004193f0` |
| <a id="53-pair-copy-allocation-after-correcting-the-tails-alias-behavior"></a>53. Pair-copy allocation after correcting the tail's alias behavior | `0x00407760` |
| <a id="bounded-tl-setup-and-return-ordering-controls-2026-10-04"></a>Bounded TL setup and return ordering controls, 2026-10-04 | `0x4d8d17`, `0x4d9ce3`, `0x528166`, `0x5287da`, `0x528839`, `0x528a90`, `0x528b49`, `0x57486d`, `0x5748f5`, `0x57494b`, `0x774720`, `0x100df20`, `0x1015f40`, `0x1015f48`, `0x10161bc` |

</details>
