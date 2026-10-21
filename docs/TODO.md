# Current work

## Status snapshot (2026-10-21 12:02 UTC)

The [README and charts](../README.md#reconstruction-status) now use one
`rebrew status --all-targets --json` report from the current working tree.

- Server: 250/251 C matches, 99.9% code accounting, and **8 differing raw-file
  bytes** out of 286,720. Earlier whole-file identity is a historical checkpoint.
- GoldTL: 3,805/5,123 C matches (74.2%), 48.4% code accounting.
  Gold: 2,466/4,592 C matches (53.7%), 22.8% code accounting.
- Both configured client executables are absent after failed relinks. Their
  raw-file metric is N/A; older scaffold scores are not reused.
- Stored initialized-data verification remains 100.0% for server and 0.0% for
  each client. GoldTL has 338 displaced symbols; Gold has 304.
  [Data metrics](../README.md#data-verification) separate bytes, symbols and EXACT
  reference-address verdicts.

This documentation refresh performs no compilation or new data verification.
The source/inventory/metadata reconstruction changes remain separate; rebuild,
compare and run the gate before claiming current whole-file identity.

The [three-binary objective](../goal.md) is incomplete. This checkpoint records
Goal110 checks on **2026-10-18**, completed client builds on **2026-10-19**,
the later, interrupted GUI text-creator integration, and the resumed delegated
reconstruction waves on **2026-10-19**.
Both clients remain comparison scaffolds. Historical checkpoints are in
[goal history](goal-history.md).

## Live state (2026-10-21, round 34)

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
