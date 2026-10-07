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
  .text VirtualSize 0x22846 with residue at or below RESIDUE_BASELINE and
  `rebrew verify --full` at or above its BASELINE.
- Reproduce Europa1400Gold_TL.exe (PE, x86-32, MSVC6) from C source with 100%
  byte-identical output: every function EXACT, every data byte matching. This is
  the active reversing focus.
- Reproduce Europa1400Gold.exe (PE, x86-32, MSVC6; onboarded rebrew target,
  binary at original/Europa1400Gold.exe) with 100% byte-identical output: every
  function EXACT, every data byte matching. Feed it from the shared tree +
  cross-import; do not reverse it in isolation.
- Rebuild the unified shared source structure the original devs most likely had:
  one shared source tree serving all three targets, shared game logic lives once
  with per-build markers (one source file carries one marker per build),
  target-specific code stays in target-specific dirs, no duplicated shared
  sources drifting apart; placement follows module prefixes and
  __FILE__/string evidence, recorded in docs/TODO.md session notes.
- Overlapping functions across targets (same code, different VAs) stay in ONE
  shared source file with one marker line per target in the same file where
  rebrew supports it, or one thin file per target that includes the shared body;
  the cross-import result must be verified against each destination before STATUS
  promotion. Cross-target VA-keyed metadata collisions and shared-source marker
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
- Run `scripts/gate.sh` before every commit (lint, compile, verify baseline,
  residue baseline). Never lower `RESIDUE_BASELINE` or raise `BASELINE`
  except on a measured improvement.

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
- Globals `g_` prefix, unknown = `g_<hex>`. Strings stay
  `s_<content>_<addr>`. Structs `UPPER_CASE`. Constants
  `prefix_UPPER_SNAKE` (`ob_`, `cmdt_`, `GM_`, `HE_SIM_`).
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
- `scripts/gate.sh` before every commit, no exceptions. It is the four
  binding checks: lint, compile (`error C####`/`error LNK####` only —
  postlink failure is expected until position-aligned), verify baseline,
  residue baseline.

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
