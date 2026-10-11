# Goal — 100% Byte-Identical server.dll, Europa1400Gold_TL.exe, AND Europa1400Gold.exe Recompilation with a rebuilt unified source tree matching what the original devs most likely had.

Tracked as goal `goal-dd7dd2dd-8cde-4e14-a043-8674d4ec5631` (revision 21, 65/256 rounds).
This file is the durable copy: if the session goal state is ever lost, re-create it from here.

- 2026-10-11 (shared memory reporter and group type): TL0x41df00 and
  GOLD0x422750 now bind the canonical m_ReportGroupInfo. One body serves all
  three targets; only SERVER emits the six native logging calls. Scoped client
  tracker aliases reuse existing globals, with no storage or data verdict added.
  The duplicate64-line client reporter is retired and both shutdown calls use
  the shared name and pointer prototype. One40-byte GroupNode replaces the
  equivalent MemPool definition; MemBlock remains16 bytes. Two deallocator
  field references adopt the canonical labels without changing instructions.
  Both complete client reporters retain880 native bytes/44 typed operands,
  complete literals and167 reachable instructions each, with30 rejecting
  shifted-symbol controls. Both shutdown destinations reject shifted callees.
  Before/after whole-object checks preserve56 surrounding bodies across the
  normal server build, a legacy-flag-off compile, both clients and their callers.
  All13 group/record size/field assertions pass in each target compiler. All21
  affected existing client matches pass (12TL/9Gold); every status and game
  counters251/3584/2082 are preserved. Lint retains0 errors and0/1/38 warnings.
  Full server gate passes316/316 functions,652/652 data, imports/exports/Wine,
  library/toolchain checks and all286720 raw bytes. Coverage is refreshed for
  all3 targets; standalone C backlog decreases to3830 and3931 files scan.
  Original function/type/field names and storage owners remain inferred or
  unresolved; full client raw links/data, allocator/shutdown integration and
  faithful discarded-server source remain open. Receipt:
  .scratch/goal21/shared-pool-report. No game push/live sync.

- 2026-10-11 (shared pool allocator extent): native CFG proves TL0x41e1d0
  and GOLD0x422a20 contain261 bytes,103 reachable instructions and two returns;
  the next11 NOPs are alignment. The existing canonical m_PoolAlloc already
  matches both complete bodies, including four typed operands and two full
  literals per client, with three rejecting shifted-symbol controls each.
  `rebrew test --size 261` records fresh RELOC261/261 through the managed writer;
  no C, headers, assembly, flags, storage or library bytes change. Existing fill
  assembly evidence is recorded separately with the native34-byte operand-homed
  macro and prior compiler/stock-library controls. Game match counts become
  SERVER251/TL3584/GOLD2082; all-target lint has0 errors and0/1/38 warnings.
  Coverage is refreshed for all3 targets: catalog regions retain272 discovery
  bytes, while code hashes exclude11 NOPs and status accounts261 body bytes.
  The full server gate passes316/316 functions,652/652 data, Wine/library and
  toolchain checks, and every286720 raw reference byte. Data/type stores and
  all other function statuses remain unchanged. Original names/fields/owners,
  full client raw links and faithful discarded-server source remain open.
  Upstream PR19 fixes diff/GA losing shared-root headers in temporary compiles;
  merged3d271d64, integrated locally with inherited edits preserved. Both MSVC
  and GCC regressions fail before the fix;175 focused tests,11689 full local
  tests/52 skips at88% coverage, all local checks/hooks and both Python CI jobs
  pass. Temporary validation checkouts are removed and root hooks restored.
  Receipts: .scratch/goal21/pool-alloc-upstream. No game push/live sync.

- 2026-10-11 (shared pool deallocator): TL0x41e2e0/GOLD0x422b30 now bind
  the canonical m_pool_free in Develop/Units/m_alloc/m_alloc.c. Only the two
  fatal diagnostics are SERVER-specific; the common bounds, slot accounting
  and unlink logic are unchanged. The duplicate 51-line client source and its
  private Chunk definition are retired; six caller files use the shared name.
  Both complete 112-byte client bodies match native bytes with all four call
  operands bound, and reject shifted-callee controls. Surrounding allocator
  bodies and 11 caller contexts retain their instructions, typed operands and
  compiler literals; all 14 native caller operands independently retain their
  targets. All 25 affected existing client matches pass (15 TL / 10 Gold).
  The normal server gate passes 316/316 functions, 652/652 data and all 286720
  raw bytes, plus Wine exports, library and toolchain checks. The experimental
  legacy-flag-off compile is a check of our source, not another original server.
  All statuses, data/types/provenance, flags, layout and stock libraries are
  preserved; coverage is refreshed for all three targets. The standalone C
  backlog decreases to 3831. Client names and storage owners remain inferred
  or unresolved; full client raw links and faithful discarded-server source
  remain open. Receipts: .scratch/goal21/shared-pool-free. No push/live sync.

- 2026-10-11 (upstream tooling and workflow cleanup): upstream PR18 is merged
  as f81f6828. Generic pinned-source vendoring lives in `rebrew library vendor`;
  CMake uses it, 37 duplicate/obsolete scripts are retired, and nine project
  helpers remain. The packaged AGENTS template and workflow/data skills now
  route work to existing commands/public APIs before adding helpers; project
  copies are refreshed with local naming rules retained. Game commit e6135bc9
  records cleanup and fresh SERVER verification. All11687 local upstream tests,
  88% coverage, both Python CI jobs and packaging/provenance/reproducibility
  checks pass; all11 project tests and the complete server gate pass. The raw
  server remains identical at286720 bytes, with316 functions and652 data rows.
  Temporary validation worktrees are removed; inherited upstream edits survive.
  Archived scratch receipts are retained, not replayed. There is one original
  server.dll: references below to server "variants" mean reconstruction compile
  settings with the temporary REBREW_LEGACY_SERVER_LAYOUT flag on/off, not two
  original server builds. Faithful discarded source and both complete client
  raw links remain open. Receipts: .scratch/upstream-tooling.

- 2026-10-11 (shared allocator initializer): TL 0x41de50 and Gold 0x4226a0 now
  bind to the existing canonical m_init in Develop/Units/m_alloc/m_alloc.c.
  The duplicate 96-line client file is removed; canonical C and all caller
  declarations/bodies are unchanged. Six native comparisons (old/shared clients
  plus the normal server build and a legacy-flag-off compile) preserve 972 bytes
  and 108 explicit operands,
  rejecting 98 shifted-binding controls. Each distinct native body is 162 bytes
  with 18 relocations; the original 26-byte operand-homed fill macro remains.
  Both client identities freshly verify 162/162 from the canonical source.
  Gold's existing native macro provenance is recorded through the source CLI;
  warnings improve from 40 to 39, with SERVER/TL unchanged at 0/2 and zero errors.
  Fixed the server initializer's stale deallocator description through the
  locked metadata writer. Stock archive probes identify Gold 0x5dec8d as the
  18-byte malloc wrapper and complete TL malloc's size; both LIBC and LIBCMT
  match the Gold wrapper, so archive selection remains unresolved. No CRT body,
  new assembly, global storage or data verdict was added. All existing game
  match counts 251/3583/2081 are retained; Gold's library inventory gains one
  correctly attributed wrapper. Full server gate passes 316/316 functions,
  652/652 data, 100 imports, Wine exports and 286720-byte raw reference identity.
  Data/type stores, canonical sources, flags, layout, references, stock archives
  and inherited upstream edits are unchanged. Receipts:
  .scratch/goal21/shared-allocator-init. Full client raw links, original global
  owners/names and faithful discarded-server source remain open. No push/live
  sync; the complete three-image/shared-tree goal remains active.

- 2026-10-11 (vendor removal probes and target status): four fresh isolated
  native links test stock version literals, stock compress.c, VFS ownership,
  and ordinary read-only storage without /ORDER. They differ by 17, 16663,
  16579 and 6123 bytes respectively. VFS ownership restores the original Rich
  compiler-object counts, but does not restore CRT placement. Natural readonly
  storage preserves section sizes and counts but moves pools and tables. All
  import identities, IAT slots and hints stay equal; production inputs and
  raw server identity stay intact. No patch was removed and no archive,
  compiler flag, canonical link rule or postlink bytes changed. Recovering
  original read-only owners and discarded-source composition remains required.
  Receipts: .scratch/goal21/vendor-workaround-removal.
  User's TL data status is accurate: all 283 visible rows are unchecked,
  initialized-data verification is 0/335380 bytes, and no TL raw build is
  available for comparison. Upstream local commit 27544cea makes a bare
  shared --target/-t list configured targets without command execution, honors
  --root/JSON, preserves default/named selection and target-creation options,
  and explains unverified data in status. 303 focused tests and applicable
  hooks pass; inherited upstream uv.lock/IDEAS diffs are unchanged. Receipts:
  .scratch/goal21/target-status-{tests,hooks,commit}.log. No push/live sync.
  All-three-image and faithful unified-source goals remain open.

- 2026-10-11 (shared allocator helpers): canonical m_is_tracked and
  m_pool_free_all now serve both clients. Four function identities and four
  extern declaration rows move through locked writers; 31 caller files bind
  through the CLI and two duplicate helper sources are deleted. A private
  compile-time binding preserves different legacy global spellings without
  creating storage. Four full native proofs preserve 206 bytes and 6 typed
  operands, with 6 rejecting shifted-binding controls. Native object checks
  preserve all 14 allocator bodies in four profiles, 37 VFS bodies in two
  profiles, and 35 caller contexts. All 40 affected existing client matches
  freshly pass (28 TL / 12 Gold), preserving every status and game counters
  251/3583/2081. Full server gate passes 316/316 functions, 652/652 data,
  100 imports, Wine exports and all 286720 raw reference bytes. All 36 build
  objects are current; all-target lint retains zero errors and existing
  0/2/40 warnings. Three coverage documents are refreshed. Original helper
  names and declaration owners remain unresolved; the bindings are temporary.
  Root standalone C backlog remains 3832. Full client raw links and faithful
  discarded-server source recovery remain open. Receipts:
  .scratch/goal21/shared-allocator-helpers. No push or live sync.

- 2026-10-11 (shared tracked-free implementation): one canonical m_FreeTracked
  definition now serves the native188-byte SERVER and117-byte TL/Gold bodies
  using REBREW_SERVER. Invalid-pointer and underflow reporting remain server
  specific. Two client identities are rehomed through locked writers,85 caller
  files bind to the shared symbol through the CLI, and the duplicate source is
  retired.115 caller contexts preserve26641 bytes/1535 typed operands; four
  distinct native compiler/define contexts preserve the other13 allocator
  bodies in the normal server build and a legacy-flag-off compile. Two fully
  bound client bodies retain234
  native bytes/18 typed operands, with12 rejecting wrong-binding controls.
  All115 affected client identities freshly verify(88TL/27Gold), preserving
  every existing status and game match counts251/3583/2081. All-target lint
  retains0 errors with existing0/2/40warnings. All3 coverage docs are refreshed.
  Canonical server gate passes316/316 functions,652/652 data,100 imports,Wine
  exports and raw286720-byte identity(SHA3cc2ce90...). The common implementation
  name remains inferred; numeric global declarations create no new storage.
  Root standalone C backlog3832(down1). The temporary historical server guard,
  faithful discarded-source recovery, client raw links and broader unified-tree
  goal remain open. Receipts:.scratch/goal21/shared-tracked-free. No push/live
  sync or full client image gate is part of this change.

- 2026-10-11 (stock CRT deallocator binding prerequisite): complete stock
  archive comparisons uniquely identify client free: TL64dfda is233 bytes
  from multithreaded LIBCMT; Gold5dec24 is105 bytes from single-threaded LIBC.
  Corrected TL's ambiguous RTCastToVoid label and added Gold's library identity
  through locked writers. Three shared client sources now call free directly;
  no CRT implementation, data storage or archive patch was added. Six whole
  native proofs preserve734 bytes and62 typed operands, including26 free calls,
  with rejecting wrong-target controls. All6 callers freshly verify under2.25.0;
  game match counts remain SERVER251/TL3583/Gold2081. The server full gate passes
  316/316 functions,652/652 data,100 imports,Wine exports and raw identity.
  Upstream df26aadd lets source rename bind placeholders to managed library
  headers and scopes destination conflicts to affected files.133 focused checks,
  all hooks and an isolated pinned-dependency suite11655pass/52skip/119warnings
  pass. Seven initial environment/packaging failures reproduce on unmodified
  cfd6f58a; the local tool checkout was fast-forwarded to published2.25.0 before
  applying the fix. Inherited uv.lock/IDEAS edits and the existing Resembl
  checkout are preserved. Full client raw links and original-source fidelity
  remain open. Next: consolidate the actual117-byte client tracked-free body
  with the188-byte server body, retaining native logging/underflow differences.
  Gold's provisional runtime link selection needs other-member evidence before
  its raw link. Receipts:.scratch/goal21/stock-free-binding. No push/live sync.

- 2026-10-11 (user-authorized temporary historical server variant): the user
  requested `#ifdef` isolation while faithful reconstruction continues. The
  server alone defines REBREW_LEGACY_SERVER_LAYOUT alongside REBREW_SERVER.
  Two source files restore the sixteen historical placeholder calls, old
  affinity expression and absence of the client treasury formatter only under
  both defines. Disabling the flag preserves all41 reconstructed functions in
  each of the three native compiler profiles; enabling it preserves all40
  historical functions, including complete typed relocation/literal contents.
  The full canonical gate passes:316/316 functions,652/652 data,409 exact
  placements,100 imports,Wine exports and whole-file identity. Raw286720 bytes
  equal reference SHA3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
  All36 build objects pass integrity checks. All20 affected client identities
  freshly pass(TL13/Gold7); all-target lint
  retains0 errors and existing0/2/40 warnings. Stock CRT archives, reference,
  layout, linker rules and gate remain unchanged. The guards are reconstruction
  debt, not proof of original discarded source; the unified original-source and
  full client-image goals remain open. Remove the second server define and
  regenerate CMake to select the reconstructed variant. Evidence:
  .scratch/goal21/legacy-server-ifdef/{variant-proof.json,gate.log,client-verification.json}.
  No full client gates, push or live sync are part of this change.

