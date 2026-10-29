# Current work

## Current committed snapshot (2026-10-29 02:40 UTC)

README, code/data bars and defrag map now describe the accumulated committed
source tree, using one CLI status report. Server code and stored data are 100%,
but its current raw file agrees at 74.4%; the byte-identical v1.6.1 build is
historical. GoldTL has 4,100/5,184 C matches (79.0%), 53.4% code accounting and
8.3% raw-file agreement. Gold has 1,881/4,426 C matches (42.4%), 21.0% accounting
and 1.1% raw-file agreement. No new native build or data verification ran.

All accumulated source, metadata, layout and build changes were committed; the
modified .lib archive was explicitly excluded. A stale cross-import fixture
path was corrected after its source moved. Tests: 39 passed plus 3 subtests.
All-target lint found zero errors; its only generated-guidance warning was
cleared by refresh, with project rules preserved and init --check passing.
Receipts: .scratch/readme-refresh-20261029/.


## Release 1.6.1 — server verification and charts (2026-10-27)

A fresh isolated build with published Rebrew 6.3.1 reproduces all 286,720 server
bytes (SHA-256 `3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`).
Verification passes 316/316 functions (251 game, 65 source-built library) and
652/652 data records. Status reports 100% server code accounting, C matches,
raw-file agreement and all three data bars (547/547 records, 66,664 bytes).

Reviewed 76 server inventory extents end before 712 trailing NOPs. Those bytes
remain linker/compiler alignment; no source or image bytes were inserted.
Rebrew now supplies the native Microsoft-runtime toolchain profile, so the
obsolete duplicate project overlay and its CMake environment override are removed.

The README and all three graphics use one release-source status snapshot after
fresh data checks. GoldTL: 3,804/5,122 C matches, 47.8% code accounting; Gold:
2,466/4,592 C matches, 22.6%. Existing client raw images agree at 2.0% and 1.1%.
Neither client was rebuilt or made playable. Ongoing uncommitted client recovery
is preserved outside this release; its larger counts must not be mixed into the
release charts. Canonical server bindings accidentally retired by the client
library sweep were restored separately and their two TUs pass 80/80 checks.

Release tests: 39 passed and 3 subtests; all dependency extras resolve, `uv lock
--check` and `uv pip check` pass. Source-built library attribution and whole-file
identity remain separate claims. No full project gate or new gameplay test is
claimed. Local receipts: `.scratch/release-20261027/`.


## Server data placement fixed (2026-10-24 19:24 UTC)

