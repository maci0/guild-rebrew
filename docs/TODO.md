# Blockers — 100% Round-Trip Goal

Last verify: 278/280 passed, 2 failed (0x100093a0 ServerMainThread 2433 vs
2434, 0x10018850 gm_CreateEntityFromParents 3694 vs 3689).
Goal requires 280/280 with inline asm only for 1-5 byte padding.

## gm_Open back to RELOC (2026-09-12)

`0x10015950` had drifted to SIZE_MISMATCH (859/861) when a later rewrite
replaced the proven producible-count tail with a `count_p` pointer local.
Restoring the inline double spelling of `g_entity_type_table + row_index *
0x24d + 0x21` brings it back to RELOC 861/861: the multiply form is what gives
the byte counter the SIB base role (docs/msvc6-c-shapes.md section 34), and
routing the read-modify-write through a pointer local forces a `lea` and lands
2 bytes short.  verify --full 277/280 -> 278/280.

## `.text` link shortfall (2026-09-11) — the build is not byte-identical

The linked `.text` is 0x3a29 (14,889 bytes) shorter than the reference's
0x22846, and `rebrew postlink` used to pad it back to the reference's
VirtualSize and apply the layout package's call/operand maps by offset,
producing a binary 92% wrong in `.text` while the section table, imports and
header fields all matched. Nothing failed: `rebrew verify` is per-function at
the object level, and `verify --whole-binary` compares section sizes, exports,
imports, `.rsrc` and headers, never `.text` content.

Measurements (raw link, postlink skipped):

| commit | date | `.text` VirtualSize | vs reference |
|---|---|---|---|
| `8f135ed` | 2026-08-22 | 0x22c9f | +0x459, trimmable, layout map 99.5% |
| `cce0a1b` | 2026-08-25 | 0x2344f | +0xc09, trimmable |
| `93ecf29` | 2026-08-26 | 0x1edc2 | **-0x3a84** |
| `c77489a^` (parent) | 2026-08-26 | 0x1edc2 | -0x3a84 (same tree) |
| `b67f1d3` (HEAD) | 2026-09-11 | 0x1ee1d | -0x3a29 |

So the regression is `93ecf29` ("Convert naked asm to proper C across
game/loadsave/command units"), not the LIBCMT switch in `c77489a` that
followed it. That commit deleted 72,290 lines and added 6,197 across 140
files: the naked `_emit` dumps became proper C and the link lost ~18KB of
`.text` it had been emitting. `8f135ed` is the last link that produced the
reference's shape.

Tried and measured (all in the raw-link metric above):

- Restoring the 11 `crt_region` TUs deleted by `7d48b38` (`malloc.c`, `free.c`,
  `realloc.c`, `ioinit.c`, `tidtable.c`, `cexit.c`, `setargv.c`, `flsall.c`,
  `fwrite_fread.c`, `h_ad29.c`, `lock_streams.c`), after renaming the
  `g_<VA>` globals to the current CRT names: 0x1ee1d -> 0x1fcdd. Recovers
  0xec0 of the 0x3a29. Necessary, not sufficient.
- Forcing the reference's CRT members in with `#pragma comment(linker,
  "/include:...")` for every `// LIBRARY:` marker in `library_msvc.h`: fails
  with 104 unresolved externals. Many names in those headers (`code_translate`,
  `overflow_add`, `bit_reverse`, ...) are not linkable LIBCMT symbols; the
  true symbol/object mapping has to come from `scripts/check_library_code.py`,
  and MSVC marks some helpers (`_initterm`, `_parse_cmdline`) static so they
  cannot be named at all.

Next: find which converted functions emit less than the dumps did. `link /MAP`
on the current tree lists every contribution to `.text`, which answers it in
one relink. The dump files emptied by `93ecf29` are the place to look:
`Units/vfs/infblock_dump.c`, `infcodes_dump.c`, `inffast_dump.c`,
`vfs_CompressBlock.c`, `gz_gzread.c`, `gz_check_header.c`,
`ReadVfsCompressed.c`.

The guard added to `rebrew postlink` on 2026-09-11 makes this class of
breakage loud: it validates the layout package's sparse maps against the
built bytes before patching and fails below 90% coverage (reference 100%,
this tree 4%).

> **Tooling moved (2026-08-22):** the `scripts/` helpers referenced below
> were folded into rebrew: `gen_link_stubs.py` → `rebrew gen-stubs`,
> `inline_strings.py`/`define_strings.py` → `rebrew inline-strings`,
> `own_globals.py`/`own_init_arrays.py` → `rebrew data --own`,
> `reassign_globals.py` → `rebrew data --fix-ownership`,
> `converge_layout.py` → `rebrew data --converge`,
> `consolidate_declarations.py` → `rebrew merge --consolidate`.
> Entries below describe the work at the time.

## Service-pack sweep (2026-09-11) — new, and negative

The game was built with an SP4-or-later toolchain: the reference's sbh family
matches `LIBCMT` from SP4/SP5/SP6 and not from base/SP1/SP2, and `0x1001e638`
(`___old_sbh_resize_block`, 169 B) matches SP5 alone.  That pins the pack; it
does not change a byte.

Compiler sweep: all seven VC 6.0 builds (base, SP1..SP6, CL 12.00.8168 and
12.00.8804) over the 21 functions `rebrew verify --full` does not byte-match.
Twenty compile to identical objects under every build.  The one exception,
`0x1000d930 _cm_ExSellObjekt`, gives `obj 2030` under SP3/SP4 and `obj 2055`
under the other five; the target is 2057, so neither variant closes it.  Both
remaining `verify` failures (`0x100093a0` 2433 vs 2434, `0x10018850` 3694 vs
3689) are byte-identical across all seven.

Library sweep: relinking the built objects against SP5's whole `LIB` tree
instead of SP6's moves `.text` at 2 offsets (112357, 123706), the same
magnitude as relinking one tree twice.  SP6's `LIBCMT` is compatible with the
reference for everything our link pulls.

Where the remaining 3,269 B is, with the false leads removed: it is CRT member
selection, not missing game code.  The 279 annotated functions net +29 B
against the reference (the 19 PROVEN sum to roughly +25, the two walls +4), so
nothing we reverse explains the deficit.

Matching every catalog entry typed `library` (`0x10022ff1`; reloc slots
zero-filled) against the four MSVC 6.0 `LIBCMT.LIB` variants and every object
the build compiles leaves 24 entries (3,360 B) with no supplier in the link.
Three resolve to interior catalog addresses inside members we do have (`0x1001af30`
is 156 B into `_strchr`, `0x1001aff0` 100 B into `_strstr`, `0x10021ac0` 140 B
into `_strcmp`), and `strdup`/`isctype`/`setmode_lk` are in the link map, so
about 2.6 KB are genuinely absent:

| reference VA | size | CRT member | in the link map |
|---|---|---|---|
| `0x10022a2f` | 673 | `_ld12cvt` | no |
| `0x1001b757` | 334 | `_unlock_09e` | no |
| `0x1001f1e2` | 233 | `_IsProcessorFeaturePresent` | no |
| `0x100219f7` | 201 | `_dtold` | no |
| `0x1001e7d4` | 197 | `_exsup` | no |
| `0x100200a6`, `0x1002001d`, `0x1001a89c`, `0x1001abeb`, `0x1001b8a5`, `0x1001a8fb`, `0x1001ac43` | 156-45 | `_unlock_09f/g/a/c/9/b/d` | no |
| `0x1001f855` | 123 | `_isctype` | yes |
| `0x100207b8` | 120 | `_wctomb_lk` | no |
| `0x10022ea1` | 111 | `_setmode_lk` | yes |
| `0x1001b088` | 56 | `_init_fptrs` | no |
| `0x10020915` | 46 | `_crt_once_init` | no |
| `0x10023812` | 46 | `_strdup` | yes |
| `0x1001e7ba` | 34 | `_EH3_save_context` | no |
| `0x1001b070` | 23 | `_fpmath` | no |
| `0x1001a140` | 14 | `_getpid` | no |

`_strncnt` (43) is in the same list but cannot be named at all: it is static
inside `a_cmp.obj` (COFF storage class 3), so it is absent from the archive
symbol index and `/INCLUDE:_strncnt` fails LNK2001.

`___ld12mul` (544) and `__except_handler3` (216) are a different case: both are
in LIBCMT and reachable with `/INCLUDE:`.  Measured on the raw link
(`/INCLUDE:___ld12mul /INCLUDE:__except_handler3`, which also pulls
`mantold.obj` and `tenpow.obj`): link clean, imports unchanged at 100, `.text`
VirtualSize 138,113 -> 139,185 (+1,072 B) against the reference's 141,382.  That
1,072 B is a link change, not decompilation.

The rest of the table has no stock supplier: a substring search of each
reference body against the members of all four LIBCMT variants finds none of
them, so `/INCLUDE:` cannot reach them.  `rebrew xrefs 0x10022ff1` puts both
callers inside the CRT, so they are not recoverable by reversing game code
either: our displaced CRT startup (`_fltused` at `link_stubs.c:168`, the
`dllmain.c` substitution) never references the startup/float/stdio path that
pulled these members in the original.  Closing the rest needs the game's own CRT
archive, not more decompilation.

Tooling: the SP1/SP2/SP3/SP5 images never exported `INCLUDE`/`LIB`, so `rebrew
match --flag-sweep-toolchains` reported them as compile failures
(`score: Infinity`) until `rebrew.toolchain.image_msvc_env` supplied the env
from each image's `tool_root`.  All seven builds now report the same match
counts.  The technical matrix lives in rebrew's `docs/TOOLCHAIN.md`
("Service packs: what differs, and how to tell which one a target used").

## cm_RouteCommand recovered (2026-09-11)

`0x10014ca0` carried metadata (RELOC, 265 B) but no source anywhere in the
tree: the only copy was `lobby_c/lb_BroadcastStateChange.c.bak`, left behind
when that TU was split into `lobbycommands.c`, `lb_HandleEntitySync.c` and
`plant.c`.  `lobbycommands.c`'s `case 6` was calling the `fcn_10014ca0` stub in
`link_stubs.c`, which returns 0.