- 2026-10-11 (durable type identities and full native D3 byte layouts):
  Human requested both managed type metadata/checks and native layout recovery.
  Upstream main980a49b6 adds locked atomic rebrew-types.toml, types bind with
  target C89 sizeof/offsetof gates, stale checks in types check/lintW031, and
  fail-closed raw conditional-field parsing. Stable IDs d3.object,
  d3.object_draw_data and d3.draw_part each have GOLDTL/GOLD bindings.
  Canonical Develop/Units/d3/d3_object.h represents complete native byte extents:
  object0x228 both; draw data TL0x1640/GOLD0x970;4 slots at+0xf4 with
  TL0x4a4/GOLD0x198 stride. Resource context+0x1cc is kontext, not the tree
  parent eltern(TL+0x1fc/GOLD+0x1f8). Original names remain inferred;
  unknown semantic fields are explicit byte regions, not recovered field meanings.
  Full native allocation/init/tree/allocator-return spans and direct branch
  boundaries checked. All6 target type layouts pass MSVC6 assertions. The4
  character bodies retain1181 native bytes,52 actual operands and52 rejecting
  wrong-target controls;4 matches freshly verify against actual upstream main.
  Prior unchanged141320 sanitizer cases and10 consumer bodies are reused.
  500 focused checks,18 hooks and final full suite11642pass/51skip/117warnings
  pass. Two interrupted/superseded full runs are not passing gates; final logs
  are authoritative. All-target lint0errors, unchanged SERVER0/TL2/GOLD40warnings;
  TL3583/GOLD2079 matches and root3836 C backlog preserved. All3 coverage
  documents rebuilt. Only character.c changed, one D3 header was added, and4
  function notes/verification/stamps refreshed; data and unrelated source/header,
  config/layout/reference/raw-server pins preserved. No storage/data verdicts,
  game commit, push or live sync. Inherited upstream uv.lock/IDEAS preserved.
  Receipt: .scratch/goal20/type-identity-layouts/scope-final.json. All jobs terminal.
  The broader all-three-image/unified-tree goal remains open. Do not repeat
  finished native/type/compiler/byte proofs. Continue evidence-based source
  organization/shared helpers or further semantic field recovery when requested.

- 2026-10-11 (historical100% replay and current gate): user confirmed there
  is no additional original source/PDB/object set and requested all current
  repository changes be committed. Isolated native compilation of just m_alloc.c
  and server.c from383252b5, with all other current linker inputs unchanged,
  reproduces every286720 reference byte and reference SHA3cc2ce9049e41ab6... .
  This localizes the current29 input-DIR32 deficit exactly: allocator117->103
  (-14), server393->378(-15). Sixteen removed, explicitly marked placeholder
  logs account for30 records; the recovered treasury formatter adds1. Restoring
  those calls restores bytes but proves no original source fidelity. The user
  explicitly requested a correct repair, so no placeholder, padding, archive
  change or header patch was adopted. Current canonical gate was rerun:
  316/316 functions,652/652 data,100 imports and Wine exports pass; only header
  0x260/0x261 fails whole-file identity. All-target lint0 errors with unchanged
  SERVER0/TL2/GOLD40 warnings. This checkpoint and the broader three-image,
  unified-original-source objective remain incomplete. Receipts:
  .scratch/goal21/last-green-trace/historical-replay.json and object-dir32-deltas.json;
  .scratch/goal21/commit-gate.log. No push or live sync is authorized.

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
  match, no recompile), so the shared source file (one managed identity per target)
  covers both. Never reverse the same function twice in both clients.
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
- Judge candidates with an isolated raw native link and the full gate, not object scores:
  positional `match_count` and structural `aligned` routinely disagree with
  the link (one hoist: aligned 662 → 665, match 1004 → 947, link +42 worse).
  When rulers disagree, link and measure. The historical `linktest.sh` is retired;
  use current build/placement CLI commands and public APIs (docs/tooling-upstream.md).
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

- 2026-10-11 (shared client allocator repairs and source placement):
  The prior turn made evidence progress on the server header, not a repair.
  No new original artifact was supplied. Continued the unified-source objective
  with two proved client fixes: GOLD4225e0 is a60-byte tracking check followed
  by4 external NOPs, not the old64-byte extent; GOLD422c60's old39-byte source
  omitted the native null-head guard. Public fix-sizes and verified shared import
  repair both. Gold now2081/4598 matched (+2); TL3583 and SERVER251 retained.
  One43-byte free-all body now serves both clients; the wrong Gold duplicate is
  retired. Both client helper files live under Develop/Units/m_alloc, with all4
  function identities and4 existing extern declarations rehomed through writers.
  Four new declaration rows bind the actual counter/pointer cells in each native
  zero-filled .data tail, each4 bytes. They allocate no storage and have no data
  verdict; source owners, heap array extent and original declaration names remain
  unresolved. Legacy numeric spellings retained, no guessed original-name claim.
  Four complete native proofs cover206 bytes and6 typed operands with6 rejecting
  wrong-binding controls. Eight baseline builds and7 final complete COFF contexts
  preserve all surviving function/caller bodies and typed bindings. All7 identities
  freshly verify; no existing match lost. All-target lint0 errors, unchanged0/2/40
  warnings; all3 coverage docs rebuilt. Root C backlog3833 (down3). Existing data,
  types/source stores, unrelated C/headers/layout/config/reference and upstream
  dirty edits preserved. Server source list, all server rows and raw SHA2583c710...
  remain unchanged; only header0x260/0x261 differs. No full server/client gates
  rerun, no tool-code change, game commit, push or live sync. Receipt:
  .scratch/goal21/allocator-client-repair/scope-final.json. All scope jobs terminal.
  Next: reconcile the actual client m_FreeTracked117-byte provider with the live
  server188-byte provider before moving the remaining client helper bodies into
  the shared m_alloc.c. Preserve native build differences and prove caller operands;
  do not alias the clients onto the server-only free implementation. The29-record
  server discarded-input deficit remains unresolved; no header repair is claimed.

- 2026-10-11 (remaining server header gap investigated; not repaired):
  Fresh current-input census proves5506 actual DIR32 reservations versus5535
  required by the native reference, missing29 (348 bytes). All3499 emitted
  relocation sites/types agree exactly; only header0x260/0x261 differ. Stock
  LIBCMT and OLDNAMES census copies hash-identically to the actual pinned Docker
  archives. Current shared-TU advisory scan:196 server/209 ported/338 blocked/
  19 ruled-out and no portable candidate. Removing heuristic native pairing
  produces21 candidate hints, all previously attributed to represented server
  bodies or existing discarded Error.c helpers; shape pairing is not proof.
  No missing original server body is newly established, and no code/header/
  archive/linker/gate mutation is landed. The project's three original images
  are the only original game artifacts found under the scanned relumea tree;
  rebuild/probe objects are not original evidence. A request for another original
  server build/PDB/source/object path is pending. Gate remains FAIL; do not mark
  this or the all-three-image goal complete. Do not invent log calls, data
  providers or fixups to close the count. Next server step requires evidence
  identifying discarded original inputs or a justified source reconstruction.
  Evidence: .scratch/goal21/server-header-fix/{current-input-census.json,
  investigation.json,sweep-current.tsv,sweep-managed.tsv,stock-archive-hashes.txt}.

- 2026-10-11 (server data drift repair with stock CRT):
  User requested fixing the canonical 648/652 data result and reiterated that
  LIBCMT/CRT are linked stock libraries, never reversed. Removed only two
  unsupported placeholder LogMessageInternal calls from the game's shared
  m_alloc.c helpers m_is_tracked and m_pool_free_all, preserving line counts.
  Both native client helpers are non-library code. Four complete native-body
  proofs cover 206 bytes with six typed operands and six wrong-binding controls;
  actual plain/Processor-Pack builds agree. All12 surrounding allocator bodies
  and typed bindings are unchanged in each of the three profiles. A frozen
  control link reproduces the old16580-byte raw divergence; the source-only
  candidate restores stock LIBCMT:a_cmp.obj at1002350a and matches every section
  byte. No CRT implementation, archive patch, compensating padding, new log,
  object mutation, linker/order/flag change, reference edit or header patch.
  Canonical gate:316/316 functions and652/652 data pass;409 exact placements,
  100 imports and Wine exports pass. Gate exit1 is solely the header identity
  gap below. Five fresh client matches pass; four inherited SIZE_MISMATCH
  verdicts remain unchanged. All-target lint0 errors, unchanged0/2/40 warnings;
  game match counts251/3583/2079 retained. All3 coverage documents rebuilt.
  Independent raw audit: SHA2583c710fc60a11cb707fe5dab606d66d8419c67237a9f926a5f1fef75f38680,
  286720 bytes, only offsets0x260/0x261 differ. .reloc VirtualSize66072 vs66420,
  short348; all other headers and section raw bytes are identical. Whole-image
  identity and the all-three-image/unified-source goal remain open. Recover
  evidence-backed original discarded inputs/TU boundaries; do not invent CRT
  code or relocation reservations. No game commit, push or live sync.
  Receipt: .scratch/goal21/server-data-fix/scope-final.json.

- 2026-10-11 (attested character renames completed before server fix):
  Public caller-aware rename operations apply seven diagnostic-attested names
  to14 client identities across13 C files: ch_AttachMotion, ch_TakingObject,
  ch_DroppingObject, CreateCharacterAtDummy, PlayCharacterAniScript,
  PlayCharacterAniScriptInt and SetCharacterCamera. All21 baseline/final COFF
  contexts preserve complete bodies, typed operands and compiler literals.
  Twenty matches freshly verify; inherited GOLD40afb0 SIZE_MISMATCH is unchanged.
  Game matched counts remain SERVER251/TL3583/GOLD2079. All-target lint has
  zero errors and inherited SERVER0/TL2/GOLD40 warnings. Naming/source-layout
  notes and all3 coverage documents refreshed. No CRT or new implementation.
  Receipt: .scratch/goal21/continuation/scope-final.json. That scope is terminal;
  do not rerun completed naming/native/COFF proofs. The original broad goal
  remains active; server data repair above supersedes its old raw/data pins.

- 2026-10-11 (character source placement continued after organization request):
  Previous immediate status-only goal turn was no progress; revalidated the finished
  MSX receipt instead of repeating it, then completed this new organization scope.
  Moved17 existing character C sources and1 canonical motion header into the attested
  Develop/DieGildeAddOn/game directory. Sixteen root sources removed; shared inferred
  CreateAnimationEvent now lives at game/CreateAnimationEvent.c, not the unrelated
  command-handler split directory. Canonical ch_motion.h moved beside its only user.
  Character-subsystem placement is inferred from native diagnostic/resource strings
  and task callbacks, not exact original character compilation-unit filenames.
  Native33-identity audit finds27 direct character diagnostics/resource references;
  all33 stock LIBCMT probes negative. No CRT source or library was changed.
  Public rehome previews/writes move all33 function identities and9 existing data
  rows across clients. Only4 include spellings changed; no function body, flags,
  storage, identity, view type or data verdict added/changed. All28 baseline and28
  final source builds pass, preserving34 complete COFF bodies, typed operands and
  compiler literals (including unbound GOLD preloader). The2 existing unmatched
  sitting-query bodies/statuses remain unchanged. All31 previously matched identities
  freshly verify (TL17/GOLD14); zero matches lost. TL3,583/4,905 and GOLD2,079/4,598
  unchanged. Lint0 errors, unchanged SERVER0/TL2/GOLD40 warnings; all3 coverage docs
  refreshed. Root backlog now3,836 C files, inventoried in remaining-root-inventory.json.
  Every unrelated C/header/config/layout/reference/server raw image and managed row
  is pinned and unchanged. Game HEAD383252b5/upstream42e0a8c0/inherited uv.lock unchanged.
  No upstream code defect encountered; no full tool-suite rerun for file placement.
  Source layout, naming notes and src/README.md updated. Receipt:
  .scratch/goal20/character-placement/scope-final.json. All scope jobs terminal.
  The failed staged-legacy scan is a terminal scratch diagnostic, not a final result;
  do not rerun it. baseline.json/final.json/verification.json are the completed checks.
  New next action: caller-aware attested character renames and shared reconstruction
  of the two remaining duplicate client pairs. Scene transfer TL403bc0/GOLD4033c0
  differs in scene-node light bit (TL+215 bit1, GOLD+211 bit3); TakeObjectScript
  TL40d410/GOLD40c4f0 differs in dummy name-pointer field (TL+40c/GOLD+104).
  Preserve these native build differences in typed shared C and prove actual targets
  before merging; generous relocation agreement is insufficient. Diagnostics in
  native-evidence.json attest their original function spellings. Other character
  sources have attested names awaiting caller-aware renames; exact original units
  remain unresolved. The prior TL420210 updater2-byte induction-base wall remains
  open; do not repeat its15 forms or quick flags. Upstream known-binding safeguard
  idea is already recorded. Full all3 raw-identity/source/naming/storage goal remains
  active and unfinished; no game commit, push or live sync.


- 2026-10-11 (MSX start/volume integration and false path-buffer twin repair):
  Completed verified progress; do not redo the prior33-body/native/sanitizer probes.
  Shared Units/Msx/msx.c now11 functions/22 client bindings. Added start/queue helper
  TL41fe10/GOLD423b30 (699), volume TL41fc10/GOLD423930 (98), and inferred
  unprefixed SetTrackPath TL420760/GOLD4243d0 (22). Two module fragments and one
  root GOLD raw-address copier retired through public migration/merge/rehome and
  managed identity writers. The volume API and all callers use canonical track
  pointers; no byte-pointer casts remain there. Default flags and error/lock behavior
  are preserved. ROOT backlog3,852 C files; full source organization remains open.
  GOLD423b30 was cross-imported through the CLI into the existing shared source,
  without duplicating the TL body. The704-byte inventory span includes5 NOPs;
  independent native return/branch checks establish699 bytes. Stock CRT attribution
  identifies the formatter; no CRT source or archive was patched/reimplemented.
  Strict native checking exposed an older false twin: src/GOLD.fcn_00478860.c
  paired TL420760 music-path storage14cc360 with GOLD478860 game storagef8aae0.
  The true GOLD music-path counterpart is4243d0, using14611a0. TL420760 and
  GOLD4243d0 now share SetTrackPath in MSX; both game callers use its canonical
  declaration. The unrelated GOLD478860 retains its22-byte native body andf8aae0
  destination, with provisional g_f8aae0. Old literal-address loop at4243d0 is gone.
  Canonical path declarations now bind TL14cc360/GOLD14611a0; one new alias view,
  two old data relationships corrected. Complete buffer extents, original names and
  allocation owners are unresolved; no storage allocation or data verdict invented.
  Both old stores and every unrelated source/header/config/layout/reference/server
  raw image are pinned. Twenty successful baseline builds and15 successful final
  builds preserve33 complete baseline COFF bodies/typed operands. The repaired
  GOLD path helper matches all22 native bytes, as does the unrelated game copier.
  The shared unit reproduces3404 complete native bytes with206 actual typed
  relocation operands and206 isolated wrong-target controls. Unresolved operands
  are observed from native bodies and checked across uses, literals and native call
  entries; this does not establish unknown callee/library/global ownership.
  1083 strict C89 32-bit ASan/UBSan volume/lock-order cases and1785 path-copy cases
  pass. The path test's512-byte fixture is not a binary allocation-extent claim.
  33 fresh byte matches pass(TL19/GOLD14), none lost. TL3,583/4,905 remains
  282 EXACT/3,301 RELOC. GOLD2,079/4,598 now119 EXACT/1,960 RELOC. Unchecked
  globals TL277/GOLD241 count the newly described alias, not data byte progress.
  Lint0 errors, unchanged0/2/40 warnings; all3 coverage documents refreshed.
  TL420210 updater remains793 bytes against791, with code/old status preserved.
  The loop anchors at track+110 rather than native+118; six differing instruction
  widths give+2 bytes. Fifteen C/type/context probes and the quick flag sweep did
  not solve it. Blocker/delta2 recorded through the CLI. Do not rerun those probes:
  updater-diff-before.json, updater-probes*.json, updater-in-unit.json,
  signed-volume-view.json and updater-flags.log record the results in this scope.
  Upstream42e0a8c0 code unchanged; the documented generous DIR32 agreement mode
  masked the false known buffer binding. Added a known-binding hardening proposal
  to upstream docs/IDEAS-GUILD.md immediately. It is a missing safeguard beyond the
  current documented contract, not a newly fixed code defect. Prior ideas and
  inherited uv.lock preserved; no unnecessary full upstream suite repeat.
  Receipt: .scratch/goal20/msx-start-volume/scope-final.json. Jobs all terminal.
  No game commit, push or live sync; all3 raw-identity/source/naming/storage goals
  remain active and unfinished. Next: close the TL updater's induction-base match
  with a new statement/alias-analysis hypothesis, not repeated loop or quick flag
  trials. Consider the upstream known-binding safeguard before further cross-import
  so an existing named global conflict cannot silently earn an agreement match.

