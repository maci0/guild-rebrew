# Goal — 100% Byte-Identical server.dll, Europa1400Gold_TL.exe, AND Europa1400Gold.exe Recompilation with a rebuilt unified source tree matching what the original devs most likely had.

Tracked as goal `goal-dd7dd2dd-8cde-4e14-a043-8674d4ec5631` (revision 21, 65/256 rounds).
This file is the durable copy: if the session goal state is ever lost, re-create it from here.

## Priority and focus

- **Priority order: server.dll first, then Europa1400Gold_TL.exe, then
  Europa1400Gold.exe.** All three must reach 100% byte-identical, but the focus
  of day-to-day reversing is GOLDTL — the TL client — not GOLD.
- **The primary deliverable is the unified shared source tree** — the tree the
  original developers most likely had, where shared game logic lives once and is
  compiled into every target. Per-target .exe bytes are the scoreboard that
  validates that tree; the tree itself is the goal.
- **Exploit the GOLD ↔ GOLDTL code overlap.** Both are clients of the same game
  engine: a large share of functions is byte-identical between the two, only at
  different VAs. Every function matched in one client should be transferred to
  the other via `rebrew source import-related --from <src> --target <dst>` (structural
  match, no recompile), so the shared source file (one marker per target) covers
  both. Never reverse the same function twice in both clients.
- GOLD remains onboarded and verified, but after the shared-tree buildout it is a
  validation target, not where new reversing effort is spent.

## Targets

- Reproduce server.dll (PE, x86-32, MSVC6) from C source with 100% byte-identical
  output: every function EXACT, every data byte matching, link producing reference
  .text VirtualSize 0x22846 and raw output identical to the reference, with
  linked EXACT and data verification retained as supporting checks.
- Reproduce Europa1400Gold_TL.exe (PE, x86-32, MSVC6) from C source with 100%
  byte-identical output: every function EXACT, every data byte matching. This is
  the active reversing focus.
- Reproduce Europa1400Gold.exe (PE, x86-32, MSVC6; onboarded rebrew target,
  binary at original/Europa1400Gold.exe) with 100% byte-identical output: every
  function EXACT, every data byte matching. Feed it from the shared tree +
  cross-import; do not reverse it in isolation.
- Rebuild the unified shared source structure the original devs most likely had:
  one shared source tree serving all three targets, shared game logic lives once
  with one managed `MODULE.0xVA` identity row per build bound to that source,
  target-specific code stays in target-specific dirs, no duplicated shared
  sources drifting apart; placement follows module prefixes and
  __FILE__/string evidence, recorded in docs/TODO.md session notes.
- Overlapping functions across targets (same code, different VAs) stay in ONE
  shared source file with one managed identity row per target;
  the cross-import result must be verified against each destination before STATUS
  promotion. Cross-target VA-keyed metadata collisions and shared-source identity
  handling are rebrew multi-target shortcomings to fix upstream (see below), never
  worked around in game source.

## Multi-target rebrew shortcomings

Any shortcoming detected in rebrew for multi-target work — overlapping functions and
data at different VAs across targets (cross-target VA-keyed metadata collisions,
shared-source marker handling, per-target lint/verify/test isolation,
layout/postlink per-target state, tool-owned TOML interference between targets) —
gets fixed upstream in the rebrew checkout (precedent: layout rename compat,
merge-sweep, case-label registry, atomic writes, verify-cache guards), with its suite
green before returning to reversing; never work around a toolchain bug in game source.
Missing features go in the rebrew ideas file (docs/IDEAS-GUILD.md in the rebrew
checkout): pain, proposed feature, evidence pointer. Append on encounter, not at
session end.

## Hard constraints

- **C only (C89, MSVC6).** No `//` comments in code bodies, no
  declarations-after-statements, no `/GS`, no `__declspec(noinline)`.