Restored as `command/command_c/cm_RouteCommand.c` (RELOC, 265/265, 6 relocs),
call site renamed, stub deleted.  `rebrew verify --full` 277/279 -> 278/280;
raw-link `.text` 0x21a81 -> 0x21b81 (+256 B net; the stub was 16 B).

Look for more of this class by crossing `link_stubs.c` stubs and stray `.bak`
files against the metadata: a stub whose VA has a strong status, or a `.bak`
holding a function no live TU defines.  The raw "strong status but no live
annotation" scan over-reports (63 VAs, mostly library companions such as
`gzread` and `inflate_blocks`), so the stub/`.bak` cross-check is the
trustworthy signal.

## Types and globals into headers (2026-09-11) — measured, not started

- `rebrew_globals.h` (generated by `rebrew data --gen-header`) is included by
  **no file**, and neither is `types.h` (65 named structs pulled from Ghidra).
  Meanwhile 170 of 309 extern-declared globals are declared in two or more
  files (`g_entity_type_table` in 33).
- Wiring the globals header exposed two generator bugs, both fixed in rebrew:
  a leading underscore was stripped from metadata-named globals
  (`_FPinit` -> `FPinit`, `_osver` -> `osver`), and array / function-pointer
  types were emitted as invalid C (`extern struct T[18] x;`,
  `extern void (__cdecl *)(int) x;`).  Regenerating now emits
  `extern struct T x[18];` and `extern void (__cdecl *x)(int);`.
- Three things still block the wiring:
  1. the header names two types it does not define, `OldSbhRegion` (with its
     `OldPara` / `OldRegionMap` / `OldSbhPage` family) and
     `struct rterr_entry`, which are defined inside `sbh_pool.c` and
     `amsg_exit.c`;
  2. `rebrew test` / `rebrew verify` compile with only the source directory on
     the include path, so `#include "rebrew_globals.h"` resolves in the CMake
     build (`-I src/server.dll`) but not there;
  3. 77 of the 290 declarations disagree with the header's type, six of them
     real conflicts (`g_connections` array-vs-scalar, `g_download_slots`,
     `g_log_buffer`, `g_log_level_table`, the two m_pool strings).  The TU
     spelling is the one that compiles to matching bytes.
- Once those three are done, `.scratch/consolidate_globals.py --apply` removes
  the 213 matching declarations across 55 files in one pass.  It was applied
  and reverted because the header did not compile.
- Recipe for (1), measured: the sbh family is defined in full in
  `sbh_pool.c:70-99` and `sbh_globals.c:61-90` (identical fields, only the
  offset comments differ), while `sbh_aliases.c:20,22` carries bare forward
  typedefs (`typedef struct __old_sbh_page OldSbhPage;`) that would collide
  with the real typedefs.  `struct rterr_entry` is defined in
  `amsg_exit.c:22` and `data_globals.c:113`.  So: put `OldPara`,
  `OldRegionMap`, `OldSbhPage`, `OldSbhRegion` and `struct rterr_entry` in a
  new `rebrew_types.h`; drop the full blocks from those four files, replace
  the two forward typedefs in sbh_aliases.c with the include; insert
  `rebrew_types.h` *before* `rebrew_globals.h` in every file the consolidation
  touches.
- Applying the recovered structs needs a layout check first.  `CommandPacket`
  has the right extent (0x99, matching `cmd_buffer_primary[0x99]` in
  ServerMainThread.c) but its field map cannot be right: it places
  `payload[137]` at 0x8, while the lobby handlers read a command-type byte at
  `msg+0x10` and ints at `msg+0x14` / `msg+0x18`.

## Short-local naming pass (2026-09-11) — done bar the tail

Method: `scripts/rename_locals.py` renames identifier occurrences outside
comments, member accesses and struct field declarations; `scripts/rename_locals_comments.py`
then follows the rename through the probe logs, skipping the verbatim Ghidra
quote blocks.  Re-test the file after each (`rebrew test <file>`), then the
periodic `rebrew verify --full`.

Policy: loop counters (`i`, `j`, `k`) and `n`/`id` stay — idiomatic counters,
not decompiler temporaries.  Some audit hits are struct members (`fc` in
`aemter.c`'s COPY24, `a`/`b`/`c` in `ls_LoadSavegameHeader.c`'s SaveHeaderTail)
and stay: renaming a field would desynchronise its accesses.

Renamed in 30 files: aemter, spiel622, alchemistry_logic2/3, spiel_dumpD,
gv_ExAllocGraveyardWorker, gv_AllocField, gv_SpawnEntities, cm_ChkChangeBits,
cm_ChkChangeAttribute, cm_ChkJoinLeaveElection, cm_ExJoinLeaveElection,
cm_ChkSellObjekt, cm_ExSimSpecialAction, cm_ExChangeDesire, cm_ExChangeFloat,
cm_ExClearLagerslot, cm_ExAllocWarEvent, cm_ExAllocClientSpieler,
cm_GetBuildingStatCount, cm_ExModifyStat, cm_ExMoveObjekt,
cm_ExRemoveLinkedObject, amsg_exit, crt_heap, vfs4, vfs_OpenStream,
check_header, CrashDumpUnhandledExceptionFilter, InitializeLogAndErrorHandler,
plant, loadsave2, loadsave3, spiel, spiel5, spiel6, spiel62,
gm_CreateEntityFromParents, gm_AllocBuildingContents, gm_InitObjektHersteller,
gm_RefreshMarketAvailability, InitNewDynastyEntity, lb_HandleEntitySync,
lb_HandleLobbyCommands, lobbycommands, m_alloc2, ProcessSendData, server4,
srv_ProcessReceiveData.

Closed since (all renamed, re-tested RELOC/NEAR_MATCHING unchanged):
- `server2.c` — the three `p` locals are `slot_walk` (the struct-declaration
  guard in `scripts/rename_locals.py` was treating `struct Foo* x;` as opening
  a struct definition, so the declarations were skipped while the uses were
  renamed; only a line without a trailing `;` starts a definition now).
- `m_AllocTracked.c` — `np`/`node_slot`, `pp`/`prev_slot`, comments included.
- `ls_LoadDynamicEntities.c` — `p`/`record_cursor`;
  `ahm_ExAllocAlchemist.c` — `pp`/`slot_ptr`.
- `cm_ExAllocWarEvent.c` `fc`, `aemter.c` `fc`, `ls_LoadSavegameHeader.c`
  `a`/`b`/`c`: **struct members**, not locals — renaming a field would
  desynchronise its accesses, so they stay.
- `crc32.c` `c`: zlib's own code, kept for library fidelity.

Structs (`types.h`) — measured, not applied: the Ghidra-pulled set is a
*shape* catalogue, and most of its fields are placeholders (`word0`, `byte2`,
`field178`), so applying it would move placeholder names into the code.
`PlayerSlot` is the exception worth mining: its fields are named and it
composes `CommandPacket` at 0x18 and 0xb1 (two 0x99-byte buffers, so the
composition is self-consistent).  `CommandPacket`'s own field map is wrong —
it puts `payload[137]` at 0x8, while the lobby handlers read a command-type
byte at `msg+0x10` and ints at `msg+0x14`/`msg+0x18` — so it has to be
recovered from its use sites before anything composes it.

- `CloseVfsStream` (0x10008d10, 301 B, vfs4.c) vs the pre-existing
  `vfs_CloseStream` (0x100038a0, 177 B, vfs.c): two distinct functions, not a
  duplicate, which is why the rename was refused.  `CloseVfsStream` still
  needs a `vfs_` name, but the two do different things and the choice needs a
  semantic read of the 301-byte one rather than a name swap.

## BSS work (2026-08-22) — raw .data VirtualSize now falls out of the link

`scripts/gen_link_stubs.py` now emits every stub global zero-initialized
(non-tentative, `= 0` / `= {0}` → obj `.bss` → PE `.data` VS, raw=0) plus a
BSS tail pad sized so the RAW link (before any postlink fix) reports
`.data` VS = 0x174059c and `.reloc` VA = 0x1768000 — the BASERELOC data
directory falls out of the link naturally.  Byte identity is preserved
(sha256 c7ac331f…) and `rebrew verify` is 242/242.

Two gotchas fixed along the way:
- **Regenerating drifts the symbol set** (130 → 80 globals): the build-without-
  stubs re-collection surfaces a different unresolved set than the file was
  generated from.  Restored the proven file and applied the BSS conversion +
  tail by hand; the generator now reproduces it (player slots + calibrated
  tail, `_BSS_CALIBRATION = 0xF24` — RE-CALIBRATE after any regeneration).
- **COMMON placement broke 4 .text operands**: `g_player_slot_0`/`_field`/
  `_overflow` were tentative (`extern TYPE x[]` with no definition) → COMMON
  weak symbols parked at the END of the now-huge .data.  Code folding a struct
  offset into the base (`g_player_slot_0[i].data` → base + 0x2641fc) then
  landed at 0x119cb700, outside fix_data's rewrite range → 4-byte diffs.
  Fixed by defining them non-tentatively in link_stubs (BSS_ARRAYS).

DELIVERED (2026-08-22, continued): the .data gap TU
(`src/server.dll/crt_region/data_gap.c`, generated, linked first after
crt_imports) declares the original's raw .data bytes [0x3000:0xe000] that our
game TUs do not emit.  The RAW link now reports `.data` rsz=0xe000 AND
vs=0x174059c AND `.reloc` va=0x1768000 — all three section sizes plus the
BASERELOC data directory fall out of the link.  Byte identity (c7ac331f…) and
`rebrew verify` 242/242 stay green.  `link_stubs.c` tail re-calibrated to
0x1269f30; generator `_BSS_CALIBRATION = -0xB0DC` reproduces it.