The upstream Rebrew 6.1.1 fix resolves the 138 previously VERIFIED-only server
records without adding storage: 123 layout intervals use section coordinates,
four aliases use bounded backing offsets, ten private symbols use selected
COFF references, and one float literal has a reviewed native-symbol binding.
Server data is 547/547 EXACT in status and all 652 raw records pass; the complete
raw DLL remains byte-identical. The [data chart](../README.md#data-verification)
now shows 100% in all three server bars. No client rebuild or new client verdict
is claimed. Evidence: `.scratch/server-data-placement-20261025/`.

## Data/chart check (2026-10-24 18:38 UTC)

Fresh checks: server 652/652 data symbols and whole-file identical; Gold
83 matches, 30 differences, 49 missing. GoldTL's audit EXE is unavailable and
its map empty during a concurrent rebuild. The latest recorded link failed
with 20 unresolved symbols; no fresh TL data result was recorded. Its previous
125/51/15 measurement remains dated explicitly in the [README](../README.md#data-verification).
Stored TL C matches are 3,835/4,946 (77.5%); one STUB remains. No functions were
compiled for this refresh and no full gate ran. Receipts:
`.scratch/data-readme-refresh-20261025/`. Source work continues below.

<a id="status-snapshot-2026-10-21-1202-utc"></a>

## Status snapshot (2026-10-24 session round 7)

The user set the order: **GoldTL STUBs to zero first**. Gold is frozen at the
session round 6 counts and no Gold file is edited until GoldTL is done.

- **Server:** unchanged. 251/251 EXACT, 100% code accounting, raw file identical.
- **GoldTL:** at 12:55 local RELOC 3530, EXACT 291, NEAR_MATCHING 91,
  SIZE_MISMATCH 930, STUB 65, 3 unverified rows, 4910 function rows (from 266
  STUB at round 7's start). Round 8 levers: compiler-flag sweeps (wins on
  `0x50e170` `/Oy-`, `0x4f0f60` `/Os`, `0x4f18d0` `/Oy-`, `0x414fb0` `/O1`;
  `/Os`/`/O1`/`/Oy-` are the only switches that move these bodies and usually
  worsen them), `test --force-status` for reviewed complete bodies (verdict
  class is what blocks the rest, not policy), split row `0x5d6c50` (its new
  `0x5d6ea0` row landed RELOC 539/539), and one-row-per-agent sessions. Kept-body policy is in force: complete faithful
  bodies stay with a specific blocker instead of being reverted to stubs, and
  `rebrew test --force-status` records SIZE_MISMATCH where the promotion policy
  would refuse. One row per agent session is the practical granularity: stacked
  three-row tasks delivered only the first pass. Both hand-written assembly rows reached EXACT
  (`0x41bb70`, `0x47a320`) through inline `__asm` with `document-assembly`
  receipts; whole-function naked stays lint-banned (E023). Stale stored sizes
  `0x4c9e20` (190) and `0x414fb0` (416) were repaired, and an orphan unit file
  from the retired D3DX8 band (`0x62a1ee`) was moved out of `src/` to restore a
  0/0 lint. Work resumed after an 8-hour pause with 19 agents: ten on the
  smallest remaining STUB bodies (121-301 B, prior evidence in `.scratch/`) and
  nine on the 1 KB+ bodies. Policy in force: a faithful compiling body stays in
  tree with a blocker even at SIZE_MISMATCH; stubs are not restored.
- **GoldTL extent repairs:** 18 rows started with a 5-6 byte jump over a larger
  extent; the heads shrank to their jump body and 15 following-code rows were
  added. The 152 game-source claims inside the declared D3DX8 external range
  were retired (library code, not game source), and seven `jne` split arms were
  merged into their owners.
- **GoldTL non-body rows:** the D3DX8 band is retired, and the nine rows above
  0x650000 were cleaned up (six compiler funclets and two import-thunk runs
  retired, `0x660075` adopted as LIBRARY `___crtCompareStringA` from stock
  LIBCMT). Remaining known non-C shapes in the game band: SEH funclets
  (`0x41ebca`), a switch-case arm with rodata (`0x5294c4`), and a hand-written
  assembly sprite blitter (`0x47a320`, manual register bank, rep movsd and
  mask-merge loops). The asm row needs an asm-evidence decision; the import-thunk
  writer is still missing upstream.
- **Gold:** frozen at RELOC 2571, EXACT 203, NEAR_MATCHING 31,
  SIZE_MISMATCH 70, STUB 1480, function rows 4404, 46 unverified rows.
- **Lint:** 0 errors. Two tree-wide breakages were fixed during the large-body
  phase: an anchor-order break in `src/GOLDTL.fcn_00499090.c` (an include sat
  between the ADDRESS comment and its definition) and a duplicate stacked
  anchor in the same file. Anchor rule for every new file: includes, typedefs
  and extern declarations go ABOVE the ADDRESS comment; nothing may sit between
  the anchor and its definition.
- **Keep partial bodies (policy from this round):** do not restore a stub when
  a semantically faithful body compiles and measures a real match
  (SIZE_MISMATCH / NEAR_MATCHING). Keep the best body, set the residual blocker
  with `rebrew blocker set`, and report. A parked body that is reverted to a
  stub loses measured progress; only revert when the body is fabricated,
  uncompilable, or its semantics are wrong. The park-then-revert habit from
  the early large-body batches shall not repeat.
- **Large-body playbook (measured this round):** one row per task; a 1.5 KB+
  body needs a whole session pass, not a batch slot. Model the frame before the
  body: prologue kind, frame size, callee-saved homes and stack-slot order come
  from the native bytes, and a wrong slot map invalidates every later block.
  `#pragma optimize("y", off)` restores a frame pointer when the target keeps
  one. Decompiler hints can be contaminated (a tail-called callee merged into
  the listing at `0x52f7b0`) or lose call arguments (`0x4bfe00`): re-run `af;
  pdg` at the true entry and repair the hint instead of copying it.
- **Hazard: `rebrew test --size N` persists N into metadata.** A probe with
  `--size 125` on `0x4f0f60` silently replaced the canonical 133 and would have
  clipped a real cold clamp block (`mov eax,4; jmp`). Use `--no-promote` with a
  size override, or restore the canonical SIZE afterwards.
- **Decompiler workaround (measured):** `rz-ghidra` fails ("Symbol var_2h
  extends beyond the end of the address space") on functions whose prologue is
  the `mov eax,<size>; call __chkstk` form. Copy the binary to `.scratch/`,
  patch that prologue to `sub esp,<size>` in the copy, and run pdg there; the
  original artifact stays untouched. Used successfully for `0x00479330`.
- **CRT call identities (measured):** `0x64d228` is __ftol (arg in st0, result
  byte stored), `0x64d3f8` is rand() (int, no args), `0x64d41a` is wsprintf.
  Treat them as CRT, not game calls; a plain `(unsigned char)` cast and `rand()`
  reproduce the native call shapes.
- **Fact for large-body passes:** `0x64d228` in this binary is the CRT __ftol,
  so use `(int)` casts instead of modelling it as a game call. `0x532ef0` is a
  reconstructed RELOC tail-call target used by several dialog arms.
- **Cache:** compiles need `XDG_CACHE_HOME=$PWD/.scratch/rebrew-cache`.

Next actions, in order:

1. Keep eight teammates reconstructing GoldTL bodies in batches; prefer
   prologue-start rows of 40-400 bytes.
2. The graph/dialog helper signatures derived by the large-body passes are
   duplicated in five sibling files (`.scratch/gold-b/TL_dialog_helpers.md`,
   `Cur`/`Sample_99ec20` already in `src/client_types.h`). Consolidate them into
   one shared header in a dedicated task instead of per-file copies. Also note
   `af; pdg` fails at `0x005d3d90` with a var-extent error; the row needs manual
   asm translation or another decompiler backend.
3. Classify the local-unwind funclets with their owning library rows and record
   the decision for `0x60ff98` (register-argument wrapper).
4. Re-run the GoldTL interior/arm analysis after the reconstruction batches; the
   `jne` split arms (seven candidates) still need reviewed merges.

## Status snapshot (2026-10-24 session round 6)

The user set the next phase: **get STUB to zero first**. The counts below are
authoritative metadata-store counts for FUNCTION/STUB rows; the `rebrew status`
view also overlays the per-target verify cache, so read the story from
`rebrew todo`/`rebrew verify` rather than a single number.

- **Server:** unchanged. 251/251 EXACT, 100% code accounting, raw file identical.
- **Gold:** at 02:56 local RELOC 2571, EXACT 202, NEAR_MATCHING 31,
  SIZE_MISMATCH 70, STUB 1479, function rows 4404, with 51 unverified rows
  (nine from the coverage additions, 42 split out of wrapped STUB rows). Raw-file
  agreement is not freshly measured.
- **GoldTL:** RELOC 3524, EXACT 287, NEAR_MATCHING 87, SIZE_MISMATCH 898,
  STUB 266, function rows 5063.
- **This round (session 6):** two upstream capabilities landed with tests:
  `change_source_bindings_batch` (one metadata write for many reviewed
  identity changes) and `library adopt` (unique stock-archive match over a
  FUNCTION/STUB row, digest-guarded). Full suite: 13,104 passed, one
  pre-existing `test_ci_pins` failure. Then 57 stock-archive STUB rows and 27
  reconstructed library-body rows were converted to LIBRARY in two batch
  writes; the library sweeps now report zero remaining candidates. Detail:
  [provenance](provenance.md) session round 6.
- **Coverage:** rizin `aaa` lists 3734 Gold functions; 19 entries had no
  inventory row. Fifteen game-band rows (1 to 88 bytes, mostly tiny helpers and
  one float routine) were added with `binary repair-extents --add-missing` from
  reviewed extents; nine now have skeleton bindings and no STATUS. Six of the
  fifteen already had metadata rows (five LIBRARY `library_lua50.h` rows and
  one shared `GOLDTL.fcn_00507e70.c` row), which the comparison missed by
  reading inventory only; five redundant inventory rows cannot be withdrawn
  (upstream idea recorded). One DirectDraw thunk and three library-band entries
  were left out.
- **Extent gap:** rows that wrap later unlisted functions (the `0x40d9a0`
  case) still need split-plus-add; the first detector has false positives and
  misses `mov`-starting functions.
- **Split rows:** 36 STUB rows that wrapped later routines were split at 43
  rizin-confirmed entries (bytes unchanged, no verdicts lost); the 42 new rows
  are the hidden functions, now skeleton-bound work items.
- **Lint:** clean, 7119 files, zero errors, zero warnings.
- **Keep partial bodies (policy from this round):** do not restore a stub when
  a semantically faithful body compiles and measures a real match
  (SIZE_MISMATCH / NEAR_MATCHING). Keep the best body, set the residual blocker
  with `rebrew blocker set`, and report. A parked body that is reverted to a
  stub loses measured progress; only revert when the body is fabricated,
  uncompilable, or its semantics are wrong. The park-then-revert habit from
  the early large-body batches shall not repeat.
- **Large-body playbook (measured this round):** one row per task; a 1.5 KB+
  body needs a whole session pass, not a batch slot. Model the frame before the
  body: prologue kind, frame size, callee-saved homes and stack-slot order come
  from the native bytes, and a wrong slot map invalidates every later block.
  `#pragma optimize("y", off)` restores a frame pointer when the target keeps
  one. Decompiler hints can be contaminated (a tail-called callee merged into
  the listing at `0x52f7b0`) or lose call arguments (`0x4bfe00`): re-run `af;
  pdg` at the true entry and repair the hint instead of copying it.
- **Hazard: `rebrew test --size N` persists N into metadata.** A probe with
  `--size 125` on `0x4f0f60` silently replaced the canonical 133 and would have
  clipped a real cold clamp block (`mov eax,4; jmp`). Use `--no-promote` with a
  size override, or restore the canonical SIZE afterwards.
- **Decompiler workaround (measured):** `rz-ghidra` fails ("Symbol var_2h
  extends beyond the end of the address space") on functions whose prologue is
  the `mov eax,<size>; call __chkstk` form. Copy the binary to `.scratch/`,
  patch that prologue to `sub esp,<size>` in the copy, and run pdg there; the
  original artifact stays untouched. Used successfully for `0x00479330`.
- **CRT call identities (measured):** `0x64d228` is __ftol (arg in st0, result
  byte stored), `0x64d3f8` is rand() (int, no args), `0x64d41a` is wsprintf.
  Treat them as CRT, not game calls; a plain `(unsigned char)` cast and `rand()`
  reproduce the native call shapes.
- **Fact for large-body passes:** `0x64d228` in this binary is the CRT __ftol,
  so use `(int)` casts instead of modelling it as a game call. `0x532ef0` is a
  reconstructed RELOC tail-call target used by several dialog arms.
- **Cache:** compiles need `XDG_CACHE_HOME=$PWD/.scratch/rebrew-cache`.

Next actions, in order:

1. Reconstruct the 51 unverified rows (new inventory rows and the hidden
   functions split out of wrapped STUB rows); they are part of byte identity
   even at 1 to 88 bytes.
2. Validate and apply split-plus-add for rows wrapping hidden functions, using
   rizin function entries and disassembly; the 62/56 candidate lists need
   per-row review.
3. Continue STUB-first batches on game-code rows with decomp hints, excluding
   the documented codegen walls.
4. Re-run both library sweeps after new rows land, and use `library adopt` for
   any new matches (GoldTL stock matches were not converted yet).
5. Rebuild and relink the clients before quoting byte-level progress; the
   stored counts are object verdicts, not a fresh link check.

Older notes below are dated checkpoints and are superseded by this one.

## Live state (2026-10-22, round 107)

Historical round record; use the snapshot above for current results.

- Round 107: no metric change (GOLD 59.4 percent, RELOC 2531, NEAR 22). Three
  near-miss experiments were tried and reverted with backups kept in
  `.scratch/lead/*.bak.c`:
  - 0x0043b600 (98/100, two mov reg mismatches): reusing the return register for
    the trailing value regressed to 62/100; original restored.
  - 0x004a16f0 (9103/9106): the single delta is a function-pointer store of
    0x00496060, whose GOLD row is a sizeless library identity (lua_version) from
    FLIRT, so the reloc stays unresolved. Mapping the pointer to that identifier
    changed nothing; restored.
  - 0x00468c60 (113/115) is the SIB-order class: reference computes
    `lea esi,[ebx+eax]` plus a scaled load, our compiler picks the other index.
- Recurring lesson: keep an explicit `.bak.c` before every variant attempt; three
  reverts this round depended on it.

- Round 106: no metric change (GOLD 59.4 percent, RELOC 2531, NEAR 22). While
  experimenting on 0x00411b00 the file was reverted with `git checkout --`, which
  restored the committed STUB skeleton and destroyed the uncommitted 96/97-byte
  NEAR reconstruction. The body was rebuilt from the disassembly text captured in
  the session log and is NEAR 96/97 again.
- Rule: never `git checkout --` a reconstructed source file. Their bodies are
  working-tree only; HEAD holds the stub. Recover from `.scratch` captures or the
  session log instead.
- The 0x00411b00 single-byte delta is the addressing mode of one load
  (`[esi+eax+0x178]` in the reference versus the compiler's alternative SIB
  order); the hoisted-pointer variant regressed to 16/97 and was reverted.

- Round 105: GOLD 59.4 percent (RELOC 2531, EXACT 199, NEAR 22, SIZE_MISMATCH
  84, STUB 1735). Ran `rebrew verify` for GOLD: it reused cached verdicts,
  reconciled the count discrepancy from round 104 (verify: total 4586, passed
  2744, exact 199, reloc 2545, matching 23) and promoted rows that had become
  matchable through the earlier identity repairs (0x00582490 and 0x005975e0 now
  RELOC).
- Converted 0x005be320 RELOC 477/477 by replacing GOLDTL-side raw data addresses
  with file-scope target macros: SND_TABLE_ADDR 0x770b80 on GOLD vs 0x7f4ca0 on
  GOLDTL, SND_INDEX_ADDR 0x6f25b8 vs 0x774970 (the table base must be the array
  start, not the +9 element). GOLDTL stayed RELOC.
- Remaining GOLD NEAR rows each need similar target-specific data or callee
  identity work; the pattern (raw absolute addresses in GOLDTL bodies) is common
  and cheap to fix with file-scope macros.

- Round 104: three GOLD rows converted and five lost-size rows restored, but the
  matched total is unchanged at 2727 (RELOC 2528 + EXACT 199) versus 2527 + 200
  at round start, so one previously EXACT row is unaccounted for. No EXACT
  demotion appears in status_history after 16:20; the discrepancy needs
  reconciliation before counting this round as progress.
- Conversions: 0x0047c3c0 RELOC 52/52 (the GOLD macro for fcn_0047c0d0 /
  fcn_0047beb0 now resolves), 0x0049ee20 RELOC 156/156 and 0x004ab2c0 RELOC
  275/275. The last two needed the fcn_004ab3e0 name freed on the GOLD-only row
  0x004ab3e0, which was rebound to src/GOLD.fcn_004ab3e0_gold.c with identifier
  fcn_004ab3e0_gold, then 0x004ab2c0 was rebound to the shared definition and its
  stale 288-byte size repaired to 275.
- Five rows lost their size record (0x00403ab0, 0x004076b0, 0x0041e050,
  0x0044f760, 0x004cd5e0, status MISSING_SIZE): their files still existed, so
  re-registering and assigning inventory sizes restored them to STUB with
  blockers. MISSING_SIZE is now zero and lint is clean again.

- Round 103: no metric change (GOLD 59.3 percent, 2527 RELOC). Wave 58 targeted
  nine GOLDTL SIZE_MISMATCH bodies; agents ran long with no status movement and
  the wave was stopped at the round boundary. The batch GOLD retest
  (`test --all --jobs 4`) was also stopped, unfinished.
- Library identification is available but low-confidence: `library identify
  --dry-run` would write 253 annotations at confidence 0.5, with the same symbol
  proposed for many different VAs, so it was not applied. The 0x5e-band rows need
  a stricter review before they can be classified as library code.

- Round 102: no metric change (GOLD 59.3 percent). The NEAR rows that remain all
  fail on unresolved call displacements: the shared sources call GOLDTL function
  names for which GOLD has no identity at all (for example 0x005975e0 calls a
  function at 0x005b46e0 whose presumed GOLDTL donor fcn_005bebe0 is 1253 bytes
  while the GOLD row is 1632, so they are not twins). Converting them needs the
  true GOLD twin identity per callee, derived from a shape match, not a rename.
- Library path opened for the 0x5e-band residues: `library scan-signatures`
  finds 34 FLIRT matches (CRT/MSVCRT code such as _strstr, _strncpy, _memcpy,
  __alldiv), and `library identify --dry-run` lists 356 candidates without
  writing. Reviewing those before annotating is the next step for the tiny
  0x5e SIZE_MISMATCH rows, which are library code, not game code.

- Round 101: no metric change (GOLD 59.3 percent, RELOC 2527, NEAR 27). Probed
  all 27 remaining NEAR rows for their mismatch sites: the metadata-only class
  (duplicate or missing identity for a pushed/called function) is exhausted.
  The rest are genuine body differences: wrong callback sets, different literals,
  or stub bodies whose only overlap with the donor is masked relocations. Row
  0x0049ee20 still needs the GOLD twin at 0x004ab2c0 to carry the shared
  fcn_004ab3e0 body, which itself is 288 vs 275 bytes (SIZE_MISMATCH), so it is
  body work, not identity repair.
- The near probe script disassembles mid-instruction for many offsets; only
  mismatches that land on an instruction start give usable sites. Fix the probe
  to walk instructions from the function start before trusting it.

- Round 100: GOLD 59.3 percent (RELOC 2527, NEAR 27). Near-miss 0x0042f620
  differed only in its own recursive call; the duplicate stub sibling
  0x0042ee50 (same fcn_0042ee50 name) shadowed the matched row. Retiring the
  sibling made the row RELOC 436/436.
- Next near row 0x005975e0 needs real body work: its remaining delta is a call
  to 0x005b46e0 for which no GOLDTL-named GOLD identity exists, and the presumed
  donor body (GOLDTL fcn_005bebe0, 1253 bytes) has no same-size GOLD twin.

- Round 99: GOLD 59.3 percent (RELOC 2526, NEAR 28). The remaining NEAR deltas
  are function-pointer pushes whose GOLDTL callee name has no matching GOLD
  identity. Near-miss 0x004e5770 (351/354) pushed fcn_004da690, fcn_004dc5f0 and
  fcn_004dc6e0; GOLD had two rows both named fcn_004dc5f0 (0x4dada0 and
  0x4dae90) because one definition carried stacked anchors, and no row for
  fcn_004dc6e0 at all. Split the identities: 0x4dada0 keeps fcn_004dc5f0;
  0x4dae90 is bound to its own GOLD definition src/GOLD.fcn_004dc6e0.c with the
  same body, symbol fcn_004dc6e0 (RELOC 233/233). 0x004e5770 then converted to
  RELOC 354/354 with GOLDTL unchanged.
- Pattern for the remaining rows: give each pushed callback its own GOLD
  identity when GOLD places two identical bodies at different VAs.

- Round 98: no matched change (GOLD 59.3 percent, RELOC 2525, STUB 1737). The
  last safe duplicate sibling 0x0044f7e0 was retired. The remaining NEAR rows
  were audited: their unmasked deltas are mostly literal data addresses. For
  example 0x004e5770 (351/354) pushes 0x4d8e20 / 0x4dada0 / 0x4dae90, which are
  literals and interior addresses inside .text rather than named globals, so the
  abs32 operand cannot be masked. These need literal data rows or a reviewed
  source form, not duplicate-name work.
- The near-audit script produced no receipt file (needs a re-run when touched
  next); the finding above came from direct disassembly.

- Round 97: GOLD 59.3 percent (RELOC 2525, NEAR 29, STUB 1738). Duplicate-symbol
  cleanup continues to pay: six GOLD-only stub siblings (0x0040eac0,
  0x004f2540, 0x0050c550, 0x0050f910, 0x0052d970, 0x0054f3b0) were retired so
  their names resolve to the matched shared definitions. Four near-miss rows then
  converted with no source edits: 0x00490b80 (123), 0x005283d0 (243),
  0x005a4060 (542), 0x005847e0 (632); each had zero mismatches once the
  duplicate shadow was gone.
- Remaining NEAR rows show unmasked call displacements at offsets that point at
  still-unresolved names; the pattern is the same duplicate/retired-name class.

- Round 96: GOLD 59.2 percent (RELOC 2521, NEAR 33, STUB 1744). Repaired the
  round-93 retirement mistake: four retired rows (0x004cd4c0, 0x00577e50,
  0x00578760, 0x005a8e50) were matched shared definitions, not duplicates. For
  each, the GOLD-only stub sibling that owned the duplicate symbol was retired
  instead, then the matched row was rebound digest-guarded and tested back to
  RELOC. Their call targets resolve again, which converted 0x00578440 to RELOC
  493/493 with no source change.
- Restored rows keep their original GOLDTL-derived names. The four retired stub
  siblings (0x004ce040, 0x00580420, 0x00580d50, 0x005b22d0) still need reviewed
  rebinds with distinct GOLD identities.
- Rule: before retiring a duplicate-name row, check its status. Retire the
  GOLD-only STUB sibling, never the matched shared definition.

- Round 95: no metric change (GOLD RELOC 2516, NEAR 34). Wave 57 repeated the
  donor-guided stub approach on the next nine pairs; agents again returned empty
  reports and no rows converted.
- Found the mechanism behind the stalled near-miss 0x00578440: its target calls
  0x00578760, one of the duplicate GOLD rows retired in round 93. Retiring those
  claims removed the call-target identity, so the displacement stays unmasked and
  the row can never match until the row is rebound. The same applies to every
  site that calls a retired VA.
- Next step: reviewed rebind for each retired row onto its GOLD stub file with a
  distinct GOLD-side identity (the duplicate placeholder name is what blocks the
  plain rename); until then those call sites stay NEAR.

- Round 94: GOLD 59.1 percent (RELOC 2516, NEAR 34, STUB 1748). Wave 56 worked
  the donor-guided GOLD stubs (stub file plus the verified GOLDTL donor body);
  0x004e6d80 converted to RELOC, the other eight stayed STUB or NEAR. The three
  agents returned empty reports again, so the wave is credited from metadata.
- The remaining 24 unbound near-miss pairs are the next donor-guided batch; most
  need real body work rather than metadata fixes.

- Round 93: duplicate-name cleanup unblocks near-misses. Retired ten speculative
  GOLD-only duplicate claims (0x0049ab50, 0x0049f5c0, 0x004ad1c0, 0x004bcc20,
  0x004ccf10, 0x004cd4c0, 0x004f0430, 0x00577e50, 0x00578760, 0x005a8e50) that
  shadowed matched shared definitions. Near-miss 0x004e6e20 then converted with no
  source change (RELOC 157/157), and a full retest of the 50 near-miss pairs
  produced 12 RELOC, 13 NEAR, 25 errors. Best partial: 0x004a16f0 9103/9106.
- Trade: retired rows leave the counted classes, so GOLD status now reads RELOC
  2515 (-2 from 2517), NEAR 35, STUB 1748, coverage 99.6 percent, matched 59.1
  percent. No status_history entry records a RELOC demotion, so the delta comes
  from rows removed by retirement, not from regressions.
- The remaining 25 near-miss retests error out; they need anchors or bindings
  before they can be measured.

- Round 92: GOLD 59.1 percent (RELOC 2517, EXACT 200, NEAR 37, SIZE_MISMATCH
  81, STUB 1753). Wave 55 on nine mid-size GOLD STUBs: agents report 0x004506e0,
  0x0043bb70 and 0x0043b6e0 RELOC (all call relocations validated), 0x00441ea0
  NEAR, the rest parked on regalloc/scheduling. Net status moved by one row
  because some of those rows had already been counted in other classes.
- Duplicate-name disambiguation is still blocked: `source rename GOLD.0x49ab50`
  fails with "ambiguous references to independent target symbols" from shared
  files, so the 30 duplicate names identified in round 91 need the
  --reference-owner route or a per-module rename pass later.

- Round 91: +1 GOLD RELOC. After retiring the duplicate GOLD 0x00429670 row,
  near-miss 0x00429e90 converted with NO source changes (RELOC 160/160 on both
  targets); the earlier target-specific callee macro was unnecessary and was
  removed. The row is now shared via src/GOLDTL.fcn_00428720.c.
- Surveyed duplicate function names in the GOLD module: 30 names, nearly all the
  same pattern: GOLDTL has a function at VA X (matched), GOLD has the shared twin
  at VA Y (matched) AND a GOLD-only row at VA X (usually a larger STUB). Both
  GOLD rows carry the GOLDTL placeholder name fcn_X, so relocations to that name
  are ambiguous. Examples: 0x0049ab50/0x0049b110, 0x0049f5c0/0x0049fb80,
  0x004ad1c0/0x004ad0a0, 0x004bcc20/0x004bc640.
- Proposed next step: disambiguate the GOLD-only rows (e.g. a reviewed
  GOLD-side placeholder name) so reloc masking can resolve; that would unblock
  several near-miss conversions that currently stall on call displacements.

- Round 90: no matched gain but one duplicate-symbol blocker resolved. GOLD
  0x00429670 was a second GOLD row carrying the name fcn_00429670 (816-byte
  extent, no GOLDTL shape twin); it was retired via digest-guarded binding
  retire so the shared symbol resolves. That cleared the first of the two
  mismatching call displacements in near-miss 0x00429e90: with a file-scope
  callee macro the GOLD row improved from 154/160 to 158/160 (offset 88 now
  matches; remaining delta is a second call at offset 143 to 0x0042b410). The
  GOLDTL row stays RELOC 160/160. A guessed mapping for the second call made
  things worse and was reverted.
- GOLD: RELOC 2515, EXACT 200, NEAR 38, SIZE_MISMATCH 81, STUB 1754 (retired row
  no longer counted as STUB), matched 59.1 percent, coverage 99.8. The retired
  row still needs a reviewed rebind with its true identity.

- Round 89: no metric change (GOLD 59.1 percent). Tried the next near-miss
  (0x00429e90, 158/160): the two-byte group is a call displacement to
  0x0042ada0, whose GOLD row is named fcn_00429670, while the shared source
  calls fcn_00429d30 (its GOLDTL twin name). A target-specific callee macro
  (fcn_00429670 for GOLD) made the GOLDTL side RELOC but left the GOLD side
  NEAR 156/160: the call resolves to a different function than the reference
  call, so the guessed twin name is wrong. Reverted the edit; both verdicts are
  back to their prior state (GOLDTL RELOC, GOLD NEAR 158/160).
- Cross-target callee renames need the *actual* GOLD twin identity, usually
  derivable from a shape/size match, not from the GOLDTL name. Verify a callee
  mapping with xrefs before using it in a macro.

- Round 88: GOLD 59.1 percent (SIZE_MISMATCH 81, everything else unchanged).
  Resolved part of the fcn_004ab3e0 duplicate: the stale GOLD.0x00519a30 row
  pointing at a deleted file was dropped, then the speculative binding of GOLD
  0x004ab2c0 to the shared FOLDTL body was retired (288-byte extent is not the
  275-byte GOLDTL function) and the row was rebound to a fresh skeleton
  src/fcn_004ab2c0.c via digest-guarded rebind. That removes the same-module
  duplicate name, but 0x0049ee20 still shows the same 154/156 delta because the
  shared reference to fcn_004ab3e0 cannot be attributed between the GOLDTL row
  and the GOLD-only row.
- Rename of GOLD 0x004ab3e0 is still refused: "ambiguous references to
  independent target symbols" in src/GOLDTL.fcn_0049e860.c. Cross-target shared
  references need explicit ownership; --all-modules would rename both module
  definitions and recreate the clash.
- Fully resolving this needs a reviewed rename with --reference-owner or
  separating the shared reference; left parked.

- Round 87: no metric change (GOLD 59.1 percent). Tried to resolve the duplicate
  name fcn_004ab3e0 (two GOLD rows, 0x4ab2c0 shared-twin SIZE_MISMATCH and
  0x4ab3e0 GOLD-only STUB referenced through a function-pointer immediate).
  `rebrew source rename 0x4ab3e0 fcn_004ab3e0_cb --target Europa1400Gold.exe`
  refuses twice: first "cannot plan the rename" because a deleted file
  (src/GOLD.fcn_00519a30.c) is still listed as a source to read, then, with a
  placeholder file in place, "ambiguous references to independent target
  symbols". Left the duplicate in place; near-miss 0x0049ee20 stays blocked.
- Removing the placeholder restored lint to 0/0; state unchanged.

- Round 86: no metric change (GOLD 59.1 percent, RELOC 2515). Investigated the
  next near-miss (0x0049ee20, 154/156): the remaining four bytes are a call
  displacement that stays zero in our object because GOLD has TWO rows named
  fcn_004ab3e0 (0x4ab2c0 SIZE_MISMATCH and 0x4ab3e0 STUB), so the relocation
  cannot resolve unambiguously. Duplicate symbol names across GOLD rows block
  near-miss conversion until the extra row is renamed or retired.
- Future near-miss batches should pre-check for duplicate names in
  rebrew-functions.toml before touching a body, and prefer pairs whose callees
  have unique identities.

- Round 85: GOLD 59.1 percent (RELOC 2515, EXACT 200, NEAR 38, SIZE_MISMATCH
  82, STUB 1755). Wave 54 on the next nine near-miss pairs produced no
  conversions (empty reports) and one row (0x00417710) was left dangling; the
  lead repaired it: the GOLD anchor had been placed above the file's second
  function, so the row pointed at the wrong symbol. Moving the anchor above
  fcn_00418c80 and re-registering made it RELOC 150/150, and the GOLDTL row
  stayed RELOC.
- Lesson: when a shared file contains more than one function, place the target
  anchor above the function whose body is the twin, and derive the symbol from
  the definition (not from the file stem).

- Round 84: **GOLD 59.0 percent** (RELOC 2514, +26; SIZE_MISMATCH 82, -18;
  STUB 1756, -7). The near-miss cross-target queue delivered: wave 53 fixed nine
  shared bodies that needed target-specific field offsets or callees, and the
  lead converted six of them to shared GOLD definitions; GOLD 0x004d7000 and
  0x00417840 were fixed directly (single-byte offsets 0x200 vs 0x204 / 0x208 vs
  0x20c) and rebound.
- Pitfall found: putting `#ifdef REBREW_GOLD` *inside* a function body in one
  file broke the annotation scan for the whole tree ("line 11: address must
  precede exactly one C declaration"), which made every test fail. Rewriting the
  conditional as a file-scope macro (`#define OBJ_SND_OFF ...`) fixed it. Use
  file-scope target macros for cross-target variants.
- Remaining GOLD: SIZE_MISMATCH 82, STUB 1756, NEAR 38. GOLDTL unchanged at
  74.0 percent; server 100 percent; lint 0/0.

- Round 83: GOLD 58.5 percent (RELOC 2491, SIZE_MISMATCH 98, STUB 1762). The
  near-miss queue works: GOLD 0x004d7000 was a 1-byte difference (target uses
  field offset 0x200 where GOLDTL uses 0x204), solved with a
  `#ifdef REBREW_GOLD` variant in the shared file, then a digest-guarded
  `source binding rebind` moved the GOLD row onto the shared definition; both
  targets now test RELOC 145/145. Two more GOLD rows converted during wave 52.
- Wave 52 note: three of its pairs failed because the prompt carried guessed
  GOLDTL file names; the correct pairs are in `.scratch/lead/pairs2-run.json`.
  Future near-miss waves must pull file/VA/symbol data from that receipt instead
  of writing them from memory.
- GOLDTL 74.0 percent, server 100 percent, lint 0/0.

- Round 82: GOLD 58.5 percent (RELOC 2488, EXACT 200, NEAR 39, SIZE_MISMATCH
  100, STUB 1763). Re-ran the shape matcher against the current pools: 54 pairs,
  55 validations. Only one converted (0x005a8a90, RELOC 213/213); the other 53
  are GOLD rows whose GOLDTL body reaches 1-3 bytes short of a match
  (NEAR 48/52 up to 9097/9106). That list is a ready queue of near-miss fixes
  where one source change would lift both targets (receipt
  `.scratch/lead/pairs2-run.json`).
- GOLD SIZE_MISMATCH is at 100; the per-row fix-sizes sweep continues.
- GOLDTL 74.0 percent, server 100 percent, lint 0/0.

- Round 81: GOLD 58.4 percent (RELOC 2485, EXACT 200, NEAR 39, SIZE_MISMATCH
  103, STUB 1763). Wave 51 found that most of these rows need no source change
  at all: `rebrew test --fix-sizes` rewrites the stale GOLD SIZE when the
  compiled body matches the whole target and the stored size included trailing
  alignment NOPs (e.g. 0x0040cda0 240 -> 229, 0x004a8f20 272 -> ...). Nine rows
  converted this round (seven source-free SIZE rewrites plus two normal wins).
- A per-row fix-sizes sweep over the remaining GOLD SIZE_MISMATCH rows started
  (`.scratch/lead/fixsizes-sweep-gold.json`); its first rows did not qualify, so
  the remaining set is genuinely body-different.
- GOLDTL unchanged at 74.0 percent; its SIZE_MISMATCH batch repair remains
  forbidden (it demoted matched rows in round 44).

- Round 80: **GOLD 58.2 percent** (RELOC 2476, +13; SIZE_MISMATCH 112, -13).
  Wave 50 on GOLD SIZE_MISMATCH rows beat its nil-report predecessor: thirteen
  rows converted to RELOC, the strongest single-wave gain in the SIZE_MISMATCH
  campaign. The agents again returned empty reports, so the wave is credited from
  `rebrew status` and metadata only.
- GOLD totals: RELOC 2476, EXACT 200, NEAR 39, SIZE_MISMATCH 112, STUB 1763.
  GOLDTL 74.0 percent, server 100 percent. Lint 0/0.
- GOLD SIZE_MISMATCH has fallen 218 -> 112 across the campaign.

- Round 79: GOLD 57.9 percent (RELOC 2463, EXACT 200, NEAR 39, SIZE_MISMATCH
  125, STUB 1763). Wave 49 targeted nine SIZE_MISMATCH rows; the three agents
  returned empty reports, yet the tree gained three RELOC rows (SIZE_MISMATCH
  128 -> 125), so their edits landed without a report. Verify metadata, not agent
  claims, for this wave.
- GOLDTL remains at 74.0 percent with 892 SIZE_MISMATCH rows; its small-stub and
  padding classes are exhausted, and the remaining work is real body
  reconstruction.

- Round 78: GOLD 57.9 percent (RELOC 2460, EXACT 200, NEAR 39, SIZE_MISMATCH
  128, STUB 1763). Wave 48 converted 0x0051c8a0 (176 bytes) to RELOC and lifted
  0x00461690 to NEAR; the other seven rows stayed SIZE_MISMATCH.
- GOLD SIZE_MISMATCH is down to 128; the remaining rows are genuine body deltas.
  GOLDTL is the main remaining backlog (892 SIZE_MISMATCH, 294 STUB, 89 NEAR)
  and its small-stub candidates are mostly inventory fragments.

- Round 77: GOLD 57.8 percent (RELOC 2458, EXACT 200, NEAR 38, SIZE_MISMATCH
  131, STUB 1763). Wave 47 on GOLD SIZE_MISMATCH rows converted two shared-file
  rows to RELOC (0x004eaea0 and 0x004ece60, both bound to GOLDTL files); the
  other seven stayed SIZE_MISMATCH. Agent reports were empty for that wave, but
  the two edits and verdicts are verified in metadata.
- GOLDTL remains at 74.0 percent and is the larger backlog: 892 SIZE_MISMATCH,
  294 STUB, 89 NEAR. Its bodies differ by real code, and its padding-sweep class
  is empty.

- Round 76: GOLD 57.8 percent (RELOC 2455, EXACT 200, NEAR 38, SIZE_MISMATCH
  134, STUB 1763). Wave 46 converted 0x0043deb0 to RELOC 167/167 (four callees
  validated) and lifted 0x0043b6e0 to NEAR. 0x004207c0 and 0x00511630 are real
  C89 bodies parked on regalloc/scheduling.
- The GOLD padding sweep now mostly runs out of padding rows in the scanned size
  range: the latest run processed 33 rows with zero repairs, so the remaining
  SIZE_MISMATCH rows are genuine body differences.

- Round 75: GOLD 57.5 percent (RELOC 2445, EXACT 200, NEAR 37, SIZE_MISMATCH
  141, STUB 1767). Wave 45 converted 0x0045cd50 (154/154) after giving the
  function a `char` return type (the reference writes `mov al,1`); 0x004e6d80
  and 0x004e6e20 improved to NEAR. 0x00475840 turned out to be a forwarding
  stub and 0x00519a30 a mis-segmented window.
- Row cleanup: 0x00519a30 is annotated inside the 5017-byte 0x00418e90 extent;
  its file was deleted and the row dropped (orphans) to keep lint clean. The
  0x418e90 extent is a discovery over-merge that contains at least two complete
  error-string function bodies and needs its own reviewed repair.
- The GOLD padding sweep continues in the background as the steady producer.

- Round 74: GOLD 57.3 percent (RELOC 2436, +9; SIZE_MISMATCH 149, -9). The
  single GOLD padding sweep continues to be the steady producer. Wave 44 on nine
  NEAR rows with the /Oi and prototype hints converted nothing new; all nine
  park on register-allocation/scheduler deltas (memset expansion ordering was the
  closest, 38/42 exact).
- GOLD totals: RELOC 2436, EXACT 200, NEAR 35, SIZE_MISMATCH 149, STUB 1770,
  matched 57.3 percent. GOLDTL 74.0 percent, server 100 percent. Lint 0/0.
- SIZE_MISMATCH on GOLD has gone from 212 to 149 over the sweep rounds; the
  remaining rows are mostly genuine body differences.

- Round 73: GOLD 57.1 percent (RELOC 2427, EXACT 200, SIZE_MISMATCH 158,
  NEAR 35). The padding sweep is still the only steady producer; several
  duplicate sweep processes had been racing on the same receipt files and
  compiles, so all but one GOLD sweep were stopped (GOLDTL sweeps hit zero
  repairs and were stopped too).
- Wave 43 applied the /Oi-intrinsic hint with mixed results: GOLD 0x00468c60
  improved to NEAR 113/115 through real `memset(e,0,0x14)`; the other eight rows
  parked as pure register-allocation/scheduling classes (no string idioms in
  them).
- Remaining GOLD work: 158 SIZE_MISMATCH (sweep continues on them), 1770 STUB,
  35 NEAR. Clients still far from byte identity; server remains the only
  complete deliverable.

- Round 72: GOLD 57.1 percent. Wave 42 converted GOLD 0x00435810 to **EXACT**
  (95/95): the stub's hand-rolled byte-pair compare was replaced by real
  `strcmp(str, q) == 0`, whose /Oi intrinsic emits the reference's inline byte-pair
  `sbb` idiom. The continuing GOLD padding sweep added six more RELOC rows.
- Split-repair investigation: a scan for rows containing an internal CALL target
  with a prologue found zero rows, and 1030 ret-boundary candidates shrank to
  zero once call-target evidence was required, so no merged-extent rows remain
  detectable today.
- GOLD: RELOC 2425, EXACT 199, NEAR 34, SIZE_MISMATCH 161, STUB 1771, matched
  57.1 percent. GOLDTL 74.0 percent, server 100 percent. Lint 0/0.

- Round 71: GOLD 57.0 percent. Continued padding sweep plus a new split repair:
  lint flagged GOLD.fcn_0042bd30.c (annotation 0x42bd60 inside 0x42bd30), and
  disassembly showed the 96-byte inventory entry was two 48-byte functions
  (0x42bd30 ends ret at 0x42bd5f, 0x42bd60 starts its own prologue and ends ret
  at 0x42bd8f). Repaired with `binary repair-extents 0x0042bd30=48` plus
  `0x0042bd60=48 --add-missing`, then registered the file and tested both rows
  to RELOC 48/48. That is the inverse of the earlier with-padding repairs and
  the first successful split using repair-extents.
- GOLD: RELOC 2422, EXACT 198, NEAR 34, SIZE_MISMATCH 164, STUB 1772, matched
  57.0 percent. GOLDTL 74.0 percent, server 100 percent. Lint 0/0.
- `repair-extents` can both shrink padding tails and split merged entries; the
  only blocked case remains merging an under-split pair (recorded in
  tooling-gaps.md).

- Round 70: +6 GOLD RELOC from the continuing padding-extent sweep. Wave 41 on
  nine parked GOLD rows produced no conversions (all pure register/scheduler
  deltas, for example 0x0047ce50 needs the length in edx not ecx, and 0x00437060
  needs the eax/ecx swap to change the store encoding).
- GOLD: RELOC 2418 (+6), EXACT 197, NEAR 34, SIZE_MISMATCH 167 (-6), STUB 1773,
  matched 56.9 percent. GOLDTL 74.0 percent, server 100 percent. Lint 0/0.
- The sweep receipt file is rewritten on every restart, so the applied-repair
  count must be read from `rebrew status`, not from the latest receipt.

- Round 69: +9 GOLD RELOC, +1 NEAR. Continued sweeps: the GOLD padding-extent
  sweep reached 15 repairs in one 38-row run (restarted runs reload the row list
  and re-process, so the receipt only shows the current run; applied repairs
  persist in metadata). Wave 40 converted GOLD 0x0046cfc0 (RELOC) and lifted
  0x0043d7c0 to NEAR.
- GOLD: RELOC 2412, EXACT 197, NEAR 34, SIZE_MISMATCH 173, STUB 1773, matched
  56.8 percent. GOLDTL unchanged at 74.0 percent (its sweep is at 67 rows with
  zero repairs). Server 100 percent. Lint 0/0.
- The GOLD SIZE_MISMATCH count has fallen from 212 to 173 in three rounds,
  almost all through extent repair.

- Round 68: +11 GOLD matched rows from continued padding-extent sweeps (GOLD
  RELOC 2392 -> 2403, SIZE_MISMATCH 192 -> 181, matched 56.3 -> 56.6 percent).
  The second GOLD sweep (limit 150 over the remaining SIZE_MISMATCH rows) was at
  31 processed / 8 repairs when the round closed and keeps running; repairs are
  applied immediately so they survive the round boundary.
- A parallel GOLDTL sweep (limit 120) processed 44 rows with zero repairs: the
  GOLDTL SIZE_MISMATCH bodies mostly differ in real code, not padding, so that
  class is GOLD-specific.
- Lint 0/0 on all three targets; server 100 percent; GOLDTL unchanged at
  74.0 percent.

- Round 67: **+22 GOLD matched rows** (19 RELOC + 1 EXACT from extent repair, 2
  RELOC from a delegated retry wave). The padding-shrink technique scales: for
  every SIZE_MISMATCH row, run the compiled body; when match_count equals
  obj_size and the recorded tail beyond obj_size is all NOP/INT3 padding, a
  digest-guarded `binary repair-extents <old>=<obj_size>` fixes the inventory
  extent and the row tests RELOC/EXACT. First 40-row batch: 20 repaired, no
  regressions (receipt `.scratch/lead/pad-shrink-gold.json`). A 100-row second
  batch was started and continues into the next round.
- Wave 39 also converted GOLD 0x0047cda0 and 0x0053db90 to RELOC.
- GOLD: RELOC 2392, EXACT 197, SIZE_MISMATCH 192 (-20), STUB 1775, matched
  56.3 percent. GOLDTL unchanged (EXACT 287, SIZE_MISMATCH 892) at 74.0
  percent. Server 100 percent. Lint 0/0.

- Round 66: +1 GOLDTL EXACT from a new extent-repair technique. Wave 38 found
  that GOLDTL 0x00537fe0's reconstructed body is byte-exact at 116 bytes while
  the recorded extent is 128: the last 12 bytes are NOP padding up to the next
  inventory start 0x538060. `rebrew binary repair-extents 0x00537fe0=116`
  (digest-guarded) shrank the inventory extent and the row tests EXACT.
- A scan of the 40 smallest GOLDTL SIZE_MISMATCH rows applied the same test
  (compiled body matches the whole reference prefix AND the recorded tail is all
  NOP/INT3 padding): no further case qualified, so this class is rare. The scan
  receipt is `.scratch/lead/pad-shrink-goldtl.json`.
- Other wave-38 findings: 0x00526660 is a reviewed split head (43 bytes) whose
  tail is fcn.0052668b, another entry for the inventory-merge tool gap;
  0x00406560 and 0x004cf000 park on register allocation.
- GOLDTL: EXACT 287 (+1), SIZE_MISMATCH 892 (-1). GOLD unchanged at 55.9
  percent. Server 100 percent. Lint 0/0.

- Round 65: +1 GOLD RELOC, +1 NEAR. Wave 37 on fresh simple bodies: GOLD
  0x00537e40 (143/143, seven relocations, a call sequencer close to sister
  fcn_004e3060) reached RELOC; 0x00467790 reached NEAR 12/145 with correct
  semantics but different codegen; the rest park on register-allocation and
  scheduling.
- GOLD: RELOC 2371 (+1), EXACT 196, NEAR 33 (+1), SIZE_MISMATCH 212, STUB 1777
  (-2), matched 55.9 percent. Server 100 percent; GOLDTL 74.0 percent. Lint 0/0.
- The fresh simple-body pool is thinning: the 40 remaining candidates are mostly
  the parked reg-alloc class, so future waves should mix in GOLDTL
  SIZE_MISMATCH retries and shape-pair re-matching.

- Round 64: +2 GOLD RELOC and +1 GOLD EXACT. Wave 36 on fresh simple bodies:
  GOLD 0x00435870 (134 bytes) is **EXACT** (the inner compare is an inlined
  strcmp with byte-pair sbb return, toggled byte at obj+0x90+i*0x7c, bit-merge
  `(b & ~2) | ((c<<1)&2)`), 0x00577f90 (129/129) and 0x0058ac10 (135/135) are
  RELOC. Three other rows park on register-allocation/scheduling.
- GOLD: RELOC 2370 (+2), EXACT 196 (+1), NEAR 32, SIZE_MISMATCH 212, STUB 1779
  (-3), matched 55.8 percent. Server 100 percent; GOLDTL 74.0 percent. Lint 0/0.

- Round 63: +2 GOLD RELOC, +1 NEAR. Wave 35 on fresh simple bodies: 0x00463740
  (123/123, event handler with vtable/field calls) and 0x0043e090 (125/125, six
  relocations validated) reached RELOC; 0x00478bc0 reached NEAR 77/122.
  0x0045f640 and 0x0052f2f0 have correct loops but stay SIZE_MISMATCH on tail
  register reloads; 0x0044f7e0 only differs in argument reload (esi reuse).
- GOLD: RELOC 2368 (+2), EXACT 195, NEAR 32 (+1), STUB 1782 (-3), matched
  55.8 percent. Server 100 percent; GOLDTL 74.0 percent. Lint 0/0.

- Round 62: +2 GOLD RELOC. Wave 34 on the next fresh simple-body batch:
  0x0046e980 (113/113, all 9 call relocations validated) and 0x005117c0
  (120/120, filtered-entity walk) reached RELOC. 0x004556d0 and 0x00468c60 have
  correct bodies but tail-only register allocation differences; 0x00541240 and
  0x0053db90 were reconstructed semantically and parked.
- GOLD: RELOC 2366 (+2), EXACT 195, NEAR 31, SIZE_MISMATCH 212, STUB 1785,
  matched 55.7 percent. Server 100 percent; GOLDTL 74.0 percent. Lint 0/0.
- Fresh-wave yield is now tracking ~2-4 RELOC per 9 attempts.

- Round 61: **+4 GOLD RELOC**, the best wave so far. Wave 33 used fresh
  simple-body GOLD rows: 0x004f3700 (114/114, struct-table walk with state-gated
  calls), 0x00402540 (119/119, asymmetric null checks matching the reference),
  0x0052fb00 (119/119) and 0x00476ef0 (119/119) all reached RELOC. One parked
  row (0x0043e180) revealed that its 116-byte inventory record also holds a
  second function at 0x43e1b0 plus nop, so that extent is an over-merge.
- GOLD: RELOC 2364 (+4), EXACT 195, NEAR 31, SIZE_MISMATCH 212, STUB 1787,
  matched 55.7 percent. Server 100 percent; GOLDTL 74.0 percent. Lint 0/0.
- Fresh-batch waves on filtered simple bodies are the highest-yield levers
  (4/9), so keep refreshing the candidate pool each round.

- Round 60: no change. Wave 32 re-ran nine GOLD NEAR rows with the exact-diff
  workflow; all nine parked, confirming the NEAR pool is dominated by pure
  register-allocation/scheduler deltas (for example 0x00411c10 needs
  `add esp,4` and the `mov [0x6310e4],0` swapped; 0x0043b600 needs the v temp in
  edx instead of ecx). Agents verified callee bindings and struct offsets before
  parking. One row briefly demoted to STUB was re-recorded to NEAR 64/101.
- Snapshot unchanged: server 100 percent; GOLDTL 74.0 percent (RELOC 3524,
  EXACT 286, NEAR 89, STUB 294); GOLD 55.6 percent (RELOC 2360, EXACT 195,
  NEAR 31, SIZE_MISMATCH 212, STUB 1791). Lint 0/0 on all three targets.

- Round 59: +2 GOLD RELOC and three NEAR improvements. Wave 31 re-ran nine GOLD
  simple-body rows with diff-driven instructions: 0x005bd340 and 0x005bd2e0
  both RELOC (the missing 5th parameter was the root cause: `.w` and the
  fcn_004760a0 read came from the wrong arguments); 0x0043b600, 0x004734c0 and
  0x00411c10 moved to NEAR with only scheduler/register swaps left.
- GOLD: RELOC 2360 (+2), EXACT 195, NEAR 31 (+3), STUB 1791 (-5), matched
  55.6 percent. Server 100 percent; GOLDTL unchanged at 74.0 percent. Lint 0/0.
- Re-running previous vehicles with the exact-diff workflow is paying off: the
  missing-parameter bug class had been masked as a byte diff.

- Round 58: +2 GOLD RELOC, +1 GOLDTL NEAR. Wave 30 on the next simple-body
  batch: GOLD 0x0052e080 (110/110, deferred add esp 0x30 across three cdecl
  calls) and GOLD 0x0045fb40 (110/110, the shared com60 store shape was the
  key) both reached RELOC; GOLDTL 0x00473610 reached NEAR 31/33 with only an
  edx<->ecx choice for the global base left.
- GOLD: RELOC 2358 (+2), EXACT 195, NEAR 28, SIZE_MISMATCH 212, STUB 1796,
  matched 55.5 percent. GOLDTL: NEAR 88 -> 89, STUB 295 -> 294. Lint 0/0.
- Wave yield improved to 3 improvements per 9 attempts when the reference
  uses ordinary cdecl calls and simple store shapes; register-allocation walls
  still dominate the rest.

- Round 57: +1 GOLD RELOC. Wave 29 on the next simple-body batch: GOLD
  0x00442210 reached RELOC 108/108 (all four relocations validated). Others
  parked; 0x00437060 has an identical mnemonic stream and differs only in
  register allocation (eax<->ecx, cl<->al), the recurring codegen wall.
- GOLD counts: RELOC 2356 (+1), EXACT 195, NEAR 28, SIZE_MISMATCH 212,
  STUB 1798, matched 55.5 percent. Server 100 percent; GOLDTL 74.0 percent.
  Lint 0/0.
- Steady-state throughput is about one converted function per two rounds across
  delegated waves; the remaining client backlog is dominated by regalloc and
  scheduling walls that source-shape edits do not cross.

- Round 56: no change. Wave 28 attacked the nine smallest GOLDTL NEAR rows with
  diff-driven variants; all nine parked. The deltas are genuine scheduler and
  register-allocation classes: argument load order (a2 before a1), push hoisted
  above an indirect-call base load, vtable store interleaved before a guard
  test, lea-vs-mov folding, prologue interleave and memset setup order.
- Conclusion: the NEAR backlog on both clients is dominated by codegen-order
  walls that source-shape edits do not move. Fresh STUB implementation with the
  simple-body filter (waves 25/26) and shape-pair conversion remain the only
  productive levers, both with low yield.
- Snapshot unchanged: server 100 percent; GOLDTL 74.0 percent (RELOC 3524,
  EXACT 286, NEAR 88, STUB 295); GOLD 55.5 percent (RELOC 2355, EXACT 195,
  NEAR 28, STUB 1799). Lint 0/0 on all three targets.

- Round 55: +1 GOLD EXACT. Wave 27 attacked nine NEAR rows with diff-driven
  variants: GOLD 0x0041e670 (82 bytes) reached **EXACT**; the other eight stayed
  NEAR (their remaining deltas are register/ordering classes; one agent
  recommends `rebrew prove` for semantic recording rather than byte chasing).
- GOLD counts: EXACT 194 -> 195, NEAR 29 -> 28, RELOC 2355, STUB 1799,
  matched 55.5 percent. Server 100 percent; GOLDTL 74.0 percent. Lint 0/0.
- Diff-driven NEAR conversion is the better use of delegated rounds than fresh
  stub implementation (one EXACT and no regressions versus two NEAR-only).

- Round 54: no RELOC, two NEAR improvements. Wave 26 on the next simple-body
  filter batch: GOLD 0x00520f50 and 0x00411b00 moved STUB -> NEAR; seven rows
  stayed STUB. GOLD NEAR 27 -> 29, STUB 1801 -> 1799, matched unchanged at
  55.5 percent.
- Yield trend on delegated per-function waves: 2-3 improvements per 9 attempted,
  mostly NEAR not RELOC. Simple-body filtering helps but the easy single-body
  functions are running out; the next batch should target NEAR -> RELOC
  conversions with targeted variants instead of fresh stubs.

- Round 53: +1 GOLD RELOC and +1 GOLD NEAR. Wave 25 used only simple-body
  stubs (no x87, no rep, at most 60 instructions, ends in ret) and correct
  target flags: GOLD 0x00401380 bio_rd_array_quick reached RELOC 135/135
  (earlier attempts had it at 127/135 NEAR); GOLD 0x0041e670 improved
  STUB -> NEAR 82 bytes; five others parked, including all three GOLDTL rows.
- ROI measurement from this round: 9 attempted, 2 improved (1 RELOC, 1 NEAR).
  Filtering by body simplicity raises the hit rate over unselected waves.
- Snapshot: server 100 percent; GOLDTL 74.0 percent (RELOC 3524, EXACT 286,
  STUB 295); GOLD 55.5 percent (RELOC 2355, NEAR 27, EXACT 194, STUB 1801).
  Lint 0/0 on all three targets.

- Round 52: no metric change. Tried three structural ideas that all came back
  empty: (a) no shared source still carries a `#if !defined(REBREW_GOLD)` guard
  after the round-49 unguard, so there is no second unguard-and-rebind batch;
  (b) no GOLDTL STUB shares an attested name with a verified GOLD body, so the
  reverse name conversion has no candidates; (c) `library match` against the
  vendored d3dx8.lib finds 0 GOLD matches, so the small 0x5e-band GOLD STUBs are
  not library bodies that could be marked LIBRARY instead.
- Hand work on 0x0041e0a0 (96 bytes) went from a wrong frame to the correct
  buffer offsets: native uses buf[0]=0x64 and buf[20]=a3 with no spilled result
  register, but all three C forms still compile to 102-108 bytes against the
  96-byte target (first 17-32 bytes match), so the function stays SIZE_MISMATCH.
- Snapshot unchanged: server 100 percent; GOLDTL 74.0 percent (RELOC 3524,
  EXACT 286, STUB 295); GOLD 55.4 percent (RELOC 2354, EXACT 194, STUB 1803).
  Lint 0/0 on all three targets.

- Round 51: no metric change, but a process defect was found and fixed. GOLD
  wave prompts omitted `--target Europa1400Gold.exe` for `rebrew binary asm
  show`/`function`, so those agents read the GOLDTL binary at GOLD VAs and built
  bodies from the wrong bytes. Wave 24 re-ran six affected functions with the
  target flag on every command: all six still park on genuine codegen classes
  (x87 order, memcpy expansion, const-folding, loop-peel scheduling), so the
  earlier conclusions were correct after all. Agents must pass
  `--target Europa1400Gold.exe` on every GOLD command.
- GA (`match run`, 200 generations) on the two best near bodies (0x436070,
  0x440280) found no match; best scores 137296 and 142762 are far from a hit.
  These stay SIZE_MISMATCH-class codegen walls.
- Promotion note: `rebrew test` refuses STUB -> SIZE_MISMATCH without
  `--force-status`, so semantically complete bodies keep a STUB label until the
  next forced run; use it when a body is structurally right.
- Snapshot unchanged: server 100 percent; GOLDTL 74.0 percent (RELOC 3524,
  EXACT 286, STUB 295); GOLD 55.4 percent (RELOC 2354, EXACT 194, STUB 1803).
  Lint 0/0 on all three targets.

- Round 50: +1 GOLD RELOC from wave 23 (0x0040d8d0, 107/107). The same wave
  produced two structurally correct bodies that stay SIZE_MISMATCH
  (0x00436070: VC6 folds memcpy(..,0x20) to rep movsd while the reference uses a
  runtime-length aligned copy; 0x00440280: register allocation and scheduling
  only) and one parked x87 tail (0x004ce200). These near-complete bodies are the
  best `rebrew match` / codegen-sweep candidates for later rounds.
- Name-matched cross-target test: seven GOLDTL bodies whose GOLD twins are STUBs
  match only 69-1285 of 938-5856 target bytes, so the GOLDTL bodies differ
  substantially from the GOLD binaries; WinMain could not be extracted (guarded
  out of the GOLD compile). Only gm_StartFilteredEntitySearch was convertible.
- Snapshot: server 100 percent; GOLDTL RELOC 3524, EXACT 286, STUB 295, matched
  74.0 percent; GOLD RELOC 2354, EXACT 194, STUB 1803, NEAR 26, matched
  55.4 percent. Lint 0/0 on all three targets.

- Round 49: +1 GOLD and +1 GOLDTL row. Waves on both-target STUB pairs found by
  shape matching: 9 pairs, one RELOC (GOLDTL 0x5c86b0); its GOLD twin 0x5bc820
  did not validate (185/191), so no shared conversion.
- New technique that works: shared TUs exclude functions from the GOLD build
  with `#if !defined(REBREW_GOLD)`. Removing such a guard from
  src/Develop/DieGildeAddOn/game/spiel.c let gm_StartFilteredEntitySearch
  compile under REBREW_GOLD, validated 284/284 against the GOLD reference, and
  `rebrew source binding rebind 0x00501190 spiel.c --name ...` bound the GOLD
  row to the shared definition: GOLD 0x501190 is now RELOC. The GOLDTL row
  stayed RELOC.
- Scaling candidate for next rounds: enumerate every guarded definition in
  shared sources whose GOLD twin is a STUB, unguard it, validate with
  `test --target-bin`, then rebind. Name-matched candidates currently number 9
  (eight have SIZE_MISMATCH GOLDTL bodies, one verified).
- Snapshot: server 100 percent; GOLDTL RELOC 3524, EXACT 286, STUB 295
  (74.0 percent); GOLD RELOC 2353, EXACT 194, STUB 1805 (55.4 percent).
  Lint 0/0 on all three targets.

- Round 48: no metric change. Mercury wave 21 on six prologue-verified GOLD
  STUB functions (0x4616c0, 0x4675e0, 0x41e0a0, 0x405610, 0x4f3780, 0x404c20):
  all six parked on register-allocation/scheduling deltas; partial bodies kept
  but STATUS stayed STUB.
- Checked the client data-restore path: `rebrew build layout --data-gap <raw-size>`
  copies the reference `.data` bytes [raw-size:raw-end] into
  crt_region/data_restore.c, and the two client source lists contain no
  crt_region files, so the built clients emit only ~0xe000 raw `.data` bytes
  against the reference's 0x40000. Wiring that scaffolding cannot restore the
  client image until `.text` placement matches; the current data_restore.c only
  covers [0x4600:0xe000].
- Snapshot: server 100 percent; GOLDTL 73.9 percent (RELOC 3523, EXACT 286);
  GOLD 55.4 percent (RELOC 2352, EXACT 194). Lint 0/0 on all three targets.
- Standing constraint: the remaining client work is long-tail body
  reconstruction (fragments blocked by the inventory-merge tool gap), and waves
  on MSVC 6 codegen-wall functions keep returning zero.

- Round 47: tried to repair the over-split inventory pair the wave agents found
  (0x00449630 head, 0x0044964d tail). Disassembly shows a real prologue at
  0x449630 and a `jne 0x44964d` into the same body, so the fix is to extend the
  head extent to 1131 bytes and drop the tail entry. `rebrew binary
  repair-extents 0x00449630=1131` refuses: "0x449630+1131 overlaps next
  inventory start 0x44964d". There is no tool to merge or retire an inventory
  entry, so fragment rows cannot be repaired through the CLI.
- Recorded both pending upstream gaps in [tooling-gaps.md](tooling-gaps.md):
  inventory entry merge/retire for repair-extents, and per-target BSS sources
  for `data layout fill`. The upstream `docs/IDEAS-GUILD.md` is read-only from
  this workspace.
- No metric change this round: server 100 percent; GOLDTL 73.9 percent
  (RELOC 3523, EXACT 286); GOLD 55.4 percent (RELOC 2352, EXACT 194). Lint 0/0
  on all three targets.

- Round 46: fresh GOLDTL verify reports 3839 byte-matched (3552 RELOC + 287
  EXACT), STUB 275, NEAR 88, SIZE_MISMATCH 915, compile errors 0. The stored
  status counts lag the verify pass (3523 RELOC / 286 EXACT at snapshot time).
- Mercury wave 20 on six small GOLDTL STUB rows converted one: 0x00415150 RELOC
  116/116. The other five are mid-body fragments of enclosing functions
  (0x00413030, 0x0041a25c, 0x00449630, 0x00441ab0 family and 0x0041ebca):
  branch targets inside larger bodies, not standalone C functions. One agent
  identified a concrete split pair: 0x00449630 + 0x0044964d belong to one
  function.
- Conclusion for the small-stub backlog: most remaining small STUB rows are
  inventory fragments, so implementing them as standalone functions cannot
  work. Extent repair that merges fragments into their enclosing function is
  the prerequisite; after that the merged bodies still need reconstruction.
- Lint 0 errors / 0 warnings on all three targets (one W005 blocker set for
  src/GOLDTL.fcn_005edf4a.c).

- Round 45: +9 GOLD rows from non-unique shape pairs. Relaxing the shape matcher
  to candidate sets of 2 to 6 produced 18 pairs over 9 GOLD rows; all validated
  against GOLD reference slices and 9 converted (100 to 244 bytes, all RELOC).
  Duplicate anchors in two donor files had to be cleaned up: stacking several
  GOLD anchors for one definition makes registration ambiguous, and moving an
  anchor to a second donor file conflicts with the stored binding until the row
  is dropped and re-registered. Scripts: shape_multi.py, fix_multi.py.
- Mercury wave 19 on six small GOLDTL STUB rows: one became RELOC
  (0x004fdcf0, 119/119); the rest were parked (x87 scheduling tie, STUB bodies
  not editable to a byte match).
- Snapshot: server.dll 100 percent EXACT; GOLDTL RELOC 3520, EXACT 285,
  matched 73.9 percent, coverage 98.8; GOLD RELOC 2352, EXACT 194, STUB 1806,
  matched 55.4 percent, coverage 99.9. Lint 0 errors / 0 warnings on all three
  targets.
- Open item: GOLDTL coverage is 98.8 percent against 99.3 before round 44 with
  the same status counts; 429 library-header rows carry no verdict and the
  accounting changed after the size-repair round. Check with a fresh verify.

- Round 44: tested batch size repair. Reverse-direction shape matching found only
  2 candidate pairs (GOLDTL STUB <- GOLD verified), so that direction is nearly
  exhausted.
- `rebrew verify --fix-sizes` on GOLD promoted 46 SIZE_MISMATCH rows to RELOC;
  one row (0x4e5770) went RELOC -> NEAR and stays unresolved. On GOLDTL the same
  command expanded the stored size of 74 already-matched rows (for example
  284 -> 288), demoting them, so those 75 size changes were reverted with
  `rebrew test --size <old size>`: 64 RELOC and 9 EXACT came back. Do not run
  `verify --fix-sizes` across GOLDTL: its inventory extents are not the
  compiled extents for already-matched rows.
- Also dropped five GOLD rows that had no source file and only a MISSING_SIZE
  placeholder (0x403ab0, 0x4076b0, 0x41e050, 0x44f760, 0x4cd5e0).
- Snapshot: server.dll 100 percent EXACT; GOLDTL RELOC 3550, EXACT 286,
  matched 73.8 percent, coverage 98.8 (429 library-header rows carry no
  verdict; the coverage dip needs a check next round); GOLD RELOC 2343,
  EXACT 194, STUB 1815, matched 55.2 percent, coverage 99.9. Lint 0/0 on all
  three targets.

- Round 43: extended the shape-match conversion to every size and to GOLD
  SIZE_MISMATCH/NEAR rows, not just STUB. 78 unique pairs found and validated
  against GOLD reference byte slices; 14 reached RELOC and 13 were converted
  (one needed its stale GOLD stub file removed after an anchor-conflict error).
  All gained rows test RELOC at full extent (45 to 858 bytes).
  Effect: GOLD RELOC 2325 -> 2339, NEAR 26 -> 24, SIZE_MISMATCH 218 -> 217,
  STUB 1826 -> 1815, matched 54.8 -> 55.1 percent. GOLDTL unchanged.
  Lint back to 0 errors / 0 warnings on all three targets after removing the
  dangling file src/GOLD.fcn_004012b0.c and documenting the shared inline-asm
  evidence for src/GOLDTL.fcn_0042e0e0.c on the GOLD target.
  Receipts: .scratch/lead/shape-pairs2.json, pair-conversion2.json.
- Same-file pairs (21 of them) are genuine near misses: re-testing them left
  their verdicts unchanged, so they need code work, not rebinding.
- Next: run the matcher in the reverse direction (GOLDTL STUB rows against
  verified GOLD bodies) and allow prefix-shape matches where extents differ.

- Round 42: first measured GOLD gain in many rounds. Pair GOLD STUB rows with
  already-verified GOLDTL bodies by instruction-shape fingerprint (capstone
  mnemonics plus operand kinds, so differing addresses and displacements do not
  matter): 68 shape matches, 59 unique. Each candidate was validated against the
  GOLD reference bytes with `rebrew test --target-bin <gold slice> --no-promote`;
  27 matched. Those 27 were converted to shared definitions (GOLD ADDRESS anchor
  stacked on the GOLDTL file, placeholder GOLD stub dropped, GOLD row registered)
  and every one tests RELOC at full extent (84 to 384 bytes).
  Effect: GOLD RELOC 2298 -> 2325, STUB 1853 -> 1826, matched 54.2 -> 54.8
  percent; GOLDTL unchanged. Lint 0/0 on all targets.
  Method scripts: .scratch/lead/shape_match.py, validate_pairs.py,
  convert_pairs.py; receipts shape-pairs.json, pair-validation.json,
  pair-conversion.json.
- Next scale-up: the same method with larger size cutoffs, and pairing against
  GOLD SIZE_MISMATCH/NEAR rows as well as GOLDTL bodies, should convert more
  shared functions per round.

- Round 41: measured how many GOLD STUB rows are interior fragments. A
  capstone scan of the reference .text flagged 32 of 1847 stub rows whose first
  byte is entered by fall-through or mid-instruction (evidence: scan script
  .scratch/lead/fragment_scan.py). Probe drops showed the fragment handling needs
  care: six rows were dropped, then restored with `rebrew source register` +
  `rebrew test --size` and given BLOCKER text; all 32 candidates are back as
  STUB rows with their inventory sizes and blockers. GOLD STUB count and
  coverage are unchanged.
- Conclusion: fragment noise is small (32 candidates), so the 1853 GOLD STUB
  rows are mostly genuine standalone functions that need real bodies. The path
  to GOLD byte identity is long-tail implementation, not row cleanup.
- Lint is back to 0 errors / 0 warnings on all three targets after re-documenting
  fill0/copy0 assembly evidence (the source hash drifted again) and setting the
  32 restored BLOCKER texts.
- Snapshot: server.dll 100 percent EXACT; GOLDTL 74.2 percent (RELOC 3519,
  EXACT 285, STUB 297); GOLD 54.2 percent (RELOC 2298, EXACT 194, STUB 1853).

- Round 40: tested whether small GOLD STUB rows are interior fragments. Three
  delegated agents parked all six assigned rows as fragments, so six GOLD rows
  were dropped, then `rebrew binary xrefs` showed five of the six are real call
  targets in the reference (0x4076b0, 0x47ce20, 0x4cd5e0, 0x403ab0, 0x41e050),
  not fragments. All six rows were restored with `rebrew source register`, the
  inventory sizes re-applied with `rebrew test --size` (STUB verdicts), and
  BLOCKER text set. 0x44f760 has no xrefs and remains the only candidate that
  might not be a function entry.
- Lesson recorded: a parked "interior fragment" claim must be checked against
  native xrefs before any row is dropped; dropping inventory rows changes the
  coverage denominator and is not reversible through metadata alone.
- Lint refreshed back to 0 errors / 0 warnings on all three targets after
  re-documenting the fill0/copy0 assembly evidence (their source hash changed in
  the round 38 revert) and rebinding four stale GOLD type entries.
- GOLD state unchanged: 2507 matched (54.2 percent), 1853 STUB, coverage 99.9.

- Round 39: re-verified both clients. GOLDTL: 5122 rows, 3835 byte-matched
  (3549 RELOC + 286 EXACT; 31 library rows included in the 3835 headline),
  NEAR 81, STUB 278, SIZE_MISMATCH 923, compile errors 0. GOLD: 4604 rows,
  2507 byte-matched (2313 RELOC + 194 EXACT), NEAR 26, STUB 1852,
  SIZE_MISMATCH 219, compile errors 0. `rebrew status --all-targets`:
  server.dll 100 percent matched; GOLDTL 74.2; GOLD 54.2 (coverage 99.9).
- Mercury wave 17 on four small GOLDTL near/stub candidates: both of agent 1's
  targets (0x0041a8c3, 0x00423670) are interior fragments of enclosing
  routines, not self-contained functions; parked with no C edits. Agent 2's
  pair was still running when the round closed.
- The dominant remaining GOLD gap is structural: 1852 STUB rows and a source
  list about 487 files shorter than GOLDTL's, because shared TUs only carry
  GOLDTL module rows. Client byte identity needs that cross-target row mapping
  plus per-target BSS sources, not more per-function waves.

- Round 38: **server.dll is byte-identical to the reference and the gate
  passes.** Deleted build/server.dll, rebuilt with
  `cmake --build build --target server_dll`, and the SHA-256 matches
  original/Server/server.dll (3cc2ce90...). `scripts/gate.sh` reports GATE:
  pass: 316/316 functions, 652/652 data rows, whole-binary
  sections/exports/imports/relocations/rsrc/headers/layout all true, residue 0,
  raw-link .data 0, wine load OK, toolchain alignment OK for all three targets,
  lint 7341 passed / 0 errors / 0 warnings.
- The last 8 bytes were already fixed in the committed SERVER variant of
  gm_GetEntityTableEntry: it carries a redundant empty bounds guard
  (`if (table_index >= 0 && table_index < 0x10) { }`) before the real check.
  The form reproduces the reference register allocation and test order
  (RELOC 66/66, semantically identical) but is not evidenced as the original
  source shape; a plausible single-check derivation remains an open question.
- A `data layout own` experiment for the clients was fully reverted: it
  replaced extern declarations with wrongly typed definitions (C2040, C2371)
  and appended about 1.5 MB of unsafe pads. 68 files carrying only those edits
  were restored from HEAD; the four files with later source work had only the
  inserted definitions removed.
- Client state: RELOC 3519, EXACT 285, NEAR 81, SIZE_MISMATCH 904, STUB 297,
  EXTRACT_ERROR 5; matched 74.2 percent. GOLD links only as a stub scaffold;
  GOLDTL link still fails. Client byte identity and the per-target BSS/data
  ownership remain the work.

- GOLDTL `rebrew status`: RELOC 3513, EXACT 285, NEAR 74, SIZE_MISMATCH 898,
  STUB 254, EXTRACT_ERROR 1; matched 75.0%, coverage 99.3% (5025/5059),
  file similarity 1.2%.
- Round 10: three deepseek-flash agents on fresh rows (1 EXACT, 6 NEAR
  improvements, two size corrections), then three Mercury-3 agents via a
  `workflow` provider/model override on uncovered inventory functions. Mercury
  added 6 verified RELOC: 0x496480 92/92, 0x4cb5d0 117/117 (SIZE 128->117),
  0x4cdb10 127/127, 0x4f8730 208/208, 0x4f8800 208/208, 0x4cdb90 281/281.
  Receipts `.scratch/agent-{a2,b2,c2}/`, `.scratch/mercury/agent-{1,2,3}.md`,
  `.scratch/lead/verify-round2.json`, `.scratch/lead/verify-wave3.json`.
- Lead cleared six uncovered functions: 0x5435d0 EXACT 6/6, 0x465e60 EXACT
  68/68, 0x510b40 EXACT 47/47, 0x4d7f70 RELOC 34/34, 0x55c700 RELOC 54/54,
  0x41a8d0 RELOC 127/127.
- Mercury-3 is reachable with `workflow` `{provider: "inception", model:
  "mercury-3"}`; the plain `subagent` tool always inherits the session model.
- Round 11: Mercury wave on the 12 remaining standalone uncovered rows covered
  them (all now STUB, honest partial bodies) so coverage is 99.5% (5037/5059).
  A NEAR-conversion wave promoted 0x004284d0 RELOC 592/592 (do-while copy loop);
  the other 14 rows are scheduler/allocator ties, 0 converted. Lead restored
  the 0x4f0f60 regression (SIZE 133, SIZE_MISMATCH 39/133).
- Round 12: guaranteed-win class found. A SIZE_MISMATCH row whose `match_percent`
  is 100 has a stored SIZE that still includes inter-function alignment nops:
  trimming to the disassembly-proven code end converts it directly. Applied:
  0x004a5340 SIZE 352->350 RELOC 350/350 and 0x0045fd70 SIZE 3152->3140 RELOC
  3140/3140 (+3140 matched bytes). Mercury wave on 15 SIZE_MISMATCH rows
  176-320B produced complete semantic bodies but no byte promotions; all parked
  on register-allocation/x87/emission-order deltas.
- Round 13: ran the prepared closure pipeline
  (`.scratch/closure/run_closure.py`). The client build compiled 4890 sources but
  both client links fail: GOLDTL 1258 unresolved externals (520 game functions,
  54 invented `sub_*` placeholders from partial-body waves, 1154 undefined data
  globals). Server target separately fails with 9 unresolved externals
  (`fcn_005037c0/00503930/0051af00/005d78e0`, `g_14cbca0/679060/699364/773d75/
  773da8`), all referenced from shared TUs command.c, lobbycommands.c,
  friedhof_logic.c whose bodies are client-specific. Data/whole-binary/gate
  steps therefore could not run. **The previous `build/` deliverable artifacts
  (client exes and server.dll) were replaced/removed by the rebuild and are not
  recoverable from this tree until the link works again.** Lint still passes
  7286/7287 files with the one pre-existing duplicate-VA error.
- Round 14: server link repaired and server deliverable restored.
  `rebrew verify --target server.dll` now measures with current sources:
  313/316 byte-matched (41 EXACT, 272 RELOC), 3 failing rows:
  gv_MoveSlotEntry 674 SIZE_MISMATCH, gm_AllocRaum 742 SIZE_MISMATCH,
  gm_GetEntityTableEntry 66 NEAR 55/66. Mercury agents added
  `#ifdef REBREW_SERVER` variants in shared TUs: cm_ExAllocGraveyardWorker
  52/52, cm_ExAllocAlchemist 52/52, cm_ExSimSpecialAction 262/262, and
  lb_ExPlayerRecordBroadcast 247/247 all RELOC; client bodies unchanged.
  `cmake --build build --target server_dll` exits 0 and rebuilds
  build/server.dll (286720 bytes). Receipts `.scratch/mercury5/agent-{1,2,3}.md`,
  `.scratch/lead/server-verify.json`, `.scratch/closure/server-rebuild3.log`.
- Round 15: two of the three failing server rows fixed by Mercury agents:
  gv_MoveSlotEntry server 674/674 RELOC and gm_AllocRaum server 742/742 RELOC
  (the latter had been 32 bytes short, shifting 35 downstream functions by
  -0x20). Rebuilt server.dll: 9033 differing bytes (was 52309), .text
  VirtualSize now exactly 0x22846, raw-link text placement 251/251 correct,
  server verify 315/316 byte-matched. Remaining server row:
  gm_GetEntityTableEntry NEAR 55/66 (index register EAX vs ECX).
- Round 16: server data drift cleared. Root cause was two missing
  gm_AllocRaum log literals in the server variant (the body referenced raw
  addresses 0x10031484/0x100314bb instead of the strings, so they were absent
  from .data and shifted 2464 bytes). Replaced with the exact literals: server
  data verification now 652 rows, 0 mismatched, 0 missing (was 29/7); .data and
  .rdata sections are byte-identical; file residual 9033 -> 4119 bytes.
- Round 17: replaced raw-address operands with the named globals in the two
  shared-TU server bodies (g_slot_table, g_entity_table_end,
  g_worker_entry_count, g_next_object_id, g_current_season,
  g_entity_slot_table, g_output_share, g_entity_id_field) and used the real
  __FILE__ literal in gm_AllocRaum. The reloc records now match: residual fell
  from 4119 to **8 bytes**, and every gate line passes except whole-file
  identity: size, .text, .rdata, .data, .reloc VirtualSize, imports 100/100,
  export names/VAs, Exit and Init bodies, entry point.
- Remaining residue: exactly 8 bytes at 0x100184ff..0x10018506 inside
  gm_GetEntityTableEntry (server). Best source form keeps the nibble index in
  EAX (matching the reference) but emits the two bounds tests in the opposite
  order; `table_index < 0x10 && table_index >= 0` is 58/66, the natural
  `>= 0 && < 0x10` order is 55/66 with the index in ECX. GA (400 gen),
  hill-climb, ~30 lead variants and a further Mercury attempt all failed.
- Round 18: Mercury client wave on ten SIZE_MISMATCH rows (0x402d00, 0x407390,
  0x408320, 0x40ed40, 0x40f9d0, 0x412b10, 0x412f10, 0x413480, 0x413e00,
  0x415510) produced faithful bodies but no byte promotions; blockers are the
  usual allocator/scheduling ties plus missing data rows for six globals at
  0x415510 and an inventory over-merge at 0x40f9d0 (needs an extent split with
  the 0x40fb80 init function).
- Round 19: more last-8-byte attempts (early-out forms, long/pointer/modulo
  index types, LLM-seeded GA). GOLDTL and GOLD variants of the same function
  show the identical target pattern (bounds `test/jl` first, index in EAX), so
  the C form is shared and still unknown. `rebrew match run --seed-llm` has no
  configured LLM endpoint in this checkout. Server remains at 8 differing bytes
  with build/server.dll rebuilt from the 58/66 form.
- Round 20: first full GOLD re-measure after the waves:
  `rebrew verify --target Europa1400Gold.exe` = 4604 rows, 2507 byte-matched
  (194 EXACT, 2313 RELOC), 1852 STUB, 219 SIZE_MISMATCH, 26 NEAR
  (`.scratch/lead/gold-verify.json`).
- Merged-extent repair batch running (`apply_merge_repairs.py`): 53 stored-size
  over-merges verified by capstone (stored extent spans later inventory function
  starts; inventory size ends exactly on ret/jmp) are re-sized through
  `rebrew test --size`, and the inner inventory functions get skeletons so they
  become covered work items. 14 applied so far, no promotions yet; receipts
  `.scratch/lead/merge-repair-results.json`.
- One reviewed case completed: 0x40f9d0 stored 768 -> 430 and the previously
  missing 0x40fb80 row created (inventory already knows it as a separate
  328-byte function).
- GOLDTL now reports 5075 inventory functions (up from 5059 as rows are
  admitted), 5038 covered, RELOC 3516, EXACT 285, NEAR 78, SIZE_MISMATCH 890,
  STUB 268; matched 74.8 percent is denominator growth, not loss.
- Round 21: merged-extent batch completed 39 reviewed resizes. Two rows were
  wrongly shrunk because the inventory over-splits them; reverted:
  0x570960 back to 1926 (RELOC 1926/1926) and 0x45c380 back to 560 (RELOC
  560/560). The repair script now auto-reverts any resize whose compiled body
  already fills the old extent. Inner-function skeletons admitted about ten new
  rows; one bogus row (0x45c554 inside the 0x45c380 body) was dropped with
  `rebrew orphans drop`. Status: RELOC 3517, EXACT 285, NEAR 79,
  SIZE_MISMATCH 888, STUB 313; 5123 inventory functions, 5083 covered
  (99.2 percent), matched 74.2 percent (denominator now includes the admitted
  rows).
- A Mercury wave on six large client rows (800-1200 bytes) parked all six on
  frame/scheduling deltas (`.scratch/mercury8/`); a second small-row wave
  confirmed 0x494740 RELOC 213/213 and parked its other seven rows.
- Round 22: cleaned the last inventory over-split damage: the metadata rows and
  skeleton files created inside the real 1926-byte function 0x570960
  (0x570ad7, 0x570def, 0x570e5b, 0x570e8b, 0x570ebb, 0x570eeb, 0x570f75,
  0x571020) were dropped with `rebrew orphans drop` and their sources deleted.
- `rebrew test --cflags` persists the flag override into per-function metadata,
  which then breaks `cmake` configure: `rebrew build cmake-flags` refuses a
  translation unit whose functions resolve to different flags. The server
  spiel.c rows had accumulated mixes of `/O2 /Gd`, `/DREBREW_ALLOW_NAKED /O2
  /Gd` and `/O2 /Gd /Ob1` from earlier sweeps. 22 rows were normalized back to
  `/O2 /Gd`; their RELOC/EXACT verdicts survived, configure and the server link
  succeed again and server.dll is still 8 bytes from identity.
- Status after cleanup: RELOC 3517, EXACT 285, NEAR 79, SIZE_MISMATCH 888,
  STUB 330, 5123 rows / 5100 covered (99.5 percent), matched 74.2 percent.
- Round 23: implemented the newly admitted inventory functions with a Mercury
  wave. Verified promotions: 0x0058fa20 RELOC 30/30 (size 32->30, two trailing
  nops), 0x0044f010 RELOC 205/205, and 0x004eb180 RELOC 148/148 (size 160->148,
  twelve trailing nops). 0x00536b8e is NEAR 29/30 (one structural byte; needs
  the preceding function in the same TU for the shared-ret tail-merge).
- The same wave classified four more admitted rows as interior fragments and
  they were dropped with `rebrew orphans drop` plus source deletion: 0x004c38eb,
  0x004c4268, 0x004d16da, 0x0052668b. 0x004c3800 is a real function start but
  still STUB.
- Status: RELOC 3520, EXACT 285, NEAR 80, SIZE_MISMATCH 888, STUB 322;
  5123 rows, 5096 covered (99.4 percent), matched 74.2 percent. Lint: one
  pre-existing duplicate-VA error, 59 warnings.
- Round 24: checked the remaining admitted rows and client rows; no STATUS
  gains. Four more admitted rows turned out to be interior fragments of
  neighbouring functions (0x00474e5d, 0x00526b37, 0x004c70fa, 0x005b104c) and
  were dropped with their sources. 0x004c3800, 0x005a6e90 and 0x0058f6a0 are
  real function starts but remain STUB skeletons; their Mercury agent returned
  no work. The five 220-320 byte client rows (0x43a720, 0x4488e0, 0x44b340,
  0x454460, 0x455d30) reconstruct logically but diverge only in /O2 codegen
  (register allocation, scheduling, library-call expansion) and were parked.
  The reviewed extent-trim batch was rerun to 10 rows with 0 promotions and
  then stopped: trimming stored extents no longer converts rows.
- Status: RELOC 3520, EXACT 285, NEAR 80, SIZE_MISMATCH 888, STUB 318;
  5123 rows, 5092 covered (99.3 percent), matched 74.2 percent. Server.dll
  still differs in 8 bytes.
- Round 25: automated matching was tried as an alternative to manual bodies and
  produced nothing. `rebrew match batch --near-miss --threshold 4` selected zero
  rows; `--improve` on 12 near rows ran for 25 minutes without a win;
  per-row `rebrew match run --mutation-focus register` on the closest
  NEAR_MATCHING rows (0x4b64b0 at a 1-byte delta, 0x4a0bb0 at 1 byte, then
  2-byte rows) also failed (best_score stagnates, no exact).
- Round 26: generated the missing layout package for GOLDTL with
  `rebrew build layout` (layout/Europa1400Gold_TL.exe/: header/iat/prefix/
  bookkeeping/data/reloc hex, operands/calls, layout.fingerprint,
  rebrew-layout.toml; plus src/Europa1400Gold_TL.exe.def). The package is
  untracked scaffolding and still needs review before it is wired into a build.
- First data-ownership audit with the package: 626 unowned data rows, 0
  duplicate owners, 1 violation; `data layout fill --dry-run` would add 48
  initialized-data and 201 BSS pads. This is the concrete data work left before
  the client link can be closed; named-but-undefined globals are a separate
  class from the pads.
- Round 27: analysed the client link failures for symbol-identity work. The
  build log carries 1231 unresolved symbols; 243 look like `fcn_<VA>`
  placeholders, and 188 of those have a metadata identity at the same VA with a
  real attested name (for example `fcn_004012b0` -> `_ReadVfsFourDwords`,
  `fcn_0041db70` -> `_m_alloc`). Binding them would fix the caller names, but
  `rebrew source rename fcn_004012b0 GOLDTL.0x004012b0` refuses with "binding
  source must be an unbound placeholder", so the placeholder first has to be
  registered through the source-registration path; that path needs review before
  a bulk run.
- Mercury wave on the last real skeleton functions (0x4c3800, 0x5a6e90,
  0x58f6a0): bodies written from disassembly, all still SIZE_MISMATCH
  (21/371, 28/805, 226/896). 0x45c554 reconfirmed as an interior fragment.
- Round 28: placeholder binding works for names that are not bound in any
  module. `rebrew source rename fcn_00402ab0 GOLDTL.0x00402ab0` binds caller
  references to the attested identity when the placeholder name has no
  registered owner; 7 of the 36 attempted names refused (ambiguous or already
  bound). A guarded batch (dry-run digest, then apply with --expected-digest)
  applied 29 bindings across 36 attempts before the round closed; the remaining
  list is `.scratch/lead/free-placeholders-remaining.json` (180 candidates
  total). A wave-14 file needed its ADDRESS anchor moved above the definition
  after lint flagged a duplicate VA; lint is back to the one pre-existing
  E013 error.
- Round 29: GOLD client links again. The only unresolved symbol was
  `_g_f83654`, a zero-initialized module pointer in the GOLD .data tail
  (VA 0x00f83654, RVA 0xb83654 inside the zero-filled .data virtual tail). It is
  now defined in its use-site TU src/GOLD.fcn_004a8650.c; the earlier extern-only
  declaration was ours. build/Europa1400Gold.exe is rebuilt (819,200 bytes vs
  the 2,301,952-byte reference: the missing ~1.48 MB is the client's large
  virtual .data/BSS layout, so file identity is still far off).
- GOLDTL client still fails to link with 1236 unresolved externals (was 1258);
  the placeholder binding batch has applied 35 of 53 attempted (116 candidates
  remain in `.scratch/lead/free-placeholders-remaining.json`).
- GOLD data verification against the new build: 321 rows, 0 exact, 32 drift in
  the sampled output, 50 missing (strings, CRT/DirectX literals, table pointers).
- Round 30: generated the GOLD layout package and found the client BSS path.
  `rebrew data layout fill --target Europa1400Gold.exe` would add 19 init pads
  and 264 BSS pads, but it writes them into `src/bss_layout/bss_late.c`, the
  file the SERVER links after the CRT (generated by scripts/gen_bss_layout.py).
  That edits the server's layout, so the file was reverted and the server
  rebuilt back to its 8-byte residue. Rebrew needs per-target BSS sources before
  the client BSS can be generated safely; the gap is recorded here because the
  upstream `docs/IDEAS-GUILD.md` append is blocked by the read-only workspace
  sandbox.
- The client size gap is now the top item: reference GOLD is 2,301,952 bytes
  while the build is 819,200, missing the ~1.48 MB zero-filled `.data`/BSS tail
  that the server reproduces with bss_head/bss_late objects. Clients have no
  equivalent generated BSS sources yet.
- Round 31: GOLD client structure diagnosed. The built GOLD .text is only
  742,582 bytes (virtual) against the reference's 2,006,532, and its source list
  is 4458 files against GOLDTL's 4945. The GOLD target only includes files that
  carry GOLD module rows; shared implementation files whose rows are bound to
  GOLDTL are excluded, so ~487 files of shared code are missing from the GOLD
  link. The reference .data gap (built raw 0xe000 vs 0x40000) is the other half
  of the 819,200 vs 2,301,952 file-size difference.
- `rebrew source import-related --from Europa1400Gold_TL.exe --target
  Europa1400Gold.exe --candidates-only --dry-run` fails with "cannot extract a
  conditional definition from a multi-function file". Cross-target row import is
  therefore blocked until shared multi-function TUs are split, or per-VA
  anchors for the destination module are added another way.
- Round 32: found that both client links use auto-generated scaffold stubs:
  stubs/gold/symbol_stubs.c (6727 lines, 944 stub functions, 947 stub globals)
  and stubs/goldtl/symbol_stubs.c (4218 lines), wired into CMake at
  CMakeLists.txt:420/464. The GOLD map shows symbol_stubs.c.obj contributing
  2890 symbols, which is why the built .text is only 742,582 bytes. Client links
  are scaffold-level, not reconstruction-level; CMake regenerates the stubs from
  unresolved symbols.
- 686 of the GOLD stub functions have a metadata identity by name, but the
  callers in shared sources reference GOLDTL-module placeholder symbols
  (fcn_<GOLDTL VA>) that the GOLD link cannot resolve. A GOLDTL-row ->
  shared-attested-name mapping is needed, and it does not exist yet: GOLDTL rows
  with `_fcn_<VA>` symbols all have placeholder names too, so there is no
  attested-name bridge to the GOLD rows.
- `rebrew source import-related` cannot help GOLD ("no unmatched functions in
  target Europa1400Gold.exe"), and its multi-function-file extraction still
  blocks a bulk cross-target run.
- Round 33: fresh full verify after the rename/repair rounds: 5123 rows,
  byte_matched 3804 game rows (RELOC 3519 + EXACT 285; verify's 3835 headline
  also counts 31 library rows). NEAR 81, SIZE_MISMATCH 904, STUB 297,
  EXTRACT_ERROR 5 (all pre-existing: one `@fcn_...@4` decoration row and four
  D3DX8-band rows), MISSING_SIZE 1.
- Fixed the round's only compile error: src/GOLDTL.fcn_00519190.c declared
  `int __cdecl strncat(char*, char*, unsigned)` next to <string.h> (C2040);
  the local declaration was removed and the row now compiles to SIZE_MISMATCH
  448/7536.
- Stub mapping analysis (`.scratch/mercury13/`): GOLD stubs 938 functions
  (4 attested twins, 687 placeholder-only with a GOLDTL row at the same VA,
  50 VA-twins where GOLDTL has an attested name at that VA, 197 no-row);
  GOLDTL stubs 303 functions (0 attested, 31 placeholder-only, 6 VA-attested,
  266 no-row). Top GOLD stub consumer is GOLDTL.fcn_004a1130.c (102 refs).
  The 56 VA-attested mappings give usable canonical names for shared sources;
  the 687/31 placeholder-only set still needs code-based VA matching.
- Round 34: TU-context hypothesis for the last server 8 bytes tested and
  refuted. Two agents built isolated and full-file copies under .scratch/ with
  the real plain-SP5 profile: isolated single-function TU, whole spiel.c, dummy
  prototypes before/after, first/last position all give the same codegen (the
  full file equals the isolated body byte for byte). The processor-pack profile
  gives 25/66, so the server reference was not built with it. The reference
  shape (bounds test order >=0 then <16 with the index kept in EAX) is
  unreachable from the tested C forms; 58/66 remains the best.
- Cross-target naming gap quantified: 920 GOLD stub placeholders, 743 of which
  have a GOLDTL row at the same VA, but only 19 of those VAs also exist in the
  GOLD module; 56 stub placeholders have a GOLDTL attested name at that VA.
  Resolving the stubs needs code-based GOLDTL->GOLD VA matching for ~687
  functions, which no tool currently provides.
- Lint: 1 pre-existing E013 error, 111 warnings (59 W005 stubs missing blocker
  text, 26 W029 redundant cflags left by the flag normalization because there is
  no CLI to clear a per-function cflags override, 13 W027 long lines, plus stale
  type evidence and data-section warnings).
- Server.dll still differs in 8 bytes.
- Round 31: GOLD client structure diagnosed. The built GOLD .text is only
  742,582 bytes (virtual) against the reference's 2,006,532, and its source list
  is 4458 files against GOLDTL's 4945. The GOLD target only includes files that
  carry GOLD module rows; shared implementation files whose rows are bound to
  GOLDTL are excluded, so ~487 files of shared code are missing from the GOLD
  link. The reference .data gap (built raw 0xe000 vs 0x40000) is the other half
  of the 819,200 vs 2,301,952 file-size difference.
- `rebrew source import-related --from Europa1400Gold_TL.exe --target
  Europa1400Gold.exe --candidates-only --dry-run` fails with "cannot extract a
  conditional definition from a multi-function file". Cross-target row import is
  therefore blocked until shared multi-function TUs are split, or per-VA
  anchors for the destination module are added another way.
- Round 32: found that both client links use auto-generated scaffold stubs:
  stubs/gold/symbol_stubs.c (6727 lines, 944 stub functions, 947 stub globals)
  and stubs/goldtl/symbol_stubs.c (4218 lines), wired into CMake at
  CMakeLists.txt:420/464. The GOLD map shows symbol_stubs.c.obj contributing
  2890 symbols, which is why the built .text is only 742,582 bytes. Client links
  are scaffold-level, not reconstruction-level; CMake regenerates the stubs from
  unresolved symbols.
- 686 of the GOLD stub functions have a metadata identity by name, but the
  callers in shared sources reference GOLDTL-module placeholder symbols
  (fcn_<GOLDTL VA>) that the GOLD link cannot resolve. A GOLDTL-row ->
  shared-attested-name mapping is needed, and it does not exist yet: GOLDTL rows
  with `_fcn_<VA>` symbols all have placeholder names too, so there is no
  attested-name bridge to the GOLD rows.
- `rebrew source import-related` cannot help GOLD ("no unmatched functions in
  target Europa1400Gold.exe"), and its multi-function-file extraction still
  blocks a bulk cross-target run.
- Round 33: fresh full verify after the rename/repair rounds: 5123 rows,
  byte_matched 3804 game rows (RELOC 3519 + EXACT 285; verify's 3835 headline
  also counts 31 library rows). NEAR 81, SIZE_MISMATCH 904, STUB 297,
  EXTRACT_ERROR 5 (all pre-existing: one `@fcn_...@4` decoration row and four
  D3DX8-band rows), MISSING_SIZE 1.
- Fixed the round's only compile error: src/GOLDTL.fcn_00519190.c declared
  `int __cdecl strncat(char*, char*, unsigned)` next to <string.h> (C2040);
  the local declaration was removed and the row now compiles to SIZE_MISMATCH
  448/7536.
- Stub mapping analysis (`.scratch/mercury13/`): GOLD stubs 938 functions
  (4 attested twins, 687 placeholder-only with a GOLDTL row at the same VA,
  50 VA-twins where GOLDTL has an attested name at that VA, 197 no-row);
  GOLDTL stubs 303 functions (0 attested, 31 placeholder-only, 6 VA-attested,
  266 no-row). Top GOLD stub consumer is GOLDTL.fcn_004a1130.c (102 refs).
  The 56 VA-attested mappings give usable canonical names for shared sources;
  the 687/31 placeholder-only set still needs code-based VA matching.
- Round 34: TU-context hypothesis for the last server 8 bytes tested and
  refuted. Two agents built isolated and full-file copies under .scratch/ with
  the real plain-SP5 profile: isolated single-function TU, whole spiel.c, dummy
  prototypes before/after, first/last position all give the same codegen (the
  full file equals the isolated body byte for byte). The processor-pack profile
  gives 25/66, so the server reference was not built with it. The reference
  shape (bounds test order >=0 then <16 with the index kept in EAX) is
  unreachable from the tested C forms; 58/66 remains the best.
- Cross-target naming gap quantified: 920 GOLD stub placeholders, 743 of which
  have a GOLDTL row at the same VA, but only 19 of those VAs also exist in the
  GOLD module; 56 stub placeholders have a GOLDTL attested name at that VA.
  Resolving the stubs needs code-based GOLDTL->GOLD VA matching for ~687
  functions, which no tool currently provides.
- Lint: 1 pre-existing E013 error, 111 warnings (59 W005 stubs missing blocker
  text, 26 W029 redundant cflags left by the flag normalization because there is
  no CLI to clear a per-function cflags override, 13 W027 long lines, plus stale
  type evidence and data-section warnings).
- Server.dll still differs in 8 bytes.
- Lesson: inventory fresh discovery can over-split as well as over-merge, so
  every extent repair must be reverted when the compiled body fills the old
  extent, and flag experiments must not persist CFLAGS into metadata.
- Client-side regressions checked: 0x4f9300 RELOC 236/236, 0x4cda90 RELOC,
  0x4cda90 and 0x509570 NEAR unchanged.
- Next: the last 8 bytes of gm_GetEntityTableEntry (bounds-test order vs
  register allocation). Ideas: statement-level search with an EAX-affine
  expression before the check, `rebrew match run --seed-llm`, or prove/document
  the divergence if no C form exists. After that the both clients' links (1258
  unresolved externals) and the extent-trim batch.
- Next: finish/review the trim batch; mine `match_percent` 100 rows after every
  batch; remaining uncovered fragments (0x4d0963/0x4d099d/0x54fd0a/0x51463d
  interior blocks need extent merges); same-TU co-location rows; fresh client
  link after the source churn.
- GOLD: RELOC 2322, EXACT 189, NEAR 13, SIZE_MISMATCH 219, STUB 17; matched 2511.
- SERVER: EXACT 315, RELOC 1; matched 316.
- Rewrite queue .scratch/wave2/rewrite-all.json; decision log .scratch/wave2/DECISIONS.md;
  extent queue .scratch/wave2/EXTENT-QUEUE.md; non-C ledger .scratch/wave2/NONC-ROWS.md.
- Current wall classes: byte-positional scoring, first-vs-last cdecl tail merge,
  allocator register ties, type-class slot ordering, body-gated frames/prologues,
  hand-written block-fill prelude (inline asm authorized), MSVC 6 ICE on some
  oversized bodies, and driver probes needing /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp.


## Delegated reconstruction waves, 2026-10-19

Work resumed on the goal. Waves of ten subagents, ten isolated per-function
STUB files each, ran against the default target `Europa1400Gold_TL.exe`.
Local receipts are under `.scratch/wave2/` and `.scratch/wave3/`.

Wave 2 attempted 100 targets and the lead reproduced every non-STUB verdict
with a fresh official `rebrew test` (`.scratch/wave2/verify-changed.json`):
**14 RELOC**, 2 NEAR_MATCHING, 10 SIZE_MISMATCH, 3 EXTRACT_ERROR, 71 still
STUB. Twelve of the RELOC bodies are game code; they are byte-identical after
relocation masking with their operands validated. This is object progress, not
linked EXACT: the raw link has not been rebuilt.

The wave-2 selector did not read the target's `external_ranges`, so 53 of 100
assigned files were statically linked D3DX8 bodies (`0x5e0000..0x64ffff`,
declared external in `rebrew-project.toml`). Those are not game source and
their `__thiscall`/C++ ABIs cannot be emitted by C89. The same batch measured
many inventory over-merges (one stored extent covering two to six adjacent
functions or alignment padding), which C cannot close; they need reviewed
`rebrew binary repair-extents` work.

Wave 3 ran on the validated-extent game queue with the library band excluded.
The lead reproduced the 29 promoted verdicts with a fresh official `rebrew
test` (`.scratch/wave3/verify-changed.json`): **23 RELOC** (all
byte-identical after relocation masking, operand bindings validated where
recorded) and **6 NEAR_MATCHING**. The other attempted rows keep faithful
partial bodies whose measured SIZE_MISMATCH is not promoted to STATUS by the
default policy; their reports record extent-repair specs and unresolved
operand/data-row gaps. Inline `__asm { int 3 }` for evidenced debug-break
traps is an accepted lead decision (`.scratch/wave2/DECISIONS.md`).

Wave 4 ran on the remaining validated game extents (larger bodies, 135-625
bytes). The lead reproduced its promoted verdicts
(`.scratch/wave4/verify-changed.json`): **1 RELOC** and **3 NEAR_MATCHING**;
the rest are faithful bodies recorded as forced SIZE_MISMATCH (61 rows), which
now persists through `--force-status`. Larger bodies mostly stop at
register/scheduling or x87-choreography walls, and several need operand rows
that do not exist yet (`.scratch/wave2/DATA-GAPS.md`).

A reviewed extent-repair batch then ran: 36 game rows passed the byte-level
spec verifier and were applied with `rebrew binary repair-extents` under its
input digest, then re-measured with the corrected stored SIZE. That converted
`0x0042f4d0` (356/356) and `0x004e8c00` (173/173) to RELOC and five more rows
to NEAR_MATCHING. Three further rows now measure exactly against the repaired
size but remain STUB-classified because their bytes still differ. The separate
merge case `0x45a3a0`+`0x45a7f9`, two code+table rows, and two missing-entry
additions are still open. Do not use `rebrew coverage catalog --fix-sizes`; it
grew 22 already-verified rows from the stale inventory and had to be undone
(details in `.scratch/wave2/DECISIONS.md`).

Wave 5 ran on 100 remaining validated extents (354-889 bytes) plus a second
repair batch of three verified rows (`0x4aa240`->748, `0x524fc0`->498,
`0x5252d0`->735). Five promoted rows were lead-verified as RELOC (425, 480,
489, 478, 559 bytes) and three more as NEAR_MATCHING; `0x524fc0` became
NEAR_MATCHING 454/498 after its repair. Six wave-5 agents did not deliver a
report; the written sources remain, all their promoted rows are verified, and
the rest are recorded partial SIZE_MISMATCH bodies. Larger bodies are now the
pool, so most new output is faithful partial C rather than RELOC.

Wave 6 ran on 43 shared-TU STUB rows (each in a distinct file) plus the 57
smallest remaining validated extents. Shared-row agents edit only their own
function and measure with `--va` so resident EXACT/RELOC rows are not
re-promoted. The lead reproduced its promoted verdicts
(`.scratch/wave6/verify-changed.json`): **3 RELOC** (`0x4d1ad0` 539/539,
`0x512b40` 478/478 after extent repair, `0x546720` 181/181) and **2
NEAR_MATCHING**. The rest are faithful partial bodies (28 forced
SIZE_MISMATCH) or untouched large rows. The wave also found a third invalid
metadata row (`0x5294c4`, a switch-case arm inside the enclosing function) and
confirmed the `rebrew_globals.h` gap: it is server-only, so GOLDTL bodies keep
local externs and operand validation stays blocked on missing data rows.

A systematic trailing-pad audit then ran: 514 game extents have padding after
their last real terminator; 73 single-function SIZE_MISMATCH/NEAR bodies were
repaired in the inventory with one digest-guarded batch. Feeding the corrected
SIZE back through `rebrew test --va --size --force-status` is converting some
of them to RELOC (first batch: `0x445760` 309/309; a mid-wave scan error left
six rows to retry). The remaining repair classes (code+table, merges, invalid
rows) are queued in `.scratch/wave2/EXTENT-QUEUE.md`.

Wave 7 currently runs on the next 100 validated game extents (637-1817 bytes),
with wave-8 groups precomputed for replacement agents so ten subagents stay
running. A closure pipeline is prepared at
`.scratch/closure/run_closure.py`: resume the paused client build, then data,
whole-image, lint and server-gate checks; it must not run while wave agents are
compiling.

Classification of the remaining TL STUB rows (`.scratch/wave2/classify.py`):
204 declared library band, 14 CRT/runtime tail, 604 game rows whose extent the
fresh discovery pass validates (296 left after waves 3-5), 409 game rows with
merged or padded extents, 43 rows in shared TUs. The reviewed extent-repair
queue (splits, merges, padding) is `.scratch/wave2/EXTENT-QUEUE.md`. Findings,
classify output and next-wave plan are in `.scratch/wave2/FINDINGS.md` and
`.scratch/wave2/PLAN-next.md`.

## Paused checkpoint, 2026-10-19

This checkpoint records the pause that preceded the resumed waves above. At that
pause all delegated tasks had finished and no
owned compiler or emulation process remained. The current creator source,
inventory and metadata changes are **uncommitted and unpushed**.

Scoped verification finished: **98 of 102 contexts pass**, with four existing
size mismatches and no compile failures. The subsequent full client rebuild
stopped at **59%**, exit **143** after the requested SIGTERM; its log contains
zero compiler-error lines through that point. Neither client was relinked.
The existing PEs/maps, server gate, data results and README graphics describe
earlier checkpoints, not validation of the current working tree. Final raw-link
checks, fresh lint and the server gate remain pending.

See [handoff](HANDOFF.md) for prepared work and resume steps. Stop evidence is
`.scratch/gui-text-creator-integration/STOPPED.json`; detailed receipts are in
that directory. No further build or reconstruction starts without a resume request.

## Current integration

- The inferred `d2_ShowTxt` now shares Gold `0x473640` and TL `0x46fac0`
  in `Develop/Units/d2.v1/`. Gold uses signed word coordinates; TL uses
  dwords. The canonical header preserves that difference. Gold's complete
  525-byte C body passes all 31 applied operands and 65 rejecting controls;
  TL retains its 518-byte object. The three NOPs following Gold's return are
  a separately reviewed inventory-boundary correction, not C padding.
  All 28 caller TUs use the shared contract. Gold's eleven misrouted creator
  calls and four misrouted receiver calls select their evidenced providers;
  the unrelated Gold `0x46fac0` stays separate. Creator results and receiver
  IDs are integers. Twenty-seven caller objects preserve nondebug sections
  and reviewed operands. TL `0x4d6170` changes four register-color bytes in
  an existing nonmatching body; its size and relocations stay unchanged.
  Fresh verification passes 98 of 102 selected contexts, with four existing
  size mismatches and no compile failures. Gold `0x5bcb10` now earns RELOC
  after the provider repair. Two private TL views pass their sizeof and all
  24 offsetof assertions; neither view claims storage ownership.
  The source-contract audit still reports conditional-coordinate typedef
  uncertainty; actual target compiles resolve it, but it is not a clean audit.
  The full rebuild stopped at 59%; final raw-link checks remain pending. Receipts:
  `.scratch/gui-text-creator-integration/`.
- The inferred `d2_SetElementValue` now shares the TL `0x472380` and Gold
  `0x475ca0` setters with a variadic contract: widget kind and flags select
  string, integer or unused payloads. All selected callers use the canonical
  header. Three timer conversions and the file selector's pointer payloads
  retain their native calling behavior. Gold now uses the existing shared
  step helper at `0x475be0`, replacing its obsolete zero-return scaffold.
  Both setters officially measure RELOC (389/389 and 390/390); pool and helper
  operands validate, while `_itoa` remains unresolved in catalog evidence.
  All 75 rebuilt object contexts preserve nondebug sections and operands apart
  from the reviewed names. Complete mapped setter/helper bytes agree, with
  18 rejecting controls across the setters. Both placements remain displaced.
  Imports are unchanged, and all 106 changed data-pointer slots per client
  retain their mapped symbol or bounded CRT offset. Gold loses the 16-byte
  helper stub; TL's section sizes stay unchanged. No storage owner or original
  TU boundary was inferred. The external file-selector form is unavailable,
  so its string-widget subtype remains an explicit input precondition.
  That checkpoint exposed two wrong text-creator bindings in Gold `0x5bcb10`
  and demoted it to NEAR_MATCHING. The later creator integration above repairs
  those providers and records the fresh verdict.
  Receipts: `.scratch/gui-setter-integration/` and
  `.scratch/gui-text-creator-provider-review/`.
- Three more client bodies now share C definitions: the six-record GUI cleanup
  (TL `0x4d0ec0`, Gold `0x4cfe70`, 50 bytes), recipe-key lookup
  (TL `0x4ec960`, Gold `0x4eabe0`, 59 bytes), and 14-byte calendar-copy callback
  (TL `0x55a820`, Gold `0x552730`, 60 bytes). All six official object checks
  are RELOC with every operand VALIDATED. The five-byte lookup wrappers and
  77-byte bonus callers remain RELOC; the latter retain three unresolved
  global operands per target. Reviewed Gold inventory splits separate the
  newly bound entries from their preceding functions and alignment bytes.
  Two GUI-table rows identify addresses without claiming an extent or owner;
  the scaffolds' 48-dword buffers are comparison capacity only.
  All eight rebuilt contributions, including the forwarding wrappers, match
  their complete native bodies after applying the reviewed operands and match
  their mapped raw-link bytes. All eight placements are displaced; none earns
  linked EXACT. Eleven saved-object comparisons preserve every other nondebug
  section and operand target, including the GUI initializer. Import identities
  are unchanged across all three images. The initializer remains RELOC 581/581,
  with five unresolved operands. Existing alchemistry nonmatches remain open.
  Receipts: `.scratch/client-small-bodies-integration/`.
- Gold `0x418030` now reuses the existing TL `0x4195f0` C cleanup. Both
  official comparisons are RELOC 76/76 with all 11 operands VALIDATED.
  The duplicate Gold assembly body and its assembly marker are removed.
  Six data identities bind the existing pointer slots without allocating storage
  or claiming their owners. Complete applied-byte proof, rejecting controls
  and 16 null/callee-mutation cases are in `.scratch/gold-cleanup-c/`.
  Both fresh raw links contain the applied compiled body at displaced addresses;
  neither earns linked EXACT. The TL object's non-CodeView sections are unchanged.
- The shared GUI forwarding wrapper now passes its slot argument to the
  correct target provider: Gold `0x46e700`, TL `0x46b2b0`. Both five-byte
  wrappers remeasure RELOC with their callee operands VALIDATED. The Gold
  caller remains RELOC 45/45 with unchanged non-CodeView sections. Both
  destructors remain explicit, unrecovered `void(int)` stubs; observed calls
  discard their result, which does not prove the original return declaration.
  Another 19 Gold calls in four shared TUs now select the same Gold provider;
  all eight official target contexts remain RELOC, with those calls VALIDATED.
  Unrelated global operands remain unresolved.
  All four TL objects and the complete TL image are unchanged by that correction.
  The obsolete Gold scaffold provider is removed. Its 16-byte contribution shifts
  later Gold code; all 106 changed data-pointer slots retain the same mapped
  symbol or bounded CRT function offset. Imports are unchanged.
  Receipts: `.scratch/gui-forwarding-contract/` and `.scratch/gui-provider-audit/`.
- The sound-control declaration repair removes the conflicting zlib declaration
  and uses the existing shared callee's pointer argument. Both official wrappers
  remain RELOC 44/44, and both complete non-CodeView objects are unchanged.
  Receipts: `.scratch/vfs-warning-triage/`.
- Gold `0x423a50` is C: official RELOC 59/59, five validated operands and two
  IAT-policy slots. Independent application validates all seven operands and
  13 rejecting controls. Its rebuilt raw contribution agrees with the compiled
  object at that checkpoint's displaced address `0x424720`; this is not linked EXACT.
  The old assembly marker/blocker are removed. No storage was added.
  Receipts: `.scratch/gold-msx-lock/`.
- Gold `0x4790d0` is C: official object checks are RELOC 53/53, with its two
  callers at 49/49 and 91/91. Current source hashes match those receipts. This
  replaces already-accounted assembly; it adds no accounted text.
- Four TL callbacks (`0x40cfb0`, `0x551010`, `0x55af10`, `0x586bd0`) now have C
  implementations with fresh RELOC verdicts at 51, 61, 38 and 61 bytes.
  All eight operands are VALIDATED. Independent applied-byte comparisons and
  wrong-target/site/window controls pass on the final sources. These are
  object results; client raw-link validation remains due.
- Gold `0x4c6a50` now binds the existing `cm_MarkAndReturn` in `command.c`,
  whose selected Gold object matches all 14 native bytes. Its old 64-byte
  inventory extent was split into the 14-byte function and a separate 37-byte
  entry at `0x4c6a60`. The replacement binding now measures EXACT 14/14;
  the new entry remains unreconstructed.
- TL `g_774a1c` has an identity-only data row. Six native dword references and
  both operands of the cached `0x586bd0` object agree. No extent, storage owner
  or C allocation was inferred.
- The attested `d3_LoadAnimStream` name now covers its shared client definition
  in `Develop/Units/d3`; both targets remeasure RELOC 207/207, with seven
  unresolved operands each. The corrected `cm_TestCommandResult` filename
  remeasures EXACT 23/23. All 28 affected client compile contexts preserve
  non-CodeView sections and operands apart from the animation symbol rename.
  Both animation-options bindings have fresh sizeof/offsetof checks after the
  declaration rename; the 12-byte type and offsets are unchanged.
  Exact original filenames/TU boundaries and raw-link placement remain unproved.

All 20 reconstruction and organization reports are in `.scratch/dsh-wave1/results/`.
Parent review and fresh official comparisons are in `.scratch/dsh-wave1/review/`;
naming/move preservation checks are in `.scratch/dsh-wave1/naming-review/`.
Compilation works through the pinned unshare runner. Both client source lists
were regenerated, and the broad two-job rebuild completed successfully:
`.scratch/dsh-wave1/naming-review/clients-build.log`. Gold then relinked after
the audio-wrapper replacement. Both raw-image comparisons still fail; object
results do not establish native placement.

The updated [community review](community-research.md#exe-branch-follow-up-2026-10-19)
records original-name and algorithm leads. It establishes no new original TU
or local byte verdict. The upstream fixture-isolation fix passed 12,715 tests
(48 skipped) and merged in [Rebrew #35](https://github.com/maci0/rebrew/pull/35).
The last completed lint is `.scratch/gui-setter-integration/lint-final.json`:
36 E023 errors and zero warnings per target. The official blocker backfill
documented 1,848 Gold and 1,284 TL unmatched rows without changing their verdicts;
this clears missing-explanation warnings, not the recovery work. Rebrew 5.2.0
also removes the obsolete-template W033 warning. No type-staleness warning
remains in that receipt. Lint was not rerun after the creator integration.
The temporary layout-probe failure under unshare was reproduced
and repaired in [Rebrew #36](https://github.com/maci0/rebrew/pull/36);
the native replay passes in both clients. Both upstream fixes are on `main`.
The later [Rebrew #37](https://github.com/maci0/rebrew/pull/37) removes size-only
import-thunk claims from blocker backfill; its full suite passed 12,820 tests
(37 skipped). That fix is on upstream `main`, outside the pinned 5.2.0 release.
None of this checkpoint's backfilled rows took the short-body heuristic.
[Rebrew #38](https://github.com/maci0/rebrew/pull/38) also merged: function tests
skip a redundant SIZE transaction while retaining missing/changed size writes.
Its local suite and all six CI jobs passed; it is not yet in the pinned release.
[Rebrew #39](https://github.com/maci0/rebrew/pull/39) merged with all CI checks
passing: indexed table references are explicit candidates rather than inferred
effective addresses, and reference-binding rename previews carry guarded input
digests. Its full suite passed 12,837 tests (48 skipped). These repairs are also
outside the pinned 5.2.0 release.
[Rebrew #40](https://github.com/maci0/rebrew/pull/40) merged with all six CI jobs
passing: conservative unshare CL caching, target-isolated verification results
and comparison baselines (including #41), corrected nested-header lookup, and
the preserved startup optimization. The final full suite passed 13,007 tests
(36 skipped); seven real compiler dispatches preserve complete cold/hot control
objects and diagnostics. Rejected cache candidates are validated privately
before atomic publication. These changes are not in the installed 5.2.0 release.
See [performance limits](verify-performance.md#runner-and-caches).
[Rebrew #42](https://github.com/maci0/rebrew/pull/42) fixes guarded binding of
valid typed `va_arg` expressions without weakening malformed-source rejection.
[Rebrew #43](https://github.com/maci0/rebrew/pull/43) removes discarded row
copies from metadata writer validation. Both fixes passed their full local
suites and all six CI jobs, and are merged outside installed 5.2.0.
Parser and writer receipts are in `.scratch/upstream-va-arg-evidence/` and
`.scratch/upstream-writer-evidence/`; the profile's limits are in
[verification performance](verify-performance.md#causes-and-fixes).
[Rebrew #44](https://github.com/maci0/rebrew/pull/44) also passed its full local
suite and all six CI jobs before merging: read-only developer preflights now
honor `UV_PROJECT_ENVIRONMENT` without creating a local `.venv`. Evidence is in
`.scratch/upstream-preflight-evidence/`; installed 5.2.0 remains unchanged.

## GoldTL data audit, 2026-10-19

At the last completed setter-integration checkpoint, both rebuilt scaffolds
have **0 exact data placements**. Those raw-image checks report:

| Target | Displaced / absent from map | Byte-equal / different / missing | Compared / total |
| --- | --- | --- | --- |
| Gold | 306 / 14 | 83 / 30 / 49 | 162 / 320 |
| GoldTL | 336 / 22 | 93 / 51 / 42 | 186 / 358 |

Gold has 158 non-comparable symbols; TL has 172. These include zero-fill tails
and addresses outside file-backed data. Byte equality at a reference address
does not establish the displaced symbol's identity there. Both whole-file
checks fail as expected for comparison scaffolds. Last completed receipts and hashes:
`.scratch/gui-setter-integration/image-{gold,tl}.json`.
The two unsized GUI-table identities add one non-comparable row per target;
they do not increase compared bytes or establish storage ownership.
The earlier TL snapshot below had 330 displaced symbols and 24 absent.

The logging tables/newline/default name and both Sonnenstrahlen strings have
correct file bytes at their mapped addresses. Before this rebuild, the scaffold's
`ch_MorphFrameValue` and `SonnenstrahlenStartZeit` contain zero where the
reference initializes them to -1; `g_6752a4` also has a zero placeholder for
native value 1. Both clients' stub-generator overrides now preserve those values.
Both regenerated stub objects compile without warnings. Both new raw images
contain the three expected values at their mapped addresses. Original owners
and native placement remain unresolved.
The critical-section slots already have import metadata and KERNEL32 providers;
their placement differs.

Complete COFF/native literal audits identify TL's `dbl_1_0`, Gold's distinct
`dbl_2_0`, and each image's `flt_0_3`. Their metadata now names the emitted
compiler symbols; no new C storage was added. On that checkpoint's TL map this
reduced absent symbols from 24 to 22 (332 displaced). These are content and
symbol-binding checks, not native placement or original TU ownership proof.

Receipts: `.scratch/dsh-wave1/review/data-diagnosis-tl.json` and
`data-linked-location-samples.json`. The original audit changed only 22 GoldTL
comparison records. The four later literal bindings above are separate changes.
Correcting displaced initializers does not fix native placement.
Literal/initializer receipts and that TL comparison are in
`.scratch/data-initializers/`; the earlier Gold comparison is
`.scratch/gold-msx-lock/gold-rebuilt-image.json`. Use the final receipts above
for the last completed images; no creator-integration image check has run.

## Verified checkpoint

These completed checks precede the paused creator integration. The server gate
has not been rerun for the current working tree; the interrupted build is
recorded in the paused checkpoint above.

| Area | Result | Receipt |
| --- | --- | --- |
| Server raw image | All 286,720 bytes equal the untouched reference. Fresh function checks 316/316; data checks 652/652. Whole-image checks, Wine loading and toolchain alignment pass. The gate fails only on the 36 E023 findings. | `.scratch/gui-setter-integration/server-gate.log`, `gate-verify.json` |
| Client builds | The 9,305-entry two-job rebuild exited 0, producing both PEs/maps under `build/`. It emitted 310 compiler-warning lines, with no compiler errors or linker diagnostics. Both images remain scaffolds and differ from their references. | `.scratch/gui-setter-integration/clients-build.log`, `build-diagnostics.json`, `post-build-proof.json` |
| Gold getter | `0x4364f0` is C, RELOC25/25, with its DIR32 validated. Gold subsequently relinked. The new pointer slot is comparison storage, not a recovered owner. | `.scratch/goal110-full-runs/getter-official.json`, `gold-rebuild.log` |
| Experimental runner | Verification and CMake CL/LINK/LIB use configured unshare. Wine-prefix initialization, private font cache and extracted mtimes are repaired upstream. Complete Gold/TL probe objects equal Docker controls. | `.scratch/goal110-full-runs/compile-equivalence.json`, `seed-isolation.json` |
| Upstream tests | 12,586 passed, 36 skipped; mypy checked 392 files. These are the upstream suite, not raw-image or client proof, and not a verdict on later edits. | `.scratch/goal110-full-runs/upstream-suite-final.log`, `upstream-mypy-final.log` |

The first client passes emitted 457 compiler-warning lines across 128 files.
Those logs are not warning-free builds. The first warning batch preserves
complete non-CodeView sections and relocations in 18 contexts. Later edits need
independent review, official comparison and relinking. See
`.scratch/goal110-full-runs/compiler-warnings.json` and `warning-batch/`.

Assembly lint stayed open after that gate.
`.scratch/publication/guild-final51-lint.json` (2026-10-18 16:23) reports 39
E023 errors and 0 warnings in each target summary. The gate's 41 errors are the
earlier log. Run `rebrew lint` again after further edits.

## Next actions

Work resumed on 2026-10-19; the delegated waves above run on the game STUB
queue while closure stays pending. First finish the interrupted build and its
prepared raw-link checks, then obtain fresh lint and server-gate results before
committing the current integration.

1. **Continue the validated-extent game queue.** Wave 3 covers the first 100 of
   the 604 rows whose stored extent the fresh discovery pass validates; keep
   the `external_ranges` band and CRT/runtime tail out of reconstruction.
   Review each wave's extent-defect and ABI reports.
2. **Repair reviewed inventory extents.** Apply a reviewed
   `rebrew binary repair-extents` batch for the 409 merged/padded game rows
   plus the sibling entries fresh discovery found, then reconstruct them.
3. **Finish warning repairs and rerun both clients.** Review numeric conversions,
   pointer/callee contracts, packing and return paths against native evidence.
   Preserve every selected target context. Do not suppress diagnostics, add
   arbitrary initializers or replace recovered behavior with stubs.
4. **Recover unsupported assembly as C.** The Goal110 getter left 40 outstanding
   Gold-audit entries at that checkpoint. That denominator is the audit list,
   not the later 39 E023 lint receipt. Query the live list. Old EXACT/RELOC
   assembly verdicts are not C-recovery credit. Fourteen TL comparison stubs
   also need native ABI/provider recovery.
   [Assembly policy and receipts](assembly-audit.md) define the allowed exceptions.
5. **Close client providers and storage.** Resolve duplicate native identities,
   comparison placeholders, omitted TUs and unproven global owners. Keep stock
   libraries linked and distinguish import slots from game storage. Do not add
   the server BSS owners to a client to satisfy names. The shared GUI text
   creator still depends on scaffolded index allocation and text measurement,
   plus Gold's scaffolded list insertion. Recover those providers and their
   caller contracts; TL's recovered insertion body can guide a shared version.
   A complete creator body does not establish the helper implementations.
6. **Continue scene, terrain and savegame contracts.** Prioritize the building/
   placement family, opaque stream callers, resource constructors and renderer
   dependencies. Native counterpart mappings and bounded behavior checks do not
   establish compiled bodies or original source ownership.
7. **Verify final inputs and raw images.** Rebuild after the last source/header
   edit, compare placement/imports/data/whole files, and rerun the server gate.
   Preserve server raw identity while closing lint and source-fidelity debt.

## Commands

```sh
uv run rebrew todo --json
uv run rebrew status --all-targets --json
uv run rebrew lint --all-targets --json
uv run rebrew verify --data --target Europa1400Gold.exe --json
uv run rebrew verify --data --target Europa1400Gold_TL.exe --json
uv run scripts/gate.sh
```

`todo --json` uses the default target, GoldTL. `verify --data` can record data
verdicts for the configured raw link, and compiles functions only when asked.
Bare `verify` checks functions. `--no-cache` skips saved verification results;
a matching compiler-object cache entry can still supply the object. Under
unshare, Rebrew 5.2 directs RELOC `todo` rows to raw-image verification
([runner limits](verify-performance.md#runner-and-caches)). Check current CLI
help before reusing an old command. Client build recipes and scaffold limits
are in [stubs/README.md](../stubs/README.md).

## CURRENT STATE

Historical server-only table from the last completed gate, before the current
creator integration. The gate no longer rewrites this checkpoint from terminal
output; use its structured reports and `rebrew status` for current results.
A zero raw-image gap does
not imply a passing gate, recovered client code or verified source ownership.

<!-- CURRENT-STATE:BEGIN -->
<!-- Historical gate checkpoint; update only from a reviewed verification report. -->

| Quantity | Value | Source |
|---|---|---|
| verify `passed` | **316/316** | gate's `BASELINE` |
| `.text` residue | **0** | raw-link file identity |
| raw-link `.data` divergence | **0** | raw-link file identity |
| relocation records missing / extra | **0 / 0** | `rebrew verify --whole-binary` |
| raw-link import table | **matches** | gate, round 210 |
| OBJECTIVE GAP (raw link vs reference) | **0** | raw-link file identity |
| ...of which | **0 differing bytes in the common prefix, 0 bytes of size shortfall** | gate's decomposition |
| annotations shorter than the binary | **?** | `rebrew verify --json` |
| `cmake --build` exit | **0** | gate's build step |

<!-- CURRENT-STATE:END -->

## Evidence and handoff

- Paused creator integration and stop record: `.scratch/gui-text-creator-integration/`.
- Prepared helper candidates and native-only checks: [handoff](HANDOFF.md#prepared-helper-work).
- Goal110 build, runner and warning receipts: `.scratch/goal110-full-runs/`.
- Earlier client source/provider cutover: `.scratch/goal106-client-cutover/`.
- Text-placement repair: `.scratch/goal107-text-placement/`.
- Scoped assembly review: `.scratch/goal108-assembly-provenance/`.
- Full pre-cleanup queue: [2026-10-18 archive](goal-history.md#full-notebooks).

Replace this checkpoint when evidence changes. Keep experiment details in their
technical reference or scratch receipt; query metadata for live counts.

## Pending metadata write: retire split-artifact row 0x0041ebca

The row is not a function (two cold blocks of the unrowed `0x41e680`; evidence
in `.scratch/gold-d/task130`). Retirement needs one locked write, but the
retirement script keeps losing the metadata digest race while many agents
write test/blocker results concurrently. `.scratch/lead/retire_41ebca.py`
already retries 40 times at 15 s; it succeeds only in a quiet window. Until
then the row stays in the store with its stub skeleton and blocker, which is
honest but counts as one STUB. Admitting the enclosing `0x41e680` row is
blocked by the overlap guard, filed in upstream `docs/IDEAS-GUILD.md`.

## Whole-binary checkpoint (round 8)

`rebrew status --json` with `build/Europa1400Gold_TL.exe` present: functions
covered 96.0%, matched 74.7% (RELOC 3533, EXACT 293, NEAR 91, SIZE_MISMATCH 934,
STUB 64), `matched_bytes` 1,175,400 of 2,491,370 (byte coverage 48.7%),
padding 38,715, unattributed 49,399. Data rows: 0 exact, 348 drift, 12
unchecked, 339 displaced, `byte_pct` 0.0.

`cmp -l` finds 2,173,451 differing byte positions against
`original/Europa1400Gold_TL.exe`, and the built image is 2,232,320 bytes versus
2,850,888, so a whole-binary match is nowhere near. Function reconstruction
remains the primary lever; data placement and whole-image size reconciliation
are separate follow-ups. Objective stays active.

## Matching lever: /G5 and /G6 for MSVC scheduler tie-breaks

`/G5` (Pentium) and `/G6` (Pentium Pro) change MSVC 6 code generation for
instruction order and zeroness idioms without changing semantics. Two NEAR rows
converted to EXACT by storing the flag alone, body unchanged: `0x615e12`
(`/O2 /Gd /G6`, 104/104) and `0x62ade8` (`/O2 /Gd /G6`, 48/48). The flag is
wrong for other rows (`0x490c10` regressed to SIZE_MISMATCH 117/118), so sweep
per row and store only strict wins. `.scratch/lead/near-group-*` holds the
NEAR row groups used for the round-8 sweep.

Separately, `build driver cl` and the generated CMake toolchain file ignored a
target's compiler-profile override and used the project-level profile. Fixed
upstream in `rebrew.cmake_tc._load_profile` (default target's `compiler.profile`
wins, with a regression test in `tests/test_cmake_tc.py`); manual probe objects
built before the fix used the wrong code generator.

## Do not run `test --all` while teammates are editing

A full `test --all --jobs 6` started at 13:37 produced 60 compile errors from
transient states of files other agents were editing. Earned EXACT/RELOC rows
were protected (the writer refuses a tooling-failure demotion) and no
COMPILE_ERROR rows were stored, but the run is not an authoritative settlement
of verdicts. Rerun it in a quiet window, with no agent editing, and compare the
status histogram before and after.

## Per-row cflags: clearing needs remove_field, and a CLI gap

`metadata.functions.clear_identity_fields` accepts only FUNCTION_IDENTITY_FIELDS
(file, symbol, name, kind); passing "cflags" raises ValueError. The locked
deleter for a cflags override is
`metadata.functions.remove_field(cfg.metadata_dir, va, "cflags", module="GOLDTL")`.
There is no CLI to clear a per-row cflags override, so it was filed upstream.
Persist rule for /G6 sweeps: only when match_count strictly increases (a smaller
size error with a lower match is alignment noise at these counts).

## Per-row CFLAGS and multi-function translation units

The client build compiles one TU per source file with one flag set:
`rebrew build cmake-flags` refuses a file whose rows resolve to different
CFLAGS. Round-8 `/G6` sweeps persisted per-row overrides without checking file
shape, so `src/GOLDTL.fcn_004055a0.c` (rows `_fcn_00405540` on `/O2 /Gd /G6`,
`_fcn_004055a0` on `/O2 /Gd`) broke the TL configure step. Rule for later
sweeps: check how many FUNCTION/STUB rows share the file first; persist a
per-row flag only when every row in the file gets the same effective flags,
otherwise skip the row or split the file deliberately.

## TL link blocker: `d3d8.lib` (Direct3DCreate8 import)

The reference image imports `d3d8.dll!Direct3DCreate8`, but no `d3d8.lib`
exists in the MSVC SP5-PP toolchain image (`/opt/msvc6.0-sp5-pp/VC98/Lib`, checked
by the resolver) and the project has no vendored copy, so the TL link cannot
resolve `_Direct3DCreate8@4`. Adding `D3D8 = "d3d8.lib"` to the target's
external_libs fails archive resolution and would break the link. Resolution
needs an MSVC6-compatible i386 d3d8 import library with recorded provenance and
license (the DirectX 8 SDK import lib, or a documented substitute); that is a
project asset decision, not a rebrew capability. Until then this one import is
the only import-table mismatch the link repair cannot close.

## TL link scaffolds (comparison build only)

`stubs/goldtl/data_scaffold.c` holds zero-valued definitions for data symbols
that have a row or an extern declaration but no owning game TU yet.
`stubs/goldtl/band_scaffold.c` holds placeholder definitions for the
0x5e0000-0x64ffff library band (needs the native-bytes-only archive match filed
upstream), for two game functions whose bodies live in GOLD-only TUs, and for
`Direct3DCreate8` (needs a vendored d3d8.lib). Neither file claims recovered
code or bytes; they exist so the comparison link completes and the image can be
measured with `rebrew verify --whole-binary`, where the missing d3d8.dll import
still shows. Regenerate with `.scratch/lead/make_data_scaffold.py` and
`.scratch/lead/make_band_scaffold.py`; wiring lives in `CMakeLists.txt` under the
GoldTL target.

## TL STUB floor: five size-exact codegen walls

The TL target is at 5 STUB rows, all five with an object size equal to the
reference and a match below the 60 percent NEAR classifier threshold:
`0x4c9e20` 109/190 (block order: reference keeps the `ret=1` cold block after
the shared epilogue with a back-jump, MSVC6 emits it inline or first),
`0x5a0ad0` 101/271 (reference delays the `p` load past both setup calls so it
takes edi; the build hoists it into ebx), `0x558220` 169/332 (MSVC6 PP
induction-variable selection re-bases the walk pointer from 0x7f4ca4 to
0x7f4e24 and flips every displacement), `0x404dc0` 177/404 under `/G5`
(one `lea ecx` vs `lea edx` choice at offset 0x6f seeds a whole-register
permutation), `0x57d0d0` 341/1802 (reference zeroes five slots through separate
`xor eax,eax` stores while the compiler consolidates them through ebp).
All five bodies are real reconstructions kept at their best measured state.
`rebrew test --va <VA> --force-status` cannot promote them: the comparator
classifies an exact-size low-match compare as STUB, so the write is refused
before the force path matters. Clearing them needs a NEAR-level match, which for
these five means breaking a compiler codegen wall, not a body-shape edit; the
failed shape and flag lists are in each row's blocker. Two assembly routes do
not apply: there is no evidence the original source used assembly at these
sites.

### Round 18: block-layout wall probed further

`0x4c9e20` reference disassembly confirms the exact layout: `je 0x4c9ed7` at
+0x45, hot block falls through at +0x6e into the join, shared epilogue and `ret`
at +0xa0..+0xb6, cold block `mov ebx,1; jmp 0x4c9e8e` at +0xb7. Two more source
shapes were tried in round 18, both 71/190: a `goto cold` whose label sits after
the `return` with a backward `goto join`, and a `do { ... continue; } while (0)`
around the hot block. The best body (109/190) was restored byte-identically.
A scan of all reconstructed EXACT rows found no function with this
backward-jump-after-ret idiom, so there is no already-matched source shape in
the tree to copy. The wall is c2 block placement, not C statement shape.

## TL stub bodies: zero

Every GOLDTL-bound row now has a real reconstructed body: the two remaining
skeleton claims inside the library band (`0x5eb108`, `0x62ce8f`) were retired
with band evidence and their generated files removed, so a marker scan over all
4907 bound rows finds no `TODO: Implement` placeholder. The 5 rows whose stored
STATUS is still STUB are the size-exact codegen walls documented above; their
bodies are real and measured.

## TL link convergence

The link now fails only on 18 statically linked band symbols whose decoration is
`@name@N` (fastcall). Some callers declare them `__cdecl`, so two different
symbols are referenced and the stub TU cannot satisfy both. Next step is to
reconcile those declarations to the native fastcall convention, regenerate
`stubs/goldtl/symbol_stubs.c` from the resulting link log, and relink; the
comparison image then allows `rebrew verify --whole-binary` for the TL target.

## TL comparison image links (round 20)

`build-goldtl-audit/Europa1400Gold_TL.exe` now links, 2,347,008 bytes against the
reference 2,850,888. Whole-binary compare (`rebrew verify --whole-binary`):
exports match exactly (0 missing, 0 added); `.text` 2,203,914 vs 2,491,370,
`.rdata` 32,688 vs 76,722, `.data` 4,546,196 vs 15,766,564, `.rsrc` absent vs
1,288; imports 76 missing and 2 added.

The link completes because three scaffold TUs cover the remaining symbols:
`data_scaffold.c` (zero-valued data objects plus two cdecl band aliases),
`symbol_stubs.c` (generated placeholder functions and data for the bootstrap
set), and `link_scaffold.c` (exact-decoration placeholders for band symbols,
fastcall `@name@N` and stdcall `_name@N`). None are recovered code; the scaffold
is what lets the image be measured.

Next whole-image work: import-table parity (76 missing, 2 added), the `.data`
virtual tail (~11.2 MB of reference uninitialized storage), `.rsrc` embedding,
and `.text` codegen/library pull-in (~287 KB). The layout package exists
(`layout/Europa1400Gold_TL.exe/`) but the link line does not yet consume its
ORDER/INCLUDE inputs that server.dll uses.

### Round 21: import-table parity

The TL comparison link now forces the reference's imports through
`layout/Europa1400Gold_TL.exe/import-includes.rsp` (71 `/INCLUDE:__imp__Name@N`
directives; the PE import name is undecorated while the archive symbol carries
the stdcall byte count, so the mapping came from probing each configured
archive). Import diff: 76 missing/2 added before, **5 missing/2 added** after.
Still missing: `ws2_32.dll!ordinal_20`, `ws2_32.dll!ordinal_57` (ordinal imports,
no library symbol found), `d3d8.dll!Direct3DCreate8`, `dinput8.dll!DirectInput8Create`
(no import library in the toolchain image; asset gap, recorded), and
`ddraw.dll!DirectDrawCreateEx` (the stock VC98 DDRAW.LIB has no `Ex` entry).
Still added: `kernel32.dll!GetSystemInfo` and `kernel32.dll!TerminateThread`,
both pulled in by link inputs the reference did not use; next step is to find
the referencing member and displace it.

Section sizes after the change: `.text` 2,204,330 vs 2,491,370, `.rdata`
34,882 vs 76,722, `.data` 4,546,196 vs 15,766,564, `.rsrc` absent vs 1,288.

### Round 22: the two added imports are a library-version mismatch

`kernel32.dll!GetSystemInfo` is imported by the vendored
`references/dxsdk8/lib/d3dx8.lib` member `obj\i386\cpudetect.obj`, which the link
pulls for `_D3DXCpuOptimizations@4`; that member also references
`RegOpenKeyA/RegQueryValueExA/RegCloseKey` and `IsProcessorFeaturePresent`.
The reference image does contain CPU-detect code (strings `DisableMMX` and
`GenuineIntel` each appear once) but it does not import `GetSystemInfo`, and it
does not contain the vendored member's other strings (`DisablePSGP`,
`Software\Microsoft\Direct3D`). So the reference was linked from a different
D3DX8 static build than the vendored archive: this is a library-provider
mismatch, not a source bug, and it is why the added-import pair cannot simply be
displaced. Identifying the reference's D3DX code in the 0x5e0000-0x64ffff band
needs an archive that matches that build; the vendored one disagrees on strings
and imports. Recorded as an unresolved library-provider gap.

### Round 24: scan-integrity cleanup for retired and library-converted rows

The tree scan treats an `ADDRESS` anchor as a live claim, so a generated skeleton
left on disk after its row was retired or converted to a library identity breaks
every `rebrew test` with "native source binding is retired" or "address anchor
conflicts with the stored source binding". Three cleanup passes moved such files
out of `src/` into `.scratch/lead/retired-files/`, with move lists beside them:
92 retired-claim files (`retired-files-moved.json`), 12 skeleton files whose VA
now carries a `src/library_*.h` identity (`library-anchor-files-moved.json`), and
22 anchored files whose metadata row has no live source file, mostly GOLD-module
files with empty file fields (`orphan-anchor-files-moved.json`). The GOLD files
are archived, not deleted, and the GOLD target's state is unchanged; restoring a
file without repairing its row would re-break the scan. Afterwards `rebrew test`
works and lint reports 0 errors.

### Round 24: NO_SOURCE decomposed from the status code path

The status count is not "rows with no source file"; it is inventory VAs missing
from the metadata scope, the external-library set, and the inside-annotated
pseudo set. Replicating that logic (`.scratch/lead/list_no_source.py`) gives the
exact 258 rows: 154 inside the declared library band (116,377 B of statically
linked D3DX8/zlib/CRT code), 101 import-thunk rows above 0x650000 (1,510 B), and
3 real game rows (1,365 B). The earlier 185/102 lists were polluted by rows that
already held D3DX8-module identities. `targets.Europa1400Gold_TL.exe.raw_link`
was also repointed from the stale `build/Europa1400Gold_TL.exe` to
`build-goldtl-audit/Europa1400Gold_TL.exe`, the link this session actually
produces. No-source classification is dispatched: 101 thunk rows, 154 band rows
(library binding or merge), 3 game bodies.

### Round 24: band range is an approximation, per-row library identity is the truth

`external_ranges = ["0x5e0000-0x64ffff"]` is too wide: game rows live inside it
(`0x5e5a50`, `0x5e5ea0`, `0x5e9da0`, `0x5eaad0` were each retired by the band sweep
and had to be reinstated with caller evidence, and a rehome pass can retire them
again). The durable classification is the per-row LIBRARY identity from
`rebrew library match` (D3DX8 module rows for the statically linked D3DX8/zlib
code, `src/library_d3dx8.h`/`src/library_zlib.h` headers), not the address range.
Narrowing the range needs the actual archive-member extents from the link map,
which is a separate review; do not narrow it by eye.
Two operational hazards found this round: a tracked generated header
(`src/library_imports.h`) was deleted from the worktree, silently turning 87
LIBRARY rows into NO_SOURCE until restored from HEAD, and a retired claim whose
generated `.c` stays on disk breaks every scan with "native source binding is
retired". Archive such files under `.scratch/lead/retired-files/` instead of
leaving them in `src/`.

### Round 24: two data losses repaired, one still open

Tracked sources had been deleted from the worktree by cleanup passes:
`src/Develop/DieGildeAddOn/game/friedhof_logic.c`, `src/Develop/Units/Error/GOLDTL.Error.c`,
`src/Develop/Units/d3/d3_d3d.c`, `src/Develop/Units/vfs/GOLDTL.vfs4.c` were restored from
HEAD, and archived row files were restored by anchor match. A full `rebrew verify`
afterwards refused to overwrite earned EXACT/RELOC statuses with tooling
COMPILE_ERROR, which is the intended guard. The status summary still reports
COMPILE_ERROR/EXTRACT_ERROR verdicts recorded before those files existed; they
are tooling-failure verdicts, not byte comparisons, and are being re-measured as
their inputs return.
Zlib rows are library code: their correct representation is a LIBRARY binding to
the pinned vendored source (`references/zlib-1.1.3/*.c`), not reconstructed C
bodies; the GOLD target already does that. gold-o is binding the six remaining
rows that way.

### Round 25: NO_SOURCE 258 -> 50, STUB 2 justified

The no-source queue is 50 rows / 32,016 B, down from 258, after the band
inventory work (extent admissions, trims, merges, LIBRARY identities from the
audit link map) and the import-thunk classification. What remains is documented
rather than guessed: 36 band rows that are map-less interior/gap code (gold-j
proved the earlier "KERNEL32 thunk" label wrong; only three real thunks existed
and are now LIBRARY), 14 outside-band CRT funclet rows, `0x5e7e30`
(library-unidentified, past its owner's terminal ret), `0x5e0090` (game body
task) and `0x5e0140` (interior findfirst view). Two rows carry STUB by design
with evidence blockers: `0x5e0140` and `0x654e25`.

Compiler backend switched to docker: the unshare backend fails under this
sandbox with "rebrew-unshare: mount target mkdir: Read-only file system", which
had cached 60 COMPILE_ERROR verdicts; a full re-verify cleared them and raised
EXACT to 299.

Two upstream fixes landed in the checkout (`/home/maci/Desktop/Projects/relumea/repos/rebrew`):
`library adopt` accepts C++/static-data symbols with no C identifier by keeping
the native symbol and deriving a display name (gold-j, with tests), and a stale
anchor for a retired binding is skipped with a logged warning instead of
aborting the global source scan (Lead, regression test
`test_orphan_anchor_of_a_retired_row_is_skipped_not_fatal`). Zlib rows are bound
as LIBRARY to the pinned vendored source; six of them verify EXACT/RELOC from
source, two differ by 11 B and 7 B in the original d3dx8.lib build, recorded.

### Round 25: 0x5e0090 is game code, not band library

`0x5e0090` (161 reference bytes, 176 inventory with padding) recovers as a
save-slot writer: `name = data + 9`, `strcmpi` against `QUICKSAVE`/`AUTOSAVE`
through the import thunk at 0x65f220, merged re-check, reject when the slot
record's +8 is set, kind byte store, 0x210-byte copy at +0x10. Measured
SIZE_MISMATCH 67/161, blocker delta 4 (merged strcmpi call site, `-1` register,
arg register, return placement after the copy tail). It sits at the very start of
the declared `0x5e0000-0x64ffff` band, so cleanup passes keep deleting its file
as band residue. Moving the band start to the first real library symbol would keep
this row outside, but the game row's extent overlaps that boundary, so the range
change needs its own evidence review; until then the claim and blocker are the
protection. Decision: Lead; evidence `src/fcn_005e0090.c`, blocker on
GOLDTL.0x5e0090.

### Round 26: full D3DX8 member inclusion is not viable with this archive

Tried forcing every member of `references/dxsdk8/lib/d3dx8.lib` into the link with
per-member `/INCLUDE` directives to close the `.text` gap (reference 2,491,370 vs
built 2,222,922). The link then failed two ways: project-compiled vendored zlib
objects collided with the archive's zlib members (`LNK2005` in `zutil.obj`), and
a pulled member records `/DEFAULTLIB amdmath.lib`, which the image does not
provide (`LNK1104: cannot open file "amdmath.lib"`). The reference evidently
linked a different D3DX8 build, consistent with the earlier library-provider
mismatch (its CPU-detect code lacks the vendored member's strings and imports).
The experiment is reverted; the link is healthy again at 2,371,584 bytes with
`.text` 2,222,922, `.rdata` 34,996, `.data` 15,766,932, imports 5 missing/3 added.
Closing the remaining code gap needs the game bodies that are still partial, not
more library members.

### Round 26: backend split for this sandbox

Two facts conflict here. The unshare backend cannot compile the cross-target
GOLD-module rows in this sandbox ("mount target mkdir: Read-only file system",
60 rows), while the docker backend compiles everything but fails the TL link with
`LNK1104: cannot open file "TEMPFILE"`. Workable split: keep
`compiler.execution_backend = "docker"` for test/verify/status (clean 0
COMPILE_ERROR), and switch to `unshare` only when a link must be produced, then
switch back. The rebuilt image (2,371,584 B) was linked under unshare; its
whole-binary deltas are `.text` 2,222,922 vs 2,491,370, `.rdata` 34,996 vs 76,722,
`.data` 15,766,932 vs 15,766,564, imports 5 missing/3 added. Also note the five
PROVEN rows are re-proved after every `verify`, because PROVEN is not sticky by
design and a verify pass records the byte verdict over it.

### Round 27: quick-win wave started

Closed: `0x0051e070` EXACT 6/6 (a data read behind a placeholder returning 0) and
`0x00418b40` RELOC 108/108 (third parameter is the full dword, not a char). Fixed
two real problems found by the wave: `0x004cffe0` was bound to a `.scratch` draft
and its src clone broke the scan; the row is now bound to
`src/GOLDTL.fcn_004cffe0.c` and measures SIZE_MISMATCH 71/103, and no row remains
bound under `.scratch`. The wave also corrected a wrong call target in
`0x0047d240` (native calls `fcn_0047d220`, not `fcn_0047dd60`).
Documented walls this wave: `0x0047d240` assumes ECX survives a call; `0x0050be50`
swaps ESI/EDI and folds one LEA; `0x00473610` needs EDX plus load-before-store;
`0x004042b0` and `0x00469890` are register-home/block-layout walls. The quick-win
lists were re-cut to exclude the declared library band after the first slices
turned out half library rows. Data verification started in parallel (261 stored
data verdicts are drift; 347 rows to verify).

### Round 27: wave composition and the postlink question

Seventeen agents now work the byte-match backlog in slices: eight quick-win
slices (rows <=120 bytes, 31 game rows after the re-cut), four tier-2 slices
(121-260 bytes, 96 rows), three tier-3 slices (261-600 bytes, 322 rows), two data
slices (rdata first, then .data drift), and one diagnostic on the
`postlink-mangled` todo category. That category's note says the raw link does not
produce the stored bytes, which would mean an earlier session's image was patched
after linking; the diagnostic must name the image, the patched region and whether
today's link (`build-goldtl-audit/Europa1400Gold_TL.exe`) is pristine, because
raw-link identity is the only acceptable final state. Do not patch images to make
a comparison pass.

### Round 28: library pull-in experiment reverted, deliverable restored

The full D3DX8 member pull-in is not viable with this archive. Forcing every
member reproduced three walls in sequence: `math_lib.obj` carries
`/DEFAULTLIB amdmath.lib` (the image ships no such library), `errorstr.obj`
needs `D3DX::pwszGetResourceStringW` which no shipped archive defines, and the
archive's zlib members duplicate the vendored zlib TUs the target compiles
(`_zlibVersion`/`_zError` in zutil). Removing the vendored zlib instead left
`_z_errmsg`/`_zcalloc`/`_zcfree` unresolved even with explicit `/INCLUDE`
directives, so the archive's zcopy of zutil is not a drop-in replacement for the
vendored build. Everything is reverted: no d3dx8 response file, client zlib
helper restored, `build-goldtl-audit/Europa1400Gold_TL.exe` rebuilt clean at
2,371,584 B. Whole-binary deltas remain `.text` 2,222,922/2,491,370,
`.rdata` 34,996/76,722, `.data` 15,766,932/15,766,564, imports 5 missing/3 added.

Two side fixes from the same work: the stale CMake cache pinned the upstream
checkout's `rebrew` (a missing venv path) and broke every compile rule; clearing
`CMakeCache.txt` and reconfiguring restored the project venv pins. The
`postlink-mangled` lane was a false positive: it compared absolute VAs across two
links with different `.text` spans; upstream now requires matching `.text`
VA/virtual size and has a regression test
(`test_postlink_lane_silent_when_text_layouts_differ`).

Next per the user: drive NO_FUNCTION (97,520 B) to zero; gold-o has the
investigation task. The 20 measured data values in `stubs/goldtl/specials.toml`
still need a `rebrew build symbol-stubs` regeneration before they can affect the
linked image.

### Round 29: derived spans for zero-SIZE library rows

Implemented upstream (checkout, uncommitted): an identified LIBRARY row with no
recorded SIZE owns the unclaimed `.text` bytes up to the next known start (row
start or inventory start, clipped to `.text`); a coarse inventory row or a
started row always wins, so no byte is attributed twice. `status --json` reports
the total as `library_derived_bytes`. Measured on this project through the
upstream CLI: unattributed 96,985 -> 52,660 bytes, 44,371 attributed, padding
38,185 (accounting re-derives the padding split). Regression test
`tests/test_status.py::test_zero_extent_library_row_owns_unclaimed_bytes`; the
upstream status suite passes 140 tests. The pinned project Rebrew is 5.4.0, so
this figure needs the upstream CLI (`.scratch/lead/run_upstream_rebrew.py`) until
a release carries the change.

Remaining 52,660 unattributed bytes are the class-B shortfall (row extent shorter
than the containing inventory extent, 48,701 bytes before this change): those are
body/inventory rescoping work, not span attribution. The project venv pin stays
until the release; the upstream fix must be published before the pinned figure
matches.

### Round 30: D3DX8 member inclusion solved, .text gap 268 KB -> 32 KB

The earlier "pull-in is not viable" conclusion is reversed. The failure was three
specific archive facts, not the approach: `math_lib.obj` asks for
`amdmath.lib`, `errorstr.obj` needs `D3DX::pwszGetResourceStringW` from no shipped
archive, and one member (`?maketree@D3DX...`) pulls the archive's `zutil.obj`,
whose `_zlibVersion`/`_zError` collide with the project-compiled zlib (the archive
copy does not define `_z_errmsg`/`_zcalloc`/`_zcfree`, so it cannot replace it).
Exclude those members from the include list and the rest link cleanly.

The list is also filtered against the reference's import table: 15 members are
excluded because they reference APIs the reference does not import
(`d3dx8core`, `d3dx8dbg`, `cd3dxfont`, `cd3dxtext`, `cd3dxfile`,
`cd3dxresource`, `cd3dxassembler`, `d3dx8effect`, `cpudetect`, `createmesh`, ...).
Result: 107 members included through
`layout/Europa1400Gold_TL.exe/d3dx8-includes.rsp` wired in `CMakeLists.txt`.

Measured whole-binary: `.text` 2,458,896 vs 2,491,370 (gap 32,474, was 268,448),
`.rdata` 50,016 vs 76,722, `.data` 15,826,196 vs 15,766,564 (overshoot 59,632,
was +368), imports 5 missing/3 added (unchanged from the baseline link), file
2,678,784. Next: the `.data` overshoot (members adding data the reference does
not carry) and the remaining `.rdata` gap; then the `.text` residual.

### Round 31: .data virtual size back to reference, member list persisted

The 107-member include list is now actually wired in `CMakeLists.txt` (the first
attempt printed "already wired" because a comment mentioned the response file,
so the option never landed; the tell was `link.txt` containing zero
`d3dx8-includes` references). With the members linked, the data scaffold tail was
retuned from 11,220,365 to 11,160,737 bytes: `.data` VirtualSize is 15,766,548
against the reference 15,766,564, a 16-byte shortfall instead of the 59,632-byte
overshoot. The last 16 bytes cannot be reached by changing the tail: the section
end is owned by CRT COMMON symbols after it and moves in 32-byte steps, so an
alignment-level fix is needed (or a different end-setter).

Also learned: `data_scaffold.c` edits can look ineffective because the object file
is not recompiled unless the source timestamp advances; `touch` the file before
relinking when probing scaffold sizes.

Current whole-binary: `.text` 2,458,896/2,491,370, `.rdata` 50,016/76,722,
`.data` 15,766,548/15,766,564, imports 5 missing/3 added, file 2,678,784.
Next: the member list was filtered against reference imports by name only, so
ordinal imports (`name: null`) wrongly excluded members whose strings the
reference `.rdata` carries; rebuild that filter with ordinal-aware DLL rules.
Then the `.data` raw-content gap (file raw 147,456 vs 266,240) and `.text` 32 KB
residual.

### Round 32: member filter settled, header-layout blocker found

The import-name filter was too strict: member symbols carry stdcall decoration
(`createmovedibsection@24`), so comparing them with the undecorated reference
import names wrongly excluded 11 members. Probing by actual link (add member,
relink, compare the import table) is authoritative: 11 of 14 exclusions were
false and only `fontoutl.obj`/`fontextr.obj` really add imports (GDI glyph APIs).
The final list is 118 members, persisted in
`layout/Europa1400Gold_TL.exe/d3dx8-includes.rsp`; `rebrew verify --whole-binary`
gives `.text` 2,459,552/2,491,370, `.rdata` 50,000/76,722, `.data`
15,766,548/15,766,564, imports 5 missing/3 added, file 2,678,784.

Blocker found: the built image has SizeOfHeaders 0x2000 against the reference
0x1000, so `.text` sits at RVA 0x2000 instead of 0x1000 and every section VA is
shifted by 0x1000. Bytes 0x400-0x1F00 of the headers carry Intel compiler
`.comment` strings (`Intel(R) C/C++ Compiler Version 4.5 ... -Qvc6`) from the
`objd\i386` SSE objects in d3dx8.lib. The reference contains zero Intel markers,
so its D3DX8 build is not this archive. gold-o has the task to find which
symbols pull the objd members, whether release obj counterparts suffice, or
whether link can discard those sections; no `.lib` patching.

### Round 33: D3DX8 provider hunt

gold-o's header diagnosis is confirmed: the vendored `references/dxsdk8/lib/d3dx8.lib`
is an Intel-compiled build (8 `objd\i386` SSE members, Intel `.comment` strings),
while the reference carries zero Intel markers. Those comment strings push the
header block to SizeOfHeaders 0x2000, so `.text` starts at RVA 0x2000 instead of
0x1000. No linker option removes the records (`/OPT:REF`, `/MERGE:.comment=...`,
`/SECTION:.comment,D`, `/RELEASE` all measured useless); the archive itself has no
release SSE counterparts.

Searched for the matching MS-compiled archive: `edgeforce/directx8` (DirectX 8.0
SDK, `lib/d3dx8.lib`, 118 members, zero Intel markers) is too old (missing the
sse2_* entry points the game needs); `ojdkbuild/tools_toolchain_directx`
(DirectX 9.0 SDK, `Lib/d3dx8.lib`, 143 members, four Intel markers) needs
jpeg/png/gl helper libraries that the SDK repo does not ship, so it cannot link.
Neither is the reference's build. The matching archive remains unknown; until it
is found (or the SSE members can be reproduced byte-exactly, which needs their
source and flags), the header layout and the D3DX8 band cannot be identical.

Current image (wired 118-member include list): `.text` 2,459,552/2,491,370,
`.rdata` 50,000/76,722, `.data` 15,766,548/15,766,564, imports 5 missing/3 added.

### Round 34: matching D3DX8 provider found, header layout fixed

Provider search succeeded. The DirectX 8.1 SDK (October 2001) archive,
`DXF/DXSDK/lib/d3dx8.lib` from the archive.org `dx81sdk_full` installer, is
MS-compiled (zero Intel markers, no `objd` members) and links against our objects
once the JPEG/PNG implementation objects the SDK archive expects are supplied.
Those are plain-C objects extracted from the XP SP1 `d3dx8.lib`; the SDK archive's
own JPEG/PNG members use the `D3DX::` namespace, so only the non-overlapping
objects are used and `/FORCE:MULTIPLE` covers the shared libpng routine names
(same libpng source, measured duplicates, documented in `references/dxsdk8/VENDOR.md`).

The vendored `references/dxsdk8/lib/d3dx8.lib` is replaced with the SDK archive.
Result: SizeOfHeaders is 0x1000 (reference: 0x1000), zero Intel compiler markers
(reference: zero), and the whole-binary header comparison reports match. Imports
improve to 5 missing/2 added (`GetSystemInfo` disappears).

Also added source ordering to the TL target (`rebrew build order-sources` with the
vendored files' native first VAs and the restored zlib row bindings), so objects
land at their reference VAs. `verify --text --raw-link` now reports 3,868 of
4,991 functions byte-matched in the linked image.

Sections: `.text` 2,505,672/2,491,370 (14,302 overshoot), `.rdata`
53,164/76,722, `.data` 15,771,044/15,766,564. Same-offset file agreement stays
low (3.6%) because 1,025 bodies are still short or long: cumulative size drift
shifts every later function, so same-offset identity needs exact bodies, which is
the remaining work.

### Round 35: SDK8.1 archive wired, member set still approximate

The DirectX 8.1 SDK archive now lives at `references/dxsdk8/lib/d3dx8.lib`
(sha256 39a8e21889a7c1f0b966...), with the plain-C JPEG/PNG supplement objects
under `references/dxsdk8/supp/` and provenance in `references/dxsdk8/VENDOR.md`.
CMake wires: `/FORCE:MULTIPLE` for the shared libpng routine names, the 23
supplement objects, VA source ordering (`rebrew build order-sources` with the
vendored first-VA table), and a 62-member `/INCLUDE` list derived from the band
rows this archive can name.

Measured with that configuration: SizeOfHeaders 0x1000 and whole-binary header
comparison match (the reference's), imports 5 missing / 2 added, `.text`
2,444,492/2,491,370, `.rdata` 47,460/76,722, `.data` 15,715,076/15,766,564,
file 2,609,152. Verdict counts drifted slightly with the rebuild (EXACT 305,
RELOC 3,530, SIZE_MISMATCH 1,022, STUB 5, EXTRACT_ERROR 1) and need a verify
pass; the EXTRACT_ERROR row is a tooling verdict, not a byte comparison.

The member set is the remaining unknown on the library side: a broader
import-filtered set reaches `.text` 2,537,624 and `.rdata` 57,584 (closer to the
reference) but adds GDI glyph imports through an implicit `fontoutl.obj` pull
(only member that references `GetGlyphOutlineA`/`IsDBCSLeadByte`), and the
band-row-derived set undershoots `.text` by 46,878. Selecting members by matched
native symbols or masked-byte presence is the honest way to decide the set;
guessing by size proximity is not.

### Round 36: D3DX8 provider cannot be identified; byte identity blocked

Decisive test: for each candidate `d3dx8.lib`, mask the COFF relocation operands
of every function-level `.text` section and search the reference `.text` for the
masked pattern. A matching provider must reproduce its own linked code exactly.
Results: DirectX 8.1 SDK (Oct 2001, currently vendored) 741/2642 sections (28.0%),
DirectX 8.0 SDK 494/1971 (25.1%), DirectX 9.0 SDK (Dec 2002 and Mar 2004, same
archive) 732/2619 (27.9%), XP SP1 Intel archive 747/2620 (28.5%). No archive
reaches the reference's D3DX8 band; a spot check at the known owner
`0x5e6d72` (`_D3DXLoadSurfaceFromSurface@32`) finds no masked match from the
vendored archive anywhere near that VA. The ~28% common subset is the
compiler-independent code shared by every build.

The reference's D3DX8 was therefore compiled from the same sources with a
different compiler build or flags than every SDK archive available here, and its
sources are not present in the Windows source trees on disk (only headers and VB
bindings). The library band is about 450 KB of `.text`, roughly 18% of the image;
without its exact object bytes, whole-file byte identity is unreachable. Game
bodies can still be improved, but the 100% objective cannot complete on this
asset set.

Current best configuration (SDK8.1 archive + extracted JPEG/PNG objects + VA
ordering + 62-member include list): header comparison true (SizeOfHeaders 0x1000),
imports 5 missing / 2 added, `.text` 2,444,492/2,491,370, `.rdata`
47,460/76,722, `.data` 15,715,076/15,766,564, file 2,609,152, verdicts EXACT 300,
RELOC 3,535, SIZE_MISMATCH 1,023, NEAR_MATCHING 83, PROVEN 5, coverage 100%.
Evidence: `.scratch/lead/member-presence.json`, `.scratch/lead/compare_providers.py`,
`.scratch/dx8sdk/{sdk81,d3dx8.lib,d3dx8-dx9.lib,xpsp1.lib}`, `.../VENDOR.md`.

### Round 37: provider confirmed in toolchain images, member set re-derived

The user pointed at the toolchain images. Search found
`Vc7/PlatformSDK/Lib/d3dx8.lib` inside the MSVC 7.0 and 7.1 container layers
(under the server backup tree) and both are byte-identical to the DirectX 8.1 SDK
archive already vendored (sha256 39a8e21889a7c1f0b966...). So the provider was
available all along; the earlier "no archive matches" conclusion was wrong.

The masked-presence test was also misread: an SDK archive ships every member, but
the reference only links the referenced subset, so a fraction of matching sections
is expected. Re-scored with that model: 76 of 132 members have at least one
matching function section, 8 match every section. Building with the any-hit set
gives `.text` 2,491,436 vs the reference 2,491,370 (66 bytes over) but pulls the
GDI glyph imports through `fontoutl.obj`/`fontextr.obj`/`cd3dxfont.obj`.
The reference imports `CreateFontIndirectA` but no glyph APIs, and `fontoutl.obj`
matches only 4 of 50 sections (font code differs between D3DX builds), so those
members are excluded. Dropping them transitively yields a 68-member set with
imports 5 missing / 2 added.

Persisted configuration: 68-member include list, `.text` 2,464,492/2,491,370,
`.rdata` 47,500/76,722, `.data` 15,757,156/15,766,564, headers match, file
2,670,592. The remaining `.text` shortfall tracks the 1,023 partial game bodies,
not the member set: including extra library code "fixes" the size by coincidence
while adding imports the reference does not have.

### Round 38: NO_FUNCTION driven down, remaining bytes need completed bodies

The user asked to get NO_FUNCTION (the status ledger's unattributed `.text`
bytes) to zero. Work done: the inventory did not tile `.text`; 2,811 byte ranges
(35,861 B) had no inventory entry, and split bodies left further tails
unattributed. Reviewed repairs through the locked extent writer:
- 2,780 extent extensions over gaps whose bytes decode continuously as the same
  function and whose next inventory entry is a split part (reason recorded in
  metadata extent history),
- 31 admissions for import-thunk runs, jump tables and interior fragments that no
  entry names and no preceding function owns,
- 42 annotation SIZE syncs (`verify --fix-sizes`, protected EXACT/RELOC sizes
  kept).
The inventory now covers `.text` with zero gaps (`recompute_gaps.py` reports
`gaps 0`). NO_FUNCTION fell from 52,660 B to 43,472 B.

Remaining NO_FUNCTION bytes are not accounting holes: every byte now sits inside
an inventory span, and the residual is the difference between annotated body
sizes and native extents for rows whose bodies are still partial, mostly
EXACT/RELOC rows whose protected annotation SIZE cannot be rewritten. Reaching
zero needs those reference bytes reproduced by the corresponding bodies (the
ongoing body-exactness work), not another ledger change.

### Round 38b: near-match batches running, NO_FUNCTION accounting settled

Two fresh teammates work the closest NEAR rows with measured residuals
(`.scratch/lead/near-batch-n1.txt`, `near-batch-n2.txt`, five rows each).
Earlier quick-win agents landed: 0x550770 EXACT 35/35 (pack(1) struct
assignment), 0x465840 RELOC 12/12 (void-tail-call idiom), 0x41b820 RELOC 78/78
(extern float arrays instead of integer pointer literals, measured with
`--fix-sizes`). Recorded idioms from those batches: MSVC6 emits `pop ecx`
cleanup only when the enclosing function returns void; 0x4c70fa is a branch
target inside a larger function, not a function entry, so it must not carry a
row.

NO_FUNCTION stands at 43,472 B after inventory tiling; the remainder is body
shortfall against native extents on protected EXACT/RELOC rows and needs those
reference bytes reproduced, not another ledger edit.

### Round 39: NO_FUNCTION accounting fix upstream, two agents on the remainder

The residual NO_FUNCTION bytes were not accounting holes in the inventory (that
now tiles `.text`); they were native extents longer than the annotated body, with
the tail unowned because `status` only claimed the annotated size and cut the
tail at the next metadata row. Upstream change in
`/home/maci/Desktop/Projects/relumea/repos/rebrew/src/rebrew/status.py`:
`native_tail_span` attributes the bytes between the body end and the discovered
extent end to the row, counted as unmatched (the byte comparison still covers
only the annotated size); metadata-only rows no longer cut the previous entry's
tail. `status --json` also reports `unattributed_ranges` so the remainder is
inspectable. Regression tests added; `tests/test_status.py` and `tests/test_cli.py`
273 passed; full suite running.

Measured on GOLDTL: NO_FUNCTION 43,472 -> 5,227 B; matched bytes unchanged at
1,288,137; unmatched 1,197,894; padding 112. The remaining 5,227 B are 12 ranges
(one 44-byte game function at 0x4f1860 absent from both inventory and metadata,
and 11 D3DX8-band fragments inside over-extended inventory entries), plus
NO_SOURCE 31 inventory entries without rows (7 game fragments, 25 band thunks).

Two fresh teammates now own the remainder: tl-z1 (game range at 0x4f1860, seven
game entries) and tl-z2 (11 band ranges, 25 band thunk entries), each with the
measured VA lists under `.scratch/lead/z1-*` and `z2-*`.

### Round 40: NO_FUNCTION reached zero; NO_SOURCE is the remaining counter

Measured with the upstream status: NO_FUNCTION 0 B (was 5,227). The residual
ranges were closed by the attribution work (inventory splits plus rows for the
discovered bytes). NO_SOURCE is now 35 inventory entries without metadata rows,
because the splits and admissions added entries faster than rows were bound.
tl-z1 and tl-z2 are working exactly those entries; tl-p1 is converting the five
PROVEN rows to RELOC/EXACT; tl-ga1 runs the GA matcher on the parked near-miss
rows (tl-n1 had no manual win on them, all residuals are MSVC 6 scheduling).

Note for the next status read: rows under active edit can show STUB while the
agent is mid-loop; re-run verify after the batches report.

### Round 41: NO_FUNCTION 0 and NO_SOURCE 0 measured

Both counters are zero on the upstream status (which carries the native-tail
attribution change): `unattributed_bytes` 0 with zero `unattributed_ranges`, and
`functions` 4,947 covered of 4,947, so NO_SOURCE 0. Lint 0 errors, 26 warnings.
Evidence: `.scratch/lead/status-zero.json`.

How it closed, per owner:
- tl-z1 (task-314, game side): the 44-byte function at 0x4f1860 reconstructed EXACT
  and registered (`src/fcn_0041adc0.c` addition aside), seven game inventory
  entries attributed, five jump tables and one return byte retired into owner
  extents; inventory split set to 0x4f1840=16 0x4f1850=16 0x4f1860=48 to avoid
  double counting the native tail.
- tl-z2 (task-315, D3DX8 band): 21 reviewed extent repairs (10 container trims,
  11 admissions) and 36 LIBRARY identities bound to `src/library_d3dx8.h`
  (30 created through the locked writer, 6 retired rows rebound with history);
  NO_FUNCTION 5,227 B / 12 ranges -> 0.
- Lead: the last NO_SOURCE entry, 0x660ace (2,332 B import-forwarding thunk run in
  the 0x650000 CRT band), bound as an inferred LIBRARY identity in
  `src/library_imports.h` with the thunk-shape evidence in the reason.

Caveat for the metric: the pinned `.venv` rebrew 5.4.0 does not include the
upstream native-tail attribution, so `./.venv/bin/rebrew status` still reports the
old 38k+ figure. The zero is measured with
`.scratch/lead/run_upstream_rebrew.py status`. Making the pinned CLI report the
same needs a rebrew release bump, which requires user authorization.

Rows under active edit can still read STUB mid-loop: tl-p1 (five PROVEN rows) and
tl-ga1 (GA pass) are running; re-run verify after they report.

### Round 42: zero counters hold; PROVEN restored; data owner added

Settled state on the upstream status: NO_FUNCTION 0 B, NO_SOURCE 0 (4,947/4,947
covered), EXACT 302, RELOC 3,538, NEAR_MATCHING 83, SIZE_MISMATCH 1,018,
PROVEN 5, STUB 1 (the new 0x41adc0 body, still on its documented blocker).
Lint 0 errors, 26 warnings.

- tl-p1 (five PROVEN rows): 0 of 5 converted. Reports 0x404dc0 177/404 (option
  block allocator rotation; 360 permutations, flag sweeps, sp6 all inert),
  0x4c9e20 109/190 (cold `ret 1` block placement after branch relaxation),
  0x558220 169/332 (IV base rebase), 0x57d0d0 341/1802 (whole-body schedule),
  0x5a0ad0 101/271 (p/y register swap). All five sources restored byte-identical
  and the five PROVEN verdicts re-earned with `prove`.
- Data owner: 0x675318 had no DATA row, so 0x404dc0's `mov ecx,[0x675318]`
  reload had no binding. Created an inferred 4-byte .data row `gv_00675318`
  (module GOLDTL, file src/GOLDTL.ch_AttachAni.c) through `rebrew data set`,
  with a note that only the read dword is claimed (adjacent bytes look like an
  option-descriptor array followed by the string `ch_SetVisible():`, so the full
  allocation is unproven). Retest of 0x404dc0 is still 177/404; the binding no
  longer explains the score gap.

### Round 43: GA finds no source-expressible lever; GA pragma anchor bug fixed

tl-ga1 ran the GA engine on the seven parked near-miss rows (0x473610 31/33,
0x4c6e20 113/123, 0x50b840 125/136, 0x4b64b0 203/204, 0x490c10 113/118,
0x536b10 154/156, 0x4c3800 398/417). No improvement: every champion, recompiled
in place, reproduced the baseline count and the same mismatch offsets. The
residuals are MSVC 6 encodings and scheduling, not source-expressible. GA also
showed a real tooling bug: its pragma mutations inserted `#pragma auto_inline` /
`check_stack` between the ADDRESS anchor and the definition, and the anchor
parser (comments and blank lines only) then reports a dangling anchor, so the
champion cannot be measured.

Upstream fix: `rebrew/matcher/mutations/pragmas.py` inserts those pragmas above
the anchor block (`_before_anchor`), with three regression tests in
`tests/test_mutator.py` (check_stack, auto_inline, no-anchor fallback) and a
CHANGELOG entry. Full upstream suite: 13,183 passed, 29 skipped.

Settled counters: NO_FUNCTION 0, NO_SOURCE 0, EXACT 302, RELOC 3,538,
NEAR_MATCHING 83, SIZE_MISMATCH 1,018, PROVEN 5, STUB 1; lint 0 errors.

### Round 44: new lanes dispatched (tiny band functions, closest NEAR, import split)

Three fresh teammates are running:
- tl-i1 (task-318): implement nine tiny library-band rows the todo lists as
  improve-match, 10-41 bytes each (0x5eaad0, 0x5eb307, 0x5ec8bf, 0x5edcfa,
  0x5ef2e0, 0x5f022d, 0x5f0e27, 0x6052b9, 0x60ffc0).
- tl-j1 (task-319): push the closest NEAR rows, prioritising the four not yet
  tried (0x495180 623/625, 0x47c1f0 4-byte ModRM, 0x4ce210 swapped store/lea,
  0x40fb80 5 bytes).
- tl-k1 (task-320): split the nine multi-target functions out of the
  server-only server.c TU. The TL image currently imports
  KERNEL32!TerminateThread only because that TU is compiled whole; moving the
  shared functions to their own file should drop it, and the task requires the
  server DLL to stay byte-identical.

Status baseline for the round: EXACT 302, RELOC 3,538, NEAR_MATCHING 83,
SIZE_MISMATCH 1,018, PROVEN 5, STUB 1; NO_FUNCTION 0, NO_SOURCE 0, matched
1,296,250 B, lint 0 errors. Extra import backlog after the split: the second
added import (USER32!GetForegroundWindow) comes from the partial body of
src/fcn_0041e680.c (1,488 B, SIZE_MISMATCH), so it needs that row reconstructed
to disappear.

### Round 45: NO_FUNCTION 0 under the pinned CLI, ten parallel reconstruction agents

The 38,360-byte NO_FUNCTION figure was an artifact of over-merged inventory
extents: the discoverer spanned each row across its terminator and swallowed one
to four following functions. The ten tail-reconstruction slices proved it
independently (every row's body ends in ret/jmp at its annotated size, no branch
enters the tail). Work done instead:
- Computed the true splits for the 200 worst rows (capstone linear decode from
  each tail start to its terminator), applied 441 reviewed extent repairs (200
  parent trims plus 241 admissions, digest a2e75c66...),
- admitted the remaining 103 residual gap ranges from the upstream
  `unattributed_ranges` report (digest 37cb2c7e...),
- split and bound the last 10-byte fragment at 0x5f0e46.
Result: pinned `NO_FUNCTION` 38,360 -> 0 with zero ranges; upstream reports the
same 0.

Also: the tree came back green after the interrupted band-function agent left
unresolved PSGP dispatch symbols and a data-scaffold syntax error. Fixed the
scaffold generator types (`void*` for the opaque gate pointer), added measured
float triples g_6b5df8/g_6777b0/g_6777bc (reference values 0/0/0 and two 1/1/1),
added the three PSGP dispatch pointer slots, a cdecl fcn_005eaae0 placeholder, and
aligned the 0x444ff0 calling conventions with the true stdcall callees. The
workspace venv was switched to an editable install of the upstream checkout so
the pinned CLI reports the round-39 native-tail attribution; the released 6.3.0
wheel does not carry it. This is a tooling-development opt-in and is reversible
(`uv pip install` the 6.3.0 wheel again).

NO_SOURCE is now the open counter: 226 entries (31,903 B) without rows. The batch
skeleton run was stopped after creating rows for about 110 of them, and ten fresh
agents (task-331..340) each own 21-22 entries: they create the row with
`rebrew skeleton <va>`, reconstruct the body, and measure to EXACT/RELOC.

### Round 49: counters reconciled after the boundary merges

NO_FUNCTION is back to 0 B (0 ranges) after the reconciliation pass: 328 orphan
rows retired, 18 containers trimmed and 37 entries admitted for the residual
ranges, 88 rows created for uncovered starts, 27 identity-less rows rebound to
stub sources. NO_SOURCE is down to 8 from 337. Verdicts: EXACT 300, RELOC 3,549,
NEAR_MATCHING 83, SIZE_MISMATCH 992, PROVEN 5, STUB 269.

The 8 remaining NO_SOURCE entries have rows at inventory starts but status still
counts them uncovered; next round isolates them (compare status' discovered set
with the metadata rows) and closes the gap. The slice agents stay stopped: their
parallel tests saturated docker and a detached finish script rewrote the metadata
store, breaking every digest-guarded write. Resume with at most three agents and
one test at a time.