- **No asm. No naked, no `_emit`, no `__asm`.** Allowed only when certain
  the original game source used raw asm at the same site. Certain means
  positive evidence (for example a code shape no MSVC6 C output can
  produce, or a corroborating string/symbol), not a hunch from a hard
  match. Doubt means C. Convert existing `_emit` dumps to proper C
  (prior conversion cost ~0x3a84 of `.text` shortfall — recover it with real
  C, not asm).
- **Never reverse ZLIB or LIBCMT.** Both link in as stock libraries. Before
  touching any function, run `rebrew library match --stock-lib LIBCMT.LIB
  --va 0x<VA>`. Anything matching is library code — skip it.
- **Do not patch a third-party `.lib`.** This covers Microsoft's statically
  linked CRT (`LIBCMT`) and every other archive the project did not write. A
  copy with member bytes changed is still a patch. The one exception is clear
  evidence that the original game authors shipped the same edit. A byte match
  that only a patched member can produce is not that evidence. On unwanted
  library pull-in, displace with a local symbol definition or remove the
  reference (see `CMakeLists.txt` `_CRT_REGION_KEEP` pattern).
- **`REBREW_DEBUG_INFO=OFF`** for every link check (`/debug` grows `.rdata`
  and breaks postlink layout).

## Toolchain (always use it)

- `rebrew todo --json` — pick highest-ROI item first.
- `rebrew library match` — library check before reversing (see above).
- `rebrew skeleton 0x<VA>` — new function skeletons.
- `rebrew test <file> --json` / `rebrew test --all --json` — compile + compare.
- `rebrew diff <file> --json` — byte diff; `rebrew match run` / GA only after
  the test/diff loop stalls.
- `rebrew verify --json` / `--full` — bulk check; `rebrew lint --json` —
  annotation validity; `rebrew data list --json` — globals inventory.
- Judge candidates with `scripts/linktest.sh <file.c`, not object scores:
  positional `match_count` and structural `aligned` routinely disagree with
  the link (one hoist: aligned 662 → 665, match 1004 → 947, link +42 worse).
  When rulers disagree, link and measure.
- Run `scripts/gate.sh` before every commit: build integrity, clean lint,
  raw CMake build, linked EXACT, data/import placement, Wine exports and
  independent whole-file identity. Never weaken its checks or lower a passing
  verification baseline to conceal a regression.

## Types and structs

- Define types where the game would have had them: real struct names,
  real field names, game-domain vocabulary. No `_4i`, no `field_0x4`
  placeholders surviving past first pass.
- One word, one meaning: same type name for the same layout everywhere.
- Verify sizes against the binary (`sizeof` == reference span) and record
  the size on the definition.
- **Lift shared types into headers.** If two or more TUs use a layout, it
  leaves the `.c` file. Existing homes: `rebrew_types.h` (globals support
  types), `game_structs.h` (domain structs), `game_common.h` (common
  includes), `types.h` (Ghidra-pulled — hand-promote from here, never treat
  it as final naming). New header only when no existing one fits.
- No duplicate definitions across TUs — a duplicate-symbol `LNK4006` is a
  finding (shared type not lifted, or library symbol reimplemented), never
  silenced with `/FORCE:MULTIPLE`.

## Naming (adhere + improve)

- `docs/naming_conventions.md` binds. Read it before naming anything.
- Function name = `<module>_<VerbNoun>`. Verbs English, game nouns German
  (`Spieler`, `Objekt`, `Gebaeude`/`Geb`, `Raum`, `Lagerslot`, `Wohnsitz`).
- Module prefixes: `cm_`, `gm_`, `lb_`, `ahm_`, `gv_`, `sim_`, `amt_`,
  `ls_`, `plt_`, `m_`, `vfs_`, `srv_`. Client-only prefixes (`ch_`, `ai_`,
  `he_`, `d2_`, `d3_`, `nt_`, `ob_`, `gs_`, `am_`, …) out of scope —
  never reuse them for server symbols.