- 2026-10-11 (canonical MSX track view and source consolidation):
  Completed the previous next step; do not redo its broad baseline or native probes.
  Shared Units/Msx/msx.c now8 functions/16 client bindings: added ordinary acquisition
  TL41fd70/GOLD423a90 (151), ambient acquisition TL420780/GOLD4243f0 (186), and
  active-track selection TL420650/GOLD4242c0 (49) to the previous5-function unit.
  Three module fragments retired through public migration/merge/rehome writers.
  Root TL420210 updater now lives beside the MSX unit; its793-byte compiled body
  is preserved, with the old791-byte SIZE_MISMATCH still unresolved. Root backlog
  now3,853 C files. Existing file/unit names are provisional except attested paths.
  Canonical296-byte Chan_14cc460 now describes the previously opaque24-byte tail,
  including unsigned volume at0x118 and self-pointer at0x124. Removed two local
  full-track duplicates in1fe10/20210. Replaced legacy b106 with attested bAmbient;
  other field/type names remain provisional. Shared header signatures and five
  game callers now use track pointers instead of integer returns/slots. Removed
  one duplicate identical double declaration; SDK locking and error behavior remain.
  Selector now uses valid indexed C, preserving both49-byte native bodies and
  removing fake raw-address end-object declarations. Two older crossed native
  pointer-store operands in TL4c2100 are corrected by the chained assignment
  g_772d1c = g_772d20 = track. Declaration ordering alone did not fix them; both
  standalone and merged objects were checked, with no volatile workaround used.
  All558 sources in the conservative include/use closure were pinned first:
  884 baseline builds successful;878 final builds successful;928 complete baseline
  function bodies preserved with their typed operands and compiler literal bytes.
  Two indexed selectors and two corrected store operands have independent native
  proof. Entire shared unit matches1766 native bytes across both clients, with112
  strict typed relocation operands and112 isolated wrong-target controls.8704
  strict C89 32-bit ASan/UBSan cases check296-byte layout, self-pointers, unsigned
  tail values, all byte flag values and first-active priority. Prior1608/404-case
  harnesses were not redundantly rerun; their historical receipts stay intact.
  GOLD acquisition old160/192 spans included9/6 NOPs; native terminal returns and
  every direct branch establish151/186 complete bodies. Managed identity writer
  corrects only those2 extents; final statuses come from fresh public verification.
  879 fresh matches pass:TL568/GOLD311. No existing match lost. TL3,583/4,905
  (282 EXACT/3,301 RELOC); GOLD2,077/4,598 (119 EXACT/1,958 RELOC).
  Five observed4-byte pointer-slot views now use canonical client_sound.h declarations:
  TL772d1c/20/24 and GOLD6f0b6c/74, proven from actual native operands. GOLD's
  unused corresponding20 slot is not invented. Two old first-active-byte views
  retain their table backing and move to the canonical MSX header. No new storage,
  allocation owner or data verdict. Unchecked globals TL277/GOLD240 include the
  newly described views, not data byte progress. Lint0 errors and unchanged0/2/40
  warnings; all3 coverage documents refreshed. All unrelated sources, headers,
  metadata rows, config, layout, references and server raw image remain pinned.
  Upstream42e0a8c0 unchanged; no new tool defect or unnecessary full-suite repeat.
  Inherited uv.lock and IDEAS-GUILD.md preserved. Jobs terminal; no game commit,
  push or live sync. Receipt: .scratch/goal20/msx-track-type/scope-final.json.
  Next: reconcile remaining MSX start/volume/updater contracts and original names.
  GOLD's acquisition calls independently target423b30, but the shared1fe10 C source
  has no GOLD identity yet; prove its complete native body before cross-import or
  including it in the shared unit. Inspect stock-library attribution first. Keep
  TL updater's791/793 mismatch separate from its successful type/placement cleanup.
  Continue evidence-based unit organization; no bulk merge from address adjacency.
  All3 raw byte-identical binaries, client raw links/data and full source/naming/
  storage ownership goal remain unfinished; this is a verified progress checkpoint.

- 2026-10-11 (MSX table helpers and caller contracts):
  Completed the previous next step; do not redo the table/native/behavior probes.
  Folded two root sources into shared Units/Msx/msx.c, now5 functions/10 client
  bindings. Renamed the shared lookup/free-slot helpers through the CLI to inferred
  unprefixed FindTrackByName (TL4205e0/GOLD424250) and FindFreeTrack
  (TL420690/GOLD424300). Their original spellings and exact helper units remain
  unproven. Native table base TL6b71b0/GOLD6325d0, ten296-byte records, plus
  dummy record TL14cc460/GOLD14612a0 are declaration-only views. The native startup
  independently clears296 dummy bytes (ECX74/REP STOSD). Four new view rows and
  two previously section-only first-active-byte rows now record their table backing
  at offset0x104. No storage owner, allocation definition or data verdict invented.
  Retired duplicate src/g_6b71b0.h; its3 direct users reuse canonical track/header
  declarations. Rehomed the existing49-byte active-track selector from root into
  Units/Msx with both COFF bodies unchanged. Its raw loop-bound/return contract and
  the fully expanded local Chan in1fe10 still need reconciliation; not called done.
  Two older module callers fcn41fbd0/4200d0 now take const-char strings and typed
  track returns, using SDK critical-section imports instead of TL absolute guards/
  locks. Native outer lock ordering is preserved: stop happens after unlock,
  volume dispatch happens inside it. Acquisition users reuse canonical pointers/
  sizeof and header prototypes; volume explicitly receives its existing char*
  byte view. Complete canonical track tail and allocation ownership remain pending.
  Whole994 main bytes +130 caller bytes/72 actual operands strictly match;72
  independently isolated wrong-target controls reject.404 C89 ASan/UBSan table,
  record-preservation and caller-order cases pass.21 old COFF bodies unchanged;
  both corrected callers relocate to their unchanged complete native bytes.13
  affected final builds +2 input-identical volume objects reused; no redundant
  rerun of the earlier1608-case MSX harness. Previous raw-caller linked bodies
  independently checked against the same native130 bytes.
  GOLD lookup/free-slot old112-byte spans included6/10 trailing NOPs. Native
  terminal returns and every direct branch establish complete106/102-byte bodies;
  public identity writer normalizes only these2 sizes.19 fresh matches pass
  (TL12/GOLD7); two older GOLD acquisition SIZE_MISMATCH rows remain unchanged.
  TL3,583/4,905 (282 EXACT/3,301 RELOC); GOLD2,075/4,598 (119 EXACT/1,956 RELOC).
  Unchecked globals TL274/GOLD238: two new table/dummy views and one completed
  section-only interior row per client. Lint0 errors, unchanged0/2/40 warnings;
  all3 coverage documents refreshed. Root backlog3,854 C files. Full pin/store
  closure preserves server C/H/config/raw/reference and every unrelated source/
  row. Four old literal rows retain all semantics; only rehome timestamps changed.
  Upstream remains42e0a8c0, inherited uv.lock and IDEAS-GUILD.md unchanged. No
  new tool defect, so no upstream code/full-suite repeat. Fixed migration/rename/
  merge/rehome APIs moved all identities; no hand-edited stores or new markers.
  Receipt: .scratch/goal20/msx-track-table/scope-final.json. Jobs all terminal.
  No game commit/push/live sync; client raw-link/data identity still unverified.
  Next: reconcile the complete MSX track type and remaining selector/acquisition
  contracts from native evidence. Inspect local full Chan in1fe10, root20210,
  old active selector20650, canonical Chan_14cc460's opaque tail and all540 direct
  client_types.h users before changing that broad header. Preserve current native
  behavior and all field offsets/Win32 pointer widths, including linkage at0x124.
  Then consolidate acquisition20780 and1fd70 with the unit; prove their GOLD
  padded extents before promotion. The older1fd70 game callers still declare int
  track returns and keep integer globals; trace their whole use scopes first.
  Keep working toward all3 raw binaries plus original-style names/storage/tree;
  this batch does not complete the full goal or all source organization.


- 2026-10-11 (shared MSX source consolidation and upstream merge repair):
  Completed the prior next step; do not redo its native or behavior probes.
  Three functions now share src/Develop/Units/Msx/msx.c with canonical msx.h:
  fade TL420700/GOLD424370 (81), channel stop TL420120/GOLD423df0 (126),
  ambient stop TL420840/GOLD4244b0 (82). Both wrappers attest the original
  D:\develop\units\Msx\msx.c path and hTrack->bAmbient expression. Helper
  placement follows channel calls/state; original function/type names and full
  storage owners remain unknown. Removed three obsolete inputs, including the
  falsely placed game/GOLDTL.sim.c. One C source serves six managed bindings.
  Reused canonical296-byte Chan_14cc460 and SDK24-byte critical section; removed
  the local duplicate track type. Fade mode is scalar; two game callers now use
  canonical track-pointer declarations through client_sound.h/msx.h. b106 remains
  the old spelling of attested bAmbient; wider540-user type cleanup is pending.
  All578 native bytes and40 actual operands match;40 independently isolated
  wrong-target controls reject. C89 ASan/UBSan1608 cases pass, including nested
  locks, signed handles, whole records and assertion arguments. Mock assertion
  returns; native CRT abort/dialog was not executed. Stock _assert whole-body
  matches both clients; the two new GOLD twins are not library functions.
  All17 surrounding complete COFF bodies/typed operands preserve prior output
  across15 builds. Fresh public verification12 TL +10 GOLD passes; no matches lost.
  Sixteen declaration/import/literal rows add no storage or data verdict.
  Native import slots are excluded from the global denominator: TL271 and GOLD235
  unchecked globals. TL3,583/4,905 (282 EXACT/3,301 RELOC), GOLD2,073/4,598
  (119 EXACT/1,954 RELOC). Lint0 errors with unchanged0/2/40 warnings; all3
  coverage documents refreshed. Root source backlog remains3,857 C files.
  The real merge exposed Rebrew deleting legacy-marker inputs without retargeting
  coexisting managed rows. Restored the exact inputs, reproduced the bug, then
  fixed upstream (no metadata workaround) as42e0a8c01fecad54953df55080a864a1e676313d.
  Legacy merges now retarget all targets/data via existing locked rollback writer
  and refuse absent bound definitions before writing. Seven new regression cases;
  full suite11,620 passed/51 skipped/0 failed. Final typing-only corrections pass
  focused72 tests, full Ruff/format/Mypy and commit hooks. Actual upstream main
  fast-forwarded; inherited uv.lock hash and IDEAS-GUILD.md change preserved.
  Fixed CLI preview/apply moves all4 existing rows; the2 new GOLD rows remain.
  Scope and compile-input/store/server-raw preservation receipt:
  .scratch/goal20/msx-shared-unit/scope-final.json. All jobs terminal; no game
  commit/push/live sync or client raw-link/data identity claim. Whole goal open.
  Next: continue native-evidence source organization and shared MSX declarations.
  Inspect root track lookup/free-slot helpers src/GOLDTL.fcn_004205e0.c and
  src/GOLDTL.fcn_00420690.c and their TL/GOLD managed identities before placement
  or consolidation with the known track acquisition TL420780/GOLD4243f0. The
  neighboring helpers' pointer/string declarations conflict in older callers;
  resolve from native operands and complete COFF proof, not merely directory
  affinity. Reuse the finished shared-unit proof and preserve unrelated sources.
  Do not rerun finished compiler walls, path scan or completed match scopes.


- 2026-10-11 (native unit evidence, MSX grouping and EndScene repair):
  Native path/operand scan finds37 directly referencing functions across both clients.
  Moved13 MSX channel sources under Develop/Units/Msx: TL420840's msx.c path is
  attested; all13 native TL bodies reference the same critical section. Other exact
  units/names remain inferred. Rehomed20 function identities through locked writers;
 19 pre-existing COFF bodies/typed operands unchanged across20 builds. GOLD438780
  now occupies attested Units/d3/d3_d3d.c and uses its attested EndScene expression.
  Repaired wrong vtable slot40/extra dereference to slot10 and inverted error test
  to nonzero. Full44 native bytes/5 operands equal;5 wrong-target controls reject;
  6 C89 sanitizer cases check this/method/result/diagnostic. Added owning-subsystem
  declaration header and4 pointer/scalar/literal views, no storage/data verdict.
  Original function/interface types and complete allocation owners remain unknown.
 17 fresh matches pass,3 incomplete GOLD channel rows unchanged, no matches lost.
  TL3,583/4,905; GOLD2,071/4,598 (119 EXACT/1,952 RELOC),229 unchecked globals.
  Lint0 errors, unchanged0/2/40 warnings; all3 coverage documents refreshed.
  Remaining3,857 root C files inventoried in native-unit-batch/remaining-root-inventory.json.
  Upstream135d57e7 and inherited uv.lock unchanged; native source-unit inventory
  feature recorded in upstream docs/IDEAS-GUILD.md. No upstream code defect/full
  suite rerun. Receipt: .scratch/goal20/native-unit-batch/scope-final.json.
  Next: canonicalize TL420840's raw-address music guard/critical section/imports/
  assertion/helper bindings, then verify the structural100% GOLD4244b0 twin from
  one shared MSX source. Preview identifies it; no GOLD row promoted yet. Reuse
  current native-unit-map/{msx,gold-msx}-asm.json and msx-import-preview.json.
  Preserve completed/retired match scopes and compiler walls. Whole goal open;
  no game commit/push/live sync. All current jobs terminal.


- 2026-10-11 (source organization started at user request):
  Moved8 existing C files and2 headers into evidenced game, VFS, net, d2 and d3
  directories under src/Develop. Managed rehome preview/apply updates all affected
  function/data rows across clients. Only3 include spellings adjusted; no function
  body, compiler flags, storage or other source changed. All19 complete COFF bodies
  and typed operand bindings preserved across13 builds;12 matched identities freshly
  verify,2 existing incomplete identities unchanged. TL3,583/GOLD2,070 matches unchanged.
  Lint0 errors, unchanged0/2/40 warnings; all3 coverage documents refreshed.
  Placement evidence and inferred units documented in docs/source-layout.md; src/README.md
  explains the unassigned root backlog. Still3,871 root C files,3,865 address named.
  remaining-root-inventory.json lists their managed identities. Automatic TL CU map's
  three broad clusters do not justify bulk original-unit placement or merging.
  Receipt: .scratch/goal20/source-organization/scope-final.json. No new upstream
  defect, commit, push or live sync; whole goal remains open. All jobs terminal.