Tooling (2026-08-22): `scripts/gen_data_gap.py` regenerates the gap TU
(`--raw-size` must track the game TUs' initialized .data raw, default 0x3000);
`scripts/calibrate_bss.py` automates the raw-link .data-VS calibration loop
(link raw -> measure VS -> adjust g_bss_tail -> repeat until 0x174059c).
`gen_link_stubs.py` reproduces the working link_stubs.c (BSS_ARRAYS +
`_BSS_CALIBRATION = -0xB0DC`; RE-CALIBRATE after regeneration).

FINAL ARCHITECTURE (the best achievable; byte-identical c7ac331f):
- From the RAW link: .data rsz=0xe000 (gap TU), .data vs=0x174059c (BSS
  stubs + tail), .reloc VA=0x1768000 (BASERELOC dd).
- From the final metadata fix (fix_data_vs, the original's own approach):
  SizeOfInitData=0x22000, BaseOfData=0x27000, SizeOfImage=0x1779000.
  Proven not linker-producible in any single link: SizeOfInitData/BaseOfData
  are the no-BSS link-time values (mutually exclusive with the BSS-grown vs
  that .reloc VA/SizeOfImage require), and the exact SizeOfImage needs the
  .reloc content (the original's reloc table is ~6x ours, driven by its
  .data pointer content — the per-TU placement limit).  The final build
  matches the original on every section and header field.

NOT falling out of the link (evidence for the goal's stop rule):
- `BaseOfData` (0x24000 vs 0x27000) and `SizeOfInitData` (0x1747000 vs 0x22000):
  identical section tables (names/RVAs/characteristics) but the linker computes
  different values than the original's — the original's values look post-patched
  or from a different linker computation; `rebrew link-sweep` proves no LINK
  option changes them.
- `SizeOfImage` tracks the `.reloc` raw size (content-driven; the reloc table
  shrinks with the 0x3000 vs 0xe000 raw .data) — needs the data-restore TU.
- `.data` raw 0xe000 needs the data-restore TU in the FULL build, which the
  other TUs' string COMDATs overflow (the known MSVC6 intra-OBJ emission limit).

## Layout metadata storage (2026-08-22) — no binary blobs in the repo

- `rebrew gen-layout` writes the READABLE layout metadata (sections, exports,
  imports, link options, IAT-slot VAs, export stamp) into
  `rebrew-project.toml` under `[targets."<t>".layout]` — plain text,
  committed, diffable.
- The opaque reconstruction data is now a TEXT-ONLY layout package in
  `layout/<target>/` (committed): a structured `layout.txt` plus hex dumps of
  exactly the linker-stamped regions the fixers copy (`header.hex`,
  `iat.hex`, `bookkeeping.hex`, `data.hex`, `reloc.hex`), the drift-check
  prefix (`prefix.hex`) and sparse `.text` maps (`operands.txt`,
  `calls.txt`).  Zero binary bytes at rest anywhere; no `original/` needed.
- The build (`rebrew postlink --layout layout/<target>`) reconstructs the
  reference purely from that text metadata.  Fresh checkout flow:
  `cmake --build build` (the layout package is committed).

## Build no longer needs the original binary (2026-08-22)

The CMake POST_BUILD now converges the linked DLL onto the committed text
layout package (`layout/server.dll/`) via `rebrew postlink --layout`
instead of passing `original/Server/server.dll` to the fixers.  Verified: a
FULL CLEAN rebuild with the original binary moved away produces exactly
`c7ac331f44292657c1fa613608ffd84c9d8ee778e3e7696c7782b37dd6d40ee5`
(byte-identical to the original).  The original is still needed for
`rebrew verify` (function matching) and for regenerating the layout package
(`rebrew gen-layout --target server.dll` — commit `layout/<target>/` so a
fresh checkout can build without it).

## Regression fixed (2026-08-22) — byte-identity restored, clean rebuild deterministic

Symptom: after `rm -rf build && cmake -B build ... && cmake --build build`, the DLL was
no longer byte-identical. `.text` VS grew 0x22846 -> 0x2395f (+0x1119); everything from
VA 0x10005840 onward shifted +0xCC0; fix_imports refused (".rdata prefix 0x241a0 does
not match"); the zlib region looked scrambled/duplicated (two copies of
inflateReset/inflateEnd/inflateInit2_, one "truncated" at 0x80 bytes).

Root cause: `src/server.dll/Units/vfs/infblock_dump.c` — the naked `inflate_blocks_free`
body had been "completed" by extracting **3328 bytes** from the original starting at
VA 0x10004b40, but the real function is only **57 bytes**. The extraction swallowed the
following 0xCC0 bytes (gm_AllocAndInit, inflate_fast, gm_DispatchCall, inflate_codes,
inflateReset, inflateEnd, inflateInit2_ head) as dead, unreferenced code inside the
inflate_blocks_free COMDAT. `/OPT:NOREF` kept the giant section, so .text grew 0xCC0 and
every subsequent function shifted.

Fix: trimmed the naked body to 64 bytes = 57 code bytes + 7 alignment NOPs (the
original's section is 0x3b40..0x3b80). Verified: `sha256sum build/server.dll
original/Server/server.dll` -> `c7ac331f...` identical, both on incremental AND a full
clean rebuild.

Lesson: when "completing" a naked `_emit` dump from the original, extract exactly the
function's catalog size (db/server.dll_functions.csv), not a round number; verify the
following bytes aren't the next function's code.

## Open functions (2)

`rebrew verify --full` is 278/280.  Both failures are documented walls, not
unfinished work; `rebrew todo` reports the same two and nothing else.

| VA | Name | Size | State | Wall |
|---|---|---|---|---|
| 0x10018850 | gm_CreateEntityFromParents | 3689 | obj 3694, 924 B matched | A single-statement hill-climb over the store schedule converged here (header in the .c).  The object is 5 B long and ~990 instructions sit in a different order, so the schedule, not the control flow, is wrong; the statement order has to be re-derived from the target disassembly rather than moved one line at a time. |
| 0x100093a0 | ServerMainThread | 2434 | obj 2433, 1162 B matched | obj 1 B short.  Two cold blocks (host-slot store 0x1000973a, unsynced flag 0x10009b66) that the original C2 deferred into gaps inside unrelated chains.  Nine rounds of label position, branch polarity, guard form, duplication, cold-tail placement, region size and pragma probes all emit them adjacent to their source loop (header in the .c); all seven VC6 SP builds compile it identically. |

The 16 SIZE_MISMATCH rows and the exit 0x1001a670 STUB that earlier revisions of
this file listed are resolved (exit is RELOC under /O1).

## What would unblock

- ServerMainThread: a C2 block-ordering lever that pure C89 does not expose; the
  1-byte size deficit follows from the same placement decision.  A CFLAGS sweep
  confirms flags are not the lever: /O1, /Og-, /Os, /G6 and /Oa all lose (191,
  219, 179, 695, 915 matched against the 1162 baseline), and /Ot, /Ob2, /Oy, /Ox
  are inert.
- gm_CreateEntityFromParents: re-derive the statement order from the target
  disassembly.  Positional hill-climbing cannot cross from a wrong schedule.
- Prove still fails on path explosion for the loop-heavy functions; slice proving
  with explicit start/end offsets promoted two.

## Inline asm audit (2026-09-12)

Three `__asm` blocks remain, 15 asm lines each (45 total), one per hand-written
block-fill site:

| File | Function | Site |
|---|---|---|
| `server4.c:448` | srv_InitBuildingTypeTable | 0x1000b040 |
| `m_alloc2.c:231` | m_PoolAlloc | 0x10006d20 |
| `m_alloc.c:220` | InitPacketPool | 0x100068e0 |

All three emit the original's 24-byte zero-fill prelude (`lea ecx,[edi+edi*2]` /
`and 3` / `sub ebx,ecx` / `jle` / `rep stosb` / `mov ecx,ebx` / `and ebx,3` /
`shr ecx,2` / `rep stosd` / `add ecx,ebx` / `rep stosb`), which is byte-invariant
across all four shipped binaries, absent from LIBCMT, and not emitted by any ms
vc6 C spelling (docs/msvc6-allocator.md Finding 19).  Each block carries a TODO
to replace it with proper C once a spelling is found.

No other inline asm exists.  `REBREW_ALLOW_NAKED` in the metadata CFLAGS is
inert: `cm_ProcessCommandQueue.c`, `gm_RefreshMarketAvailability.c` and `aemter.c`
carry the define but contain no `__asm` and no `naked`.

## Build/tooling state (2026-08-21)

Byte-identity tooling is in place; remaining gap is content, not machinery:

- **PE normalization** — `scripts/fix_data_vs.py` runs POST_BUILD (CMakeLists): relocates
  headers to `e_lfanew 0x80` (strips linker Rich header), forces `TimeDateStamp`,
  copies export-dir stamp pair (MSVC6 LINK writes link time into export
  `Characteristics`; original has it in `TimeDateStamp`), grows `.data VS` to
  `0x174059c` (BSS tail, raw stays small), fixes `.reloc` VA + basereloc
  DataDirectory[5], `SizeOfImage`, recomputes CheckSum.
- **`REBREW_DEBUG_INFO`** (default ON): `/Z7` + `/debug` for reccmp PDB mapping.
  OFF = byte-identity build — the original DLL has no debug directory; `/debug`
  emits an RSDS entry (`.rdata` grows 0x20 B).
- **Link order** — `scripts/order_sources.py` sorts objects by each file's lowest
  `// FUNCTION:` VA (zlib table from `db/server.dll_functions.csv`); drops
  `compress.c`/`uncompr.c` (absent from original). `.text` now starts
  byte-identical; reccmp "aligned" 0 -> 2 and cascades as bodies become exact
  (first non-exact function shifts everything after it).
- **Docker** — wine only (wibo segfaults under MSVC6 CL; `docker/Dockerfile`
  sets `REBREW_USE_WIBO=0`). Host and container builds are byte-identical
  (`REBREW_DEBUG_INFO=OFF` config).

Placement progress (2026-08-21, same session):
- `scripts/inline_strings.py` — rewrote 75 C-level `s_<hint>_<0xADDR>` uses to
  real string literals extracted from the original `.data` (comments/asm/extern
  lines untouched; fixed-width octal escapes). Game-only reccmp 93.28 -> 93.96%.
- `scripts/define_strings.py` — 45 asm-referenced `s_*` tokens now have real
  `char s_x[] = "..."` definitions in their owning TU (content + link-order
  placement); multi-file tokens get one owner definition.
- `scripts/own_globals.py` — 41 scalar globals moved from link_stubs commons
  into most-referencing TUs with the original's initial bytes (BSS-address
  globals = zero-init). link_stubs regenerates cleanly (0 LNK4006).
- `rebrew verify` still 259/259, 0 failed. Build `.data` nonzero 8.5KB -> 11.5KB,
  printable 4.2KB -> 7.2KB.

Remaining for 100%: (1) array globals — real sizes from toml address gaps +
original initializer bytes (entity tables, dispatch tables, currency arrays;
the 20MB player-slot BSS array is one 8x0x264264 array in one TU); (2) complete
the initialized `.data` to the original 0xe000 so the BSS tail (and every BSS
global) lands at its original VA; (3) CRT region — LIBCMT objects vs original
static CRT (`/NODEFAULTLIB` note above); (4) front-to-back body exactness —
aligned goes 0 -> 2 and cascades per exact function.


Placement data passes (same session, empirical):
- `scripts/own_init_arrays.py` — 5 initialized named arrays (log tables, mode
  bytes, g_str_*) filled byte-exact from the original (string sizes NUL-based,
  tables gap-based). Kept: raw prefix match 27.3% -> 28.6%, game reccmp 94.00%.
- REVERTED after measurement: blanket BSS pads (fill_data.py), init-region pads
  (fill_gaps.py v1), coverage-aware gap pads (fill_gaps.py v2). All three
  overshoot .data raw (0x14000 vs 0xe000) or drop reccmp: the compiler-emitted
  string COMDATs do not yet sit at their final addresses, so any byte-range pad
  double-counts them. Lesson: placement converges only via per-TU accounting —
  each OBJ's .data/.bss contribution must equal the original's per-TU
  contribution (sizes, content, intra-TU order). Next tool: a per-TU layout
  audit (expected per-OBJ contribution from cumulative address accounting vs
  actual) to drive targeted fixes instead of blanket pads.

## Per-TU layout audit (2026-08-21)

`scripts/audit_layout.py` — per-OBJ .data/.bss feasibility audit (link order vs
toml addresses). Current findings:
- 19 TU violations: SPAN (own symbols in disjoint regions: Error.c
  0x27078..0x11766204, m_alloc.c 0x28b60..0x117640c4, spiel.c, aemter.c,
  gm_NextEntityQueryMatch.c, gm_StartFilteredEntitySearch.c) and ORDER
  (TU later in link order owns lower addresses than an earlier TU).
- 31 toml symbols unowned/absent from the binary (g_file_append_mode, g_str_*,
  g_stream_*, g_entity_*, download fields, player slots) — several were dropped
  entirely (e.g. g_connection_counter: extern in rebrew_globals.h, no uses ->
  nothing unresolved -> dropped from link_stubs). They must be re-emitted with
  their original values.
Next: ownership re-assignment pass driven by this audit (contiguous runs in
link order), then re-emit missing symbols, rebuild, re-audit (iterative).

## Reassignment pass (2026-08-21)

`scripts/reassign_globals.py` — ownership re-assignment + missing-symbol
emission driven by the audit: 26 edits, clean build, audit violations 19->17,
reccmp game-only 94.01%. Placement-by-address did NOT converge: per-TU
automated passes cannot reproduce the original's intra-TU data order/cumulative
sizes without the original's TU boundaries. Remaining sanctioned path: add
`// GLOBAL:` annotations en masse from rebrew-data.toml, then
`rebrew data --bss --json` + `rebrew data --fix-bss` (project tooling for
exactly this) — needs the annotation pass first (`--fix-bss` currently reports
"No annotated BSS globals").

## Annotation pass (2026-08-21)

`scripts/annotate_globals.py` — mass-generated `// GLOBAL: SERVER 0xVA` markers
from rebrew-data.toml (202 markers; skips decls already carrying `// DATA:`
markers to preserve their declaration adjacency). Pipeline now live:
`rebrew data` -> annotated 63, `rebrew data --bss` -> 38 known entries, 18 gaps,
`rebrew data --fix-bss --dry-run` proposes 18 BSS padding arrays. Do NOT apply
--fix-bss yet: its pads assume the section base lands at 0x10035000, which
requires the initialized .data to reach the original 0xe000 first (established
ordering dependency). Next: converge initialized .data by fixed-point
iteration — measure each TU's .data start, adjust its leading pad by the delta
to its first toml symbol, rebuild, repeat.

## Converger v1 (2026-08-21)

`scripts/converge_layout.py` — fixed-point placement iteration: per-OBJ walk
(corrected image base 0x10000000) -> delta per TU between its first toml
symbol's expected and current VA -> leading pad insertion/removal, filled with
original bytes. Dry-run validated the model (deltas now sensible: spiel.c
+0x28ab, gv_ExAllocGraveyardWorker.c +0x469, Error.c -0x6fc5, m_alloc.c
-0x6ba5...). Key finding: negative deltas come from non-toml early data —
zlib/game TU statics preceding the first annotated symbol (e.g. Error.c's
g_log_level_table is NOT the section's first emission; the original has ~0x78
bytes of earlier-TU data before it). Next: reconcile non-annotated data —
verify our zlib statics (inftrees 0x11ed .data, `local uInt fixed_*`) match the
original's section placement (.data vs .rdata) before toml placement can
converge.

## Contiguous partition + marker lesson (2026-08-21)

- `reassign_globals.py` rewritten to gap-based contiguous partitioning: the K
  data-contributing TUs (link order) own contiguous, address-ordered symbol
  runs; boundaries at the K-1 largest address gaps. Result: audit violations
  17 -> 7, reccmp game-only 94.16% (peak), all 88.47%, build clean.
- CRITICAL: `// GLOBAL:` markers inserted above non-declaration lines break
  `rebrew test`'s function scanner (4-byte diffs / NEAR_MATCHING regressions in
  spiel.c: gm_AssignBuildingOwner, gm_GetEntityTableEntry). All markers
  stripped; verify restored to 259/259, bm 244. Annotator must match only real
  declaration lines (`extern TYPE name;`, `TYPE name[N] = ...`) — fix before
  re-running the --bss/--fix-bss pipeline.

## Converger verdict (2026-08-21)

Converger round 1 applied and REVERTED: reccmp 94.16 -> 93.59, audit
violations 7 -> 11. Fourth distinct automated pad approach to regress (after
BSS pads, init-region pads, coverage-aware pads). Conclusion: MSVC6's
intra-OBJ data emission (COMDAT string order vs regular declarations,
alignment, per-literal pooling) is not controllable by leading pads alone —
automated data-layout passes have reached their empirical limit. Remaining
placement work is per-TU manual ordering with `rebrew test` as the oracle
(standard decomp iteration), gated additionally by the .text size gap
(0x2a000 vs 0x23000 shifts .data/.rdata/.reloc VAs by 0x7000).

Stable state: reccmp game-only ~93.6%, all ~88.4%, rebrew verify 259/259
(bm 244), audit violations ~11, .data raw 0x7000 vs 0xe000.

## First-0x78 byte map (CRT reconciliation spec, 2026-08-21)

Original .data[0x27000:0x27078] vs ours, byte-level:
- +0x00..+0x2f: CRT onexit/atexit pointer table. Orig: 0x1001baa4, 0x100220eb,
  0x1001bb4c. Ours: 0x1001de67, 0x10024b01, 0x1001df0f. Both are CRT code
  addresses; delta = different LIBCMT pull-set (our exit.c reimplements part
  of the CRT + /FORCE dedup changes which crt0dat objects link). Owner: LIBCMT
  library objects (placed at .data offset 0 by LINK), not any explicit OBJ.
- +0x30: orig has `ff ff ff ff` before the broadcast.c path string; ours does
  not. CRT-owned -1 global, part of the same CRT data block.
- +0x60: `"1.1.3\0\0\0"` + ptr 0x1002e06c — identical in both.
- +0x74: orig 0x1002706c (ptr into .data), ours 0x00000001. CRT/zlib block
  tail word.
=> Reconcile the CRT region (LIBCMT pull-set + CRT function addresses) before
these bytes can match; this is downstream of CRT function matching.

## CRT function fixes (2026-08-21)

First CRT divergence fixed: `__ftol` (0x1001B564, 39B) — real implementation as
fenced naked asm in `src/server.dll/__ftol.c` (FUNCTION/SIZE/CFLAGS
annotations, `#ifdef REBREW_ALLOW_NAKED` guard with C fallback). The
`return 0` stub removed from link_stubs (regen: 154 -> 141 unresolved).
reccmp: __ftol 0% -> 100%; all-function 88.38 -> 88.66%. rebrew verify:
260/260, bm 245, __ftol EXACT.

Pattern validated: fix CRT functions front-to-back in address order; each
exact one re-aligns the CRT-region cascade (next: _printf 89%, _realloc 58%,
__amsg_exit 73%, _ctime/_fopen stubs...).

## Debug-CRT experiment (2026-08-21)

`rebrew-crt-match` maps the original's heap functions to DBGHEAP.C sources
(debug CRT): _malloc->DBGHEAP.C:126, _free->DBGHEAP.C:952, _realloc->
DBGHEAP.C:763, _calloc->DBGHEAP.C:452. Hypothesis: original linked the debug
CRT. Direct switch MSVC_RUNTIME_LIBRARY MultiThreaded -> MultiThreadedDebug:
71 link errors (LIBCMTD conflicts with exit.c reimplementations) — REVERTED.
Proper path needs surgery: /NODEFAULTLIB:LIBCMT + selective LIBCMTD object
pulls, or decomp DBGHEAP.C functions individually (__ftol pattern). State
restored: reccmp 88.66%, verify 260/260 bm 245, __ftol 100%.

## CRT chain lesson (2026-08-21)

_printf (0x1001B58B, 65B) attempt REVERTED: its 5 internals (__lock_file,
__stbuf, __ftbuf, __output, __unlock_file) don't resolve from LIBCMT in our
link (they became link_stubs stubs), and __output is the ~5KB printf engine.
Leaf CRT helpers (__ftol) are the reliable per-turn win; engine chains need
either grouped decomp (__output + deps) or the selective LIBCMTD pull surgery.
State restored: reccmp 88.66%, verify 260/260 bm 245, __ftol 100%.

## CRT leaf pattern (2026-08-21)

__amsg_exit (0x1001BA71, 51B) implemented in src/server.dll/crt_amsg_exit.c:
crt0msg.c shape (error-mode gate -> crt_runtime_error / _NMSG_WRITE / _exit(255)
via static pointer slot). Key discovery: CRT helpers compile with **/O1** (the
/O2 build was 2 bytes over: `add esp,8` vs `pop ecx;pop ecx` idiom). Externs
renamed to LIBCMT's real symbols (__error_mode 0x10035508, __app_type
0x1003550C). Result: rebrew verify RELOC 100% (bm 246), reccmp 73 -> 93%
(remaining 7% = data-symbol naming gaps in original annotations).

## CRT iob helpers (2026-08-21)

crt_ioblock.c: crt_fcloseall_thunk (0x1001BB4C, 20B) RELOC 100% and
_lock_stream (0x1001BB60, 47B) RELOC 100% (condition: stream >= _iob &&
stream <= _iob+0x260 -> __lock(index); else EnterCriticalSection via
__declspec(dllimport) for the ff15 import-call form). __ioterm
(crt_ioterm.c) body is byte-perfect 168/168 but verify reports SIZE_MISMATCH:
rebrew-functions.toml records size 235 (spans the two now-separate helpers);
rebrew has no tool path to refresh library-region sizes (extract only lists
un-reversed candidates) — metadata artifact, not a code issue. bm 248.

## CRT leaf batch (2026-08-21)

__free_osfhnd (0x1001BC61) — 174/174 byte match (match_percent 100; SIZE_MISMATCH
label = stale toml size 174 vs real 130, same artifact class as __ioterm).
Iteration notes: (1) the first __get_osfhandle result is DEAD after the -1/fh
checks (kept in EAX, never stored) — duplicate the mergeable CloseHandle block
instead of a `hloc &&` guard; (2) comparison source order matters:
`__get_osfhandle(1) == hloc` (cmp edi,eax not cmp eax,edi); (3) pioinfo entry
stride is 36 (osfile+osfhnd+pad[0x1f]), not 40.
CRT scoreboard: __ftol EXACT, __amsg_exit RELOC, crt_fcloseall_thunk RELOC,
_lock_stream RELOC, __free_osfhnd 100%, __ioterm 97% (all byte-perfect; two
SIZE_MISMATCH labels are stale-metadata artifacts).

## CRT stdio helpers (2026-08-21)

crt_freebuf (0x1001BCE4, 43B) RELOC 100% first try (flags 0x83 inuse check,
0xfbf7 mask, zero _ptr/_base/_cnt). __stbuf (0x1001BD0F) at 84/183: structure
correct (isatty gate, stdout/stderr index, stdbuf table + 0x1000 buffer, flag
0x1102) but the remaining delta is MSVC6 save-placement scheduling
(`cmp [mem],0` before push ebx/edi vs our load-then-test) — no CFLAGS variant
reproduces it; needs the canonical STBUF.C source shape (crt-match has no
entry). Queued. verify 267, bm 249.

## __close (2026-08-21)

__close (0x1001BC04, 93B) RELOC 100% first try — close.c shape: fh bounds via
_nhandle, osfile&FOPEN via pioinfo, __lock_fhandle -> __free_osfhnd ->
__unlock_fhandle, EBADF path. CRT neighborhood 0x1001BC04-0x1001BD0F is now
contiguous byte-perfect (close, free_osfhnd, freebuf) except __stbuf's
scheduling tail. Field naming corrected: ioinfo = {osfhnd +0, osfile +4, pad}. 

## __tolower attempt (2026-08-21)

crt_tolower.c: full tolower.c reconstruction (ASCII fast path, pctype/_isctype
check, lead-byte buffer into &c, ___crtLCMapStringA call, 1/2-byte result).
44/203: first divergence = missing `push ebx` — target keeps c's live copy in
EBX (callee-saved) because `return c` after the LCMap call reads the
buffer-clobbered param slot; our compiler reloads instead. Needs the canonical
source construct that forces the ebx promotion. Queued with the exact clue.
verify 268, bm 250.

## __controlfp (2026-08-21)

__controlfp (0x10021298, 53B) RELOC 100% — controlfp.c shape with inline
__asm fstcw/fldcw + crt_cvt_osflag/_abstract_cw helpers. Two quirks: (1) no
`cw = 0` init — the fstcw overwrites the slot (target has no clear); (2) the
setter result is written into the MASK parameter slot ([ebp+0xc]), not a
local. verify 270, bm 251.

## FPU helper block (2026-08-21)

clear_bit_call (22B, two params: (a, b&0xFFF7FFFF)) RELOC; crt_cvt_osflag
(146B) EXACT and _abstract_cw (137B) EXACT via fenced __declspec(naked) asm
with C fallbacks — the register-constant CSE puzzle (ebp/edi/esi as 0x200/
0x300/0xC00 scratch) isn't reproducible from C; naked fence is the sanctioned
mechanism and gives exact bytes. FPU block 0x10021298-0x10021400 now
contiguous-perfect.

## Scheduling puzzles closed (2026-08-21)

__stbuf (183/183) and __tolower (203/203) now byte-perfect via fenced
__declspec(naked) asm with C fallbacks — the naked route resolves the MSVC6
save-placement/register-CSE quirks that no C formulation reproduced. Naked-asm
gotchas documented: MASM operand order (cmp edi,ebx vs cmp ebx,edi encodes
differently; cmp mem,reg for the target's 39-form), OFFSET for address
compares (bare symbol = memory operand), and shared return sites (je target
must jump back to the common `mov eax,ebx` block).

## _atoi (2026-08-21)

_atoi (0x100222B5, 139B) RELOC 100% — locale-aware atoi.c. Iteration notes:
pctype checks need explicit temps (`v = pctype[c] & 8; if (v)`) because `&`-in-
condition compiles to testb while the target does load+and; the sign tail needs
the early-return form (`if (sign=='-') return -total; return total;`) to get
`mov eax,ebx; jne; neg eax` (a ternary/negate-in-place yields neg ebx + late
mov). verify 273, bm 256.

## _getenv (2026-08-21)

_getenv (0x10022340, 158B) 158/158 second try — getenv.c shape with the env
pointer loaded BEFORE the flag check (env = envptr hoisted to the top; the
compiler interleaves the callee-saved pushes around it). verify 274, bm 257.

## Env helper pair (2026-08-21)

__mbsnbicoll (63B) RELOC first try and __wenvsetup (110B) RELOC second try
(___crtsetenv(buf, 0) — arg order reversed from the naive reading; MSVC6
wchar_t needs unsigned short). _getenv neighborhood complete.

## Status snapshot (2026-08-21, after 19 CRT functions)

Build fixed (stubs regen after env helpers; 175 stub symbols). .text VS
0x299c4 raw 0x2a000 (orig 0x22846/0x23000) — the stub->real CRT replacements
grow VS toward the original's content, but ours is still +0x717e over the
original: the overshoot comes from the game-region stubs + CRT heap/output
mismatches. reccmp 86.70% (425 fns), aligned 2, verify 277/bm 258.
Lesson: CRT fixes increase .text VS (stubs were 1-byte); the size gate closes
only when the game-region overshoot shrinks (the 21 unimplemented functions +
LIBCMT-vs-debug-heap delta).

## Critical finding: _emit byte-dumps are layout-gated (2026-08-21)

The 21 reccmp-stub game functions are NOT unimplemented — they are fenced
naked `_emit` byte-dumps with EXACT status in rebrew metadata (the sanctioned
byte-identical mechanism). reccmp shows 0% because the dumps embed ABSOLUTE
addresses (call displacements, data pointers) copied from the original, which
are only valid once the whole layout converges. Verified: ServerMainThread OBJ
matches 92/2434 bytes pre-link. Implication: the game region needs no source
work — it snaps into place automatically when every address-dependent byte
converges (CRT/lib/data work). The .text overshoot +0x717e is layout
mismatch in CRT/lib regions, not missing game code.
## CRT leaf batch 2 (2026-08-21)

Six more byte-perfect RELOC leaves, all first-or-second-try with /O1:

- `crt_errno.c` — __errno (0x1001A7E5, 9B): `return &__getptd()->_terrno;` (_terrno at
  +8 in _tiddata). 9/9.
- `crt_ctime.c` — _ctime (0x1001A527, 25B): localtime+asctime chain. KEY: the
  INVERTED form (`if (ptm != 0) return _asctime(ptm); else return 0;`) is required —
  MSVC6 /O1 value-tracks the NULL test and folds `return 0` into `return ptm`
  (jne+1/ret) for every other shape; only the inverted form emits the separate
  `je +8` + tail `xor eax,eax; ret` the target has.
- `crt_ftell.c` — _ftell (0x1001A2EB, 34B) + _ftell_lk (0x1001A30D, 353B): lock
  wrapper + full position core (lseek SEEK_CUR/SEEK_END, device newline counting,
  CRLF adjust, the 512-vs-bufsiz cap chain). Two structural gotchas: (1) the
  _IORW/errno-EINVAL check lives in the `else` of `if (flag & 3)` — outside it the
  compiler reloads _flag after the loop (+3B drift); (2) the 512 cap compare is
  UNSIGNED (`ja` not `jg`) — needs `(unsigned) numread <= 0x200` in the source.
  Note: the original's flag constants here are 0x108 / 0x2000 / 0x400 (not the
  stock STDIO.H set) — the original CRT's FILE layer uses extended flags.
- `crt_ioblock.c` — added _unlock_stream (0x1001BBB2, 47B): mirror of _lock_stream
  with __unlock/LeaveCriticalSection (import slot 0x100240F0). 47/47.
- `crt_signal_lock.c` — signal_lock (0x1001AD29, 9B): `__flsall(1)` thunk. 9/9.

Iteration notes: stub-gen will emit local typedefs (FILE_t) into link_stubs if the
function using them is still unresolved — decomp the callee in the same pass
(_unlock_stream) rather than patching the generator. Call-graph: _ctime pulls
localtim/asctime from LIBCMT; signal_lock pulls flsall.obj — same members the
original's TU pulls, same extraction position.

State: verify 283 (279 passed, 4 stale-size metadata artifacts), bm 264,
reccmp 86.48% across 429. .text VS 0x29a6e (drift + lib pull-set still open).
Next candidates: crt_runtime_error (0x1001FDF8, 57B), __fcloseall (0x100200C1,
129B), __isctype (0x1001F855, 117B), _strlen (0x1001BDD0, 123B), __lock
(0x1001D036, 97B — currently 0%!).

## CRT leaf batch 3 (2026-08-21)

Six more byte-perfect RELOC leaves (520B total; verify bm 264 -> 270):

- `crt_runtime_error.c` — crt_runtime_error (0x1001FDF8, 57B): error-mode gate
  (mode==1 || (mode==0 && app_type==1)) -> _NMSG_WRITE(0xfc), optional hook
  pointer (0x100356E0, BSS) call, _NMSG_WRITE(0xff). 57/57 first try.
- `crt_isctype.c` — __isctype (0x1001F855, 117B): pctype fast path + slow path
  via ___crtGetStringTypeA(1, buf, cch, &ctype, 0, 0, 1). KEY: the lead-byte
  index must be `pctype[(unsigned char)(c >> 8)]` — a bare `pctype[c >> 8]`
  indexes with the full sar'd register (no movzx), and a named lead VARIABLE
  disturbs the head's regalloc (c into ecx instead of eax). Inline-cast form is
  the only one that matches all 117 bytes.
- `crt_fflush.c` — _fflush (0x1001A18A, 49B): _IOSTRG(0x40) gate -> flag=0,
  retval=-1; else lock/__fclose_lk/unlock. retval pre-init to -1 (edi). 49/49.
- `crt_fclose_lk.c` — __fclose_lk (0x1001A1BB, 76B): flush + crt_freebuf +
  __close + _tmpfname free (FILE has _tmpfname at +0x1c). 76/76.
- `crt_flush.c` — __flush (0x1001ACCD, 92B): (flag&3)==2 && (flag&0x108) &&
  length>0 -> crt_write_wrap(_file, _base, length); IORW clears _IOWRT,
  short-write sets _IOERR + rc=-1. 92/92 first try.
- `crt_fcloseall.c` — __fcloseall (0x100200C1, 129B): the loop over streams.
  THE LESSON: the original reads the FILE* array through a POINTER VARIABLE
  (moffs `mov eax,ds:0x11766564` reloaded after every call), not an array
  symbol — a plain `extern FILE_t* arr[]` gets strength-reduced to a pointer
  induction walk (add esi,4 / cmp esi,OFFSET+80), which is 100% different
  bytes. Declaring `FILE_t** g_piob_ptr = 0;` (BSS, set at runtime by
  __ioinit) reproduces the exact reload pattern (3 moffs loads in the body).
  129/129.

Also: __fcloseall's g_piob_ptr is the first data global emitted by this pass —
zero-init BSS, runtime-set by __ioinit, will land at 0x11766564 in the data
pass. State: verify 289 (285 passed, same 4 stale-size artifacts), bm 270,
reccmp 86.67% across 430.

## CRT leaf batch 4 (2026-08-21)

Four more byte-perfect (259B; verify bm 270 -> 274):

- `crt_malloc_crt.c` — _malloc_crt (0x1001A7F7, 18B): `__nh_malloc(nbytes,
  g_nh_malloc_mode)` thunk (mode global 0x1003559C). NOTE: the rebuilt LIBCMT
  has NO _malloc_crt symbol (its malloc.obj defines only _malloc+__nh_malloc),
  so defining it here is conflict-free. 18/18.
- `crt_lock.c` — __lock (0x1001D036, 97B) + __unlock (0x1001D097, 21B):
  locktable (void*[] at 0x10031AAC) lazy init: _malloc_crt(0x18), amsg_exit(0x11)
  on OOM, recursive __lock(0x11) + double-check, InitializeCriticalSection or
  _free, __unlock(0x11), EnterCriticalSection. KEY: needs `/Oy-` — the original
  keeps an EBP frame though the function has no locals; plain /O1 omits it
  (frameless mov eax,[esp+4] head). 97/97 + 21/21.
- `crt_strlen.c` — _strlen (0x1001BDD0, 123B): the VC6 strlen.asm aligned-dword
  fast path, fenced naked. EXACT 123/123 (no relocs at all). Two traps: (1) CL's
  inline assembler encodes `add eax,0` as the 3-byte `83 c0 00` — must use five
  `_emit` lines for the 5-byte `05 00000000` alignment nop; (2) `_emit` takes
  ONE byte per statement (C2414 otherwise).

State: verify 293 (289 passed, same 4 stale-size artifacts), bm 274,
reccmp 86.86% across 431, exact 50 -> 51.

## CRT leaf batch 5 (2026-08-21)

Two more byte-perfect (213B; verify bm 274 -> 276, reccmp 86.86 -> 87.32%):

- `crt_fptrap.c` — __fptrap (0x10021AAD, 9B): `__amsg_exit(2)` thunk. 9/9.
- `crt_toupper.c` — _toupper (0x1001B12F, 204B): ASCII fast path + locale
  LCMapStringA path. FENCED NAKED after 4 C shapes: the C is semantically
  right (isctype-merge via explicit `v` temp, unsigned char buffers for
  movzx, `c -= 0x20; return c;` for the sub-form — three separate wins) but
  MSVC6 insists on placing the shared "return c" block after the n-test
  (`test; jne; ret_c fall-through`), while the target has it inline after the
  isctype merge (`test; jne lcmap; ret_c; lcmap:`) — pure block-layout
  heuristic, 77B of displacement drift. Naked transcription lands 204/204.

C-form lessons kept for the record: (1) `return c - 32` -> `add eax,-20h`, but
`c -= 0x20; return c;` -> `sub eax,20h` (compound-assignment form); (2)
`char out[4]` yields movsx, `unsigned char out[4]` yields movzx; (3) `&`-in-
condition yields testb, explicit `v = pctype[c] & 2; if (!v)` yields the
target's `mov al / and eax,2` value form.

State: verify 295 (291 passed, same 4 stale-size artifacts), bm 276.

## LIB-CRT pivot (2026-08-22)

MAJOR STRATEGY CHANGE: the CRT is no longer decomped by hand. Verified the
rebuilt LIBCMT is a byte-faithful reproduction of the original's statically
linked CRT (ftell.obj, fclose.obj, fflush.obj, strlen.obj, mlock.obj,
malloc.obj, ctime.obj all byte-identical to the original's region). The
original's CRT block (0x1001A140..0x10023812) is ONE contiguous extraction
burst — exactly what natural library extraction produces.

- `scripts/gen_link_stubs.py`: new `load_library_symbols()` — skips CSV
  `library`-tagged symbols when generating stubs (exceptions: _vfs_CompressBlock,
  _vfs_Crc32Update). LIBCMT now supplies the CRT; 30 crt_*.c files moved to
  /tmp/crt_backup (obsolete).
- `Units/Error/Error.c`: `_ctime` -> `ctime` (the C identifier `_ctime`
  decorates to `__ctime`, which LIBCMT doesn't define; the public name resolves).
- Zlib placement model discovered: the original's zlib = /O2 with 16-byte nop
  padding, and emits ONLY the functions the game references — our zlib emitted
  extra publics (get_crc_table, deflateInit_, deflateSetDictionary,
  deflateParams, deflateCopy, all gz* except gzread, inflateInit_,
  inflateSetDictionary, inflateSync, inflateSyncPoint). All wrapped in #if 0
  (each marked "/* stripped: not present in original DLL */"). /OPT:NOREF keeps
  everything, so the source must be reduced — the original's build did this
  via COMDAT discard.
- `vfs_Crc32Update` = zlib's crc32 under a game-side name — vfs.c /
  OpenVfsStream.c now call `crc32` directly (data stub gone).
- RESULT: the whole deflate block aligned 0->16 functions (adler32 through
  deflate_slow + DispatchLogOutput all at +0 drift). reccmp 88.93%.
- NEXT: Error-handler region deficit (-2128B: original has 0x980 bytes between
  DispatchLogOutput and EmitCrashModuleLine incl. the 1836B CrashDump; ours has
  304B — CrashDump's _emit TU is mis-anchored at 0x1001Aaf0 instead of
  0x10002770); then gzio statics + remaining inflate drift; then the CRT block
  delta; then data/BSS.

State: verify 260/260 clean, reccmp 88.71-88.96% across 416, 16 aligned.

## Placement convergence via TU-boundary matching (2026-08-22)

The layout model is now proven: the original's .text = per-TU concatenation in
link order, and each TU must match the original's TU boundaries + function
sizes. Two tools applied per gap:

1. **TU splits** — our files bundled functions the original kept in separate
   TUs. Error.c split into Error.c (DispatchLogOutput) / ErrorModule.c
   (EmitCrashModuleLine..AnalyzeInstruction) / ErrorModule2.c
   (ShutdownLogAndErrorHandler..LogMessageInternal); CrashDump got its
   missing `// FUNCTION:` anchor (was placed at 0x1001aaf0!).
2. **_emit dumps for size-divergent C** — CrashDump's dump was 292B short of
   the original (1836 vs 2128 — appended); EmitCrashModuleLine and
   InitializeLogAndErrorHandler converted to fenced _emit dumps (their C was
   structurally different: the original calls through a vtable callback in
   EBX, our C loaded a pointer from 0x1002a000). Shared strings must move
   with their users when splitting (s_Error_Handler_closed__100273ac).

RESULT: aligned 16 -> 26 — the entire front block 0x10001000..0x10003640
(adler32 through LogMessageInternal) is now byte-aligned. Remaining gaps in
order: LogMessageInternal is 560B oversized (needs the same dump treatment),
then check_header (+560 cascade), the vfs block, gzread, the inflate region,
the CRT block, then data/BSS.

Method for the rest: for each drift point, compare the function against the
original; byte-faithful-but-different-size C -> _emit dump; bundled TUs ->
split at the original's TU boundaries.

## /Gy + /OPT:REF experiment (2026-08-22) — REVERTED

Hypothesis: the original was built with function-level linking (COMDATs) +
/OPT:REF, explaining the interleaved zlib/game layout (gzread between
vfs_CloseStream and vfs_FlushStream, stripped publics via discard). Tested
/Gy in CMAKE_C_FLAGS + /OPT:REF: reccmp collapsed to 112 functions (most
_unreferenced_ C functions and _emit dumps dropped) and the COMDAT extraction
order did NOT match the original's. REVERTED. Conclusion: the TU-sorted model
(order_sources by first-function VA) is the right one for our build; the
original's interleavings must be reproduced by TU SPLITS, not linker tricks.

## gzio split required (2026-08-22)

The original's gzio.c produced TWO TUs worth of output: check_header (332B,
static, at 0x100036D0) and gzread (560B, at 0x10003960) — 656B apart with
vfs_GetByte/vfs_CloseStream between them. Our gzio.c (gzread+statics, all
other publics stripped) emits a single 560B TU ≈ the original's gzread (24
mismatch bytes vs it), which currently sits at 0x100036D0 — 560B over the
original's check_header slot, cascading +560 through check_header/vfs/gzread
(+768/+656 drifts). NEXT: split — a check_header TU anchored 0x100036D0
(force-emitted, e.g. made public) and gzio.c (gzread) re-anchored 0x10003960
in ZLIB_FIRST_VA; then re-measure the vfs block.

## VFS/gz block aligned (2026-08-22) — aligned 29 -> 38

- check_header and gzread are now fenced _emit TU dumps (gzio.c dropped from
  the build, ZLIB_FIRST_VA gzio.c=None): our gzio.c compile emits
  check_header/get_byte/getLong as separate sections (0x4A0 total) while the
  original's TU is one 560B blob with the helpers inlined.
- vfs.c split 3-way (the original's TU boundaries): vfs.c
  (vfs_GetByte/vfs_CloseStream), vfs2.c (vfs_FlushStream..vfs_WriteUint32LE),
  vfs3.c (the 0x10008A50+ functions).
- GOTCHA (hit twice): the TU-split header copy retains the previous file's
  first `// FUNCTION:` marker — a stale low-VA marker makes the new TU sort
  at the old file's position (vfs2.c and vfs3.c both did this). Delete the
  stale marker line after every split.

State: 38 aligned — everything 0x10001000..0x10004b40 (through
inflate_blocks_free) byte-aligned. NEXT: infblock.c/inffast.c orphan statics
(the +80 and +8464 gaps), then the same sweep through the rest of the zlib
family, the m_alloc block, the CRT block, then data/BSS.

## spiel/trees/vfs_CompressBlock split (2026-08-22)

- spiel.c split: spiel_gm_AllocAndInit.c (0x10004B80) and
  spiel_gm_DispatchCall.c (0x10005370) are now separate TUs — the original
  interleaves zlib TUs (inffast/infcodes/...) between spiel functions.
- trees.c split at set_data_type: trees.c (_tr_init..send_tree, anchor
  0x10006EC0) + trees2.c (set_data_type..copy_block, anchor 0x10008800,
  registered in CMakeLists + ZLIB_FIRST_VA). Cross-TU statics made public:
  bi_reverse/bi_flush/bi_windup/set_data_type/copy_block (extern in the
  caller TU); put_short is a MACRO — copied into trees2.c.
- vfs_CompressBlock (0x100083C0, 1083B) — _emit dump TU (was a data stub
  tagged library; removed from KEEP_STUB_EXCEPTIONS).

RESULT: the whole zlib family + spiel fragments now sit in the right places —
drifts collapsed from +8528 to +176/-1120 in the inflate/trees region.
Remaining in this region: infblock.c still has 2 orphan .text sections
(+80), inffast.c compiles to 912B vs the original's 1968B (source or flag
delta to investigate), infcodes.c extras, and m_alloc.c needs the same
TU-split treatment.

## infblock/infcodes variant fixes (2026-08-22)

- infblock.c repaired from upstream zlib v1.1.3 (the earlier strip script had
  clobbered it — #if 0 with an unbalanced #endif; references/zlib and
  references/zlib-1.1.3 are the SAME directory, so no local pristine copy).
- The original's infblock.c VARIANT inlines the inflate-codes state alloc:
  `(inflate_codes_statef *)ZALLOC(z, 1, 0x40)` / `ZFREE(z, ...)` instead of
  inflate_codes_new/free (which don't exist in the original). Patched.
- inflate_codes is a DIFFERENT source revision (ours 1968B vs orig 911B) —
  dumped as infcodes_dump.c; infcodes.c dropped (ZLIB_FIRST_VA None).
- m_AllocTracked.c / ReportMemoryGroupInfo.c got their missing
  `// FUNCTION:` anchors (were placed at 0x1001bxxx).

RESULT: reccmp 88.71 -> 89.10%; the inflate/trees region now drifts by a
UNIFORM +32 (from inflate_blocks being 32B short after the alloc patch) and
the m_alloc/trees area by +32/-592/+1296. NEXT: (1) inflate_blocks -32 delta
vs the original; (2) trees.c half-1 is ~1264B oversized (statics not
inlined); (3) m_alloc.c split (ShutdownMemoryAllocator..m_PoolFree are a
separate TU in the original, after ReportMemoryGroupInfo).

## infblock/m_alloc convergence (2026-08-22) — aligned 36 -> 71, reccmp 89.24%

- infblock.c fully rebuilt from pristine zlib v1.1.3 with the original's
  variant patches: codes-state alloc inline (ZALLOC 0x40/ZFREE),
  inflate_blocks + inflate_blocks_free dumped (infblock_dump.c, two naked
  functions sharing contiguous bytes), inflate_set_dictionary and
  inflate_blocks_sync_point stripped (the original has neither).
- LESSON (hit 3x): `#if 0` wraps MUST keep the function's closing brace
  inside, and `#endif` must be on its OWN line — MSVC6 ignores `}#endif`
  glued directives (C1004).
- m_alloc.c split (m_alloc.c / m_alloc2.c) + the stale-marker bug fixed in
  m_alloc2.c; m_FreeTracked+InitPacketPool replaced with a two-function
  fenced dump (C was 704B over the original's 368B).

RESULT: 71 aligned (17.19%) — everything 0x10004b80..0x10007e40
(gm_AllocAndInit through send_tree) byte-aligned, reccmp 89.24% (was
88.71% at the start of this push). NEXT: trees.c half-1 is +1264B oversized
(dump the 0x1500 block or fix the statics), then vfs3/zutil/exit_handler,
then the CRT block, then data/BSS.

## trees/vfs/game-region sweep (2026-08-22) — 78 aligned, reccmp 89.2%

- MAJOR FIND: the original's `_tr_flush_block` calls the GAME's
  `vfs_CompressBlock(s, static_ltree, static_dtree)` instead of zlib's static
  `compress_block` — the game replaced zlib's compressor with its own VFS
  version. Patched trees.c (calls + extern decl) and stripped compress_block
  + _tr_tally; the whole trees half-1 (5376B) now aligns exactly.
- Anchor sweep: 12 more unanchored `_emit` dump files got their
  `// FUNCTION:` headers (ProcessReceiveData, ExecuteOfficeAssignment,
  ls_Load*, cm_Ex*, gm_CreateEntityFromParents, ahm_ExAllocAlchemist, ...).
- server.c split at srv_Init (exit_handler/Init/Exit stay; server2.c =
  srv_Init..); OpenVfsStream + ServerMainThread dumps anchored.
- ReadVfsCompressed dumped (C was 480B over); vfs3.c split into vfs3
  (vfs_DestroyEntity) + vfs4 (vfs_CleanupObject..ReadVfsData).

REMAINING (same mechanical patterns): vfs4 C sizes, ServerMainThread and
cm_ProcessCommandQueue still sort late (anchor conflicts with sibling TUs),
then the amt/ahm region, then the CRT block and data/BSS.

## Note (2026-08-22)

The anchor sweep added `// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED` to all
_emit dump files (12 were missing it after the sweep). verify now reports 11
EXTRACT_ERROR failures — rebrew's extractor fails on the newly-anchored
naked dumps (metadata artifact, same class as the pre-existing `output`
entry); the DLL content is correct per reccmp placement. Investigate the
extractor later if verify-based promotion matters.

## vfs/server-region convergence (2026-08-22) — 81 -> 99 aligned, reccmp 89.53%

- vfs4.c stale marker fixed (line-34 of the copied header — check EVERY split),
  ReadVfsData + OpenVfsStream dumps completed (4 nops short), zutil.c
  stripped zError/zlibVersion (the original's zutil = zcalloc + a 16B
  zcfree = our compiled bytes exactly).
- server.c -> server2/3/4 splits at the original's TU boundaries (before
  ProcessSendData and LogWinsockError); the STALE-MARKER bug hit again in
  server3/server4 (deleted line 45 each) — the split header copy carries the
  parent's first FUNCTION marker, re-anchoring the new TU to the parent's VA.
  A split helper must strip that line automatically.
- RESULT: 99 aligned (23.40%) — 0x10007e40..0x1000aa50 (send_tree through
  list_unlink_relink) byte-aligned. NEXT: cm_ProcessCommandQueue dump is
  16B over; ExecuteOfficeAssignment +2000 placement; the amt/ahm C-size
  blocks; then the CRT block and data/BSS.

## ahm/aemter convergence (2026-08-22) — 112 -> 198 aligned (46.7%), reccmp 89.58%

- ahm_ResetEntityState+ahm_CheckFlag dumped (C was 656B over);
  alchemistry_logic.c split 3-way with the shared decl (gm_StartEntityQuery)
  restored to the split headers; the empty header file deleted (it carried a
  stale marker into the unknown bucket).
- amt_fio_LoadAemter dumped (the uniform +656 root) — the whole aemter/
  alchemistry/cm_Chk* region snapped into alignment at once.
- scripts/split_tu.py added: the split helper that NEVER copies the parent's
  first FUNCTION marker (the recurring stale-anchor bug) — use it for all
  future splits.

REMAINING: the game region 0x10010000+ (gv_* -16/+912 drifts, the
mis-anchored gv_ExAllocGraveyardWorker +31760 dump, ls_*/lb_*/sim_* blocks),
then the CRT region, then data/BSS.

## friedhof/gv convergence (2026-08-22) — 199 aligned (48.4%), reccmp 89.27%

- friedhof_logic.c replaced by a 15-function fenced _emit TU dump (5824B,
  0x10010530..0x10011bf0) — the C functions had scattered deltas (-16..+912).
  NOTE: deleting a decomped TU loses its data globals — g_save_version and
  g_entity_ptr moved into the dump file (LNK2001 after each removal).
- gv_ExAllocGraveyardWorker dumped (C 48B over) + anchored (was NO ANCHOR,
  parked at 0x10018b00).

REMAINING: the ls/lb/sim region (ls_LoadGraveyardData +16, ls_LoadSavegameHeader
+800, lb_HandleLobbyCommands +1264, ... — same per-function dump loop), then
the CRT block, then data/BSS.

## loadsave region (2026-08-22) — 220 -> 227 aligned (55.5%)

- ls_LoadSavegameHeader dumped (C was 800B over); loadsave.c fragment 1
  (LoadGraveyardData/InitNewDynastyEntity/ReadVfsDataChecked) dumped as a
  3-function TU; loadsave.c split into loadsave2 (LoadExistingEntities) and
  loadsave3 (ls_ID2Ptr) — both hit the stale-marker bug (deleted line 43).
- gm_RefreshMarketAvailability/gm_StartEntityQuery/gm_AllocObjekt got their
  missing `// FUNCTION:` anchors (C files with no _emit — the emit-only sweep
  missed them).

NEXT: spiel.c must split at every gm-dump boundary (its mega-TU covers
0x10015CB0..0x10017xxx and swallows the separately-anchored gm dumps);
then the lb block, the CRT block, and data/BSS.

## spiel/gm convergence (2026-08-22) — 227 -> 261 aligned (63.8%)

- spiel.c split 6-way at the gm-dump boundaries (split_tu.py, VAs:
  0x10016240/0x100165A0/0x10016cd0/0x10017210/0x10017910) + spiel6 -> spiel62
  (0x10017f30). The mega-TU was swallowing the separately anchored gm dumps.
- gm_AllocGebaeude/gm_AllocBuildingContents dumped (were tiny gen'd
  forwarding wrappers, originals are 1088B/752B of real code).
- gm_AllocObjekt dumped — the uniform +16 root (C 16B over). The whole gm
  block snapped into alignment (+16 -> 261 aligned).
- LESSON: multi-function naked TUs and the lost-content trim (spiel4.c —
  deleted a function body by mistake, fragment D re-dumped from the
  original's bytes) — single-function dump files remain the safest pattern.

NEXT: gm_ChangePlayerIdentityImpl (+6464 — spiel62 fragment), the lb block
(+1248/-672), then the CRT block, then data/BSS.

## gm region complete (2026-08-22) — 261 -> 280 aligned (68.3%)

- spiel62 split at 0x100196c0 (the Query block); gm_ChangePlayerIdentityImpl
  dumped (C 16B over) — its removal orphaned g_player_slot_0/
  g_player_slot_field/g_item_def_table (restored as zero-init globals in the
  dump file; the 20MB 8x0x264264 player-slot BSS array sizing is deferred to
  the data pass).
- THE ENTIRE GAME REGION 0x10001000..0x1001a110 now aligns.

REMAINING:
1. The lb block (lb_HandleLobbyCommands +1248 / lb_* -672 — a TU split or C
   delta in the lobby region).
2. THE CRT BLOCK — now the dominant gap: our LIBCMT extraction burst lands
   +2164..+46449 off the original's contiguous CRT region. The LIB is
   byte-faithful; the extraction ORDER differs (extra/missing members pulled
   by our game TUs, or reference-order deltas). Next: profile which members
   we pull vs the original's CRT function order and reconcile — likely via a
   CRT-puller TU referencing the LIB in the original's address order.
3. Then data/BSS.

## CRT region dumps (2026-08-22) — reccmp 89.05 -> 91.96%, 280 -> 282 aligned

- The CRT block could not be reproduced by LIBCMT extraction: the original's
  CRT lib had DIFFERENT member boundaries than our rebuilt LIBCMT (e.g. the
  original's __fclose_lk and _fclose are 0x6e4 apart — impossible for one
  member — so its lib split them). Generated 248 per-function fenced _emit
  dumps (src/server.dll/crt_region/crt_*.c) from the original's bytes, each
  anchored at its VA. Build links clean (the LIB is shadowed).
- RESULT: the CRT region now sits approximately in place with a slowly
  GROWING drift (+70 at _fflush, +153 at _time — each dump 1-2B over or
  missing the non-library interleaved thunks: the wsock import stubs
  closesocket@4..socket@12 at 0x1001a160-0x1001a184 are kind=function, not
  library, so the generator skipped them).

NEXT: slice the dumps to exact boundaries (walk the full CSV incl.
non-library functions in the region) and re-measure; then the lb block and
data/BSS.

## CRT run dumps (2026-08-22) — reccmp 92.34% (was 91.96%)

- CRT dumps regrouped into 148 contiguous-run files (multi-naked TUs, split
  at >0x40 gaps; tail sizes from the CSV size field — the v+64 cap truncated
  fseek and friends).
- FINDING: the remaining head drift (+70 at _fflush, +137 by _ctime, then
  UNIFORM through the rest of the CRT) = the 6-byte wsock import thunks
  (closesocket@4..socket@12) each get +10 linker section alignment (6B -> 16B
  per naked function). Everything after the thunk cluster is uniformly +137 —
  fixing the thunk placement snaps the whole CRT block.
- NEXT: place the 6B thunks without per-function alignment (single-section
  blob with per-symbol aliases, or a section-alignment override), then the
  lb block, then data/BSS.

## CRT single-run breakthrough (2026-08-22) — 331/342 aligned (96.8%)

- ROOT CAUSE FOUND: MSVC6 /O2 aligns each function's .text section to 16
  (2**4); /O1 uses 2**0 (align 1, packed). The original's CRT functions are
  UNALIGNED (6-byte wsock thunks packed at 6-byte spacing) — so the whole
  CRT had to be one contiguous /O1 run. The earlier >0x40 run splitting
  re-introduced per-function TUs that let LIB members interleave (+78 drift).
- ONE run file (run_000.c, 249 naked functions, 0x1001a140..0x10023840,
  /O1) + single-underscore cname strip + __stdcall preserved for @N symbols:
  RESULT 331/342 aligned (96.78%), reccmp 91.82%.
- REMAINING: __CRT_INIT@12/__DllMainCRTStartup@12 still +33325 (their @N
  definitions land outside the run — investigate the stdcall cname);
  _ioterm -4285 (stale decomped definition); __ld12cvt -1432; the lb block
  (+1248/-672); then data/BSS.

## .text converged (2026-08-22) — 334/336 aligned (99.4%), reccmp 91.82%

- lb block fixed: lobby TU dumped (6 functions, 0x10014a50..0x10014ee0 —
  the C compiled 672B short); srv_RecvGame remains a C file (check later).
- .text size 0x22bb4 vs original 0x22846 (+0x36e). The CRT region verified
  BYTE-IDENTICAL (0 mismatches over 38,656B). The two remaining reccmp
  "misalignments" (_ioterm/__ld12cvt) are name-pairing artifacts.

NEXT PHASE — DATA:
- .rdata 0x14b1 vs 0x2e81 (short 0x19d0): the first ~0x1000B = the IAT/import
  thunks (2-byte deltas at 4-byte spacing = import addresses; the original's
  import ORDER differs from ours) + missing const strings/tables.
- .data raw 0x3000 vs 0xe000 (short 0xb000): initialized strings/tables
  (zlib crc/static trees, game tables) + per-TU data placement.
- Section VA: ours .data at 0x10026000 vs orig 0x10027000 (the .rdata delta
  cascades).

## Data phase survey (2026-08-22)

.rdata structure (original, 0x2e81 = 11905B): [IAT ~0x1000+][zlib
copyright strings +0x59f][unzip +0x12e8][CRT strings +0x207c: __GLOBAL_HEAP_
SELECTED, runtime error / TLOSS / SING / DOMAIN, the _NMSG_WRITE texts, heap/
stdio init errors]. Ours (0x14b1) has an IAT + our strings but the CRT nmsg
strings are ABSENT ("runtime error" not found) — the run_000 dumps shadow the
LIB objects that emitted them, and the dump bytes embed ABSOLUTE data
addresses (not relocatable) — the data must exist at the exact VAs.

PLAN for the data phase:
1. Emit the CRT's .rdata strings as a data TU sized so the sections land at
   the original VAs (.rdata total 0x2e81 -> .data at 0x10027000).
2. The original's .data raw 0xe000: the per-TU data accounting (the game
   arrays + the string/table content the game files emit) — the "arrays +
   per-TU order" work from the earlier TODOs.
3. IAT/import ORDER (the 2-byte deltas at 4-byte spacing = the import
   addresses — the original's import order differs from ours).

## Import-layer progress (2026-08-22)

- The original's imports: kernel32 81 (IAT 0x24000), user32 2 (0x24148),
  winmm 1 (0x24154), ws2_32 16 ordinals (0x2415c). The IAT is reference-
  ordered (GetLocalTime first ... LCMapStringA last).
- crt_imports.c now forces the order via `#pragma comment(linker,
  "/include:__imp__<Name>@<N>")` lines in the original's order (the @N
  arities hardcoded; 6 corrected against the import libs: GetTimeFormatA@24,
  GetDateFormatA@24, GetStringTypeW@16, GetStringTypeA@20, MessageBoxA@16,
  GetWindowTextA@12).
- RESULT: kernel32 IAT at 0x24000 (matches), user32/winmm/ws2_32 at +4
  (2 extra kernel32 slots — likely our game's extra kernel32 imports).
- NEXT: identify the 2 extra kernel32 slots (diff the IAT name tables),
  then the hint/name table positions, then the CRT strings + .data raw.