- `cm_Chk` = validate (0 OK, 1 reject); `cm_Ex` = execute (0 OK, 1 fail);
  both `int __cdecl f(void* cmd, void* result)`. `fio` infix = file-I/O
  helper (`amt_fio_LoadAemter`).
- `Error.c` and `broadcast.c` have no prefix. Never invent `err_`/`net_`.
- `m_alloc` unit is snake_case (`m_alloc`, `m_init`, `m_pool_free`).
  `m_alloc_debug` is a block group name, not a symbol.
- Attested globals keep their original spelling. Otherwise follow the owning
  module's style: `<module>_CamelCase`, heap table pointers `lp` + German noun
  (`PROT`/`INST`), file statics `s_`, typed pointers `tp_`. Record inferred names.
  Compiler literals have no original source identifier: inventory rows use
  `str_<content>`, `flt_` or `dbl_`. Unproven layout spans retain `g_gap_*` and
  `g_before_*` until their owners are established. Structs `UPPER_CASE`, fields
  German snake_case, constants `prefix_UPPER_SNAKE` (`ob_`, `cmdt_`, `GM_`, `HE_SIM_`).
- Rename only via `rebrew source rename`. Keeps cross-references.
- Evidence hierarchy: `"<name>(): "` log prefix plus confirmed push of
  the literal is strongest. RevEng attribution alone untrusted (wrong
  twice). `__FILE__` strings reveal module. No attested string means
  descriptive name with no invented prefix.
- Preserve original spellings including errors (`gm_ObjectsAvailble`,
  `gm_SubObjectNoKill` beside `gm_SubObjekt`, stripped umlauts). Never
  "fix" spelling.
- Improve doc with each finding: new name adds attested-table row (VA +
  standing: renamed from X / already correct); new prefix adds module
  row; new verb/noun adds vocab row. Attest first, then record.

## Source tree reconstruction

Rebuild the original source organization as findings allow:

- Target layout mirrors `docs/naming_conventions.md` source-tree map:
  `DieGildeAddOn/command|game|loadsave|auxillary/`,
  `DieGildeAddOnServer/`, `Units/<module>/`. New file placement follows
  the map; `__FILE__` strings and module prefixes decide placement.
- Headers mirror inferred original structure: shared domain types lift to
  the header the game would have had (see Types section). No shared game
  headers in decompiled code means the original likely kept structs local
  per TU — lift only on multi-TU evidence, never speculatively.
- Re-evaluate placement on new findings: a recovered `__FILE__` string,
  a cross-TU type use, or a module-prefix correction can move files and
  decls. Record the move + reason in `docs/TODO.md` session notes.
- Map stays speculative where unattested: mark speculative entries as
  such in `naming_conventions.md` merged-tree section. Attested entries
  need a `__FILE__`/PDB/string pointer.

## General knowledge

- `docs/general-knowledge.md` holds discovered facts that fit no other
  doc: original build environment, project organization, game-domain
  facts, toolchain observations. One fact, one bullet, evidence pointer.
- Append on discovery, not at session end. Naming evidence goes to
  `naming_conventions.md` instead; codegen to shapes/allocator/walls;
  method to measure-traps; process to workflow-traps.

## Codegen facts and quirks

Docs by finding category, no overlap:

- `docs/msvc6-c-shapes.md` — **C spelling → emitted bytes.** Declaration
  types, operand forms, statement order, loop shape. Entry needs: source
  pattern, instruction difference, verified call site. Retired spellings
  stay listed so nobody re-probes them.
- `docs/msvc6-allocator.md` — **register/slot decisions.** `eax/ecx/edx`
  vs `ebx/esi/edi` colouring, frame slot maps. Entry needs: probe method,
  allocation observed, target function.
- `docs/codegen-walls.md` — **compiler walls.** Exhausted levers, inert
  permutations with counts, encodings no C spelling reaches. Judgement
  marked as judgement.
- `docs/measure-traps.md` — **method traps.** Metric lies (relocation
  accounting, rulers, residue≠error size), tool traps, build side effects.