- 2026-10-11 (worker-housing callback and pointer return repaired):
  False TL49d640 cm_ExAllocClientSpieler binding corrected to inferred RunBuergermeister;
  GOLD49dc00 counterpart added to shared src/RunBuergermeister.c/client_actions.h.
  Native action registration attests Buergermeister, id0x2e. Both369-byte bodies
  strictly match52 actual relocation operands;52 wrong-target controls reject.
  7,200 C89 sanitizer cases check full248-byte packets, callbacks and results;
  25 cases check repaired fcn00507ab0 pointer return. Both helpers68 bytes and
  initializers9106 bytes retain full COFF code/typed bindings; four fresh RELOCs.
  Sixteen data views/literals recorded, no new storage or data verification claims.
  Original unit/domain types and cross-TU calendar view consolidation unresolved.
  TL3,583/4,905 (282 EXACT/3,301 RELOC); GOLD2,070/4,598 (119/1,951).
  Lint0 errors, unchanged0/2/40 warnings; all3 coverage documents refreshed.
  Other source/header/config/layout/reference/server pins and rows unchanged;
  zero prior matches lost. No new upstream defect, commit, push or live sync.
  Receipt: .scratch/goal20/mayor-worker-housing/scope-final.json; all jobs terminal.
  User steers next work to proper source organization: root still has3,879 C files.


- 2026-10-11 (fourth false command binding repaired; shared GUI image update matched):
  TL466330 is not cm_ExAllocThemaPredigt. Its complete176-byte body and GOLD469240's
  complete190-byte counterpart now share inferred d2_SetElementImage in src/d2_gui.c,
  with canonical declarations and accessed views in d2_gui.h. Original function/unit
  spelling remains unproven; attested d2_ prefix and native GUI/resource flow support
  the module/role. The genuine SERVER1000f2f0 command handler and command.c are unchanged.
  TL uses756-byte GUI entries,32-bit dimensions/clipping and offset+88. GOLD reuses
  existing748-byte GuiEnt,16-bit dimensions/clipping, offset+78 and its unchanged-image
  early return. gold_gui.h's six-byte padding at+76 is enriched as two-byte padding
  followed by bild_offset; all15 existing users retain complete COFF code/typed operands
  and freshly verify RELOC. Native clip load/zero order required two C forms; no flags
  or GA sweep. All366 native bytes strictly agree after resolving20 actual operands
  from managed catalog;20 individual wrong-target and4 damage controls reject. Final
  public tests: TL176/176, GOLD190/190 RELOC,10 relocations each. MSVC6 asserts both
  native32-bit layouts and84-byte resource stride/dimension offsets. Host64-bit C89
  checks with address/undefined sanitizers pass8,640 cases against independent field
  writes and callback event/argument expectations, including signed dimensions,
  clipping extremes, unchanged-image behavior, kind threshold and load-side mutations.
  Native valid-index preconditions retained; invalid indices are not claimed tested.
  Ten managed alias views bind existing C spellings to native .data zero-filled-tail
  pointer/scalar accesses; no storage, backing owner/complete extent or data verdict
  invented. TL has9 direct call sites, including separate70-byte4bfbc0 merged into
  the discovery range for4bf8e0; its call is after the existing734-byte dialog return
  and2 alignment bytes. Existing dialog C is not missing the call. Both clients'
  direct callers are unreversed; no existing update reference needs renaming.
  Only2 source/header files added, gold_gui.h enriched,2 function identities corrected/
  added,15 existing GUI verification records refreshed and10 data rows changed. All
  other C/H/config/layout/data/function/reference/server raw pins preserved; zero
  existing matches lost. GOLDTL3,582/4,905(73.0%):282 EXACT/3,300 RELOC,80 size,
  14 near,3 stubs; accounted text44.5%,258 unchecked globals. GOLD2,069/4,598(44.9%):
  119 EXACT/1,950 RELOC,218 unchecked globals. Lint0 errors, unchanged0/2/40 warnings;
  all3 coverage documents refreshed. Upstream135d57e7 and inherited uv.lock unchanged;
  no new tool defect or completed-suite rerun. Full goal ACTIVE; no game commit/push/
  live sync. Receipt: .scratch/goal20/ui-resource-bind/scope-final.json; all jobs terminal.
  Continue false TL49d640 cm_ExAllocClientSpieler binding: stock miss,119/123 structural
  instructions (ratio0.9675); native worker-housing strings upgr_arbeiter_unterk and
  bau_arbeiter_unterk,369 complete bytes plus15 NOPs. No production edit for that body
  yet; establish original module/name, globals/callers and GOLD counterpart from
  ui-resource-bind/next-49d640-{library,diff,recon}.json. Skip completed/retired probes
  and existing AHM/NUL/sitting/pool/table-entry/task/animation matching walls.


- 2026-10-11 (third false command binding repaired; shared water-region fill matched):
  TL43bf60 is not cm_ExAllocRaum. Its complete268-byte body is a six-argument
  square byte-grid flood fill, with three self-recursive neighbors and a
  fourth tail loop. GOLD440170 is identical over all268 native bytes. One
  pure C implementation now owns both managed identities under inferred
  d3_FillWaterRegion, in inferred src/d3_floor.c with d3_floor.h declaration.
  The correct attested SERVER cm_ExAllocRaum1000d350 and command.c are unchanged.
  Only external callers TL43db70 / GOLD440360 prepare floor water; their
  d3_fl:Water allocation labels and PrepareFloorWater diagnostic establish
  module/role, not this helper's original spelling or compilation-unit path.
  Both external callers are unreversed; no existing C reference to rewrite.
  Stock-library misses: TL's completed receipt reused, GOLD checked fresh.
  First C form matches all536 bytes after applying6 real self-call operands;
  all6 individually wrong-target controls and4 damage/truncation controls
  reject. Both final actual objects equal the proven stage code/operands.
  Public test268/268 RELOC in both clients. Host C89 behavior check with
  address/undefined sanitizers passes6,274 cases against independent queue
  fill, including borders, disconnected cells, initial non-old seed behavior,
  full-width positive/negative color arguments and guard preservation.
  Native valid-coordinate/different-low-byte-color preconditions retained;
  no extra guard invented, invalid inputs not claimed tested.
  Only2 function rows changed,2 shared source/header files added; all previous
  C/H/config/layout/data/reference/server metadata/raw pins unchanged. Zero
  prior matched statuses lost; no global or C storage allocation introduced.
  GOLDTL3,581/4,905(73.0%):282 EXACT/3,299 RELOC,81 size,14 near,3 stubs;
  accounted text44.5%,254 unchecked globals. GOLD2,068/4,598(44.9%):119 EXACT /
  1,949 RELOC. Lint0 errors, unchanged0/2/40 warnings; coverage refreshed all3.
  Upstream135d57e7 unchanged; no new tool defect, no completed suite repeated.
  Naming guide's stale statement excluding client modules corrected to the
  current three-target goal. Evidence: .scratch/goal20/grid-flood-fill/scope-final.json.
  Full goal ACTIVE; no game commit/push/live sync; all scope jobs terminal.
  Continue the remaining mismatched client command.c identity audit, starting
  TL466330 cm_ExAllocThemaPredigt. Initial audit disproves that packet-handler
  binding:176-byte native body updates756-byte indexed records using resource
  release/acquire and signed dimensions from84-byte entries. Stock archive
  miss; structured diff saved. No C or metadata changes yet; establish module,
  globals/callers and GOLD counterpart from next-466330-{library,diff,asm}.json.
  Skip retired403040/4042b0/406120 and existing
  AHM/NUL/sitting/pool/table-entry/task/animation matching walls.


- 2026-10-11 (second false command binding repaired; shared motion cleanup matched):
  TL404410 is not cm_ExClearLagerslot. Its334-byte body and GOLD403c10's
  331-byte counterpart finish the active motion, optionally creating and
  attaching a named morph continuation. One shared C body now owns both
  managed identities under inferred ch_FinishAni. The attested SERVER
  cm_ExClearLagerslot1000e690, command.c and all SERVER inputs remain unchanged.
  Eight native caller sites found across four unreversed owning functions;
  there are no existing C callers to rewrite. Neighbor diagnostics belong
  to ch_CheckAniMorph4045c0, not this function; do not claim that attested name.
  Native version difference retained: continuation stream field+0x318 in TL,
  +0x10 in GOLD, plus each edition's existing character-index helper.
  Reused the matched12-byte motion-options view, including native partial
  initialization. First form had11 different bytes in two swapped field
  stores; one initialization-order adjustment matches all665 native bytes.
  Strict proof applies all18 actual operands;18 wrong-target and4 byte
  damage/truncation controls reject. Library misses exclude stock bodies;
  GOLD sprintf archive check matches, TL's completed stock proof reused.
  Public tests TL3/3 and GOLD2/2 pass; all4 pre-existing COFF bodies and
  typed operands unchanged, zero prior matches lost. No GA/flag sweep or
  historical probes repeated. New ch_motion.h supplies inferred declarations.
  ch_MorphFrameValue is a declaration-only accessed4-byte view at TL675314 /
  GOLD5f129c, initializedffffffff in references. Backing allocations and
  storage owners unknown:2 alias rows added, no C storage or data verdict;
  all existing data rows preserved. Only2 new/repaired identities and3
  refreshed function verifications; other C/header/config/layout/raw pins
  unchanged. GOLDTL3,580/4,905(72.9%):282 EXACT/3,298 RELOC,82 size,14 near,
  3 stubs;254 unchecked globals. GOLD2,067/4,598(44.9%):119 EXACT/1,948 RELOC,
  213 unchecked globals. Lint0 errors, unchanged0/2/40 warnings; all3 coverage
  documents refreshed. Upstream135d57e7 unchanged; no new tool bug found and
  no completed suite repeated. Evidence:
  .scratch/goal20/character-motion-clear/scope-final.json.
  Full goal ACTIVE; no game commit/push/live sync; all scope jobs terminal.
  Continue auditing remaining mismatched client command.c bindings, starting
  TL43bf60 cm_ExAllocRaum. Initial audit now shows a268-byte six-argument
  square byte-grid flood fill, with4 external NOPs. Stock archive miss;
  structured diff disproves the command-handler binding. No production
  changes or C/flag probes yet; saved next-43bf60-{library,diff,asm}.json and
  next-binding-audit.json. Establish callers/unit/name and GOLD counterpart.
  Skip retired403040/4042b0/406120 and the completed
  AHM/NUL/sitting/pool/table-entry/task/animation matching walls.


- 2026-10-11 (false TL command binding repaired; native motion helper matched):
  TL404ca0 is not cm_ExAllocSpieler: its complete283-byte body preloads named
  character model motions. Corrected its identity through the managed writer
  to inferred ch_PreloadModelMotions in the existing shared motion-loader file.
  The correct attested SERVER cm_ExAllocSpieler and all command.c inputs remain
  unchanged. Reused the existing12-byte option view and character loader calls;
  preserved both native literal reads from address0x34. Independent inventory
  function scans found no direct callers, and no absolute pointer references
  occur in the shipped image. GOLD importer preview and bounded complete-body
  shape scan establish no counterpart; no GOLD identity was invented.
  Strict proof matches all283 bytes with9 actual operands. All9 wrong-target
  controls and2 byte-damage/truncation controls fail. Compiler literals match
  complete native strings; stock archive matching includes sprintf, and two
  independent native loaders establish the external animation attachment VA.
  Public tests pass TL2/2 and GOLD1/1. Both existing loader COFF bodies and
  typed operands remain unchanged; all prior matched statuses preserved.
  Two existing inline markers removed after confirming their managed rows;
  pure C body added, no asm, flag change or storage definition. Only3 function
  rows changed: corrected TL identity/verdict and2 refreshed verifications.
  All other source/header/config/layout/data/reference/server rows and raw
  image pins unchanged. GOLDTL3,579/4,905(72.9%):282 EXACT/3,297 RELOC,
  83 size,14 near,3 stubs; accounted text44.5%,253 unchecked globals. GOLD
  stays2,066/4,598. Lint0 errors, unchanged0/2/40 warnings; coverage refreshed
  all3. Upstream135d57e7 unchanged; no new tool defect or repeated suite.
  Evidence: .scratch/goal20/alloc-spieler-client/scope-final.json.
  Full goal ACTIVE; no game commit/push/live sync. All scope jobs terminal.
  Correction to previous next pointer: TL4042b0 was already retired in
  docs/TODO.md Round149 (66/80; unsigned-byte extension wall). Do not redo it.
  Also skip known retired403040/406120 and bounded existing matching walls.
  Next: audit the remaining mismatched client command.c bindings, starting
  TL404410 cm_ExClearLagerslot. Initial audit now disproves that binding:
  stock archive miss;107/108 diff instructions structural, native334 bytes
  plus2 external NOPs operate on character motion pointers, with optional
  continuation attachment. Saved next-404410-{library,diff,asm}.json and
  next-binding-audit.json. GOLD403c10 is only a candidate; no proof or import
  yet. No production changes or C/flag probes made for this next helper.


- 2026-10-11 (missing managed source bindings repaired upstream; saved work recovered):
  Fresh todo's TL40df00 was not new work: CharacterSitting's completed
  definition was absent from its current neighboring file, while its identity
  and blocker survived. Four other completed bodies were also missing:
  CharacterSitsDown40e110, task unlink4050c0, animation control405540 and
  sound constructor418c80. All five recovery copies exactly match their
  recorded verification source hashes in .scratch/goal-resolver-consolidation/
  before/src. Restore finished work; never repeat its old reconstruction/probes.
  Upstream135d57e7 now reports missing managed bindings as extract-error
  repairs with their real names/blockers instead of a new skeleton. Actual
  source coverage remains unchanged by the tool fix. Other targets/libraries
  are excluded; cached matches cannot hide a missing scanned binding. Six
  regression cases;427 focused passed/1 skipped;358-file Mypy and all hooks
  pass. Full suite11,613 passed/51 skipped/113 warnings in339.96s; final
  doc recheck27 passed. Committed and fast-forwarded into local upstream main;
  original uv.lock diff preserved, no push. GOLD/SERVER preview found0 repairs.
  Five exact saved C files restored; no identity/flag/name/data-store changes.
  Fresh13-identity verification: TL6/10, GOLD3/3, no prior match lost. All8
  existing neighboring COFF bodies/typed operands unchanged. Constructor
  TL418c80 again RELOC150/150; strict full-byte proof applies all6 operands,
  with6 wrong+4 controls rejected. Its strncpy64d530 callee independently
  matches the stock LIBCMT archive. Library attribution is intentionally
  excluded from the ordinary callee catalog; the proof adds this verified
  binding explicitly. No CRT body, library bytes or storage owner invented.
  Four old first passes remain unmatched. Current measurements: flag queries
  C52/native56 with16 differing bytes each; animation C102/native94 with72
  differences; task unlink12 differences. Three stale blocker deltas refreshed
  via CLI, preserving historical walls and controls. No new flag/GA/body probes.
  GOLDTL3,578/4,905(72.9%):282 EXACT/3,296 RELOC,84 size,14 near,3 stubs;
  covered3,679(75.0%),1,226 no source; accounted text44.5%,253 unchecked globals.
  GOLD remains2,066/4,598(44.9%). SERVER source inputs/raw SHAa96692d9 unchanged;
  no new server link required. Lint0 errors with unchanged0/2/40 warnings;
  coverage refreshed all3. Evidence:
  .scratch/goal20/missing-character-bindings/scope-final.json.
  All jobs terminal. Full goal ACTIVE; no game commit, push or live sync.
  Next unstarted candidate TL4042b0 has saved library/asm receipts under
  .scratch/goal-character; inspect them before new work. Skip known retired
  403040/406120 and existing ahm/NUL/sitting/pool/table-entry/task/animation walls.


