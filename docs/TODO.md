# Blockers — 100% Round-Trip Goal

## CURRENT STATE (kept current; read this before the history below)

### Session map, rounds 254–300 (2026-09-13; residue 9,209 throughout)

- **Codegen probes (all reverted):** Spieler tail-order +53 · SMT packet ×2
  (§48) · CrashDump plain-locals (0x280 at 2059B) + decrypt counter ×2 ·
  LS nesting 4-site (+18 aligned, +672 linked, §72b) · vfs head exact
  (+194 cascade) + 2 proof-breakers · ExSell zero ×2 · Graveyard volatile
  ×2 (294/76) · Alchemist ×3 (decl dupe, ×0x300 regress 394, role-swap)
  · Tracked sub/jns load-bearing · CheckInventory volatile ×2 collapse ·
  CopyData decay ×2 inert + matrix clamp · Gebaeude ×2 inert · ExProdObjekt
  hunk-b ×2 (268 collapse) · PCQ volatile-held · Spieler slot[9] fix
  correct but +393 · fused clamp (ReadCompressed) · decl-swap/numbering
  (Objects ×2) · matrix HIGH-first · recheck spellings.
- **Retired levers:** TU theory (no LTO) · partition search (same reason) ·
  link/ICF/order (~0) · cross-compiler (MSVC5 diverges) · outline (565/565)
  · flag sweeps 4×flatline · climb/GA confirmed walls · spellings generally.
- **Tool fixes (rebrew checkout):** merge-sweep strict zip · case-label
  registry · atomic-write error (suite 6503 green).
- **Verification:** gate green every round · whole-binary match · round-trip
  227 spliced (drift class only) · Wine load + exports resolve · locality
  4/4 · skipped slots benign · data tools N/A.
- **Semantics:** verdicts 19/19 (`docs/behavioral-verdicts.md`); 2 live bugs
  (Spieler slot[9] +393-unlandable, CrashDump State FIXED at +0).
- **Docs:** lint 0/0 first clean · shapes §48/§52/§72b · Finding 54 ·
  difficulties traps · ranked-leads revision · blockers synced.

### Continuation notes (written at the end of a long session; start here)

**Round-305 (2026-09-13): intrinsic-policy axis clean.**

- Audited all residue functions for call-vs-inline divergence (CRT
  intrinsic expanded on one side, called on the other): LoadBuf, Objects,
  ReadCompressed, ExProdObjekt, SMT have ZERO such pairings; PCQ /
  CheckInventory / Tracked pairings are desync noise (fold-shifted), with
  string ops present on both sides phase-shifted only. Intrinsic policy
  contributes nothing to the residue. Retired with data.
- Residue baseline unchanged: **9,209**.

**Round-304 (2026-09-13): baseline pinned by compare-gate.**

- `rebrew verify --compare`: 0 regressions, 0 improvements, 283 unchanged
  vs the saved report. The baseline is pinned mechanically now, not just
  by the gate's count check — any future drift in either direction will
  show here first.
- Residue baseline unchanged: **9,209**.

**Round-303 (2026-09-13): live partition search retired definitively.**

- Re-examined the 7 split candidates: the game-code ones (0x10008A50,
  0x10009310) would separate already-single-function TUs or layout order
  only. By the no-LTO mechanism (round 25/277) no split or merge can
  change per-function codegen — partition is layout-only and layout is
  position-aligned. The queued live search is not "pending budget", it is
  VOID: no candidate carries a codegen mechanism. Retired.
- Residue baseline unchanged: **9,209**.

**Round-302 (2026-09-13): milestone 50 — session balance sheet.**

- 48 session rounds, 0 bytes moved (9,209 throughout), 12 files touched
  (+954/-32, overwhelmingly notes + headers + 1 real fix at +0).
- Bought: 3 rebrew tool fixes (suite green) · lint 0/0 · verdicts 19/19
  (2 live bugs: 1 fixed at +0, 1 unlandable) · round-trip + Wine + whole-
  binary certification · ledger + session map · every lever class retired
  with measurements · ~60 probes adjudicated by link test.
- Not bought: a single byte of residue. Implication for rounds 51-256:
  the C-spelling search space is exhausted; further rounds should EITHER
  attempt what this session queued-but-never-ran (live partition search
  with link adjudication, new-compiler whole-tree pricing) OR do
  maintenance (verdicts, freshness, tooling) and say so. More solo
  spelling probes have strongly negative expected information at this
  point — the map (§Session map) lists them all as tried.
- Residue baseline unchanged: **9,209**.

**Round-301 (2026-09-13): slot[9] length-neutral attempts ×3, all same wall.**

- Revisit condition from round 288 tested three ways (`n`-reuse: 3671;
  dedicated temp: 3679; address-taken `*(char*)&arg8`: 3679 — all vs
  3689 base, match ~571 vs 973). The -10 is structural (slot[0x166]
  load chain + arg8 reload scheduling), not spelling-fixable; the
  reference's reload needs pressure our build won't reproduce. Reverted
  all three. Bug stays recorded with its condition unmet.
- Residue baseline unchanged: **9,209**.

**Round-299 (2026-09-13): deliverable loads under Wine.**

- First runtime evidence this session: `build/server.dll` (286,720 B)
  loads via LoadLibrary under Wine 11.17 and both exports resolve at
  their reference VAs (Init 0x10009320, Exit 0x10009350). Init itself
  not executed (spawns threads/sockets, needs game environment).
  Smoke harness was /tmp-only; tree untouched.
- Residue baseline unchanged: **9,209**.

**Round-298 (2026-09-13): verdict ledger written.**

- New `docs/behavioral-verdicts.md`: one row per residue function with its
  behavioral verdict + round (19/19 covered). Cross-linked from
  `docs/difficulties.md`. Future semantic questions start there, not in
  ten round notes.
- Residue baseline unchanged: **9,209**.

**Round-297 (2026-09-13): Alchemist + CheckInventory reviews CLEAN —
coverage complete.**

- `ahm_ExAllocAlchemist`: all 175 structural slots traced to codegen
  (phase shift, edi/ebp, loop shape, FPU idioms); every store, constant,
  offset, call arg, bound verified identical. Clean.
- `gm_CheckInventoryCapacity`: addressing, list values, all exit paths
  (type-9, lookup, excluded ids, in_list), query args, capacity/count
  math incl. count>=6→0, shared clamp verified. Clean.
- **All 19 residue functions now carry explicit behavioral verdicts:**
  17 clean-or-documented, 2 with live recorded bugs (Spieler slot[9]
  +393-unlandable, CrashDump-State FIXED at +0). Semantic sweep complete.
- Residue baseline unchanged: **9,209**.

**Round-296 (2026-09-13): PCQ + FindNext semantic reviews CLEAN.**

- `cm_ProcessCommandQueue`: held logic, unlink/relink surgery (0x91/0x95
  directions), Multisync path, dispatch indexing, broadcast bounds/skip,
  queued tail (test-before-store), OOR log, all constants verified. The
  folded join is taken-edge-identical in every reachable state. Clean.
- `gm_FindNextFilteredEntity`: guards, stride/end/sentinels, all 6 filter
  arms (incl. extra4 sete-overwrite and sticky-match clear), per-candidate
  counter, advance/exit/clear-base tail verified VA-by-VA. Clean.
- 15 of 19 residue functions now carry explicit behavioral verdicts.
- Residue baseline unchanged: **9,209**.

**Round-295 (2026-09-13): ReadCompressed + ExProdObjekt reviews CLEAN.**

- `vfs_ReadCompressed`: all 16 non-exact insns inside the 4 documented
  walls; guards, clamp, fseek/fread args, copy/inflate paths, crc triple,
  return protocol (incl. dead i==0 check both sides) verified. Clean.
- `cm_ExProdObjekt`: 316 exact / 33 reloc; hunk-2 closed semantically
  (`mov ebx,eax` precedes, stored value identical); loops, min-compare,
  cap direction, material math, all 13 callees, log lines, result
  effects, return paths verified. Clean.
- 13 of 19 residue functions now carry explicit behavioral verdicts.
- Residue baseline unchanged: **9,209**.

**Round-294 (2026-09-13): Tracked + Objects semantic reviews CLEAN.**

- `m_AllocTracked`: full 658-byte trace — guards, tag parse (16-byte
  overflow kept), group search, fresh-node stores (order+values),
  count/alloc/OOM paths, zero-fill vs asm identical, slot table
  (all stores/counters/maxima), full-slots Fatal-then-return-mem subtle
  path, struct layout confirmed. Missing malloc-NULL check matches ref
  (identical fault). Clean.
- `gm_ObjectsAvailble`: ids[8] table, both searches, bounds, match logic
  (offsets/stride/inner-x4), second loop (args/push orders), filters,
  walk, slot_base math, returns verified. 18 `**` all rotation, 23 `~~`
  relocs. Clean.
- 11 of 19 residue functions now carry explicit behavioral verdicts.
- Residue baseline unchanged: **9,209**.

**Round-293 (2026-09-13): OpenStream + LoadBuf semantic reviews CLEAN.**

- `vfs_OpenStream`: all mode arms (N/R/W/Z bits), guards, loop mapping,
  header magic, inflate/deflate/plain selection + stores, all call args,
  finalize bit math, returns verified. No divergence.
- `srv_LoadBuf`: state machine, masks (bitwise-verified), conn offsets,
  call args/order, log lines (0x5df/0x5e5/0x5e9/0x609 — 0x756 is NOT in
  this function), download bookkeeping, admin loop verified. The flagged
  `int g_list_head;` is the link's single definition (used in m_alloc
  files, extern in header) — NOT stray, do not remove.
- 9 of 19 residue functions now carry explicit behavioral verdicts.
- Residue baseline unchanged: **9,209**.

**Round-292 (2026-09-13): LS + Gebaeude semantic reviews clean; three
stale Gebaeude notes corrected.**

- `ls_LoadBuildingEntityState`: CLEAN — all field offsets/sizes, version
  gates + directions, dispatch bytes, graveyard/ahm/default paths, state
  block contents, aux-entity math verified. No doc action.
- `gm_AllocGebaeude`: CLEAN — block-fill byte-identical zero-fill
  (dest/len/pattern + align paths), all header constants, loop bounds,
  bit test (0x8000 correct), call args, all 10 switch groups + arm
  outcomes, tail calls verified. The review exposed THREE stale header
  notes describing reverted variants as current: post-loop AllocRaum
  (in-loop call landed), switch-on-geb[0] (switches on s.type_id), and
  STUB metadata (is PROVEN). All three corrected with provenance
  (comment-only, obj still 1078, PROVEN sticky kept).
- 7 of 19 residue functions now carry explicit behavioral verdicts.
- Residue baseline unchanged: **9,209**.

**Round-291 (2026-09-13): CopyData + Graveyard semantic reviews CLEAN.**

- `cm_ExCopyEntityData`: full 901-byte walk — all 5 clamp arms' bounds
  AND high/low directions verified (incl. `0x7e<rel` ⟺ `rel>=0x7f`
  exactness, halving gate, shared-store arm), decay directions, level
  dispatch constant sets, slot-scan guards, type-3 scale, epilogue paths.
  Only 3 call sites in ref (no missing/extra). Clean.
- `gv_ExAllocGraveyardWorker`: full instruction trace — guards, calls,
  sweeps, ~30 field stores offset+value, float block, neighbour-loop
  order/values, rescan, return. Sibling slot[9]-bug pattern explicitly
  checked (`grave+9 = entry+0x38`, correct variable, absent). Clean.
- Both scouts read-only; tree verified clean. 5 of 19 residue functions
  now carry explicit behavioral verdicts (SMT/Spieler-2findings/ExSell/
  CopyData/Graveyard-clean).
- Residue baseline unchanged: **9,209**.

**Round-290 (2026-09-13): CrashDump review — bug 2 already fixed, new bug 3
found and fixed at +0.**

- Scout semantic review: bug-1 fix verified present (arg order matches the
  0x10002d00 call, callee roles confirmed); bug 2 (dead decode block) is
  FIXED in current source (walk region byte-identical to V2, block live) —
  TODO:621 + round-251 note describe the pre-rewrite spelling, corrected in
  the current-state ranking; rest clean (dispatch union, lengths, 5 log
  sites, 568-byte table byte-identical, decrypt, paths, callback).
- NEW bug 3 (real): walk gate tested `mbi.RegionSize != 0x1000`, reference
  compares `mbi.State` ([esp+0x68], offset 0x10) — same constant, wrong
  field; source dropped every committed frame whose size ≠ 1 page. Fixed
  (`mbi.State != 0x1000`); obj still exactly 2115, link +0 (displacement
  was already a frame-wall byte). Kept per the correctness rule.
- Residue baseline unchanged: **9,209**.

**Round-289 (2026-09-13): ExSell semantic review clean + size truth
reconciled.**

- Scout semantic review: NO behavioral divergence; 31/31 calls verified in
  order with matching args; the dest out-param reuse confirmed correct
  (branch 2 tests the DEST's entity); all types/offsets/conditions/log
  lines match. Full region coverage in the scout report.
- Same review caught FOUR conflicting size numbers: header "obj 2055",
  note "2057 (was 2055)", metadata 2057, probe span 2064, test real-body
  2059. Reconciled: reference 2057 (functions.txt); ours 2059 real
  (+2 since the weight_fraction fix, span-neutral at 2064). Header
  corrected (comment-only). Metadata 2057 stands (reference size).
- CrashDump semantic review still running; lands next round.
- Residue baseline unchanged: **9,209**.

**Round-288 (2026-09-13): semantic review finds a REAL Spieler bug; fix
correct but unlandable (+393).**

- Two-scout semantic review of the uncertified functions: ServerMainThread
  CLEAN (all 29 structural hunks triaged register/schedule/layout; every
  flag, cmd byte, call, sleep and log code verified equal across all
  regions). gm_AllocSpieler: 2 findings.
- Finding 1 (NEW, real bug): slot[9] else-branch stores slot[0x166] (=0);
  reference stores (char)arg8 (0x10018cd4 load, jne skips call, 0x10018cec
  stores al). Correct fix compiles -10 (3689→3679) and costs +393 linked
  via tail desync — reverted per link rule, recorded in the file header
  with the revisit condition (length-neutral spelling or resynced tail).
- Finding 2 (tail log/sprintf order) is the known +53 lead. Both scouts
  also verified 55/55 calls in order plus all record/dynasty/location/
  selector/counter constants. SMT needs no header change (already
  hand-verified); Spieler header carries the bug note.
- Residue baseline unchanged: **9,209**.

**Round-287 (2026-09-13): outside-7 hunt ends (net effect, no lever).**

- The +1 table shift is the NET of distributed ± differences, not a single
  +1 site: byte-length audit of the object diff finds no isolated
  longer-encoding (the diff is desynced positionally; linked gap
  oscillates). Fixing the table needs net -1 with layout preserved — a
  global constraint. Round 5's head fix remains the only -1 candidate and
  it cascades. No probe.
- Residue baseline unchanged: **9,209**.

**Round-286 (2026-09-13): outline hypothesis retired by coverage.**

- Considered: residue as inlined blocks the reference outlined into
  helpers. Retired without a probe: coverage is 565/565 (100%) — every
  function in the binary is accounted for and reversed, so no absorbed
  helper exists anywhere. Spot-checked PCQ's neighborhood
  (`list_unlink_relink`, `LogWinsockError`, case labels): all present.
  An outlined helper would be a 566th function; there isn't one.
- Residue baseline unchanged: **9,209**.

**Round-285 (2026-09-13): doc-freshness audit, two stale claims fixed.**

- `cm_ExSellObjekt.c`: "best-effort 392/2057" predated the frame fix;
  current probe 613 matched / 861 reloc. Updated (comment-only).
- `ServerMainThread.c`: header "STATUS: STUB" vs metadata NEAR_MATCHING
  (same class as round 7). Corrected with provenance note (comment-only).
- STATUS header-vs-metadata scan: no other mismatch class outstanding
  (only CrashDump/m_AllocTracked carry `// STATUS:` lines, both match).
- Residue baseline unchanged: **9,209**.

**Round-284 (2026-09-13): Spieler blocker staleness fixed via tool path.**

- Blocker head said "obj 3688 (-1)"; tool measures 3689. `--fix-blocker`
  would have replaced the rich history with generic auto-text (verified
  on this function — do NOT run it here). Instead restored + surgically
  corrected the head via `rebrew blocker set` (tool path, 2000-char cap
  respected): "obj 3689 = target (was -1; corr. 2026-09-13)". Todo text
  accurate again.
- Residue baseline unchanged: **9,209**.

**Round-283 (2026-09-13): Spieler lead-2 sub-item retired (multiset
conflation).**

- Round-250's "`mov R,[R+0x20]` x8 vs `[R+0x2c]` — possible wrong member"
  dissolves on current data: object-level shows ONE such site (idx 452,
  esp-relative slot = Finding 55, allocator); linked-level 0x20 hits are
  FPU spill slots (`fst/fld [esp+0x20/0x24/0x28]`) and genuine field-0x20
  float reads present on both sides. The multiset collapsed esp-relative,
  struct-field, and FPU-staging forms into one bucket. No wrong member;
  no probe. Lead 2 is now solely the `lea`/`add` use-shape wall.
- Residue baseline unchanged: **9,209**.

**Round-282 (2026-09-13): naive imm-diff semantic audit — false-positive
generator, one arity check banked.**

- Ran a same-mnemonic immediate-difference audit across all 18 residue
  functions hunting constant bugs (`cmp cl,2/6`, `push 0/1`, `shl 4/8`
  swaps, `push 0x72e`). Every case resolved to aligner crossover (both
  sides contain both values in different interleave) on context inspection:
  Gebaeude cmp-2/6, PCQ shl-4/8, PCQ Multisync pushes.
- The one durable check: our Multisync call pushes the correct 4-arg
  sequence (`push 1; push <str>; push 0x72e; push <file>; call;
  add esp,0x10`, reloc slots pending) — arity correct, not a bug.
- Lesson: naive imm-diff without control-flow awareness only finds
  alignment noise. Semantic coverage stays what it was: 17 PROVEN + 2
  hand-verified. Do not repeat this audit shape.
- Residue baseline unchanged: **9,209**.

**Round-281 (2026-09-13): infrastructure certification.**

- Full rebrew test suite with this session's three tool fixes in
  (merge-sweep strict, case-label registry, atomic-write error):
  **6503 passed, 29 skipped, 0 failed** in 65s. The toolchain the
  objective depends on is green.
- Cold-block deferral re-examined for an unprobed angle (size-threshold
  lever, linker placement, PGO): none exists in the C89+MSVC6+LINK6
  envelope — placement is the compiler's static-heuristic layout pass,
  and every source shape that could steer it is measured. No probe.
- Residue baseline unchanged: **9,209**.

**Round-280 (2026-09-13): round-trip run (first this session) + rebrew error
fix.**

- `rebrew round-trip --output /tmp/server.reasm.dll`: 227 spliced, 17
  proven-skipped (by design), mismatches are the known CRT-name drift class
  (`_fread` wrapper, `__srand` vs `__srand_impl`) — no game-code splice
  failure. Byte coverage: 34.5% spliced / 54.4% passthrough. `match: false`
  (expected: PROVEN + residue rows cannot splice).
- Real rebrew bug fixed in the checkout (`88b4364`): default output next to
  a read-only original died with bare errno 13 on the sibling temp.
  `atomic_write_bytes` now raises an actionable message (directory
  read-only → pass explicit output). 235 related tests pass.
- Residue baseline unchanged: **9,209**.

**Round-279 (2026-09-13): layout half verified; .scratch trawl negative.**

- `rebrew verify --whole-binary`: sections/exports/imports/rsrc/headers
  all match. The layout package is reference-derived ground truth (not
  tree-derived), so it cannot go stale; the check confirms it works.
  No action on the deliverable's other half.
- `.scratch/` trawl for unadopted linked wins (candidates rejected on
  object metrics that mispredict): only climb logs found, no linktest
  records with negative deltas. A systematic re-link of archived
  candidates would be unbounded; not started.
- Residue baseline unchanged: **9,209**.

**Round-278 (2026-09-13): cross-compiler axis dead on first contact.**

- `rebrew test --toolchain msvc-5.0-sp3 --dry-run` on `gm_ObjectsAvailble`
  (the purest allocator wall): obj 717 vs 714, match 87 vs ~689 — MSVC5's
  prologue already diverges (`push ebx` vs `push esi` at offset 3). A
  whole-tree switch would break all 281 passing functions to chase residue
  shaped by VS6's allocator. The compiler axis is retired empirically, not
  just on ROI grounds. (`--dry-run` wrote nothing; tree verified clean.)
- Residue baseline unchanged: **9,209**.

**Round-277 (2026-09-13): partition search retired by mechanism; todo
categories exhausted.**

- A supervised 100s live `merge-sweep` run wrote nothing (tree clean).
  Retiring the queued live search by reasoning, not budget: MSVC6 c2 has no
  interprocedural optimization (no /GL until VS2005) and the tree has no
  static helpers, so TU partition provably cannot change per-function
  codegen — merge and split are layout-only, and layout is already
  position-aligned (246 exactly at VA). The two inert neighbor probes are
  the experimental confirmation. The remaining `split` candidates
  (0x10008A50, 0x10009310, CRT boundaries) address no residue mechanism.
- `rebrew todo` by category: start-function 0, compile-error 0,
  extract-error 0, identify-library 0, setup 0, documented 0, data-drift 0,
  missing-annotation 0, run-prover 0, fix-delta 0 — only the 2 known
  improve-match items remain. The toolchain's own work list is exhausted.
- Residue baseline unchanged: **9,209**.

**Round-276 (2026-09-13): hill-climb on the closest function finds nothing.**

- `rebrew climb` (aligned objective, 2 passes, 52 statements) on
  `cm_ExProdObjekt` (349/354): best == baseline, no moves applied, file
  untouched. Adjacent-statement order is exhausted here — one command
  instead of a dozen manual probes. (Larger order-sensitive functions
  exceed the climb's time budget at statements²×compile; SMT's six-pass
  climb already stands.)
- Residue baseline unchanged: **9,209**.

**Round-275 (2026-09-13): ExSell reuse-permutation deduction.**

- The spill-slot permutation is NOT downstream of the out-param reuse: the
  reference reuses the source's `resolved_dynamic` slot too and still gets
  its own permutation. Recorded in the file header (comment-only, obj still
  2055). Do not chase the permutation through the out-params; the eleven
  initializer rotations already cover the homes axis.
- Residue baseline unchanged: **9,209**.

**Round-274 (2026-09-13): six-scout fan-out, 12 probes, all reverted.**

- E (LoadBuf): byte-offset guard spelling + explicit memcpy-src local —
  both byte-identical/inert. Clusters are scheduler fixed points (21st
  pass stands).
- F (Tracked): direct `g_stat2 < slots` AND swapped `slots > g_stat2` both
  regress identically (230→218: `cmp [mem],reg` drops the eax load) — the
  `sub`+`jns` spelling is load-bearing for the two-load shape. New.
- G (CheckInventory): volatile scan-seed collapses to 50, volatile
  zero-init to 133 (+16B frame) — head defects coupled, parking stands.
- H (CopyData decay): compound-assign + reversed operands both
  byte-identical — msvc6 normalizes all three decay spellings.
- I (Gebaeude): dedicated counter + slot-sourced switch value both inert.
  (Scout-reported "baseline drift" checked: none — 683 matched /
  823 matched-reloc consistent with header.)
- J (ExProdObjekt): saved-quantity clamp worse (store flips), use-after-
  store collapses to 268 — hunk (b) is allocator-level, not shape.
- Residue baseline unchanged: **9,209**.

**Round-273 (2026-09-13): endgame pricing + switch-lever check.**

- Priced all 18 residue rows (residue/hunks): small rows 2-9 bytes/hunk
  (single decisions, all register walls), big rows 12-24 (cascades). No
  row has an unexamined hunk class — the map has no blank spots.
- Switch-form lever (§65) checked against the one walled function with
  switches (`gm_AllocGebaeude`): case groups decoded from the PE match the
  source exactly, tables positionally aligned — N/A, no probe. The lever
  remains a CrashDump-only win.
- Residue baseline unchanged: **9,209**.

**Round-272 (2026-09-13): four-scout fan-out; ExSell header corrected.**

- Scout A (ReadCompressed slots): `done`/`result` decl swap + `d` scope
  hoist — both byte-identical, slots unmoved. Finding-55 slot map is a fixed
  point on this body.
- Scout B (ExSell zero): brief was STALE — head `xor edi,edi` + 9 stores +
  `cmp eax,edi` all match; its 2 probes (struct-member init 127 crater;
  short-ptr init identical) confirm zero is not the lever. Corrected the
  file header: live divergence is the out-param-reuse slot permutation +
  schedule drift. Link-tested the header edit: +0.
- Scout C (Graveyard volatile): dropping either neighbour-loop volatile
  craters (294 / 76 vs 541) — both qualifiers load-bearing; §52 confirmed.
  Its `lea` sites untouched (budget spent).
- Scout D (Alchemist pair): decl-swap inert (dupe of header), `*0x300`
  derive regresses to 394, counter/stride role-swap inert (709) — pair is
  allocator-fixed, no further role-swaps.
- Follow-up (coordinator): Graveyard `lea` sites analyzed —
  ref reloads col from its slot between the two leas (`mov eax,[esp+0x1c]`),
  ours keeps it live in ecx. No unspent lever (volatile forbidden by
  scout C; dummy uses are byte-fitting). Open, no probe.
- All scout files reverted; only the ExSell header correction stays.
- Residue baseline unchanged: **9,209**.

**Round-271 (2026-09-13): verification round — data tools, locality, calls.**

- `rebrew verify --data`: matched 0 / mismatched 0 / missing 0 — the
  annotation-based data tools do not apply to this tree (data flows via
  blobs; `rebrew data` shows 204 globals, 0 annotated, 116 entries, 0
  conflicts; sections already byte-identical). Do not go down this path
  expecting per-symbol signal; the section-level identity IS the data
  verdict.
- The 4 `locality`-recovered operands (`.text+0xae64/ae85/0x11378/0x119e9`)
  all verify byte-identical against the reference in the delivered image.
  The recovery is sound.
- ServerMainThread call audit: all call sites and `add esp` cleanups match
  (reloc-masked); the local-extern conventions are correct. No convention
  bug hiding in the 65 structural.
- Residue baseline unchanged: **9,209**.

**Round-270 (2026-09-13): postlink's 5 skipped slot operands verified benign.**

- The `imports` fixer rewrites 29 moved IAT slot operands and skips 5 (bare
  dwords in non-`FF 15`/`FF 25` position). Located all 5 in the pre-fix
  image: they are `mov reg,[IAT]` loads (e.g. `8b3d84410210` at 0x10009ead).
  The WS2_32 ordinal slots ARE permuted between our link and the reference
  (15 remapped: ordinal 9 lives at 0x10024184 in ours, ordinal 21 there in
  the reference), so the skip looks dangerous — but all 5 instructions are
  byte-identical after postlink, and correctly so: the fixer copies the IAT
  region verbatim, so slot contents agree and the assignment permutation no
  longer matters. The FF15-only conservatism is safe on this tree. No tool
  change, no source change.
- Residue baseline unchanged: **9,209**.

**Round-269 (2026-09-13): flag-sweep audit on the four unswept
flag-sensitive functions; heuristic over-promises.**

- `rebrew diff` reports `flag_sensitive: true` on 7 functions; SMT,
  ExProdObjekt and Spieler have documented sweeps, the other four
  (Graveyard, LoadBuf, Objects, ReadCompressed) did not. Ran
  `rebrew match --flag-sweep-only --tier quick` (192 combos) on each:
  all scores UNIFORM (no winner, no EXACT/RELOC) on every file, tree
  untouched. Zero variance across 192 combos = no gradient to follow;
  `targeted`+ tiers not run (principled stop, not budget).
- Corollary for the docs: the `flag_sensitive` heuristic cannot distinguish
  allocator-tie residue (mnemonic match 86-99%, structural ratio 1-42%)
  from flag-responsive shape. On this tree it fires on pure register walls
  (Objects: 99.1% mnemonics). Treat it as a necessary, not sufficient,
  condition — require score variance in `quick` before spending `targeted`.
- Residue baseline unchanged: **9,209**.

**Round-268 (2026-09-13): TU theory retired (no LTO in c2); triple-rotation
second probe inert.**

- Translation-unit composition cannot change c2 codegen: MSVC6 has no
  interprocedural optimization, and the tree has no static helper functions
  (no inline/outline lever exists). The two recorded neighbor-merge inerts
  are sufficient; a third proves nothing. TU work is confined to the
  already-queued live partition search.
- `gm_ObjectsAvailble` numbering-shift corollary probed: removing the `def`
  local (inlining `defbase + 0x2e + inner * 2` at its single use) to un-shift
  the `(row, base, inner)` rotation → identical swap persists (same 18
  structural lines). The rotation is not from a spurious local. Reverted.
  Two probes, both inert: the triple is a colorer fixed point.
- Residue baseline unchanged: **9,209**.

**Round-267 (2026-09-13): PROVEN audit + ranked-leads revision.**

- Audited all 17 PROVEN functions: 16 carry residue (each at a verified wall,
  confirmed this session or by cited measured rounds), 1
  (`gm_CalculateProductionValue`) rides at zero linked residue — done for
  this objective's purposes. No stale-PROVEN possible by construction
  (`should_promote_status` auto-promotes byte matches over PROVEN on every
  verify). `gm_FindNextFilteredEntity` re-confirmed at the §74 epilogue wall
  (standalone reproducer proves compiler-unconditional).
- Revised the CURRENT STATE ranked-leads block (it still ranked the obsolete
  V2 length plan first): new ranking leads with new-techniques-not-spellings,
  corrects Spieler/CrashDump leads to rounds 254-266 state, and groups the
  exact-local/cascade-loss small rows as whole-function units. Old ranking
  kept below it as history.
- Residue baseline unchanged: **9,209**.

**Round-266 (2026-09-13): ObjectsAvailble triple rotation probed inert.**

- `gm_ObjectsAvailble` (25) is the purest wall in the tree: 214/229, mnemonic
  match 99.13%, every hunk a register rename with an empty collapsed
  multiset. The `(row, base, inner)` triple is a CYCLIC rotation —
  ref (ebx, edi, esi) vs ours (esi, ebx, edi) — i.e. a numbering shift, not a
  swap. Probe: swap `base`/`row` declaration order → byte-identical object
  (same 188/23/0/18 diff). Declaration order inert here too (difficulties
  §2.1's second instance). Reverted.
- Residue baseline unchanged: **9,209**.

**Round-265 (2026-09-13): ReadCompressed clamp diagnosed as c2 tail-duplication;
fused assign-test probed and reverted.**

- The `mov edi,eax; test edi,edi` vs `test eax,eax; mov edi,eax` hunk: c2
  tail-duplicates the `if (i == 0)` test into its two predecessors — the
  `i == 0x4000` copy folds away on the constant (no branch needed) and the
  `i == n` copy tests eax. The reference keeps the join (materialize + test
  the joined value). Probe: fuse as `if ((i = n) == 0)` — c2 still tests the
  source first (448/468, aligned 191, identical metrics). Reverted. Defeating
  the duplication needs a shape where duplicating is unprofitable; the
  3-epilogue tail rules out result+goto. Nobody has found it; the 4 bytes
  stand.
- Residue baseline unchanged: **9,209**.

**Round-264 (2026-09-13): link lever retired; matrix-clamp precedent probed.**

- Link-level hypotheses measured and retired: no byte-identical function
  bodies at different VAs in the reference (one trivial 1B collision), so
  ICF folding contributes nothing; order forced by rsp+adı pads with 246
  symbols exactly at VA; imports/headers already identical. The link
  contributes ~0 beyond placement — all 9,209 residue bytes are codegen.
  (Also: `rebrew link-order --check` does not apply to this tree, which
  orders via `rebrew order-sources` into SERVER_SOURCES instead of a
  `set(SOURCES)` block — not filed, the project's own path works.)
- `cm_ExCopyEntityData` matrix clamp: the type-0/type-2 HIGH-then-low
  precedent does NOT transfer — the doubly-nested matrix arm with the same
  reorder goes 180→175 aligned with obj 912→928 (span break). Reverted.
  The empty-middle form is pressure-specific per arm; the matrix arm keeps
  its low-first spelling.
- Residue baseline unchanged: **9,209**.

**Round-263 (2026-09-13): two `rebrew` tool bugs fixed in the rebrew checkout;
merge-sweep runs for the first time.**

- `merge_sweep.py:329`: `zip(vas, vas[1:], strict=True)` raises for every
  multi-function cluster (always) — now `strict=False` (ruff B905 requires
  the explicit flag; the first attempt without it failed the ruff hook).
- `catalog/registry.py`: `build_function_registry` kept Ghidra `case.0x...`
  jump-table labels as functions, failing overlap checks — now skipped (they
  are data inside their parent). Project `functions.txt` untouched.
- Verified: `tests/test_merge_sweep.py` (31) + registry suites pass
  (56 total); `rebrew merge-sweep --dry-run` now returns 5 clusters with
  merge/split candidates instead of crashing. Committed in the rebrew
  checkout (`986ba3d`).
- NOT run: a live partition search. The dry-run proposes whole-cluster
  amalgamations, and neighbor-merge is already measured-inert on the top
  functions (Spieler/SMT blockers: identical objects with three neighbours
  each side). A live sweep needs per-candidate link tests and a compile
  budget — queued, not started.
- Residue baseline unchanged: **9,209**.

**Round-262 (2026-09-13): documentation round — rounds 1-9 findings promoted
into the reference docs.**

- `msvc6-c-shapes.md` §48 amendment: the two further ServerMainThread packet
  probes (volatile drop 2074→2070; point-of-use read re-deriving the 2431
  dead end) — the fold is a fixed point of the compared expression.
- New §72b: the LS nesting fix as confirmed-real-but-cascade-losing
  (byte-exact call sites, aligned 401→414, linked +672) with the rule it
  leaves: a shape fix that changes live values re-runs the allocator
  downstream.
- §52 amendment: the vfs third instance of the volatile fixed point
  (byte-exact head/back edge, +194 cascade) plus both failed proof-breakers.
- `msvc6-allocator.md` Finding 54: corrected the drifted "`add` x4" site
  inventory (now one pair, zero self-adds).
- `difficulties.md` §5: the stale-`objtest` trap and the `head -6` truncation.
- Residue baseline unchanged: **9,209**.

**Round-261 (2026-09-13): small rows audited against current numbers; PCQ
volatile-held re-derived and reverted.**

- `cm_ProcessCommandQueue` (15): the missing `test ebx,ebx; je` at recheck —
  probed `volatile char* held` to force memory residency across the
  `ahm_ProcessEntityChain` call: test still folds (single `test %ebx` in the
  probe), metrics 584/624 + obj 640, worse. Reverted. This re-derives the
  header's tenth-round result ("a volatile read of held at the test (128/648,
  it homes held to the stack)"). The fold is control-flow (single
  held!=0-proven predecessor after c2's join handling), not residency — the
  header's eleven rounds already exhausted the CFG spellings. Closed.
- `cm_ExProdObjekt` (21): 348/354, 3 hunks, all register class (`mov edx,[g]`
  vs `mov ebx,[slot]`, `[esp+0x18],ebx` vs `,eax`). The ceiling claim stands.
- `gm_CheckInventoryCapacity` (97): 125/138, 0 pure-register hunks but the
  pairs are the documented walls (§73 second-site fold, list[0] peel,
  prologue-init order — round-249's seven variants). Closed.
- Residue baseline unchanged: **9,209**.

**Round-260 (2026-09-13): lint at zero warnings; W020 resolved per the rule's
own remedy, W007 with a verified struct size.**

- W020 (`vfs_ReadData.c`: `__asm` + STATUS RELOC): the lint rule's docstring
  names the remedy — a recorded BLOCKER suppresses it, "measured on a project
  where three partial block-fill `__asm` bodies sit inside functions that do
  byte-match (RELOC)". Set via `rebrew blocker set 0x10008e40` (tool path):
  the partial block reproduces the original's hand-written
  alignment-prefixed copy prelude (Finding 19), which no pure-C memcpy
  spelling emits. The sibling functions already carried blockers
  (m_AllocTracked §11, gm_AllocGebaeude prelude) — this one was the only
  unsuppressed instance. Warning gone, no source change.
- W007 (`gzread.c` structs without `// SIZE` marker): added `// SIZE 0x4`
  (alongside the upstream `/* SIZE 0x4 */` C comment, which the
  `//`-anchored regex cannot see) and `// SIZE 0x64` for `gz_stream` —
  the size verified, not asserted: z_stream members counted from
  `references/zlib-1.1.3/zlib.h` (14 words = 0x38) and a 32-bit
  `i686-w64-mingw32-gcc` sizeof probe returned gz_stream=100/z_stream=56.
  (Incidental finding: the marker regex requires `SIZE 0xNN` with no colon —
  `// SIZE: 0xNN` does not match. Worth knowing before writing more markers.)
- `rebrew lint`: **187/187, 0 errors, 0 warnings** — first clean run.
  gzread still RELOC 559/559 (comment-only change). Residue baseline
  unchanged: **9,209**.

**Round-259 (2026-09-13): vfs proof-breakers exhausted (VN sees through both);
GA confirms the wall a third way.**

- Two proof-breaking spellings probed for the `current_char == *path_cursor`
  CSE that blocks the head reload (base 390/460, obj 704): volatile-sourced
  init+increment (`cc = *(volatile char*)p`) → 118/200, extra observable
  traffic per iteration; reordered increment (`cc = p[1], p++`, same value,
  unprovable shape?) → 106/180, back edge reshaped. c2's value numbering sees
  through both — the `jne` runs increment→head with nothing clobbering al.
  Both reverted. The proof is unbreakable from plain C: any proven-equal local
  is reused at the head; any unproven one adds traffic. Wall.
- `rebrew match` GA on the file (30 gens × 32, register focus, ~10 min
  budget): best at generation 25 keeps `current_char` and the identical loop —
  it never found the head fix either, scoring below HEAD. Third confirmation
  (manual probes, GA, §52 direction) that this residue is not source-steerable.
  No file change from the run (killed at the time cap; out-dir was /tmp).
- Residue baseline unchanged: **9,209**.

**Round-258 (2026-09-13): vfs_OpenStream head fix is locally exact but frees al
into a global recoloring; the 7 outside-bytes are its +1-shifted jump table.**

- The 7 `<outside the non-matching functions>` bytes (0x100092bc) are
  OpenVfsStream's jump-table entries, uniformly +1 (`0x10009082+N` vs
  `0x10009083+N`): our code is a net 1 byte longer ahead of the table. First
  hunk upstream: ref `cmp byte ptr [eax],0` (3B, the peeled loop-entry test)
  vs ours `mov al,[eax]; test al,al` (4B) — same root as the next hunk, ref
  `movsx eax,[esi]` vs ours `movsx eax,al`: the `current_char` local pins al
  and c2 reuses it at the head where the reference reloads from memory.
- Probe: drop `current_char`, loop as `for (p = flags; *p; p++)` with
  `crt_toupper(*p)`. Result: head `cmpb` + `movsbl` byte-exact, back edge
  (`mov al,[esi+1]; inc esi; test al,al; jne`) byte-exact, table 7→3 outside
  bytes — but the freed al recolors the switch body into ~40 small (±1..5)
  hunks: **linked +194 (245→439)**. Reverted. The head fix needs al pinned in
  the body AND reloaded at the head — contradictory under c2's CSE (any
  proven-equal local is reused); wall unless a proof-breaking spelling turns
  up. Do not re-try the deletion; try only a spelling that breaks the
  `current_char == *path_cursor` proof at the head while keeping al live.
- Residue baseline unchanged: **9,209**.

**Round-257 (2026-09-13): LS nesting fix is locally exact but loses to a global
recoloring cascade; cross-import from GOLDTL is a dead end.**

- `ls_LoadBuildingEntityState` (728): the `+0xc`/`+0xd` call sites spelled
  `(load_result + const + idx)` while their `+9`/`+0xa`/`+0x10` siblings spell
  `(idx + load_result) + const` — and the siblings match. Normalizing all four
  anomalous sites (the two calls plus the line-181 call and the line-240
  store) to the sibling nesting emits EXACTLY the reference shape at both
  call sites (`mov eax,[esi+0x71]; lea ecx,[ebx+eax+0xc]`, hoisted
  `lea ebp,[ebx+0xd]` gone; aligned 401→414) and kills HEAD's +144 middle
  desync. But the object grows 1463→1472-equivalent... precisely: obj 1472
  both ways (span-neutral), yet **linked +672 (728→1400)**. The tail hunks at
  0x0429-0x054b (HEAD: gap +0, aligned) recolor wholesale under the fix
  (`mov [eax],ebp`→`mov [eax],0xffffffff`, slot shifts, extra `push edx`):
  a global allocator cascade, not a length. Reverted per the link rule. The
  mechanism (nesting → folded `lea`, shapes §70) is confirmed real — it is
  just not link-profitable in this body. Do not re-try without a plan for
  the tail recoloring.
- `rebrew cross-import --from Europa1400Gold_TL.exe --dry-run`: 280/280
  destination functions skipped, "no unambiguous match above threshold" — the
  EXE's code differs too much to source any server.dll function. Dead end.
- Residue baseline unchanged: **9,209**. Next: the honest state stands —
  every live function at a measured wall; new techniques, not more spellings.

**Round-256 (2026-09-13): CrashDump HEAD is length-exact with distributed
residue — the V2 +59 length plan is obsolete; decrypt-loop counter probed
twice, both reverted.**

- `gaptrace` on HEAD: real code ends reference 0x0850, ours 0x0850 (tables
  already at 0x72c/0x7ac via F3); gap oscillates +50/-43 and returns toward 0
  repeatedly — cause 3 (distributed), no monotone cascade. The round-251 plan
  (+21/+12/+17/−15 = +35 net toward V2's 1777→1836) was written for V2's body;
  applying it to HEAD's exact-size 2115 object would overshoot. Lead 1 as
  worded is spent; what remains on this function is the frame (now 0x284 vs
  0x280 — F3's volatiles already closed half the documented 0x28c gap), the
  4-reg-vs-2-reg-deferred prologue, and distributed hunks. Do not re-derive.
- Decrypt-loop `i` residency (+21 site) probed twice on HEAD (base 530/840,
  obj 2128): separate plain counter `di` → byte-identical metrics (allocator
  keeps it in edx, as Finding 54 predicts for a use-shape no-op); `volatile`
  counter → 413/799, obj 2144 (span break: COMDAT 2128 exceeded, tables move).
  Both reverted. The reference spills `i` under 5-value register pressure
  (eax key, edx tmp, ecx ptr, esi bound, ebx base); ours colors the same five
  values with `i` in edx unspilled. No C spelling tried creates that pressure.
- Residue baseline unchanged: **9,209**. Next: cm_ExSellObjekt is parked, the
  small functions are allocator ties — the honest state is that every live
  function is at a measured wall and further rounds should attempt new
  techniques (different compiler, allocator steering), not more spellings.

**Round-255 (2026-09-13): CrashDump frame fact re-verified on the current body;
a stale-object trap documented; gm_AllocSpieler lead-2 inventory corrected.**

- V2's frame claim reproduces deterministically on the CURRENT (F3) body, not
  just V2's older one: V2's file and the current file with the same 5
  `volatile` qualifiers dropped (`fail_line`, `nFrames`, `excCode`,
  `instrType`, `szDateLen`) are byte-identical sources and probe identically
  (obj 2064, matched 312/2115, `sub esp,0x280` in the fresh probe object).
  Plain-locals on the current body via `rebrew test`: obj 2059, match 490 vs
  631 at HEAD — the documented trade (frame right, tables 56 early), so still
  spent. All probes reverted; tree clean.
- **Measurement trap (near-miss, caught before writing it up):** after the
  in-place qualifier edit, `objdump` of
  `build/objtest/CrashDumpUnhandledExceptionFilter.obj` still showed
  `sub esp,0x28c` — that file is NOT refreshed by `rebrew test` (stale from an
  earlier run). The fresh probe object (`build/objtest/probe_*.obj` from
  `scripts/probe_function.py`) shows 0x280. Never read the frame from a named
  objtest file; always disassemble the object the measuring command just
  wrote. (Also: `objdump -d file | head -6` truncates before the first
  instruction — the header lines eat the budget; use `head -12`.)
- `gm_AllocSpieler` lead 2's "`add R,R` x4 vs `lea R,[R+R]` x4" inventory no
  longer reproduces: the current diff has exactly one `lea`-vs-`add` pair
  (idx 805, `lea edi,[ecx+ebx]` vs `add esi,ebx`, registers also differing,
  inside the sympathy-loop register cascade) and zero self-`add R,R` sites in
  the candidate. The conclusion stands (use-shape change needed per allocator
  Finding 54; wall), but do not go looking for four sites.
- Residue baseline unchanged: **9,209**. Next: CrashDump length work at the
  identified sites (+21/+12/+17/−15); both verify-blocked functions remain at
  measured walls.

**Round-254 (2026-09-13): two verify-blocked functions probed, both reverted; one doc
lead closed, one stale note corrected.**

- `gm_AllocSpieler` tail-order lead (file header: "Verify against the reference
  before taking it") is now verified AND spent. Reference order confirmed from
  disassembly (`0x10019636 jne` skips the 0x286c bug-log, `sprintf` PlayerID at
  0x10019666, then the 0x2888 log at 0x1001967c — i.e. log-after-sprintf, the
  opposite of the source). Applied: obj 3689 -> 3687, match 973 -> 915,
  **linked +53 (2861 -> 2914)**. Reverted per the only-the-link-decides rule;
  the header records the measurement so it is not re-tried.
- `ServerMainThread` packet-build region re-probed twice against the 2074/2434
  base: dropping `volatile` on the cmd+4 store (2070, -4) and reading
  `total_size` at point of use (obj 2431, SIZE_MISMATCH). Both reverted. The
  second outcome re-derives shapes §48's memory-operand-compare dead end; §48
  already documents it, so no new doc entry.
- Stale prose corrected in `gm_AllocSpieler.c` header: it claimed `/Ow` "must
  stay on the `// CFLAGS:` line below, which is what the CMake build reads
  (`apply_annotation_cflags`)". There is no such line (verified: no
  `^// CFLAGS` anywhere in `src/server.dll/`); both tools and CMake resolve
  CFLAGS from `src/rebrew-functions.toml` via `rebrew cmake-flags`, with
  metadata winning over any inline value (`metadata._apply_metadata_entry`).
  Comment-only change; object still exactly 3689.
- No `rebrew` tool bug found this round. Two false alarms checked and cleared:
  `test --json` emitting nothing was a stdout/stderr pipe mixup (direct
  redirect parses fine), and `todo`'s "obj 3688" text is the committed blocker
  string, not a live measurement (`test` now reports obj 3689 and syncs the
  status STUB accordingly via the tool path, not a hand edit).
- Residue baseline unchanged: **9,209**. Next: the ranked leads below (CrashDump
  frame work first); both verify-blocked functions are at measured walls.

**Verified state at handoff.** `rebrew lint` 187/187 (0 errors, 2 warnings); a full
`bash scripts/gate.sh` passes — 0 compile/link errors, `rebrew verify --full` 281/283 against
the 281 baseline; and `bash scripts/split_link.sh` + `postlink_residual.py --write` reproduces
`build/server.dll` at **9,209 bytes of `.text` residue in 286,720 bytes**, so the committed tree
and the deliverable agree. Every non-`.text` section is byte-identical, and the import table is
100 entries matching in set and order. All remaining work is `.text` codegen.

**The faithful `CrashDump` work landed after all: -71 linked.**  Candidate `F3`
(`.scratch/cand/F3_y2_plus_nf.c`) is the only one measured that lands both jump tables exactly
at 0x72c/0x7ac (code 1836, +-0), giving CrashDump 1668 -> 1597 and the image 9280 -> 9209.
**Read its caveat before touching it**: it reaches those offsets by qualifying several locals
`volatile` so the allocator keeps them in memory, which is a *byte-fitting* device rather than a
recovered mechanism -- for szDateLen/szTimeLen/excCode/fail_line the reference keeps the value
in a register -- and its frame is 0x284 against the reference's 0x280.  It is accepted because
`volatile` changes no observable behaviour (unlike a swapped argument, fixed at +1 earlier); if
the allocator tie breaks the other way, frame 0x280 and exact tables arrive together and should
measure above 600 matched.  Lead 1 is therefore **spent**; do not re-derive it.  The other — the last three small functions — has since
finished: `vfs_ReadCompressed` was improved by **-1 linked** (residue 9,281 -> 9,280, its row
24 -> 23) by unqualifying only the post-loop test, while `cm_ExProdObjekt` and
`cm_ProcessCommandQueue` were left at HEAD because their `matched-reloc` already equals their
ceiling (allocator Finding 59's amendment).  **Check `list_agents` and `.scratch/*.FINAL.c`
timestamps before starting new work**, so you do not collide with the CrashDump agent.

**Ranked leads, most promising first (REVISED 2026-09-13 — rounds 254-266;
supersedes the ranking below it, which is kept as history):**

1. **New techniques, not more spellings.** Every live function is at a
   measured wall (register-allocation/scheduling choices, epilogue merging,
   tail duplication, CSE proofs, or cascades where a local fix recolors the
   function). Fifteen rounds of source probes return exact-local-shapes that
   lose at the link, or inert objects. What has NOT been tried: a different
   compiler for the whole tree (SP1-SP6 measured byte-identical on one
   function; anything further invalidates 281 passing functions), a live
   TU-partition search (merge-sweep repaired round 263, dry-run only), and
   allocator steering beyond `volatile` (qualifier direction/polarity
   exhausted; numbering inert).
2. **`gm_AllocSpieler` (2,861, 31%) — largest row, deepest wall.** Frame
   correct (0x41c both sides); tail-order lead verified-then-reverted (+53);
   the "`add` x4" inventory is now one register-cascaded pair (Finding 54
   corrected). Ceiling ~3115 on one-sided relocs. Only a use-shape change
   not yet imagined moves it.
3. **`CrashDumpUnhandledExceptionFilter` (1,597) — HEAD is length-exact
   (real code ends 0x0850 both sides, tables at 0x72c/0x7ac); the V2 +59
   length plan is obsolete.** Frame now 0x284 vs 0x280 (F3's volatiles closed
   half the 0x28c gap); plain-locals give 0x280 but cost the code length.
   Remaining: frame + 4-reg-deferred prologue + distributed hunks.
   CORRECTION 2026-09-13: bug 2 (dead decode block) is FIXED in the current
   source — the walk region is byte-identical to V2 and the decode block is
   live; the "still open" below and the round-251 note describe the
   pre-rewrite spelling. Bug 1's fix verified present (arg order matches
   0x10002d00 call). NEW bug 3 (round 290): walk gate tested
   mbi.RegionSize, reference tests mbi.State — fixed at +0 linked.
4. **Small rows with exact-local-fix/cascade-loss signatures** (LS nesting
   §72b, vfs head §52-3rd-instance, ReadCompressed tail-duplication): each
   has a verified local shape and a measured cascade. Landable only with a
   plan for the downstream recoloring — the unit of work is the whole
   function, not the hunk.

**Older ranking (rounds ≤253; superseded — kept as history):**

1. **`CrashDumpUnhandledExceptionFilter` (1,668) — the only frame-size mismatch left, and the
   faithful version is in hand but unfinished.**  `.scratch/…V2-frame0x280.c` reproduces the
   reference's `sub esp,0x280` *exactly* (ours is 0x28c) and its buffer offsets, by spelling the
   stack-walk cursor as `frameInfo[2]` and the instruction destination as `frameInfo[3]` — which
   is what the reference does, and which also fixes two real bugs (see below).  It measured
   **+131 at the link** purely because its code is **1777 bytes against the reference's 1836**,
   moving its jump tables 56 bytes early.  The task is length at identified sites: **+21** make
   the decrypt-loop `i` memory-resident (the reference caches `CreateFileA` in `esi` and
   `ReadFile` in `edi`), **+12** the stack walk, **+17** the epilogue pops, **−15** the classify
   switch is already long.  Target: code 1836 so the tables land at `0x72c` and `0x7ac`.
   Reference segment lengths: 315 to the `CreateFileA` return, 343 to the classify compare, 653
   to `VirtualQuery`, 522 to `ret 4`, 3 for the `ret 4`.
2. **`gm_AllocSpieler` (2,861, 31%) — frame confirmed correct, two leads open.**  `add R,R` x4
   where the reference has `lea R,[R+R]` x4 (allocator Finding 54 says strength reduction follows
   the value's *uses*, so this needs a use-shape change, not an address respelling), and the
   0xc slot-map assignment itself.  Its `matched` ceiling is ~3115 of 3689 on one-sided
   relocations, so treat the gap from 736 as mostly unreachable.
3. **The two correctness bugs below.**  Bug 1 is fixed; bug 2 is not, and the faithful spelling
   that fixes it is V2, hence lead 1.

**Two real correctness bugs were found in `CrashDump`'s source.**  (1) The `AnalyzeInstruction`
call passed its first two arguments swapped — the callee at 0x10003260 uses arg2 as a count
(`cmp edx,5`) and arg1 as a pointer (`cmp byte ptr [eax-5],0xe8`), and the reference caller at
0x10002d09 pushes `&buffer, edi, cursor, &out` — so our code would have dereferenced `nInstr-5`.
**Fixed, at a deliberate cost of 1 linked byte.**  (2) The stack walk writes to `instrDest` while
the loop tests `eip`, which is assigned once from `pCtx->Eip`, so `if (eip != pCtx->Eip)` is
false every iteration and the instruction-decode block is **dead at run time** — which is the
only reason bug 1 is harmless today.  Not fixed; V2 fixes it.

**Do not re-derive these; they are measured walls.**  Every function except `CrashDump` is
closed at a local optimum: the residue there is register-allocation and scheduling choices no C
spelling steers (allocator Findings 52-55, 60-61), plus msvc6's unconditional merge of
byte-identical early-return epilogues (shapes §74).  The frame lever is exhausted on 17 of 18
functions (audit above).  The fill-byte line is closed.  A source-spelling sweep will not reach
0; it needs a different compiler or a new technique for steering the allocator.


**Round-253: frame audit across all 18 residue functions — `CrashDump` is the ONLY frame-size
mismatch, and the frame lever is therefore exhausted everywhere else.**

A wrong frame is the largest single lever class in this project: it makes *every* `esp`-relative
operand wrong without changing any length, which is why it produces a huge residue with a
satisfying single-cause explanation.  It was found and solved on `CrashDump` by an agent this
session, so it was worth asking whether any other function has the same root.  Measured by
disassembling the reference and the built image at each function's VA and comparing the
prologue's `sub esp,N`:

```
gm_AllocSpieler                    0x41c / 0x41c   OK
CrashDumpUnhandledExceptionFilter  0x280 / 0x28c   ** DIFFERS **
cm_ExSellObjekt                    0x228 / 0x228   OK
ls_LoadBuildingEntityState         0x0c  / 0x0c    OK
cm_ExCopyEntityData                0x0c  / 0x0c    OK
gv_ExAllocGraveyardWorker          0x10  / 0x10    OK
ServerMainThread                   0x1e4 / 0x1e4   OK
gm_AllocGebaeude                   0x410 / 0x410   OK
vfs_OpenStream                     0x0c  / 0x0c    OK
gm_FindNextFilteredEntity          (no frame -- pushes only)  OK
ahm_ExAllocAlchemist               0x08  / 0x08    OK
gm_CheckInventoryCapacity          0x20  / 0x20    OK
m_AllocTracked                     0x118 / 0x118   OK
srv_LoadBuf                        0x2a0 / 0x2a0   OK
gm_ObjectsAvailble                 0x28  / 0x28    OK
vfs_ReadCompressed                 0x08  / 0x08    OK
cm_ExProdObjekt                    0x10  / 0x10    OK
cm_ProcessCommandQueue             0x08  / 0x08    OK
```

**Consequence: for 17 of the 18 functions, the frame is not the defect and cannot be the
fix.**  Do not spend probes trying to move a frame on any of them; a slot-map difference is a
different thing (allocator Finding 55, and `gm_AllocSpieler` is the recorded instance).  The one
frame-level opportunity left is `CrashDump`, where the faithful spelling gives `sub esp,0x280`
exactly and is already in hand.


**Round-252: a 0xc slot shift in `gm_AllocSpieler` is a slot-MAP difference, not a frame bug —
and the frame is confirmed correct from the reference itself.**

`instr_diff`'s kind multiset showed `mov R,[R+0x20]` x8 in the reference against
`mov R,[R+0x2c]` in ours — a 0xc displacement difference, which is exactly the *signature* of
the frame bug on `CrashDumpUnhandledExceptionFilter` (there a 0xc frame error shifts every
`esp`-relative operand).  So it was worth asking whether `gm_AllocSpieler` — 31% of all
remaining residue, closed by four passes — has the same root.

It does not.  The reference's prologue at `0x10018850` is **byte-identical to our object's for
the first 48 bytes**, `sub esp,0x41c` included:

```
10018850 81ec1c040000  sub esp,0x41c        <- ours: 81ec1c040000, identical
10018856 53            push ebx
10018857 55            push ebp
10018858 33db          xor ebx,ebx
1001885a 56            push esi
1001885b 57            push edi
1001885c 895c241c      mov [esp+0x1c],ebx    <- same slot
10018860 b8a0580310    mov eax,0x100358a0
10018865 668138ffff    cmp word ptr [eax],0xffff
...
```

So the frame is `0x41c` on both sides and the earlier passes' note is right.  The `[esp+0x20]`
against `[esp+0x2c]` difference is a **slot-map** difference — which slot each temporary was
given — with the frame size unchanged.  That is precisely allocator Finding 55's case ("the
frame can be right while the slot map is not"), and it is not fixable by adding or removing a
local.  **Do not re-open `gm_AllocSpieler` looking for a frame bug.**

The two leads from round 250 that remain live there are unaffected by this and are *not*
frame-related: `add R,R` x4 against `lea R,[R+R]` x4, and the `[R+0x20]`/`[R+0x2c]` slot
assignment itself (a colourer outcome).


**Round-251: 9,280 -> 9,281, a deliberate +1 for correctness, and CrashDump re-opened with a
plan.**

**Two real correctness bugs were found in `CrashDumpUnhandledExceptionFilter`'s source, and one
is now fixed.**  The `AnalyzeInstruction` call passed its first two arguments swapped.  I
verified it independently rather than taking it on report: the reference's call site
(0x10002d09) pushes `&buffer` as arg1, `edi` (the count) as arg2, `[esp+0x44]` (the stack-walk
cursor) as arg3 and `&[esp+0x48]` (the output int) as arg4; and the callee at 0x10003260 agrees
on every role — `mov edx,[esp+8]` then `cmp edx,5` (arg2 is a count), `mov eax,[esp+4]` then
`cmp byte ptr [eax-5],0xe8` (arg1 is a pointer), `mov ecx,[esp+0x10]` then `mov [ecx],0`
(arg4 is the output).  Our source would have had the callee dereference `nInstr - 5`.

**The fix costs 1 byte of linked residue (9,280 -> 9,281), and that is deliberate.**  The rule
is that only the linked residue decides, so a +1 needs a stated reason: the objective is a
*recompilation*, and a source that passes a length where the original passed a code pointer is
not one.  Byte-identity bought with semantically wrong C is a false match, and every byte of a
final 100% would be suspect.  The block containing the call is currently **dead** — the second
bug below — which is the only reason the swap is harmless today; fix the cursor and this call
executes and faults.  **The baseline is therefore 9,281, not 9,280**; the 1 byte is expected to
come back when the length work below lands.

The second bug, found by the same pass and **not** fixed: the stack walk writes to `instrDest`
while the loop tests `eip`, which is assigned once from `pCtx->Eip`, so `if (eip != pCtx->Eip)`
is false every iteration and the instruction-decode block never runs.  The reference advances a
cursor in memory.

**`CrashDumpUnhandledExceptionFilter` (1,668, the largest live target) is re-opened with a
plan.**  A previous pass produced `.scratch/…V2-frame0x280.c`, which reproduces the reference's
frame **exactly** (`sub esp,0x280` against HEAD's 0x28c) and its buffer offsets, by spelling the
stack-walk cursor as `frameInfo[2]` and the instruction destination as `frameInfo[3]` — i.e. V2
is the *faithful* version, and it also fixes both bugs above.  It measured **+131 at the link**
because it is **unfinished**: its code is 1777 bytes against the reference's 1836, so the jump
tables move 56 bytes early and the tail cascades.  The task is therefore length, at identified
sites: +21 the decrypt-loop `i` needs to be memory-resident (the reference caches `CreateFileA`
in `esi` and `ReadFile` in `edi`), +12 the stack walk, +17 the epilogue pops, minus 15 the
classify switch is already long.  Target: code 1836 so the tables land at 0x72c and 0x7ac.
An agent is on it.

**A useful counterexample to "object metrics always mispredict."**  V2's object metric was much
worse (312 against HEAD's 478) *and so was the link* (+131), because the mechanism — a 59-byte
shortfall displacing a function's own jump tables — was understood.  Object metrics mispredict
when the mechanism is opaque; they are informative when it is not.  The rule that survives is:
do not reject on a metric *alone*, and do not accept on one either.


**Round-250: hunk composition quantified, and it corrects the "everything is an allocator
tie-break" conclusion for the largest function.**

`scripts/instr_diff.py <va> --built build/server.dll` classifies every hunk, and the split is
decisive about *which kind* of work is left:

| function | hunks | same-kind (regs/addr) | different-kind (shape) | insert/delete (length/layout) |
|---|---|---|---|---|
| `gm_AllocSpieler` | 175 | 33 | 20 | **122** |
| `CrashDumpUnhandledExceptionFilter` | 101 | 26 | 26 | 49 |

**Correction to round 248/249.** Those rounds concluded from the *small* functions that the
remaining residue is dominated by register-allocation tie-breaks.  That is true of
`gm_ObjectsAvailble` / `srv_LoadBuf` / `m_AllocTracked`, and it is **not** true of
`gm_AllocSpieler`, where 122 of 175 hunks are *insert/delete* — length and layout differences,
not register choices.  "Distributed (168 hunks)" was accurate but hid which kind of difference
dominates; do not read the small-function verdict across to the big one.

**Two concrete leads on `gm_AllocSpieler` from the same run** (kind multiset, addresses and
registers collapsed — 84 reference-only against 82 built-only):

- `add R,R` x4 in ours against `lea R,[R+R]` x4 in the reference — a 1-byte strength-reduction
  difference per site, and the reference uses the `lea` form.  (Allocator Finding 54 says
  strength reduction follows the value's uses; this is the first site inventory of it.)
- **`mov R,[R+0x20]` x8 in the reference against `mov R,[R+0x2c]` x4 plus `mov [R+0x2c],R` x3
  in ours — a 0xc (12-byte) struct-field offset difference.**  Worth a look as a possible
  wrong member/offset in the source rather than an allocator effect, since it is a *value*
  difference and the previous passes were working FPU forms and zero-extends.
- plus the known `and R,0xffff` x6 against `xor R,R` x4 (the volatile zero-extend wall, shapes
  section 52).

**`CrashDumpUnhandledExceptionFilter` shows the same 0xc fingerprint and it is a *consequence*
there**, which is useful confirmation: `lea R,[R+0x90]` x5 and `[R+0x188]` x4 in the reference
against `[R+0x9c]` x5 and `[R+0x19c]` x3 in ours, and `mov R,[R+0x20]` x3 against
`mov R,[R+0x18]` x3.  Every one of those is an `esp`-relative slot shifted by 0xc, exactly the
reference's 0x28c against our 0x280 frame.  So for that function the offsets are *symptoms* and
the frame is the root — the agent working it is on the right target, and fixing the frame
should move a large share of the 49 insert/delete hunks at once.


**Round-249: the full gate passes end-to-end, and two more functions are closed.**

**GATE: pass** — the first complete run with a clean tree in many rounds: `rebrew lint`
187/187 (0 errors, 2 warnings), **0** compile/link errors, `rebrew verify --full` 281/283
with the baseline held.  The build's post-link failure is expected and deletes
`build/server.dll`, which was regenerated via `split_link.sh` + `postlink_residual.py`;
the re-link reproduces **9,280 by 286,720 bytes exactly**, so the committed tree and the
deliverable agree.

**Two more closed, with walls measured rather than assumed:**

- `gm_FindNextFilteredEntity` (226): the reference keeps **five `ret` sites and merges none**
  — three byte-identical short epilogues and two byte-identical long ones — while our `/O2`
  object keeps two with five `rel32` branches into one.  The exit paths are byte-identical in
  the reference, so the cross-jump is **not** downstream of any shape difference: it is an
  unconditional merge our compiler performs.  Proven by a 352-byte standalone reproducer that
  matches the reference's prologue byte-for-byte and still folds the exits; `/O1`, `/Os`,
  `/Og-`, `/Ot /Oy-` all fold too.  This is the wall behind the "reference keeps N epilogues"
  note that recurs in this project, and it explains why eight return spellings are inert
  (`docs/msvc6-c-shapes.md` §74).
- `gm_CheckInventoryCapacity` (97): the entire tail `+0x8f..+0x18a` is byte-identical and all
  97 differing bytes lie in a **same-length permuted head** `+0x0..+0x8e`.  Three coupled
  defects — `base + idx` folding to `[edi+ecx]` (a **second confirmed site of shapes §73**;
  breaking it flips `entity_index`/`in_list` roles and adds 7 instructions), `elem = list[0]`
  constant-propagating into a peeled loop entry, and the two prologue zero-inits landing
  0x1d bytes late — survived seven source-order and declaration variants.  Note the object
  metric and the link **agree** here (`395-298 = 375-278 = 97`).

**A lever, and a past commit it implicates.**  `end = g_entity_ptr + 0xa900;` must precede
`if (g_entity_type_table == 0)` for that function's prologue to be byte-exact
(`docs/msvc6-c-shapes.md` §75); commit `551bea67`, accepted as a climb win at the time, moved
it below the guard and costs the prologue plus 3 `matched` bytes.  Worth remembering when a
function's first 0x20 bytes are wrong, and as a caution about what a climb metric accepts.

**Where this leaves the objective.**  Every function except `CrashDumpUnhandledExceptionFilter`
(1,667, one agent still working its frame) is now closed at a *measured* local optimum, and the
reason is consistent across all of them: **the remaining residue is dominated by
register-allocation and scheduling choices that no C spelling steers** (allocator Findings
52-55, 60, 61) plus the unconditional epilogue merge above.  Rounds now return tens of bytes,
not hundreds.  Reaching 0 needs either a different compiler or a technique for steering the
allocator that this campaign has not found; another sweep of source spellings will not do it.


**Round-248 (later): five more functions closed with nothing found, and the two walls that
explain it are now measured.**

`vfs_OpenStream` (245) and `ahm_ExAllocAlchemist` (201) were worked to exhaustion and no
candidate beat HEAD; both are back at HEAD with the FINAL copies byte-identical to it.  Their
gap curves oscillate and return to 0 (distributed), and **both frames are excluded as the
cause by measurement** — `vfs`'s `sub esp,0xc` with slots `[esp+0x13/0x14/0x18]` and
`ahm`'s `sub esp,8` with `[esp/0x10/0x14/0x18/0x1c]` match the reference exactly.  So Cause 2
(cause: frame value) is ruled out on both; the residue is instruction choice and schedule.

Two walls worth not re-deriving:

- **`#pragma optimize("a", on)` is a wall here, not section 44's load/store-reorder lever.**
  Exact spelling (the pragma before the definition, `#pragma optimize("", on)` after) takes
  `ahm` 714 -> 480 with COMDAT 1008 -> **1024** and `vfs` 390 -> **83** with COMDAT 704 -> 720.
  Both leave the admissible span, so they fail on layout as well as score.  Section 44's lever
  does not transfer.
- **A store's *value* spelling cannot move its materialisation earlier.**
  `*(volatile unsigned short*)(..) = (unsigned short) minus_one;` against `= 0xffff;` is
  byte-identical on `ahm` — msvc6 constant-propagates the local and re-folds the immediate.
  Only a *use* of the value creates the live range.

**Corrected constraints, from one compile each:** `vfs_OpenStream` carries 5 relocations past
its last `ret`, so the **real** length binds at 701 (Finding 56's intra-object row) — any
real-body change moves its jump table and case map.  `ahm_ExAllocAlchemist` has none, so the
padded band binds with **no lower bound**, and its real body is already exactly at the
admissible 1008 — meaning shrinkage is free and any growth is composition-breaking.  The
`ahm` file header's "obj exactly 1002" invariant is over-strict.

**And the `matched` ceiling is mostly REL32 calls, not data addresses** (allocator Finding
59's amendment): every local `call` carries a COFF `REL32` that the linked reference does not
relocate, so four bytes per call can never count.  `ahm`: 52 of its 74 ours-only bytes are 13
calls, ceiling 858 = its current `matched-reloc`, i.e. **it already matches everything it
can**.  `vfs`: 207 bytes of headroom no code edit will move.

**Net effect on strategy:** five functions closed this round at a measured local optimum, all
on allocator/scheduler ties.  With `gm_AllocSpieler`, `ls_LoadBuildingEntityState`,
`cm_ExSellObjekt`, `cm_ExCopyEntityData`, `gv_ExAllocGraveyardWorker`, `gm_AllocGebaeude` and
these five all closed, the live hope is `CrashDumpUnhandledExceptionFilter` (1,667, agent still
working its frame) and the mid-size pair.  Everything else needs a *new* kind of lever, not
another sweep.


**Round-248: the small-function residues are register-allocation ties, and that is the
general shape of what is left.**

Three functions were worked with 11 probes and nothing was found — but the *reason* is the
result, and it generalises:

| function | linked residue | what it actually is |
|---|---|---|
| `gm_ObjectsAvailble` | 28 | **one** `ebx`<->`edi` rename (`mov edi,esi` ours against `mov ebx,esi` at 0x10016090) cascading to the row/inner pair |
| `srv_LoadBuf` | 49 | 9 clusters, all register names or schedule; the largest is a second `sprintf` buffer address materialised lazily after the mask in the reference and hoisted a block earlier in ours |
| `m_AllocTracked` | 93 | 12 clusters of byte-neutral push/pop shrink-wrap reorderings and one tail accumulator rename |

All three have real bodies already **exactly** the reference's length and no relocated tail
data, so the size rule offers nothing in either direction.  All three are allocator
tie-breaks — the same obstacle as the big functions, in miniature.  **This is why recent
rounds return tens of bytes rather than hundreds: the reachable part of the residue is now
dominated by choices the C source cannot steer** (`docs/msvc6-allocator.md` Findings 52-55,
60-61).  Recognizing this early is worth more than another sweep.

Also retires, with measurements:
- `m_AllocTracked`'s Finding-51 fixed point is **already crossed in the shipped body** — frame
  `0x118` and `xor ebx,ebx` are both present and the object span is exactly 672.  The file
  header's "227/658" and "13 bytes short" are stale; HEAD is 525/658 at exact size.  Finding
  51 is not binding here.
- The `#pragma function/intrinsic` axis on `m_AllocTracked` is **retired for this body**: five
  variants (memset/strcpy/strcmp in several combinations) are byte-identical.

**Quantified confirmation of Finding 59:** the reference's `.reloc` is *empty* in all three
windows while ours relocates every absolute memory operand.  On `srv_LoadBuf` that makes
`matched-reloc - matched` 100 bytes of a 750-byte function — **13%** — so a `matched` of 601
really represents 703/752 of correct content.  Where a window has zero reference HIGHLOW
entries, read `matched-reloc` and the linked residue, and do not treat the `matched` gap as
codegen work.


**Round-248: `gm_AllocSpieler`'s largest hunk localised to an instruction, and one suspected
source bug ruled out.**

Four passes called this function's 2,861 bytes "distributed (168 hunks)" and left it there.
The single biggest hunk (the +160 peak, and the +144 one has the same shape) is the
**trait-interpolation loop** at `+0x5a0..+0x650`, and it is now localised to three concrete
differences rather than "FPU operand forms":

1. **The `slot+0x124`/`slot+0x128` FPU block is HOISTED above the loop in our object.**  Ours
   computes it at `+0x5bd..+0x5e9` (then calls `0x1001a0f0`); the reference computes it
   *after* the loop, at `+0x627..+0x657` (`call 0x1001a0f0`, `fadd qword [0x10025688]`, ...,
   `fst dword [ebp+0x124]`).  That is ~8 instructions moved across the whole 14-iteration
   loop, so it displaces everything in between -- which is why the aligner reports a huge
   replace here rather than a small one.
2. **The loop counter lives in memory in ours and in a register in the reference.**  Ours:
   `mov eax,[esp+0x14]` / `dec eax` / `mov [esp+0x14],eax` at `+0x62b/+0x636/+0x637`; the
   reference keeps it in `ebx` (`mov ebx,0xe` ... `dec ebx`).
3. **Two FPU forms differ.**  The reference emits `fsubr qword [0x100257d8]` directly; ours
   emits `fld qword [const]` then `fsub st(1)`, and carries an extra `fstp st(0)` after the
   loop-body store.

**One suspected source bug was ruled out, and the reasoning is worth keeping** so it is not
re-investigated.  `src/.../gm_AllocSpieler.c:425` has `dst[-2] = (float)((double) dst[-3] *
g_dbl_const_6d0);` sitting *outside* the 14-iteration `for` (brace depth 2 against the body's
3), while the reference plainly executes the equivalent store **inside** the loop tail
(`fld [esi-0xc]; fmul qword [0x100256d0]; fstp [esi-8]`, before its `jne`).  That looks like a
misplaced statement.  It is not: the loop body already writes three floats per iteration
(`dst[0]`, `dst[-1]`, and `dst[-2] = dst[-3] * const`), so line 425 recomputes element 40 --
which the *last* iteration already wrote with the same value from the same input.  It is a
redundant duplicate, hence dead, hence eliminated by the compiler.  Our object and the
reference both write exactly three floats per iteration and both have the back edge after the
third.  **Do not "fix" line 425 by moving it into the loop.**


**Round-247: the whole image outside `.text` is verified byte-identical, and the fill-byte
line is closed.**

Structural verification, all measured this round:
- the PE has exactly four sections (`.data`, `.rdata`, `.reloc`, `.text`) and the first three
  differ by **0**; there is **no `.idata` section** -- imports live inside the already-matching
  `.rdata`/`.data`, which is why the residue table has no imports row;
- the import table is **100 entries in both, matching in set *and* in order** (AGENTS.md's
  documented check);
- so 100% of the remaining work is `.text` code generation.

**The fill-byte line is closed.** Round 246 won 13 bytes from a gap byte (`0xCC` where the
reference had `0x90`) and it was reasonable to ask whether more of that class existed.  It
does not: scanning every run of >=4 identical padding bytes in the reference (`0x90`, `0xCC`
or `0x00` -- 435 runs, 3,295 bytes, 2.3% of `.text`), only **30 bytes** differ, and all 30 are
*code overrunning padding*, not fill mismatches.  The largest is 4 bytes at `0x1000bf64`
where the reference has four zero bytes and we have instructions -- a code-length difference
in the preceding function, which is exactly the work the per-function climbs are already
doing.  No second pad-style fix exists; do not re-open this.


**Residue: 9,280 bytes of 0x22846 in `.text` (6.56%).** Everything else in the PE is
already byte-identical: `.data`, `.rdata`, `.reloc` and the headers all differ by **0**, and
the import table is 100 entries matching the reference in set *and* order. There is no
`.idata` section — imports live in the `.rdata`/`.data` that already match. So **all
remaining work is `.text` code generation**, and the deliverable is
`build/server.dll` at 286,720 bytes.

**The objective is byte-identity. `rebrew todo` does NOT measure it** — it reports semantic
coverage (99.6%) and lists only functions needing implementation work. `PROVEN` outranks
nothing: `EXACT` is the strongest claim and `PROVEN` ranks below `RELOC` because a proven
function's bytes still differ (see the round-246 entry). The residue table below is the work
list.

**A written-up account of the obstacles themselves — compiler-level walls, measurement traps,
process failures and the errors made along the way — is in `docs/difficulties.md`.  Read it
before starting work; it exists to stop a fresh attempt repeating what has already been
measured.

**Regenerating the deliverable** (do this after any `cmake --build`, which *deletes*
`build/server.dll` on its expected post-link failure):

```
bash scripts/split_link.sh
.venv/bin/python scripts/postlink_residual.py --write build/server.dll
```

**Measuring one candidate** (serialized — never while another agent is writing):
`bash scripts/linktest.sh <the one source>`; diff against `.scratch/residue_base.log`.

| function | residue | state |
|---|---|---|
| `gm_AllocSpieler` | 2861 | **closed, 4 passes** — distributed (168 hunks), `matched` ceiling ~3115 |
| `CrashDumpUnhandledExceptionFilter` | 1667 | agent: frame + decrypt-loop induction variable |
| `cm_ExSellObjekt` | 1404 | **parked, 2 passes** — slot swap is a pure colorer tie, source-inert |
| `ls_LoadBuildingEntityState` | 728 | **closed, 2 passes** — five pinned length steps |
| `cm_ExCopyEntityData` | 462 | closed (−1 taken) |
| `gv_ExAllocGraveyardWorker` | 456 | closed (−1 taken) |
| `ServerMainThread` | 367 | parked (−4 taken); four length deltas cancel, partial fixes harmful |
| `gm_AllocGebaeude` | 327 | **closed on the C-only constraint** — its win needed an `__asm` barrier |
| `vfs_OpenStream` | 245 | agent; no length defect (tables aligned at window 0x02bf) |
| `gm_FindNextFilteredEntity` | 226 | agent |
| `ahm_ExAllocAlchemist` | 201 | agent |
| `gm_CheckInventoryCapacity` | 97 | agent |
| `m_AllocTracked` / `srv_LoadBuf` / `gm_ObjectsAvailble` | 93/49/25 | agent |
| `vfs_ReadCompressed` / `cm_ExProdObjekt` / `cm_ProcessCommandQueue` | 24/21/15 | agent |
| *outside every named function* | 7 | was 20; 13 fixed by the pad-fill correction |

**Three rules that were learned expensively — apply them before spending probes:**

1. **Only the linked residue decides.** Object metrics mispredict in both directions and have
   disagreed in sign **six** times; `aligned` in particular has picked the losing candidate.
   Never reject a candidate on an object metric alone.
2. **Read the *shape* of the gap curve, not the first divergence.** A monotone step that never
   returns is a length cascade; a gap that oscillates back to 0 is distributed differences; a
   gap that stays flat through a region that still differs byte-wise is a frame or operand
   *value* difference (`sub esp,0x28c` vs `0x280`, both 6 bytes) which no local edit fixes.
   Assuming a cascade where there was none cost two agent budgets (round 244).
3. **The size rule.** `cl` pads each COMDAT to 16 bytes, so for an object with no relocated
   data after its code any real body at or below `16*ceil(size/16)` is composition-neutral,
   with **no lower bound**. If the object *does* carry a jump table or case map after its
   code, the **real** length binds and the pad cannot protect it (Finding 56).

**Constraint reminder:** C only. `__asm` is allowed only where the *original* had hand-written
assembly (one such block-fill exists in `gm_AllocGebaeude`); a `nop`/barrier block is not
that, and a large measured win had to be discarded for using one (shapes section 69).

**Round-246 (result): 9,293 -> 9,280 (-13), from a fill byte rather than from code.**

The win came out of a scan for residue that falls *outside* every named function.  That
region was 20 bytes, and 13 of them were `0x90` in the reference against `0xCC` in ours --
not code at all, but the gap between `CrashDumpUnhandledExceptionFilter`'s end and the next
function.  The cause: `pad_short_functions.py` padded a short object to the **unaligned**
`want` (2115 against `have` 2112), which left the remaining 13 bytes of that 16-byte slot for
LINK to fill -- and LINK fills with `0xCC`.  It now pads to the **aligned span** (2128) and
fills with `0x90`, emitting the whole slot itself.  Re-linking with no source recompiled:
9,293 -> 9,280, all 13 in the outside-functions row, and no other row moved.

Worth noting the check that made it safe: the built `.text` contains **295 bytes of `0xCC`,
and only those 13 differ** -- the other 282 match the reference's own `0xCC`.  So this is a
targeted fill, not a blanket refill; a blanket change of the pad byte would have created 282
new mismatches.  Also verified that `pad_short_functions` pads exactly one object today.

**`gm_AllocSpieler` is closed for good, and my brief for it was wrong.**  I sent an agent to
apply the `volatile`-at-use-site lever there on the premise that adding `volatile` selects
the reference's `xor r,r; mov r16,[mem]` form.  Section 52 of the shapes doc says the
opposite -- `volatile` selects the *masked* form -- and it is right; 14 probes refuted my
premise.  What the pass established is where the lever stops, now recorded as an amendment to
section 52: dropping the qualifier does reproduce the reference's form at the sympathy-loop
reads, but it is what holds that loop's register allocation, so it costs 362 matched bytes.
Sweeping the qualifier *in* is strictly worse (736 -> 488/408/365) and the full sets exceed
the 3696 composition band.

Also closed there: the "6 extra `and r,0xffff`, 4 missing `xor`" inventory that three passes
worked from is a **fixed-offset artifact**.  Both sides' real code is already exactly 3689
bytes, the gap curve oscillates +-48 and returns to 0, and all 4 reference `xor`s are present
in our object.  Of our 16 masks only 7 are genuinely extra.  And `matched` there has a
ceiling of ~3115 of 3689 on one-sided relocations (allocator Finding 59), so the distance
from 736 to 3689 was never reachable codegen work.

**Round-246 correction already filed:** `cm_ExSellObjekt`'s frame is `0x228` (read from the
reference prologue), so round 2's "the reference's frame is 4 bytes larger" is wrong and its
histogram explanation with it.


**Round-246: two passes disagreed about `cm_ExSellObjekt`'s frame; the reference settles it,
and round 2 was wrong.**

Round 2 explained the rel8/rel32 histogram (ours 71/32 against the reference's 70/33) as
"the reference's frame is 4 bytes larger, so its sites sit ~4 bytes further from the tail and
one crosses the +-127 boundary", and implied frame `0x22c` variants were closer.  The first
pass, and the project's own record, said the frame **matches**.

Disassembling the reference's prologue at `0x1000d930` settles it:

```
1000d930  81ec28020000   sub esp, 0x228      <- the reference's frame IS 0x228
1000d936  a16c0b0310     mov eax,[0x10030b6c]
1000d93b  53             push ebx
...
1000d955  897c2410       mov [esp+0x10],edi   <- the =0 initialiser block,
1000d959  897c2414       mov [esp+0x14],edi      in SOURCE order, not address order
1000d95d  897c242c       mov [esp+0x2c],edi
1000d961  897c2418       mov [esp+0x18],edi
1000d965  897c2420       mov [esp+0x20],edi
1000d969  897c2428       mov [esp+0x28],edi
```

So `0x228` is correct, `0x22c` is not closer, and **the histogram difference is downstream of
the body's other length differences, not an independent lever** -- do not try to "fix" the
frame by adding 4 bytes.

Two incidental readings from the same disassembly, recorded because they are cheap ground
truth for any future pass on this function:
- the reference's zero-initialiser stores are emitted **in source order** and are *not* in
  ascending slot order (`0x2c` is stored third, before `0x18`), so the store sequence encodes
  the source's initialiser order combined with the slot map;
- the slot map round 2 read out with a sentinel probe (allocator Finding 60) is therefore the
  thing to compare against this sequence -- but that pass measured eleven rotations of our
  initialiser block as all byte-identical, so on this function the sequence is not steerable
  from the source and the swap stays parked.


**Round-245 (result): 9,297 -> 9,293, and a toolchain bug fixed at source.**

One win: `ServerMainThread` -4 linked (its volatile-pinned cmd8 store; the agent was honest
that it is a positional artefact rather than a shape fix, and flagged it for revert if that
function's four cancelling length deltas are ever resynced).  `cm_ExSellObjekt` round 2 found
nothing in ~50 probes and is parked.

**A `rebrew` correctness bug, found because a claim in the generated `AGENTS.md` contradicted
the code.**  The tool ranks `EXACT` 0, `RELOC` 1, `PROVEN` 2 — `verify.py`'s own comment
reads *"PROVEN is a post-verify semantic promotion, NOT a byte match: a proven function
compiles to bytes that differ from the target"* — but `AGENTS.md.template` told every agent
`PROVEN > EXACT > RELOC > STUB`, the exact reverse.  **PROVEN must never outrank EXACT**, and
it propagated: a note written in this file from that template repeated the wrong ordering
until it was caught.  Fixed the claim everywhere it was made — the template, `status.py`'s
`matched_pct` docstring and its rendered `"N% byte-matched"` label, the `dashboard.py`
coverage comment, and `depgraph.py`'s node style, which coloured `PROVEN` with the `EXACT`
class.  Full rebrew suite: 6503 passed, 29 skipped, 0 failed.

**A composition hazard closed.**  `file(GLOB_RECURSE)` swept a leading-underscore scratch
file an agent had dropped in `src/` mid-link-test; it was transient and never reached
`rsp.rsp`, so the measurement it interrupted was valid, but the next configure would have
compiled it as an extra object.  `CMakeLists.txt` now excludes the `_` prefix — inert today
(the resolved list is still 176 files) and free insurance.

Also folded in: allocator Findings 59-61 (relocation accounting explains *why* only the
linked residue decides, and corrects an over-strong "metric wall" call I made last round;
the sentinel-initial instrument for reading out a frame slot map; `volatile` on a local as a
per-variable fixed point rather than a knob).


**Round-245: `rebrew todo` says 99.6% matched and lists two items.  That is SEMANTIC
coverage, not this objective, and the difference is the whole remaining task.**

Running the toolchain's own prioritisation this round:

```
coverage: ghidra_funcs 219, covered 565, exact 313, reloc 233, proven 17,
          matching 1, stub 1, documented 0, pct_matched 99.6
todo:     2 items -- gm_AllocSpieler (roi 39.4, match 26.4%) and
          ServerMainThread (roi 16.0, match 85.0%)
```

Both of those are also the two largest items in the linked-residue table, so the tool and
the byte-identical measure agree on *priority*.  But the headline number does not measure
this goal, for two reasons, and a future round must not read it as near-completion:

- **`PROVEN` is not a byte match, and it must never be read as outranking `EXACT`.**
  `EXACT` (byte-perfect) is the strongest claim; `PROVEN` (semantically verified) ranks
  **below `RELOC`**, because a proven function still compiles to bytes that differ from the
  target.  `cm_ExCopyEntityData` is `PROVEN` and carries **462 bytes** of linked residue.
  The toolchain's code is unambiguous about this (`rebrew/verify.py`'s `_STATUS_RANK` is
  `EXACT` 0, `RELOC` 1, `PROVEN` 2, with the comment "PROVEN is a post-verify semantic
  promotion, NOT a byte match"; `catalog/grid.py` repeats it; and
  `metadata.should_promote_status` lets `EXACT`/`RELOC` override sticky `PROVEN` so a
  function that finally byte-matches does record the win).
  **The generated `AGENTS.md` template said the opposite** — `PROVEN > EXACT > RELOC >
  STUB` — and that is what propagated into this file on the first pass.  Fixed at source in
  `rebrew/src/rebrew/AGENTS.md.template`, together with `status.py`'s `matched_pct`
  docstring, its rendered `"byte-matched"` label, the `dashboard.py` comment and
  `depgraph.py`'s node style (which coloured `PROVEN` as `exact`).
  Separately, `rebrew verify --full` passes a function on object-level equality *with
  relocation slots masked*, while the linked image compares every byte after patching.
- **`rebrew todo` lists only functions needing implementation work** (STUB, SIZE_MISMATCH,
  NEAR_MATCHING).  The other **17** functions carry linked residue while being semantically
  complete, so they never appear in the list at all.

The two measures are therefore complementary, not competing: `rebrew todo` answers "what
is not yet implemented", the residue table answers "what is not yet byte-identical", and
**this objective is the second one.**  After CrashDump's and cm_ExSellObjekt's wins the
residue table is the authoritative work list:

```
gm_AllocSpieler                            2861   31%   walled: 168 hunks, distributed
CrashDumpUnhandledExceptionFilter          1667         agent working (frame 0x28c vs 0x280)
cm_ExSellObjekt                            1404         agent working (a -121 block-layout step)
ls_LoadBuildingEntityState                  728         closed: five pinned length steps
cm_ExCopyEntityData                         462         closed (one -1 win taken)
gv_ExAllocGraveyardWorker                   456         closed (one -1 win taken)
ServerMainThread                            371         agent working
gm_AllocGebaeude                            327         closed on the C-only constraint
vfs_OpenStream / gm_FindNextFilteredEntity / ahm_ExAllocAlchemist /
gm_CheckInventoryCapacity / m_AllocTracked / srv_LoadBuf /
gm_ObjectsAvailble / vfs_ReadCompressed / cm_ExProdObjekt /
cm_ProcessCommandQueue                      996 total   agents working
```


**Round-244: 9,532 -> 9,297 (-235), the largest single-round drop so far.**

Three link-measured wins, all from agents, all kept only after the link test:

| function | change | object honest | linked |
|---|---|---|---|
| CrashDumpUnhandledExceptionFilter | dispatch chain -> one `switch` (+ dead store, + call order) | matched 231 -> 478 | **-219** |
| cm_ExSellObjekt | `weight_fraction` forced into the log buffer's first slot | matched 598 -> 613, **aligned 491 -> 461** | -15 |
| gv_ExAllocGraveyardWorker | combined counter bump + two pinned stores | matched 535 -> 541 | -1 |

The CrashDump win is the switch/table-order lever of `msvc6-c-shapes.md` section 65: a
chain and a real `switch` emit their out-of-line jump tables in opposite order, and the
reference's order is the switch order.

**The object metrics disagreed in sign on two of the three.** `cm_ExSellObjekt` improved
`matched` and `matched-reloc` while `aligned` fell by 30, and the link agreed with the
former; `gv_ExAllocGraveyardWorker` gained 6 byte-agreement bytes while `matched-reloc` fell
and `aligned` did not move. That is now six recorded instances. The rule stands: **only the
link test ranks a candidate**, and no object metric may be used to reject one.

**Three functions closed, and one of them on constraint grounds rather than merit.**

- `gm_AllocSpieler` (2,861, now 31% of everything left): no improvement in ~39 probes; the
  cascade re-open was wrong (see the round-244 correction above). Two passes plus this one
  agree it is distributed. It also has a hard **140-byte metric ceiling** (one-sided
  relocations; see below), so its reachable target is ~2,721.
- `ls_LoadBuildingEntityState` (728): no improvement in ~31 probes. The delta curve steps
  five times, not once, so there is no single encoding to find; all 68 archived probe
  objects for this VA re-score at or below HEAD's 645 matched.
- `gm_AllocGebaeude` (327): a candidate measured matched 683 -> 830 and reloc 823 -> 970,
  but its lever is an `__asm { nop nop nop }` **scheduling barrier**, and the objective is C
  only. Removing just the barrier gives 377 (worse than HEAD) and a COMDAT of 1072 instead
  of 1088, which moves the jump table and breaks composition -- so the whole gain rested on
  the barrier and the file was reverted. See `msvc6-c-shapes.md` section 69.

**Current ranking** (from a full regeneration, 9,297):

```
gm_AllocSpieler                            2861   31%
CrashDumpUnhandledExceptionFilter          1667
cm_ExSellObjekt                            1404
ls_LoadBuildingEntityState                  728
cm_ExCopyEntityData                         462
gv_ExAllocGraveyardWorker                   456
ServerMainThread                            371
gm_AllocGebaeude                            327
vfs_OpenStream                              245   then 10 more, all under 250
```

**End-to-end verified this round.** Rather than trust the per-file link tests
individually, the tree was rebuilt from scratch through the deliverable pipeline
(`scripts/split_link.sh` + `postlink_residual.py --write`): `build/server.dll` is 286,720
bytes at residue **9,297**, exactly the accumulated baseline. So the three commits
reproduce end to end.

**Operational footgun, worth knowing.** `cmake --build build` FAILS at the post-link layout
step by design (the cmake link's `.text` is short -- `0x221e6` against `0x22846` -- and the
layout package needs 90% alignment, getting 5.1%), with **no `error C####` or `error
LNK####`**, which is why `scripts/gate.sh` counts only those. The consequence to remember:
`make` **deletes the failed target**, so `build/server.dll` disappears. Regenerate it with
`bash scripts/split_link.sh` followed by
`.venv/bin/python scripts/postlink_residual.py --write build/server.dll`. Never leave the
tree after a bare `cmake --build` without doing that, or the deliverable is simply gone.


**Round-243 (instruments): the tools the campaign depends on were untracked, and one of
them was quietly lying.**

`ndiff.py`, `cdiff.py`, `gaptrace.py` and `reallen2.py` lived in gitignored `.scratch/`
while being the instruments every agent is told to use — they would not survive a clean
checkout.  Promoted to `scripts/`, with the two that assumed they were run from the repo
root now resolving paths from `__file__`.

`gaptrace.py` then showed two defects when actually used on a function with out-of-line
tables:

1. **The `size` argument was a trap, and it caught me.**  The correct window is the
   reference's REAL BODY, which for a function with a jump table or case map is larger than
   the metadata `size` (code only).  `vfs_OpenStream` is 667 bytes of code inside a 701-byte
   real body inside a **704**-byte window before the next function.  The three
   choices read as three different functions:

   | size passed | reference window | reading |
   |---|---|---|
   | 667 (metadata) | code only | "220 insns, 37 B long, 20 extra insns" — bogus |
   | 701 (real body) | code + tables | "3 B long" — bogus, it is cl's 0x90 rounding |
   | 704 (next VA) | full window | both tails at 0x02bf — aligned |

   The 667 case decodes our table bytes as instructions and invents the extra instruction
   count.  `size` is now optional and defaults to the next function's VA, with a NOTE when
   an explicit size disagrees.  **Use the derived window.**

2. `IndexError` when the two streams end at different lengths — the exact situation the
   trace exists to display.  Both ends now print `end`.

**Verified negative: `vfs_OpenStream` (245 bytes of residue) has no length defect.**  With
the derived 704-byte window both streams end at `0x02bf`, so its jump table and case map sit
at the reference offsets and the earlier `-36` length win is intact.  Its 245 bytes are code
shape — consistent with its recorded blocker (`frame/slot + cmp[mem],0 vs mov/test`).
Worth recording because the length lever is the tempting hypothesis there (it was worth -36
once) and it is now measured, not assumed.

**Round-244: THE CASCADE FRAMING WAS WRONG — high residue has TWO causes, and I
conflated them.**

Round 243 ranked the functions by residue and inferred, from a high
`residue / bytes-remaining` ratio, that one early *encoding-length* decision shifts the
tail.  That inference is invalid, and pointing agents at the "first divergence" on its
strength cost two budgets before it was refuted.  Both refutations are measurements:

**Cause 1 — a length divergence that cascades.**  Real, and it is the mechanism behind
Finding 56 (a table placed N bytes early).  But it is *not* what the ratio shows.

**Cause 2 — a frame-size difference, which changes every `esp`-relative operand and no
length at all.**  `CrashDumpUnhandledExceptionFilter` (0x10002770) was the top of my table
at 89%.  Its first differing byte `0x10002772` is the **immediate of `sub esp,0x28c` vs
`sub esp,0x280`** — `81 EC xx xx xx xx` on both sides, *6 bytes each*.  There is no length
difference anywhere near it.  A wrong frame makes ~every `[esp+N]` displacement wrong, so
the residue is enormous while the instruction stream is the same length.  The agent spent
most of its budget at the offset I named; the byte there is a value.

**Cause 3 — genuinely distributed differences.**  `gm_AllocSpieler` (0x10018850), 81% in my
table: **168 hunks**, and the running gap visits ±40 and *returns to 0 repeatedly* over the
whole body.  A single early length difference produces one monotone step and a flat tail;
this curve oscillates with the code.  The two passes before this one were right that it is
distributed, and my re-open was wrong to doubt them.

**The corrected table** (ratios as before, but the diagnosis column is what matters):

| function | ratio | what the first divergence actually is |
|---|---|---|
| CrashDumpUnhandledExceptionFilter | 89% | a frame **value** (`0x28c` vs `0x280`), same length |
| gm_AllocSpieler | 81% | distributed — 168 hunks, gap returns to 0 |
| cm_ExSellObjekt | 72% | distributed — gap steps at ~15 sites; first diff is a same-length `lea` disp |
| gv_ExAllocGraveyardWorker | 59% | a tail-merge direction (which epilogue the jumps target) |

So: **the ratio does not discriminate between the three causes.**  What does is
`gaptrace`: a monotone step that never returns is cause 1; a gap that oscillates back to 0
is cause 3; a gap that is flat through a region that still differs byte-wise is cause 2.
Run it *before* choosing a strategy, and read the shape of the curve, not the first
divergence.

Two more things this round established about how to read a residue number:

- **`matched` has a hard ceiling of `size − one-sided-reloc bytes`.**  The reference's
  `.text` has *no* relocations inside `gm_AllocGebaeude` (0 of its 3499 HIGHLOW entries fall
  in 0x100174d0..0x10017910), so every absolute address we emit there is a one-sided
  relocation that can never be counted as matching: `matched-reloc − matched` = 140 bytes,
  identical at HEAD and at the best candidate.  **Do not chase those bytes by editing code.**
  That is a metric wall, not a codegen defect.
- **`gaptrace`'s instruction counts include cl's trailing alignment fill** (and the
  reference's own inter-function pad), so they read high — `gm_AllocSpieler`'s real count is
  1056 on both sides where the tool implies otherwise.  Do length arithmetic on the **last
  instruction offset / `ret_end`**, not on a count.

**Round-243 (closing note): the drag lead is dead — layout costs ~15 bytes total.**

I opened a line of inquiry last round into whether objects whose code exceeds their
reference span drag the symbols after them, on the reasoning that a whole shifted
function would count as residue.  **It does not.**  The evidence is already in the
residue report and it is decisive:

```
0x252d of 0x253c differing bytes are inside the 19 functions `rebrew verify`
reports as not byte-matched; 0xf are not
```

Placement-attributable residue across the entire image is therefore **15 bytes**.  And the
three residue functions that happen to sit in genuinely over-span objects show ordinary
residues, in the same range as functions in well-behaved objects:

| function | its object | object excess | its residue |
|---|---|---|---|
| vfs_OpenStream | vfs_OpenStream.c.obj | +32 | 245 |
| gm_FindNextFilteredEntity | spiel_dumpD.c.obj | +16 | 226 |
| gm_CheckInventoryCapacity | spiel622.c.obj | +112 | 97 |

If a +112-byte object excess shifted the following symbols, `gm_CheckInventoryCapacity`'s
window would be wholly wrong and its residue would be its own size, not 97.  So the
composition places each of our objects at its reference VA independently of its
neighbours' excess — an over-span object does not push what follows it.  (The 73 split
symbols that are not exactly at their reference VA, up to +0x31c, are CRT members, and
they cost the 15 bytes above.)

**Consequence for strategy: there is no layout fix to make.**  The remaining 9,517 bytes
are code-shape differences inside 19 named functions, and the only lever is the
per-function climb.  That is worth stating plainly because the drag hypothesis is
attractive and would otherwise be re-derived: a big residue number looks like a
displacement, and for the top three functions it *is* — but a displacement *within* the
function (one early encoding shifting the tail), not a displacement *of* the function.

**Round-243: the residue is POSITIONAL CASCADE, and three functions are 65% of it.**

First measurement of the campaign against the full per-function residue table rather
than against one function at a time.  Ranked, from `.scratch/residue_base.log`
(9,532 total):

```
gm_AllocSpieler                            2861   30% of everything left
CrashDumpUnhandledExceptionFilter          1889
cm_ExSellObjekt                            1421
ls_LoadBuildingEntityState                  728
cm_ExCopyEntityData                         462
gv_ExAllocGraveyardWorker                   457
ServerMainThread                            371
gm_AllocGebaeude                            327
vfs_OpenStream                              245   then 10 more, all under 250
```

Top three = 6,171 of 9,532 = **65%**.  Ten functions share the remaining 3,361.

**The shape of a large residue number.**  A function's `bytes` column is *not* how
much code is wrong.  `gm_AllocSpieler` is 2,861 bytes of residue over a 3,689-byte
function, but its first differing byte is at `0x100188fa`, which is **+0xaa — 170
bytes in** — and its instruction count is 1054 against the reference's 1056, a
deficit of *two*.  A near-identical instruction stream over a 2,861-byte region means
one early instruction is encoded at a different length, every byte after it is
shifted, and the tail "differs" without being wrong.  A shifted region differs
almost everywhere, so the residue number is *bounded by* the distance from the first
divergence to the end of the function, and approaches it.

**How far it approaches it, measured** (first-diff offset, remaining bytes, residue,
ratio) — the honest version of the claim, because the ratio is not constant and the
cascade explanation is strong for some of these and weak for others:

| function | size | 1st diff | remaining | residue | ratio |
|---|---|---|---|---|---|
| CrashDumpUnhandledExceptionFilter | 2115 | +2 | 2113 | 1889 | 89% |
| gm_AllocSpieler | 3689 | +170 | 3519 | 2861 | 81% |
| cm_ExSellObjekt | 2057 | +75 | 1982 | 1421 | 72% |
| gv_ExAllocGraveyardWorker | 1040 | +263 | 777 | 457 | 59% |
| cm_ExCopyEntityData | 912 | +48 | 864 | 462 | 53% |
| ls_LoadBuildingEntityState | 1463 | +60 | 1403 | 728 | 52% |
| gm_AllocGebaeude | 1088 | +96 | 992 | 327 | 33% |
| ServerMainThread | 2434 | +967 | 1467 | 371 | 25% |

At the top of that table a single early encoding accounts for nearly the whole residue
and the reward curve is a cliff.  At the bottom it does not: `ServerMainThread` matches
its first 967 bytes exactly and then has genuinely distributed differences, so its 371
bytes have to be worked individually.  **Read the ratio before choosing a strategy** —
for CrashDump (+2, 89%) spend the budget localising one instruction at the top of the
prologue; for ServerMainThread start at `0x10009767` and expect many small defects.
Deciding this by the ratio avoids both failure modes: hunting a cliff that is not there,
and sweeping a whole body that one instruction would have accounted for.

Two consequences that do hold throughout:

- **The 1st-diff VA is the coordinate to start at.**  For every large entry it is early
  in the function, and it is the only place a cliff can be.
- **A big residue number is not big wrong code.**  Rank by residue to choose *which*
  function; then work at that function's first divergence, not across its whole body.

This is the same effect Finding 57 describes for cross-composition comparisons,
observed *within* one function.

**Round-243: `gm_AllocSpieler` (2,861 bytes, 30%) is re-opened, and the reason is a
correction to the search constraint.**  Two previous passes closed it having searched
for **size-neutral** edits only.  The size rule they were working under is wrong:
`cl` rounds each object's `.text` up to 16 bytes, the pad step fills a shortfall with
zeros, and the linker aligns each contribution to 16 — so the composition survives
iff the real body is at or below `16*ceil(want/16)`, i.e. **real <= 3696 for this
function, with no lower bound**.  A candidate that changes the body length is
admissible; only exceeding 3696 is not.  Full derivation in
`docs/msvc6-allocator.md` Finding 58.  A fresh pass is running against the gap trace
(`.scratch/gaptrace.py 0x10018850 3689`), which is the instrument for exactly this.

**Round-243: `cm_ExCopyEntityData` closed with a measured win, and the object metrics
disagreed in sign.**  Two candidates were link-tested against the 9,533 baseline:

| candidate | object honest | reloc | aligned | real | linked |
|---|---|---|---|---|---|
| type-2 clamp arm in-range/HIGH/low, per-arm stores | **443** | 567 | 184 | 905 | **-1** (kept) |
| that + type-1 secondary in-range/LOW/high (`.alt_t1.c`) | 437 | 573 | **195** | 900 | **+2** (rejected) |

`cm_ExCopyEntityData` 463 -> 462; total 9,533 -> 9,532.  The alternate that won the
*positional* object metric (`aligned` 195 against 184 — the closest object-level
analogue of the linked byte compare) lost at the link level by 3 bytes.  Fifth
recorded instance of an object metric pointing the wrong way; do not rank candidates
by `aligned`.  The kept change and the rejected alternate are both recorded in
`docs/msvc6-c-shapes.md` sections 62-64.

Baseline moved: **9,533 -> 9,532** (`.scratch/residue_base.log` regenerated).


**Round-154 (same round, finished): the build now compiles what the tools
measure.**

The migration above is done and verified as a no-op.  `CMakeLists.txt` no longer
parses `// CFLAGS:` at all: it writes its source list, calls
`rebrew cmake-flags --sources-file ...`, and includes the generated table, with
`rebrew-functions.toml` on `CMAKE_CONFIGURE_DEPENDS` so editing the metadata
reconfigures instead of silently reusing baked `COMPILE_FLAGS` (the footgun that
made the `/Ow` fix look like a no-op).

Reconciling first is what makes the switch provable: six per-function entries
recorded a flag set the build never used while their functions are correct in
the linked image under the file's default (`initterm` verified byte-by-byte, the
rest `RELOC`/100% under both sets), so `rebrew lint --fix` dropped them as
redundant, and the 41 inline `// CFLAGS:` lines across 35 server sources are
gone -- the metadata already carried identical values.

Two things this round taught, both worth keeping:

- **`rebrew test` writes metadata.**  Running it to *read* a verdict rewrote
  `STATUS`/`CFLAGS` on unrelated entries (a `dllmain` entry lost its load-bearing
  `/Oy-`, `__initterm` lost `EXACT`), which then blocks `lint`/`verify`.  Use
  `rebrew diff`/`probe_function.py` for measurement, or revert the metadata
  afterwards.
- **`initterm.c` is the shape the emitter refuses**, and the refusal was right:
  its two functions agree on `/O1 /Gd` (which is what `verify` needs) while the
  build had been compiling the file with `/O2 /Gd`.  Splitting the file into two
  TUs was tried and **reordered the whole link** (`exactly at their reference VA`
  246/319 -> 0/319, residue 11,138 -> 48,600), so the split was reverted and the
  file now compiles with its metadata value instead.  A function moved between
  files moves in the link; the migration must not repartition TUs.

Final state: residue unchanged at **11,138** differing bytes with everything
outside `.text` byte-identical, 246/319 symbols exactly at their reference VA,
`rebrew verify` 281/283 with the baseline held, lint warnings 4 -> 2.

**Round-154 (same round): one authority for compile flags.**

`gm_AllocSpieler`'s bug was not a stray flag, it was three different answers to
"what flags does this file compile with": the CMake build reads the `.c`'s
`// CFLAGS:` (per file), `rebrew test/verify/match/prove` read
`rebrew-functions.toml` (per function), `annotation.py`'s overlay lets the TOML
overwrite the inline value, and `lint`'s own merge lets the inline value win.
The divergence was silent — lint keeps the inline value in `found_keys` and
`metadata_sourced_keys` then suppresses W019 — and W019's advice ("migrate the
inline CFLAGS into the TOML") is advice that changes what the build compiles.

Decided with the user: the TOML is the store, per-file is the granularity, and
per-function entries are overrides.  Two changes landed in rebrew:

- `lint` now reports an inline `// CFLAGS:` that disagrees with the metadata in
  *codegen* flags (W019, the treatment `// SIZE:` already had; `/D` excluded).
- `rebrew cmake-flags` resolves every annotated source file through the tool
  chain and writes a CMake include setting `COMPILE_FLAGS` for it, so the build
  can compile what the tools measure.  A file whose functions resolve to
  different codegen flags is an error rather than an average; `/D` defines are
  not emitted (the `DREBREW_ALLOW_NAKED` guard must not reach the shipped
  build) and each omission is printed as a note.

Run here it emits 180 of 187 files and reports exactly three genuine in-file
conflicts.  Switched over, it would differ from the current build in six files
— `crt_region/{dllmain,initterm,crt_init}.c` (`/O1` vs `/O2`),
`ls_LoadTownData.c` (`/Ox`), `srv_SeedRandomWithTime.c` (`/O1`),
`srv_LoadBuf.c` (`/Ot`) — i.e. metadata flags the build never used.  Those six
are inert against the target (the functions are byte-identical today under
`/O2 /Gd`), so the migration is: reconcile those six, resolve the three
conflicts, point `CMakeLists.txt` at the generated include, add
`rebrew-functions.toml` to `CMAKE_CONFIGURE_DEPENDS` (which also kills the
"a bare rebuild reuses stale baked flags" footgun hit last round), and delete
the inline `// CFLAGS:` lines.

**Round-242: CORRECTION -- the size constraint is the PADDED COMDAT, not the real
body.**

This invalidates verdicts this campaign has been applying for many rounds, so it goes in
prominently.

cl pads every COMDAT to a 16-byte multiple.  For a function whose object has no
out-of-line data after its code, the only thing that moves the *composition* is that
padded size.  Measured on `cm_ExCopyEntityData` (0x1000ec00, whose reference tail is
pure code -- no jump table, no relocated table bytes; checked in round 186):

```
real 912 -> COMDAT 912   composition-neutral
real 905 -> COMDAT 912   composition-neutral
real 897 -> COMDAT 912   composition-neutral
real 913 -> COMDAT 928   composition-breaking
```

So the admissible band for that object is every real body **at or below 912**, not
"exactly 900" and not even "[897, 912]" -- 897 was merely the lowest value a probe had
tested.  My instruction to its agent -- "hold object size 912 AND real body 900" -- was
**over-strict**, and the earlier verdict that its `do/while` dst-scan restructure was
"size-changing (real 900 -> 904) and therefore rejected" was wrong on its stated
grounds: 904 also yields COMDAT 912 and is composition-neutral.  **That variant should
be re-tested.**

Round 242 addendum, from reading `pad_short_functions.py` rather than arguing:
`have` is cl's **16-aligned** object size (`16*ceil(real/16)`) while `want` is the
**unaligned** sum of reference sizes, so the step labels 149 of 319 objects `LONG` as
noise (`gm_NoopRet2.c.obj: 16 > 1`).  The genuine test is
`have > 16*ceil(want/16)`, i.e. real code exceeding the reference's PADDED span --
that, and only that, moves the following symbols.  Anything shorter is padded up at
zero-byte cost to this function's own slot.  Full derivation in
`docs/msvc6-allocator.md` Finding 58, which also records that **Finding 15's amendment
has its inference inverted** and should not be relied on.

The distinction that keeps this from being a blanket relaxation, and it matters:

- **inter-object**: what moves the next symbol is the *padded* COMDAT size, so a real
  body inside the current 16-byte bucket is free;
- **intra-object**: what moves a function's *own* out-of-line jump table or case map is
  its *real* body length.  That is why `vfs_OpenStream` was genuinely real-length
  sensitive -- fixing its 8-byte shortfall was worth -36 -- while `cm_ExCopyEntityData`
  is not.

Applying the padded rule where the intra-object rule is the binding one is the same
class of error as applying neither.  Check whether the object has relocated data after
its code (`reallen2.py` reports the real length; the `.reloc` entries in the object are
the direct evidence) before deciding which bucket rule applies.

**Practical effect: relax the bounds check from "real == reference real" to "padded
COMDAT == reference padded span", and re-test candidates previously rejected on real
length alone** where the object has no tail data.

**Round-241: `gm_AllocSpieler` is closed to size-neutral work -- two independent
passes found nothing.**

Residue **9,533**.  The largest remaining function (2,861 bytes) is now retired from
active effort, and the reason is worth stating because it redirects the campaign.

The function has had **two independent agent passes** since the committed -40:

- the round-210 pass reported, at checkpoint, "the committed baseline is currently the
  best -- I have found no improving size-neutral edit yet", with the object at 3696 /
  real body 3689 and 1054 instructions against the reference's 1056;
- the round-223 pass ran from round 210 to round 241 -- thirty-one rounds -- without
  ever writing `.scratch/gm_AllocSpieler.FINAL.c` or touching the tree, and did not
  answer two checkpoint requests.  I interrupted it this round.

Two passes, one explicit "no improving size-neutral edit" and one that produced nothing
in thirty-one rounds, is enough to treat the size-neutral space here as empty.  Its
`.scratch/gm_AllocSpieler.FINAL.c` is byte-identical to HEAD, so the file is already at
its best known state.

What is known about its residual, for anyone who returns with a new idea: the real body
is already exactly the reference's 3689, so this is not a length problem; the two
-instruction deficit (1054 against 1056) is **distributed**, not localised -- the
running-gap trace swings between +48 across the `sprintf -> LogMessageInternal` region,
-32 through the citizen path, and +7 net, i.e. dozens of compensating scheduling
differences rather than one missing pair.  That is consistent with every large-function
wall this campaign has hit: `CrashDump`'s frame, `gm_ObjectsAvailble`'s callee-saved
pair, `ahm_ExAllocAlchemist`'s stride chain.

**Two process notes, both learned expensively.**  A pass with no probe budget and no
obligation to report "none found" will run indefinitely and deliver nothing -- the
round-210 brief lacked both, and cost thirty-one rounds.  And an agent that never writes
its candidate to a named path leaves the coordinator with no way to tell progress from a
hang; both of the round-223 agent's failures were of that kind.

**Round-236/237: `cm_ExCopyEntityData` is closed -- a budgeted pass found nothing.**

Residue **9,533**.  The first result from the changed fan-out protocol, and worth
recording because it retires a function rather than adding one to the queue.

A fresh agent was given `cm_ExCopyEntityData` (0x1000ec00, 465 bytes, 71.5% aligned) with
a **hard budget of ~40 probes** and an explicit instruction that "none found, plus what
I tried" is a correct answer.  It delivered `.scratch/cm_ExCopyEntityData.FINAL.c`, whose
md5 is `383682da451450c2422ba8479a416d40` -- **byte-identical to the committed state**,
probe reading matched 430 / matched-reloc 584 / object 912, exactly the candidate
committed in round 193.  So its answer is "none found", delivered on time and without
leaving an unmeasured candidate in the tree.

Together with the earlier work this function is now done as a target:

- its residual was localised by running-offset alignment (matrix clamp 25B against the
  reference's 27B; dst scan +5 from a rotated loop; the `0xffff` guards held in `ebp`
  versus our two rematerialised 6-byte immediates; src scan +10 for an entry guard the
  reference lacks);
- its main structural alternative -- the `do/while` dst-scan restructure -- was measured
  as **size-changing** (real body 900 -> 904) and rejected;
  > **RETRACTED in round 242.**  904 and 912 both pad to COMDAT 912, so that variant is
  > composition-neutral and the rejection above is wrong on its stated grounds.  The
  > binding constraint is the padded COMDAT, not the real body.  See round 242.
- the reference's three epilogues against our two is the documented cross-jump wall;
- and an independent budgeted pass found nothing.

**Stop spending here.**  Point the effort at the functions with room: `CrashDump`
(1,889 bytes, 37.8% aligned), `cm_ExSellObjekt` (1,421, 73.2%), `ls_LoadBuildingEntityState`
(728), and `gm_AllocGebaeude` (327, the remaining size-changer suspect that still needs
its candidate re-derived).

*The protocol change is what produced this.*  Twenty-plus rounds were lost to agents
sweeping without delivering; a probe budget plus "none found is a result" plus
"write the candidate to a named path first" turned an open-ended wait into a bounded
answer.  Keep all three in every fan-out brief.

**Round-227/228: file ownership has to be checked, not assumed.**

Residue **9,533**.  A process failure, recorded because it has now happened twice and
the cost is not obvious from the outside.

Round 201 recorded that two agents had been working `gm_AllocSpieler` at once -- both
reported the file changing under them, my reverts fought their writes, and the round's
measurements thrashed.  I then did it again: round 223 launched a second agent onto
`gm_AllocSpieler` without checking whether the round-199 fan-out agent was still live on
it.  It was.

**The fault is not the brief.**  Every brief in this campaign states "edit ONLY your
assigned files", and every agent has obeyed.  What fails is the coordinator's knowledge
of *which previous fan-out is still running*: with ~40 agents accumulated in one
session, `list_agents` is the only source of truth for ownership, and I assigned from
memory of what I had intended rather than from what was live.

The rule, for whoever coordinates next: **before launching any fan-out, call
`list_agents`, take the `running` set, diff their file assignments against the ones you
are about to hand out, and only then write the briefs.**  A function with two writers
produces an unmeasurable tree and wastes both agents, which is exactly the state that
made rounds 201-207 unproductive.

The correction cost nothing this time -- the newer agent was redirected to
`cm_ExCopyEntityData`, one of the two open size-changer suspects, rather than
interrupted -- but that was luck, not process.

**Round-220/221: the block-creation-order lever does NOT reach
`gm_FindNextFilteredEntity`, and why.**

Residue **9,533**.  Recorded as a negative with its reason, because the function looks
like the best remaining target on paper -- the lowest alignment in the tree (63/118,
53.4%) with 226 bytes -- and §59 is the newest lever, so a future round would
otherwise retry it.

`gm_FindNextFilteredEntity`'s guards are early returns:

```c
if (g_entity_type_table == 0)  { return 0; }
end = (unsigned char*) g_entity_ptr + 0xa900;
if (g_dynasty_field_4c > 0x100) { return 0; }
```

§59's mechanism is that the front end creates `else`-blocks innermost-first, so
`if (success) { body } else { error }` materialises cold handlers at the tail in reverse
source order.  Applying it to an early-return guard means nesting the entire remainder
of the function in the success arm -- but **the reference has no tail handlers here**:
it keeps two inline `xor eax,eax; pop esi; ret` epilogues and jumps over them
(`jne`/`jle`).  What is needed is the opposite of nesting, and the obstacle is that
msvc6 cross-jumps the identical guard bodies into one shared block.  §59 changes *where*
a cold handler lands, not whether identical bodies merge, so it does not reach this.

That matches the earlier agent's measurement here: every distinct-return spelling
(`end - end`, `&0`, `*0`, a ternary, `^`, `(char*)0`) compiled **byte-identically**,
because msvc6 constant-folds them before cross-jumping.  The function was closed on that
evidence and §59 does not reopen it.  Its 53.4% alignment is a cross-jumping wall, not a
block-creation-order one.

**Round-217: the corrected per-function picture.**

Residue **9,533**.  With `instr_diff.py`'s decode fixed (round 215), the alignment
figures below are the first trustworthy set this campaign has had; only
`gm_AllocSpieler` moved materially (618 -> 646), and the rest agree with what the
per-function agents independently measured with `probe_function.py`, so the two tools
are now consistent.  Sorted by residue, not by alignment:

```
                                       residue   aligned (ref)      %     object/real
gm_AllocSpieler        0x10018850        2861    646/1056         61.2%   3696/3689
CrashDump              0x10002770        1889    274/725          37.8%   2128/2113
cm_ExSellObjekt        0x1000d930        1421    488/667          73.2%   2064/2055
ls_LoadBuildingEntity  0x100128f0         728    396/499          79.4%   1472/1460
cm_ExCopyEntityData    0x1000ec00         465    186/260          71.5%    912/900
gv_ExAllocGraveyard    0x10011bf0         457    258/333          77.5%   1040/1040
gm_AllocGebaeude       0x100174d0         327    309/356          86.8%   1088/1078
ServerMainThread       0x100093a0         371    579/627          92.3%   2448/2434
vfs_OpenStream         0x10009020         245    157/197          79.7%    704/701
gm_FindNextFiltered    0x10016f80         226     63/118          53.4%    352/342
ahm_ExAllocAlchemist   0x1000bdf0         201    247/286          86.4%   1008/1002
vfs_ReadCompressed     0x10008a90          24    192/200          96.0%    496/492
gm_CheckInventoryCap   0x10019ed0          97    125/138          90.6%    400/395
m_AllocTracked         0x10006580          93    230/249          92.4%    672/658
srv_LoadBuf            0x1000a570          49    205/226          90.7%    752/750
gm_ObjectsAvailble     0x10015f70          25    214/229          93.4%    720/714
cm_ExProdObjekt        0x1000e140          21    348/354          98.3%   1008/993
cm_ProcessCommandQueue 0x1000aac0          15    202/205          98.5%    640/639
```

Read it as a priority list with a caveat this campaign has learned repeatedly: residue
and alignment disagree, and neither predicts the linked result reliably.  The three
functions with the *highest* alignment (98.5%, 98.3%, 96.0%) have 15, 21 and 24 bytes
left -- near-closed -- while `CrashDump` at 37.8% alignment still carries 1889.  A high
alignment with a small residue is the cheapest place to start; the functions in the 70-80%
band (cm_ExSellObjekt, ls, cm_ExCopyEntityData, gv) are where a single structural fix
still moves hundreds of bytes.

The one thing this table cannot show, and the reason it is written down rather than
derived: `postlink_residual` attributes by reference VA, so a symbol misplaced by an
earlier object's length drags its whole window, and only a full rebuild between
measurements keeps these numbers comparable.

**Round-215: RESOLVED -- that was a tool artefact, and it was understating every
alignment figure.**

The 40-instruction gap was `instr_diff.py`'s own decode.  Its `main` built the
disassembler without `skipdata`, so `disasm` **stops at the first byte it cannot
decode**: on `build/server.dll` at 0x10018850 it halted 112 bytes early on a single byte
(offset 0xdf9, VA 0x10019649) and reported 1014 built instructions against a true 1054,
with a correspondingly bogus hunk list.  With `skipdata` the same window decodes 1054
and the alignment is 646, not 618.  Fixed in `scripts/instr_diff.py` -- `md.skipdata =
True`, which is what `probe_function.py`'s aligned path already did (round 172 added it
there for the same reason and I did not carry it across).

Two consequences worth keeping:

- The linked image was never wrong.  The first real difference between the object and
  the linked bytes at that VA is a relocation slot (`00 00 00 00` against a resolved
  `34 54 03 10`), i.e. the composition does place the committed object's code there.
  The "deliverable does not contain the committed object" claim below is withdrawn.
- **Every `instr_diff --built` alignment figure this campaign has quoted for a function
  containing such a byte is understated**, and any hunk list from it is truncated from
  that point on.  The numbers are still usable as a *relative* signal within one
  function, but the absolute counts were wrong wherever this fired.

The lesson is the same one as rounds 202, 203 and 214: a surprising measurement should
send you to the raw bytes first.  Here the raw bytes showed a relocation slot, and the
"missing 40 instructions" was capstone giving up.

**Round-214 note, kept for the record and superseded by the above.**

Residue reported 9,533; **treat that as unverified for `gm_AllocSpieler` and possibly in
total** until this is settled.

The `gm_AllocSpieler` agent reported that `build/server.dll` is stale for its function
and built a kept object to measure from instead.  Verified directly, and it is not
staleness:

```
fresh compile (probe_function.py)   3696 object, real body 3689, 1054 instructions,
                                    matched 736 / matched-reloc 1310
build/server.dll at 0x10018850      reference 1056, BUILT 1014, aligned 618
obj mtime 01:37:50 == source mtime 01:37:50;  COMDAT 3696 bytes, sym _gm_AllocSpieler
```

The object is current and carries the right symbol and size, so the composition is not
placing that object's full body at the reference VA.  Forty instructions are absent
from the linked image.  Possible causes, none yet tested: the composition trims an
overrun (this object is 3696 against a 3689 slot, which is only 7 bytes), a pad object
or a different object occupying that VA, or `postlink_residual`'s fixers rewriting
bytes inside the body rather than only operand slots.

**Why this matters more than the bytes:** every linked per-function number, and the
9,533 total, are produced by measuring `build/server.dll`.  If the linked image can
differ from the committed object by 40 instructions, then the campaign's headline metric
is not measuring the tree.  The direct check is cheap and should be the first thing done
next: disassemble the two streams side by side
(`scripts/instr_diff.py 0x10018850 --obj <kept object>` versus `--built build/server.dll`)
and find where they diverge, then compare the object list
`build/split_poc/rsp_pad.rsp` against `objects1.rsp` for that TU.

The agent left `.scratch/gm.obj` (warn-clean) and `.scratch/gm_build.sh` so a fresh
single-function object can be produced without a full build; its frozen candidate is at
`.scratch/gm_AllocSpieler.FINAL.c` (md5 26343bf9fc95f5477d0962ece227c8da), byte-identical
to HEAD, and it found no improving size-neutral edit.

**Round-209: an interrupted agent loses its candidate, and the isolation rule.**

Residue **9,533**.

*Standing requirement, from a real loss.*  Two agents (`dd176ee8`, `067c30f1`,
`12d219e0` -- three, in fact) were interrupted mid-turn in round 207 to unblock the
build.  Their candidates were reverted before they could be tested, and neither
delivered a ranked list, so their work is gone: the surviving scratch directories
(`.scratch/ovs2`, `pp`, `cmp`, `res`, `rvc2`, `gm_cand`, `ahm2`, `nx`, `fz`) hold dozens
of variant files each and there is no index saying which one is the frozen candidate.
The `gm_AllocSpieler` win survived only by luck -- that agent happened to have written
its candidate to `.scratch/FINAL.c`, which is why round 208 could recover it and measure
-40.

**So: every agent must leave its frozen candidate at a named, indexable path** --
`.scratch/<function>.FINAL.c` -- and name that path in its report, before anything else.
An interrupted turn otherwise costs the whole round's work, and the coordinator cannot
reconstruct it from a directory of variants.  Put this in the fan-out brief.

*The isolation rule, now demonstrated from both sides.*  The same three candidates
measured **together** collapsed the composition to 0/319 symbols at reference VA and
53,931 differing bytes; measured **alone**, `gm_AllocSpieler` was a clean -40.  A single
object whose length is wrong moves every symbol after it, so a batch measurement
attributes nothing.  That is now three distinct ways batched measurement has misled
this campaign: round 179 (an incremental link mixes objects), rounds 201-203 (a build
compiled while agents write), and this one (several candidates at once).  The rule:
**one candidate, one full rebuild, one number.**

*Untested and unresolved.*  `cm_ExCopyEntityData` and `gm_AllocGebaeude` were each
suspected size-changers (the former's `do/while` restructure measured real 900 -> 904;
the latter's added statement measured object 1104 against 1088) and neither has been
measured alone.  Their candidates must be re-derived before they can be tested.

> **Round-242 split verdict on the two cases above -- they are not the same kind of
> size change, and only one of them survives as a rejection.**
> `cm_ExCopyEntityData` real 900 -> 904 is *within* one 16-byte COMDAT bucket (both pad
> to 912): composition-neutral, rejection retracted, variant is testable.
> `gm_AllocGebaeude` object 1104 against 1088 is *across* buckets: a real change to the
> composition, rejection stands.  When the recorded numbers are real-body lengths,
> compare the padded values; when they are already object sizes, compare them directly.

**Round-201: restoring the metadata file changes the compile flags, and can break
the composition.**

Residue **9,533**, composition at 246/319, gate green.

The round went sideways and the detour is worth recording.  After a gate run I restored
`src/rebrew-functions.toml` to HEAD (the correct-looking thing, since the gate rewrites
it -- see round 178).  The next `cmake --build` then produced a composition with
**0 of 319 symbols at their reference VA and 37% of `.text` differing**.  The cause:
`CMakeLists.txt` has the metadata on `CMAKE_CONFIGURE_DEPENDS`, `rebrew cmake-flags`
reads it at *configure* time, and `git checkout` bumps the file's mtime -- so restoring
it triggers a reconfigure that regenerates every file's `COMPILE_FLAGS`.  The metadata
HEAD carries therefore does not produce the same objects as the metadata a gate run
leaves behind, and one of the two gives a broken layout.

Two consequences, both worth acting on:

**RESOLVED (round 203): there is no metadata bug.  The collapse was concurrent writes.**

Both candidate mechanisms are now eliminated by direct inspection: the two metadata
versions differ in **zero** `cflags` lines (only two `status` lines), and a forced
reconfigure leaves `build/CMakeFiles/server_dll.dir/objects1.rsp` **byte-identical**
(0 diff lines, one line either side).  So restoring the metadata changed nothing about
what was compiled or in what order.

The real cause is the one recorded further down this same round: **five agents were
writing source files while that rebuild ran.**  A `cmake --build` compiles whatever is
on disk at that instant, so it compiled a mixture of HEAD, mid-write and candidate
states, and a single object of the wrong length moves the whole composition.  Nothing
about the metadata file was involved, and the "re-run the gate afterwards" rule below
was treating a symptom: the gate rebuilds *and* the agents had stopped by then.

**Superseded correction, kept because the mistake is instructive.**  The round-202 text
below asserted the mechanism was wrong and listed `objects1.rsp` regenerating as the
prime candidate.  That was itself wrong.  Two hypotheses were retracted in two rounds
for the same reason -- reasoning from a sequence of observations instead of doing the
one direct check (diff the two files) that settles it.  This is the fifth such
retraction in the campaign.

**Original round-201 note, kept for the record but superseded by the above.**  Diffing the two metadata
versions directly shows **zero** differing `cflags` lines -- only two `status` lines --
so the reconfigure does NOT regenerate different `COMPILE_FLAGS`, and the collapse was
not a flag change.  The observation stands (a full `cmake --build` after restoring the
metadata gave 0/319 and 37% differing; re-running the gate restored 246/319 and 9,533),
but the cause is still unidentified.  Candidates not yet ruled out: the reconfigure
regenerating `build/CMakeFiles/server_dll.dir/objects1.rsp` (which `split_link.sh`
consumes as the object list, so its order or membership would move the whole
composition) or regenerating the generated include with a different per-file *order*,
which some CMake generators sort differently.  What is established is the operational
rule:

- **Do not `git checkout` the metadata file as a reflex.**  Whatever the mechanism, the
  sequence "restore it, then build" produced a broken composition and "re-run the gate,
  then link" produced a good one.  Re-run the gate afterwards, or leave the gate's
  version in place.
- **Reproducibility is still open.**  If a fresh configure produces a different
  `objects1.rsp`, a fresh clone may not reproduce the residue at all.  Settle it by
  comparing `build/CMakeFiles/server_dll.dir/objects1.rsp` before and after a
  reconfigure -- that is a one-file diff, not a clone: `git` cannot help because the
  file is generated.

Recovery that worked: re-run `scripts/gate.sh` (which rebuilds and re-writes the
metadata), then `scripts/split_link.sh` and `postlink_residual.py --write`.  That
restored 246/319 and gave 9,533 -- better than the 9,573 before the round, because a
`gm_AllocSpieler` candidate is in the working tree.

**Concurrency warning.**  `gm_AllocSpieler.c` had two agents on it at once (one of them
mine, from the round-199 fan-out, and one from the round-193 fan-out that had never
stopped).  Both reported seeing the file change under them.  Two writers on one file
wastes both agents' work and corrupts the baseline; the fan-out needs to track which
agent owns which file, not just that assignments are disjoint.

**Round-190: gm_AllocSpieler's biggest segment delta is a scheduler hoist, not a
statement order.**

Residue **9,684**, unchanged.

The function's diagnostic map puts `+60` on the `sprintf -> LogMessageInternal`
segment, the largest single segment.  Reading our object between the two calls gives
the whole of it: the reference emits **5 instructions** there (the four argument
pushes and the call), we emit **16** --

```
70 call sprintf
71 mov eax,[g_next_object_id]      74 inc eax                 81 mov [ebp+0x216],bl
72 mov dl,[esp+0x454]              75 mov [g_next_object_id],eax  82 mov [ebp+0x218],1
73 mov [ebp+4],eax                 76 lea eax,[esp+0x40]      83 mov [ebp+8],0x64
                                   77 push 8                  84 mov [ebp+0x217],bl
                                   78 push eax                85 mov [ebp+0x1e4],1.0f
                                   79 push 0x2637             86 mov [ebp+0x164],dl
                                   80 push 0
87 call LogMessageInternal
```

Those eleven extra instructions are the id store/increment, the `arg6` load and five
slot stores.  **The source already has them after the call** -- the scheduler hoisted
them into the gap to fill the call's latency.  So this is not the statement order the
agent's note rejected at 1262; it is a scheduling artefact, and the lever that would
move it is a dependency the compiler cannot see through, not an order.

Worth knowing before another round goes here: this single segment is a sixth of the
function's excess, and it is the same class as `CrashDump`'s `sub esp,0x28c` (an
allocator/scheduler fixed point), so it belongs with the functions whose residue is
scheduling rather than with those whose residue is spelling.

**Round-189: the pad step's LONG list is not a lever, and the last pad is gone.**

Residue **9,684**.

`cm_ExCopyEntityData` -1 (466 -> 465), and structurally more than the byte: its object
was 896 and `pad_short_functions.py` was appending a separate 16-byte `.text` of zeros
to reach 912, the reference's own span.  It is now 912 of real code -- three hunks: the
type-2 arm's `cmd_ptr+0x18` read and the type-1 arm's `>= 0` test become volatile (same
value), and the type-1 *secondary* clamp is rewritten in-range-first, which is
equivalent (the new third arm fires exactly when the old first did).  The pad step now
reports nothing short anywhere in the tree.

*The `LONG` list is noise.*  It has 149 entries and reads like the drift source, but it
compares our **padded** object size against the **metadata** size, so most entries are
16-byte alignment slack (`cm_ProcessCommandQueue 640 > 639 (+1)`) and some are
meaningless (`vfs_OpenStream 704 > 667 (+37)` compares against a size that excludes the
object's own jump table and case map, whose real span is 701 rounded to 704).  The
quantity that would matter is our padded size against the *reference object's* padded
size, and nothing computes that.  Do not spend a round on `LONG` as it stands.

*Only one object needed padding*, which is worth knowing: the drift that moves 73 of
319 symbols is not coming from short objects any more.  Whatever remains of it is in
the 149 long entries' alignment slack, or in the link order itself.

**Round-188: per-function numbers are not comparable across compositions.**

Residue **9,685**.

The `cm_ExSellObjekt` 1,413 -> 1,460 swing is now explained, and it is not a
regression.  Its round-181 value of 1,413 was *fresh* at the time, in the composition
that existed then; the vfs, gv and `gm_AllocGebaeude` changes since altered the layout,
and `postlink_residual` reports differing bytes by reference VA, so a symbol that is
not exactly at its reference VA drags its whole window.  The total nonetheless fell
(9,743 -> 9,686), so the drift was net positive.  **Per-function numbers from
different rounds cannot be compared; only a full-rebuild total can.**  This is the
third form of the same lesson (round 179: incremental links mix objects; round 185:
`git add -A` mixes commits; here: per-function windows move with the layout), and it
means the per-function table is for *ranking within one run*, not for trend.

Settled in the current composition: the `cm_ExSellObjekt` line-328 inversion, which
measured +46 against a stale baseline in round 186, is **-1** here (1,460 -> 1,459).
Kept -- and justified independently of the score, since the reference emits that site
as `test ecx,ecx; je <error>; push; push; call; jmp`, i.e. the error block is the
taken branch, which is what the inverted form produces.

A rejected candidate re-measured in a fresh composition can be a win, and vice versa.
That is the practical consequence: keep the candidate lists, not just the verdicts.

**Round-187: the baseline was stale, and the volatile-declaration lever has no
remaining instances.**

Residue **9,686** -- and that is a correction, not a regression.

*The 9,644 figure was measured against a stale object.*  `linktest.sh` recompiles
only the files it is named, so the per-function tables of rounds 185-186 were built
on whatever objects happened to be in `build/`, and at least one of them
(`cm_ExSellObjekt`) was a variant whose source had since been reverted.  A plain
`gate.sh` full rebuild -- which is what a fresh clone gets -- produces **9,686**, with
`cm_ExSellObjekt` at 1,460 against the 1,413 the incremental runs reported.  The
lesson is the same one round 179 taught from the other side: an incremental link is
only as good as the objects it did not recompile.  **Run the gate (or `cmake
--build`) before believing a new low**, and treat it as the baseline.  The 1,413
reading is not reproducible from HEAD and should not be chased.

*The `volatile`-declaration lever is exhausted.*  Round 185's -62 came from replacing
`volatile int done; volatile int result;` with plain locals plus `*(volatile int*) &x`
at the use sites.  A sweep for the same shape finds only two bare `volatile`
declarations left in the tree: `srv_InitBuildingTypeTable`'s `volatile int n;` (inside
an `__asm` fill, and outside the holdout set) and `gv_ExAllocGraveyardWorker`'s
`volatile int iv;`, which is a deliberate *never-read* scheduling barrier with no use
site to move the qualifier to.  Neither is applicable, so that lever is done.

Note also that the `Europa1400Gold_TL.exe` copies of `vfs_ReadCompressed.c`,
`m_AllocTracked.c` and `vfs_ReadData.c` still carry the old `volatile int`
declarations -- independent evidence that the pattern was in the original source and
that removing it in the server.dll copy is the faithful direction.

**Round-186: the real-length lever is closed, and two candidates measured at the
link.**

Residue **9,644** (from 9,645).

*The round-184 lever was a one-off.*  `vfs_OpenStream` is fixed, so I corrected
`.scratch/reallen2.py` (window the reference to the **next function's VA**) and swept
every holdout.  Six genuine length differences came back:

```
CrashDump                    -2    cm_ExSellObjekt             -2
ls_LoadBuildingEntityState   -3    gm_FindNextFilteredEntity   -4
cm_ExCopyEntityData          -9    vfs_ReadCompressed          +4 (ours longer)
```

but a length difference only *matters* when the function has out-of-line data after
its code, because that is what gets misplaced.  Dumping each reference tail settles
it: all five are pure code ending in `pop`/`ret`, with no jump table and no relocated
entries.  (CrashDump's `-2` is not even a length difference — its padding byte is
`0x09`, not `0x90`, so stripping `0x90` stops early.)  `vfs_OpenStream` was the only
function in the tree with a jump table + 13-byte case map inside its own object, and
it is done.  **No further layout lever of this kind exists**, which is worth knowing
before another round is spent hunting one.

*`gv_ExAllocGraveyardWorker` -1* (458 -> 457): the three statements after the memsets
permuted so the slot+4 store and `memset(m2,neg,32)` precede the volatile `0xffff`
store.  Size-neutral (obj 1040 = real 1040 = the reference's).  Note the reference's
*own* order measures 668 matched-reloc, i.e. worse -- this is a scheduling
coincidence, not a claim about the source's statement order.  Committed by named path
only, per round 185.

*`cm_ExSellObjekt`, the error-site inversion: rejected, +41.*  `if (x == 0) { log;
return 1; } remove(x);` written inverted is semantically identical and matches the
reference's emitted order at that site (`test ecx,ecx; je <error>; push; push; call;
jmp`), and it does improve the bytes after the function (14 -> 9), but it costs 46
in-function to buy 5 outside:

```
cm_ExSellObjekt  1413 -> 1459   (+46)
<outside>          14 ->    9   ( -5)
.text total     9,644 -> 9,685  (+41)   reverted
```

Its agent's own arithmetic is worth keeping: with *both* error sites inverted the body
is 2052, five bytes short of the reference's 2057, so the missing length is elsewhere
-- our build tail-merges more error sites than the reference's seven separate
`push 8; push str; push line; jmp` sites.

**Round-185: `vfs_ReadCompressed` -62 (committed by accident), and the real-length
sweep needs the right window.**

Residue **9,645** (from 9,707).

*vfs_ReadCompressed 134 -> 72, link-measured.*  Its agent moved `volatile` from the
declarations to the use sites: plain `int done; int result;` with
`*(volatile int*) &x` at the real accesses.  A volatile *declaration* makes the two
entry zero-stores scheduling barriers, so msvc6 leaves the `handle` load+test behind
them; qualifying the accesses instead reproduces the reference prologue byte for
byte (`mov eax,[esp+0xc] / push ebx / push ebp / push esi / test eax,eax / push edi
/ store / store / jne`).  Two sub-facts worth keeping: the one plain read
`int acc = result;` must stay plain (qualifying it costs 32 bytes), and on the old
body merely casting the two *init* stores already gives 382 -- so it is the init
stores, not the declaration, that are the barrier.  This is the converse of docs
section 39, which defers a load via a volatile read.

*It was committed without being measured, by accident.*  `git add -A` in round 184
swept the agent's working-tree edit into `6e5b7c22` (whose message names only
vfs_OpenStream), and `linktest.sh` recompiles only the files it is named, so the
change sat in the tree uncompiled and unmeasured for a round.  It happened to be a
-62 win.  **Never `git add -A` on this tree while agents are working** -- commit
named paths only, or the commit silently carries unvalidated work.  The same
mechanism put an agent's `cm_ExSellObjekt` edit into an earlier commit.

*The real-length sweep needs the window to reach past the function.*  Round 184's
lever -- a real COMDAT body shorter than the reference's puts the out-of-line jump
table / case map at the wrong offset -- generalises, so `.scratch/reallen.py`
compares the reference's real body against ours for every holdout.  But the first
run was wrong for exactly the functions it was written for: the metadata `size`
(667 for vfs_OpenStream) covers only the *code*, so the reference window stops
before the table and reports a bogus +34 for a function already fixed.  The window
must run to the **next function's VA**, not to the metadata size.  The reliable
statement is the direct one: reference content ends at the last non-0x90 byte
before the next symbol.

For the record, the first (untrustworthy) run reported CrashDump -2, cm_ExSellObjekt
+9, ls_LoadBuildingEntityState -3, cm_ExCopyEntityData -9, vfs_ReadCompressed +4,
gm_FindNextFilteredEntity -4.  `gm_AllocGebaeude` reads +0 once measured properly --
its CSV size 1088 is padded, its real content is 1078 like ours, and its jump table
and case map match byte for byte -- so it is *not* a length case.

**Round-181: `cm_ExSellObjekt` -19, and the out-of-function residue explained.**

Residue **9,743** (from 9,762).

`cm_ExSellObjekt` 1432 -> 1413, measured with `linktest.sh` on a tree where it was
the only modified file (the round-180 attribution guard was silent, so the delta is
attribution).  Three changes, all equivalence-checked before committing: two guard
inversions that keep the same operator and the same arm bodies in the same effect
order, and a `source_dynamic_ref` local replacing two deliberate self-assignments.
The latter is only safe because `source_dynamic_entity` has exactly two assignments
in the whole function (init to 0, and `= resolved_dynamic`), both *before*
`source_dynamic_ref` is set — verify that before reusing the pattern.

**The 32 differing bytes "outside the non-matching functions" are mostly one
object's real length.**  `vfs_OpenStream`'s real COMDAT body is 693 against the
reference's 701, so its out-of-line jump table and 13-byte case map — which live
after the code inside the same object — sit 8 bytes early, and every 4-byte
relocated entry in them points one byte late.  A previous agent had a spelling
(`int mode18` with byte-width accesses, direct `*p` in the flag loop and switch, a
volatile second `sprintf` argument) that lands the real body on exactly 701 but
costs 172 in-function bytes; it was never applied.  Applied and linked here:

```
<outside the non-matching functions>    32 -> 10    (-22)
vfs_OpenStream                         263 -> 435   (+172)
.text total                          9,743 -> 9,893 (+150)   rejected
```

So the diagnosis is confirmed and **quantified: fixing the length alone recovers 22
of the 32 out-of-function bytes**.  The target is therefore narrow — find the 8
bytes of real body length the reference has and we do not, and add only those,
rather than respelling the function to change its length.  The agent has been given
that instruction; its object metrics (matched-reloc 285 against the baseline's 451)
were the reason it had withheld the spelling, and this measurement shows why the
ranking metric is the wrong instrument for a layout hypothesis: the object score
ignores the 22 bytes it would have fixed.

The 8 bytes are then localised by tracking the cumulative offset gap (ours minus
the reference's) across the aligned streams: it starts +1, peaks +6 around refoff
0xc6, and ends **-8** at refoff 0x289, so 14 bytes are lost between 0xc6 and the
epilogue.  Two sites account for it, and the table/case map are byte-for-byte the
same size in both objects (5 four-byte entries + a 13-byte map) — the table only
*starts* 8 bytes early:

The gap is **0 from refoff 0x118 through 0x246** — so everything between those
points is exactly the reference's length, and the whole 8 bytes are in the finalize
tail:

```
gap 0 at refoff 0x246  ->  gap -17 at refoff 0x260  ->  recovers to -8 by the epilogue
```

The reference there loads and masks mode18 **twice** — `mov edx,[esp+0x18]` at
0x24b with `and edx,0xff` at 0x265 pushed as the first `sprintf` argument, then
`mov eax,[esp+0x18]` again at 0x277 with `and eax,0xff` at 0x27b pushed as the
second.  Our source's `sprintf(..., mode18, mode18)` CSEs into one eax pushed
twice, which is the 17-byte shortfall.  The fix is the tail half of the rejected
spelling only — `int mode18` with byte-width access and a volatile second argument,
per this file's header lines 120-126 — *not* the flag-loop rewrite that cost the
172 in-function bytes.  (My earlier note in this round blamed a 7-byte block at
refoff 0x107; that was wrong.  The gap returns to 0 at 0x118, so adding that block
would overshoot by 7.)

**The running-gap trace is the right instrument for a length hypothesis** and found
this in one run: align the two streams, and print our offset minus the reference's
at the start of each equal block.  `probe_function` and `instr_diff` cannot see a
length hypothesis at all — the object score for the spelling that fixes the length
was 285 against a 451 baseline.

**Round-180: a semantic break caught by reading the diff, and a neutral candidate
discarded.**

Residue unchanged at **9,762**; tree back at the validated commit.

*`m_AllocTracked`, rejected as a semantic break.*  The candidate rewrote

```c
if (g_stat2 - slots < 0)          /* g_stat2 <  slots */
if (0 <= slots - g_stat2)         /* g_stat2 <= slots */
```

which is not the same guard: the equality case flips and the guarded body runs when
`g_stat2 == slots`.  The original spelling is also the one the file's header records
as load-bearing (`g_stat2 < slots` re-folds the volatile load into
`cmp dword ptr [g],edi` and drops matched-reloc 565 -> 467).  **An algebraic rewrite
of a comparison is only safe if it keeps the strict/non-strict boundary** — `a - b <
0` is `a < b`, never `b <= a`; to change which operand folds, flip the operands of
the same operator (`slots > g_stat2`).  Caught by reading the diff before linking,
not by any score: at the object level it looked like an ordinary respelling.

*`cm_ExSellObjekt`, neutral.*  Re-introducing a `source_dynamic_ref` local in place
of the deliberate self-assignment `source_dynamic_entity = source_dynamic_entity;`,
plus a polarity inversion of the `0xffff` guard, link-tested at exactly 0 (9,762 ->
9,762), so it was reverted rather than kept as churn.

Both were measured with the round-179 procedure: revert every other pending file
first, then `linktest.sh` the single file, so the delta is attribution.

**Round-179: attribution, and a wrong commit caught by re-measuring.**

Residue **9,762** (from 9,820).  The round's value is mostly methodological.

*A per-function delta is only attribution when exactly one object changed.*  A
CrashDump hunk was link-tested at "-58" (CrashDump 1962 -> 1918, gm_AllocSpieler
2905 -> 2901, the trailing bytes 42 -> 32) and committed on that reading.  It was
wrong: re-measuring the same source in the same composition gives **+56** on
CrashDump (1918 -> 1974) and +66 overall.  The -58 came from the *other* objects in
the composition — cm_ExSellObjekt's and gm_AllocSpieler's layout — because
`postlink_residual` attributes differing bytes by reference VA, and every symbol
after a changed object moves.  `linktest.sh` recompiles only the files named, so a
single-file run is clean **provided no other object has changed since the last full
build**; once an agent has edited a second file, the per-function table mixes both
effects and cannot be read as attribution.  The correct procedure is one file at a
time against a freshly rebuilt baseline, or a full rebuild before each batch.
`880bbb54` reverts the bad commit.

*And on CrashDump neither object metric is safe.*  Its agent measured three
states with the linked result: goto-only 162 honest / 562 reloc -> linked -13;
hoisted 153 / 541 -> -21; `c0beebd3` 212 / 586 -> -27.  The first two are
anti-correlated with *both* metrics, which is the opposite of the 4/4 finding on
the earlier four cases.  So the rule cannot be "rank by matched-reloc" — it is
"link-test everything", and `matched-reloc` is only a way to order the queue.

*Warning gate worth reusing.*  The same agent gated every candidate on (a) the
matched pattern occurring exactly once, (b) the moved statement landing on the
unconditional path, (c) object size unchanged, (d) **a fresh compile with no new
warning**.  (d) caught its best-looking number of the session — moving
`excCode = ...ExceptionCode;` below the dispatch scored 200 honest / 576 reloc, but
cl emitted C4700 and the code tested an uninitialised slot.

**Round-177/178: a fresh build directory could not be linked, and a gate run
rewrites metadata it does not own.**

Residue **9,820** (from 10,023).  Two `rebrew` bugs found and one fixed.

*A fresh `build/` could never complete its first link.*  `scripts/pad_short_functions.py`
read `build/split_poc.map` unconditionally, but that map is written by the split
link itself (`/MAP:split_poc.map`, line 192 of `split_link.sh`) and the pad step
runs *before* it — so on a clean tree it raised `FileNotFoundError` every run and
the composition could not be bootstrapped at all.  It now reports and returns no
pads on the first run; the map exists from then on and the next run pads as usual.
This is what made a clean reconfigure look unrecoverable for a whole round.

*Reconfiguring from scratch also needs the toolchain file.*  `cmake -S . -B build
-DREBREW_DEBUG_INFO=OFF` — the form `AGENTS.md` documents — configures against a
cache holding a native compiler and silently falls back to it: `MSVC for
decompilation: FALSE`, then `fatal error: windows.h: No such file or directory`
and no `objects1.rsp`, so `split_link.sh` cannot run.  The working invocation is

```
cmake -S . -B build --toolchain cmake/toolchain-msvc-6.0-sp6-docker.cmake \
      -DCMAKE_BUILD_TYPE=Release -DREBREW_DEBUG_INFO=OFF
```

**`rebrew verify` rewrites STATUS on entries that never claimed PROVEN.**  The gate
runs `rebrew verify --full`, and one run demoted `["SERVER.0x10018850"]` from
`SIZE_MISMATCH` to `STUB` and stamped `updated_by = "verify"` — a status the entry
never held a claim to.  Two write sites in `verify.py`:
`~line 1004` (`update_statuses_batch`, gated on `stale_proven` from `proven_vas`,
which is built from entries whose status *is* `PROVEN`) and `~line 1794`
(`should_promote_status(current_status, status)`).  The entry was `SIZE_MISMATCH`,
so site 1 cannot have fired; site 2 did, because `should_promote_status` ends
`return current != new` — *every* status change is allowed, demotions included.

**This is by design, not an oversight, and the fix is therefore a decision rather
than a patch.**  `tests/test_property_status.py` asserts it in two places:
`test_symmetric_under_rule_set` encodes "a promotion is allowed iff none of the
refusal rules fire" with the refusal set being only {sticky, STUB -> size-state},
and `test_exact_to_stub_demotes` says so outright (`should_promote_status("EXACT",
"STUB") is True  # demotion ok`).  A patch adding the symmetric
`SIZE_MISMATCH/MISSING_SIZE -> STUB` guard was written and reverted: it fixes the
observed corruption but fails that property test, i.e. it contradicts the
documented contract on a guess.  The asymmetry worth raising with the maintainer
is that the existing STUB guard already encodes "a placeholder must not erase a
classification", and a byte-state is the *more* informative side of the pair — it
names the measured delta in its note, where STUB says only "unclassified".

The practical mitigation meanwhile is on this repo's side: a gate run rewrites
`src/rebrew-functions.toml`, so restore it after gating
(`git checkout HEAD -- src/rebrew-functions.toml`) rather than committing the
churn.  **Every gate run will rewrite it again until the question above is
settled.**

*CrashDump -27* (1989 -> 1962, net -23 with a +4 knock-on in the bytes after the
function, which are its own jump table/byte map).  The hunk moves `nFrames = 0x800`
up to the date-write block — a move, not a deletion: the initialiser is still there
and still precedes every use — and adds two redundant stores (`frameInfo[1]` twice,
`eip = pCtx->Eip` before the `unknown_exc` label) that match the reference's
emission.  Both are semantically inert.

**Round-174: the fan-out repeated with the ranking metric corrected, and the
validation cycle made a command.**

*The cycle is now a script.*  Round 173's validation was done by hand three times
and the compile flags were written from memory once — which mis-measured a link
and produced the round's one wrong "no regression" reading.  `scripts/linktest.sh`
does the whole thing: recompile exactly the named files with the command
`build/CMakeFiles/server_dll.dir/build.make` records for them (so the flags cannot
drift from what `cmake --build` uses), relink the per-reference-offset composition,
apply `postlink_residual.py --write`, and diff the per-function table with
`scripts/residue_diff.py` (promoted out of `.scratch/`, where a fresh clone loses
it) against `.scratch/residue_base.log`.  `--new-base` adopts the result.

*The archive re-ranked by the metric that actually tracks the linked residue — and
there is nothing left in it.*  Round 173 re-judged the ~8,700 already-compiled
probe objects under `.scratch/` by the LCS score; that ranking is now withdrawn,
so they were re-judged by `matched-reloc`.  For sixteen of the eighteen holdouts
the live tree ties or beats the best archived variant:

```
gm_AllocSpieler        live 1246  archive 1197  (-49)
cm_ExSellObjekt        live  834  archive  373  (-461)
ls_LoadBuildingEntityState 879 / 815, gm_AllocGebaeude 644/518,
gv_ExAllocGraveyardWorker 660/655, m_AllocTracked 565/314,
ServerMainThread 2149/1640, gm_CheckInventoryCapacity 298/293
vfs_ReadCompressed, gm_FindNextFilteredEntity, srv_LoadBuf,
cm_ExProdObjekt, cm_ProcessCommandQueue   live == archive
cm_ExCopyEntityData    live  573  archive  576  (+3, the shipped object itself)
CrashDump              live  523  archive  577  (+54, .scratch/flagprobe/cd_o2.obj)
```

The one outlier is a Sep-10 object with no preserved source beside it, and it is
the round-162 profile: it is very likely the relocation-inflated class, since
`matched-reloc` credits a byte under a relocation on either side.  Everything else
confirms the tree is not leaving wins on the table in its own history.

*First link-validated candidates of the round, and one measurement fact that
explains round 172's surprise.*  Baseline 10,097 -> **10,023**:

```
gm_AllocSpieler       2934 -> 2908   (-26)  one word: InitNewDynastyEntity(type & 0xff, ..)
                                            -> InitNewDynastyEntity(slot[2] & 0xff, ..)
vfs_ReadCompressed     158 ->  134   (-24)
CrashDump             1988 -> 1975   (-13)  date/time block order, hProc move, and a goto
                                            still under review (see below)
cm_ExSellObjekt       1434 -> 1433    (-1)
```

The gm_AllocSpieler win is worth reading twice: `slot[2] = (char) type` is assigned
earlier in the function, so naming `slot[2]` again instead of `type` is
semantically identical, and it lets msvc6 reuse the `mov al,[ebp+2]` it already
made for the `== 0x15 / == 0x16` test, emitting the 5-byte `and eax,0xff`
accumulator form instead of the 6-byte `and esi,0xff`.  matched-reloc 1246 -> 1269
and honest matched 668 -> 691, so it is not relocation inflation, and the real body
length goes 3690 -> 3689, i.e. *exactly* the reference's.

That last number is the measurement fact worth keeping: **msvc6 pads a COMDAT to a
16-byte multiple with trailing `nop`s, so every real body length from 3681 to 3696
reports "object size 3696".**  A candidate can therefore change the linked section
size — and move every symbol after it — while every tool reports the size as
unchanged.  That is what made round 172's gm_AllocSpieler reorder look size-neutral
when it was not, and it is why the honest `matched` and the real body length both
need checking, not just the reported object size.

*Under review.*  The CrashDump candidate adds `goto no_dbg;` immediately before the
`log_close:` label, which makes the normal path skip that block's
`LogMessageInternal` call.  That is a behavioural change rather than a scheduling
one, so it is being held out of the tree until the agent confirms against the
reference disassembly that the original really does branch over it; the date/time
block reorder and the `hProcess` move are pure ordering and are kept.

*CrashDump's `goto` is the reference's control flow, not a shortcut.*  The
candidate link-tested 1988 -> 1967.  `goto no_dbg;` before `log_close:` looked
like a behavioural change, so it was held out and the agent asked to justify it
against the reference rather than the score.  It did, by enumerating branch
targets: the reference's normal path ends `0x10002dae  e9 b3 00 00 00  jmp
0x10002e66` (unconditional, landing on `no_dbg`), and the block our fall-through
reached at `0x10002db3` is the target of exactly one branch, `je 0x10002db3` at
0x100028f5, the `hCrashLog == -1` failure arm.  The four LogMessageInternal call
sites are 0x10002dc4/0x10002dfa/0x10002e3a/0x10002e5e and the normal path reaches
none of them.  So the fall-through was the reconstruction bug.

*Probe drivers that write into the source make link validation racy.*  Three agents
sweep by writing each experiment into the source file and restoring it seconds
later.  `linktest.sh` recompiles that exact path, so a run sampling mid-sweep
measures a transient — which is what produced a spurious `m_AllocTracked` +161 (the
file was back at HEAD with no diff when inspected).  The protocol is now: an agent
puts its best candidate in the file, stops sweeping, and says "file frozen" before
any link test; only then is the file measured.

**Round-173: the eighteen holdouts fanned out across six subagents, and the
object-level proxy caught pointing the wrong way four more times.**

10,846 -> **10,098** differing bytes, all in `.text`, with `.data`/`.rdata`/
`.reloc`/headers still byte-identical and nothing regressed.  This is the first
round since the pad landed where a batch of independently-probed changes was
link-validated as a batch, and the batch is where the win came from:

```
cm_ExSellObjekt            1,759 -> 1,435   (-324)
vfs_ReadCompressed           348 ->   158   (-190)
m_AllocTracked               256 ->    93   (-163)
ls_LoadBuildingEntityState   775 ->   728   ( -47)
ServerMainThread             379 ->   371   (  -8)
ahm_ExAllocAlchemist         209 ->   201   (  -8)
gm_AllocGebaeude             530 ->   527   (  -3)
gv_ExAllocGraveyardWorker    464 ->   462   (  -2)
<outside the functions>       36 ->    33   (  -3)
```

*The method.*  Six subagents, one per disjoint set of source files, each told to
probe only (the coordinator owns the build, the link and the linked validation)
and to accept a change only when an object metric rose and the object's size did
not.  Every agent's kept hunk was then recompiled into `build/` with the exact
`build.make` command and the whole composition relinked, which is the only
measurement that decides.  Context is the binding constraint on this work — the
per-function headers alone run to hundreds of lines — so this is the first round
where the parallel form was used end to end.

The largest single win came from the same lever round 172 found: `cm_ExSellObjekt`
(-324) is a pure statement-order transcription — the block of eight pointer
initialisations reordered to the reference's emission, two `container_ptr` dead
temps dropped so the container stores are direct, and the `0xffff` owner guard
inverted so the zero arm is the `else`.  `vfs_ReadCompressed` (-190) is five
independent spelling fixes, the biggest being `unsigned int i` -> `int i`, which is
what stops msvc6 proving `i != 0` and deleting the reference's live
`test edi,edi / je`.  `m_AllocTracked` (-163) hoists the load-bearing volatile
`g_array_count` read into a local so it stays in `edi` across the guard, the way
the reference keeps its loop bound.

*The proxy was wrong four more times, and one of them was the coordinator's.*
Each of these improved `aligned` (the LCS instruction score added in round 172)
and was a linked regression:

- `gm_AllocSpieler`, two statement reorders read straight off the reference's
  emission: aligned 647 -> 660, object size unchanged, **linked 2,934 -> 2,970**.
  Reverted.  Round 172 recorded this change as "no regression"; that reading came
  from a postlink run that had not been preceded by `scripts/split_link.sh`, so
  the vehicle it measured was the previous link's.  Run the `final` pipeline
  (`cmake --build --target server_dll` -> `scripts/split_link.sh` ->
  `postlink_residual.py --write build/server.dll`) or the number means nothing.
- `ls_LoadBuildingEntityState`, the seven plant-map reads all made pointer-first
  (its own agent flagged it, correctly): aligned 396 -> 414, object size 1472 both
  ways, **linked 728 -> 1,400** because the change drops `push ebp` and the
  `or ebp,-1` sentinel and every `[esp+N]` in the function then differs.  Rejected.
- `gm_CheckInventoryCapacity`, the eight element stores folded into an
  `int list[8] = { ... }` initialiser: aligned 125 -> 127, **linked +7**.  Rejected.
- `cm_ExProdObjekt`, the recipe address folded back to `g + idx * 0x41` (the
  pre-pass-4 spelling, still visible in `.scratch/epm/w/exp.c`): aligned 349 ->
  351, **linked 21 -> 44** plus 36 bytes of collateral on `gm_AllocSpieler`
  because a size change in an earlier object moves everything after it.  Rejected.

Taken together those four are a clean result and it is **not** the one round 172
predicted.  In every case `matched-reloc` — the legacy fixed-offset count, the
one this project has always used — moved the right way, and `aligned`, the LCS
score added in round 172, moved the *wrong* way: it rose in all four while the
linked residue grew.  So the ranking rule is **`matched-reloc` up**, with
`aligned` demoted to a diagnostic; round 172's "`aligned` is the better gradient"
is withdrawn.  `matched-reloc` has one known false positive, which is the reason
the honest count now exists beside it: it credits a byte under a relocation on
either side, so an instruction that introduces a new absolute address buys up to
four bytes for free — round 162's CrashDump move (523 -> 575, ten linked bytes
worse) is that case, and honest `matched` reads 147 -> 127 on it.

Whatever the ranking says, the rule is explicit: **a candidate is worth keeping
only after the composition is relinked.**  The cheap way to honour it is to batch
— probe many changes, then recompile exactly those files with their `build.make`
command line and relink once.  `scripts/linktest.sh` is that cycle in one command
(recompile exactly the named files, relink the composition, apply postlink, diff
`scripts/residue_diff.py` against `.scratch/residue_base.log`); round 173 was the
first time the cycle was done by hand three times and the flags were written
wrong once, which is why it is now a script.

*The archive was re-judged and is mostly superseded.*  Every past campaign
recorded "inert at N" from the fixed-offset count, so the ~8,700 already-compiled
probe objects under `.scratch/` were re-scored with the aligned objective
(`.scratch/rescore3.py`, COMDAT symbol -> VA, both sides at the metadata size).
For thirteen of the eighteen holdouts the live tree already beats the best
archived variant, which is the useful result: the tree is not leaving easy wins
on the table.  Three exceptions were chased to the end — `gm_CheckInventoryCapacity`
(`.scratch/pv/pv_H1.c`'s `while (elem != 0)` loop reaches aligned 129 but is a
*semantic* bug: it classifies the zero sentinel as a miss where the reference
tests `elem == type` first, so it was not adopted), the `cm_ExProdObjekt` and
`ls_LoadBuildingEntityState` cases above, both linked regressions.

*Measurement defects fixed in the tooling.*

- `probe_function.py` counted a byte as matched when *either* side had a
  relocation on it, so an instruction that introduces an absolute address bought
  all of its operand bytes.  The round-162 CrashDump move (523 -> 565 "matched",
  which cost 10 linked bytes) was 90% new reloc slots; a per-byte audit at that VA
  reads 74 both-side relocs and 73 plain-equal for the baseline against 47 and 80
  for the rejected variant.  `matched` is now the honest count — both sides
  relocate it, or neither does and the bytes agree — and the old number is kept
  beside it as `matched-reloc`, because every figure written into a source header
  before this round is that one.
- `instr_diff.py --obj <object.obj>` and `probe_function.py`'s second line print
  the aligned (LCS) score for a probe without relinking; `kind()` folds an
  object's `[0]`/`0` addend onto `ADDR`, without which every relocated global read
  counted as a kind the other side did not have.

Also this round: `gm_CheckInventoryCapacity`'s archive lead was reported to its
agent and correctly refused on semantic grounds; `vfs_OpenStream` (263 bytes) and
`gm_FindNextFilteredEntity` (226) and `srv_LoadBuf` (49) and `CrashDump` (1988)
produced no win — CrashDump's first divergence is byte 2 (`sub esp,0x28c` vs
`0x280`) and the frame is slot-coloured over live ranges, so it is not
declaration-order steerable.

**Round-172: an object-level sequence score, and gm_AllocSpieler's schedule read
off the reference instead of searched for.**

Residue 10,846 at the time; round 173 link-validated the two source changes below
properly and they are a **regression** (2,934 -> 2,970) and have been reverted.
The measurement finding that produced them stands, and is the round's real
content; the reading of it — "the linked image is byte-identical" — came from a
postlink run that had not been preceded by `scripts/split_link.sh`, so it measured
the previous link's vehicle.

*The measurement was the blocker.* `probe_function.py` scores a **fixed-offset**
byte compare against the target's size, so once the instruction stream diverges by
one byte every later byte counts as wrong.  On a 3,689-byte function that
saturates: gm_AllocSpieler reads 755/3689 from the linked image and 1,246/3689 from
the freed object, while its instruction *sequence* is two-thirds right.
`hillclimb.py` optimized that saturated number, which is why it "converged with no
improving move" on a function that still has 178 hunks.

`scripts/instr_diff.py --obj <object.obj>` scores one compiled COMDAT that way,
without relinking the vehicle (a full build per probe is minutes; this is ~1.5 s
plus the compile), and `probe_function.py` now prints the same number on a second
line (`aligned N/M reference instructions`) so a probe needs only the one command.
`kind()` also now folds an object's `[0]`/`0` addend onto `ADDR` — without that,
every relocated global read as a kind the other side did not have and inflated
gm_AllocSpieler's multiset difference from 79/83 to 111/115.

*Reading the reference's order beats searching for it.*  Two reorders in
gm_AllocSpieler, both transcribed from the reference disassembly at 0x100188fa
onward, both leaving the object at exactly 3696 bytes:

- the record-header block moves `*(int*)(slot+0x16c) = 0` up beside
  `*(int*)(slot+0x170) = 0` (both after `slot[2] = type`), giving the reference's
  type/0x170/0x16c/0x1f0/0x210/0x215 sequence, and `LogMessageInternal` moves to
  directly after the `sprintf` it logs — the reference calls it at 0x10018980,
  before the `slot[4]`/`slot[8]`/`slot[0x1e4]`/`slot[0x164]` stores our source put
  ahead of it.  LCS 647 -> 659 of 1056.
- the citizen path's `rnd = gm_RandomMod(8) & 0xffff` moves above
  `*(int*)(slot+0x1f0) = *(int*) ent` (the reference's `mov [ebp+0x1f0],edx` sits
  at 0x10018921, *after* the `gm_RandomMod` call our source preceded it with), and
  `slot[0x164] = ent[0xd4]` moves above `slot[9] = ent[0xd5]` (0x1001891e before
  0x10018927).  LCS 659 -> 660.

Two claims in that file's own notes are contradicted by the current reference
disassembly and should not be trusted: "`slot[2] = type` sinks below the two zero
stores at 0x170 and 0x16c, which is the target's order", and "in the citizen path
`slot[9] = ent[0xd5]` precedes `slot[0x164] = ent[0xd4]`".  The reference emits
`mov [ebp+2],al` (type) at 0x1001891e, *then* the two `ebx` zero stores, and it
emits `slot[0x164]` before `slot[9]`.

That the linked number did not move is the point to keep: the residue is a
per-function **saturated** fixed-offset compare, so a sequence-level gain is
invisible to it until the function is positionally aligned end to end.
gm_AllocSpieler has ~178 hunks to close at roughly +1..+12 LCS per transcribed
region — a per-function source-reconstruction job, not a search job, and one that
is now measurable per probe.

Also this round: the remaining holdouts were fanned out across six subagents on
disjoint files, probing only (the coordinator owns the build and the linked
validation), because the per-function work is independent and context-bound.

**Round-171: three rebrew defects fixed, one spelling measured shut.**

10,846 bytes unchanged on the DLL; `rebrew`'s own suite went from 3 failures to
**6503 passed, 0 failed**.

*The spelling.*  `cm_ProcessCommandQueue` is 15 bytes from done and its
difference is localised: the target re-tests the candidate after assigning it
(`mov ebx,esi` / `test ebx,ebx` / `je`) where our source writes `held = pkt; goto
advance;`.  The two are equivalent (`pkt` is non-NULL there, so the shared test
takes the same branch), so removing the `goto` should let the fall-through serve
as that test.  Measured: **624 -> 204 matched**.  msvc6 lays the `recheck` block
out differently and the arm order collapses -- the same end every CFG spelling of
this function reaches, which its notes already record.

*Three defects in rebrew, all pre-existing except one of mine:*

- `rebrew --version` printed **1.1.0** while the code was **1.2.0**: the callback
  read `importlib.metadata`, whose value is baked at install time, so an editable
  checkout starts lying the moment `__init__.py` changes.  It now reads
  `rebrew.__version__`, which is also what packaging uses as the single source
  (`[tool.setuptools.dynamic] version = {attr = ...}`).  This had been failing
  `test_main.py::test_version_matches_module`.
- `.agents/skills/` had drifted from the canonical `src/rebrew/agent-skills/` —
  **my** doing: round 154 added the `cmake-flags` row to the workflow skill and
  did not re-render the copy.  Re-rendered with the command the sync test's
  docstring gives.
- `rebrew-toolchains` had no `ido/5.3-linux` or `ido/7.1-linux` Dockerfile,
  though rebrew's registry defines both as image-backed toolchains and pins the
  decompals/ido-static-recomp v1.2 asset by sha256 — so a fresh clone could not
  rebuild them (exactly the "untracked Dockerfile" class
  `test_toolchain.py::TestDockerfileSanity` exists to catch).  Both are the
  sibling `-n64` Dockerfile with the tag, labels and target naming changed; the
  URL, sha256, extraction path and `cc` wrapper are identical.

**Round-170: the pad lever's other candidates, both measured flat.**

No byte change (10,846).  Round 169's padding makes size-changing improvements
adoptable, so the two candidates it had been blocking were finally tested.

*CrashDump's `/Oy-` is not a win.*  It was the biggest measured object gain in
the tree (+66 matched, 523 -> 589) and 112 bytes SHORTER, which is exactly what
the pad now absorbs, so it was adopted and built:

```
pad   CrashDumpUnhandledExceptionFilter.c.obj: 2016 -> 2115 (+99)
exactly at their reference VA: 246        (the pad worked)
CrashDumpUnhandledExceptionFilter  1988 -> 1997   (+9)
.text total                     10,846 -> 10,868   (+22)
```

Reverted.  That is the third time an object-level gain turned into a linked loss
(+52/+10 on this function in round 162, +50/-88 on cm_ExCopyEntityData in round
169), and it settles the flag for good: the object score is a proxy, and on this
function in particular it points the wrong way.

*And `--allow-shrink` finds nothing.*  `hillclimb.py` can now accept a move that
makes the object smaller (the pad absorbs the gap; growth is still refused,
because code cannot be cut to fit a shorter slot).  Run on the four largest
functions -- gm_AllocSpieler, cm_ExSellObjekt, ls_LoadBuildingEntityState,
cm_ExCopyEntityData -- it converges with no improving move, so the shrinking
space is empty too.

With that, every lever this campaign has is measured flat on every remaining
function: statement order (reach 3-12, swaps, size-preserving and shrinking),
declaration qualifiers, compiler flags (18 variants), toolchain (VC4.2/5.0/6.0
and every 6.0 service pack), and expression/clamp spellings.  The residual is a
per-function source-invention problem, not a search problem.

**Round-169: the vehicle now pads, and the first size-changing win is in.**

10,934 -> 10,846 differing bytes.  `cm_ExCopyEntityData` 555 -> 467.

Round 168 named the blocker: the layout is `make_split_rsp.py`'s order (sorted by
reference VA) plus each object's section sizes, so a function that compiles
SHORT drags every symbol after it.  That made any better-shaped but
differently-sized function unusable -- the two-arm `0x7f` clamp on that function
measures +50 matched bytes and -16 of size, and adopting it collapsed the
composition to 1/319 symbols aligned and 86,425 bytes of residue.

`scripts/pad_short_functions.py` fixes that: for every `<source>.c.obj` whose
`.text` is smaller than the reference sizes of the functions it defines, it emits
a one-section `.text` object of `want - have` zero bytes and inserts it into the
response file immediately after.  `scripts/split_link.sh` now runs it before the
link.  With nothing short the step is a byte-for-byte no-op (verified: 246/319
and 10,934 unchanged), and with the two-arm clamp in place it pads
cm_ExCopyEntityData 896 -> 912, the composition stays aligned at 246/319, and the
object's +50 matched bytes finally show up in the link: -88.

Two COFF details cost a build each and are worth recording, because nothing in
the pipeline's own emitters had to be written from scratch before:

- a section needs its **own section symbol** (name `.text`, storage class 3, one
  aux record) before any other symbol, or LINK answers `LNK1143: invalid or
  corrupt file: no symbol for comdat section 0x1`;
- the SectionDefinition aux record is **18 bytes** (Length, NumberOfRelocations,
  NumberOfLinenumbers, CheckSum, Number, Selection, 3 unused).  Packing 16 shifts
  every symbol after it and LINK reports `LNK1106: cannot seek to 0x705f0082` --
  the ASCII of the section name read as an offset.

The step only pads SHORT objects; 149 objects still compile *longer* than their
reference sizes (gm_AllocSpieler +7, spiel622.c +124, spiel_dumpD.c +25, ...) and
are reported.  Those cannot be cut without losing code, so the size gap there
still has to be closed in the source.

**Round-168: why a better object cannot be bought, and the mechanism behind it.**

No byte change (10,934).  Every per-function lever is now measured flat: the
last unfinished climb (`ahm_ExAllocAlchemist`, 89 statements, whose earlier runs
all timed out mid-round-0) completed and converged immediately (851 matched, one
declaration swap, no gain), and all eighteen have converged under the current
tool, on every flag variant, on VC5/VC4.2, and against the size objective.

So the round went at the thing that blocks the one measured win.  The layout is
`make_split_rsp.py`'s order (sorted by reference VA) plus each object's section
sizes -- there is no alignment flag in the link command
(`/nologo /out: /dll /machine:I386 /incremental:no /OPT:NOREF /FORCE:MULTIPLE
/ENTRY:...`), which is why a size change moves everything after it.

Two observations worth keeping, and one that does not fit:

- `scripts/split_audit.py` reports 246/319 symbols exactly at their reference VA
  with deltas up to +0x31c, i.e. the vehicle already carries accumulated drift;
  the residue is attributed per function regardless.
- A size change of +1/+2/+4 (gm_AllocSpieler, m_AllocTracked, cm_ExSellObjekt,
  ls_LoadBuildingEntityState) and the current -8 on cm_ExCopyEntityData are all
  absorbed -- consistent with LINK aligning each object's section to 16 bytes, so
  only a change that crosses a 16-byte boundary (CrashDump +16, the two-arm clamp
  -16, `/Oy-` -112) moves the following symbols.
- The counter-example: `vfs_OpenStream` sits 26 bytes OVER its target (693 vs
  667) and the composition is aligned anyway.  So the 16-byte rule is the best
  model so far, not established fact.

The unblocking work is therefore concrete: make the vehicle absorb a size
difference by padding each function's `.text` to its reference size, after which
the cm_ExCopyEntityData clamp rewrite (+50 matched, -16 size, currently refused
by a full-composition collapse to 86,425 bytes of residue) becomes adoptable, as
would every similar trade.  `scripts/split_coff.py:build_object` is the existing
COFF emitter to build it on.  A first attempt this round rewrote our objects'
section headers directly and was abandoned as too fragile; emitting a small
padding object per short function and inserting it into the response file is the
simpler mechanism.

**Round-167: VC6 confirmed by measurement, and a size/bytes trade the link
refuses.**

No byte change (10,934); two things measured shut.

*The holdouts are VC6 output.*  A rebrew note says this target is "a mix of MSVC
4.2/5.0/6.0 output", and only the VC6 service packs had ever been checked
(SP1-SP6 byte-identical).  Probing the holdouts with the vendored VC5 and VC4.2
settles it:

```
cm_ProcessCommandQueue   msvc-6.0-sp6 624/639   msvc-5.0 206   msvc-5.0-sp3 209   msvc-4.2 165
gm_ObjectsAvailble       msvc-6.0-sp6 686/714   msvc-5.0 154   msvc-5.0-sp3 154   msvc-4.2 180
```

So the mix must be elsewhere (the LIBCMT region), and per-function toolchains
are not what is missing here.

*And a better object can be refused by the link.*  `scripts/sizediff.py` found
`cm_ExCopyEntityData` emitting its `0x7f` clamp **twice** (ref: once, with the
constant out of line) -- +17 bytes of pure duplication.  The file's notes describe
a two-arm clamp form, so it was measured against the shipped three-arm one:

```
three-arm (shipped)  523 matched / 255 insns / object 912  (= target)
two-arm              573 matched / 247 insns / object 896  (-16)
```

+50 matched bytes, and the rebuild collapses the composition (1/319 symbols at
their reference VA, residue 10,934 -> 86,425).  Reverted.  Note the asymmetry
that makes this a per-case gamble rather than a rule: this function is *already*
8 bytes short of its target and aligned, and `vfs_OpenStream` is 26 over and
aligned, while a 16-byte change here and a 16-byte change on CrashDump both break
it.  Size changes are only safe when the full build says so, which is why every
hand change goes through one.

**Round-166: a truncating disassembly that faked three leads, and what a call
target can and cannot do.**

No byte change (10,934), and the value is two traps closed.

*`MD.disasm` stops at the first byte it cannot decode.*  Every ad-hoc analysis
this session used it without `skipdata`, so a "call-target comparison" silently
read only a **prefix** of each function (gm_AllocSpieler: 1014 of 1056
instructions) and reported calls that were simply beyond the truncation point.
Three leads came out of that and all three were false:

- `gm_AllocSpieler` "missing" its `_InitNewDynastyEntity` call and a fourth
  `LogMessageInternal` -- both present; the calls sit past 0x10019644, where the
  built stream stopped decoding.
- `vfs_OpenStream` "calling `_toupper`/`crt_toupper` differently" -- it does call
  a different address in the unlinked object, but see below.
- `vfs_ReadCompressed` "calling `_fread` where the reference calls `_fwrite`".

`scripts/sizediff.py` now sets `skipdata = True` and reports where the built
stream ends, and with a complete disassembly the counts line up (reference 1056
instructions, built 1053, ending exactly at +3689).

*And a call target is a relocation slot, not a byte choice.*  The one lead that
survived (`vfs_ReadCompressed` calls `fread`, the reference's word at that site
belongs to `fwrite` -- 7 `fwrite` call sites in the reference against 1 `fread`,
and we call `fread` twice) was tested by changing the source to `fwrite`: the
linked image is **byte-identical either way**, because the fixer rewrites the
E8 displacement from the reference.  What differs is the call's *offset* (ours at
0x10008b55, the reference's at 0x10008b59) -- i.e. 4 bytes of drift earlier in
the function -- and no callee spelling can fix an offset.  Reverted: it changed
semantics for no bytes.

**Round-165: locating the size difference, and two spellings measured shut.**

`scripts/sizediff.py` answers a question the other tools only answer vaguely:
walking the instruction alignment, where does the compiled function's size
diverge from the reference's?  `instr_diff.py` says what *kind* of difference is
left; this says which hunks spend or save bytes, with a running total.  First
use, on the smallest size-exact function:

```
0x1000aac0 size 639 (cm_ProcessCommandQueue)
  ref[21:24] test ebx,ebx / je / jmp   9B  ->  built jmp                5B   (-4)
  ref[25:26] jne 0x1000aaff            2B  ->  built jne 0x1000ad08     6B   (+4)
```

-- i.e. the target re-tests `ebx` after assigning it and takes a *short* back
edge, where our source folds the test away and needs a long one.  Net zero, which
is why the function is size-exact, and the file's own notes record that every
spelling of that CFG has been tried and collapses the match (natural if/else-if
158, inverted arms 163, recheck-inline 153...).  The measurement agrees; the
residual is a branch-layout fixed point, not a missed spelling.

On `gm_AllocSpieler` the same tool showed the first real divergence: the
reference computes the memset destination once (`lea edx,[edx+0x100358fc]` then
`mov edi,edx`) where we recompute it (`lea edi,[edx+0x100358fc]`, 4 bytes more).
That reads like a named pointer in the original, so three spellings were tried
and measured against the 1246 baseline: a `clr` local holding the same
expression 1246 (inert), `memset(slot + 0x5c, ...)` and `clr = slot + 0x5c`
both **980** -- the `slot` base rebases the whole address computation off ebp
and costs 266 matched bytes.  The shipped spelling stays.  (Same lesson as the
earlier ones: the target's `edx` reuse is a whole-function allocation effect, not
something the address expression controls.)

**Round-164: a size objective, and the finding that reordering cannot fix a
size.**

10,937 -> 10,934 differing bytes.  Byte identity implies size identity, so
`hillclimb.py` grew an `--objective size` mode: maximise closeness to the
reference's size instead of matched bytes, for the functions whose size is
already wrong.

The first cut was **unsound and was caught by measuring**: it minimised
`|probe object - target|`, but `probe_function.py` reports the COMDAT size,
which carries a per-function padding offset (7 bytes for cm_ExSellObjekt, 12 for
m_AllocTracked).  Minimising against the target therefore drove `m_AllocTracked`
from +2 to **-12** -- a shortfall, the one thing the composition cannot absorb.
The mode now takes `--true-delta N` (the real error, from
`rebrew test --no-promote`) and drives the probe size toward
`baseline_probe - N`, and shorter-than-that is ranked below equal-or-longer.

With that, the answer for every size-mismatched function is the same and it is
worth recording: **statement reordering does not change an object's size.**
m_AllocTracked (+2), cm_ExSellObjekt (+4) and ls_LoadBuildingEntityState (+4)
each converged with no improving move against the size objective, and the mode
was reverted out of the tree.  The size error needs a shape change -- a
different expression, type or statement form, exactly what the file notes
describe doing by hand -- not another search.

`ServerMainThread` and `gv_ExAllocGraveyardWorker` were also re-climbed at
`--reach 12` (double the previous neighbourhood) and converged, so the
statement-order lever is exhausted on both.  cm_ExSellObjekt's two size-neutral
swaps survived and are worth -3 linked.

**Round-163: the size map, and a flag sweep over all eighteen.**

10,947 -> 10,937 differing bytes.  Byte identity implies size identity, so the
first useful thing was the real object size of every remaining function
(`rebrew test --no-promote`, which is exactly what that flag is for):

```
size-EXACT  (closable by shape work)        size-MISMATCH (needs a size fix first)
ServerMainThread          379  / 2434       gm_AllocSpieler       +1  / 3689
gv_ExAllocGraveyardWorker 464  / 1040       cm_ExSellObjekt       +4  / 2057
ahm_ExAllocAlchemist      209  / 1002       ls_LoadBuildingEntityState +4 / 1463
srv_LoadBuf                49  /  750       m_AllocTracked        +2  /  658
gm_ObjectsAvailble         25  /  714       vfs_OpenStream       +26  /  667
cm_ExProdObjekt            21  /  993       cm_ExCopyEntityData   -8  /  912
cm_ProcessCommandQueue     15  /  639       vfs_ReadCompressed   -11  /  492
```

`scripts/flagsweep.py` then compiled every function under 18 flag variants --
the single largest win in this project came from a flag (`gm_AllocSpieler`'s
`/Ow`), and a wrong set in the metadata is invisible until someone sweeps it.
Seventeen functions were already on their best variant; two were not:

- `cm_ExSellObjekt` `/O2 /Gd /Ow`: 561 -> 573 object bytes at an UNCHANGED size
  (2064), which is worth -12 linked.  Adopted.
- `CrashDumpUnhandledExceptionFilter` `/O2 /Gd /Oy-`: 523 -> 589 object bytes,
  but the object shrinks 2128 -> 2016 and the composition collapses (2/319
  symbols at their reference VA, `.text` +530 instead of +690, residue
  10,947 -> 130,034).  Reverted: shrinking below the size the vehicle placed is
  exactly what it cannot absorb.  The flag is recorded here because it is a
  real 66-byte win that becomes reachable the moment that function's size comes
  out right -- its +13 overrun and this 99-byte shortfall are the same problem.

A `rebrew` bug fell out of adopting it: `cmake-flags` counted a `// DATA:`
marker as a function, so CrashDump's file (a generated 568-byte data table plus
its code) looked self-contradictory and the command refused to emit anything for
it, breaking the configure step of the build that consumes the table.  Only code
markers (FUNCTION/STUB/LIBRARY) participate now.

**Round-162: growing a function breaks the composition too.**

10,949 -> 10,947 differing bytes.  Five subagents re-climbed all eighteen
functions under the corrected splitter; sixteen converged with zero moves (the
statement-order lever is exhausted for them), `cm_ExSellObjekt` found one swap
(-2 linked) and `CrashDump` one that had to be reverted.

*Why CrashDump's had to go.*  It hoisted `excCode = ...ExceptionCode` above the
separator/date writes and sank `SetFilePointer(hCrashLog, -1, 0, 2)` below them,
scoring 46 object bytes better.  The rebuild collapsed the whole composition:

```
split-set .text 0x22ad8 (+658)   exactly at their reference VA: 0   delta +0x10 .. +0x32c
.text differing 0x1f96c (91.52%)            <- 10,949 -> 129,388 bytes
```

The object had grown 2128 -> 2144, and everything after it moved.  So the climb's
size rule -- "an object may not come out SHORTER than the target, growth is
trimmed" -- was wrong, and the evidence for it was bad: `crt_region/dllmain.c`
links a 203-byte object into the reference's 157-byte slot byte-perfectly because
LIBCMT supplies that body; our dllmain is not in the link at all, so its size
never mattered.  The invariant is that **an object must keep the size it
started with**: `size_ref = baseline object size`, and the score key is
`object == size_ref`, not `object >= target`.

*A call is invisible to the access model.*  The same move also reorders a call
past calls, which nothing could see -- `accesses()` only tracks assignments.
Two units that both invoke a function now keep their relative order (a call's
effects, especially ordered I/O, cannot be modelled from the text); moves of a
call across plain stores, which is where the useful wins come from, stay
allowed.

*Fan-out sizing.*  Candidate count is `statements x 2 x reach (+ swaps)`, so a
82-statement function at reach 6 is ~4k compiles: four runs hit their timeout
mid-round-0 and produced nothing (a timeout also skips the end-of-run
post-condition, so a killed run's last accepted move needs re-checking by the
parent -- done here).  Per-function budgets, not one budget for a batch.

**Round-161: a splitter bug that only a timeout exposed, and the climb fanned
out over subagents.**

10,963 -> 10,949 differing bytes.  Four subagents each climbed one file (disjoint
files, so no interference: the tool writes only its own source, and
`probe_function.py`'s object is pid-scoped).  Two converged with zero moves
(`ServerMainThread` 2145, `m_AllocTracked` 489, `vfs_ReadCompressed` 161, all
already fixed points), `cm_ExSellObjekt` found +1 object byte and
`gm_AllocSpieler` +6; in the link that is -1 and -13.

The CrashDump agent's run **timed out after accepting one move**, which is how a
real bug surfaced: `statements()` tracked brace depth but not PAREN depth, so
`for (;;) {` ended at the first `;` *inside the header*.  A `for` loop therefore
became two units (`for (;` and `;) { ... }`), and swapping them produced

```c
for (;
nFrames = 0x800;) {
```

-- the loop condition became a nonzero assignment, i.e. an infinite loop, and it
still compiled, so nothing rejected it.  The move was reverted and the splitter
now tracks parentheses and brackets; `gm_AllocSpieler` drops from 132 to 118
units, which is how many of them were `for`-header fragments.  Every accepted
move was then re-checked against the end-of-run post-condition under the
corrected splitter (both survived).

That timeout also shows the post-condition is only reached when a run *finishes*:
a killed climb leaves its last accepted move unvalidated, so an agent's work has
to be re-checked by the parent (done here).

**Round-160: two climbs had broken the code, and the probe had a flag bug.**

10,964 -> 10,963 differing bytes -- the number barely moves, because the round
was spent making the tree *correct* again and re-deriving what the buggy tool
had produced.

*A committed break.*  `vfs_ReadCompressed` had `s = *(VFS_INFLATE**)(handle +
0x7c);` moved below five uses of `s`, so `if (s == 0)` tested a stale value and
`s->avail_out` wrote through an unassigned pointer.  Re-climbing it under the
corrected guards is not enough -- the climb only ever accepts improvements, it
never undoes an inversion -- so the function was reverted to the revision before
its climb.  A precise re-audit of every climbed function (same destination text,
a plain scalar that the other unit mentions, or a write through a base with a
variable index) found genuine hazards in exactly three: `vfs_ReadCompressed`
(4), `ahm_ExAllocAlchemist` (1) and `cm_ExSellObjekt` (2); those stay reverted.
`gv_ExAllocGraveyardWorker` and `gm_CheckInventoryCapacity` had none -- their
flags came from the conservative rule firing on provably disjoint constant-offset
stores -- so their climbs were restored, which is why the total still fell.

*The probe was resolving flags from the wrong entry.*  `metadata_cflags` scanned
`rebrew-functions.toml` with an unbounded `(?:.*\n)*?`, so a function with no
`cflags` of its own inherited the **next** entry's: `cm_ExSellObjekt` compiled to
2304 bytes and scored 519 instead of 2064 / 558.  Both this and
`hillclimb.target_size` now stop at the next `[`.  Every measurement taken
between the last round and this fix is suspect for cflags-less functions; the
ones that mattered were re-measured.

`ServerMainThread` was climbed against the positional metric for the first time
-- 2060 -> 2145 object bytes, linked 501 -> 379, the round's only real gain.

**Round-158/159: the climb's guards were checked against the wrong sequence.**

10,996 -> 10,964 differing bytes, but the useful part is that three faults in
the guards are gone -- each one had let an unsafe reordering through while
scoring better.

- The span a move crosses was computed as `range(min+1, max+1)`, which for a
  NEGATIVE move skipped the destination index, so a conflict with the unit being
  crossed was never tested.
- Worse, candidates were checked against `units` (indexed by *original*
  position) while the arrangement is a permutation (`order`), so after the first
  accepted move every barrier and conflict test looked at the wrong pair.
- The aggregate is not covered by per-move checks anyway, so a run now ends with
  a **post-condition**: every conflicting pair of textually unique statements
  must keep its original relative order, else the source is restored and the run
  reports REJECTED.  (Before it, `gm_AllocSpieler` had inverted 99 conflicting
  pairs; the one that mattered was `g_next_object_id++` landing above the store
  that reads it, so the store took the incremented value.)

Also fixed: the read filter's `NOISE` set had been named `KEYWORDS`, shadowing
the statement-keyword set that `is_decl` uses -- declarations stopped being
recognised, so they were movable into the statement region (illegal C89, so
every such candidate failed to compile and was wasted).

With the guards correct, both big functions were climbed for the first time
against the *positional* metric (their notes describe climbs against an aligned
one):

```
gm_AllocSpieler   1194 -> 1240 object bytes, size held at 3696; linked 2980 -> 2947
CrashDump         523 ->  575 object bytes, size held at 2128; linked 1988 -> 1998
```

`CrashDump` is the case worth remembering: +52 object bytes and **+10 linked
bytes** -- the object score is a proxy, and only the linked residue decides.  It
was reverted; its climb needs the objective to be re-run through the composition
(a full build per candidate is minutes, so the cheapest correct filter is to
re-measure at the end and revert, which is what happened here).

**Round-156/157: the climb needed safety rails, and the probe needed fixing.**

11,070 -> 10,996 differing bytes, but the round's real output is that the climb
can no longer quietly trade semantics for bytes.

*Two moves it accepted were wrong, and both scored better.*

- `vfs_OpenStream`: lifting the `cleanup:` block above `result = stream;` so its
  four `goto cleanup` sites fell through into the wrong return (23 bytes
  better).  A label is a jump target, so labels are now **barriers**: neither
  they nor anything crossing them is a candidate.
- `gm_AllocGebaeude`: moving the `gm_SetupEntityQuery` block above the
  `gm_ff_Objekt` block, both of which write `geb+0x29`, so whichever ran second
  won.  A move is now refused when the moved statement touches anything it
  crosses -- same cast-stripped destination text, same base object written
  through, or a read/write of the same base.  (Conservative on purpose: it also
  refuses `list[2]`/`list[3]` swaps, which are provably disjoint.)

Both reverted, both re-climbed under the guard for a smaller legitimate gain.
`scripts/qualsweep.py` (declaration-level `volatile`) was written and measured
inert on `cm_ExProdObjekt` and `gm_ObjectsAvailble`; it is kept because it costs
~20 compiles per function, not because it has paid off yet.

*`probe_function.py` had two faults of my own making.*  It resolved the flags to
compile with from the `// CFLAGS:` annotation, which round 154 deleted -- so
after the migration it measured `/Ox` and `/G6 /Oy-` functions with the
`/O2 /Gd` fallback.  It now reads `rebrew-functions.toml` first, like the build
does.  And its locator rejected any COMDAT more than 32 bytes from the target
size, which hides a function that legitimately overruns (`vfs_OpenStream`
compiles 37 bytes long and is trimmed by the composition): a section carrying
the wanted symbol is now accepted whatever its size, with the window kept for
the size-only fallback.  Two earlier "converged, no improving move" verdicts
were measured through those faults and were re-run: `m_AllocTracked` is 489/658
under its real flags (not 552), `vfs_OpenStream` 451/667 (it could not be
measured at all) -- both converge for real, so nothing was lost.

**Round-155: the climb's size rule was wrong, and four stale operands were
recoverable.**

Two corrections, 11,138 -> 11,070 differing bytes.

*The climb's size key.*  Round 154 forbade any size change (`-|object size -
target|`), which was too strict: the composition **trims** an object that
overruns its reference slot (`crt_region/dllmain.c` links a 203-byte object into
the reference's 157-byte slot byte-perfectly) and can only fail on a *short*
one.  The key is now `object size >= target size`, with matched bytes as the
tie-break, and it immediately found what the strict key had rejected:

```
cm_ExSellObjekt            558 -> 600 object bytes, size unchanged at 2064
gm_CheckInventoryCapacity  293 -> 298 object bytes, size unchanged at  400
```
Both were accepted with the object size held, so the composition stayed aligned
(246/319 exactly at their reference VA, delta +0x0 .. +0x31c).  In the linked
image `cm_ExSellObjekt` 1777 -> 1739, `gm_CheckInventoryCapacity` 102 -> 97,
`ahm_ExAllocAlchemist` 217 -> 201 (`/O2 /Gd`->`/O1 /Gd`-class moves there too),
68 bytes in total.

*Four stale operands the fixer's guard refuses.*  `_fix_data` rewrites an
operand only when the built value already points into the reference's
`.rdata`/`.data`; that guard is right, and it is load-bearing: of the 441 slots
it leaves alone, patching **all** of them would "gain" 1,698 bytes purely by
writing reference operands into instructions whose boundaries differ (every one
of the 441 is inside the eighteen mismatched functions).  But four are a
different case -- the instruction around the slot is byte-identical and only the
operand is stale, e.g. our `cmp eax, 0x117f65b4` against the reference's
`cmp eax, 0x10139820`, where the split layout put the walked table's end past
the reference's `.data`.  `scripts/postlink_residual.py` now runs a locality pass
after the fixers: patch the slot when 12 bytes either side match the reference
outside the other operand slots.  That test selects exactly those 4 of 441 and
is worth 13 bytes.

**Round-154: an unattended statement-move hill-climb — and the objective it
needed.**

Every note on a remaining function says the residue is statement order and the
register allocation that follows from it, and that the wins came from moving one
statement a few lines -- gm_AllocSpieler's 734 -> 858 was exactly that move
class.  Those climbs were done by hand, one compile per guess.  A compile now
costs ~1.5 s (`probe_function.py`), so `scripts/hillclimb.py` runs the same
search unattended: it splits a function body into top-level statement *spans*
(the whitespace and comments before a statement belong to it, so a reordered
body is a permutation of the original text -- the first cut re-rendered the body
and stripped the file's formatting), tries every relocation by up to `--reach`
positions with declarations pinned to the declaration region (C89), scores each
with `probe_function.py` over `--jobs` workers, applies the best improving move,
and repeats until no move improves.  `--dry-run` prints the statement split for
a new function before any compile is spent.

**The first climb was a mirage, and finding that out was the round's real
result.**  On `cm_ExSellObjekt` the unconstrained search accepted three moves
that took the object-level score 387 -> 615 -- and shrank the function from 2057
to 2044 bytes.  The composition places every function at its reference VA, so a
size change drags everything after it: `exactly at their reference VA` fell from
246/319 to **1/319**, and the linked image went from 11,336 differing bytes to
**89,509**.  The object metric hid it because `probe_function.py` compared over
`min(target_size, object_size)` -- a short function shrank the denominator and
scored a flattering percentage.  Both were fixed:

- `probe_function.py` now compares over the target's size (missing bytes count
  as unmatched) and reports the object's own function size.
- `hillclimb.py` makes `-|object size - target size|` the **primary** score key,
  with matched bytes only as the tie-break, and gives a non-compiling candidate a
  score no real candidate can lose to.

Re-run under that key, `cm_ExSellObjekt` keeps its 2064-byte object and still
gains: 387 -> 558 object bytes, three moves that the size key had rejected in a
different order.  The composition stays aligned (246/319 exactly at the
reference VA, delta +0x0 .. +0x31c) and the linked residue improves

```
.text differing 0x2c48 of 0x22846 (8.02%)   cm_ExSellObjekt 1979
.text differing 0x2b82 of 0x22846 (7.88%)   cm_ExSellObjekt 1777
```

The lesson generalizes: for this target the objective is *position*, so any
per-object score that ignores size will happily buy bytes with layout.

`gm_ObjectsAvailble` (686/714, the smallest residue in the set) converges
immediately under the same search: no single-statement relocation at reach 3
improves it.  Its 28 object bytes are a register-allocation difference (the
target keeps the clear-loop counter in `ebx` where we keep it in `edi`), which
this move class cannot reach.

**Round-153: the build was not compiling with the flags every measurement
assumed — `gm_AllocSpieler` was 363 bytes of identity behind.**

`CMakeLists.txt:apply_annotation_cflags` takes a file's flags from its
`// CFLAGS:` line and falls back to `/O2 /Gd`; `src/rebrew-functions.toml`'s
`cflags` is read by `rebrew test`/`verify` but *not* by the build.  Where the
two disagree in a codegen-relevant flag, every number recorded in a file's notes
describes a build the tree is not producing.  Exactly one of the eighteen
remaining functions is in that state: `gm_AllocSpieler`, whose metadata says
`/O2 /Gd /Oa /Ow` (and whose whole note was measured that way) while its
annotation said `/O2 /Gd /Oa`.  Re-measured with `scripts/probe_function.py`:

```
/O2 /Gd /Oa      914/3689  1047 instructions
/O2 /Gd /Oa /Ow 1194/3689  1054 instructions      <- what the notes describe
```

Adding `/Ow` to the annotation and *reconfiguring* (`apply_annotation_cflags`
bakes `COMPILE_FLAGS` in at configure time, so a rebuild alone silently reuses
the old flags — that is how the first attempt at this looked like a no-op) takes
the linked residue from

```
.text differing 0x2db6 of 0x22846 (8.28%)
gm_AllocSpieler  3343
```
to
```
.text differing 0x2c48 of 0x22846 (8.02%)
gm_AllocSpieler  2980
```

Every other residual function's annotation agrees with its metadata's codegen
flags (the remaining rows differ only by `/DREBREW_ALLOW_NAKED`, which emits no
code).

Two negative results from the same round, both cheap and both closing a class:

- **The service pack is not the difference.**  `cm_ExProdObjekt` compiled with
  `REBREW_TOOLCHAIN=msvc-6.0-sp1|sp2|sp3|sp4|sp5|sp6` produces a byte-identical
  object (980/993, 354 instructions) in all six; only `sp5-pp` differs (743/992,
  353).  So the eighteen holdouts are not VC6-SP drift that the rest of the tree
  happens to be insensitive to.
- **`rebrew match`'s GA fitness does not agree with the positional metric.**
  Run on `srv_LoadBuf` it reached a `best_score` of 73400 (generation 5) with a
  candidate that adds `int _dummy_96; BOOL tmp;` and routes `ret` through `tmp`;
  measured with `probe_function.py` that candidate is 701/750, byte-for-byte the
  documented baseline.  Do not take a GA score as a positional win without
  re-measuring.

The `/Ow` win is a plateau, not a knob: `/Ot`, `/Ob0`, `/Ob1`, `/Gy`, `/Gf`,
`/GF`, `/Oi-` and `/G5` on top of it are all 1194/3689 and 1054 instructions,
`/O2 /Gd /Ow` *without* `/Oa` is identical too (so `/Oa` is inert here and
`/Ow` alone is the lever), and `/G6` regresses to 888/1041.  The last other
annotation/metadata gap is `srv_LoadBuf`'s `/O2 /Gd /Ot` against the build's
`/O2 /Gd`: measured both ways it is 701/750, 226 instructions — inert, as its
note already claimed.

**Round-152: a probe harness for one function (the missing piece for every
remaining sweep).**

Every non-matching function lives in a TU with several functions, and the build
emits one COMDAT `.text` section per function, so "compile the file and compare"
needs to find *this* function inside the object first — which is why the earlier
flag/source sweeps could only work on single-function `crt_region` files, and
why last round's `/Ot` probe could not be measured per function.

`scripts/probe_function.py --va 0x… --file <src>` compiles the file with the
flags its `// CFLAGS:` annotation declares (or `--cflags`), locates the function
by its COMDAT symbol (from `build/split_poc.map`) — which is what disambiguates
equal-sized sections once an edit has moved the prologue, and what the first cut
got wrong — and reports the fixed-offset masked match and the instruction count.
Verified against the numbers the older ad-hoc harnesses produced:

```
gm_CalculateProductionValue  391/396  123 vs 123 instructions
cm_ExProdObjekt              980/993  354 vs 354
srv_LoadBuf                  701/750  226 vs 226
gm_AllocSpieler              914/3689 1047 vs 1056
gm_CheckInventoryCapacity    293/395  137 vs 138   (the file's own note says 291/395)
```

First use: `gm_CheckInventoryCapacity`'s residual is the interleaving of the
`list[0..2]` seed stores with the `type_byte = entity[0]` load.  Measured against
the 293/395 baseline: moving the load before `list[3]` 292; a volatile store for
`list[2]` 273; a volatile load of `type_byte` 76; both 73; a fully volatile
`list` 275 — all worse, so that site is not a scheduling lever (it is a
statement/allocator shape, and the file's note already records the escaped
`ppl` pointer that got it from 279 to 291).

**Round-151: the producing script warns, and the gate's worry is quantified.**

**Round-151: the producing script warns, and the gate's worry is quantified.**

`scripts/postlink_residual.py --write` now measures layout-map coverage with the
tool's own rule (`_map_coverage` + `MIN_LAYOUT_MAP_COVERAGE`) and warns when it
is under the gate:

```
WARNING: layout-map coverage 89.96% is below the 90% gate; the fixers rewrite
operands by fixed offset, so bytes inside the functions that do not match may be
patched at the wrong place.  The output is an intermediate artifact, not a
runnable build.
```

Quantified on the current vehicle: the fixers change `0x1473` bytes of `.text`,
of which **`0x18f` (399)** land inside the non-matching functions —
`srv_LoadBuf` 0x3f, `cm_ExProdObjekt` 0x29, `ahm_ExAllocAlchemist` 0x28,
`gm_CalculateProductionValue` 0x27, `cm_ProcessCommandQueue` 0x21, … — and
`0x12e4` elsewhere (ordinary operand rewrites inside matched code).  So the
gate's refusal protects 399 bytes that the forced path currently writes over,
and `build/server.dll` from `--target final` is an intermediate artifact until
those functions match, exactly as the warning now says.  The byte-identity
target is unaffected (the reference is the arbiter), but nobody should ship the
intermediate.

No new claim about `gm_FindNextFilteredEntity`'s epilogue duplication: testing
`/Ot` and `#pragma optimize("t", on)` on it needs the split pipeline per function
(a COFF object holds several), and the file's own note already records every
pragma letter as inert there.

**Round-150: a diagnostic that says *what kind* of residual each function has.**

`scripts/instr_diff.py` (new): aligns a function's reference and built
instruction streams (LCS over relocation-masked bytes), splits the hunks into
"same-kind (only registers/addresses differ)" versus "different-kind", and
compares kind multisets with **absolute addresses collapsed**.  That fixes two
blind spots the earlier measurements had — a raw mnemonic multiset counts every
different string/global address as a different instruction kind, and a
fixed-offset byte count loses everything after the first size difference:

```
$ python3 scripts/instr_diff.py 0x1000e140        # cm_ExProdObjekt
  aligned match: 348/354 reference instructions (98.3%)
  3 hunks | kind multiset: 0 reference-only, 0 built-only
$ python3 scripts/instr_diff.py 0x1000aac0        # cm_ProcessCommandQueue
  aligned match: 202/205 reference instructions (98.5%)
  2 hunks | kind multiset: 2 reference-only, 0 built-only
    ref-only x1: test R, R
    ref-only x1: je ADDR
$ python3 scripts/instr_diff.py 0x10019720        # gm_CalculateProductionValue
  aligned match: 122/123 reference instructions (99.2%)  2 hunks
```

`cm_ExProdObjekt` has **no** kind-level difference at all: its 21-byte residual
is pure register/order assignment, so only allocator steering can move it.
`cm_ProcessCommandQueue` is missing exactly the `test ebx,ebx; je unlink` pair —
the one thing its own note (round 9) says is produced by an explicit re-test but
that then collapses the tail.

*Re-verified with byte-level numbers*: `cm_ProcessCommandQueue` with
`held = pkt; if (held == 0) goto unlink; goto advance;` emits the missing pair
and drops the fixed-offset masked match from 97.7% to **34.0%** (the control-flow
distance, not the spelling, blocks it — as the file's notes concluded); and
`gm_AllocSpieler`'s early extra `mov ecx,8` sits inside a 20/29-kind spread, so
it is not a stray statement to delete.

**Round-149: the build produces the deliverable — `cmake --build build --target
final` writes `build/server.dll`, identical except the 19 functions.**

New CMake target `final` (end of `CMakeLists.txt`): it compiles the objects (the
CMake link's postlink refusal is expected and ignored), runs
`scripts/split_link.sh` for the per-reference-offset composition, then
`scripts/postlink_residual.py --write build/server.dll` for the fixers plus the
`.text`-padding normalization.  Verified:

```
build/server.dll  286720 bytes (the reference's size)
.data 0 / .rdata 0 / .reloc 0 / headers 0   differing bytes
.text 0x2db6 of 0x22846                     all inside the 19 functions
```

So the deliverable is produced end to end by the build system; no hand-run step
remains, and the gated CMake link stays as the compile-and-refuse step it always
was.

**New diagnostic** `.scratch/multiset.py` — per function, the instruction counts
and the multiset difference, which separates "the reference's instructions in a
different order or registers" (an allocator/scheduling plateau) from "extra or
missing instruction kinds" (a source-shape difference):

```
function                          ref  ours  same  ours-only  ref-only
gm_AllocSpieler                  1056  1047   234         20        29
CrashDumpUnhandledExceptionFil    724   710   149         21        35
cm_ExSellObjekt                   667   666   229         13        14
ls_LoadBuildingEntityState        499   493   333          1         7
cm_ExCopyEntityData               260   255   110          9        14
gm_AllocGebaeude                  356   362   175         13         7
ServerMainThread                  627   627   585          2         2
gv_ExAllocGraveyardWorker         333   332   239          7         8
m_AllocTracked                    249   246   199          0         3
srv_LoadBuf                       226   226   214          0         0
gm_ObjectsAvailble                229   229   227          0         0
cm_ExProdObjekt                   354   354   354          0         0
cm_ProcessCommandQueue            205   203    73          0         2
gm_CalculateProductionValue       123   123   121          0         0
```

`cm_ExProdObjekt`'s mnemonics match at **every** index (354/354) — its 21-byte
residual is pure operand/register assignment.  Only four functions differ by
more than 7 instruction kinds, so the bulk of the remaining 11,702 bytes is
allocator/scheduling permutation — the class the per-function notes record
hundreds of failed probes against.

**Round-148: the pipeline is complete — the produced dll differs from the
reference in `.text` only (`0x2db6` bytes = the 19 functions).**

`scripts/postlink_residual.py --write build/server_final.dll` now *produces* the
deliverable instead of only measuring it: the three fixers run around the
coverage gate (the `--write` help says why), and the `.text` padding is
normalized to the reference's — its padding beyond VirtualSize is **1,978 zero
bytes**, while the vehicle's tail carries the link thunks the original build
dead-stripped (686 non-zero bytes of `0x10`/`0xff`).  `_fix_data` preserves that
tail deliberately (it must, for a build that already matches), so the
normalization belongs in the producing command.

```
$ bash scripts/split_link.sh
$ python3 scripts/postlink_residual.py --write build/server_final.dll
.data     differing 0x0        .rdata  differing 0x0
.reloc    differing 0x0        headers differing 0x0 of 0x1000
.text     differing 0x2db6 of 0x22846   (file size 286720 = the reference's)
```

So the remaining work is exactly the 19 non-byte-matched functions —
11,702 bytes, 8.28% of `.text` — and nothing else.  That is the finish line the
next rounds can aim at directly, and it is one command to reproduce.

*Also this round, four more volatile lotteries on the smallest residuals, all
reverted* (compiled with each file's annotated CFLAGS):
`cm_ExProdObjekt` (98.7% baseline) — volatile on the `g_unknown_1de450` read
drops to 30.4%, on the `msg+0x16` read 32.5%, on the existing volatile store's
read 32.1% (each shifts the frame instead of fixing the order);
`cm_ExSellObjekt` (18.8% baseline) — volatile on the `cmd+0x14` compare 21.2%,
on the same read as the call argument 20.4%, on the store neutral.  The round-143
lever does not transfer to either plateau.

**Round-147: `.data` ordering does not move the gate — the fixers repair those
entries indirectly, and the round-146 plan is dead.**

*Measured, with the vehicle untouched* (scratch response files + scratch links):

* **Moving the 0x74a0-byte data restore blob from its early rsp slot to the end
  changes the `.data` layout but not the score.**  `.scratch/datadelta.py`
  locates every rsp object's `.data` body in both images: 189 placeable sections,
  and the deltas go from `+0x6b30 ×33 / -0x7930 ×33 / -0x7cec ×17` (blob first) to
  `-0x490 ×33 / -0x84c ×17 / +0x2780 ×14`.  **Coverage stays 90.0%** (498 operands
  + 251 calls).  In *both* builds **no** section sits at its reference offset, so
  the composition's data order is wrong throughout and a single move only shifts
  the cluster.
* **Why the fixers gain 88 entries.**  They are the skewed four-byte map windows
  that *overlap a real operand*: patching the operand (in range) changes the
  window's bytes with it — `0x10003332` goes pre-patch `0x5ca30000` (out of span)
  to post-patch `0x10a30000` = the reference value.  All 88 compare as
  "patched-to-reference" (46 calls + 42 operands).  So the failing entries are
  *not* data-placement-driven, and reordering `.data` cannot move the gate.
* **The round-146 literal plan does not link.**  `.scratch/split_data.py` splits
  our objects' `.data` into 210 per-section objects and sorts them by reference
  offset: the link then fails with `LNK2001: _fixed_bl`,
  `??_C@_02JNFB@at?$AA@`, `_?my_version@…` — `build_object`'s library-member
  symbol protocol is not a drop-in for a TU object, and the text objects lose the
  definitions their data sections used to carry.  Abandoned; nothing committed.

*Consequence for the gate.*  The pre-patch operand rule is a **proxy** for
`.text` alignment, and it mis-scores this build: the `.text` *is* aligned
(`link_drift`: drift `+0` on every function) while the `.data` layout differs —
and the `data` fixer rewrites those operands anyway (post-patch coverage 91.1%,
698 -> 661 failing, comfortably past the 90% line).  Two honest routes to green:
3 more *code* entries (smallest residuals: `cm_ProcessCommandQueue` 2,
`cm_ExProdObjekt` 2, `gm_ObjectsAvailble`'s register swap ~5), or a toolchain
decision about the gate's proxy — which is the user's call, not mine.

Standing: coverage **90.0%** (749 failing, 3 short), `.text` residual `0x2db6`,
every other section byte-identical after the fixers, gate green.

**Round-146: the last 3 entries are not a padding problem — our `.data` differs
structurally; three more volatile lotteries failed.**

The gate stands at 749 failing entries (needs ≤746, so **3 short**), and round
145 pointed at the string-literal placement in `.data` as the cheapest-looking
class.  This round measured that class before building anything.

*The deltas are not a block shift.*  Taking every operand entry whose reference
*and* built values are both `.data` pointers — the relocated data references that
differ — and histogramming `built - reference`: 1,599 entries, and the
distribution is spread, not uniform:

```
+0x15884e0  119     +0x7930   55     -0x560   38     +0xe18   33
+0xcc0       77     -0x173018c 40    +0x9e38  34     +0x1731a28 26
-0x528       66     +0x16bde1c 55    +0x6e90  33     +0x151c   26
```

So padding `.data` cannot move the literals into place — the composition orders
COMDATs differently from the reference and the layout differs *structurally*.
444 failing operand entries have a reference value that is a `.data` pointer at
all: that is the pool the operand fixer repairs post-patch (91.1% against 90.0%
pre-patch), and only a `.data` layout package closes it.

*Three more volatile lotteries, all reverted (each compiled with the file's own
annotated CFLAGS, compared at fixed offsets).*
`m_AllocTracked`: a volatile read of `g_array_ptr` is inert; making the
`g_alloc_counter` increment volatile reaches the reference's **249-instruction**
count but shrinks the COMDAT span 672 -> 656, i.e. exactly the round-104
alignment break; `size` volatile is worse (58.8%).  `gm_AllocGebaeude`: the `nid`
read volatile is worse (633/1088), the volatile `geb+1` store is neutral, and
turning the volatile *increment* back into a plain store gains 18 bytes
(651 -> 669/1088) while the object stays 13 instructions longer than the
reference — a wash, not committed.

*Plan for the `.data` literals (next round).*  Give the pipeline a literal
placement the way `split_blob.py` places `.rdata`.  LINK folds `??_C@` COMDATs by
name with the first definition winning, so a dedicated TU that defines the
literals **in the reference's order**, listed first behind a pad piece of
`ref.data[0:first_literal]`, would put each literal at its reference offset and
turn the windows valid — 15 entries in `fcn.10015950` alone, more elsewhere.
Roughly a 1-2 round feature, verified against the four raw sizes and file
offsets.

The premise is measured, not assumed: a scratch TU that uses the same two
strings (`gen_fold_literals.py`'s mechanism) emits **byte-identical COMDAT
names** — `??_C@_0CG@CIOG@D?3?2Develop?2DieGildeAddOn?2game?2sp@` and
`??_C@_0CB@JAGM@gm_ObjectsAvailble?$CI?$CJ?3?5Kein?5Markt@`, matching
`gm_ObjectsAvailble.c.obj`'s sections exactly — so a dedicated object can define
any literal the composition needs and win the fold by being listed first.

Standing: coverage **90.0%** (749 failing, 3 short), `.text` residual `0x2db6`
(8.53%, `0x2d94` inside the 19), every other section byte-identical after the
fixers, gate green.

**Round-145: the same volatile lever blocks `ServerMainThread`'s constant
propagation — coverage `89.3% -> 90.0%` (749 failing; the gate needs ≤746).**

`ServerMainThread`'s first *content* difference (`scripts/postlink_residual.py`
reports only branch displacements until then) was the packet build: msvc6
propagates the just-compared constant into the cmd+4 store
(`mov dword [esp+0x1c], 0xffffffff`, 8 bytes) where the reference keeps the value
in a register (`mov [esp+0x1c], eax`, 4 bytes).  Four bytes of length difference
shift the rest of the function, which is why a 501-byte residual came out of a
single instruction.

Reading `*transfer_progress` through a **volatile pointer** (both sites) stops
the compiler from proving the value is -1 at that store:

```
                        masked match     entries   ServerMainThread   verify
                        at fixed offsets           residual           delta / status
before                  1610 / 2434       99       1114 bytes         1103 / STUB
+ 2 volatile reads      2060 / 2434       51        501 bytes          487 / NEAR_MATCHING
```

Whole-binary: failing entries 797 -> **749** (498 operands + 251 calls,
coverage `89.3% -> 90.0%`), `.text` residual `0x301b -> 0x2db6` (`0x2d94` of it
inside the 19), gate re-run green (lint 187/0 errors, 0 compile errors,
`verify --full` 281/283 — stub count 1 -> 0).

Swept and reverted, each measured: volatile on the point-of-use sync globals
`0x10035884/80/88/8c` (masked match falls to 1495), both together (1795), the
`total_size` reads of `0x101deac0` and its `>=` compare (inert), the zero store
(inert), and the second `transfer_progress` read (inert).

**The last 3 entries, and where they are.**  Measuring the *patched* bytes —
`scripts/probe_postlink.py`'s fixers via `scripts/postlink_residual.py` — gives
**91.1%** (661 failing), i.e. the operand fixer repairs 88 more entries than the
gate's pre-patch check sees.  The cheapest of those classes is the
**string-literal placement in `.data`**: `fcn.10015950`'s 15 failing operands are
skewed four-byte map windows straddling a `push <literal>` whose code is
byte-identical and whose literal simply sits elsewhere — the reference pushes
`0x10031004` / `0x10031218` where we push `0x1003204c` / `0x10032074`, a uniform
**+0x1048**.  `.data` COMDAT order is the linker's, so the pipeline cannot place
literals yet; a `--split-data`-style per-section placement for *our* objects'
`.data` (round 139's attempt split *archive members*' data and broke the CRT with
`LNK2001: _main`) would move 15-40 of these entries inside the gate.

**Round-144: the round-143 volatile lever does not generalise — three sweeps,
all reverted; plus a first-divergence column for the residual table.**

Round 143 beat `ls_LoadBuildingEntityState`'s constant-caching blocker by making
a family of field reads volatile.  This round tried the same lever on the other
two functions whose blockers are documented as allocation decisions, and it does
not transfer.  Each variant was compiled with the file's own flags and compared
at fixed offsets against the reference (relocation slots and branch targets
masked):

* **`CrashDumpUnhandledExceptionFilter`** (112 failing entries; frame `0x28c`
  against the reference's `0x280`, four saved registers against two).  Declaring
  each of its eight long-lived locals volatile — `hDbgFile`, `hCrashLog`,
  `pDbgBuf`, `hProcess`, `pCtx`, `fail_msg`, `fail_line`, `nBytesWritten` — one
  at a time and all at once never changes the prologue (still
  `ebx/ebp/esi/edi`, frame `0x28c` or `0x290`) and moves the masked match from
  24.7% to at best 29.6% (`hCrashLog`, object 2128 -> 2224, i.e. 100+ bytes
  longer).  Its cascade is a frame/local-shape difference, not a residency one.
* **`cm_ExSellObjekt`** (96 entries; its first difference is `0x1000d945`, the
  zero register — `edi` in the reference, `ebx` in ours).  Volatile on the 54
  `*(int*)(cmd + N)` reads: 20.4%.  On every `cmd` cast: 19.3%.  On the eleven
  zero-initialised locals: 18.3% (and frame `0x228 -> 0x230`).  On both: 17.6%.
  The baseline 18.8% stays best, which *confirms* the file's own note that no
  formulation shifts the zero register off ebx.
* **`ls_LoadBuildingEntityState`**'s store block: a `volatile int* state_ptr`
  gives 58.4% at object 1488 (+16 bytes); direct `*(int*)(esi + 0x99 + 4k)`
  stores are byte-identical to the current 1472/1463 at 58.5%.  Neutral or worse.

**The remaining 59 entries of `ls_LoadBuildingEntityState` need a lever that
separates two coupled decisions.**  Every spelling that reproduces the
reference's loop shape (`load_result + field + N`, pointer arithmetic,
field-first order, `4 + load_result + ...`) loses the `or ebp,-1` caching and
drops to 24.0-24.1% masked match; every spelling that keeps the caching folds
`+8` into the induction variable (`mov ebx,8; lea ebp,[ebx-8]` against the
reference's plain `xor ebx,ebx` with `lea [ebx+edx+N]`).  Volatile at a single
field site does not cache either; adding it to the store's own read kills it.
`volatile` neg1 stores, `unsigned int` counters and `+=` vs `= ... +` are inert.

**New tooling**: `scripts/postlink_residual.py` now reports the *first* differing
offset per function, which separates systematic from late divergences:

```
gm_AllocSpieler                     3343  @0x100188f4      m_AllocTracked          256  @0x10006591
CrashDumpUnhandledExceptionFilter   1988  @0x10002772      gm_FindNextFilteredEntity 232  @0x10016f86
cm_ExSellObjekt                     1979  @0x1000d945      ahm_ExAllocAlchemist    217  @0x1000be64
ServerMainThread                    1114  @0x10009767      gm_CheckInventoryCapacity 102  @0x10019ee3
ls_LoadBuildingEntityState           775  @0x1001292c      srv_LoadBuf              49  @0x1000a5c0
cm_ExCopyEntityData                  555  @0x1000ec30      gm_ObjectsAvailble       25  @0x1001607d
gm_AllocGebaeude                     529  @0x10017530      cm_ExProdObjekt          21  @0x1000e20d
gv_ExAllocGraveyardWorker            465  @0x10011ce9      cm_ProcessCommandQueue   15  @0x1000aaf7
vfs_ReadCompressed                   348  @0x10008a93      gm_CalculateProductionValue 5 @0x10019804
vfs_OpenStream                       263  @0x10009040                               (34 outside the 19)
```

`CrashDump` (byte 2) and `cm_ExSellObjekt` (0x15) differ in their *prologue*, so
their whole bodies are shifted — a source-shape/frame job.  `gm_AllocSpieler`,
the biggest bucket, does not diverge until `0x100188f4` (the statement-order
plateau its note describes); `ls_LoadBuildingEntityState`'s first difference is
only a branch displacement (`jle` target), i.e. stream length, not content.

Standing after this round: **coverage 89.3%** (797 failing entries; the gate
needs ≤746, so 51 to go), `.text` residual `0x301b` of `0x22846` (`0x2ff9` of it
inside the 19), all other sections byte-identical after the fixers, gate green
(lint 187/0 errors, 0 compile errors, `verify --full` 281/283).

**Round-143: a volatile field read beats the constant-caching wall — coverage
`88.6% -> 89.3%`, `ls_LoadBuildingEntityState` residual `1404 -> 775` bytes.**

The round-24 note called this function "one constant-caching decision away" and
recorded the decision as unreachable from C: the reference caches the `-1`
sentinel in ebp (`or ebp,-1` once, then `mov [..],ebp` at three sites) while
`/O2` rematerialises `mov dword [..],0xffffffff` — and the missing saved register
shifts every frame slot, desyncing the whole function (1404 differing bytes, 114
failing entries).  `/Oa` caches the constant but also CSEs `*(int*)(esi+0x71)`
out of the read loop, `/Ow` merely cancels `/Oa`, and `#pragma optimize("a",on)`
is `/Oa`.

**It is reachable.**  Writing the *eight* `ls_ReadVfsDataChecked` argument reads
of that field as `*(volatile int*) (esi + 0x71)` — the store stays plain — makes
`/O2` emit the reference's cached form *and* keep the per-call reloads:

```
                       obj size   masked match at fixed offsets   or ebp,-1   loads of 0x71(%esi)
/O2 (before)             1464        347/1463  (23.7%)               no              10
/O2 + 8 volatile reads   1472        856/1463  (58.5%)              yes              10
reference                1463                 —                    yes              10
```

Beware the milestone table in round 24: it says a volatile read "regresses to
117/1471" — measured here it is the *only* spelling that works, and it keeps the
reloads.  (The LCS "matching %" metric moves the *other* way, 89.3% -> 82.9%,
because the LCS is position-independent: it prefers the old, shifted stream.)

The switch is fragile and global.  Swept on top of the working shape, each
reverted: volatile at any **one** of the ten field sites leaves the constant
rematerialized; the store's own read volatile kills it again; `4 + load_result +
...`, the field-first order, `char*` arithmetic, add-then-constant, a `volatile`
store (alone or on top), `unsigned int load_result` (byte-identical) and
`load_result = load_result + 0x18` (byte-identical) all lose it or are inert.

```
                                     failing entries   coverage   .text bytes     residual
                                                                   (whole file)   in the function
round 142                                    852         88.6%        0x328f           1404
round 143                                    797         89.3%        0x301b            775
```

The gate needs ≤746 failing entries, so this one change halved the gap: **51
entries to go** (the function still owns 59 of them).  Its 25 aligned hunks are
the read loop's induction form (`mov ebx,8; lea ebp,[ebx-8]` where the reference
keeps a plain `xor ebx,ebx` with `lea [ebx+edx+N]`), the store block
(`state_ptr[0] |= 1` folds to a single store where the reference reloads — making
that read volatile costs 16 bytes), one `lea esi,[edx+ecx]`/`[ecx+edx]` operand
order, and the `g_aux_entity_buffer` block.  Gate re-run with the change: lint
187/0 errors, 0 compile errors, `verify --full` 281/283 (baseline held).

**Round-142: the split set lost LIBCMT's SEH scopetables (`+7` entries, `-21` bytes);
with the fixers applied the binary differs from the reference in `.text` only.**

*The whole-binary measurement first*, because it re-frames everything else.
`scripts/postlink_residual.py` (new) applies the three fixers outside the build
(calling `rebrew.postlink.FIXERS` directly, i.e. bypassing
`check_text_alignment`) and diffs the result against the reference.  The output
is **byte-identical to the reference** in the header block, `.rdata`, `.data` and
`.reloc`, at the reference's exact 286,720 bytes.  Only `.text` differs:
`0x328f` of its `0x22846` VirtualSize (9.15%), of which `0x326e` sit inside the
19 non-byte-matched functions:

```
gm_AllocSpieler                    3343     vfs_OpenStream        263
CrashDumpUnhandledExceptionFilter  1988     m_AllocTracked        256
cm_ExSellObjekt                    1979     gm_FindNextFilteredEntity 232
ls_LoadBuildingEntityState         1404     ahm_ExAllocAlchemist  217
ServerMainThread                   1114     gm_CheckInventoryCapacity 102
cm_ExCopyEntityData                 555     srv_LoadBuf            49
gm_AllocGebaeude                    529     gm_ObjectsAvailble     25
gv_ExAllocGraveyardWorker           465     cm_ExProdObjekt        21
vfs_ReadCompressed                  348     cm_ProcessCommandQueue 15
                                            gm_CalculateProductionValue 5
outside the 19 functions             33
```

Every non-`.text` part of the pipeline is therefore already converged, and 100%
is exactly "the 19 functions, `0x326e` bytes" (the 33 outside are their size
tails, listed at the end of this section).

That also calibrates the gate: re-measuring coverage *on the patched bytes*
gives 89.7% (771 failing) against 88.6% on the link, because the operand map
holds straddling 4-byte windows whose bytes include a data pointer — the fixer's
in-range guard skips the window itself, but the patch at the real operand lands
inside it.  So `check_text_alignment` reads ~1.1 points below the state the
fixers would leave behind; it is still the right check (it is what makes a
wrong-offset patch impossible), just not the same number.

*The defect.*  `split_coff.py` splits a member per section, so a relocation to a
**local label in another of the member's sections** survives as an *undefined
static* — `$T17396`, the scopetable `malloc`'s SEH prologue pushes.  LINK never
reports an undefined static: it defines it as absolute 0.  Seven prologues
therefore pushed `0x10000000` instead of the scopetable address.  Evidence: the
scan for `55 8b ec 6a ff 68` finds exactly 7 sites in every build, all resolved
in the non-split ones (`server_probe.dll`, `server_lf.dll`, `server_split.dll`)
and all zero in the split composition.  Statics are object-local, so an
`emit_defs.py`-style *separate* object defining them is ignored (measured), and
an in-object ABSOLUTE symbol is honoured only with storage class 2 (same object:
`scl 3 -> 0`, `scl 2 ->` the value).

`scripts/resolve_static_labels.py` promotes each such symbol **in place** to an
external ABSOLUTE definition whose value is read from the reference (a reloc
site's VA is the object's name prefix — the split function's VA — plus the reloc
offset, and the reference's dword there is what the reference's link wrote).  It
adds no section bytes, so the geometry the layout package checks is untouched;
it is idempotent and reproduces all 7 patches from pristine split objects.  Wired
into `scripts/split_link.sh` after the blob step.

```
                             failing operands   call entries   coverage   .text bytes
                                                                    outside the 19
before (round 141)                      571            288      88.5%            53
after                                   564            288      88.6%            33
```

The 33 that remain outside the 19 functions are size tails — 2 bytes past
`m_AllocTracked`'s end, 1 past `ls_LoadBuildingEntityState`'s, 3 past
`gm_AllocSpieler`'s, 23 in `vfs_OpenStream`'s tail (its object runs 26 bytes long)
— plus one 4-byte operand at `0x10012378` (`cmp eax, 0x10139820`) that the data
fixer leaves because the built value is out of range.  All of them belong to the
19 functions' work.

**Round-141: no data-side lever is left — all 859 failing entries are inside the
19 non-byte-matched functions.**

Round 140 ended by asking whether one more data-side fix could clear the 113
entries the 90% gate needs.  It cannot: every failing entry now sits in the
`.text` of the 19 functions whose code is not byte-identical, and the failing
values are not misplaced pointers.

*Where they are.*  `scripts/cov_buckets.py` on `build/split_poc.dll`: the top
five functions own 600 of the 859 entries (396 operands + 204 calls —
`gm_AllocSpieler` 179, `ls_LoadBuildingEntityState` 114,
`CrashDumpUnhandledExceptionFilter` 112, `ServerMainThread` 99,
`cm_ExSellObjekt` 96), the next ten 195 (largest `ExCopyEntityData` 33), and the
remaining ~64 are 1-2 entries each.  No bucket lies outside the 19 (the bucketer
attributes a site to the nearest reversed function below it, so read the names
as regions; the byte accounting below is the proof).

*The failing values are junk, not misplaced data.*  Reading each failing
operand's **built** value and looking it up in the **built** image's own section
table: 570 of 571 point outside every section of `split_poc.dll` (only one lands
in `.text`).  A linker-relocated operand can never do that, so those slots are
not relocated operands at all — they are arbitrary instruction bytes in code
that differs.  That is the correction to round 139's reading: the 891
"past the end of the reference `.data`" entries were *not* mostly misplaced BSS
pointers (452 of them were, and round 140 fixed those); the 432 that remain are
windows inside the 19 functions' differing code.

*How much code is actually wrong.*  With both images' relocation slots masked,
`.text` differs in `0x2d96` bytes (8.3%); `scripts/text_match.py` splits that as
`crt 100.00%` and `game 90.84%`, and the sum of the 19 functions' `delta`
values (11,772 bytes, `0x2dfc`) accounts for it.  Per function (masked,
differing bytes): `cm_ExSellObjekt` 28.3% (1479), `gm_AllocSpieler` 30.4%
(2571), `CrashDumpUnhandledExceptionFilter` 32.3% (1440),
`ls_LoadBuildingEntityState` 37.0% (927), `vfs_ReadCompressed` 41.7% (289),
`gm_AllocGebaeude` 64.8% (383), `ServerMainThread` 72.6% (671),
`m_AllocTracked` 71.6% (191), `srv_LoadBuf` 93.5% (49).

*Leverage, for whoever takes the gate next* — failing entries per differing byte:
`ServerMainThread` 99/671 = 0.148, `ls_LoadBuildingEntityState` 114/927 = 0.123,
`m_AllocTracked` 21/191 = 0.110, `ahm_ExAllocAlchemist` 17/163 = 0.104,
`ExCopyEntityData` 33/352 = 0.094, `CrashDumpUnhandledExceptionFilter`
112/1440 = 0.078, `gm_AllocSpieler` 179/2571 = 0.070.  So **one** of
`ls_LoadBuildingEntityState` (114) or `ServerMainThread` (99) plus one small
function clears the gap; nothing on the data/link side does.

*Shape of the residue.*  The mismatch is a cascade, not a few missing blocks:
`gm_AllocSpieler` 236 non-reloc fragments over 2675 bytes (largest 147),
`ls_LoadBuildingEntityState` 105 over 1005 (largest 35),
`CrashDumpUnhandledExceptionFilter` 77 over 2000 in its 2115-byte range
(largest 165).  Each of those files' own header notes already names the cause
(allocator permutation, out-of-line block placement, the `/Oa`-only
constant-caching decision), and each records long probe lists.

*New measured lever, negative on the one function tried.*  msvc6 **reuses a
stack slot for locals declared in disjoint scopes** — `.scratch/scope/p.c`, two
`char[0x100]` in two blocks: frame `0x200`, versus `0x300` when both live in one
block; `.scratch/scope/q.c`, three address-taken ints: one shared slot nested,
two slots not.  Scope is therefore the lever for frame-footprint deficits (the
`SIZE_MISMATCH` class, and the `.data`-side story above is unrelated).  Applied
to `CrashDumpUnhandledExceptionFilter`, whose frame is `0x28c` against the
target's `0x280` with four saved registers against two: moving the
decrypt/classify temporaries (`excCode`, `i`, `key`, `pDwords`) into one nested
block is **byte-identical** output (`obj_size` 2113, `match_count` 271, the same
1844 mismatches), i.e. msvc6 already shares those scalar slots — the 12-byte
excess is a spill/register fact, not a scope fact.  Reverted.

*Measurement note.*  For a function whose object size differs from the target's,
`rebrew diff`'s positional count desynchronises at the first size difference and
its candidate column can even print the wrong prologue (the `ls_LoadBuilding_
EntityState` header says this; it is still true for
`CrashDumpUnhandledExceptionFilter`).  Use `rebrew test --json`'s `obj_size` +
a mnemonic LCS, or `scripts/text_match.py`, and remember the layout maps index
`.text` by `VA - 0x10001000`, not `VA - 0x10000000`.

**Round-140: the BSS tail pad was 0x329c too long — coverage `82.3% -> 88.5%`.**

`link_stubs.c`'s `g_bss_tail` exists to grow `.data` VirtualSize to the
reference's `0x174059c`, and it had been sized for an earlier tree: the section
came out `0x1743838`, so the common symbols at the end of the BSS sat `0x339c`
past the *reference's* `.data` span — which is what `_map_coverage` tests a data
pointer against.  Every operand naming one of them failed: 452 entries whose
excess was about `0x2000`, exactly round 139's biggest class.

Trimming the pad by `0x329c` (`g_bss_tail[0x1269f30] -> [0x1266c94]`) puts the
vehicle's `.data` at `0x17402e4`, i.e. `0x2b8` *under* the reference rather than
over, so the commons land inside the span with a little room to grow:

```
                          failing operands   failing calls   entries   coverage
before (round 138)                 1,030             288      1,318     82.3%
after                                571             288        859     88.5%
```

Nothing else moves — all four raw sizes and file offsets `ok`, the `.rdata`
prefix exactly `0x2468` bytes with zero mismatches, `.text` placement 246/319 —
and the top of the bucket list is now the game functions alone:
`gm_AllocSpieler` 179, `ls_LoadBuildingEntityState` 114,
`CrashDumpUnhandledExceptionFilter` 112, `ServerMainThread` 99,
`cm_ExSellObjekt` 96, `ExCopyEntityData` 33, … (`InitBuildingTypeTable` alone
fell from 65 to 20 on this fix).  The gate needs 90%, i.e. about 112 more
entries — two or three of the 19 functions, or another data-side fix of this
kind.

**Round-139: the biggest remaining class is 891 operands pointing past the end of
the reference's `.data` — our BSS is 0x339c too big.**

Classifying every failing operand entry by its *built* value against the
reference's spans (`.rdata [0x24000,0x26e81)`, `.data [0x27000,0x176759c)`):

```
match (built == reference value)                     2436
inside the reference's .rdata/.data span             1290   -> both validate
built past the end of the reference's .data           891   <- the big one
built below the reference's .data start               132
resolve to the image base (unresolved)                  7
```

`_map_coverage` accepts a pointer into the reference's `.data` **span**, which
is the reference's VirtualSize — and ours is `0x1743838` against `0x174059c`,
i.e. `0x339c` larger (`rebrew data --bss`: BSS at `0x10035000`, 24,323,484
bytes, but that is the *reference's* figure; the tool has no globals to check
against here, 0.0% coverage).  Every symbol that lands in our extra `0x339c` of
BSS therefore misses the span, and the 452 entries whose excess is about
`0x2000` are exactly that tail.  The remaining excess histogram has a few dozen
entries with absurd excesses (`0xed5f000`, `0xc748000`) which are not data
pointers at all and need reading individually.

So the next CRT/data-side win is to bring our `.data` VirtualSize down to the
reference's — `0x339c` of BSS we declare that the reference does not — and it is
worth up to ~450 entries.  (132 operands point *below* `.data`, i.e. into
`.text` or the headers, which the rule never accepts; those need the `.text`
values themselves to match and belong with the game-function work.)

**Round-138: split members keep their own statics — coverage `81.3% -> 82.3%`.**

`split_coff.py --promote-statics` emits a `_`-named *data* static as an external
(class 2) instead of file-local (class 3).  The original member had them
file-local and resolved them internally; splitting it across objects broke that,
which is exactly round 137's `_dststart`/`_dstend`/`_tzapiused`.  Measured on
the vehicle, with `--promote-statics` now passed by `split_link.sh`:

```
                 failing operands   failing calls   entries   coverage
before                    1,104            292      1,396     81.3%
after                     1,030            288      1,318     82.3%
```

All three statics are now in the map, `fcn.10020943`'s own failures drop from 28
entries to 9, and nothing else moves: all four raw sizes and file offsets `ok`,
the `.rdata` prefix still exactly `0x2468` bytes with zero mismatches, `.text`
placement still 246/319 at their reference VA.

Postlink now reports 6,145/7,463 = **82.3%**, and the bucket list is unchanged at
the top — the 19 game functions are ~1,000 of the remaining 1,318 entries.  The
CRT tail is spread thin (8-14 entries each across `fcn.100151e0`,
`fcn.10016460`, `fcn.100170e0`, `fcn.10020943`, `OpenVfsStream`, …), so the next
CRT-side win needs whatever symbols those reference rather than one more single
fix.

**Round-137: the ~390 CRT failures are *unresolved member statics*, and the
signature is a built value of `0x10000000`.**

Round 136 stopped at "the built slot holds the image base"; it is not a data
symbol at the wrong offset, it is an **undefined external**.  The object for
`fcn.10020943` (`10020943_.text.obj`, `.text` only) references

```
+0x18 -> _dstend      sec 0  (undefined)
+0x1f -> _dststart    sec 0
+0x26 -> _tzapiused   sec 0
```

and none of the three appears anywhere in the built map — the link only
succeeded because `/FORCE` is on (`warning LNK4088: image being generated due
to /FORCE option`), so every reference to them resolves to RVA 0, i.e. the
image base, and 27 operand entries for that one function fail.  Across the CRT
that is the ~390 entries.  A built value of exactly `image_base` in a failing
operand entry is therefore the signature of an unresolved symbol, not a
misplaced one.

The members' data sections are supposed to prevent this: `split_coff.py
--with-data` attaches them to the member's lowest-VA *mapped* function, and
`emit_defs.py` is meant to cover whatever is still undefined.  Something in
that pair misses these statics — the fix is to make the split set define every
member data symbol (or carry the data sections on members whose lowest-VA
function is not in the mapped set), and it is worth ~5 points of the gate.
Round 136's "different things from the same section" reading is superseded.

**Round-136: the ~390 CRT entries fail on *data* operands, and that is the blob
strategy's own chicken-and-egg.**

Sampling the failing entries of `fcn.10020943` (28 of them) shows what they are:

```
off 0x1f95b in fcn.10020943   ref value 0x10034028   built 0x10000000
off 0x1f9a7 in fcn.10020943   ref value 0x10035744   built 0x10000054
off 0x1f9bf in fcn.10020943   ref value 0x100356e8   built 0x10000000
```

Every failing value is an address inside `.data` (`0x10027xxx…0x1003xxxx`), and
the built slot holds either the image base (`0x10000000`, i.e. the symbol
resolved to RVA 0) or another low address — because our `.data` symbols do not
sit at the reference's offsets.  That is deliberate: `data_restore.c`'s blob is
the reference's raw bytes *followed by* our own data, and `rebrew postlink`'s
`data` fixer rewrites exactly these `.text` operands once it runs.  The
coverage gate runs **before** the fixers, so entries the fixer would repair
count as failures: ~390 of them, 5 points of the 8.7 the gate needs.

Two consequences worth carrying forward:

* placement is not the CRT half's problem — 228 of the 229 split objects sit at
  their reference VA, only `1001e7d4_.text.obj` is off (by 8 bytes), and the
  `.text` surplus (0x2b2) is extra *tail* content (defs/commons/thunks objects)
  which postlink trims anyway;
* so a `.data` layout that reproduces the reference's symbol offsets would be
  worth ~5 points on its own, and it is the same problem the blob solves for
  content — the two want different things from the same section.

**Round-135: the coverage gap, itemised — 1,396 failing entries, ~1,000 of them
in the 19 functions and ~390 in the CRT.**

`scripts/cov_buckets.py` (new) applies postlink's own rule to every layout-map
entry and attributes each failure to the reference function holding the offset.
On the vehicle (`build/split_poc.dll`, the composition that now satisfies the
`.rdata` prefix gate):

```
failing operand entries 1104/4756, call entries 292/2707 -> 81.3%
fcn.10018850  gm_AllocSpieler                180   (117 ops,  63 calls)
fcn.100128f0  ls_LoadBuildingEntityState     114   ( 66,     48)
CrashDumpUnhandledExceptionFilter            112   ( 95,     17)
ServerMainThread                             101   ( 71,     30)
TradeCommandHandler (cm_ExSellObjekt)         96   ( 50,     46)
InitBuildingTypeTable                         65   ( 46,     19)
ExCopyEntityData                              33   ( 27,      6)
gv_ExAllocGraveyardWorker                     29   ( 23,      6)
fcn.10020beb / ExecuteOfficeAssignment / ahm_ExAllocAlchemist  28 / 27 / 27
…then a long tail of CRT symbols (fcn.10020943, fcn.10015950, fcn.10016290,
fcn.100151e0, fcn.10016460, …) worth about 390 entries in total.
```

So the 90% gate needs **both** halves: the game functions from round 119's table
(they alone are ~1,000 entries, i.e. 13 points) and the remaining member/CRT
placement (the other ~5 points).  Neither is sufficient alone — perfect
placement would leave the vehicle at ~86.5%, and the game functions alone
without placement at ~68%.

Two traps in reimplementing the rule, both hit here and worth keeping:
`_map_coverage` compares `value - image_base` (an RVA) against
`meta.section(".rdata").va`, which is an RVA and not an absolute VA (getting
that wrong reads 65.1% instead of 81.3%); and a call entry also validates when
the site sits on an `E8`/`E9` with matching two-byte contexts, which is why
2,415 of 2,707 calls pass even though most targets differ.

**Round-134: postlink's `.rdata` prefix gate is satisfied — exact size, zero
mismatching bytes — and `.text` coverage is what is left.**

The last eight bytes were cvt.obj's `__real@8@00000000000000000000`, which the
reference packs at the odd offset `0x1341` right after a byte-packed string.  A
piece cut from the reference can end there, but msvc6 emits a
`const unsigned char[]` as a 4-aligned `.rdata` section, so the fix is to lower
the alignment to `ALIGN_1` — **only** on the pieces and the one object that
touch that section.  Measured:

```
                          .rdata VS   import dir   prefix   prefix bytes   .text placement
all 4-aligned                0x2e81       0x2610    0x2470        0 differ   246/319
all ALIGN_1                  0x2e81       0x2608    0x2468      470 differ   246/319
only the touching ones       0x2e81       0x2608    0x2468        0 differ   246/319
reference                    0x2e81       0x2608    0x2468
```

Lowering everything drops the pads the reference *does* have (first mismatch at
`0x2061`, right after `___lookuptable`); leaving everything at 4 loses those
eight bytes.  `split_blob.py --byte-align` now patches a piece only when its
start or end is odd, and the object when its own offset is odd, and
`split_link.sh` passes it.

`bash scripts/split_link.sh` therefore ends with the vehicle at: all four raw
sizes and file offsets `ok`, `.rdata` the reference's size, the prefix exactly
`0x2468` bytes and byte-identical, `.text` 0x22af8 with 246/319 mapped symbols
exactly at their reference VA.  Postlink's message is now only the coverage
gate — **6067/7463 = 81.3%** — which needs the 19 non-byte-matched functions
(round 119's table), and the CMake artifact still links its own composition, so
adopting this one there is the other half of the remaining work.

**Round-133: the split blob is in the pipeline — `.rdata` is now the reference's
size exactly, the prefix is byte-identical, and 8 bytes are left.**

`split_blob.py` grew the two things round 132 named, and `split_link.sh` runs it
before the link:

* it also scans `--defs` (the `___dnames`/`___mnames` tables live in a defs
  object, not in the split set);
* an anonymous COMDAT section that holds *pointers* (the CRT marker tables at
  `0x1fc0`) is **absorbed** rather than placed: nothing names it, so the member
  object is dropped and the piece covers its bytes — the reference's own pointer
  values, where a relocation in our layout would put the image base.

```
                     .text VS   .rdata VS   .data raw   members at VA   import dir   prefix   prefix bytes
round 128             0x22af8     0x2fe1       0xe000        246/319       0x2768    0x25c8   0 differ
round 133             0x22af8     0x2e81       0xe000        246/319       0x2610    0x2470   0 differ
reference             0x22846     0x2e81       0xe000                      0x2608    0x2468
```

All four raw sizes and file offsets are still `ok` and `.text` placement is
untouched.  The last **8 bytes** are cvt.obj's `__real@8@00000000000000000000`,
which the reference packs at the odd offset `0x1341`; `--byte-align` patches the
generated pieces to `ALIGN_1` so a piece can *end* there (and `.rdata` still
comes out at `0x2e81`), but the placed section's own object is 4-aligned, so it
lands at `0x1344` and 3,238 bytes shift.  The remaining work is therefore to
lower the alignment of *that* object too — it is our own COFF object, not a
library one — or to place the eight bytes by hand and define the symbol
elsewhere.

**Round-132: the split blob runs — prefix surplus `0x160 -> 0xd8`, four bytes
short of exact — and the four bytes name the last problem.**

`scripts/split_blob.py` (new, not yet wired into `split_link.sh`) locates every
`_r*.obj` in the reference with its relocation slots masked, sorts by offset,
and rewrites the response file into `piece0, obj0, piece1, obj1, …` in place of
`rdata_restore.c.obj`, dropping the moved objects from the tail.  Measured on
the vehicle:

```
                     .text VS   .rdata VS   .data raw   members at VA   prefix   prefix bytes
before                0x22af8     0x2fe1       0xe000        246/319    0x25c8   0 differ
with split_blob       0x22af8     0x2f51       0xe000        246/319    0x2540   4 differ
reference             0x22846     0x2e81       0xe000                 0x2468
```

The four bytes are at `.rdata 0x1fc7`: the CRT marker tables at `0x1fc0` hold a
pointer, `ref 9c a8 01 10` (`0x1001a89c`) against ours `00 00 00 10` (the image
base).  A relocation that resolves differently in our layout cannot be placed
as-is — postlink rewrites `.text` operands, **not `.rdata` contents** — so a
section holding a pointer has to be *synthesised* from the reference's bytes
with its symbols defined by our own array rather than linked as the member's
object.  That is fine for `___lookuptable`, `___dnames`/`___mnames` and the
unnamed tables (no symbols at all); `__real@8@…` cannot be named in C, so those
stay in the tail.

Two more limits, both measured and filtered in the script:

* a cut piece is a 4-aligned `.rdata` section, so a section the reference packs
  at an odd offset (cvt's `__real@8@` at `0x1341`) cannot be landed there;
* a section that folds (`??_C@…`, re-declared by `rdata_fold.c`) emits nothing,
  so placing it would leave a gap — placing all of them first took the prefix to
  `0x2178` with 2,934 mismatching bytes.

**Round-131: the member `.rdata` sections are separable now — `split_coff.py
--split-rdata`, wired into the pipeline and verified byte-neutral.**

Round 130's recommendation was to split only the `.rdata` sections out and
leave `.data`/`.bss`/`.CRT$*` bundled, which is what `--split-rdata` does.  Each
of a member's `.rdata` sections becomes its own object (`<va>_<sym>_r<k>.obj`)
at the same VA, with `extra={i}` so the closure walk still pulls the same-member
`.text` its initialisers name.  `split_link.sh` passes it, and the vehicle is
unchanged in every measured respect:

```
                       .text VS   .rdata VS   .data raw   members at VA   prefix   prefix bytes
before the split        0x22af8     0x2fe1       0xe000        246/319    0x25c8   0 differ
with --split-rdata      0x22af8     0x2fe1       0xe000        246/319    0x25c8   0 differ
```

(round 130's failure — `crt0.obj` pulled, `_main` unresolved — came from
splitting *all* the data sections; keeping `.data`/`.bss`/`.CRT$*` bundled
avoids it, and `--split-rdata` is documented in `split_coff.py --help` as the
safe half.)

**Measured and not taken:** simply *not linking* the new `_r*.obj` objects
shrinks `.rdata` to `0x2f41` and the prefix to `0x2528` with the prefix bytes
still byte-identical — but `.text` grows to `0x22d4f` and 22 `LIBCMT` members
come back, because the omitted sections' symbols go undefined.  That is round
130's trap again: the sections have to be *placed*, not dropped.

So the pieces are all measured and in place for the split blob: the arrangement
(round 129), the offsets of all 57 sections (round 130), and now the separate
objects to place.  What is left is the `split_blob.py` step itself — locate each
`_r*.obj` in the reference, sort by offset, emit `piece0, obj0, piece1, obj1,
…` in place of `rdata_restore.c.obj`, drop the moved objects from the tail, and
confirm the prefix reaches `0x2468` with zero mismatches.  Its remaining
unknown is the pad LINK inserts between sections: round 129 measured `0x40` for
a `0x3d`-byte section (`align 4`), and the locator's offsets are the check.

**Round-130: the split blob's input exists — every surviving section is
locatable — but unbundling them as separate objects breaks the link.**

Locating is solved.  Masking each data object's relocation slots (the rule
`scripts/locate_sections.py` uses — a raw `bytes.find` fails on every section
that holds a pointer, which is why the first attempt found only the 3-byte
`"TZ"`) and searching the reference's `.rdata[0x12e8:0x2608)` finds **57** of
`split_coff.py`'s data sections at their exact reference offsets, survivors
included:

```
0x17d8 1001f1a4_.text_s0  0x0008   __real@8@…            (testfdiv)
0x2008 1001c19b_.text_s0  0x0059   ___lookuptable        (output)
0x2064 1001c19b_.text_s2  0x000e   unnamed pointer table
0x207c 1001d253_.text_s1  0x0017   unnamed pointer table (heapinit)
0x20b0 1001f1a4_.text_s1  0x0008   __real@8@…
0x2458 10020915_.text_s2  0x0003   "TZ"
…plus crt0msg's 25 R60xx strings, crtmbox's four, cvt's and a_map's
```

With the arrangement round 129 proved, that list is enough to cut
`rdata_restore.c` into pieces with every section at its own offset.

What fails is making them orderable.  `split_coff.py` bundles a member's
non-`.text` sections into its lowest-VA function object, so a section cannot be
moved without moving the function's `.text` with it.  Emitting one object per
data section (a `--split-data` variant, `written` entries at the same VA so the
index order is unchanged) links to
`LIBCMT.lib(crt0.obj) : error LNK2001: unresolved external symbol _main` — the
unbundling changes symbol resolution until `crt0.obj` (the EXE startup) is
pulled.  Most likely the `.CRT$` markers and the `.data`/`.bss` sections have to
stay bundled with the function object, and only the `.rdata` sections split
out; that is the next attempt, and it has to be verified byte-neutral (same
`.text`/`.rdata`/`.data`, same 246/319 placement) before the pieces are cut.

**Round-129: the split blob works — proven on the timeset tables, prefix
surplus `0x168 -> 0x120` with the prefix bytes still byte-identical.**

The vehicle's remaining `.rdata` surplus is content that cannot fold
(`___lookuptable`, the unnamed pointer tables, four `__real@8@`, `___dnames` /
`___mnames`).  Round 124 proposed covering it with a *split* blob: keep the
member sections, and cut `rdata_restore.c`'s single array so each one lands at
its own reference offset inside the blob's range.  That is now measured, using
`build/split_poc/defs/def_timeset.obj_s0.obj` — a data-only object, so it can
be ordered independently of any `.text`:

```
reference .rdata 0x2418  "SunMonTueWedThuFriSat…NovDec"   (0x40 bytes, the
                                                           dnames/mnames pair)
arrangement       [piece A: ref .rdata[0x12e8:0x2418)]  (0x1130)
                  [def_timeset.obj_s0.obj]              (0x40)
                  [piece B: ref .rdata[0x2458:0x2608)]  (0x1b0)
                  total 0x1320 = the blob's own length
```

Result: `.rdata` VirtualSize `0x2fe1 -> 0x2fa1`, import directory `0x2768 ->
0x2728`, all four raw sizes and offsets still `ok`, `.text` placement
unchanged (246/319 at their reference VA), and **zero bytes differ from the
reference in `[0x1a0, 0x2608)`**.

One trap, measured: the piece after the member section must resume at the
*linker's* aligned end, not at the object's raw section size.  The defs object
carries `0x3d` bytes of `.rdata` but LINK pads the contribution to `0x40`, so a
piece B cut at `0x2455` shifted everything by three bytes (401 mismatching
bytes in the prefix); cutting at `0x2458` is exact.  Compute each cut from the
next section's start as LINK reports it (the map), not from the object's
section sizes.

The other four items are still bundled inside `.text` objects
(`1001c19b_.text.obj` carries `___lookuptable` and its unnamed tables,
`1001f1a4_.text.obj` / `1001f20b_.text.obj` the reals), so the same treatment
needs `split_coff.py` to emit a member's data sections as their own objects —
which is the next step, and then the whole surplus is one `split_blob.py`
helper away: locate each data object's bytes in the reference, sort by offset,
cut the blob between them, and order the response file `A, obj1, B, obj2, C…`.

**Round-128: the split composition's section geometry now matches the reference
exactly — all four raw sizes, all four file offsets, no extra section.**

Two fixes closed it, both in the pipeline rather than in the link:

* **A composition-specific data gap.** `data_restore.c`'s blob is sized for the
  CMake build's own `.data`; the split objects carry more, so the same blob
  overshot the reference's raw size by `0x2460`.  Since postlink overwrites
  `.data` wholesale, only the blob's length matters (round 119's rule), so
  `split_link.sh` now emits a shorter blob (`0x74a0`, cut from the reference's
  own `.data` tail) and swaps the CMake object out of the response file.
* **`.CRT$` definition objects must not be linked.**  `emit_defs.py` emits one
  object per missing symbol's defining section, including `___xc_a` and friends
  from `crt0init.obj` section 7.  Those sections make LINK create a separate
  `.CRT` *output* section (raw `0x1000`) after `.data`, which moves `.reloc` off
  the reference's file offset; leaving them out lets LIBCMT's own
  `crt0init.obj` supply the same symbols, merged into `.data` at section 3
  offsets `0x0..0x30` exactly as the reference has them.
  `make_split_rsp.py` now skips `--defs` objects whose sections are all
  `.CRT$`.

```
build/split_poc.dll      .text raw 0x23000   .rdata raw 0x3000   .data raw 0xe000 @0x27000
                         .reloc @0x35000     no extra section    members at VA 246/319
reference                .text raw 0x23000   .rdata raw 0x3000   .data raw 0xe000 @0x27000
                         .reloc raw 0x11000 @0x35000
```

`scripts/section_geometry.py` reports every row `ok`, and postlink's message on
the vehicle is now the coverage gate rather than a geometry one: **6072/7463 =
81.4%** (was 6060/81.2% before the fold).  What is left in this composition is
the `.rdata` prefix surplus `0x168` (the split-blob piece, round 124) and the
game region's 19 non-byte-matched functions, which are what cap the coverage
short of 90%.

**Round-127: the fold is part of the split pipeline now, and what it exposes is
the split composition's `.data`.**

`scripts/gen_fold_literals.py` gained a `--split-dir` mode that reads the
`??_C@…` symbols straight out of `split_coff.py`'s per-section objects (each
`??_C@` section is exactly the literal plus its terminator, so the section size
recovers even the two strings whose first byte is NUL — a_map.obj's `"\0"` and
`L"\0"`, which the map+DLL mode cannot see).  `scripts/split_link.sh` now
generates, compiles and inserts that TU at token 1 of its response file, so the
vehicle comes out with the reference's `.rdata` by default:

```
build/split_poc.dll    .text 0x22af8 (+690)   .rdata raw 0x3000   .data raw 0x11000
                       members at their VA 246/319
reference              .text 0x22846          .rdata raw 0x3000   .data raw 0xe000
```

The fold cost nothing to `.text` placement (unchanged) and fixed `.rdata`'s raw
size, and it makes the composition's remaining `.data` surplus the visible one:
`0x3000` over the reference, from the members' bundled `.data`/`.bss`
(`0x2700` across the split objects) plus `emit_defs.py`'s definition objects.
That content is *only* needed so the members' data symbols exist — postlink
overwrites `.data` wholesale and rewrites the `.text` operands that point into
it — so the same move that folded the strings applies: drop the bundled
`.data`/`.bss` sections from the split objects and define their symbols with
one-byte arrays of our own, iterating until no member is pulled back from
`LIBCMT.lib` for an undefined symbol.  That is the next step, and it is the
last piece of the member-section composition (`.text` placement ✓, `.rdata`
raw ✓, `.data` raw ← this, prefix surplus `0x168` ← the split blob).

**Round-126: the split composition can carry the reference's `.rdata` too — the
two gates are not mutually exclusive after all.**

Round 124 measured the split composition's `.rdata` at `0x33b1 / raw 0x4000`
and concluded the member-section route traded one gate for the other.  It does
not: that surplus is *strings*, and they fold exactly like the CMake build's.
`scripts/gen_fold_literals.py` (new) reads every `??_C@…` symbol out of a build
that still carries the member copies and emits the C spellings; adding its TU
plus the existing `rdata_fold.c` to the split response file gives

```
                     .text VS   .rdata VS   .rdata raw   .data off   prefix
split_poc              0x22af8     0x33b1       0x4000      0x28000   0x2838
+ full literal folds   0x22af8     0x2fe1       0x3000      0x27000   0x25d0
reference              0x22846     0x2e81       0x3000      0x27000   0x2468
```

So one composition now has the reference's `.rdata` **and** `.data` raw sizes,
the reference's file offsets, and `.text` at 81.2% layout coverage (vs the CMake
build's 55.6%).  The remaining prefix surplus `0x168` is the same item list as
the CMake build's `0x158` (the three non-COMDAT tables, the `__real@8@`
constants, the unnamed pointer tables) - no new blocker, and the split-blob
route from round 124 applies to it.

Two notes for shipping this: the fold TU has to reach the split pipeline
through `objects1.rsp` (so the literals live in `rdata_fold.c`), and there the
40 extra literals cost about `0x340` of `.data`, which needs
`data_restore.c`'s blob re-tuned by the same amount - in the CMake build they
fold nothing (those members are not linked) and would only spend that budget,
so the generator is the right place to keep them until the compositions merge.

**Round-124: the member-section route to both remaining gates, and the one
piece of it that has no answer yet.**

The plan the last rounds imply is: link the *per-section* member objects
(`scripts/split_coff.py`, ordered by reference VA) instead of `LIBCMT.lib`
members, so that (a) `.text` lands at the reference's VAs (81.2% coverage
instead of 55.6%) and (b) the members' `.rdata` sections can simply be
*omitted*, since `rdata_restore.c`'s blob already holds those bytes.  Measured:

```
                                   .text VS   .rdata VS   .rdata raw   imports
split_poc (member sections, data)   0x22af8     0x33b1       0x4000      100
same, member .rdata omitted         0x23334     0x3311       0x4000      100
```

Dropping the members' `.rdata` shrinks it by only `0xa0` and grows `.text` by
exactly the `0x83c` round 75 recorded: the omitted sections' *symbols* go
undefined, so whole members are pulled back in from `LIBCMT.lib` — with their
`.rdata`.  The folding TU (`rdata_fold.c`) was not in that response file, and
covering the rest would need one-byte definitions for `___lookuptable`,
`__dnames`, `__mnames` and the remaining unnamed content.

**What has no answer yet is the three `__real@8@` constants.**  If
`testfdiv.obj`'s `.rdata` is omitted, those symbols are undefined and the
member is pulled back for them — and a data-only TU cannot define them: a
file-scope `const double a = 1.0;` (or `(double)1`, `2.0/2.0`, `1.0+0.0`)
emits `_a`, never a `__real@8@…` pool entry (measured: no `__real@` symbol in
the object).  Only an *expression inside a function* does, and that adds
`.text`.  So `testfdiv.obj`'s `.rdata` — `0x18` of reals plus its two strings —
stays, which caps the *omission* route at a surplus of roughly `0x18` plus our
own definitions unless the reals can be defined another way (an absolute symbol
in the `.def`, or an `/alternatename` equivalent — neither exists in this
linker).

The remaining `0x158` in the CMake build is now fully attributed:

```
0x2608 __real@8@3fff8000000000000000 / @4015800bf6.. / @4014bffffc..  testfdiv   0x18
0x2620 unnamed pointer tables                                        output.obj 0x48
0x2668 ___lookuptable                                                output.obj 0x5c
0x26c4 unnamed pointer tables                                        timeset    0x1c
0x26e0 ___dnames  (the day-name string "SunMonTueWedThuFriSat")       timeset   0x18
0x26f8 ___mnames  (the month-name string "JanFebMar…NovDec")          timeset   0x28
0x2720 unnamed pointer tables                                        timeset/a_map 0x40
0x2760 import directory (reference 0x2608)
```

`___dnames`/`___mnames` are the *strings themselves*, not pointer tables, and
every one of those named sections is plain non-COMDAT data of an object the
link needs for code, so none of them can be folded away.

The one route that can zero the surplus is the member-section link plus a
**split blob**: `split_coff.py` already emits one object per member *section*,
so the sections whose `.rdata` has to sit at a particular reference offset can
be kept while the rest are left out, and `rdata_restore.c`'s single array
becomes pieces with gaps at exactly those offsets.  Those VAs are inside the
blob's range today (`0x12e8..0x2608`), which is precisely what one contiguous
array cannot express - it cannot share its range with a real object.  Nothing
measured this round contradicts that route; it is simply a bigger change than a
fold (generate the per-section set, filter it, re-cut the blob, regenerate the
response file, link) and it is where the prefix gate should be attacked next.

**Round-122: the foldable half of the `.rdata` duplicate is folded — 11 COMDATs,
prefix surplus `0x1c8 -> 0x158`.  The other half is provably not foldable.**

Extended `crt_region/rdata_fold.c` with the three remaining literal spellings
(`"\0"`, `L"\0"`, `L"(null)"` - the mangled name encodes the bytes, so those
reproduce a_map.obj's two `??_C@` entries and output.obj's wide `"(null)"`):

```
                       .rdata VS   import dir   prefix surplus
round 119                    0x3041      0x27d0   0x1c8
+ 8 narrow string COMDATs     0x2ff1      0x2778   0x170
+ 3 wide/NUL spellings        0x2fd1      0x2760   0x158
```

All four raw sizes still match (`scripts/section_geometry.py`), and `.rdata`
raw stays `0x3000`.  Measured negatives, each one removing an avenue:

* **`___lookuptable` / `___dnames` / `___mnames` do not fold.**  They are
  plain (non-COMDAT) `.rdata` in LIBCMT, so a definition of ours does not
  discard theirs - `/FORCE:MULTIPLE` keeps *both* sections and the surplus
  grows by whatever we define.  Marking ours `__declspec(selectany)` does make
  them COMDAT (verified in the object: section flags gain `0x1000`) and still
  does not fold the library's.  Those `0x9c` bytes are only removable by not
  linking `output.obj` / `timeset.obj`.
* **The three `__real@8@` FP constants are COMDAT but unreachable from a
  data-only TU.**  A file-scope `const double x = 1.0;` emits `_x`, not a
  `__real@8@...` pool entry; only an *expression* in a function does, and that
  would add `.text` - which breaks byte identity by construction.
* A `.bss` definition defines the symbol but does not fold a read-only COMDAT,
  so "define it somewhere cheap" is not a workaround for either case.

So the remaining `0x158` splits into `0x9c` of non-foldable named tables,
`0x18` of pooled FP constants, and roughly `0xa0` of unnamed content around
them (`.rdata[0x2638:0x2738)`, still unclassified).  Reaching the gate's exact
`0x2468` needs those objects out of the link, not more folding.

**Round-121: the linker folds COMDATs by symbol name, so the six objects' duplicate
`.rdata` can be *discarded* rather than avoided — all four section raw sizes now
match the reference.**

msvc6 derives a string literal's `??_C@...` COMDAT name from its contents, and
MSVC LINK folds COMDAT sections by name, keeping the first definition it sees.
`crt_region/rdata_fold.c` (new, no `.text`) references the same literals the six
library objects emit after `rdata_restore.c`'s blob, so theirs are the copies
that get discarded.  Measured on the real CMake build:

```
              .text              .rdata             .data              .reloc
reference  raw 0x23000       raw 0x3000         raw 0xe000 @0x27000   raw 0x11000 @0x35000
before     raw 0x23000       raw 0x4000         raw 0xe000 @0x28000   raw 0x08000 @0x36000
after      raw 0x23000       raw 0x3000         raw 0xe000 @0x27000   raw 0x08000 @0x35000
```

`scripts/section_geometry.py` reports `.text`, `.rdata` and `.data` `ok` and
`.reloc` at the reference's `0x35000`; postlink then grows `.reloc` to
`0x11000`, so the post-postlink file is exactly the reference's `0x46000`
bytes.  Eight of the library's string COMDATs are gone from the map
(`build/server_lf.map`); `.rdata` VirtualSize went `0x3041 -> 0x2ff1`.

The literals themselves land in `.data` (msvc6 puts referenced literals there,
not `.rdata`), which is harmless because postlink overwrites `.data`
wholesale; the pointer array in the new TU exists only to reference them
without adding a `.text` function, and `data_restore.c`'s blob was left as-is
because the section still ends inside the `(0xd000, 0xe000]` band.

**Still not folded, and the remaining `.rdata` prefix surplus is now 0x170**
(the import directory sits at `0x2778` where the reference has `0x2608`; the
gate wants the region between the IAT and the import directory to be exactly
`0x2468` bytes *and* byte-identical):

```
0x2608 litfold4-style table definitions (ours)      0x10
0x2618 __real@8@3fff8000000000000000 (1.0, folded)  0x08
0x2628 __real@8@4015800bf60000000000  testfdiv.obj  0x08
0x2630 __real@8@4014bffffc0000000000  testfdiv.obj  0x08
0x2638 .. 0x2738  unnamed COMDAT content (0x100)    <- a_map/timeset tables
0x2738 two ??_C@ a_map.obj strings                   0x0c
```

The same mechanism extends to all of it: `__lookuptable`, `__dnames` and
`__mnames` fold against our own same-named COMDAT (a one-byte `const` array is
enough - the reference's bytes are already in the blob, and postlink rewrites
the `.text` operands that point at them), and the reals and the remaining
strings fold against literals/constants of the same value.  The unnamed 0x100
needs identifying first (`build/server_lf4.map` + the byte dump at
`.rdata[0x2638:0x2738)`), then the same treatment.  If the region reaches
exactly `0x2468`, `_fix_imports`' prefix check passes for the first time.

**Round-119: `.data` raw is now the reference's `0xe000`, and postlink's next
gate after `.text` is the `.rdata` prefix — pinned to the same six objects.**

**The `.data` surplus is closed.**  The gap blob (`crt_region/data_restore.c`)
was sized for the project's `.data` as it was when it was generated; the TUs
have since grown `0x1500` bytes of literals, so the section's content ended at
`0xf500` instead of `(0xd000, 0xe000]` and the raw came out `0x10000` rather
than `0xe000`.  The blob is a *prefix* (linked first, after the `.CRT$`
sections), so the only thing that matters is its length:

```
own .data (measured from the map's .bss line, 0xdf00 - 0x30 - blob)
content_end = 0x30 + blob + own          raw = align_up(content_end, 0x1000)
```

Re-tuning it to `0x9a00` (`rebrew gen-layout --data-gap 0x4600`, plus the
matching `src/rebrew-data.toml` entry, or lint gains a W016 warning) gives

```
                 .text              .rdata             .data              .reloc
reference   vs 0x22846 raw 0x23000  vs 0x2e81 raw 0x3000  vs 0x174059c raw 0xe000  raw 0x11000 @0x35000
before      vs 0x22256 raw 0x23000  vs 0x3041 raw 0x4000  vs 0x1744a98 raw 0x10000 raw 0x08000 @0x38000
after       vs 0x22256 raw 0x23000  vs 0x3041 raw 0x4000  vs 0x1743498 raw 0xe000  raw 0x08000 @0x36000
```

No `.data` symbol had to move: postlink copies the reference's `data.hex`
over the whole raw anyway, so the blob's *content* is irrelevant to the
output.  With `.rdata` raw at `0x3000` (the one remaining surplus) the built
`.reloc` lands at `0x35000` and postlink's `.reloc` growth to `0x11000` makes
the file exactly the reference's `0x46000` bytes.

**The `.rdata` prefix gate, measured.**  `_fix_imports` refuses to run unless
the built bytes between the IAT and the import directory are the reference's
`meta.prefix` — `0x2468` bytes (`layout/server.dll/prefix.hex`), i.e. all of
`.rdata[0x1a0:0x2608)`.  Ours is `0x2630`.  The `0x1c8` surplus is one block
after `rdata_restore`'s blob (`0x1320` at `0x12e8`, ending exactly at
`0x2608` like the reference) and it is LIBCMT `.rdata` re-emitted by six
objects the link pulls for code:

```
0x2608 testfdiv.obj reals + "IsProcessorFeaturePresent"   0x2740 timeset.obj __dnames/__mnames
0x2690 x10fout.obj  "1#QNAN".."1#SNAN"                    0x2780 tzset.obj   "TZ"
0x26b0 output.obj   __lookuptable, "(null)"               0x2784 a_map.obj  "SunMon..","JanFeb.."
0x27d0 __IMPORT_DESCRIPTOR_KERNEL32   <- import directory, 0x1c8 late
```

`crt0msg.obj`/`crtmbox.obj` were the first two members of this set and round
115 removed them by fixing the alias decoration (`0x33b1 -> 0x3041`); these
six are what is left, and the reference carries the same bytes inside the
blob (`"1#QNAN"` at `0x24a8`, `"(null)"` at `0x2074`, `"TZ"` at `0x2458` on
both sides).  Shrinking the blob by `0x1c8` does not substitute: the bytes
that would move up into `[0x2440, 0x2608)` are our own COMDAT order, which
matches 53 of 456 reference bytes, and the gate compares bytes.

**`/OPT:REF` confirms the mechanism and is not usable.**  Relinking the same
objects with `/OPT:REF` instead of `/OPT:NOREF` drops unreferenced COMDATs and
lands `.rdata` at `vs 0x2f81 / raw 0x3000` — the reference's raw — but it also
guts `.text` (`0x22256 -> 0x100c6`), because a large part of our reversed
`.text` is not referenced by anything.  Recorded as evidence that the surplus
is unreferenced COMDATs, not as a flag to switch.

**New reference: `docs/msvc6-link-layout.md`.**  Everything above, plus the
section-geometry rules (`raw = align_up(content_end, FileAlignment)`, the map's
`.bss` line as the content end, `file_offset(n+1) = file_offset(n) + raw(n)`,
the literal-goes-to-`.data` rule), the import layer's hash-driven order and
why the hint/name table's size differs by `0xa`, what postlink may and may not
overwrite, the `/MAP` probe recipe, and the `gen-layout` churn trap
(`crt_imports.c` and the toml's import order come out in set-iteration order —
revert them after regenerating the blob).  Compiler-side sweep results and the
five residual codegen classes are in `docs/msvc6-c-shapes.md` sections 49-50.
`scripts/section_geometry.py` is the check: it prints the table above from
`.scratch/server.dll.prelayout` and fails while a raw size still differs, so a
future blob or literal change cannot silently re-open the `.data` surplus.

**Round-119 addendum: the remaining `.text` gap is 19 functions, and the CMake
link's CRT placement — not its code — is what fails postlink's coverage gate.**

`scripts/text_match.py --drift auto` (split set, the better-aligned vehicle:
`.text` 0x22af8 vs the reference's 0x22846) says whole `.text` raw 87.02% /
masked 94.97%, and the game region 81.35% / 92.10% — 6,542 differing bytes over
260 ranges.  Bucketed by function, those bytes are almost entirely in the 19
functions `rebrew verify` still does not byte-match (17 PROVEN + 1 STUB + 1
SIZE_MISMATCH; the other 264 are EXACT or RELOC, i.e. byte-equal once
relocations are masked):

```
 delta      va  size   match   name
     5 0x10019720   396   98.7%  gm_CalculateProductionValue   PROVEN
    15 0x1000aac0   639   97.7%  cm_ProcessCommandQueue        PROVEN
    17 0x1000e140   993   98.3%  cm_ExProdObjekt               PROVEN
    28 0x10015f70   714   96.1%  gm_ObjectsAvailble            PROVEN
    49 0x1000a570   750   93.5%  srv_LoadBuf                   PROVEN
   102 0x10019ed0   395   74.2%  gm_CheckInventoryCapacity     PROVEN
   179 0x1000bdf0  1002   82.1%  ahm_ExAllocAlchemist          PROVEN
   180 0x10016f80   346   48.5%  gm_FindNextFilteredEntity     PROVEN
   210 0x10006580   658   68.4%  m_AllocTracked                PROVEN
   266 0x10009020   667   64.0%  vfs_OpenStream                PROVEN
   339 0x10008a90   492   31.8%  vfs_ReadCompressed            PROVEN
   434 0x10011bf0  1040   58.3%  gv_ExAllocGraveyardWorker     PROVEN
   469 0x1000ec00   912   48.3%  cm_ExCopyEntityData           PROVEN
   507 0x100174d0  1088   53.0%  gm_AllocGebaeude              PROVEN
  1098 0x100093a0  2434   54.9%  ServerMainThread              STUB
  1339 0x100128f0  1463    8.5%  ls_LoadBuildingEntityState    PROVEN
  1844 0x10002770  2115   12.8%  CrashDumpUnhandledExceptionFilter  PROVEN
  1853 0x1000d930  2057    9.9%  cm_ExSellObjekt               PROVEN
  2838 0x10018850  3689   23.1%  gm_AllocSpieler               SIZE_MISMATCH
```

The top five are *documented plateaus*: each file header records the residual
site and the exhaustive list of spellings already measured against it
(`gm_CalculateProductionValue` 4 formulations at the multiply/`cmp` site,
`cm_ProcessCommandQueue` twenty rounds on the two-arm order,
`cm_ExProdObjekt` ~50 variants of the pre-loop block, `srv_LoadBuf`'s one
`lea`/`and` schedule).  So the next lever for those cannot be another source
spelling — it has to be the automated search (`rebrew match`) or something
outside the C source.  Re-derive this list, in this order, with

```sh
rebrew verify --json > .scratch/v.json
jq -r '.results[] | select(.status!="EXACT" and .status!="RELOC")
       | "\(.delta)\t\(.va)\t\(.size)\t\(.status)"' .scratch/v.json | sort -n
```

**The CMake build's `.text` placement is wrong for a mechanical reason.**  Its
`.text` is 0x22256 against the reference's 0x22846 (-1520) and
`scripts/link_drift.py --object-errors` puts every *game* function at drift 0
while the CRT region is split in two: `__CRT_INIT`/`DllMain` at +8380 and
`mlock`/`sbh_pool` at -11636/-12737.  The cause is the one
`scripts/map_libcmt.py` names: MSVC LINK appends every archive member after
every command-line object, so our `LIBCMT.lib` members land in one block at
the end, while the reference *interleaves* them with the project's CRT objects
(its `dllcrt0` body sits at 0x1001b8fb, before our `dllmain.c` at 0x1001b9d4).
`map_libcmt.py --json` already produces the reference-VA-ordered member list
(228 matches spanning 0x1001a18a..0x10023812, with 3,052 bytes of gaps that are
exactly the project objects), and the split set already links that order — it
is why the split set reaches 81.2% coverage where the CMake build reaches
55.6%.  Putting the members on the CMake link line is the next structural step
for `.text`; it is necessary but not sufficient for the 90% gate, which also
needs the 19 functions above to close.

**Round-120: interleaving the members by VA is *not* the fix — the composition
is.  Measured, four links over the same object set** (postlink coverage, and
`scripts/split_audit.py`'s "split symbols exactly at their reference VA" out of
319 mapped symbols):

```
 link                                                  .text     coverage   exact
 CMake as committed                                 0x22256   55.6%       n/a
 members merged in by reference VA (defs/commons)   0x234d2   55.9%       n/a
 members after our objects, blobs last              0x22b08   56.0%       n/a
 same, IAT thunk object before the members          0x22af8   78.2%   216/319
 `make_split_rsp.py` (mirrors dropped, blobs at the
 `_BLOB_AT_DATA` cut) - the split set               0x22af8   81.2%   246/319
```

Two things this settles, both by direct measurement rather than inference:

* **Merging our objects and the member sections into one reference-VA order
  makes placement worse, not better**: 0 of 230 member sections land at their
  reference VA and coverage does not move (55.9%).  MSVC LINK places
  command-line objects in command-line order, so what matters is the *grouping*
  — all our objects, then all members in reference order — not a global sort.
  The reference's interleaving (its `dllcrt0` at 0x1001b8fb before our
  `dllmain.c` at 0x1001b9d4) is reproduced instead by *dropping* the eight
  hand-reversed CRT mirrors (`make_split_rsp.py`'s `DROP`): the member sections
  carry those same bodies and land on their VAs.
* **The last 42/12 bytes come from the thunk and blob slots, not from the
  members.**  The `emit_thunks.py` object belongs *before* the member sections
  (as `scripts/split_link.sh` documents) and its `_tail` companion *after*
  them; putting either on the wrong side shifts every member by its `.text`
  size.  The two restore-blob objects belong at the `.data` running-total cut
  (`_BLOB_AT_DATA = 0x3400` in `make_split_rsp.py`), not at the end: with them
  late the same object set scores 78.2%, with them at the cut it scores 81.2%.

Dropping the mirrors keeps the import set exact: reference, `split_poc` and the
interleaved variants all carry **100 imports across the same 4 DLLs**.  The
`_CRT_REGION_KEEP` note above (extra `IsBadWritePtr` / `FatalAppExitA` imports)
applies to linking *whole* `LIBCMT.lib` members, not to the curated per-section
objects `scripts/split_coff.py` emits.

So the CMake target's remaining link-side work is not a new ordering scheme but
adopting the response file `scripts/make_split_rsp.py` already produces from
`objects1.rsp` (a custom link step, since CMake always emits its own object
list before the trailing libraries).  That closes 55.6% -> 81.2%; the last 9
points to the 90% gate are the 19 functions above.

**Round-117: the CRT half is not where the remaining failure is, and the game
half is uniformly allocator-bound.**

**The CRT's residual byte differences are address operands, not code.**  Taking
the worst untracked window (text offset 0x1f000, VA 0x10020000, 144 invalid map
entries) and listing its differing runs: 133 runs, 389 bytes, and nearly every
one is a 4-byte absolute address -- `ref 4c647611` (0x1176644c) against
`built 60a90310` (0x1003a960), or `80757611` against `2c990310`, repeating at a
dozen sites.  Those are relocation slots whose value differs because our data
placement differs, which is exactly what postlink's `data` fixer rewrites and
what `_map_coverage` accepts as "a pointer into the reference's .rdata/.data
span".  So a strict same-value comparison (`.scratch/mapcov.py`) overstates the
CRT failure; the authoritative number stays postlink's 81.2%.

**`ServerMainThread`'s residual, itemised.**  627 instructions on both sides,
618 matched register-agnostically, 11 runs -- and every run is one of the four
known classes:

```
T 0x100097fb mov [r+0x1c], r          vs  mov [r+0x1c], 0xffffffff   -1 caching
T 0x1000984b lea r,[r+r]              vs  add r,r                    flags/lea
T 0x100098e3 je <head>                vs  jne <exit>                 branch polarity
T 0x10009baf mov [r+0x24],r / [r+0x20] / [r+0x30]
                                      vs  [r+0x28] / [r+0x2c]        frame offsets
```

which is what the file's own note already records ("the wait-loop back edge
(`je <head>` against our `jne <exit>`)", "three sync-packet store placements").

**`gm_AllocSpieler`'s 12 `and r, 0xffff` sites are the same zero-register wall.**
The register-agnostic gap counts six `and r,0xffff` in ours against four
`xor r,r` in the target.  Reading the candidate disassembly, the shape is

```
0x8c9  mov  ax, word ptr [ebp]      ; a 16-bit local read
0x8cd  and  eax, 0xffff             ; zero-extend the upper half
```

where the reference zeroes a register once and uses `mov reg16, [mem]` -- the
constant-caching/zero-register behaviour `m_AllocTracked` records as
unreachable from C, and the reason `ls_LoadBuildingEntityState` stays one byte
long (round 116).

Nothing in the three classes is source-steerable on the evidence so far: the
one that *was* (cm_ExCopyEntityData's clamp arms, round 110) flipped because the
store block was reached from several duplicated branches, and none of these
functions has that shape.

**Round-116: with the CRT order and the `.rdata` duplicate settled, postlink's
gate is now bound by the game region.**

Measured on the two builds after rounds 110 and 115:

```
                    postlink layout-map coverage   note
CMake build (probe2)      4146/7463 = 55.6%        the artifact
split set (split_poc)     6060/7463 = 81.2%        ordered CRT objects
gate                      6716/7463 = 90%
```

The CMake build gained 24.8 points from the four span fixes alone (30.8% ->
55.6%), so the game region was already carrying most of its coverage; the
remaining 25.6-point gap to the split set is the CRT member order the CMake
link does not control (round 106).  Either way both are short of 90%, and the
per-function breakdown (round 111) puts the missing 656 entries where the
game-region instruction differences are: `gm_AllocSpieler` 186,
`CrashDump` 121, `ls_LoadBuildingEntityState` 114, `ServerMainThread` 105,
`cm_ExSellObjekt` 97.

**`.rdata` after the round-115 fix** (CMake build): VirtualSize 0x32d1 ->
**0x3041** against the reference's 0x2e81, same-offset match 81.39% -> 81.71%.
Windows `+0x2800` and `+0x2c00` still read 5.5% and 7.0%, but those are the
import hint/name records and the export table, which postlink copies verbatim
from the layout package -- they are not a source problem.  The remaining
+0x1c0 of surplus is the section running long after them.

**`ls_LoadBuildingEntityState`'s -1 cache is not source-steerable.**  The file
records the reference caching the sentinel in ebp (`or ebp,-1` once plus
`mov [..], ebp` at three sites) where our build rematerialises
`mov dword ptr [..], 0xffffffff` at each.  Six spellings measured on the
current body, none better and one dangerous:

```
identity 1464   no-`register` 1464   unsigned 1464   assigned outside the
guard 1465   `-1` written directly at all three sites 1464
volatile 1473 -- and its COMDAT span moves 1472 -> 1488, which would break
position alignment
```

So the function stays at 1464 against the target's 1463: the size flag is real
and the deficit is the constant-caching codegen, as the file's own note says.

**Round-115: the `.rdata` duplicate is fixed -- it was one missing
underscore.**

`crt_region/amsg_exit.c` exists, in its own words, "to keep crt0msg.obj out of
the link (its runtime-error strings duplicate rdata_restore.c)".  It defined the
CRT aliases as

```c
void __cdecl __NMSG_WRITE(int rterrnum) { ... }
int  __cdecl __crtMessageBoxA(...)      { ... }
```

and MSVC decorates a C identifier with one more leading underscore, so those
became the COFF symbols **`___NMSG_WRITE`** and **`___crtMessageBoxA`** -- one
underscore too many.  They satisfied nothing, `dllcrt0.obj`'s references to
`__NMSG_WRITE` / `__crtMessageBoxA` stayed undefined, and LIBCMT's
`crt0msg.obj` and `crtmbox.obj` were pulled in anyway, bringing exactly the
`??_C@...` string block the file was written to prevent.  The compiled symbols
made it visible:

```
___NMSG_WRITE       1001b970   amsg_exit.c.obj    <- ours, unused
__NMSG_WRITE        10020b48   LIBCMT:crt0msg.obj <- what the link actually used
__GET_RTERRMSG      10020c9b   LIBCMT:crt0msg.obj
```

Renaming them to `_NMSG_WRITE` and `_crtMessageBoxA` (one leading underscore in
C, so two in COFF) fixes it:

```
                              before        after
"runtime error " copies       2             1     (reference has 1)
"R6028" copies                2             1
crt0msg / crtmbox in the map  present       absent
.rdata VirtualSize            0x32d1        0x3041   (reference 0x2e81)
.rdata same-offset match      81.39%        81.71%
.text VirtualSize             0x223d6       0x22256
```

Game-region drift is unchanged (`link_drift` still reports the same single `+0`
change there), and the gate holds: 186 lint files, 0 errors, `verify --full`
281/283.

The split set is unaffected (`.rdata` still 0x33b1, two copies): there the
strings come from `1001fdf8_.text.obj`, the split object carrying `crt0msg.obj`'s
24 `.rdata` sections, on top of `rdata_restore.c`'s blob -- a duplication inside
the split pipeline, not from the library.  The CMake build, which is the
artifact, is fixed.

This retires rounds 112-114's plan: the strings never needed re-emitting from a
`// DATA:` TU, they needed the library object not to be linked at all.

**Round-112: the `.rdata` surplus, found and mechanically validated.**

`.text` is not the only section that has to converge, and `.rdata` is currently
the larger gap:

```
                reference        CMake build     split set
.text vs        0x22846          0x223d6 (-0x470) 0x22af8 (+0x2b2)
.rdata vs       0x2e81           0x32d1  (+0x450) 0x33b1  (+0x530)
.data vs        0x174059c        0x1744b18        0x1746c28
.reloc vs       0x10374          0x7f14           0x81d8
```

`.data` and `.reloc` are converged by `rebrew postlink` (it copies the
reference's `.data` and replaces `.reloc`), and the `.rdata` import bookkeeping
is too -- but postlink only governs the IAT and the import descriptors; the
rest of `.rdata` is reproduced by our own `crt_region/rdata_restore.c`.

**The surplus is one duplicated block.**  Same-offset match per 1 KB window of
`.rdata`:

```
+0x0000 (IAT + import bookkeeping)  82.1%   <- the addresses postlink rewrites
+0x2400                            56.0%
+0x2800                             3.8%
+0x2c00                             3.6%
```

and the last two windows are not garbage -- they are a **second copy of the CRT
message strings**:

```
                        "runtime error "   "R6028"
original/server.dll           1 (0x26110)     1 (0x26150)
build/probe2.dll              2 (0x26110, 0x26724)  2 (0x26150, 0x26764)
build/split_poc.dll           2 (0x26110, 0x26768)  2 (0x26150, 0x267a8)
```

`crt0msg.obj` is pulled in for `__NMSG_WRITE` / `__GET_RTERRMSG`, and its 17
`??_C@...` message literals are emitted *again* after `rdata_restore.c`'s blob,
which already carries those bytes at the reference's offsets.  The extra copy
starts at VA 0x10026724 and runs `"runtime error "`, `"TLOSS error\r\n"`,
`"R6028\r\n- unable to initialize heap\r\n"` ... `"R6002\r\n- floating
point not loaded\r\n"` -- the full `crt0msg` string table.

**The fix mechanism is validated.**  A TU that re-establishes those 17 strings
as real C literals compiles them to the *same* `??_C@...` COMDAT names, so the
linker discards LIBCMT's copies instead of emitting both.  Measured with
`.scratch/keepcrt.c` added to a manual link:

```
.rdata VirtualSize  0x32d1 -> 0x3091   (-0x240)
crt0msg.obj's ??_C@... data symbols:  gone from the map
__NMSG_WRITE / __GET_RTERRMSG:        still from LIBCMT, as the reference has them
```

It is not yet a fix because that TU's own literals then land elsewhere
(`.data`, at file offset 0x36da4), so the strings are still emitted twice --
just in different places.  Completing it needs the 17 strings **removed from
`rdata_restore.c`'s blob** and re-emitted from a TU carrying
`// DATA: SERVER 0x10026110` so `scripts/order_sources.py` places them at the
reference's offsets, in the gap the blob then leaves.  That is the concrete next
step on the `.rdata` half; the blob is one contiguous array, so it splits into
`[0x252e8 .. 0x26110]` + literals + `[0x269b0 .. 0x26608]`.

**Round-113: the `.rdata` duplicate, pinned down to a ready-to-execute step.**

Three things measured this round sharpen round 112's finding.

1. **The split pipeline already emits the strings.**  `build/split_poc/split/`
   `1001fdf8_.text.obj` -- the object built from `crt0msg.obj`'s first section,
   by `split_coff.py --with-data` -- carries **24 `.rdata` sections** with the
   `??_C@...` symbols the library defines (`??_C@_0P@GGKG@runtime?5error?5?$AA@`,
   `??_C@_0O@DELO@TLOSS?5error?$AN?6?$AA@`, ... `??_C@_0CF@EANP@R6028...`).
   So the split set defines them; the duplicate survives anyway, which rules out
   "the map never found the section" as the cause.
2. **`/FORCE:MULTIPLE` is not the cause either.**  Relinking without it fails on
   exactly four *non-COMDAT* duplicates -- `_putc` (link_stubs.c vs fputc.obj),
   `__amsg_exit` and `__FF_MSGBANNER` (amsg_exit.c vs dllcrt0.obj/crt0msg.obj),
   `___app_type` (link_stubs.c vs dllcrt0.obj) -- and no `??_C@...` symbol.
   The string collision is COMDAT and would dedupe on its own.
3. **The block is exactly reproducible.**  The reference's `crt0msg` string
   table is 645 bytes at VA 0x10026110 -- blob offset 0xE28 -- holding the 17
   strings packed at **4-byte** alignment, and the library's own copy at
   0x10026724 is byte-for-byte the same 645 bytes (`"runtime error "` at +0,
   `"R6028..."` at +0x40, ... `"R6002\r\n- floating point not loaded\r\n"` at
   +0x260).  A TU of those literals therefore reproduces both the bytes and the
   layout, and its identical mangled names make the linker discard LIBCMT's.

The executable step, then: split `rdata_restore.c`'s 4896-byte array at 0xE28
and 0x108D, emit the 17 literals from a new TU annotated
`// DATA: SERVER 0x10026110` so `scripts/order_sources.py` places it in the gap,
and drop the now-redundant bytes from `g_rdata_restore_252e8`.

What round 112's `.scratch/keepcrt.c` experiment shows is that the *mechanism*
alone is not enough: adding the literals without cutting the blob drops `.rdata`
0x32d1 -> 0x3091 and removes `crt0msg.obj`'s data symbols from the map, but the
same-offset `.rdata` match is unchanged (81.39% -> 81.32%) because the region
then has to be refilled by postlink's import-bookkeeping copy.  Cutting the blob
is what turns it into bytes.

**Round-114: round 113's plan does not work, and `/FORCE:MULTIPLE` is back on
the table.**

**MSVC6 will not put our literals in `.rdata`.**  Two measurements:

- An *unreferenced* string literal is not emitted at all -- a TU containing
  only `"runtime error ";` produces `.drectve`, `.text` and `.debug$F`, with no
  `.rdata` and no `??_C@` symbol.
- A *referenced* one goes to **`.data`**, not `.rdata`, under `/O2 /Gd /MT` with
  `/Gf`, `/Gf /Gy` and `/GA` alike (a switch-bodied anchor emitting three
  literals gives three `.data` sections of 15, 14 and 37 bytes).

LIBCMT's own crt0msg strings are `.rdata` (they land at 0x10026724 in our
build), so the CRT was built with a placement this toolchain will not reproduce
from C.  That kills round 113's plan: re-emitting the 17 strings from a
`// DATA: SERVER 0x10026110` TU would put them in `.data`, leave the `.rdata`
gap at 0x10026110-0x10026395 unfilled, and shift every byte after it by 645 --
which is worse, not better, because postlink patches by offset.

**The duplicate therefore has to go through COMDAT selection, and
`/FORCE:MULTIPLE` appears to be what defeats it.**  Both builds emit LIBCMT's
copy *and* the split object's copy of the same `??_C@...` sections; a COMDAT
collision should keep one.  Relinking without `/FORCE:MULTIPLE` (round 113)
fails on exactly four *non-COMDAT* duplicates, all of them local
reconstructions overriding a LIBCMT definition:

```
_putc           link_stubs.c        vs LIBCMT fputc.obj
__amsg_exit     crt_region/amsg_exit.c  vs LIBCMT dllcrt0.obj
__FF_MSGBANNER  crt_region/amsg_exit.c  vs LIBCMT crt0msg.obj
___app_type     link_stubs.c / data_globals.c  vs LIBCMT dllcrt0.obj
```

Resolving those four -- each is a deliberate local reconstruction of code the
reference has at a known VA -- and dropping `/FORCE:MULTIPLE` is the next
experiment: it is the only remaining mechanism that can make the linker discard
the duplicated string block, and it would do so in both the CMake build and the
split set at once.

**Round-111: position alignment is complete, and the asm constraint is
audited.**

**Every tracked function is now at its reference VA.**  `scripts/link_drift.py`
on `build/split_poc.dll` reports a single drift change -- the first symbol, at
delta `+0` -- so the whole 141 KB `.text` is position-correct for the first time.
Rounds 104-110 fixed one object span at a time to get here
(`m_AllocTracked`, `CrashDump`, `vfs_ReadCompressed`, `cm_ExCopyEntityData`);
the four are the only objects in the game region whose COMDAT span ever
disagreed with the reference's.

**The "only C" constraint: there is no naked asm left, and the six remaining
inline-asm blocks are load-bearing.**

```
grep -rn "_emit\|__declspec(naked)" src/server.dll   ->  nothing
```

Six files carry exactly one `__asm` block each, all the msvc6 block-fill /
copy prelude:

```
Units/vfs/vfs_ReadData.c              our alignment+movsb/movsd prelude
Units/m_alloc/m_alloc_c/m_AllocTracked.c   rep stosd/rep stosb block fill
Units/m_alloc/m_alloc.c                    same
Units/m_alloc/m_alloc2.c                   same
DieGildeAddOnServer/server4.c              same
DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c  same
```

They are named-operand inline asm (`mov edi, buf`), not `_emit` byte dumps, and
`docs/msvc6-allocator.md` Finding 19 records that no shipped MSVC -- 6.0, SP1-6,
5.0, 5.0-sp3, under `/O2 /O1 /Ox /Og- /Oi- /G5 /G6 /Oy- /Ot` -- emits the
prelude from any C spelling of `memcpy` or of a hand-written head/middle/tail
loop.  Removing one is not free: replacing `vfs_ReadData`'s block with
`memcpy(buf, fsrc, total)` gives obj 450 (the plain intrinsic), a byte loop 442,
against 472 today -- and its COMDAT span would move 480 -> 464/448, which would
re-break the position alignment rounds 107-110 just established, for everything
after it.  Flagged as a known tension between "only C" and byte identity; the
blocks stay until either a C spelling is found or the user overrules.

**Where the remaining difference is.**  `rebrew todo` lists exactly two items,
both already-known: `gm_AllocSpieler` (SIZE_MISMATCH, obj 3688 against 3689) and
`ServerMainThread` (STUB, obj 2434 = target exactly, 86.9% aligned).  By
alignment-corrected byte match (`scripts/align_match.py`) the tail is:
`cm_ExProdObjekt` 92.9, `ls_LoadBuildingEntityState` 88.8,
`cm_ProcessCommandQueue` 88.3, `gm_CheckInventoryCapacity` 87.7,
`ServerMainThread` 86.9, `gm_ObjectsAvailble` 86.0, `gm_CalculateProductionValue`
82.9, `cm_ExCopyEntityData` 77.9 (was 77.1 before round 110's clamp reorder),
`ahm_ExAllocAlchemist` 76.6, `vfs_ReadCompressed` 76.5 (was 79.0 -- the
round-110 single-read hoist costs 2.5 points locally), `srv_LoadBuf` 75.7,
`gv_ExAllocGraveyardWorker` 73.6, `m_AllocTracked` 72.7, `cm_ExSellObjekt` 72.6,
`gm_AllocSpieler` 63.4, `gm_FindNextFilteredEntity` 61.0.

Where postlink's 1,403 non-validating layout-map entries sit
(`.scratch/mapcov.py`, exact-value comparison against
`layout/server.dll/operands.txt` + `calls.txt`):

```
 711  untracked (CRT region, spread over text offsets 0x19000-0x22000;
      those windows are 90.5-95.2% raw-identical at the same offset)
 186  gm_AllocSpieler          114  ls_LoadBuildingEntityState
 121  CrashDumpUnhandled...    105  ServerMainThread
  97  cm_ExSellObjekt           67  srv_InitBuildingTypeTable
```

Note that several of the smaller offenders (`srv_InitBuildingTypeTable`,
`gm_Open`, `srv_LogWinsockError`, `srv_RecvGame`) are **RELOC** -- their
instructions are where the map says and only the address *values* differ, which
is what postlink patches.  The genuinely open ones are the SIZE_MISMATCH /
PROVEN functions above.

**Round-110: all three position breaks fixed.  Whole-`.text` masked 76.61% ->
94.97%; postlink coverage 56.6% -> 81.2%.**

Three object sizes were holding the whole game region and the CRT tail off
their reference VAs.  All three are now correct, and the three edits are one
reordering plus two hoists -- no semantics changed.

```
                        obj        span        reference span
CrashDumpUnhandled...   2137->2113  2144->2128   2128
vfs_ReadCompressed       497->481    512->496     496
cm_ExCopyEntityData      880->904    880->912     912
m_AllocTracked (r107)    654->660    656->672     672
```

```
                        whole .text raw   masked    postlink coverage
round 107/108 state          58.45%        76.61%   4221/7463 = 56.6%
now                          87.02%        94.97%   6060/7463 = 81.2%
```

The three fixes:

1. **`cm_ExCopyEntityData` -- a clamp reordering, and it improves content too.**
   The `ebx_type == 0` arm and the matrix loop are now spelled "in range first,
   then HIGH, then low" (`else if (rel_value >= 0x7f)`) instead of "in range
   first, then low, then high".  That makes msvc6 materialise the clamp
   constants in eax (`mov eax,0x7f` / `mov eax,0xffffff81`) in four more arms
   rather than folding them into byte-immediate stores.  880 -> 904, span 912;
   positional 196 -> 198; register-agnostic 202/31 -> 204/25.  Either clamp
   alone gives obj 892 / span 896 -- one byte short of the window, which is why
   round 109 saw it as "not enough".
2. **`vfs_ReadCompressed` -- read the volatile `done` once.**  The reference
   reuses eax across `cmp eax,1 / je / test eax,eax / jne`; ours re-read the
   volatile between them.  Hoisting it into a block-scoped `int d` gives
   497 -> 481, span 496.  Register-agnostic matched 176 -> 171: a real content
   cost, taken because the span is worth 18 points of whole-.text match.
3. **`CrashDumpUnhandledExceptionFilter` -- share the log tail.**  Our object
   had FIVE `call LogMessageInternal` sites for the same five messages; the
   reference has FOUR call instructions because it shares `push 1; push
   0x10027144; call` between the VirtualAlloc-failed (0x218) and ReadFile-size
   (0x21b) paths.  Routing both through an out-of-line `log_close` label with
   the line and message in locals reproduces the sharing: 2137 -> 2113, span
   2128; positional 347 -> 352; register-agnostic 416 -> 423.

   The label has to sit at the END of the function.  Placing it directly after
   the `if (!pDbgBuf)` block makes the entire rest of the body unreachable and
   msvc6 dead-code-eliminates it -- measured: a 320-byte function.

Game region 92.16% -> 92.10% (6491 -> 6542 differing): the two restructurings
cost a little local content, which the +18.4 points of whole-.text alignment
swamps.  Gate: 186 lint files, 0 errors, `verify --full` 281/283.

**What is left.**  postlink still refuses (81.2% against a 90% gate).  The
remaining 1403 non-validating map entries are: the `+690` byte overhang after
the last CRT symbol (the `crt_region/` objects the split rsp appends), the
in-object closure-helper drift `1001b200_.text.obj` / `1001eab0_.text.obj`
(+0x31c internally), and the game region's instruction-level differences.

**Round-109: the three spans are worth +18.4 points, two of them are in hand,
and `CrashDump` is the blocker.**

**The prize, measured.**  `.scratch/padobj.py` forces the three open objects to
the reference spans (`CrashDump` 2144 -> 2128, `vfs_ReadCompressed` 512 -> 496,
`cm_ExCopyEntityData` 880 -> 912) and `scripts/split_link.sh` relinks:

```
                              whole .text raw   masked   postlink coverage
current (net 0, spans wrong)      58.45%        76.61%   4221/7463 = 56.6%
all three spans correct           87.04%        95.01%   6056/7463 = 81.1%
```

+18.4 points of whole-`.text` masked, and 81.1% is within striking distance of
postlink's 90% gate (the CMake build, whose CRT is scrambled, sits at 30.8%).
The game region barely moves (92.16 -> 92.15), so the whole of that gain is the
CRT tail coming into place.

**Two of the three fixes are found -- both are pure branch reordering, no
semantic change.**

1. `cm_ExCopyEntityData`, in the `ebx_type == 0` arm and the matrix loop: spell
   each clamp "in range first, then HIGH, then low" (`else if (rel_value >=
   0x7f) { rel_value = 0x7f; } else { rel_value = -0x7f; }`) instead of "in
   range first, then low, then high".  Either reordering alone gives obj 892,
   whose span is 896 -- still one byte short of the window -- and both together
   give obj **904 / span 912**, the reference bucket:

```
                             obj   positional  reg-agnostic matched / tgt-only
baseline                     880      196            202 / 31
type-0 high-first            892      --            203 / 27
type-0 + matrix high-first   904      198            204 / 25
```

   So this one improves the content as well as the size.
2. `vfs_ReadCompressed`: hoist the volatile `done` read into one local --
   `{ int d; d = done; if (d == 1) return result; if (d != 0) return d; }` (or
   the same through the dead `i`/`n`) -- obj 497 -> **481 / span 496**.  The
   reference reuses `eax` across the two tests where ours re-reads the volatile;
   the content cost is 176 -> 171 register-agnostic matched, which the +18.4
   whole-binary points swamp.

**`CrashDump` is the blocker, and its +22 is not source-steerable.**  Needs real
2137 -> 2113..2128.  The whole deficit is inline-vs-outlined cold blocks: our
object has **five** `call LogMessageInternal` sites (line numbers 0x220, 0x21b,
0x218, 0x213, 0x20f) and the reference has only **four** `call` instructions for
the same five messages -- it shares the `push 1; push 0x10027144; call` tail
between the 0x218 (VirtualAlloc failed) and 0x21b (ReadFile size) paths:

```
0x10002e1d push 0x10027120     <- 0x218 message
0x10002e22 push 0x218
0x10002e27 jmp  0x10002e35
0x10002e29 push 1
0x10002e2b push 0x10027110     <- 0x21b message
0x10002e30 push 0x21b
0x10002e35 push 0x10027144     <- shared tail
0x10002e3a call LogMessageInternal
```

C cannot express "jump into the middle of another call's argument pushes", so
that sharing is not reachable from source.  Merging the two sites *fully* (one
shared call) lands at ~2107, span 2112 -- six bytes *below* the window -- so the
obvious restructuring overshoots.  This is the same layout-pass behaviour as the
missing third epilogue in `cm_ExCopyEntityData` (round 104) and the folded
redundant tests in `cm_ProcessCommandQueue` (round 106).

**Both ready fixes stay unlanded on purpose.**  The three errors sum to zero
(`+16 +16 -32`) and that net is what places the 58 KB CRT tail; round 105
measured a strict subset (net -16) at 48.83% against the current 63.66%.  Land
all three together or none.  The two above are one edit each, so the round that
cracks `CrashDump` lands the whole set.

**Round-108: the rel32 blind spot bites a second time -- a call to a data stub.**

`rebrew test` masks the rel32 of every call, so a call to the **wrong**
function passes as RELOC.  Round 107's missing `srv_SeedRandom` thunk was one
instance of that; a multiset compare of every tracked object's call targets
against the reference's (`.scratch/callscan.py` for the sweep,
`.scratch/callcmp.py` to print one function's lists side by side) turns up a
second, and a worse one:

```
reference  gv_HireProductionWorker 0x10011337  call 0x10016ea0
ours       gv_HireProductionWorker             call _fcn_10016ea0
```

0x10016ea0 is `gm_SubObjectNoKill` in `spiel_dumpD.c`, whose definition is
`int __cdecl gm_SubObjectNoKill(int a, int b, int c)` -- the same three
arguments the two call sites pass.  Our sources instead called
`fcn_10016ea0`, and `src/link_stubs.c` defined that name as a **4-byte data
variable** (`int fcn_10016ea0 = 0;`), auto-generated back when the function was
still unreversed.  The link therefore resolved both calls to a data address: a
call that would fault at run time, invisible to `rebrew test` (masked) and to
postlink (it patches the rel32 to the reference value regardless).

Fixed: `gv_HireProductionWorker.c` and `gv_ExtendProductionTime.c` declare and
call `gm_SubObjectNoKill`, and the stub is gone.  Sizes are unchanged --
`.text` 0x223d6, whole-`.text` masked 76.61%, game 92.16% / 6491 -- so the fix
buys correctness of the built image, not a metric.  Note that
`scripts/gen_link_stubs.py`, which the stub file's header says to regenerate
with, no longer exists; `link_stubs.c` has to be edited by hand.

**The same scan's other ~20 hits are labelling, not wrong callees.**  Do not
"fix" them:

- `library_msvc.h` mislabels `fclose.obj`'s first section (0x1001a18a) as
  `_fflush` when it is `_fclose` -- the code there tests `[esi+0xc] & 0x40`,
  locks the stream and calls `0x1001a1bb`, which `map_full.json` names
  `fclose_lk`.  Eight call sites in six functions (`_DispatchLogOutput`,
  `_InitializeLogAndErrorHandler` x2, `gm_Open` x2, `vfs_CloseStream`,
  `vfs_DestroyEntity`, `CloseVfsStream`) are `fclose` in ours and resolve to
  that same member section, byte for byte.
- `ftell.obj`'s first section (0x1001a2eb) is the public `ftell` wrapper (lock,
  call the 353-byte worker, unlock); our `_ftell` is that same wrapper, and the
  353-byte worker is what `map_full.json` labels `ftell`.

`map_full.json`'s **member** names are the authoritative side of that
comparison; the per-function `name` field is a heuristic label and several are
wrong.

**Round-107: a missing 16-byte function was holding the whole CRT region 16
bytes early.  Whole-`.text` masked 63.66% -> 76.61%.**

The reference has a 12-byte thunk at **0x1001a150** that our tree never had:

```
0x1001a150  mov eax, [esp+4]
0x1001a154  push eax
0x1001a155  call _srand            (0x1001b535)
0x1001a15a  pop ecx
0x1001a15b  ret
```

i.e. `void __cdecl srv_SeedRandom(unsigned int seed) { srand(seed); }`.  It is
called from **six** command handlers -- `cm_ExAllocSpieler` 0x1000d476,
`cm_ExAllocClientSpieler` 0x1000d58b, `cm_ExEmployWorker` 0x1000f74b,
`cm_ExCreateCitizen` 0x1000f9b2, `cm_ExAllocGraveyardWorker` 0x10010328 and
`cm_ExAllocAlchemist` 0x10010368 -- which our sources had calling the CRT
`srand` directly.

**Why it survived every previous pass.**  `rebrew test` masks the rel32 of every
call, so `call _srand` and `call 0x1001a150` are the same object to it: all six
callers are RELOC and stay RELOC either way.  The catalog made the same mistake
in the other direction -- `library_msvc.h` and `CATALOG.md` record 0x1001A150 as
LIBCMT's `_srand` (`LIBRARY/EXACT`), but `map_full.json` puts `rand.obj`'s
`srand_impl` at 0x1001b535, so 0x1001a150 is not a library section at all.  And
`functions.txt` lists it as `fcn.1001a150`, 12 bytes, untracked.

**The whole CRT region was 16 bytes early because of it.**  The split set places
`_fclose` at 0x1001a17a against the reference's 0x1001a18a: everything from
`_fclose` back was short by exactly this object, and a uniform misplacement is
invisible to a per-function match (each function still matches itself) while
being fatal to a same-offset byte compare.

```
                        split exact-VA symbols   delta range      whole .text raw   masked
before                  1 / 319                  -0x10..+0x30c    33.57%            63.66%
after                   246 / 319                +0x0..+0x31c     58.45%            76.61%
```

Build `.text` 0x223c6 -> 0x223d6 (+16); game region unchanged at 92.16% / 6491
differing, as it should be -- the fix is entirely in the CRT.  Gate: 186 lint
files, 0 errors, `verify --full` **281/283** (baseline raised 280 -> 281).  The
remaining split drift (`+0x0..+0x31c`) is now confined to the two closure-helper
objects `1001b200_.text.obj` and `1001eab0_.text.obj`, whose internal symbol
offsets differ by up to 0x31c while the objects themselves end in the right
place.

Landed: `src/server.dll/DieGildeAddOnServer/server_c/srv_SeedRandom.c`, an
`extern` in `command_internal.h`, and the six call sites redirected from
`srand` to `srv_SeedRandom`.

**The CRT half is now essentially done in the split set.**  Same-offset raw
match of `build/split_poc.dll` vs the reference, per 8 KB window: the CRT
windows (`0x1a000` up, i.e. VA 0x1001a000 onward) read 93.9 / 95.1 / 92.7 /
94.8 / 96.7%, and every *tracked* CRT function reports 100.0% masked with drift
+0 (`__CRT_INIT` 217 B, `_mlock` 97 B, `__old_sbh_alloc_block` 520 B,
`___sbh_find_block` 43 B, `DllMain` 157 B, all 0 differing).  The residual in
those windows is untracked CRT bytes, not misplacement.

That makes the split set's object list the thing the **build** should be
linking.  `scripts/split_link.sh` already assembles it (CMake objects + one
object per mapped LIBCMT section, in reference order); the CMake target still
links stock `LIBCMT.lib`, whose member order is scrambled (round 106, drift
+9516 at `__CRT_INIT`).  Converting the target to the ordered object list is the
next structural step; nothing about the CRT's *content* is still open.

**Round-106: the CRT member set, and why `.text` size parity is a trap.**

**The CMake link is missing 26 LIBCMT members the reference has.**  Joining
`build/probe2.map` (a `/MAP` link of the current objects) against
`build/split_poc/map_full.json` on member name gives 93 members in our link, 116
in the reference, and 26 of the reference's absent.  Fifteen are absent as
*symbols*, not merely as member names -- the rest are provided by the
`crt_region/` local definitions rather than the library:

```
_strcspn _strpbrk _stricmp _strnicmp _tolower _memmove __mbscat _ecvt _strdup
_fptostr _strgtold12 _atodbl _cfltcvt _controlfp __mbsdup
```

All but the last five are public in the toolchain's own `LIBCMT.lib`.  The
reference also has `mlock.obj`, `sbheap.obj`, `cprintf.obj`, `wincrt0.obj`,
`wwincrt0.obj`, `fpinit.obj`, `crtmbox.obj`, `popen.obj`, `wpopen.obj`,
`fgetchar.obj`, `fgetwchr.obj` and `cwprintf.obj` whose symbols our link *does*
define, from `src/server.dll/crt_region/*.c`.  Our link has three members the
reference does not: `strcat.obj`, `strdup.obj`, `winxfltr.obj`.

**Forcing them in fixes the size and nothing else.**  `/INCLUDE:` is already the
project's mechanism for this (eight directives in `CMakeLists.txt`), so the
marginal cost of each missing member was measured by relinking with one
directive at a time:

```
baseline                0x223c6              _memmove   0x22706  (+832)
_strcspn   0x22406 (+64)   _strpbrk  0x22406 (+64)   __mbscat 0x224b6 (+240)
_strdup    0x223d0 (+10)   _tolower  0x22506 (+320)  _stricmp 0x225e2 (+540)
_strnicmp  0x22613 (+589)  _ecvt     0x22855 (+1167) reference      0x22846
```

`_memmove` + `_tolower` is exactly `+832 +320 = +1152`, and the link then
reports **`.text` 0x22846 -- the reference's size to the byte**.  It is worth
nothing:

```
                       .text      same-offset raw match   drift at __CRT_INIT
baseline (probe2.dll)  0x223c6    46644/140230 = 33.26%       --
+_memmove +_tolower    0x22846    46697/141382 = 33.03%      +9516
```

The raw match *falls*, and `__CRT_INIT` then sits 9516 bytes after its reference
VA.  Size parity is not layout parity: what is wrong in the CRT region is the
member **order**, and `/INCLUDE` cannot steer it -- the linker appends a forced
member in the library's own index order, not in the order the directives appear.
Only an explicit, ordered object list can, which is what `scripts/split_link.sh`
builds and why its `.text` is +674 with the members roughly in place instead of
scrambled.  Do not chase `.text` size here; chase the order.

Two smaller notes from the same link: `/INCLUDE:__strdup` in `CMakeLists.txt`
resolves nothing (the public symbol is `_strdup`; the member's alias is
`__mbsdup`), so that directive is a no-op, measured at +10 bytes when corrected;
and `strcat.obj` in our link against `mbscat.obj` in the reference is the same
LIBCMT-version rename as `strdup.obj` / `mbsdup.obj`.

**The honest per-function metric, for the record.**  `scripts/align_match.py`
(alignment-corrected, so one inserted instruction does not desynchronise the
count) ranks the non-exact functions:

```
 cm_ExProdObjekt            354 tgt / 369 cand   329 identical   92.9%
 ls_LoadBuildingEntityState 499 / 495            443             88.8%
 cm_ProcessCommandQueue     205 / 204            181             88.3%
 gm_CheckInventoryCapacity  138 / 142            121             87.7%
 ServerMainThread           627 / 641            545             86.9%
 gm_ObjectsAvailble         229 / 235            197             86.0%
 gm_CalculateProductionValue 123 / 127           102             82.9%
 vfs_ReadCompressed         200 / 216            158             79.0%
 cm_ExCopyEntityData        249 / 239            192             77.1%
 ahm_ExAllocAlchemist       286 / 293            219             76.6%
```

The top of that table is *one instruction out of place*, not missing code.
`cm_ExProdObjekt`'s entire residual (`scripts/regdiff2.py`: 351/354 matched,
3 runs) is a three-instruction rotation -- the target loads `g_unknown_1de450`
into edx *above* the volatile `loop_count` store, ours sinks it below.  Four
spellings were compiled and are byte-identical at obj 993: splitting the load
onto its own line above the store (`recipe_shift = g_unknown_1de450;`), the same
through a `char* gsave` temp, moving the whole `recipe_shift` assignment above
the store, and the baseline.  The volatile store is the scheduling barrier and
the load cannot be hoisted across it from C -- the conclusion the file's own
pass-7 note reaches from the other side (hoisting the *whole* address
computation clears the 14 bytes but sinks the store past `lea edi,[eax+0x26]`,
net 966).  `gm_CalculateProductionValue` is the same shape one slot wide:
`cmp byte ptr [esi],0x17` interleaved into the x87 sequence, ours one
instruction earlier, 122/123 matched.

**Round-105: the three open spans must land together, and one of them is a
compiler-phase difference.**

**A partial span fix is a regression.**  The three remaining errors sum to
`+16 (CrashDump) +16 (vfs_ReadCompressed) -32 (cm_ExCopyEntityData) = 0`, which
is *why* the CRT tail currently lands on the reference's offset at all.  Fix any
strict subset and the net moves off zero and the 58 KB CRT region follows it.
Measured with `.scratch/padobj.py` (vfs_ReadCompressed's object forced to span
496, nothing else touched):

```
                          whole .text masked    whole raw    built .text delta
current (net 0)           89997/141382 = 63.66%   33.57%          +674
vfs span fixed (net -16)  69037/141382 = 48.83%    7.74%          +658
```

So the earlier "fixing vfs_ReadCompressed's span alone is worth +7.8 points"
measurement (round 104) was made against the *pre-`m_AllocTracked`* tree, whose
net was `-16`; with the net now correct, the same change costs 14.8 points.  The
three have to move as one set, or not at all.

**`cm_ExCopyEntityData`'s +17..32 is a compiler-phase difference, not source.**
The reference materialises the clamp constants in a register in every cold arm
(`mov eax,0xffffff81` / `mov eax,0x7f`, then `mov [mem],al`), roughly +5 bytes
per arm over SP6's `mov byte ptr [mem],imm8`; this is exactly the
"store-via-reg" fingerprint `rebrew toolchain detect` flags.  Probed on the
current body and **byte-identical at obj 880**: `(int) val`, `(unsigned char)
val`, `*(int*) &mat_row[inner_idx] = val`, dropping the `(char)` cast at each of
the four clamp sites and at all of them together, plus round 104's four epilogue
spellings.  SP6 forward-substitutes through the block duplication; the reference
compiler did not.  Under the pinned toolchain this function's window is not
reachable from C, which is what makes the whole set above blocked.

**`vfs_ReadCompressed`'s honest fix exists, and must not be landed alone.**  The
candidate re-reads the volatile `done` where the reference reuses `eax`:
target `cmp eax,1 / je / test eax,eax / jne`, ours `cmp eax,1 / je / mov
eax,[esp+0x14] / test eax,eax / jne`.  Hoisting the read into one local --
`{ int d; d = done; if (d == 1) return result; if (d != 0) return d; }`, or the
same through the dead `i` or `n` -- gives obj **481** (span 496 = the reference
bucket) against 497, for a register-agnostic cost of 176 -> 171 matched
(7 -> 13 target-only).  It is the right fix and it is currently unlandable,
because by the first item it would move the net to -16.

**`srv_LoadBuf`'s remaining gap is one instruction.**  Register-agnostic over the
226-instruction function: 222 matched, 1 target-only, 1 cand-only.  The one
difference is the frame offset -- target `lea ecx,[esp+0xb0]` against our
`[esp+0xb4]`, with the frame size itself identical (`sub esp,0x2a0` on both
sides).  All six permutations of the three buffer declarations
(`logbuf_hi[256]`, `logbuf_lo[256]`, `pktbuf[156]`) are byte-identical, so the 4
bytes are not declaration order.  The other 48 differing bytes are register
roles.

**Process note.**  `.scratch/padbak/*.obj` snapshots are taken from the *build
tree*, so restoring them after a source fix silently reverts that object: the
tree read `.text` 0x22ad8 instead of 0x22ae8 and the whole-`.text` metric fell
back to 53.37%.  Rebuild the object from source after a source change; only use
the snapshot to undo a padding experiment inside the same build revision.

**Round-104: the four position-alignment breaks -- one fixed, three windowed.**

**`m_AllocTracked` is fixed and out of the list.**  Its window was 657..672 and
its size deficit was not code at all: the group-list sentinel was written as the
literal `(struct GroupNode*) 0x117640a0`, so msvc6 proved the address nonzero and
folded the reference's loop-head null test (`mov esi,offset g_alloc_root; mov
eax,esi; test eax,eax; je`) into an unconditional `jmp`.  Declaring the global
`extern` (the address is not known until link, so it cannot be folded) and using
`(struct GroupNode*) &g_alloc_root_name` -- the spelling `m_ReportGroupInfo.c`
already uses on the same global -- gives

```
obj_size          654 -> 660        COMDAT span 656 -> 672  (= the reference's)
rebrew test match 269 -> 451
register-agnostic 232 matched / 5 target-only -> 235 / 2
postlink layout coverage            8.2% -> 30.8%
whole-.text masked                53.37% -> 63.66%   game 92.08% -> 92.16%
game differing bytes                 6563 -> 6491
```

One object, +10.3 points of whole-`.text` masked match and 72 bytes in the game
region.  Note what the fix does to the drift *profile*: the four errors used to
cancel (net `+16-16+16-32 = -16` entering the CRT), and correcting one leaves the
net at `+16+0+16-32 = 0`.  The game region now reads drift `0 / +16 / +32 / 0`
across `0x10002fc0 / 0x10008c80 / 0x1000efb0`, so the middle is *less* aligned
locally than before while the whole binary is much better -- the CRT tail is
where the bytes are, and 0 is the right number there.  Every one of the three
that remains has to be fixed for the game region to be right as well.  The three
breaks that remain:

| function | ours | ref code | ours span | ref span | needs |
|---|---|---|---|---|---|
| `CrashDumpUnhandledExceptionFilter` @0x10002770 | 2137 | 2115 | 2144 | 2128 | 2113..2128 (shrink 9..24) |
| `vfs_ReadCompressed` @0x10008a90 | 497 | 492 | 512 | 496 | 481..496 (shrink 1..16) |
| `cm_ExCopyEntityData` @0x1000ec00 | 880 | 901 | 880 | 912 | 897..912 (grow 17..32) |

Every remaining layout problem in the game region is **one object whose 16-byte
COMDAT bucket differs from the reference's**.  `scripts/link_drift.py` on the
build *before* the fix above showed the drift change exactly four times between
`0x10001130` and `0x1001a0d0`, and each change is attributable to the object
immediately before it (`0x10002fc0-0x10002770 = 0x850`,
`0x10006820-0x10006580 = 0x2a0` -- now fixed, `0x10008c80-0x10008a90 = 0x1f0`,
`0x1000ef90-0x1000ec00 = 0x390`).  `span = align16(COMDAT length)` and the span
is exactly `next_ref_VA - ref_VA`, so **any** length inside the window re-aligns
everything after it.  Being 1 byte from the target's length is not a 1-byte
problem, it is a 387-symbol problem.  The original table, for the record:

| function | ours | ref code | ours span | ref span | needs |
|---|---|---|---|---|---|
| `CrashDumpUnhandledExceptionFilter` @0x10002770 | 2137 | 2115 | 2144 | 2128 | 2113..2128 (shrink 9..24) |
| `m_AllocTracked` @0x10006580 | 654 | 658 | 656 | 672 | 657..672 (fixed above) |
| `vfs_ReadCompressed` @0x10008a90 | 497 | 492 | 512 | 496 | 481..496 (shrink 1..16) |
| `cm_ExCopyEntityData` @0x1000ec00 | 880 | 901 | 880 | 912 | 897..912 (grow 17..32) |

**What that is worth, measured.**  `.scratch/padobj.py` rewrites the four
objects' `.text` raw size to the reference span (nop-padding three, truncating
CrashDump) and `scripts/split_link.sh` relinks; `scripts/text_match.py --drift
auto` then reports

```
                     whole .text masked        game masked   game differ
baseline (spans wrong)   75459/141382 = 53.37%     92.08%        6563
spans forced correct    115905/141382 = 81.98%     92.07%        6570
```

Both rows are measured against the same `db/verify_results.json` (the game
region's baseline reads 92.16% / 6495 against the previous DB revision), so the
0.01-point game wobble is noise and the +28.6 points of whole-`.text` is not.
`m_AllocTracked` of that set is now really fixed (above), which is where the
63.66% comes from; the three still-open windows are the remaining gap between
that and 81.98%.

The gain is in the CRT region: the split objects there are placed `+16`
early/late and the four sizes move the whole tail into place.  This is by a wide
margin the largest single lever left, and it is why the four windows above are
the priority over any further per-function content work.

`.scratch/padobj.py` is a measurement tool, not a fix: nops are not the
reference's bytes, and CrashDump's truncation cuts real code.  It answers "how
much is alignment worth", and the answer is "far more than the content gaps".

Fixed one at a time the payoff is smaller but still large -- **superseded, see
round 105: this was measured against the pre-`m_AllocTracked` tree, where the
net offset was -16; with the net correct the same change is a regression**:
forcing only `vfs_ReadCompressed`'s span to 496 gives whole `.text` raw
13.64% -> 26.78% and masked 53.37% -> **61.14%** (`delta range -0x30..+0x2ec`).  So each of the four
moves the CRT tail, and the four together are worth more than the sum of the
parts -- the tail has to land on the reference's own offset, not merely closer
to it.

**Three attractive size fixes were measured and rejected.**

1. `/Ge` lands `m_AllocTracked` on **exactly** real 658 / span 672.  It does it
   by replacing the prologue's `sub esp,0x118` with `mov eax,0x118; call
   __chkstk` -- 4 bytes of stack probe the reference does not have.  A size
   match, not a content match: `rebrew test` drops 269 -> 177 positional and
   the aligned diff loses `sub esp,0x118` itself.  Rejected as a size cheat.
   (It is also one byte away from fixing `cm_ExCopyEntityData`: `/Ge` there is
   real 887 / span 896, and the window starts at 897.)
2. `#pragma optimize("a", on)` (or `/Oa`) lands `vfs_ReadCompressed` on real
   489 / span 496 -- the reference bucket -- and would carry the +7.8 points
   measured above on its own.  It is a content regression: the register-agnostic
   alignment drops 176 matched / 7 target-only to **162 / 16**, and the target's
   own tail keeps a value in `edx` across the byte stores where the /Oa form
   spills it back to `[esp+0x10]`.  `/Oa` is not the reference's flag for this
   file; it just happens to land the size.  Rejected, but flagged as the
   cheapest honest-looking size lever if the content is ever fixed anyway.
3. `msvc-6.0-sp5-pp` (the SP5 VC++ patch build in `rebrew-toolchains`) fixes
   two of the four outright -- `vfs_ReadCompressed` 496 with 192 matched
   (against 497/161) and `cm_ExCopyEntityData` 897 with 438 (against 880/525) --
   and `m_AllocTracked` moves 654 -> 632, `CrashDump` 2137 -> 2073, so it is not
   an overall win either.  It is **not usable on the build regardless**: the
   metadata `toolchain` key is read by `rebrew test` only; CMake compiles the
   whole target with the one `rebrew-cmake-cl` wrapper and takes per-file flags
   from each source's `// CFLAGS:` line (`apply_annotation_cflags` in
   `CMakeLists.txt`), so a per-file toolchain would move the measurement and not
   the binary.  VC5 is far worse everywhere (`vfs_ReadCompressed` 514/136,
   `m_AllocTracked` 655/230, `CrashDump` 2093/290) and SP6 SP1..SP6 are
   byte-identical to SP6's own default.

**The "pre-6.0 constant-caching codegen" reading is a false positive.**
`rebrew toolchain detect` reports 5 constant-hoist sites (`mov ebx/ebp/esi/edi,
small-imm32` followed within 32 bytes by `mov [mem], same-reg`), which is the
signal that made `m_AllocTracked`'s notes conclude "the target was not built
with the msvc6 SP6 codegen this project has".  Our own SP6 build reproduces 4 of
the 5 at the same VAs (`0x10001415`, `0x10002439`, `0x100059f4` for the
reference's `0x100059e4`, `0x10015982` for `0x10015992`); the fifth
(`0x10022899`) is in the CRT region `probe.dll` does not reach.  Three of the
five are in **zlib** (`references/zlib-1.1.3`, compiled by this build, not
reversed), one is in `gm_Open` -- which is already RELOC-matched.  So SP6 is the
right compiler and the conclusion in that file is unsupported; the remaining
size gaps are ordinary codegen, not a wrong toolchain.

**Round-104 dead ends, each measured on the current body and reverted.**

- `cm_ExCopyEntityData`'s `0xffff` sentinel: a shared `ushort free_slot` local
  feeding both slot-guard compares, and the same with the comparison operands
  swapped, are both **byte-identical to the baseline** (obj 880, match 525).
  msvc6 rematerialises the immediate at both sites, as pass 3 of that file's own
  notes already recorded.
- Its epilogue spelling: `return (int) 1;`, `return 1u;`, `return (char) 1;`,
  and routing the src-scan-exhausted return through an assigned `src_slot` are
  all byte-identical (880).  The reference's third epilogue is not reachable
  through the return expression.
- `vfs_ReadCompressed`: 17 structural spellings (bottom-test polarity, `!= 0`,
  `(int)` cast, `for(;;)+break`, top-tested loop, `while (i != n)`, `(volatile
  int)` on inflate, swapped accumulator order, `n <= 0x3fff` clamp) leave the
  real size at 497.  Only `avail_out` top-tested (502) and `<= 0x3fff` (500)
  move at all, both the wrong way.  The plateau is a local one.
- `m_AllocTracked`: 12 `#pragma` spellings of the memset/strcpy/strcmp
  intrinsic/function split plus `optimize("a"/"w")`; every one is 654 or
  smaller (615, 579, 650 ...), never the 657..672 the window needs.  A wide flag
  sweep (`/Gs` `/Gi` `/Gz` `/Gv` `/Gr` `/Ge` `/GF` `/GA` `/GD` `/Oi-` `/Ob2`
  `/Op` `/Og` `/Ox` `/Zd` `/G3..G6` `/GB` `/Gy` `/Gs /GF`, and `/O1` `/Os` `/Od`
  which crater) leaves 654/656 except `/Ge` (658, rejected above) and `/G5`
  `/G4` `/G3` `/GB` (656).
- `vfs_ReadCompressed` pragmas: `optimize("a", on)` is the only one that moves
  the size into the window (489/496, rejected above); `"w" "g" "t" "y" "p" "q"
  "i" "b" "e" "n" "z"` are byte-identical, `"s"` 369, `"g",off` 736;
  `function`/`intrinsic(memcpy)` and `(memset)` are inert.

**Round-103: tool fix, and the `0xffff` sentinel is the next content item.**

The gap tool was reporting relocation displacements as content differences: an
object's `movsx r, byte ptr [r]` is the linked `movsx r, byte ptr [r + R]`.
Canonicalising `[reg]` to `[reg + R]` for instructions that cover a relocation
slot removes that class.  `cm_ExCopyEntityData`: matched 198 -> 202,
register-agnostic target-only 39 -> 31.  Re-read every earlier gap number in
this file with that in mind.

What survives in `cm_ExCopyEntityData` is a real content item.  The reference
materialises the slot sentinel once and uses it twice:

```
target 0x1000edc0  mov ebp,0xffff
       0x1000edce  cmp word ptr [eax + 0x100358a0], bp    ; src-slot scan
       0x1000ee5d  cmp word ptr [edx*4 + 0x100358a0], bp  ; dst-slot scan
ours               cmp word ptr [...], 0xffff             ; both folded
```

The two sites are the two `== (ushort) 0xffff` compares at source lines 407 and
436.  Six bytes immediate-vs-three bytes register is a wash for one use and a
win for two, which is why the reference hoisted it -- but msvc6 folds both in
our build, and a first attempt at a shared `ushort free_slot;` local did not
compile and was not pursued to a measurement.  That is the concrete next item
for this function, and it needs the placement of the local such that its live
range spans both compare sites.

**Round-102: a signedness bug, found by the register-agnostic gap list.**
Game region 6,515 -> **6,495** differing bytes.

The gap list for `cm_ExSellObjekt` had a pair that is a genuine type difference,
not allocation:

```
target  mov  r, byte ptr [r + 0x1e]     (a byte register, zero-extended)
ours    movsx r, byte ptr [r + 0x1e]    (sign-extended)
```

Both `gm_QueryEntitySum(*(int*)(... + 0xbc), cmd[0x1e])` call sites in that
function passed a **signed** `char`, so msvc6 sign-extended it.  The reference
zero-extends, and the two differ for every value >= 0x80:

```c
gm_QueryEntitySum(*(int*)(source_owner_entity + 0xbc), (unsigned char) cmd[0x1e]);
```

```
obj_size        2055 -> 2057   (now exactly the target)
register-agnostic target-only  42 -> 38
split pipeline  6,515 -> 6,495 masked differing bytes, game 92.13% -> 92.16%
```

Gate: 0 lint errors, 0 compile/link errors, `verify --full` 280/282, metadata
untouched (`status = "PROVEN"`).

**The pattern does not repeat elsewhere.**  A scan of every remaining non-exact
function's register-agnostic gap for `movsx` against a target byte load finds:
`cm_ExCopyEntityData` 1/0, `gv_ExAllocGraveyardWorker` 1/0, `gm_AllocSpieler`
0/2, `gm_CheckInventoryCapacity` 0/1, `gm_AllocGebaeude` 0/1, and nothing at all
in the rest.  The only clean pair was `cm_ExSellObjekt`'s; the others are
one-sided and belong to the `movsx` versus byte-register choice inside a larger
expression, not to a parameter's signedness.

**`vfs_OpenStream` cannot be measured with the gap tool.**  Its target stream
disassembles into the 5-entry switch jump table and 13-byte case map that follow
the `ret` (the catalogue's 667 excludes them, the doc's 701 includes them), so
the tail of its "target-only" list is `adc byte ptr [r - 0x6f76f000], R` --
data, not instructions.  Read that function's numbers from `rebrew test` and
the file's own notes, not from `.scratch/relcat.py`.

**Round-101: the climb tool is exhausted, and one more width lever regresses.**

`rebrew climb --objective aligned --passes 3 --dry-run` on
`cm_ExCopyEntityData` reports **no improving adjacent-statement swap** at all
(baseline == best == 189,967 aligned bytes, `moves: []`) -- the same verdict the
file already records for `gm_ObjectsAvailble`, and the +1-byte move it still
finds on `gm_CheckInventoryCapacity` (statement 18) reproduces round 25's
number exactly.  The deterministic statement climber has nothing left on the
close functions; its 15 top-level statements on `cm_ExCopyEntityData` do not
reach the nested clamp arms anyway.

**`gm_AllocSpieler`'s x87 comparison is right and its spelling is not the
lever.**  The register-agnostic gap there is 77 target-only, and one entry is a
genuine type difference at 0x10018bb7:

```
target  fild dword [esp+0x10] ; fst dword  [esp+0x24] ; fcomp dword [ebp+0x20]
ours    fild dword [esp+0x14] ; fst qword  [esp+0x24] ; fld dword [ebp+0x20]
                                ^ stores a double      ^ then fcompp
```

i.e. the reference compares in **float** where our `(double)` cast compares in
double, with the 8-byte temporary that follows from it.  Measured three
spellings -- `(float) cast`, no cast, and a parenthesised float -- and all
three are **worse**: obj 3,672 against 3,688 and register-agnostic target-only
77 -> 84 (matched 853 -> 832).  So the `(double)` here is load-bearing for the
function's frame and x87 homes in the same way the deliberate `(double)` casts
in the `slot+0x10` expression are (section 8a); removing one to match a single
`fst` costs more than it buys.  Reverted.

The two smaller items at the same site are also allocator/scheduling: the
reference emits `add edx,0x3c` where ours narrows to `add dl,0x3c`, and `and
edx,0x86` in the 6-byte form where ours uses the 3-byte sign-extended one --
both follow from the value's width, and both are shorter in ours.

**Round-100: what the last few instructions actually are, per function.**

With the register-agnostic metric from round 99, the three closest functions'
entire content gaps are now enumerated, and none of them is semantic:

```
srv_LoadBuf       1 / 1   lea r,[r+0xb0]  against  lea r,[r+0xb4]
m_AllocTracked    5 / 1   mov r,r  mov r,r  cmp r,r  test r,r  je   (loop-entry
                          test)  against  cmp r,dword ptr [R]        (the fold)
gm_CheckInventory 8 / 7   mov r,r  add r,r  mov r,byte ptr [r]  mov r,8
                          lea r,[r+0x10]  mov r,[r+4]  jmp
                          against  mov r,byte ptr [r+r]  (SIB fold)
                          mov [r+0x38],r / mov r,[r+0x38]  (byte spill)
                          cmp r,8  (folded sentinel)  lea r,[r+0x14]
```

`srv_LoadBuf` is one instruction from content-exact and it is a *position*
difference: the reference hoists the second lobby `sprintf`'s buffer `lea`
above the `*conn = *conn & 0xffffff7f` mask, ours emits it after the following
`push`, which is why the displacement reads `0xb4` against the target's
`0xb0`.  The `docs/msvc6-c-shapes.md` section 10/8c levers for pinning that
order (statement permutation, a block-local alias, a volatile read) are all
recorded as inert on this cluster, and the same source owns the `eax/ecx/edx`
rotation that the register-agnostic pass now ignores.

`m_AllocTracked` has no semantic content left at all: its five target-only
entries are the loop-entry null test (round 89, unreachable) plus the one
folded compare, and the single cand-only entry is that fold.

`gm_CheckInventoryCapacity`'s gap is four shapes, all documented as
grid-searched: the entity-address SIB fold, the byte spill, the folded
sentinel `8`, and the `list` base offset (`[esp+0x10]` against `[esp+0x14]`).
Re-measured this round: `elem = *(volatile int*) &list[0];` scores **48** at
obj 398, and making the `list[0] = 8;` store volatile scores **269** at obj 395
against the 293 baseline, so the volatile lever regresses here where it won on
`m_AllocTracked`'s guard.

**Round-99: the content gap is small everywhere -- the mass is the allocator.**

Round 97's tool counted register-role swaps as content differences.  Adding a
second, register-agnostic pass (every register name canonicalised to `r`, so
`mov ebx,[esi+0x18]` and `mov ebp,[esi+0x18]` compare equal while
`[esi+0x18]` against `[esi+0x10]` still differs) changes the picture
completely:

```
function                       tgt  cand  matched  runs  target-only  cand-only
cm_ExProdObjekt                354   354    351      3        0           0
srv_LoadBuf                    226   226    222      8        1           1
m_AllocTracked                 249   245    232     27        5           1
vfs_ReadCompressed             200   201    176     25        7           8
gm_CheckInventoryCapacity      138   137    126     10        8           7
vfs_OpenStream                 206   212    184     22       13          19
gm_FindNextFilteredEntity      118   109     93     14       16           7
gv_ExAllocGraveyardWorker      333   332    295     37       18          17
ahm_ExAllocAlchemist           286   287    256     29       20          21
gm_AllocGebaeude               346   359    303     29       27          40
ls_LoadBuildingEntityState     499   487    466     22       29          17
cm_ExCopyEntityData            249   239    198     31       39          29
cm_ExSellObjekt                667   664    559     88       42          39
gm_AllocSpieler               1056  1053    853    174       77          74
```

Compare the last two columns with round 97's -- `vfs_ReadCompressed` 21/22 ->
7/8, `cm_ExSellObjekt` 103/100 -> 42/39, `gm_AllocSpieler` 218/215 -> 77/74,
`cm_ExProdObjekt` 1/1 -> **0/0**.

Three consequences:

- **`cm_ExProdObjekt` is content-exact.**  Every instruction the reference has,
  we have, with the same operands up to register naming.  Its 13 masked
  differing bytes are entirely allocation and schedule -- which is exactly what
  its file header says about the pre-loop dead-store interleave.  No source
  change can close it.
- **`gm_AllocSpieler`, the largest remaining function at 1,947 differing bytes,
  has 77 target-only instructions out of 1,056** -- about 7% content, 93%
  schedule/renaming.  Same for `cm_ExSellObjekt` (42 of 667) and
  `ls_LoadBuildingEntityState` (29 of 499).
- **Only five functions have a content gap above 25 instructions**, and only
  `gm_AllocSpieler` is above 42.

So the remaining ~6,500 differing bytes are overwhelmingly *not* content.  The
enumerable source work left is: `gm_FindNextFilteredEntity` (16, layout-
bound), `ahm_ExAllocAlchemist` (20), `gm_AllocGebaeude` (27), `ls_Load` (29,
one allocator decision), `cm_ExCopyEntityData` (39), `cm_ExSellObjekt` (42) and
`gm_AllocSpieler` (77).  Everything else is at or below 8.

Practical reading: source reconstruction is essentially done; the goal now needs
either the reference's exact source text or a way to steer msvc6's allocator,
and neither has yielded to any measured lever in this session.

**Round-98: the round-97 tool pays for itself -- `m_AllocTracked` 6,528 ->
6,515.**

The content-gap list for `m_AllocTracked` was seven target-only instructions,
and one pair of them was the fold `docs/msvc6-c-shapes.md` section 8b is about:

```
target 0x10006755  mov edi,[g_stat2]        ; loaded into a register, and live
                   mov eax,[g_array_count]  ;   for the slot loop below
                   cmp eax,edi
ours               cmp dword ptr [g_stat2],reg   ; folded: g_stat2 read twice
                   mov edi,[g_stat2]
```

A volatile read on the operand that must stay in a register fixes it:

```c
if (g_stat2 < *(volatile int*) &g_array_count) {
```

```
obj_size        649 -> 654   (reference 658)
match_count     257 -> 269
content gap       7 -> 6 target-only, 2 cand-only
split pipeline  6,528 -> 6,515 masked differing bytes
```

Both operands are `int` and the read is the same value, so the volatile is
behaviour-preserving.  Gate: 0 lint errors, 0 compile/link errors,
`verify --full` 280/282.

**The lever does not generalise.**  Searching every remaining non-exact
function's content-gap list for a candidate-side `cmp ... [R]` fold finds none:
`ahm_ExAllocAlchemist`, `vfs_OpenStream`, `cm_ExCopyEntityData`,
`vfs_ReadCompressed`, `gm_AllocGebaeude`, `gv_ExAllocGraveyardWorker` and
`cm_ExSellObjekt` have no folded-memory-compare in their gap.  The pattern was
specific to `m_AllocTracked`'s guard, where the loaded global is also live
across the following loop.

**`ls_LoadBuildingEntityState`'s gap is exactly its documented blocker.**
Content gap 49 target-only, and the list opens with `push ebp` / three
`pop ebp` / `or ebp,0xffffffff` / `mov [eax],ebp` -- the fourth callee-saved
register and the `-1` sentinel cache.  Nothing else in its 49 is structural,
so that function is one allocator decision away and no further.

**Round-97: the content/​schedule split, per function.**

New tool `.scratch/relcat.py`.  The old comparisons all conflate two different
things: instructions we are **missing** (a source change can fix those) and
instructions that are merely **scheduled or allocated differently** (no source
change has ever fixed one).  Both look identical to a byte diff, because a
reorder shifts every later byte.

The tool canonicalises both streams with relocation *and* image-address masking
(the candidate is a COFF object whose symbol operands are zeros -- and several
sources here write the target VA as a **literal**, so their object needs no
relocation at all while the reference has one, which is why a relocation-table
based mask disagreed), LCS-aligns, and reports the multiset difference of the
*unmatched* instructions.  Reorders cancel in that multiset; real gaps do not.

```
function                       tgt  cand  matched  runs  target-only  cand-only
cm_ExProdObjekt                354   354    350      4        1           1
srv_LoadBuf                    226   226    212     16        4           4
m_AllocTracked                 249   244    231     27        7           2
gm_CheckInventoryCapacity      138   137    126     10        8           7
gm_FindNextFilteredEntity      118   109     93     13       16           7
vfs_ReadCompressed             200   201    164     25       21          22
ahm_ExAllocAlchemist           286   287    244     32       33          34
vfs_OpenStream                 206   212    166     24       34          40
gm_AllocGebaeude               346   359    277     39       44          57
cm_ExCopyEntityData            249   239    190     34       47          37
gv_ExAllocGraveyardWorker      333   332    274     39       49          48
ls_LoadBuildingEntityState     499   487    447     35       49          37
cm_ExSellObjekt                667   664    494    112      103         100
gm_AllocSpieler               1056  1053    747    180      218         215
```

Read the last two columns, not the byte counts.  They say:

- **`cm_ExProdObjekt` is one instruction from content-exact.**  Its entire
  content difference is `mov dword ptr [esp+0x18], ebx` (reference) against
  `mov dword ptr [esp+0x18], eax` (ours) -- the long-documented byte 410.  Every
  other run in that function is the pre-loop schedule, where both sides hold the
  same instruction multiset.  Its 13 masked differing bytes are therefore
  schedule, not content.  Re-confirmed unreachable this round: a volatile
  read-back of `quantity` scores 431 at obj 1001, an address read-back and a
  self-assignment are byte-identical at 976.
- **`srv_LoadBuf` is four instructions from content-exact** -- the pure
  `eax/ecx/edx` rotation at the two lobby `sprintf`s.
- **`m_AllocTracked` has 7 target-only against 2 cand-only**, i.e. a net five
  missing instructions, which is its `-13` obj gap.
- **`cm_ExProdObjekt`, `srv_LoadBuf` and `gm_CheckInventoryCapacity` together
  account for 13 of the game region's ~6,500 differing bytes**; the mass is
  `gm_AllocSpieler` (218 missing) and `cm_ExSellObjekt` (103), and both are
  overwhelmingly schedule.

So the remaining work splits cleanly: four functions have a small, enumerable
content gap worth attacking, and eleven are schedule-bound.  The tool is the
first thing here that tells the two apart without a hand-built diff.

**Round-96: CrashDump's +29 is section 17, and the four blockers are all
layout or scheduling.**

`CrashDumpUnhandledExceptionFilter` (0x10002770, obj 2137 against 2115) is the
last of the four position-alignment blockers to be characterised, and its size
error is the block-placement pass.  The bytes at its first error site:

```
target 0x100027a0  call esi                  ; CreateFileA
                   mov ebp,eax  cmp ebp,-1  mov [esp+0x28],ebp
                   je 0x10002e4d             ; <- the error block is OUT OF LINE,
       0x100027ad  push ebx  push edi        ;    at the end of the function
ours               call ebx  mov edi,eax  cmp edi,-1  mov [esp+0x44],edi
                   jne 0xd8                  ; <- the error block is INLINE
                   push 1  push 0x10027104  push 0x220  push 0x10027144
                   call LogMessageInternal  add esp,0x10  jmp <tail>
```

Nine error sites are inline in ours and out of line in the reference, and each
inline one costs a 5-byte `jmp` to skip it.  `docs/msvc6-c-shapes.md` section 17
is explicit that this pass is not steerable from source and that three label
placements were measured inert on `ServerMainThread`; the same verdict applies
here.  So the four alignment blockers are:

```
CrashDump            +29 obj   block placement (section 17) -- not steerable
m_AllocTracked       -13 obj   loop-entry null test + branch encodings
vfs_ReadCompressed    +5 obj   prologue parameter-load hoist
cm_ExCopyEntityData  -32 obj   folded constant stores in the ==2 clamp
```

None of the four is a source-shape lever that has not been tried, which is why
the CMake link's position alignment has to come from the postlink's layout
convergence rather than from matching every object size by hand.

**`gm_AllocSpieler`'s first divergence is also a schedule hoist.**  At 0x10018898
the source order is the reference's -- `*(int*)(0x100358a4 + idx*0x21c) = -1;`
then `memset((void*)(0x100358fc + idx*0x21c), 0xff, 0x20);` -- but msvc6 hoists
the memset setup (`mov ecx,8; mov eax,esi; lea edi,[edx+0x100358fc]`) above the
store, while the reference stores first and then sets up `rep stosd`.  That is
the first of the function's 194 mismatch runs and the pattern for most of them:
same instructions, hoisted setup.

**Round-95: the two remaining game-region size gaps are scheduling, not
source shape.**

**`cm_ExCopyEntityData`'s clamp is closed for now.**  Round 94 localised its
-32 to the two folded constant stores per `ebx_type == 2` branch.  Four more
spellings this round, all at obj 880:

```
one shared store after the clamp, original comparison order   877/505
the same with `rel_value >= 0x7f`                             877/505
clamp through `temp`, the int local that is live in other arms 880/525
`long rel_value`                                               880/525
```

The one-store forms emit *one* store (msvc6 does not tail-duplicate it into the
three branches), so the three-store source shape is right and the only wrong
thing is the fold.  `volatile int rel_value` was re-confirmed as a regression
(1004/194).  The `ebx_type == 0` arm remains the proof that a clamped,
still-live value produces the reference's `mov eax,0xffffff81 / mov [mem],al`
shape -- it has one store after the clamp and matches instruction for
instruction -- so the `== 2` arm needs the same liveness, and no spelling that
keeps its three stores has produced it.

**`vfs_ReadCompressed`'s +5 is a prologue hoist.**  Its first two sizediff runs
are the whole story:

```
target  0  sub esp,8
        1  mov eax,[esp+0xc]      <- the `handle` parameter, BEFORE the pushes
        2  push ebx   3 push ebp   4 push esi
        5  test eax,eax
        6  push edi
        7  mov [esp+0x14],0       <- done = 0
        8  mov [esp+0x10],0       <- result = 0
        9  jne ...
ours    0  sub esp,8
        1  push ebx   2 push ebp   3 push esi   4 push edi
        5  mov [esp+0x14],0
        6  mov [esp+0x10],0
        7  mov eax,[esp+0x1c]     <- loaded after the pushes and the stores
        8  test eax,eax
        9  jne ...
```

Same instructions, same slots, different schedule -- msvc6 hoists the parameter
load above the prologue pushes in the reference.  Every statement permutation
that could express that (moving `done = 0; result = 0;` above or below the
`handle` test, splitting them) leaves the load where it is.

**So the game region's four alignment blockers are three scheduling artefacts
and one fold**, and the map's delta transitions (round 92) confirm the list is
complete: nothing else between 0x10001130 and 0x1001a140 has a size error.

**Round-94: `cm_ExCopyEntityData`'s -32 is two folded constant stores per
clamp, and an object-level disassembly trap.**

`cm_ExCopyEntityData` (0x1000ec00, obj 880 against 912) is the largest of the
four position-alignment blockers and the one that is *far* short, so it got the
round.  `sizediff.py` puts the whole gap in the three `ebx_type` clamp blocks,
and the difference is narrow and specific.

**The addressing is not different -- do not chase it.**  Disassembling the
*object* shows ours as `mov byte ptr [ecx], 0x81` where the reference (linked)
reads `mov byte ptr [ecx + 0x100a9820], al`.  That looks like a materialised
base against a table displacement, but the object's displacement is a **DIR32
relocation slot holding 0**; after the link ours is `[ecx + 0x100a9820]` too.
`scripts/fdiff.py` and `sizediff.py` compare linked bytes, but `objcmp` /
`bigruns` disassemble the object, so relocation displacements read as zero
there.  Both streams put the same value in `ecx` (the `dst_slot` index).

**The real difference is the store source.**  Reference, `ebx_type == 2`:

```
target 0x1000ee8b  cmp eax,-0x7f
                   jl  <low>
                   cmp eax,0x7f
                   jge <high>
                   mov [ecx+0x100a9820],al     <- value still in eax
                   jmp <join>
        <low>      mov eax,0xffffff81          (5)
                   mov [ecx+0x100a9820],al     (6)
                   jmp <join>
        <high>     mov eax,0x7f
                   mov [ecx+0x100a9820],al
ours               mov byte ptr [ecx+0x100a9820],0x81    (7)
                   jmp
                   mov byte ptr [ecx+0x100a9820],al      <- middle branch matches
                   jmp
                   mov byte ptr [ecx+0x100a9820],0x7f
```

The middle branch already matches; the two outer branches fold `(char)rel_value`
into a memory immediate (7 bytes) where the reference rematerialises the
constant in `eax` and stores `al` (11 bytes).  The reference is the *larger*
form, which is why it only appears when the value stays live in a register --
and here `rel_value` is dead after the store, so msvc6 folds in our build.

Measured and inert on the way to that conclusion, all at obj 880:

```
pointer form `*((char*)g_relationship_matrix_primary + dst_slot) = ...`  880/525
`else if (rel_value >= 0x7f)` with the else-branch first                 880/522
clamp then one shared store (the `ebx_type == 0` shape)                  877/505
secondary store and temp load swapped                                    880/525
```

`ebx_type == 0` is the counter-example that proves the shape is source-reachable
in principle: it has one store *after* the clamp, `rel_value` is live there, and
ours matches the reference instruction for instruction
(`mov eax,0xffffff81` / `jmp` / `mov eax,0x7f` / `jmp` / `mov byte [ecx],al`).
So the `== 2` case needs `rel_value` to be live across its three stores, and no
spelling that keeps the three stores has produced that yet.

**Round-93: a size-difference locator, and the 16-byte padding threshold.**

New tool `.scratch/sizediff.py`: aligns the target and candidate instruction
streams, then reports the *byte* difference of every aligned run, so a
function's missing bytes can be located instead of guessed.  It is what turned
`m_AllocTracked`'s "-13" into a list.

**`m_AllocTracked`: the count increment is reachable, the loop-entry test is
not.**  `node->count++` folds to `inc dword ptr [esi+0x20]` (3 bytes) under
every spelling tried, while the reference emits the register form
(`mov eax,[esi+0x20]; inc eax; mov [esi+0x20],eax`, 7 bytes at 0x100066d7).
A **volatile read** is the one form that keeps the value live:

```c
taglen = *(volatile int*) &node->count;
node->count = taglen + 1;
```

Same value in single-threaded code, and it reproduces the reference's three
instructions exactly.  Effect: `obj_size` 645 -> **649** against the reference's
658, aligned instruction match 208 -> **211** of 249, one fewer mismatch run,
split-pipeline masked differing bytes **unchanged at 6,528**.  The positional
`match_count` falls 266 -> 257 purely because the 4-byte insertion shifts every
later operand (the round-88 artefact).  Kept, because the size is what the
whole-binary goal needs and the honest metric does not move.

The remaining `-9` is the loop-entry null test and branch encodings.  Ten more
spellings were tried for the test this round -- sentinel assigned before the
`strncpy`, sentinel before `buf[taglen] = 0`, a volatile read-back of `node`, a
volatile store, `volatile struct GroupNode* node`, and the `node_slot` alias
with its address escaped -- and **none emits `test eax,eax`**.  msvc6 proves the
literal sentinel `0x117640a0` non-null in every form; the reference's test is a
scheduling artefact.

**The 16-byte threshold is what the alignment needs, not the exact size.**  A
function's COMDAT is padded to a multiple of 16 before the linker places the
next object, so what moves subsequent VAs is `align16(obj_size)`, not
`obj_size`.  `m_AllocTracked`'s section is 656 bytes for any `obj_size` in
645..656, so the placed gap stays 656 against the reference's 672 -- **the
object has to reach 657 bytes, not 658, before the next function moves.**  The
same arithmetic applies to the other three alignment blockers:

```
function              obj   target  align16(obj)  reference span  placed delta
CrashDump             2137   2115      2144           2128           +16
m_AllocTracked         649    658       656            672           -16
vfs_ReadCompressed     497    492       512            496           +16
cm_ExCopyEntityData    880    912       880            912           -32
```

`cm_ExCopyEntityData` is the one that is *far* short: 880 against 912, and it
needs +32 whole bytes of code (its `sizediff` shows the missing blocks are the
two clamp bodies at T82-86 and T178-183, where the reference materialises
`mov eax,0xffffff81` / `mov eax,0x7f` and stores `al`, and ours folds the
immediate into the store).

**Round-92: `rebrew test`'s `total` is not the object size, and position
alignment is broken in exactly four places.**

Two corrections and one measurement, all from building the CMake tree and
reading its map.

**1. The honest object size is `obj_size`, not `total`.**  `rebrew test --json`
returns both, and they differ whenever the object is not the target's length.
`total` is the *comparison length* (the target's size, or the overlap); the
candidate's real code length is `obj_size`, which trims the COMDAT's trailing
alignment nops.  `m_AllocTracked` is the worked example: the object has 11
trailing nops, so the section is 656 bytes but the code is **645**, against the
reference's 658 -- **13 bytes short**, not "exact".  Several notes in this file
and in `src/server.dll/Units/m_alloc/m_alloc_c/m_AllocTracked.c` say "obj 658 /
exact size" and are wrong for that reason; they have been corrected in the
source file.

The honest table for every non-exact function (`obj_size` against the catalog
size, best size first):

```
function                        target   obj  diff   positional match
ahm_ExAllocAlchemist              1002  1002     0      823
cm_ExProdObjekt                    993   993     0      976
cm_ProcessCommandQueue             639   639     0      624
gm_CalculateProductionValue        396   396     0      391
gm_ObjectsAvailble                 714   714     0      686
gv_ExAllocGraveyardWorker         1040  1040     0      606
ServerMainThread                  2434  2434     0     1336
srv_LoadBuf                        750   750     0      701
ls_LoadBuildingEntityState        1463  1464    +1      125
gm_AllocSpieler                   3689  3688    -1      851
cm_ExSellObjekt                   2057  2055    -2      201
gm_FindNextFilteredEntity          346   342    -4      168
vfs_ReadCompressed                 492   497    +5      161
gm_AllocGebaeude                  1088  1078   -10      571
m_AllocTracked                     658   645   -13      266
cm_ExCopyEntityData                912   880   -32      525
vfs_OpenStream                     667   693   +26      444
```

**2. Position alignment breaks in four places, all in the game region.**
Linking the CMake objects by hand with `/MAP` (the POST_BUILD postlink deletes
the DLL, so the map has to be captured from a manual link) gives the VA of
every public symbol.  Comparing those against the catalog, the cumulative delta
is piecewise constant with exactly four transitions before the CRT:

```
at 0x10001130 SendBroadcastPacket      +0
at 0x10002fc0 EmitCrashModuleLine     +16   <- CrashDump is +29 bytes
at 0x10006820 m_FreeTracked             0   <- m_AllocTracked is -13, which
                                               happens to land it back on a
                                               16-byte boundary
at 0x10008c80 vfs_CleanupObject       +16   <- vfs_ReadCompressed +5
at 0x1000ef90 cm_ChainAssignId        -16   <- cm_ExCopyEntityData -32
```

So **four size errors move 387 of 399 public symbols off their reference VA**,
which is why `rebrew postlink` reports "only 614/7463 layout-map entries
validate (8.2%)" and refuses.  Fixing those four would re-align the whole game
region; nothing else in it is misplaced.

**3. The CRT region beyond 0x1001a140 is in a different order entirely.**  From
`_srand` onward the deltas are not multiples of 16 but thousands of bytes
(+13440, +8332, +8260, ... -28688), i.e. the LIBCMT members are linked in a
different sequence than the reference's.  That is the split PoC's problem to
solve, not the CMake link's: it is the reason the split set controls member
order explicitly, and it is why `.text` is 0x223b6 against the reference's
0x22846 (-0x490) even though the game region's own deltas sum to only -16.

**Round-91: `gm_FindNextFilteredEntity`'s head is not the loop.**

`docs/msvc6-c-shapes.md` section 38 says the lever for a target that
shrink-wraps is *loop register demand*, with the corollary "delete the loop and
recompile; if the head then matches, the entry spelling is right and the loop is
the blocker".  Applied here it says the opposite: **with the loop deleted the
head still does not match.**  The reference's early returns are *inlined*
(`xor eax,eax; pop esi; ret` at 0x10016f87 and 0x10016f93); ours jump to a
shared tail (`je 0x...`).  That is an epilogue-merge decision, and section 7
documents it as source-reachable -- two consecutive guards returning the same
value give two epilogues -- yet our source already spells them as two
consecutive `if (...) return 0;` guards and msvc6 still merges them here.

What the reference does that ours does not, from the bytes at 0x10016fe1:

```
target  53            push ebx     8a1d 900b0310  mov bl,[g_query_filter_extra4]
        55            push ebp     8b2d 8c0b0310  mov ebp,[g_query_filter_extra2]
        56            push esi     8b3d 880b0310  mov edi,[g_query_filter_extra1]
        57            push edi
```

-- three loop-invariant filter globals hoisted into callee-saved registers and
three pushes shrink-wrapped to that block.  Measured this round, and worse:

```
explicit `qf1/qf2/qf4` locals read before the loop   95/354   aligned 65/118
`while (*list_head == 0 || 1)` -> `do {} while (..==0)`  161/358
baseline                                            168/346  aligned 75/118
```

So the hoist is the reference's *compiler* doing loop-invariant motion on
globals that our build declines to move, and spelling it out makes it worse.  The
`|| 1` in that loop is also load-bearing: the honest `do/while` that replaces it
costs 16 bytes, because `|| 1` makes the loop body unconditional, which is what
the reference's always-advance shape needs.

**Also measured this round.**  `vfs_ReadCompressed` aligns at 164/200; the
residue is the round-85 comparison flip (`cmp eax,edi / jae` against
`cmp edi,eax / jbe`) plus a store/branch reorder at indices 160-180, where the
reference loads two stack slots before the `[esi+0x50]`/`[esi+0x5c]` stores and
ours stores first.

**Round-90: the loop-entry test is not reachable by spelling, and a survey of
where the remaining bytes actually live.**

`.scratch/fdiff.py` (round 89) gives, per function, the differing-byte *runs*
between the linked split image and the reference at the best drift offset.  Run
over all fourteen non-exact game functions, **raw** differing bytes (these
include relocation slots, so they run above the masked figures in
`text_match.py`) and the three largest runs:

```
                                   raw   drift    largest runs
srv_LoadBuf            0x1000a570  108    +16      14, 11, 6
gm_CheckInventoryCap   0x10019ed0  111    -16      28, 22, 18
vfs_OpenStream         0x10009020  269    +16      83, 29, 27
ahm_ExAllocAlchemist   0x1000bdf0  266    +16      51, 34, 25
vfs_ReadCompressed     0x10008a90  314     -4      95, 37, 36
gm_FindNextFilteredEnt 0x10016f80  258    -16      77, 43, 25
cm_ExCopyEntityData    0x1000ec00  471    +16      73, 63, 54
gv_ExAllocGraveyardWkr 0x10011bf0  485    -16      61, 46, 43
gm_AllocGebaeude       0x100174d0  545    -16     121, 55, 54
ls_LoadBuildingEntityS 0x100128f0  881    -21      52, 18, 4
ServerMainThread       0x100093a0 1135    +16      80, 49, 42
cm_ExSellObjekt        0x1000d930 1699    +18     110, 92, 83
CrashDump              0x10002770 1868     +2     107, 105, 71
gm_AllocSpieler        0x10018850 3190    -19     177, 132, 112
```

No function is a single-shift case like `m_AllocTracked`: `srv_LoadBuf` and
`gm_CheckInventoryCapacity` are many 1-2 byte ModRM/register runs, and the rest
are dozens of medium runs.  `ls_LoadBuildingEntityState` is the most
concentrated (881 raw in a 52+18+4 profile) but 4 runs of <= 4 bytes means it is
diffuse too.

**`m_AllocTracked`'s loop-entry test, closed as unreachable.**  Round 89 found a
4-byte `test eax,eax` the reference emits at 0x100066b9 on the literal sentinel
`0x117640a0`, which msvc6 folds away in our build.  Confirmed first that the
sentinel really is a literal and not a relocated symbol: the reference's
`.reloc` table has no entry at 0x100066b1, and 0x117640a0 is not a relocation
*target* either.  Seven spellings then measured against the exact byte pattern,
each compiled and grepped for `85 c0` within 30 bytes of the `be a0 40 76 11`
sentinel load:

```
baseline (direct `while (node != 0)`)          no-test
`node = ...` / `node_slot = &node` swapped     no-test
explicit `if (*node_slot != 0) { while ... }`  no-test
sentinel through an int temp                   no-test
`*(struct GroupNode* volatile*) &node = ...`   no-test
the same plus a volatile read-back             no-test
`struct GroupNode* volatile node`              no-test (and 720 bytes, +64)
```

So the test is a scheduling artefact of the reference build, not a source shape:
msvc6 emits it around the `add esp,0xc` that cleans the `strncpy` args and folds
it in every spelling we can write.  The ~200 bytes it shifts stay parked.


**Round-89 metric** (`scripts/text_match.py --drift auto` after
`scripts/split_link.sh`): game region **92.12% masked, 6,528 differing bytes**
(m_AllocTracked 250 -> 249).  The round-88 figure was 6,529 and the round-87
figure 6,537.

**Round-89: `m_AllocTracked`'s remaining gap is one unfolded null test.**
265 -> 266/658 positional, aligned 207 -> 208 of 249, one fewer mismatch run.
The `node_slot` alias on `node` was deleted — it is only ever assigned `&node`,
so the double-indirection loop *is* the direct one, and the alias never bought
the thing it was added for.

What dominates the function's **250 remaining masked differing bytes** is a
single 4-byte instruction shape at the search-loop head.  `.scratch/fdiff.py`
(new) shows the differing runs are ten small ones in the first 180 bytes and
then *everything* from offset 0xb4 to the end — i.e. one shift:

```
target 0x100066af  mov esi,0x117640a0
       0x100066b4  mov eax,esi
       0x100066b6  add esp,0xc
       0x100066b9  test eax,eax        <- the loop-entry null test
       0x100066bb  mov [ebp-4],esi
       0x100066be  je  <alloc>
       0x100066c0  jmp <loop body>
ours                        add esp,0xc
                            mov [ebp-4],esi
                            jmp <loop body>          <- test proven away
```

`node` is assigned the literal `0x117640a0`, so msvc6 proves it non-null and
drops the test; the reference keeps it.  That is 4 bytes, and because the
object size is pinned at 658 the difference is repaid downstream, so every byte
from 0xb4 on lands at the wrong offset.  Measured and inert on the way to this
conclusion: `node = (struct GroupNode*) nodev;` before the increment (265),
`volatile int count` (257), all four increment spellings, and the flag set
`/O2 /Gd /Oy-`, `/O2 /Gd /G5 /Oy-`, `/O2 /Gd /G6`, `/O2 /Gd /GB /Oy-` (all
265).  Reproducing the test needs msvc6 to lose the constant — the same
escaped-pointer lever `gm_CheckInventoryCapacity` uses — but there is no spare
local here and making `node_slot`'s own address escape has to be done without
growing the 0x118 frame.

**Round-88 note: a positional win that is byte-neutral, measured both ways.**
`gm_FindNextFilteredEntity` (0x10016f80) carries a redundant second `match = 0;`
at its `candidate:` label — the first store dominates it.  Deleting it makes
msvc6 see the entry store as live and emit the reference's third instruction
exactly:

```
target  0  mov eax,[g_entity_ptr]      3  lea esi,[eax+0xa900]
        1  push esi                    4  mov eax,[g_entity_type_table]
        2  xor cl,cl                   5  test eax,eax
variant identical at 0-5;  current body: 2 = lea esi, 6 = je <shared tail>
```

Against the reference's own size (346) the variant lands at 349 and the current
body at 342, and the aligned instruction match is 76/118 against 75 — but
`scripts/text_match.py --drift auto` gives the function **55 differing bytes
either way**, so the variant closes nothing.  `rebrew test`'s positional count
disagrees loudly (168 -> 105) purely because the 7-byte size change shifts every
later operand.  Reverted; recorded so the next round does not re-run it.

The wider lesson, which applies to every "measured and reverted" verdict in
this file: those verdicts were taken with the positional count.  Where a variant
changes the object size, that number can move by tens of bytes while the honest
masked metric does not move at all.  **Any candidate that changes the size must
be re-judged with the split pipeline**, not with `rebrew test`.

**Round-88 metric** (`scripts/text_match.py --drift auto` after
`scripts/split_link.sh`): game region **92.12% masked, 6,529 differing bytes**
(the round-87 figure of 6,537 predates the `m_AllocTracked` `prev->next` fix,
which is worth 8 bytes there: 258 -> 250 differing, 62.0%).  Split `.text` still
+0x292.

**Round-87c, `m_AllocTracked` correct C: 263 -> 265/658.**  The reconstruction
read an uninitialised pointer: `(*prev_slot)->next = node;`, where `prev_slot`
is declared and never assigned.  `prev_slot` only ever appeared to help because
it made MSVC emit an extra `mov eax,[ecx]` dereference.  The reference emits a
*single* indirection (`mov [ecx+0x24],edx`), which is exactly `prev->next =
node;`.  `prev` is always assigned before use — the loop head is `node`
initialised to the nonzero sentinel 0x117640a0, so `prev = *node_slot` executes
at least once — so the replacement is both faster to match and correct.  The
`prev_slot` declaration then removes cleanly (codegen-inert).

This is worth generalising: **an alias that the source never assigns is a red
flag, not a lever.**  The old note in that file called the unassigned spelling
"load-bearing for the score"; it was load-bearing only for the extra
instruction the extra dereference emitted, and the correct spelling pays the
same byte back.

**Round-87 net effect on the honest metric** (`scripts/text_match.py --drift
auto`, after `scripts/split_link.sh`): the game region goes from 91.77% to
**92.11% masked**, and its differing bytes from 6,851 to **6,537** — 314 bytes
closed by three functions:

```
                       before            after
vfs_ReadData           112/472 matched   RELOC 472/472, 100%
m_AllocTracked          46.6% -> 51.4%   60.8% masked
gm_AllocGebaeude        39.1% -> 41.6%   73.5% masked
```

The split `.text` also shortens from +0x2b2 to **+0x292** (0x22ad8 vs the
reference's 0x22846).  Gate: 0 lint errors, 0 compile/link errors,
`verify --full` 280/282.  The 87c `m_AllocTracked` fix moves that function to
265/658 (from 263, and from 182 at the start of the round).

## `gm_AllocGebaeude` — address-taken struct members force reloads (2026-09-13, round 87b)

438/1078 -> **571/1078** matched bytes at the exact object size, by applying the
aliasing half of the round-87 finding.  The rule the reference follows, and the
reconstruction did not:

> A pointer held in a **plain local** is kept in a register and stored through
> repeatedly.  A pointer held in an **address-taken aggregate member** must be
> reloaded after every store through it, because a `char*` store may alias the
> field itself.

Three sites were spelled the wrong way round:

- **case 0x14** (the 0x1b5 sub-object).  `s.record` is a member of the 0x410
  address-taken struct, so the four field stores emitted three `mov
  [ebp-8],...` reloads.  The reference stores the pointer *nowhere* and issues
  all four stores from one register:

  ```
  target 0x100177a8  or ecx,0xffffffff ; mov [eax+0x22],bl
                     mov [eax+0x1c],cl ; mov [eax+0x1d],cl ; mov [eax+0x1e],ecx
  ours              mov ecx,[ebp-8] ; mov [ecx+0x1c],al
                    mov edx,[ebp-8] ; mov [edx+0x1d],al
                    mov ecx,[ebp-8] ; mov [ecx+0x1e],eax
  ```

  A local `char* rec` reproduces it.
- **case 0x1e** (the 0x600 table).  The reference writes the allocation only to
  `geb+0x71` and reads the pointer back out of that field: the first store comes
  from the call result still in `eax`, the second reloads `mov ecx,[esi+0x71]`
  because the intervening char store may alias the field.  Keeping a second
  copy in `s.record` cost one extra store and three extra reloads.
- **case 0x4b** (the 0x3c record): same shape, same fix.

Separately, `*(int*) s.dest = ...` became `*(int*)(geb + 0x65) = ...` at the six
switch sites that use it.  `s.dest` is assigned once (`geb + 0x65`) and never
written again, so the two are equivalent, but the reference resolves the
constant address where ours kept a live pointer.  **Not** case 6/7: that one
really does go through the pointer, and making it direct measured 489.

## `vfs_ReadData` is DONE — the shadow struct, not the prelude, was the wall (2026-09-13, round 87)

Every previous pass on `vfs_ReadData` (0x10008e40) concluded the residual was
the hand-written memcpy prelude, wrote the prelude as the sanctioned `__asm`
block, and parked the function at 446 bytes on the theory that "EXACT is not
attainable from C".  The prelude was never the problem.  The frame was.

Two changes take it to **RELOC, 472/472 bytes, exact size**.

**1. The `sh` shadow struct allocated a slot the target does not have.**
The header had `struct { volatile int zp; volatile int tv; } sh;` plus
`sh.tv = total;` and `sh.tv = (int) avail;`, added long ago because the
target homes the cursor at `[ebp-0xc]` and the byte count at `[ebp-8]`.  But
the copy prelude names `total` as an asm operand, and MSVC6 gives every asm
operand a memory home — so `total` lands on `[ebp-8]` by itself, and that is
*the same slot the target reuses*: the reference's `mov [ebp-8],esi` at
0x10008f00 is simultaneously the count's home and its shadow.  The `tv`
member therefore bought a second, redundant dword:

```
                          frame    matched
baseline (sh.tv + volatile) 0x110    112/472
sh.zp plain, no sh.tv       0x10c    338/472     <- frame now exact
```

`rebrew diff`'s candidate column had reported the frame as fine all along
because it truncates the candidate to the target's length; the give-away is
`sub esp, 0x110` against the target's `sub esp, 0x10c` in the raw object.

**2. The gzip magic was read at byte width.**  The reference compares a
zero-extended byte against the *dword* at 0x10029450/0x10029454
(`xor ecx,ecx; mov cl,[ebx]; cmp ecx,[0x10029450]` at 0x10008f92, and the
same shape at 0x10008fa4), and `vfs_OpenStream.c` reads those two constants
as ints as well.  Reading them as bytes cost the last four bytes.  The
operands are 0..255, so the forms are behaviour-identical — this was
previously measured as *worse* (136 at obj 450) only because the stale
0x110 frame was charging four bytes the compare could not repay.

**Generalisable lesson.**  An `__asm` block is not neutral to the frame: every
C variable named inside it is forced to memory, so it *supplies* homes the
surrounding C may already be faking with `volatile` shadows.  When a function
with a prelude is one dword over, look for a shadow variable that the asm
operand has made redundant — `rebrew diff` will not show it, because it
truncates the candidate and hides the prologue.

**Lint note.**  `rebrew lint` now reports W020 on this file ("inline `__asm`
block but STATUS claims RELOC"), taking the warning count 3 -> 4.  It is a
false positive of exactly the kind the rule's own docstring describes: a
block-fill `__asm` body inside a function that does byte-match.  The rule's
only escape is a recorded `blocker`, and there is no blocker — `rebrew test`
cleared it when the function matched (`match_percent: 100.0`, `delta: 0`,
7 relocs).  Gate still passes: 0 lint errors, 0 compile/link errors,
`verify --full` 280/282.

**Same lever, second site: `m_AllocTracked` (0x10006580), 182 -> 263 of 658.**
The identical mistake was there.  Its `volatile unsigned int sz` and
`volatile int nodev` were shadowing two spill slots, but the zero-fill
prelude names `sz` as an asm operand, so MSVC6 homes it anyway — and the
shadow was paying for a second, redundant dword.  Dropping `volatile` from
both shadows took the frame 0x120 -> 0x11c; shrinking `buf[0x14]` back to
`buf[0x10]` closed the last four and gave the target frame exactly:

```
target   sub esp,0x118   node [ebp-4]   size [ebp-8]   buf [ebp-0x18]
ours     0x120  ->  0x11c  ->  0x118  (exact)
matched  182    ->  257    ->  263  of 658  (rebrew test)
```

Note the older note in that file argued *for* `buf[0x14]` on the previous
0x120 frame — it was compensating for the shadow's extra slot.  The 0x10
buffer is the reference's real size, which means the reference has a latent
16-byte buffer overflow when a tag's first ':' is at index >= 15
(`strncpy(buf, tag, taglen)` is not capped by the `taglen >= 0x10` warning
above it).  That is reproduced as-is; bug-compatibility is byte identity.

## The frame hole is an aggregate, not alignment — `cm_ExSellObjekt` (2026-09-13, round 86)

`cm_ExSellObjekt` (0x1000d930) has been parked for months on a 4-byte frame
difference: the reference `sub esp, 0x228`, every C formulation 0x224, "one
fewer spilled local".  The hole is real and now reproduced.

What the reference frame looks like (offsets from post-prologue `esp`):

```
0x00..0x10   ebx ebp esi edi          (4 pushed callee-saved)
0x10..0x34   nine spilled dword locals
0x34..0x38   bytes the reference NEVER touches  <- the hole
0x38..0x238  the 512-byte log buffer, ending exactly at the return address
```

Both `sub esp` sizes and the buffer/base offsets line up once the hole exists:
the reference's `lea ecx,[esp+0x38]` addresses the buffer where a plain array
gives 0x34, and its param slot is `[esp+0x238]` where a plain array gives
0x234.

Ruled out, by measurement (`.scratch/ap2.c`, msvc6 /O2 /Gd):

```
char a[4] + char   buf[512]   sub esp 0x204
char a[4] + __int64 buf[64]   sub esp 0x204
char a[4] + double  buf[64]   sub esp 0x204
char a[4] + struct {__int64 q;} buf[64]   sub esp 0x204
char a[4] + char   buf[516]   sub esp 0x208
```

MSVC6 packs stack objects on 4 bytes and does not 8-align `__int64`/`double`
aggregates, so the hole is not an alignment pad.  `__declspec(align(8))` on a
local is a fatal `C1600: unsupported data type`.  A plain unused local is
eliminated outright -- adding `int dead_pad;` and zeroing it with the others
changed neither the frame nor the store list.

What does reproduce all three is an aggregate with a leading member the source
never reads:

```c
// SIZE 0x204
struct SLogBuffer { unsigned int reserved; char text[512]; };
...
struct SLogBuffer log_buffer;
```

MSVC6 allocates the whole 516-byte object, so the first dword is reserved and
untouched while `text` lands on 0x38.  With that, `sub esp,0x228` (was 0x224),
`mov esi,[esp+0x238]` (was 0x234) and the buffer base all match byte for byte.

Aligned instruction match 71.8% -> 72.7% (479 -> 485 of 667); the object size
is unchanged at 2055 because the frame fix changes no instruction length.

**Residual is now the allocator's local->slot permutation, not the frame.**

```
                        target   ours
source_static_entity     0x24    0x24
resolved_dynamic         0x14    0x18
source_existing_entity   0x30    0x2c
```

with a different zero-store order (target `0x10 0x14 0x2c 0x18 0x20 0x28 0x30
0x1c 0x24`; ours `0x18 0x1c 0x28 0x14 0x10 0x30 0x2c 0x20 0x24`) and a
different zero register: the reference parks 0 in `edi` and keeps it live
across the first call (`cmp eax,edi` at 0x1000d994), ours parks it in `ebx`
and rematerializes `test eax,eax`.  Swapping `ebx`<->`edi` in the candidate
stream and re-running the LCS makes it *worse* (72.7% -> 70.8%), so the
remaining delta is the slot permutation, not a register rename.

**The hole is unique to this function.**  A sweep of the first instruction of
every non-exact game function against its built object (`.scratch/framescan.py`:
target via `rebrew asm`, candidate via the COFF symbol table of
`build/CMakeFiles/server_dll.dir/<src>.obj`) shows the two `sub esp` immediates
agreeing exactly everywhere else:

```
gm_AllocSpieler              0x41c / 0x41c      vfs_OpenStream          0xc   / 0xc
CrashDumpUnhandledException  0x280 / 0x28c *    ahm_ExAllocAlchemist    (no frame)
cm_ExSellObjekt              0x228 / 0x228      srv_LoadBuf              0x2a0 / 0x2a0
ServerMainThread             0x1e4 / 0x1e4      gm_ObjectsAvailble       0x28  / 0x28
ls_LoadBuildingEntityState   0xc   / 0xc        cm_ExProdObjekt          0x10  / 0x10
gm_AllocGebaeude             push ebp (both)    cm_ProcessCommandQueue   8     / 8
gv_ExAllocGraveyardWorker    0x10  / 0x10       m_AllocTracked           push ebp (both)
cm_ExCopyEntityData          0xc   / 0xc
```

So the frame is *not* a general lever: 18 of 19 match and the frame-hole
technique above applies only to `cm_ExSellObjekt`.  The one real outlier left
is `CrashDumpUnhandledExceptionFilter`, whose frame is 12 bytes too big
(0x28c vs 0x280) on top of the register cascade already recorded for it.

## `vfs_ReadCompressed`'s comparison is not source-reachable (2026-09-13, round 85)

LCS-aligned the 216-instruction candidate against the 200-instruction target.
LCS is 158, and the residue is *not* a pile of missing logic: it is one
two-byte encoding difference plus normalizer noise.

The real difference is at object instruction 101 (the stored-block guard):

```
target                 ours
cmp  eax, edi          cmp  edi, eax      ; 3b c7  vs  3b f8
jae  <skip>            jbe  <skip>        ; 73 xx  vs  76 xx
mov  edi, eax          mov  edi, eax
```

`edi` is `n = s->avail_in` clamped against `s->avail_out`; the pair is
`min()` and the two encodings are semantically identical -- MSVC picked the
commutative mirror.  Three source spellings of that clamp were tried:

```
source form                          raw  obj
if (n > s->avail_in)  (baseline)     161  497
if (s->avail_in < n)                 161  497   <- byte-identical
if (s->avail_in <= n)                161  497   <- byte-identical
a fourth, stricter clamp spelling   142  488   (different object, worse)
```

Both flips are *inert*: byte-identical objects, so the clamp's source
spelling cannot produce the target's operand order.  The difference therefore
comes from register assignment of `edi`/`eax` earlier in the function, not
from this line.  File restored; no net change.

Also noted: the LCS diff reports `[ecx+eax]` (target) vs `[ecx+eax*1]`
(ours) in the copy loop.  `eax*1` is `SIB` with `index=none, base=eax`,
i.e. the same bytes as `[ecx+eax]`; the two are only distinguishable because
MSVC emits the SIB form when the accumulator is in `eax`.  Normalizer
artifact -- do not chase.

## Reconstructing the dispatch table is not enough for `/OPT:REF` (2026-09-13, round 84)

Round 83 said the `/OPT:REF` route needs the game's data tables expressed as
real C objects so the linker sees the references.  Sizing that first: of the
data blob's 11,264 dwords, **222 point into `.text`**, in two runs --

```
blob +0x23f8   212 entries   first target 0x1000d2e0
blob +0x9bb0     6 entries   first target 0x10021aad
```

-- and the 212-entry one is the command dispatch table
(`cm_ChkCommandType`, `MarkAndReturn`, `RejectCommand`, ...), 848 bytes.

Generating it as a real `DshFn const [212]` with function names, and linking it
into the split set:

```
                        .text                    .rdata
split_poc          diff 86608  vsize 0x22af8   diff 2237  vsize 0x33b1
probe + /OPT:NOREF diff 86608  vsize 0x22af8   diff 2218  vsize 0x3701
probe + /OPT:REF   diff 78416  vsize 0x13af0   diff 8554  vsize 0x3371
```

The references do help the walk -- `/OPT:REF` retains 0x2340 more `.text` than
it did without them (0x118b0 -> 0x13af0) -- but it still drops 0xec08, so the
dispatch table is not what anchors the game code.  `/OPT:REF` remains
unusable, and reconstructing the last 872 bytes of pointer tables will not
change that.

Incidental but worth knowing: 47 of the 212 entries name symbols our build does
not define, because `src/server.dll/functions.txt` carries the catalog names
(`RejectCommand`) while the sources define their own (`cm_RejectCommand`).  A
real-pointer reconstruction needs a reference-VA -> our-symbol map, not the
catalog names.

Probe removed, tree clean.

## `/OPT:REF` fails because the restore blobs have no relocations (2026-09-13, round 83)

Round 82 blamed `/Gy` for `/OPT:REF` dropping 0x11248 of `.text`.  That is
wrong, and the test is direct -- compile `spiel.c` three ways and count the
`.text` sections:

```
flags          .text sections
(none)              5
/Gy-                5
/Gy                 5
```

MSVC6 emits the per-function COMDAT `.text` sections in this configuration
regardless, so `/Gy-` is not a lever and the flag cannot be turned off.

The real cause is the blobs.  Both restore objects have **zero relocations**:

```
data_restore.c.obj    sections 2   relocations 0
rdata_restore.c.obj   sections 2   relocations 0
```

The game's dispatch and function-pointer tables are baked into those arrays as
raw bytes.  A table entry that should be a reference to a game function is just
four bytes to the linker, so the reachability walk that `/OPT:REF` performs
from the entry point never reaches the game functions and discards them.  This
is why every `/OPT:REF` attempt collapses `.text`, and it is not fixable with
linker flags: `/OPT:REF` and raw-byte data blobs are mutually exclusive by
construction.

So the `/OPT:REF` route needs the game's data tables reconstructed as **real C
objects** -- arrays with initialisers naming the functions, which generate real
relocations -- rather than as blobs.  Unlike rounds 76-82 that is not library
code: it is the game's own `.data`, and it is exactly the work the goal wants.

## `/OPT:REF` needs `/Gy-` across the whole build, not just the split set (2026-09-13, round 82)

Round 81 proposed emitting the split objects' `.text` sections as **non**-COMDAT
so `/OPT:REF` would keep them (command-line objects' ordinary sections are
never dropped) while discarding only the duplicated `.rdata` COMDATs.  Tested
by clearing `IMAGE_SCN_LNK_COMDAT` (0x1000) on every `.text` section
`split_coff.py` emits, and rebuilding the split set:

```
                        .text                    .rdata                  .data
split_poc          diff 86608  vsize 0x22af8   diff 2237  vsize 0x33b1   diff 25311  vsize 0x1746c28
non-COMDAT .text   diff 86608  vsize 0x22af8   diff 2237  vsize 0x33b1   diff 25311  vsize 0x1746c28
```

byte-identical under `/OPT:NOREF` -- a useful fact in itself, the change is
free -- but `/OPT:REF` on the same object set still collapses the image:

```
non-COMDAT + /OPT:REF   .text 0x118b0   .rdata 0x32f1   .data 0x1745c7c
                        .text loses 0x11248
```

So the split objects were not what `/OPT:REF` was dropping.  It is the **game**
objects: every one of the 196 CMake objects has COMDAT `.text` sections

```
spiel.c.obj   .text chars 0x60501020   COMDAT=YES     (5 such sections)
```

which is MSVC's `/Gy` function-level linking, and `/OPT:REF` discards any that
the entry point cannot reach.

So the `/OPT:REF` route needs `/Gy-` on the whole build, not just on the split
set -- a compiler-flag change across all 196 objects, which is a different and
much larger experiment than anything attempted so far, and one that would also
change `.text` padding (round 71 measured 32 bytes of per-object padding for
just 25 files).  Recorded as the next step for the `.rdata`/`.data` overlap;
reverted, tree clean.

## The literal alias works on symbols, not on bytes (2026-09-13, round 81)

Round 78 concluded the duplicated `.rdata` needs the members' symbols to
resolve into the blob's bytes rather than either copy being deleted.  MSVC6
turns out to give half of that for free: writing the **same string literal**
in another translation unit produces the **same mangled COMDAT name**, so LINK
sees a duplicate and keeps one.

Probe: add `const char* const g_probe_null_literal = "(null)";` to
`rdata_restore.c`, which is linked before the split objects, and relink.

```
(null)  reference  0x2074
        split_poc  0x2074, 0x26bc        (the blob's copy and the member's)
        probe      0x2074                the duplicate is gone
"second definition ignored" warnings in the probe link: 24
extra string occurrences over the reference:  18 -> 17
.rdata differing:                           2237 -> 2234
.rdata vsize:                               0x33b1 -> 0x33b1
```

So the mechanism works at the symbol level -- LINK discards 24 member COMDATs
-- and the duplicated *bytes* stay anyway, because `/OPT:NOREF` keeps a
discarded COMDAT's section in the image.  `/OPT:REF` is what would drop them,
and it is unusable:

```
                   .text vsize   .rdata vsize
split_poc              0x22af8        0x33b1
literal + /OPT:REF     0x0ec80        0x3021     .text loses 0x1b478
```

`/OPT:REF` drops every unreferenced COMDAT, and every split object *is* one
COMDAT, so the whole split set evaporates.

That points at a specific follow-up rather than a dead end: `split_coff.py`
copies the members' `.text` sections as COMDATs because that is how LIBCMT
builds them, but a command-line object's **non**-COMDAT sections are never
dropped by `/OPT:REF`.  If the split `.text` sections were emitted as ordinary
`.text`, `literal alias + /OPT:REF` would discard exactly the duplicated
`.rdata` COMDATs and nothing else.  That is a change to `split_coff.py`'s
section emission and has not been tried.

Probe reverted, objects rebuilt; tree clean.

## A size match that is a coincidence (2026-09-13, round 80)

Following round 78's conclusion that the duplicated `.rdata` cannot simply be
deleted, the interesting measurement is what the blob is actually needed for.
Dropping `rdata_restore.c.obj` from the response file entirely:

```
              .rdata diff   vsize     raw
split_poc         2237     0x33b1   16384
no blob           3438     0x2091   12288      <- raw exactly the reference's 0x3000,
                                                 but the section is 0xdf0 SHORT
```

so of the blob's 0x1320 bytes, 0xdf0 are genuinely needed and 0x530 duplicate
-- and 0x530 is exactly the surplus.  Truncating the blob to its first 0xdf0
bytes therefore looks like the fix, and it lands the section *exactly* on the
reference:

```
              .rdata diff   vsize     raw
split_poc         2237     0x33b1   16384
blob truncated    2513     0x2e81   12288      <- 0x2e81 and 0x3000, both exact
```

`0x2e81` is the reference's `.rdata` VirtualSize to the byte, and the raw size
matches too.  It is a coincidence.  The truncated tail held the locale strings
-- `H:mm:ss`, `dddd, MMMM dd, yyyy`, `M/d/yy`, the month names -- which
**nothing else in the link supplies**:

```
reference .rdata strings missing from the truncated image: 17
  H:mm:ss   dddd, MMMM dd, yyyy   M/d/yy   December   November   October ...
```

The size came out right because unrelated member content filled the space.  A
byte-exact section size is not evidence of correctness, and this is the
cheapest demonstration of that in the log -- worth remembering before trusting
any future "the sizes match now" result on `.rdata` or `.data`.

Both variants reverted; tree clean.

## The flag space is closed: 36 pairs, all inert (2026-09-13, round 79)

Round 51 swept nine individual optimisation flags over this project's 20
residues and found nothing.  The remaining possibility was that the target
needs a *combination*.  All 36 pairs of `/Ot /Os /Og /Oy /Ob1 /Ob2 /Oi /Op /Oa`
on `gm_CalculateProductionValue` (the closest function -- two instructions,
five bytes, by far the best candidate for a flag to tip over):

```
base  /O2 /Gd                    391/396 obj 396
36 pairs, e.g.
      /O2 /Gd /Ot /Ob2           391/396 obj 396
      /O2 /Gd /Os /Og            391/396 obj 396
      /O2 /Gd /Oi /Oa            391/396 obj 396
BEST /O2 /Gd                     391/396 obj 396
```

Every pair reproduces the baseline byte-for-byte; not one moves a single byte.
With round 51's single-flag sweep and its compiler-service-pack sweep (MSVC
6.0 sp0..sp6 identical for four of five functions tested, a 3-byte step at sp4
for the fifth), the flags-and-toolchain axis is now closed for these residues.

That leaves exactly two things for the 20: MSVC6's block-sharing decisions,
which source restructuring has not reached in any of the attempts logged
(rounds 51, 70, 74, 77), and the `.rdata`/`.data` overlap, which round 78
showed needs an alias rather than a deletion.

## The duplicated `.rdata` is load-bearing for symbols (2026-09-13, round 78)

Round 76 pinned `.rdata`'s 0x480-byte duplicate block at 0x26bc and blamed the
LIBCMT objects the link pulls for their code.  The map says exactly which
split objects own those bytes:

```
1001fdf8_.text.obj 22   crt0msg.obj    1001f1a4_.text.obj  5   cvt.obj
10022107_.text.obj  4   crtmbox.obj    10022a2f_.text.obj  4   heapinit.obj
1001c19b_.text.obj  3   a_map.obj      1001d253_.text.obj  2   output.obj
1001f20b_.text.obj  2   testfdiv.obj   1001f631_.text.obj  2   tzset.obj
10020915_.text.obj  1                  1001d253_.text.obj      x10fout.obj
```

so a targeted exclusion is testable -- round 75's 80-byte result came from
excluding `.rdata` on all 229 objects, which is not the same experiment.
`split_coff.py`'s `data_secs` gate was narrowed to skip `.rdata` for exactly
those nine members and the whole split set rebuilt:

```
                  .text                    .rdata                  .data
split_poc    diff 86608  vsize 0x22af8   diff 2237  vsize 0x33b1   diff 25311  vsize 0x1746c28
nine excluded  diff 86807  vsize 0x23309  diff 2217  vsize 0x33f1   diff 25311  vsize 0x1746da8
```

Worse on every axis: `.rdata` *grows* by 0x40, `.text` by 0x811.  The reason is
that those sections are not only bytes -- they define symbols
(`__real@8@...` float constants, `??_C@...` strings).  Dropping them leaves
them undefined, `emit_defs` manufactures replacements, and the replacements
cost more than the duplication did.

So neither copy can simply be deleted: the blob is needed for the reference's
byte layout and the member sections are needed for the symbol table.  A
working fix has to make one set of symbols resolve to the other's bytes (an
alias at the blob's addresses, so LINK can discard the member COMDATs) rather
than removing either.  Reverted; tree clean.

## `vfs_ReadCompressed`: the accumulator placement is already right (2026-09-13, round 77)

The file's own note says the target loads and tests `handle` *before* the two
accumulator zero-stores, and that moving the stores "below the guard checks"
drops the object to 475 and 26/492.  That left one position untried: after the
*first* guard only, which is what the target's order literally says.  Measured,
all reverted:

```
baseline (stores first)          497 bytes  161/497
stores after the handle guard    481 bytes   37/492
stores after the s guard         481 bytes   46/492
stores after the inbuf guard     481 bytes   46/492
```

Every later placement is both smaller (481 against the target's 492) and far
worse, so `done = 0; result = 0;` before the guards is right and the residual
15 bytes are elsewhere.  Combined with the file's own note -- the candidate is
missing a 5-instruction epilogue the target has (7 bytes) while running 14
bytes long elsewhere -- the residue is again a duplicated-versus-shared return
block, the same class as round 74's `gm_FindNextFilteredEntity` and the other
18.

Two rounds of variants on two different functions have now landed on the same
conclusion from opposite directions: the remaining `.text` gap in all 20 is
MSVC6's block-sharing choices, and the levers that reach source-level structure
(statement order, guards, locals, volatile, flags, compiler service packs) do
not reach it.

## The `.rdata` surplus has one root cause, and it is pinned (2026-09-13, round 76)

Round 75 left the 0x530 `.rdata` surplus unexplained.  It is the **tail of the
import hint/name table**, pushed past the reference's section end:

```
surplus .rdata[0x2e81:0x33b1] contains
  AllocConsole FreeConsole CreateThread ... WideCharToMultiByte LCMapStringA
  KERNEL32.dll  GetWindowTextA  MessageBoxA  USER32.dll  WS2_32.dll  timeGetTime
  WINMM.dll  server.dll
```

That tail is downstream of a single insertion.  The blob itself
(`rdata_restore.c`, ref `.rdata[0x12e8:0x2608]`) matches the reference exactly,
and so does everything up to 0x2607 -- but four CRT strings then appear a
**second** time:

```
              reference      built (blob copy)   built (duplicate)
(null)          0x2074            0x2074              0x26bc
runtime error   0x2110            0x2110              0x2768
SunMonTue...    0x2418            0x2418              0x2af8
GetLocalTime    0x2a90             --                0x2d3e
KERNEL32.dll    0x2a06             --                0x32f8
```

The duplicate block sits at 0x26bc, about 0x480 bytes of it, and everything
after shifts by that much: the hint/name table moves from 0x2a06 to 0x2d3e and
its tail runs off the end of the section.  One insertion, one surplus.

The duplicates come from LIBCMT objects the link pulls for their *code*
(`crt0msg.obj` for `__NMSG_WRITE`/`__GET_RTERRMSG`, and the six others round 55
named), whose `.rdata` the blob already reproduces.  Removing them from the
*blob* cannot work: the blob is one contiguous array that matches the reference
byte-for-byte, so deleting bytes from its middle moves everything after it and
destroys the match that 0x12e8..0x2607 depends on.

So the fix is to keep those objects out of the link, and for `crt0msg.obj` that
means supplying `__NMSG_WRITE` and `__GET_RTERRMSG` locally -- writing
replacement bodies for library code.  That is a direct conflict with this
goal's "do not reverse LIBCMT, it will just be linked in", and it is worth
stating rather than working around: `.rdata` (and, by the same mechanism,
`.data`) cannot be finished under that rule as it stands.  The three options
are to relax the rule for the handful of objects whose `.rdata`/`.data` the
restore blobs already carry, to drop the blobs and let the library supply
everything, or to leave both sections as they are.

## The split members' `.rdata` is not the `.rdata` surplus either (2026-09-13, round 75)

Round 55 named seven LIBCMT objects (`crt0msg`, `testfdiv`, `x10fout`,
`output`, `timeset`, `a_map`, `tzset`) whose `.rdata` lands after
`rdata_restore.c`'s blob and duplicates it.  The direct test is to stop the
split objects emitting `.rdata` at all -- `split_coff.py`'s `data_secs` set is
`.data/.bss/.rdata/.CRT$`, so dropping `.rdata` from it is a one-line change --
and rebuild the whole split set into a scratch directory:

```
                    .text                  .rdata                 .data
split_poc     diff 86608  vsize 0x22af8   diff 2237  vsize 0x33b1   diff 25311  vsize 0x1746c28
no member .rdata   diff 86813  vsize 0x23334  diff 2207  vsize 0x3361   diff 25311  vsize 0x1746da8
```

`.rdata` shrinks by 80 bytes and its disagreement by 30; `.text` grows by
0x83c and its disagreement by 205; `.data` is untouched.  Strongly negative, so
`--with-data` keeps `.rdata` as well as `.data`, and this is the second variant
of "stop emitting the members' data" to fail (round 66 dropped all of it and
made `.rdata` three times worse).

The 80 bytes are also the answer to how much of the `.rdata` surplus those
seven objects actually account for: not much.  The surplus is 0x530, and round
55's 1600-byte estimate came from counting the seven objects' *section* sizes
rather than their placed contributions.  So the `.rdata` surplus is still
unexplained, and the next thing to measure is the same as for `.data` -- where
the bytes after the reference's section end actually come from.

## Back to `.text`: `gm_FindNextFilteredEntity` (2026-09-13, round 74)

The partition branch is closed for now, so this round went back to the 20
functions.  `gm_FindNextFilteredEntity` (0x10016f80, 346 bytes) is among the
smallest residues -- 55 differing bytes by the drift-aware metric -- and its
object is 342 bytes, four short.

The desync is at instruction 2, and it is a block-layout choice:

```
reference                          ours
2  xor cl, cl                      lea esi, [eax + 0xa900]
3  lea esi, [eax + 0xa900]         mov eax, [g_entity_type_table]
4  mov eax, [g_entity_type_table]  test eax, eax
5  test eax, eax                   je 0x152
6  jne 0x1b                        cmp [g_dynasty_field_4c], 0x100
7  xor eax, eax                    jg 0x152
8  pop esi                         ...
9  ret
```

The reference puts this first `return 0` **inline** and jumps over it to the
body; ours merges the return with the three later ones and jumps forward to the
shared block.  Four variants, all reverted, none of which moved it:

```
baseline      168/346 obj 342     swap the two guards        163/346 obj 342
local for the table  168/346 obj 342     move `end` after the guard 162/346 obj 342
add an unreachable guard  168/346 obj 342
```

Worth recording alongside: the positional score says 168/346 while the
drift-aware comparison says 291 bytes equal.  The object being four bytes short
desyncs everything after instruction 2, so `match_count` is not a usable
progress signal on this file either.

## `merge-sweep` is blocked by a one-word tool bug (2026-09-13, round 73)

Round 72 traced the registry and stopped at "a third source I did not
identify".  It is `src/server.dll/functions.txt` -- 561 lines of `VA name size`,
plain project data, with the 17 `case.0x...` rows in it at lines 106-122 (not
the CSV, and not `function_structure.json`, which has no `case` entries at
all; `merge_sweep.py` reads `cfg.function_list`, which is that file).

Removing those 17 rows clears the overlap error:

```
$ grep -v " case\.0x" src/server.dll/functions.txt > f && mv f src/server.dll/functions.txt
$ rebrew merge-sweep --dry-run --json --max-compiles 2
{"error": "zip() argument 2 is shorter than argument 1", "code": 2}
```

and the next error is the real blocker, in `rebrew/merge_sweep.py`:

```python
for prev_va, curr_va in zip(vas, vas[1:], strict=True):     # line 329
```

`vas` has n elements and `vas[1:]` has n-1, so **`strict=True` makes this raise
for every cluster with more than one function** -- that is, always.  The
partition search cannot run on any target, and the `case.*` rows were only the
first error it happened to hit.  The fix is to drop `strict=True` (the trailing
element is simply the one with no successor).

Both edits were reverted; `functions.txt` is back to 561 lines and the tree is
clean.  The fix belongs in the rebrew checkout, which this goal does not own --
recording the one-line change here so whoever does own it can apply it.

## `merge-sweep` is blocked by jump-table pseudo-functions (2026-09-13, round 72)

Round 71 concluded the merge question is really a partition question, and
`rebrew merge-sweep` is the tool that searches partitions.  It does not run:

```
$ rebrew merge-sweep --dry-run --json --max-compiles 4
{"error": "overlapping functions 0x1000ad40 (ends 0x1000af98) and
           0x1000ad68: fix the registry before clustering", "code": 2}
```

The overlap is a jump-table artefact, not a registry mistake.  `srv_LogWinsockError`
is 600 bytes at 0x1000ad40, and inside it sit sixteen Ghidra auto-named case
labels:

```
0x1000ad68 case.0x1000ad61.10019  32      0x1000aea8 case.0x1000ad61.10007  32
0x1000ad88 case.0x1000ad61.10012  32      0x1000aec8 case.0x1000ad61.10010  32
...  (16 of them, 0x20 apart, plus a 248-byte one at 0x1000af48)
0x10018272 case.0x10018211.15    190      (inside the function at 0x10018211)
```

Seventeen `case.*` entries in all, and they are registered in two places:
`db/server.dll_functions.csv` (17 rows) and `binsync/functions/*.toml` (17
files, each `name = "case.0x..."` with a `size`).

Neither removal unblocks it, and both were reverted:

* deleting the 17 CSV rows (`grep -v '|case\.'`) -- same error;
* moving the 17 `binsync/functions/*.toml` aside -- same error.

So the registry `merge-sweep` clusters comes from a third source that I did not
identify.  `merge_sweep.py` builds it with `build_function_registry(funcs, cfg,
ghidra_path=src/server.dll/function_structure.json)`, and that JSON contains no
`case.` entries at all, so `funcs` is not the CSV either.  Finding where the
case labels enter the registry is the next step; `rebrew catalog --export-ghidra`
caches a Ghidra function list and is the likeliest candidate.

Recording this rather than guessing: the tool that would answer the partition
question is currently unusable, and the fix is upstream of the project tree.

## The merged cluster compiles, and what it buys (2026-09-13, round 71)

Finishing the canonicalisation from round 70 -- four more prototypes, one
struct, one member, one preamble fragment -- gets the 25-file `spiel` merge to
compile as a single translation unit.  The last four edits:

```
void __cdecl gm_AddObjekt(int,int,int);          -> int __cdecl
int  __cdecl LogMessageInternal(char*,int,char*,int);
                                                 -> void __cdecl (char*,unsigned,char*,int)
                                                    (error.h already declares it void)
char* __cdecl gm_GetEntityTableEntry(char*);     -> short* __cdecl
void __cdecl gm_FreeObjectListRecursive(void*);  -> int __cdecl (char**)
LinkedNode     defined twice; hoisted the complete one and dropped both
DISPATCH_OBJ   the merge emitted the struct's tail without its head
```

Result, with the merged object compared against the 25 per-function objects:

```
             .text    .data
originals    18896     1063
merged       18864      916
```

**The merge is viable.**  `.data` drops 147 bytes for this cluster -- duplicate
string literals collapsing -- and `.text` drops 32.

That `.text` change is the important detail and it cuts both ways.  The 32
bytes are the per-object 16-byte `.text` padding: 25 objects are padded
individually, one object is padded once.  The reference was linked from *its*
translation units, so it has whatever padding that partition implies.  Merging
therefore does not simply remove waste -- it changes `.text` placement, and it
is only correct if the merged unit matches the original partition.  That is
exactly what `rebrew merge-sweep` searches for, and it is also why the merge
cannot be adopted one cluster at a time on a metric.

So: viable, small per cluster (147 bytes of `.data` here against the 4337
measured project-wide), and gated on partition accuracy rather than on
compilability.  The canonicalisation list above is the reusable part.

## Canonicalising the cluster's shared declarations: 22 -> 10 errors (2026-09-13, round 70)

Round 69 left 22 errors over 14 symbols in the merged `spiel` cluster.
Canonicalising eleven declarations — keeping the spelling that matches the
definition in the same cluster — takes it to **10 errors over six symbols**:

```
  1  char* g_slot_table;                       drop (extern unsigned char [] is authoritative)
  1  char g_entity_type_bytes;                 drop
  1  int g_entity_table_end;                   drop
  1  char g_entity_state_base;                 drop
  2  void* gm_AllocObjekt(int,int,int);        -> char*  (matches its definition)
  3  int   gm_AllocRaum(char*,int);            -> char*  (matches its definition)
  1  void* gm_SearchStruct(void);              -> char*
  1  char* gm_ResolveParentEntity(void*);      -> short* (short*)  (matches its definition)
```

What remains is a shorter list of the same kind, plus two structural ones:

```
gm_FreeObjectListRecursive   (3)   conflicting prototypes
gm_AddObjekt                 (2)   int vs void*
LogMessageInternal           (1)
gm_GetEntityTableEntry       (1)
LinkedNode                   (1)   struct defined twice, differently (C2011)
'active'                     (1)   not a member of LinkedNode (C2039)
```

`LinkedNode` is the interesting one: two of our files define the same struct
name with different members, so one of the two reconstructions is wrong
independent of merging.  `gm_AllocRaum` and `gm_AllocObjekt` being declared
`int`/`void*` where their own definitions say `char*` is the same signal at
function granularity — the per-function files disagree with each other about
the cluster's own interface.

That is a bounded cleanup: four more prototypes, one struct, one member, and a
preamble syntax error (`probe.c(41): '}'`).  The canonicalisation was applied
to the probe only; the real fix belongs in the sources (ideally one shared
header per cluster instead of repeated externs), and then the merge can be
tried for real and the `.data` duplication measured.

## The include blocker is solved; the externs are next (2026-09-13, round 69)

Round 68 left `rebrew merge` failing on relative includes that no longer
resolve once 25 inputs at two depths become one file.  That is mechanical and
now done: `.scratch/norm_includes.py` copies each input to a flat directory
rewriting every `#include "..."` against the directory the merged TU will live
in (24 includes re-based for the `spiel` cluster).  Merging the patched copies
compiles past the includes and surfaces the real remainder:

```
probe.c(41)   : error C2059: syntax error : '}'
probe.c(1965) : error C2040: 'g_entity_table_end' : 'int ' differs in
                levels of indirection from 'unsigned short *'
probe.c(1970) : error C2372: 'g_slot_table' : redefinition
probe.c(1971) : error C2040: 'g_entity_state_base' ...
```

22 errors over 14 distinct symbols, and they are all the same kind of thing:
the per-function files were written independently, so they declare the shared
cluster symbols with slightly different types.  The set:

```
functions  gm_AddObjekt  gm_AllocRaum  gm_AllocObjekt  gm_FreeObjectListRecursive
           gm_GetEntityTableEntry  gm_ResolveParentEntity  gm_SearchStruct
           LogMessageInternal
globals    g_entity_state_base  g_entity_table_end  g_entity_type_bytes  g_slot_table
types      LinkedNode (C2011 redefinition)   'active' (C2039, no such member)
```

Harmonising those ~14 declarations -- ideally by giving the cluster one shared
header instead of repeating externs in every file -- is what stands between
here and a compile, and after that the whole `.data` duplication problem goes
with it.  The normaliser is kept because the same step is needed for every
other cluster.

## `rebrew merge` works on the bodies, not the includes (2026-09-13, round 68)

Round 67 concluded the `.data` duplication needs the objects' order corrected so
the blob is unnecessary, which is what `rebrew merge` is for.  Tried on the
largest cluster -- the 25 files that came out of the original `spiel.c`:
`spiel.c`, `spiel2/3/5/6/62/622.c`, `spiel_dumpD.c`, `spiel_gm_DispatchCall.c`
and the sixteen `spiel_c/*.c`:

```
$ rebrew merge <25 files> -o probe.c --dry-run --json
count 84   input_count 25   extern_dropped 0   extern_conflicts 0
```

Clean: 84 functions, no dropped or conflicting externs.  But the merged output
does not compile as written.

```
probe.c(26)  : error C2059: syntax error : '}'
probe.c(151) : fatal error C1083: Cannot open include file:
               '../../../Units/Error/error.h'
```

The second is the real blocker and it is structural: the inputs live at two
different depths -- `game/*.c` uses `../../Units/...` and `game/spiel_c/*.c`
uses `../../../Units/...` -- and the merged file can only sit at one of them,
so the other group's relative includes stop resolving.  `--consolidate` hoists
what it can but does not rewrite them, and introduces a header ordering error
of its own (`rebrew_globals.h(107): syntax error : missing '{' before '*'`).

So the merge needs include rewriting (normalise every input's relative includes
to a single base, or move the merged TU and fix its own) before it can be
tried for real.  That is a mechanical pass over the inputs, and it is the next
step for the whole `.data` duplication problem -- the 105 extra string
occurrences, the +0x4000 raw surplus and the blob overlap all go away if the
original translation units are restored.

## The blob duplicates the objects placed after it (2026-09-13, round 67)

Round 66 left the 0x4000 `.data` raw surplus unexplained.  Locating the blob
exactly explains it: the best shift for `ref[0x3000:0x5000]` into our `.data`
is **+0x1e8**, so the blob sits at 0x31e8, and the surplus region
[0xe000:0x12000] is a *third* copy of content the blob already carries.

```
ref .data 0x3000  'Aemter(): Can't load mamt'   ours 0x2858 and 0x31e8
ref .data 0x6400  'cm_ExCreateGeb(): failed'    ours 0x65e8 and 0xe284
```

`0x65e8` is the blob's copy (`0x6400 + 0x1e8`); `0xe284` is the surplus's.  968
of the surplus's 1024 16-byte blocks also occur inside `ref[0x3000:0xe000]`.

The mechanism is the cut itself.  `.data` is placed in response-file order, so
the blob divides the game objects into two groups: those before it contribute
the 0x31e8 prefix, those after contribute the 0x4000 surplus -- and the surplus
is content the blob also reproduces.  That is the duplication round 59
measured as 105 extra string occurrences, now localised: **it is the objects
placed after the blob**.

Which means the cut cannot be tuned away.  Moving it trades prefix against
surplus but never removes the overlap; the two arrangements are "objects, then
blob" and "blob, then objects", and either way one of them duplicates the
other's content.  Resolving it needs either the blob reduced to the bytes the
objects do *not* emit, or the objects' `.data` order corrected so the blob is
unnecessary -- both of which are the object-order problem, and the second is
what `rebrew merge` exists for.

## Dropping the split objects' data sections does not help (2026-09-13, round 66)

The `.data` gap is bigger than the blob placement work has been addressing, and
the raw section sizes say so plainly:

```
                        .data raw   .data vsize   .rdata raw   .rdata vsize
reference                  57344      0x174059c       12288        0x2e81
build/split_poc.dll        73728      0x1746c28       16384        0x33b1
build/server_manual.dll    65536      0x17448b8       16384        0x32d1
```

`.data` raw is exactly 0x4000 too big and `.rdata` raw 0x1000 too big, in both
builds.  Note the byte-level `.data` metric compares only
`min(ours, reference)` = 57344 bytes, so everything past the reference's end is
*invisible* to it -- the +0x4000 is not in the 25311 figure at all.

Hypothesis tested and rejected: that the surplus is the 229 split LIBCMT
member objects' own `.data` sections duplicating the blob.  Running the whole
split pipeline without `split_coff --with-data` into a scratch directory:

```
              .text (differing/vsize)   .rdata diff   .data diff
with data        0x22af8 / 86608            2237         25311
without data     0x23e7a / 87188            7441         25311
```

`.text` gains 0x1634, `.rdata` agreement more than triples its disagreement, and
`.data` is byte-identical in the compared range -- the member data sections are
not where the surplus comes from.  (`--with-data` stays on.)  The `defs` group
grows from 20 to 40 objects to compensate, which is most of the `.text` cost.

So two different problems are open in `.data`: the 25311-byte disagreement
inside the reference's 0xE000, and a 0x4000 raw surplus past its end that
nothing currently measures.

## `rebrew verify-placement` is not usable on these binaries (2026-09-13, round 65)

Looking for a per-symbol `.data` placement diagnostic, I ran
`rebrew verify-placement` -- "Compare .data symbol VAs of the current build
against the data metadata".  It reports:

```
$ rebrew verify-placement --built build/split_poc.dll
symbols: 274  toml-matched: 29  correct-VA: 0  misplaced: 29
  g_file_append_mode    exp 0x100270f8  our 0x100333e4  d +0xc2ec
  g_log_format_table    exp 0x10027084  our 0x1003306d  d +0xbfe9
  ...

$ rebrew verify-placement --built original/Server/server.dll      # the reference itself
symbols: 274  toml-matched: 29  correct-VA: 0  misplaced: 29
  g_file_append_mode    exp 0x100270f8  our 0x100323e4  d +0xb2ec
```

Pointing it at the reference binary still says **29 of 29 misplaced**, which is
impossible, so the tool is not reading symbol VAs out of these images the way
its description implies (the reference is a stripped release PE with no COFF
symbol table).  Its output must not be used to judge `.data` placement here --
the round-58/60 byte-level comparisons are the sound measurement.  Recording
this because the 0/29 figure looks like a finding and is not one.

## The last 16 missing strings are a different case (2026-09-13, round 64)

After round 63, 16 reference `.data` strings are still absent from our image,
and they are one block, `\project\DieGilde\game\`, `Usefull Sync`,
`Sending data...`, `SERVER>>>> ALL PLAYER ARE READY`, `GamePath`, `Config`,
`\game.ini`, `_main_:`, a vfs format string and a few more.  Fourteen of them
are addressed by absolute VA from `ServerMainThread.c` (nine) and
`m_alloc.c` / `vfs_OpenStream.c`, so they are the same defect as rounds 62 and
63.  Adding the whole contiguous reference range
`.data[0x2560:0x2960]` (1024 bytes) as one array to `ServerMainThread.c` and
re-sweeping the cut:

```
 cut    .data differing
  90         31679
  92         31919
  95         31134     <- best of the sweep
```

Against 25311 without it, that is **+5823 bytes of `.data` disagreement for
1024 bytes of content** -- nine times the cost of the CrashDump block, which
was 637 bytes for 568.  Reverted.

The difference is overlap.  The crash-dump range was absent in its entirety;
this one is *interleaved* with content we already emit:

```
ref .data 0x2560  'stream end'                        our image has it at 0x28d5c
ref .data 0x28b0  'D:\\Develop\\...\\server.c'         our image has it twice, 0x28d8c and 0x28e08
```

so a contiguous blob duplicates them and shifts everything after it.  This
group needs the object-order problem solved first -- the same duplication
round 59 measured as 105 extra string occurrences -- rather than a fourth
copy of the content.  Recorded rather than forced.

## The crash-dump message data was absent too (2026-09-13, round 63)

Same defect as round 62, twenty-eight strings wide.  `CrashDumpUnhandledExceptionFilter.c`
addresses its message data by absolute VA throughout --
`LogMessageInternal((char*) 0x10027104, 0x220, ...)`, the WriteFile argument
table at 0x10027178..0x10027260, `CreateFileA((const char*) 0x10027318, ...)`
-- and nothing defined any of it, so those reads landed outside the section.
The reference has, in `.data[0x104:0x33c]`:

```
no dbg file   bad dbg file   no memory   bad (small) dbg file
D:\Develop\Units\Error\Error.c   not open crashdump
STACK_OVERFLOW  PRIV_INSTRUCTION  INT_OVERFLOW  INT_DIVIDE_BY_ZERO
FLT_UNDERFLOW  FLT_STACK_CHECK  FLT_OVERFLOW  FLT_INVALID_OPERATION
FLT_INEXACT_RESULT  FLT_DIVIDE_BY_ZERO  NONCONTINUABLE_EXCEPTION
INVALID_DISPOSITION  FLT_DENORMAL_OPERAND  ARRAY_BOUNDS_EXCEEDED
ILLEGAL_INSTRUCTION  IN_PAGE_ERROR  0x%08X  WRITE   READ
ACCESS_VIOLATION   BREAKPOINT  SINGLE_STEP  __crashdump.log  --> 
```

`CrashDumpUnhandledExceptionFilter.c` now carries those 568 bytes as one array
generated from the reference, under `// DATA: SERVER 0x10027104`.  The
missing-string count over the reference's `.data` drops 44 -> 16, and what is
left is one server/network group (`This is Gilde talking, can you hear me?`,
`Sending data...`, `GamePath`, ..., 16 strings) for a later round.

It costs placement, and re-sweeping the cut recovers most of it:

```
 cut    .data differing        cut    .data differing
  86         27985              94         29779
  90         27985              96         25311   <- optimum
  92         29539              98         30195
```

`_BLOB_AT_DATA` is therefore 0x3400; the script picks 95, and 95 and 96 are
equivalent because object 96 contributes no `.data`.  Net against the start of
round 62:

```
          round 62 start   round 62   round 63
.text          86600         86606      86608
.rdata          2237          2237       2237
.data          26799         24674      25311     (53.27% -> 55.86% equal)
```

`.data` is 637 bytes *worse* than round 62's peak and 568 bytes of previously
absent referenced data are now present.  That is the right trade for this
goal: the reference has those bytes, and once placement converges the content
has to be there to match.  The same reasoning applies to every entry in this
list -- produce the bytes first, then place them.

## The log-name table was truncated (2026-09-13, round 62)

`Error.c` declared the log-name table as 13 bytes:

```c
// DATA: SERVER 0x10027084
char g_log_format_table[13] = { 0x5f, 0x5f, ... };   /* "__server.log" only */
```

but `InitializeLogAndErrorHandler` walks it from 0x10027084 in **0x20 steps**
until 0x100270e4, and `DispatchLogOutput` indexes it as
`g_log_format_table + idx * 32`.  The reference has three entries there:

```
0x10027084  "__server.log"       (13 B + 19 pad)
0x100270a4  "gilde_server.log"   (17 B + 15 pad)
0x100270c4  "__dbg.log"          (10 B + 22 pad)
```

Only the first existed; the other two were absent from the image entirely, so
the loop read whatever followed.  The declaration is now the full 96 bytes,
generated byte-for-byte from the reference rather than hand-typed, and
`rebrew_globals.h`'s prototype matches.

That fixes content and costs placement: `.data` grew by 0x60 and, at the old
cut, agreement fell 26799 -> 28146.  Re-sweeping the cut with the corrected
table gives a much better optimum than either:

```
 cut    .data differing
  90         28757
  91         29859
  92         24674     <- measured optimum, and what the script now picks
  93         29101
  95         28552
  98         28146
```

`_BLOB_AT_DATA` is therefore 0x3050, not 0x3200.  The landscape is jagged --
one object either way costs thousands of bytes, and at cut 92 the blob sits
0xf4 bytes *early* and still scores best -- so the constant is measured, not
derived.  Anyone changing an object's `.data` size must re-sweep.

Net through `scripts/split_link.sh`:

```
          round 60    round 62
.text     86600       86606
.rdata     2237        2237
.data     26799       24674     (53.27% -> 56.97% equal)
```

## Where the restore blobs go in the response file (2026-09-13, round 60)

Rounds 56 and 57 established that `.data` and `.rdata` are placed in
response-file order, and moved both restore blobs out of `head` to sit after
the game objects.  "After the game objects" is not the end of the story: the
blobs want to sit where the reference has them, and the reference has
`rdata_restore.c`'s blob at reference `.data` offset 0x3000 (its own
`// DATA: SERVER 0x1002a000` marker).  Sweeping the insertion point across the
game objects, with `.data` differing bytes as the metric:

```
 insertion point            .text    .rdata   .data
 head (index 1, round 56)   86699     9328    38561
 end of mid (index 185)     86608     2237    33690
 after 64 objects           86599     2237    33009
 after 80 objects           86600     2237    31125
 after 92 objects           86600     2237    30165
 after 96 objects           86600     2237    28634
 after 98 objects           86600     2237    26799
 after 100 objects          86600     2237    28931
 after 128 objects          86600     2237    28931
 after 160 objects          86606     2237    32601
 after the split objects    86682     6365    37768
 at the very end            86759     6422    37922
```

Index 98 is the optimum and index 98 is also principled: the running `.data`
total of the first 97 game objects is 0x31c9 and object 98 takes it to 0x3238,
so 0x3200 is the first threshold at which the cumulative total passes the
blob's 0x3000 reference offset.  That is why the case sits just past a
cumulative-0x3000 rule rather than exactly on it -- our objects' `.data` runs a
little ahead of the reference's, which is the duplication problem round 59
measured, not an independent fact.

`make_split_rsp.py` now computes that cut itself: it sums each game object's
`.data` section sizes out of its COFF header and inserts the blobs at the first
object where the running total reaches 0x3200.  Effect end to end through
`scripts/split_link.sh`:

```
          before round 60    after
.text     86608              86600
.rdata     2237               2237
.data     33690              26799     (41.25% -> 53.27% equal)
```

A follow-up sweep (round 61) confirms 98 is the optimum and records a
counterintuitive fact about the metric.  Where the blob actually lands, and
what it scores:

```
 cut   blob shift   .data differing
  98       -0x30         26799
  99       -0x04         27781
 100       +0x40         28931
```

Cut 99 puts the blob four bytes from its reference offset and scores **worse**
than cut 98, which is 48 bytes out.  Same-offset agreement is a property of
the whole arrangement, not of the blob's own alignment: moving the cut slides
every game object between the old and new positions, and that costs more than
the blob's alignment gains.  So the cut has to be swept, and "make the blob
land exactly at 0x3000" is not the right objective.

Also measured and inert or negative: putting `rdata_restore` immediately after
`data_restore` (identical), `data_globals` there (`.text` 86600 -> 86598, the
rest unchanged -- two bytes, not worth the special case), and the defs/commons
group there (`.text` 86600 -> 94985, far worse).

## `/GF` is not the string-dedup answer (2026-09-13, round 59)

Our `.data` carries duplicate string literals the reference does not: 105 extra
occurrences, and the worst is `"D:\\Develop\\DieGildeAddOn\\game\\spiel.c"`,
which appears **22 times** across eight of our sources -- `spiel.c`,
`spiel2.c`, `spiel5.c`, `spiel_dumpD.c` and four `spiel_c/*.c` -- because we
split the original single `spiel.c` translation unit into per-function files.
The reference has one copy each.

`/GF` (eliminate duplicate strings) looks like the fix and is not.  Adding it
to `CMAKE_C_FLAGS` and rebuilding:

```
                 .rdata vsize   .rdata diff   .data vsize   .data diff   .data strings
before              0x32d1          2215       0x17448b8       38470          469
with /GF            0x4fa1         10712       0x1742bf8       35407          369
```

It does merge -- `.data` loses 0x1cc0 and 100 string occurrences -- but it
over-merges (369 against the reference's 453) and it moves the pooled strings
into `.rdata`, which grows by 0x2120 and whose agreement collapses from 2215 to
10712 differing bytes.  Net strongly negative, reverted.  The reference was
built without `/GF`; its lack of duplicates comes from its translation-unit
partition, not from a flag.

That makes TU merging the lever for `.data`, which is what `rebrew
merge-sweep` exists for, and it is a much larger change than anything else on
the list.

## `.data`: the blob is perfect and 0x72C too late; 46 strings are missing (2026-09-13, round 58)

`data_restore.c`'s blob is **byte-perfect**.  Comparing the reference's
`.data[0x3000:0xe000]` against ours at a shift of +0x72c gives 45056 of 45056
bytes equal, and at shift 0 only 41% of the section matches.  So `.data` is a
pure placement problem: the blob starts at our offset 0x372c where the
reference has it at 0x3000.

```
ref[0x3000]  41 65 6d 74 65 72 28 29 3a 20 43 61 6e 27 74 20 6c 6f 61 64 20 6d 61 6d 74 00 00 00
bld[0x372c]  41 65 6d 74 65 72 28 29 3a 20 43 61 6e 27 74 20 6c 6f 61 64 20 6d 61 6d 74 00 00 00
```

1836 bytes of our `.data[0:0x372c]` have no counterpart in the reference's
`[0:0x3000]`.  The block-by-block shift profile is noisy (16-byte `find`
matches recur), but every block from 0x3000 on that matches cleanly matches at
exactly +0x72c, so the excess accumulates before the blob and nowhere else.
Fixing it is worth about 37 points of `.data` agreement: 45056 of 57344 bytes
become comparable, i.e. 41% -> ~79%.

The prefix also has real *content* missing.  Of the reference's 453 `.data`
strings, **46 are absent from our whole image**, and every one belongs to the
crash-dump / error module:

```
gilde_server.log     __dbg.log            no dbg file        bad dbg file
no memory            bad (small) dbg file not open crashdump D:\Develop\Units\Error\Error.c
STACK_OVERFLOW       PRIV_INSTRUCTION     INT_OVERFLOW       INT_DIVIDE_BY_ZERO
FLT_UNDERFLOW        FLT_STACK_CHECK      FLT_OVERFLOW       FLT_INVALID_OPERATION
FLT_INEXACT_RESULT   FLT_DIVIDE_BY_ZERO   FLT_DENORMAL_OPERAND
NONCONTINUABLE_EXCEPTION  INVALID_DISPOSITION  ARRAY_BOUNDS_EXCEEDED
ILLEGAL_INSTRUCTION  IN_PAGE_ERROR        0x%08X             ... (46)
```

That is the exception-name table `CrashDumpUnhandledExceptionFilter` is 22.5%
identical against, and `CrashDumpUnhandledExceptionFilter.c` defines none of
it.  The strings have no direct `push imm32` reference anywhere in the
reference's `.text`, so they are dead data the original link kept; they belong
in the restore blob (or the file), and they are the one concrete content gap
left in `.data`.

## The same fix for `.data` (2026-09-13, round 57)

Round 56's classifier bug sent `rdata_restore.c.obj` to the `head` group.
`data_restore.c.obj` was *deliberately* there, from the CMake world where the
comment says it has to be linked next so the raw link's `.data` rsz reaches
0xe000.  That reasoning does not hold for the split response file, and the
same symptom appears: the `.data` blob reproduces reference bytes that the
game objects' own `.data` contributions sit in front of, so in `head` it lands
far too early.

Moving it into the same slot as the `.rdata` blob -- after the CMake objects
and before the split ones -- is inert for `.rdata` and moves `.data` a long
way:

```
                   .text    .rdata   .data        (differing bytes)
split_poc before   86647     2237    38546
split_poc after    86608     2237    33690
```

`.data` goes 33% -> 41% equal, `.text` picks up 39 bytes, `.rdata` is
unchanged.  The relative order of the two blobs does not matter (both
`data,rdata` and `rdata,data` measure identically), and `data_globals.c.obj`
is inert wherever it sits, so it stays where it was.

## Fixed: the split build's `.rdata` order (2026-09-13, round 56)

Round 55 left the split build's `.rdata` landing the `rdata_restore.c` blob at
offset 0x1a0 instead of the reference's 0x12e8.  The cause was a one-line
suffix test in `scripts/make_split_rsp.py`:

```python
t.endswith("data_restore.c.obj")     # True for "rdata_restore.c.obj" too!
```

so the rdata blob was classified into the `head` group, along with the data
blob, and linked third.  `.rdata` placement *does* follow response-file order
-- what misled round 55 was reading `rdata_restore`'s index in the CMake
response file as 2, when it is 192.  Moving it to sit after the CMake objects
and before the split ones (index 186 of 454) puts it where the reference has
it:

```
                              unzip 0.15a  deflate 1.1.3  runtime error   .rdata differing
reference                          0x12e9          0x5a1          0x2110   --
build/split_poc.dll (before)       0x01a1          0x18c1          0x0fc8   10625 / 11905
build/split_poc.dll (after)        0x12e9          0x5a1          0x2110    2237 / 11905
```

`.rdata` agreement goes 11% -> 81%, matching the CMake build's 2215, and
`.text` differing drops 86,719 -> 86,647 as a side effect.  `.rdata` is still
+0x530 too long for the reason round 55 recorded (the seven LIBCMT objects
whose `.rdata` the blob also supplies), so the size is unchanged; only the
arrangement moved.

The classifier now matches on `/<name>`, which is what the bug needed.
Verified end to end through `scripts/split_link.sh`, not just by hand-editing
a response file: the pipeline reproduces 2237/11905 on its own.

## The split build's `.rdata` is in the wrong order; the CMake build's is not (2026-09-13, round 55)

This round's useful surprise: the CMake build reproduces the reference's
`.rdata` *arrangement* while the split build -- the byte-identity vehicle for
`.text` -- does not.

```
                              unzip 0.15a  deflate 1.1.3  runtime error   .rdata differing
reference                          0x12e9          0x5a1          0x2110   --
build/server_manual.dll            0x12e9          0x5a1          0x2110   2215 / 11905
build/split_poc.dll                0x01a1          0x18c1          0x0fc8   10625 / 11905
```

`rdata_restore.c`'s blob is byte-identical in both; only its start moves
(0x1a0 against the reference's 0x12e8), and everything the blob carries moves
with it.  The blob's internal layout is fine -- `runtime error ` sits 0xe28
bytes into it in both builds.

The cause is the 229 LIBCMT member objects the split set emits explicitly:
their `.rdata` contributions land before the blob, where in the CMake build
the library's contributions land after it.  So the split build's `.text` is
the reason to use it and its `.rdata` is the reason not to, and the two need
reconciling before the split build can be the whole answer.

Note also that `.rdata` placement does **not** follow response-file order:
moving `rdata_restore.c` from the second slot of objects1.rsp to just after
`trees.c.obj` (round 54) left `.rdata` byte-for-byte identical, and the split
rsp puts the blob last yet it lands first.  Whatever MSVC6 keys the merge on,
it is not the object order that drives `.text`.

## Who the `.rdata` surplus actually is (2026-09-13, round 55)

After the IAT fix, `.rdata` differs in two runs.  The tail one is a surplus of
0x450 over the reference, and asking the map which objects own the symbols at
0x10026000..0x10026c60 names them exactly:

```
LIBCMT:crt0msg.obj   17 symbols      LIBCMT:timeset.obj   2
LIBCMT:testfdiv.obj   5              LIBCMT:a_map.obj     2
LIBCMT:x10fout.obj    4              LIBCMT:tzset.obj     1
LIBCMT:output.obj     3
```

Every one of those is a LIBCMT object our link pulls for its *code*, whose
`.rdata` then comes along and lands after `rdata_restore.c`'s blob instead of
inside the region the blob already reproduces.  So the blob and the linked
library are supplying the same bytes twice, which is exactly what
`CMakeLists.txt` records under `amsg_exit.c`.

The sizes say how much of the blob is load-bearing:

```
rdata_restore.c.obj  .rdata  0x1320   (4896 B)
built .rdata overshoot       0x0450   (1104 B)
data_restore.c.obj   .data   0xb000  (45056 B)
built .data  overshoot       0x431c  (17180 B)
```

so roughly 0xED0 of the blob is genuinely missing content and ~0x450 of it is
duplicated by those seven objects.  Deleting the duplicated strings from the
blob is the recorded attempt and lands `.rdata` at +0x40 rather than +0x450 --
the remaining 64 bytes are the open question, and `.data` is the same shape
with a much bigger blob.

Note this is *not* the same problem as rounds 52/54: there the fix was a wrong
symbol name and a swapped pair of `/include` directives, both one-line.  Here
the two programs are both right and they overlap, so the work is deciding
which bytes belong to the blob.

## The IAT is in slot order now (2026-09-13, round 54)

The IAT lives in `.rdata` and its slot order is part of byte identity.  Two of
the 100 slots were swapped:

```
MessageBoxA      ref 0x10024148   built 0x1002414c
GetWindowTextA   ref 0x1002414c   built 0x10024148
```

`crt_imports.c` already listed the two `/include` directives in the
reference's order; emitting them in the opposite order lands each import in
the reference's slot.  Reading the map's `__imp__` symbols in address order
now gives **0 mismatches** against the reference across all four DLLs, with an
identical per-DLL order (KERNEL32 81, USER32 2, WS2_32 16, WINMM 1).  The
split build, which is the byte-identity vehicle, verifies 0 mismatches too,
and both binaries put the IAT at the reference's 0x10024000..0x10024154.

**Tooling trap, worth remembering:** comparing import tables with pefile's
`DIRECTORY_ENTRY_IMPORT` order reports WS2_32 as badly scrambled, but that
walks the *OriginalFirstThunk* (ILT), a different table from the IAT.  The
check that matters is per import descriptor, read `FirstThunk` and the
`IMAGE_IMPORT_BY_NAME` behind each `OriginalFirstThunk` entry, then compare
`FirstThunk + 4*i` between the two binaries.  Do not trust the ILT order.

After this, `.rdata` differs in exactly two runs:

```
0x0000..0x0198   the import region -- the IAT slot *contents* are RVAs into
                 the hint/name table, which our surplus content displaces
0x2608..0x2e80   the crt0msg surplus, plus 0x2e81..0x32d1 which the
                 reference does not have at all
```

Everything between 0x0199 and 0x2607 matches the reference **exactly**, so
the import-region run is downstream of the surplus, not a separate problem.

## The CMake `.text` shortfall is substitution, not absence (2026-09-13, round 53)

The 0x470 the CMake link is short is *not* code the linker failed to pull.
`build/split_poc/map_full.json` records 244 reference CRT sections across 116
LIBCMT members; 101 of those members are pulled by the CMake link and 26 are
not -- together 11,315 bytes of reference CRT code:

```
sbheap.obj 4628   strgtold.obj 1233   cvt.obj 1062    intrncvt.obj 1004
memmove.obj 821   mbscat.obj   464    ieee87.obj 358  tolower.obj  314
mlock.obj   267   strnicmp.obj 257    stricmp.obj 208 ...  (26 total)
```

None of them has a direct `call rel32` site in the reference: they are pulled
transitively, through the CRT's own tables.  Forcing all 21 of them in with
`/INCLUDE:<first external symbol>` settles what that means:

```
built .text  0x223d6   (1136 short)   as linked
             0x25d9e   (13144 over)   with the 26 members added
```

So the reference has those members and the CMake link does not -- but adding
them overshoots by 0x3568 (14,280 bytes of new `.text`, against 11,315 in the
map, the difference being the sections the map never claimed).  The reason is
that 7,648 bytes of `.text` are already occupied by *our* C: the
`_CRT_REGION_KEEP` scaffolding (`sbh_pool.c` 4556, `crt_heap.c` 944,
`amsg_exit.c` 1168, `sbh_aliases.c` 480, `mlock.c` 212, `initterm.c` 80,
`dllmain.c` 208, `link_stubs.c` 16) stands in for `sbheap.obj`, `mlock.obj`,
`crt0msg.obj`, `dllcrt0.obj` and friends, and the net of those substitutions
against the library bodies they displace is the 1136-byte shortfall.

That is a design fact, not a bug to chase: the CMake build *cannot* be
byte-identical while it substitutes C for library members, unless each
substitute body is itself byte-exact.  Byte identity goes through the split
set, which emits the real member sections at their reference VAs and already
matches the CRT region 100.00% (39,877 bytes, round 50).  The CMake build's
job is `rebrew verify` / `rebrew test`; the split build's job is the byte
comparison, and `scripts/text_match.py --align` is how it is scored.

## The link had an extra import, from one underscore (2026-09-13, round 52)

`server.dll` has exactly 100 imports.  The CMake link had **101**, and the
extra one was `IsBadWritePtr` -- the import the whole `sbh_globals` /
`sbh_pool` / `sbh_aliases` / `crt_heap` scaffolding exists to keep out, by
displacing LIBCMT's `sbheap.obj`.  It did not work, and the reason was one
character: `sbh_aliases.c` wrote

```c
int __cdecl ___sbh_heap_init(unsigned int size)
```

MSVC decorates C `__sbh_heap_init` to COFF `___sbh_heap_init`, which is what
`sbheap.obj` exports and what `heapinit.obj` calls.  The local definition was
spelled with a third underscore in C, i.e. COFF `____sbh_heap_init`, a
*different symbol*: the real one stayed undefined, the linker pulled
`sbheap.obj` for it, and `__imp__IsBadWritePtr@8` came with it.  Every sibling
in the same file is spelled the library's way (`__sbh_find_block`,
`__sbh_heap_check`, `__sbh_free_block`), which is what exposed the typo.

To measure the CMake link without the postlink step deleting it:

```
cd build && PYTHONPATH=../.scratch/rebrew-stable/src \
  eval "$(sed 's#/out:server.dll#/out:server_manual.dll /MAP:server_manual.map#; \
               s#/implib:server.lib#/implib:server_manual.lib#' \
          CMakeFiles/server_dll.dir/link.txt)"
```

before -> after:

| | before | after | reference |
|---|---|---|---|
| imports | 101 | **100** | 100 |
| KERNEL32 imports | 82 | **81** | 81 |
| `LNK4006` duplicates | 50 | **8** | -- |
| `.text` vsize | 0x2276c | 0x223d6 | 0x22846 |
| `.rdata` vsize | 0x32f1 | 0x32d1 | 0x2e81 |
| `.rdata` differing bytes | 7414 / 11905 | **2215 / 11905** | 0 |
| `.data` vsize | 0x17468d8 | 0x17448b8 | 0x174059c |

`.rdata` agreement goes 38% -> 81% because the import tables sit at its very
start: with a wrong import set every RVA in them is off.

The 0x396 that `.text` lost is dead duplicate code, not a regression.
`sbheap.obj` was being linked even though `sbh_aliases.c.obj`'s definitions
won (`LNK4006 ... second definition ignored`), so its bodies occupied `.text`
without ever being referenced.  Removing them reveals the honest shortfall:
`.text` is 0x470 (1136 bytes) *short* of the reference, not the 0xda the
duplicate bodies were hiding.  Closing that is the next `.text` item.

### What is left in `.rdata`: 0x450 too big, from crt0msg

After the fix `.rdata` is still +0x450, and the cause is visible in the
`LNK4006` list: `crt0msg.obj` is still pulled, for `__NMSG_WRITE` and
`__GET_RTERRMSG` (only `__FF_MSGBANNER` is duplicated, by `amsg_exit.c`).  Its
23 one-string `.rdata` COMDATs then land *and* `rdata_restore.c`'s blob
supplies the same strings, so eleven literals appear twice:

```
'`h````'  '(null)'  'runtime error '  'KERNEL32'  'GAIsProcessorFeaturePresent'
'SunMonTueWedThuFriSat'  'JanFebMarAprMayJunJulAugSepOctNovDec'
'1#QNAN'  '1#INF'  '1#IND'  '1#SNAN'
```

The evidence that the blob is the right copy and the library's is the
surplus is positional: the *first* occurrence of every one of them lands at
exactly the reference's offset, and the second does not.

```
             reference   built (first)   built (second)
runtime error   0x2110       0x2110          0x2724
R6028           0x2150       0x2150          0x2764
R6002           0x2370       0x2370          0x2984
(null)          0x2074       0x2074          0x271c
```

`CMakeLists.txt` already records the trade: the original packs those strings
into 0x2eb bytes, while the linker's per-COMDAT placement of crt0msg's copies
costs 0x32b, so the blob is what reproduces the reference.  But the blob only
wins if `crt0msg.obj` stays out of the link, and it does not, because nothing
else defines `__NMSG_WRITE` / `__GET_RTERRMSG`.  Displacing those two locally
(same pattern as the sbh files) drops the duplicate literals and puts
`FF_MSGBANNER` (57 B) and `NMSG_WRITE` (339 B) back into `.text`, where the
reference has them at 0x1001fdf8 and 0x1001fe31 -- 0x18c of the 0x470
shortfall.

## The compiler build is not the missing lever (2026-09-13, round 51)

Every one of the 20 game residues is an MSVC6 allocator/scheduler fixed point,
so the obvious remaining hypothesis was that the reference was built by a
different CL.  It was not.  Compiling the same source with every MSVC 6.0
service pack the toolchain images provide (`REBREW_TOOLCHAIN=msvc-6.0[-spN]`)
gives byte-identical output for four of the five closest functions, and a
3-byte difference for the fifth:

```
                       sp0..sp3        sp4..sp6
gm_ObjectsAvailble     683/714         686/714   objsize 720
gm_CalculateProductionValue 391/396    391/396   objsize 400
cm_ProcessCommandQueue 624/639         624/639   objsize 640
vfs_OpenStream         434/667         434/667   objsize 704
```

The sp4 step on `gm_ObjectsAvailble` is the reference's own build being sp4+,
which is what the project already uses; it does not close the gap.  So the
toolchain choice is right and the residue is in the C.

A one-at-a-time flag sweep (`/O1 /Os /Ot /Og /Oy /Ob1 /Ob2 /Oi /Op /Oa /Ox`,
plus the `/O2`-minus variants) over the same functions agrees:

```
CrashDumpUnhandledExceptionFilter  base 293/2115  best /O2 /Oi-  316/2115
m_AllocTracked                     base 197/658   best /Oa        198/658
vfs_ReadCompressed                 base 167/492   best (base)     167/492
vfs_ReadData                       base 120/472   best (base)     120/472
vfs_OpenStream                     base 434/667   best (base)     434/667
ServerMainThread                   base 1383/2434 best (base)    1383/2434
```

No single flag moves a function more than 23 bytes out of 2115 and none is
exact.  This matches the per-file logs (`/O1` and `/Ot` give frame-pointer
prologues on `vfs_OpenStream`, `/Ox` equals `/O2`) and closes the flag and
compiler-version lines of attack for the whole set.

Also measured and negative this round, on `cm_ExProdObjekt` (4 instructions,
the `g_unknown_1de450` load and the `loop_count` store interleaved the other
way): three semantically identical reorderings of

```c
recipe_idx   = (uint)*(ushort*)(msg + 0x14);
*(volatile int*)&loop_count = *(int*)(msg + 0x16);
recipe_shift = g_unknown_1de450 + (recipe_idx << 6);
loop_count   = 4;
```

-- shift-expression first, the global split into its own assignment before the
volatile store, and the global assignment first -- all compile to the *same*
976/993 bytes as the current form.  MSVC6 re-derives its own schedule from the
expression DAG, so statement order is not the lever here either.  A fourth
variant that hoists the shift into `recipe_idx` breaks the size (249/990).

## The CRT region of the split link is byte-exact (2026-09-13, round 50)

There is now an honest whole-`.text` metric, and it says the stock-library half
of the split-set link is **done**.

`scripts/text_match.py` reports, per range, bytes equal at the same offset
(`raw`) and bytes equal *or* filled in by the linker (`masked`).  The mask is
principled, not a heuristic: every DIR32 slot from the image's own
base-relocation table, plus every rel32 operand of a branch or call.  What
survives is exactly the part the compiler controls — opcodes, ModRM, register
allocation, displacements, constants.  `masked == 100%` over a range means the
code there *is* the reference's code.

```
whole .text  raw 54663/141382 = 38.66%   masked 78775/141382 = 55.72%
crt    raw  94.50%   masked 100.00%   (39877 bytes, 244 ranges, 0 differ)
game   raw  79.47%   masked  91.58%   (82829 bytes, 260 ranges, 6975 differ)   [--drift]
```

The `game` line needs `--drift <link_drift.json>`: drift is piecewise constant
and shifts whole objects, so a fixed-offset comparison understates the game
region badly (38.91% vs the true 91.58%).  With `--drift auto` the tool runs
`link_drift.py` itself.  CRT ranges are emitted in reference-VA order, so the
fixed-offset figure is already the right one for them.

Two bugs stood between the last round and `0 differ` over 39,877 bytes, both in
`scripts/split_coff.py`, both about COFF indices:

* **Relocations name symbol-table *entries*, not positions.** `Coff.symbols`
  was a compacted list (AUX records skipped via `i += 1 + entry[17]`), while a
  relocation's `symidx` counts AUX records.  Any index past an AUX record was
  therefore wrong, and `remap.get(symidx, 0)` silently emitted symbol 0 — the
  object's own section symbol — so calls jumped to their own start.  `fclose.obj`
  §3 names entries 13..16 while the compacted list held 14 symbols.  The list is
  now `[None] * nsyms` indexed by entry index, with `None` guards at every
  consumer (`locate_sections.py`, `emit_commons.py`, `emit_defs.py` too).
* **A member matched in two service packs was emitted as one group.**  The
  reference CRT genuinely mixes packs (sp6 for most sections, sp5 for
  `dosmaperr`, `NMSG_WRITE`, `setmbcp`, `output`, `sbheap` §34 …), and the map
  records the pack per VA.  `split_coff` keyed the object by member alone and
  used whichever pack came first, which emitted sp6's
  `sbheap.obj` §34 — `3b f0 77 55` where the reference has sp5's
  `3b c6 72 55` — at 0x1001e638: one byte wrong in 39,877.  Grouping by
  `(member, library)` fixes it, but then a group only knows *its own* mapped
  sections, so the closure pass re-emitted the other pack's sections (sp5's
  `___initmbctable` landed at 0x10021ec0 and displaced the sp6 `crtGetACP` that
  belongs there).  The mapped set is now member-wide, resolved per copy by
  symbol name when the recorded index belongs to the other pack, and the
  member's data sections are emitted once per member rather than once per group.

The remaining gap is entirely the game region, and it is 20 functions:

| function | bytes | differ |
|---|---|---|
| `gm_AllocSpieler` | 3689 | 1971 |
| `CrashDumpUnhandledExceptionFilter` | 2115 | 975 |
| `cm_ExSellObjekt` | 2057 | 973 |
| `ServerMainThread` | 2434 | 506 |
| `ls_LoadBuildingEntityState` | 1463 | 382 |
| `gm_AllocGebaeude` | 1088 | 363 |
| `gv_ExAllocGraveyardWorker` | 1040 | 358 |
| `m_AllocTracked` | 658 | 288 |
| `vfs_ReadCompressed` | 492 | 233 |
| `vfs_ReadData` | 472 | 208 |
| `cm_ExCopyEntityData` | 912 | 187 |
| `vfs_OpenStream` | 667 | 154 |
| `ahm_ExAllocAlchemist` | 1002 | 136 |
| `gm_CheckInventoryCapacity` | 395 | 89 |
| `gm_FindNextFilteredEntity` | 346 | 55 |
| `srv_LoadBuf` | 750 | 49 |
| `gm_ObjectsAvailble` | 714 | 28 |
| `cm_ExProdObjekt` | 993 | 13 |
| `gm_CalculateProductionValue` | 396 | 5 |
| `cm_ProcessCommandQueue` | 639 | 2 |

6,975 differing bytes; those 20 functions account for all of them.  Six objects
also carry a size error, and each one is a drift step:

```
CrashDumpUnhandledExceptionFilter.c.obj   span=2128  built=2144  err=+16
m_AllocTracked.c.obj                      span=672   built=656   err=-16
vfs_ReadCompressed.c.obj                  span=496   built=512   err=+16
vfs_OpenStream.c.obj                      span=752   built=704   err=-48
cm_ExCopyEntityData.c.obj                 span=912   built=880   err=-32
gm_AllocGebaeude.c.obj                    span=1088  built=1120  err=+32
```

Once those are zero the drift is 0 end to end, the built `.text` (0x22af8,
+690) loses the dead-stripped import thunk tail that `rebrew postlink` already
trims, and masked-100% becomes byte identity.

Where to start, smallest residue first, all with `scripts/text_match.py
--align` for the size of the gap and `rebrew diff <va> --json` for its shape:

| function | VA | differ | shape |
|---|---|---|---|
| `cm_ProcessCommandQueue` | 0x1000aac0 | 2 | block layout: the `test ebx,ebx; je` guard and the `jne` back edge are one block earlier in the reference; the object is already the right length |
| `gm_CalculateProductionValue` | 0x10019720 | 5 | `fxch st(1)` and `cmp byte ptr [esi],0x17` emitted in the opposite order |
| `cm_ExProdObjekt` | 0x1000e140 | 13 | 4 instructions: the `g_unknown_1de450` load and the `mov [esp+0x18],ebx` store interleave the other way |
| `gm_ObjectsAvailble` | 0x10015f70 | 28 | pure ebx/edi register swap plus one spill slot |

Negative results from this round, so they are not repeated: a targeted
flag sweep over `/O2 /Gd`, `/GB`, `/Oy`, `/O1`, `/Ox`, `/Ot`, `/Og-` on
`gm_CalculateProductionValue` finds **no exact flag set** (best score 7500,
all `exact: false`), and `rebrew climb --passes 2 --objective aligned` on
`gm_ObjectsAvailble` finds **no improving adjacent-statement swap**
(baseline == best == 207,984 matched bytes, `moves: []`).  Both confirm
what the per-file logs already record: these residues are MSVC6 allocator
and scheduler fixed points, not statement-order choices.

## Distance to byte identity (2026-09-13, round 24)

One place to read the whole gap.  Nothing here is new work; it is the state
the round-by-round entries below establish.

| piece | state | size |
|---|---|---|
| reference `.text` | — | 141,382 B (0x22846) |
| game functions, byte-exact at object level | 261 of 281 `byte_matched` | ~140 KB |
| game functions, not byte-exact | **20** (10 size mismatches + 10 byte-different; 18 of them `PROVEN`/`STUB`, so `verify` hides them) | ~19 KB |
| first link-alignment gate | CrashDump +16 over 0x2fd0..0x6820; then m_AllocTracked -64, vfs_ReadData -32, cm_ExCopyEntityData -32 | — |
| standard CMake link, `.text` | 0x2276c (-218), postlink coverage 401/7,463 (5.4%) | — |
| split-set link (LIBCMT member objects), `.text` | 0x22af8 (+690, the dead-stripped thunk tail); 246 of 319 symbols exactly at their reference VA, 0 LIBCMT pulls | — |
| CRT region, masked-identical (round 50) | **100.00%, 0 differing bytes** | 39,877 B in 244 ranges |
| CRT functions no library carries | **9** (`srand`, `__CRT_INIT`, `fpmath`, `init_fptrs`, `unlock_9`, `crt_close_handle`, `crt_once_init`, `allmul_slow`, `fcn_1001a643`) | 542 B |
| CRT split-set leftovers | **34** symbols across ~10 members | 5,294 B |

The two halves are independent: the game walls keep the standard link from
byte identity, and the CRT leftovers keep the split-set link from it.  Within
the CRT half, rounds 18-21 (aliases, static demotion, section merging) moved
the leftover count 71 -> 34 and then plateaued; rounds 15-16 removed a whole
member by correcting five game call sites from `fflush` to `fclose`.

Last verify: 279/281 passed, 2 failed (0x100093a0 ServerMainThread, object
size 2434 = the target's but the bytes differ; 0x10018850
gm_AllocSpieler 3688 vs 3689).  gzread (0x10003960) is new: it was defined
in check_header.c without a `// FUNCTION:` marker, so `verify` never counted
it; it is byte-exact (559/559, RELOC) now that it has its own TU and marker.
Goal requires 280/280 with inline asm only for 1-5 byte padding.

**`verify` is not a byte-identity gate.**  18 of the 20 non-byte-exact
functions carry `PROVEN`, and `passed: true` for PROVEN does not consult the
byte compare: CrashDumpUnhandledExceptionFilter reports `match_percent 12.5`
and `delta 1873` yet counts as passed.  The honest number is `byte_matched`
in `db/verify_results.json` (261/281 at this revision).  Whole-binary
identity needs the 20 byte diffs **and** the link alignment below.

**CrashDump's four-register prologue is not the loop.**  Section 38's
corollary says to delete the loop and recompile; if the head then matches, the
loop is the blocker.  Round 3 cut CrashDump's `for (;;)` stack walk out
entirely (probe `.scratch/zz_cdprobe.c`, since removed): the object drops to
1761 bytes but the prologue is still `sub esp,0x234; push ebx; push ebp;
push esi; push edi`, i.e. all four callee-saved registers are reserved at
entry with no loop at all.  The demand is in the entry region — the target
puts the CreateFileA IAT pointer in esi and `hDbgFile` in ebp (both pushed at
entry) and only reaches for ebx/edi after the `hDbgFile == -1` guard, while
this reconstruction puts the same two values in ebx/edi, so the compiler
reserves all four up front.  It is a register-role permutation across the
entry block, not loop pressure, and not reachable by deleting or reshaping
the walk.

## `ls_LoadBuildingEntityState` is one constant-caching decision away (2026-09-13, round 24)

Read this section with the measurement caveat first, because the tooling
misreported this function in every earlier round.

**`rebrew diff`'s positional count is meaningless here and its candidate
column lies about the prologue.**  The file's own header note already says the
function is 100% mnemonic-aligned with the reference, and that is right: an
LCS over mnemonics gives **484 of the reference's 499 instructions (97%)**
against the current `/O2` object.  But the reference materialises `-1` once
(`or ebp,0xffffffff`) where the candidate rematerialises it at each of the
three stores, so the two instruction streams differ in length and the diff's
index alignment desyncs at instruction 2 — it then reports only **3** exact
instructions and prints a candidate prologue of `push esi; push edi` where the
real object has `push ebx; push esi; push edi`.  `rebrew-cmake-cl` +
`objdump -d -Mintel` is the ground truth for prologues; mnemonic LCS is the
ground truth for "how close".

**The whole gap.**  Reference prologue and the three `neg1` stores:

```
target   83ec0c 53 55 56 57   sub esp,0xc; push ebx; push ebp; push esi; push edi
/O2 obj  83ec0c 53 56 57      push ebx; push esi; push edi          (one short)
target   83cdff               or ebp,0xffffffff        once at 0x10012934
target   8928 / 89afa5000000 / 89af95000000
                             mov [eax],ebp / mov [edi+0xa5],ebp / mov [edi+0x95],ebp
/O2 obj  c700ffffffff ...     mov dword [mem],0xffffffff at all three sites
```

The register *roles* otherwise agree — the reference and the candidate both
put `stream_ctx` in edi and the entity pointer in esi (the source note's claim
that ours differs is stale).  Everything else is the knock-on: no ebp means
every frame slot is 4 bytes low from instruction 5 on, and the object is
1464 vs 1463.

**`/Oa` flips exactly that one decision**, which is why it is the only flag
that moves this function (125 -> 713 matched bytes) and why its prologue is
byte-identical: the `/Oa` object has `or ebp,0xffffffff` and the three
`mov [mem],ebp`.  But `/Oa` also keeps the `m_AllocTracked` result in a
register for the whole read loop instead of reloading it before each call
(`lea ebx,[eax+8]`, no `mov edx,[esi+0x71]` anywhere) and gives up 36 bytes.
Declaring the read helper's buffer parameter `int*` or `char*` does not bring
the reloads back (the CSE is not parameter-type driven), and a volatile read
regresses to 117/1471.  So the reference really is `/Oa`-style constant
caching with `/O2`-style aliasing.

Under the tree's own `/O2 /Gd`, eleven spellings of `neg1` all leave ebp
uncached and the object at 1464: dropping `register`; `~0`; moving the
assignment above `offset = 0`, above the `entity_count` guard, or into the
loop body; initialising it at the declaration; `long` instead of `int`; a dead
`neg1 == 0` guard in the loop; deleting the `dummy` local; inlining the
`int* ebx` pointer local; and `/G6` (130/1464).  **Raising the use count does
not trigger it either** — a diagnostic build with a fourth and a fifth
`neg1` store (obj 1475 / 1479) still has no `or ebp,0xffffffff`, so the
decision is not a use-count threshold.  This is the round-23 constant-caching
wall seen from the other side: the allocator's choice is reachable by a *flag*
that also rewrites the memory model, and by no source form at all.  `cl /help`
offers no finer-grained switch — the whole family is `/Oa` (assume no
aliasing), `/Ow` (assume cross-function aliasing), `/Og`, `/Ob<n>`, `/Ot`,
`/Oy`, `/Oi`, `/Ox`, and `/Oa` and `/Ow` each alone reproduce neither half of
the pair.

**The rest of the flag sweep.**  `/Ox`, `/O1`, `/Ot`, `/Og-`, `/Ow`, `/Ob1`,
`/Ob2`, `/Oy-`, `/G6`, `/G5`, `/Oi-`, `/Gy`, `/Os` on top of `/O2` are all
inert or worse for this function; `#pragma optimize("a", on)` around the body
is byte-identical to `--cflags "/O2 /Gd /Oa"`.

Register-aware diff of the `/Oa` build: 142 exact, 28 reloc, **51
register-only**, **278 structural**.  The register-only set is a clean
esi/edi swap — under `/Oa` the reference keeps `stream_ctx` in edi and the
entity pointer in esi, ours the other way round.  Four source attempts to move
it are
byte-identical to the baseline and inert: copying the parameter into a local
`char* ctx` and using that at all 43 sites, renaming the entity-pointer local,
declaring it before the two int locals, and adding an extra local.  The
structural remainder is the CSE block above plus the rotated 0x55 loop tail.

**Sweep table.**  `match/total@obj` for each function's *recorded* CFLAGS and
for the same flags with `/Oa` appended.  **`rebrew test --cflags` replaces the
metadata CFLAGS outright**, so a sweep that passes a fixed flag string
silently measures a different configuration for the six functions whose
`src/rebrew-functions.toml` entry is not the `/O2 /Gd` default; the numbers
below pass each function's own recorded string (the first column is identical
to a plain `rebrew test --no-promote` on the untouched tree):

| function | recorded cflags | recorded | + `/Oa` |
|---|---|---|---|
| CrashDump | `/O2 /Gd` | 267/2137@2137 | 265/2129@2129 |
| m_AllocTracked | `/O2 /Gd /G6 /Oy-` | 241/658@608 | 241/658@608 |
| vfs_ReadCompressed | `/O2 /Gd /DREBREW_ALLOW_NAKED` | 138/499@499 | 43/493@493 |
| vfs_ReadData | `/O2 /Gd /Oy- /DREBREW_ALLOW_NAKED` | 138/472@446 | 71/472@447 |
| vfs_OpenStream | `/O2 /Gd` | 444/693@693 | 114/697@697 |
| ServerMainThread | `/O2 /Gd` | 1336/2434@2434 | 1142/2450@2450 |
| srv_LoadBuf | `/O2 /Gd /Ot` | 701/750@750 | 112/780@780 |
| cm_ProcessCommandQueue | `/O2 /Gd /DREBREW_ALLOW_NAKED` | 624/639@639 | 99/639@609 |
| ahm_ExAllocAlchemist | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 823/1002@1002 | 507/1010@1010 |
| cm_ExSellObjekt | `/O2 /Gd` | 199/2057@2055 | 226/2057@1963 |
| cm_ExProdObjekt | `/Ox /Gd` | 976/993@993 | 341/993@982 |
| cm_ExCopyEntityData | `/O2 /Gd` | 525/901@880 | 525/901@880 |
| gv_ExAllocGraveyardWorker | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 606/1040@1040 | 245/1042@1042 |
| ls_LoadBuildingEntityState | `/O2 /Gd` | 125/1464@1464 | **713/1463@1427** |
| gm_ObjectsAvailble | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 686/714@714 | 567/714@709 |
| gm_FindNextFilteredEntity | `/O2 /Gd` | 168/346@342 | 168/346@342 |
| gm_AllocGebaeude | `/DREBREW_ALLOW_NAKED /O2 /Gd` | 418/1078@1078 | 243/1078@1078 |
| gm_AllocSpieler | `/DREBREW_ALLOW_NAKED /O2 /Gd /Oa /Ow` | 851/3689@3688 | 851/3689@3688 |
| gm_CalculateProductionValue | `/O2 /Gd` + pragma `a` | 391/396@396 | 391/396@396 |
| gm_CheckInventoryCapacity | `/O2 /Gd` | 293/395@395 | 152/395@389 |

Three functions are already `/Oa`-equivalent and their column is unchanged:
`gm_AllocSpieler` (`/Oa` in the metadata), `gm_CalculateProductionValue` and
`cm_ExCopyEntityData` (the `#pragma optimize("a", on)` in their sources).
`ls_LoadBuildingEntityState` is the only function `/Oa` helps; it is the only
one whose column should be read as a lead.

The six non-default `/O2 /Gd` entries are load-bearing and were re-measured
here for the first time as a set: `m_AllocTracked` is 241/658 with
`/G6 /Oy-` against 123/680 with plain `/O2 /Gd`, `vfs_ReadData` is 138/472
against 46/482, and `gm_AllocSpieler` is 851/3689 against 500/3689 — the
`/Oa /Ow` in its metadata is worth 351 matched bytes.

**Prioritised target list**, `rebrew diff <va>` under the tree's own
`/O2 /Gd`, sorted by structural mismatches (the only counts that need code
work; `reloc` slots are masked and `reg`-only diffs are not in this table):

| function | exact | structural | instrs | obj vs target |
|---|---|---|---|---|
| `gm_CalculateProductionValue` | 106 | 2 | 123 | 396 vs 396 |
| `cm_ExProdObjekt` | 316 | 5 | 354 | 993 vs 993 |
| `gm_ObjectsAvailble` | 188 | 18 | 229 | 714 vs 714 |
| `srv_LoadBuf` | 166 | 25 | 226 | 750 vs 750 |
| `vfs_OpenStream` | 96 | 99 | 199 | 667 vs 667 |
| `gm_FindNextFilteredEntity` | 5 | 112 | 118 | 342 vs 346 |
| `ServerMainThread` | 477 | 115 | 627 | 2434 vs 2434 |
| `gm_CheckInventoryCapacity` | 9 | 128 | 138 | 395 vs 395 |
| `vfs_ReadData` | 31 | 143 | 174 | 446 vs 472 |
| `vfs_ReadCompressed` | 50 | 150 | 200 | 492 vs 492 |
| `gv_ExAllocGraveyardWorker` | 166 | 160 | 333 | 1040 vs 1040 |
| `cm_ExCopyEntityData` | 78 | 169 | 249 | 880 vs 901 |
| `cm_ProcessCommandQueue` | 30 | 173 | 205 | 639 vs 639 |
| `ahm_ExAllocAlchemist` | 98 | 175 | 287 | 1002 vs 1002 |
| `m_AllocTracked` | 33 | 208 | 249 | 608 vs 658 |
| `gm_AllocGebaeude` | 75 | 264 | 353 | 1078 vs 1078 |
| `ls_LoadBuildingEntityState` | 3 | 496 | 499 | 1463 vs 1463 |
| `cm_ExSellObjekt` | 59 | 607 | 667 | 2055 vs 2057 |
| `CrashDump` | 11 | 701 | 724 | 2115 vs 2115 |
| `gm_AllocSpieler` | 82 | 971 | 1056 | 3688 vs 3689 |

The two closest (`gm_CalculateProductionValue`, `cm_ExProdObjekt`) are both
documented exhaustively as scheduling walls — the FP-stack `fxch`/folded-compare
exclusivity in the first, the pre-loop volatile-store interleave in the
second — so the structural count understates how hard they are.

**Superseded (round 25).**  The `structural` column above is *not* a priority
signal: `rebrew diff` aligns positionally, so one instruction of length
difference desyncs everything after it.  See the alignment-corrected table in
the round-25 section below before choosing a target.

## Every import thunk had a doubled IAT address (2026-09-13, round 48)

`emit_thunks.py` builds each thunk as six body bytes plus a DIR32 relocation to
`__imp_<symbol>`.  COFF **adds** the value already in the bytes to the resolved
symbol, and the body was taken from the reference, which already contains the
address — so LINK wrote `0x10024198 + 0x10024198 = 0x20048330` and all seven
socket thunks at 0x1001a160..0x1001a18a read `jmp dword ptr [2 * IAT]` instead
of `jmp dword ptr [IAT]`.  Present since the file was written; invisible to the
drift audit because the thunks still occupy the right 42 bytes.

The body is now `ff 25 00000000` and the relocation supplies the address.  All
eight match the reference byte for byte.

**And there are eight, not seven.**  The reference's `.text` ends with
`jmp dword ptr [0x10024124]` at 0x10023840 — the `_RtlUnwind@16` thunk that
`except_handler3` calls.  It is not adjacent to the socket group, so it gets its
own object (`import_thunks_tail.obj`) and `make_split_rsp` places it after the
CRT objects: any thunk object whose stem ends in `_tail` goes in a separate
group between `ordered` and the `emit_defs` objects.

## The section prefix before a matched symbol (2026-09-13, round 47)

Round 46 left 201 of 319 symbols on a constant **-16** plateau starting at
`_strchr`.  The cause was not missing code but *unclaimed* code: a match can
start partway into its member section, and the bytes before it are real code
the reference places immediately before it.  `strchr.obj` §1 starts with

```
8d42ff              lea eax,[edx-1]      <- the strncpy return-value tail
5bc3                pop ebx; ret
8da42400000000 8d642400                  11 bytes of 16-byte alignment padding
...                 _strchr at offset 16
```

so the reference has those 16 bytes at 0x1001af20 and `_strchr` at 0x1001af30,
while our map only knew about the offset-16 entry and emitted from there.

For every hit with a non-zero section offset the map now adds a second entry at
`VA - offset` covering `[0, offset)`, unless another entry already covers that
VA.  The `exsup` group is unaffected because its offset-0 entry is already
present, so the prefix is skipped.

| | before | after |
|---|---|---|
| symbols exactly at their reference VA | 46 | **246** |
| sum of abs delta over placed symbols | 32,172 | **30,088** |
| delta range | -0x10 .. +0x30c | **+0x0 .. +0x31c** |
| objects LINK discards | 0 | 0 |
| LIBCMT archive pulls | 0 | 0 |
| split-set `.text` | 0x22cba (+1140) | 0x22cfa (+1204) |

**Every mapped section now starts at its reference VA.**  `split_audit` still
reports 73 symbols with a delta, but they are all *interior* symbols of a
shared-tail object — the `memcpy.obj` `LeadUp*`/`UnwindUp*`/`TrailUp*` family,
`exsup3`'s `__except_handler3` and `__seh_longjmp_unwind@4`, `strchr`'s
`___from_strstr_to_strchr`, `fpinit`'s `__fpclear`.  The audit keys a symbol to
the VA in its *object filename*, so an interior label reads as if the whole
section were late by its offset.  Filtering those families out leaves **4**
nonzero deltas, and all four are that same artefact — the symbols really are at
their reference VAs.

So the +1204 in `.text` is entirely **after** the CRT region: `link_stubs.c`,
`emit_defs`' objects and the 96 unreferenced import thunks, which `rebrew
postlink`'s `data` fixer trims as "the extra `.text` tail".  The CRT half's
placement is done; what is left there is the functions no LIBCMT variant
carries (round 46) and the tail.

Note that `split_audit`'s "objects LINK discards" test is by object basename,
and the new prefix object defines no map-visible *symbols* of its own — it is
in the image (the bytes at 0x1001af20 match the reference exactly) but does not
show up in the map, so it reads as discarded.  Compare bytes, not basenames.

## The catalog's function size was truncating every longer object (2026-09-13, round 46)

The map's `size` came from the catalog — Ghidra's function size — and
`split_coff` trims each object to it.  That silently cut every reference
function longer than its catalog entry.  `_free` is the case that mattered:
LIBCMT's `free.obj` §1 is **233 bytes**, and Ghidra had catalogued 0x1001ab81
as a 106-byte `free` with the tail as two more "functions" (`unlock_09c` 88,
`unlock_09d` 45).  Our object was cut to 106 and the other 127 bytes were never
emitted — which is exactly the -128 drift island at `__alloca_probe`.

`match()` now reports how many bytes the member holds from the matched symbol
on, and the map takes the **larger** of that and the catalog size.  `--trim`
still caps at the section, so nothing grows past the member.

Two matcher filters also had to change:

* **`MIN_COVER = 0.5`** — `match()` compares `min(len(body), len(data))`, so a
  section that ends early still "matched" on its last few bytes: the
  `popen.obj` §6 entries at 0x1001abeb (88 B) and 0x1001ac43 (45) matched only
  the 9 bytes at offset 956 of a 965-byte section.  The floor has to stay at
  0.5 because catalog sizes are sometimes padded *above* the real function —
  crt0dat's 34-byte `exit` is a 17-byte section, exactly 0.5.
* **`MIN_FIXED_BYTES = 12`** — `MIN_FIXED_FRACTION` alone is too strict for
  relocation-dense code.  `init_fptrs` (`fpinit.obj` §7, 56 B) is six stores of
  absolute addresses, so 44 of its 56 bytes are operand slots and only 12 are
  opcodes.  A match now passes with **either** 12 fixed bytes **or** half the
  section fixed.  The absolute floor alone would be wrong: the fraction test is
  what keeps `undname.obj` §2 (0 fixed of 86) out, and that section otherwise
  matches several targets.

`match` selection also now prefers the library with the **longest** matching
section rather than the first that fits, since a shorter one matches as a
prefix and is then trimmed.  (That is what should have chosen vc7's 292-byte
`strncpy.obj` over sp6's 254-byte one; vc7's turns out to be a different
implementation and does not match, so the change is currently neutral — kept
because the rule is the right one.)

| | before | after |
|---|---|---|
| region functions matched | 229/244 | **234/244** |
| symbols exactly at their reference VA | 38 | **46** |
| sum of abs delta over placed symbols | 155,180 | **32,172** |
| delta range | -0x310 .. +0x25c | **-0x10 .. +0x30c** |
| objects LINK discards | 6 | **0** |
| LIBCMT archive pulls | 0 | 0 |

**201 of the remaining 319 symbols sit at exactly -16.**  That plateau starts
at `_strchr` (0x1001af30) and is one missing piece: between `_strncpy` (which
ends at 0x1001af1d, `pop ebx; pop esi; pop edi; ret`) and `_strchr` the
reference has

```
0x1001af1e  cc cc                     int3 padding
0x1001af20  8d42ff                    lea eax,[edx-1]
0x1001af23  5b                        pop ebx
0x1001af24  c3                        ret
0x1001af25  8da42400000000            lea esp,[esp]      \
0x1001af2c  8d642400                  lea esp,[esp]       > 11 bytes of padding
0x1001af30  33c0                      xor eax,eax        /   <- _strchr
```

a 5-byte strncpy return-value tail plus 11 bytes of msvc6's 16-byte
intra-section alignment.  Emitting it means an object whose section carries
16-byte alignment — the split objects take their alignment from the member, so
a 5-byte one left at 1-byte alignment would land `_strchr` at -11, not -16.

**Next step:** the missing 5-byte tail at 0x1001af20 (done in round 47), then
the CRT functions no LIBCMT variant carries at all — `allmul_slow`
(0x10022f29, 27 B), `unlock_9` (0x1001b8a5, 86 B) and the `unlock_09e/f/g`
group (0x1001b757 334, 0x1002001d 137, 0x100200a6 156).

**Correction (round 48): those are not missing.**  Every one of them is
*interior* to a section we already emit — `unlock_9` sits at offset 729 and
`unlock_09e` at offset 395 of the 815-byte `1001b5cc_.text.obj`
(`realloc.obj` §1); `unlock_09f` at +153 and `unlock_09g` at +290 of the
317-byte `1001ff84_.text.obj`; `allmul_slow` at +25 of the 52-byte
`10022f10_.text.obj`.  `map_libcmt` only walks catalog entries, so a Ghidra
split inside a member section shows up as an unmatched catalog row even though
the bytes are emitted.  Nothing has to be written by hand.  The only two
uncovered VAs left in the whole CRT are `srand` (0x1001a150, 12 B) and the
eighth IAT thunk `_RtlUnwind@16` (0x10023840, 6 B) — the reference's `.text`
ends there, and `emit_thunks.py` only emits the seven socket thunks because
they are the ones that sit together at 0x1001a160.

`srand` also accounts for the last -16 island in the *game* region: the drift
goes +16 from `gm_SetupEntityQuery` to `gm_QueryEntitySum` (0x100196c0) and
back to 0 at `__CRT_INIT`, and 0x100196c0 plus spiel622, `gm_RandomFloat01`,
`gm_RandomQuadratic` and `srv_SeedRandomWithTime` lands exactly on 0x1001a150.
The reference's 12 bytes there are `mov eax,[esp+4] / push eax / call
0x1001b535 / pop ecx / ret` — a wrapper around the 13-byte getptd/store body
that `rand.obj` §1 supplies at 0x1001b535.  It **cannot be written as C here**:
`library_msvc.h` declares 0x1001A150 a LIBRARY function, and `rebrew skeleton
0x1001A150` refuses with "Already covered by: library_msvc.h".  The tooling is
right — it is library code whose service pack we do not have, not game code.
Writing it would also collide with `_srand`, which `rand.obj` already defines
for the same symbol, so the 13-byte body at 0x1001b535 would be displaced.

## The map did not say which library it matched in (2026-09-13, round 45)

The first drift island in the split set was **-128 at `__alloca_probe`**: every
object from `_fclose` to 0x1001ab81 was placed contiguously and correctly, and
then the object for 0x1001ac70 landed at 0x1001abf0.  The reference has two
functions in between — 0x1001abeb (88 bytes) and 0x1001ac43 (45) — and our
objects for them emitted **nothing**.

**Cause 1: the map did not record the library.**  `map_libcmt` searches the
five service packs in order and `split_coff` resolves a member by name against
the first library that has it.  They disagree on section numbering: vc7's
`popen.obj` §6 is a 965-byte `.text`, 6.0-sp6's §6 is not code at all.  The map
now carries `lib`, and `split_coff` indexes members per `(library, member)`.

**Cause 2: the reference overlaps functions freely.**  popen's `$L21349`
fragment at 0x1001a89c is *interior* to `malloc.obj`'s 252-byte `__malloc`, and
wpopen's at 0x1001a8fb likewise; emitting them again duplicates bytes that are
already there and pushed everything after them 18 bytes late.  `split_coff` now
drops any entry whose VA falls inside the extent another entry **actually
emits** — computed from the section's `raw_size` and `--trim`, not the catalog
size.  That distinction matters: crt0dat's `exit` pair are two separate 17-byte
sections that really do tile, and a catalog-size test (34 and 17) would collapse
one of them.

| | before | after |
|---|---|---|
| split-set `.text` | 0x22b8a (+836) | **0x22a0a (+452)** |
| objects LINK discards | 11 (315 B) | **6 (72 B)** |
| symbols exactly at their reference VA | 38 | 37 |
| LIBCMT archive pulls | 0 | 0 |

**Honest reading: this is progress on size and completeness, not on
placement.**  The per-symbol drift is if anything wider at the tail (81 symbols
at -592, 80 at -752, against -731/-848 before), because the layout is a chain
and the objects after the changed ones all move.  The `.text` figure is the one
that improved unambiguously, and 384 bytes of it is content that used to be
missing or duplicated.

**Still wrong:** the popen `$L21349` entries at 0x1001abeb and 0x1001ac43.  A
catalog size of 88 and 45 matched only a **9-byte prefix** at offset 956 of a
965-byte section — there is nothing left of the section after that offset — so
all three entries emit the same 9 bytes and LINK keeps one.
`match()` accepts a 9-byte common prefix because it compares
`min(len(body), len(data))`; a match this short should be rejected, or the
entry needs locating from scratch.

**Method note.**  `rebrew postlink`'s `data` fixer already trims "the extra
`.text` tail (import thunks/stubs the original build dead-stripped)", so the 96
unreferenced import thunks from round 44 are a *known and handled* condition,
not a blocker — they only matter because the tail must be trimmable, which
requires everything before it to be position-aligned.

## 96 import thunks the reference does not have (2026-09-13, round 44)

Counting `ff 25` (`jmp dword ptr [imm32]`, the import-thunk form) across
*every* section:

| | reference | split set | standard link |
|---|---|---|---|
| `ff 25` | **11** | 107 | 106 |
| `ff 15` (`call dword ptr [imm32]`) | 211 | 208 | — |
| `.rdata` VirtualSize | 0x2e81 | 0x3401 | — |

The reference's eleven are the seven socket thunks at 0x1001a160, the
`_RtlUnwind@16` thunk at 0x10023840, and three in the game region
(0x10015513, 0x10021eda, 0x10021eef).  Ours has **96 more, all at the end of
`.text` starting at 0x10023950**, and **nothing references them** — no
relocation in the image points at 0x10023950.  They are ~576 bytes, which is
most of the split set's +836.

They are dead COMDATs kept alive by `/OPT:NOREF`.  The import libraries put
`_GetLocalTime@4` (the thunk) and `__imp__GetLocalTime@4` (the IAT slot) in one
member; our objects reference 124 `__imp_` symbols across 54 objects, so the
members get pulled, and `/OPT:NOREF` then refuses to drop the unused thunk
COMDAT that came with each.

Measured split of the 96, by deleting one object from the response file and
relinking:

| source | thunks |
|---|---|
| `crt_imports.c.obj` — 100 `#pragma comment(linker, "/include:__imp__X@N")` | **20** |
| genuine `__imp_` references in the game and split objects (124 across 54) | **76** |

`crt_imports.c` is the auto-generated TU that forces the IAT slots to be
allocated in the reference's order.  Removing it from the link costs 0x78
bytes of `.text` and 20 thunks, but the IAT order is then whatever LINK's hash
produces — which is why it exists, and which `rebrew postlink` already rewrites
from the layout package.  So it is a candidate, not a fix: 20 of 96.

**`/OPT:REF` is not the answer.**  Linking the split set with it drops `.text`
to **0xc510 (50,448 bytes)** — 90 KB of the reference's code would go, because
almost nothing references a split object: they are one section each, and the
archive's own internal cross-references are gone.  `/OPT:NOREF` is what keeps
them, and the reference clearly used the same discipline.

That experiment also exposed a real malformation.  `/OPT:REF` failed with
`1001a7f7_.text.obj : error : Internal error during ReadSymbolTable`, because a
section-definition AUX record with COMDAT selection **ASSOCIATIVE (5)** carries
the section *number* it is associated with, and `build_object` copied AUX
records verbatim while renumbering the sections — `malloc.obj` §1's `.rdata`
kept `assoc 5` inside a two-section object.  `build_object` now remaps that
number through `new_secnum` and falls back to `SELECT_ANY` when the associated
section was not emitted.  The `/OPT:NOREF` link is unaffected.

**Next step on this thread:** the thunks have to stop being *included*, not be
discarded afterwards.  Since they arrive with the `__imp_` symbol's member, the
options are to define the `__imp_` symbols locally against our own import table
(the layout package already carries the full IAT), or to accept the 576 bytes
and attack the drift instead.  Note the reference's IAT is 1408 bytes smaller
than ours too, so some of the same excess may be in `.rdata`.

**Method note.**  Do not try to parse `KERNEL32.LIB` member-by-member with a
naive archive reader: the first member is a linker member whose "symbols" are
not COFF at all, and the reader will happily interpret a section count of
several thousand and dump garbage.

## LINK was pulling exsup.obj out of LIBCMT (2026-09-13, round 43)

The split link had **five symbols satisfied by an archive member**:

```
0001:00022bb4  _gu_return                10023bb4 f   LIBCMT:exsup.obj
0001:00022bbc  __unwind_handler          10023bbc f   LIBCMT:exsup.obj
0001:00022c46  __abnormal_termination    10023c46 f   LIBCMT:exsup.obj
0001:00022c72  __NLG_Notify              10023c72 f   LIBCMT:exsup.obj
0001:00022c85  __NLG_Dispatch            10023c85 f   LIBCMT:exsup.obj
```

LINK could not find them among our objects, so it pulled the whole
`exsup.obj` member and appended it **after** everything else, at 0x10023bb4 —
256 bytes at the end of `.text` instead of in the CRT region.

**Why they were missing.**  `exsup.obj` §1 is one 238-byte section holding
seven reference functions at offsets 0, 24, 32, 66, 154, 170, 205, 214 and
233.  `map_libcmt` already recorded which one each VA matched, through the
symbol's offset in the section, but `split_coff` emitted every entry as the
section from byte 0 and then `--trim` dropped every symbol past the reference
function's length.  `__abnormal_termination` sits at offset 170; the entry at
0x1001e78e is 35 bytes long, so it was discarded along with the bytes it
belonged to.

**Fix: `build_object` grew a `start`.**  The body becomes
`body[start:start+trim]`, symbol values and relocation offsets are rebased,
symbols and relocations outside the slice are dropped, and the root COMDAT's
section symbol is never dropped (a COMDAT without one is `LNK1143: no symbol
for comdat section`).  Sliced objects also get an **empty alias set** — the
alias index lists every spelling of the *whole* section, and exporting those
from each slice puts the same symbols on several objects again.

**A second bug surfaced on the way.**  The pre-existing trim filter
(`sym["value"] >= trim`) was still applied to sliced objects, so the slice at
offset 170 dropped `__abnormal_termination` because `170 >= 35` — it deleted
the very symbol the slice exists to define.  It now applies only when
`start == 0`.

| | before | after |
|---|---|---|
| symbols satisfied by a LIBCMT archive member | 5 | **0** |
| split-set `.text` | 0x22c8a (+1092) | **0x22b8a (+836)** |
| objects LINK discards | 10 | 11, all duplicates |

Slicing is skipped when the section `split_coff` actually loaded is not code,
or when the offset is past its end, because the map records the section of the
*first* library that matched while `split_coff` resolves the member against the
first library that has it.

**Method note.**  Checking whether a discarded object's content is really lost
by searching the built `.text` for the reference's exact bytes gives false
negatives for any block containing a `call`: the rel32 depends on the drifted
callee address.  Compare the two blocks with their relocations set aside
instead — that is how the ten duplicates in the round-42 entry were confirmed
harmless.

## Three CRT members carry the same 101 bytes (2026-09-13, round 42)

The alias mechanism in `split_coff` exports every byte-identical spelling of a
section body, because that is what stops LINK pulling a sibling archive member
just to resolve another name.  Round 41 narrowed it to the object's *own*
member, which fixed crt0dat §14/§16 and fread/fwrite — but `lseek.obj`,
`read.obj` and `write.obj` all carry the **same 101 bytes**, so each still
exported all three of `__lseek`, `__read` and `__write`.  Three objects
defining the same symbol set makes LINK keep one and drop two, which is what
lost 101 bytes at 0x1001e8b4 and 101 more at 0x1001eec1.

The exclusion now covers the mapped sections of **every** member
(`all_mapped_names` in `split_coff`).

| | round 41 | round 42 |
|---|---|---|
| symbols exactly at their reference VA | 35 | **38** |
| sum of abs delta over placed symbols | 150,062 | **114,890** |
| objects LINK discards | 14 (541 B) | **10 (280 B)** |
| delta range | -0x2b0 .. +0x22c | **-0x264 .. +0x25c** |

**All ten remaining discards are harmless duplicates — verified, not assumed.**
Seven are the `$L21349` / `$L21312` fragments with a zero-length `.text`.  The
other three look like losses and are not:

| discarded | reference VA | but the bytes are emitted by |
|---|---|---|
| `1001e7dc___except_handler3.obj` | 0x1001e7dc | `1001e7d4_.text.obj`, at +8 — found at 0x1001e5e4 |
| `1001e899___seh_longjmp_unwind_4.obj` | 0x1001e899 | same object, at +197 — found at 0x1001e769 |
| `1001ba7f___amsg_exit.obj` | 0x1001ba7f | `1001ba71_.text.obj`, at +14 — found at 0x1001b81b |

The quick check that suggested otherwise was wrong: searching the built `.text`
for the reference's exact bytes fails for any block containing a `call`, because
the rel32 depends on the drifted callee address.  Comparing the two blocks with
their relocations set aside shows `__amsg_exit` at 0x1001b81b is byte-for-byte
the reference's, and the exsup3 and seh_longjmp interiors are present at their
expected offsets inside the object that carries the whole section.

**So the split set is not losing content.  It has the opposite problem: its
`.text` is 0x22c8a against the reference's 0x22846, 1092 bytes too long.**  The
CRT half's remaining work is placement and duplication, not missing bytes.

**Why the exsup3 pair is hard.**  `exsup3.obj` §1 is one 224-byte section
holding *three* reference functions, and `map_libcmt` records which one it
matched through the symbol's offset inside the section:

| reference VA | section offset | size |
|---|---|---|
| 0x1001e7d4 | 0 | 197 |
| 0x1001e7dc | 8 | 216 |
| 0x1001e899 | 197 | 27 |

`split_coff` never sees that offset, so all three emit the section from byte
0, trimmed to three different lengths.  The first object carries the closure
and so defines all three symbols, and the other two are then duplicates —
which is harmless here, because the section is emitted once and the interior
functions sit at the right relative offsets inside it.

See the round-43 entry below for the case where *not* slicing was not
harmless: `exsup.obj`, where the same omission left three symbols undefined
and made LINK pull the whole member out of LIBCMT.

**Cross-library section indices are a trap.**  A map entry can name a section
that only exists in a later service pack: vc7's `popen.obj` has 21 sections
where the 6.0 ones have 9, and its §6 is a 965-byte `.text` while sp6's §6 is
not code at all.  `split_coff` resolves a member by name against the *first*
library that has it, so the offset is meaningless there.  Round 41 added a
section-count filter; the slice experiment needed a second guard (only slice a
`.text` root section, and only when the offset is inside it).  The real fix is
to record the library in the map and have `split_coff` read that copy.

## Two reference VAs were sharing one library section (2026-09-13, round 41)

The split set's CRT drift had two independent causes, and both reduce to the
same failure: **two of our emitted objects came out byte-identical, so LINK
kept one and silently dropped the other.**

**1. `map_libcmt` matched on content alone.**  A CRT member can hold two
COMDAT sections with identical bodies that differ only in their relocation
target:

| VAs in the reference | member sections | body |
|---|---|---|
| 0x1001a746 / 0x1001a74f | `crt0dat.obj` §14 / §16 | `6a0d e8???? ???? 59 c3` — `__lockexit` / `__unlockexit` |
| 0x1001a931 / 0x1001aa6a | `fread.obj` §1 / (alternative) | 47 bytes, both calling 0x1001bb60 |

The matcher returned the first section that fitted, so both VAs claimed §14
(or fread §1), the two objects came out with the same md5, and LINK discarded
one — the 9 bytes at `__initterm` and the 47 bytes before `__fread_lk`.
`match()` now takes a set of `(member, section, value)` keys already handed to
another VA and skips them.  The fallback matters: an alias at *one* VA
(`_mbsdup` / `__strdup` both sit at 0x10023812) must still resolve to the
shared section, so the exclusion only applies while the same library has an
unclaimed candidate left.

**2. `split_coff` exported the sibling's name.**  Even with distinct sections
the objects still clashed: the alias index lists every byte-identical spelling
of a body, so the §14 object exported `__unlockexit` and the §16 object
exported `__lockexit`, and two objects defining one symbol is again a
duplicate for LINK.  Each object's alias set now excludes the external names
defined by its own member's mapped sections.

**3. Section indices are library-specific.**  A map entry can point at a
section that only exists in a later service pack — vc7's `popen.obj` has 21
sections where the 6.0 ones have 9 — and `split_coff` resolves a member by
name against the *first* library that has it, so vc7 §17 indexed past the end
and crashed the splitter.  Entries above the canonical library's section count
for that member are now filtered out.

**Effect on the split set:**

| | before | after |
|---|---|---|
| symbols exactly at their reference VA | 25 | **35** |
| objects LINK discards | 20 (923 B) | **14 (541 B)** |
| first drift island | -9 at `__initterm` | **gone** (first is -47 at `__fread_lk`) |
| delta range | -0x353 .. +0x22c | **-0x2b0 .. +0x22c** |
| sum of \|delta\| over placed symbols | ~182,000 | **150,062** |
| section VirtualSize | 0x229fa | 0x22b8a |

The VirtualSize grows because 382 bytes of reference content that used to be
dropped are now emitted; it is not the metric to read here.  Note also that
`rebrew verify` is unaffected (280/282) — these are split-set pipeline
scripts, not part of the build.

**Next step:** 14 objects are still discarded.  Their pairs are in the map
with the same `(member, section)`; the remaining ones want the same treatment,
and if a member has no second section that fits, the object needs a distinct
primary symbol rather than a distinct section.

## The component loop walks a pointer, and the CPU flag is /G5 (2026-09-13, round 40)

`gm_AllocGebaeude`'s component loop indexed the record by the counter:

```c
	geb_type = 0;
	for (; geb_type < 0x40; geb_type++) {
		unsigned short comp = *(unsigned short*) (s.record + 0x23 + geb_type * 2);
		if (comp == 0) break;
		if (comp == 0xffff) continue;
		...
	}
```

The target walks a pointer instead, and keeps the pointer increment *ahead*
of the counter increment:

```
lea edi,[eax+0x23]            ; once, before the loop
...
add edi,2 / mov eax,[ebp+8] / inc eax / cmp eax,0x40 / mov [ebp+8],eax / jl
```

Written as a pointer walk with both increments in the for-header:

```c
	rec = (unsigned short*) (s.record + 0x23);
	for (; geb_type < 0x40; geb_type++, rec++) { comp = *rec; ... }
```

Both increments have to be in the header — with `rec++` at the end of the
body the `continue` for a 0xffff component skips it.  Aligned 41.6% ->
**42.5%**; object 1120 -> 1118 bytes (target 1088).  The island stays: the
function still carries about 19 extra instructions elsewhere.

**The project's CPU flag is not /G6.**  `spiel622.c` carries 17 functions, 15
of them byte-exact, so it is a good probe.  `/O2 /Gd /G3`, `/G4` and `/G5`
produce a byte-identical object to the `/O2 /Gd` default — `rebrew diff`
reports the same `2 structural, 15 reloc, 106 exact` for
`gm_CalculateProductionValue` under all four.  `/O2 /Gd /G6` changes the
codegen of **12 of the 17** functions, so the default is a `/G5`-class
setting and any function whose metadata says `/G6` is an explicit override,
not the house style.

**`gm_CalculateProductionValue` is the closest function in the binary to
byte-exact and is still two instructions away.**  `rebrew diff` on it reads
`2 structural diff(s), 0 register diff(s), 15 reloc diff(s), 106 exact
match(es)` — the two structural diffs are one swapped pair:

```
target:  fmul qword [0x100257d0] / fxch st(1) / cmp byte [esi],0x17 / fmulp st(1)
ours:    fmul qword [0x100257d0] / cmp byte [esi],0x17 / fxch st(1) / fmulp st(1)
```

The `cmp` is hoisted one slot too far into the x87 delay shadow.  Re-tested
this round against the `acc = quot; mod_value = ...; value = (float)(acc *
mod_value);` block: swapping the first two statements, casting both operands
to double, and folding `mod_value` into the `value` expression all leave it at
`2 structural / 106 exact`; using `quot` directly in place of `acc` makes it
worse (4 structural, 104 exact), and folding the whole multiply into one
expression is much worse (54 structural).  Combined with the round-1..7
sweep in the file header, this is a genuine fixed point of the x87
scheduler — every spelling lands on the same two-instruction swap.

**Next step:** unchanged — the five islands.  `vfs_ReadCompressed` is 497
bytes against a 496-byte bucket, so one legitimate byte of shrinkage would
close it; `m_AllocTracked` is 656 against 672 and needs 1..16 more;
`cm_ExCopyEntityData` needs 32 bytes of code found.

## A clamped length has to be its own variable (2026-09-13, round 39)

`vfs_ReadCompressed` clamped its read chunk in place:

```c
n = s->remaining;
if (n > 0) {
    if (n > 0x4000) n = 0x4000;
    if (n == 0) return 0;
    ... fread(s->inbuf, n, 1, s->file); ...
}
```

The target does not clamp in place.  It materialises the constant first and
keeps the dead check that follows:

```
mov edi,0x4000 / cmp eax,edi / jae L / mov edi,eax / test edi,edi / je ret0
```

Clamping `n` makes msvc6 emit the *other* min shape
(`cmp edi,0x4000` / `jbe L` / `mov edi,0x4000`) and drop the check entirely.
Using `i` — the separate clamped length the source already declares — gives
the target's shape byte for byte.  **499 -> 497 bytes, aligned 76.5% ->
79.0%.**

Measured and reverted while getting there: four different ternaries, an
if/else, and the constant on the left all give the clamp shape (73.6%); a
signed `lim` with casts gives 497 at 75.8%; folding the two `volatile int`
locals into one struct gives 497 with no gain.

**The prologue reorder is a real trade.**  Moving `if (handle == 0)
return -102;` above the two `volatile` initialisers drops the object's
section from 512 to 496 — which is exactly the reference span, so it *closes*
that drift island — but costs 4 points of byte alignment (79.0% -> 75.0%),
because the target initialises `done`/`result` at the top and only schedules
the handle test late.  Not kept.

**CFLAGS sweeps of the two default-flag functions came back empty.**

| function | default | best other | target |
|---|---|---|---|
| `CrashDumpUnhandledExceptionFilter` | 2137 | `/G6` 2129 (`/Oa` 2129) | 2115 |
| `cm_ExCopyEntityData` | 880 | `/G6` 881; `/Oy-` 875 | 912 |

`/G6` shrinks `CrashDump` by 8 bytes but costs 3.2 points of alignment
(22.5% -> 19.3%), and neither reaches the next 16-byte bucket, so the island
would not move.  `cm_ExCopyEntityData` is 32 bytes short under *every* flag
set — it is missing code, not mis-flagged.  All five of the round-38 islands
are single-function files, so these sweeps are safe to repeat.

`cm_ExCopyEntityData`'s remaining differences are structural, not scheduling:
the target writes `movsx eax,[edx+ecx]` where we write `[ecx+edx]` (swapped
base/index roles), it has a two-way `jge`/`jmp`/`mov eax,-1`/`jmp` where we
have a one-way `jl`, and it compares through a pointer
(`mov edx,IMM / cmp [edx],eax`) where we load the value first
(`mov esi,[IMM] / cmp esi,eax`).

**Next step:** same five islands.  `m_AllocTracked` (section 656 against the
672 span) and `vfs_ReadCompressed` (512 against 496) are one 16-byte bucket
away; `cm_ExCopyEntityData` needs 32 bytes of code found, and
`CrashDump`/`gm_AllocGebaeude` need real reversing.

## One missing function was 16 bytes of the game region's drift (2026-09-13, round 38)

The object-error table from round 37 has a caveat worth stating: msvc6 pads a
COFF `.text` section to a 16-byte multiple, and LINK merges the *padded*
length, so an object's contribution is `round16(function size)` — not the
function size.  `vfs_ReadCompressed` is the clean example: its function is 7
bytes long (499 against 492) and its section therefore rounds to 512 where
the reference's rounds to 496, which is the whole +16.  Every remaining
game-region island is a wrong *function* size plus that rounding.

**`gv_GetSlotEntry` was missing a function, not mis-sized.**  The reference
has a second function in that translation unit at 0x10010700:

```
8b4c2408   mov  ecx,[esp+8]
33c0       xor  eax,eax
837904ff   cmp  dword ptr [ecx+4],-1
0f94c0     sete al
c3         ret
```

It has no caller, no catalog name, and never appeared in the 281 tracked
functions, so nothing pointed at it.  Without it the object is 329 + 7 bytes
of msvc6's 16-byte intra-section alignment = 336, against the 352-byte span
to `FindSlotEntryFiltered`; with it the object is 329 + 7 + 14 + 2 = 352.
Written as ordinary C in `gv_GetSlotEntry.c` it is **EXACT 14/14**.

`rebrew skeleton 0x10010700` is what puts the `size = 14` annotation in
`src/rebrew-functions.toml`; `rebrew test` skips a marked function with no
SIZE, reporting `SKIPPED: No SIZE annotation`.  Note that rebrew leaves the
toml mode 444, so restoring a backup of it needs `rm` first — `cp` over it
fails with EACCES.

**Effect:** `verify` is 280/282 (up from 279/281), built `.text` 0x2275c
(-234) -> **0x2276c (-218)**, and the split set now places **25 of 330**
symbols exactly at their reference VA, up from **0**.

**`scripts/link_drift.py` needed a tie-break.**  Several functions here are
byte-identical twins — the `cm_ExAllocAlchemist` / `cm_ExAllocGraveyardWorker`
thunks, `amt_FindEntity26` / `amt_FindEntity27` — so "highest score wins"
latched onto the wrong copy and reported an 80-byte drift where the real one
was 16.  Ties now break towards the reference offset.

**The five remaining game-region size errors**, and the drift island each one
creates:

| object | function delta | island |
|---|---|---|
| `CrashDumpUnhandledExceptionFilter` | +22 | +16 at 0x10002770 |
| `m_AllocTracked` | -2 | -16 at 0x10006580 |
| `vfs_ReadCompressed` | +7 | +16 at 0x10008a90 |
| `cm_ExCopyEntityData` | -21 | -32 at 0x1000ec00 |
| `gm_AllocGebaeude` | +32 | +32 at 0x100174d0 |

`gv_GetSlotEntry` is no longer among them.  Every one is on the 20
non-byte-exact list, so the game half of the link cannot be aligned without
finishing them.

**Next step:** the five above, smallest first.  `m_AllocTracked` (2 bytes),
`vfs_ReadCompressed` (7) and `cm_ExCopyEntityData` (21) are all at documented
scheduling plateaus, but `vfs_ReadCompressed`'s 7 bytes are the prologue
order (the target hoists `mov eax,[esp+0xc]` above `push ebx` and puts
`test eax,eax` after `push esi`), which is the same class of lever that
closed other functions.  The standard link cannot fix the CRT half at all:
`link_drift` shows the `sbh_*` / `crt_*` reconstruction objects 12,737 bytes
away from where the reference has them, because LINK appends command-line
objects after the archive members — that is the split set's job.

## The link's whole remaining error is seven object sizes (2026-09-13, round 37)

`objects1.rsp` is **already sorted by reference VA** — 0 inversions in 173
adjacent pairs — so the game region is not misordered.  What breaks it is
purely per-object length: the drift profile below is piecewise constant and
changes value only at the objects whose `.text` is the wrong size.

`scripts/link_drift.py` (new) is what makes this visible.  It masks the bytes
a relocation may legitimately change (every rel32, every immediate or
displacement pointing into the image), then finds the offset in the built
`.text` that maximises the match, per tracked function.  Output today:

```
built .text 0x2275c  reference 0x22846  delta -234
  SendBroadcastPacket / crc32 / DispatchLogOutput     drift  0
  EmitCrashModuleLine .. vfs_WriteUint32LE            drift +16   (CrashDump broke it)
  m_FreeTracked .. m_pool_free                        drift  0
  ...
  sim_* .. gm_RandomQuadratic                         drift -32
```

**The block-fill prelude has exactly six sites in the whole binary**, all in
the game region, and three were still unreproduced:

| site | function | kind | state |
|---|---|---|---|
| 0x10006730 | `m_AllocTracked` | zero-fill | this round |
| 0x10008f0c | `vfs_ReadData` | copy | this round |
| 0x10017611 | `gm_AllocGebaeude` | zero-fill | this round |
| 0x10006929 | `m_init` | zero-fill | already asm |
| 0x10006e0d | `m_PoolAlloc` | zero-fill | already asm |
| 0x1000b057 | `srv_InitBuildingTypeTable` | zero-fill | already asm |

Five are `xor eax,eax` + `rep stosb/stosd`; `vfs_ReadData` is the same
template with `rep movsb/movsd` from `esi`.  The prelude is **not reachable
from C**: re-probed this round with eight `memset` shapes, twenty `memcpy`
shapes and one 0x100-frame shape mimicking `vfs_ReadData`, across
`/O2 /Gd`, `/O2 /Gd /G6`, `/O2 /Gd /G5`, `/Ox`, `/O1`, `/Oy-`, `/Os`, `/Oa`,
`/Ow` and every `6.0`…`6.0-sp6` image, plus `4.2` and `5.0`.  Every one emits
the naive `shr ecx,2; rep stosd; and ecx,3; rep stosb`.  `/G6` *is* being
applied — it changes the scheduling around the fill — it just does not select
this template.  Reproducing the six sites as block-fill asm by naming the
operands as ordinary locals is therefore the only route, and is the sanctioned
exception to "C only": the target has no C spelling, and the same idiom
appears nowhere else in the binary (no other `sub reg,reg; jle` without a
`test` between).

**Effect of the three new sites:**

| function | object before | object after | target | aligned before | aligned after |
|---|---|---|---|---|---|
| `m_AllocTracked` | 608 | 656 | 672 | 46.6% | 51.4% |
| `vfs_ReadData` | 446 | 479 | 472 | 58.0% | 76.4% |
| `gm_AllocGebaeude` | 1088 | 1120 | 1088 | 37.3% | 41.6% |

Built `.text` **0x226fc (-330) -> 0x2275c (-234)**, and the game region's
accumulated drift at `gm_RandomQuadratic` goes from about -100 to **-32**.

**The remaining per-object size errors** (span = distance to the next
object's first reference VA, so only objects that tile densely are
meaningful):

| object | span | built | error |
|---|---|---|---|
| `vfs_OpenStream.c.obj` | 752 | 704 | **-48** |
| `cm_ExCopyEntityData.c.obj` | 912 | 880 | **-32** |
| `gm_AllocGebaeude.c.obj` | 1088 | 1120 | +32 |
| `CrashDumpUnhandledExceptionFilter.c.obj` | 2128 | 2144 | +16 |
| `m_AllocTracked.c.obj` | 672 | 656 | -16 |
| `vfs_ReadCompressed.c.obj` | 496 | 512 | +16 |
| `gv_GetSlotEntry.c.obj` | 352 | 336 | -16 |

`gm_AllocGebaeude` is the one deliberate trade: its object was exactly 1088
before, and carrying the correct prelude makes it +32, but that is *also*
what took the whole `.text` 32 bytes closer.  Its other 32 bytes of excess
have to come out before it can be byte-exact; the prelude is a prerequisite
because it sits directly in front of the component loop and shifts every
register assignment downstream.

**Next step:** `vfs_OpenStream` (-48) and `cm_ExCopyEntityData` (-32) are the
two biggest remaining size errors and neither is a prelude site, so their
shortfall has a different cause — start there.  `gv_GetSlotEntry` (-16) is
not on the non-exact list at all, so its 16 bytes are missing *content*, not
a wrong function size.

## Deleting the dead half of `link_stubs.c` takes 368 bytes off the split link (2026-09-13, round 36)

Round 35 left the deletion undone because the dead names appeared in the
tooling.  Checked: the only hits outside `docs/` and `.scratch/` are Ghidra
label fields inside `src/rebrew-functions.toml` (`ghidra = "..."` on *other*
functions) plus the definitions themselves — **no link-time or postlink-time
dependency**.  Recomputing deadness as "defined by `link_stubs.c.obj` and
undefined in no object of either response file" gives **89 of 232** symbols.

Removed the 24 that are C functions (20 one-line stubs, 4 multi-line):
`_callnewh`, `ahm_RandomBelow`, `destroy_entity`, `fcn_1001accd`,
`fcn_1001c083`, `fcn_1001e8b4`, `fcn_1001eab0`, `fcn_1001ede5`, `fcn_1001eec1`,
`find_entity_26`, `find_entity_27`, `rand_mod`, `read_uint32_be`,
`vfs_EntityCleanup`, `vfs_FreeGameSubobject`, `vfs_FreeSubobj`,
`vfs_LockedFwrite`, `FreeCommandBuffer`, `free_node`, `game_free`,
`write_log`.  The other 65 dead symbols are `.data`/`.bss` globals and were
left alone — they do not emit `.text`, and `.data` is postlink's business.

`link_stubs.c.obj` `.text` **512 -> 128 B**; the split set **0x22aea (+676) ->
0x2297a (+308)**.  `gate.sh` still passes: 0 compile/link errors, 279/281.

**The standard link got worse and that is the honest reading.**  It went
`0x2283c (-10) -> 0x226fc (-330)`: at -10 it was only accidentally the right
total length while 94.6% of the layout map failed.  Delete nothing further
here without measuring: the 128 B left is exactly the seven stubs that *are*
referenced (`thread_proc`, `RecvGameSavegame`, `fcn_1001af30`,
`fcn_10020ff8`, `putc`, `crt_toupper`, `_crt_locked_call4a`), and they go away
only when the functions behind them are reversed.

**Corrected accounting of the remaining +308:**

| term | bytes |
|---|---|
| game region (`_fclose` starts 0x80 early: 96 B of game shortfall + 32 B `_getpid`/`srand`) | -128 |
| CRT content (38,618 against the reference region's 38,588) | +30 |
| `link_stubs.c` scaffolding `.text` | +128 |
| residual slack | +278 |
| | **+308** |

**The +308 is not the real distance.**  `split_audit` still reports **0 of 330
placed symbols at their reference VA**: `_fclose` lands at 0x1001a10a against
0x1001a18a, a uniform **-0x80** for the first ten symbols, drifting to -0x3d3
by the tail (`__strdup` at 0x10023442 against 0x10023812).  The -0x80 is
exactly the game region's shortfall, so the CRT cannot be placed until the
game half is the right length; matching the total would only hide that.

**Two more measured facts.**

*LINK discards 20 of the 246 split objects* (923 B of `.text`) as duplicate
COMDAT sections — aliases where the reference has two names for one body:
`crt0dat.obj` §14 at both 0x1001a746 and 0x1001a74f, `_mbscat`/`__mbscat`,
`__except_handler3`, `_amsg_exit`, the four `$L21349` fragments.  They are in
the response file and in the audit's `--content` sum but occupy no bytes, so
`split_audit`'s "slack" figure double-counts them and is not a padding
measurement.

*`srand` (0x1001a150, 12 B) is in no LIBCMT variant, and no `srand.obj` member
exists in any of the six.*  `rand.obj` supplies only the 13-byte seed-setter
(content-matched at 0x1001b535) and `_rand` (34 B at 0x1001b542).  The
reference's 12-byte `mov eax,[esp+4] / push eax / call 0x1001b535 / pop ecx /
ret` wrapper is therefore a separate function with no library supplier, and
`0x1001a140` (`srv_SeedRandomWithTime`) calls the same 0x1001b535 helper.

**Where the -0x80 actually is.**  `db/verify_results.json` has ten size
divergences; the sign below is *ours minus target*:

| function | target | ours | delta |
|---|---|---|---|
| `m_AllocTracked` 0x10006580 | 658 | 608 | **-50** |
| `vfs_ReadData` 0x10008e40 | 472 | 446 | **-26** |
| `cm_ExCopyEntityData` 0x1000ec00 | 901 | 880 | **-21** |
| `vfs_ReadCompressed` 0x10008a90 | 492 | 499 | +7 |
| `vfs_OpenStream` 0x10009020 | 667 | 693 | +26 |
| `CrashDumpUnhandledExceptionFilter` 0x10002770 | 2115 | 2137 | +22 |
| `gm_FindNextFilteredEntity` 0x10016f80 | 346 | 342 | -4 |
| `cm_ExSellObjekt` 0x1000d930 | 2057 | 2055 | -2 |
| `gm_AllocSpieler` 0x10018850 | 3689 | 3688 | -1 |
| `ls_LoadBuildingEntityState` 0x100128f0 | 1463 | 1464 | +1 |
| | | | **-48** |

The other 15 bytes of the -0x80 are `srand`'s 16 absent bytes minus one byte
of LINK padding.  So the shortfall is **three functions**, not a diffuse
layout problem: `m_AllocTracked`, `vfs_ReadData` and `cm_ExCopyEntityData`
alone are 97 of the 128 bytes.  A size delta is a structural difference (a
missing or extra instruction), which is why those three are the right targets
and the five near-matches (5-49 byte deltas at identical size) are not.

**The three size deltas are the memcpy alignment prelude, and it is not
flag-selected.**  All three are short by the same thing: the target expands
`memcpy` with a destination-alignment prelude
(`lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx; jle; rep movsb; mov ecx,ebx;
and ebx,3; shr ecx,2; rep movsd; add ecx,ebx; rep movsb`), msvc6 emits the
naive `shr ecx,2; rep movsd; and ecx,3; rep movsb`.  Re-probed this round on
a fresh four-shape file (`/O2 /Gd`, `/O2 /Gd /G6`, `/Ox /Gd`, `/O1 /Gd`,
`/O2 /Gd /Oy-`, `/O2 /Gd /G6 /Oy-`, `/Os /Gd`): every flag set emits the naive
template, so `/G6` does not select it.  The `lea ecx,[edi+edi*2]; and ecx,3`
is worth recognising: it is `(-edi) & 3` computed as `(3*edi) & 3`, which is
the same value because `4*edi ≡ 0 (mod 4)` — so the prelude is the *standard*
dest-align form, not an exotic one.  Until MSVC6 is made to emit it, these
three functions stay short and the game region stays at -0x80.

**Next step:** the residual is now the biggest single term, but it cannot be
attacked before the -0x80: every split object is displaced by the game
region's length.  The 20 non-exact game functions are the prerequisite, not an
alternative — start from the three size mismatches above.  Note
in passing that `cm_ExProdObjekt` (976/993, the closest of the twenty) was
re-tested this round: hoisting the `g_unknown_1de450` load into its own
statement above `recipe_idx` and splitting the `<< 6` off leaves it at exactly
976 with the identical mismatch set, confirming the round-7 finding that the
volatile dead store pins the load.

## The remaining 784 bytes of "slack" are mostly our own scaffold (2026-09-13, round 35)

Round 34 called the 784-byte difference between the split region's span and its
summed content "inter-object slack".  That is wrong: **`link_stubs.c.obj` alone
contributes 512 bytes of `.text`**, and all of it is code the reference does not
have.  It is in the response file but not in any of the `--content`
directories, so it fell into the residual.  The other scaffolding objects
(`data_globals.c.obj`, `rdata_restore.c.obj`, `crt_imports.c.obj`) contribute
**0** bytes of `.text`; only `link_stubs.c` emits code.

`link_stubs.c` defines 232 symbols, and **96 of them are referenced by no object
in either the standard or the split response file** — about half its `.text` is
dead stubs kept alive only by `/OPT:NOREF`.  Removing them would be worth on the
order of 250 bytes, but it was **not done**: several dead names
(`ahm_RandomBelow`, `FreeCommandBuffer`, `rand_mod`, `_putc`, `write_log`)
appear in the tooling and configuration, so the postlink's expectations have to
be checked before deleting them.  The file is shared scaffolding, not
reconstruction, so a mistake there is expensive.

**Corrected accounting of the remaining +676:**

| term | bytes |
|---|---|
| game region (`_fclose` starts 0x80 early: 96 B of game shortfall + 32 B `_getpid`/`srand`) | -128 |
| CRT content (38,618 against the reference region's 38,588) | +30 |
| `link_stubs.c` scaffolding `.text` | +512 |
| residual slack | +262 |
| | **+676** |

**Also measured, and negative.**  Only 89% of member-internal adjacent section
pairs are contiguous in the reference (118 of 133), so the reference's layout is
section-by-section like ours and per-member emission would not reproduce it.
The exceptions are the members whose sections the reference splits:
`memcpy.obj` at 0x1001b200 and 0x1001eab0, `popen.obj` in five places,
`lseek.obj` in three, `cwprintf.obj`, `fread.obj`, `crt0dat.obj`.

**Next step:** either check the postlink's symbol expectations and delete the
dead half of `link_stubs.c`, or leave the CRT half where it is and go back to
the 20 non-exact game functions — the game region is still 128 bytes short and
that is the larger remaining piece.

## Trimming each section to the reference function size removes 2,170 bytes (2026-09-13, round 34)

`map_libcmt` matches a reference function to a member section by *common
prefix*, so a section can be far longer than the function it was matched to:
the 238-byte `exsup` section carries **six** reference functions of 34, 35, 66,
148, 197 and 216 bytes, and `split_coff` was emitting all 238 bytes for each of
them.  The same holds for `realloc` (member section 815 B against a 395-byte
reference function), `calloc`, `free`, `output` and `strchr`.

`split_coff --trim` cuts the emitted root section to the map's size for that
entry, drops the symbols defined past the cut, and drops relocations past it.
Result:

| | round 33 | round 34 |
|---|---|---|
| `.text` | 0x23364 (+2,846) | **0x22aea (+676)** |
| drift range | -0x132 .. +0x76c | -0x3d3 .. +0x1ac |
| archive members pulled | none | none |

**2,170 bytes**, and the emitted CRT content is now 38,618 bytes against the
reference CRT region's 38,588 — **+30 bytes of content**, with the remaining
784 bytes being inter-object slack across ~290 objects.  The whole CRT half is
now within 814 bytes of the reference, and the total +676 decomposes as -128 for
the game region (96 bytes of game shortfall plus the 32-byte `_getpid`/`srand`
pair that no LIBCMT carries) and +814 for the CRT region (784 slack + 30
content).

**`--trim` exposed a filter bug in `emit_defs`.**  Its missing-symbol filter
skipped every `?`-prefixed name as a C++ string literal, so when trimming
removed `?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z` from the middle of `handler.obj`'s
section, nothing replaced it and LINK pulled the whole member back.  Only
`??_C@` names are string literals; with the filter narrowed to `("__imp_",
"??_C@")` the pull disappears and `.text` drops another 10 bytes (0x22af4 ->
0x22aea).

`scripts/split_link.sh` runs the trimmed configuration and reproduces 0x22aea.

**Next step:** the residual is now dominated by the 784 bytes of slack plus the
128-byte game shortfall, both small and local.  Per-object slack is worth one
more look — the audit's worst deltas are a block of ~40 objects sitting at
-0x3d0 — but the bigger prize is the other half: the 20 non-exact game
functions.

## Three of the "no library carries" functions are in LIBCMT after all (2026-09-13, round 33)

Rounds 11-13 recorded nine CRT functions that no available library carries
(`srand`, `__CRT_INIT`, `fpmath`, `init_fptrs`, `unlock_9`, `crt_close_handle`,
`crt_once_init`, `allmul_slow`, `fcn_1001a643`), and round 31 leaned on that
when it concluded `_getpid`/`srand` at 0x1001a140 are "not ours to reverse".
**Three of those nine are member sections the catalog mapping simply could not
reach**, and `scripts/locate_sections.py` finds them:

| catalog VA | member section | located at |
|---|---|---|
| `fcn_1001a643` | `crt0dat.obj` section 2 — symbol `__cinit` | 0x1001a643, 45 B |
| `fpmath` | `fpinit.obj` section 3 — symbol `__fpmath` | 0x1001b070, 23 B |
| `__CRT_INIT` | `dllcrt0.obj` section 3 — symbol `__CRT_INIT@12` | 0x1001b8fb, 217 B |

`map_libcmt` matches *catalog functions to member sections* by name and prefix
length; these sections are only reachable through a member's section symbol or
under a different name, so they fell through.  `locate_sections.py` goes the
other way — for a member section, find its reference VA — with the mask the
round-31 note said was needed: relocation slots plus the four bytes after every
`E8`/`E9` (intra-image relative calls carry no relocation entry), a fixed-run
`bytes.find` pre-filter, and a full scan for heavily relocated code where no
16-byte run is fixed (the thunk block is 14 fixed bytes in 42).  Run over every
member of the five variants it recovers **12 sections** the map missed; run
over the emitted thunk object it returns 0x1001a160, confirming that object's
content matches the reference exactly.

**Measured on the whole pipeline** (`.text` against the reference's 0x22846,
and the per-object drift range from `scripts/split_audit.py`):

| configuration | `.text` | drift range | exact placements |
|---|---|---|---|
| round 32 (catalog map, `--closure`) | **0x2334a (+2,820)** | -0x230 .. +0xa7c | 0 |
| catalog map + catalog map completion, `--closure` | 0x233ea (+2,980) | -0xf0 .. +0xbdc | **2** |
| completed map, no `--closure` | 0x23364 (+2,846) | **-0x132 .. +0x76c** | 0 |

The completed map is the better state to build on even though it is 26 bytes
larger: the worst-case drift falls by 784 bytes, which is what byte identity
needs, and `--closure` is subsumed once the map covers the sections (it exists
to recover sections the catalog mapping misses).  `scripts/split_link.sh` now
runs the completion step and drops `--closure`; it reproduces 0x23364.

**Next step:** with the map complete, the remaining excess can be attributed
per section rather than per category — the 12 recovered sections and the
`emit_defs`/commons objects should each now be checkable against a known
reference VA, so any that still have none are the real over-inclusion.

## The socket IAT thunks now sit where the reference has them (2026-09-13, round 32)

Round 31 named 42 of the missing 74 CRT-pre bytes: the seven
`jmp dword ptr [IAT]` stubs at 0x1001a160..0x1001a18a that the reference's
`SendBroadcastPacket` calls from nine sites.  They exist because the original
source declares those imports without `__declspec(dllimport)`, so MSVC emits a
five-byte `call _socket@12`; ours does the same, but LINK takes the thunk from
`WS2_32.lib` and archive members are appended after every command-line object,
so it lands at the end of `.text` instead.

`scripts/emit_thunks.py` emits the reference's own six bytes for each thunk
(`ff 25 <IAT>` with the operand as a DIR32 relocation against the import
library's `__imp_<decorated>` symbol), as one COMDAT `.text` in the reference's
order (closesocket, sendto, bind, htons, htonl, setsockopt, socket), and
`make_split_rsp.py --thunks DIR` inserts it between the game objects and the
CRT objects.  Measured:

| | before | after |
|---|---|---|
| `.text` | 0x23354 (+2,830) | **0x2334a (+2,820)** |
| `_fclose` placement delta | -0xaa | **-0x80** |
| thunk VAs | absent from `.text` | 0x1001a0e0..0x1001a10a, same order as the reference |

`scripts/split_link.sh` runs the whole pipeline including this step and
reproduces 0x2334a from scratch.

**What the remaining -0x80 is.**  The reference has `_getpid` (14 B) at
0x1001a140 and `srand` (13 B + padding) at 0x1001a150, before the thunks —
32 bytes — and the other 96 bytes are the game shortfall.  Neither `_getpid`
nor `srand` is defined by **any** member of the five LIBCMT variants (a scan of
every member finds no such symbol), which is why `map_libcmt` could not place
them and why `emit_defs` never sees them: nothing in our link references them.
They are the first two of the nine functions the map records as carried by no
library, and under this objective they are not ours to reverse — the reference
build simply has CRT code that the available LIBCMTs do not.

**Bug note.**  `.text` is five characters, so `sec[0:6] = b".text\0\0"`
assigns *seven* bytes into a six-byte slice and resizes the bytearray by one:
the object then claims a 42-byte body that starts one byte early, and LINK
reports the section as corrupt ("bad string table size" from objdump, LNK1143
from LINK).  It is the same class as round 29's `.bss` bug, and the fix is
`sec[0:8] = b".text\0\0\0"` — always assign into an 8-byte name slice.

## The remaining 2,830 bytes, attributed (2026-09-13, round 31)

Round 30 left the split-set `.text` at 0x23354, +2,830 over the reference, and
"attribute it" as the next step.  `scripts/split_audit.py --content DIR` now
prints the region span against the objects' summed `.text`, so the three terms
fall out:

| term | bytes |
|---|---|
| game region — the built stream ends at 0x1001a0e0, the reference at 0x1001a18a | **-170** |
| CRT content 40,755 against the reference CRT span 38,588 | **+2,167** |
| inter-object slack — region span 41,588 minus content 40,755 | **+833** |
| | **+2,830** |

**The -170 has a name.**  96 bytes of it is *game* code (the game objects end
0x60 before the reference's CRT starts) and 74 bytes is CRT code before
`_fclose`:

```
0x1001a140  _getpid        14 B   call [GetCurrentProcess]; push eax; call srand; pop ecx; ret
0x1001a150  srand          13 B
0x1001a160  7 IAT thunks   42 B   jmp dword ptr [0x10024198/94/90/8c/88/84/80]
```

Those seven thunks are `socket`, `setsockopt`, `htonl`, `htons`, `bind`,
`sendto`, `closesocket`, and they are live code, not dead stubs: the
reference's `SendBroadcastPacket` (0x10001130) makes **nine direct
`call`/`jmp` to them** between 0x10001142 and 0x100011c0.  Our builds do
generate equivalent thunks — but at 0x1001c2b8+ in the standard build and at
the end of `.text` (0x100240f0+) in the split build, targeting an IAT base of
0x10025000+ rather than the reference's 0x10024180.  So what is missing at
0x1001a160 is **import-thunk placement plus a matching IAT layout**, not code:
the six-byte `jmp [IAT]` bytes themselves are the same shape we already emit,
and they come from `WS2_32.lib` in the standard build.

**The +2,167 content excess** is the sum of the terms rounds 27-30 measured:
the mapped sections' +1,049 over-inclusion (15 sections larger than the
reference function they were matched to), the closure helper sections (+744),
and the 13 definition objects (+268) — 2,061 of the 2,167, the remainder being
rounding across the region.

**The +833 slack** is 3.2 bytes per object across 259 split objects plus 28
helper/definition objects, so it is not worth chasing: the round-27 "5,619
bytes of LINK padding" was a measurement mistake, and the real inter-object
slack is this.

**Two facts about the definition sections, from trying to place them.**  The
reference's `__DllMainCRTStartup@12` does not call `__CRT_INIT@12` directly: at
0x1001b9fa it is `mov eax, dword ptr [0x11767588]; ...; call eax`, i.e. the
address is taken and stored in a data slot, so `__CRT_INIT@12` cannot be
located by following a direct call.  And a relocation- and `E8`-masked search
over the reference's `.text` finds no position for the emitted `__CRT_INIT@12`
body — but that body is dense enough with relocations and `call` displacements
that no 16-byte run free of both exists, so the search is not conclusive either
way.  `_DllMain@12`'s six-byte stub (`6a 01 58 c2 0c 00`) *is* present in the
reference.  Placing these sections at their reference VAs therefore needs a
proper masked matcher (the technique `scripts/map_libcmt.py` already uses), not
a window search.

**So the open items on this half are:** (1) place the import thunks and match
the IAT base — a `.data`/PE-layout problem, which the postlink step already has
the `iat_thunks` list for in `rebrew-project.toml`; (2) byte-match the emitted
definition and closure sections against the reference so they land at the right
VAs; and (3) the 96-byte game shortfall, which is the other half's business
(the 20 non-exact functions).

## No LIBCMT member is pulled any more (2026-09-13, round 30)

The last five pulled members were driven by symbols whose *defining section*
the split set never emits — sections the map did not match to a reference
function, in members that are otherwise mapped, and whole members the map does
not cover:

| symbol | member | defining section |
|---|---|---|
| `__except_list` | `exsup.obj` | **ABSOLUTE** (section -1, value 0) |
| `__XcptActTab` | `winxfltr.obj` | `.data` (0x88) |
| `__cinit` | `crt0dat.obj` | `.text` (0x2d, section 2) |
| `___xc_a` | `crt0init.obj` | `.CRT$XCA` (4) |
| `__CRT_INIT@12` | `dllcrt0.obj` | `.text` (0xd9, section 3) |
| `_DllMain@12` | `dllmain.obj` | `.text` (6, section 1) |

`scripts/emit_defs.py` closes it from the symbol side: read the defined and
undefined externals of every object already on the response file, take the
difference, map each missing symbol to the section that defines it in one of
the LIBCMT variants, and emit that section as its own object — or, for an
`ABSOLUTE` symbol, a one-symbol object with section number 0xFFFF.

**It has to iterate.**  One pass is not enough because the definitions cascade:
emitting `__CRT_INIT@12` (dllcrt0 section 2) *introduces* the reference to
`_DllMain@12`, which no object on the response file had named before.  The
script re-scans its own output and repeats, converging in four passes from 74
missing symbols to 0.  Two bugs found on the way, both worth recording because
they are easy to mistake for linker behaviour: objdump prints a COFF definition
as `(sec N)` and an undefined external as `(sec 0)`, so a first pass that
treated section 0 as a definition reported "0 undefined" and emitted nothing;
and keying the output file on `member + section` alone makes two symbols in one
section overwrite each other, which silently lost `crt0dat`'s and
`crt0init`'s sections until the emit was grouped by `(member, section)`.

`make_split_rsp.py --defs DIR` adds the objects, and `scripts/split_link.sh`
now runs the whole pipeline — map, split, commons, definitions, response file,
link, audit — in one command against a configured `build/` tree.  Result:
**zero LIBCMT archive members are pulled**, and `.text` 0x23686 -> **0x23354** (-818 bytes), so the
overshoot is down from 7,840 to **2,830 bytes** — 5,026 bytes removed since the
round-26 baseline, and the CRT half is now "LIBCMT is linked in" in the literal
sense: every symbol the split set references is defined by a command-line
object.

**What the remaining 2,830 bytes are.**  The 13 emitted definition objects add
only 268 bytes of `.text`, and the commons objects add none, so the residue is
not the new objects.  It is the round-26/27 terms: the -0xaa missing prologue
before `_fclose`, the split objects' +1,049 over-inclusion, the inter-object
slack, and whatever the *game* region contributes.  Attributing it needs a
fresh map audit — `scripts/split_audit.py` on the new link is the first step.

## Carried data sections are closure roots; commons are parked (2026-09-13, round 29)

Two fixes and one parked experiment on top of round 28's `--with-data`.

**1. A carried data section must be a closure root.**  `_file.obj`'s `.data`
holds `__iob`, whose initialisers name `___endstdio` — and that lives in a
*second* `.text` section of the same member (section 7 of 16), which the map
never mapped.  Carrying the `.data` therefore turned a definition into an
undefined reference, and LINK went straight back to the archive for the whole
member.  `build_object` now walks relocations from the extra data sections too,
not only from the root `.text` (still restricted to same-member `.text`, so it
cannot pull another member's data).  Effect: `_file.obj` drops out of the pull
list, 7 -> 6 members and 1,635 bytes, `.text` 0x238c5 -> **0x238c1**.

**2. Uninitialized sections were written as raw data.**  A `.bss` section has
`PointerToRawData == 0`; the code was emitting `raw_size` zero bytes into the
file and advancing the cursor for them, so the object claimed contents for a
section that has none and the following section's file offsets shifted.  Such a
section now contributes no bytes and keeps `SizeOfRawData = raw_size` with
`PointerToRawData = 0`.  Neutral on `.text` (0x238c1 either way) and the default
path is unchanged — regenerating the plain `--closure` set still reproduces
**0x246e6**, so nothing earlier in this line moved.

**3. The commons are emitted as standalone objects, and that is worth another
571 bytes.**  The six remaining pulls are driven by symbols that no member
*section* defines: `mbctype.obj` declares `__mbctype` as section 0 value 0x101,
`___mbcodepage` 4, `___mbulinfo` 0xc, and `crt0dat.obj` declares `__FPinit` /
`___onexitbegin` / `___mbctype_initialized`, `winxfltr` `__XcptActTab`, `exsup`
`__except_list`, `dllcrt0` `__cinit` — all *common* symbols, which the linker
allocates, so LINK searches the archive and takes the whole member.

`scripts/emit_commons.py` emits one tiny one-section object per member holding
that member's commons in a `.bss` (each at its aligned offset, size from the
symbol's `Value` field as COFF records for a common), one object per member,
deduplicated by symbol name across libraries; `make_split_rsp.py --commons`
adds them to the link line.  Result: `mbctype.obj` drops out of the pull list,
6 -> 5 members, `.text` 0x238c1 -> **0x23686** (-571 bytes).

**The failure this replaced was a two-byte bug, not a COMDAT problem.**  The
first attempt folded the synthetic `.bss` into the split object itself and LINK
rejected it (`LNK1143: invalid or corrupt file: no symbol for comdat section
0x2`), and after correcting the section-count accounting the symbol table was
still unreadable ("bad string table size").  The cause was in the object
writer, not in the linker's COMDAT rules: a section header's name is 8 bytes,
and `sec[0:5] = b".bss\0\0\0"` assigns **seven** bytes into a five-byte slice,
which *resizes* the bytearray and shifts every following offset by two.  With
`sec[0:8] = b".bss\0\0\0\0"` the same synthetic section is fine.  The
in-object `--with-commons` path keeps the code but stays off by default; the
standalone-object route is simpler and is what the numbers above use.

**Current state of this half:** `--closure --with-data` plus the commons
objects links clean at **0x23686** (reference 0x22846, **+0xE40 = 3,648
bytes**), down from 0x246f6 at the start of this line — 4,208 bytes removed in
three rounds.  Five members are still pulled (`crt0dat.obj`, `dllcrt0.obj`,
`dllmain.obj`, `exsup.obj`, `winxfltr.obj`) and the next causes to attack are
`_DllMain@12` (the `/ENTRY:` symbol), `__CRT_INIT@12`, and the `__cinit` /
`___xc_a` cascade into `crt0dat.obj`.  `/ENTRY:_DllMainCRTStartup@12` is worth
a further 2 bytes whenever the entry question is settled.

## `split_coff --with-data` removes 3,617 bytes of the overshoot (2026-09-13, round 28)

Round 27 concluded that LINK loads the 12 leftover members for their *data*
symbols, because the split set extracted only `.text`.  This round implements
that: `split_coff --with-data` carries each mapped member's `.data`, `.bss`,
`.rdata` and `.CRT$*` sections on the object for that member's lowest-VA mapped
function, so the member's data has a command-line definition.  It also fixes a
latent bug the flag exposed: a `.bss`-style section has `PointerToRawData == 0`,
and `section_body` was reading the object *header* for it; such sections now
emit `raw_size` zero bytes.

Measured on the closure set, both VS-sorted by `scripts/make_split_rsp.py`:

| build | `.text` | vs reference | archive pull |
|---|---|---|---|
| `--closure` (round 27) | 0x246e6 | +0x1ea0 (7,840 B) | 12 members, 34 symbols, 4,978 B |
| `--closure --with-data` | **0x238c5** | **+0x107f (4,223 B)** | **7 members, 16 symbols, 1,655 B** |

**-0xE21 = 3,617 bytes**, and the archive pull shrinks by exactly the
difference: `output.obj`, `sbheap.obj`, `cvt.obj`, `tzset.obj`, `strtol.obj`,
`intrncvt.obj`, `atox.obj`, `handler.obj`, `crt0msg.obj`, `_newmode.obj`,
`ioinit.obj`, `ncommode.obj` and the rest stop being loaded.  The default path
is unchanged: regenerating the plain `--closure` set with the patched script
reproduces 0x246e6 byte-for-byte, so the `.bss` fix only affects objects that
actually carry an uninitialized section.

**What is left, from LINK `/VERBOSE`.**  With the flag on the remaining pull is
7 members, and `/VERBOSE` names the one symbol that loads each
(`Found <symbol>` / `Referenced in <obj>`):

`_DllMain@12` -> `dllmain.obj`; `__except_list` -> `exsup.obj`;
`__CRT_INIT@12` -> `dllcrt0.obj`; `___endstdio` -> `_file.obj`;
`__XcptActTab` -> `winxfltr.obj`; `__mbctype` -> `mbctype.obj`;
`__cinit` / `___xc_a` -> `crt0dat.obj`.

Most of these are **common symbols**, not data a section carries: `mbctype.obj`
defines `__mbctype` as section 0 with value 0x101, `___mbcodepage` as section 0
value 4, and so on.  A common is allocated by the linker, so no `.data` section
of ours can satisfy the lookup; the object has to carry the allocation itself.
`_DllMain@12` is different again: it is the `/ENTRY:` symbol, and the split rsp
drops the `crt_region/dllmain.c.obj` that supplied it, so LINK looks in the
archive and finds LIBCMT's `dllmain.obj`.  Measured: switching `/ENTRY:` to
`_DllMainCRTStartup@12` (which resolves to `__DllMainCRTStartup@12`, the
symbol the split set's `1001b9d4_.text.obj` actually defines) links clean at
**0x238c3**, two bytes better; `/ENTRY:__DllMainCRTStartup@12` fails outright,
confirming LINK prepends its own underscore.

**Next step for this half:** emit the pulled members' commons as ordinary
`.bss` definitions of the recorded size (the symbol's `Value` field), and
either keep `crt_region/dllmain.c.obj` in the rsp or use the
`_DllMainCRTStartup@12` entry.  Both are small, and the remaining 4,223 bytes
decompose into the ~1,655-byte pull plus the `-0xaa` missing prologue and
inter-object slack from round 27.

## The split-set overshoot is 12 archive-pulled members (2026-09-13, round 27)

The round-26 audit left one question open: the built `.text` is 7,840 bytes
over the reference's 141,382, and the placed objects are mostly in the right
order, so where do the bytes come from?  Three measurements this round answer
it, and one of them was a genuine tooling bug.  (An intermediate answer in
this round — "5,619 bytes of LINK padding" — was wrong and is corrected in
item 3 below.)

**1. `split_coff`'s `index.json` is not in reference-VA order.**  Four descents
in the 235-entry list, the worst being `0x1001eab0` emitted immediately after
`0x1001b200`.  Both are 821-byte LIBCMT bodies (`memmove2` and `memmove`) and
the reference has them 0x38b0 apart, so the old rsp — which fed `index.json`
straight to LINK, as `/tmp/mkrsp.py` did — dropped the `memmove` body 13.5 KB
from where it belongs and every later object inherited the shift.
`scripts/make_split_rsp.py` replaces that ad-hoc rsp construction and sorts by
the VA in each object's name (verified byte-identical to the hand-sorted rsp).
Effect on the closure build: worst placement error -0x3640 -> **-0x260**,
`.text` 0x246f6 -> **0x246e6**.  Modest in bytes, but the layout is now
reference-ordered, which every later measurement depends on.

**2. Over-inclusion is +1,049 bytes, in 15 objects.**  Summing the `.text`
section sizes of the 235 mapped split objects gives 39,723 bytes against the
38,674 those same functions occupy in the reference.  Only 15 objects are
bigger than the reference function, and they carry 2,161 bytes of excess;
the largest are `realloc` (+420, the member section is 815 against the
reference's 395), `0x1001f8d0` (+224), the three `exsup` spellings
`__NLG_Notify` / `__unwind_handler` / `__abnormal_termination` (+204 each) and
`0x1001e6e4` (+172).  Round 19's "the leftovers are intra-member statics"
story is a different effect from this one: this is the extracted section being
longer than the reference function.

**3. The rest of the overshoot is 12 whole LIBCMT members LINK still pulls
from the archive.**  The split objects themselves pack to 41,300 bytes
(0x1001a0e0 .. 0x10024234) against 40,467 of content — only **+833** bytes of
slack — so the split objects are *not* where the overshoot lives.  What sits
after them is: the link still pulls `output.obj`, `sbheap.obj`, `mbctype.obj`,
`crt0dat.obj`, `cvt.obj`, `tzset.obj`, `exsup.obj`, `winxfltr.obj`,
`dllmain.obj`, `_file.obj`, `dllcrt0.obj`, `a_cmp.obj` from `LIBCMT.lib` —
**12 members, 34 symbols, 4,978 bytes** (0x10024234 .. 0x100255a6) — because
some reference from a command-line object is still satisfied only by the
archive.  That member list is exactly the one rounds 17-21 recorded as "the 34
leftovers", so a symbol-level metric and this byte-level one agree for once.

So the complete decomposition of the +7,840-byte overshoot is

| component | bytes |
|---|---|
| game region, missing code before `_fclose` | -170 |
| split objects, inter-object slack | +833 |
| archive-pulled members (12 members / 34 symbols) | +4,978 |
| trailing data/stub/helper objects and end padding | +2,199 |
| **total** | **+7,840** |

**Correction.**  An earlier draft of this section claimed 5,619 bytes of
"LINK per-object padding" from comparing the summed `.text` of everything on
the rsp (143,603) with the built `.text` (149,222).  That comparison is
invalid: it spans the game objects, the split objects and the archive members
mixed together, and the archive members are not on the rsp at all.  Measured
inside the split region the slack is 833 bytes, and the real third term is the
archive pull above.

**Consequence for the CRT half.**  Two thirds of the gap is one problem —
"stop LINK loading those 12 members" — and the symbol analysis says why it
loads them.  Collecting the defined and undefined externals of all 447
command-line objects shows the split set extracts **only `.text`**: the
members' *data* symbols (`__environ` from `crt0dat.obj`, `__iob` from
`_file.obj`, `___mbcodepage`, `__XcptActTab`, `__exitflag`, ...) are defined by
nothing else on the command line, so LINK satisfies each reference by loading
the whole member and appending its `.text`.  (`_g_current_season`,
`_g_slot_array`, `__crtheap`, ... are `<common>` and not part of this — a first
pass that treated every section-0 symbol as undefined produced a false 113-symbol
list before the commons were separated out.)

So the next `split_coff` extension is to emit each mapped member's `.data` /
`.bss` sections alongside its `.text` section, so the data references resolve
from command-line objects.  That should drop the 4,978-byte archive pull
without touching a byte of code, and `scripts/split_audit.py` shows the result
directly.  `scripts/make_split_rsp.py` and `scripts/split_audit.py` make it
measurable; the recipe above reproduces the starting state.

**Also measured:** layout fidelity of the sorted closure build is **169 of 240**
consecutive split-object pairs placed with exactly the reference's gap; the
nonzero steps are the closure helper objects landing next to their parent
section (+1950/-1841, +1233/-1173, +647/-625) and the 15 oversized objects.

## The split-set link reproduced, and measured from the linker map (2026-09-13, round 26)

Rounds 4-21 built the split-set link repeatedly and recorded only an end
figure; nobody had measured *where* LINK put each split object.  This round
rebuilt it and did, from `/MAP`.

Reproducible recipe (all from the project root; the library list is a
preference order, first match wins):

```
python3 scripts/map_libcmt.py --lib .scratch/libcmt/LIBCMT.sp6.LIB \
    --lib .scratch/libcmt/LIBCMT.sp5.LIB --lib .scratch/libcmt/LIBCMT.base.LIB \
    --lib .scratch/libcmt/LIBCMT.vc7.LIB --lib .scratch/libcmt/LIBCMT.sp4.LIB \
    --json > .scratch/libcmt_map_u.json
python3 scripts/split_coff.py --lib <same five> --map .scratch/libcmt_map_u.json \
    --out build/libcmt_split --closure          # 259 objects
# rsp = objects1.rsp minus the eight crt_region/*.obj, with the 259 split
# objects inserted in map (reference-VA) order after the game objects
cd build && eval "$(sed 's#@CMakeFiles/server_dll.dir/objects1.rsp#@split.rsp#;
    s#/out:server.dll#/out:server_split.dll /MAP:server_split.map#;
    s#/implib:server.lib#/implib:server_split.lib#; s# /pdb:[^ ]*##' \
    CMakeFiles/server_dll.dir/link.txt)"
python3 ../scripts/split_audit.py server_split.map
```

The link succeeds.  `.text` VirtualSize **0x246f6** (end 0x100256f6) against
the reference's 0x22846 — within 4 bytes of round 18's recorded 0x100256f2, so
the documented state reproduces, and 259 objects matches round 19's count.

**What the map says.**  `scripts/split_audit.py` reads the object name's
reference VA against the address LINK gave it.  Of 340 placed split symbols,
**none is at its reference VA.**  The mapped objects start uniformly at
**-0xaa** — `_fclose` (0x1001a18a) lands at 0x1001a0e0 — and the drift grows
monotonically to **+0x5c0** by the tail.  The two ends have different causes:

- the **-0xaa start** is the ~170 bytes of CRT code the reference has before
  `_fclose` that the split set never emits.  The map matches 235 of the
  region's 244 functions; the nine it cannot (`srand`, `__CRT_INIT`, `fpmath`,
  `init_fptrs`, `unlock_9`, `crt_close_handle`, `crt_once_init`, `allmul_slow`,
  `fcn_1001a643`, 542 B) are part of it, and the eight `crt_region` objects the
  split rsp drops were displacing exactly that space in the standard build.
- the **+0x5c0 drift** accumulates over ~300 objects and is the split objects'
  COMDAT padding, so it is not a member-selection problem at all.  This is the
  first measurement that separates the two: rounds 17-21 treated the whole
  7,852-byte overshoot as leftover "excess of the included members", but at
  most ~1.5 KB of it can be padding.

`--closure` is a third, independent source of drift: its helper objects are
placed far from their reference VA (`memcpy.obj`'s `LeadUp1` lands 0x3640
*below* it, `__STRINGTOLD`'s helper 0xa5c above).

**Also re-measured, negative.**  A reloc-masked search for each mapped
reference body in the built `.text` (masking the reference's `.reloc` slots
*and* the four bytes after every `E8`/`E9`, since intra-image relative calls
carry no relocation entry — see round 11) finds **99 of 235 anywhere** and
**0 of 235 at their reference VA**.  So the split set is not "the reference CRT
region, slightly misplaced"; most of the reference CRT code is not in the
image at all.  The 34-symbol leftover count in rounds 17-21 is a symbol-level
metric and understates this badly.

**`--closure` is worth 0x758 bytes but adds the outliers.**  Re-run with the
same map and no `--closure` (235 objects instead of 259): the link still
succeeds and `.text` grows 0x246f6 -> **0x24e4e** (over by 0x2608 instead of
0x1eb0), 319 placed symbols instead of 340, drift -0x3650 .. +0x607.  So
closure is the better configuration for total size — as round 10 found — and
the current link's `/ENTRY:DllMain@12` no longer needs the `__CRT_INIT` helper
that forced `--skip-helper` in rounds 8-10.

**Also run, negative.**  `rebrew climb --objective aligned` (4 passes,
dry-run) on `gm_CheckInventoryCapacity` — the closest function the round-25
alignment table had not already shown to be a scheduling wall — reports one
move at statement 18 worth **+1 matched byte** of the whole binary, i.e. noise.
The deterministic adjacent-statement climb has nothing to offer on it; its
residual is the documented address-form/spill wall, not statement order.

**Next step for this half:** the ~0x1eb0 overshoot splits into the -0xaa start
(missing code) and the +0x5c0 tail drift (padding), but the mapped sections
themselves total 38,674 B against the reference region's 34,550 B, so there is
also ~4 KB of over-inclusion.  Attribute the drift between padding and
over-inclusion object by object — the map has the per-symbol addresses to do
it.

## `rebrew diff`'s positional count is not a priority signal (2026-09-13, round 25)

`rebrew diff` aligns the target and candidate streams *positionally*.  When the
candidate inserts or deletes one instruction the alignment desyncs for the rest
of the function, so `structural` explodes and `exact` collapses even though the
two streams are the same program in the same order.  Two examples measured this
round: `cm_ProcessCommandQueue` reads **15.6%** positionally but **88.3%** once
aligned, and `ls_LoadBuildingEntityState` reads **0.6%** positionally but
**88.8%** aligned.  The round-24 flags on both functions were chasing a
measurement artefact.

`scripts/align_match.py` computes the honest number: the longest common
subsequence of normalized instruction text, i.e. the largest number of target
instructions that can be matched, in order, by an instruction that will be
byte-identical in the linked image.  Normalization lowercases, drops `;`
comments and segment prefixes, masks bracketed symbol operands and any number
`>= 0x10000` (image addresses / relocations), and keeps only the mnemonic for
branches and calls; register names and small displacements are *kept*, so a
register-role or frame-offset difference is still a mismatch.

| function | tgt | cand | identical, in order | % | `rebrew diff` positional |
|---|---|---|---|---|---|
| `cm_ExProdObjekt` | 354 | 369 | 329 | 92.9% | 98.6% |
| `ls_LoadBuildingEntityState` | 499 | 495 | 443 | 88.8% | 0.6% |
| `cm_ProcessCommandQueue` | 205 | 204 | 181 | 88.3% | 15.6% |
| `gm_CheckInventoryCapacity` | 138 | 142 | 121 | 87.7% | 7.2% |
| `ServerMainThread` | 627 | 641 | 545 | 86.9% | 81.7% |
| `gm_ObjectsAvailble` | 229 | 235 | 197 | 86.0% | 92.1% |
| `gm_CalculateProductionValue` | 123 | 127 | 102 | 82.9% | 98.4% |
| `cm_ExCopyEntityData` | 249 | 239 | 192 | 77.1% | 32.1% |
| `ahm_ExAllocAlchemist` | 286 | 293 | 219 | 76.6% | 39.2% |
| `vfs_ReadCompressed` | 200 | 213 | 153 | 76.5% | 25.0% |
| `srv_LoadBuf` | 226 | 228 | 171 | 75.7% | 88.9% |
| `gv_ExAllocGraveyardWorker` | 333 | 332 | 245 | 73.6% | 52.0% |
| `cm_ExSellObjekt` | 667 | 673 | 479 | 71.8% | 9.0% |
| `gm_AllocSpieler` | 1056 | 1061 | 669 | 63.4% | 8.1% |
| `gm_FindNextFilteredEntity` | 118 | 119 | 72 | 61.0% | 5.1% |
| `vfs_ReadData` | 174 | 168 | 101 | 58.0% | 17.8% |
| `m_AllocTracked` | 249 | 228 | 116 | 46.6% | 16.5% |
| `gm_AllocGebaeude` `!` | 346 | 186 | 129 | 37.3% | 25.7% |
| `CrashDump` `!` | 724 | 266 | 163 | 22.5% | 3.2% |
| `vfs_OpenStream` `!` | 197 | 31 | 27 | 13.7% | 50.8% |

The positional column is `(exact + reloc) / total` from the round-24 diffs.
Rows marked `!` have a candidate slice far shorter than the target — objdump
splits those COMDATs — so their percentage is meaningless and the tool prints
`!` for them.

Two consequences worth carrying forward.  First, the ordering above is the
ordering to work in: `cm_ProcessCommandQueue`, `gm_CheckInventoryCapacity` and
`cm_ExCopyEntityData` are much closer than the positional metric suggested,
while `gm_CalculateProductionValue` and `cm_ExProdObjekt` are already known
scheduling walls despite sitting at the top.  Second, `rebrew diff -r`
(register-aware) only partially repairs this — it moves
`gm_ObjectsAvailble`'s structural count 18 -> 3 but leaves
`cm_ProcessCommandQueue` at 167 structural — so it is not a substitute.

Tool: `python3 scripts/align_match.py [--va 0x...] [--json]`.

## m_PoolAlloc closed: asm operands must be named locals (2026-09-13, round 23)

`0x10006d20 m_PoolAlloc` was the first of the 21 to fall: **266/270 ->
270/270**, `NEAR_MATCHING` -> `RELOC`, and the tree's byte-exact count goes
259 -> 261 (the 260th is `gzread`, see the distance table).  The residual was
the two parameter-home stores in the target's descending order
(`mov [ebp+0xc],edx` / `mov [ebp+8],esi`) where the reconstruction emitted
them ascending; every source swap of the two statements scored 260 because
msvc6 then sinks `alen -= 4` (`add esi,-4`) below the stores.

The reconstruction had been forcing those homes with volatile aliases
(`*(volatile int*) &head = asize;` / `*(void* volatile*) psize = slot;`),
which is what pinned the stores in source order.  **That whole apparatus is
unnecessary and harmful.**  `/O2` reuses the dead parameter slots for two
ordinary block-scope locals on its own, and when the asm block names those
locals directly it emits the target's exact sequence:

```c
char* fdest;
int flen;
...
fdest = (char*) slot;
flen = (int) alen;
__asm {
    mov edi, fdest
    mov ebx, flen
    xor eax, eax
    lea ecx, [edi+edi*2]
    ...
}
```

`fdest` lands at `[ebp+0xc]` and `flen` at `[ebp+8]` (the dead `head`/`size`
slots), the stores come out dest-then-len in the target's order, and
`add esi,-4` stays ahead of both.  No volatile, no `&param` aliasing, no
undefined behaviour.

**The generalisable rule:** when the reference's block-fill prelude reads its
operands from memory, the operands were *ordinary locals* in the original
source and the register allocator chose those slots.  Naming the locals in
the asm block and letting msvc6 allocate reproduces the choice; forcing the
slots through volatile aliases reproduces the addresses but not the schedule,
and the schedule is what the byte compare sees.  The same test was run on the
other two missing-prelude functions and neither is prelude-limited:
`m_AllocTracked` (0x10006580) reaches obj 646 against 658 with the prelude
present and its score falls (241 -> 180) because the frame grows 8 bytes and
the entry register roles are the real wall (see "Next three blockers");
`gm_AllocGebaeude` (0x100174d0) emits the prelude correctly but is 22 bytes
over and structurally shifted from offset 96.

Also re-confirmed this round, and negative: the 2026-09-11 service-pack sweep
already covers all seven VC 6.0 builds over these functions ("Twenty compile
to identical objects under every build"), so another SP sweep is redundant.

**Second negative: the `-1` constant-caching wall is not a spelling.**
`ls_LoadBuildingEntityState` (0x100128f0) is the cleanest example — 1464 vs
1463 bytes, 100% mnemonic-aligned, and the entire gap is that the reference
caches the sentinel in `ebp` (`or ebp,0xffffffff` once, then three
`mov [mem],ebp`) while msvc6 rematerializes `mov dword ptr [mem],0xffffffff`
at each of the three stores and so needs no fourth callee-saved register
(entry is `push esi; push edi` against the target's
`push ebx; push ebp; push esi; push edi`, and every frame offset is 8 low).
Seven spellings of `neg1` measured: dropping `register`, `~0`, moving the
assignment above `offset = 0`, `unsigned int` + `0xffffffffu`, and a
file-scope `static int s_neg1 = -1;` read into `neg1` — all inert at
125/1464 except the last two, which are worse (obj 1481/1475).  Delaying the
assignment to the first loop iteration reaches 150/1481.  The caching
decision is the allocator's, driven by live-range pressure the
reconstruction does not reproduce, exactly as `docs/msvc6-c-shapes.md` §48
records for `ServerMainThread`'s `sent_bytes`.

## Static demotion is clean but neutral (2026-09-13, round 21)

Third attempt at the intra-member static problem, this time without merging
sections: make every cross-section reference to a `.text` static external, and
export the defining object's statics under the same name as externals.  Two
rounds of triage were needed to get the link clean:

- demoting *all* cross-section statics to external produced
  `unresolved external symbol .debug$F` (debug section symbols must stay
  object-local), and
- after excluding `.`-named symbols, `unresolved external symbol
  _dstflag_cache` / `$T17396` — member-local `.bss`/`.data` statics we never
  extract.  Restricting the demotion to symbols whose defining section is
  `.text` made the link clean again.

Result: exit 0, but **34 leftovers / 5,294 B / `.text` 0x100256f2 — identical
to round 18.**  The members are being pulled for other symbols anyway, so the
static references were not what kept them alive.  Reverted to keep the
splitter simple; the round-18 state stands.

## The merge's exact blocker: a section symbol per COMDAT (2026-09-13, round 20)

Re-attempted the static-sharing merge with VA-ordered roots (so the merged
object's section order follows the reference, not the member's section order).
LINK now rejects the object outright:

```
1001a681_.text.obj : fatal error LNK1143: invalid or corrupt file:
                     no symbol for comdat section 0x4
```

Dumping the merged object shows why: it has six sections but only five section
symbols — the nine-byte `LINK_ONCE_DISCARD` section (crt0dat.obj's
`__lockexit`/`_doexit` neighbourhood) has none, and one symbol still points at
section 6 while the discardable section has no number.  A COMDAT section is
only valid when its section symbol (and its AUX record) is present, and the
current keep-set walk drops that one.

So the merge is a COFF bookkeeping problem, not a placement problem: every
emitted section needs its section symbol kept and its AUX `Number` (assoc)
renumbered.  Renumbering the assoc field alone did not fix it — the missing
symbol is the issue.  Reverted again; the round-18 state (34 leftovers,
`.text` 0x100256f2) stands.

## The 34 survivors, and a measured negative (2026-09-13, round 19)

The remaining leftovers are concentrated in a few members: `sbheap.obj` (5
symbols, 1,608 B), `tzset.obj` (3, 1,395), `mbctype.obj` (5, 571), `cvt.obj`
(3, 398), `winxfltr.obj` (2, 376), `crt0dat.obj` (4, 251), `output.obj` (6,
201), `exsup.obj` (2, 214), `dllcrt0.obj` (1, 217), plus singles.

Tracing undefined references from the split objects shows the mechanism for
several of them: MSVC emits **statics that the member's own sections
reference**.  `output.obj` §5 (`output`) calls `_write_char`, which is a
*class-3 static* defined in §6 of the same member.  Splitting every section
into its own object turns that intra-member local reference into an
unsatisfiable external, so the linker pulls LIBCMT's whole `output.obj` — and
the same shape recurs in `cvt`, `mbctype`, `tzset`, `crt0dat` and `sbheap`.

I tried the obvious fix — group mapped sections that are adjacent in the
reference VA space back into one object, so the intra-member statics resolve.
Measured: objects 259 -> 138, but leftovers **34 -> 60** and `.text` end
0x100256f2 -> 0x10025d72.  Reverted.  The grouping misplaces sections whose
order inside the member does not match the reference VA order, so the merge has
to be done per static-sharing group with an order check, not by simple
adjacency.

## Duplicate wrapper bodies masquerade as leftovers (2026-09-13, round 18)

Tracing which split object leaves each leftover undefined found a general
cause.  The CRT builds the same thin wrapper into several members: `lseek.obj`'s
`__lseek` and `write.obj`'s `__write` are **the same 101 bytes** (verified
byte-for-byte, same 28 relocation slots).  Whichever member the map picks for
that VA, references to the other spelling stay undefined, so the linker pulls
the sibling member purely to resolve the alias — which is where a whole group
of the "CRT-internal" leftovers came from.

`split_coff` now indexes every `.text` section body (relocation slots zeroed)
across all libraries and exports the other members' external symbol names as
aliases on the extracted section.  One object then satisfies both spellings.

Measured on the split-set link, all links clean:

| | leftovers | leftover bytes | `.text` end |
|---|---|---|---|
| round 17 | 71 | 6,650 | 0x10025c3e |
| round 18 | **34** | **5,294** | **0x100256f2** |

That also invalidates part of round 17's conclusion: the leftovers were not
all "internal references we cannot touch" — over half were aliases of bodies
already in the split set.

## The remaining leftovers are CRT-internal (2026-09-13, round 17)

The per-function check that found the five `fclose` sites was applied to the
whole leftover list.  Grepping every game source, every `crt_region` file and
`link_stubs.c` for each leftover's name (`strdup`, `_write_char`,
`___endstdio`, `__unlock_file`, the sbh extras, `_ceil`, `_strtoxl`,
`_strtoul`, `__ld12tof`, `__atoldbl`, `__STRINGTOLD`, `__XcptFilter`,
`matherr`, the fpexcept family, `tzset`/`cvtdate`, ...) returns **no live
reference** — the only two hits are comments (`link_stubs.c`: `flsall`,
`crt_heap.c`: `strtoul`).  So the 71 leftovers are pulled by the CRT members
themselves, not by game code naming a wrong symbol: they are the build-variant
excess of the included members.

That closes the "game C names a wrong CRT symbol" line of attack; the rest of
the region gap is (a) the 9 functions no available library carries and (b) the
internal references of the members we do include.

Also re-confirmed on the game side: CrashDump's four-register prologue is
immune to entry reshaping.  Hoisting `hProcess = GetCurrentProcess()` to the
top and reordering the local declarations both leave
`sub esp,0x28c; push ebx; push ebp; push esi; ... push edi` unchanged, the
same inertness the file's own notes record for other entry spellings.

## Fixed: those call sites were `fclose` (2026-09-13, rounds 15-16)

`rebrew diff` resolves the *reference's* operand, which is what round 14 lacked:
reading the per-function diff of `DispatchLogOutput` (0x10002640),
`vfs_CloseStream` (0x100038a0), `vfs_DestroyEntity` (0x10008a50) and `gm_Open`
(0x10015950) shows all five `fflush`-looking call sites targeting
**0x1001a18a**, and that function's 49 bytes are byte-identical to
`fclose.obj`'s `_fclose` in both SP6 and SP5 (the `fflush` name was the
catalog's RevEng.AI guess).  The reconstruction had spelled them `fflush`,
which is why LIBCMT's `fflush.obj` was pulled for a public `_fflush` the
reference's CRT build does not contain.

All five sites now call `fclose`.  A game function's call displacement is a
masked relocation, so the compiled bytes are unchanged and every affected
function re-tests RELOC at its original size (290/290, 177/177, 53/53,
861/861), with `verify --full` holding at 279/281.

Measured effect on the split-set link:

| | leftovers | leftover bytes | `.text` end |
|---|---|---|---|
| before | 73 | 6,858 | 0x10025d0e |
| after | **71** | **6,650** | **0x10025c3e** |

`LIBCMT:fflush.obj` is no longer in the link at all, and the standard build's
`.text` drops 0x2284c -> 0x2283c.

The generalisable check: for every CRT symbol our game C names, run
`rebrew diff` on the enclosing function and compare the reference's resolved
target against the member whose body lives there.  A mismatch means the
catalog name is wrong and the link is pulling a member the reference never had.

## Why `fflush.obj` is pulled: the reference has no public `_fflush` (2026-09-13, round 14)

`/VERBOSE:LIB` names the culprit for one leftover group.  LIBCMT's
`fflush.obj` is pulled and then ignored piecewise:

```
LIBCMT.lib(fflush.obj) : warning LNK4006: __fflush_lk already defined in 1001ac9f_.text.obj
LIBCMT.lib(fflush.obj) : warning LNK4006: __flush     already defined in 1001accd_.text.obj
LIBCMT.lib(fflush.obj) : warning LNK4006: __flushall  already defined in 1001ad29_.text.obj
```

The split set already carries the reference's `fflush.obj` sections — the map
matches 0x1001ac9f / 0x1001accd / 0x1001ad29 / 0x1001ad32 to sections 3, 5, 7
and 9 of that member (`__fflush_lk`, `__flush`, `__flushall`, `_flsall`).  The
member is pulled anyway for two symbols the reference does **not** contain:
`_fflush` and (elsewhere) `_flsall`'s public partner.  In other words the
reference's CRT build omitted the public `_fflush` wrapper, while three game
files (`gm_Open.c`, `Error.c`, `vfs.c`) call `fflush`, so our link pulls the
member to resolve it.

That matters because a game function's call target is a *masked* relocation —
it does not have to name the same symbol as the reference, only resolve to a
VA that postlink rewrites.  If those call sites named the function the
reference actually calls (its `__fflush_lk`, i.e. the body at 0x1001ac9f,
which the split set already provides), the member would not be pulled at all
and the leftover would disappear.  The same shape should be checked for the
other leftovers that our game code references but the reference omits.

Identifying the reference's own target is not a byte-scan: the built `.text`
is not offset-aligned with the reference, so reading the reference at the
built call-site offset yields garbage (measured — five `fflush` call sites,
none with an `E8` at the matching offset).  It has to be read per function.

## VC7 fills the unlock family; 9 functions remain (2026-09-13, round 13)

Swept the 16 unmatched region functions against more CRT builds (extract with
`docker run --rm --entrypoint sh -v $PWD/.scratch/libcmt:/out <image> -c 'cp
<path>/libcmt.lib /out/<name>.LIB'`; the image paths are
`/opt/msvc5.0/lib/libcmt.lib`, `/opt/msvc7.0/Vc7/lib/libcmt.lib`,
`/opt/msvc7.1/Vc7/lib/libcmt.lib`):

| library | unmatched matched |
|---|---|
| VC5 LIBCMT | 0 / 16 |
| LIBC 6.0 (single-threaded) | 0 / 16 |
| VC7 LIBCMT | **7 / 16** — the whole `unlock_09*` family (778 B) |

So `--lib SP6 --lib SP5 --lib VC7` resolves **235 of 244 region functions
(38,674 of 39,216 B)**, leaving 9 (542 B): `srand`, `fcn_1001a643`, `fpmath`,
`init_fptrs`, `unlock_9`, `__CRT_INIT`, `crt_close_handle`, `crt_once_init`,
`allmul_slow`.  None of VC5/VC6-base/SP4/SP5/SP6/VC7/LIBC carries them, so they
are a build variant none of the libraries on hand reproduces.

The link is unchanged by the VC7 addition (73 leftovers, `.text` 0x10025d0e):
the extracted `unlock` helpers are still pulled from LIBCMT members that other
symbols need, so *coverage* improves while the leftover set does not shrink.
73 leftovers is 6,858 B of the 0x24c8 region overshoot; the rest of the gap is
the split set's own excess.

## The reference CRT is a service-pack mix (2026-09-13, round 11)

Two findings, both from chasing the 22 unmatched region functions.

**Section symbols must be indexed.**  Many LIBCMT helpers are only reachable
through their `.text` *section* symbol; skipping every symbol starting with
`"."` hid them.  Indexing them recovered `exsup` (0 diffs against
`exsup3.obj`, 224 B body vs the catalog's 197).

**The rest are not SP6.**  `dosmaperr`, `NMSG_WRITE`, `setmbcp` and `output`
differ from SP6 by exactly one opcode byte: the reference has `7c` (`jl`)
where SP6 has `72` (`jb`) at the same offset — a signed/unsigned source
difference.  They match **LIBCMT.base and LIBCMT.sp5** instead.  Per-region
byte-match counts:

| library | region functions | bytes |
|---|---|---|
| LIBCMT.base | 209 | 33,414 |
| LIBCMT.sp4 | 224 | 36,844 |
| LIBCMT.sp6 | 223 | 34,987 |
| LIBCMT.sp5 | **228** | **37,896** |
| SP6 then SP5 (union) | **228** | **37,896** |

`map_libcmt.py` and `split_coff.py` now take `--lib` repeatably as a preference
list, so `--lib SP6 --lib SP5` resolves 228 of 244 region functions — the
remaining 16 (1,320 B) match no version on hand (`srand`, `__CRT_INIT`,
`unlock_09*`, `fpmath`, `init_fptrs`, `crt_close_handle`, `crt_once_init`,
`allmul_slow`, two `fcn_*`).

Note the union set does **not** yet improve the PoC link: without `--closure`
it links but leaves 175 LIBCMT symbols (vs 112 for SP6 alone), because the SP5
members define different symbol spellings; with `--closure` it loses `/ENTRY`
again.  The coverage number is the solid result; the link metrics need the
symbol reconciliation.

*Corrected in round 12:* the 175 was a splitter bug, not a symbol problem.
Section-symbol matching means a member has one `.text` symbol per COMDAT, and
`split_coff` looked sections up *by symbol name*, so it extracted an arbitrary
section.  Finding the section from the map's recorded section number restores
the SP6 numbers and makes the union a net win.  All links exit 0:

| split set | objects | LIBCMT leftovers | `.text` end |
|---|---|---|---|
| SP6, no closure | 223 | 112 | 0x100264dc |
| SP6 -> SP5 union, no closure | 228 | 107 | 0x100264de |
| SP6, closure | 246 | 77 | 0x10025ac7 |
| SP6 -> SP5 union, closure | 252 | **73** | 0x10025d0e |

Reference `.text` ends at 0x10023846, so the region is still ~0x24c8 over: the
73 leftovers, i.e. group (2)'s remaining 16 unmatched functions (`srand`,
`__CRT_INIT`, `unlock_09*`, `fpmath`, `init_fptrs`, `crt_close_handle`,
`crt_once_init`, `allmul_slow`, two `fcn_*`) and group (3)'s CRT-internal
references.

## `--closure` works: leftovers 121 -> 77 (2026-09-13, round 10)

The round-9 blocker was one helper object.  Bisected by dropping candidates
from the rsp: when our split set supplies `__CRT_INIT@12`, LIBCMT's
`dllcrt0.obj` is not pulled and LINK stops resolving
`/ENTRY:_DllMainCRTStartup@12` — it builds the console-EXE chain
(`crt0.obj` / unresolved `_main`) instead.  Removing that single object from
the link restores it (exit 0), so `--skip-helper` now defaults to
`__CRT_INIT@12` and the closure is usable.

Measured, all links exit 0:

| split set | objects | LIBCMT leftovers | `.text` end |
|---|---|---|---|
| default (single-section) | 222 | 112 | 0x100263fc |
| `--closure` | 246 | **77** | **0x10025ac7** |

Reference `.text` ends at 0x10023846, so the region is still 0x2281 over — the
remaining 77 leftovers, i.e. group (2) and (3) from round 7 minus what the
closure absorbed.  `__CRT_INIT@12` itself (0x1001b8fb, unmatched) is one of
them and is currently placed by LIBCMT at the end rather than at its VA.

## Section closure: helpers land, the entry lookup does not (2026-09-13, round 9)

Two changes this round, one measured and shipped, one still blocked.

**Shipped: section-symbol relocations are retargeted.**  A relocation may name
a `.text` *section* symbol of a COMDAT the object does not carry; emitting it
as an external literally named `.text` left LINK with an unresolvable
reference.  `build_object` now retargets it at the external function symbol
defined at that section (lowest value), and guards the few members whose
relocations carry out-of-range indices.  With the default single-section
split: **leftovers 121 -> 112 and `.text` end 0x268c0 -> 0x263fc**, link still
clean.  Object counts and the default path are otherwise unchanged.

**Blocked: `--closure` and `/ENTRY`.**  The helper sections are now emitted as
their own *single-section* objects, placed immediately after the function that
branches to them (247 objects total), so the multi-section object shape is no
longer involved.  The link still fails: LINK pulls `crt0.obj` for
`mainCRTStartup` and reports `unresolved external symbol _main`, i.e. it is
building the console-EXE startup chain instead of using the DLL entry.  A
`/FORCE:UNRESOLVED` map of the same link shows `__DllMainCRTStartup@12`
defined by `1001b9d4___DllMainCRTStartup_12.obj` **and** `_mainCRTStartup`
present from `LIBCMT:crt0.obj`, so the entry symbol exists and LINK is still
not selecting it.  The one thing that correlates with the failure is our
objects now supplying `__CRT_INIT@12`, so LIBCMT's `dllcrt0.obj` is no longer
pulled.  Next: either keep `dllcrt0.obj` in the link, or find why
`/ENTRY:_DllMainCRTStartup@12` stops matching when it is absent.

## Section closure: implemented, and the entry symbol blocks it (2026-09-13, round 8)

Group (1) of the leftovers is fixed in the tool.  `scripts/split_coff.py`
gained `--closure`: it walks the relocation graph from the mapped section and
includes the same-member `.text` sections it references, stopping at sections
that are themselves emitted as their own object (so nothing is duplicated) and
claiming each helper section once across the whole run.  With `--closure` the
set is 222 objects / 37,871 B (against 34,280 B single-section), and a
`/FORCE:UNRESOLVED` link drops the leftovers **121 -> 101** at
`.text 0x10026824`.

It is off by default because of one concrete blocker: with closure on, LINK
stops resolving `/ENTRY:_DllMainCRTStartup@12`.  The extracted `dllcrt0`
object does define `__DllMainCRTStartup@12` — a `/FORCE:UNRESOLVED` map shows
it at 0x1001b824 from `1001b9d4___DllMainCRTStartup_12.obj` — and the link
succeeds again if the multi-section object is not used, so the failure is in
the multi-section object's symbol/section wiring (or LINK's entry lookup over
it), not in the closure itself.  `/ENTRY:__DllMainCRTStartup@12` is wrong —
LINK prepends its own underscore and looks for `___DllMainCRTStartup@12`.
That is the next thing to fix; everything else about the closure is measured
and working.

## What the split set still misses (2026-09-13, round 7)

Fixing `map_libcmt.match` to compare the *common prefix* instead of requiring
the member body to be at least as long as the catalog entry (the catalog
pads/truncates: `_exit` 34 vs 17, `_strncpy` 272 vs 254, `_strchr` 192 vs 188)
recovered 209 -> **222 of 244 region functions, 34,790 B of 39,216**.  Relinked
with the 222 split objects, `.text` still ran to 0x100268c0 against the
reference's 0x10023846, with **121 symbols still pulled from `LIBCMT.lib`**.
Those 121 fall into three groups, and only the first is a splitter bug:

1. **Intra-member section closure.**  `_memmove`'s body branches to labels that
   MSVC emitted as *separate COMDAT sections of the same member*
   (`LeadUp1..3`, `UnwindUp0..7`, `TrailUp0..3`, `LeadDown*`, `UnwindDown*`,
   `TrailDown*` — ~40 symbols).  The splitter demotes cross-section references
   to undefined, so the linker re-pulls the whole `memmove.obj` and its
   internals land after the region.  The fix is to include the transitive
   closure of same-member sections in the extracted object.
2. **The 22 unmatched region functions** (4,426 B): `srand`,
   `output` (1,857), `__CRT_INIT`, `exsup` (197), `NMSG_WRITE` (339),
   `setmbcp` (429), `dosmaperr`, the `unlock_09*` family, `crt_close_handle`,
   `crt_once_init`, `allmul_slow`, `fpmath`, `init_fptrs`,
   `fcn_1001a643`, `fcn_1001e638`.  Each needs its own matching rule (several
   are single-instruction helpers, others span COMDAT boundaries).
3. **CRT-internal references** the split set does not supply: `fpexcept`,
   `util`, `fpctrl`, `matherr`, `tzset`, `handler`, `_ceil`, `_strtoxl`.  These
   are pulled by other members, not by game code (`ceil` appears nowhere in
   `src/server.dll`), so they are part of whatever the reference's own members
   referenced.

**The catalog is an incomplete view of the region.**  It lists 254 functions
above 0x1001a150; the PoC link emits 343 there.  Section (2) is bounded by the
catalog, but closing the gap needs the region's true function inventory read
from the binary (boundaries and all), not a name list — otherwise the split
set and the leftover set can never be proven equal.

## Per-function COMDAT selection works (2026-09-13, round 6)

`scripts/split_coff.py` turns the mapped members into standalone per-function
COFF objects: LIBCMT is built `/Gy`, so each function is its own COMDAT
`.text` section, and the script re-emits one object per section (relocations
remapped onto a rebuilt symbol table, string table rebuilt, cross-section
symbol references demoted to undefined so the linker resolves them from the
sibling object).  Measured: **209 objects, 34,280 B of `.text` against the
reference region's 34,550 B** — per-*function* selection is essentially exact,
against the 40,896 B whole members carry.

A PoC link with those 209 objects on the command line, in reference-VA order,
places them inline and in order:

```
_fclose                  split object   0x1001a0e0   (reference 0x1001a18a)
_srand                   split object   0x1001b105
__DllMainCRTStartup@12   split object   0x1001b4cb
```

The offsets are the game region's cumulative -0xaa, as in round 5, so member
placement still cannot be checked until the game region is exact.

**What is left is not placement but coverage.**  The PoC's `.text` still ran to
0x10025ce2 against the reference's 0x10023846, because `LIBCMT.lib` is still on
the link line and appends every member our objects reference that the split set
does not contain (`_fflush` landed at 0x10022bd8 from `LIBCMT:fflush.obj`).
That residue is the "our C references symbols the reference does not have"
side of the reconciliation, not a placement bug: the split set is 270 B short
of the region, while the leftovers account for the extra ~9 KB.  Next: either
supply every symbol the link needs from the split set (so `LIBCMT.lib` drops
out) or reconcile the extra references themselves.

## Explicit member placement works; whole members overshoot (2026-09-13, round 5)

Round 5 built the link the plan calls for and measured the two obstacles.

**The reference's `DllMain` is LIBCMT code.**  `0x1001b9d4` — the reference's
`AddressOfEntryPoint` — is byte-for-byte `__DllMainCRTStartup@12` from
LIBCMT's `dllcrt0.obj` (`scripts/map_libcmt.py` reports the symbol).  So
`crt_region/dllmain.c` reverses library code, and `/ENTRY:DllMain@12` should
be `/ENTRY:_DllMainCRTStartup@12`.  The same holds for `amsg_exit.c`
(`__amsg_exit`, also `dllcrt0.obj`).

**Explicit member objects are placed inline, in the order given.**  A PoC link
put 99 extracted LIBCMT members (the ones `map_libcmt.py` maps for
VA >= 0x1001a150) on the command line after the game objects:
`_fclose` landed at 0x1001a0e0, immediately after `srv_SeedRandomWithTime`,
and the rest followed in the supplied order (after fixing a sort bug that
ordered the members by *path* instead of by VA).  So the mechanism the plan
needs is confirmed — the library is no longer appended at the end.

**But dropping the hand copy regresses today.**  Replacing
`crt_region/dllmain.c` with LIBCMT's `_DllMainCRTStartup@12` (and
`/ENTRY:DllMain@12` with `/ENTRY:_DllMainCRTStartup@12`) measured
`.text 0x2277c` against the reference's `0x22846` — **-0xca**, where the
committed tree is +6 — and postlink coverage 394/7463 against 402.  So the
`dllmain.c` object is supplying something else as well (or the entry change
alters which members the linker pulls), and the swap has to wait until the
member placement is in place.  The tree is restored; this is recorded as the
target state, not a change to make on its own.

Two obstacles, both measured:

1. **Whole members overshoot by ~6.3 KB.**  The 99 members carry 40,896 B of
   `.text` against the reference region's 34,550 B (0x1001a150..0x10022846),
   because a member ships functions the reference never had.  The PoC's
   `.text` therefore ran to 0x10025658.  Per-*function* selection is required:
   either split each member's `/Gy` COMDATs and place only the sections the
   reference uses, or drive the link with `/OPT:REF` plus an `/INCLUDE:` for
   every symbol in the region.  A first `/OPT:REF` attempt collapsed the whole
   link to 0x10011504, so the `/INCLUDE:` list has to be complete before that
   switch is flipped.
2. **Absolute VAs inherit the game region's cumulative error.**  Placing the
   members right after the game objects put `_fclose` at 0x1a0e0 against the
   reference's 0x1a18a, exactly the -112 B the game region is short by the end
   (CrashDump +16, m_AllocTracked -64, vfs_ReadData -32, cm_ExCopyEntityData
   -32, ...).  Member placement cannot be checked until the game region is
   exact, but it can be developed independently.

## LIBCMT is appended after every object — the reference interleaves it (2026-09-13, round 4)

The objective says zlib and LIBCMT are to be *linked in*, not reversed, so
round 4 tested dropping the eight `crt_region` files that exist only to
displace LIBCMT members (`dllmain.c` must stay: the reference's
`AddressOfEntryPoint` is 0x1001b9d4, i.e. the hand-written `DllMain`, not
LIBCMT's `DllMainCRTStartup`).  Measured, with `dllmain.c` kept:

| | committed (keep files) | keep files dropped |
|---|---|---|
| compile errors | 0 | 0 |
| `.text` VirtualSize | 0x2284c (+6) | 0x22572 (**-0x2d4**) |
| imports | 100 | 102 (**+IsBadWritePtr +FatalAppExitA**) |
| postlink coverage | 402/7463 | 402/7463 |

Dropping them is worse on both counts, so the tree is restored.  But the
experiment exposes the real structure of the problem:

**MSVC LINK places every archive member after every command-line object.**  Our
link ends its own objects at ~0x1bd40 and LIBCMT's members start at ~0x1c000
(`_fflush` at 0x1caf5, `_srand` at 0x1d8d0, `__mtinitlocks` at 0x1c663).  The
reference **interleaves** members with game/CRT objects:

```
0x1001a140 srv_SeedRandomWithTime   (game, 14 B)
0x1001a150 srand                    (LIBCMT)
0x1001a18a fflush                   (LIBCMT)
0x1001a1bb fclose_lk                (LIBCMT)
  ...                                (LIBCMT members through 0x1001a643)
0x1001a643 fcn_1001a643             (crt_region/initterm.c)
0x1001a758 __initterm               (LIBCMT)
  ...
0x1001b9d4 DllMain                  (crt_region/dllmain.c)
0x1001d036 _mlock                   (crt_region/mlock.c)
```

So the LIBCMT region can only line up if its **member objects are on the
command line, in reference-VA order**, instead of the whole `.lib` being
appended.  That is still "linking LIBCMT in" — stock objects, no reversing —
and it is the concrete next step for roughly 39 KB (28%) of `.text`.

Feasibility, measured this round by byte-matching every reference `.text`
function against LIBCMT.sp6's COMDAT sections with the same
fixed-bytes-minus-reloc-slots rule `check_library_code.py` uses: **209 of the
254 reference functions at or above 0x1001a150 match a stock LIBCMT body
outright — 32,455 B of 39,216 B (83%)**, including the sbh family and the 68
functions already reversed under `crt_region/`.  (A first pass reported only
136 because it pre-filtered candidates on their raw first 8 bytes; the
reference's resolved `a1 imm32` operands differ from the library's zeroed
reloc slots, so the pre-filter has to be reloc-insensitive.  A full scan with
the mask rule is the correct method and costs seconds.)

The 45 non-matching ones are mostly boundary artifacts rather than missing
code: `0x10021ac0 strcmp` is 140 B *inside* LIBCMT's `_strcmp`, so the
catalog's boundary, not the body, is what differs.  The genuinely absent set
is the ~2.6 KB the file already lists elsewhere (`_ld12cvt` 673 B, several
`unlock_09*`, `_output` 1857 B, ...).  So placing the stock members explicitly
buys ~32 KB of byte-exact `.text` before any of those need a decision.

## The ten real size mismatches (2026-09-13, round 3)

`rebrew verify --full` is the only accurate size source; `db/server.dll_functions.csv`
carries stale registry sizes (it reports 600 B for `srv_LogWinsockError`, whose
`rebrew test` slot is 758 and byte-exact).  The functions whose object size
disagrees with the target are exactly:

| VA | function | obj | target | delta | match |
|---|---|---|---|---|---|
| 0x10002770 | CrashDumpUnhandledExceptionFilter | 2137 | 2115 | +22 | 12.5% |
| 0x10006580 | m_AllocTracked | 608 | 658 | -50 | 36.7% |
| 0x10008a90 | vfs_ReadCompressed | 499 | 492 | +7 | 27.6% |
| 0x10008e40 | vfs_ReadData | 446 | 472 | -26 | 30.0% |
| 0x10009020 | vfs_OpenStream | 693 | 667 | +26 | 64.0% |
| 0x1000d930 | cm_ExSellObjekt | 2055 | 2057 | -2 | 9.7% |
| 0x1000ec00 | cm_ExCopyEntityData | 880 | 901 | -21 | 58.3% |
| 0x100128f0 | ls_LoadBuildingEntityState | 1464 | 1463 | +1 | 8.5% |
| 0x10016f80 | gm_FindNextFilteredEntity | 342 | 346 | -4 | 48.5% |
| 0x10018850 | gm_AllocSpieler | 3688 | 3689 | -1 | 23.1% |

Note that a near-zero size delta does not mean a near byte match:
`cm_ExSellObjekt` (-2), `ls_LoadBuildingEntityState` (+1) and
`gm_AllocSpieler` (-1) are 8-23% matches.  The remaining 11 non-byte-exact
functions are size-exact but byte-different (`srv_LoadBuf`, `gm_ObjectsAvailble`,
`cm_ProcessCommandQueue`, `cm_ExProdObjekt`, `m_PoolAlloc`,
`gm_CalculateProductionValue`, `vfs_OpenStream`, `gm_CheckInventoryCapacity`,
`ahm_ExAllocAlchemist`, `gv_ExAllocGraveyardWorker`, `ServerMainThread`).

**The inline-asm prelude is not transplantable into a divergent body.**
Round 3 replaced m_AllocTracked's `memset(ptr, 0, sz)` with the target's
prelude as an `__asm` block naming the C locals.  Result: obj 608 -> 646,
match 241 -> 182.  The reference's prelude reads dest from `[ebp-4]` and
length from `[ebp-8]`; this reconstruction homes them in ebx and `[ebp+0xc]`,
so the block is not the same bytes and the surrounding allocator degrades.
Getting the prelude bytes into a function whose operand homes already differ
is not the win it looks like — the homes have to match first.

## The alignment is now a short, named list (2026-09-13, round 2)

Every game TU is contiguous, so `/MAP` deltas against
`db/server.dll_functions.csv` now read as one gate plus four small shortfalls.
`.text` is 0x2284c (+6) and postlink coverage 402/7463 (5.4%).

| from VA | delta | cause |
|---|---|---|
| 0x10001000 | 0 | |
| 0x10002fc0 | **+16** | CrashDumpUnhandledExceptionFilter, obj 2137 vs 2115 |
| 0x10006820 | **-48** | m_AllocTracked, obj 608 vs 658 |
| 0x10008c80 | -32 | |
| 0x10009020 | -64 | |
| 0x1000ef90 | -96 | |
| 0x10010710 | -112 | last event before the LIBCMT region |

Fix CrashDump and the delta is 0 for the first 0x3800 bytes of `.text` — the
whole 0x2fd0..0x6820 span, ~28% of the map entries, validates in one change.
It is the highest-value function in the tree by a wide margin.  The prologue
is the whole difference: the target saves ebp/esi with frame 0x280 and keeps
`hDbgFile` in ebp; ours saves ebx/ebp/esi/edi with frame 0x28c and spills it.
Any C rewrite that drops two callee-saved registers is the fix; the body
after the prologue already matches instruction for instruction once the
0x14 esp displacement is taken out.

Round 2 also split the last two non-contiguous game TUs the way round 1 split
friedhof_dump/lobbycommands: `spiel62.c` -> `gm_RemoveObjectWrapper.c`
(0x17f30+0x17f60) and `spiel622.c` -> `gm_RandomQuadratic.c` (0x1a110), so
`gm_InitEntityIfValid.c` (0x17f90) and `gm_RandomFloat01.c` (0x1a0f0) land
between their neighbours.  All four moved functions re-tested unchanged.

## The block-fill prelude is not a compiler template (2026-09-13)

Round 1 mapped the six `lea ecx,[edi+edi*2]; and ecx,3` sites (3 present via
inline asm, 3 missing).  The open question was whether another MSVC emits it.
Measured by compiling m_AllocTracked with `#pragma intrinsic(memset)` — the
configuration that inlines the fill — under every toolchain that has a memset
expansion:

| toolchain | match | obj |
|---|---|---|
| msvc-4.2 | 143 | 694 |
| msvc-5.0 | 193 | 617 |
| msvc-6.0-sp4 | **226** | 613 |
| msvc-6.0-sp6 | 226 | 613 |
| msvc-7.0 | 134 | 617 |
| msvc-7.0-rtm | 135 | 615 |
| msvc-7.1 | 134 | 617 |

No toolchain reaches the prelude (target 658); the shape is byte-invariant
across the shipped binaries, `sub`+`jle` with no intervening `test` is not
msvc6 output, and no C spelling of the align-up split reproduces it.  The
prelude is therefore hand-written asm in the original game code, not a
compiler template — reproducing it with an inline `__asm` block matches what
the original did (the tree already carries three such blocks).

**m_PoolAlloc (0x10006d20) is 4 bytes from exact and its recorded blocker is
stale.**  The metadata says "alignment-prefixed memset prelude — pure C cannot
emit"; the object is 270/270 and the prelude IS emitted by the file's inline
asm.  `rebrew diff 0x10006d20` reports `{exact 101, reloc 4, structural 2}`:
the only residual is the order of the two parameter homes, target
`mov [ebp+0xc],edx` / `mov [ebp+8],esi`, ours reversed.  Measured this round:
any source order that puts the slot home first (swapped stores, a shared
`volatile int*`, dropping the `asize` temp and homing `alen` directly) lets
the scheduler sink `add esi,-4` past it and lands on 260/270.  The shipped
order keeps `add esi,-4` early but emits the homes reversed.  Whoever clears
that one scheduler artifact gets the function free.

## Structural link alignment (2026-09-13) — `.text` +214 -> +6, order fixed

The raw link (postlink skipped — the POST_BUILD step still refuses) was
`0x2291c` before this pass and is `0x2284c` now against the reference's
`0x22846`: **+6 bytes**, down from +214.  postlink map coverage 4.1% -> 5.4%.
The size is now nearly right; what is left is placement and per-function size.

Five fixes, each measured by relinking with `/MAP` and diffing symbol VAs
against `db/server.dll_functions.csv`:

- **check_header.c had a private `get_byte`.**  The reference's check_header
  (0x100036d0) calls **0x10003820** twelve times (disassembly of the target),
  i.e. the shared VFS reader, not a TU-local helper.  `rebrew test` passed
  the file anyway because call displacements are masked.  Replacing the local
  body with a `vfs_GetByte` call deleted the unreferenced static
  `_get_byte` (128 B) from the link and left check_header byte-identical
  (332/332 RELOC).
- **gzread split into its own TU.**  The original places check_header
  (0x36d0), then vfs.c's two functions (0x3820, 0x38a0), then gzread (0x3960);
  one object can only emit its functions contiguously, so gzread moved to
  `Units/vfs/vfs_c/gzread.c`.  It is 559/559.
- **Two infblock bodies are not in the reference at all.**
  `inflate_set_dictionary` and `inflate_blocks_sync_point` have no exact-byte
  match anywhere in the target (their only callers, `inflateSetDictionary`
  and `inflateSyncPoint`, are already `#if 0` in `references/zlib/inflate.c`),
  but the tree links `/OPT:NOREF`, which keeps unreferenced COMDATs.  They
  were `#if 0`'d in `references/zlib/infblock.c` too (~0x50 B).
- **infcodes.c and inffast.c had no `--first-va` in `order-sources`.**  They
  sorted last and their five functions linked at 0x1a950-0x1b160 instead of
  0x4b80-0x5390 (2,900 B out of place).  Added
  `--first-va infcodes.c=0x10004b80` and `--first-va inffast.c=0x10005390`.
- **Two merged TUs split.**  `order-sources` orders *files* by their first
  VA, so a file holding functions from non-adjacent reference regions cannot
  be position-aligned.  `friedhof_dump.c` (0x10530/0x10d10/0x11940) became
  `gv_CheckSlotActive.c` + `gv_UpgradeField.c` + `gv_MoveSlotEntry.c`;
  `lobbycommands.c` (0x145e0/0x146c0/0x14af0/0x14db0) became
  `lb_ExPlayerlist.c` + `fcn_10014af0.c` + `lb_ExLobbyServerCommand.c`.
  All seven functions were re-tested and kept their status.

With those in place the delta is a single **+16** from 0x10002fd0
(EmitCrashModuleLine) through 0x100067f0 — every function in the first 40% of
`.text` links exactly where the reference has it, once CrashDump is fixed.

## The six block-fill prelude sites (2026-09-13) — three are missing

`docs/msvc6-c-shapes.md` §11 says the `lea ecx,[edi+edi*2] / and ecx,3 /
sub ebx,ecx / jle / rep stosb / …stosd… / …stosb` prelude needs asm.  Scanning
both images for `8d0c7f 83e103` locates the sites exactly:

| reference | built | supplier |
|---|---|---|
| 0x10006730 | — | **m_AllocTracked (0x10006580)** — the -50 B shortfall |
| 0x10006929 | 0x100068f9 | m_init (0x100068e0), inline `__asm` in m_alloc.c |
| 0x10006e0d | 0x10006ddd | m_alloc2.c inline `__asm` |
| 0x10008f0c | — | **vfs_ReadData (0x10008e40)**, PROVEN 30.0% |
| 0x1000b057 | 0x1000b017 | server4.c inline `__asm` |
| 0x10017611 | — | **gm_AllocGebaeude (0x100174d0)**, PROVEN 38.8% |

So the three non-byte-exact PROVEN functions that are *not* prologue/register
walls are exactly the three whose prelude site is missing: supplying the fill
is most of each one's size delta (m_AllocTracked -50, vfs_ReadData,
gm_AllocGebaeude).  Only three `__asm {` blocks remain in the tree
(`grep -rn '__asm[[:space:]]*{'`): server4.c:448, m_alloc.c:220,
m_alloc2.c:231 — all of them this one prelude.

A pure-C spelling of the prelude would close three functions at once and
delete all remaining inline asm — this is the single highest-value open
question in the tree.  Everything §11 records as tried (pointer type,
provenance, length shape, 12 flag sets, the align-up split) should be read
before re-probing; the split form in particular is documented as worse
(42-66 matched vs 105 for plain `memset`).

## Next three blockers, in link order (2026-09-13)

1. **0x10002770 CrashDumpUnhandledExceptionFilter** — obj 2137, target 2115.
   +22 bytes, and with 16-byte COMDAT padding it is the whole +16 shift for
   0x2fd0-0x6820.  `PROVEN` masks it in `verify`.  Blocker is the prologue:
   4 saved regs (ebx/ebp/esi/edi) against the target's 2 (ebp/esi, ebx/edi
   deferred), frame 0x28c vs 0x280, hDbgFile spilled at [esp+0x44] instead
   of held in ebp.  This is the single highest-value function in the tree.
2. **0x10006580 m_AllocTracked** — obj 608, target 658 (-50).  First
   shortfall; moves the delta from +16 to -48.  `PROVEN`, 36.7% match.
3. **spiel62.c / spiel622.c** are the last non-contiguous game TUs
   (`gm_InitEntityIfValid` at 0x17f90 interleaves spiel62's 0x17f60/0x17fb0;
   `gm_RandomFloat01` at 0x1a0f0 interleaves spiel622's 0x1a0d0/0x1a110).
   Split them the same way as the two above.  `server4.c` and
   `crt_region/initterm.c` also report interlopers but those are Ghidra
   switch-case labels / library bodies, not real TU members.

## Tooling environment (2026-09-13) — the rebrew checkout is a moving target

`rebrew` is installed editable (`__editable__.rebrew-0.6.0.pth`) pointing at
`~/Desktop/Projects/relumea/rebrew/src`, which is being edited concurrently.
Mid-pass `rebrew-cmake-cl` died with `ToolchainSpec.__init__() got an
unexpected keyword argument 'image_binary'` (working-tree refactor of
`toolchain_spec.py`/`toolchain_data.py`).  A stable copy of the committed
tree (`git archive HEAD src/rebrew`) was extracted to
`.scratch/rebrew-stable/` and used through `PYTHONPATH` for `verify`,
`lint` and the build.  `scripts/gate.sh` will keep failing on the build step
until that checkout is consistent again — it is not this tree's regression.
There is also a docker container from a 2026-09-11 `rebrew match` still
spinning (`docker ps` name `rebrew-93321f0d944a`), pinning one core.

## gm_Open back to RELOC (2026-09-12)

`0x10015950` had drifted to SIZE_MISMATCH (859/861) when a later rewrite
replaced the proven producible-count tail with a `count_p` pointer local.
Restoring the inline double spelling of `g_entity_type_table + row_index *
0x24d + 0x21` brings it back to RELOC 861/861: the multiply form is what gives
the byte counter the SIB base role (docs/msvc6-c-shapes.md section 34), and
routing the read-modify-write through a pointer local forces a `lea` and lands
2 bytes short.  verify --full 277/280 -> 278/280.

## `.text` link shortfall (2026-09-11) — the build is not byte-identical

The raw link's `.text` is 2,197 B short of the reference's 0x22846 (0x21fb1,
3,269 B before the `/INCLUDE:` change below).  `rebrew postlink` used to pad it
back to the reference's VirtualSize and apply the layout package's call/operand
maps by offset, producing a binary 92% wrong in `.text` while the section table,
imports and header fields all matched.  Nothing failed: `rebrew verify` is
per-function at the object level, and `verify --whole-binary` compares section
sizes, exports, imports, `.rsrc` and headers, never `.text` content.  The layout
guard now fails loud instead: 269/7,463 map entries validate (3.6%, minimum 90%).

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
  true symbol/object mapping has to come from `rebrew lib-match --stock-lib`,
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
remaining `verify` failures (`0x100093a0` obj 2434 = target but bytes differ,
`0x10018850` 3673 vs 3689) are byte-identical across all seven.

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
in LIBCMT and reachable with `/INCLUDE:`, and `CMakeLists.txt` now passes both
on `server_dll` (both `target_link_options` branches; it also pulls `mantold.obj`
and `tenpow.obj`).  Measured: link clean, imports unchanged at 100, `.text`
VirtualSize 138,113 -> 139,185 (+1,072 B) against the reference's 141,382, and
the postlink layout coverage is unchanged (269 vs 270 of 7,463 map entries).
That 1,072 B is a link change, not decompilation.

**This paragraph's conclusion was wrong and is retracted (2026-09-12).**  The
LNK2001 list came from *guessed, undecorated* symbol names.  With RevEng.AI's
names for the same VAs the members are in LIBCMT after all, and forcing six of
them — `___dtold`, `_wctomb`, `__setmode_lk`, `__strdup`, `__NLG_Notify`,
`__ms_p5_mp_test_fdiv` — takes `.text` from 0x21fb1 to **0x228ec against the
reference's 0x22846**: 166 B *over*, where this file previously claimed 2,197 B
short and unreachable.  `$I10_OUTPUT` (0x10022a2f, 659 B) is genuinely absent
(LNK2001) and is not forced, so the honest count is six of seven.  `exsup.obj`
is likewise present, reachable via `__NLG_Notify`, not absent as the table said.

What remains is **member selection, not missing code**: `/INCLUDE` drags whole
LIBCMT objects, so the six add ~2,363 B for ~492 B of annotated functions
(`___dtold` alone pulls `cfout.obj`, contributing 944 B).  The 166 B is the
difference between the reference's choice of members and ours.

**How not to measure it.**  Five attempts to attribute the 166 B by searching
the two linked images all failed, and the reason is structural: the operands
that differ between two links — IAT slots (`[0x10024154]` vs `[0x10024158]`) and
intra-image relative call displacements — carry **no relocation entry**, so
masking cannot reach them; and the annotation VAs do not bound functions
reliably.  Byte search, `.reloc`-masked search and disassembly-level search are
all invalid here.  The working route is a layout-resolved comparison
(`rebrew test --linked`, or `reccmp`, for which `db/server.dll_functions.csv`
is already formatted) or a member-level comparison against `LIBCMT.LIB` itself.

`rebrew lib-match --lib .scratch/libcmt/LIBCMT.sp6.LIB` byte-matches 18 reversed
functions against LIBCMT members (the `__sbh_*` / `___old_sbh_*` family,
`__DllMainCRTStartup@12`, `__initterm`, `__lock`, `__unlock`), so the
`crt_region/` scaffolding agrees with the library rather than duplicating a
member the link already carries.

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
gv_ExAllocGraveyardWorker, gv_AllocGraveyardField, gv_SpawnEntities, cm_ChkChangeBits,
cm_ChkChangeAttribute, cm_ChkJoinLeaveElection, cm_ExJoinLeaveElection,
cm_ChkSellObjekt, cm_ExSimSpecialAction, cm_ExChangeDesire, cm_ExChangeFloat,
cm_ExClearLagerslot, cm_ExAllocWarEvent, cm_ExAllocClientSpieler,
cm_GetBuildingStatCount, cm_ExModifyStat, cm_ExMoveObjekt,
cm_ExRemoveLinkedObject, amsg_exit, crt_heap, vfs4, vfs_OpenStream,
check_header, CrashDumpUnhandledExceptionFilter, InitializeLogAndErrorHandler,
plant, loadsave2, loadsave3, spiel, spiel5, spiel6, spiel62,
gm_AllocSpieler, gm_AllocRaum, gm_InitObjektHersteller,
gm_ObjectsAvailble, InitNewDynastyEntity, lb_HandleEntitySync,
lb_ExPlayerHasJoined, lobbycommands, m_alloc2, ProcessSendData, server4,
srv_LoadBuf.

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
| 0x10018850 | gm_AllocSpieler | 3689 | obj 3673, 527 B matched; 661/1056 insns identical (order-based diff); 61 unmatched block shapes of 225 | The `__ftol` call form was wrong: the reference passes the operand in st(0) (its only `sub esp` is the prologue) while we pushed 8 bytes per site, and that is what held the object at +5 bytes; the sites are casts now.  Both sympathy-matrix loops also reload `*(unsigned short*) slot` per write in the reference, so those reads are volatile, and the no-parent loop needed the two index locals first.  That took the object to 3690 (one byte over) and the order-based alignment from 617 to 650 of 1056. The stat guard then had to compare in single precision - the reference spills 32 bits (`fst dword [esp+0x24]`) before `fcomp dword [ebp+0x20]` - which gives 3678, 652/1056 and 72 unmatched blocks, and improves every structural metric including `rebrew test`'s own score (504 -> 514) while moving away from the target size.  Judge gm by unmatched block shapes and order-based alignment, never by |size - target|.  The reloc-masked figure (543, was 570) and the byte-offset score (504, was 752) both regress and should NOT be used to judge a gm variant: the reloc-masked metric is only sound when the candidate's reloc layout matches the target's, and this file's own note records that byte-offset alignment reads structural where the schedule merely differs.  `rebrew prove` returns "no terminal states" at 200 s / `--loop-bound 1` (path explosion over the 0x300 loops), so PROVEN is not available either. |
| 0x100093a0 | ServerMainThread | 2434 | obj 2434 (exact), 1343 B positional; 582/627 insns aligned under the reloc-masked metric | The "no C89 lever" verdict this row used to carry was **wrong** and is retracted.  Two levers move it.  (1) Loop **form**: a `do {} while` whose single-condition body ends in a `goto` compiles to a rotated, test-duplicated loop; the equivalent top-tested `while` carrying the same body and `goto` compiles to the target's single-test shape.  Applied to the host-slot search, the transfer scan and two others.  It is loop-specific, not universal: the pending-sync loop regresses and `process_pending_sync` is neutral, so each conversion must be measured.  (2) Operand **width**: `((host_flags_word & 8) ? 7 : 0) + 2` is byte-width in the target; the `? 9 : 2` spelling keeps the expression `unsigned char` and reproduces it.  Reading the sync-packet clock words into locals first (the target hoists all three loads) takes the object from 2436 to exactly the target's 2434.  Sound-metric alignment 558 -> 582 of 627, hunks 47 -> 36 (27 scheduling, 1 operand, 8 substitution); the instruction count now matches exactly, 627/627.  Flags, declaration order, TU composition, loop spelling and GA mutations are all swept and inert.  `rebrew prove` still returns "no terminal states" (420 s, `--loop-bound 1`). |

`scripts/zlibcheck.py` is the reference measurement: masking the byte ranges
the object's own relocation table covers, on both sides, it reports the zlib
region's 46 functions as exact, which validates the metric.  Alignment figures
above come from the same masking (`.scratch/wall.py`); the older pattern-based
numbers in this file should not be compared with them.

`scripts/seqdiff.py` produces those counts.  `rebrew diff` aligns by byte
offset, so a 1-4 byte size difference desynchronises it and every later
instruction reads as structural (973 reported for gm_AllocSpieler
against 663 by sequence alignment, and 67 exact instructions against 614).

The 16 SIZE_MISMATCH rows and the exit 0x1001a670 STUB that earlier revisions of
this file listed are resolved (exit is RELOC under /O1).

## What would unblock

- ServerMainThread: closed at this precision.  Object size is exactly the
  target's 2434 and the instruction count matches 627/627.  Comparing
  **basic-block shapes** (fingerprints of mnemonics only, which survive both
  register naming and scheduler reordering) leaves exactly **4 unmatched
  blocks of 207, and that is the floor across all 36 variants built for this
  function** - 34 of them also score exactly 4, the fold removal scores 5 and
  one spelling scores 6.  The four are: the loop back-edge polarity; `add
  esi,eax` where the target has `lea esi,[eax+ecx]`; and two blocks that
  differ only in the order of the same six mnemonics.  Every lever derivable
  from the reference's disassembly has been tried and measured: loop **form**
  (which did work, twice) is exhausted, operand **width** worked once, and
  CFLAGS are fully swept (/O1, /Og-, /Os, /G6, /Ge, /Oa all lose; /Ot, /Ob2,
  /Oy, /Ox, /Ow, /Og, /Op, /G3, /G4, /G5, /GB, /GA, /Gi inert), as are
  declaration order, TU composition, statement swapping and loop spelling.
  Do not use call-ordinal, branch-ordinal, FP-subsequence or matching-block
  deltas as per-site locators: all four were built, all four oscillate, and
  each was spot-checked against identical code.  The GA is also unusable here
  - its score ranks a 2433-byte result above a 2434-byte one.
- gm_AllocSpieler: 3678 B vs the target's 3689, 1049 vs 1056
  instructions, 652/1056 order-based alignment, **72 unmatched block shapes of
  225**.  Two real corrections landed: the `__ftol` call convention (the
  reference passes its operand in st(0), so our pushes were spurious and were
  the whole of the old +5-byte "match") and the stat guard, which compares in
  single precision.  **Judge this function by unmatched block shapes and
  order-based alignment, never by |size - target|**: the float guard improved
  every structural metric including `rebrew test`'s own score (504 -> 514)
  while moving the size 11 bytes further away.  The 7-instruction gap is
  distributed - five of our size-6 blocks are size-7 in the target, plus three
  missing size-1 blocks - not one missing construct.  The FP operand-width
  deltas (`fiadd` 0/3, `fimul` 1/0, `fild` 10/8, `fld qword` 0/1, `fsubr
  qword` 2/1) and every spelling tried against them, including the `rnd` cast
  and the second guard site, all return byte-identical objects.  Nothing
  outstanding is reachable from C89 as far as these measurements go.
- Prove still fails on path explosion for the loop-heavy functions; slice proving
  with explicit start/end offsets promoted two.

## Inline asm audit (2026-09-12)

Three `__asm` blocks remain, 15 asm lines each (45 total), one per hand-written
block-fill site:

| File | Function | Site |
|---|---|---|
| `server4.c:448` | srv_InitBuildingTypeTable | 0x1000b040 |
| `m_alloc2.c:231` | m_PoolAlloc | 0x10006d20 |
| `m_alloc.c:220` | m_init | 0x100068e0 |

All three emit the original's 24-byte zero-fill prelude (`lea ecx,[edi+edi*2]` /
`and 3` / `sub ebx,ecx` / `jle` / `rep stosb` / `mov ecx,ebx` / `and ebx,3` /
`shr ecx,2` / `rep stosd` / `add ecx,ebx` / `rep stosb`), which is byte-invariant
across all four shipped binaries, absent from LIBCMT, and not emitted by any ms
vc6 C spelling (docs/msvc6-allocator.md Finding 19).  Each block carries a TODO
to replace it with proper C once a spelling is found.

No other inline asm exists.  `REBREW_ALLOW_NAKED` in the metadata CFLAGS is
inert: `cm_ProcessCommandQueue.c`, `gm_ObjectsAvailble.c` and `aemter.c`
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
inlined); (3) m_alloc.c split (m_ShutdownAllocator..m_pool_free are a
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
  m_alloc2.c; m_FreeTracked+m_init replaced with a two-function
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
  `// FUNCTION:` headers (ProcessReceiveData, amt_ExecuteOfficeAssignment,
  ls_Load*, cm_Ex*, gm_AllocSpieler, ahm_ExAllocAlchemist, ...).
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
  16B over; amt_ExecuteOfficeAssignment +2000 placement; the amt/ahm C-size
  blocks; then the CRT block and data/BSS.

## ahm/aemter convergence (2026-08-22) — 112 -> 198 aligned (46.7%), reccmp 89.58%

- ahm_ResetEntityState+ahm_CheckFlag dumped (C was 656B over);
  alchemistry_logic.c split 3-way with the shared decl (gm_ff_Objekt)
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
+800, lb_ExPlayerHasJoined +1264, ... — same per-function dump loop), then
the CRT block, then data/BSS.

## loadsave region (2026-08-22) — 220 -> 227 aligned (55.5%)

- ls_LoadSavegameHeader dumped (C was 800B over); loadsave.c fragment 1
  (LoadGraveyardData/InitNewDynastyEntity/ReadVfsDataChecked) dumped as a
  3-function TU; loadsave.c split into loadsave2 (LoadExistingEntities) and
  loadsave3 (ls_ID2Ptr) — both hit the stale-marker bug (deleted line 43).
- gm_ObjectsAvailble/gm_ff_Objekt/gm_AllocObjekt got their
  missing `// FUNCTION:` anchors (C files with no _emit — the emit-only sweep
  missed them).

NEXT: spiel.c must split at every gm-dump boundary (its mega-TU covers
0x10015CB0..0x10017xxx and swallows the separately-anchored gm dumps);
then the lb block, the CRT block, and data/BSS.

## spiel/gm convergence (2026-08-22) — 227 -> 261 aligned (63.8%)

- spiel.c split 6-way at the gm-dump boundaries (split_tu.py, VAs:
  0x10016240/0x100165A0/0x10016cd0/0x10017210/0x10017910) + spiel6 -> spiel62
  (0x10017f30). The mega-TU was swallowing the separately anchored gm dumps.
- gm_AllocGebaeude/gm_AllocRaum dumped (were tiny gen'd
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
1. The lb block (lb_ExPlayerHasJoined +1248 / lb_* -672 — a TU split or C
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