- `docs/workflow-traps.md` — **process traps.** Agent concurrency, scope
  constraints, past mistakes on record.
- `docs/TODO.md` — **session log.** Round number, what was tried, measured
  delta (+/− bytes), landed or reverted. No theory, only history.

Routing rule: spellings → shapes; registers/slots → allocator; dead ends
→ codegen-walls; fake signal → measure-traps; process → workflow-traps;
attempts with numbers → TODO. One finding, one home — never two.

Before reshaping a compiling-but-mismatched function, read shapes first.
Probes go in `.scratch/`, never in the tree.

- Statement/definition ORDER changes land wins; spelling changes have never
  landed — reorder first, respell only with a measured link delta.
- Retired levers stay retired (TU theory, partition search, flag sweeps,
  outline, cross-compiler, statics, SEH). Re-probe only with new evidence.

## `rebrew` bugs

Bugs encountered in `rebrew` itself get fixed in the `rebrew` checkout
(layout rename compat, merge-sweep, case-label registry, atomic writes,
verify-cache guards — precedent exists), with its suite green before
returning to reversing. Never work around a toolchain bug in game source.

- Missing features go in the rebrew ideas file
  (`docs/IDEAS-GUILD.md` in the rebrew checkout): pain, proposed feature,
  evidence pointer. Append on encounter, not at session end.

## Continuous hygiene (lint, verify, test)

Byte match rots fast. Run checks constantly, not just before commits:

- `rebrew lint --json` after every annotation edit. It validates the
  `MODULE.0xVA` row that binds the body. Zero warnings is the only
  acceptable state; fix new lint hits before testing further.
- `rebrew test <file> --json` after every source edit; `rebrew test --all
  --json` after any shared-header or cross-TU change, since one header edit
  can demote unrelated functions.
- `rebrew verify --json` for single-file confirmation; `rebrew verify
  --full` for whole-tree state; `rebrew verify --data` after any data,
  struct, or header change. Never count `PROVEN` as byte-matched — it ranks
  below `RELOC` and always carries a non-zero delta.
- Never hand-edit `src/rebrew-functions.toml` or `src/rebrew-data.toml`.
  They are tool-owned (`test`, `match`, `diff --fix-blocker` write them).
  Manual edits corrupt tool workflow; lint catches the fallout.
- `scripts/gate.sh` before every commit, no exceptions. Compile/link failures
  are failures. The deliverable is the raw CMake DLL, and the gate requires
  byte identity, linked EXACT, data/import agreement and working Wine exports.

## Done criteria

- server.dll — `rebrew verify --full`: all functions EXACT, zero drift.
- Linked `.text` VirtualSize exactly `0x22846`, import table exactly the
  reference 100 imports, residue at zero.
- `scripts/gate.sh` green; Wine load + exports (`Init`, `Exit`) resolve.
- Europa1400Gold_TL.exe: `rebrew verify --full` all functions EXACT, zero drift,
  `scripts/gate.sh` green.
- Europa1400Gold.exe: onboarded as rebrew target, `rebrew verify --full` all functions
  EXACT, zero drift, `scripts/gate.sh` green.
- Shared tree: all three targets build from the same shared sources with no duplicated
  game-logic files, gates green on all.
- Docs current: shapes, allocator, codegen-walls, measure-traps,
  naming, general-knowledge, TODO.


## Live handoff

Current working state lives in `.scratch/HANDOFF.md` (gitignored). Update both files each round.

- 2026-10-06: 8 server rows rebound from GOLDTL.cm_* twin files to cm_*.c; verify back to 316/316. Detail in .scratch/HANDOFF.md.

