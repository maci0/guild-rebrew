# Community research leads

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

Their [suspended-process EXE harness](https://github.com/europa1400-community/europa1400-decompilation/blob/eabb183f6fecc3607ce661ca3810e03da7e336bc/docs/exe/exetest.md) currently tests four pure functions. Its executable hash gate and hardcoded addresses target German, and the game CRT is uninitialized. Recordings are ignored rather than shipped in Git; their reported replay/fuzz results were not reproduced here. A future English harness needs its own build bindings and bounded fixtures. No harness is implemented by this note.

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