- 2026-10-11 (parent/getter extents verified; table-entry controls finished):
  GOLDTL now3,577/4,905(72.9%):282 EXACT/3,295 RELOC,81 size,
  13 near,3 stubs;1,231 without source; accounted text44.5%,253 unchecked
  globals. GOLD2,066/4,598(44.9%):119 EXACT/1,947 RELOC.
  gm_ResolveParentEntity TL50d490/GOLD50a050 is82 bytes plus14 external
  NOPs; gm_GetEntityType TL50d530/GOLD50a0b0 is62 plus2 external NOPs.
  Both clients match the complete existing shared bodies after all6 actual
  relocation operands are applied; all6 wrong+4 controls invalidate their
  changed operand. Only4 managed extents/notes and2 precise comments changed;
  no C body, header, flags, ABI, data allocation or storage owner changed.
  gm_GetEntityType returns the resolved static first word or dynamic+0x27,
  otherwise0xffff; its inherited domain name remains inferred.
  All127 owner identities verified: SERVER63/63, TL27/34, GOLD26/30;
  no previously matched function lost. All156 COFF bodies/typed operands
  remain unchanged in each target. Fresh SERVER verification316/316 EXACT,
  251/251 placement; same raw SHAa96692d9 and16,580 differing file bytes;
  648/652 data with the same4 span DRIFTs; whole-image match remains false.
  Imports100, including order and IAT slots, unchanged. Lint0 errors with
  unchanged0/2/40 warnings; coverage refreshed all3.
  Table-entry helper:8 isolated formulations/24 target builds, no safe winner.
  Two bounds forms broke SERVER; cached-word form changed an unrelated caller.
  No production C or flags applied; clients remain65 bytes/11 differences
  and receive managed blockers. Flag/identifier sweeps were not performed.
  Evidence: .scratch/goal20/parent-type-extents/scope-final.json and
  .scratch/goal20/table-entry-shape/probe{,-phase2,-phase3}-complete.json.
  Upstream8e74ba3a unchanged; no new Rebrew defect found, no suite repeated.
  Full goal ACTIVE; no game commit/push or live sync. Completed probes must
  not be repeated; next unblocked todo is TL40df00 after library attribution.