- 2026-10-06 (later): server TUs consolidated to one file per original TU; raw link places every game and compiled-library function at its reference VA. Details: .scratch/HANDOFF.md, docs/naming_conventions.md.
- 2026-10-06: Error.c inline-literal pilot negative (literals leave plain .data as COMDATs), reverted; see .scratch/HANDOFF.md round 9.
- 2026-10-06 (round 9b): CRT locale stubs removed (real members linked), rdata_fold.c removed, text equal outside relocs, WS2 thunk order exact, Error.c pool in blob; open: BSS, spiel literals, IAT WS2. See .scratch/HANDOFF.md.
- 2026-10-06 (round 10): BSS generated in reference order (.data VS equal, 0 displaced), Error.c/spiel literals restored, upstream data placement verdicts; open: IAT RtlUnwind slots, hint/name order, WS2 thunks, lconv bss, .reloc. See .scratch/HANDOFF.md.
- 2026-10-06 (round 11): absolute data addresses symbolized and dispatch tables name their handlers (missing relocs 473 -> 168, all .text), lint clean, committed on feat/tu-structure-layout (e60fad4b). See .scratch/HANDOFF.md.
- 2026-10-06 (round 12): missing base relocs 138 -> 2 (loop ends named, float literal pools, download_state struct), CRT inittime/nlsdata3/txtmode load order (.text diff 65, .data 9), .reloc reservation model confirmed. See .scratch/HANDOFF.md.
- 2026-10-06 (round 13): TU boundaries from literal pools: command data + gm_GetFieldByType into command.c, plant_pairs.c split, aemter/alchemistry/plant/broadcast/vfs strings inlined as literals, winsock strings -> Units/net/net.c (file-name link order). Layout unchanged, verify 316/316. Upstream: rebrew source rehome.
- 2026-10-07: late CRT members and imports load in the reference order (.data identical, .rdata 1768 -> 242, .text 138 = IAT operands); IAT slot order left (VC6 qsort model; reference array not recovered). Released guild v1.2.0 and rebrew v2.24.0 (local tags).
- 2026-10-07: all 3499 relocation sites present. Remaining gaps (IAT order, GetLastError, .reloc size) shown to be fingerprints of client code the server link discarded (shared sources; Rich header counts 37/124/6/126 vs 36/113/1/109). Reconstructing the real client-only functions; documented in msvc6-link-layout 5e and rebrew skill link-fingerprints.
- 2026-10-08 (round 16): reconstructed client code the server discards (net.c, vfs.c, zufall.c, timer.c, game TUs) merged. hint/name order exact, .rdata 122, .text 146 (KERNEL32 IAT operands only), .data 0, .reloc 59928/66420, IAT 37/100 slots off (USER32/WS2_32/WINMM exact). Rich still 8 LIBCMT C members and 5 alias objects short. Details: msvc6-link-layout 5f.
- 2026-10-08 (round 17): timer unit dropped (IAT inversion: w + m must be 5 or 7), mkdir/getcwd/stricmp/strcmpi called by their OLDNAMES names, bss_late -MT (no MSVCRT chr.obj), minizip split into Units/vfs/unzip.c (stock 0.15 + client additions), the client's vfs directory tree and vfs_init ported, two spiel name lookups. .text, .rdata, .data and the IAT now equal the reference; whole file differs only in 91 header bytes and the .reloc reservation (59868/66420, 546 DIR32 short). Rich 38/120/4/126 vs 37/124/6/126. Details: msvc6-link-layout 5e/5f.
- 2026-10-08 (round 18): zlib is built from its stock 1.1.3 files whole (gzio.c replaces gz_stream.c, one trees.c, inflateSync's marker was border[]'s tail); its discarded gz* functions load the four missing LIBCMT members. Ported vfs.c's file API and the client's savegame writers, building-site box cache, unit conversions and price formatter; itoa and strnicmp by their old names give the last two alias objects. Every Rich record, section and IAT slot now equals the reference; the file differs in 6 header bytes and one .reloc page (5123 of 5535 DIR32). Finding: the server's log macro expands to LogMessageInternal calls the clients compile away, so client-derived ports cannot prove the remaining count. Details: msvc6-link-layout 5f.
- 2026-10-08 (round 19, placeholder): 211 marked placeholder LogMessageInternal calls in discarded client-only functions (stopgap until real code is found) plus the amt_fio_SaveAemter and rd_GetBKSize ports close the last 412 DIR32 records: .reloc 66420 and server.dll byte-identical to the reference. Placeholders only where the kept file-path literal cannot move. Details: msvc6-link-layout 5f.
- 2026-10-08 (round 19, integrated on exp/r19-integrate): merged the sweep, loadsave, orphans, units and alchemistry branches (one definition per client VA) plus Error.c's ReportError and LogMessage. Real code supplies 5246 of the 5535 DIR32 records, 155 marked placeholder calls the other 289 (16 formatted, 53 guard, 19 not-found, 67 entry traces; no exit traces left); server.dll still byte-identical, a_cmp keeps _strncnt. Rounds 16-19 names audited (docs/naming_conventions.md, "Names added in rounds 16-19"). Details: msvc6-link-layout 5f.
- 2026-10-08 (Codex continuation): preserved the already merged byte-match work. Updated the gate to verify CMake's raw DLL, linked EXACT and data placement without the retired split-link/postlink experiment. Gate passes: 316/316 compiled functions EXACT, 652/652 data symbols compared and matched, imports and Wine exports pass, whole file byte-identical. Fixed Rebrew's explicit archive scans accidentally including automatic vendored objects; 11,371 upstream tests pass (50 skipped), Ruff/Mypy and pre-commit pass. Existing rename/BinSync worktrees and unrelated edits were left untouched. Details and merge receipts: .scratch/HANDOFF.md.
- 2026-10-08 (goal20 resumed): repaired the `unz_copyright` and `crc_table` data rows to name their actual vendored owners through `rebrew data set`; lint remains clean and 652/652 compared data symbols match. Existing original-name changes and save/load identity corrections remain in their worktree. Prepared a disposable Rebrew main + BinSync-fixes integration and narrowly scoped fixes for its outstanding validation failures; focused checks include a successful real BinSync round trip. Git metadata, sibling checkouts and Docker are inaccessible under this session's restricted filesystem/network, so merging and compiler checks remain pending. Receipts and integration patches: `.scratch/HANDOFF.md`.
- 2026-10-08 (goal20 receipts): the fresh SERVER candidate `.scratch/goal20/codex-states/server` loads in BinSync's own Client with 651 functions, prototypes for all 251 compiled game functions, and 598 typed/sized globals. Old configured state and all pre-existing worktrees are preserved. Full integration suite: 11,383 passed / 58 skipped / 15 failed (14 sandbox restrictions, one existing path-dependent diagnostic assertion reproduced on unchanged main); Ruff/format/Mypy pass. Integration patch is ready for review against Rebrew main 6579338f, but is not merged. Duplicate/incomplete types remain, so Ghidra cleanup and the original-source goal are still open.
- 2026-10-08 (packed type sync): fixed shared Rebrew layout parsing and BinSync export in the disposable integration checkout: preserve file-local packing, embedded alignment, incomplete-layout boundaries and names expanded through aliases. Fresh candidate `.scratch/goal20/codex-states/server-packed-final` loads through BinSync's Client with all 1,118 struct names retained; EntityQueryRecord/LinkedNode/BuildingDefaults match their proven sizes (0xa9/0x43/0x15) and offsets. Final focused checks: 416 passed / 1 skipped, real Client round trip passed, Ruff/format and Mypy (356 files) pass. Game sources, 651 function artifacts, 598 global artifacts and byte-identical DLL remain unchanged. Refreshed integration/final-fixes patches; remaining integration, compiler and type cleanup work is recorded in `.scratch/HANDOFF.md`.
- 2026-10-08 (struct extents): fixed BinSync's omitted natural tail padding in the disposable checkout. Complete size and members now reconcile as one definition; old baselines upgrade without losing their last-shared values, and unrepresentable peer size-only edits remain pending with a reason. Fresh `.scratch/goal20/codex-states/server-sized` corrects 20 aggregate sizes with all member definitions, function/global artifacts and the DLL unchanged. All local/remote type projections agree; BinSync Client loads the candidate. Focused checks: 345 passed / 1 skipped; Ruff/format and Mypy pass. The complete integration patch passes a read-only application check against Rebrew main. Real integration and remaining type/source reconstruction work are still pending; details in `.scratch/HANDOFF.md`.
- 2026-10-08 (extent validation receipt): final revision full suite has 11,395 passing tests / 58 skips / the same 15 previously identified failures (14 sandbox restrictions, one existing path-dependent assertion). No new failures and no checks weakened. The real BinSync round trip preserves padded sizes, while unchanged-source assertions retain the byte-identical DLL. Integration remains pending under the current restrictions.
- 2026-10-09 (validation and naming follow-up): resolved the path-dependent refactor diagnostic assertion and three uv cache failures; final upstream integration run has 11,399 passing tests / 58 skips / 11 socket-bind denials, with no new failures or weakened checks. Ruff/format/Mypy pass and the refreshed integration patch still passes a read-only application check. Aligned this goal and the naming guide with original global/literal naming, managed identities and the raw-link gate. Type-scope evidence records 159 differing names, 1,034 client-bound exported types and three conflicts with server compile inputs; lexical scope and include/use closure must precede type consolidation. Compiler/integration gates remain pending; receipts and replay instructions are in `.scratch/HANDOFF.md`.
- 2026-10-09 (alias and scope continuation): traced server source/include conflicts to lexical scopes, preventing an unsafe consolidation of function-local types. Fixed BinSync alias expansion corrupting member identifiers and foreign aliases overriding local aggregate definitions in the disposable integration checkout. Both regressions pass. The final candidate `server-member-types-final` retains all 1,118 structs and all member/aggregate extents, with seven corrected local type spellings; real Client loading, unchanged artifacts and byte-identical DLL checks pass. Broad validation passes all alias checks but exposed a separate PDB parser property failure; state receipts, patches and remaining type/integration limits are in `.scratch/HANDOFF.md`.
- 2026-10-09 (PDB record boundaries): fixed the newly discovered parser bug dropping a procedure named `S_GPROC32`, plus an unnamed procedure borrowing a data-symbol name. Both deterministic regressions failed first; all 18 PDB/parser/property tests pass, along with Ruff/format/Mypy. Frozen-revision full run: 11,402 passed / 58 skipped / only the 11 previous socket-bind denials. The complete staged patch includes the repair; actual unrestricted validation/integration remains pending. Receipts and replay instructions are in `.scratch/HANDOFF.md`.
- 2026-10-09 (original-name integration candidate): prepared an isolated current-main + existing name-branch merge, carrying 16 committed name identities, six pending client identity repairs and the two vendor-owner file fixes through locked metadata writers. All historical verdicts/verification remain preserved; the new load row has no byte verdict. Server lint and scaffold checks pass; each client retains four assembly warnings with zero lint errors. Existing server compile inputs match the previously verified name branch, and both existing DLLs remain reference-identical. The candidate itself still needs a compiler gate; Docker access and actual repository integration remain unavailable. Review patch, assertions and full limits are in `.scratch/HANDOFF.md`.
- 2026-10-09 (assembly warning scope): fixed W020 combining unrelated function/target statuses and blockers in the disposable upstream integration. Eight regressions and all 264 lint tests pass; Ruff/Mypy pass. Candidate lint still has zero errors but now exposes 2 server, 6 GOLDTL and 40 GOLD assembly findings, superseding the previous suppressed warning counts. Every finding is bound to its source definition; the two server findings have no identity or entry in the existing raw map. No source/byte-verdict changes or gate weakening occurred. Broad validation is running; remaining provenance, compiler gates, integrations and the full shared-tree goal stay open. Receipts and continuation details are in `.scratch/HANDOFF.md`.
- 2026-10-09 (upstream integration): access was restored and the user reiterated that tool problems must be fixed upstream. Merged the pending BinSync branch and all finishing layout/alias/PDB/lint fixes into actual Rebrew main as `551f0d0cc58bbe8da48793ca177a2faa98868695`. The unrestricted suite exposed a further MSVC-mask offset/newline bug; three regressions failed first and the shared upstream parser was repaired. Final full suite: 11,432 passed / 50 skipped / 0 failed; all 18 pre-commit hooks pass. Unrelated dirty main/worktree files remain unchanged. The fresh original-name candidate configured and built successfully with debug info off: 316/316 functions verify, 652/652 data symbols match (409 exactly placed), imports and Wine exports pass, and the raw DLL is byte-identical. Its gate fails only on two assembly provenance warnings in unbound client VFS definitions; do not report it green. Game-name integration and the complete three-target source/type/byte goal remain open. Details and receipts are in `.scratch/HANDOFF.md`.
- 2026-10-09 (raw-link acknowledgement): fixed the misleading copied-data-section warning upstream and fast-forwarded actual Rebrew main to `98b131135a5f1f0340bb736615facdc394a2f3c9`. Explicit/configured raw links omit the warning; unknown inputs still warn and retain guarded write-back. Three regression cases and all 409 focused tests pass; final full suite has 11,435 passed / 50 skipped / 0 failed, with all 18 pre-commit hooks passing. Unrelated dirty work remains unchanged. Bound the two existing VFS bodies to their proven GOLDTL addresses through locked metadata writers and recorded their exact original aligned-copy sites as assembly provenance; no source or byte verdict was fabricated. Client checks without promotion report size mismatches (1526/1472 and 496/368). The final game candidate gate passes: zero server lint errors/warnings, 316/316 functions, 652/652 data symbols, imports/Wine exports and whole-file raw identity. All-target lint retains six GOLDTL and 40 GOLD assembly warnings with no errors. Actual game integration and the full three-target goal remain open.
- 2026-10-09 (game-name merge and scaffold JSON): merged the verified original-name candidate into actual game main as `f85897d6439da4fea5f47b9bb574fd6fff6ba308`, preserving unrelated files/worktrees. The real checkout initially reported two stale generated BinSync skill files; refreshing from upstream preserves the existing project instructions, and the real gate passes with zero server lint findings and a byte-identical raw DLL. The refresh exposed a further upstream CLI bug: `init --refresh-agents --json` emitted no JSON. Fixed and merged actual Rebrew main to `31720e4e46445de97543c4906d5c7241e4907fa4`; four regressions failed first, all 432 focused tests and 18 hooks pass, and the full suite has 11,439 passed / 50 skipped / 0 failed. Real CLI no-op and zero-drift checks pass. The final main gate is refreshing verification against the new package fingerprint. The source-provenance feature for unaddressed inline helpers, client byte matches, type cleanup and the full three-target goal remain open; receipts and continuation pointers are in `.scratch/HANDOFF.md`.
- 2026-10-09 (final integration verification): the actual-main gate against Rebrew `31720e4e` passes every axis, including clean server lint, 316/316 compiled functions, 652/652 compared data symbols (409 placed exactly), all 100 imports, Wine exports and raw whole-file identity. All 316 stored SERVER measurements use the new package fingerprint; identities, CFLAGS, source/reference hashes, statuses and existing client facts are preserved. Unrelated root/upstream files and both pre-existing worktrees remain unchanged. This completes the pending tool/name integrations, not the broader source reconstruction: client warnings/matches, inline-helper provenance, type cleanup and placeholder removal remain open. The top GOLDTL CRT todo item is a stock archive match with an existing library identity and a conflicting legacy body; reconcile its source/provider facts instead of reversing it. Detailed receipts and next work are in `.scratch/HANDOFF.md`.
