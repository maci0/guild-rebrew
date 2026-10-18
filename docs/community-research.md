# Community research leads

## EXE branch follow-up, 2026-10-19

Reviewed [`exe-decompilation` at `181935f64a2a754c468420503ef7b57bbe27f64b`](https://github.com/europa1400-community/europa1400-decompilation/tree/181935f64a2a754c468420503ef7b57bbe27f64b),
228 commits after the review below. Their `GOLD` remains German TL; their
`GOLD_EN` corresponds to our English TL. Their non-identical C and behavioral
test results are research leads, not local byte verdicts.

Twenty English native windows were inspected. Thirteen original names were
confirmed, including `gs_AddBeweis`, `bio_rd_array_quick`, `ch_UseGate`,
`ecmd_RotateObject`, `evt_EnterFunction`, `txt_ReloadTextFile`,
`txt_loadTextFile`, and six historical-text parsers. Preserve their original
spelling: the community source translates `gs_AddBeweis` to `gs_AddEvidence`
despite its own diagnostic ledger. Generated labels need independent review.

| Priority | Local TL work | Useful external evidence |
| --- | --- | --- |
| Original names | `0x4f5770`, `0x401500`, `0x406850`, `0x40eac0`, `0x427c40` | [Diagnostic ledger](https://github.com/europa1400-community/europa1400-decompilation/blob/181935f64a2a754c468420503ef7b57bbe27f64b/docs/anchors/GOLD.md), checked against our native operands. |
| Historical text | Six placeholders at `0x4b20e0`, `0x4b2300`, `0x4b2670`, `0x4b2a10`, `0x4b2e20`, `0x4b3010` | [Two-pass parser](https://github.com/europa1400-community/europa1400-decompilation/blob/181935f64a2a754c468420503ef7b57bbe27f64b/src/game/game_g_historical_text.c): selectors, replacements and callback contracts. |
| EVT | Tokenizer, preprocessing, parameter/frame entry and evaluation placeholders | [Interpreter design](https://github.com/europa1400-community/europa1400-decompilation/blob/181935f64a2a754c468420503ef7b57bbe27f64b/docs/modules/GOLD-evt.md); retain our repaired command-slot contracts. |
| Quantization | `0x41bdc0`, `0x41bf90`, `0x41c290`, `0x41c470` | [Octree reconstruction](https://github.com/europa1400-community/europa1400-decompilation/blob/181935f64a2a754c468420503ef7b57bbe27f64b/src/game/game_g_quantize.c) and failure/tie fixtures; reuse our existing `octree.h`. |
| TXT boundary | Loader `0x42d880`, possible separate writer `0x42dac0` | Our native loader returns at `0x42dabe`, before another prologue and `txt_SaveTextFile` diagnostics. Review the recorded 1,040-byte extent before implementation. |
| Further algorithms | A*, BMP decoding, mouse state, scene morphing and AI | Corresponding [module notes](https://github.com/europa1400-community/europa1400-decompilation/tree/181935f64a2a754c468420503ef7b57bbe27f64b/docs/modules) and fixtures supply bounded behavior checklists. |

Unique exported hashes locate 1,268 descriptive hypotheses after excluding
address-generated labels, explicit guesses and tagged library ranges. Of these,
233 have community C and no local stored verdict. These are triage counts,
not missing-function counts or recovered bytes. Their newer harness covers
return widths, immediate 80-bit ST0 capture, callback mutations and call order;
its reported results were not reproduced here.

Their `game_g_*.c` files are reconstruction packages, not original TU
attestations. Proposed local homes remain inferred and require provider,
type-layout and native-order review. No new original TU was established, and
no community source, types, storage or verdicts were imported. No general
repository source license was found; zlib's separate license does not cover
the reconstruction. Use the factual leads for independent native recovery.

Full review: `.scratch/community-exe-review/REPORT.md` (13 ranked groups,
47 checked pinned links), with external candidate lists and native JSON receipts.

## Earlier review, 2026-10-18

Reviewed 2026-10-18: [europa1400-decompilation](https://github.com/europa1400-community/europa1400-decompilation/tree/eabb183f6fecc3607ce661ca3810e03da7e336bc), commit `eabb183f6fecc3607ce661ca3810e03da7e336bc` (2026-10-09). This records independently checked facts and bounded research leads; it imports no source, types, storage or verdicts.

## Match the build first

Their main reconstructed target is **German v2.06**. Guild's reference SHA-256 values exactly match their **English reference** entries in the [binary manifest](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/tools/binaries-gog.sha256):

| Guild reference | SHA-256 | Their reference |
| --- | --- | --- |
| `original/Server/server.dll` | `3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1` | SERVER_EN |
| `original/Europa1400Gold_TL.exe` | `6fe7a24c93192f6511bc8595eb82fd166db44f6cbeaf7c2f036838f3b6b4af45` | GOLD_EN |
| `original/Europa1400Gold.exe` | `7d1f178f6463ab41f90987451187a93056814293832a5d2c76444dbd087e3ae8` | GOG English non-TL |

Their **GOLD** means German D3D8; Guild **GOLD** means English non-TL. Their German SERVER addresses also differ. Use hashes and native operands before transferring a name, signature or offset. Their [binary/version notes](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/binaries.md) explain the filename/module mismatch.

## Accepted native naming evidence

These three leads came from their [English TL symbol export](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/symbols/GOLD_EN/functions.csv). Reviewed against Guild's current C sources and the native English TL instructions, including direct string operands:

| TL function VA | Community name | Native evidence and accepted finding |
| --- | --- | --- |
| `0x00402a00` | `ch_SetVisible` | **Original name attested.** At `0x00402a83`, `push 0x00675328` supplies `ch_SetVisible(): invalid character`. The body forwards visibility to attached objects, clears/sets bit `0x20` in the byte at character `+0x8c`, and calls `ch_Updatelowpoly`. Current source: `src/GOLDTL.fcn_00402a00.c`. |
| `0x00403200` | `ch_Create_Character` | **Accept original name `ch_Create`, not the proposed spelling.** At `0x0040325c`, `push 0x0067534c` supplies `ch_Create:Too many characters!`; the allocation label at `0x0067536c` is `ch:Create:Character`. The body allocates/zeros `0x244` bytes, finds a slot in the `0x300`-entry table, stores its index, or frees the allocation on exhaustion. Current source: `src/GOLDTL.fcn_00403200.c`. |
| `0x004050c0` | `Deinit_QueueEntry` | **Accept unlink-and-clear semantics; original spelling unproved.** Native `+0x24/+0x28` links and owner `+0x14` update the owner's head at `+0x128`; `rep stosd` clears `0x65` DWORDs (`0x194` bytes). NULL returns 0, successful removal returns 1. No naming string occurs in the complete body. Current source: `src/GOLDTL.fcn_00405080.c`. |

The first two names are ready evidence for a separately reviewed rename through `rebrew source rename`; no rename or STATUS change is performed by this research ingestion. The third remains a semantic lead under the [naming rules](naming_conventions.md).

The wider source scan found **422 unreviewed candidates** where their export supplies a descriptive name and our active TL identity still uses `fcn_`/`FUN_`. That is a search queue, not 422 accepted names. Some rows are guesses or repeat facts already in our comments. For example, their `d3_LoadBinaryAnimationStream` at TL `0x004011f0` is broader than the locally visible four-byte VFS read establishes; `vfs_Tfopen` at TL `0x0042ff50` is already documented and implemented here.

## Useful native review checklists

Their [character creator notes](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/modules/SERVER-character-create.md) and [fixtures](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/src/server/shadow_character_create.c) offer concrete cases: free/dead/full slots, mutations retained after late failure, parent/child aliases, consumed random calls, matrix intersections, and x87 store rounding. Their German creator is `0x10016f60`; Guild's known English creator is `gm_AllocSpieler`, `0x10018850`. This is a semantic correspondence, not a cross-build byte proof. Our [historical behavioral review](behavioral-verdicts.md) already covers the English function.

Their [trade-command notes](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/modules/SERVER-command-handler-trade.md) propose meanings for Character counters `+0x198/+0x19c/+0x1a0/+0x1a4` and town-good fields `+0x18/+0x1c`. Their German `cm_ExSellObjekt` is `0x1000ca10`; ours is `0x1000d930`. Some field meanings are explicitly guesses. Check our operands and owning layouts before using them in canonical types.

Their [coverage audit](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/modules/SERVER-standalone-audit.md) found 57 overlooked address-taken functions by following two 106-slot command tables. Their [table tests](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/src/server/shadow_command_tables.c) and [partial-read notes](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/modules/SERVER-load-structure.md) are useful test designs. These do not establish missing Guild server bodies: the current Guild server build already matches the complete reference file, while source-fidelity work remains. Compare current status through Rebrew rather than their differently scoped 248-function count.

## Testing design worth retaining

Their [session recorder](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/src/server/record.h) intercepts socket/time APIs and writes E1REC records containing inputs, results and payloads. The [replayer](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/src/tools/replay.c) compares outgoing messages with an explicit mask for nondeterministic bytes. Their [shadow framework](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/src/hook/shadow.h) snapshots explicit regions, normalizes listed pointer fields and journals dependent calls; [fault counterchecks](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/scripts/verify-shadow.ps1) verify that deliberate errors are detected. This could complement our byte gates when testing intentional behavior changes.

Their [suspended-process EXE harness](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/exe/exetest.md) tests four pure functions at the reviewed commit. Its executable hash gate and hardcoded addresses target German, and the game CRT is uninitialized. Recordings are ignored rather than shipped in Git. Their reported replay and fuzz results were not reproduced here. A future English harness needs its own build bindings and bounded fixtures. This note implements no harness.

## Import limits and replay

No general repository LICENSE/COPYING or source license declaration was found in the tracked paths, README, CMake and docs inspected. Establish permission before copying their reconstructed source or harness. Their separately licensed [zlib provenance](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/third_party/zlib-1.1.3/PROVENANCE.md) does not license the rest; Guild already has zlib providers. No new asset corpus/parser was established here, and separately linked community repositories were outside the scan.

The review covered the 597-file tracked-path inventory, selected binary/strategy/server/type/testing docs and source, English/German symbol exports, and Guild source/catalog searches. It was not a line-by-line audit of the repository. Native naming checks are reproducible without compiling:

```sh
rebrew binary asm show 0x00402a00 --size 146 --strings --target Europa1400Gold_TL.exe --json
rebrew binary asm show 0x00403200 --size 110 --strings --target Europa1400Gold_TL.exe --json
rebrew binary asm show 0x004050c0 --size 110 --strings --target Europa1400Gold_TL.exe --json
sha256sum original/Server/server.dll original/Europa1400Gold_TL.exe original/Europa1400Gold.exe
```

Only documentation is ingested. No source copies, native execution, builds, metadata renames, type bindings or storage definitions were added.