- 2026-10-11 (stat/group helpers consolidated and verified):
  Existing shared gm_CheckStatLevel TL5074e0/GOLD5044b0 now has the complete
  87-byte extent, excluding9 external NOPs. Its five actual operands are
  bound to the correct client globals and callees through strict proof.
  gm_MapEntityStatRange TL507b00/GOLD504ad0 is the existing shared291-byte
  spiel.c body:123 code bytes, one internal alignment byte,72-byte branch
  table and95-byte case map;13 external NOPs excluded. All95 cases/default
  are checked. The duplicate GOLDTL.fcn_00507b00.c is retired, and its caller
  aliases (including GOLD's fcn_00504ad0) use the canonical shared name.
  gm_GetEntityTableEntry TL509570/GOLD506430 is newly bound to the existing
  shared implementation:65-byte native CFG plus15 external NOPs, kinds5/6/7,
  flag0x8000, index0..15, stride172. It remains NEAR_MATCHING with11 register/
  scheduling differences in each client; never count it as byte-matched.
  The canonical spiel.h prototypes replace inconsistent caller declarations;
  typed casts retain callers' existing reconstructed views. Original helper
  names and domain types remain inferred. False threshold/clamping comments
  in spiel.c are corrected. Four new client data rows are declaration-only
  aliases: g_entity_type_bytes is g_slot_table+0x164, and g_entity_base is the
  accessed16*172-byte view. No new C storage; full backing allocations and
  native storage owners remain unresolved.
  New header declarations initially changed SERVER gm_ObjectsAvailble's
  allocation; moving the whole header later fixed SERVER but changed TL.
  One accidental duplicate prototype insertion was also corrected. Final
  SPIEL_EARLY_STAT_DECLARATIONS preserves the owning TU's proven declarations
  and its include after gm_Open; callers receive the canonical prototypes.
  All156 owning COFF bodies/typed operands are unchanged in each of the three
  targets. All47 changed source/header files preserve C diagnostic positions;
  112 source/header files are in the affected closure. Public verification
  covers447 identities: SERVER151/151, TL148/173, GOLD103/123; no previously
  matched function lost and no compile/extract errors. Native proof examines
  1,330 bytes: seven full matches totaling1,200 bytes and two65-byte helper
  identities with11 differences each. All78 wrong+4 controls invalidate the
  changed operand, including the two unmatched helpers. Evidence:
  .scratch/goal20/stat-level-extent/scope-final.json.
  A clean debug-OFF SERVER build returns the same raw SHAa96692d9:316/316
  compiled EXACT including65 libraries,251/251 placements,275 raw-linked
  promotions,648/652 data with the same4 span DRIFTs. Raw remains16,580 bytes
  different, .text+16/.reloc-300,100 matching imports including their order
  and IAT slots. Whole-binary verification remains false without tool errors.
  TL3,575/4,905(72.8%, percentages floor):282 EXACT/3,293 RELOC,83 size,
  13 near,3 stubs;1,231 no source; accounted text44.5%,253 unchecked globals.
  GOLD2,064/4,598(44.8%):119 EXACT/1,945 RELOC,429 size,23 near,7 stubs;
  212 unchecked globals. Lint0 errors with unchanged0/2/40 warnings; coverage
  refreshed all3. Upstream main remains8e74ba3a; no new Rebrew tool defect
  found and no upstream suite repeated. All jobs terminal. Full goal ACTIVE;
  no game commit or push. Next unblocked todo is the newly bound table-entry
  helper509570, then gm_ResolveParentEntity50d490 and gm_GetEntityType50d530.
  No table-entry body-shape/flag probes were run this scope. Preserve known
  ahm/NUL-loop/sitting/pool blockers; do not repeat completed old probes.

- 2026-10-11 (strict operand proof upstream and complete entity-class extents):
  Rebrew8e74ba3a adds smart_reloc_compare(..., strict=True) for source/data
  proofs. Known mapped DIR32 must satisfy VA+addend even when the actual
  address is absent from the catalog. Unbound, unsupported, out-of-extent
  and symbol-free claims fail through invalid_relocs; implicit zero masking
  is disabled. Explicit IAT policy remains. Ordinary source agreement keeps
  its documented tolerant contract; do not label it a fully bound proof.
  The existing strict-proof feature request in upstream IDEAS is implemented
  in the API.25 new cases cover wrong bases/bounds, compiler-local tables,
  REL32 context, explicit IATs and invalid masks.137 focused tests and the
  full11,607 passed/51 skipped/112 warnings are green. A test-only dictionary
  typing annotation caught by the first commit hook was corrected; all25
  cases were rechecked and final hooks (including full Mypy) pass. Actual main
  fast-forwarded; unrelated uv.lock patch preserved exactly; no push.
  Existing shared gm_EntityClassCheck TL506e20/GOLD503f50 now has canonical
  extent70, not80:34 code bytes,2 internal alignment,8 jump-table bytes and26
  case-map bytes, followed by10 external NOPs. All26 cases/default and140
  complete native bytes are independently proved with8 actual COFF-local
  DIR32 bindings and8 wrong+4 controls, using the new strict API. Stock
  LIBCMT misses both. Public client tests record70/70 RELOC. No source/header,
  data, config, flags, ownership or raw image change; only2 client function
  rows change via public locked writers. SERVER remains251 game EXACT and
  its unchanged raw image retains the completed316/316 compiled EXACT proof,
  including65 libraries and251 correct map placements. Same16,580 raw byte
  differences, .text+16/.reloc-300,100 matching imports and4 data-span DRIFTs.
  GOLDTL is3,573/4,905(72.8%):282 EXACT/3,291 RELOC,85 size mismatches,
  12 near matches,3 stubs;1,232 no source; accounted text44.4%, globals251
  unchecked. GOLD2,062/4,598(44.8%):119 EXACT/1,943 RELOC,431 size mismatches,
  22 near matches,7 stubs. Client coverage refreshed; lint0 errors,0/2/40 warnings.
  Current receipt: .scratch/goal20/entity-class-extent/scope-final.json.
  All jobs terminal. Full three-image/shared-tree goal remains ACTIVE; no game
  commit or push. Next unblocked TL todo: gm_CheckStatLevel5074e0; preserve
  known ahm/NUL-loop/sitting/pool blockers and do not repeat exhausted probes.
  Sound ownership, ICF/layout/data, original names/types and full client links
  remain open; source agreement counts are not complete-image verification.

- 2026-10-11 (shared object resource cleanup, verified):
  SERVER10016670, TL502ec0 and GOLD500080 now share the inferred
  gm_ClearObjektResources in the existing game/spiel.c. SERVER retains its
  one-byte empty body under configured REBREW_SERVER; clients reuse their
  existing54-byte resource cleanup, not the SERVER empty helper. The old
  GOLDTL.fcn_00502ec0.c clone is retired. Recursive bodies at SERVER10016710,
  TL502f80 and GOLD500140 are66 bytes; both client extents80→66 exclude14
  alignment NOPs. Complete307 native bytes and10 typed operands were proved
  with actual resolution and negative controls; no new storage or optimization flags.
  Canonical spiel.h declarations/callers are updated. Preserve the early
  recursive forward declaration in spiel.c and include the expanded header
  after gm_Open. Remove the redundant gm_ObjectsAvailble query initialization:
  this restores native861-byte gm_Open and714-byte gm_ObjectsAvailble while
  every other compiled body/typed operand stays unchanged in all3 contexts.
  All C source line counts and original __LINE__ diagnostics are preserved.
  Verification covers279 unique affected entries: SERVER82/82, TL100/112,
  GOLD70/85, with no existing match lost and only prior client mismatches.
  This includes53 additional unchanged sources using the expanded header.
  Full SERVER verification and public raw-link promotion record316/316 EXACT,
  including65 compiled libraries;251/251 map placements agree. Fresh raw SHA
  returnsa96692d9...535643c, all100 imports agree,16,580 raw differences and
  the same4 layout-span data DRIFTs remain (648/652 agree). Data store unchanged.
  GOLDTL is3,572/4,905(72.8%):282 EXACT/3,290 RELOC,86 size mismatches,
  12 near matches,3 stubs;1,232 without source. GOLD2,061/4,598(44.8%).
  All3 coverage documents refreshed; lint errors0 and warnings0/2/40.
  Rebrew CMake incorrectly omitted configured target defines: upstreamb9a8dfe0
  fixes annotated and listed support sources, with70 focused and11,582 full
  passes/51 skips plus green hooks; actual main fast-forwarded, no push.
  Completed receipt: .scratch/goal20/recursive-object-list/scope-final.json.
  Helper name/original domain types remain unproven; whole-image goal ACTIVE.
  Follow-up entity-class extents and the upstream strict-proof API are now
  complete; see the newer checkpoint above and entity-class-extent/scope-final.json.
  No game commit/push; do not repeat completed compiler/source-order probes.

- 2026-10-11 (shared ahm_CheckFlag owner and client extent correction):
  TL4ec850 and newly bound GOLD4eaad0 now share the unchanged existing
  DieGildeAddOn/game/alchemistry_logic.c definition with SERVER1000bda0.
  The misleading TL ahm_ResetEntityState.c clone is retired after complete
  clone/owner equality in both actual client compiler contexts:70-byte body
  and one identical DIR32 operand. Genuine reset helpers remain separate.
  Both complete native client CFGs are70 bytes plus10 alignment NOPs; canonical
  g_entity_type_table operands agree independently. Existing data rows remain
  declarations/aliases, with no new allocations or owner assertions.
  Both clients retain11 native scheduling differences and are NEAR_MATCHING,
  not byte matches. Existing C-shape/scheduler probes are exhausted and must
  not be repeated. Blockers record the pop-ESI/xor-EAX tail discrepancy.
  Actual caller verification preserves every existing match: TL14/15 pass,
  GOLD10/13 pass (helper and two previously unmatched GOLD callers fail),
  SERVER3/3. The completed SERVER object measurements were recovered rather
  than repeated after correcting an overly strong scratch assertion.
  Fresh public raw-link verification restores316/316 compiled EXACT including
  65/65 compiled libraries, with251/251 correct map placements and no missing
  or misplaced functions. Raw SHA remainsa96692d9...535643c; prior16,580 raw
  differences and four layout-span data DRIFTs remain open.
  GOLDTL stays3,571/4,905(72.8%):282 EXACT/3,289 RELOC,87 size mismatches,
  12 near matches and3 stubs;1,232 functions lack source. Accounted text44.4%,
  tracked globals251 unchecked. GOLD stays2,060/4,598(44.8%), covered2,522.
  Both client coverage documents refreshed. Lint errors0, warnings0/2/40.
  All other sources, headers, flags, data and config are pinned unchanged.
  Inferred helper name/original parameter domain types remain unproven.
  No new upstream defect; Rebrew remainsaf430142 with its completed full gate.
  Scope proof: .scratch/goal20/ahm-flag-ownership/scope-final.json.
  All jobs terminal. Whole three-image/shared-tree goal remains ACTIVE; no
  game commit or push. Next unblocked TL todo: gm_FreeObjectListRecursive
  at502f80 in spiel.c; also preserve the open sound, ICF/layout/data and
  complete-client-link work. Do not redo completed probes.

- 2026-10-11 (durable TODO error repair and shared table-search restoration):
  Rebrew todo omitted GOLD44eeb0's managed COMPILE_ERROR when its disposable
  cache entry was absent. Upstream af430142 now classifies compile/extract
  errors using the shared effective-status rule. Six regressions cover durable
  errors, newer cached EXACT and PROVEN precedence. Focused121 tests, Ruff,
  Mypy, hooks and full11,579 passed/51 skipped/113 warnings are green.
  The real-project fixed preview reports the formerly hidden error. Actual
  Rebrew main fast-forwarded; no push, unrelated uv.lock changes preserved.
  GOLD44eeb0 was a malformed placeholder with0x... and wrong used arguments.
  Exact raw-byte search identifies the existing TL44d7b0 EXACT donor. Both
  complete native CFGs are38 bytes plus10 alignment NOPs, with no calls,
  relocated operands or global storage. Broad structural search was ambiguous;
  explicit --source-va44d7b0 selects the independently proved donor safely.
  Public rename and verified shared import now bind both identities to
  src/FindTableEntryIndex.c. The existing body is reused unchanged except its
  inferred function name and removal of the inline identity marker. Both old
  per-target files retire through public tools; no new placeholder/storage.
  Independent complete object checks prove all76 native bytes; targeted TL
  test and GOLD import record EXACT. Name/unit and unused original parameters
  remain unproven. The two used arguments are value and passed-in table:
  12-byte rows,64-row limit,0x28 terminator,0x27 missing result. No array owner
  or source-wide enum/domain type is invented.
  GOLD gains one EXACT:119 EXACT/1,941 RELOC =2,060/4,598(44.8%). Game-source
  compile errors are now zero, and fresh compile-error TODO is empty. Library
  header5e3d3d retains its separate error/provider gap outside game counts.
  GOLDTL stays282 EXACT/3,289 RELOC =3,571/4,905(72.8%). Coverage documents
  refreshed, lint zero errors with SERVER/TL/GOLD warnings0/2/40 unchanged.
  Every unrelated source/header/flag/config, all SERVER rows and raw image,
  and all data/source ownership stores are pinned unchanged. No SERVER link
  rerun was needed: raw SHA remainsa96692d9...535643c, with prior16,580 raw
  differences and four layout-span data DRIFTs still open. No client link claim.
  Scope proof: .scratch/goal20/table-search-repair/scope-final.json.
  All jobs terminal; full original three-image/shared-source goal remains
  ACTIVE and no game commit is allowed. Next: current highest-ROI TL todo,
  avoiding completed matching/path probes; the sound voice-start source,
  separate GOLD pan matrix ABI/binding, SERVER ICF/layout/data and complete
  client links remain unfinished. Do not redo completed sound, random,
  prototype/context, table-search or compiler-path validation.

- 2026-10-11 (client sound identity, callback and prototype repair):
  The false TL40ce80/Gold40bf60 cm_ChkSetGebBesitzer identity is repaired:
  both clients share src/PlayEntitySound.c, an inferred animation-task sound
  callback. It calls the actual four-argument positional sound helper
  fcn_004193f0 (TL4193f0/Gold417e30), with one canonical client_sound.h
  prototype consumed by both source callers and the existing definition.
  The genuine SERVER command validator, dispatch entries and three-argument
  ahm_AllocateEntitySlot remain intact. The false copied server decompilation
  comment and duplicate extern are removed. No replacement storage introduced.
  The animation caller's exact native diagnostic attests PlayCharacterAniSound;
  TL40cee0/Gold40bfc0 now share src/PlayCharacterAniSound.c. Its old numeric
  callback reference binds PlayEntitySound and consumes the canonical header.
  Existing caller line counts are preserved; original compilation unit names
  remain unproven. Scoped source-definition API rename preserves the unrelated
  SERVER twin; CLI all-module preview would rename it. The acknowledgement gap
  is recorded upstream in cb275d8b:27 docs checks and hooks pass, actual main
  fast-forwarded, no push, unrelated uv.lock changes preserved. No new runtime
  Rebrew change; the prior full runtime suite remains11,573 passed/51 skipped.
  Stock CRT probes miss for all affected bodies. Ten affected compiler contexts
  preserve all body bytes/typed operands. Eight complete native bodies prove
  1,068 bytes and50 relocated operands with wrong+4 controls. Remaining source-
  unbound voice-start calls and numeric data views are explicitly identified;
  proof establishes native operands, not a complete client link or data owner.
  GOLD wrapper and second sound caller extents exclude14 trailing NOPs:
  82 and114 code bytes respectively. Both now RELOC, gaining two GOLD matches.
  Fresh scoped verification passes TL5/5 and GOLD5/5, no existing matches lost.
  GOLDTL stays3,571/4,905(72.8%); GOLD now2,059/4,598(44.7%).
  Lint remains zero errors, warnings SERVER/TL/GOLD0/2/40; coverage refreshed.
  Fresh SERVER raw verification remains316/316 EXACT,65/65 compiled libraries,
  251/251 correct map placements. Raw SHA unchangeda96692d9...535643c;
  the prior16,580 raw differences and four SERVER data DRIFTs remain open.
  Scope audit: .scratch/goal20/sound-wrapper/scope-final.json; all jobs terminal.
  Next: voice-start native TL423670/Gold427110 has discovery extent384 but no
  source binding. GOLD's pan helper4179f0 remains a separate managed source:
  TL calls a stdcall matrix helper(dst,src), GOLD a cdecl helper(src,dst),
  so do not blindly merge the281/283-byte variants or assert a shared alias.
  Voice-creator declarations/numeric sound data ownership remain unreconciled.
  GOLD's existing game compile error is44eeb0; library header5e3d3d also carries
  a compile-error row outside the game-source status count. Check current todo
  before further reversing. Full original three-image/shared-source goal stays
  ACTIVE; no game commit allowed. Do not redo completed prototype/context,
  random-unit, native extent or compiler-path proofs.

- 2026-10-11 (canonical alchemy prototype and upstream text-verifier repairs):
  GOLDTL remains 3,571/4,905 matched (72.8%): 282 EXACT and 3,289 RELOC;
  102 covered functions unmatched (88 SIZE_MISMATCH, 11 NEAR_MATCHING,
  3 STUB), 1,232 without source, accounted text 44.4%, 251 globals unchecked.
  The previously open command.c void declaration of ahm_SlotClearMatch is
  repaired: command.c and its existing alchemistry_logic.c definition consume
  one reconstructed alchemistry_logic.h int(char*,char*,char*) declaration.
  Only these includes and the new header change; all bodies/line counts remain.
  Twelve complete compiler contexts preserve 642 body/typed-operand measurements
  and full COFF except timestamps/compiler-local label names. Fresh scoped
  verification passes SERVER84/84, TL4/18, Gold3/6; all17 client failures were
  already unmatched, with no lost stored matches. SERVER rebuild preserves
  raw SHA a96692d9075b3e4e43228300df265d709146774097dcf771f9c4ee39f535643c.
  Two verifier bugs fixed upstream and integrated into actual Rebrew main:
  cd19f304 uses the available MSVC map for text placement and linked EXACT;
  c5922cd4 excludes DATA/global rows from expected function placement.
  Full suites pass 11,569/51 skipped and 11,573/51 skipped respectively;
  focused checks, Mypy and commit hooks pass. No push; unrelated uv.lock
  changes preserved. Fresh final SERVER verification:316/316 EXACT,
  65/65 compiled libraries,251/251 correct map placements,zero missing/misplaced.
  Data remains648/652 with the same four layout-span DRIFTs. Raw binary still
  differs from reference by16,580 bytes; no whole-image identity is claimed.
  Lint remains zero errors with SERVER/TL/Gold warnings0/2/40. TL coverage
  refreshed. Scope audit passes; all jobs terminal, no game commit allowed.
  Evidence: .scratch/goal20/ahm-prototype-contexts/scope-final.json.
  Next: resolve the false client sound binding at TL40ce80/Gold40bf60.
  The current cm_ChkSetGebBesitzer wrapper calls native sound helper
  TL4193f0/Gold417e30 with four arguments, but labels it ahm_AllocateEntitySlot,
  whose genuine SERVER alchemy definition takes three. No sound edits made;
  original wrapper name/unit and Gold extent remain unproven. Check libraries,
  complete both native CFGs/operands and reconcile identities before editing;
  do not globally rename or alter the genuine SERVER allocator to fit this caller.
  Evidence: ahm-prototype-contexts/next-sound-binding-audit.json.
  Full three-image/shared-source goal remains ACTIVE. Allocator131-byte
  iterator, SERVER ICF/layout and full client links remain open; do not redo
  completed random consolidation, extent proofs or compiler-path controls.

- 2026-10-11 (alchemy helper extent repair and allocator path controls):
  GOLDTL now records3,571/4,905 matches(72.8%):282 EXACT and3,289 RELOC.
  Covered3,673; unmatched102(88 SIZE_MISMATCH,11 NEAR_MATCHING,3 STUB);
  no-source1,232; accounted text44.4%; all251 recorded globals unchecked.
  TL4ee9c0 and Gold4ecbc0 ahm_SlotClearMatch had managed SIZE112 even though
  complete native CFG ends at110 with two trailing alignment NOPs. Existing
  unchanged shared alchemistry_logic.c emits110 in each client. Independent
  reachable-byte coverage, both typed call operands per client, native numeric
  helper identities and wrong-target+4 controls prove all220 code bytes.
  Stock LIBCMT misses for both entries. Public locked SIZE/note writers and
  targeted CLI tests now record both as RELOC110. Only these two client rows
  changed; the source unit, flags, identity owners, configuration, data/source
  stores and every SERVER function row are preserved. No padding or asm added.
  Both gm_ff_Objekt and gm_RemoveObjectByType canonical client labels remain
  catalog-unbound: native numeric identities prove the exact call destinations,
  not a completed client link. command.c's void return declaration also still
  disagrees with this int helper and needs its affected compiler contexts checked.
  Fresh lint TL0errors/2warnings and Gold0/40; TL coverage document refreshed.
  Upstream extent/binding proposal augmented with this evidence in9d7905cd;
  27 docs checks and commit hooks pass; actual main fast-forwarded, no push.
  Unrelated upstream uv.lock diff remains byte-identical.
  New compiler-path controls use unchanged complete allocator units: basename,
  attested Develop/Units/m_alloc/m_alloc.c relative path and attested #line path
  across three targets. Nine successful compiles preserve126 function-body and
  typed-operand measurements; preprocessed tokens agree after excluding #line.
  Iterator stays136 in both processor-pack clients and138 in non-PP SERVER,
  versus native client131. Tested paths do not close the mismatch. The wrapper
  rejects backslash source argv; an actual D-drive compiler input was not tested.
  Completed paths: pool-filename-context-complete/{receipt,preserved-inputs}.json.
  SERVER raw hash remainsa96692d9...535643c; prior16,580 differing bytes,
  .reloc short300 and four layout-span data DRIFTs stay open. No link rerun was
  needed for these metadata-only corrections. All jobs are terminal.
  Extent proof/scope: .scratch/goal20/ahm-slot-clear-extent/{native-proof,scope-final}.json.
  Next: source-backed extent/operand audit of remaining shared spiel helpers;
  canonical callee/return declarations, allocator tracked-free/free-all variants,
  SERVER ICF/layout and full client links still need completion. Do not repeat
  finished random consolidation or allocator filename controls. Full original
  three-image/shared-tree goal remains ACTIVE; no game commit is allowed.

- 2026-10-11 (random unit ownership repair and caller reconciliation):
  GOLDTL now records 3,570/4,905 matches (72.7%): 282 EXACT and 3,288 RELOC;
  103 covered functions remain unmatched and 1,232 lack source. Accounted
  text remains44.4%; all251 recorded client globals remain unchecked.
  The existing, unchanged game/zufall.c now owns seven TL and six Gold
  identities. Complete native CFG/extents, all typed operands and wrong+4
  controls prove153/131 client bytes; the five SERVER bodies contribute128
  unchanged bytes. TL42e430 gm_RandomRange is22 bytes plus10 NOPs and was
  omitted from discovery; its verified identity increases both the total
  and covered count by one. The stale TL gm_RandomMod spiel.c binding and
  Gold's stale numeric source binding are repaired through locked writers.
  Eight superseded single-body source files are retired via verified public
  imports, with all230 native bytes in their11 former contexts checked.
  Public reference bindings update234 TL-modulo, four Gold-modulo and three
  seed-alias files, preserving declarations and line counts. The508-profile
  audit passes:420 recompiles,77 unchanged-input reuses,11 retired contexts,
  and2,542 surviving body/typed-operand measurements preserved. Fresh native
  verification passes SERVER5/5, TL255/257 and Gold166/202; all38 failures
  were already unmatched and no stored match is lost. The13 shared client
  helpers all freshly earn RELOC. One definition per helper across the tree.
  Headers, flags, toolchains and data/source stores are preserved. Added
  stock WINMM import libraries to both provisional client configurations,
  supported by the native timeGetTime IAT slots TL662318/Gold5eb284.
  SERVER rebuild succeeds and retains raw SHAa96692d9...535643c exactly;
  therefore the prior open raw/layout problem and four data DRIFTs remain.
  Lint remains zero errors, warnings SERVER/TL/Gold0/2/40. GOLDTL's coverage
  document is refreshed. All random checkpoint jobs are terminal.
  Native CRT origins remain stock: TL/SERVER LIBCMT, Gold rand LIBC. Gold's
  generic seed setter has ambiguous templates, but writes the exact word
  at62e108 read by its matched rand. Neither client has a proven full linked
  runtime provider. No CRT definition, library patch or storage owner added.
  The missing operand-supported library-identification feature is recorded
  upstream in2e99d68d (27 docs tests and hooks pass, no push); the runtime
  cache fix remains133643df with11,566 full-suite passes and51 skips.
  The unrelated upstream uv.lock diff is preserved exactly.
  Source-scope receipt: .scratch/goal20/random-consolidation/scope-final.json;
  native proofs and provider evidence: random-unit-probe/. This does not
  accept the pool gate or allow a game commit. Next: raw SERVER ICF/layout,
  iterator136/131 and tracked-free/free-all ownership, full client links,
  canonical random declarations/prototype narrowing and inferred naming,
  remaining data/types/owners and the complete three-image shared tree.
  The original goal stays ACTIVE; game changes remain uncommitted.

- 2026-10-11 (pool first/next integration; validation remains open):
  Before the random-unit repair, GOLDTL recorded 3,569/4,904 matches
  (72.7%): 282 EXACT and 3,287 RELOC;
  103 source-backed functions remain unmatched, 1,232 lack source, and all
  251 client globals remain unchecked. Accounted text is 44.4%.
  Client pool-first identities now share m_pool_first in m_alloc.c, with
  complete 39-byte native bodies and the native iterator call proven in
  both clients. The old numeric first unit was retired through public
  verified imports. m_pool_next has honest identities in both clients but
  remains SIZE_MISMATCH (136 compiled versus 131 native). Its bounded failed
  probes are complete; do not repeat them. M_POOL_BLOCK and unit placement
  remain inferred. The focused m_pool.h is included late in allocator/VFS;
  m_alloc.h is restored exactly. Four caller destinations are verified.
  Existing tracked-free definitions correctly block free-all consolidation;
  no collision guard was relaxed. 141 unsupported log placeholders remain.
  The broader m_alloc.h draft was rejected because it changed surrounding
  code. Preserve its archived evidence and recovery snapshots. The 44 COFF
  contexts are saved; the profile audit finds no missing changed-source
  profile witnesses. The reconciled open scope audit passes: 42 live contexts,
  35 reused unchanged inputs, seven recompiles and 1,640 surrounding body/typed
  operand measurements preserved. It explicitly records checkpoint_accepted=false;
  gate acceptance still requires the raw ICF/layout regression to be resolved.
  An upstream Rebrew batch bug reproduced gm_Open as 859 instead of 861
  bytes: nested compiler filenames changed VC6 output despite identical
  preprocessed C, and contaminated the single-file object cache. The upstream
  fix skips nested batches and invalidates old object keys. The corrected
  public verifier passes all 63 SERVER spiel.c functions; the TL/Gold rechecks
  retain their 211-byte promotions and prior unmatched functions. TL's
  gm_RandomMod extraction failure then retained its earlier earned verdict;
  the random-unit repair above now freshly verifies the correct owner.
  Evidence and upstream validation logs are saved.
  The previous SERVER gate ended FAIL: its gm_Open verifier regression is
  now corrected, but its raw image still has 16,580 differing bytes, .text
  141,398 versus 141,382 and .reloc 66,120 versus 66,420. The a_map.obj ICF
  survivor differs. This is not the previous two-header-byte checkpoint.
  No raw-file/library patch, fake relocation, storage/provider or flag change.
  Upstream fix is committed locally as 133643df and fast-forwarded into
  the actual Rebrew checkout; no push. The repaired full suite now passes:
  11,566 passed, 51 skipped, 117 warnings (422.42 seconds). The earlier three
  documentation failures are resolved. The 315 focused compiler/cache/verifier
  tests and commit hooks also pass. The unrelated upstream uv.lock patch is
  preserved exactly.
  GOLDTL's coverage document is refreshed. Final SERVER function/raw-link
  verification ended successfully: 316/316 functions, all recorded EXACT,
  including 65/65 compiled library functions. This does not establish whole-
  file identity or replace a complete gate. No current jobs remain. Receipt:
  pool-first-next-upstream-server-verify.json. Validation logs are preserved
  in pool-first-next-upstream-validation/. Fresh data verification records
  648/652 matches, four honest layout-span DRIFT verdicts, 409 exact placements,
  243 unplaced rows and no displaced rows. The frozen verbose native link
  reproduces the current raw image and counts 5,510 actual DIR32 inputs versus
  5,535 implied by the reference. Independent ICF controls show that a native
  131-byte iterator still occupies a 144-byte padded COMDAT and retains a_map;
  matching that body alone cannot repair the survivor. Next: resolve raw ICF/
  layout before accepting the pool checkpoint or committing game code. The
  random-helper stale source binding is being audited separately.
  The full three-image/shared-tree goal stays ACTIVE; game changes remain
  uncommitted. Evidence lives in .scratch/goal20/pool-first-next-*.

- 2026-10-11 (shared pool helper checkpoint):
  TL41e440/41e490/41e4d0 now use the existing shared m_alloc.c definitions
  m_pool_clear, m_pool_info and m_pool_stats. Removed three unsupported
  entry logs, preserving source line counts. All223 native bytes match
  exactly, with no calls or relocations; all33 surrounding bodies and typed
  operands are preserved across SERVER/TL/Gold. Three numeric source owners
  are retired through verified public imports. No header, caller, allocation
  or Gold counterpart is inferred. These three functions were already EXACT:
  TL remains3568/4904 matched (72.7%),282 EXACT/3286 RELOC, with103 covered
  unmatched and1233 without source;44.4% of text is accounted including
  libraries/padding. All251 recorded client globals remain unchecked.
  The existing TL m_PoolAlloc SIZE_MISMATCH remains unchanged (261/272).
  Lint has0 errors and SERVER/TL/Gold warnings0/2/40. The SERVER gate retains
  316/316 functions,652/652 data comparisons,409 exact placements,100 imports
  and Wine exports. Whole-file identity still fails: only header offsets
  0x260/0x261 differ, .reloc VirtualSize66168 versus66420 (short252);
  all section raw bytes and .text VirtualSize141382 match. Source fidelity
  removes six input relocations; no fake calls, header patch or archive edit.
  The earlier frozen census measured5520 DIR32 inputs versus5535 implied
  by the reference reservation. That census predates these three removals;
  no fresh complete-input census is claimed.143 unsupported log placeholders
  remain. No upstream tool bug was found in this checkpoint.
  Next: wider pool first/free-all declarations and native callees, iterator
  register/loop mismatch (136 compiled versus131 native), discarded original
  translation units, full client links, names/types/owners and relationships.
  The full three-image/shared-tree goal remains ACTIVE; game changes remain
  uncommitted. Evidence: .scratch/goal20/pool-clear-info-stats-scope-final.json,
  pool-clear-info-stats-objects/ and pool-clear-info-stats-raw-server-audit.json.

- 2026-10-11 (identity statistic shared-source checkpoint):
  TL4e73f0/Gold4e58e0 now share srv_FormatStatIdentity in the existing
  client-only server_stats.c, with one canonical server_stats.h prototype.
  Both complete159-byte native bodies, every operand and the37-byte literals
  match; wrong-address controls pass. The class fallback remains table+240,
  despite different neighboring strings in the clients. Names/unit placement
  remain inferred; no SERVER counterpart or storage owner is invented.
  Gold's scalar year view is770ae0, not the rejected770b60 guess. Seven
  existing Gold target/flag groups have no year operand in their bound bodies;
  broad legacy g_7f4c00 users/catalog remain unchanged. Fifteen declaration/
  literal rows bind native operands without new allocations or data verdicts.
  All85 surrounding bodies/typed operands are preserved. All21 affected
  client checks pass (12 TL and9 Gold RELOC), and the unowned single-body
  numeric duplicate is retired through the verified public importer.
  All-target lint retains0 errors and0/2/40 warnings. Server gate still fails
  only whole-file identity:316/316 functions,652/652 data comparisons,
  409 exact placements,100 imports and Wine exports pass. Raw output is
  unchanged: only offsets0x260/0x261 differ, .reloc VirtualSize short180;
  all section raw bytes and every other header byte match. No header patch,
  compensation, archive edit or game commit. Allthree coverage documents
  are refreshed after verification. TL remains3568/4904 matched (72.7%),
  282 EXACT/3286 RELOC,3671 covered/1233 without source,44.4% accounted text;
  251 tracked globals remain unchecked in a linked client. Consolidation
  improves the shared tree, not the already-earned match count.
  The full three-image/shared-tree goal remains ACTIVE. Next: relationship
  formatter and ambiguous lookup identities/callers, the server's remaining
  discarded-TU relocation reservation, full client links, names/types/owners.
  Evidence: .scratch/goal20/stat-identity-scope-final.json,
  stat-identity-final-objects/ and stat-identity-raw-server-audit.json.

- 2026-10-11 (shared office-query recovery): TL4e7b70/4e7bf0/4e7c70
  and Gold4e6030/4e60b0 now use the existing shared server.c definitions:
  srv_GetEntityOfficeSlot121, srv_GetEntityCouncilSlot124 (TL only), and
  amt_GetOfficeAffinity193, all freshly RELOC. Removed three unsupported
  guard log calls and read template rank through its native unsigned-byte
  view at+8; source line counts remain unchanged. Gold affinity's old208-byte
  span included15 alignment NOPs. Seven caller files now use canonical
  aemter.h prototypes; all18 native query call destinations are checked.
  Complete production comparisons prove752 native query bytes and all
  operands, including wrong-binding controls. All89 surrounding bodies and
  typed operands are preserved across20 affected target/flag groups. Fresh
  client checks retain30 RELOC and two existing Gold caller SIZE_MISMATCH.
  Both superseded numeric units are removed only after proving all5 old
  target bodies equal their shared replacements, every former claim moved,
  no storage/helper/provenance owner remains and no caller still references
  them; kept backups record the explicit source edit. The automatic importer
  retains its conservative single-body guard. Upstream documentation7ff37e19
  records the missing guarded multi-body retirement workflow; all commit hooks
  pass, actual local main fast-forwards, unrelated uv.lock/old worktrees remain,
  no push and no tool-code change. Four new declaration-only data views bind
  native role/float tables; all960/196 initializer bytes equal the existing
  server tables. Existing slot labels/types and unproven alternate addresses
  remain. No client allocation, storage owner or linked data verdict is invented.
  All-target lint remains0 errors with0/2/40 warnings. Server gate still fails:
  2 raw differences, .text+0/.reloc-180.
  All316/316 functions and652/652 data comparisons pass,409 placements are exact,
  and the reference LIBCMT:a_cmp _strncnt survivor is restored. Independent
  whole-file audit locates the only two differences at file offsets0x260/0x261:
  .reloc VirtualSize0x102c0 versus0x10374. All section raw contents and all other
  header bytes match; no header patch is used. This supersedes the previous
  16579-difference checkpoint and its four data drifts.
  The full three-image/shared-tree goal remains ACTIVE and game changes uncommitted.
  TL remains3568/4904 matched with44.4% accounted text;
  244 tracked globals remain unchecked in a linked client. Next are
  first/relationship statistic bodies (four stock-LIBCMT misses confirmed),
  ambiguous lookup identities/callers, original TU/layout, names/types/storage
  and full client links. Receipts: .scratch/goal20/office-query-scope-final.json.
  New first-formatter evidence establishes the fallback at class-table base+240
  in both clients, despite different neighboring string bytes. Preserve that
  table-relative view; the complete backing extent/original expression remain
  unproven. Do not substitute one inline fallback string or allocate a label.

- 2026-10-11 (delimiter source recovery and native data catalog): TL4e73c0
  and4e77e0 now use the existing shared srv_FormatStatDumpBegin/End bodies,
  bothRELOC34. Four unsupported log calls are removed with source line counts
  preserved; verified shared imports retire both final numeric duplicates.
  Complete54/52-byte .data compiler literals and the calendar's first-four-byte
  scalar view are recorded without creating storage. The primary calendar
  analysis label/type remain; its complete backing extent and owner are unknown.
  No Gold delimiter identity is established or invented. Independent production
  comparisons validate all68 native bytes, every operand and both full literals;
  full COFF checks preserve79 surrounding bodies/typed operands, and all14
  affected client checks pass. Upstream080277bb fixes the shared relocation
  catalog ignoring exact native data spellings, with four failing-before
  regressions,97 focused passes, all18 hooks and the frozen full suite
  (11567passed/50skipped). Local integration preserves unrelated work.
  The full server gate is terminal:316/316 functions,648/652 data,409 exact
  placements,100 imports and Wine exports pass; raw identity still fails with
  16579 differing bytes, .text+16 and .reloc-108 (5526 versus5535 reserved
  DIR32 records). No padding, guessed logs or library patch is introduced.
  TL remains3568/4904 object-matched; its242 tracked globals remain unchecked
  in a linked client. The next three office-query guards have no native calls:
  TL bodies121/124/193 and Gold counterparts121/193 are independently bounded;
  no complete masked Gold council counterpart is established. Their source
  recovery, the remaining statistic bodies, original source arrangement,
  names/types/ownership and full client images remain open. The complete
  three-target/shared-tree goal stays active; game changes remain uncommitted.
  Receipts and continuation state: `.scratch/HANDOFF.md`.

- 2026-10-11 (office statistic recovery): the fourth formatter now shares
  `srv_FormatStatAemter` in server_stats.c at TL4e75a0/GOLD4e5a90. Independent
  comparisons prove all87 native bytes, literal bytes and typed operands in
  both clients. Verified import retires the final numeric duplicate; both
  canonical callers pass. A reconstructed aemter.h supplies the string-pointer
  declaration to the formatter and existing UI reader, without allocating
  an unknown-sized table. TL68d934 is corrected to a complete13-byte .data
  compiler literal. Full COFF checks preserve85 existing function bodies
  and operands across the affected builds; fresh affected client checks pass.
  An initial server.c placement failed the real link because the role-label
  table has no verified server provider. It is now one shared client-only
  unit selected by client identities, with no invented storage or target guard.
  The revised server gate is terminal:316/316 functions,648/652 data,
  all100 imports and Wine exports pass; whole-file identity still fails with
  16,579 differences, .text+16 and .reloc-36. Scope checks preserve unrelated
  work and all other function identities/statuses. The next shared lookup is proved but its
  client name collides with a different32-record lookup; their native callers
  must be reconciled before binding. The full three-image/shared-tree goal
  remains active, with source/link/data/type/name work unfinished. All three
  coverage documents are regenerated after terminal measurements. TL's
  begin/end bodies are independently bounded at34 bytes and have no log
  calls; Gold contains neither matching complete code patterns nor their
  delimiter literals. The four source placeholder calls remain next work.

- 2026-10-11 (attributes/skills source recovery, validation in progress): the
  existing shared attributes and skills bodies now serve both clients as
  RELOC179/68 after removing two unsupported placeholder log calls. Verified
  imports retire the two numeric source duplicates; the canonical header and
  explicit pointer casts preserve the caller's instructions. Complete COFF
  checks preserve 77 surrounding bodies and typed operands, and independent
  native checks compare every formatter/literal byte. TL68d924 is now a
  complete 16-byte compiler-literal inventory row, not another allocation.
  The current raw link still differs in 16,579 bytes: .text141398/141382,
  .reloc66384/66420 and the wrong CRT ICF survivor. The affected client checks
  pass; corrected all-target lint retains only0/2/40 assembly warnings. An
  unsupported note tag exposed a public-writer validation gap; the game notes
  are corrected and the upstream common-stamper repair has five failing-before
  regressions, 513 focused passes and all 18 hooks. Its frozen full suite
  passes11,563 tests with50 skips; the four-file fix is committed and integrated
  into actual upstream main as `891169ffcaefb34cc74231c52eaa8e4374316d79`, with
  unrelated dirty work and the older worktrees preserved. Fresh verification
  against that revision is terminal: client checks pass and the server gate
  still fails with the same 16,579 differing bytes. Source/link fidelity, client images/data and
  the complete three-target goal remain unfinished; the game changes are
  uncommitted. Current handles and receipts: `.scratch/HANDOFF.md`.

- 2026-10-11 (treasury recovery and upstream definition discovery): the shared
  treasury formatter now matches all 90 bytes in both clients; its sole
  shared caller also passes fresh verification. GOLD's existing accumulation
  helper is imported as RELOC74. Rebrew's definition finder omitted functions
  after inline assembly and shifted multiline attribute locations; fixed
  upstream as `b096459b7e115bb544567464b089944c094c7e34`, with three failing
  regressions, 708 focused tests, all 18 hooks and the frozen full suite
  (11,558 passed / 50 skipped). Actual upstream main is fast-forwarded, with
  unrelated work preserved. The full COFF audit preserves 106 existing
  measurements. Current server gate FAILS: adding faithful discarded code
  flips LINK's identical CRT `_strncnt` survivor, causing a 16-byte .text
  increase, 12-byte .reloc increase and four data drifts. Treasury changes
  remain uncommitted while the original source and link layout are recovered;
  do not weaken the gate or restore fabricated logs to hide this difference.
  GoldTL now has 3,568 matched game functions (282 EXACT / 3,286 RELOC), with
  all 240 tracked globals still unchecked. The complete three-target goal
  stays active. Receipts and current continuation work: `.scratch/HANDOFF.md`.

Current working state lives in `.scratch/HANDOFF.md` (gitignored). Update both files each round.

- 2026-10-11 (shared character pairs and metadata-only SIZE policy):
  Consolidated the attested ch_MoveCharacter2Universe (TL403bc0/GOLD4033c0)
  and TakeObjectScript (TL40d410/GOLD40c4f0) into game/character.c, retiring four
  duplicate client files. This compilation unit and the partial struct/field names
  are inferred; function names are directly attested. Canonical ch_motion.h supplies
  prototypes and six game declaration views; two legacy sites now include it.
  Public writers migrate the scoped identities and rehome eight existing data views;
  four newly recorded TL aliases add no storage, data verdict or allocation claim.
  Complete 1,181 native bytes agree with 52 actual typed operands and 52 isolated
  wrong-target controls. Ten consumer bodies and all 14 final COFF bodies are
  preserved across eight final builds (ten baselines). All 141,320 strict C89 32-bit
  sanitizer cases pass under modeled helper/valid-input contracts. MSVC6 measures
  the partial C-view sizes; no complete native allocation or helper provider inferred.
  All 12 existing matches freshly verify against actual upstream main; no match lost.
  The existing unmatched GOLD character query remains unchanged. TL3,583/4,905 and
  GOLD2,079/4,598 retained; TL281/GOLD241 unchecked declaration views. Root backlog
  remains 3,836 C files. Lint zero errors with unchanged SERVER0/TL2/GOLD40 warnings;
  all three coverage documents refreshed. All unrelated C/header/config/layout,
  reference binaries, managed rows and the raw server image remain pinned unchanged.
  User requested metadata-only sizes. Retired obsolete upstream W007's file-level
  struct SIZE-comment requirement as actual main 34e0e05d0978c29f67507fa710ff03d32f8db6a0.
  Two regressions failed first; 284 focused tests, all 18 hooks and the frozen full
  suite (11,620 passed / 51 skipped / zero failed) pass. Function addresses/sizes
  remain in managed TOML; character.c has no inline SIZE comments. Goal wording
  now says one managed identity per target. Inherited upstream uv.lock/IDEAS work
  preserved. Game HEAD383252b5 unchanged; no game commit, push or live sync.
  Receipt: .scratch/goal20/character-shared-pairs/scope-final.json. All jobs terminal.
  Do not repeat native/baseline/sanitizer/consumer proofs. The abandoned block-SIZE
  lint fix/full-suite run and annotation-final.json are superseded scratch probes;
  final.json, verification-current.json and upstream-result.json are authoritative.
  Native callers/registering functions remain unreversed: scene call is in sibling
  TL407390/GOLD4067f0 after a 96-byte selector, not in its matched body; TakeObjectScript
  registration lives at TL40e1a0/GOLD40d270. TL402aa0 is a verified one-byte RET plus
  15 NOPs, filtered by discovery's documented eight-byte minimum; not an upstream bug.
  Next: continue evidence-based character grouping/shared helpers and canonical
  naming, or known-binding import hardening already recorded upstream. Retired MSX
  updater/type/flag probes stay retired. Full three-target/source/ownership goal
  remains unfinished; raw client linking and complete data verification are open.

- 2026-10-11 (shared slot-helper consolidation): TL50dac0 and GOLD50a640 now use the existing spiel.c `gm_WalkEntityChain` body, RELOC 124 in both, alongside SERVER10019be0. The public importer preserves the first remaining owner and retires only the final unowned duplicate; 52 caller files use the canonical unsigned-short prototype. Complete COFF checks preserve all 82 caller target/flag groups, 108 function bodies and both shared client units. Fresh caller verification retains 101 RELOC and seven existing SIZE_MISMATCH verdicts. A prototype-only spiel.h and the original bare `int` spelling preserve MSVC6 context; the broader entity.h and added `extern` forms produced real regressions and were rejected. Upstream 2b46dab0 fixes shared-file retirement; 3214649a fixes parent-relative includes for source-in-workdir probes. Both pass focused regressions, all 18 hooks and their frozen full suites (11,553 and 11,555 passes, each with 50 skips). The final server gate passes 316/316 functions, 652/652 data comparisons, 100 imports, Wine exports and whole raw 286,720-byte DLL identity. No earned match is lost; GoldTL remains 3,567/4,904 matched, with 44.4% accounted text and 240 unchecked globals. Statistic formatter recovery, client linking/data, original types/names and placeholder removal remain open; the full three-target unified-source goal stays active.

- 2026-10-11 (shared filtered iterator and upstream import evidence repair): the existing spiel.c iterator now serves TL503e80 and GOLD501030 as RELOC341, alongside SERVER10016f80. Bounded native traversal establishes the complete341-byte client bodies and11 following NOPs; all20 operand sites resolve exactly, with wrong-binding controls. Upstream0fbab4fb fixes selected-function flags, verified identity-name replacement, successful retry inputs, stale flag overrides and failed same-file retarget preservation. Five initial and two further regressions failed first;370 focused tests, all18 hooks and the final full suite(11,536pass/50skip/0fail) pass. Verified replay corrects exactly the two client rows; sources, headers, layout, every other client row and unrelated work remain unchanged. The fresh actual-main gate passes316/316 functions,652/652 data comparisons,100 imports,Wine exports and whole raw286720-byte DLL identity; all316 SERVER comparison fingerprints are current. All-target lint retains0/2/40warnings, and all3 coverage documents are regenerated. Plain C scratch proofs also establish the90-byte statistic formatter and124-byte shared slot helper in both clients; production consolidation/recovery remains next, with52 caller files,82 target/flag groups and108 function measurements scoped. Client images/data, original names/types and the complete all-three-target unified-source goal remain open.

- 2026-10-11 (shared plant lookup and upstream linker rename repair): independently proved the complete69-byte lookup and11 following layout NOPs in all three binaries, plus the full280-byte initialized table. Renamed the shared helper/global to inferred plt_FindPlantInfo/plt_PlantInfo and consolidated its prototype without changing whole COFF section payloads or resolved relocation graphs across12 target/flag groups and98 function measurements. Locked writers corrected only the two client lookup extents; fresh results are RELOC69. Client table rows describe the existing single source owner; no linked client data verdict is claimed. Upstream main662d7132 repairs target-scoped linker references through the shared rename plan and rollback;196 focused tests, all18 hooks and the corrected full suite(11,526pass/50skip/0fail) pass. The first full run's sole failure was a duplicate changelog group, corrected with source/tests/limits unchanged. CLI reference binding repairs the stale server /INCLUDE anchor without C/store edits. Fresh actual-main gate again passes316/316,652/652 data comparisons,100 imports,Wine exports and whole rawDLL identity. Seven affected client-file verifications refresh24 rows and retain existing command/padded-extent mismatches; no earned match is lost. All-target lint preserves0/2/40warnings, coverage is regenerated, and the preservation guard passes. Full client images, domain types/fields, source reconstruction and the all-three-target goal remain open; next native evidence disproves TL4e7600's srv_Init(void) binding.

- 2026-10-10 (Buergerrecht starter recovery): inferred PrepareBuergerrecht now provides one ordinary C89 body for TL499a50 and GOLD49a010, both RELOC125 with the default compiler flags. Independent native registration proves the action in each client; full operand resolution reproduces every instruction byte and both float payloads, with wrong-binding/literal controls. A32-bit C89 check passes640 boundary/branch cases and rejects three semantic mutations. Explicit reference binding and a corrected four-argument prototype preserve the shared initializer's9106-byte RELOC body in both clients. Original starter name/source unit/full domain types remain unresolved; the unplaced source filename is provisional. This is source/body progress, not whole-client linking or completion of the three-image/unified-tree goal.

- 2026-10-10 (requested-VA selection and false identity cleanup): upstream main 9a2f9bb0 fixes the shared selector used by probe, gap trace and qualifier sweep. A positional VA now selects its own annotation; a missing explicit VA errors before compilation or editing. Seven regressions failed first, 152 focused tests, all 18 hooks and the full suite (11,516 passed / 50 skipped / zero failed) pass. The actual-main server gate again passes 316/316 and whole-file raw DLL identity. Removed only the disproven TL499a50 binding to ahm_ProcessEntityChain through the locked writer, retaining native inventory and every other client fact. Correct chain bodies TL4c4d30/GOLD4c43c0/SERVER1000ca00 measure 130/130. Native registration proves the removed VA is the Buergerrecht starter, not the chain dispatcher; its source recovery remains open. Current TL totals are 3,564 matched of 4,904, with 1,234 without source. No earned match was removed. Full client images/data and unified-source completion remain open.

- 2026-10-10 (CharacterClearSitting semantics): TL406560 now retains its seat pointer across the void402aa0 helper and passes model/name to435500 in the original order. A 32-bit C self-check passes all16 branch combinations and rejects reversed-argument/wrong-seat-offset controls. This corrects behavior, not bytes: MSVC6 still emits98 bytes versus the complete native87. Bounded empty-helper/TU-order/inlining probes do not recover the original register-preservation context, and no asm, helper definition or alternate compiler flag was added. The original extent remains87 and SIZE_MISMATCH is retained; no GOLD import is eligible from this donor. Gate and preservation receipts are recorded in the current handoff.

- 2026-10-10 (padding repair and shared animation checkpoint): upstream main 2613fa04 excludes only proven trailing x86 NOP/int3 padding from import/BinSync signatures; score/gap and byte verification stay unchanged. Four regressions failed first; 292 focused checks, Ruff/Mypy, all 18 hooks and the normal full suite (11,507 passed / 50 skipped / zero failed) pass. The earlier disabled-bytecache startup failure remains recorded, with unchanged source/tests/limits. The project's editable CLI now uses actual upstream main. Reviewed shared imports earn GOLD callback248, builder75 and caller152 RELOC; the callback has one inferred per-target offset selector (+0x84 GOLD / +0x390 TL), whose omission reproduces two real differences. All seven TL/GOLD animation measurements pass. Actual-main server gate passes 316/316 functions, 652/652 data comparisons, 100 imports, Wine exports and whole-file raw DLL identity. The pre-commit guard verifies 316 current SERVER fingerprints (compiler hash 71cafe38a4d312f4625aba2c62717deca730209f95768e0ccd41d3fdce88ee06) and preserves unrelated source/data/client/worktree facts. Client data, raw client linking, remaining types/names and unified-tree reconstruction remain open; the full three-target goal is active. Current receipts and next steps are in `.scratch/HANDOFF.md`.

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
- 2026-10-09 (inline-helper evidence): implemented and merged source-definition assembly provenance upstream as `734babb2c90e19f79896e14966c194a50bf816c1`; actual Rebrew main is `0b7793f873c4fc105bef44e1d0066eece383333d` after its lock-file documentation follow-up. The new managed `rebrew-source.toml` binds file, C symbol, target and current definition hash without inventing a VA or byte verdict. W020 accepts only that definition's reviewed evidence; W031 surfaces invalid/stale records and E023 remains enforced. Also fixed root source trees adopting metadata outside their project. Final upstream suite: 11,463 passed / 50 skipped / 0 failed; all 18 hooks pass. Reviewed three original GOLDTL fill/copy sites, excluded the stock CRT archives and freshly measured their callers as RELOC (297/297, 528/528, 378/378); source and stored client verdicts are unchanged. All-target lint has zero errors, with SERVER 0 / GOLDTL 3 / GOLD 40 warnings. The actual server gate passes: 316/316 functions, 652/652 data symbols (409 placed), 100 imports, Wine exports and raw DLL whole-file identity. All 316 SERVER measurements use compiler identity `cf2ca90d7b8a5eeab070ccc555e033d31dc7a93124b87ea0016c19a6b7f6e145`, with unrelated work and all original source/identity/status/client/data facts preserved. Client byte identity, mapped assembly review, CRT identity cleanup, types/names and placeholder removal remain open; this does not complete the full goal.
- 2026-10-10 (library identity precedence and recovered client fixes): fixed partial library-header migration dropping managed identities and declaration headers masking explicit compiled-source bindings upstream; actual Rebrew main is `5794ceb976c19515a8f03813e1db6452dabd4b26`. Both regressions failed first; 496 focused tests and all hooks pass. Full suite: 11,463 passed / 50 skipped, with two packaging failures caused by the agent's offline cache missing pinned setuptools; both pass on the unchanged tree after fetching the dependency (11,465 passing cases across the runs). The stock GOLDTL initterm loop is visible as library code again; its client provider/native identity still needs reconciliation. Restored the earlier successful buffer-reader variants at GOLDTL 0x4013b0/0x4013f0, freshly RELOC 60/60 each; sanitized behavior checks retain the original stream handle. Restored the missing NUL-inclusive write loop with legal pointer arithmetic, but it remains SIZE_MISMATCH (36/34); no GA rerun or byte-match claim. Reviewed original srv_InitBuildingTypeTable fill at 0x4e7827 and recorded GOLDTL-only source evidence; its caller freshly matches RELOC 372/372, and GOLDTL lint has two remaining assembly warnings. Actual-main gate passes: 316/316 functions, 652/652 data symbols, all 100 imports, Wine exports and byte-identical raw server.dll. SERVER measurements use compiler identity `2a445d2674b16a2d3c9a15205a4f0a164391e2fdbf6d67808f6be54384769a75`; preservation checks pass and all three coverage documents are regenerated. The full client/source/type/placeholder goal remains open; receipts are in `.scratch/HANDOFF.md`.
- 2026-10-10 (animation reference binding): fixed the reconciliation gap upstream as `15d99c7f341fc5c8bb8648dd10bf6b8386991f2f`. Explicit `source rename PLACEHOLDER MODULE.0xVA` binds unbound references to a unique existing external definition without mutating identity/verdict rows or relaxing ordinary duplicate guards. Also corrected function-pointer declarator classification. Full suite 11,490 passed / 50 skipped / 0 failed; all 18 all-files hooks pass. Restored the prior successful TL animation builder and renamed only its identity/file to inferred CreateAnimationEvent, preserving the independent server health handler. Bound two numeric-placeholder callers and corrected their string-pointer declarations. Fresh TL results are RELOC 75/75, 138/138 and 152/152. GOLD's existing caller still has SIZE_MISMATCH (152-byte matching object, 160-byte span); default shared imports decline its padded span and the GOLD builder's 75-byte body plus five NOPs. Recorded the complete-extent/signature issue upstream; no threshold override or new GOLD builder verdict. Actual-main server gate passes all axes and the raw DLL remains byte-identical; all 316 SERVER measurements use compiler identity `4c19857593eaaf6b1c3a6aece59d4d90f57bb0b2e967916eb80c9949f63ed4df`. Preservation guard passes. Stored GOLDTL status is 3,564/4,904 game functions object-matched (282 EXACT / 3,282 RELOC), with 44.4% of .text accounted including library code and padding; client whole-file/data identity remains unverified. Continue the upstream extent repair, then client sharing/matching, types, ownership and placeholders. Full goal remains active and incomplete; detailed receipts and next pointers are in `.scratch/HANDOFF.md`.
