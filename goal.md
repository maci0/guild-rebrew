# Goal — 100% Byte-Identical `server.dll` Recompilation

## Objective

Reproduce `server.dll` (PE, x86-32, MSVC6) from C source with 100%
byte-identical output: every function `EXACT`, every data byte matching,
link producing reference `.text` VirtualSize `0x22846` with residue at or
below `RESIDUE_BASELINE` and `rebrew verify --full` at or above its `BASELINE`.

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
  touching any function, run `rebrew lib-match --stock-lib LIBCMT.LIB
  --va 0x<VA>`. Anything matching is library code — skip it.
- **Never patch a `.lib`.** On unwanted library pull-in, displace with a
  local symbol definition or remove the reference (see `CMakeLists.txt`
  `_CRT_REGION_KEEP` pattern).
- **`REBREW_DEBUG_INFO=OFF`** for every link check (`/debug` grows `.rdata`
  and breaks postlink layout).

## Toolchain (always use it)

- `rebrew todo --json` — pick highest-ROI item first.
- `rebrew lib-match` — library check before reversing (see above).
- `rebrew skeleton 0x<VA>` — new function skeletons.
- `rebrew test <file> --json` / `rebrew test --all --json` — compile + compare.
- `rebrew diff <file> --json` — byte diff; `rebrew match` / GA only after
  the test/diff loop stalls.
- `rebrew verify --json` / `--full` — bulk check; `rebrew lint --json` —
  annotation validity; `rebrew data --json` — globals inventory.
- Judge candidates with `scripts/linktest.sh <file.c`, not object scores:
  positional `match_count` and structural `aligned` routinely disagree with
  the link (one hoist: aligned 662 → 665, match 1004 → 947, link +42 worse).
  When rulers disagree, link and measure.
- Run `scripts/gate.sh` before every commit (lint, compile, verify baseline,
  residue baseline). Never lower `RESIDUE_BASELINE` or raise `BASELINE`
  except on a measured improvement.

## This round: data and other segments

Focus is `.data` / `.rdata` / `.bss`, types, and structs — not `.text`
chasing. Current state: 96.1% functions matched (313 EXACT, 233 RELOC),
`rebrew todo` shows 246 `start-data` items and 34 `data-drift`. Work them in
ROI order:

1. `rebrew verify --data` drift first (known symbols, known bytes).
2. Then `start-data` inventory (`rebrew data --json`): name, size, section,
   cross-TU users.
3. After any data change, re-run gate: data edits move `.text` cost
   unpredictably (AcceptConnections rounds 518/520: local 0 diffs, gate
   `.text` +180 — COMDAT literal emission and call-site churn dominate).

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
- Rename only via `rebrew rename`. Keeps cross-references.
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
  `// FUNCTION:` identity header and the marker/VA contract. Zero warnings
  is the only acceptable state; fix new lint hits before testing further.
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

- `rebrew verify --full`: all functions EXACT, zero drift.
- Linked `.text` VirtualSize exactly `0x22846`, import table exactly the
  reference 100 imports, residue at zero.
- `scripts/gate.sh` green; Wine load + exports (`Init`, `Exit`) resolve.
- Docs current: shapes, allocator, codegen-walls, measure-traps,
  naming, general-knowledge, TODO.
