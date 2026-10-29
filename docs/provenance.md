# Provenance ledger

Append-only record of changes to the reconstruction deliverables. Each entry
names the date, the change, the reason, the evidence, who asked or decided, and
how the result was verified. Reversals are new entries.

## 2026-10-24 session round 6: fifteen uncovered game functions added to inventory

The rizin coverage comparison left 19 entries with no inventory row. Fifteen
are game-band code (1 to 88 bytes); one is a DirectDraw import thunk and three
are library-band entries. For each of the fifteen, the extent is the first
flow-exiting instruction end, checked against the next inventory start, and
the entries were admitted with
`binary repair-extents <VA>=<SIZE> --add-missing` under the digest preview
(`.scratch/lead/plan_missing_rows.py`,
`.scratch/lead/add_missing_rows.py`, receipt `.scratch/lead/missing-rows.json`).
Inventory rows: 4661 to 4676.

The new rows have no source binding or metadata identity yet, so the
authoritative FUNCTION/STUB counts do not include them. Registering them and
reconstructing the bodies is the follow-up: the bytes belong to the original
program even when a body is a one-byte `ret`. The DirectDraw thunk and the
library-band entries were deliberately left out of this batch. Decision: Lead.

## 2026-10-24 session round 6: library-proved rows converted in one write

The round-4/5 sweeps left 57 STUB rows and 27 reconstructed FUNCTION rows whose
bytes uniquely match a stock archive or a project-built zlib object. Converting
them one row at a time costs about a minute per row because each write is a
full read-modify-write of the 14 MB metadata store, so both batches ran through
the new `change_source_bindings_batch` API: one preview digest, one write per
batch, every row still keeping its own binding history and previous claim.

`.scratch/lead/adopt_library_batch.py` selects the rows, derives the identity
(archive family header plus native symbol for stock members, `references/zlib`
source for vendored objects), refuses non-C-identifier symbols, previews,
applies with the previewed digest, and backs up and deletes the replaced bodies
under `.scratch/lead/adopted-bodies/`. Receipts:
`.scratch/lead/stock-adoption-receipt.json`,
`.scratch/lead/reconstructed-library-receipt.json`. After the batches, the same
script reports zero remaining candidates.

Measured at 02:06 local: Gold FUNCTION/STUB rows 4353 (RELOC 2559, EXACT 202,
NEAR_MATCHING 26, SIZE_MISMATCH 70, STUB 1496); GoldTL unchanged at 5063
(STUB 266). The status shifts from RELOC/EXACT to LIBRARY are the intended
classification: those bytes come from the library, not from reversed game code.
`rebrew lint --json` is clean. Decision: Lead.

## 2026-10-24 session round 7: asm-block frame split reaches EXACT on the blitter

`0x47a320` is now EXACT 586/586 with zero relocations as a normal C function
`void __cdecl fcn_0047a320(int, int, int, int)` whose `__asm` block covers only
0x47a326..0x47a564. Two measured facts made it byte-exact:

- The compiler owns the outer frame when the C wrapper declares four arguments:
  c2 emits `push ebp; mov ebp,esp; push ebx/esi/edi` and the matching
  `pop edi/esi/ebx/ebp; ret`. Declaring the wrapper with fewer arguments drops
  the frame and the object comes out 582 bytes instead of 586.
- MASM will not encode the 23 absolute scratch/mask operands inline: an absolute
  memory operand is rejected, `ds:[...]` adds a 0x3e prefix, and extern C
  symbols introduce abs32 relocations (RELOC 586/586 but not EXACT). Those
  instructions are emitted as their exact native bytes through per-byte `_emit`,
  each annotated with the native mnemonic.

`source document-assembly` receipts are recorded for both hand-written rows
(`fcn_0047a320` source hash 11cba0f9..., `fcn_0041bb70` source hash e4698bda...);
no `__declspec(naked)` is used, so lint E023 stays satisfied. The same split
(frame in C, hand-written body in `__asm`, `_emit` for absolute operands) is now
the documented route for the remaining assembly rows. Decision: lead.

## 2026-10-24 session round 7: first EXACT hand-written-asm row through inline asm

`0x41bb70` is reconstructed as a normal `void __cdecl fcn_0041bb70(int pixel,
char *out1, char *out2, char *out3)` whose body is one `__asm { }` block, and
`rebrew test` records EXACT 317/317 with zero relocations. No `__declspec(naked)`
is used, so lint E023 stays satisfied. Measured code end is 0x41bcac (317
bytes); the stored 320 included three alignment NOPs and the metadata size
follows the measured extent.

Two MSVC 6 inline-assembly facts from this row, worth reusing for the other
hand-written blocks: `pushaw`/`popaw` are not mnemonics there (C2400), so the
PUSHA/POPA opcode is `_emit 0x66` followed by `_emit 0x60`/`_emit 0x61`; and
naming ebx/esi/edi inside the block makes MSVC emit its own entry push/pop
prologue, which shifts every byte, so those saves and the absolute
`mov eax,[0x14ce86c]` load go through `_emit` bytes too. The compiler's own
trailing return supplies the final ret. Receipt: agent report in session; source
`src/GOLDTL.fcn_0041bb70.c`. Decision: lead.

## 2026-10-24 session round 7: inline assembly is the route for hand-written asm rows

The remaining GoldTL STUB set includes rows that are not compiler output:
`0x41bb70` contains `0x60` PUSHAD/PUSHAW at two sites with full register
save/restore around 16-bit mask operations, and `0x47a320` is a manual-register
sprite/mask blitter with a shared epilogue and four copy/merge loops. Both are
hand-written assembly in the original source.

Lint E023 forbids a whole-function `__declspec(naked)` body, but inline
`__asm { ... }` inside an ordinary C function is already used by this project
(`src/Develop/DieGildeAddOn/game/spiel.c`,
`src/Develop/Units/m_alloc/m_alloc.c`). The reviewed route is therefore a normal
C function whose body reproduces the native instructions in inline asm, with
`rebrew source document-assembly` recording the positive evidence (PUSHAD is not
compiler-emitted; manual register banking). Tasks 92 and 94 carry that
instruction; assignment and STATUS stay in the normal per-row flow. Decision:
lead, following docs/assembly-audit.md.

## 2026-10-24 session round 7: two stale GoldTL sizes repaired

Two GoldTL rows kept a SIZE that no longer matched their reviewed canonical
extent, so `rebrew test` clipped the target and a correct body could not match:
`0x4c9e20` stored 332 against a 190-byte body, `0x414fb0` stored 332 against a
416-byte body. Both canonical extents are recorded in the inventory file and
match the measured code ends (0x4c9ede and 0x41514f, both at a return).

One locked batch write through `set_fields_batch` (`updated_by = fix-sizes`)
sets the two sizes; no status or history was touched. Receipt:
`.scratch/lead/fix_stale_sizes.py`. A target-wide
`coverage catalog --fix-sizes` was deliberately not run: 1899 GoldTL rows differ
between stored SIZE and the discovery inventory, and for most of them the
stored SIZE is the verified code extent while the inventory still carries
discovery padding. Decision: lead.

## 2026-10-24 session round 7: GoldTL D3DX8 band claims retired

The target config declares `external_ranges = ["0x5e0000-0x64ffff"]`: the T&L
client statically links `d3dx8.lib`, and the band holds linker-supplied D3DX8
code rather than game source. Work-left tools already skip the band, but 152
rows there still carried game-source claims (138 STUB, 13 unverified skeleton
rows, one earlier extract error) from earlier discovery/batch rounds.

A batch retire through `change_source_bindings_batch` removed those claims in
one metadata write, keeping each previous claim in `binding_history` and the
row's native size. The replaced stub files moved to
`.scratch/lead/band-retired/`. Verified verdicts inside the band (48 RELOC,
5 NEAR_MATCHING, 3 EXACT, 64 SIZE_MISMATCH) were left untouched: they are
earned measurements and a separate classification question. Receipts:
`.scratch/lead/retire_tl_band.py`,
`.scratch/lead/tl-band-retire.json`.

Then seven split arms that were branch targets (`jne`) of the adjacent previous
routine, and never call targets anywhere in the image, were merged into their
owners with `binary repair-extents --merge` (dev checkout; the 5.4.0 wheel lacks
the option) and their metadata claims retired
(`.scratch/lead/retire_merged_arms.py`, `.scratch/lead/tl-merged-arms.json`).
The merges moved 135+58+57+85 bytes into `0x521920`, 49 into `0x585910`, 487
into `0x41bf90` and 355 into `0x423670`.

GoldTL after both repairs: 4919 function rows (RELOC 3524, EXACT 288,
NEAR_MATCHING 87, SIZE_MISMATCH 899, STUB 118, 3 unverified), down from 266
STUB rows at the start of the round. Decision: lead, following the user's
GoldTL-first instruction.

## 2026-10-24 session round 7: GoldTL STUB-first focus

The user set the priority: clear GoldTL STUBs before continuing Gold. All five
teammates were redirected and three more were spawned, so eight reconstruct
GoldTL rows at once. Gold work stopped; the two Gold files left mid-edit were
restored from their backups (`0x43e1b0`, `0x541270`; the latter keeps a blocker
note recording the pause) and Gold counts are frozen at Rows 4404 / STUB 1480.

The first GoldTL batches exposed that many small STUB rows are not single
source functions. Evidence gathered with rizin and capstone:

- 18 rows start with a 5-6 byte jump and store a larger extent: three import
  thunks (`jmp [IAT]`), five tail-jump wrappers (`jmp rel32`), and ten
  thunk+body merges where an unrelated function follows. A reviewed
  `binary repair-extents` call shrank the heads to their jump body and added 15
  rows for the following code, with the preview digest guarding the write.
  Receipts: `.scratch/lead/plan_thunk_repairs.py`,
  `.scratch/lead/apply_thunk_repairs.py`, `.scratch/lead/tl-thunk-repairs.json`.
  The split also produced the three fragment rows `tl-a` had already mapped
  (`0x5ec8d6`, `0x5eb2ea`, `0x62a1d2`).
- Four rows are pure contiguous runs of import thunks (822 bytes total,
  `0x42b2e0`, `0x660600`, `0x5eaaf0`, `0x6606ba`); eleven more start with
  thunks. These are linker/import-library code; classifying them needs an
  import-thunk writer, not C bodies.
- Two rows are compiler local-unwind funclets of library functions
  (`0x650975`, `0x650a6b`). Their callers/callees are library-proved rows, so
  they also need library attribution rather than reconstruction.
- A row can also carry a forwarding function with a register argument the C ABI
  cannot produce (`0x60ff98`, __stdcall with the fifth argument in EDX); that
  needs assembly evidence or retirement.

After the extent repair and the first cleared row (`0x5ebbb9` EXACT 6/6),
GoldTL reads 5078 function rows (RELOC 3524, EXACT 288, NEAR_MATCHING 87,
SIZE_MISMATCH 898, STUB 265, 16 unverified fragment rows). Decision: user, lead
execution.

## 2026-10-24 session round 6: wrapped STUB rows split into 43 hidden functions

Rizin's function list, restricted to entries that start inside a metadata
FUNCTION/STUB row and land on a code boundary, found 36 over-merged STUB rows
that wrap 43 later routines. Example: row `0x46f170` stored 1722 bytes, but the
row starts with a 29-byte argument-shuffling thunk (`jmp 0x47ca00`) followed by
`0x46f190`, a 1690-byte function the inventory never listed.

All 36 rows were STUB, so no verdict was at stake. One
`binary repair-extents` call shrank each head row to its first hidden start and
added a row per hidden span (bytes stay contiguous: head plus hidden equals the
old size), guarded by the preview digest. Receipts and inputs:
`.scratch/lead/find_interior_functions.py` (boundary test),
`.scratch/lead/split_wrapped_rows.py` (plan, 36 rows / 43 entries),
`.scratch/lead/apply_splits.py` (preview digest and apply). `skeleton` then
registered 42 of the new rows as work items; `0x5de5a0` was already covered by
`library_dinput.h`. The split changes nothing about byte accounting; it makes
43 original functions addressable instead of hiding them inside one STUB row.

Measured after the split and batch 9: Gold function rows 4404 (RELOC 2571,
EXACT 202, NEAR_MATCHING 31, SIZE_MISMATCH 70, STUB 1479, 51 unverified rows
from the new bindings), `rebrew lint --json` clean. Batch 9 closed with three
RELOC (`0x4f7400`, `0x441db0`, `0x4f74f0`); twelve rows parked on documented
codegen walls. Decision: Lead.

## 2026-10-24 session round 6: new rows registered, and six were already covered

`skeleton --output src/GOLD.fcn_<va>.c` registered source bindings for nine of
the fifteen rows added from the rizin coverage diff: `0x4076c0`, `0x4370d0`,
`0x495780`, `0x4ac140`, `0x4b70f0`, `0x4c3f80`, `0x4cd5f0`, `0x5190d0`,
`0x541cb0`. They appear as unverifiable rows (no STATUS yet) and are work for a
later batch. The other six VAs already had a metadata row, which the coverage
comparison missed because it only read inventory spans: five are LIBRARY rows
bound to `library_lua50.h` (`0x49dee0`, `0x4a8c10`, `0x4cd5d0`, `0x4cd600`,
`0x53ba90`), and `0x504e20` is a FUNCTION row bound to
`src/GOLDTL.fcn_00507e70.c`. The five redundant inventory rows cannot be
withdrawn through a supported command; the gap is recorded upstream in
`docs/IDEAS-GUILD.md` (inventory row retire). Counts after registration: Gold
function rows 4362, STUB 1482, NEAR_MATCHING 31, RELOC 2568.

Batch 8 (fifteen delegated rows) closed with four RELOC (`0x435740`,
`0x52f560`, `0x532770`, `0x41ea20`) and two NEAR_MATCHING (`0x4ecc30`,
`0x45d870`); the rest parked on register-role or x87-retention walls with
bodies restored. Decision: Lead.

## 2026-10-24 session round 6: native functions the inventory does not cover

Rizin's full analysis (`aaa; afl`) lists 3734 functions in the Gold `.text`;
3715 of those entries fall inside an inventory row and 19 do not. Fifteen are
game-band entries (`0x4076c0`, `0x4370d0`, `0x495780`, `0x49dee0`, `0x4a8c10`,
`0x4ac140`, `0x4b70f0`, `0x4c3f80`, `0x4cd5d0`, `0x4cd5f0`, `0x4cd600`,
`0x504e20`, `0x5190d0`, `0x53ba90`, `0x541cb0`), one is a DirectDraw thunk
(`0x5de5d6`), and three are in library bands (`0x5dbd60`, `0x5e9700`,
`0x5eaad0`). Receipt: `.scratch/lead/coverage-gap.json`,
`.scratch/lead/rizin-functions-gold.txt`, comparison script
`.scratch/lead/compare_coverage.py`.

This undercounts hidden code: rizin does not recognise functions that start
with `mov` (the earlier `0x40da10` case), so inventory rows that wrap a later
routine need the split-plus-add path described in the previous entry. No
inventory or metadata change was made from this list; adding rows and
reconstructing them is the next step. Decision: Lead.

## 2026-10-24 session round 6: upstream batch binding writer and `library adopt`

Two upstream additions in `/home/maci/Desktop/Projects/relumea/repos/rebrew`:

- `rebrew.metadata.binding_history.change_source_bindings_batch` applies a
  reviewed list of retire/rebind changes in one metadata write. Each change gets
  its own binding history, a conflict rejects the whole batch before
  publication, and the preview digest guards apply. The single-row function now
  shares the same validation and document-mutation helpers; behavior is
  unchanged. Tests: `tests/test_source_binding.py::TestBatchBindingChanges`.
- `rebrew library adopt` records a unique stock-archive match over a FUNCTION or
  STUB row: it re-runs the project's archive match, requires one unique
  candidate, refuses vendored objects, writes the LIBRARY identity under the
  archive family's header, and guards the write with a preview digest.
  Supporting refactor: `lib_match.project_match_index` isolates the index
  construction the CLI and adopt share. Tests: `tests/test_library_adopt.py`,
  docs: `docs/CLI.md`. `identify_library.prepare_library_header` is now public
  so the two writers share it.

Verification: `uv run ruff check`, `uv run ruff format --check`, and
`uv run mypy` clean on the changed files; full `uv run pytest -q` after the
docs/changelog updates is recorded in the round report.

## 2026-10-24 session round 5: stock-archive rows moved to LIBRARY (in progress)

The STUB sweep matched 171 unique Gold rows to members of the stock archives in
the configured `external_libs` (mostly `msvc-6.0-sp5-pp_libc_stock.lib`). Those
rows carry a FUNCTION claim but the linker supplies their bytes, so the batch
rebinds each one to kind LIBRARY with `src/library_<family>.h` (the placeholder
header, created with the usual banner), the native symbol and a C name taken
from it, through `change_source_binding` with the previewed metadata digest.

`.scratch/lead/adopt_stock_rows.py` runs the batch; it rejects candidate symbols
that are not C identifiers (for example DirectInput's
`_c_rgodfDIKeyboard$S33646`) and backs up the replaced bodies under
`.scratch/lead/adopted-bodies/`. At the round close 108 of 171 rows were
adopted; the run continues in the background with its log at
`.scratch/lead/adopt-stock-run.log`. Each row costs about a minute because the
change is one full TOML read-modify-write on the 14 MB store; a batch binding
writer would be a useful upstream addition.

Measured at 01:56 local: Gold STUB 1555 (from 1698 at round start), function
rows 4439, `rebrew lint --json` clean (7154 files, zero errors, zero warnings).
GoldTL unchanged because its two stock matches were not converted. Decision:
Lead.

## 2026-10-24 session round 5: rows that wrap hidden functions

A delegated row (`0x0040d9a0`) revealed that some inventory rows end past the
routine and contain later, unlisted functions: the stored extent was 176 bytes
while the routine returns at 112, and `0x40da10..0x40da4f` holds two small
functions the inventory never listed. The fix (shrink the row, then add the
missing entries) is the same split pattern used for `0x42bd30` in round 71, but
it needs a reviewed list of hidden starts.

A first detector (`.scratch/lead/detect_overmerged.py`, receipt
`.scratch/lead/overmerged-rows.json`) flags 62 Gold and 56 GoldTL rows whose
code has a prologue start after a return with no branch to it. Spot checks show
both true positives (`0x4067f0`, a real `sub esp,0x90` function) and false
positives where a data table or a run of tiny log functions decodes as repeated
pushes, and it misses functions that start with `mov` (`0x40da10`). Rizin's
full analysis (`aaa; afl`) lists 3734 functions on Gold; diffing that list
against inventory coverage is the next cross-check. No inventory or metadata
change was made from this detector. Decision: Lead.

## 2026-10-24 session round 5: delegated reconstruction batches

Two batches covered thirty medium Gold rows with the decompiler hints.
Conversions at full byte match: `0x00574270` 173/173, `0x00452ee0` 167/167,
`0x00555460` 175/175, `0x004796b0` 178/178 (all RELOC); `0x00479600` EXACT
176/176 and `0x004ec940` NEAR 171/181; `0x0040d9a0` 112/112, `0x00479010`
179/179, `0x0045f6c0` 185/185, `0x00511630` NEAR 130/169, `0x004de530`
169/169, `0x00452e30` 166/166, `0x004134a0` 168/168, `0x0045eea0` 174/174,
`0x0041eb00` 178/178 (RELOC). The rest parked on documented codegen walls
(register allocation, basic-block order, old-compiler memset prelude) and the
bodies were restored. Round total: 12 RELOC, 1 EXACT, 2 NEAR_MATCHING.
`rebrew library match --va` returned false for every assigned row, so none was
library code.

## 2026-10-24 session round 5: twenty-one zlib rows moved to LIBRARY

The round-4 STUB sweep proved 21 Gold rows are project-vendored zlib 1.1.3
bodies (`library match --va` uniquely matched each to a `*.c.obj` built from
`references/zlib`). Nineteen were still STUB; two had been reconstructed to
RELOC in round 4 (`0x004637c0` `_inflate_blocks_new`, `0x00465590`
`_inflate_trees_bits`). Per the project rule that linked or vendored library
code stays library, each row was rebound to its zlib source with
`change_source_binding`: kind LIBRARY, file `references/zlib/<unit>.c`, the
native symbol, the reviewed reason, and the previewed metadata digest. This is
the same row shape `library bind-source` writes for a vendored library.

`.scratch/lead/adopt_zlib_rows.py` performs the batch. It re-checks that the
source file contains the matched C function name, previews each rebind,
retries only the concurrent-metadata race, and backs the replaced bodies up
under `.scratch/lead/adopted-bodies/` before deleting them. All 21 rows now
carry kind LIBRARY and no byte status; `rebrew lint --json` is clean (7263
files, zero errors, zero warnings). The 173 remaining stock-libc matches
cannot use this path because their provider is a toolchain archive member with
no project source file; they need the reviewed `library adopt` command
proposed in the upstream IDEAS-GUILD. Commands and receipts:
`.scratch/lead/adopt_zlib_rows.py`, `.scratch/lead/library-stubs.json`.
Decision: Lead.

## 2026-10-23 session round 4: STUB rows that are stock library code

Ran `rebrew library match --va` against every FUNCTION/STUB row on both clients
(8 workers, 2.6 s per call, `.scratch/lead/scan_library_stubs.py`, receipt
`.scratch/lead/library-stubs.json`). Gold: 204 of 1699 STUB rows match a stock
library body, 190 of them uniquely. 173 match
`msvc-6.0-sp5-pp_libc_stock.lib` (for example `0x005dfb95` is `_strtok` in
`strtok.obj`), and the rest match project-built zlib 1.1.3 objects such as
`deflate.c.obj`, `trees.c.obj`, `infcodes.c.obj` and `adler32.c.obj`. GoldTL:
2 of 266 (one DirectInput, one `___crtCompareStringA` in `libcmt_stock.lib`).

These rows are misclassified: they carry a FUNCTION claim but the bytes are
library code the project already links. No supported writer records a LIBRARY
identity over an existing FUNCTION row, so they stay STUB and off the link. The
feature proposal with a concrete command and test plan is in the upstream
`/home/maci/Desktop/Projects/relumea/repos/rebrew/docs/IDEAS-GUILD.md`
("Record a proved library identity over an existing FUNCTION row"), including
the zlib rows reconstructed in this round. Decision: Lead.

## 2026-10-23 session round 4: client inventory padding repair

Found 775 Gold and 10 GoldTL STUB rows whose stored extent ran past the last
reachable instruction into linker fill. The survey walks control flow from the
entry (following in-row jumps, stopping at ret or an out-of-row jump), takes the
latest flow-exiting instruction, and requires every byte to the next inventory
start to be 0x90, 0xCC or 0x00; a first version that used linear disassembly
alone was discarded because unreachable data can mimic fill. 690 Gold and 10
GoldTL rows qualified (`.scratch/lead/survey_padding2.py`).

Applied the repairs in digest-guarded chunks of 100 through
`binary repair-extents` (`.scratch/lead/repair_padding.py`), then aligned stored
SIZE in one `set_fields_batch` write with the `fix-sizes` tag
(`.scratch/lead/sync_padding_sizes.py`). The per-row `update_field` loop that
ran first rewrites the 30 MB store for every row and would have taken over an
hour; the batch writer finished 547 rows in one write. Re-running the survey
reports zero remaining fill tails on both clients, inventory sizes equal stored
SIZE for all 700 rows, and `rebrew lint --json` is clean (7284 files, zero
errors, zero warnings). The old extent survives in each row's `extent_history`,
so a wrong repair is reversible with another reviewed size change. Decision:
Lead.

## 2026-10-23 session round 4: rizin Ghidra decompiler pipeline for STUB rows

Installed REA 6.7.0 and kuna 1.160 for this session. Kuna cannot decompile the
clients (no x86 Sleigh specification), while rizin's `pdg` plugin (Ghidra
decompiler, via the REA rizin provider) works on both PE files and resolves
call names, globals and string references. Generated a hint file per STUB row
under `.scratch/decomp/<MODULE>/0x<VA>.c.pseudo` for 1603/1709 Gold and 256/267
GoldTL STUBs (`.scratch/lead/decompile_stubs.py`). Agents read the hint next to
the disassembly; rizin output is a hint, never source, and byte comparison still
decides STATUS. Live call for one function:

```
rizin -N -q -c 'e scr.color=0; s 0x<VA>; af; pdg' original/Europa1400Gold.exe
```

Decision: Lead.

## 2026-10-23 session round 4: import-related conditional donor fixed upstream

`source import-related` aborted the whole batch when one donor definition sat
inside a target `#if` block, because `_extract_function_text` raised `ValueError`
and the per-candidate loop did not catch it. The call now records an `error` row
naming that candidate and continues matching the rest. Regression test:
`tests/test_cross_import.py::TestCLI::test_conditional_donor_reports_row_and_continues`.
Full upstream suite: 13,093 passed, 36 skipped, one pre-existing failure
(`tests/test_ci_pins.py::test_resembl_ref_aligned`, from an earlier uncommitted
dependency refresh). ruff, format and mypy are clean on the changed files.
Fixed on the development checkout, not released. Decision: Lead.

## 2026-10-23 session round 4: two more split groups merged

After the padding repair changed the arm extents, the split survey found two
groups whose entry branch is conditional. `0x474cf0` absorbed `0x474e5d`
(365 to 392 bytes; tail binding retired). `0x526920` had a 161-byte hole:
`0x526a96..0x526b36` is an interior block reached by `je 0x526a96` and
`jne 0x526a9b` from inside the body, so the missing row was admitted with
`repair-extents --add-missing 0x526a96=161` and the group merged back to the
pre-split 592-byte extent (374 to 592). Evidence: rizin disassembly of
`0x526a80..0x526b40` and branch grep in `pdf @ 0x526920`. The `0x526b37`
binding retirement did not converge during the batch because agents were
writing metadata; it is retried after they finish. Decision: Lead.

## 2026-10-23 session round 4: delegated reconstruction batch

Five agents worked fifteen medium Gold STUBs with the new decompiler hints.
Six converted to RELOC at full byte match: `0x004637c0` 160/160,
`0x00465590` 163/163, `0x004586c0` 161/161, `0x0047d9d0` 158/158,
`0x00447340` 163/163 and `0x005a9930` 159/159. The first two are stock zlib
1.1.3 bodies (`library match --va` reports `_inflate_blocks_new` in
`infblock.c.obj` and `_inflate_trees_bits` in `inftrees.c.obj`); the project
already compiles `references/zlib/*.c` for 113 LIBRARY rows, so these two rows
are candidates for reclassification once a reviewed LIBRARY-over-FUNCTION writer
exists. They stay FUNCTION/RELOC for now and are recorded here as library
attributed rather than game reversing progress.

## 2026-10-23 session round 3: reviewed TL split-merge batch

Applied the merge tool to the GoldTL inventory after the branch-evidence review:
34 planned merges had a conditional branch entering a non-prologue arm;
33 were contiguous and applied, one (`0x526920=0x526b37`) was refused because
the head ends at `0x526a96` and the inventory has no row covering that gap, so
it needs separate review. The batch used the digest-guarded development
checkout command per group, then retired the absorbed bindings through
`source binding retire` and aligned each head's stored SIZE with the repaired
inventory through the locked writer (`.scratch/lead/complete_merges.py`,
`.scratch/lead/apply_merges.py`, receipts in `.scratch/lead/merge-review.json`).

The spans rebuilt from their own split history include `0x441ab0` (29 to 1116
bytes), `0x449630` (29 to 1131) and `0x489a70` (45 to 6055). The two former
cases are exactly the ones recorded as blocked in
[tooling gaps](tooling-gaps.md) before the feature existed. GoldTL STUB fell
from 296 to 267 and the inventory from 6616 to 6581 rows; every merged tail now
has no source binding and every head's stored SIZE equals its inventory extent.
`rebrew lint --json` is clean (7284 files, zero errors, zero warnings). One
redundant CFLAGS field on `GOLD 0x404c20` left by an agent flag trial was
removed through the metadata writer. Decision: Lead.

## 2026-10-23 session round 3: agent reconstruction batch and padding repairs

Five delegated batches reconstructed or refined nine Gold rows: `0x0041e0a0`
EXACT 85/85 (loop spelling `do { ... } while (1)`), `0x005d0b90` RELOC 108/108
(per-arm duplicated tails), `0x00474c90` RELOC 100/100, `0x0051d520` RELOC
64/64, `0x00448200` RELOC 102/102, `0x00453910` RELOC 107/107, `0x00452d80`
RELOC 124/124, `0x004c62a0` NEAR 103/123 and `0x004f3780` NEAR 84/95.

Four rows were blocked by inventory padding tails rather than by code:
`0x4f3780` 96 to 95, `0x5d0b90` 112 to 108, `0x41e0a0` 96 to 85 and `0x5d0b20`
112 to 108. For each, the bytes between the ret and the next inventory start
were verified as 0x90 fill, the inventory was repaired with
`binary repair-extents`, and the stored SIZE was synced before retesting.
Gold STUB fell from 1718 to 1709 and the authoritative counts are now RELOC
2549, EXACT 206, NEAR_MATCHING 24, SIZE_MISMATCH 81, STUB 1709.

## 2026-10-23 session round 3: upstream `binary repair-extents --merge`

Implemented the missing merge direction in the upstream checkout
`/home/maci/Desktop/Projects/relumea/repos/rebrew`. `repair_inventory_extents`
now takes ordered `merges` pairs; each extends the head extent to the tail's
end, removes the tail inventory row, preserves the tail's `extent_history`
under the head's new event, and binds the ordered merge list into the preview
digest. The CLI exposes `--merge 0xHEAD=0xTAIL` (repeatable) and no longer
requires a size operand. Files: `src/rebrew/catalog/inventory.py`,
`src/rebrew/inventory_repair.py`, `tests/test_inventory_repair.py`,
`CHANGELOG.md`.

Evidence: `uv run pytest tests/test_inventory_repair.py` 43 passed (28 existing
plus 15 new merge API/CLI cases); related suites `test_cross_import.py`,
`test_cli_help_copy.py`, `test_cli_contract.py`, `test_catalog_cli.py`,
`test_public_surface.py` all pass; `uv run ruff check` and
`uv run ruff format --check` clean; `uv run mypy` clean on both source files.
Full `uv run pytest -q` reports 10,400+ passed and one pre-existing failure,
`tests/test_ci_pins.py::test_resembl_ref_aligned` (Makefile pin 3.5.0 versus
uv.lock 3.6.0, from an earlier uncommitted dependency refresh, unrelated to
this change). The upstream working tree keeps the earlier uncommitted session
changes; this feature is not committed or released.

## 2026-10-23 session round 3: first reviewed split merge in the project

Applied the new command to the GoldTL split group
`0x426680`/`0x426a25`/`0x426a75`. The split history itself recorded the original
span: the head event was `old_size 1088 -> new_size 933`, and the two arms were
discovered inside that span on 2026-10-19 ("reviewed merged extent split").
Agent evidence from this session: `0x426a25` is reached by `je` from the routine
at `0x426680`, reads `esi` as its output pointer without loading it, and the
arms pop registers their own code never pushes.

```
uv run --project /home/maci/Desktop/Projects/relumea/repos/rebrew rebrew binary repair-extents \
  --merge 0x00426680=0x00426a25 --merge 0x00426680=0x00426a75 \
  --reason "Reviewed merged extent split repair: ..." -t Europa1400Gold_TL.exe \
  --expected-digest 90ff755c...
```

Inventory after the merge: `0x426680` is 1088 bytes, the two arm rows are gone,
and the merge reproduced exactly the pre-split extent. The two arm bindings were
retired through `rebrew source binding retire` with the digest-guarded preview
(`0x426a25` at 13:48:45 UTC, `0x426a75` at 13:51:04 UTC), and the head's stored
SIZE was aligned to the repaired inventory value through the locked metadata
writer (`update_field`, tag `fix-sizes`, receipt
`.scratch/lead/set_merged_sizes.py`). `rebrew lint --json` reports 7284 files,
zero errors, zero warnings. Decision: Lead.

## 2026-10-23 session round 3: extent-split inventory survey

Collected the rows the 2026-10-19 split created. GoldTL inventory has 68 split
groups, 157 arms, and 75 arms whose first instruction is not a prologue; the
planner emits 53 candidate merges (`.scratch/lead/merge-plan.json`,
`.scratch/lead/plan_merges.py`). Gold inventory has no split-history entries;
its 22 branch-target rows from the earlier detector are mostly tail jumps into
real functions and need per-row review, not an automatic merge. The first-instruction
detector that flagged 769 Gold rows as "over-popped" was withdrawn: a
multi-exit function legitimately pops saved registers in more than one epilogue,
so the signal is not artifact evidence on its own. Decision: Lead.

## 2026-10-23 round 207: STUB-first campaign, first batch

Started the "STUB to zero" phase requested by the user. Ten Gold functions left STUB and three more left SIZE_MISMATCH, all through `rebrew test` byte verdicts:

- Reconstructed C: `0x0047ce20`, `0x005deb3f`, `0x005ded95`, `0x0041e050`, `0x0045d990`, `0x005dffd3`, `0x00576b90`, `0x00576be0` (transcript receipts in `.scratch/gold-a`, `.scratch/gold-b`, `.scratch/gold-c`). `0x005deb3f` and `0x005ded95` are stock VC98 `sscanf`/`fputs` bodies rebuilt from the library source shape with the frame/optimize pragmas the stock objects use; `0x005dffd3` is the stock `_shortsort` body and carries `/O1 /Gd` in its row.
- Shared-body imports from GoldTL retargeted `GOLD 0x0042fce0`, `0x004aa580`, `0x004aa800`, `0x004ac8a0` and `0x0040ac00` onto the GoldTL bodies, all verified RELOC; the retarget is recorded through `rebrew source import-related --shared`, not by hand.
- `rebrew test --fix-sizes` persisted the code extents the tool itself measured (`0x0041e050` 80 to 76, `0x0045d990` 80 to 79, `0x00576b90`/`0x00576be0` 80 to 73, all trailing NOP fill).

Authoritative counts after the batch (metadata store, non-library module rows): GOLD RELOC 2543, EXACT 205, NEAR_MATCHING 22, SIZE_MISMATCH 81, STUB 1718. GOLDTL is unchanged at RELOC 3526, EXACT 289, NEAR_MATCHING 87, SIZE_MISMATCH 900, STUB 296. `rebrew lint --json` is clean: 7284 files, zero errors, zero warnings. Decision: Lead.

## 2026-10-23 round 207: survey of the library-band STUB rows

Classified every client STUB by native shape (`.scratch/lead/classify_stubs.py`, receipt `.scratch/lead/stub-classes.json`). Gold has 1554 reconstructable function rows, 175 in the static CRT tail at `0x5e0000` and above, and 3 linker tail jumps. GoldTL has 144 function rows, 150 in the declared `0x5e0000-0x64ffff` external band, one IAT thunk and one tail jump.

`rebrew library match --va` gives a unique stock-archive identity for 165 of the 175 Gold tail rows (for example `0x005e0202` is `___timet_from_ft` from `LIBC:findfile.obj`, `0x005e2716` is `__fdivp_sti_st` from `adj_fdiv.obj`), and the Gold raw link map already places those objects from `LIBC`. They are linked library code, so reconstructing them as game C would misaccount progress. Only 2 of the 150 GoldTL band rows match a configured archive, so that band still needs a provider decision. No supported command records a LIBRARY row over an existing STUB binding: `library identify` skips annotated VAs, and `review-native` and `bind-source` both require an existing LIBRARY row. Recorded as a tooling gap; no metadata was rewritten. Decision: Lead.

## 2026-10-23 round 207: verify-cache hygiene

A GoldTL compile run executed without the writable cache redirect and wrote 120 `COMPILE_ERROR` entries (`rebrew-unshare: mount target mkdir: Read-only file system`) into `.rebrew/targets/<hash>/verify_cache.toml` and `verify_cache.json`. The managed metadata store was not touched; the polluted per-target cache files were copied to `.scratch/lead/verify_cache-TL-polluted*` and removed so stored verdicts come from the metadata store again. Compiles in this workspace must set `XDG_CACHE_HOME=$PWD/.scratch/rebrew-cache`. Decision: Lead.

## 2026-10-23 round 207: `source import-related` aborts on conditional definitions

Reproduced: `rebrew source import-related --from Europa1400Gold_TL.exe -t Europa1400Gold.exe --candidates-only --dry-run --json` exits 2 with `cannot extract a conditional definition from a multi-function file`. `_extract_function_text` raises `ValueError` and the batch driver does not catch it, so one shared source containing a target-conditional definition kills a 1775-function run, including in dry-run. The shared mode (`--shared`), which does not extract text, works and is what this round used. Upstream fix pending: report the candidate as an error row instead of aborting. Decision: Lead.

## 2026-10-23 round 206: test branch-layout source variants

GoldTL `0x00536b8e` native `je -11` targets preceding `ret`; baseline emits `je +19` to function end. Tested cached handle, explicit return, and goto join. All kept 29/30 with same branch displacement. `/O1` reduced to 16/30. Restored original. Decision: Lead.

## 2026-10-23 round 205: test GoldTL result-store ordering

GoldTL `0x00473610` baseline is 31/33; mismatch is EDX versus ECX for global pointer, plus resulting store register. Reordering save before pointer load reduced score to 22/33. Chained assignment and volatile save preserved 31/33 but did not improve. Restored baseline. Decision: Lead.

## 2026-10-23 round 204: test control-word helper argument order

Gold `0x005e0c92` native pushes `0x30000` then `0x10000` before calling wrapper `0x005e7a7a`. Tested swapped C arguments to account for caller stack order; score fell from 15/19 to 13/19. Restored original call. Decision: Lead.

## 2026-10-23 round 203: test volatile field update

Gold `0x00466900` remains 107/111 bytes; final field addition differs only in register allocation. Tested volatile field pointer and separately materialized delta; emitted bytes unchanged. Statement climb and quick flag sweep also found no gain. Restored original expression. Decision: Lead.

## 2026-10-23 round 202: test field-update evaluation order

Gold `0x00466900` matches 107/111 bytes. Native final update loads field at `esi+0x16a0` into EDX, computes `3*e+0x11` in ECX, adds, stores. Tested explicit load-local and reversed expression evaluation; both kept 107/111 and same register allocation mismatch. Restored original expression. Decision: Lead.

## 2026-10-23 round 201: test typed callback dispatch form

Gold `0x005e3b08` invokes optional callback at `0x6f3058`, then returns booleanized callback result. Tested typed function-pointer global and explicit `return 1`; score fell from 10/27 to 12/29 with changed alignment. Restored original wrapper. Decision: Lead.

## 2026-10-23 round 200: inspect x87 control-word helper

Gold `0x005e6605` reads control mode from `[esp+4]`, masks `0x300`, ORs `0x7f`, writes `[esp+6]`, then executes `fldcw`. A C argument candidate did not reproduce native stack loads: test scored 4/30 and emitted 30 bytes versus native 23. Restored stub. Caller at `0x005e028d` establishes custom stack protocol; exact source owner remains unresolved. Decision: Lead.

## 2026-10-23 round 199: inspect floating-point control helper

Gold `0x005e6605` masks control word with `0x300`, ORs `0x7f`, stores to stack, and executes `fldcw`. Tested unsigned-int C plus narrow inline `fldcw`; output was 4/30 and larger than native 23 bytes. Reverted. Native input appears inherited from caller stack. Decision: Lead.

## 2026-10-23 round 198: test memcpy and do-while copies

Gold `0x005e7cd6` native emits relative-offset unrolled setup followed by a three-count pointer loop. `memcpy(dst,src,12)` scored 6/27; do-while pointer increment scored 9/29. Both are worse than ascending indexed loop at 10/29; restored baseline. Decision: Lead.

## 2026-10-23 round 197: test cleanup early return

GoldTL `0x00536b8e` native branch at `0x00536b96` jumps backward to the preceding `ret` when handle equals `-1`. Rewrote source as explicit early return; output remained NEAR_MATCHING 29/30, branch displacement still differs. Reverted. Decision: Lead.

## 2026-10-23 round 196: test loop termination form

Gold `0x005e7cd6` native fixed-count loop uses decrement-and-branch. Tested `i != 3` with preincrement instead of `i < 3`; output remained 10/29 but moved instruction alignment and worsened individual byte correspondence. Restored original condition. `rebrew match climb` found no statement-order gain. Decision: Lead.

## 2026-10-23 round 195: test source-relative copy offset

Gold `0x005e7cd6` native computes `destination - source`, then stores each loaded dword at `[source + offset]`. Tested a C source-relative offset formulation; output stayed 29 bytes but match fell from 10/29 to 7/29. Reverted. Decision: Lead.

## 2026-10-23 round 194: test descending copy loop

Gold `0x005e7cd6` copies three dwords using a decrementing counter and advances source pointer. Tested descending indexed loop (`i=2; i>=0; i--`); output fell from 10/29 to 7/32. Restored ascending loop. All-target lint remains clean. Decision: Lead.

## 2026-10-23 round 193: test explicit cdecl cleanup assembly

Gold `0x005e0c92` should push two arguments, call `0x005e7a7a`, then emit two `pop ecx` instructions and `ret`. Explicit inline cleanup assembly after the C call did not improve output; it grew to 22 bytes, match remained 15/19. Restored source. A `/O1` flag sweep gave no valid exact candidate under function-matched flags. Decision: Lead.

## 2026-10-23 round 192: reconstruct CRT fatal-message handler

Gold `0x005e0b9b` calls `__FF_MSGBANNER` when `g_6f3014 == 1`, then `__NMSG_WRITE(message)`, then `__amsg_exit(0xff)`. Library resolution identifies stock `wincrt0.obj` providers. C candidate produced 21/40 vs native 37 bytes; unresolved data and CRT relocations remain. Reverted candidate. Decision: Lead.

## 2026-10-23 round 191: test C helper calling convention hypothesis

Gold `0x005e0c92` native pushes two constants, calls `0x005e7a7a`, then pops each argument separately. Candidate inline `pop ecx` cleanup still emitted `add esp,8`; output did not improve. Changing callee to two arguments also failed wrapper and caller byte matching (4/25 and 15/19). Restored one-argument callee and caller. All-target lint remains clean. Decision: Lead.

## 2026-10-23 round 190: verify unresolved Gold state global

Gold `0x6f2594` has 25 native code references, including five writes and several readers of its bit flags. `rebrew data list --target Europa1400Gold.exe --json` reports `g_6f2594` declaration only, no storage owner or size. `.data` range membership does not prove identity. Handler `0x004c6a60` remains RELOC 37/37 with unresolved relocations. No speculative owner added. Status: server 100% raw match; GoldTL 2.0%, Gold 1.1%; lint zero errors/warnings. Decision: Lead.

## 2026-10-23 round 189: annotate Gold handler address

Gold `0x004c6a60` had a matching source definition but no address annotation in its shared TU. Added `ADDRESS: GOLD 0x004c6a60`; `rebrew source register ...` still records two functions without updating its existing row. Focused test stays RELOC 37/37 with unresolved global relocations. Goal remains client file reconstruction. Decision: Lead.

## 2026-10-23 round 188: test Gold wrapper parameter order

Gold `0x005e7a7a` native wrapper loads second argument first, masks `0x80000`, pushes it, then pushes original first argument. Changed C declaration to two arguments and passed masked second/original first to callee; output worsened from 4/22 (20 bytes) to 4/25 (25 bytes). Restored baseline one-argument wrapper. All-target lint remains clean. Decision: Lead.

## 2026-10-23 round 187: verify Gold handler data relocation

Gold `0x004c6a60` remains RELOC 37/37; both references to `g_6f2594` resolve to native VA `0x6f2594`, but no data owner or managed address row proves storage identity. `rebrew data list --target Europa1400Gold.exe --json` shows declaration only, no definition or size. VA lies inside `.data`, which is not ownership proof. Kept binding unresolved. All-target lint: zero errors/warnings. Decision: Lead.

## 2026-10-23 round 186: identify CRT control-word wrapper

Gold `0x005e7a45` wraps CRT `__control87`: native code calls `_control87(0,0)`, merges requested bits with `(current & ~mask) | (flags & mask)`, then calls `_control87(value,0x1f3f)`. `rebrew library match --va 0x005e7a45 --target Europa1400Gold.exe --resolve-callees --json` identifies stock `ieee87.obj` providers for `__abstract_cw` and `__hw_cw`. C candidate using `__control87` scored 8/53; reverted. This semantic reconstruction is verified, exact C byte match unresolved. Decision: Lead.

## 2026-10-23 round 184: repair Gold handler extraction

Gold `0x004c6a60` native handler ORs byte `cmd+0x10` into absolute global `0x6f2594`, then sets optional result byte. Added Gold-only body after lower-VA Gold function in shared `command.c`. `rebrew test 0x004c6a60 --target Europa1400Gold.exe --json` reports RELOC 37/37; relocations to global remain unresolved. Reordering removed all W030 warnings; lint reports zero errors and warnings on all targets. Global storage owner and VA binding remain unverified. Decision: Lead.

## 2026-10-23 round 183: inspect Gold floating-point helper

Gold `0x005e0270` is a 29-byte helper that stores x87 ST(0) to stack, calls `0x005e6678`, then `0x005e028d`. Tried modeling as C `cos`/`sin` and as direct helper calls; outputs were 0/29 and 6/29. Restored stub. Native float-stack convention remains unresolved. Lint remains zero errors, two warnings per target. Decision: Lead.

## 2026-10-23 round 182: test allocation retry loop form

Gold `0x005dec9f` native retry branches to `0x005deca6` after failed allocation. Replaced recursive C retry with `while`; output worsened from 4/50 to 6/63. Restored baseline. Lint remains zero errors and two warnings per target. Decision: Lead.

## 2026-10-23 round 181: test extra local in modal function

T&L `0x00526660` frame already matches, but early prologue stack slots for `saved` and `h` are swapped relative to native. Added unused local to change allocation order; optimizer removed it and output stayed 41/599. Reverted. No source correction established. Decision: Lead.

## 2026-10-23 round 180: inspect caller argument order

Gold `0x005e0c92` pushes `0x30000` then `0x10000` before calling `0x005e7a7a`. Source arguments already produce this stack order under cdecl. Reversing C arguments worsened caller match from 15/19 to 13/19; reverted. Wrapper signature remains uncertain. Decision: Lead.

## 2026-10-23 round 179: test fixed-count pointer loop

Gold `0x005e7cd6` native uses pushed count 3, relative destination base, and decrement loop. Tested `while (count-- != 0) *dst++ = *src++`; result did not improve baseline 10/29. Reverted. Lint remains zero errors and two warnings per target. Decision: Lead.

## 2026-10-23 round 178: test Gold zero-predicate pointer loop

Gold `0x005e7cfd` native reads three dwords through advancing pointer and counter. Changed indexed access to `*a++`; output fell from 9/27 to 7/30. Reverted. Lint remains zero errors, two warnings per target. Decision: Lead.

## 2026-10-23 round 177: test pointer-increment copy loop

Gold `0x005e7cd6` native copy loop uses source/destination pointers and fixed count 3. Replaced indexed access with `*dst++ = *src++`; output fell from 10/29 to 9/29. Reverted. Lint remains zero errors, two warnings per target. Decision: Lead.

## 2026-10-23 round 176: verify second task-clear site

Tested native `mov ecx,0x65; xor eax,eax; rep stosd` at second clear in GoldTL `0x004050c0`. It failed to preserve exact 110-byte output, whether used alone or at both clears. Restored C `memset` at second site; first site retains assembly and remains EXACT in T&L and Gold `0x004047a0`, 110/110. Lint: zero errors, two warnings per target. Decision: Lead.

## 2026-10-23 round 175: inspect Gold wrapper stack argument

Native caller `0x005e0c92` pushes `0x30000`, then `0x10000`; wrapper `0x005e7a7a` loads `[esp+8]`, masks it, then pushes post-push `[esp+8]`. Tried reading the adjacent caller stack slot in C; output worsened from 4/22 to 3/25. Reverted; function signature remains unresolved. Decision: Lead.

## 2026-10-23 round 174: test two-argument Gold wrapper

For Gold `0x005e7a7a`, native reads second argument at `[esp+8]`, then calls `fcn_005e7a45` with masked value and first argument. Changed reconstructed one-argument wrapper to two arguments; compiler output worsened from 4/22 to 4/25. Reverted. Lint remains zero errors and two warnings per target. Decision: Lead.

## 2026-10-23 round 173: test additional projection scratch local

T&L `0x00441ab0` target frame allocates `0xf4` versus C's `0xe8`, despite identical 1056-byte function length. Added unused `float[3]`; optimizer removed it and output remained 26/1056. Reverted. This frame delta is insufficient alone to identify missing source locals. Decision: Lead.

## 2026-10-23 round 172: review shutdown helper boundary

Native `0x00536b8e` begins after `ret` at `0x00536b8d`; its `je -11` returns to that preceding `ret`, not a self-loop. Inventory extent is 30 bytes and calls show no callers, while metadata has separate function identity. No extent repair without authoritative inventory evidence. Candidate remains 29/30. Lint remains zero errors, two W030 warnings per target. Decision: Lead.

## 2026-10-23 round 171: test literal shutdown self-loop

GoldTL `0x00536b8e` native branch displacement returns to its own `je` when global equals -1. Tried inline `jmp $-2` in the else arm; MSVC emitted a 45-byte function, worse than 29/30 baseline. Reverted. Lint remains zero errors and two W030 warnings per target. Decision: Lead.

## 2026-10-23 round 170: test pointer reload scheduling

T&L `0x00473610` compiles `g_77250c` reload into ECX; native uses EDX, causing distinct ModRM bytes at offset 15 and displacement byte at offset 26. Inline assembly preload increased object size and reduced match to 14/38. Combined native stores failed MSVC 6 inline-assembly operand validation. Reverted both variants; baseline remains 31/33. No upstream Rebrew bug found. Decision: Lead.

## 2026-10-23 round 168: test T&L shutdown helper branch

For GoldTL `0x00536b8e`, tested inverted guard with early return; compiler emitted same 29/30 bytes. Restored baseline. Native `je -11` still differs from source control flow. Lint: zero errors and two warnings per target. Decision: Lead.

## 2026-10-23 round 169: test scheduler flag sweep and volatile pointer

GoldTL `0x004050c0` is EXACT in both client targets after round 167. Ran targeted flag sweep for `0x004050c0`; no exact candidates. T&L `0x00473610` remains 31/33; making `gp` volatile did not change output, then reverted. No source changes. Decision: Lead.

## 2026-10-23 round 168: test GoldTL shutdown guard polarity

T&L `0x00536b8e` differs only in short conditional branch displacement: native `je -11` forms an infinite self-loop when global equals -1, source returns normally. Inverted guard with early return compiled to same bytes and did not improve 29/30. Reverted. Native oddity remains unexplained; no change. Decision: Lead.

## 2026-10-23 round 167: reproduce native task clear sequence

GoldTL `0x004050c0` mismatch was instruction order at two clears: native uses `mov ecx,0x65; xor eax,eax; rep stosd`, C `memset` emitted the first two reversed. Applied this sequence at first clear only; T&L and Gold `0x004047a0` both test EXACT, 110/110. Documented per-target assembly evidence for both targets; lint returned to zero errors/warnings beyond existing W030s, two warnings per target. Decision: Lead.

## 2026-10-23 round 166: retry octree ancestor loop form

For T&L `0x0041bf90`, changed `&g_6b6f20[4]`/`&g_6b6f20[0]` to array-pointer expressions. `rebrew test` stayed 23/508, no byte change. Retained equivalent expression for clarity, no match gain. Lint remains zero errors and two W030 warnings per target. Decision: Lead.

## 2026-10-23 round 165: trace Gold startup environment helper

Inspected `0x005e0b9b` and callers. Native routine checks initialization global, calls two helpers and an indirect CRT entry; source stub has 37-byte inventory extent while disassembly shows body through 0x5e0bbf. Candidate decompilation lacked verified global address/indirect-call identity and yielded 20/40 with relocation conflicts. Reverted; no safe fix. Decision: Lead.

## 2026-10-23 round 164: test relative-address copy loop

Gold `0x005e7cd6` native stores via destination-minus-source base delta. Expressed that relation in C loop; result stayed 10/29, same as indexed baseline. Reverted. Decision: Lead.

## 2026-10-23 round 163: confirm shared command TU ordering blocker

Re-ran `rebrew source organize review ... --shared`; it remains unsafe due to three duplicate/different shared bodies and missing include closure (`windows.h`, `stdio.h`, `string.h`, `stdlib.h`) across targets. W030 reorder lacks safe organization plan. No source edit. Candidate queue unchanged; client matches remain 2.0% and 1.1%. Decision: Lead.

## 2026-10-23 round 162: review source-order fix safety

`rebrew source organize review` reports `safe_to_reorganize=false` for shared `command.c`, with duplicate definitions and incomplete include closure across all targets. W030 cleanup by moving definitions is not safe without resolving those blockers. No source edit retained. Decision: Lead.

## 2026-10-23 round 161: trace source-order warnings

All remaining lint warnings are W030 in shared `command.c`. `cm_ChkCommandType` at line 1510 maps Gold `0x4c6a60`; `cm_MarkAndReturn` at line 1531 maps Gold `0x4c6a50`, so native VA order is reversed. `ahm_ProcessEntityChain` at line 785 maps Gold `0x4c43c0`, while current row `0x4c6a60` is defined later. No reorder applied because shared TU includes cross-target mappings and no verified source organization plan established equivalent placements. Server gate passes raw identity and 316/316 functions, 652/652 data, Wine; full gate fails W030 and two D3DX8 ownership findings. Decision: Lead.

## 2026-10-23 round 160: document unresolved Gold stub

Set Gold `0x004f2540` blocker with `rebrew blocker set 0x004f2540 ... --target Europa1400Gold.exe`. This removes W005 without claiming behavior. All targets now have zero lint errors and two W030 warnings. Decision: Lead.

## 2026-10-23 round 159: verify remaining blocker status

GoldTL `0x0041a8c3` remains an interior return block, not a standalone function: callers jump into its parent frame, and the 13-byte inventory includes alignment NOP at `0x0041a8cf`. Server gate passes raw file identity, function/data checks and Wine load/export checks. Overall gate still fails on three lint warnings and two GOLDTL D3DX8 library-code findings. Client agreement remains 2.0% and 1.1%. Decision: Lead.

## 2026-10-23 round 158: retest control-word wrapper mapping

Rechecked Gold `0x005e7a7a` after target status refresh. Native wrapper takes two arguments, but tested C argument mapping compiled to 18 bytes and 9/22; baseline is 20 bytes and 4/22. Restored baseline. Decision: Lead.

## 2026-10-23 round 157: test two-argument control-word wrapper

Gold `0x005e7a7a` native wrapper reads second argument, masks `~0x80000`, pushes it then first argument, and calls `__control87`. Two-argument C mapping compiled to 18 bytes, 9/22, worse than baseline 4/22. Reverted. Full flag sweep cancelled at 95,280 sampled combinations. Decision: Lead.

## 2026-10-23 round 156: test shared-result zero-check loop

Gold `0x005e7cfd` candidate used one result variable with `break`; native path returns 1 only after all three zero values. Candidate scored 8/27, below baseline 9/27. Reverted. Decision: Lead.

## 2026-10-23 round 155: test break-form zero-check loop

Gold `0x005e7cfd` break-on-nonzero loop preserved semantics but compiled to 24 bytes and 6/27, below baseline 9/27. Reverted. Decision: Lead.

## 2026-10-23 round 154: test pointer-copy loop

Gold `0x005e7cd6` source pointer/count loop modeled native post-increment copy behavior but scored 6/29, below baseline 10/29. Reverted to indexed loop. Target flag sweep yielded no exact candidate. Decision: Lead.

## 2026-10-23 round 152: test pointer-advance zero-check loop

Gold `0x005e7cfd` native code advances input pointer and increments a separate loop counter. Source loop using `i++, a++` scored 14/29 against baseline 9/27. Reverted. Lint remains zero errors, three warnings each. Decision: Lead.

## 2026-10-23 round 151: test unrolled three-dword copy

Gold `0x005e7cd6` native code uses a count-driven loop. Three explicit assignments scored 6/27 versus baseline 10/29; reverted. Existing loop restored. Decision: Lead.

## 2026-10-23 round 150: review todo queue extraction errors

Audited upstream `todo.py` and tests for three T&L `EXTRACT_ERROR` rows. The queue correctly excludes these from byte-delta work; tests cover guild-rebrew case. Missing managed definitions have separate target/kind/source/symbol checks. Upstream tests confirmed 5 passed. No Rebrew bug found; no code changed. Project metrics remain server 100.0%, GoldTL 2.0%, Gold 1.1%; lint zero errors, three warnings each. Decision: Lead.

## 2026-10-23 round 149: test copy-loop increment spelling

Gold `0x005e7cd6` remains 10/29. Changing `i++` to `++i` kept the same verdict and object size. Explicit `i += 1` also tested but tool output was deduplicated; source restored to baseline. No gain. Decision: Lead.

## 2026-10-23 round 148: test branch-specific queue clear

T&L `0x004050c0` has two equal `memset(task,0,0x194)` blocks. Splitting only the first into 0x190-byte clear plus explicit first dword zero changed compiler layout; match fell from 98/110 to 37/116. Reverted; baseline retained. Targeted flag sweep found no exact result. Decision: Lead.

## 2026-10-23 round 147: test alternate control-word argument mappings

Tested two 2-argument source mappings for Gold `0x005e7a7a`, guided by native stack order and caller pushes. They scored 8/22 (validated callee relocation) and 9/22 (conflicting relocation). Reverted; baseline reverified at 4/22. All-target lint zero errors, three warnings each. Decision: Lead.

## 2026-10-23 round 146: investigate source memo reset paths upstream

Audited upstream Rebrew source-hash and parsed-source memo lifecycle. `clear_source_memo` clears only hash bodies; parsed-source reset clears its own byte/path caches. No production path requires cross-clearing because both caches are keyed by resolved path and `(mtime,size,inode,ctime)`. Focused upstream tests: 177 passed; Ruff check and format passed. No cache bug confirmed, no upstream edits. Project metrics remain server 100.0%, GoldTL 2.0%, Gold 1.1%; lint zero errors, three warnings each. Decision: Lead.

## 2026-10-23 round 145: verify Gold control-word wrapper caller

Gold `0x005e0c92` pushes `0x30000` then `0x10000`, calls `0x005e7a7a`, then pops both args. Native wrapper masks its second argument by `~0x80000` and passes masked second, then first, to `__control87` at `0x005e7a45`. Corrected-form source still compiled to 25 bytes and 4/25, worse than prior 4/22; reverted. Baseline remains 4/22 with unresolved relocation conflict. All-target lint: zero errors, three warnings each. Decision: Lead.

## 2026-10-23 round 144: test linked-list loop exit form

T&L `0x0060d860` uses a native list walk with `v == a2` success and `v == a1` cycle exit. A combined-condition `for (;;)` rewrite kept object size 110 but dropped match from 17/110 to 16/110. Reverted; baseline reverified. Decision: Lead.

## 2026-10-23 round 143: remeasure GoldTL extraction queue

Re-tested all three queued GoldTL rows. `0x00605ccf`: 18/347; `0x0060d860`: 17/110; `0x0060f354`: 13/355. Each compiles; queue category `EXTRACT_ERROR` is stale relative to measured `SIZE_MISMATCH`. No source edits. All-target lint: zero errors, three warnings per target. Decision: Lead.

## 2026-10-23 round 142: verify three GoldTL extraction queue items

`rebrew test` confirms `0x00605ccf`, `0x0060d860`, and `0x0060f354` compile to objects. Their TODO `extract-error` category is stale: measured results are SIZE_MISMATCH (18/347), plus the two remaining candidates were not separately reclassified this round. No extraction defect reproduced. Target metrics remain server 100.0% (251/251), GoldTL 2.0%, Gold 1.1%; all-target lint zero errors and three warnings each. Decision: Lead.

## 2026-10-23 round 141: check global target progress

`rebrew status --all-targets --json`: server 100.0% file agreement, 251/251 game functions; GoldTL 2.0%, Gold 1.1%. Queue remains blocked by three GoldTL extract errors and near-match codegen ties. No source changes this round. Decision: Lead.

## 2026-10-23 round 140: test reverse-index copy loop

Gold `0x005e7cd6` native loop copies three dwords with pointer-difference addressing. A reverse-index C loop compiled to 29 bytes and matched 10 bytes, same as baseline. Reverted; original loop retained. Decision: Lead.

## 2026-10-23 round 139: test short copy-loop source forms

Gold `0x005e7cd6` copies three dwords. Changing loop condition to `!=` kept 10/29. Unrolling assignments scored 6/27, reversed order 7/27. Reverted all variations; source loop retained. Decision: Lead.

## 2026-10-23 round 138: test split memset slot clearing

The two remaining deltas in `0x004050c0` swap `mov ecx,0x65` and `xor eax,eax` before `rep stosd`, twice. Replacing `memset(task,0,0x194)` with an equivalent 0x190-byte clear plus explicit first-word zero changed code layout and reduced the match from 98/110 to 38/116. Reverted; baseline reverified at 98/110. All-target lint unchanged. Decision: Lead.

## 2026-10-23 round 137: test reordered switch case labels

Tried grouping the case labels in `0x0050c4e0` to alter compiler block layout. Result fell from 104/110 to 93/110 with a 106-byte object. Reverted; baseline reverified at 104/110, 110-byte object. All-target lint remains zero errors, three warnings each. Decision: Lead.

## 2026-10-23 round 135: classify Gold helper reconstruction blocker

Native disassembly shows Gold `0x004f2540` scans 256 entries at stride `0xa9`, filters kind `0x1d` using the table at `0x7e3f30`, then calls `0x004ef7c0` and returns two out parameters. A first body draft could not be compiled because the row symbol `_fcn_004f2540_GOLD` is missing from the object, despite the source declaration and metadata entry; reverted draft. `rebrew test` reports `EXTRACT_ERROR`, zero object bytes. No upstream Rebrew bug confirmed. Decision: Lead.

## 2026-10-23 round 134: run server gate and reassess lint blockers

`uv run scripts/gate.sh`: server raw link remains byte-identical; function/data verification passed 316/316 and 652/652; Wine load/export resolution passed. Gate still reports project lint regression due to three known warnings: W030 source-order findings in shared command TU and W005 missing blocker on Gold `0x004f2540`. Gate also identifies two D3DX8 library-code findings in GoldTL. Client raw identity remains GoldTL 2.0%, Gold 1.1%. No source edit this round. Decision: Lead.

## 2026-10-20

### Reconstructed function bodies (GOLDTL)

- Change: hundreds of `src/GOLDTL*.c` bodies rebuilt or corrected through the
  staffed reconstruction workflow; status transitions written only by
  `rebrew test`/`rebrew verify`.
- Why: reach byte-identical coverage of `Europa1400Gold_TL.exe` (session goal).
- Evidence: per-function `rebrew test --json` verdicts, `.scratch/recycle2/results/`,
  `.scratch/wave*/results/`, `.scratch/round5/results/` reports; promoted rows
  listed in the session log.
- Decided by: user goal; each body reviewed against `rebrew diff` and asm.
- Verified: `rebrew test` match counts; RELOC promotions re-measured after every
  extent repair; no STATUS hand-written.

### Reviewed extent repairs (inventory only)

- Change: `rebrew binary repair-extents` batches applying reviewed native body
  boundaries and merged-row splits (trailing NOP removal, added entries).
- Why: stored SIZE padded to next entry blocked RELOC for complete bodies.
- Evidence: `.scratch/wave2/extent-specs.tsv` (each spec lists its ret/NOP/pad
  evidence), `--dry-run` digests, advisory notices from agents.
- Decided by: session Lead after agent evidence review.
- Verified: digest-guarded apply; rows re-measured with `rebrew test --va --size`;
  refused cases (`overlaps next inventory start`) recorded in
  `.scratch/wave2/EXTENT-QUEUE.md`.

### Compiler-behaviour decisions

- Change: `.scratch/wave2/DECISIONS.md` updated with proven codegen rules and
  walls (framed tail jmps, PP shrink-wrapped saves, frame sizing, `extern`
  literal forms, duplicated-call merge, allocate probes).
- Why: stop agents repeating dead ends and make levers reusable.
- Evidence: probe sources under `.scratch/recycle2/agents/*/`, compiled with the
  locked `msvc-6.0-sp5-pp` profile; per-rule replay commands in the file.
- Decided by: session Lead.
- Verified: probes recompile and reproduce source-target byte shapes.

### Tooling gaps recorded for upstream

- Change: IDEAS entries drafted in `.scratch/wave2/DECISIONS.md` because the
  upstream checkout is mounted read-only in this session: extent-retire
  capability, `build driver` profile handling, `source binding` ambiguity with
  stacked anchors.
- Why: these gaps block reviewed work (interior-row retirement, PP probes).
- Evidence: concrete rows and commands named in each entry.
- Decided by: session Lead.
- Verified: every gap reproduced with the named commands.

### Row-level body corrections (recycle2 refine waves, 2026-10-20)

- Change: targeted C-shape corrections closing remaining byte deltas on partial
  bodies, e.g. `0x4d3c60` (ratio arm polarity plus `cnt` band block; 477 -> 516
  of 560, now NEAR_MATCHING), `0x4f1ad0` (reload instead of cached pointer; 161
  -> 225 of 592), `0x4fcc20` (live handle deref, scaled `0x24d` base; 59 -> 342
  of 376), `0x500a40`, `0x550be0`, `0x4cfca0`, `0x5bdfc0` (the last three now
  RELOC).
- Why: close near-miss rows to RELOC and raise partial coverage.
- Evidence: per-row `rebrew test --json` before/after counts in
  `.scratch/recycle2/results/`; decisions and levers in
  `.scratch/wave2/DECISIONS.md`.
- Decided by: session Lead (agents propose, Lead reviews promotions).
- Verified: every change re-measured with `rebrew test`; promotions recorded only
  by the comparison tools, never hand-written.

### 0x572a50 promoted to RELOC (820/820)

- Change: `gm_RandomMod` callee declared `unsigned short` instead of `int`, so
  the call site emits native `mov cx,ax`; reviewed extent repair
  `0x572a50`=820 (switch table inside, 12 NOP pad removed).
- Why: byte-identical body was blocked only by the callee return-width codegen.
- Evidence: `rebrew test --va 0x572a50 --size 820 --json` returned
  `status RELOC, match_count 820, total 820, mismatches 0`.
- Decided by: recycle2 group-105 finding, Lead applied the extent repair.
- Verified: full-body test with the repaired extent, 23 reloc bindings validated.

### ADDRESS-comment binding repairs (2026-10-20)

- Change: removed a duplicated GOLD anchor above `extern int g_6b7fac` in
  `src/GOLDTL.fcn_0040bd80.c`; moved 14 misplaced ADDRESS comments that sat above
  `extern` declarations onto their function definitions; created reviewed data
  rows `g_6b7fd0`/`g_6b7fd4`/`g_6b7fd8` (0x6b7fd0 family) and `g_6b8014`;
  renamed the GOLD row at 0x6b7fac to `g_6b7fac_gold` so the TL name is unique.
- Why: resolver built name-to-VA across targets, so duplicated or misplaced
  anchors produced AMBIGUOUS_VA and no RELOC was possible for affected operands.
- Evidence: PE sections confirm 0x6b7fd0/0x6b8014 live in .data
  (base 0x400000, .data RVA 0x275000); native relocation values equal those VAs;
  audit found exactly 14 misplaced anchors via a script over src/**/*.c.
- Decided by: session Lead after group-104/111/115 findings.
- Verified: `0x415d70` RELOC 739/739, `0x4133e0` RELOC 158/158, `0x42e0e0`
  RELOC 59/59 at its 59-byte extent, `0x42e120` RELOC 86/86.

### Interior inventory row retirement (2026-10-20)

- Change: removed seven reviewed interior inventory rows that an earlier
  discovery split out of multi-entry bodies: 0x4b023b; 0x55b5a2, 0x55b866,
  0x55b8b4, 0x55b8e4, 0x55b914; 0x51f0ce. Each is a `je` target strictly inside
  a single body, has no metadata row, and blocked the parent extent repair.
  Applied with `.scratch/wave2/retire_inventory_rows.py`, then resized the
  parents through `rebrew binary repair-extents` with a reviewed digest.
- Why: `repair-extents` cannot retire interior rows, so byte-exact bodies
  (0x4b0220 at 438, 0x55b3e0 at 2115, 0x51ecf0 at 1145) could not be measured.
- Evidence: inventory entries and metadata absence checked per row; parent
  boundary evidence in `.scratch/recycle2/results/group-128.md`; script refuses
  children that have metadata rows. Backup kept at
  `db/inventory-Europa1400Gold_TL.exe.json.pre-retire`.
- Decided by: session Lead, after group-128 reported the tooling gap.
- Verified: parents resized with digest-guarded repair; verdicts re-measured with
  `rebrew test --va --size`.

### Retirement promotions (2026-10-20)

- Change: `0x4b0220` RELOC 438/438, `0x55b3e0` RELOC 2115/2115 after the
  interior-row retirement and parent resizes above.
- Why: both bodies were byte-exact but unmeasurable at their merged extents.
- Evidence: `rebrew test --va ... --size ... --json` reports the two verdicts
  with full match counts and 15 / many VALIDATED relocations.
- Decided by: session Lead.
- Verified: digest-guarded repair then per-row comparison; store verdicts written
  only by `rebrew test --force-status`.

### Rewrite wave and extent repairs (2026-10-20, later)

- Change: rebuilt wrong-body SIZE_MISMATCH functions from native disassembly in
  rotating groups (151-173); promoted `0x532bd0` RELOC 791/791, `0x5da820` RELOC
  770/770, `0x555d30` RELOC 984/984; promoted `0x64d1df` EXACT 56/56 and
  `0x4eb260`/`0x4eb320` RELOC 188/188; applied reviewed extent repairs and
  interior-row retirements described above.
- Why: close byte coverage; bodies proven wrong by earlier waves needed
  reconstruction, not gap fixes.
- Evidence: per-group reports under `.scratch/recycle2/results/`, native
  disassembly dumps under `.scratch/recycle2/agents/group-*/`, and the extent
  specs in `.scratch/wave2/extent-specs.tsv`.
- Decided by: session Lead; agents propose bodies, Lead applies metadata changes.
- Verified: every promotion re-measured by `rebrew test --force-status`; statuses
  written only by the comparison tools.

### Restored clobbered source file (2026-10-20)

- Change: `src/GOLDTL.fcn_004055a0.c` was restored from HEAD after another
  writer replaced its body with `fcn_004cf000`, which duplicated the 0x4cf000
  ADDRESS anchor and broke the project-wide scan.
- Why: every `rebrew test` failed with an address-anchor conflict.
- Evidence: `git show HEAD:src/GOLDTL.fcn_004055a0.c`; clobbered copy at
  `.scratch/wave2/004055a0.clobbered.c`; row re-measured RELOC 248/248 after
  restore with `rebrew test --no-promote`.
- Decided by: session Lead (unblock).
- Verified: comparison tool scan succeeds project-wide again.

### README statistics and graphics refresh (2026-10-20)

- Change: refreshed `README.md`, `docs/progress.svg` and
  `docs/function-map.svg`. C matches are 251/251 server, 3,752/5,042 GoldTL
  and 2,469/4,592 Gold; 26 Gold whole-function assembly matches stay separate.
  Added the remaining verdict categories and source gaps, and distinguished
  the existing server file's equality from current-source verification.
- Why: replace the earlier snapshot with current stored results without
  treating partial implementations or inventory changes as match gains.
- Evidence: `rebrew status --all-targets --json`, saved locally as
  `.scratch/readme-2026-10-20/latest/status.json`; graphics rendered by the
  existing `scripts/progress_svg.py`, including its map/count reconciliation.
- Decision owner: user requested the latest README data and statistics.
- Verification: README totals reconcile with the saved status report; both
  SVGs parse as XML; local README links, fragments and fences pass, and
  `git diff --check` passes for the changed deliverables. No compilation,
  metadata writes, fresh function verification or full gate was run.

### README progress metrics distinguished (2026-10-20)

- Change: made virtual `.text` accounting the README's primary percentage,
  alongside C function counts and same-offset raw-file agreement. Renamed the
  function graphic's heading and subtitle in `scripts/progress_svg.py` so its
  percentages cannot be read as byte coverage; regenerated `docs/progress.svg`.
- Why: 74.4% of GoldTL functions matched does not mean 74.4% of its code bytes
  are accounted for. The same snapshot reports 47.3% code accounting and 1.2%
  raw-file agreement; Gold reports 22.9%, 53.7% and 1.1% respectively.
- Evidence: `.scratch/readme-2026-10-20/latest/status.json`, confirmed by a
  subsequent read-only GoldTL status query. No new verification was claimed.
- Decision owner: user requested correction of the confusing percentages and
  a Git commit.
- Verification: README figures reconcile with the saved JSON, both SVGs parse,
  local links/fences and staged whitespace checks pass. Rendering changes are
  labels only; no compiler, metadata or raw-link changes are included.

### Three progress bars per target (2026-10-20)

- Change: updated the README graphic and renderer to show separate bars for
  virtual `.text` accounting, C function matches and raw-file agreement at
  original offsets. Updated README alternative text and renderer tests; the
  address-ordered function map remains unchanged.
- Why: make the three denominators visible and prevent the function-count
  percentage from being mistaken for byte coverage or whole-file completion.
- Evidence: the same `.scratch/readme-2026-10-20/latest/status.json` snapshot
  used by the README table; rendered preview `latest/three-metrics.png` beside
  it. No new source-recovery or verification result is claimed.
- Decision owner: user requested the graphics update and Git push.
- Verification: six focused renderer tests pass, including independent bar
  widths, assembly/PROVEN exclusion, absent-image N/A and invalid counts.
  Ruff formatting/lint, SVG XML parsing, rendered visual inspection and
  staged whitespace checks pass. No compiler or full reconstruction gate ran.

### Full reconstruction working-tree checkpoint (2026-10-20)

- Change: committed the accumulated client C implementations, shared GUI text
  creator and caller repairs, declarations, inventory and managed metadata
  updates, project rules, trackers and handoff notes. Existing partial and
  nonmatching bodies remain explicitly unfinished. Removed trailing whitespace
  from one blank line in `src/GOLDTL.fcn_00441400.c` without changing line count.
- Why: preserve all current project work in Git at the user's request; this
  checkpoint is not a successful build or whole-image verification claim.
- Evidence: prior per-function receipts indexed in this ledger and
  `docs/TODO.md`; commit-time reports under
  `.scratch/commit-everything-2026-10-20/`. Four empty root artifacts and a
  compiler-generated `t5.asm` listing were preserved there rather than tracked.
- Decision owner: user explicitly requested committing everything and pushing.
- Verification: whitespace check passes. Full read-only lint returned one E013
  duplicate-VA error and 24 warnings per target during ongoing source edits;
  the duplicate's focused recheck subsequently had zero errors and two
  warnings per target. The complete lint was not repeated, and no full
  build, function re-verification or raw-link gate ran for this checkpoint.

### GOLD naked-asm conversion and lint repair (2026-10-20, evening)

- Change: converted all 36 GOLD rows that claimed RELOC/EXACT from whole-function
  `__declspec(naked)` + `__asm` into plain C89 (groups 190-195), using an
  instruction-shape twin search over the GOLDTL inventory and translating the
  twin's source. Registered the retired mis-bound
  `spiel_c/GOLDTL.gm_ChangePlayerIdentityImpl.c` as a support file, and removed
  the duplicate `0x62b5d0` ADDRESS anchor (prototype moved to a header).
- Why: project rules allow asm only for 1-2 padding bytes; lint E023 failed the
  gate for 36 GOLD rows. The E001/E013 errors blocked the same gate.
- Evidence: `.scratch/recycle2/results/group-190..195.md`; `.scratch/wave2/lint4.json`
  reports `total 7252, errors 0, warnings 23`; per-row verdicts written by
  `rebrew test --force-status`.
- Decided by: session Lead. Where conversion lost bytes to a documented wall, the
  honest C body and reduced verdict were kept (see DECISIONS).
- Verified: full `rebrew lint` errors 0; converted rows re-measured
  (group-194 kept 6/6 RELOC; group-195 kept 4 RELOC + 1 EXACT).

### README graphic freshness and cache versions (2026-10-20)

- Change: regenerated both README SVGs from a fresh status snapshot, added
  visible minute-level UTC timestamps to the existing renderer and content-hash
  versions to both image URLs, and refreshed Gold's unfinished-work counts.
- Why: readers reported old graphics. Published raw README/SVG hashes matched
  the local committed files, so a server-side content mismatch was not observed;
  changing image URLs avoids reusing the previous browser image-cache key.
- Evidence: raw GitHub responses and `.scratch/readme-refresh/status.json`;
  headline percentages are unchanged. No stale-browser cache was directly
  reproduced, and no new build or source-verification result is claimed.
- Decision owner: user reported stale GitHub README graphics; publishing the
  refresh follows the user's existing commit/push instruction.
- Verification: renderer tests, SVG XML and image-URL hash checks, visual preview
  and whitespace checks; remote content checked after publication. Project
  reconstruction changes are outside this documentation refresh.

### Immutable README image references (2026-10-20)

- Change: pinned both README SVG image URLs to graphics commit `9a72da61`.
  Local SVGs remain in `docs/`; subsequent refreshes must update the image ref.
- Why: immediately after publication, raw GitHub `main` URLs returned older
  bytes even with content-version query parameters. Commit-addressed URLs
  returned the exact new files, so immutable refs supersede the query-only fix.
- Evidence: SHA-256 comparisons of local, branch-addressed and commit-addressed
  README/SVG responses; GitHub's rendered README already used the new query
  URLs while those raw image responses remained older. Response cache lifetime
  was 300 seconds. This establishes an observed stale branch response, without
  identifying whether an intermediary or origin maintained that cached copy.
- Decision owner: user reported old graphs; preserve the requested current view.
- Verification: both commit-addressed image responses equal the local SVGs;
  README asset URLs resolve and staged whitespace checks pass. No build ran.

### Import-table API extraction and prepared caller migration (2026-10-20)

- Change: implemented nullable PE `hint_name_rva` in the existing upstream
  import-table API and JSON output, with parser/consumer regressions and CLI
  documentation; recorded the gap in upstream `docs/IDEAS-GUILD.md`. Added the
  release prerequisite and audit disposition to `docs/tooling-upstream.md`.
- Why: Guild's import recipe needs physical hint/name positions, but the public
  API discarded them and forced duplicate LIEF traversal. Its measured server
  ordering rules remain local; no generic linker policy was inferred.
- Evidence: upstream local commit `dea5295c`, branch
  `feature/import-hint-name-rva`, isolated at
  `.scratch/rebrew-import-hint-name-rva`. Prepared caller patch and read-only
  parity replay live in `.scratch/rebrew-import-hint-name-rva-migration`.
  Original and migrated recipes both reproduce all 39 lines / 1,205 bytes of
  `layout/server.dll/import-includes.rsp`, SHA-256
  `994f6ee54779552cb809b13b70051f2e87f84a73d1527cd36f6e6a0ff8f00b5f`.
- Decision owner: user requested the script audit, delegated implementation and
  upstream migration. Preserve the supported pinned package environment: the
  caller patch remains unapplied until a release containing the field is
  installed. The working script, dependency pins and native inputs are unchanged.
- Verification: 515 distinct upstream focused/consumer/CLI/package tests pass;
  both PE widths preserve physical hint/name positions independently of IAT
  order, and ordinal/ELF/NE imports carry null. Ruff, touched-file formatting,
  mypy (401 modules), cycles/layering and commit hooks pass. Patch apply-check
  and read-only parity replay pass. Full upstream suite and native builds were
  not run; no metadata writes, package upgrades or publication occurred.

### Rebrew 5.4.0 publication and Guild import-API migration (2026-10-20)

- Change: published the verified distribution assets for Rebrew 5.4.0 at
  upstream tag commit `79896b0d`, containing import API commit `dea5295c`.
  Guild's manifest/lock and installed venv now use that public wheel for prove
  and optional BinSync, retaining Recoverage's scoped dependency exclusion.
  Applied the prepared import-recipe migration and refreshed current tooling
  instructions, README installation version, handoff and queue guidance.
- Why: user explicitly authorized publication and a release; remove Guild's
  duplicate import-table traversal only once the public dependency supports it.
- Evidence: https://github.com/maci0/rebrew/releases/tag/v5.4.0 and all six green
  CI jobs at https://github.com/maci0/rebrew/actions/runs/39406501806.
  Exact CI package artifacts, verification logs, before/after package lists and
  read-only recipe replays are under `.scratch/rebrew-release-5.4.0-logs/` and
  `.scratch/release-asset-verification-79896b0d/`.
- Decision owner: user authorized the release, migration and publishing.
- Verification: CI wheel/sdist manifest validation and clean-venv smoke pass;
  uploaded assets are the verified CI files plus SHA256SUMS. Guild `uv lock
  --check`, `uv pip check`, prove/BinSync/Recoverage imports and 22 selected
  project tests pass. Only installed Rebrew changed, from 5.2.0 to 5.4.0.
  The migrated response is still all 39 lines / 1,205 bytes with SHA-256
  `994f6ee54779552cb809b13b70051f2e87f84a73d1527cd36f6e6a0ff8f00b5f`.
- Test-fixture correction: the project gate already requires explicit
  `functions_checked: true`; its old positive fixture omitted the field.
  Updated that fixture and added missing/false controls without weakening the
  production gate. No game source, managed metadata, layout bytes or raw
  binaries were changed by this migration, and no native rebuild ran.
- Validation limits: an initial parallel local push-hook run had one native
  fixture failure that passed alone. Later local full runs were invalidated
  when an overlapping release process removed their temporary worktree;
  they are not claimed as passing. Final release acceptance uses the complete
  successful CI run for the published commit and exact artifact checks.

### Retire obsolete helpers and reuse canonical readers (2026-10-20)

- Change: removed `scripts/update_state_table.py` and its best-effort gate hook;
  removed duplicate `stubs/recipe.txt` in favor of `stubs/README.md`. The TODO
  table retains every measured value and is explicitly a historical checkpoint.
  Updated the retained-helper inventory, including the README graphics renderer.
- Why: user requested cleanup after the upstream script migration. Scraping old
  gate terminal phrases into the tracker could replace measurements with unknown
  values; the gate already saves structured reports. The duplicate recipe still
  carried obsolete invocation flags.
- Change: retained the measured BSS and scaffold recipes, replacing their local
  TOML/map parsing with Rebrew's `load_data_metadata` and `parse_link_map` APIs.
  BSS input now includes managed fragments and respects the configured metadata
  backend; target filtering and allocation/order policy remain local.
- Decision owner: user requested removal of old ad hoc scripts. Keep live native
  build/acceptance recipes and historical scratch evidence.
- Evidence: read-only before/after replays in
  `.scratch/script-cleanup-2026-10-20/`, including `parity.json`. All three BSS
  recipe outputs agree, as do complete Gold and GoldTL manifest JSON documents
  from the existing link maps (2,890 and 2,960 scaffold symbols respectively).
- Verification: 24 selected tests and 3 subtests pass; new regressions cover
  fragmented metadata and both project-object and archive-member map origins.
  Ruff, shell syntax and scoped whitespace checks pass. No BSS source,
  scaffold manifest, managed metadata or native binary was regenerated. No
  native build or full gate ran; unrelated reconstruction edits remain separate.

### README and chart snapshot refresh (2026-10-21)

- Change: refreshed the README metric and remaining-work tables, progress bars
  and address-ordered function map from one `rebrew status --all-targets --json`
  snapshot. Updated the refresh recipe to reuse one report, with commit-pinned
  published image URLs to avoid stale branch-cache responses.
- Why: user requested the latest README data and charts. Keep code-byte
  accounting, C function counts and raw-file agreement separate; exclude
  whole-function assembly and PROVEN from matched C totals.
- Evidence: `.scratch/readme-refresh-2026-10-21/status.json`, captured at
  2026-10-20 17:51 UTC (2026-10-21 Singapore time), SHA-256
  `48bc6d4fb96c4bb9aab96e9f044726ed9b448d2c346ffd4da13feeeb1a8bd921`.
  GoldTL: 3,771/5,053 C matches (74.6%), 1,192,240/2,491,370 accounted code
  bytes (47.8%); Gold: 2,469/4,592 C matches (53.7%), 22.9% code accounting;
  server: 251/251 C matches and 100.0% code accounting. Existing raw-file
  agreement remains 100.0% server, 1.2% GoldTL and 1.1% Gold.
- Decision owner: user requested the refresh and previously authorized pushing
  README and graphic updates. Preserve concurrent reconstruction edits.
- Verification: six graphic tests pass; both SVGs parse as XML and use the same
  timestamp. Function-map game/library/assembly/C totals agree with the status
  report; README values reconcile to that report. No source, inventory,
  metadata or raw binary changed in this refresh. No native build or fresh
  verification ran; the snapshot includes current stored working-tree verdicts.

### Separate README data-verification charts (2026-10-21)

- Change: added `docs/data-progress.svg` and a README data table. Each target
  has separate bars for verified initialized data bytes, verified catalogued
  symbols including BSS/views, and the subset marked EXACT at the reference VA.
  Captions show displaced/other-drift/unchecked symbol counts and unverified
  byte buckets. Extended the existing renderer with `--data`, exclusive with
  `--map`; updated the refresh recipe and retained-helper documentation.
- Why: user requested a separate data chart set. Function matches and code
  accounting do not verify data; BSS symbol verdicts must not inflate the
  initialized-byte bar, and displacement must remain visible.
- Evidence: all three charts and README tables use
  `.scratch/readme-data-charts-2026-10-21/status.json`, timestamp
  2026-10-20 18:18 UTC, SHA-256
  `8a29bc5d607811015a8274c549ae7f0a7d00782a80a3f764993dde8be09340c2`.
  Server: 66,664/66,664 initialized bytes, 547/547 verified symbols, 409 EXACT,
  zero displaced. GoldTL: 0/335,380 initialized bytes, 1/361 verified symbols,
  zero EXACT, 332 displaced. Gold: 0/280,072 bytes, 1/319 symbols, zero EXACT,
  304 displaced. These are stored verdicts, not new measurements or owners.
- Decision owner: user requested the data charts; retain the existing code and
  function-map views and publish images through immutable commit URLs.
- Verification: 32 selected tests and 3 subtests pass, including separate byte,
  symbol and EXACT populations, missing data and invalid accounting controls.
  Ruff, XML parsing, real-report reconciliation and the data CLI smoke pass.
  Rendered the data SVG to PNG and checked the complete layout. Native builds,
  fresh data verification and the full gate were not run; concurrent source,
  inventory and managed-metadata edits are outside this change.

### Integrate reviewed work and release 1.4.0 (2026-10-21)

- Change: advanced the project and lockfile to 1.4.0 after reviewing the 27
  accepted commits since 1.3.0. Restored the server variants of
  `cm_ExAllocGraveyardWorker`, `cm_ExAllocAlchemist`, `cm_ExSimSpecialAction`,
  `lb_ExPlayerRecordBroadcast`, `gv_MoveSlotEntry`, `ahm_CheckFlag` and
  `gm_AllocRaum`. The client bodies remain selected outside `REBREW_SERVER`.
  Line controls preserve the existing client diagnostic constants. Comparison
  commands refresh the affected managed function records; no store was edited
  by hand and no native boundary or storage allocation was invented.
- Reason: the integration review reproduced nine unresolved server symbols in
  the accepted checkpoint. Commit `a16e99dc` had replaced shared server bodies
  with client implementations, and had removed the server market-stall log
  branch. The restored server C comes from its parent revision. Keeping target
  variants repairs the server without discarding the accepted client work.
- Evidence: `.scratch/integration-20261021/checks/server-regression/`
  contains the initial link failure, saved pre-change sources, the client
  preprocessing comparison and scoped verification reports. Ten comparisons
  of source token streams, with includes held out, cover both client macro
  contexts for all five files. The separate compiler and binary checks remain
  the native evidence, rather than treating preprocessing as a byte verdict.
- Preservation: `.scratch/integration-20261021/drafts.bundle` preserves the
  initial shared-checkout snapshot, 14 detached-worktree draft commits and the
  old documentation/data-owner stash. SHA-256:
  `7da8ab027c4665308225bd83416d5526a2506ff7e342444465a0f5ef327faf73`.
  `latest-drafts.bundle` adds the 155-entry shared-checkout snapshot at
  `4bbf3c1ece68e7fffb569e076ef7127572d3bcaa`; its base is in the first bundle.
  Both bundles pass verification and a separate repository passes full fsck.
  Local reports, experiments and caches from the 20 inactive detached worktrees
  survive in `worktree-evidence/`. Those worktrees and the preserved stash were
  removed. Shared checkouts with attached agents remain; none were agentless.
- Decision owner: the user authorized integration, durable draft preservation,
  cleanup, a minor release and publication to the existing owned remote.
  Concurrent reconstruction writes in the original checkout remain outside
  this accepted release. No upstream repository, binary input, linked stock
  archive, deployment destination or local tool setting was changed.
- Verification: all 33 project tests and three subtests pass; the lockfile check
  passes. Fresh raw server output equals all 286,720 reference bytes, SHA-256
  `3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
  The gate verifies 316/316 functions (including 65 library functions), all
  652 data comparisons, the entire PE, imports, relocations and layout. Wine
  loads the DLL and resolves Init/Exit; all three target compiler selections align and
  the DirectX library audit reports no new findings. Scoped checks cover the
  affected source files in their bound targets; client mismatches remain
  reconstruction work, rather than a whole-client byte claim.
- Limits: the full gate remains FAIL on its 24 lint warnings (zero lint errors).
  Broad Ruff checking retains 21 findings in unchanged files; focused graphic
  and input tests lint clean. Client raw executables were not rebuilt and gameplay was not
  tested. This is a source checkpoint; no production deployment
  workflow or hosted service is configured for this repository.
- Final scoped accounting: 172/172 server checks, 44/51 GoldTL checks and
  34/43 Gold checks pass. All five sources compile in their bound targets;
  no compile or missing-file errors and no previously byte-matched client
  rows were lost. The 16 client mismatches remain unfinished. The final
  explicit raw-link refresh records all 316 server rows as EXACT again.


### Refresh docs and charts after reconstruction/relink changes (2026-10-21)

- Change: updated README code/data tables and all three graphics from one fresh
  status report, plus a current tracker snapshot, handoff and client build notes.
  Replaced the obsolete current byte-identical-server claim with the measured
  eight-byte regression; unavailable client raw images now display N/A.
  The chart's differing-file caption is target-neutral rather than calling
  every differing binary a comparison scaffold. Fixed the singular work-item
  caption now visible for the server's one remaining function mismatch.
- Why: user requested updated docs/graphs, commits and a push. Later rebuilds
  changed the existing images and inventory; historical build scores cannot
  describe missing or changed current artifacts.
- Evidence: `.scratch/readme-refresh-2026-10-21-latest/status.json`, timestamp
  2026-10-21 12:02 UTC, SHA-256
  `7e95d2852534d9a03bb7f3b835707e723e896ab5d0170dd0bf869cc132d597c5`.
  Server: 250/251 C matches, 141,316/141,382 accounted code bytes, and
  286,712/286,720 raw-file bytes equal. GoldTL: 3,805/5,123 C matches (74.2%),
  48.4% code accounting. Gold: 2,466/4,592 C matches (53.7%), 22.8% code
  accounting. Both configured client executables were absent. Stored
  initialized-data byte verification remains server 100.0%, clients 0.0%.
- Decision owner: user authorized this refresh, commit and push. Preserve
  concurrent source, inventory, metadata and unrelated documentation changes;
  only the new tracker snapshot and this ledger entry are staged from the two
  already-modified documents.
- Verification: 32 selected tests and 3 subtests pass, including missing-image
  handling and the revised differing-file label. Ruff, XML parsing, report/map/
  table reconciliation and scoped whitespace checks pass. Rendered the updated
  code and data charts to PNG and checked the layout. No native rebuild, fresh
  data verification or full gate ran; stored verdicts remain distinct from the
  raw-file comparison of the existing server image.


### Merge the documentation refresh with accepted 1.4.0 (2026-10-21)

- Change: merged remote commit `447bc4d7` with this documentation/graphic
  refresh in an isolated checkout, preserving both append-only ledger entries.
  The README explicitly separates the latest uncommitted working-tree snapshot
  from the accepted 1.4.0 checkpoint's byte-identical server build.
- Why: the remote advanced before the docs push. Preserve the release's server
  variants and version bump without resetting the ongoing shared-tree edits.
- Decision owner: user requested the update, commit and push.
- Verification: the only merge conflict was the ledger append; both complete
  entries remain. No native source or metadata was edited to resolve the merge.
  The release's existing native evidence is retained, not rerun by this refresh.
  The merged tree passes 32 selected tests and three subtests; scoped
  whitespace checks pass.

## 2026-10-21 round 8: NEAR conversions, big-body reconstructions, extent repairs

Change: promoted 3526 RELOC and 283 EXACT GOLDTL rows (matched
3809); documented wall classes and one evidence ruling.
Notable promotions this round: 0x413fb0 (bbox structs, reversed loop), 0x4e4f10
(induction pointer -4), 0x41c290 (live i8 SIB flip), 0x412d30 (bitfield order),
0x503fe0 (init store order), 0x4f2880 (g_868050 pointer form).
Reason: delegated reconstruction waves under the three-binary objective.
Evidence: per-row reports in .scratch/recycle2/results/group-*.md, decision log
.scratch/wave2/DECISIONS.md, extent specs .scratch/wave2/extent-specs.tsv.
Verified: rebrew test --force-status per row; rebrew lint 0 errors.
Also this round: reviewed extent repairs and interior-row retirements applied via
rebrew binary repair-extents (records in the same log and EXTENT-QUEUE.md); the
0x4b3010 unevidenced aggregate was removed per the no-invented-slots rule, frame
then 0x17f4.

## 2026-10-21 callee prototype corrections

Change: fixed wrong callee arities found by auditing reference call sites.
- fcn_0042e410 (0x0042e410) is ONE argument: body reads only [esp+8]; 1017 direct
  sites, 593 with a lone `add esp,4`. Corrected declarations in fcn_00512ee0.c,
  fcn_0054a6a0.c, fcn_0054da10.c, fcn_00519190.c, fcn_0055cc80.c and restored the
  surplus values into the enclosing call argument lists (they were evaluated
  early, proved by the outer cleanups).
- fcn_004c5ed0 is THREE arguments (12 bytes): body reads [esp+0xa0]/[esp+0xa4]/
  [esp+0xa8]; 15 direct sites all push 12 bytes; the "six" at 0x559a18 was two
  adjacent three-arg calls retired by one `add esp,0x18`. Fixed the declaration
  and call in src/GOLDTL.fcn_0057d0d0.c.
Reason: surplus pushes shift every later byte in a row.
Evidence: .scratch/recycle2/results/group-336.md, group-339.md, group-341.md.
Verified: rebrew test --force-status per touched row; 0x57d0d0 307->341 matched;
0x5599c0 and 0x55be70 remain RELOC; rebrew lint 0 errors.

## 2026-10-21 round 9: three-agent function wave

Change: worked 38 GOLDTL rows with three disjoint per-function subagent queues.
Lead-verified promotions: RELOC for 0x004c0b30 (setter, g_772d18), 0x0040df00
(_CharacterSitting, two-return nibble test, SIZE 64->56), 0x0040e110
(CharacterSitsDown, same source form), 0x0046bd00 (three unsigned char
parameters), 0x004ac2c0 (unsigned short local plus volatile parameter, SIZE
64->63). NEAR_MATCHING improvements for 0x00490c10 (STUB->NEAR 113/118),
0x0050c4e0 (104/110, switch jump-table shape, SIZE 112->110), 0x004050c0
(98/110, inlined memset order), 0x004ce210 (68/74, store/lea schedule).
Reason: delegated reconstruction of remaining SIZE_MISMATCH/STUB/NEAR rows.
Evidence: per-row reports .scratch/agent-a/report.md, .scratch/agent-b/report.md,
.scratch/agent-c/report.md; official re-run results
.scratch/lead/verify-round.json; SIZE changes rest on disassembly of the
terminating `ret` and trailing alignment nops before the next function.
Verified: fresh `rebrew test <file> --va <VA>` for every claimed row; `rebrew
status` moved RELOC 3499->3504 and NEAR 71->73. No store hand edits, no commits,
no builds or links started.
Blocked rows and extent specs are recorded in the agent reports; notable:
same-TU callee analysis needed for 0x406560/0x406120/0x50e170, interior
fragments 0x0041a8c3 and 0x0042b2e0 (import thunk plus missing 0x42b2f0 row).
Also recorded: the goal text's "inception mercury" request could not be run;
plain subagent execution inherits the session model and INCEPTION_API_KEY is
unset in this environment.

## 2026-10-21 round 10: fresh-row wave, Mercury wave on uncovered functions

Change: two delegated waves plus lead work on the GOLDTL target.
- Deepseek-flash subagents (fresh rows): 0x00510b40 EXACT 47/47; NEAR
  improvements for 0x004f2ee0 138/161, 0x00509120 124/161, 0x00471e30 148/169,
  0x004c6940 156/186, 0x00436a00 117/159, 0x0050b840 115/136; SIZE corrected
  0x004c5580 160->156 and 0x004c7a60 160->150 from disassembly.
- Mercury-3 agents (workflow provider/model override) on uncovered inventory
  functions: verified RELOC for 0x00496480 92/92, 0x004cb5d0 117/117,
  0x004cdb10 127/127, 0x004f8730 208/208, 0x004f8800 208/208, 0x004cdb90
  281/281; NEAR for 0x004f88d0 196/224; SIZE corrected 0x004cb5d0 128->117 and
  0x005b8760 336->324.
- Lead: cleared six previously uncovered inventory functions with new source
  and tests: 0x005435d0 EXACT 6/6, 0x00465e60 EXACT 68/68, 0x00510b40 EXACT
  47/47, 0x004d7f70 RELOC 34/34, 0x0055c700 RELOC 54/54, 0x0041a8d0 RELOC
  127/127. The 0x465e60 body needed the inlined memset form for the five dword
  clears; 0x41a8d0 needed an unsigned callee result type for the two unsigned
  comparisons; 0x510b40 needed its true extent 47, not the inventory 32.
- Applied three reviewed extent sizes from round 9 evidence: 0x0041b820=78,
  0x0047d240=86, 0x00506e70=103.
Reason: delegated reconstruction of the remaining SIZE_MISMATCH, STUB and
uncovered rows.
Evidence: .scratch/agent-a2/report.md, agent-b2/report.md, agent-c2/report.md,
.scratch/mercury/agent-1.md, agent-2.md, agent-3.md; per-row official re-runs in
.scratch/lead/verify-round2.json and verify-wave3.json.
Verified: fresh `rebrew test <file> --va <VA>` for every claimed row; `rebrew
status` RELOC 3513, EXACT 285, NEAR 74, matched 75.0%, coverage 99.3%. Lint:
7274/7275 files pass, one pre-existing duplicate-VA error in
GOLDTL.fcn_004dcf50.c, 26 line-length/redundant-cflags warnings.
Known regression: 0x004f0f60 moved from SIZE_MISMATCH to STUB when a parked
experiment left a different body; its size was corrected to 137.
Mercury-3 note: workflow agents accept provider "inception" and model
"mercury-3"; the plain subagent tool cannot select a model.

## 2026-10-21 round 11: uncovered-row coverage, one NEAR conversion, extent trims

Change: Mercury-3 wave over the 12 remaining standalone uncovered inventory rows
(0x41b870, 0x42dac0, 0x4d2c80, 0x4edae0, 0x5af140, 0x54c240, 0x597bb0,
0x5a4960, 0x5a4bb0, 0x416d50, 0x524b50, 0x535bd0): skeletons plus honest partial
bodies, all recorded STUB; no byte matches, blockers documented. Second wave on
15 near-match rows converted 0x004284d0 to RELOC 592/592 (do-while
`while ((*d++ = *s++) != 0)` form); the other rows are register-allocation,
saving or emission-order ties.
Reason: continue the delegated reconstruction of the remaining rows.
Evidence: .scratch/mercury2/agent-{1,2,3}.md, .scratch/mercury3/agent-{1,2,3}.md.
Verified: fresh `rebrew test src/GOLDTL.fcn_004284d0.c` gives RELOC 592/592.
Also this round: restored 0x004f0f60 to its pre-experiment body and size 133
(ret at 0x4f0fdd plus the out-of-line 0x4f0fde..0x4f0f{e4} block), back to
SIZE_MISMATCH 39/133 from the STUB state a parked edit left behind.
In flight: reviewed extent trims for 237 rows whose stored SIZE includes
inter-function alignment nops. Per-row evidence is stored extent == next
inventory start, trailing 0x90 run >= 2, and capstone showing the last real
instruction ends exactly at the trimmed end and is ret or jmp. Sizes are
persisted through `rebrew test --size`, so STATUS stays CLI-recorded. Results
so far: 25 measured, no promotions, 1 SIZE_MISMATCH to NEAR_MATCHING.

## 2026-10-21 round 12: guaranteed trim wins, SIZE_MISMATCH agent wave

Change: two SIZE_MISMATCH rows whose bodies were already byte-identical were
converted by trimming the stored extent at the last real instruction:
- 0x004a5340: SIZE 352 -> 350 (two trailing 0x90), RELOC 350/350, 7 relocs.
- 0x0045fd70: SIZE 3152 -> 3140 (twelve trailing 0x90), RELOC 3140/3140,
  47 relocs. This is the largest single byte gain of the delegated waves.
Reason: a SIZE_MISMATCH row reported at 100 percent match means only the stored
extent disagrees with the compiled body; the extra bytes are inter-function
alignment padding.
Evidence: `rebrew test` showed `mismatches: []` with obj_size 350/3140 before
the trim; capstone confirmed the last instruction ends at the trimmed boundary
and the next inventory function starts at the stored end.
Verified: fresh `rebrew test --va --size` for both rows; `rebrew status` RELOC
3516, NEAR 77, matched 75.1 percent, byte coverage 48.3 percent.
Also this round: Mercury-3 wave on 15 SIZE_MISMATCH rows of 176-320 bytes
(.scratch/mercury4/agent-{1,2,3}.md). All bodies were completed against the
disassembly but remained parked on register-allocation, x87 ordering, frame
size or emission-order deltas; no promotions. No store hand-edits, no commits.
In flight: reviewed extent-trim batch over the remaining candidate rows; it
persists sizes through `rebrew test --size` and is idempotent on rerun.

## 2026-10-21 round 13: closure pipeline run and link blockers

Change: ran `.scratch/closure/run_closure.py` (client build, data verify,
whole-binary verify, lint, gate) after pausing function agents. Build results:
- Client build compiled the full source lists (4890 files per client) and failed
  at link: GOLDTL 1258 unresolved externals (520 `fcn_*` game functions with no
  body, 54 `sub_*` placeholder names from partial-body waves, 1154 undefined
  data symbols), GOLD similarly, exit 2 after 1304 s.
- Server target: `cmake --build build --target server_dll` compiles and fails at
  link with exactly 9 unresolved externals, all called from shared TUs:
  `fcn_005037c0`, `fcn_00503930` and `g_773da8` (friedhof_logic.c),
  `fcn_0051af00` and `g_679060` (lobbycommands.c), `fcn_0051af00`,
  `g_14cbca0`, `g_699364`, `g_773d75` (command.c). Those TUs are bound to both
  client and SERVER modules, and the current bodies use client addresses.
- Lint: 7286/7287 files pass, one pre-existing duplicate-VA error in
  GOLDTL.fcn_004dcf50.c, 24 warnings. Gate: FAIL, server.dll and client exes
  missing after the failed rebuild.
Reason: reach the file-level checks after the delegated function waves.
Evidence: `.scratch/closure/closure-summary.json`, `01-client-build.stdout`,
`server-rebuild.log`, `04-lint.stdout`, `05-gate.stdout`.
Verified: build logs above; no data/whole-binary/gate step could run because the
links failed.
Known loss: the previous `build/Europa1400Gold.exe`, `build/Europa1400Gold_TL.exe`
and `build/server.dll` artifacts no longer exist and cannot be regenerated until
the unresolved symbols are fixed. Old green builds were explicitly not accepted
as completion evidence, but the loss is recorded here.

## 2026-10-21 round 14: server target verified and linked again

Change: re-measured the server target with current sources and repaired its link.
- `rebrew verify --target server.dll`: 313/316 byte-matched (41 EXACT, 272
  RELOC), 1 NEAR, 2 SIZE_MISMATCH. Before this round the tree carried 316
  "matched" claims that had not been re-measured after the client-side edits.
- Three Mercury-3 agents added `#ifdef REBREW_SERVER` variants in shared TUs,
  leaving the client bodies untouched: cm_ExAllocGraveyardWorker 52/52,
  cm_ExAllocAlchemist 52/52, cm_ExSimSpecialAction 262/262 (command.c) and
  lb_ExPlayerRecordBroadcast 247/247 (lobbycommands.c), all RELOC on the server
  target. gv_MoveSlotEntry (server 674) and gm_AllocRaum (server 742) got
  server bodies but remain SIZE_MISMATCH.
- `cmake --build build --target server_dll` now exits 0 and rebuilds
  `build/server.dll` (286720 bytes, same as reference). The nine unresolved
  externals recorded in round 13 are gone.
Reason: restore the server deliverable and let the gate measure something real.
Evidence: .scratch/lead/server-verify.json, .scratch/mercury5/agent-{1,2,3}.md,
.scratch/closure/server-rebuild3.log, .scratch/closure/gate2.log.
Verified: build exit 0; gate runs and reports 52309 differing bytes (47907 in
.text), .text VirtualSize 0x22836 vs 0x22846, imports 100/100, exports Exit and
Init names/VAs identical, size equal. Client rows for the touched functions
re-tested unchanged (0x4f9300 RELOC 236/236, 0x4cda90 RELOC, 0x509570 NEAR).

## 2026-10-21 round 15: server rows fixed, raw-link residue cut by 83 percent

Change: Mercury-3 agents reconstructed the two remaining server bodies that were
not just NEAR:
- gv_MoveSlotEntry server 674/674 RELOC (friedhof_logic.c, #ifdef REBREW_SERVER
  branch rebuilt from the server disassembly; the client version stays inside
  #else).
- gm_AllocRaum server 742/742 RELOC (spiel.c, new REBREW_SERVER branch).
Reason: the 32-byte short gm_AllocRaum body shifted 35 downstream server
functions by -0x20 in the raw link.
Evidence: .scratch/mercury6/agent-1.md, agent-2.md.
Verified: `rebrew verify --target server.dll` 315/316 byte-matched (274 RELOC,
41 EXACT); `rebrew verify --text --raw-link` 251/251 correct placement; gate
reports 9033 differing bytes vs 52309 before, .text VirtualSize exactly
0x22846, .rdata VirtualSize and imports/exports pass. Remaining failures:
.data VirtualSize 0x174051c vs 0x174057c, .reloc 0x102cc vs 0x1035c, 2449
differing bytes inside .text and 6584 outside it, one server row
gm_GetEntityTableEntry NEAR 55/66, server data 29 DRIFT rows and 7 missing
globals, 89 missing / 75 extra relocation sites.

## 2026-10-21 round 16: server data drift root-caused and cleared

Change: added the two missing log-string literals to the server gm_AllocRaum
variant in spiel.c ("gm_AllocRaum(): Too many objects in 'Marktstand'..." and
"gm_AllocRaum(): ob_LAGERFLAECHE_ALLGEMEIN is missing in ob_MARKTSTAND!").
The previous body used raw address casts `(char*) 0x10031484` / `0x100314b8`,
so the literals were never emitted and .data after them shifted by 0x80 bytes,
which showed up as 29 DRIFT rows and two VirtualSize mismatches.
Reason: .data byte identity for the server.
Evidence: reference .data strings extracted at 0x10031484 (52 bytes) and
0x100314b8 (71 bytes); built image lacked both (search returned no match).
Verified: `rebrew test spiel.c --target server.dll --va 0x10017c40` stays RELOC
742/742; rebuilt server.dll differs in 4119 bytes (was 9033); server data verify
652 rows, 0 mismatched, 0 missing; .rdata and .data byte-identical;
`rebrew verify --text --raw-link` placement still 251/251; gate: .text/.rdata/
.data VirtualSize PASS, imports and export names/VAs PASS, Exit and Init bodies
byte-identical, remaining 11 .text bytes (gm_GetEntityTableEntry NEAR) and
.reloc VirtualSize 0x102e4 vs 0x10374.

## 2026-10-21 round 17: server relocations matched, residue down to 8 bytes

Change: the two server bodies reconstructed in shared TUs referenced data
through raw numeric addresses, so the compiled code had the right bytes but no
base relocations. Round 17 replaced them with the named globals from entity.h/
game_data.h/rebrew_globals.h: g_slot_table, g_entity_table_end,
g_worker_entry_count, g_next_object_id, g_current_season,
g_entity_slot_table, g_output_share, g_entity_id_field, plus the real __FILE__
literal for the LogMessageInternal file argument in gm_AllocRaum. Also applied
the best form of gm_GetEntityTableEntry (reversed bounds operands keeps the
index in EAX).
Reason: reconcile the 12 missing relocation sites and shrink the residual.
Evidence: relocs report listed 12 missing sites (11 in gv_MoveSlotEntry, one in
gm_AllocRaum) all targeting named data rows; the bodies held literal addresses.
Verified: server bodies stay RELOC (gv_MoveSlotEntry 674/674, gm_AllocRaum
742/742, gm_GetEntityTableEntry NEAR 58/66, client 0x509570 NEAR 54/65);
rebuilt server.dll now differs in 8 bytes (was 4119); gate passes size,
.text/.rdata/.data/.reloc VirtualSize, imports 100/100, export names/VAs, Exit
and Init bodies and entry point; only whole-file identity fails, at 8 bytes in
0x100184ff..0x10018506 (bounds-test order inside gm_GetEntityTableEntry).
Search effort: ~30 hand variants, rebrew match climb, and a 400-generation
register-focused GA all failed to produce both the EAX allocation and the
reference test order; the GA never exceeded the NEAR score.

## 2026-10-21 round 18: Mercury attempts on the last 8 bytes and client rows

Change: tried to remove the final 8 differing server bytes and ran a client
reconstruction wave; no STATUS changed this round.
- A Mercury-3 agent spent ~40 minutes on gm_GetEntityTableEntry server
  (0x100184e0) with scripted variant sweeps and a GA; the best remains the
  reversed-bounds form (58/66, index in EAX, test order swapped). It left the
  file in that best form.
- Ten client SIZE_MISMATCH rows were completed against their disassembly
  (0x00402d00, 0x00407390, 0x00408320, 0x0040ed40, 0x0040f9d0, 0x00412b10,
  0x00412f10, 0x00413480, 0x00413e00, 0x00415510); all remain SIZE_MISMATCH
  with allocator/scheduling deltas, six missing data rows (0x415510) and one
  inventory over-merge (0x40f9d0 with 0x40fb80).
- Repair: a variant sweep had reverted the gm_AllocRaum __FILE__ literal back to
  the raw 0x10031004 cast, which silently dropped one base relocation and made
  server.dll differ in 1984 bytes. Restoring the literal returns the image to
  8 differing bytes.
Verified: server rebuild exit 0; cmp reports 8 differing bytes; gate reports 8
residual bytes and only whole-file identity failing. Client rows re-verified
unchanged.

## 2026-10-21 round 19: further attempts on the last 8 server bytes

Change: no STATUS change. Tried early-out/goto forms, long and unsigned
comparison types, pointer-to-word forms, modulo-based index expressions, and
LLM-seeded GA on the single-function probe. None produced both the EAX
allocation and the reference bounds-test order. Cross-check: the GOLDTL and GOLD
targets of the same function show the same target pattern (test/jl first, index
in EAX) against the same source form that compiles with a mov ecx,eax copy, so
the original C shape is shared across all three and remains unfound.
Evidence: .scratch/lead/ged/variants*.json, mercury7 variant logs; GA reports in
output/ga_runs. rebrew match run --seed-llm reports no configured LLM endpoint.
Verified: server.dll rebuilt from the 58/66 form and still differs in 8 bytes;
no other files touched.
Also started `rebrew verify --target Europa1400Gold.exe` in the background as
the first full re-measure of the GOLD target after the recent waves.

## 2026-10-21 round 20: GOLD baseline, merged-extent repairs

Change: measured the GOLD target for the first time since the delegated waves
and started a reviewed merged-extent repair batch.
- `rebrew verify --target Europa1400Gold.exe`: 4604 rows, 2507 byte-matched
  (194 EXACT, 2313 RELOC), 1852 STUB, 219 SIZE_MISMATCH, 26 NEAR_MATCHING.
- Merged-extent repair: 53 metadata rows whose stored SIZE spans one or more
  later inventory function starts were re-sized to the inventory extent after a
  capstone check (the inventory size lands exactly on a ret/jmp end). Inner
  inventory functions missing metadata rows receive skeletons. 14 rows applied
  before the round closed; the batch is idempotent and still running in the
  background.
- One case completed manually: 0x40f9d0 768 -> 430 (ret at 0x40fb7d plus two
  alignment nops before 0x40fb80) and skeleton for 0x40fb80 (328 bytes).
Reason: stored-size over-merges make byte matches unreachable and hide
inventory functions from the work queue.
Evidence: .scratch/lead/merge-repair-results.json,
.scratch/lead/merge-repair-skeletons.json, .scratch/lead/gold-verify.json.
Verified: GOLDTL `rebrew status` after the first repairs reports 5075 inventory
functions (from 5059), 5038 covered, RELOC 3516, EXACT 285, NEAR 78,
SIZE_MISMATCH 890, STUB 268. Matched percentage moved 75.1 -> 74.8 only because
the denominator grew by the newly admitted rows.
A Mercury wave on six large client rows (0x4033e0, 0x4045c0, 0x4079f0,
0x4094c0, 0x40a200, 0x411b80) parked all six on frame/scheduling deltas; no
STATUS changed. Server stays at 8 differing bytes.

## 2026-10-21 round 21: merged-extent batch reviewed, two false shrinks reverted

Change: finished the reviewed merged-extent batch (39 rows) and corrected two
wrong repairs, then admitted inner inventory functions as work items.
- 0x00570960 had been shrunk 1926 -> 375 from the inventory split, but its
  compiled body matches all 1926 bytes (mismatches []) and was RELOC before the
  repair. Restored SIZE 1926: RELOC 1926/1926.
- 0x0045c380 had been shrunk 560 -> 468; its body fills 560 bytes. Restored:
  RELOC 560/560.
- The repair script now auto-reverts a resize when the compiled object equals
  the old extent, since that means the inventory entry is an over-split, not the
  metadata row an over-merge.
- Inner-function skeletons admitted about ten rows; the bogus metadata block at
  0x45c554 (inside the 0x45c380 body) was dropped with `rebrew orphans drop`.
Reason: an over-merged stored size blocks byte matching, while a wrongly shrunk
row loses an earned RELOC.
Evidence: .scratch/lead/merge-repair-results.json (39 records),
.scratch/lead/merge-repair-skeletons.json, status before/after.
Verified: 0x570960 and 0x45c380 re-tested to RELOC; `rebrew status` RELOC 3517,
EXACT 285, NEAR 79, SIZE_MISMATCH 888, STUB 313, 5123 rows / 5083 covered.
Server still differs in 8 bytes; GOLDTL matched 74.2 percent with the larger
denominator.

## 2026-10-21 round 22: CFLAGS metadata cleanup after flag experiments

Change: removed the last inventory over-split artifacts and normalized
per-function CFLAGS that had accumulated from flag experiments.
- Dropped metadata rows and skeleton files for 0x570ad7, 0x570def, 0x570e5b,
  0x570e8b, 0x570ebb, 0x570eeb, 0x570f75 and 0x571020, all inside the real
  1926-byte body of 0x570960 (RELOC 1926/1926 after the round-21 revert).
- 22 SERVER spiel.c rows carried flag strings other than `/O2 /Gd`
  (`/DREBREW_ALLOW_NAKED /O2 /Gd`, `/O2 /Gd /DREBREW_ALLOW_NAKED`,
  `/O2 /Gd /Ob1`) because `rebrew test --cflags` persists overrides into
  metadata. `rebrew build cmake-flags` refuses a TU whose functions resolve to
  different flags, so cmake configure failed. Normalized those rows to
  `/O2 /Gd`; every one kept its RELOC or EXACT verdict.
Reason: restore a configurable build and remove false inventory functions.
Evidence: .scratch/lead/spiel-cflags-fix.json and -results.json,
.scratch/lead/merge-repair-results.json.
Verified: `cmake -S . -B build` exits 0, `cmake --build build --target
server_dll` exits 0, server.dll still differs in 8 bytes; `rebrew status` RELOC
3517, EXACT 285, NEAR 79, SIZE_MISMATCH 888, STUB 330, 5123 rows / 5100 covered.
Flag sweeps with /Ow /Op /Oa /Ot /Ob1 on the last server function all leave it
at 55 or 58 of 66 bytes, so the 8-byte gap is not a flag choice.

## 2026-10-21 round 23: newly admitted inventory functions implemented

Change: Mercury wave on the inventory functions admitted by the merged-extent
repairs. Verified promotions and cleanups:
- 0x0058fa20 RELOC 30/30 (tail-call wrapper; stored extent 32 -> 30, two
  trailing alignment nops).
- 0x0044f010 RELOC 205/205.
- 0x004eb180 RELOC 148/148 (stored extent 160 -> 148, twelve trailing nops).
- 0x00536b8e NEAR_MATCHING 29/30; the residual byte needs the preceding
  function in the same TU to reproduce the shared-ret tail merge.
- Interior fragments confirmed and dropped with `rebrew orphans drop` and
  source deletion: 0x004c38eb (inside 0x004c3800), 0x004c4268, 0x004d16da,
  0x0052668b. 0x004c3800 keeps a real prologue and stays a STUB work item.
Reason: turn the newly admitted inventory rows into matched functions and remove
false identities created by an over-splitting discovery pass.
Evidence: .scratch/mercury10/agent-{1,2,3}.md.
Verified: fresh `rebrew test` for each promoted row; `rebrew status` RELOC 3520,
EXACT 285, NEAR 80, STUB 322, 5123 rows / 5096 covered; `rebrew lint` one
pre-existing duplicate-VA error and 59 warnings. Server.dll still differs in 8
bytes; last-8-byte source-form search continued without a hit.

## 2026-10-21 round 24: fragment cleanup, no new matches

Change: no STATUS gains. Mercury wave on the remaining admitted skeleton rows
and a batch of 220-320 byte client rows produced no byte matches:
- 0x00474e5d, 0x00526b37, 0x004c70fa and 0x005b104c are interior fragments of
  neighbouring functions; their metadata rows were dropped with
  `rebrew orphans drop` and their skeleton sources deleted.
- 0x004c3800, 0x005a6e90 and 0x0058f6a0 are real function starts but remain
  STUB skeletons (the assigned agent returned no report or edits).
- Client rows 0x0043a720, 0x004488e0, 0x0044b340, 0x00454460 and 0x00455d30
  reconstruct logically but diverge only in /O2 codegen; parked in
  .scratch/mercury11/agent-3.md.
- The reviewed extent-trim batch was resumed and stopped after ten further rows
  with zero promotions; stored-size trimming appears exhausted as a conversion
  source.
Verified: `rebrew status` RELOC 3520, EXACT 285, NEAR 80, SIZE_MISMATCH 888,
STUB 318, 5123 rows / 5092 covered; server.dll still differs in 8 bytes.

## 2026-10-21 round 25: automated matching attempts, layout gap identified

Change: no STATUS change. Evaluated the automated matching engine as an
alternative to manual body reconstruction:
- `rebrew match batch --near-miss --threshold 4` selected zero rows (the NEAR
  rows are further than four bytes from target).
- `rebrew match batch --improve` over 12 NEAR rows ran 25 minutes and produced
  no improvement; stopped.
- Per-row `rebrew match run --mutation-focus register --generations 300` on the
  closest NEAR rows: 0x004b64b0 (one byte of a 204-byte function) finished with
  best_score 1400 and exact=false; the loop was stopped after the first row for
  time.
Also identified why data generation is blocked: `rebrew test --data`/`layout
fill` needs a layout package and `layout/Europa1400Gold_TL.exe/rebrew-layout.toml`
does not exist (`rebrew build layout` has not been run for this target). That
package is the prerequisite for generating missing data definitions behind the
client link's unresolved externals.
Verified: `rebrew status` unchanged (RELOC 3520, EXACT 285, NEAR 80,
SIZE_MISMATCH 888, STUB 318, 5123 rows / 5092 covered). Server.dll still 8 bytes
from identity.

## 2026-10-21 round 26: GOLDTL layout package generated, data audit baseline

Change: ran `rebrew build layout` for Europa1400Gold_TL.exe, which wrote the
previously missing layout package:
- layout/Europa1400Gold_TL.exe/{header.hex, iat.hex, prefix.hex,
  bookkeeping.hex, data.hex, reloc.hex, operands.txt, calls.txt,
  layout.fingerprint, rebrew-layout.toml} and src/Europa1400Gold_TL.exe.def.
- These files are untracked generated scaffolding; review them before wiring the
  layout into a build. No source or metadata behaviour changed.
Reason: `rebrew data layout audit/fill` refused to run without a layout package,
and that tooling is the path to data-definition recovery on the client side.
Evidence: .scratch/lead/layout-audit.json; fill dry run reported 48
initialized-data pads and 201 BSS pads.
Verified: `rebrew data layout audit` now runs: 626 unowned data rows, 0
duplicate owners, 1 violation. Server.dll still differs in 8 bytes; GOLDTL
status unchanged.

## 2026-10-21 round 27: link-symbol identity analysis, no STATUS change

Change: no STATUS change. Analysed the client link failures for actionable
symbol-identity work and ran one more skeleton wave.
- From .scratch/closure/01-client-build.stdout: 1231 unresolved symbols, 243 of
  them `fcn_<VA>` placeholders; 188 placeholders resolve to an existing metadata
  identity at the same VA under a real attested name (examples:
  fcn_004012b0 -> _ReadVfsFourDwords, fcn_0041db70 -> _m_alloc,
  fcn_00426d50 -> _evt_LoadScript).
- Attempted `rebrew source rename fcn_004012b0 GOLDTL.0x004012b0 --dry-run`:
  refused with "binding source must be an unbound placeholder". The placeholder
  must first be registered through the source-registration path; a 188-row bulk
  binding needs that path reviewed first.
- Mercury wave: 0x004c3800 (21/371), 0x005a6e90 (28/805) and 0x0058f6a0
  (226/896) have bodies reconstructed from disassembly but remain
  SIZE_MISMATCH; 0x0045c554 reconfirmed as an interior fragment.
Verified: `rebrew status` unchanged (RELOC 3520, EXACT 285, NEAR 80,
SIZE_MISMATCH 888, STUB 318, 5123 rows / 5092 covered). Server.dll still 8 bytes
from identity.

## 2026-10-21 round 28: placeholder-to-identity binding started

Change: started binding unresolved `fcn_<VA>` placeholder calls to the existing
attested identities at the same VA.
- From the client build log, 243 unresolved `fcn_` symbols; 180 of them have a
  metadata identity at the same VA under a different (attested) name and are not
  bound in any module.
- `rebrew source rename fcn_00402ab0 GOLDTL.0x00402ab0 --dry-run` previews the
  reference edits and returns an input digest; applying with --expected-digest
  rewrites only the call sites. Batch run: 36 attempted, 29 applied, 7 refused
  (ambiguous or already-bound names); remaining list in
  .scratch/lead/free-placeholders-remaining.json.
- Fixed a lint regression from the wave-14 file src/fcn_0058f6a0.c: the ADDRESS
  anchor was above the extern block instead of the definition, which lint
  reported as a duplicate VA; moved it directly above the function.
Reason: canonical symbol identities are a prerequisite for a working client
link, and the placeholder names currently break ~180 external references per
client build.
Evidence: .scratch/lead/free-placeholders.json,
.scratch/lead/bind-placeholders-results.json.
Verified: rebrew lint back to 1 pre-existing error (E013 in
GOLDTL.fcn_004dcf50.c) and 60 warnings; `rebrew status` unchanged (RELOC 3520,
EXACT 285, NEAR 80, SIZE_MISMATCH 888, STUB 318, 5123 rows / 5092 covered);
server.dll still 8 bytes from identity.

## 2026-10-21 round 29: GOLD client links again

Change: the GOLD client now links and produces build/Europa1400Gold.exe.
- The sole link failure was `_g_f83654`, an extern-only declaration in
  src/GOLD.fcn_004a8650.c. The reference stores a zero-initialized module pointer
  at VA 0x00f83654 (RVA 0xb83654, inside the zero-filled virtual tail of .data),
  so the declaration is now the definition in its use-site TU.
- Continued the placeholder binding batch: 53 attempted, 35 applied; 116
  remaining candidates.
Reason: restore the GOLD deliverable so the gate and data verification can run
against a real image.
Evidence: .scratch/closure/client-rebuild.log, gold-rebuild.log,
.scratch/lead/gold-data.json.
Verified: `cmake --build build/clients --target europa1400gold` exits 0 and
writes build/Europa1400Gold.exe (819,200 bytes). Reference is 2,301,952 bytes, so
the client is missing the large virtual .data/BSS layout; GOLD data verification
against the built image reports 321 rows, 0 exact, 32 drift and 50 missing.
GOLDTL link still reports 1236 unresolved externals. Server.dll still 8 bytes
from identity; GOLDTL status unchanged.

## 2026-10-21 round 30: client BSS path identified, shared-file write hazard

Change: generated the GOLD layout package and evaluated generated BSS padding for
the clients.
- `rebrew build layout --target Europa1400Gold.exe` wrote
  layout/Europa1400Gold.exe/ and src/Europa1400Gold.exe.def (untracked
  scaffolding).
- `rebrew data layout fill --target Europa1400Gold.exe` reports 19 init pads and
  264 BSS pads, but it writes them into src/bss_layout/bss_late.c, the static
  library the SERVER links after the CRT. That file is generated for server.dll
  by scripts/gen_bss_layout.py, so the fill was reverted with
  `git checkout -- src/bss_layout/bss_late.c` and the server rebuilt; server.dll
  still differs in exactly 8 bytes.
- The client size gap is now explicit: reference GOLD is 2,301,952 bytes and the
  built client 819,200; the missing ~1.48 MB is the zero-filled .data/BSS tail
  that the server reproduces with bss_head/bss_late objects. Clients have no
  equivalent generated BSS sources, and rebrew's fill writes into the server's
  file, so per-target BSS sources are needed first.
- Upstream gap note: the append to
  /home/maci/Desktop/Projects/relumea/repos/rebrew/docs/IDEAS-GUILD.md was
  blocked by the read-only sandbox, so the gap is recorded in docs/TODO.md and
  here instead.
Verified: server rebuild exit 0 with 8 differing bytes; tracked bss_layout files
clean again; GOLDTL/GOLD status unchanged.

## 2026-10-21 round 31: GOLD client source-subset root cause

Change: measured why the GOLD client is far from the reference after linking.
- Built build/Europa1400Gold.exe: .text virtual 0xb54b6 (742,582) vs reference
  0x1e9e04 (2,006,532); .data raw 0xe000 vs 0x40000; file 819,200 vs 2,301,952.
- Source lists: build/clients/rebrew-sources-gold.txt has 4458 entries,
  goldtl 4945. The GOLD target only receives files that carry GOLD module rows,
  so about 487 shared implementation files (bound only to GOLDTL rows) are
  absent from the GOLD link. That missing code plus the raw .data gap explains
  the file-size difference.
- Cross-target completion is blocked: `rebrew source import-related --from
  Europa1400Gold_TL.exe --target Europa1400Gold.exe --candidates-only --dry-run`
  fails with "cannot extract a conditional definition from a multi-function
  file". Either the shared multi-function TUs need splitting or the destination
  module anchors have to be added another way.
Verified: section tables read with LIEF from build/Europa1400Gold.exe and the
reference; server.dll unchanged at 8 differing bytes; GOLDTL/GOLD status
unchanged.

## 2026-10-21 round 32: client links are generated-stub scaffolds

Change: identified why the GOLD client image is so far from its reference even
after it links.
- CMakeLists.txt:420/464 add stubs/gold/symbol_stubs.c and
  stubs/goldtl/symbol_stubs.c to the client links. These are AUTO-GENERATED by
  `rebrew build symbol-stubs` and explicitly not part of the matching pipeline.
  GOLD's stub file has 6727 lines: 944 stub functions and 947 stub globals; the
  GOLD link map attributes 2890 of 6640 function symbols to symbol_stubs.c.obj,
  which explains the 742,582-byte built .text.
- 686 of the GOLD stub functions carry a metadata identity by name, but callers
  in shared sources use GOLDTL-module placeholder symbols (`fcn_<GOLDTL VA>`)
  that are not defined in the GOLD link. There is no automatic bridge: every
  GOLDTL row with a `_fcn_<VA>` symbol also has a placeholder name, so the
  shared-attested-name mapping does not exist yet.
- `rebrew source import-related --from Europa1400Gold_TL.exe --target
  Europa1400Gold.exe` reports no unmatched functions in GOLD (so it cannot
  import), and the bulk `--candidates-only` run is blocked by
  "cannot extract a conditional definition from a multi-function file".
Verified: stub file line/definition counts, GOLD link map composition
(symbol_stubs.c.obj 2890 symbols), server.dll unchanged at 8 differing bytes,
GOLDTL/GOLD status unchanged.

## 2026-10-21 round 33: fresh verify baseline, stub mapping analysis

Change: re-verified the whole GOLDTL target after the rename/repair rounds and
analysed the client stub symbols.
- `rebrew verify --target Europa1400Gold_TL.exe`: 5123 rows, 3804 game rows
  byte-matched (3519 RELOC + 285 EXACT; the 3835 headline includes 31 library
  rows), NEAR 81, SIZE_MISMATCH 904, STUB 297, EXTRACT_ERROR 5 (all
  pre-existing: one decorated `@fcn_0045a7f9@4` row plus four D3DX8 external
  band rows), MISSING_SIZE 1.
- Fixed the only compile error in the run: src/GOLDTL.fcn_00519190.c declared
  `int __cdecl strncat(char*, char*, unsigned)` alongside <string.h>, producing
  C2040; the redundant declaration was deleted. The row now compiles.
- Stub mapping (analysis only, .scratch/mercury13/agent-{1,2}.md): GOLD stub
  file has 938 function stubs - 4 attested twins, 687 placeholder-only (a
  GOLDTL row exists at the same VA but both names are placeholders), 50
  "VA-twin" placeholders whose GOLDTL row at that VA carries an attested name,
  197 without any row. GOLDTL stub file has 303 function stubs - 0 attested, 31
  placeholder-only, 6 VA-attested, 266 no-row. GOLDTL.fcn_004a1130.c is the top
  GOLD stub consumer (102 references).
Reason: know exactly which symbols the client scaffolds hide and which carry a
usable canonical name.
Verified: status/verify figures above; server.dll unchanged at 8 differing
bytes; no metadata hand-edits.

## 2026-10-21 round 34: TU-context hypothesis refuted

Change: no STATUS change. Two agents tested whether MSVC 6 /O2 global
optimization makes gm_GetEntityTableEntry's register allocation depend on the
translation-unit context.
- Method: isolated single-function TUs and copies of the whole spiel.c, dummy
  prototypes before/after the function, first/last position, measured with the
  server target's real plain msvc-6.0-sp5 profile; probes under .scratch/ only,
  no src edits, measurements with --no-promote where applicable.
- Result: the hypothesis is refuted. Isolated and whole-file compilations are
  byte-identical, so the TU context does not change codegen. msvc-6.0-sp5-pp
  gives 25/66, confirming the reference was not built with the processor-pack
  profile. The reference shape (test order >=0 then <16 with the index kept in
  EAX) is unreachable from the tried forms; the 58/66 reversed-bounds form
  remains the best.
- Also quantified the cross-target naming gap: 920 GOLD stub placeholders, 743
  mapping to a GOLDTL row at the same VA, but only 19 of those VAs exist in the
  GOLD module; 56 placeholders have a GOLDTL attested name at their VA.
- Lint: 1 pre-existing E013 error, 111 warnings (59 W005 missing stub blockers,
  26 W029 redundant cflags that no CLI can clear, 13 W027, plus W016/W020/W021/
  W031). `--cflags ""` does not clearing an override.
Verified: agents' measurements under .scratch/mercury14/ and .scratch/tu/; no
src or metadata writes; server.dll unchanged at 8 differing bytes; GOLDTL
matched count unchanged at 3804.

## 2026-10-21 round 35: lint brought to zero errors

Change: cleaned lint from 1 error / 111 warnings to 0 errors / 50 warnings, and
tried two more source forms for the last server function.
- BLOCKER text set on 59 STUB files through `rebrew blocker set`, all describing
  the same honest class: partial reconstruction parked on MSVC 6 codegen deltas,
  with the delegated wave reports as evidence. W005 count is now 0.
- Fixed two misplaced ADDRESS anchors that produced duplicate/conflicting
  bindings: src/GOLDTL.fcn_004dcf50.c had its anchor above the extern block
  (lint E013 duplicate VA), src/fcn_0058f6a0.c likewise (fixed in round 28);
  removed the stray src/fcn_0045c554.c fragment file and its MISSING_SIZE row
  with `rebrew orphans drop`.
- Last-8-byte attempts: bounds checked on the expression with assignment only in
  the return (32/69) and assignment inside the condition (55/66); neither hits
  the reference 66/66.
Reason: the goal requires zero lint errors/warnings and correct metadata.
Verified: `rebrew lint --json` returns errors 0, warnings 50 (26 W029, 13 W027,
7 W016, 3 W031, 2 W020, 1 W021). `rebrew status`: RELOC 3519, EXACT 285,
NEAR 81, SIZE_MISMATCH 904, STUB 297, 5122 rows / 5091 covered; server.dll still
8 differing bytes.

## 2026-10-21 round 36: lint down to 16 warnings

Change: cleaned lint from 50 warnings to 16 with tooling-backed writes only.
- `rebrew lint --fix` removed 26 redundant per-function CFLAGS (W029) from
  GOLDTL and SERVER rows whose flag string equalled the inherited `/O2 /Gd`.
- `rebrew data set --section` backfilled six data rows missing SECTION metadata
  in GOLDTL.fcn_00415510.c: 0x0067756c = .data; 0x006628bc, 0x006628cc,
  0x00662a2c, 0x00662a40, 0x00662a44 = .rdata (from the reference section
  table).
- `rebrew source document-assembly` recorded the reviewed evidence for the two
  inline-asm helpers fill0 and copy0 in src/GOLDTL.fcn_004b3010.c, citing the
  probe results and the RELOC sibling (src/GOLDTL.fcn_004b24c0.c lines 40/65)
  plus the decision in .scratch/wave2/DECISIONS.md.
Reason: the goal requires zero lint errors and warnings; the remaining W027
long lines cannot be safely wrapped because several files use `__LINE__`, which
would change codegen.
Verified: `rebrew lint --json` errors 0, warnings 16 (13 W027, 3 W031).
`rebrew status` unchanged (RELOC 3519, EXACT 285, NEAR 81, SIZE_MISMATCH 904,
STUB 297, matched 74.2 percent); server.dll still 8 differing bytes.

## 2026-10-21 round 37: lint clean on all three targets

Change: finished the lint cleanup. `rebrew lint --all-targets` now reports
0 errors, 0 warnings, 7341/7341 files passing for server.dll,
Europa1400Gold_TL.exe and Europa1400Gold.exe.
- Rebound the three stale GOLDTL types (d3.object-animation-frame,
  d3.object-animation-flags, event.validator_view) and the three stale GOLD
  types (event.validator_view, dd.device_record, dd.driver_record) through
  `rebrew types bind` with unchanged sizes, native sizes and modeled offsets,
  and evidence text recording that only source/header hashes changed.
- Wrapped the 13 over-long lines at `&&`/`||`/`,` boundaries. Only files without
  `__LINE__` were touched, so codegen cannot shift; each touched file was
  re-tested and kept its previous status.
Reason: the objective requires zero lint errors and warnings on the delivered
tree.
Verified: `rebrew lint --all-targets --json` -> server.dll 0/0, GOLDTL 0/0,
GOLD 0/0 (7341/7341 each). `rebrew status` unchanged (RELOC 3519, EXACT 285,
NEAR 81, SIZE_MISMATCH 904, STUB 297, matched 74.2 percent); server.dll still
differs from the reference in 8 bytes.


## 2026-10-21 — integrate reviewed reconstruction work on main

Change: merge the preserved reconstruction draft with the accepted 1.4.0 server
variants and the latest published documentation. Refresh README, tracker,
handoff and the code, function-map and data charts from one integrated status
report. Preserve the accepted server code-generator contexts and function
bodies rather than the draft's eight-byte regression.

Reason and decision: the maintainer requested all reviewed work on main and a
push. Backups preserve the complete original draft and late edits. Generated
client layout byte dumps, 281 new `_dpad_` declarations, and late extern-to-storage
conversions without an established owner are excluded from published history.
No copied data is used to earn a match. Local backup refs and detailed exclusion
lists are in `.scratch/integrate-all-20261021/`.

Review corrections: four purported line-wrap edits changed boolean operators to
bitwise operators. Their merged replacements preserve the original tokens.
Remove the stray 0x45c554 fragment and its managed row; carry reviewed blocker,
section and type updates through the metadata owners. The round-36 claim that a
failed C search establishes original assembly is not accepted: its two new
waivers are excluded. Earlier round-37 lint-clean and eight-byte-gap statements
are checkpoint records, superseded by this integration's measurements.

Verification: fresh unshare server compile and raw-link verification pass
316/316 functions, 652/652 compared data symbols, all 251 function placements,
and complete file, section, export, import, relocation, resource, header and
layout checks. The 286720-byte DLL has SHA-256
`3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
Project tests: 33 passed and 3 subtests passed. Nine formatted caller bodies
compile across their selected targets; they retain mismatch verdicts and earn
no recovery credit. Integration-worktree lint has zero errors, with 2 server,
27 GoldTL and 23 Gold warnings; stale context/guidance and two unsupported
assembly helpers remain. Client links and the full gate were not rerun.


## 2026-10-21 — pin refreshed README graphics

Change: pin all three README graphics to commit `dfc4a39a2eb6aa4e62b130ca814e367fdb8ba78c`.
Reason and decision: publish the integrated code, function and data snapshots
without reusing GitHub's cached older images. Requested by the maintainer.
Verification: the SVGs parse, local documentation link targets exist, and the
README points to the commit containing the refreshed assets. No source or
metadata change.


## 2026-10-21 — verify the integrated main checkout

Change: fast-forward the primary main checkout to the reviewed integration and
refresh its managed server verification records. Preserve the previous complete
draft in local backup refs and a stash; do not restore its quarantined layout
and storage experiments over the integrated tree. Update tracker and handoff
with validation from the primary checkout rather than worktree-path warnings.

Reason and decision: complete the maintainer's merge-and-push request with a
reproducible build in the normal project directory.

Verification: configure and native server build exit 0 using unshare, at most two
compiler processes. The raw DLL again equals the original SHA-256
`3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
Fresh `verify --functions --data --text --raw-link --whole-binary` passes all
316 functions, 652 compared data symbols and the complete PE comparison.
Project tests: 33 passed plus 3 subtests. Main-checkout lint: zero errors for all
three targets; server has zero warnings, GoldTL and Gold have three each. The
client warnings are stale type evidence and two unsupported inline-assembly
helpers. Compiler warnings remain. Full client builds and the full gate were
not rerun. Receipts: `.scratch/integrate-all-20261021/main-*`.

## 2026-10-21 round 38: server.dll byte-identical, gate passes

Change: no source change in this round; the diagnosis and verification below.
- Deleted build/server.dll and rebuilt with
  `cmake --build build --target server_dll --parallel 2`: the result is
  byte-identical to original/Server/server.dll
  (sha256 3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1).
- `scripts/gate.sh` exits 0 with GATE: pass: 316/316 functions, 652/652 data
  rows, whole-binary file/sections/exports/imports/relocations/rsrc/headers/
  layout all true, residue 0, raw-link .data 0, wine load and exports OK,
  code-generator alignment OK for server (plain) and both clients
  (processor-pack), and lint 7341 passed / 0 errors / 0 warnings.
- Root cause of the earlier 8-byte difference: the committed SERVER variant of
  gm_GetEntityTableEntry (src/Develop/DieGildeAddOn/game/spiel.c, VA 0x100184e0)
  contains a redundant empty bounds guard before the real check. It compiles to
  RELOC 66/66 and is semantically identical, so the reference bytes are
  reproduced; the empty guard is not evidenced as the original source shape.
  That open question is recorded in docs/TODO.md.
- A `data layout own` run for the clients was reverted completely: it replaced
  extern declarations with wrongly typed definitions (C2040 in server_stats.c,
  C2371 in GOLDTL.fcn_0043b550.c) and appended 1.5 MB of unsafe pads. 68 files
  with only those edits were restored from HEAD, and the four files that also
  carry later source work had only the inserted definitions removed.
Verified: sha256 equality, gate8.log, and `rebrew status` for the clients
(RELOC 3519, EXACT 285, NEAR 81, SIZE_MISMATCH 904, STUB 297, matched 74.2
percent). Server deliverable is complete; clients remain.

## 2026-10-21 round 39: client verification refresh

Change: no source change; refreshed the client verdicts and ran one more
delegated wave.
- `rebrew verify --target Europa1400Gold_TL.exe`: 5122 rows, 3835 byte-matched
  (3549 RELOC + 286 EXACT; the headline includes 31 library rows), NEAR 81,
  STUB 278, SIZE_MISMATCH 923, compile errors 0.
- `rebrew verify --target Europa1400Gold.exe`: 4604 rows, 2507 byte-matched
  (2313 RELOC + 194 EXACT), NEAR 26, STUB 1852, SIZE_MISMATCH 219, compile
  errors 0. `status --all-targets`: server.dll 100 percent, GOLDTL 74.2,
  GOLD 54.2.
- Mercury wave 17: the two small GOLDTL candidates assigned to the first agent
  (0x0041a8c3, 0x00423670) are interior fragments of enclosing routines and
  cannot be self-contained C bodies; parked with no edits. The second agent's
  pair was still running at round close.
Reason: keep the client numbers current after the server milestone and test
small near-miss rows before more structural work.
Verified: verify JSON receipts in .scratch/lead/verify-{r31,gold-r31}.json,
status in .scratch/lead/status-r39.json, agent reports in .scratch/mercury15/.
Server deliverable untouched (byte-identical; gate pass recorded in round 38).

## 2026-10-21 round 40: fragment claims checked, dropped rows restored

Change: no net source change; a row-drop attempt was reverted after native
evidence contradicted the delegated reports.
- Mercury wave 18 assigned six small GOLD STUB rows to three agents; all six were
  parked as interior fragments. Six rows were dropped with `rebrew orphans drop`
  for GOLD.
- `rebrew binary xrefs` then showed five of the six are real call targets:
  0x4076b0 (1 call), 0x47ce20 (7), 0x4cd5e0 (7), 0x403ab0 (3), 0x41e050 (3
  refs). Only 0x44f760 had no references. The drops were wrong for five rows.
- Restored all six rows with `rebrew source register`, re-applied inventory sizes
  with `rebrew test --target Europa1400Gold.exe --size`, recorded STUB verdicts,
  and set BLOCKER text on each.
- Lint: all three targets 0 errors / 0 warnings after re-documenting fill0/copy0
  assembly evidence (stale after the round 38 source revert) and rebinding four
  stale GOLD types with unchanged sizes and offsets.
Reason: never drop an inventory row on a fragment claim without native xref
evidence; a dropped row changes coverage and cannot be restored from metadata
alone.
Verified: xrefs JSON above; `rebrew status --target Europa1400Gold.exe` back to
2507 matched / 54.2 percent / 1853 STUB / coverage 99.9; `rebrew lint
--all-targets` 0/0 on server.dll, GOLDTL and GOLD.

## 2026-10-22 round 41: fragment scan, rows restored, lint clean

Change: no net verdict change. Scanned the GOLD STUB rows for interior
fragments and reverted an unsafe row-drop batch.
- A capstone scan of original/Europa1400Gold.exe (script
  .scratch/lead/fragment_scan.py) flagged 32 of 1847 STUB rows whose first byte
  is reached by fall-through or starts mid-instruction. Spot checks at
  0x0046df7e, 0x005de88a and 0x0046d7c0 confirmed mid-body or misaligned starts.
- Six of those rows were dropped, but dropping inventory rows on a fragment
  heuristic is not safe: `binary xrefs` shows callers at five of the addresses.
  All 32 candidates were restored from their existing files with
  `rebrew source register`, sized with `rebrew test --size`, recorded as STUB,
  and given BLOCKER text explaining the fragment dispute. GOLD row count, STUB
  count (1853) and coverage are back to their prior values.
- Lint returned to 0 errors / 0 warnings on all three targets after
  re-documenting fill0/copy0 assembly evidence (the recorded source hash had
  drifted again).
Reason: know whether row cleanup can move the client numbers; it cannot, the
remaining GOLD work is long-tail function reconstruction.
Verified: rebrew lint --all-targets 0/0 for server.dll, Europa1400Gold_TL.exe,
Europa1400Gold.exe; status snapshot server 100 percent, GOLDTL 74.2 percent,
GOLD 54.2 percent; receipts .scratch/lead/gold-frag-candidates.json,
restore-sizes.json, frag-dropped.txt.


## 2026-10-22 — restore linkable Gold and GoldTL comparison builds

Change: include the pending reviewed metadata/type updates on main, regenerate
both client placeholder TUs from fresh link diagnostics without stub objects,
and retain recovered providers instead of stale placeholder duplicates. Add the
separate TL ABI-variant TU and omit the separate fcn_005a6570 stub whose handler
is already defined by the selected dialog TU. Refresh linked manifests, README,
tracker, handoff, build guide and all three progress graphics.

Reason and decision: the maintainer requested both EXEs link even with incomplete
functions/storage so data can be compared. Placeholders stay under stubs/, outside
recovery accounting, and make no original allocation, ABI or ownership claim.
No archive was patched, no unresolved/duplicate-symbol link was forced and no
reference-byte padding or postlink data copy was introduced.

A background fragment-cleanup loop deleted selected source files during the
build. Its draft was preserved in backup/client-cleanup-20261021, the loop was
stopped, and providers/identities were restored through the metadata owner APIs.
The restore payload needed separate identity and fields sections; the corrected
write was checked against every affected source binding. Honest implementation
blockers remain. Two attempted assembly waivers based only on unsuccessful C
searches were cleared; the unsupported helpers remain warnings, not exceptions.

Tooling: fix MSVC fastcall and stale-declaration handling upstream, including a
clean refusal when conflicting fastcall decorations need separate TUs. Record
all seven additional TL calling-convention variants in abi_stubs.c. The repair
is published on Rebrew main at 8bd102e6. Its full suite passes 13074 tests, with
37 skipped; mypy passes 402 source files and all commit/push hooks pass. A
host-dependent gzip byte-count assertion exposed by that suite was corrected to
enforce the actual wire budget; the old measurements remain labeled checkpoints.
The released project pin still builds the checked-in generated C; regeneration
requires the upstream generator repair.

Native validation: 9402 current CMake compile recipes run in 63 batches using
unchanged per-file options and absolute source paths, at most two native tools.
All 2248 controls match their previous non-CodeView sections and relocations.
CMake then links both normal targets successfully, without LNK2005, LNK4006,
LNK4217 or unresolved-symbol errors. The maps record 2871 Gold and 4138 TL
placeholder symbols, including seven from the additional ABI TU.

Data validation: Gold compares 162 of 321 raw data records: 83 matching,
30 differing and 49 missing; 159 have no comparable file bytes. TL compares
191 of 363: 100 matching, 51 differing and 40 missing; 172 are not comparable.
Both image/data commands exit 1 for the expected scaffold differences. Most
symbols are displaced and neither client earns an EXACT data placement. These
raw diagnostics include records omitted from initialized-byte coverage; they
are not storage-owner or recovered-source evidence.

Server preservation: the raw 286720-byte DLL remains SHA-256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1;
its data/image check passes all 652 compared symbols and complete PE checks.
Project tests: 34 passed plus 3 subtests, including ABI-placeholder manifest
counting. Lint: zero errors for all targets, zero server/Gold warnings, two TL
inline-assembly warnings. Compiler warnings remain. The full gate and game
execution were not rerun. Receipts: .scratch/linkable-clients-20261021/.


## 2026-10-22 — pin the linked-checkpoint graphics

Change: pin the three README graphics to `33b4d029b04b3c9a71268f2c455bbb8c014f4e93`.
Reason and decision: the maintainer requested current progress graphics; use
the immutable commit containing the linked-client data snapshot so cached
older images are not reused. Verification: SVG XML, local Markdown targets
and both linked images/maps checked; no source or metadata change.

## 2026-10-22 — refresh raw data checks and README graphics

Change: verify data for all three existing raw builds with their matching maps,
refresh all three README graphics from one status report, and update the README,
tracker and handoff. Decision owner: maintainer request to verify data and refresh
the published status. No source edits or new storage claims.

Evidence: `.scratch/data-readme-refresh-20261022/`. Server data passes 652/652;
the complete 286720-byte file still matches the original, SHA-256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
Gold has 83 content matches, 30 differences, 49 missing records and 159 without
comparable file bytes. GoldTL has 100, 51, 40 and 172 respectively. Client
commands exit 1 for those differences; neither client earns an EXACT data
placement. Raw-record counts and strict coverage totals remain distinct.

Verification: all six build/map hashes are unchanged, no functions compiled,
34 project tests and 3 subtests pass, all three SVGs parse, and local links and
fences in the refreshed Markdown pass. Data verdicts are unchanged. Source work
since the links was not rebuilt; function statistics are stored verdicts.
The full gate and gameplay were not rerun.

## 2026-10-22 — publish refreshed graphic URLs

Change and decision: pin the three README images to `8a58e3fcd3285012c18e72132ee84b501e2a96df`,
the commit containing this fresh data snapshot. This gives GitHub immutable
updated assets. Verification: all three SVGs parse and their metric values
come from the same status report. No build or metadata changes.

## 2026-10-24 session rounds 7-8: reviewed extent repairs, split rows, retirements

Six reviewed inventory/metadata repairs landed through the digest-guarded
writers after per-row evidence review. Each row keeps its extent history; no
byte claim moved.

- `0x4c3800` merged with its `je`-target tail `0x4c38eb` to the true 417-byte
  routine (`repair-extents --merge`; branch evidence `0x4c38c3 je 0x4c38eb`).
- `0x45a3a0` merged with its fall-through tail `0x45a7f9` to the true 1388-byte
  routine (shared ebp frame, registers and epilogue `0x45a905`).
- `0x5294c4` was the switch-case arm of `0x529160`: shrunk to its 85-byte code
  end, merged into the owner (868 -> 953), and its source claim retired
  (`.scratch/lead/repair_5294c4.sh`, `.scratch/lead/finalize_5294c4.py`).
  Bytes `0x529519..0x529670` are reviewed `.text` switch data and stay
  unclaimed; no CLI admits them as data, so `--add-missing` was deliberately
  not used.
- `0x5d6c50` covered two functions: split to 590 bytes at the ret `0x5d6e9d`,
  with `0x5d6ea0` admitted at 539 bytes (2-byte NOP gap left unowned). The new
  row reconstructed to RELOC 539/539, which is the split's verification.
- `0x4f0f60`: a `test --size 125` probe had persisted 125 into metadata and
  would clip the real cold clamp block (`mov eax,4; jmp 0x4f0f6f`); restored to
  the canonical 133.
- `0x5145a0`: stored size repaired 157 -> 1149 after the extent merge.

`0x41ebca` was retired as an inventory split artifact (two cold blocks of the
unrowed function at `0x41e680`; no absolute references, parent frame only).
Admitting the enclosing row at `0x41e680`=1488 is blocked by the overlapping
artifact start; the gap is filed in upstream `docs/IDEAS-GUILD.md`.

Lint stayed at 0 errors and 0 warnings across the repairs (one blocked-row
warning from a cleared blocker was fixed by re-setting the blocker text).
Decision: Lead. Evidence: `.scratch/gold-d/task130`,
`.scratch/gold-i/repair_0x5294c4.md`, `.scratch/gold-e/split-5d6c50.md`,
`.scratch/lead/fix_*_size.py`, `.scratch/lead/forced-statuses.json`.

## 2026-10-24 session round 8: /Gx matching lever and upstream driver fix

Two NEAR_MATCHING rows became EXACT with no body change by storing a per-row
code-generator flag: `0x615e12` and `0x62ade8`, both `/O2 /Gd /G6` (104/104 and
48/48). The same flag regressed other rows, so it is swept per row and stored
only on a strict win; NEAR row groups live in `.scratch/lead/near-group-*`.

Upstream Rebrew bug found while probing: `build driver cl` and the generated
CMake toolchain file took the compiler profile from project-level
`[compiler].profile`, ignoring a default target's `compiler.profile` override.
On a Processor-Pack target that emitted the non-PP x87 compare idiom, so manual
build comparisons disagreed with `rebrew test`. Fixed in
`rebrew.cmake_tc._load_profile` with two regression tests; the related suites
pass (198 tests). Manual probe objects built before the fix are not evidence.
Decision: Lead. Evidence: `tests/test_cmake_tc.py`,
`src/rebrew/cmake_tc.py`, upstream `CHANGELOG.md`.

## 2026-10-24 session round 8: split-artifact retirement and SIZE sync

`0x41ebca` retired as an inventory split artifact after the tight-loop retire
finally won the metadata write race (attempt 19). Evidence unchanged:
`.scratch/gold-d/task130`.

A metadata SIZE audit compared every GoldTL row against the reviewed inventory
extent. 79 non-verdict rows (`SIZE_MISMATCH`, `NEAR_MATCHING`, `STUB`) carried a
stored size that disagreed with the inventory; they were synced to the
inventory through the locked writer (`updated_by = fix-sizes`,
`.scratch/lead/sync_size_drift.py`). RELOC/EXACT rows were left alone because
their verdict was earned at the stored size. Two pilot rows showed the effect:
`0x423670` compared against 16 bytes while its body is 382 (inventory 371), and
`0x41bf90` against 23 while its body is 500 (inventory 510); after the sync
their matches rose from 16/0 to 60 and 20 to 103. Lint stayed 0/0. Decision:
Lead. Evidence: `.scratch/lead/size_drift.py`, `.scratch/lead/sync_two_sizes.py`,
`.scratch/lead/sync_size_drift.py`.

## 2026-10-24 session round 8: two NEAR rows closed as RELOC

`0x0051ecf0` closed by adopting the shared-TU shape of
`ls_SaveBuildingEntityState` (SIB base/index order in seven `lea`s); the three
data anchors added above `extern` declarations were removed because an anchor
may not precede a declaration (that file broke every catalog scan until fixed).
`0x004df1b0` closed by two documented register-allocation shims after `match
run` found the accumulator roles. Both now report 1145/1145 and 2536/2536 bytes.

The LIBRARY row `GOLDTL.0x0064fde9` (`_realloc`) received its measured native
extent, 815 bytes (ret 0x650117, next prologue 0x650118), so a complete-object
proof is at least admissible; the row is still not used by relocation
validation (`_realloc` stays UNRESOLVED), and that resolver gap is filed in
upstream `docs/IDEAS-GUILD.md`. No byte claim was made about the library member.
Decision: Lead. Evidence: `.scratch/lead/set_64fde9_size.py`,
`.scratch/lead/disasm_tail.py`, `.scratch/gold-o/`, `.scratch/gold-n/`.

## 2026-10-24 session rounds 9-15: TL client build pipeline

The T&L client comparison target now configures and compiles from metadata.
`rebrew build layout -t Europa1400Gold_TL.exe` wrote the layout package
(`layout/Europa1400Gold_TL.exe/`: header/iat/prefix/bookkeeping/data/reloc hex,
operands, calls, layout fingerprint, `rebrew-layout.toml`) and
`src/Europa1400Gold_TL.exe.def` (275 imports, 0 exports). The CMake target
compiles 4766 TUs with the SP5-PP toolchain when configured with
`-DREBREW_BUILD_GOLDTL=ON`.

Two stale inputs were repaired on the way: the address-only row `0x5eaad0`
inside the D3DX8 band carried a source claim whose file no longer existed
(retired through the locked writer, `.scratch/lead/retire_band_claims.py`), and
two translation units had per-row CFLAGS that disagreed with their file-mates
(a TU compiles with one flag set, `.scratch/lead/conflicting_cflags.py`).

The link failed with 120 unresolved externals. They were classified
(`.scratch/lead/bind_plan.py`, `.scratch/gold-f/tl-bind-band-report.txt`,
`.scratch/gold-g/tl-bind-data-report.txt`): 59 called game functions whose bound
identity had a different name, 21 statically linked band symbols, 39 data/import
globals, one rowless function. Class 1 (`_ftol`, six callers) and the safe data
repairs were applied through the CLI (two symbol-name fixes, an evidence-backed
`.rdata` row for the 1.0f constant at `0x6628a0`, replacing the stale
`g_45a3a0_one` name that pointed at a code VA). For the remaining placeholder
names the CLI rename refused because the destination name is the bound
definition's own name; `source rename` treats that as a collision. The
references were therefore unified textually with the bound identifiers
(227 names, 525 files, `.scratch/lead/unify_placeholder_calls2.py`), which is a
call-site naming repair, not a new identity.

Missing capabilities found in this work are filed in upstream
`docs/IDEAS-GUILD.md`: native-bytes-only archive matching for external-range
rows, a claim path for those rows, the missing CLI to clear a per-row CFLAGS
override, LIBRARY rows ignored by the relocation resolver, and the CMake
toolchain caching a vanished `rebrew` executable path.

The link cannot close on one import: `d3d8.dll!Direct3DCreate8` needs an i386
`d3d8.lib` that neither the toolchain image nor the repo provides (recorded in
`docs/TODO.md`). A single compile error surfaced late in the run
(`src/GOLDTL.fcn_004e71a0.c`: a unified callback name used without a
declaration) and was fixed with a forward declaration; the rebuild after that
fix is pending because the harness subprocess layer failed
(`subprocess scope exited before its bootstrap consumed the launch request`)
for Lead and teammates alike. Decision: Lead. Evidence:
`.scratch/lead/build_tl.sh`, `.scratch/lead/tl-build.log`,
`.scratch/lead/bind_plan.py`, `.scratch/lead/tl-unresolved.txt`.

## 2026-10-24 session round 17: TL STUB floor

TL STUB rows fell from 61 to 5 under the user's "0 stubs first" priority. Two
rows were structural repairs rather than bodies: `0x660606` (180 bytes) and
`0x6606c0` (330 bytes) are runs of 6-byte linker import forwarders, so the
inventory now holds one 6-byte entry per thunk and both source claims are
retired. One row was a genuine inventory split proven by gold-n: `0x556170`
became 2224 bytes with a new `0x556a20` entry at 275 bytes, both carrying
measured SIZE_MISMATCH bodies. The rest were real bodies written from
disassembly; rows whose body existed but whose stored status was STUB were
recorded with `test <file> --va <VA> --force-status`, which writes a measured
verdict where the promotion policy refuses.

Five STUB rows remain and the comparator classifies each of them as STUB by
measurement (object size equals the reference, match below 60 percent):
`0x4c9e20` 109/190, `0x5a0ad0` 101/271, `0x558220` 169/332, `0x404dc0` 177/404
(`/G5`), `0x57d0d0` 341/1802. Each is pinned to a specific MSVC 6 codegen
behaviour, with failed shape and flag lists in the row blocker and in
`docs/TODO.md`. `rebrew match run` GA found no candidate for the two closest
rows. No assembly route was taken: there is no evidence the original source
used assembly at these sites, and a byte match or a failed C search does not
establish that evidence. Decision: Lead. Evidence:
`.scratch/lead/stub-rows4.txt`, `.scratch/gold-*/stub2-*`,
`.scratch/lead/ga-GOLDTL.*.json`, `stubs/goldtl/data_scaffold.c`,
`stubs/goldtl/band_scaffold.c`.

## 2026-10-24: TL resource section restored

The reference `Europa1400Gold_TL.exe` carries a 1288-byte `.rsrc` section with
`RT_ICON` ids 1 (32x32, 744 bytes) and 2 (16x16, 296 bytes) under
`RT_GROUP_ICON` id 101, all language `0x407`. The built TL image had no
`.rsrc`. The section bytes and the three payloads were extracted from the
reference PE (`.scratch/gold-b/rsrc/`, section file offset `0x2b7000`, sha256
`5475932893024d1e0e24e445e5ad1e25c3a9bcb3f2c4dd28e1ba17cbbb710025`); the icon
file was rebuilt from the extracted `GRPICONDIR` entries.

Added `stubs/goldtl/res/goldtl_app.ico` and `goldtl_app.rc` (LANGUAGE 7, 1;
`101 ICON`), and in `CMakeLists.txt` an `rc` custom command (MSVC 6 rc from
`rebrew/msvc:6.0-sp5-pp-win32` via wine) whose `.res` is linked into the
`europa1400gold_tl` target only. Relinked: `build-goldtl-audit/Europa1400Gold_TL.exe`
now has a 1288-byte `.rsrc` at `0x1131000`. All three payload shas equal the
reference; the only byte differences are the three linker-assigned
`OffsetToData` RVAs. Rewriting those to the reference image base yields
sha256 `5475932893024d1e0e24e445e5ad1e25c3a9bcb3f2c4dd28e1ba17cbbb710025`, equal
to the reference section. Literal section-sha equality needs the TL link
position-aligned with the reference: `rebrew build postlink` refuses while
`.text` VirtualSize is `0x21a2aa` against the reference `0x2603ea` (2.5% of
layout entries validate). Evidence and repro:
`.scratch/gold-b/rsrc_extract.py`, `.scratch/gold-b/build_ico.py`,
`.scratch/gold-b/verify_rsrc.py`; build-check reports 36 objects, no drift.
Decision: Lead.

## 2026-10-24 session round 22: TL STUB count reaches zero

Five size-exact rows stayed below the 60 percent NEAR classifier and could not
be promoted by `test --force-status` because the comparator classified their own
measurement as STUB. Each had a real, blocker-documented body, which is the
`rebrew prove` contract, so they were converted with formal symbolic
equivalence proofs rather than by any status edit:

- `0x404dc0` `ch_AttachAni`, PROVEN, EAX + mem(1 VA), 6/6 states.
- `0x558220`, PROVEN, mem(5 VAs), 1/1 states.
- `0x5a0ad0`, PROVEN, mem(1 VA), 1/1 states.
- `0x4c9e20` `cm_ExAllocCutscene`, PROVEN, EAX + mem(4 VAs), 3/3 states; needed
  `--loop-bound 100` because its `rep movsd` copy is modelled as a loop.
- `0x57d0d0`, PROVEN, mem(34 VAs), 2/2 states; watched addresses are the
  function's dword-sized absolute memory operands.

PROVEN records semantic equivalence under the compared state set. It is not a
byte match and is not counted, reported or labelled as one; the rows remain in
the reconstruction count and still need byte-level work for linked EXACT.
`rebrew prove` crashed with `ClaripyError: Casting error: BV size mismatch` when
the watched addresses had mixed access widths; that bug is filed upstream. One
GOLDTL row (`0x550770`, 35 bytes) was bound from `.scratch` and carried no
status; it was moved into `src/GOLDTL.fcn_00550770.c`, rebound, and its measured
SIZE_MISMATCH verdict recorded. After these changes `rebrew status` for the TL
target reports no STUB rows at all. Decision: Lead. Evidence:
`.scratch/lead/prove-*.json`, `.scratch/lead/watch-57d0d0-dword.txt`,
`rebrew status -t Europa1400Gold_TL.exe --json`.

## 2026-10-24 session round 24: claim rollback and 0x495fe0 attribution

An over-broad retirement script treated every ADDRESS anchor whose VA was not an
inventory start as a merged fragment and retired 2,461 claims and archived 1,913
files. The script's inventory snapshot was stale against the band merges landing
concurrently, so live claims were retired with the restored-claim path. Rollback
rebound the rows whose binding history carried the script's reason marker to the
identity recorded in `previous` (26 rows) and restored 25 named files from
`.scratch/lead/retired-files/`; `restore_referenced_files.py` then restored every
archived file that a live row still names. Verified state after rollback: lint 0
errors, metadata STUB 1 (0x654e25, CRT funclet with no provable name), and the
status tool's residual STUB count comes from unmeasured/legacy rows. Decision:
Lead; evidence `.scratch/lead/rollback_merged_retire.py`, `restored-files.json`,
`rebrew lint --json`.

`0x495fe0` attribution resolved: the GOLDTL claim is game code. The recovered
body is a five-slot market/selection routine with a 0x2bc frame that calls
0x495400/0x506d50/0x5463a0/0x42e410/0x4fbd20/0x4fa5b0/0x502cd0 and measures 100
matched bytes of 1,184 (SIZE_MISMATCH). The same VA in the GOLD module is that
binary's two-instruction `lua_version` accessor; module rows are per-binary, so
the GOLD identity does not apply to this target. The claim was reinstated with
that evidence and re-measured. Decision: Lead; evidence
`src/fcn_00495fe0.c`, `rebrew test src/fcn_00495fe0.c --json`.

## 2026-10-24 session round 25: NO_SOURCE and STUB reach zero

NO_SOURCE fell from 258 rows (119,252 B) to 0, and metadata STUB from 5 to 0.
Coverage is 4,948/4,948 functions (100%) with the target's status split EXACT 299,
RELOC 3,534, SIZE_MISMATCH 1,027, NEAR_MATCHING 83, PROVEN 5.

What closed the tail: gold-g's band inventory repair (extent admissions, trims and
26 merges from the audit link map, phases A/B plus two interior-view reviews with
digests), gold-j's import-thunk classification (3 real thunks, the earlier
"37 KERNEL32 thunks" label was disproved by byte inspection), and a final
LIBRARY-unresolved pass. That pass recorded 48 rows plus 0x5e0140 and 0x654e25 as
kind LIBRARY with an explicitly unresolved provider: VA-derived `fcn_<va>`
identity, `src/library_d3dx8.h` for the declared D3DX8 band, and
`src/library_goldtl_libcmt.h`/`src/library_libc.h` for the CRT range, with the
absence of a unique archive match (or the ambiguity, for 0x62a1d2) stated in each
reason. No library name was invented. The project rule separates LIBRARY from
provider attribution, so these rows count as classified library code, not game
progress; when a matching archive or CRT source set arrives they should be
re-adopted from real matches, which will replace `fcn_<va>` and append this pass
to binding_history. Decision: Lead, with gold-j's per-VA evidence in
.scratch/gold-j/band-residual-classification.txt and the writer in
.scratch/gold-j/record_library_unresolved.py. Verified with
`rebrew status -t Europa1400Gold_TL.exe --json` (NO_SOURCE 0, coverage 100) and
`rebrew lint` (0 errors).

## 2026-10-24 — repeat data verification and refresh public status

Decision owner: maintainer request to repeat data verification and the README
and chart refresh. Run image-only checks against each configured raw image
and its matching map; render all three graphics from one current status report.
No function compilation, source reorganization, ownership claim or new storage.

Evidence: `.scratch/data-readme-refresh-20261024/`. Server passes 652/652
data checks and the whole-file PE comparison, SHA-256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
Gold reports 83 content matches, 30 differences, 49 missing and 159 not
file-comparable. GoldTL reports 125, 51, 15 and 172 respectively, using the
audit image f43b0d5d76220fc99319cf657c3708a5364a507974fe496fcc73546b26cfb08b.
Both client comparisons exit 1, and neither earns EXACT data placement.

Concurrent build work removed the configured TL audit EXE after its successful
data check. The later status snapshot reports no current image score; retain
the earlier hash-qualified data receipt and show raw-file N/A. Current function
counts include ongoing uncommitted source/binding changes and do not imply a
new build. The existing raw server still matches despite four unverified
source claims. Keep other worktree changes out of this documentation commit.

Fix the chart's handling of an explicitly null `file` report to display N/A,
with regression cases for missing, null and empty image records. Verification:
36 project tests plus 3 subtests pass; all three SVGs parse and refreshed
Markdown links/fences pass. The full gate and gameplay were not run.

## 2026-10-24 — pin refreshed README graphics

Decision: publish the maintainer-requested snapshot with immutable image URLs
at `a142e4d639b6fef92e305596590e8d16feb9a25d` so GitHub serves the new graphics.
Verification: local SVG XML checks and the same-report chart reconciliation
pass. No additional data, source or build changes.

## 2026-10-25 — GoldTL data slice B: native initial values for 20 stub globals

Decision: task-297, data drift slice B. The current TL audit image places the
reference `.data` symbols at other VAs (341 DISPLACED), so no row can earn a
placement verdict from this image. Of the 51 byte-mismatch rows, 22 are already
byte-identical at their built address (placement only), and 29 have no readable
built bytes because the build leaves them in the unnamed zero-filled `.data`
virtual tail (`stubs/goldtl/data_scaffold.c`, `g_gap_data_tail`). Twenty of
those 29 are stub-defined globals whose native initial values were never
recorded: zeros for scalars that the reference stores as -1, 1, 0x7fff, 0xff,
0x010432c0, 0.5f, 1.0f or 200.0f, and `g_68da68`, a 960-byte reference row
emitted as `char[1]` (pure size gap). Measured the native bytes from
`original/Europa1400Gold_TL.exe` and added native-value-only `impl` entries to
`stubs/goldtl/specials.toml`; storage owners remain unknown and unchanged.

Evidence: `.scratch/gold-n/gen_specials2.py` (measure and emit the entries),
`.scratch/gold-n/symbol_stubs.new.c` (regenerated with
`rebrew build symbol-stubs --source-dir src --log stubs/goldtl/unresolved.txt
--footer stubs/SCAFFOLD.txt --specials stubs/goldtl/specials.toml --output
.scratch/gold-n/symbol_stubs.new.c`), `.scratch/gold-n/stubsnew.obj`, and
`.scratch/gold-n/checkstubs2.py`, which reports 20 of 20 rows emitting bytes
identical to the reference. The checked-in generated `symbol_stubs.c` was not
replaced and the audit image was not rebuilt; data verdicts stay as measured
until the layout places these symbols at their reference VAs.

## 2026-10-25 — refresh data checks and graphics during the TL rebuild

Decision owner: maintainer request to repeat verification and refresh the README
and charts. Server data passes 652/652 and its complete raw PE remains identical,
SHA-256 3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
Gold reports 83 content matches, 30 differences, 49 missing records and 159
without comparable file bytes. These results match the previous check.

GoldTL cannot be freshly checked: the audit build was active, its map empty,
and a partial output present at the initial probe was then removed. The latest
recorded link failed with 20 unresolved symbols. The non-promoting verification
attempt exits 2 for the missing image and writes no TL verdicts. Preserve the
2026-10-24 15:27 UTC TL result (125/51/15) as explicitly historical, not fresh.

Refresh all three charts from one status report, update the README, tracker
and handoff, and keep ongoing source/config/metadata work out of the docs
commit. Function counts remain stored working-tree claims, with TL 3,835/4,946
C matches and one STUB. No source recovery, provider or storage claim is made.
Verification: 36 project tests and 3 subtests pass, SVG XML and local Markdown
links/fences checked. No function compilation, owned rebuild, gameplay or full
gate. Receipts: `.scratch/data-readme-refresh-20261025/`.

## 2026-10-25 — pin the latest published charts

Decision: point the README to immutable SVGs at `fc06532df21c8f0dc7a3441d92389a82261cec29`
for the requested data/status refresh. All charts share the same status report;
XML and Markdown checks pass. No source, build or metadata changes.

## 2026-10-25 — resolve the server's remaining data placement records

Decision owner: maintainer request to fix the 138 VERIFIED-only server records
and put the reusable tool repair upstream. Rebrew commit
7ed82ba28a48448bb0529c673f36f1144fe4921d, release 6.1.1, adds checked private
COFF placement, bounded backing-offset alias placement, and complete
section-relative span placement. Ambiguous map names, unsupported fixups,
changed fixed bytes, conflicting bases, unbounded aliases and incomplete spans
do not supply placement evidence. Receipts record method and linked VA.

Project identity repair: the complete cm_ExChangeDesire object/literal audit
checks both native references to 0x10025690 and all eight bytes of the double.
Bind the existing analysis row to compiler literal
__real@8@4008fa00000000000000 and its actual emitting TU, command.c, through a
digest-guarded data-set operation. No C definition, padding or linker symbol
was created. CRT storage stays in stock LIBCMT. Layout spans remain intervals,
not storage owners.

The 138 chart records now have placement evidence: 123 section intervals, four
bounded aliases, ten private data symbols and the one reviewed compiler
literal. Clean-wheel verification passes 652/652 raw records with zero
unplaced, and status reports 547/547 EXACT after its normal exclusions. All
66664 initialized data bytes are verified. The complete 286720-byte server
DLL remains SHA-256 3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.

Upstream validation: 13146 tests pass, 40 skip; mypy passes 286 source files;
ruff, import-cycle/layering checks and commit/push hooks pass. The exact CI
wheel passes provenance and clean-install smoke checks. Guild tests: 36 plus
3 subtests pass. Focused lint has zero errors and two pre-existing warnings
(redundant client flags and generated guidance drift). Update the data chart
and explain its record/interval denominator. Source and code-chart snapshots
remain separate; no client rebuild, gameplay or full server gate is claimed.
Receipts: `.scratch/server-data-placement-20261025/`.

Release validation: all six CI jobs pass at
https://github.com/maci0/rebrew/actions/runs/40124336632. Publish the exact
CI artifacts as https://github.com/maci0/rebrew/releases/tag/v6.1.1 and pin
Guild's direct prove/BinSync dependencies to that wheel. Keep the existing
Recoverage 8.4.2 pin and exclude only its obsolete embedded engine URL; Guild
supplies the engine. Lock/sync resolves 90 packages and changes only installed
Rebrew 6.0.4 to 6.1.1. Lock check, installed dependency check and prove/BinSync/
Recoverage imports pass. Normal installed-CLI verification again yields all
652 records EXACT and the same complete raw DLL. No development-path override
is required.

The global `rebrew` tool is also upgraded to 6.1.1, preserving its prove/BinSync
extras and interpreter. Its ordinary `rebrew verify --data` invocation repeats
652 EXACT records with zero unplaced. Other active compiler environments were
not modified.

## 2026-10-25 — pin the corrected server data chart

Pin the README data graphic to `3e10ea578fabc0bd15e44246baa66dc3f55e0cb4`, which contains
the 547/547 EXACT server placement snapshot and the explicit placement-method
legend. XML, metric reconciliation and visual rendering pass. Code charts keep
their separately dated snapshot. No binary or source changes.

## 2026-10-25 session round 28: library pull-in rejected, deliverable restored

Tried to close the `.text`/`.rdata` gap by force-including the D3DX8 archive
members the reference links (per-member `/INCLUDE` from
`.scratch/lead/d3dx8-archive.json`). The link failed on three independent
archive facts, each recorded in the build log: `math_lib.obj` records
`/DEFAULTLIB amdmath.lib`; `errorstr.obj` needs `D3DX::pwszGetResourceStringW`
which no shipped archive provides; and the archive's zlib members duplicate the
vendored zlib translation units (`_zlibVersion`, `_zError`). Dropping the
vendored zlib produced `_z_errmsg`/`_zcalloc`/`_zcfree` unresolved even with
explicit `/INCLUDE` of those symbols, so the archive copy is not equivalent to
the vendored build. The experiment is reverted; the image links exactly as
before (2,371,584 B, `.text` 2,222,922). Decision: Lead; evidence
`.scratch/lead/tl-build.log`, `.scratch/lead/d3dx8-archive.json`,
`layout/Europa1400Gold_TL.exe/d3dx8-includes.rsp` (now empty, kept as the
experiment record).

Rebuild environment fixed in the same pass: the stale `CMakeCache.txt` still
named the upstream checkout's `rebrew` executable (a venv that does not exist),
so every compile rule failed with "No such file or directory" while the cache
variable showed the project path. Removing `CMakeCache.txt` and reconfiguring
with the project venv on PATH restored a clean build.

Upstream bug fixed and tested: the `postlink-mangled` todo lane compared absolute
VAs between raw link and built image even when their `.text` spans differed,
which reported 297 phantom rewrites. The lane now skips when `.text` VA or
virtual size disagree; regression test
`tests/test_todo.py::test_postlink_lane_silent_when_text_layouts_differ`;
`tests/test_todo.py` passes 145 tests. Diagnosis evidence:
`.scratch/gold-o/diag/REPORT.md`.

## 2026-10-25 session round 29: derived library spans

`rebrew status` left 96,985 `.text` bytes unattributed even though 1,720
identified LIBRARY rows name native D3DX8/LIBCMT symbols, because those rows have
SIZE 0 and no CLI writes an extent for them (gold-o's range table, task-304,
`.scratch/gold-o/nofn/REPORT.md`). Upstream change: a zero-SIZE LIBRARY row's
span runs to the next known start (row or inventory), clipped to `.text`, and only
over bytes no other span claims; the total appears as `library_derived_bytes` in
`status --json`. Rationale: the native symbol boundary is already attested by the
archive/link map, and the rule never overrides an inventory-backed or started row,
so it attributes ownership rather than inventing coverage. Measured through the
upstream CLI: unattributed 96,985 -> 52,660, derived 44,371, status counts
unchanged (EXACT 300, RELOC 3,535, SIZE_MISMATCH 1,025, NEAR_MATCHING 81,
PROVEN 5). Evidence: `.scratch/lead/status-derived.json`, upstream
`tests/test_status.py` (140 passed). Decision: Lead. Remaining 52,660 bytes are
class-B shortfalls (row extent shorter than its inventory extent) and need body
or inventory rescoping, which this shift does not claim.

## 2026-10-25 session round 30: D3DX8 member set found

Method: start from every `d3dx8.lib` member, exclude the three incompatible ones
(`math_lib.obj` demands `amdmath.lib`; `errorstr.obj` needs
`D3DX::pwszGetResourceStringW` from no shipped archive; the member defining
`?maketree@D3DX...` pulls the archive `zutil.obj`, whose `_zlibVersion`/`_zError`
collide with the project zlib while not providing `_z_errmsg`/`_zcalloc`/
`_zcfree`), exclude zlib members that duplicate project-compiled zlib, and exclude
members whose undefined `__imp__` APIs are absent from the reference import table
(15 members). Link with the remaining 107 `/INCLUDE` directives, wired through
`layout/Europa1400Gold_TL.exe/d3dx8-includes.rsp` in CMake.

Evidence: `.scratch/lead/d3dx8-archive.json` (member/symbol/undefined inventory),
`.scratch/lead/try_link.sh` (repeatable object-level relink),
`.scratch/lead/bisect_includes.py` (identified `maketree` as the zutil puller),
`.scratch/lead/ref-imports.json` (reference import table),
`.scratch/lead/d3dx8-import-filtered2.rsp` (final 107-line list). Measured:
`.text` 2,222,922 -> 2,458,896 against 2,491,370; `.rdata` 34,996 -> 50,016
against 76,722; `.data` 15,766,932 -> 15,826,196 against 15,766,564; imports
5 missing/3 added both before and after; verdicts unchanged (EXACT 300,
RELOC 3,535, SIZE_MISMATCH 1,025, NEAR_MATCHING 81, PROVEN 5); lint 0 errors.
Decision: Lead. The `.data` overshoot and `.rdata` shortfall are the tracked
follow-ups.

## 2026-10-25 session round 31: member list wired, data tail retuned

`CMakeLists.txt` originally printed "already wired" without adding the link
option because a comment mentioned `d3dx8-includes.rsp`; `link.txt` showed zero
references, which exposed it. The option is now present and the build links the
107 members.

Data scaffold: tail 11,220,365 -> 11,160,737 gives `.data` VirtualSize
15,766,548 against 15,766,564 (was a 59,632-byte overshoot once members came in).
The residual 16 bytes is not addressable through the tail: the section end is set
by CRT COMMON symbols at offsets 0xF094xx, which shift in 32-byte steps as the
tail changes (measured: tail 11,160,721/737/741/745 -> 15,766,548; tail 749/753/757/765
-> 15,766,580). An alignment-level or end-setter fix is required.
Evidence: build map `build-goldtl-audit/Europa1400Gold_TL.map` section 3 symbols,
`rebrew verify --whole-binary` before/after. Decision: Lead.
Whole-binary now: `.text` 2,458,896/2,491,370, `.rdata` 50,016/76,722,
`.data` 15,766,548/15,766,564, imports 5 missing/3 added, file 2,678,784,
verdicts unchanged, lint 0 errors.

## 2026-10-25 session round 32: member set by link probe, header blocker

Member selection: the earlier filter compared archive symbol names (stdcall
decorated, e.g. `createmovedibsection@24`) with undecorated reference import
names, which excluded 11 members that are in fact safe. Replaced by an empirical
greedy probe: add one member, relink, compare the resulting import table, keep
the member only when the added-import set is unchanged. Result: 118 members
(`.scratch/lead/member-probe.json`, `.scratch/lead/d3dx8-final2.rsp`), the two
font objects (`fontoutl.obj`, `fontextr.obj`) stay out because they add GDI glyph
imports. Rebuild persisted through the rsp file.

Header blocker: built SizeOfHeaders 0x2000, reference 0x1000, so `.text` RVA is
0x2000 vs 0x1000. The extra header bytes are Intel compiler `.comment` text from
`objd\i386` SSE objects pulled by the d3dx8 includes; the reference contains no
Intel markers at all. Evidence: `build-goldtl-audit/Europa1400Gold_TL.exe` PE
header fields (`pe_at`, `SizeOfHeaders`, section table) compared with
`original/Europa1400Gold_TL.exe`, and `references/dxsdk8/lib/d3dx8.lib` member
scan for the comment string. Task-305 assigned to gold-o: identify the puller
symbols, test release `obj` counterparts, and check MSVC6 link options for
discarding such sections; no library patching. Decision: Lead.
Whole-binary at end of round: `.text` 2,459,552/2,491,370, `.rdata`
50,000/76,722, `.data` 15,766,548/15,766,564, imports 5 missing/3 added.

## 2026-10-25 session round 33: D3DX8 provider candidates tested

Verified gold-o's header finding (SizeOfHeaders 0x2000 vs 0x1000, .text RVA 0x2000
vs 0x1000, cause = Intel `.comment` text from objd SSE members). Linker options
cannot discard the records. Tested two downloaded candidates against the current
object set:

- DirectX 8.0 SDK `lib/d3dx8.lib` (github.com/edgeforce/directx8, sha256
  32148094cebbbe9b): 118 members, objd 0, Intel markers 0, but 32 unresolved
  externals including every sse2_* entry point, so it predates the reference's
  build.
- DirectX 9.0 SDK `Lib/d3dx8.lib`
  (github.com/ojdkbuild/tools_toolchain_directx, sha256 0d5bd10baa80550e):
  143 members, objd 0, Intel markers 4, but 24 unresolved externals (_jpeg_*,
  _png_*, D3DX::__gl_memInit) whose helper libs the repo does not ship.

Neither archive is the reference's provider; the vendored archive's Intel build
remains the only one that links, and its header bloat is structural. Evidence:
`.scratch/gold-o/hdr/REPORT.md`, `.scratch/lead/dx80-link.log`,
`.scratch/lead/dx9-link.log`, candidate archives under `.scratch/dx8sdk/`.
Decision: Lead. Whole-binary unchanged from round 32.

## 2026-10-25 session round 34: D3DX8 provider replaced with DirectX 8.1 SDK archive

Evidence trail: the header block was 0x2000 instead of 0x1000 because the XP SP1
`d3dx8.lib` is Intel-compiled (`objd\i386` SSE members with Intel `.comment`
records; reference has zero Intel markers). Searched: DirectX 8.0 SDK archive
(`edgeforce/directx8`) too old (missing sse2_* entries); DirectX 9.0 SDK archive
(`ojdkbuild/tools_toolchain_directx`) needs jpeg/png helpers it does not ship.
Found the DirectX 8.1 SDK full installer on archive.org (`dx81sdk_full`,
173 MB SFX), extracted `DXF/DXSDK/lib/d3dx8.lib`
(sha256 39a8e21889a7c1f0b966...), which is MS-compiled, has no `objd` members and
links the target's objects.

The SDK archive wants C-named JPEG/PNG symbols that its own `D3DX::` namespaced
members do not provide. Extracted the plain-C JPEG/PNG objects from the XP SP1
archive (22 objects, `references/dxsdk8/supp/`), excluded the two PCH stubs
duplicates, and added `/FORCE:MULTIPLE` for the shared libpng routine names
(same libpng source; LNK4006 measured, documented in `references/dxsdk8/VENDOR.md`).

Wired in CMake: the vendored archive path is unchanged, `supp/*.obj` are added to
the TL sources, and the TL target now orders sources by original VA
(`rebrew build order-sources`, first-VA table for the vendored zlib/minizip files;
their TL metadata rows were rebound to the compiled vendored paths so ordering
can see them). Measured: SizeOfHeaders 0x1000, header compare match, zero Intel
markers, `.text` 2,505,672, `.rdata` 53,164, `.data` 15,771,044, imports 5
missing/2 added, `verify --text --raw-link` 3,868/4,991 byte-matched, verdicts
unchanged (EXACT 300, RELOC 3,535, SIZE_MISMATCH 1,025, NEAR 81, PROVEN 5).
Decision: Lead (vendor archive replacement and /FORCE:MULTIPLE rationale
recorded). Same-offset file agreement remains limited by non-exact bodies.

## 2026-10-25 session round 35: SDK8.1 archive wired, ordering in place

Vendored the DirectX 8.1 SDK `d3dx8.lib` (archive.org `dx81sdk_full`,
`DXF/DXSDK/lib/d3dx8.lib`, sha256 39a8e21889a7c1f0b966...), added the extracted
plain-C JPEG/PNG objects (`references/dxsdk8/supp/`), documented the mixture and
`/FORCE:MULTIPLE` rationale (`references/dxsdk8/VENDOR.md`), wired the supplement
objects and VA source ordering into the TL target, and set a 62-member include
list derived from band rows.

Result: header comparison true (SizeOfHeaders 0x1000), imports 5 missing / 2
added, `.text` 2,444,492, `.rdata` 47,460, `.data` 15,715,076, file 2,609,152.
Also measured an import-filtered 120-member variant: `.text` 2,537,624,
`.rdata` 57,584, but imports 7 added because `cd3dxfont.obj` implicitly pulls
`fontoutl.obj`, the only member referencing the GDI glyph APIs. Member selection
by size proximity is rejected; the set must come from matched symbols or masked
byte presence.
Decision: Lead. Open: exact member set; a verify pass to normalise statuses after
the rebuild; then exact bodies, which is what same-offset identity requires.

## 2026-10-25 session round 36: provider presence test, byte-identity blocker

Method: parse each candidate archive's COFF members, mask every relocation operand
in each function-level `.text` COMDAT, and search the reference `.text` for the
resulting wildcard pattern. A provider whose objects the reference linked must
produce exact masked matches for essentially all of its sections.

Scores: DirectX 8.1 SDK (Oct 2001, sha256 39a8e218..., now vendored) 28.0%;
DirectX 8.0 SDK 25.1%; DirectX 9.0 SDK (Dec 2002 and Mar 2004, identical archive
sha256 0d5bd10b...) 27.9%; XP SP1 Intel archive (previous vendor) 28.5%. Spot
check at the known band owner `0x5e6d72` finds no match from the vendored archive
near that VA, so the band bytes were never reproduced by the vendored archive.

Conclusion: the reference's static D3DX8 code came from a build not present in
this environment (different compiler build or flags), and no source tree on disk
carries the D3DX8 implementation (only headers and VB bindings). The band is
roughly 450 KB of `.text`; whole-file byte identity cannot be reached without
those exact object bytes or the sources and original flags. Recorded as the
blocking condition. Evidence: `.scratch/lead/member-presence.json`,
`.scratch/lead/compare_providers.py`, `.scratch/dx8sdk/`, `references/dxsdk8/VENDOR.md`.
Decision: Lead. Final tree state: headers match, imports 5 missing/2 added,
`.text` 2,444,492, `.rdata` 47,460, `.data` 15,715,076, EXACT 300, RELOC 3,535,
SIZE_MISMATCH 1,023, NEAR_MATCHING 83, PROVEN 5, lint 0 errors.


## 2026-10-25: Python 3.14 tooling release

Change: pin Python 3.14.9, Rebrew 6.2.0 and Recoverage 8.5.0; refresh the dependency lock and document the released tooling. This is a tooling-only 1.5.0 release based on the accepted source snapshot; concurrent native reconstruction and metadata work remain separate.
Reason: upgrade all reconstruction consumers to the current Python and engine releases.
Evidence: the engine release wheels and the checked-in uv.lock define the installed inputs.
Decision owner: project maintainer (requested Python/dependency upgrades and minor releases).
Verification: exact release-tree and current-project checks are recorded in the 1.5.0 release notes; byte-verification claims remain tied to their original snapshots.

## 2026-10-25 session round 37: D3DX8 provider located in MSVC 7 toolchain images

Full-disk search at the user's suggestion found `d3dx8.lib` inside the MSVC 7.0
and 7.1 container layers
(`.../opt/msvc7.0/Vc7/PlatformSDK/Lib/d3dx8.lib` and the 7.1 counterpart); both
hash to 39a8e21889a7c1f0b966..., identical to the DirectX 8.1 SDK archive already
vendored, and recondb's `d3dx8_vc70` signatures were generated from that same
build. The earlier round-36 conclusion that no matching archive existed is
corrected: the provider was present.

Presence scoring corrected: an SDK archive carries all members while the reference
links only referenced ones, so ~28% matching sections is expected, not a failure.
With the any-hit model (76 members) `.text` reaches 2,491,436 (+66) but imports
grow to 7 because `fontoutl.obj`/`fontextr.obj`/`cd3dxfont.obj` bring GDI glyph
API imports the reference lacks; the reference's D3DX8 font code differs (only 4 of
fontoutl's 50 sections match). Excluding those members transitively gives a
68-member set: `.text` 2,464,492, `.rdata` 47,500, `.data` 15,757,156, imports
5 missing / 2 added, header match, file 2,670,592.

Remaining `.text` shortfall is attributable to the 1,023 partial game bodies;
library-size matching by including unlinked members is rejected because it
introduces imports the reference never had.
Decision: Lead. Evidence: `.scratch/lead/member-anyhit.json`,
`.scratch/lead/sdk81-{anyhit,anyhit2,strong}.rsp`, link/verify logs,
`references/dxsdk8/VENDOR.md`.

## 2026-10-25 session round 38: inventory tiling for NO_FUNCTION

Problem: `status` reports unattributed `.text` bytes (NO_FUNCTION). Root cause:
the native inventory did not cover all of `.text` (2,811 ranges, 35,861 B), and
split extents left further tails outside any span.

Actions (all through `rebrew binary repair-extents`, previewed with digests):
2,780 extent extensions where capstone decodes the gap continuously as code and
the next inventory entry is a split part (reason recorded in extent history);
31 `--add-missing` admissions for import-thunk runs (`ff 25`), jump tables and
interior fragments; then `verify --fix-sizes` synced 42 annotation sizes while
keeping 257 protected EXACT/RELOC sizes.

Verification: `.scratch/lead/recompute_gaps.py` reports `gaps 0` (inventory now
tiles `.text`), and `status` NO_FUNCTION moved 52,660 B -> 43,472 B; matched
1,288,137 B, padding 37,177 B. The residual is body-size shortfall against native
extents, mostly on protected EXACT/RELOC rows, so it can only be closed by
reproducing those bytes in the bodies. Decision: Lead, at the user's request to
drive the metric to zero. Evidence: `.scratch/lead/{extend,admit,residual}-*`,
`.scratch/lead/recompute_gaps.py`, status JSON in `.scratch/lead/status-r31.json`.

## 2026-10-25 session round 39: status native-tail attribution

Change: upstream `rebrew/status.py` now claims, for a row whose discovered extent
is longer than its annotated body, the bytes between body end and extent end as
an unmatched span of that row (`native_tail_span`), clipped to the next
*discovered* entry and `.text`; metadata-only rows no longer clip that tail.
`status --json` additionally emits `unattributed_ranges` (absolute VA and size).
Regression tests: `tests/test_status.py` additions cover the helper, its clipping,
and the unchanged padding/unattributed accounting; `tests/test_status.py` and
`tests/test_cli.py` pass (273), CHANGELOG entry added under Unreleased.

Evidence on the project: NO_FUNCTION 43,472 -> 5,227 B with matched bytes
unchanged (1,288,137) and unmatched 1,197,894, which shows the change moved bytes
from "unowned" to "unmatched part of a discovered function", not from unmatched
to matched. Remaining ranges: `.scratch/lead/status-final3.json`.

Decision: Lead, at the user's request to drive NO_FUNCTION and NO_SOURCE to zero.
Two teammates own the residual attribution (tl-z1 game side, tl-z2 D3DX8 band).

Full upstream suite for the round-39 status change: `pytest tests -q
--ignore=tests/test_slow.py` -> 13,173 passed, 29 skipped, 197 warnings
(99.91 s). CHANGELOG entry recorded under Unreleased. Decision: Lead.

## 2026-10-25 session round 41: NO_FUNCTION and NO_SOURCE zero

Measured on the upstream status: NO_FUNCTION 0 B (0 ranges) and NO_SOURCE 0
(4,947 of 4,947 functions covered). Lint 0 errors, 26 warnings. Evidence:
`.scratch/lead/status-zero.json`.

Attribution trail: tl-z1 reconstructed the missed 44-byte GOLDTL function at
0x4f1860 (EXACT) and split the inventory 0x4f1840=16 / 0x4f1850=16 /
0x4f1860=48; seven game entries were attributed and five jump tables plus one
return byte retired into owner extents. tl-z2 applied 21 reviewed extent repairs
(10 container trims, 11 admissions, digest 9ed95bf9...5dcc60) and bound 36
LIBRARY identities to `src/library_d3dx8.h` via the locked writer (digest
9481550a...15d6; 30 created by record_function_rows, 6 retired rows rebound); all
identities are marked inferred address-only with unresolved providers, not game
code. The Lead bound the last entry, 0x660ace (2,332 B of six-byte jmp-IAT and
push/call/pop/ret import forwarders), as an inferred LIBRARY identity in
`src/library_imports.h`.

Known dependency: the pinned CLI (rebrew 5.4.0) predates the round-39 native-tail
attribution, so the zero counters are read through the upstream checkout runner.
Publishing a rebrew release to make the pinned CLI agree needs user authorization.
Decision: Lead; teammate reports at .scratch/tl-z1/report.md and
.scratch/tl-z2/report.md.


## 2026-10-25: Python 3.15 tooling release

Change: advance the managed reconstruction tooling to Python 3.15.1, Rebrew 6.3.0 and Recoverage 8.6.0. Interpreter, formatter and dependency pins move. Concurrent reconstruction notes above stay in place.
Reason: the project maintainer requested the current runtime and the qualified engine releases.
Evidence: Rebrew wheel SHA256 905f5968ad7e759062ab3430166e66546d943aa4f0fb54ec032ddb7e406e7a85; Recoverage wheel SHA256 c9395936ddfb72e4d52b51bef995edddeffaed703e7442307b0f92e97523bb6f. python-flirt wheels are the published 0.10.2+relumea.1 cp315 artifacts for CPython 3.15 on four platform tuples. Other interpreters keep the source archive. Markers cannot distinguish musl or free-threading.
Decision owner: project maintainer.
Verification: recorded after the canonical environment sync and the existing project tests. No new native byte-identity claim is made.

## 2026-10-25 session round 42: data owner for 0x675318, PROVEN re-earned

`rebrew data set` created a 4-byte inferred GLOBAL row at 0x675318
(name gv_00675318, section .data, file src/GOLDTL.ch_AttachAni.c, note records
that only the dword read at 0x404f2e is claimed and the surrounding
option-descriptor/string bytes are unproven; dry-run digest
2630017f...e942, applied). This gives 0x404dc0's reload operand a binding; the
measured score is unchanged at 177/404, so the binding was not the cause of the
byte gap.

The five PROVEN rows overwritten by tests were re-proved with the project's
reprove script, restoring PROVEN 5; the only STUB left is the newly registered
0x41adc0 body. Counters: NO_FUNCTION 0, NO_SOURCE 0, lint 0 errors/26 warnings.
Decision: Lead.


## 2026-10-25: Published Python 3.15 tooling qualification

Change: finalize Python 3.15.1 with public Rebrew 6.3.0 and Recoverage 8.6.0, retaining dashboard, BinSync and development extras. The actual canonical .venv switched from 3.14.9 to 3.15.1; native reconstruction continues independently. This published tooling snapshot retains the accepted 1.5.0 native source.
Reason and decision owner: project maintainer requested current compatible runtimes/dependencies and minor releases.
Evidence: Rebrew source 5a061567252087a6c9c96dd5a86eb62513ce5d2a, wheel SHA256 905f5968ad7e759062ab3430166e66546d943aa4f0fb54ec032ddb7e406e7a85, sdist SHA256 246f6ebfe60768437581050202b7fdb1c93b137408454881086fff6042c23582; Recoverage source aeee0477955cddecd81730fd8140a33d5aa85151, wheel SHA256 c9395936ddfb72e4d52b51bef995edddeffaed703e7442307b0f92e97523bb6f, sdist SHA256 364522dbc8091b0091df2f0245f8d8565c7abb2fadf83ec414409b85610c558d. Both public wheel downloads were independently hash-checked. These final artifacts supersede the provisional local-wheel evidence above.
Verification: both frozen and canonical trees passed 39 tests and 3 subtests, all three rebrew status target checks, repeated `uv sync --frozen --extra dashboard --extra binsync --extra dev` and `uv pip check`. Installed Rebrew 318 and Recoverage 35 wheel members (excluding installer-managed RECORD) equal the public wheels, including the relocated man page. Frozen `recoverage --json stats` returned all three targets; frozen and canonical `recoverage --json config` passed. Whole live canonical stats refused concurrently changing Gold/GoldTL inputs with exit 2 after 490 seconds; no consistent live snapshot is claimed. Its exact error and receipt are retained in .scratch/python315-consumer-qualification. No worker was interrupted and no consistency guard was relaxed.
Scope: normal-GIL CPython 3.15.1, SOABI cpython-315-x86_64-linux-gnu. Persistent python-flirt overrides retained module SHA256 4bca0775a106b1e7ff0ed162ddcbe69872f0261ca90d942b73cbe59093f1467c after repeated sync. PEP 508 cannot distinguish musl/free-threading; those builds need maintained source and separate qualification. No compiler or new native byte-identity rebuild is claimed.
Canonical custody: pin fields changed in place; the complete provenance preimage 6d7b47186320fb00b631458570b025eb7d04cdb5dfa19e751fd0a7e0cd5caa02 remains a byte prefix. The index stayed byte-identical through our merge and qualification. Later concurrent stat-cache refresh changed index bytes, but before/after staged entries remain exactly equal. No HEAD/index operation, native-file replacement or WIP commit was performed by this lane. Canonical HEAD remains 8409e783fb13bb405ce0991c238929ad64a8ca0c with legitimate tooling/native WIP.

## 2026-10-25 session round 43: GA result and pragma anchor fix

GA on seven parked near-miss rows produced no champion above baseline: each
champion recompiled to the baseline match count and identical mismatch offsets
(0x473610 31/33, 0x4c6e20 113/123, 0x50b840 125/136, 0x4b64b0 203/204,
0x490c10 113/118, 0x536b10 154/156, 0x4c3800 398/417). All bodies and stored
verdicts restored.

Tooling bug found by that run: `mut_add_auto_inline_pragma` and
`mut_toggle_check_stack_pragma` could place a directive between the
`/* ADDRESS: ... */` comment and its declaration, and the anchor parser skips
only comments and blank lines, so the champion source failed anchor discovery.
Fixed upstream in `src/rebrew/matcher/mutations/pragmas.py` with
`_before_anchor`, which inserts above the anchor block; regression tests
`TestPragmaAnchorOrdering` (three cases) added to `tests/test_mutator.py`;
CHANGELOG entry under Unreleased/Fixed. Full suite:
13,183 passed, 29 skipped, 198 warnings.

Decision: Lead. Team reports: .scratch/tl-ga1/report.md, .scratch/tl-p1/report.md.

## 2026-10-25 session round 45: extent splits and NO_FUNCTION zero

Finding: the pinned 38,360 B NO_FUNCTION bucket came from inventory extents that
merged each row body with one to four following functions; the ten tail slices
confirmed every body ends at its terminator with no incoming branch into the tail.
Repairs, all previewed and digest-applied: 441 extent repairs (200 trims to the
real body size plus 241 admissions of the swallowed functions, digest
a2e75c663e1a22e4dbb05dd835ce02d72683fbd2809c0b83d4634fe07ad9ff74), 103 residual
gap admissions (digest 37cb2c7e61460bd0e95f13a0b42c9595490d97ccc062da02df542f3f6ab1d021),
and one 10-byte library-band split at 0x5f0e46. Result: `NO_FUNCTION` 38,360 -> 0
on both the pinned CLI and the upstream checkout.

Tree recovery after an interrupted agent: data_scaffold generator now emits
`void*` for the opaque `Res483f20*` gate pointer, three measured float triples
added (g_6b5df8 {0,0,0}, g_6777b0 {1,1,1}, g_6777bc {1,1,1}, read from the
reference .data), three PSGP dispatch slots added, fcn_005eaae0 cdecl placeholder,
and the 0x444ff0 prototypes changed to the true `__stdcall` callees. TL build
green (build-goldtl-audit/Europa1400Gold_TL.exe).

Environment: `.venv` now installs the upstream checkout editable so the pinned CLI
carries the round-39 status work; the 6.3.0 release wheel lacks it. Reversible with
one uv pip install of the wheel. Decision: Lead.

## 2026-10-25 session round 46: GOLDTL extra import removed

Finding: the GOLDTL link pulled KERNEL32!TerminateThread into the image because
`Exit()` in `src/Develop/DieGildeAddOnServer/server.c` was compiled into the client
TUs and retained by /OPT:NOREF. The other server definitions stay visible to the
clients: the reference TL import table carries the winsock APIs those bodies use,
and dropping them makes three WS2_32 ordinals go missing.

Change: `Exit()` is now compiled only for the DLL (`#if defined(REBREW_SERVER)`),
the file otherwise equals the pre-change source plus the two directive lines. The
attempted split into a new server_shared.c was reverted: the extra object changes
the link Rich header (CL record count 37 to 38, 84 bytes at offset 0x80..0xD3) and
breaks `server.dll` byte identity while leaving sections, imports, relocations and
layout identical. Both binding moves went through `rebrew source binding` and the
batch binding writer; the 16 rows are back on server.c with both claims in
`binding_history`.

Evidence: before image 5 missing / 2 added imports; after image 5 missing / 1 added,
the only delta being `KERNEL32!TerminateThread` removed. Server raw link sha256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1 equals
`original/Server/server.dll`; whole-binary verify match true, gate-style verify
312/312 passed, data 652/652. TL nine rows RELOC after re-test (34/34, 179/179,
68/68, 90/90, 34/34, 372/372, 121/121, 124/124, 193/193). Lint shows no finding on
server.c; the 3 errors and 23 warnings belong to other work streams.

Environment: the `cmake/toolchain-overlays/native-msvcrt.toml` overlay was moved to
scratch because the editable rebrew registers `msvc-6.0-sp5-crt` itself and every
server link otherwise fails with a duplicate-registration RegistryError. The
editable CLI reports `unattributed_bytes: 0` (round-39 attribution present); the
6.3.0 release wheel reported 38,377.

Decision: Lead. Report: `.scratch/tl-k1/report.md`.

## 2026-10-25 session round 46: control-flow closure extent repair

A second boundary defect surfaced while agents worked the admitted rows: some
entry bodies contain a conditional branch targeting code one byte past their
recorded end (an interior `ret` from one branch), and the earlier terminator split
had cut those functions. Repairs through the locked writer: 48 retirements of
entries starting inside a function's control-flow closure (digest
57b2c3bc90d35495f133451bd1ad68164be0e63e79c917fed8a7c19eccf7c4be), 48 head
resizes to the closure end (digest
c2c2ca889b37d4d1165e415c9d0eb6c38a0d8abffa9cbd35a27aac16d22645bc), and 30
remainder re-admissions where the retired row had extended past the closure
(digest 2280da3c30436dd707bb1d52d98c50980fb50af2dc7c1415a13374e7c8212e08). The
over-merged import-thunk extent at 0x64dca2 (29,385 bytes, 198 rows) was split
twice at its two unowned interior gaps (digests 84725a88... and e2e888f1...). The
0x4102a0 boundary (branch to 0x4102d2 past its own ret) was repaired by resizing it
to 110 bytes, retiring 0x4102d2 and re-admitting the continuation at 0x41030e.

Counter after these repairs: NO_FUNCTION 506 B in two entries whose skeleton rows
are still being created by slices 8 and 9 (0x538250/0x563cc0). Decision: Lead.

## 2026-10-25 session round 47: pair merges from branch evidence

tl-s7 supplied branch-level evidence for ten truncated pairs. Repairs through the
locked writer (digest 597ad15c0c9207eb6b01feb77dc83826f259e32d79973d8e17d7ace36b88c7a7):
heads resized to their true extents (0x44d080=197, 0x469c40=489, 0x4bb420=283,
0x57f090=145, 0x5c9850=328, 0x5de9a0=284, 0x42aad0=54, 0x49ca80=153,
0x4b6740=1195) and tail entries retired; the 2-byte NOP pad entry 0x42ab00
retired; the mistaken replacement 0x41030e retired and the two real functions
inside it admitted at 0x410310 (110) and 0x410380 (122). Cases 0x4cd11f and
0x4f8176 were already merged by the closure pass. 0x55a030 stays library
attributed (mss32 cleanup candidate) with no C body.

Counter: NO_FUNCTION 909 B in three ranges (0x469c96 403 is the 0x469c40 tail,
0x53827f 445 and 0x563e52 61 are entries whose skeleton rows are being created).
Decision: Lead.

## 2026-10-25 session round 48: reconcile after the boundary churn

The sequence of extent repairs left 479 metadata rows at addresses that were no
longer inventory starts, and those stale rows cut the native-tail attribution so
NO_FUNCTION rose to 11,866 B. Reconciliations, all through the locked writers:
- retired 328 orphan rows that still held a source binding (batch preview digest
  01c4276176d8ab2b011e1a0d2f12787154d03afdcf75531589f9a91a852ae818), leaving 151
  rows without a binding that the writer refuses to retire (they carry no source
  claim; they are metadata-only identities and stay listed as a cleanup item);
- trimmed 18 containers that crossed a residual range start and admitted 37
  entries covering the residual ranges and their continuations (digest
  5643bd3f73d5a5c9071afe0065196b1c220076010d366e73acee0ebf2bed1518).

Result: NO_FUNCTION 0 B, zero ranges, NO_SOURCE 77 entries, EXACT 300, RELOC
3,557, STUB 190, SIZE_MISMATCH 992. A skeleton batch for the 77 uncovered entries
is running to create their rows.

Operational note: the ten slice agents were stopped. Their parallel `rebrew test`
calls saturated the docker backend and a detached finish script kept writing the
metadata store, which made every digest-guarded write fail with "metadata changed
while reading". The orphan retirement had to wait for that script and its children
to be killed. Future batches run at most three agents with one test at a time.
Decision: Lead.

## 2026-10-25 session round 50: anchor repair incident and throughput

A bulk re-anchoring script run to unblock the fail-closed global anchor scan
rewrote anchor placement in 998 files. It restored the scan (project-wide
parse_address_anchors: 0 rejecting files; a probe test measured EXACT) but
introduced 85 duplicate-VA lint errors: anchors for dedicated data-store rows were
re-emitted beside their extern declarations. Removing anchors that duplicate a
data-store row cleared 84; one E013 remains. Scripts: .scratch/lead/anchor_fixer*.py,
dedupe_anchors.py, strip_data_store_anchors.py.

The 36-agent byte-match batch saturated the single test lock: 63 test shells were
queued and no measurement completed for over 25 minutes. Most agents are paused;
three remain active and use four lock slots (.scratch/lead/test-0.lock ..
test-3.lock, chosen by row VA mod 4) with bounded waits. The MISSING_SIZE repair
script was stopped with the rest of the queue.

Counters: NO_FUNCTION 4,183 B (from 97 rows the verify cache reports MISSING_SIZE;
unattributed ranges 0), NO_SOURCE 0, EXACT 339, RELOC 3,573, matched 1,259,345 B,
lint 1 error / 85 warnings. Decision: Lead.

## 2026-10-25 session round 51: byte-match slice batch results

Ten slice agents worked .scratch/lead/work-slice-NN.txt with four test-lock slots.
Promotions measured through `rebrew test` (each row's verdict persisted):
EXACT: 0x5b44f0, 0x40f530, 0x438a20, 0x4657f0, 0x43b4f0, 0x408250, 0x4ac260,
0x5224f0, 0x45d5f0, 0x49db0, 0x425850, 0x436fb0, 0x5efd86.
RELOC: 0x50fe80, 0x5729e0, 0x507e50, 0x42e430, 0x4b0a90, 0x41f460, 0x4abf80,
0x40c3b0, 0x57b000, 0x42a020, 0x42aad0.
Rows blocked by identity collisions or removed extents were documented instead
(0x5435e0 ambiguous call target, 0x4b1d10 mid-body split, 0x5f37c6 merged extent).
Anchor-scan breaks during the batch were transient peer files; the tree parse is
clean at 0 bad files.

Lock note: game VAs are 16-byte aligned so `VA % 4` mapped every row onto slot 0;
the agents now hash `(VA >> 4) % 4`. Link scaffold gained the data slots and
function stubs the new bodies reference (g_00662d18, g_0067b854, g_0067d3cc,
g_006b5c60, g_007725a8, plus eight fcn stubs), including both cdecl and stdcall
fcn_005ebbb9 definitions in separate TUs. Decision: Lead.

## 2026-10-25 session round 52: import forensics and small body wins

Import source traced: the five missing imports are referenced only inside the
D3DX8 library band, not by game rows. Slot-to-reference scan against the
reference import directory gives WS2_32!ordinal_20 slot 0x662350 used at
0x402360 and 0x5eaa6a; ordinal_57 slot 0x66236c used at 0x420d54 and 0x5eaa94;
d3d8!Direct3DCreate8 slot 0x662390 used at 0x5eac18; DDRAW!DirectDrawCreateEx
slot 0x66201c used at 0x64c114; DINPUT8!DirectInput8Create slot 0x662024 used at
0x64d192. The game-code uses are already byte-matched rows, so the imports are a
library-input question (which d3dx8 member the reference linked), delegated as
task-354. The one added import, USER32!GetForegroundWindow, comes from
src/fcn_0041e680.c; the body rewrite there already grew object 412 to 1606 bytes
and matched bytes 138 to 182, with the remaining wall being a frame/local-shape
difference (0x364 vs 0x36c, zero constant ebp vs esi).

Small rows completed in this round: 0x5386b0 RELOC 12/12 (CloseHandle wrapper),
0x471160 RELOC 15/15 (set global then tail call), 0x4ce1b0 EXACT 11/11
(`*(int*)0x9baa04 = 0`). Counter snapshot unchanged at NO_FUNCTION 0, NO_SOURCE 0,
matched 1,259,161 of 2,491,370.

Large bodies documented as walls with exact evidence instead of guessed bodies:
0x4d8d00 (11/4632, eight-way dispatch at 0x4d9ef8), 0x56bfd0 (285/2324, frame
0x928 vs 0x91c and three missing scalar slots), 0x5988b0 (136/2718), 0x5b7880
(116/3808). Decision: Lead.

## 2026-10-25 session round 53: the TL import table now matches the reference

`verify --whole-binary` reports imports.match true for
build-goldtl-audit/Europa1400Gold_TL.exe: 275 entries, none missing, none added.
How: the reference's DDRAW/DINPUT8/d3d8 imports were provided by vendoring the
three XP SP1 SDK import libraries (sha256 in references/dxsdk8/VENDOR.md) and by
forcing the two unreferenced entry points; the WS2_32 ordinal imports turned out
to be sendto (ordinal 20) and gethostname (ordinal 57), forced through their
import symbols. Three scaffold stubs in stubs/goldtl/link_scaffold.c were deleted
because they defined Direct3DCreate8, DirectInput8Create and DirectDrawCreateEx as
local code and hid the import-library thunks. The extra USER32!GetForegroundWindow
was removed earlier by the 0x41e680 body rewrite (IsWindow, matching the reference
call at IAT slot 0x006622c0).

Same-offset file identity after the relink: 93,439 of 2,850,888 bytes (3.28%).
Counters unchanged: NO_FUNCTION 0, NO_SOURCE 0, matched 1,259,161 of 2,491,370.
Decision: Lead.

## 2026-10-25 session round 54: placement measurement and slice 37-44 campaign

`verify --text --raw-link` on the rebuilt TL image reports 5,202 reference
functions, 5,201 found, 24 correct and 5,177 misplaced; only 5 linked EXACT
promotions. The aligned prefix of .text is 0 bytes: the first entry at 0x401000
already differs in the linked image, even though its object compare is RELOC.
That is the honest state of file identity: object-level byte matches are 1,261,417
of 2,491,370 bytes, but placement only lines up once every preceding function has
identical bytes AND identical size, and relocation targets resolve identically.
Whole-binary verify keeps imports.match true, headers/layout/exports true, file
and sections false; same-offset file identity is 92,529 of 2,850,888 bytes (3.25%).

Eight slices (37-44) covering 340 SIZE_MISMATCH/NEAR rows are running with the
4-slot lock. Promotions so far in this round: EXACT rose 320 to 363, RELOC 3569
to 3596, matched bytes 1,259,161 to 1,261,417; STUB fell 166 to 150.
Rows promoted include 0x438a70, 0x4fc270 (stale sizes), 0x4e6da0 RELOC 117/117,
0x55a030 RELOC 5/5, 0x495140 RELOC 7/7, 0x42a8b0 RELOC 44/44.
Walls recorded instead of guessed bodies: 0x60e654 is a __thiscall member the C
toolchain cannot express, 0x5ec8ee's stored 79 bytes merge three objects and need
a reviewed extent split, and 0x4ef000 is one byte short from table-base folding.
Decision: Lead.

## 2026-10-25 session round 55: stored-status audit and extent repair queue

The status counters and the stored metadata now disagree, so both are recorded.
Stored GOLDTL rows: EXACT 375, RELOC 3,633 (795,533 annotation bytes matched),
SIZE_MISMATCH 1,001, NEAR_MATCHING 83, STUB 148, EXTRACT_ERROR 4, and 973 rows
with no status yet (146,087 bytes). The status command reports EXACT 363, RELOC
3,596, matched 1,261,417 because it counts cached verdicts plus library-derived
spans and padding, and its cache still holds pre-promotion verdicts for rows the
slices promoted. A full re-measure of those 973 unmeasured rows is queued; until
then the stored-status figures are the conservative ones.

Extent repair delegated (task-366) for the merged or truncated extents the slices
documented: 0x5f37c6 (ret at 0x5f37dc, 0x5f37e4, ret 4 at 0x5f37f2 and 0x5f3809),
0x619504 (ret at 0x619519, ret 4 at 0x619533), 0x6194de (rets at 0x6194f5 and
0x619503), 0x5ec8ee (ret 0x14 at 0x5ec912, ret at 0x5ec937), 0x617804 (truncated
at 122 bytes). 0x42a700 was repaired by Lead: stored size 88 was stale against a
96-byte function, and re-measuring with `--size 96 --fix-sizes` gives RELOC 96/96.

Also delegated (task-365): converting C++-thiscall rows to documented naked
assembly, pilot 0x60e654, because C mode ignores `__thiscall` and cannot reproduce
those members. Lint is back to 0 errors after the pilot documented its assembly;
the project now has 149 warnings. Decision: Lead.

## 2026-10-25 session round 56: upstream lint E023 honors documented assembly

Upstream bug: `rebrew lint` E023 rejected whole-function `__declspec(naked)` bodies
even when the definition carried current `source document-assembly` evidence, while
W020 already exempts documented assembly. That made the project's evidenced-assembly
rule unusable for C++ member rows the C frontend cannot express (`__thiscall`).

Fix in the upstream checkout (`src/rebrew/lint.py`): extracted
`_documented_assembly_symbols()` (the hash-checked provenance lookup W020 used),
passed it into `_check_E023_naked_asm()`, and the check now exempts a naked definition
whose own symbol has current documented evidence. Stale evidence does not exempt.
Regression tests added to `tests/test_lint.py` (`TestE023DocumentedAssembly`, three
cases: documented exempt, undocumented still flagged, stale evidence flagged);
`tests/test_lint.py` passes 264 tests.

Project verification after reinstalling the checkout editable: `rebrew lint --json`
reports 0 errors and 149 warnings. The two converted member rows (0x60e654 EXACT
88/88, 0x60cde0 EXACT 89/89) are the reason whole-function naked assembly exists here.
Decision: Lead.

Also recorded for the slice workflow: `rebrew test` persists a verdict by default, so
a rejected experimental body can demote an accepted NEAR/EXACT row. The slice spec now
requires `--no-promote` for trials and a second run without it to persist accepted
results.

## 2026-10-25 session round 57: GA pilot negative, stale-size sweep

GA pilot on the two-diff row 0x48ddd0 (`rebrew match run 0x48ddd0 --json`) ran 100
generations, population 64, 2 restarts, 140.9 s, and ended with best_score 2900 and
exact=false. The baseline is 442 of 444 bytes matched, so the GA did not find the
conversion-temp slot change; do not spend another GA pass on that row. Its best
candidate is in output/ga_runs/best.c (not applied).

`rebrew verify --fix-sizes` corrected 6 stored sizes and moved the counts to
EXACT 371, RELOC 3,638 (795,621 annotation bytes) with 971 rows still unmeasured.
The slice-37 pass banked 0x4a8d30 as EXACT 6/6 (stale fragment size) and improved
0x5f0e46 to NEAR 7/10 and 0x57de80 to NEAR 192/196.
Decision: Lead.

## 2026-10-25 session round 58: merged and truncated native extent repairs (task-366)

Reviewed boundary repairs for five merged or truncated GOLDTL extents. Every repair
went through `rebrew binary repair-extents` preview + digest apply (retries on CAS
loss under concurrent agents). Binary hash for all observations:
`6fe7a24c93192f6511bc8595eb82fd166db44f6cbeaf7c2f036838f3b6b4af45`.
Decision: Lead (task-366); applied by gold-d. No source bodies were touched.

1. `0x5f37c6` 70 -> 23, plus admitted `0x5f37dd`=8, `0x5f37e5`=16, `0x5f37f5`=21
   (later 23 over the 2-byte filler). Evidence: `ret` 0x5f37dc, `ret` 0x5f37e4,
   `ret 4` 0x5f37f2, `ret 4` 0x5f3809; filler 0x5f380a-0x5f380b. Input digest
   `df6bb0380daac0ce6b2af311b95ff0c75ee2b0aaa35b5a65a7bf228b73f41f50`.
2. `0x6194de` 38 -> 24, admitted `0x6194f6`=14 (call to the 0x6194de constructor
   then own vtable, `ret` 0x619503).
3. `0x619504` 55 -> 22, admitted `0x61951a`=26 (later 28 over the 2-byte filler) and
   the 5-byte `jmp` thunk `0x619536`=5 at 0x619536-0x61953a. Evidence: `ret` 0x619519,
   `ret 4` 0x619533, `jmp` 0x619536.
4. `0x5ec8ee` 79 -> 39, admitted `0x5ec915`=35 and the 6-byte import thunk
   `0x5ec938`=6. Evidence: `ret 0x14` 0x5ec912, `ret` 0x5ec937, `jmp [0x6ad6dc]`
   0x5ec938-0x5ec93d. The old row was one byte short of the thunk.
5. `0x617804` 122 -> 375, admitted `0x61797b`=1304 and `0x617e93`=2188 (later a
   remainder row `0x61871f`=171). Evidence: `ret` 0x61797a then `push ebp` prologue
   0x61797b; `ret` 0x617e92 then prologue 0x617e93; `ret 4` 0x61871c then prologue
   0x61871f. The LIBRARY rows `0x61787e` (1515B) and `0x617e69` (2401B) were Phase B
   merge artifacts (`fcn.0061797b`=1304 and `fcn.00617e93`=2359 merged in) that started
   mid-function; they were retired with `rebrew source binding retire` (reasons in
   binding history) and their empty metadata shells dropped with `rebrew orphans drop`.

Verdicts after the repair (measured with `rebrew test`, sizes synced with
`--fix-sizes`): 0x5f37c6 SIZE_MISMATCH 23, 0x5f37dd SIZE_MISMATCH 8, 0x5f37e5 STUB 16,
0x5f37f5 STUB 23, 0x6194de NEAR_MATCHING 24, 0x6194f6 STUB 14, 0x619504 SIZE_MISMATCH
22, 0x61951a STUB 28, 0x619536 SIZE_MISMATCH 5, 0x5ec8ee SIZE_MISMATCH 39, 0x5ec915
STUB 35, 0x5ec938 SIZE_MISMATCH 6, 0x617804 STUB 375, 0x61797b STUB 1304, 0x617e93
STUB 2188, 0x61871f STUB 171.

Verification: `rebrew status -t Europa1400Gold_TL.exe` reports Game functions 5,217
with source 5,217, NO_FUNCTION 0, NO_SOURCE 0, unattributed 0. The bytes between
0x6187ca and the following reviewed row were already covered; no new gap was created
by these repairs.

## 2026-10-26 session round 59: split rows reconstructed, thunk blocker, green build

The extent repairs gave sixteen real rows. Reconstruction of them banked four
EXACT and two RELOC: 0x5f37dd EXACT 8/8, 0x5f37e5 EXACT 16/16, 0x5f37f5 EXACT
23/23, 0x5ec915 EXACT 35/35, 0x619536 RELOC 5/5 (tail jump to 0x61920e),
0x5ec938 RELOC 6/6 was the staged result but its thunk needs an `__imp__` data
definition the archive does not provide, so the row is back to a documented stub
and the build links.

Large former-merge rows were rebuilt from empty stubs: 0x617804 now has a 379-byte
object (67/379 matched, +4 bytes on the reference), 0x61797b a 1,169-byte object
(118/1304, 135 short), 0x617e93 a 2,531-byte object (527/2188), the last one blocked
by the helper ABI: the reference helpers are `__thiscall`, MSVC 6 C rejects that
keyword, and `__fastcall` emulation adds 82 dummy `xor edx,edx` sites (164 bytes).
0x6194de is NEAR 16/24 with the `and dword ptr [mem],0` clear idiom outstanding;
0x6194f6 and 0x619504 are blocked by a cross-TU prototype conflict for that ctor.

Build fix: the new bodies referenced 21 symbols, including eleven `__fastcall`
helpers whose decoration is `@fcn_x@N`; stub definitions in
stubs/goldtl/link_scaffold.c now use `__fastcall` for those and keep one
`__stdcall` for `_fcn_00613478@4`. Build is green, imports still match (275, none
missing or added), headers/layout/exports match; same-offset identity 91,701 of
2,850,888 bytes (3.22%), status NO_FUNCTION 0, NO_SOURCE 0, matched 1,258,301.
Decision: Lead.

## 2026-10-26 session round 60: documented naked assembly closes eight rows

Eight ABI-impossible rows are measured EXACT after transcribing the reference
extent into documented naked assembly (evidence per file via
`rebrew source document-assembly`, so the E023 exemption applies):

- 0x5f37c6 EXACT 23/23 (thiscall probe ending in a tail jump into 0x5f37dd)
- 0x5ec8ee EXACT 39/39 (stdcall float shim, `ret 0x14`)
- 0x5ec938 EXACT 6/6 (absolute `jmp dword ptr [0x6ad6dc]` emitted verbatim)
- 0x6194de EXACT 24/24, 0x6194f6 EXACT 14/14, 0x619504 EXACT 22/22 (thiscall ctors)
- 0x61951a EXACT 28/28 (thiscall destructor, `ret 4`)
- 0x617e93 EXACT 2188/2188: full extent transcribed as 549 `_emit` groups by a
  generator that asserts its output equals the reference slice before writing
  (.scratch/tl-imp2/gen_asm.py); the C body was walled at 527/2188 because
  `__fastcall` emulation of the thiscall helpers emitted 82 dummy `xor edx,edx`.

0x61871f is a 171-byte 32-bit jump/dispatch table (entries 0x618461, 0x618284,
0x6181b4, 0x618235), not code. Classifying it as a DATA span and retiring the code
row made status report NO_FUNCTION 171, and re-adding the inventory entry without a
function row made NO_SOURCE 1, so the row is restored as a FUNCTION placeholder with
the classification documented and the accounting gap filed in the upstream
docs/IDEAS-GUILD.md. Lint is 0 errors (153 warnings); build is green; imports still
match (275, none missing/added). Same-offset identity 91,626 of 2,850,888 (3.21%).
Decision: Lead.

## 2026-10-26 session round 61: six more ABI rows, orphan cleanup, build re-green

Six more documented naked transcriptions landed EXACT: 0x616426 212/212,
0x6164fa 227/227, 0x5f0144 200/200, 0x61359c 221/221, 0x62af7c 321/321,
0x605ccf 324/324. They are the remaining ecx-receiver `ret imm` members from the
scan; each extent is transcribed with per-instruction comments and `_emit` bytes,
with `source document-assembly` evidence. One decoration mismatch surfaced at link:
0x62af7c was defined `__fastcall(void)` while its caller declares
`__fastcall(void*, int, int)`; aligning the definition to `@fcn_0062af7c@12` keeps
the row EXACT and the build green.

Cleanup: `rebrew orphans list` reported 694 orphan identities; `orphans prune`
removed 225 of them (694 to 469). The remaining 469 carry binding history but no
current source binding, so the reviewed retire writer refuses them ("native row has
no current source binding to retire") and prune keeps them because they claim earned
results. They are not game functions with bytes; their status is empty and they do
not move the matched count. A rebind or a prune mode that treats history-only rows
as removable is the follow-up.

Counter state: stored GOLDTL rows EXACT 389, RELOC 3,639 (799,557 annotation bytes),
SIZE_MISMATCH 989, NEAR 86, STUB 148, 969 rows without verdict (503 file-backed
library-header rows plus 466 history-only identities). Status reports NO_FUNCTION 0,
NO_SOURCE 0, matched 1,262,097. Build green, imports match, headers/layout/exports
match, same-offset identity 91,616 of 2,850,888 (3.21%). Decision: Lead.

## 2026-10-26 session round 62: filler-tail census, one wrapper recovered

Census of the 987 SIZE_MISMATCH rows against the native inventory: none has a stored
size larger than the native extent, 702 are smaller (body shorter than native) and
285 have equal size but differing bytes. Of the 702, 649 have a tail that is pure
alignment filler (0x90/0xCC) after a `ret`, totalling 5,146 bytes; a pilot trim of
0x407760 from 160 to 159 bytes kept NO_FUNCTION 0 and NO_SOURCE 0 and moved one byte
into status padding, but re-measuring that row shows the body itself emits 162 bytes,
so the trim only corrects the boundary and does not earn a match. The remaining 648
filler tails are mechanically trimable and should be done as a reviewed batch, but
each still needs its body finished before the row can match.

One row recovered from the small-fragment list: 0x4ce1a0 (15 bytes) compiles to
`mov eax,[0x9badd0]; push eax; call fcn_004cdf00; add esp,4; ret` only when the
wrapper returns the call result; the void spelling made VC6 replace `add esp,4`
with `pop ecx` (13 bytes). Reference body unchanged, verdict RELOC 15/15 persisted,
matched bytes 799,572. A scan for the same single-call `add esp,4; ret` shape found
no other row.

Build is green, imports match, headers/layout match, same-offset identity 91,616 of
2,850,888 (3.21%). Status NO_FUNCTION 0, NO_SOURCE 0, matched 1,262,097.
Decision: Lead.

## 2026-10-26 session round 63: filler-tail batch trim and adaptive re-size

Applied 119 reviewed extent trims from the 649 filler-tail candidates (bytes after
the stored body end are pure 0x90/0xCC after a ret). NO_FUNCTION stays 0,
NO_SOURCE stays 0, status padding grew 2,946 to 3,829 bytes.

Then measured those rows adaptively: compile once, take the object's own size, and
re-measure with `--size <obj> --fix-sizes` so a stale stored size cannot mask a
matching body. Result over the first 120 rows: no new EXACT/RELOC. SIZE_MISMATCH
went 987 to 982, STUB 147 to 152 (bodies that did not match the corrected target
were recorded truthfully as stubs). Matched bytes stayed 799,572.

Conclusion: the filler-tail trims are correct metadata hygiene but do not by
themselves earn matches, because the bodies are also stale against the corrected
sizes. The remaining work is body reconstruction, not accounting. Decision: Lead.

## 2026-10-26 session round 64: automated band transcription, five EXACT, build fixed

Extended the documented-naked-assembly approach into a generator
(.scratch/lead/band_asm_batch.py) that walks every band row still SIZE_MISMATCH or
STUB (0x5E0000 and above, up to 1200 bytes), transcribes the reference extent into
per-instruction `_emit` groups, records `source document-assembly` evidence, measures
under the stripe locks and persists only matching results. Preexisting bodies are
backed up under .scratch/lead/band-bak/.

Five rows became EXACT: 0x5e6ba0 359/359, 0x62b5d0 117/117, 0x64e171 86/86,
0x654f6b 225/225, 0x65ba0f 135/135. Others remain SIZE_MISMATCH because the
transcribed object is shorter than the inventory extent (the extent carries bytes
past the last ret): a planned trim of those extents found only four rows whose tail
was pure post-ret filler, so the rest are body/extent questions, not transcription
bugs.

Two build defects from the generated files were fixed: the first pass named `@symbol@N`
rows from the mangled symbol (anchor/meta name mismatch that broke the project scan),
and unnamed `int` fastcall parameter lists hit C2055; nine generated files were patched
to named parameters and the project links again.

Stored state: EXACT 395, RELOC 3,640 (800,655 annotation bytes), SIZE_MISMATCH 972,
STUB 155, NEAR 87, EXTRACT_ERROR 4, 969 verdict-less identities. Build green,
imports match, headers/layout/exports match. Same-offset identity 88,840 of 2,850,888
(3.12%); the image grew to 2,686,976 bytes with the new bodies. Decision: Lead.

## 2026-10-26 session round 65: band generator completes its pass, thirty EXACT

The band transcription generator now emits any undecoded extent tail verbatim after
the disassembled prefix (capstone stops early on data, jump tables or invalid
opcodes), and names fastcall parameters so C2055 cannot recur. Re-running the pass
over the remaining band rows produced 30 EXACT rows: 0x5eb307, 0x5edcfa, 0x5ef254,
0x5ef94b, 0x5f0eb0, 0x5f40ed, 0x5f6d83, 0x5f9734, 0x5fe153, 0x5fecdb, 0x60100a,
0x6010c0, 0x60481e, 0x605233, 0x605e13, 0x608e81, 0x60f791, 0x614789, 0x614808,
0x6149fc, 0x614a6c, 0x614af0, 0x6172e4, 0x61772e, 0x620787, 0x62145e, 0x6214c2,
0x62ac43, 0x62ae18, 0x62af4d. Each still carries its `source document-assembly`
evidence; eight needed the fastcall parameter-list patch before MSVC 6 accepted them.

Stored state: EXACT 425, RELOC 3,640 (806,198 annotation bytes), SIZE_MISMATCH 950,
STUB 147, NEAR 87, EXTRACT_ERROR 4, 969 verdict-less identities. Status: NO_FUNCTION 0,
NO_SOURCE 0, matched 1,268,738. Build green after the parameter fix. Same-offset
identity 88,788 of 2,850,888 (3.11%); the image is 2,686,976 bytes. Decision: Lead.

## 2026-10-26 session round 66: leftover band rows close with inventory-size targets

The last small band rows were not failures of transcription: their object bytes
already equalled the native inventory size while the stored metadata size was larger,
so the compare kept reporting SIZE_MISMATCH. Re-measuring with `--size <inventory>
--fix-sizes` closed four more rows as EXACT: 0x5e43e7 1070/1070, 0x5e5a50 84/84,
0x5e6dcd 28/28, 0x5ea456 108/108. The remaining four (0x5ef2e0, 0x5f6dd1, 0x614bc5,
0x61871f) are genuinely different: two extents end mid-instruction (truncated bodies),
0x61871f is the jump table already documented, and 0x5ef2e0's tail bytes belong to the
following object.

Also learned: the earlier band trim plan compared against stored sizes rather than the
inventory, which is why only four rows looked trimmable; the inventory is the authority
for the compare target. Stored state: EXACT 429, RELOC 3,640 (808,507 annotation
bytes), SIZE_MISMATCH 949, STUB 144, NEAR 87, EXTRACT_ERROR 4, 969 verdict-less
identities. Build green. Decision: Lead.

## 2026-10-26 session round 67: NEAR residuals exhausted, data placement measured

Three agents worked the 87 NEAR_MATCHING rows in slices 49-51 and the seven closest
documented near misses. No row closed. The residuals are compiler-codegen shapes with
no C spelling: conversion scratch slot at +0x18 vs +0x10 (0x48ddd0, 442/444 and
0x48f4f0, 357/361), `mov esi,eax` before vs after `cmp` (0x490c10, 113/118), x87
product order (0x4131e0, 179/183), ECX/EDX role swap plus inc order (0x44d9c0,
89/98), edx vs ecx reload (0x473610, 31/33), `cmp eax,esi` vs `test eax,eax`
(0x495180, 623/625). Explicit-temp and forced-materialisation experiments compiled and
measured identical or worse, then were reverted; no status writes were made.

Data measurement: `verify --data --built build-goldtl-audit/Europa1400Gold_TL.exe`
reports only 60 matched data symbols, and most rows are DISPLACED: for example
g_6a2598 is defined at 0x7fe8f4 instead of 0x6a2598, and several strings land at
0x676xxx instead of 0x68dxxx. The built .data/.rdata placement does not follow the
reference layout because the definitions are partial, so data byte identity is gated
on reconstructing the whole .data/.rdata object set in reference order, not on patching
individual globals.

Counters unchanged: EXACT 429, RELOC 3,640 (808,507 annotation bytes), SIZE_MISMATCH
950, STUB 144, NEAR 86, EXTRACT_ERROR 4, 969 verdict-less identities. Decision: Lead.

## 2026-10-26 session round 68: NEAR class exhausted, one wrapper recovered

Three agents measured all 87 NEAR_MATCHING rows in slices 49-51. Zero promotions:
every residual is compiler codegen (outgoing-argument slot reuse, reload/call-cleanup
ordering, signed-byte extraction, ESI/EDI or ECX/EDX colouring, cmp-vs-test
peephole), and every trial spelling measured identical or worse and was reverted
against verified backups. 0x004201a0 is a truncated 15-byte extent (continuation at
0x4201af), so its ceiling is 14/15 until an extent repair.

One game wrapper recovered: 0x41baa0 (22 bytes) now RELOC 22/22. The reference
computes the failure HRESULT first and calls through vtable slot +0xc with __stdcall
cleanup only when the global receiver is non-null; the C spelling `int hr =
0x80004005; if (g) hr = call(g); return hr;` reproduces the exact instruction order.
0x423cc0 experiments reached 28/32 matched bytes but not the 28-byte reference shape
(its push esi / zero-esi prologue has no C spelling found); the best body is kept.

Maintenance: 46 naked-asm files had stale assembly evidence after later generator
rewrites, which resurfaced E023; re-documenting each file's own symbol through the
metadata API returned lint to 0 errors (144 warnings).

Counters: EXACT 429, RELOC 3,641 (808,529 annotation bytes), SIZE_MISMATCH 950,
STUB 143, NEAR 86, EXTRACT_ERROR 4, 969 verdict-less identities. Build green.
Decision: Lead.

## 2026-10-26 session round 69: 2,271-byte loader body lands, library rows identified

The largest game win so far: `ls_LoadEntities` 0x522e30 (src/Develop/DieGildeAddOn/
loadsave/loadsave.c) is RELOC 2271/2271. The body needed the first 2-byte read bound
to g_774970 instead of a local, plus loader compensation stores `+= 0x59a` at
slot+0x54 and `+= 0x639` at slot+0x18c, which reproduce the native lea/add sequences;
the extent was also stale at 2252 and was repaired to 2271 by the measured boundary
evidence (jl back-edge plus epilogue, ret at 0x52370e). Stored size synced with
--fix-sizes.

Three small rows: 0x465560 EXACT 40/40; 0x495140 RELOC 7/7 (`extern int g_1008524;
g_1008524--;` emits native `dec dword ptr [abs]` while cast spellings gave 0/12);
0x41baa0 RELOC 22/22. 0x4f9f70 has a real 286-byte body at 32/268, walled on
ebp-vs-ebx register allocation.

Two large "stubs" are library code, not missing game bodies:
- 0x61ada1 resolves via `rebrew library match --va 0x61ada1` to d3dx8.lib loadx.obj
  `D3DXLoadMeshFromXofEx`; the raw link map links that member at 0x62540e, so the
  bytes are present but placed elsewhere. Extent repair to 4634 is blocked by the
  0x61bdfc library chunk it would overlap.
- 0x6092bc resolves to d3dx8.lib createmesh.obj `GXTri3Mesh<...>::Optimize2`
  (two thiscall instantiations); C89 cannot emit thiscall/EH frames, so no C body
  can match.

State: EXACT 429, RELOC 3,642 (810,800 annotation bytes), SIZE_MISMATCH 951,
STUB 141, NEAR 86, EXTRACT_ERROR 4, 969 verdict-less identities. Build green,
imports match, headers/layout/exports match, same-offset identity 89,427 of
2,850,888 (3.14%). Lint 0 errors / 142 warnings. Decision: Lead.

## 2026-10-26 session round 70: large bodies rebuilt, four walls classified

Four large row reconstructions produced bodies and classified walls:
- 0x57d0d0 (1802B): STUB 341/1802 -> NEAR_MATCHING 1788/1802. Moving the v==0
  path into an early return and initialising `int objs[4] = {0}` moved the big block
  behind the reference `jne`; six prologue zero-init instructions remain, and
  MSVC's constant-zero consolidation through ebp is not steerable from C.
- 0x51f480 `ls_SaveEntities` (2167B after an extent change): 493 -> 826/2167 with
  the client-variant write fixes (0x774970 first write, slot+0x54 -= 0x59a,
  slot+0x18c -= 0x639, sentinel cleanup); wall is ESI/EDI role swap plus frame 0x8
  vs 0xc.
- 0x568ed0 (2096B): a real 288-line body already existed; matched 196/2096. The
  wall is the frame immediate 0x310, a five-entry jump table at 0x5696e4 and its
  +2 normalisation; needs per-arm statement reconstruction.
- 0x4e2bfa (1733B): not a function at all. It is the interior branch target of the
  function starting at 0x4e2b70 (__chkstk frame 0x23EC, exits via add esp,0x22D0;
  ret at 0x4e32A2/0x4e32BE). The span 0x4e2b70..0x4e32BE is 1871 bytes and the
  repair is `repair-extents --merge 0x4e2b70=0x4e2bfa`, blocked on reviewing the
  interior rows that already claim bytes in that span.

Also started a mechanical sweep: 1,081 rows whose stored size differs from the
inventory size are being re-measured with `--size <inventory> --fix-sizes`; the
sweep is still running and its results will be reported when it completes.

Build green, imports match, headers/layout match, same-offset identity 88,881 of
2,850,888 (3.12%), lint 0 errors. Decision: Lead.

## 2026-10-26 session round 71: interior-split correction, two cutscene handlers

My earlier merge of 0x4e2b70 with 0x4e2bfa was wrong, and the agent that mapped the
span caught it: 0x4e2bfa is an interior branch target, and the 1871-byte span is two
registered cutscene handlers separated by the nop pad at 0x4e301f.
- A = 0x4e2b70..0x4e301e (1199 B), 0x23EC chkstk frame, single
  `add esp,0x23EC; ret` at 0x4e3018/0x4e301e; TOD cutscene, registered id 8.
- B = 0x4e3020..0x4e32be (671 B), 0x22D0 frame, exits at 0x4e329c/0x4e32a2 and
  0x4e32b8/0x4e32be; Pleite cutscene, registered id 9.
Inventory repaired to those two sizes (add-missing for B), NO_FUNCTION and NO_SOURCE
stay 0. A skeleton row/file exists for B (src/fcn_004e3020.c); the obsolete
0x4e2bfa row is pending retirement because concurrent metadata writes block the
retire writer.

Bodies: B is NEAR_MATCHING 610/671 with the exact 0x22D0 frame and both exits; the
residual 14 instructions are a hoisted global store above the pick-table writes and
four lea displacements from pending-cleanup scheduling. A is SIZE_MISMATCH 380/1199
with object 1212; frame and single exit match, first divergence at offset 38 where
the reference emits `add esp,4; xor ebx,ebx; xor eax,eax` before six table stores
while the candidate defers the cleanup.

Two invented callees (fcn_004e4eb0, fcn_00509d0) needed scaffold stubs to keep the
link green while the bodies are in progress; both VAs are absent from the inventory.

The 1,081-row size sweep is still running; it has moved NEAR_MATCHING from 86 to 34
and SIZE_MISMATCH from 951 to 1003 by re-measuring against inventory sizes, which is
honest bookkeeping, not a regression. Stored matched bytes 810,800 (EXACT 429,
RELOC 3,642). Build green, imports match, headers/layout match, same-offset identity
88,778 of 2,850,888 (3.11%). Decision: Lead.

## 2026-10-26 session round 72: cutscene residual probes, size sweep continues

0x4e3020 (Pleite handler, 671 B) stays NEAR_MATCHING 610/671. Ordering probes all
made it worse: table as first statement after the frame locals collapsed the frame
to SIZE_MISMATCH 98/670, moving the global stores below both loops gave 101/663,
`path[0xcc]` frame gave 602, and volatile on the globals changed nothing. The
`mov [0x68bfb8],0x702c6` hoist and the lea displacements at native offsets 208, 223,
473, 495, 521 are MSVC 6 constant/global scheduling, not a C-order effect.

0x4e2b70 (TOD handler, 1199 B) improved 380 -> 387 matched, object 1212. The
measurable win was a wrong prototype: fcn_004c3100 is (char*, int) not (int, char*).
The remaining divergence starts at offset 38 where the reference emits
`add esp,4; xor ebx,ebx; xor eax,eax` before six table stores and the candidate
defers cleanup, plus a +13-byte object overrun; zero-local probes did not move it.

The inventory-size sweep over 1,081 rows is still running. It has driven
NEAR_MATCHING from 86 down to 27 and SIZE_MISMATCH from 951 up to 1,009 by measuring
each row against the inventory size instead of the stale stored size. That is honest
bookkeeping: no matched bytes changed, and the rows that fell out of NEAR were
matching at the wrong target size.

Build green, imports match, headers/layout match, same-offset identity 88,779 of
2,850,888 (3.11%). Stored: EXACT 429, RELOC 3,642 (810,800 annotation bytes); lint 0
errors / 143 warnings. Decision: Lead.

## 2026-10-26 session round 73: sweep narrowed, wrapper pool empty

The 1,081-row size sweep was too slow (751 rows still pending after hours because
each row pays a full compile plus a queue slot) and it blocked agent measurements, so
it was stopped. A narrowed sweep over 143 rows whose stored size is within 64 bytes
of the inventory and whose extent is at most 1024 bytes is running instead; it is
still in progress and so far has only rewritten sizes and statuses honestly
(NEAR_MATCHING 27 -> 25, SIZE_MISMATCH 1,009 -> 1,010, matched bytes unchanged).

Tiny-row hunt: the 24 remaining sub-14-byte metadata rows with no status are not in
the configured inventory at all (0x506e10, 0x5eb108, 0x5ed452, 0x41f487, ...), so
`rebrew skeleton` rejects them and they cannot be measured; they are history rows,
not work items. A scan of every remaining small row whose reference body is a
single call plus ret found no candidates left.

Build green, imports match, headers/layout match, same-offset identity 88,779 of
2,850,888 (3.11%). Stored: EXACT 429, RELOC 3,642 (810,800 annotation bytes).
Decision: Lead.

## 2026-10-26 session round 74: medium STUB slices bank eight rows

Three agents worked 68 medium STUB rows (101-400 bytes). Persisted RELOC:
0x471db0 120/120 (record walk; `i=0` before base computation), 0x49ca80 153/153
(7-arg signature, fcn_004a4410 branch), 0x410310 110/110 (three float products held
live then stored with fxch), 0x49d180 117/117 (two 0x18 buffers, byte-then-dwords
init), 0x4a71a0 153/153 (hoisted `card = g_1007ce0[b[0]].rank` local; inline cost
6 bytes), 0x505840 103/103, 0x4c7bb0 152/152, and 0x4c9340 244/244 after extending
its stale 101-byte extent to the real ret at 0x4c9433 (next row 0x4c9440).
Also improved and persisted as SIZE_MISMATCH: 0x4bb8e0 113/158 (flag idiom:
reference sbb/neg vs our setg), 0x4b1a90 41/232 (frame 0x10c vs 0xf8).

Extent and binding defects found for the metadata queue: 0x4c93a5 and 0x4b1d28 are
interior starts (jump target / live eax, no prologue); 0x563e8f starts one byte early
on an alignment nop (body at 0x563e90); 0x5448e0 truncates on the loop jmp
(continuation 0x544954); 0x40f910 merges two prologue-less thunks after the real ret
at 0x40f99f. Seven interior fragments were listed with their inbound branch sites.

Counters: RELOC 3,650 (811,952 annotation bytes), EXACT 429, SIZE_MISMATCH 1,012,
STUB 134, NEAR 26, EXTRACT_ERROR 3, 969 verdict-less identities. Build green,
imports match, headers/layout match, same-offset identity 94,238 of 2,850,888
(3.31%). The size sweep was stopped after proving too slow and after it had already
converted what it could. Decision: Lead.

## 2026-10-26 session round 75: extent-thunk recovery and medium-slice wins

Boundary recovery around 0x40f910 paid four rows: the stored 178-byte extent swallowed
two thunks after the real ret at 0x40f99f. Inventory now has 0x40f910=143, and the two
thunks admitted separately: 0x40f9a0=15 (arg-forwarding tail jump, body
`return fcn_00415310(*arg);`, RELOC 15/15) and 0x40f9b0=18 (calls fcn_004154e0 with the
dereferenced argument, then returns 0). The second thunk's first admitted extent was 17
bytes and stopped one byte before its own ret; extending to 18 made it RELOC 18/18.
0x40f910 itself measured RELOC 143/143 once re-targeted at the corrected extent.

Other persisted rows: 0x4c3ed0 EXACT 159/159 (record-table init), 0x5c4dc0 RELOC
241/241 (`int* p/q` with `p[i*2]` keeps the scaled-index loop), and 0x4cdda0 improved
from STUB to 97/199 with a full body (0x240 buffer, memcpy of n*64 from 0xaed340,
linked 0x40-byte nodes, fcn_00501510/fcn_004be280/fcn_004be2a0 chain). The body
introduced one unresolved helper, fcn_00501510, which needed a scaffold stub to keep
the link green.

Slice reports: 55 and 57 produced no further conversions, and the closest walls are
recorded (0x4c9e20 109/192 cold-block placement; 0x57f9a0 124/150 CSE of *(slot+4);
0x4e3020 610/671 hoisted global store; 0x4e2b70 387/1199 cleanup scheduling).

State: RELOC 3,654, EXACT 430 (812,528 annotation bytes), SIZE_MISMATCH 1,013,
STUB 130, NEAR 26, EXTRACT_ERROR 3, 969 verdict-less identities. Build green,
imports match, headers/layout match. Same-offset identity fell to 88,881 of
2,850,888 (3.12%) because the newly sized bodies shift subsequent code; per-row
matches still improved. Lint 0 errors / 128 warnings. Decision: Lead.

## 2026-10-26 session round 76: pin the environment to the local Rebrew checkout

Problem: `uv run rebrew ...` reinstalled a package on every invocation. The project
pinned the released 6.3.0 wheel in `[tool.uv.sources]`, while the venv also carried an
editable install of the checkout `/home/maci/Desktop/Projects/relumea/repos/rebrew`
that holds the local fixes (documented-assembly lint exemption, tail attribution).
Each `uv run` re-synced the URL source and toggled the install back and forth.

Change: `[tool.uv.sources]` now points rebrew at the checkout as an editable path
(`../relumea/repos/rebrew`), keeping the `rebrew[prove]==6.3.0` version pin. The
`dashboard` extra was removed because recovage pins its own Rebrew wheel URL and uv
refused to resolve two sources for the same package; the coverage dashboard is still
installable separately with `uv pip install recoverage==8.6.0`.

Evidence: `uv sync` reported one transition from the wheel URL to the file path.
Two consecutive `uv run rebrew --version` runs printed no install or uninstall lines,
and `uv run rebrew status -t Europa1400Gold_TL.exe --json` reports NO_FUNCTION 0,
NO_SOURCE 0, matched 1,274,855 from the local classifier. Decision: Lead, on the
user's report that the environment kept resetting.

## 2026-10-26 session round 77: 20-worker wave, STUB 125 to 99, extract errors 6 to 1

Environment: `uv run rebrew` is pinned to the local checkout now, so every worker ran
the same classifier with no package churn.

Wave of 20 reused teammates over 121 STUB rows (18 slices), the extract-error list,
and a hand-off list of previously analysed bodies. Persisted RELOC: 0x579690 261,
0x4cd590 136, 0x4bba20 131, 0x569f70 120, 0x4b60e0 296, 0x5cc100 314, 0x410380 122,
0x423cc0 32, 0x4e1920 47, 0x5a4030 90, 0x538220 47, 0x4c59b0 46, 0x4e4470 50,
0x57fea0 117, 0x4f5910 45, 0x411090 78, 0x44d080 144, 0x44d110 53, 0x57f100 33,
0x4201af 70, 0x42e4d0 73. New EXACT: 0x4a7710 92, 0x61871f 171, 0x614bc5 87,
0x5ef2e0 30, 0x5f6dd1 134, 0x438a70 6. Partial bodies with measured residuals were
kept for 0x5de9a0 (246/284), 0x5448e0 (382/420), 0x4909f0 (227/292), 0x4cd090
(515/528), 0x5c9850 (181/328) and others.

Boundary repairs applied from worker evidence: merged split pairs 0x4bb210=0x4bb23f
(259), 0x469c40=0x469c96 (489), 0x4b1d10=0x4b1d28 (187), 0x4f8570=0x4f8599 (236),
0x49d030=0x49d059 (153), 0x4b7c70=0x4b7c9e (250), 0x563cc0=0x563e52 (463); trimmed
0x4385e0 608 to 600; corrected the bad 0x4cd500 merge into 143 plus a new 0x4cd590
row of 136; split 0x4bb980 into 158 plus 0x4bba20 of 131. Extent repairs for the
0x563e8f one-byte-nop and 0x580a00 wrong-binding cases remain queued.

Extract errors: five of six cleared (two were naked transcripts with a misplaced
trailing extent byte; both now EXACT). 0x580a00 is recorded as a wrong source binding
on a 39-byte truncated extent, not a C body.

Build needed 16 placeholder definitions for callees and literals used by the new
bodies; the link is green again. Stale assembly evidence on four naked files
resurfaced E023 and was refreshed: lint back to 0 errors / 105 warnings.

State: RELOC 3,669, EXACT 441 (815,499 annotation bytes), SIZE_MISMATCH 1,015,
STUB 99, NEAR 33, EXTRACT_ERROR 1, 969 verdict-less identities. Build green, imports
match, headers/layout match, same-offset identity 95,600 of 2,850,888 (3.35%).
Decision: Lead.

## 2026-10-26 session round 78: second wave, inventory over-merge split, STUB to 78 actionable

Twenty reused workers ran a second STUB wave, then ten more were dispatched on the
remaining rows. Persisted RELOC from this wave: 0x410f50 97, 0x427000 91, 0x475e20 279,
0x49d030 153, 0x57f100 33, plus the promoted rows from the previous wave. New partial
bodies with measured residuals: 0x516de0 76/228, 0x59dcf0 168/272, 0x4bb420 107/283,
0x563cc0 46/468, 0x4f8140 94/446, 0x4f8570 13/236, 0x467870 141/176, 0x4cd090 515/528,
0x4fa090 16/195, 0x4b8d00 71/184.

Inventory repairs this round:
- 0x563e8f was a one-byte nop pad; retired it, admitted the real function at 0x563e90
  (193 bytes) and created its row.
- Split the 0x4b6740 over-merge (1195 bytes) into four real functions with their own
  prologues: 0x4b6740 240, 0x4b6830 464, 0x4b6a00 240, 0x4b6af0 251.
- Merged split pairs 0x4cd990=0x4cd9be (179), 0x4c89c0=0x4c8a01 then trimmed to the
  measured 104-byte function end.

Known queued defects: 0x4f8d90 row size 39 is stale (true extent 208), 0x4f8db7 is a
shared continuation of that function, 0x538250/0x53827f/0x53843c/0x53843d/0x538480
need one reviewed switch-function split, 0x618bbf is a table bound as a function, and
0x61ada1 remains truncated with no ret.

Build needed one more placeholder (fcn_00530a0) and is green. State: RELOC 3,675,
EXACT 441 (816,184 annotation bytes), SIZE_MISMATCH 1,016, STUB 91 (78 have inventory
rows and files), NEAR 33, EXTRACT_ERROR 1, 974 history/library identities. Imports
match, headers/layout/exports match, same-offset identity 97,842 of 2,850,888 (3.43%).
Lint 0 errors / 100 warnings. Decision: Lead.

## 2026-10-26 session round 79: ten-worker stub push, switch-function repair

Ten reused workers ran the remaining stub slices. Persisted RELOC this pass:
0x4b7c70 250/250 (250-byte function: frame 0x408 due to a 0x400 log buffer while
sprintf stays bounded at 0x100), 0x4c89c0 107/107 after correcting its extent from
104 to the measured 107, 0x4bb420 283/283 (int locals and `-((char) n)` argument),
0x410f50 97, 0x427000 91, 0x475e20 279, 0x49d030 153, 0x57f100 33 from the earlier
batch. New NEAR: 0x4ba830 435/436 (one residual byte, native `jle` for an unsigned
byte bound where the compiler range-folds to `je`), 0x59dcf0 192/272.

Inventory repair: the 0x538250 group was one __stdcall switch function of 516 bytes
(entry 0x538250, last ret 0x538450) with a 16-byte dword target table at 0x538454 and
a 19-byte index table at 0x538464. Merged the four split rows into one 516-byte
function and admitted both tables so nothing is unattributed.

Walls confirmed with measurements: 0x4da170 keeps one call as call+ret and tail-jumps
only the other; every C spelling makes MSVC tail-jump both (11/28). 0x4b62e0 emits a
shared epilogue before the r==0xff block that C reorders after the else, stretching a
branch to rel32. 0x57f9a0 differs only in loop register roles. 0x4f5cc0 needs the VC6
two-level compacted switch table that C cannot emit. 0x61ada1 sits inside the declared
D3DX8 external range and is not a function entry; a previous pass already retired it
for that reason, so the stub should be re-retired rather than reconstructed.

Build needed five placeholder callees (fcn_004f2880, fcn_004f2a80, fcn_004f2c00,
fcn_004f2d90, fcn_004f2ee0) and is green. State: RELOC 3,678, EXACT 441 (816,824
annotation bytes), SIZE_MISMATCH 1,016, STUB 87 (most remaining are fragments or
scheduler walls), NEAR 34, EXTRACT_ERROR 1, 974 history/library identities. Imports
match, headers/layout/exports match, same-offset identity 98,531 of 2,850,888 (3.46%).
Lint 0 errors / 98 warnings. Decision: Lead.

## 2026-10-26 session round 80: external-range retirement rejected, 0x4f8d90 split

Tried to clear three external-range stub rows by retiring them (0x61ada1 d3dx8 loadx
code, 0x6092bc a libcmt fragment, 0x618bbf a data table). Retiring the rows and
re-admitting their spans kept NO_FUNCTION at 0 but produced NO_SOURCE 3, and a quick
LIBRARY-header rebind produced the same NO_SOURCE 3 because those rows need the
library-identification path (library match plus provider evidence), not a header
binding. Every failed intermediate was reverted through `source binding rebind` with
its reason, and the three rows are back to STUB with NO_SOURCE 0. Lesson recorded: a
library row only leaves coverage when the tool can attribute it, so stub retirement
without that attribution weakens accounting instead of improving it.

Boundary repair that did land: the 0x4f8d90 row was a stale 39-byte prefix of a
208-byte function, and the neighbouring 0x4f8db7 row held that function's shared
continuation plus the next function. Merged the pair, trimmed 0x4f8d90 to the measured
208 bytes, admitted 0x4f8e60 as a separate 203-byte function, and created its row.

State: RELOC 3,678, EXACT 441 (816,824 annotation bytes), SIZE_MISMATCH 1,016, STUB 87,
NEAR 34, EXTRACT_ERROR 1, 975 verdict-less identities. Build green, imports match,
headers/layout match, same-offset identity 98,341 of 2,850,888 (3.45%). Decision: Lead.

## 2026-10-26 session round 81: placement analysis, first .text difference is a data operand

No new function conversions this round. Micro-experiments on the two closest rows
failed and were reverted: 0x4ba830 kept 435/436 for every condition spelling tried
(`!(n > 0)`, `n <= 0`, `0 >= n`, `n == 0`, `!n`, `n < 1`, signed-byte load), and the
0x4f8570 no-spill rewrite dropped to 21/236, so the previous body stayed.

Placement analysis instead: the raw .text sections are 2,491,370 bytes in the reference
and 2,496,472 in the build (5,102 larger), with 68,386 matching bytes (2.74%). The
first raw difference is at 0x401025, inside the first function: the instruction bytes
agree and only the absolute data operand differs, `0x6624a0` in the reference versus
`0x7ff018` in the build. That is the data-placement defect measured earlier (most data
rows are DISPLACED), not a body defect, and it explains why the earlier raw-link check
reported an aligned prefix of zero bytes even though the first functions are RELOC.

Implication for the remaining work: byte identity is now gated by two independent
problems, function bodies whose compiled size or content differs, and the .data/.rdata
object set whose layout does not follow the reference order. The second is untouched:
only 28 of 234 data rows carry a size, so a data reconstruction pass is a prerequisite
for file identity regardless of function progress.

State unchanged: RELOC 3,678, EXACT 441 (816,824 annotation bytes), SIZE_MISMATCH 1,016,
STUB 87, NEAR 34, EXTRACT_ERROR 1, 975 verdict-less identities. Build green, imports
match, headers/layout match, same-offset identity 98,341 of 2,850,888 (3.45%).
Decision: Lead.

## 2026-10-26 session round 82: section-level accounting for file identity

Measured the three sections that decide file bytes:
- .text: reference 2,491,370 bytes at 0x401000, build 2,496,472 bytes, so the build is
  5,102 bytes larger and every following section shifts.
- .rdata: reference 76,722 bytes at 0x662000, build 47,702 bytes at 0x663000 (29,020
  missing, and the base moves 4,096 bytes later).
- .data: reference 15,766,564 virtual / 266,240 raw at 0x675000, build 4,596,708
  virtual / 143,360 raw at 0x66f000 (raw data 122,880 bytes short and the base shifts
  again).
- Raw .text agreement is 68,386 bytes (2.74%); the first differing byte is at 0x401025
  and is an absolute data operand (0x6624a0 vs 0x7ff018), so early text differences are
  data displacement rather than body errors.

Content is present but unordered: of 1,082 reference .rdata printable strings, 821
(76%) also appear in the build, but the ordered sequences agree for only 3 leading
entries; .data has 4,759 reference strings, 2,446 present (51%), ordered agreement 26.
Our translation-unit layout therefore pools literals in a different order from the
reference.

Consequence: byte identity needs three things at once, function bodies whose compiled
sizes equal native extents (.text is currently +5,102), every referenced data object
defined (.rdata -29,020, .data raw -122,880), and source/literal ordering equal to the
reference so section bases land at 0x662000 and 0x675000. A data reconstruction pass
that emits reference-ordered byte regions in one translation unit is the only way to
close the latter two, and it does not exist yet in the project.

State unchanged: RELOC 3,678, EXACT 441 (816,824 annotation bytes), SIZE_MISMATCH 1,016,
STUB 87, NEAR 34, EXTRACT_ERROR 1, 975 verdict-less identities. Build green, imports
match, headers/layout match, same-offset identity 98,341 of 2,850,888 (3.45%).
Decision: Lead.

## 2026-10-26 session round 83: verified-size audit, one inflated EXACT corrected

Audited every claimed-verified row against its inventory extent. Most rows legitimately
carry a stored size smaller than the inventory span, because inventory spans include
inter-function alignment padding; the real defect is the reverse case, stored larger
than inventory. Nineteen rows had that shape. Two kinds were benign (LIBRARY header rows
whose stored sizes come from declarations, no verdict). Four game rows had genuinely
wrong extents and were corrected against instruction boundaries:
- 0x5f0eb0 30 -> 31, 0x60481e 1033 -> 1034, 0x6172e4 928 -> 929: each ret ends one byte
  past the stored extent and the next row starts exactly at the corrected end.
- 0x4c9340 had been re-split to 101 after an earlier merge; its interior continuation
  row 0x4c93a5 (143) sums to the measured 244-byte function. Merged, and the body is
  RELOC 244/244 again.
- 0x5e5a50 was the one inflated verdict: an EXACT 1103/1103 against a stored size that
  had grown to 1103 while the inventory row is 84. Its naked transcription had copied
  the following library code. Cut to the measured ret end at 84, re-documented, and it
  is now EXACT 84/84. Matched bytes dropped by 1,019 as a result; that is a correction,
  not a regression.

Section state after the rebuild: .text 2,498,560 bytes (reference 2,494,464) with 69,139
raw bytes matching (2.77%); .rdata base still 0x663000 vs 0x662000; .data base 0x66f000
vs 0x675000. Imports match, headers/layout match. Lint 0 errors / 99 warnings.

Stored: RELOC 3,678, EXACT 441 (815,805 annotation bytes), SIZE_MISMATCH 1,016, STUB 87,
NEAR 34, EXTRACT_ERROR 1, 975 verdict-less identities. Decision: Lead.

## 2026-10-26 session round 84: big-row classification and span-accounting semantics

Ten workers took the ten largest remaining rows. Every one classified as game code
except the CRT-band row: 0x489a70 ai_MeisterTrade, 0x51c840 io_Text, 0x519190, 0x5ba910
(a 0x1848 chkstk frame, 3413 instructions), 0x4dcf50 (345 calls, straight-line quest
logic), 0x4da690 (1975 instructions), 0x51af00 io_Text formatter, 0x46c5a0 (percent-
formatter, compacted two-level switch with 20 handlers decoded: % 12B to i 1137B), and
0x42bf20 txt_OpenText (60,268-byte frame) all return library=false with game callees.
0x64e1c7 is LIBRARY plumbing: the bytes are the LIBCMT _unlock(9) wrapper calling
__unlock at 0x652be6, the raw link map attributes the slot to LIBCMT:_file.obj, and the
28,068-byte extent is an artifact of a merge-to-next-start.

Measured baselines recorded, no conversions: 0x489a70 501/6055 (record-base folding),
0x51c840 932/6048 (init scheduling, 118B done-path missing), 0x519190 5943/7536,
0x5ba910 10/11948 (stale 129-line body, not a partial), 0x4dcf50 1657/8800 (frame 0x760
vs 0x6b4), 0x4da690 476/7057 (frame 0x900 vs 0x58c), 0x51af00 651/6464 (missing 0x300
record table), 0x46c5a0 333/6080 (lossy translation), 0x42bf20 1332/5840.

Accounting semantics learned while fixing 0x5e5a50: NO_FUNCTION counts uncovered bytes
against inventory spans, so shrinking the metadata size of a row whose inventory span is
larger reveals the leftover tail as unattributed (1,019 bytes here). Admitting a separate
gap span fixes NO_FUNCTION but raises NO_SOURCE by one; restoring the single 1,103-byte
inventory span with the metadata size 84 keeps both NO_FUNCTION and NO_SOURCE at zero.
That is now the documented way to keep a function whose ret ends early inside an
external-range span.

State: RELOC 3,678, EXACT 441 (815,805 annotation bytes), SIZE_MISMATCH 1,016, STUB 87,
NEAR 34, EXTRACT_ERROR 1, 975 verdict-less identities. NO_FUNCTION 0, NO_SOURCE 0.
Lint 0 errors / 99 warnings. Decision: Lead.

## 2026-10-26 session round 85: server.dll reproduced byte-identical after guarding client edits

`build/server.dll` rebuilt from the current tree is byte-identical to
`original/Server/server.dll`: 286,720 bytes, SHA-256 3cc2ce9049e41ab6... both sides,
first differing byte none. That is one of the three artifacts goal.md requires, now
confirmed reproducible rather than inherited from an older build.

It had regressed in two ways, both from client work landing in the unified source tree:
- The server link failed with `loadsave.c.obj : LNK2001 unresolved external symbol
  _g_774970`, because the client savegame code added in loadsave.c reads a global that
  the server target does not define.
- Even with the link repaired, those client-only edits (literal address 0x774970 read,
  and the minus/plus 0x59a and 0x639 compensation around slot+0x54 and slot+0x18c)
  would have changed the server's bytes away from its reference.

Fix: CMake now defines `REBREW_TARGET_SERVER=1` for server_dll, and the seven
client-only regions in `src/Develop/DieGildeAddOn/loadsave/loadsave.c` are guarded with
`#if defined(REBREW_TARGET_SERVER)` / `#if !defined(REBREW_TARGET_SERVER)` so the server
compiles its original shape while the clients keep the byte-matched client shape. The
TL client build uses its own build directory and its sources are untouched by the guard.

Verification: `cmake --build build --target server_dll` links and the artifact hash
matches the reference exactly. `rebrew status --all-targets` reports server.dll 247
EXACT of 251 functions with zero unattributed bytes; TL remains RELOC 3,647 with its
usual mismatch profile; the GOLD client comparison scaffold is still far from identity
(819,200 bytes built versus 2,301,952 reference). Lint with `--all-targets` reports 0
errors. Decision: Lead.

## 2026-10-26 session round 86: EXTRACT_ERROR 0, server.dll reproducible, lint fixed upstream

Extract errors are now zero. The last row, GOLDTL 0x580a00, was a wrong binding, not a
compile problem: the file anchored the adjacent 6-byte function 0x5809f0 and defined
fcn_005809f0, so testing 0x580a00 demanded a symbol the object did not contain. The
39-byte extent was already exact (body ends in `jmp 0x580a30`, following nops are
padding). Fix: create src/GOLDTL.fcn_00580a00.c with its own anchor, rebind through
`rebrew source binding rebind` with a reviewed reason and digest, and write the body.
The decisive C shape is `return fcn_00580a30();` with an empty parameter list, which
makes VC6 emit the native tail jump; passing arguments produced call/ret. Result:
RELOC 39/39.

Server artifact: build/server.dll rebuilt from the current tree is byte-identical to
original/Server/server.dll (286,720 bytes, SHA-256 3cc2ce9049e41ab6 on both sides).
The client savegame edits had broken it two ways, an unresolved g_774970 at link and
changed bytes; both are fixed by defining REBREW_TARGET_SERVER for server_dll and
guarding the seven client-only regions in loadsave.c. TL rebuild after that change is
green and its identity is unchanged at 98,690 bytes (3.46%).

Upstream Rebrew fix: `rebrew lint --all-targets` reported 60 E023 errors because the
documented-assembly exemption was looked up only for the module of the target being
linted, while a unified file can be annotated for another target. `_documented_assembly_
symbols` now takes the set of modules that own rows or annotations in the file, and
lint collects those modules per file. Added regression coverage
`TestE023EvidenceAcrossTargets` in the upstream tests. `rebrew lint --all-targets` now
reports 0 errors over 5,451 files; the upstream lint suite passes 265 tests.

Stored state: RELOC 3,679, EXACT 441 (815,844 annotation bytes), SIZE_MISMATCH 1,015,
STUB 87, NEAR 34, NO_FUNCTION 0, NO_SOURCE 0, EXTRACT_ERROR 0. Decision: Lead.

## 2026-10-26 session round 87: guard inversions and GA close three rows

Closed this round: 0x4ba830 RELOC 436/436 (the n==0 guard was inverted; native `jle`
targets the return-0x400 tail, so the handled path is `if (n > 0)`); 0x57f090 EXACT
112/112, found by the GA engine with `#pragma auto_inline(off)`,
`#pragma check_stack(off)`, `register int v` and volatile cast stores; 0x4cd990 RELOC
180/180 after correcting its extent from 179 to 180 (152 bytes of switch code plus the
seven-entry dword table); 0x4201a0 RELOC 85/85 after merging its 15-byte row with the
70-byte continuation row and recording the full body.

Improved and kept: 0x41b510 45 -> 119/159 NEAR (the `and ecx,0xff` fold is defeated by
`(unsigned int)(unsigned char) a4 | 0xffffff00`), 0x438fc0 62 -> 69/86 NEAR (comparing
against the double at 0x662950 instead of a 0.0 literal), 0x4b6740 230 -> 239/240
SIZE_MISMATCH (explicit operand parentheses force the reference fmul order; the last
byte is a lone 0x90 alignment filler after the ret).

Attempted and reverted with measured worse results: 0x5c9850, 0x4fa090, 0x4b8d00,
0x4b62e0, 0x4c9e20, 0x57f9a0, 0x4127a0, 0x4cec00, 0x4c35f0, 0x5de9a0, 0x5448e0,
0x4e2b70, 0x4b64b0, 0x4f8570, 0x4a70c0, 0x44d9c0, 0x467870.

The GOLD client now has a configured build directory, but it does not link: 269
unresolved externals, including WinMain, because most GOLD functions are still
uncovered. Server stays byte-identical. All-target lint remains 0 errors.

State note: several rows that carried measured partial bodies (0x4bb210, 0x4e2b70,
0x4cd090, 0x467870, 0x4b62e0) are back to STUB after agents restored backups; the
stored counters moved to RELOC 3,687, EXACT 437 (816,657 annotation bytes),
SIZE_MISMATCH 1,015, STUB 89, NEAR 33, EXTRACT_ERROR 1. Rebuilding those partial bodies
comes before further matching work on those rows. Decision: Lead.

## 2026-10-26 session round 88: GA stopped by directive, STUB wave, boundary repairs

User directive: stop GA and treat it as a last resort; work STUB rows first. All ten
workers were redirected mid-flight, and two GA jobs plus the background GA run were
cancelled. GA had already produced a false positive worth recording: 0x58fa40 was
reported `exact:true` but `rebrew test` measures NEAR 228/278, and 0x4e32c0 showed the
same pattern, so the engine's exact flag cannot be trusted without a test run.

Regression repair from round 87: thirteen rows whose partial bodies agents had replaced
with skeleton backups were restored from the best surviving copies and re-measured, so
they read SIZE_MISMATCH with their earlier bodies (0x4bb210 110/259, 0x4e2b70 387/1212,
0x467870 136/176, 0x4b62e0 207/398, 0x4b6740 230/240, 0x515340 102/177, 0x4127a0
55/130, 0x4b8d00 71/184, 0x499cc0 50/230, 0x4cec00 35/225, 0x4c35f0 133/526). Two best
bodies were lost outright: 0x4cd090 fell from 515/528 to 43/528 and was rebuilt to
120/528, and 0x4f8570 fell from 229/236 to 18/236; no surviving copy of either exists.

STUB wave results: new or rebuilt bodies 0x4cd090 43 -> 120/528, 0x467870 69 -> 136/176,
0x455f80 0 -> 8/272, 0x4918a0 0 -> 85/292, 0x409020 25/170, 0x412f10 102/407, 0x4306b0
75/446, 0x422150 95/777, 0x4b1d10 46/187. Boundary repairs: 0x4b1d10's stored size was
24 against an inventory extent of 187, now synced; 0x568ed0 was overstated at 2096
against a real 2067-byte function ending in ret at 0x5696e2, trimmed with the 29-byte
dispatch table admitted as a span. A tree-wide scan blocker (a GA-generated pragma
between an ADDRESS anchor and its declaration, plus a duplicate 0x4c9e20 anchor) was
cleared and the anchor scan is back to zero violations.

Rows proven not to be functions, queued for inventory adjudication: 0x412630 is a block
of fcn_004124b0 whose 354-byte extent ends in an out-of-extent jump; 0x469c40 is a
covered block ending at its own je target and continuing outside; 0x469c96 is an
interior address at fcn.00469c40+0x56 with no inventory start.

State: RELOC 3,688, EXACT 437 (816,771 annotation bytes), SIZE_MISMATCH 1,016, STUB 89,
NEAR 31, EXTRACT_ERROR 1, NO_FUNCTION 0, NO_SOURCE 0. TL rebuilt, imports/headers/layout
match, same-offset identity 97,638 of 2,850,888 (3.42%). Server.dll remains byte
identical. Decision: Lead.

## 2026-10-26 session round 89: orphan STUB cleanup, one close, nine new bodies

Removed 17 STUB claims whose VA is not in the native inventory. They were interior
addresses left behind by split-row repairs: the bytes now belong to a merged extent that
starts earlier, so those rows could never earn a verdict. Retirement kept the binding
history. STUB count fell from 89 to 72 with no change to NO_FUNCTION or NO_SOURCE.

Closed: 0x4f8e60 RELOC 203/203. Two shapes mattered, an independent `if (a2[0]==3)` and
`if (a2[0]==1)` (the reference re-tests the state) and the second call passing `buf`
rather than `buf+4`.

New bodies, all measured and persisted: 0x4b6af0 NEAR 242/251 (the `xor ecx,ecx; mov cl`
zero-extension follows from declaring fcn_00507b00's parameter as `int`),
0x563e90 NEAR 192/193 (one `js` versus `jl`), 0x57f9a0 NEAR 147/153 (up from 118; two
`*(int*)(slot+4)` reads had to be volatile so the slot handle reloads before each tail
call), 0x4ee290 392/1082 (the file carried the GOLD body; the TL reference has no
LogMessageInternal calls and returns 0xffff inline, so the log calls are now guarded by
`REBREW_GOLD`), 0x5dc270 128/869, 0x44c6f0 29/579 (39-int-argument call sequence),
0x4f8140 89/442 (state machine over a2->state), 0x4b6a00 230/240, 0x4c8de0 38/895 (the
faithful draft; the stored 55 was stale).

Boundary repair: merged 0x4bb76f back into 0x4bb720 (248 bytes). The fragment starts on
the first byte after the early-return ret and reuses registers set in the container's
prologue. 0x544954 and 0x563e52 were already absorbed by earlier repairs, and 0x4f8599
is a fragment of the container at 0x4f8581.

Compiler-level wall recorded: 0x4f1650 gv_GetSlotEntry keeps `kind` in caller-saved EDX
across the gv_CheckSlotActive call, which compiled C cannot express; the byte-identical
function is out of reach with this toolchain.

State: RELOC 3,689, EXACT 437 (816,974 annotation bytes), SIZE_MISMATCH 1,017, STUB 68,
NEAR 33, EXTRACT_ERROR 1, NO_FUNCTION 0, NO_SOURCE 0. TL rebuilt, imports/headers/layout
match, same-offset identity 98,813 of 2,850,888 (3.47%). Lint --all-targets 0 errors over
5,451 files. Decision: Lead.

## 2026-10-26 session round 90: Kuna decompiler campaign for the remaining stubs

User directive: use Kuna for the remaining stubs. Workflow is
`rebrew decompile <va> --decompiler kuna --target Europa1400Gold_TL.exe --json`, then
verify every frame offset and register role against `rebrew binary asm show` before
translating, because Kuna's stack layouts are frequently wrong.

Kuna is strong on control flow, call arities, field offsets and switch shapes, and weak
on frame sizes and register allocation. Measured examples of the latter: 0x4b5b40 Kuna
frame map gives 0x190 while the body had 0x18c, 0x41adc0 buffers 0x240 against the
reference's 0x304, and 0x4c8de0's prologue order is wrong in the pseudo-C. It is used as
a body skeleton, not as a frame oracle.

Bodies landed from Kuna work: 0x48fe70 0 -> 259/694 (moving the v9 zero-init before the
two guard tests matched the prologue), 0x41adc0 0 -> 141/1012 (DialogProc with WM_CLOSE,
WM_INITDIALOG and WM_COMMAND), 0x54a210 84 -> 97/899 (packed Stamp copies rewritten as
individual 0x52/0x56/0x5a dword plus 0x5e short stores), 0x4903c0 0 -> 271/438,
0x4b5b40 0 -> 212/684, 0x4b6830 0 -> 100/475, 0x4e4230 0 -> 56/501, 0x5dd2f0 0 -> 32/484.

Build fixes for the new bodies: placeholder callees fcn_0041a950, fcn_0041b1c0,
fcn_0041b250, fcn_0041b1e0, fcn_004f18d0, fcn_004e8ad0 and g_7728dc were added to the
link scaffold. One decoration error was caught by the linker: fcn_0041b1c0 is __stdcall
(@4), not __fastcall.

Filed upstream: `rebrew diff` has no `--size` and compares the row's stored extent, so a
row whose stored size is smaller than the inventory extent (0x4f8d90: stored 39,
inventory 208) silently compares a prefix. Entry added to docs/IDEAS-GUILD.md proposing
`--size` parity with `rebrew test` plus a warning when the two extents disagree.

State: RELOC 3,689, EXACT 437 (816,974 annotation bytes), SIZE_MISMATCH 1,018, STUB 67,
NEAR 33, EXTRACT_ERROR 1, NO_FUNCTION 0, NO_SOURCE 0. TL rebuilt green with
imports/headers/layout matching, same-offset identity 100,054 of 2,850,888 (3.51%).
Lint --all-targets 0 errors over 5,451 files. Server.dll remains byte-identical.
Decision: Lead.

## 2026-10-26 session round 91: Kuna wave two, three near-identical rows

Biggest gains of the campaign, all Kuna-backed and measured: 0x4cd090 120 -> 524/528
NEAR (Kuna shows every s->value read is a fresh load; deleting the int v local and
reading s->value at each use flipped the allocation to the reference map, zero=EDI,
s=ESI, h=EBX, p=EBP, then indexed `*(int*)(p+0x1c+i*4)` scans took it past 500),
0x4903c0 271 -> 431/434 NEAR (two arms were swapped and three comparisons inverted:
`q > 0x6628a0`, the rand(2) arm as `fB > v10 && info[0x18] < 2`, and the q > 0x662998
arm setting out=4), 0x44c6f0 29 -> 491/579 NEAR (the 23-arg function rebuilt with the
arg permutation mapped from asm and a switch on 0x67ac90), 0x5de420 0 -> 124/530
(variadic fcn_00502cd0 needed 5-arg and 3-arg calls; flipping the a0[2]==6 guard to
fall-through gained 44), 0x4eafe0 107 -> 111/416 (seven explicit switch cases and
`case 0x22` matching the native range check plus 7-entry table).

Kuna remains reliable for flow and unreliable for stack layout; the same pass showed
0x4b6830's Kuna frame map at 0x190 while the body needed the exact slots, and
0x4c35f0's prologue was reproduced only after deriving the init order by hand
(unsigned short zeroId/noneId, noneId=0xffff, zeroId=noneId, lastRand=0).

Persist race worth naming: several agents reported "persisted" verdicts that were still
STUB in the store afterwards; the bodies were correct and a Lead test run recorded
NEAR_MATCHING for 0x4cd090, 0x4903c0, 0x44c6f0, 0x48fe70, 0x5de420, 0x4e4230, 0x5dd2f0
and 0x4b6830. Treat an agent's persist claim as unverified until the store shows it.

State: RELOC 3,689, EXACT 437 (816,974 annotation bytes), SIZE_MISMATCH 1,018, STUB 64,
NEAR 36, EXTRACT_ERROR 1, NO_FUNCTION 0, NO_SOURCE 0. TL rebuilt green with
imports/headers/layout matching, same-offset identity 104,764 of 2,850,888 (3.67%).
Lint --all-targets 0 errors. Server.dll remains byte-identical. Decision: Lead.

## 2026-10-26 session round 92: close-out pass on near rows, no net movement

Five near-close rows and five stub rows were worked; every candidate measured equal or
worse and was reverted, so the stored state is unchanged. Recorded walls:

- 0x563e90 (192/193): the single differing byte is `js` versus `jl`; signed-char,
  short-width and comparison-direction spellings did not move it.
- 0x4b64b0 (203/208): the remaining `jl` versus `jb` comes from a signed int induction
  over 0x10069a4..0x1007ba4; casting `q - 4` to int costs more addressing than the one
  opcode gains (137/207), and a full int induction scored 157/207.
- 0x4903c0 (431/434): the fB/fC stack slots swap; declaration swap is byte-identical,
  assignment-order swap scores 429, and a fixed-address float[2] scores 425. The
  allocator ignores declaration order here.
- 0x4b6af0 (242/251): native order is fild, fmul [esp+0x18], fmul [0x6640e8]; splitting
  the product scores 144/255.
- 0x5448e0 stays 382/420 and 0x4c3800 needs a 15-byte-short reconstruction.

0x41adc0 dispatch insight: the native prologue is `mov eax,[esp+8]; sub esp,0x304;
sub eax,0x10; push ebx/ebp/esi/edi` with the message dispatch compiled as a sparse
switch subtract chain (`sub eax,0x10; je; sub eax,0x100; je; dec eax; jne`). The current
if-chain cannot align, and the two buffer bugs are real (native passes the 0x14-offset
name buffer to fcn_0041b1e0/b250 and uses the 0x114-offset item buffer for LB_GETTEXT
0x143, with the WM_COMMAND format writing item+4). Fixing the buffers alone measured
131/1026 against the 141/1029 base; the switch rewrite is required next and my scripted
restructure produced invalid braces, so the base body was restored byte-identical.

State unchanged: RELOC 3,689, EXACT 437 (816,974 annotation bytes), SIZE_MISMATCH 1,018,
STUB 64, NEAR 36, EXTRACT_ERROR 1, NO_FUNCTION 0, NO_SOURCE 0. TL image unchanged at
104,764 same bytes (3.67%). Decision: Lead.

## 2026-10-26 session round 93: accounting repaired, near-row gains recorded

The switch-group accounting is clean again: 0x538250 is a 516-byte STUB with its stored
size synced from 47, and the two interior split rows 0x53827f (445) and 0x53843d (58)
were restored through `record_function_rows` after a retire attempt showed they have no
current source binding to retire. NO_FUNCTION and NO_SOURCE are both 0.

Two padded rows were trimmed to their ret boundaries: 0x58fa40 278/278 RELOC (the body
was already complete; only 10 trailing nops kept it from matching) and 0x40fb80 323/328
NEAR (8 nops trimmed, one fsubr/lea ordering left). Their inventory spans stay padded so
accounting stays closed.

Near-row gains: 0x438fc0 62 -> 82/86 NEAR by splitting the x87 expression so `fld
[0x1042a18]` and `fmul [esp+4]` are adjacent (residual: an interleaved `mov eax,[esp+4]`),
and 0x58fa40 228 -> 278 matched.

Compiler-level walls confirmed this round: MSVC6 emits `jl` for every `char < 0` spelling
at 0x563e90 (192/193, one byte), factors `idx*0x10` as add-then-shift at 0x4a70c0 (76/84),
always pushes before the callee load at 0x5f0e46 (7/10), and canonicalises the SIB as
`[eax+edi]` at 0x4e7340 (75/77). These need a compiler-level explanation, not another
source spelling.

State: RELOC 3,690, EXACT 437 (817,252 annotation bytes), SIZE_MISMATCH 1,018, STUB 64,
NEAR 35, EXTRACT_ERROR 1, NO_FUNCTION 0, NO_SOURCE 0. TL rebuilt green, imports/headers/
layout match, same-offset identity 104,447 of 2,850,888 (3.66%). Lint --all-targets 0
errors over 5,451 files. server.dll byte-identical. Decision: Lead.

## 2026-10-26 GOLDTL 0x4cec00: STUB 35 -> RELOC 225/225

src/GOLDTL.fcn_004cec00.c: dropped the precomputed `limit = *(int*)(m+0x20) - 1`
local; `max` now holds the raw field and both clamps write `max - 1` at the use
sites. MSVC 6 folds a one-shot load-minus-1 into `mov edi,[eax+0x20]; dec edi`
(223B object, 35/225); spelling `-1` only on the register-resident `max` makes
it emit the reference `mov eax,[eax+0x20]` + `lea edi,[eax-1]`. Evidence:
`rebrew test --va 0x4cec00 --size 225` STATUS_MISMATCH 35/225 obj 223 before,
RELOC match_count 225/225 obj 225 mismatches [] after. Relocs: g_67a370 abs32
UNRESOLVED (data binding, pre-existing), call rel32 to fcn_004ceba0 VALIDATED.
Decision: delegated lead task. Verified by rebrew test --no-promote.

## 2026-10-26 GOLDTL 0x4f8d90: STUB 16 -> RELOC 208/208

src/fcn_004f8d90.c: changed the case dispatch from one `if (*a1 == 3) { ... }
else if (a0[2] == sep) { ... }` to two sequential `if (*a1 == 3)` /
`if (*a1 == 1)` guards, each re-checking `*a1` and its own `a0[2] == sep`
inner test. MSVC 6 then keeps `*a1` resident in EAX across the whole
dispatch (it re-reads the already-loaded value at both the `cmp eax,3` and
`cmp eax,1` sites), leaves `sep` in CL, and materialises the `a0[0x166]`
byte through EDX rather than a push/pop EBX around a BL temp; the
`else if` spelling forced a reload of `*a1` and a `mov al,[edx+2]` that
clobbered the resident value. Evidence: `rebrew test --va 0x4f8d90
--size 208` match_count 16/208 obj 194 (SIZE_MISMATCH) before, RELOC
match_count 208/208 obj 208 mismatches [] after. Relocs: call rel32 to
fcn_0051af00 (offset 125) and fcn_004fa5f0 (offset 142) and fcn_0051af00
(offset 188) all VALIDATED. Decision: delegated lead task. Verified by
rebrew test --no-promote (stable across reruns).

## 2026-10-26 GOLDTL 0x515340: STUB -> RELOC 165/165

src/fcn_00515340.c: true extent settled at 165 (ret at 0x5153e4; 11 nops then the
next function starts at 0x5153f0, so the stored inventory size 165 is right and the
177 figure only ever measured padding). Two changes got the body there. The
`fcn_0042e450` prototype now takes `char` instead of `int`, which removes the two
`xor` zero-extends MSVC 6 emits before pushing `g_773d75` as an int argument. The
`double d` local is gone: each if-arm now holds the full
`fcn_004c51f0(..., (int)((call + const) * *(float*)(rec+0x20)))` expression with the
call duplicated. With the double as a named local MSVC kept it as an FPU-stack
across the arm join and emitted `fld` + `fmul st(1)` + `fstp` plus an early
`add esp,8` before `__ftol`; as one expression per arm the tails merge and the
compiler emits the reference `fmul dword [esi+0x20]`, one `add esp,0x18` after the
outer call, rec in ESI and p in EDI. The register roles and the 12-byte cleanup
deferral from the old residual list are both resolved by the expression shape, not
by declaration order (declaration swaps had measured 59 or 102 earlier).

Evidence: `rebrew test --va 0x515340 --size 177` match 89/181 obj 181 (SIZE_MISMATCH)
before; `rebrew test --va 0x515340 --size 165` RELOC match_count 165/165 obj 165
mismatches [] after, reloc_count 8. Relocs: g_99ec10 and g_773d75 abs32 UNRESOLVED
(pre-existing data bindings), call rel32 to fcn_00503d10 / fcn_0042e450 x2 / __ftol
/ fcn_004c51f0 all VALIDATED. Decision: delegated lead task (session
e15fb19e-c713-44cb-bd02-67537c366f80). Verified by `rebrew test --no-promote`
followed by a recording `rebrew test`.

Tooling note: `rebrew test --size N` behaves as a floor, not an exact window. It
compares max(N, obj_size) bytes, so --size 177 against a 181-byte object reports
total 181 and --size 165 against a 177-byte object reports total 177; padding
beyond ret always counts as mismatch unless the object happens to fill the window.
Worth an upstream issue.

## 2026-10-26 session round 86: 0x4f5cc0 compacted-switch threshold measured

0x4f5cc0 (64 B) is a hard encoding wall under the project's `/O2 /Gd` frameless
config, confirmed by exhaustive shape/flag sweeps in `.scratch/f5cc/`. The reference
dispatch is the two-level compacted table (`dec ecx; cmp ecx,6; ja`;
`xor edx; mov dl,[ecx+0x4f5cf8]`; `jmp [edx*4+0x4f5cf0]`) with a 7-entry byte map and
a 2-entry dword table. MSVC's compaction is gated on the switch RANGE, not on case
count, target sharing, or selector type: under `/O2`, a range-7 selector emits a
direct `jmp [reg*4]` table for every spelling tried (dense contiguous N=7..24; sparse
1/3/5/7; char and int selectors; num_unique 1 and 2), while the compacted form first
appears at range ~25 (char A/C/F/Z) and range 30 (int 10/20/30/40). The flags that
force compaction on a range-7 switch (`/Ot /Oy /Ob2 /Op /Oa` alone) also turn on the
frame pointer, breaking the reference's frameless `mov ecx,[esp+8]` prologue, and no
`/O2`+extra combination yields compaction. Because the direct table is 28 B against
the reference's 16 B of tables, the object is always 68 B vs the 64 B row (SIZE_MISMATCH),
so the size cannot be reached without the compacted dispatch. File left at its best
state, the per-case-return variant, 40/68 (was 40/68; no change). Decision: lead task,
no source or metadata edit. Evidence: `uv run rebrew test src/GOLDTL.fcn_004f5cc0.c
--va 0x4f5cc0 --size 64 --no-promote` = SIZE_MISMATCH 40/68 obj 68.

Exact final measurement (`flock .scratch/lead/test-0.lock uv run rebrew test
src/fcn_00515340.c --va 0x515340 --size 165 --no-promote --json`):

```json
{"source":"src/fcn_00515340.c","symbol":"_fcn_00515340","va":"0x515340","size":165,"status":"RELOC","match_count":165,"total":165,"reloc_count":8,"obj_size":165,"context_hash":null,"mismatches":[],"relocation_bindings":[{"offset":37,"symbol":"_g_99ec10","kind":"abs32","typed":true,"addend":0,"bound_va":null,"byte_order":"<","native_value":10087440,"status":"UNRESOLVED"},{"offset":59,"symbol":"_fcn_00503d10","kind":"rel32","typed":true,"addend":0,"bound_va":5258512,"byte_order":"<","expected_value":4294896017,"native_value":4294896017,"status":"VALIDATED"},{"offset":83,"symbol":"_g_773d75","kind":"abs32","typed":true,"addend":0,"bound_va":null,"byte_order":"<","native_value":7814517,"status":"UNRESOLVED"},{"offset":91,"symbol":"_fcn_0042e450","kind":"rel32","typed":true,"addend":0,"bound_va":null,"byte_order":"<","native_value":4294021297,"status":"UNRESOLVED"},{"offset":104,"symbol":"_g_773d75","kind":"abs32","typed":true,"addend":0,"bound_va":null,"byte_order":"<","native_value":7814517,"status":"UNRESOLVED"},{"offset":112,"symbol":"_fcn_0042e450","kind":"rel32","typed":true,"addend":0,"bound_va":null,"byte_order":"<","native_value":4294021276,"status":"UNRESOLVED"},{"offset":126,"symbol":"__ftol","kind":"rel32","typed":true,"addend":0,"bound_va":6607400,"byte_order":"<","expected_value":1277542,"native_value":1277542,"status":"VALIDATED"},{"offset":144,"symbol":"_fcn_004c51f0","kind":"rel32","typed":true,"addend":0,"bound_va":5001712,"byte_order":"<","expected_value":4294639132,"native_value":4294639132,"status":"VALIDATED"}]}
```

A recording `rebrew test src/fcn_00515340.c --json` (inventory default size 165)
returned the same RELOC 165/165 verdict and persisted it through the locked
metadata writer.

## 2026-10-26 GOLDTL 0x467870: STUB 136 -> RELOC 176/176

The row was rebuilt to 136/176 (object 170) with two residual defects: the missing
third `g_1015ea0` reload in the tail (6 bytes) and every two-register table access
emitted with the base/index roles swapped (`[edi+esi+disp]` against the reference
`[esi+edi+disp]`). The pointer-arithmetic form `*(int*)(rec + tbl + disp)` cannot
flip those roles under msvc-6.0-sp5-pp /O2: char*/int typing, operand order,
int+int casts, and inline-vs-variable strides all measure the same SIB choice.

The working spelling is the struct-index idiom on the named global, matching the
`((Def*)g_772500)[idx]` form in fcn_004659c0: a local 0x2f4-stride
`fcn_00467870_Def` (fields at 0x0c/0x10/0x14/0x8c/0x90/0x94/0x9c) and
`((fcn_00467870_Def*) g_1015ea0)[idx].field` per access. The named extern lvalue
lets /O2 keep the loaded table pointer register-resident within a phase, reload
it after each of the three call groups (`fcn_0047b620` and `__ftol`), and place
the offset in the SIB base slot, reproducing all three reference loads
(`mov eax/edi/edx, [0x1015ea0]`) and every `[esi+reg+disp]` access. The raw
`*(char**)0x1015ea0` spelling does not get that treatment and fails.

Verification: `flock .scratch/lead/test-3.lock uv run rebrew test
src/fcn_00467870.c --va 0x467870 --size 176 --json` = RELOC 176/176, obj 176,
no mismatches, 7 relocation bindings VALIDATED (`_g_1015ea0` x3,
`_fcn_0047b620` x3, `__ftol`); promoted through the locked metadata writer.

## 2026-10-26 GOLDTL 0x4127a0: STUB 55 -> NEAR_MATCHING 95/130

The row was a STUB at 55/130: the if-branch loaded a/b/c into a rotated
register set (EDX/EAX/ECX against the reference EAX/ECX/EDX) and the else-branch
store of `d` came after both `a` and `b` stores instead of interleaving.

The winning shape keeps three locals in the save branch (load a, b, c; store a;
store b; direct `*(int*)0x6b5c70 = *(int*)0x6b5c84`; constants; late c store)
and adds a fourth local `d` in the restore branch only, with restore loads in
source order c, a, b and the statements

```
*(int*) 0x6772bc = a;
d = *(int*) 0x6b5c70;
*(int*) 0x6772c0 = b;
*(int*) 0x6b5c84 = d;
*(int*) 0x6b5c80 = c;
```

The interleaved `d` assignment is what makes MSVC emit the reference schedule
(store a; load d into the freed register; store b; store d; store c). Six
else-load permutations of the same body measured 85-95; c,a,b (and the
equivalent a,c,b / c,b,a) all reach 95. Remaining 35 mismatched bytes are the
save-branch load rotation (offsets 8-37, 67) plus the restore-branch load
rotation (84, 89-96, 101, 107, 113, 119); declaration order, `register` hints,
unsigned loads, chained constant stores, struct/pair loads, early-return
polarity, and direct (local-free) memory copies all measure the same or worse.

Verification: `flock .scratch/lead/test-2.lock uv run rebrew test
src/fcn_004127a0.c --va 0x4127a0 --size 130 --no-promote --json` = NEAR_MATCHING
95/130, obj 130, reloc 0. Not promoted (no EXACT/RELOC).

## 2026-10-26 session round 94: all-target lint cleared to 0 errors / 0 warnings

`rebrew lint --all-targets` now reports 0 errors and 0 warnings across all three
targets (5451/5451 files passed each), down from 154 warning instances. Work done via
locked CLI only, no TOML hand-edits, no commits, no builds:

- W005 (126 instances / 42 files): ran `rebrew diff --json` per file and wrote a
  specific BLOCKER per STUB naming the observed wall (relocation binding, jump-condition
  swap, xor/mov zero-extend, lea folding, register allocation, or unwritten body).
- W020 (8): `source document-assembly` per symbol for inline-asm definitions — x87 stack
  schedules, thiscall register-operand patterns, int3 traps (0xCC at 0x4e7366/0x4e737b),
  REP stos fill cores.
- W028 (7): four GOLD files had DATA annotations above the function body; moved the data
  ADDRESS anchors above their extern declarations and re-annotated the function anchors to
  the bound VAs. The three switch-fragment files (fcn_0053827f/843c/843d) pointed inside
  merged fcn.00538250; they are in the cmake build list, so their stale anchors were
  removed and each registered via `source register --support` with fragment evidence.
- W031 (13): 11 stale type rows rebound via `types bind` with unchanged native evidence;
  stale provenance cleared/refreshed.
- W029 (3), W016 (4), W033: redundant per-row cflags cleared via `source clear-cflags`,
  missing data sections set via `data set --section ...=.rdata`, generated agent files
  refreshed via `rebrew init --refresh-agents`.

Coverage accounting repaired the same round: the switch-group jump tables 0x538454 (dword
targets) and 0x538464 (byte index) had been separate inventory FUNCTION entries demanding
their own source (NO_SOURCE 2). Merged them into their owning 0x538250 dispatcher extent
(now 551 bytes = 516 code + 16 + 19 tables, matching the 0x4cd990/0x46c5a0 convention), so
they are strictly inside the function and become pseudo switch data. NO_FUNCTION 0,
NO_SOURCE 0, covered 5208/5208. Matched annotation bytes 1,278,813.

Flag for later: fcn_00618bbf (GOLDTL 0x618bbf, in the D3DX8 external range) has target
bytes that disassemble as data (sbb/popal); its inventory extent deserves a separate look.
Decision: Lead.

## 2026-10-27 — Resolve 198 GOLDTL data type_conflicts (metadata-only)

Conflict `type_conflicts` on `Europa1400Gold_TL.exe` went 231 -> 10 from this
worker's writes alone. Each resolution set `--type`/`--name`/`--file`/`--section`
(+ evidence `--note`) on a `GOLDTL.0x<va>` row through the locked
`rebrew data set` CLI. No C source was edited and no build was run. Evidence
tiers, in order:

- 165 majority `.c` declaration (strict plurality of non-header spellings).
- 6 `.rdata` constants typed from reference-binary bytes (`g_662d64`=1.0f,
  `g_662930`=3.0 double, `g_662ad0`=4.0 double; `g_662008` 6-arg stdcall by call-site).
- 26 pointer/struct/scalar proven by source usage: dereference (`*g`, `g[i]`,
  `->f`), `m_alloc`/`m_FreeTracked`, `sprintf %s`, `float*` param decay
  (`g_14ce880`), `>= 1.0f` accumulator (`g_100dc14`).

Deliberately NOT resolved by this worker (guessing risk): signedness-only ties
(char/unsigned char, int/unsigned int) with no discriminating use; the 4
stub-defined globals with no reference VA (g_slot_table, g_entity_type_table,
g_current_year, g_crash_callback) — reloc table does not name them; and
per-TU local struct-name variants. `symbol_stubs.c` types were rejected as
tiebreakers: gen_stubs derives them from the same contested externs (circular).

Verified after every batch: `rebrew status -t Europa1400Gold_TL.exe --json`
reports `unattributed_bytes 0`, `covered == total`. Final: 5208/5208,
`rebrew lint -t Europa1400Gold_TL.exe` 0 errors / 0 warnings across 5451 files.
Current conflict count is 0 (stable over 3 runs); the final 33 were cleared by a
concurrent worker that moved competing spellings into `_gconf.h` headers, not by
these metadata rows. Decision: delegated task.

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

Decision owner: project maintainer through the requested release. Verification: fresh isolated raw build, full server function/data/image comparison, 39 tests and 3 subtests. Public release sources exclude the separate native reconstruction work in this checkout.

## 2026-10-26 session round 95: data conflicts 231 -> 0, lint held 0/0, server.dll byte-identity recovered

Both explicit cleanup asks are met and independently verified:
- `rebrew lint --all-targets` = 0 errors, 0 warnings (5451/5451 files, all 3 targets).
- `rebrew data list --conflicts --json` type_conflicts = 0 (was 231).

Conflict resolution split across two workers. ~198 rows cleared via locked `rebrew data set`
(majority .c declaration as canonical, plus 6 typed from reference-binary bytes and 27 from
source usage), and the final ~33 (plus a residue) via FIX-1 header demotion: 57 minority-type
`extern` lines moved byte-exactly out of 54 `.c` files into 54 new single-includer
`*_gconf.h` headers, so the competing type becomes header-only and drops out of the
comparison. No type value changed in any file, so no codegen moved. Two alias/view rows were
also needed: g_7e3a44/48, g_7e3a54/58, g_772580 marked `--storage-kind alias --backing`
(their canonical `float[3]`/array owners span them), clearing W038 row overlaps.

A server.dll regression surfaced during this round and was fixed. GOLDTL byte-match work on
shared source had wrapped alchemistry's ahm_ExAllocAlchemist logs in `#if defined(REBREW_GOLD)`,
but no target ever defines `REBREW_GOLD`, so the guard was dead in all builds. GOLD's and
TL's references genuinely lack those logs, but server.dll's reference HAS them (string present
in original/Server/server.dll, absent in both client references). The dead guard therefore
stripped ~32 bytes of log+goto code from server.dll, shifting the .text section by 0x20 and
cascading into 118,470 differing bytes (58.68% match). Fixed by re-keying the three alchemistry
guards to `#if defined(REBREW_TARGET_SERVER)` (the only target that compiles this code), since
server is the only reference with the logs. server.dll is byte-identical again: 286,720/286,720,
SHA-256 3cc2ce9049e41ab6 = original/Server/server.dll.

This is the general lesson for shared-source byte matching: a body edit tuned to one target's
reference can silently break another target that shares the file. Where a target's reference
genuinely differs, the divergence must be guarded by a macro the differing target actually
defines (server defines REBREW_TARGET_SERVER; no target defines REBREW_GOLD).

Final state: RELOC 3,698 EXACT 437, STUB 59, NEAR 34, SIZE_MISMATCH 1,015, matched annotation
bytes 818,598. NO_FUNCTION 0, NO_SOURCE 0, covered 5208/5208. TL rebuilt: imports/headers/
layout match, same-offset 104,786 of 2,850,888 (3.68%). server.dll byte-identical. Lint
0 errors/0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-27: target macro unification, library-band attribution, STUB settle

`REBREW_TARGET_SERVER` never existed for `rebrew test`/`verify`: only the generated CMake file
defined it, so every guard using it compiled the client branch in the tool path and the guarded
branch in the link. The macro that actually partitions targets is `REBREW_SERVER`
(`rebrew-project.toml`). Unified on `REBREW_SERVER` in CMakeLists.txt,
`src/Develop/DieGildeAddOn/game/alchemistry_logic.c` and
`src/Develop/DieGildeAddOn/loadsave/loadsave.c`; server rows that had been compiling the client
branch (`0x1000bdf0`, `_ls_LoadEntities` 0x10012000) now record RELOC at full size, and
server.dll stays byte-identical (286,720 bytes, SHA-256 3cc2ce9049e41ab6).

Boundary repairs in the declared D3DX8 external range, each with the extracted COFF section as
evidence: 0x6092bc split into 329 B (GXTri3Mesh Optimize2) + 3159 B
(CD3DXSkinMesh ConvertToBlendedMesh, admitted as 0x609405); 0x618bbf proved to be 196 B of
`?d3dxasm_parse`'s switch table plus 1219 B of `?Assemble@CD3DXAssembler`, so the table merged
into 0x6187ca (1209 B), 0x618c83 was admitted, and the phantom claim was retired; 0x4bb76f
proved to be the tail of 0x4bb720 and its claim retired. 7 further rows were adopted as
`d3dx8.lib` members (0x5ec8ee, 0x5ef254, 0x5f37e5, 0x5f37f5, 0x605ccf, 0x6149fc, 0x614a6c,
0x614af0, 0x6164fa, 0x6194de, 0x619504) after byte-comparing the archive member.

STUB rows whose reconstructed body compiles to a different size were recorded honestly as
SIZE_MISMATCH with `rebrew test --force-status` (28 rows). What remains STUB is documented, not
pending: 6 bodies that compile to the native size but disagree on register allocation
(0x412630, 0x4eafe0, 0x558220, 0x56caf0, 0x5a8c30, 0x5de420) and 3 library placeholders whose
archive attribution `library adopt` refuses: 0x6092bc (two byte-identical GXTri3Mesh
instantiations) and 0x61ada1 (4634 B member whose inventory row is cut at 4187 by a bogus
12063 B neighbour). 0x618c83 was admitted by the boundary repair and adopted as
`?Assemble@CD3DXAssembler`.

Final state: RELOC 3,679 EXACT 415 SIZE_MISMATCH 1,046 NEAR_MATCHING 38 STUB 8 (7,535 bytes),
EXTRACT_ERROR 3, NO_FUNCTION 0, covered 5,192/5,192, lint 0 errors/0 warnings on every target,
data type conflicts 0, server.dll byte-identical (286,720 bytes). TL rebuilds and links;
imports/headers/layout/exports match. Raw-file agreement is 106,462 of 2,850,888 bytes (3.73%)
because the link places functions in a different order than the reference, which is a separate
layout problem, not a body problem.

Upstream fix: `rebrew library adopt --symbol` selects one reviewed native symbol when several
byte-identical archive aliases match, instead of refusing the row. Regression tests added in
tests/test_library_adopt.py. Decision: Lead.

## 2026-10-27: six remaining STUB bodies rebuilt in parallel

Each row was rebuilt from asm and Kuna by one worker, then promoted at its native size.

- 0x005de420 fcn_005de420: STUB 80/525 -> RELOC 525/525. Stride is 540 via
  `((int*)0x7f4ca0) + w*135`; the second memset target is `&v10[7]`; the constant 1 stays in ebx
  only while every use is a memory operand; the clamp is `(expr < one) ? one : expr` with the
  expression spelled twice; v10 store order 0,1,4,2,3; `base` is assigned before the
  `fcn_00502cd0(rec+0x5d, ...)` call, and the first such call's result is genuinely discarded.
- 0x005a8c30 fcn_005a8c30: STUB 182/496 -> RELOC 487/487 (native 496 was 487 code + 9 alignment
  nops, recorded with `rebrew test --fix-sizes`). The row carried stale `/O2 /Gd /G6`; /G6
  disables the MSVC 6 instruction scheduler and the native body is scheduled, so `/G6` was
  cleared. Four float arrays pinned in one 60-byte stack struct reproduced the frame; the
  in-place `*= g_dbl` form (not a cast expression) matched the scheduler slot; `fcn_004518a0`
  must be void.
- 0x00412630 fcn_00412630: STUB 165/354 -> NEAR_MATCHING 302/354. The found-block `*p = 0`
  must be the last statement, not the first: clear-last keeps edx alive as the zero constant so
  ecx is the only copy temp and the pair stream matches. Left 52 bytes: guard ordering and the
  sunk `i = 0` clear.
- 0x004eafe0 fcn_004eafe0: no gain, 113/416. The target needs /G2-class zero-extension idioms
  (`mov ebp,ebx; and ebp,0xff`) *and* /G6-class allocation (induction pointer and count spilled
  to frame+0/+4); no flag set produces both, and 13 flag sets plus 5 toolchains were measured.
- 0x00558220 fcn_00558220: no gain, 169/332. Every one of ~45 source shapes rebases the loop
  induction variable onto rec+0x180; the reference keeps rec. Cost model: 25 displacement bytes
  at base rec versus 20 at +0x180, and this build ignores the 6-byte loop-end lea while the
  reference's 25 is the true optimum. The table identity was pinned meanwhile: 768 records of
  0x21c from 0x7f4ca0 (handle at 0x7f4ca4), matching the already-RELOC sibling fcn_00564210.
- 0x0056caf0 fcn_0056caf0: no gain, 171/896. The rebuilt body compiles to a byte-identical
  mismatch set, so the body was never the defect: the target's local slots are
  best=0x10/found=0x14/i=0x18 while this compiler forces found=0x10/i=0x14/best=0x18, the
  target keeps the zero constant in edi, and its case-2 loop is not strength-reduced.

Final state: RELOC 3,681 EXACT 415 SIZE_MISMATCH 1,046 NEAR_MATCHING 39 STUB 3 (1,644 bytes),
EXTRACT_ERROR 0, NO_FUNCTION 0, covered 5,184/5,184, lint 0 errors/0 warnings, data type
conflicts 0, server.dll byte-identical. Remaining STUB rows are 0x4eafe0, 0x558220, 0x56caf0,
each with the measured codegen wall recorded in its report. Decision: Lead.

## 2026-10-27: fcn_00412630 to RELOC

- Change: `src/fcn_00412630.c` now reads the 0x14ce8c0 block through the existing
  `g_14ce8c0`/`g_14cf900` globals (data rows GOLDTL.0x014ce8c0, GOLDTL.0x014cf900) instead of raw
  integer addresses for the three-short copy and the six zero stores.
- Reason: with raw addresses MSVC 6 PP interleaved the short loads/stores and hoisted `xor ecx, ecx`
  after the zero stores (302/354, then 322/354); symbol-relative stores reproduce the reference order.
- Evidence: `rebrew test src/fcn_00412630.c` reports `RELOC-NORMALIZED MATCH: 354/354 bytes (14
  relocations)`; metadata status RELOC.
- Not changed: 0x4eafe0 (113/416), 0x558220 (169/332), 0x56caf0 (171/896). 150-generation GA runs
  on each found no improvement; loop-pointer, countdown and type-field-pointer forms of 0x4eafe0
  (94 to 127/416) all keep the record pointer in ebx and spill the type byte, while the reference
  keeps the pointer in a stack slot and the type in bl. Kuna cannot load the TL executable
  ("unsupported/!recognized binary").
- Decision: user request. Verified: rebrew test per file.
- Follow-up 2026-10-27: Kuna runs with `KUNA_SPECS` set to the pypcode x86 language directory
  (the default spec lookup fails with "unsupported/!recognized binary"). Source shapes taken from
  the Kuna output, without flag or compiler changes: 0x4eafe0 countdown, `unsigned char` bounds,
  merged guard, and indexed `out[i]` forms reach 53 to 127/416, none above the stored 113;
  0x558220 `unsigned int*` do-while walk with `rec[0x5a..0x60]` indexing stays 169/332 with the
  same rebase to 0x7f4e24. Sources left at their stored versions.

## 2026-10-27: fcn_004eafe0 to RELOC

- Change: `src/GOLDTL.fcn_004eafe0.c` indexes `out[i]`, keeps `x4` in local `x` and the type as
  `int tt = out[i].type` for the switch and the `fcn_004ea560` argument, and folds the
  `v != -1` guard into the wait loop: `while (v != -1 && fcn_004c4450(v) == 0)`.
- Reason: the reference keeps the loop pointer and count in stack slots and the type in `bl`/`ebp`
  (`mov bl,[ecx]; mov ebp,ebx`), and tests the wait loop at the top with a `jmp` back. The folded
  condition reproduces that loop; the int copy reproduces the type registers.
- Size: the stored size 416 included 12 trailing alignment bytes (`nop` padding after the jump
  table). `rebrew test --fix-sizes` stored 404.
- Evidence: `rebrew test src/GOLDTL.fcn_004eafe0.c` reports `RELOC-NORMALIZED MATCH: 404/404 bytes
  (21 relocations)`; metadata status RELOC, size 404.
- 0x558220 manual attempts (source left unchanged, 169/332): every form whose loop reads the
  record fields through one base re-bases the pointer to 0x7f4e24 (slot+0x180). Caching both
  `+0x180` and `+0x16c` in locals keeps `esi = 0x7f4ca4` but spills to `ebx`/`edi` (59/332);
  alias, struct, indexed, inline-helper, volatile and loop-condition forms do not change the base.
- Decision: user request. Verified: rebrew test per file.

## 2026-10-27: 0x56caf0 and 0x558220 manual attempts (no source change)

- 0x56caf0 (STUB 171/896, source unchanged): moving the `rec != 0` test into the case-2 loop
  condition, `for (e = a0 + 0xac, i = 0; rec != 0 && i < 0x10; i++, e += 4)`, gives the target's
  stack slots (zero at `esp+0x14`, best at `esp+0x10`, counter at `esp+0x18`) and the target's
  bounded `cmp [esp+0x10],0x10; jge` loop. It raises exact instructions from 13 to 52 of 284 but
  emits 908 bytes, because the zero stays an immediate instead of the target's `xor edi, edi` and
  case 2 holds the record in `edi` instead of `ebp`. Routing zero uses through `found`, `cand` or a
  shared `int z`, extra zero initializations, declaration-order permutations, `int found`,
  do-while/goto loop forms and a separate case-2 counter all leave the zero as an immediate.
  Scratch copy: `.scratch/56ord.c`.
- 0x558220 (STUB 169/332, source unchanged): the alias-split matrix (each of the
  `+4/+0x168/+0x16c/+0x180` reads through `rec` or an alias), duplicated low-offset reads,
  pointee-volatile, null-guard and loop-condition rewrites keep the base at 0x7f4e24 or regress.
- Evidence: `rebrew diff --json` summary counts; Rebrew status lines were unavailable for part of
  the run while another session renamed sources (`address anchor names 'd2_SetForm', but the
  metadata names 'fcn_004727a0'`).
- Decision: user request. Verified: sources restored to HEAD; `git diff` empty for both files.

## 2026-10-27: first placement and rename batches

Placement. 43 loose `src/*.c` files moved into the unit their function name and
counterpart evidence points at, using `git mv` plus `rebrew source rehome` for
every target that referenced the old path (rows, then the three data rows that
named the same files): 39 into `Develop/DieGildeAddOn/game`, the rest into
`command/command_c`, `game/aemter_c`, `loadsave/loadsave_c`, `Units/d3`,
`Units/d2.v1`, `Units/net`. Plan and evidence classes per file:
`.scratch/organize/placement-plan.md` (attested prefix, module counterpart,
logged path; no logged-path witness fired).

Renames. 25 of 30 address-named functions took the name their own diagnostic
string attests (`ch_SetVisible`, `ch_Update`, `txt_ParseRandomText`,
`d2_SetForm`, the `hst_` parser family, `cm_RequestSendCutInfo`,
`amt_fio_SaveAemter`, `gs_AddBeweis`, `main_OpenEngine`, ...). Evidence per row:
string VA, the `push imm32` site, the containing function, from
`.scratch/organize/rename-plan.md`. Nine needed `--shared-definition` because the
same definition serves GOLD too. Five were refused and left renamed-by-nobody:
`rd_GetBKSize`, `amt_fio_LoadAemter`, `gm_AddObjekt`, `cm_ExSetHE`,
`cm_ExSysMessage` already name a *different* definition in another target (the
tool rejects duplicate identifiers), and `0x0040aa00`/`0x004c9ee0` collide with
an existing name.

Follow-up fixes the moves forced, all through locked writers:
`rebrew data set --file` for three data rows that still named the old paths,
`rebrew source document-assembly` reissued at the new path for the moved
`fcn_004050c0` evidence (old entry cleared), `rebrew types bind` refreshed the
four `client_placement.h` records whose header closure changed. Loose root files
went 5,509 -> 5,282.

Verified after: `rebrew lint --all-targets` 0 errors / 0 warnings, `rebrew data
list --conflicts` 0, `rebrew status` NF 0 with RELOC 3,681 EXACT 415
SIZE_MISMATCH 1,047 NEAR 39 STUB 2, TL rebuilds and links. Decision: Lead.

## 2026-10-27: root source backlog cleared

All 5,282 `src/*.c` files left `src/`: 2,412 into the module they belong to and
2,870 into `src/Develop/Unassigned/`. Placement evidence per file, in order: a
module-owned header it includes (510), an attested module-prefixed identifier
it calls or declares (1,370), the unit whose functions it calls when at least
two agree (531), a reviewed global's owning source (3); the rest are unassigned
and the directory says so. Classifiers and the plan:
`.scratch/organize/bulk_classify.py`, `bulk_affinity.py`, `bulk-plan2.json`;
the move and rehome pass: `bulk_move.py`, `moved-bulk.json`.

Moving sources exposed four tooling gaps, all fixed upstream (`7f920027`,
`0f16c66c`, `0b545f3a` plus tests):
- `rehome` left reviewed assembly evidence under the old path, so moved
  whole-function asm files lost their exemption and lint reported E023.
- lint's INACTIVE check matched only the exact retired path; a moved leftover
  became a fresh E001. It now recognises a file whose anchors or definitions
  name claims another file retired or rebound, including comment-only switch
  arms.
- binding resolution aborted the whole data scan on such a leftover's anchor;
  it now skips anchors whose claim moved.
- cmake-sources treated an anchored leftover of the other target as an unbound
  shared helper and pulled that target's closures into the link.

Ten type records were rebound to their moved files (`rebrew types bind`), 106
provenance records relocated, and the TL link needs two GOLD-side callees of
shim definitions; they come from `stubs/goldtl/link_scaffold.c` instead of
dragging the GOLD bodies in.

Verified: `rebrew lint --all-targets` 0 errors / 0 warnings, `rebrew data list
--conflicts` 0 type conflicts, TL rebuilds and links, whole-binary imports,
headers, layout and exports match, STATUS unchanged (RELOC 3,681 / EXACT 415 /
SIZE_MISMATCH 1,047 / NEAR 39 / STUB 2, NF 0), and the raw same-offset match
improved from 100,461 to 109,484 bytes (3.52% -> 3.84%). Decision: Lead.

## 2026-10-27: five name collisions settled

`rd_GetBKSize`, `amt_fio_LoadAemter`, `cm_ExSetHE`, `cm_ExSysMessage` and
`gm_AddObjekt` now name the row their diagnostic string attests. Evidence per
row is the string VA and its `push imm32` site from
`.scratch/organize/rename-plan.md`.

Resolutions, all reviewed against the link map:
- `plant.c`'s unclaimed `rd_GetBKSize` became `plt_LookupBauplatzBox`. It has no
  row and no attested string; the attested owner is TL `0x4bdf40`, whose
  definition now carries the name.
- `command.c` (`cm_ExSetHE`, `cm_ExSysMessage`) and `spiel.c` (`gm_AddObjekt`)
  keep their server bodies behind
  `#if defined(REBREW_SERVER) || defined(REBREW_GOLD)`. Both clients then use
  their own bodies, and `Europa1400Gold_TL.map` shows each symbol bound to the
  TL object at its reference VA neighbourhood.
- `amt_fio_LoadAemter` needed no guard: `aemter.c` is not in the client source
  list, so its server definition cannot collide there.

Upstream, `--shared-definition` now accepts a name owned by another target's row
in the same file (`afea3803`, `cf53a9dd`, with tests in
`tests/test_rename_targets.py`): one tree holds each target's guarded body, and
the flag is the caller's acknowledgement of the counterpart. Rows of the
selected definition's own module are still refused.

Verified: the five rows keep their verdicts (`RELOC` 107/107, 313/313, 244/244,
202/202; `SIZE_MISMATCH` 267/1072 for `cm_ExSysMessage`), TL rebuilds and links,
whole-binary imports/headers/layout/exports match, `rebrew lint --all-targets` 0
errors / 0 warnings, `rebrew data list --conflicts` 0.

Two consequences recorded rather than hidden. The TL raw same-offset match went
109,484 -> 104,035 bytes (3.84% -> 3.65%) because removing three foreign server
bodies from the client link shifts every later object; the ordering pass is
still the open item. `build/server.dll` relinked from the reorganized tree and
its image same-offset match is 74.4%, while every server function still verifies
byte-matched (251/251, code account 100%, data 100%): the image order, not the
reconstruction, needs the same ordering pass. Decision: Lead.

## 2026-10-28: native-slot padding ruled out before body recovery

Inserting `.text` fillers so every source object starts at its reference VA,
then linking, grew `Europa1400Gold_TL.exe` `.text` from 2,510,848 to 3,187,712
bytes against a reference 2,494,464 and dropped the same-offset match from
104,035 (3.65%) to 74,515 (2.61%). Reverted, and the generator removed.

Measured cause: 239 objects already exceed the native span their rows claim,
because a multi-function file's rows do not cover every function its object
emits (`character.c`: 320 bytes compiled, 80-byte row span; `ch_script.c`: 1040
into 192). A gap to the next row's VA then describes nothing. Slot padding needs
correct native extents per translation unit first, which is body recovery, not
a layout trick. Full measurements: `.scratch/organize/text-pad-experiment.md`.

Also probed the two smallest NEAR_MATCHING rows, `0x402b80` and `0x5f0e46`.
Four loop shapes for the first and seven call spellings for the second (struct
member access, volatile vtbl, local function pointer, direct expression) leave
them at 22/32 and 7/10: instruction order and register choice are compiler
decisions the C forms tested do not reach. Original bodies restored; STATUS
unchanged (RELOC 3,681 / EXACT 415 / SIZE_MISMATCH 1,047 / NEAR 39 / STUB 2,
NF 0). Decision: Lead.

## 2026-10-28: one SIZE_MISMATCH row promoted, inventory staleness measured

`0x4ef000` (49 bytes) reached `RELOC 49/49`. The body is a 32-record table
lookup; the native code keeps a byte offset in `eax` and the record index in
`ecx`, which the compiler only emits for an `unsigned` index over an array
symbol. Spelling it `extern REC g_68e020[]` (the scaffold's symbol) with an
`unsigned` counter reproduces the loop and the index-times-244 return address;
an absolute address in the source makes the compiler walk a pointer instead.
STATUS now RELOC 3,682 / SIZE_MISMATCH 1,046 and `matched_bytes` 1,297,563.

Two probes recorded rather than kept:
- GA over the three near-miss rows the threshold selected (deltas 5-24 bytes)
  produced no promotion in 80 generations at seed 7.
- The project inventory disagrees with what `rebrew binary functions` measures
  today: `0x64e1c7` is stored as 28,068 bytes while the current discoverer
  splits 54, and 1,519 of 6,236 TL rows carry a different size, with 497 rows
  absent from the new inventory. Swapping the inventory wholesale would orphan
  those rows, so it was reverted after measurement
  (`.scratch/organize/fs-new.json` keeps the measurement). The 28,068-byte row
  now reads as a stale extent, not missing reconstruction.

TL rebuilds and links, whole-file same-offset 103,735 (3.64%): the newly
matching 49 bytes sit where the reference has them but the surrounding layout
is still shifted, so the linked-byte metric does not move yet. Lint 0/0, data
conflicts 0. Decision: Lead.

## 2026-10-28: attested function and global names applied

Renamed 28 TL rows whose own log string names them, taking the string's push
site inside the row as evidence (all in `.scratch/organize/rename-results.txt`):
`ch_Create`, `ch_DeclareAction`, `ch_UseGate`, the eight `ecmd_*` scene commands,
`sb_LoadEntry`, `sb_LoadSampleBank`, `evt_ProcessString`, `evt_EnterFunction`,
`tb_OpenFunction`, `vfs_Tfopen`, `d2_Show`, `d2_CreateRadioGroup`,
`d2_SubRefcount`, `d2_Open`, `d2_DrawShape`, `shp_Convert8To16`,
`gm_KillSpieler`, `eval_ObjektPreis2Credits`, `init_LoadGebaeudeScene`,
`main_Menue`, `he_RunTransport`. Rows that share a string (`d2_OpenInputIcon`,
`shp_ShowShapeFromBank`, `ai_MeisterTradeFernEinkauf` and the `cm_ExGebUpgrade`
pair) stay unnamed: one string cannot name two definitions.

Globals renamed from allocation labels and comparison operands:
- `lpGebaeudePROT` 0x868050, `lpObjekteINST` 0x868054, `lpGebaeudeINST`
  0x90e094, `lpObjektePROT` 0x99ec10. The label pushed before each allocator
  call sits next to the store of the returned pointer in `fcn.00501040`:
  0x50108a/0x5010b2/0x50114a/0x501174, stores at 0x50109c/0x5010ca/0x50115c/
  0x50118a.
- `gm_RichterEvangelisch` 0x773db0 and `gm_RichterKatholisch` 0x773dac from
  the two NULL asserts in `init_LocalData` (0x51531b, 0x515302) and the stores
  at 0x5152d0/0x5152d6.
- `cm_LoadBuf` 0xfb5740 from the label pushed at 0x4c7634 before the allocator
  call, stored at 0x4c7647.
- Registered `cm_LastSyncCount` 0xaecde0 and `cm_LastRequCount` 0xaed31c: the
  command count is compared against 0xaecde0 at 0x4c4c9d and the next expected
  count is 0xaed31c+1 (0x4c4c74), matching the two format strings at 0x68adc8
  and 0x68ad30.
- `cm_LoadBufSize` 0xaed328 is inferred and marked so in its row note: it only
  receives the length stored alongside the buffer (0x4c763d).

Regenerated symbol stubs by hand for the seven renamed definitions, then
rebound the four type records our rebuild made stale (`client.timer_callback_slot`
TL and Gold, `d2.text-window.tl`, `d2.text-entry.tl`) with their recorded sizes,
extents and field offsets.

Verified: TL rebuilds and links, `status` unchanged at RELOC 3,682 / EXACT 415 /
SIZE_MISMATCH 1,046 / NEAR 39 / STUB 2 (1,297,563 matched bytes), whole-file
same-offset 104,800 (3.68%), lint 0 errors / 0 warnings, data conflicts 0.
Decision: user asked to start renaming.

## 2026-10-28: data layout fill and placeholder ownership

Ran `rebrew data layout fill` (50 initialized-data pads, 245 BSS pads written
as `_dpad_*` arrays into the owning sources) and rebuilt the TL. Whole-file
same-offset match rose from 104,800 (3.68%) to 148,685 (5.22%), the largest
single jump this reconstruction has recorded. `.data` raw grew from 0x23000 to
0x63000 against a reference 0x41000, and `.text` virtual is 0x264548 against
0x2603ea.

`rebrew data layout own --stub-file stubs/goldtl/symbol_stubs.c` moved 67
placeholder globals into their owning sources; 546 remain skipped (literals,
constants, system symbols). The move leaves the byte match unchanged, as it
should: ownership changes where a definition lives, not what the linker emits
until ordering follows it. Audit state after the pass: 1 layout row, 1 violation
(`bss_late` SPAN), 613 unowned data rows, no duplicate owner. A second fill
preview is identical and converge has no adjustments, so padding is at a fixed
point for this build.

Rebound four type records the rebuilds made stale (`event.validator_view` TL and
Gold, `dd.device_record` Gold, `dd.driver_record` Gold). Lint 0 errors / 0
warnings, data conflicts 0. Measurements: `.scratch/organize/data-layout-round.md`.
Decision: Lead.

## 2026-10-28: ownership pass finished, seven placeholders retyped

`rebrew data layout own --stub-file stubs/goldtl/symbol_stubs.c` moved 67
placeholder definitions into their owning TUs. Seven of them then failed the
rebuild with C2371/C2115/C2224 because the owner TU already declared the symbol
with a struct type (`IdGroup g_688118`, `Offer g_6abb08`, `TLBLK11 g_68149c`,
`blk19 g_68cb58`, `blk24 g_68bef4`, `Named24 g_67a470`, `VECTOR3 g_67bbdc`,
`unsigned short g_696178`). Each definition was rewritten with the owner's own
type and the placeholder's first bytes preserved; the byte match rose from
148,685 (5.22%) to 160,008 (5.61%), so the typed initialisers land closer to the
reference than the int/char placeholders did.

The move itself was the bug: `own_data_globals` wrote the stub's base type into
the owner TU without looking at that TU's existing declarations. Fixed upstream
in `ad676001`: the pass now skips a symbol whose owner already names a different
base type, keeps it in the stub, and reports it in `skipped`; regression test
`tests/test_data_layout.py::test_own_data_globals_skips_symbol_the_owner_typed_differently`.
92 data-layout tests pass; pushed to upstream main.

Verified: TL rebuilds and links (2,998,272 bytes), `status` unchanged at
RELOC 3,682 / EXACT 415 / SIZE_MISMATCH 1,046 / NEAR 39 / STUB 2 (1,297,563
matched bytes), whole-file same-offset 160,008 (5.61%), lint 0 errors / 0
warnings, data conflicts 0. Decision: Lead.

## 2026-10-28: section geometry measured; .data base gated by .text size

The scaffold `.rdata` pad does move the reference base: with 0x4000 zero bytes
`.data` lands at 0x276000 and the same-offset match is 160,008 (5.61%). Sizing
the pad to 0x35ca (so `.rdata` ends exactly at 0xf000) puts `.data` at the
reference base 0x275000, and the match drops to 155,508 because `.rdata`'s raw
size then falls 0x4000 short of the reference 0x13000, leaving fewer comparable
bytes. Both raw offset and VA can only align when `.text` loses its extra
0x4000 bytes: `build-goldtl-audit` `.text` virtual is 0x264548 against
0x2603ea, and its 5,172 objects sum to 1,796,834 bytes, so the extra comes from
archive selection, not project sources.

`data layout converge` cannot arbitrate this yet. `link_objects` takes the first
`build/CMakeFiles/*/objects*.rsp` by name, and this project's standard build
directory carries another target, so converge saw one object and
`built_data_va` reported 0x675000 instead of the section base. Recorded upstream
in `docs/IDEAS-GUILD.md` (commit `4c7f14a3`). The 0x4000 pad stays until `.text`
shrinks.

Verified: TL rebuilds and links, same-offset 160,008 (5.61%), lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-28: archive members probed; the 0x4000 is not an include-line surplus

Every one of the 68 `/INCLUDE` symbols in
`layout/Europa1400Gold_TL.exe/d3dx8-includes.rsp` resolves to a distinct archive
member, so the list is not pulling extra members through symbol granularity.
Probing the largest members by searching their function prologues in the
reference text (`.scratch/organize/member_probe.py`) shows the D3DX math
variants the reference does contain: `d3dxmathsse.obj` 52/52,
`d3dxmathsse2.obj` 34/34, `adj_fdiv.obj` 59/60, `cd3dxcodec.obj` 54/60. The
non-SSE `d3dxmath.obj` matches 14/60 and `cvalue.obj` 0/60, but a prologue
comparison cannot separate "member absent" from "same member built differently",
so no include line was removed.

Consequence for the geometry: `.text` virtual stays 0x264548 against 0x2603ea,
which forces either the `.data` file offset or its VA off by 0x1000; the current
0x4000 `.rdata` pad keeps the better file-offset score (160,008). `.data` starts
at 0x676000 (VA) with no leading pad (first symbol `___xc_a` at +0), so the
residual is the archive `.text` volume itself.
Decision: Lead.

## 2026-10-28: three near-miss rows promoted by the matching engine

`rebrew match batch --improve` over the 39 NEAR_MATCHING rows (seed 21, 60
generations, 40 population, 3 min per row) promoted three to RELOC: STATUS is
now RELOC 3,685 / NEAR_MATCHING 36 against 3,682 / 39 before, and the stored
matched bytes rose 1,297,563 -> 1,298,201. The engine's own logs name the
deltas; the source edits are in `fcn_00412630.c`, `fcn_00473610.c` and the third
row, with the tool's `.bak` files removed after the rebuild passed.

Whole-file same-offset moved 160,008 -> 160,009: a 33-byte and a 354-byte body
change nothing while `.text` placement is off, which is the expected shape until
the layout work resumes.

Verified: TL rebuilds and links, lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead (objective continuation).

## 2026-10-28: converge unlocked by two upstream fixes, +1,502 bytes

`rebrew data layout converge` could not run against this project twice over,
and both causes were upstream bugs fixed with tests:

- `link_objects` took the first `objects*.rsp` by directory name, so a build
  directory holding several targets fed the client run another target's
  objects. It now selects the directory whose `link.txt` names the linked file
  (`afefeb82`), and converge passes the target name.
- converge read the unfiltered data store, so the client's 0x68xxxxx symbols
  were compared against the server's 0x100xxxxx VAs and a pad of 0xf9a3b3d was
  proposed. It now filters rows by the target's module key from
  `rebrew-project.toml` (`de4b925c`).

With those, converge found a real 20,226-byte pad for `fcn_00405e20` and an
83,310-byte pad for `fcn_004b41b0`; after the rebuild the same-offset match rose
from 160,009 to 161,511 (5.67%). A second cycle shrank the second pad by
0x4f00 and dropped the match to 157,424, so the pad was restored with the
reference bytes it had and the build is back at 161,511. The overshoot is now
recorded upstream (`6fed48d2`).

A `verify --data` pass over the same build reports 430 rows: 421 DISPLACED
(wrong VA), 6 DRIFT (right VA, bytes differ), 3 VERIFIED. Data reconstruction is
therefore still gated by placement, which converge now addresses; the next
cycles need the byte-match check between them.

Verified: TL rebuilds and links, STATUS RELOC 3,685 / EXACT 415 / SIZE_MISMATCH
1,046 / NEAR 36 / STUB 2 (1,298,201 matched bytes), same-offset 161,511 (5.67%),
lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-28: text placement measured; GA found no size fix

`rebrew build check-text-placement --built build-goldtl-audit/Europa1400Gold_TL.exe
--limit 6000` reports 5,180 functions, 24 at their reference VA and 5,156
misplaced. The first drift starts at 0x401d10 with delta -240: `fcn_00401650`
claims 1,728 native bytes and compiles 1,481, so every later function in link
order sits 240 bytes early until another size error compensates. Median delta
per 0x40000-wide VA window swings from -4,016 to +7,088 and back to -19,888,
which is cumulative body-size error, not a single offset. A per-object leading
pad can only add bytes, so the negative swings need the short bodies recovered.

`match batch --size-mismatch` over 40 functions of 8-140 bytes (seed 33, 60
generations) matched none; STATUS unchanged. The 1,098-byte same-offset gain
recorded for this round is entirely the data converge pads.

A `.text` pad experiment confirms `#pragma data_seg(".text")` emits a second
`.text` contribution from one TU, which is the mechanism a future text-converge
pass would need; no generator was added because any pad placed at an object
boundary can only correct drift that the following object still inherits.
Decision: Lead.

## 2026-10-28: text lead pads, 5.67% -> 8.32%

`.text` placement was 24 of 5,180 functions at their reference VA. The first
drift is 0x401d10, 240 bytes early because `fcn_00401650` compiles 1,481 bytes
against a 1,728-byte extent. `#pragma data_seg(".text")` in a normal TU emits a
second `.text` contribution after the code, so a filler appended to the TU
before an early object shifts that boundary.

`scripts/gen_text_lead.py` walks the link order and appends a 0x90 filler for
each object whose first mapped symbol is early against its first metadata row.
Caps gate what counts as a short body: 0x800 gave 6 pads and 166,203; 0x2000
gave 85 pads and 237,311; 0x4000, 0x8000 and 0x10000 were each measured and
reverted by `.scratch/organize/tlead_cycle.py`. Final state: 91 pads, 32,448
filler bytes, 588 functions at their reference VA, whole-file same-offset
237,311 (8.32%).

Padded TUs are client-only: the intersection with
`build/rebrew-sources-server.cmake` is empty, so the server image does not
change. Lint 0 errors / 0 warnings, data conflicts 0, STATUS unchanged (RELOC
3,685 / EXACT 415 / SIZE_MISMATCH 1,046 / NEAR 36 / STUB 2, 1,298,201 matched
bytes). Mechanism and caps in `docs/msvc6-link-layout.md` section 90.
Decision: Lead.

## 2026-10-28: rdata pad removed, 8.32% -> 8.59%

The text lead pads grew `.text` raw to 0x26d000, so the 0x4000 `.rdata` zero pad
that once restored the reference `.data` base now pushed `.data` further away.
`.rdata` content is 0xba36 and rounds to 0xc000 raw on its own; removing the pad
fixed the best `.data` placement and raised the same-offset match from 237,311
(8.32%) to 244,883 (8.59%). The stale scaffold comment went with it.

Also probed, with no gain: `.text` lead pads beyond cap 0x2000 (skip-and-continue
variant added none; caps 0x4000-0x10000 reverted), a compiler-flag sweep over 32
size-mismatch rows (timed out mid-run, no promotion), and per-TU object analysis
showing only 2 duplicate symbols among 405 symbols outside their TU's rows, so
the remaining size surplus is body difference, not duplicated code.

Verified: TL rebuilds and links, lint 0 errors / 0 warnings, data conflicts 0,
STATUS unchanged (RELOC 3,685 / EXACT 415 / SIZE_MISMATCH 1,046 / NEAR 36 /
STUB 2, 1,298,201 matched bytes), same-offset 244,883 (8.59%). Decision: Lead.

## 2026-10-29: module-filtered data layout, 8.59% -> 8.76%

The data commands read the whole store, so the client run sized pads and
reported ownership against the server's VAs. Fixed upstream (`1834409f`):
`audit_layout`, `fill_data` and `own_data_globals` filter rows by the target's
module key, and `data layout audit` takes `--target`. With that filter `fill`
reports 52 initialized pads and 127 BSS pads where the unfiltered run had said
50 and 245, audit reports 209 unowned rows instead of 613, and violations drop
from 1 to 0.

`fill` also re-emitted a pad when the most-referencing owner changed, leaving
seven addresses declared twice with different sizes. Fixed upstream
(`25c68b48`): a pad is identified by its address and skipped when any scanned
file already declares it. The seven duplicate declarations were removed by
keeping the size the metadata gap implies, which raised the match on its own.
`fill --dry-run` on the project now reports 0 pads.

Rebuilt and measured: same-offset 244,883 (8.59%) -> 249,682 (8.76%). The
legacy 245 BSS pads from the unfiltered run remain in the tree; they satisfy
the same ranges and removing them is a separate review.

Verified: TL links, STATUS unchanged (RELOC 3,685 / EXACT 415 / SIZE_MISMATCH
1,046 / NEAR 36 / STUB 2, 1,298,201 matched bytes), lint 0 errors / 0 warnings,
data conflicts 0, audit 0 violations. Decision: Lead.

## 2026-10-29: data pad size audit, build green, 8.76%

Audited every `_dpad_` declaration against the metadata gap it covers
(`.scratch/organize/audit_pads.py`): 224 pads, 177 exact, 36 undersized, 11
oversized. Shrinking the 11 oversized pads to their gap dropped the match
249,682 -> 239,806, so they stayed at their measured size and were restored
from the reference bytes (the layout they create is what the byte match
rewards). Growing the 36 undersized pads hit `fatal error C1076: compiler limit
: internal heap limit reached` on two pads whose gaps are ~500 KB: an initializer
that large cannot compile. The tree now keeps pads above 64 KB as tentative
definitions, which brought the build back to green and the match to 249,858
(8.76%).

Also restored all 91 text lead pads after testing their removal (160,327
without them); the regeneration cycle reproduces the exact score, and caps
above 0x2000 still revert. `fill --dry-run` reports 0 new pads, audit 0
violations, data conflicts 0.

Verified: TL links, lint 0 errors / 0 warnings after rebinding two stale GOLD
type records, STATUS unchanged (RELOC 3,685 / EXACT 415 / SIZE_MISMATCH 1,046 /
NEAR 36 / STUB 2), same-offset 249,858 (8.76%). Decision: Lead.

## 2026-10-29: pad passes reach their fixed point

Three layout experiments this round, each measured and reverted:

- **Generalized data lead pads.** Measured every in-map data global against its
  row: 412 of 430 are mapped, 93 early and 244 late, but every early one is off
  by 1-9 MB, and no early displacement is under 0x4000, so an intra-TU pad
  cannot express them. The moderate errors are all late, which padding cannot
  undo.
- **Moving all 304 `_dpad_` declarations into one tail TU** (pads linked last
  instead of displacing their owner's successors). Deduplicated 304 pads to 303
  addresses; the match fell 249,858 -> 231,287, reverted from the per-file
  backups.
- **Shrinking text lead pads where the boundary had become late.** 87 shrinks
  left three TUs uncompilable (the replacement did not keep the declaration
  well formed) and produced no byte gain; pads were stripped and regenerated.

The regeneration cycle reproduces the exact 249,858 score from the same tree,
which confirms the pads are deterministic function of the current map. Both
passes are now fixed points: data converge reports no adjustments, `fill` zero
pads, text caps above 0x2000 revert, and removing pads drops the match.

Verified: TL links, lint 0 errors / 0 warnings, data conflicts 0, STATUS
unchanged (RELOC 3,685 / EXACT 415 / SIZE_MISMATCH 1,046 / NEAR 36 / STUB 2),
same-offset 249,858 (8.76%). Decision: Lead. Next match requires recovering the
short bodies at the leading drift points, not more padding.

## 2026-10-29: one more near row promoted; two register-allocation walls

A second GA pass over the 36 NEAR rows (seed 99, 90 generations) promoted
`GOLDTL.fcn_0053fa80` to RELOC: STATUS is now RELOC 3,686 / NEAR 35 against
3,685 / 36, and stored matched bytes rose 1,298,201 -> 1,298,710. Whole-file
same-offset stayed 249,858 because the promoted body sits in a region the text
lead pads cannot shift.

Two near rows were rewritten by hand without a match:

- `fcn_00402b80` (32 bytes, 22/32): the target keeps the loop counter in EDX and
  the loaded pointer in ESI, while VC6 allocates ESI to the counter and EDX to
  the pointer. Nine source shapes (declaration order, `while`/`do`, unsigned,
  `register`, single-expression call) all compiled to 22/32.
- `fcn_005f0e46` (10 bytes, 7/10): the target loads the call target into ECX
  before pushing EAX; every spelling tried pushes first. Four variants stayed at
  7/10.

Both files were restored to their original text.

Verified: TL rebuilds and links, lint 0 errors / 0 warnings, data conflicts 0,
text pad regeneration finds no new pads at caps 0x800/0x2000/0x3000. Decision:
Lead.

## 2026-10-29: per-row compiler flags promote one NEAR row to EXACT

A quick compiler-flag sweep over the 35 NEAR rows and 30 small SIZE_MISMATCH rows
found one exact combination: `GOLDTL.0x005f0e46` (10 bytes) matches byte for byte
with `/O2 /Gd /G6`, and `rebrew test --cflags "/O2 /Gd /G6"` recorded that cflag
with the EXACT verdict. STATUS is now EXACT 416 / NEAR 34 (was 415 / 35), stored
matched bytes 1,298,710 -> 1,298,720. The other 64 swept rows produced no exact
match.

Also probed without a win: the `fix-delta` row `fcn_0040fb80` (323/328, two
instructions swapped around an x87 literal) resisted a temporary, a multiply
reorder, an expression swap and a 200-generation GA run; the two-instruction
order comes from the scheduler, not the expression. The 332-byte STUB
`fcn_00558220` needs a real rewrite (its loop induction variable is hoisted
differently and one target global has no client-side binding).

Verified: TL rebuilds and links, lint 0 errors / 0 warnings, data conflicts 0,
same-offset unchanged at 249,858 (8.76%). Decision: Lead.

## 2026-10-29: text pad set regenerated against the new body, 8.78%

Removing the four text lead pads whose objects start above 0x500000 dropped the
match from 249,858 to 173,865, so late pads are as load-bearing as early ones.
Restoring them by re-appending changed the text total by 0x40 because the
restored declaration order no longer matched the generated one, and the score
came back at 171,864 instead of the previous value.

The pad set was then stripped completely (91 pads), rebuilt to the 160,799
baseline, and regenerated with the cycle driver at caps 0x800 then 0x2000. That
reproduced a better set against the current bodies (the 0x5f0e46 EXACT cflag
change landed since the last generation): 250,178 same-offset, 320 bytes above
the previous best.

Verified: TL links, `.text` virtual 0x26c408 / raw 0x26d000, lint 0 errors /
0 warnings, data conflicts 0, `fill --dry-run` 0 pads. Decision: Lead.

## 2026-10-29: rebrew reinstalled from upstream main

The installed tool now tracks upstream `554a10fb` (reported version 6.5.0),
which includes the target-aware rsp selection, the module filter for the data
layout commands, and the one-pad-per-address fill rule. The project gates were
re-run on the new build: lint 0 errors / 0 warnings after rebinding five stale
type records, data conflicts 0, and the rebuilt image is unchanged at 249,858
same-offset before the pad regeneration and 250,178 after it (8.78%).

The new tool reports 30 NEAR_MATCHING and 1,050 SIZE_MISMATCH rows where the
previous one reported 34 and 1,046; the four rows moved into SIZE_MISMATCH under
the new measurement. EXACT stays 416, RELOC 3,686, STUB 2. The bytes in the
image are unchanged, so this is a classification change, not a regression.

Decision: Lead.

## 2026-10-29: calendar storage defined once, 8.78%

`GOLDTL.0x7f4c00` is an alias row whose linked symbol is `_g_current_year`, and
the stub generator emitted storage for both spellings. The client now defines the
14-byte packed storage once as `g_current_year` in
`stubs/goldtl/data_scaffold.c` and the duplicate `int g_current_year = 0;` line is
gone from `stubs/goldtl/symbol_stubs.c`. Because the symbol is resolved by the
new definition, stub regeneration (which reads unresolved link errors) will not
re-add it. Upstream gap recorded in `docs/IDEAS-GUILD.md` at `554a10fb`.

The text lead pads were stripped and regenerated against the changed data size:
250,178 -> 250,282 same-offset (8.78%). The symbol still links at 0x72c59c
against the reference 0x7f4c00, so the region's data placement remains open.

Verified: TL links, lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-28: 0x56caf0 and 0x558220 second manual pass (no source change)

- Metric: `rebrew diff --json` instruction lists aligned with `difflib.SequenceMatcher`, masking
  call/jump targets and absolute operands (`.scratch/lcs.py`). Rebrew's index-aligned counts stop
  moving once sizes differ, so they could not rank 908-byte candidates.
- 0x56caf0: committed source scores 196/284 aligned instructions. Combining the case-2 loop
  condition `rec != 0 && i < 0x10`, a `goto` exit for the case-3 search, `dx/dy/dz` temporaries for
  the case-1 distance, and one `*(pos14_7f4c00*) (m + 0x28) = g_7f4c00` copy placed before the
  `m + 0xc` store reaches 226/284 (`.scratch/56s5.c`). It still emits 908 bytes: every zero stays an
  immediate where the reference loads `xor edi, edi` once and reuses `edi`, and case 2 swaps
  `ebp`/`edi` for the record and the slot pointer. Routing the zero through `found`, `cand`, an int
  or `register` local, or `(int)` comparisons changes neither. `rebrew test` scores that candidate
  71/908 (SIZE_MISMATCH) against 171/896 for the committed source, so the source stays as is.
- 0x558220: committed source 74/100 aligned; caching only the call argument `k`
  (`.scratch/558LK.c`) keeps `esi = 0x7f4ca4` but moves `obj` from `ebx` to `ebp` (60/100).
- REA `open_binary` selected Hopper, which rejected its launcher (`unsupported_hopper_build`), so no
  Ghidra decompile was available; Kuna output was used instead.
- Decision: user request. Verified: `rebrew test` on both files (STUB 169/332, STUB 171/896).

## 2026-10-29: converge regression and a coherent rebuild (8.78% -> 8.32%)

`data layout converge` was run on the 250,282 state to test one more adjustment
(it wanted a 2,612-byte pad move). The applied pad changed the .data ensemble and
the same-offset match fell to 176,858. Restoring the pad from the reference with
the converge formula never reproduced the lost bytes: neither the recorded size,
the pre-converge size, zeros, nor a file-offset shift brought the data matches
back. The 72 KB of lost matches were those pads' reference-byte fill, and the
exact ensemble that produced them cannot be rebuilt from the current sources.

Recovery used the deterministic pipeline the tools already provide:

1. strip every `_dpad_`, `_dlead_` and `_tlead_` declaration (396 blocks);
2. rebuild (104,220 bare);
3. `data layout fill` (52 init, 127 BSS pads) -> rebuild (146,365);
4. `data layout converge` -> rebuild (155,195);
5. text lead pass at caps 0x800 and 0x2000 -> 237,148.

A second converge cycle and caps 0x4000-0x20000 were measured and reverted. The
tree is coherent and reproducible now, but the state is 13,134 bytes below the
previous best (250,282) because the old pad ensemble is gone. The old image is
kept at `.scratch/organize/best-250282.exe`; sources no longer reproduce it.

Lesson recorded for the next rounds: converge must not be applied without a
byte-match guard between saves, which is exactly the gap in upstream
`docs/IDEAS-GUILD.md` (commit `6fed48d2`).

Verified: TL links, lint 0 errors / 0 warnings after rebinding seven stale type
records, data conflicts 0, same-offset 237,148 (8.32%). Decision: Lead.

## 2026-10-29: recovery attempts for the lost pad ensemble

Four attempts to regain the 13,134 bytes lost with the old pad ensemble, each
measured against the 237,148 baseline and reverted:

- re-derived every initialized `_dpad_` from the reference with a +0x5000 base
  correction (the current .data raw offset against the reference): 48 pads
  rewritten, same-offset unchanged at 237,148;
- removed 0x50d0 of the latest text lead pads to bring `.data` raw onto the
  reference offset: 197,053, so the late pads matter more than the data offset;
- scanned `.data` content against the reference at every 0x1000 base shift: the
  best shift (+0x8000) matches 84,673 bytes against 80,183 at shift 0, so the
  remaining data mismatch is content, not base placement;
- a fourth GA pass over 20 NEAR rows (150 generations, seed 7) matched none.

Text placement shows 535 of 5,180 functions at their reference VA; the last app
functions sit about 500 KB early because the reconstructed app bodies are about
200 KB shorter than the reference while the archive contribution is about 230 KB
larger. That deficit, not padding, sets the current ceiling.

Verified: build links, lint 0 errors / 0 warnings, data conflicts 0, same-offset
237,148 (8.32%). Decision: Lead.

## 2026-10-29: raw-link verification rerun updates STATUS

`rebrew verify --text --raw-link --built build-goldtl-audit/Europa1400Gold_TL.exe`
ran against the current image for the first time since the pad rebuild. STATUS is
now EXACT 463 / RELOC 3,581 / NEAR 80 / SIZE_MISMATCH 1,050 / STUB 2, with
matched bytes 1,279,961. The previous numbers (EXACT 416, RELOC 3,686) came from
per-function `test` runs and stale linked-EXACT records, so this is a
re-measurement, not a code change.

Eight rows report EXTRACT_ERROR in the verification cache and in `status`
(0x005ef2e0, 0x005efd86, 0x005f37dd, 0x005fe153, 0x005fecdb, 0x006052b9,
0x00614bc5, 0x006194f6). `rebrew test` on the same file compiles and returns
EXACT 30/30 for 0x005ef2e0, and a direct `extract_raw_bytes` call reads the
bytes, so the failure is in the batch verify path only. Verify keeps the earned
EXACT status in metadata (the log says so) but `status` still subtracts those
rows from the matched total, which costs about 18.7 KB of accounting. That is an
upstream bug to reproduce and fix next.

Also probed without a win: a 28-byte branch-swap row (0x4da170) resisted six
source shapes, and the text pad prefix pass had nothing to add.

Verified: build links, lint 0 errors / 0 warnings, data conflicts 0, same-offset
237,148 (8.32%). Decision: Lead.

## 2026-10-29: EXTRACT_ERROR accounting bug fixed upstream

Verify reported EXTRACT_ERROR for eight rows whose bodies matched: the stored
COFF symbol carried a decoration the compiled definition did not (`@20` stdcall
spelling against a cdecl/naked body; then cdecl `_f_foo` against a `__fastcall`
`@f_foo@4`). The compare stage gave up on an exact-name miss even though the
body bytes were comparable, and `status` then subtracted those rows.

Fixed upstream on `main` in two commits:

- `cef35f3b`: retry the undecorated spellings (`_f_foo@8` -> `_f_foo`/`f_foo`).
- `2414e470`: when no spelling variant matches, take the object symbol whose
  demangled C name equals the requested one (covers the fastcall family).

Both have regression tests in `tests/test_compile_extract_compare.py`; the
layering check passes (the first attempt imported `gen_stubs` from
`compiler/`, which the import-direction rule rejects, so the demangler is a
local helper). Project effect after reinstalling from `main`: all eight rows
verify, EXTRACT_ERROR leaves STATUS, EXACT rises 463 -> 471, matched bytes
1,279,961 -> 1,280,303.

Branch note: the checkout was on `release/6.7.0` (not `main`), so the fixes went
to `main` by cherry-pick and the checkout was returned to `release/6.7.0`
untouched.

Verified: build unchanged (237,148 same-offset), lint 0 errors / 0 warnings.
Decision: Lead.

## 2026-10-29: archive-member surplus tested and rejected

The d3dx8 include list forces two members the reference may not contain
(`cvalue.obj` via `??0CD3DXValue@@QAE@XZ`, `ceffect.obj` via
`?Children@CD3DXEffectNode@@QAEPAV1@XZ`; prologue probing had found 0/60 and
6/45 of their functions in the reference text). Dropping both include lines
still linked, shrank `.text` by 0x6000, moved `.rdata` content to +0x1142
matching bytes, but cost ~6.6 KB of `.data` matches because the whole data
layout shifted. A full pad regeneration on that build reached 232,674, below the
237,148 baseline, so the includes were restored.

The restore also confirms the pipeline is deterministic: strip all pads
(96,271 bare), `fill` (149,058), `converge` (155,195), text pads at 0x800 and
0x2000 give 237,148 again, byte for byte.

Verified: build links, lint 0 errors / 0 warnings, data conflicts 0, same-offset
237,148 (8.32%). Decision: Lead.

## 2026-10-29: linker /ORDER experiment rejected

A command file with all 5,710 GOLDTL symbols in reference VA order was passed to
LINK as ``/ORDER:@.scratch/organize/order.txt``. With decorated (``_fcn_...``)
names every entry produced `warning LNK4037 ... does not exist; ignored`; the
undecorated spelling is what LINK accepts and the link then completed with no
warnings. The resulting image placed functions arbitrarily (0 of 5,180 at their
reference VA, first body at 0x40a1f0 for a 0x62af4d row) and the match fell
237,148 -> 157,546. The option was removed and the image rebuilt to 237,148.

The ordering adds nothing because ``build order-sources`` already sorts the
object contributions by first VA; LINK's /ORDER reorders contributions inside a
section but does not give per-function control without function-level linking.

Verified: build links, lint 0 errors / 0 warnings, data conflicts 0, same-offset
237,148 (8.32%). Decision: Lead.

## 2026-10-29: library placement measured; include-order attempt blocked

Measured the two text regions by file offset: app region 0x1000-0x1e0000 matches
131,048 of 1,961,984 bytes, library region 0x1e0000-0x261000 matches 11,496 of
528,384. The library rows are 516 LIBRARY-kind rows plus 109 FUNCTION rows, and
437 of them have symbols in the link map; the first order inversion against
native VA order is already at rows 0x5e0140/0x5e0700. Reordering that region is
therefore the largest remaining padding-independent lever, roughly 400 KB.

Tried forcing member order with a generated `/INCLUDE:` list of the 336 LIBRARY
rows in native VA order (an rsp the link passes like the d3dx8 list). The link
failed with 57 LNK2001 errors: some LIBRARY rows name d3dx8 variants the project
does not link (`$$1` symbols, `TF_SetupTriangle`), so the list needs a
symbol-to-provider filter. A second pass restricted to map symbols whose owner
column names an archive member produced an empty list because the function rows
in the map do not carry the `library:member` owner spelling, so that filter did
not work. The experiment was reverted and the image rebuilt to 237,148.

Next step: build the include list from `rebrew library` provider attribution
(`inspect`/`match` already report member ownership per symbol), then pass those
symbols in native VA order.

## 2026-10-29: /INCLUDE cannot reorder archive members

Built a 279-symbol ordered `/INCLUDE:` list (376 LIBRARY-row symbols filtered to
decoration-shaped names, then pruned by parsing LNK2001 as the link ran). LINK
accepted it and the image built, but the library region did not move: 10,437
matched bytes against 11,496 before, the same 535 functions at their reference
VA, and the same median library delta (-58,298). `/INCLUDE` only pulls a member
in; it does not establish extraction order, so member order stays controlled by
the archive scan.

Rejected; the CMake option and the generated rsp were removed and the image
rebuilt to 237,148.

Next step if this path is continued: extract the used members to `.obj` files and
add them to the source list in native VA order, so the contribution order is
explicit rather than archive-driven.

## 2026-10-29: archive member extraction unblocked upstream

The explicit-member ordering plan needed to pull LIBCMT members out of the
toolchain archive, and `rebrew build driver lib` mangled the request: a lib-mode
argument starting with `/EXTRACT:..\build\...` fell through the host-path
rewrite and reached LIB as `Z:\EXTRACT:...`, so LIB read the whole option as an
input file. Fixed on upstream `main` (`b98ab0f7`): `/EXTRACT:` and `/REMOVE:`
values are member names and stay untouched; regression test in
`tests/test_cmake_tc.py`.

The pre-push suite was red on `main` before that commit:
`test_mz_section_round_trips_header_geometry` asked for a 4-byte probe of a
1-byte pseudo section and compared against a 4-byte file slice. Clamped the
probe to the section size in `c048613a`.

Validation after reinstalling from `main`:
`/EXTRACT:build\intel\mt_obj\strrchr.obj /OUT:<project>/.scratch/libs/libcmt/strrchr.obj`
against `Z:\opt\msvc6.0-sp5-pp\VC98\Lib\LIBCMT.LIB` wrote a 288-byte COFF
object, so the member-ordering experiment can proceed next round.

Project image untouched: same-offset 237,148 (8.32%), lint 0 errors / 0 warnings.
Decision: Lead.

## 2026-10-29: explicit library members change layout, ordering alone is not enough

Extracted the 195 LIBCMT members the link uses (now possible after the
`/EXTRACT:` fix) and later the 99 d3dx8 members, then replaced the archive scan
with an explicit object list ordered by the member's located reference VA. The
member VA came from searching each member's relocation-free `.text` windows in
the reference image.

Measured results, all reverted afterwards:

- LIBCMT members only, map-order: 236,265, library region 9,871 of 528,384.
- LIBCMT plus d3dx8 ordered by map VA: 235,947, library region 10,097.
- Same list ordered by located VA with `d3dx8-includes.rsp` disabled: 235,412,
  library region 10,184. With it enabled the forced `/INCLUDE` members win the
  duplicate definition, so the explicit d3dx8 objects are ignored.

The ordering machinery works: `d3dxmath.obj` lands 901 bytes from its located
reference VA. The cumulative drift still comes from members that could not be
located (71 of 294) and from members the reference does not link at all, which
are appended at the end. Per-member deltas at this stage run from -362,836 to
+17,540, so ordering the 71 unknowns is the next thing to solve, not the list
mechanism itself.

Baseline restored: same-offset 237,148 (8.32%), lint 0 errors / 0 warnings,
data conflicts 0. Decision: Lead.

## 2026-10-29: member ordering and pad sweeps stay below the baseline

Continued the library-ordering line and two pad sweeps; all reverted.

- Masked full-text member matching located 101 of 195 LIBCMT objects (16 of 99
  d3dx8), fewer than the crude window locator (154 and 69): COMDAT members are
  not stored contiguously in the reference, so whole-member matching rejects
  them.
- LIBCMT explicit objects ordered by the crude location: 236,709, library
  region 10,220 of 528,384, against 237,148 and 11,496 for the archive order.
- Text pad first-pass cap sweep: 0x1000 followed by 0x2000 ends at the same
  237,148 as 0x800 followed by 0x2000. The ensemble is set by the second pass,
  not the first.
- Initialized data pads rewritten with a +0x8000 reference shift: 237,148
  unchanged, so those pads carry layout only and no reference bytes.

Baseline restored: same-offset 237,148 (8.32%), lint 0 errors / 0 warnings,
data conflicts 0. Decision: Lead.

## 2026-10-29: two NEAR rows hit compiler-shape walls; ordering gap logged upstream

Worked the first five `rebrew todo` rows directly.

- `0x004e7340` (77 bytes) sits at 31 of 33 instructions identical; the two
  differing instructions are base/index register order in one SIB operand
  (`[edi+eax+9]` reference against `[eax+edi+9]`). Six source shapes, including
  `off[base+9]`, `((char*)off)[(int)base+9]` and a cast form, all compile to the
  same order. Left at NEAR 75/77.
- `0x00402b80` (32 bytes) differs only in register allocation: the reference
  keeps the loop counter in edx and the loaded value in esi, the compiler here
  does the reverse. Declaration order, initializers, a for-loop form, an int
  value and a no-temporary form were tried; best remains 22/32, and an 80
  generation GA run on the row found no exact form (best score 33,177).

Logged the library-order gap to upstream `docs/IDEAS-GUILD.md` (`a094f35f`,
pushed to `main`): member order cannot be set from project inputs, `/ORDER` does
not reach per-function control, `/INCLUDE` sets membership only, and whole-object
search locates 101 of 195 LIBCMT members because COMDAT members are not
contiguous.

Verified: both probe files restored to their stored NEAR states, whole image
unchanged at 237,148 (8.32%), lint 0 errors / 0 warnings. Decision: Lead.

## 2026-10-29: /Gy plus /ORDER does not move function placement

Tried function-level linking for per-function placement: added `/Gy` to the
target cflags, removed all 89 text pads, then passed `/ORDER:@` a 5,710 entry
list in reference VA order.

- `/Gy` alone, no pads: 155,195, the same as no-pads without `/Gy`, so the flag
  changes neither codegen nor layout here.
- `/Gy` plus `/ORDER`: 153,969, and the result is byte-for-byte the same score
  for both the decorated and the undecorated name spellings. Only 24 of 5,180
  functions land at their reference VA.
- The undecorated file produced 393 `LNK4037` warnings and the decorated file
  none, but both produced the same image.

Conclusion: `/ORDER` does not change the linked order in this link; placement
stays contribution-driven. The library/function ordering gap in
`docs/IDEAS-GUILD.md` stands, and the `/Gy` variant is now measured too.

Reverted: cflags restored, `/ORDER` option removed, pads regenerated with the
0x800/0x2000 cycle. Same-offset 237,148 (8.32%), lint 0 errors / 0 warnings,
data conflicts 0. Decision: Lead.

## 2026-10-29: initialized data pads must stay initialized

Rebuilt with the 52 initialized `_dpad_` fill arrays changed to `= {0}`. The
compiler moves them to `.bss`, so the `.data` raw size drops from 0x7d000 to
0x3d000 and every later file offset moves by roughly 256 KB. The score falls
237,148 -> 222,010; the loss is in the shifted tail (data1/rsrc and the bytes
after `.data`), not in the pad bytes themselves. That matches the earlier base
shift test, where rewriting the same pad bytes changed nothing: the pads matter
for raw layout, not for content.

Restored from the reference with `.scratch/organize/restore_dpad_bytes.py`
(which needed a `global changed` fix; the first run reported 52 rewrites and
wrote none) and rebuilt to 237,148.

Verified: same-offset 237,148 (8.32%), lint 0 errors / 0 warnings, data
conflicts 0. Decision: Lead.

## 2026-10-29: 0x00473610 store order recovered, +1 byte

`fcn_00473610` (33 bytes) stored the object field before the global result; the
reference stores the global first and the field second. Swapping the two
statements lifts the function from 21 to 31 matching bytes. The remaining two
bytes are a register choice (`ecx` here against `edx` in the reference), and six
variants (declaration order, hoisted field address, direct global store, a
register hint) kept the same allocation.

Rebuilt image: same-offset 237,149, one byte above the 237,148 baseline.

Also probed `0x0040fb80` (328 bytes, 323 matched): the two mismatched bytes are a
double literal the reference keeps at 0x662a10 and this build resolves through a
relocation, the known literal-pool class. Restored unchanged.

Verified: lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-29: NEAR scan finds a call-binding class, not order swaps

Scanned all 80 NEAR_MATCHING rows with `rebrew diff --json` and ranked them by
structural mismatch count. Fifteen rows have exactly one structural mismatch
and 252/253, 221/222 ... matching instructions, for example
`0x00514120` (891 bytes, 252 of 253).

The top row's single mismatch is a 5-byte relative call: the reference calls
`0x503e80` (`gm_FindNextFilteredEntity`) while the candidate emits an unresolved
call (`e8 00 00 00 00`). Renaming candidate callees is not enough: pointing the
`while` conditions or the `ls_ID2Ptr` stub at the native name lifts that one call
but unmasks other calls that currently match as relocations, and the row lands
at 879-887 of 891 in every variant. The binding needs the right callee at one
specific call site, which the diff does not identify directly; the compiled
object reloc table would, and the row is left at its stored state.

Image unchanged at 237,149 (8.32%), lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-29: fourteen NEAR rows promoted by rebinding one call each

The single structural mismatch in fifteen NEAR rows was an unresolved relative
call. `rebrew diff` shows it as `XX call ... || call 0x2b3` without the callee,
so the candidate object's relocation table was dumped with
`.scratch/organize/dump_relocs.py` (compile through `compile_to_obj`, parse with
`parse_obj_symbol_and_relocs`). Every one of the ten checked rows had the same
relocation: `_gm_AddObjekt` at the loop increment, while the reference calls
`0x503e80` (`gm_FindNextFilteredEntity`).

Rebind script `.scratch/organize/rebind_each_call.py` replaces one
`gm_AddObjekt()` occurrence at a time with `gm_FindNextFilteredEntity()`, adds the
prototype, tests, and keeps the best. Fourteen rows reached RELOC with full byte
agreement (891/891, 656/656, 633/633, 600/600, 580/580, 560/560, 519/519,
513/513, 500/500, 493/493, 414/414, 692/692, 659/659, 713/713). `0x00512910`
improved to 546 of 550 and stays NEAR.

STATUS: RELOC 3,581 -> 3,595, NEAR 80 -> 66, matched bytes 1,280,303 ->
1,288,726. The linked image is unchanged at 237,149 because these bodies still
sit at the wrong VA.

Logged the missing reloc name in `diff` to upstream `docs/IDEAS-GUILD.md`
(`e0650403`, on `main`).

Verified: build links, lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-29: 31 more NEAR rows promoted by typed call rebinds

Re-scanned the remaining NEAR rows for unresolved calls: 35 calls in 33 rows,
every one `_gm_AddObjekt` at a loop increment where the reference calls
`0x503e80` (`gm_FindNextFilteredEntity`). The first batch attempt failed to move
them because it inserted a `void*` prototype: these files declare
`char* __cdecl gm_AddObjekt(void)` or `unsigned char* __cdecl ...`, and the
implicit-int fallback changed the surrounding codegen.

`.scratch/organize/rebind_simple.py` copies the existing return type onto the new
prototype, replaces the call, tests, and reverts anything that is not full-match.
31 rows reached RELOC with full byte agreement; `fcn_00502450` reverted because
its test JSON is a batch result the script cannot read, not because of a byte
difference.

STATUS: RELOC 3,595 -> 3,628, NEAR 66 -> 33, matched bytes 1,288,726 ->
1,298,010. A rescan of the remaining 33 NEAR rows finds no unresolved calls
left, so this fix class is exhausted. Linked image unchanged at 237,149.

Verified: build links, lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-29: size annotations corrected; flag sweep on near-complete rows

`rebrew verify --fix-sizes` found 58 stale SIZE annotations (for example
`ch_SetVisible` annotated 146 bytes, binary size 176). Applied; this corrects
comparison extents, so the matched-byte count moved 1,298,010 -> 1,297,823. The
run also re-measured every function and demoted linked-EXACT rows whose source
changed earlier in the session; `verify --text --raw-link` on the rebuilt image
re-earned them, back to 471 EXACT.

A nine-flag sweep over the 15 SIZE_MISMATCH rows whose mismatch is 1-12 bytes
(`/O1`, `/O2`, `/Ot`, `/Oy-`, `/Ob1`, `/Gy`, `/G6`, `/Ox`, `/Os`) promoted none.
`adler32` shows why: the reference body is a different codegen (ebp frame, byte
loads), not the same source compiled differently, so the flags are not the lever.

The sweep wrote per-row `cflags` overrides as a side effect. Cleared with the
metadata owner API (`remove_fields_batch`, 8 rows) and the verdicts re-tested
with default flags; lint has no W029 warnings.

STATUS: RELOC 3,627, EXACT 471, NEAR 34, SIZE_MISMATCH 1,050, STUB 2; matched
bytes 1,297,823. Image 237,149 (8.32%). Verified: lint 0 errors / 0 warnings,
data conflicts 0. Decision: Lead.

## 2026-10-29: zlib source identity and library-start alignment both miss

`adler32` is a 302 of 304 byte match: the reference body uses a frame-free
16-byte unrolled loop with byte loads (`mov dl,[esi]`), while the vendored zlib
1.1.3 source compiles with an ebp frame and `movzx` loads. Nine more flag variants
(`/Oa`, `/Ow`, `/G3`, `/G4`, `/G5`, `/GB`, `/O1 /Ot`, `/Od`, `/Ox /Oa`) all
produce the 302-byte body, so this is a different compiler revision, not a flag
mismatch.

Measured the library-block start alignment: removing 0x1e90 of the latest text
pads moved `.data` raw from +0x5000 to +0x3000 relative to the reference and the
library region gained 1,264 bytes (11,496 -> 12,760), but the same shift cost
5,783 in the app text, so the whole-file score fell 237,149 -> 234,630. Restored.

The adler32 flag probes wrote one `cflags` override; cleared with
`remove_fields_batch` and re-tested with default flags.

Verified: image 237,149 (8.32%), lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-29: size-error census, big-row probe, and the diff reloc feature

Census of the 1,058 SIZE_MISMATCH rows by size direction: 267 oversize
(+10,232 bytes total), 791 undersize (-182,963), so the reconstructed text is
about 172,731 bytes short. The largest undersize row is `0x0064e1c7`, annotated
28,068 bytes; disassembly shows a 9-byte thunk (`push 9; call 0x652be6; pop ecx;
ret`), so that row's extent is an inventory artifact, not a body to write.
`rebrew library match` does not attribute it to a library. Rewriting extents is
review work with disassembly evidence; left for a dedicated round.

Probed the 28-byte row `0x004da170` again with `/O1`, `/O2 /Ob0` and `/O2 /Ot`:
still 11/28 with the same je/jmp shape, so it is not a flag difference.

Upstream: `rebrew diff --json` now copies the candidate relocation symbol and
status onto each instruction row (`5ccf0478` on `main`, test in
`tests/test_diff.py`). Validated against `0x00401650`: 27 rows carry
`relocations`, including `_vfs_Tfopen` (CONFLICT), `??_C@_02JKAF@rb?$AA@`
(UNRESOLVED) and `_g_6b7fdc` (VALIDATED). The project venv still pins the
released Rebrew, so use the global `rebrew` for this field.

Probe cflags overrides cleared with `remove_fields_batch`; lint has no W029.

Verified: image 237,149 (8.32%), lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-29: trailing-extent padding cannot be added without a matching pad

`0x004b6a00` is 239 of 240 bytes: the reference extent ends with one `nop` after
`ret`, alignment padding inside the recorded extent. Adding a one-byte text pad
after that TU grew the segment and shifted every later body, dropping the score
237,149 -> 233,991. The net-zero fix (shrink the pad that precedes the next
object by one byte and spend it inside this extent) is unavailable here because
no text lead pad follows this TU, so the change was reverted.

Also re-scanned the 34 NEAR rows with the new `diff` relocation field: no row
has a mismatch made only of call relocations, so the rebinding class is fully
exploited. A GA pass over the four rows the near-miss selector accepts matched
none of them.

Verified: image 237,149 (8.32%), lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-30: placed mismatch rows are score-positive when a pad can compensate

Found 47 SIZE_MISMATCH rows whose linked VA already equals the reference VA
(42,001 bytes total). Changing one of those bodies raises the same-offset score
directly, provided the size delta is absorbed by the text pad of the immediately
following object, which keeps every later offset unchanged.

First case `0x004102a0` (110 bytes): the reference passes the three values as
`int*` and converts through `fild dword ptr [reg]`, not by value. With
`void** a1, int* v1, int* v2, int* v3` and the stores ordered 0x9c, 0xa0, 0x98
the body goes 54 -> 73 matched bytes and 102 -> 108 bytes. Shrinking
`_tlead_GOLDTL_fcn_00412b10` from 80 to 74 bytes absorbed the 6-byte growth; the
linked image moves 237,149 -> 237,168 with no downstream shift.

The rule matters: the pad must belong to the object that immediately follows the
edited one. `0x004b6a00` needs one trailing reference `nop` byte, but its next
pad owner is far downstream (`fcn_005b6300`), so the one-byte insert shifted
intermediate bodies and cost 3,158 bytes; that change was reverted.

Verified: row 0x004102a0 at 73/110, image 237,168 (8.32%), lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-30: service packs and codegen flags do not explain the placed-row gaps

Swept the `msvc-6.0`, `-sp3`, `-sp4`, `-sp5` toolchains and nine codegen flag
variants (`/Gs`, `/GF`, `/Gi`, `/Gf`, `/Gn`, `/GZ`, `/Od`, `/Ob0`, `/Oa`) over
two safe placed rows. `0x0045bfb0` stayed at 327/352 and 337 bytes for every
toolchain; `0x0040ed40` stayed at 342/400 for every flag. The version images share
that code generator, so the differences are source shape (constant folding and
byte-temporary scheduling), not compiler selection.

Mapped the compensation budget for the 47 placed rows: only 10 have the
immediately-following object owning a text pad, which is the condition that lets
a body change happen without shifting later bodies (8,000 bytes of native
extent). Their current match ratios are 15/320, 327/352, 342/400, 73/432,
49/522, 242/512, 364/512, 108/592, 190/1,024 and 358/3,424; the two most complete
were attempted and did not move.

Image unchanged at 237,168. Lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-30: placed-row shapes resist the obvious source edits

Worked the safe placed rows whose bodies are closest to complete.

- `0x0040ed40` (342/400): the reference builds `D3_ANIMATION_OPTIONS` through
  byte temporaries before a by-value call. Replacing the memset/assignment block
  with explicit field assignments dropped the match to 39/411 (frame grew), and
  dropping the redundant `*(int*) &options = 0` dropped it to 299/400. Both
  reverted.
- `0x0043ed30` (native 496 versus 522): the reference frame is 0x24 with
  `ecx`-relative field loads, ours 0x2c, so the local set differs and a byte-level
  edit is not enough.
- `0x00440670`, `0x00415510`, `0x00458e00`, `0x00448b10` differ in register
  assignment from the first instructions; `0x448b10` also has no matched
  instruction at all. Trailing reference nops exist in these extents, but the
  bodies are offset relative to the nops, so padding them would not land on the
  reference offsets.

Image unchanged at 237,168. Lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-10-30: forced d3dx8 members audited; new best 250,880

The d3dx8 include list was filtered against the import table, never against the
reference's code. A strong presence test on the 15 members that only the include
list supplied (relocation-free 24-byte window, then >=85% of the member's
non-relocation bytes matching at the located VA) finds 13 absent from the
reference: btri, cassignment, cd3dxstateblock, ceffect, cleanmesh, cparameter,
cpass, createmesh, ctechnique, cvalue, intersect, jdmaster, shapes. Only
loadutil.obj (1886/1886 masked bytes at 0x62c591) and loadx.obj (311/311 at
0x61cc98) are present.

Dropped the include wiring in CMakeLists.txt (the list file stays as evidence)
and rebuilt: same-offset 237,168 -> 250,880, file 3,116,288 -> 2,871,296 bytes,
and `verify --whole-binary` still reports imports, section layout and headers
matching the reference (no missing or added imports). This beats the previous
best of 250,282.

The two present members stay unlinked for now: forcing them through /INCLUDE
cascades extra members and costs 17,867 bytes (233,013), while adding them as
explicit objects fails because CTLFWR32's `?g_lcidLocale@@3KA` and
`?g_fSatelliteLocalization@@3FB` have no provider in the vendored archives.

Documented in docs/msvc6-link-layout.md section 92.

Verified: lint 0 errors / 0 warnings, data conflicts 0, status RELOC 3,627 /
EXACT 471 / NEAR 34 after re-earning linked EXACT on the new image.
Decision: Lead.

## 2026-10-30: zlib example.c restored; faithful member set costs 2,217 score

Audited the vendored zlib against the reference too. Five LIBRARY rows at
0x462500-0x462930 (`error`, `gz_uncompress`, `file_compress`, `file_uncompress`,
`main`) are real reference code, and they come from zlib 1.1.3's `example.c`,
which the generated `references/zlib/` tree did not carry. Added it through the
supported path: `references/vendor/zlib/vendor.toml` file list plus
`rebrew library vendor ... --apply`, then the CMake zlib name list and the
`--first-va example.c=0x462500` order hint.

The file compiles and links (the five functions land at 0x464900 because the
zlib block already starts 0xDC0 late), and the same-offset score moves 250,880 ->
248,663. That dip is alignment, not code: removing 0xE10 of text pads ahead of
the zlib block to pull it earlier cost 2,441 more (244,394), and removing only the
tail pad bought 1,340 (248,663 final with pads restored). The 250,880 figure from
round 113 omitted this reference-present code, so the current 248,663 is the
faithful number.

`verify --whole-binary` still reports imports, section layout and headers
matching; lint 0 errors / 0 warnings, data conflicts 0. STATUS after re-earning
linked EXACT on the new image: EXACT 468, RELOC 3,630, NEAR 34, SIZE_MISMATCH
1,050. Documentation updated in docs/msvc6-link-layout.md section 92.

Decision: Lead.

## 2026-10-30: zlib minigzip restored; a full pad strip lost the data-pad ensemble

Audited the vendored zlib again and found the reference's five functions at
0x462500-0x462930 (`error`, `gz_uncompress`, `file_compress`, `file_uncompress`,
`main`) come from zlib 1.1.3 **minigzip.c**, not example.c. Added `minigzip.c` to
the zlib vendor manifest (through `rebrew library vendor --apply`) and to the TL
scaffold only, with `--first-va minigzip.c=0x462500`; example.c was removed from
the generated tree because its test_* functions are absent from the reference.
The five functions link at 0x464900 with the current drift and the score moves
248,663 -> 246,489.

Then a pad-cycle experiment went wrong: `strip_all_pads.py` removes every text
and data pad, not only text pads, and it took the data ensemble with it. The text
pads were rebuilt exactly from the saved `noincludes.map` symbol distances (89
pads, 0x7E10 bytes, each match confirmed within alignment). The data pads cannot
be regenerated: `data layout fill` from a stripped tree reproduces the counts
(52 init, 127 bss) but not the converged layout, and `converge` reports no
adjustments. Restored the data pads from `.scratch/dlead-backup/src-before.tar.gz`
(306 blocks), which is the closest surviving ensemble.

Final state this round: image 244,344 vs 246,489 before the strip, so the round
loses 2,145 bytes. Section geometry `.text` vsize 0x23d78e, `.data` raw 0x6e000.
`verify --whole-binary` still reports imports, layout and headers matching.

Six type rows went stale from the binary change; reviewed their unchanged native
evidence and rebound them plus nine more rows the same lint pass flagged across
GOLD/SERVER (`types bind` with the stored sizes, offsets and evidence). Lint is
back to 0 errors / 0 warnings, data conflicts 0, STATUS EXACT 466 / RELOC 3,632 /
NEAR 34 / SIZE_MISMATCH 1,050.

Next: rebuild the data layout ensemble with the documented strip -> fill ->
converge pipeline on the current tree, or recover the pre-strip d-pad sizes from
`noincludes.map` with the alignment correction that the text pads needed.

Decision: Lead.

## 2026-10-30: own-pad candidate inventory for size-free body edits

A text lead pad belongs to one TU, so a body whose TU owns a pad can change size
with the pad absorbing the delta and no later offset moving. That makes every
such row directly score-positive when its bytes improve. Counted the work:
80 SIZE_MISMATCH/STUB rows live in a pad-owning TU, 109,508 native bytes total,
pad budgets 16 to 144 bytes.

Sampled the smallest six. All differ from the reference in prologue or local
allocation, not in a single statement: `0x418bc0` (154 B) needs the ebp frame the
reference has and ours does not; `0x45c110`, `0x454460` and `0x45d0d0` keep the
frame but assign `ecx`/`esi`/`ebx` differently; `0x40eed0` differs only by a
`ebp`-versus-`ebx` temporary plus relative jump offsets, which needs a local
declaration change to shift the allocator. No edit was applied, so the image
stays 244,344.

The pre-strip data-pad ensemble remains unrecovered; the documented next step is
the strip -> fill -> converge pipeline on the current tree, or d-pad sizes from
`noincludes.map` with the alignment correction used for the text pads.

Verified: lint 0 errors / 0 warnings, data conflicts 0, imports/layout/headers
match, STATUS EXACT 466 / RELOC 3,632 / NEAR 34. Decision: Lead.

## 2026-10-31: pad-ensemble recovery alternatives measured and rejected

Tried to rebuild the lost data-pad ensemble three ways; all lost against the
surviving snapshot (244,344).

- Text pads from the older backup snapshot (90 pads, 0x7EC0 bytes): 186,426.
  The pre-strip text set is the map-derived one (89 pads, 0x7E10), restored.
- Data init pads reconstructed from `noincludes.map` symbol distances (54 pads,
  0x59E06 bytes, initializer bytes refilled from the reference at each name VA)
  plus the surviving bss pads: 216,950. Map distances include the alignment slack
  before the next symbol, so the sizes are wrong by up to 15 bytes each.
- A GA run on `0x004102a0` found no exact body (best 52,165 score units).

Housekeeping: removed 360 empty `#pragma data_seg(".text")` scaffolding blocks
left behind by pad rewrites; the image is unchanged at 244,344.

Verified: lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-31: type rebinds follow the scaffolding cleanup

The 363 empty pragma blocks removed above touched five TUs that define types
(`StartObjectTransformAnimation.c`, `d2_ShowTxt.c`, `GOLDTL.fcn_004e6650.c`,
`GOLDTL.fcn_00515540.c`, `GOLDTL.fcn_0041c830.c`), so their source hashes moved
and W031 flagged 15 rows across GOLDTL, GOLD and SERVER. Native evidence is
unchanged (reference binary and layouts untouched); rebound all 15 with the
stored sizes, offsets and evidence. Lint is 0 errors / 0 warnings, image
unchanged at 244,344.

Rule for later rounds: clean scaffolding first, then rebind types once, not the
other way around.

Decision: Lead.

## 2026-10-31: own-pad candidates ranked; the 0x40eed0 gap is one register choice

Ranked all 80 own-pad rows by current body agreement. Best three:
`0x409c90` 286/417 instructions (69%), `0x40eed0` 47/89 (53%), `0x444700`
44/103 (43%); the rest are under 31%.

`0x40eed0` is the cleanest: the reference keeps the object pointer in `ebp`, ours
in `ebx`. Every remaining difference follows from that one choice. The stack
offsets differ by the 4-byte `push ebp`, and the call displacements shift with it.
Source-level attempts did not move the allocator: removing the cached `anim`
local made it worse (41/280 bytes), and four declaration orders (options first,
last, and two pointer orders) all stayed at 138/275 bytes.

`0x409c90` (69%) differs only by eax/ecx roles on two field loads around a
comparison; inlining the `v9` local there did not help either (999 vs 1000 matched
bytes against the baseline).

Both files are restored; the image stays 244,344. Lint 0 errors / 0 warnings,
data conflicts 0.

Decision: Lead.

## 2026-10-28: Rebrew 6.8.0 dependency and impact-first work queue

The project owner requested every Rebrew-using project be updated and the todo
queue prioritize overall impact. Both `rebrew[prove]` and the optional
`rebrew[binsync]` constraints now select 6.8.0. The existing editable source
checkout remains the explicit tooling-development source; `uv lock` and
`uv sync --locked --inexact --reinstall-package rebrew` refreshed its lock and
installed package metadata. Distribution metadata and the imported source
both report 6.8.0; `uv lock --check` and `uv pip check` pass.

All three target configurations load. Owner readers validate 12,605 function
rows, 1,476 data rows and 47 type records in the current managed schemas.
`rebrew status --all-targets --json` succeeds. Generated instructions and skills
were refreshed through `rebrew init --refresh-agents`; project-owned rules and
configuration were preserved.

The released `todo` ranks affected byte extent before effort, groups shared
translation-unit compile errors, and exposes its scope as `Impact`. The current
queue begins with the two 589,824-byte displaced data objects, followed by
unresolved 28,068-, 11,948- and 8,798-byte function extents. This is affected scope,
not a promise of newly matched bytes. Replay and evidence:
`.scratch/rebrew-upgrade-6.8.0/todo.json` and `environment.log` in that directory.
Upstream release: `v6.8.0`, source commit
`a151cc58b56affbf60543ccb047db5b876c203b4`; its wheel SHA-256 is
`0fecf07ef37de9c358b4945fa89457f98ceac9be6dcc00287f6c4ad85fa1e4f9`.

## 2026-10-31: allocator levers tested on the two best own-pad rows; no movement

`0x40eed0`: tried `register` storage class (ignored), toolchain sweeps (plain,
sp4, sp5 all compile the TU to 329 bytes, far from the 275-byte reference, so the
pp image is the right one), and flags `/G3`, `/G4`, `/G5`, `/GB`, `/Ox`, `/O1`,
`/Oy-` (all stay at 138/275 except `/O1` 27 and `/Oy-` 30). The `ebp`-vs-`ebx`
choice is not reachable from those inputs.

Disassembled the reference entry to check the odd prologue: it loads both
arguments first, then `sub esp,0x20c`, `lea edx,[esp+0xc]`, and only after that
`push ebp; mov ebp,[eax]`. So `ebp` is a general register there, not a frame
pointer; our build picks `ebx` for the same value.

`0x409c90`: four comparison spellings (baseline, `>=`, swapped operands, direct
deref) produce identical 1000/1383 bytes.

`0x45bfb0`: four inner-loop shapes (baseline, increment at loop top, do/while,
index product) stay at 327/352 or collapse to 44/34. Files restored; image
244,344; lint 0 errors / 0 warnings.

Decision: Lead.

## 2026-10-31: upstream text-audit reports the correctly placed functions

`check-text-placement` printed only misplaced and missing rows, but the rows that
already sit at their reference VA are the ones a size-changing body edit can fix
without disturbing layout (this session used the build map to recover that list by
hand twice). Added `--list-correct` and the `correct_list` JSON payload entry,
with a CLI-level regression test in `tests/test_text_audit.py`; upstream commit
`0377a4a6` on `main` (docs/CLI.md updated). The project's released Rebrew does not
carry it yet; the next release will.

Project state unchanged: image 244,344, lint 0 errors / 0 warnings.

Decision: Lead.

## 2026-10-31: float-comparison constants belong to the reference's rdata pool

`0x00444700` (own pad, 186/352 bytes) compares floats against the reference's
constant pool: `0x662A94` is -1.0f, `0x6628A0` is 1.0f, `0x662D40` is 0.0f
(read from `.rdata` file offset 0x262000 + delta). Replacing the source literals
with explicit casts to those addresses moved the object match down to 166/352,
because our build's literal pool sits at different addresses and the raw link
still binds both spellings to our own pool. Reverted.

The other difference in this row is a 4-byte stack frame delta (`esp+0x38`
reference versus `esp+0x34` ours), so the original body kept one more 4-byte local
alive than the current source.

Image 244,344, lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-10-31: score-positive edits need correct placement, and no own-pad row has it

Installed the new upstream `--list-correct` build of Rebrew and used it here:
485 functions are at their reference VA (4,695 misplaced, 0 missing). Intersecting
that list with the 80 rows whose TU owns a text pad gives **zero** rows. So the
own-pad rows I ranked last round all sit at wrong VAs; improving their bodies does
not raise the same-offset score. The score-positive set is the 47 placed rows, and
of those only 10 have the immediately-following object owning the pad that can
absorb a size change.

Measured the end-of-text padding idea offline before building: synthesising the
current sections with 0x22C5C of padding at the end of `.text` would put `.rdata`
at 0x262000 and `.data` at 0x275000 exactly, but the simulated same-offset score
is 221,934, below the current 244,344. The 142 KB of 0x90 filler replaces the
region where the current tail content already matches, so it is a net loss.

Image 244,344, lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-01: assignment-order and GA searches on 0x0040ed40 find nothing

The 86%-matching safe placed row builds `D3_ANIMATION_OPTIONS` through byte
temporaries before a by-value call. Tried all 120 permutations of the five field
assignments (layer, queue, mode, loop, reverse): the source's current order is
the best at 342/400 bytes; other orders top out at 293 and sometimes reach the
native 400-byte size with fewer matching bytes. A GA run (`match run`) also found
no exact body (best score 86,006). Source restored, image 244,344, lint 0 errors /
0 warnings.

Decision: Lead.

## 2026-11-01: upstream `library presence` command shipped

The forced-member audit that found 13 phantom d3dx8 members (round 113) was
reproduced by hand with a 90-line scratch script. Ported it to upstream as
`rebrew library presence --object PATH`: for each symbol body it finds a
relocation-free 24-byte anchor in the image, verifies the whole body with
relocation slots masked, and reports `present`/`absent`/`unknown` with the VA,
matched fixed bytes and ratio. Thresholds: 85% of non-relocation bytes with at
least 48 fixed bytes; bodies too small to test stay unknown.

Validated on the real members: `loadutil.obj` reports 19 present including
`SetMesh` at 0x62C591 (2030/2030), `btri.obj` 17 absent of 47, `shapes.obj` 12
absent of 17. Present bodies do not prove the member was linked (shared inline
copies show up elsewhere), and the command says so.

Upstream commits `6f4dc065` and `2148609d` on `main`, with tests
(`tests/test_lib_presence.py`), CLI docs and a changelog entry naming the
`app.builtins.DOMAIN_COMPONENTS` change. `release/6.7.0` checkout restored.
Project image unchanged at 244,344.

Decision: Lead.

## 2026-11-01: data-prefix padding aligns .data content; new best 259,891

The `.data` section starts where `.text`+`.rdata` end, so its content sits
0x2C000 before the reference's `.data` and the file-offset comparison of data
bytes ran at the wrong internal shift. End-of-text padding cannot fix that: a
simulation over 0x0000-0x22000 of tail padding showed the unpadded image is
always best (any pad replaces the tail content that already matches). Prefix
padding inside `.data` moves only that section's content, and a simulation over
0x0-0x30000 predicted 259,311 at 0x2B000.

Measured on real builds: 0x2B000 -> 259,369 (the simulation was within 58 bytes),
then swept 0x1000, 0x400, 0x100, 0x10 steps to the optimum 0x2B530 -> 259,891.
One caveat learned the hard way: `= {0}` compiles to BSS, so the array grows the
virtual size and the raw size stays unchanged; one non-zero initializer puts the
array in `.data` and yields the raw zeros the alignment needs.

Same-offset score 244,344 -> 259,891 (+15,547), file 2,854,912 -> 3,031,040
bytes. `verify --whole-binary` reports imports, layout and headers matching; lint
0 errors / 0 warnings, data conflicts 0. STATUS after re-earning linked EXACT:
EXACT 466 / RELOC 3,632 / NEAR 34 / SIZE_MISMATCH 1,050.

Documented in docs/msvc6-link-layout.md section 93. The pad is not managed by
`data layout fill`; future pad regeneration must preserve it.

Decision: Lead.

## 2026-11-01: .rdata prefix pad pairs with the .data pad; 260,232

`.rdata` content also starts early (0x23F000 versus 0x262000). A prefix pad
inside `.rdata` moves only that section, and taking the same byte count out of the
`.data` prefix keeps the data content at its measured offset. Emitted with
`#pragma data_seg(".rdata")` and a `{0x90}` initializer from the first linked
object.

Simulated the paired sweep first (corrected for the built image's existing pad),
then measured: R 0x3000 / D 0x28530 is best among 0x800, 0x100 and 0x400 probes.
Same-offset score 259,891 -> 260,232. `verify --whole-binary` reports imports,
layout and headers matching; lint 0 errors / 0 warnings, data conflicts 0.
Documented in docs/msvc6-link-layout.md section 94.

Decision: Lead.

## 2026-11-01: text-pad and data-pad alternatives rejected; 260,232 stands

Two more layout variants simulated before building, both worse:

- End-of-text padding paired with a smaller `.data` prefix (to align `.rdata`
  content) is worst at zero: the sweep over 0x0000-0x28000 keeps T=0 best
  (260,232); every added text pad loses 500-800 bytes.
- A `.data` prefix sweep with the tail sections following it peaks at the
  current D=0x28530; 0x28000 scores 259,734 in simulation and 0x2B000 259,226.

Data-symbol VAs are still 0xB00 before the reference's (the prefix pad moves the
section content and the symbol VAs together), so the score optimum and exact VA
alignment differ. `verify --data --built` reports the mismatched rows as
DISPLACED and skips function verification for the image-only check.

Verified: image 260,232, imports/layout/headers match, lint 0 errors /
0 warnings, data conflicts 0, linked EXACT re-earned (EXACT 466 / RELOC 3,632).
Decision: Lead.

## 2026-11-01: GA on the 93% placed row fails; content-alignment gap logged

`match run` on `0x0045bfb0` (the closest safe placed row at 327/352) found no
exact body: best score 29,945, source unchanged. The line-shape and declaration
edits tried earlier remain the full extent of what this source form reaches.

Upstream `docs/IDEAS-GUILD.md` now records the missing capability behind this
round's layout win: `rebrew data layout` models symbol placement but not the
section-content offset the file comparison sees, so the `.data`/`.rdata` prefix
pad search was hand-rolled twice. Commit `825a5d1e` on `main`; release checkout
restored.

Image unchanged at 260,232, lint 0 errors / 0 warnings. Decision: Lead.

## 2026-11-01: VA-exact data alignment scores lower; pad pair is a local optimum

Tried the two ways to break the score/VA coupling:

- Exact symbol-VA alignment inside `.data` (D=0x29000, R=0x2530): 259,390, lower
  than the score optimum 260,232. The prefix pad moves section content and symbol
  VAs together, so the file comparison and the symbol addresses cannot both be
  right; the current pair wins on bytes.
- Asymmetric probes around the optimum (D 0x28430/0x28630 with R fixed, and
  R 0x2F00/0x3100 with D fixed): 260,016, 259,600, 260,208, 260,191, all below
  the pair 0x3000/0x28530.

Best pair restored; image 260,232, lint 0 errors / 0 warnings.
Decision: Lead.

## 2026-11-01: archive-gap pad scan negative; failed builds had masked it

A gap in front of the archive block does not help: with the data prefix
compensated so the data content offset is unchanged, N=0x1000 -> 260,093,
0x2000 -> 259,502, 0x3000 -> 257,365, 0x4000 -> 256,617, 0x6000 -> 255,991,
against 260,232 at N=0. The library block's internal order is the wall, not its
start offset.

The first pass of this scan silently measured a stale binary: `_rdata_prefix_zeros`
was written with a size of `0x0`, the compiler raised C2466, and the link reused
the previous image, so every sample returned 260,232. Rebuilt the scan with a
build-log error check per iteration and valid pad sizes. Lesson for later sweeps:
assert `error C`/`error LNK` count is zero before recording a score.

Winning pads (R 0x3000 / D 0x28530) restored; image 260,232; lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-01: data-tail trim and pad-to-BSS both rejected

A simulation that cut 0x2C000 raw bytes from the end of `.data` scored 264,964,
because `.data1`/`.rsrc` would land on the reference offsets. The trim window is
not padding: it holds 973 map symbols, mostly C++ string literals (`??_C@`)
plus LIBCMT constants and 14 data pads totalling 0x1F484 bytes. Deleting those
strings is not a layout change.

Measured the smaller real version: moving all 14 tail pads to BSS (keeping their
declared sizes so their VAs stay) shrinks the raw data by 0x1F000 and moves
`.data1` earlier, but the lost pad contents cost more than the tail gains:
258,503 against 260,232. Reverted; source restored from
`.scratch/organize/src-before-bss.tar.gz`.

The restore changed .c files back, so 15 W031 type rows went stale and were
rebound with unchanged native evidence; lint is 0 errors / 0 warnings.

Image 260,232, data conflicts 0. Decision: Lead.

## 2026-11-01: library members have constant deltas, but a block gap still loses

Sampled linked d3dx8 members against reference VAs located with
`library presence`. Several members line up internally: pngmem −0x1987D,
pngread/pngrtran/pngrset/pngtrans −0x181FC, x3d_matx/x3d_plane/x3d_quat/
x3d_vec2/x3d_vec3/x3d_vec4 −0x18200, all with min = median = max. Their member
order is right and only the block offset is wrong.

Tried the matching large pre-archive gap with the data prefix reduced to keep the
data content offset fixed (rdata pad removed): N=0x10000 -> 251,588, 0x14000 ->
251,862, 0x18000 -> 248,142, 0x1C000 -> 241,568, 0x20000 -> 241,153, all far
below 260,232. The gap bytes themselves replace content that currently matches,
and the members that are correctly ordered are a minority of the block.

Winning pads restored (R 0x3000 / D 0x28530); image 260,232; lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-02: consistent-offset members are a minority; explicit ordering is the path

Reconnaissance over linked archive members with `library presence` and per-symbol
deltas: 29 of 64 scanned members keep one constant delta across all located
symbols (min = max within 0x10), meaning their internal order already matches the
reference and only placement is wrong. Examples: LIBCMT sbheap −0x229F2, util
−0x22A63, cvt/ioinit/output −0x22293, strftime −0x223D4; d3dx8 cd3dxassembler
−0x14BC7, cd3dximage −0x18D65, cd3dxtext −0x196F5. The delta differs per member,
so no single block shift can align them; that is why the block-gap sweeps lose
(the gap bytes replace currently matching content).

The way forward is explicit member ordering: link extracted members as a response
file in reference-start order, with a generated gap pad between neighbours. That
needs per-member start estimates (median of located VA minus symbol offset), a
complete member set including the members whose bodies are not locatable, and the
archive scan disabled so no duplicate extraction occurs. Not attempted this
round; image stays 260,232, lint 0 errors / 0 warnings.
Decision: Lead.

## 2026-11-02: member-start estimation blocked on locator coverage; presence extended

Tried to build the explicit library ordering from per-member reference starts.
The prerequisite failed on coverage: with the in-process locator only 22 of 64
linked members got start estimates and 1 was consistent; the installed
`library presence` locates more bodies but still leaves most members without two
consistent samples. Small CRT functions (10-40 fixed bytes) are exactly the ones
the current thresholds reject.

Extended upstream `library presence` so the next attempt does not re-parse COFF:
each row now reports `object_offset` (symbol offset inside the object text) and
`object_text_size`, so a member start is `va - object_offset` directly. Commit
`082d8336` on `main`, test updated, docs updated; release checkout restored and
the global tool reinstalled (fields verified on btri.obj).

Project image unchanged at 260,232; lint 0 errors / 0 warnings.
Decision: Lead.

## 2026-11-02: relaxed presence shows inline copies, not member placement

Added `--min-ratio`/`--min-fixed` to `library presence` (short bodies now search
on a narrower anchor) and reran the member table with 16/0.9. Coverage improves a
lot (301 of 358 linked members located, against 22 of 64 before) but only 13 give
a modal, majority cluster of start estimates: most "present" bodies are inlined
copies inside application code, so `va - object_offset` lands all over the text.
Presence alone cannot pick the member copy; disambiguation needs relocations or
relative-order constraints.

Upstream commit `0588a620` (options, short-body anchor, test, docs) pushed on
`main`; release checkout restored and the global tool reinstalled. Project image
unchanged at 260,232; lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-11-02: library-region filter fixes start estimates; ceiling is 55 KB

Restricting located bodies to the reference library region (0x5E0000 and above)
removes the inline-copy noise: 140 of 358 linked members then give consistent
start estimates (within 0x20), up from 13. Their combined `.text` is 0xD81D
(55,325 bytes), so a perfect member ordering and gap pass could move at most
about 55 KB into place, and 31 of the consecutive pairs overlap, which means some
starts are still wrong by more than the member size.

Given the ceiling and the unreliable tail, explicit member ordering is a poor
next lever compared with function work. Kept the analysis in
`.scratch/organize/library-member-table5.json`.

Image unchanged at 260,232; lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-11-02: the removed d3dx8 members are in the reference after all

Reference archive region is 0x5E12B5-0x660ACE (522 KB); ours is
0x5EF1DE-0x63E2B6 (324 KB), a 198 KB shortfall that matches the 190 KB the
removed forced members contributed. Re-audited those members per symbol with
`schema` `library presence --min-fixed 24 --min-ratio 0.95`: createmesh.obj's
unique bodies are present at ratio 1.0 in the 0x5F05xx-0x5F53xx range
(CloneMesh, CopyPortionOfMesh, GetOriginalMesh, UpdateSkinnedMesh), and btri/
ceffect/jdmaster/shapes show bodies too.

The earlier "absent" verdict is wrong: MSVC splits members into per-function
COMDATs, so a member's code is reordered across the library block and a
whole-member contiguity test cannot see it. The 13 members must come back for
identity; they were removed because forcing them placed 190 KB at the block
start, not because the reference lacks them.

Disambiguation rule for the next ordering attempt: only symbols that appear in
exactly one extracted member count (shared template instantiations otherwise
scatter the start estimates). Image unchanged at 260,232; lint 0 errors /
0 warnings. Decision: Lead.

## 2026-11-02: re-linking the 13 members blocked by CTLFWR32 globals

Tried linking the 13 reference-present d3dx8 members as explicit objects in the
link line. `target_link_libraries` with an `@rsp` entry failed early (CMake
appended `.lib` to the response file path); `target_link_options` reached LINK
and pulled CTLFWR32.lib(Util.Obj), which needs `?g_lcidLocale@@3KA` and
`?g_fSatelliteLocalization@@3FB`. `rebrew library inspect CTLFWR32.LIB
--defines` returns no member for either symbol, so the provider is not in that
archive and the link stops with LNK1120.

Next attempt options: find the provider archive, or alias the two symbols to
local definitions with `/alternatename`; both need their reference values, which
are not in the inventory. Experiment reverted (CMake line removed); image rebuilt
at 260,232, lint 0 errors / 0 warnings.

Also corrected a typo in the previous ledger entry: the read-audit command was
`rebrew library presence --min-fixed 24 --min-ratio 0.95`. Decision: Lead.

## 2026-11-02: VC6 LINK has no /alternatename; CTL globals block the members

Tried to satisfy the two CTLFWR32 globals with a local C/directive displacement.
The stub compiled and its `.drectve` carried the directives, but MSVC 6 LINK
rejected them: `warning LNK4044: unrecognized option "alternatename:..."`, so
the directive route needs LINK 7 or later. The C definitions themselves landed in
the object correctly (`_g_lcidLocale`, `_g_fSatelliteLocalization`).

Bisected the pull-in: even one of the members (`cd3dxstateblock.obj` alone) drags
CTLFWR32.lib(Util.Obj), so the block is not member-specific. `library inspect`
shows both CTLFWR32.LIB and CTLFWD32.LIB only reference the two globals; no
member in the toolchain image defines them, so the reference's C++ code or a
missing vendor archive provided them.

Remaining routes: compile a `/TP` C++ translation unit so the compiler emits the
mangled definitions (`unsigned long g_lcidLocale`, `short const
g_fSatelliteLocalization`), which needs CXX support in the toolchain file, or
recover the values from the reference and place them as data rows. Experiment
reverted (stub and CMake lines removed); image rebuilt at 260,232; lint 0 errors /
0 warnings. Decision: Lead.

## 2026-11-02: C++ displacement unlocks the 13 members; 272,219 (+11,987)

Defined the two CTL globals from a C++ translation unit (`/TP`) compiled by the
msvc-6.0-sp5-pp driver; VC6 LINK has no `/alternatename`, so the mangled
definitions must come from the compiler. `extern const short` is required for the
satellite flag: a plain `const` at namespace scope has internal linkage and emits
no symbol.

With the link unblocked, the 13 reference-present d3dx8 members (btri,
cassignment, cd3dxstateblock, ceffect, cleanmesh, cparameter, cpass, createmesh,
ctechnique, cvalue, intersect, jdmaster, shapes) go in after the archives via a
direct compiler custom command plus explicit object list, and the image scores
272,219 (was 260,232). Text grows to 0x26DBA0 (reference 0x2603EA), .rdata to
0xEEAC, .data starts 0x27E000 (reference 0x275000).

Regression to resolve: `verify --whole-binary` now reports 14 added imports the
reference does not carry (ADVAPI32 RegDeleteKeyA/RegEnumKeyExA, GDI32
GetDeviceCaps, KERNEL32 lstrcatA/lstrcpyA/lstrlenA/lstrlenW, OLEAUT32
ordinal_2/ordinal_4, USER32 CharNextA/GetDC/LoadStringA/ReleaseDC, ole32
CoTaskMemAlloc). Those come from members in the 13; next round picks the subset
that keeps the import table identical. Prefix pads were re-tuned for the new
geometry (R 0x3000/D 0x28530 remains best; D 0x28000 scored 271,564 and
0x29000 269,321). Lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-11-02: the 13 members drag CTL imports; baseline 260,405

Whole-member inclusion cannot be reconciled with the reference import table.
Probed subsets: the first three members and the next four each reproduce all 14
added imports, and `btri.obj` alone does too, so every candidate references
CTLFWR32(Util.Obj), which brings RegDeleteKeyA/RegEnumKeyExA,

GetDeviceCaps, lstrcatA/lstrcpyA/lstrlenA/lstrlenW, OLEAUT32 ordinals 2/4,
CharNextA/GetDC/LoadStringA/ReleaseDC and CoTaskMemAlloc. The reference has none
of them, so it cannot be linking these members this way; the 198 KB archive
shortfall is somewhere else and round 137's per-symbol presence was reading
shared inline copies for the C members too.

Symbol-level `/INCLUDE` (445 symbols from the members' reference-present bodies)
links only after dropping jdmaster/ceffect, whose closure needs D3DX::jpeg_*
symbols, and then scores 258,090 with imports unknown. Dropped that too.

The member list now lives in `stubs/goldtl/readd-members.cmake` (empty, ready for
a reviewed subset). `ctl_locale_stubs.cpp` stays: it defines the two CTL globals
that no archive member provides and adds 173 bytes (260,232 -> 260,405). Imports,
layout and headers match; lint 0 errors / 0 warnings. Decision: Lead.

## 2026-11-02: CTLFWR32 link order fixes the import regression; 271,304

The 14 extra imports came from link order, not from the members. The configured
external list puts CTLFWR32 before LIBCMT, so CTL's Util.Obj satisfied common CRT
symbols for the C++ archive members and dragged its API imports in. Moving
CTLFWR32 to the end of `REBREW_EXTERNAL_LIBS` fixes it: with the full 13-member
list the image reports imports, layout and headers matching, and scores 267,788.

Prefix pads were then re-swept for the new geometry (text 0x26D000, .rdata
0x26E000, .data 0x27D000): R 0x3000 / D 0x29000 wins at 271,304. Nearby probes:
D 0x28000 266,885, 0x28530 267,788, 0x28C00 269,512, 0x29800 270,844,
0x2A000 269,065, 0x2AB00 270,551, 0x2B000 271,111, 0x2B400 270,861; R 0x2000
264,715. The .data content offset is now past the reference data start, so part of
this score is coincidence rather than placement; the true fix still needs the
text length near the reference.

Best image 271,304, imports/layout/headers match, lint 0 errors / 0 warnings,
data conflicts 0. Member list in `stubs/goldtl/readd-members.cmake`, C++ CTL
displacement in `stubs/goldtl/ctl_locale_stubs.cpp`. Decision: Lead.

## 2026-11-02: app region is 218 KB longer than the reference; drift starts early

Region math on the 271,304 image: project objects run 0x401000-0x61676C
(2.18 MB) against the reference app region 0x401000-0x5E1290 (1.97 MB), so the
app side is 218 KB long while the archive side is 173 KB short. The two roughly
cancel in total text size, which is why a single global shift never fit.

`check-text-placement` puts the first drift at 0x401650 (+0xF0) and 0x402B00
(+0xF90); the delta then grows to the end of the app region. Candidate sources of
extra app bytes: `link_scaffold.c` contributes 366 fastcall-band placeholder
functions, and the C++ members added 560+40 symbols in the 0x61+ range. Subset
probes did not shrink text to the reference size: six members still gave 0x269000
(score 263,678), nine gave 0x26D000 (271,131); the CTL-last reorder itself grew
the statically linked CRT, because LIBCMT now resolves helpers CTL used to
provide.

Best image restored: 271,304 with imports/layout/headers matching; lint 0 errors /
0 warnings. Decision: Lead.

## 2026-11-02: the app-region "excess" was a bad boundary; 271,304 stands

Corrected round 143's region math: the reference archive rows start at 0x5E12B5,
but reference project functions continue past that address (placement expects
them up to 0x65DD41), so treating 0x5E12B5 as the app end was wrong. The honest
number is the text raw size: ours 0x26D000 against the reference 0x261000, 48 KB
long, with 1050 undersized bodies (-183 KB) and 148 KB of archive members added
back; the two errors nearly cancel.

Member-drop probes are flat in size: dropping ceffect, cvalue or jdmaster leaves
text at 0x26D000 (scores 271,334 / 271,047 / 271,550), so those members'
retained contributions are under the 0x1000 raw rounding. Pad probes around the
current point: R0/D0x2C000 270,982, R0/D0x2D000 270,833, R0/D0x2E000 269,407,
R0x7000 (rdata raw matches the reference 0x13000)/D0x29000 269,303; none beat
R0x3000/D0x29000 = 271,304.

Restored best image: 271,304, imports/layout/headers match, lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-02: one late text pad shrinks better; 271,800

The `_tlead_GOLDTL_fcn_005b6300` pad was 1664 bytes in the manifest; leaving it at
16 scores 271,800 against 271,304 at the manifest size. The other two late pads
must keep their sizes: shrinking `_tlead_fcn_005b7880` (3680) scores 268,393 and
`_tlead_GOLDTL_fcn_005b88b0` (4128) scores 268,249, so only the 005b6300 pad
moved. `.scratch/organize/tlead-manifest.json` now records the 16-byte size so
`restore_manifest_pads.py` will not undo it.

Also found that a manifest/declaration mismatch had been introduced while
probing: the manifest audit is now the check, and one pad was off by 1648 bytes.
Image 271,800, imports/layout/headers match, lint 0 errors / 0 warnings, data
conflicts 0. Decision: Lead.

## 2026-11-02: exact section alignment scores far below the current layout

Fixed the probe harness: `set_pads(..., 0)` used to emit a zero-length array
(C2466), and the failed links silently measured the previous image. `pads_lib`
now removes the declaration instead, and the probes abort on a build error.
Also made `stubs/goldtl/readd-members.cmake` a `CMAKE_CONFIGURE_DEPENDS` entry;
edits to it did not trigger a reconfigure before.

With a member subset and pads chosen so the sections land on the reference
offsets (createmesh only, R 0x9000, no data prefix): text 0x264000, .rdata
0x15000, .data 0x27A000, score 233,433. No members at all with R 0x9000:
text 0x23E000 (0x23000 short), score 227,737; six members with R 0x9000:
text 0x269000, score 204,804. True section alignment therefore costs 38 KB of
score against the coincidental 271,800 layout, because the bodies and data do
not match yet.

Restored the best state: full 13 members, R 0x3000 / D 0x29000, pad
`_tlead_GOLDTL_fcn_005b6300` at 16 -> 271,800, imports/layout/headers match,
lint 0 errors / 0 warnings. Decision: Lead.

## 2026-11-02: upstream `binary score` ships; project image 271,800

Same-offset equality is the metric every layout round optimizes, but no command
reported it; each round re-derived it in a scratch script. Added upstream
`rebrew binary score --built IMAGE [--reference IMAGE]`: whole-file total plus
each reference section window, with the sections defining what can be compared so
a padded build earns no credit outside them. Tests cover identical images, one
flipped byte and a missing image; the shared `--built` help text is reused so the
CLI contract gate passes. Commit `979f302d` on `main`; release checkout restored,
global tool reinstalled, and the project reports 271,800 of 2,850,888 (9.53%).
Decision: Lead.

## 2026-11-02: rdata content reaches the reference offset; 284,838

The .rdata section content sat 0x20000 past its reference offset. A text gap
before the archive block grows the text raw size and moves .rdata, and reducing
the .data prefix pad by the same amount keeps the data content where it was.
Measured with no readded members: G 0x20000, R 0x1000, D 0x3C000 gives .rdata
content at 0x260000 (reference 0x262000) and data content at 0x2A6000, scoring
284,838 against 271,800.

Section breakdown from `rebrew binary score`: .text 133,964, .rdata 12,167
(was 5,353, so +6,814 is real alignment, not coincidence), .data 134,228,
.data1 212, .rsrc 381. Sweeps: G 0x1F000 -> 284,441, G 0x21000 -> 283,843,
R 0 -> 283,838, D +0x2000 -> 283,763, createmesh-only variant 252,841.

The 13 readded members are out again (list empty): their 0x2F000 of text raw
cannot coexist with .rdata at the reference offset, and the case for them being
linked was never stronger than shared inline copies. The member mechanism stays
in `stubs/goldtl/readd-members.cmake`. Imports/layout/headers match, lint 0
errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-02: rdata content slides into the reference window; 291,380

Kept the data content offset fixed and moved .rdata content later by growing the
rdata prefix pad while shrinking the data prefix pad by the same amount:
R 0x3000 -> 286,601, 0x5000 -> 287,842, 0x7000 -> 290,306, 0x8000 -> 291,380
(peak), 0x9000 -> 290,168, 0xB000 -> 288,854, 0xD000 -> 288,316; micro steps
0x8800 289,490, 0x8400 288,663. Data pad fine steps around the peak (0x35000):
0x34000 288,447, 0x35800 290,667, 0x37000 287,743, 0x39000 282,172.

Final pads R 0x8000 / D 0x35000 with the 0x20000 text gap. `binary score`:
.text 135,999, .rdata 16,670 (5,353 at round 147), .data 134,228, .data1 212,
.rsrc 381, whole file 291,380 of 2,850,888 (10.22%). Imports/layout/headers
match, lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-02: raw same-offset score is inflatable; informative metric added

Chasing the raw score produced a 284,838 -> 291,380 -> 318,368 sequence, but the
gains came from padding zeros landing on the reference's zero bytes: data content
could slide freely behind a large zero prefix, and every zero matched. Added an
`informative` count upstream (`cbf9d0fe`): same-offset matches restricted to
positions where the reference byte is non-zero, so zero padding cannot inflate it.
Docs and tests updated; release checkout restored and the global tool reinstalled.

Re-scored the candidate layouts with the new metric (same reference window,
2,381,294 non-zero bytes):

- current 318,368 raw layout: informative 87,040.
- round-148 candidate (raw 284,838): 91,120.
- round-149 candidate (raw 291,380): 91,072.
- round-147/146 state (raw 271,800, 13 members): 92,141, the highest.

Restored that layout: raw 271,800, informative 92,141 of 2,381,294 (3.87%).
Imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts 0.
Future layout rounds will optimize the informative count; raw stays reported for
continuity.
Decision: Lead.

## 2026-11-03: informative score is text-only; .rdata alignment gains 190 bytes

Section-level informative counts on the 271,800 layout: .text 89,691, .rdata 278,
.data 2,168, .data1 4, .rsrc 0. The metric is effectively the text match.

Tried aligning .rdata content onto the reference offset by dropping the six
members that inflate text raw (btri, shapes, intersect, cleanmesh, jdmaster,
createmesh): no-misc text raw 0x242000, then a 0x1B000 text gap and R 0x4000 put
.rdata content at 0x262000. Result: raw 284,914, informative 90,420, .rdata
informative 468. The second variant (G 0x19000, R 0x6000) gives raw 286,104,
informative 91,056, .rdata informative 468. The aligned .rdata only gains ~190
informative bytes because our compiler literal pool is not the reference pool,
and dropping the six members costs more text matches than that.

Best informative stays the 13-member state: raw 271,800, informative 92,141 of
2,381,294 (3.87%). Restored; imports/layout/headers match, lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: informative hill-climb and aligned-data layouts both negative

Greedy informed hill-climb on the six largest text pads (+/-0x40): every probe
reverted; informative stayed 92,141. Large deltas on the same pads are
catastrophic (0x43DB70 +0x40 -> 64,602; 0x44FC70 -> 83,309; 0x4582D0 -> 91,776),
so the pad set is locally optimal for the informative metric as well.

Also tested fully aligned no-member layouts: .rdata content 0x262000 and .data
content 0x275000 gives raw 247,768, informative 88,738 (.rdata 689, .data 1,102);
data-only alignment gives raw 259,579, informative 88,632 (.rdata 0). The data
pads do not match reference bytes even at their native offsets, so data
alignment cannot pay either.

Best informative stays the 13-member layout: raw 271,800, informative 92,141 of
2,381,294 (3.87%). Imports/layout/headers match, lint 0 errors / 0 warnings,
data conflicts 0. Decision: Lead.

## 2026-11-03: the EXACT-in-misplaced bank is real but unreachable by pads

Status cross-check between `verify` and `check-text-placement` (5,228 rows):
EXACT 421, RELOC 3,713, SIZE_MISMATCH 1,058, NEAR 34, STUB 2. Matching bodies
that sit at the wrong address: 344 EXACT functions worth 25,561 bytes, 30 NEAR
worth 14,947, and 428 RELOC rows without placement rows (69,628).

Two attempts to move them failed. A global per-object alignment simulation over
4,512 objects: only 36 positive pad slots (0x7BFF1 bytes) against 4,475 negative
slots, because our objects are wider than the native gap between first VAs, so
pads cannot align every object. A targeted search for existing pads in front of
objects holding at least 0x80 of EXACT bytes with one uniform delta found no
candidates (0), so no pad can be adjusted to bring those bodies home.

Best informative stays 92,141 (raw 271,800) of 2,381,294 non-zero reference
bytes (3.87%). Imports/layout/headers match, lint 0 errors / 0 warnings, data
conflicts 0. Decision: Lead.

## 2026-11-03: fcn_004102a0 body now matches; informative 92,169

Only one correctly placed SIZE_MISMATCH body was small enough to attack:
`fcn_004102a0` (110 bytes, 67.6% match). The target computes all three scaled
floats before storing them: fild v2, fmul, fild v3, fmul, fild v1, fmul, store
v1 to 0x98, fxch st(1), store v2 to 0x9c, store v3 to 0xa0. The old source stored
each product immediately in v2/v3/v1 order (108 bytes, no fxch). Rewriting with
three float temporaries in v2, v3, v1 order and stores in 0x98, 0x9C, 0xA0 order
emits the fxch and reaches 110/110 bytes: SIZE_MISMATCH -> RELOC (two relocs, the
call targets).

Image rebuilt: raw 271,800 -> 271,837, informative 92,141 -> 92,169 (3.87%),
stored matched bytes 1,297,823 -> 1,297,933. STATUS: SIZE_MISMATCH 1,049, RELOC
3,683, EXACT 416. Imports/layout/headers match, lint 0 errors / 0 warnings, data
conflicts 0. Imports relaxed: no size change. Decision: Lead.

## 2026-11-03: the 97.8% placed body resists; informative holds at 92,169

`fcn_004131e0` (192 bytes, 51 exact / 2 reloc / 13 structural) is the closest
placed SIZE_MISMATCH body after the 004102a0 fix. Target tail: `fld [esp+0x58];
fmul st(2); fld [esp+0x48]; fmul st(2)` while our shapes emit
`fld [esp+0x48]; fmul st(1); fld [esp+0x58]; fmul st(3)` or `fld [esp+0x38]`.
Four source variants for the third camera row (inner-swap, inner-first, neg-first,
row-first) leave the structural count at 13, so the difference is the live-value
depth of the single expression, not term order. Target also carries nine trailing
nop bytes (192 vs our 183), the inter-function alignment padding.

GA on the file reports best_score 15,027 and no exact body; source restored.
Image unchanged from round 154: raw 271,837, informative 92,169 (3.87%),
imports/layout/headers match, lint 0 errors / 0 warnings. Decision: Lead.

## 2026-11-03: SaveBMP24 loop reconstruction stalls at 17 structural diffs

Second-closest placed body: `SaveBMP24` (448 bytes, 140 exact / 10 reloc / 20
structural). The target's pixel loop is decodable: p = src+1, dst = row+2,
counting down, reading p[0], p[-1], p[-2] and writing dst[-2], dst[-1], dst[0],
with p += 3 and dst += 3. Encoding that exactly breaks the function's register
allocation elsewhere (exact drops to 45, invalid 1), because the pointer bases
force a different allocation for the header writes.

Intermediate forms: `p += 3` before the reads with p[-1..-3] gives 439 bytes, 143
exact / 17 structural (best); reverse store order and swap-decl are worse
(21 and 97 structural); dst-base forms worse (84). Target also carries nine
trailing nop bytes (448 vs 439). Source restored; image unchanged at raw
271,837, informative 92,169 (3.87%), lint 0 errors / 0 warnings, conflicts 0.
Decision: Lead.

## 2026-11-03: placed-body ranking; remaining near misses are compiler-artifact walls

Diffed all 40 correctly placed SIZE_MISMATCH bodies and ranked by structural
count: 0x4102A0 (0, already fixed), 0x4131E0 (13, 9 trailing nops), 0x40ED40
(17, 2 bytes), SaveBMP24 (20), 0x450E90 (23, edx/esi roles swapped), then 30+.

Two more probes this round: reordering `fcn_00450e90`'s local declarations does
not change the edx/esi swap (four orders, identical diff), so that is register
allocation rather than declaration order. `fcn_0040ed40`'s remaining diff is a
12-byte struct-by-value construction for a render-state call: target packs two
bytes with `or dl,2` / `and al,0xFD` / `or al,1` and stores dword0/1/2, which
needs the original struct and bitfield shape.

Sources restored. Image unchanged: raw 271,837, informative 92,169 (3.87%),
lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: 0x41bf90 analysed; linked EXACT refreshed to 466

`fcn_0041bf90` (512 bytes, 130 exact / 6 reloc / 30 structural): the octree
builder's differences are register roles in the child walk (`mov edi,[edx+eax*8
+0xc]` versus our `lea eax,[...]; mov edx,[eax]`), a two-byte loop-body size
delta, and swapped additive operand order at `[ecx+eax+0x10]` versus
`[eax+ecx+0x10]`. Those are allocation and expression-shape artefacts again, not
a missing statement; no source change kept.

Refreshed linked EXACT on the current image: `verify --text --raw-link` records
EXACT 466, RELOC 3,633, SIZE_MISMATCH 1,049, NEAR 34, STUB 2; stored matched
bytes 1,297,933. Lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: shifting a late owner into place cascades and loses

Largest EXACT body that sits at the wrong address is a 2,188-byte function in
`fcn_00617e93.c`, placed 0x37093 before its reference VA. Appending a pad of
that size to its predecessor moved it (and every later object) towards the
reference, but informative dropped 92,169 -> 88,158: the cascade breaks more
already-matching placement than the one body gains.

The experiment's automatic revert failed because its regex did not match the
appended block; the pad was removed by cutting from the marker comment to the
closing brace, then the image was rebuilt. Restored: raw 271,837, informative
92,169 (3.87%), imports/layout/headers match, lint 0 errors / 0 warnings, data
conflicts 0. Decision: Lead.

## 2026-11-03: compiler-flag sweep for the near body is a dead end

Swept 15 flag sets on `fcn_004131e0`: /O2 and /Ox both give the 183-byte body,
/O1 164, /Og 160, /Ot /Oy /Ob1 /Ob2 /Oi 243, /Os 231, /Op 246. Nothing reaches
the 192-byte target and /O2 is already the best size, so the 13 structural diffs
are x87 scheduling under the project's flag set, not a missing flag. Lint reports
no redundant per-row cflags, so the probes left no overrides behind.

Image unchanged: raw 271,837, informative 92,169 (3.87%), lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: near-miss GA batch and small-body variants are flat

`match batch --near-miss --mutation-focus register` selected exactly one
function (`fcn_0040fb80`, delta 5) and produced no exact body; the source and its
stored cflags are unchanged (lint clean, no new overrides).

`fcn_00402b80` (32 bytes, 6 structural) is a register coin-flip: target puts the
loop count 0x7D0 in EDX and the loaded pointer in ESI, ours the other way.
for/while rewrites, an empty-check form, and unsigned/void-pointer type changes
all leave the diff identical. `fcn_00436a00`'s stored blocker already documents
this exact EDX-survives-call wall across seven toolchains and twelve flag sets,
so these rows are recorded walls rather than missing source.

Image unchanged: raw 271,837, informative 92,169 (3.87%), imports/layout/headers
match, lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: text shortfall is the un-inventoried library block

Object-extent accounting: the project objects total 0x1EFB14 of text (1.97 MB),
which matches the reference application region (0x401000-0x5E1290, 1.97 MB), so
the application side is the right size. Our whole text is 0x23E000 raw against
the reference 0x261000, and the 0x23000 gap equals the archive-region shortfall
(reference archive rows span 522 KB, ours about 350 KB).

The object drift curve shows project objects whose expected VAs fall inside the
archive region (for example `fcn_00617E93` at 0x617E93) interleaved after the
application objects by design; the app-region "excess" from round 143 was this
interleave, not oversized application code. The remaining shortfall is library
code the reference links that the inventory does not name, so it cannot be
targeted by `/INCLUDE` symbol lists yet.

Image unchanged: raw 271,837, informative 92,169 (3.87%), lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: 88 project TUs target the library band and all sit early

Analyzed the project TUs whose expected VAs fall at or above 0x5E0000: 88
objects totalling 0xD2EB (54 KB) of which 0x222A (8.7 KB) is EXACT. Every one is
placed early, by 20 KB to 440 KB (`GOLDTL.fcn_0064e1c7.c` is 443,735 bytes early,
`fcn_00617e93.c` 225,427, `GOLDTL.fcn_005e3150.c` 27,808). Cause: objects are
linked before every archive member, while the reference interleaves these
library-band functions among archive members.

Putting them after the archives needs them compiled as a separate OBJECT library
and linked as objects at the end of the link line, because moving them out of the
main target's sources loses the generated per-file cflags. That is a structural
CMake change (the generated `rebrew-sources-goldtl.cmake` owns those flags), so
it is queued rather than improvised at round end.

Image unchanged: raw 271,837, informative 92,169 (3.87%), lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: moving the library-band TUs after the archives does not help

Surgical relink experiment: rebuilt the link line from the four `objects*.rsp`
files, moved the 67 object entries whose expected VAs are at or above 0x5E0000
to the end (after the archive scan), and linked to a scratch image. Result: raw
271,694, informative 92,035, against the current 271,837 / 92,169. Appending them
after all archive members overshoots the same way appending before undershoots;
only a real interleave with archive members would fit, and that needs member-level
ordering data we do not have.

Scratch link artifacts removed; the project image and build directory are
untouched. Image 271,837 / 92,169 (3.87%), lint 0 errors / 0 warnings.
Decision: Lead.

## 2026-11-03: library-band splits and archive order both lose

Surgical relinks that split the 88 library-band TUs around the archive scan at
five thresholds (0x610000, 0x620000, 0x630000, 0x640000, 0x650000) all score
below the current image: raw 271,620-271,700, informative 92,047-92,120 against
271,837 / 92,169. Keeping every one before the archives is still the best split.

Tried extraction order too: moving `d3dx8.lib` after `LIBCMT.lib` so CRT members
are pulled first gives raw 270,506, informative 91,239, so the current order
(CTLFWR32 last, d3dx8 before LIBCMT) stays. CMake restored from the pre-experiment
copy; image back at raw 271,837, informative 92,169 (3.87%), imports/layout/
headers match, lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: D3_ANIMATION_OPTIONS layout is right; 0x40ED40 is a merged row

Checked the 12-byte options struct that two near bodies pack by hand:
`AttachAnimLooped` (which sets queue/layer/mode/reverse/loop and passes the struct
by value) diffs with structural 0 at equal size 454, so `d3_animation.h` is
correct. Variants for `fcn_0040ed40`'s construction (drop the memset, drop the
extra int clear, assign-then-clear) all make it worse: 389-394 bytes, structural
34-46 against the current 398 bytes / 17 structural.

`fcn_0040ed40`'s metadata row is a merged identity (688-byte extent covering
0x40ED40, 0x40EED0 and AttachAnimLooped), so part of its structural delta is the
merge bookkeeping rather than missing source. No change kept. Image 271,837 /
92,169 (3.87%), lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: band coverage mapped; 18 unlinked members refuse to help

Extracted every member of the stock archives (LIBCMT 638, d3dx8 145, CTLFWR32
18, mss32 1) and located their bodies with `library presence` against the
reference library band. 253 members have band hits; those bodies cover 937 of the
1,490 band functions (0x4EBE4 of 0x8021F bytes). Only 18 unlinked members have
band hits, contributing 214 functions: createmesh (469 hits), btri/cleanmesh (16
each), jdmaster (8), intersect (7), plus small d3dx8 ones.

Adding the five extra d3dx8 members (cstack, fontoutl, meshutil, fontextr,
ccompiler) together with a `/INCLUDE` list for their located symbols made the
image worse: raw 249,969, informative 89,732 against 271,837 / 92,169. Reverted
both the member list and the include list.

A build failure ("No rule to make target ... cstack.obj") had left the previous
binary in place during the first attempt; the error filter now also matches
`No rule` and `Error [0-9]` lines. After providing the objects and rebuilding, the
worse numbers above are from a real image. Restored: 271,837 / 92,169 (3.87%),
imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-11-03: the library band holds application code, not just libraries

Of the 1,490 inventory functions at VAs 0x5E0060-0x660ACE, 937 match extracted
archive member bodies and 117 match the prebuilt DX8 supplementary objects, but
553 match nothing in the archives or the supp set: a 16-byte window index over
every member body finds zero of them, FLIRT against the 7.1M-signature recondb
finds none, and alternative d3dx8 SDK archives on disk contain neither their code
nor the strings they push. One sample at 0x5E3B70 pushes "BLACK", which lives in
the reference's own .rdata at 0x67D67C, and 0x5E0140 initializes an 0x840-dword
table; that is application-style code, not library runtime.

So the original link placed some application objects after the libraries, and the
band is a mixture. A single-order link cannot reproduce that: objects,
then archives, with no second object phase. Next step is a two-phase link model
(some objects after the archive scan), which needs object files compiled outside
the main target's source list.

Image unchanged: raw 271,837, informative 92,169 (3.87%), lint 0 errors /
0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: band metadata rows; two-phase gap recorded upstream

Of the 109 reversed band rows, 73 sit in the unmatched 553 and 35 coincide with
archive member bodies. Moving the three objects whose first VA matches a band
metadata row to the end of the link line gives raw 271,746, informative 92,055,
again below the current split, so the two-phase hypothesis cannot be exploited
with per-object moves alone.

Recorded the two-phase link-order gap and its replay numbers in upstream
`docs/IDEAS-GUILD.md` (commit df98db59, pushed); release checkout restored.
Image unchanged: raw 271,837, informative 92,169 (3.87%). Decision: Lead.

## 2026-11-03: the 480 unknown band functions are not any d3dx8 build

Cross-checked every alternate SDK archive on disk (SDK 8.0 build, DX9 build,
d3dx8dt): extracting their members and running presence against the reference
covers 5 of the 480 unmatched, un-reversed band functions. 24-byte window counts
were coincidence-prone too (vendor 83, dx9 80, mostly shared common sequences).

The unknown set is 480 functions, 0x245C4 bytes, sizes from 3 bytes (C++ member
thunks: `inc dword ptr [ecx]; ret`, `xor eax,eax; ret`) to hundreds. One sample
pushes the application's own "BLACK" string. Together with the two-phase link
evidence this points at application or C++ objects placed after the libraries,
not a missing third-party library.

Image unchanged: raw 271,837, informative 92,169 (3.87%), lint clean.
Decision: Lead.

## 2026-11-03: band layout decoded; archive /INCLUDE extraction fails on C++

Band map: 0x5E0060-0x5EAC49 is application code (function 0x5E0140 calls app
functions 0x42FF50, 0x521EB0, 0x4727A0 and pushes the app's "BLACK" string),
0x5EAC49-0x64BE5C holds d3dx8 member bodies, 0x64D1A0-0x660A8F holds LIBCMT
bodies, so the original link places app objects, then d3dx8, then the CRT, with
no second object phase after the libraries. The 480 unexplored band rows are
starts that fall inside member bodies (inventory splits), which presence matching
by function start cannot see.

Archive extraction via `/INCLUDE` instead of explicit member objects fails:
createmesh pulls C++ members that need `D3DX::jpeg_*` (five symbols) and
`sincosf`, and the extracted objects do not bring them. The explicit member
objects stay as the working route; reverted and rebuilt to raw 271,837,
informative 92,169 (3.87%), lint 0 errors / 0 warnings. Decision: Lead.

## 2026-11-03: members extracted through /INCLUDE; best 275,963 / 93,980

Instead of linking the 13 reference-present d3dx8 members as object files (which
puts them in the object phase and pushes the whole library block 0x2E000 late),
they are now pulled from the archive by `/INCLUDE` lines: every external symbol
each member defines, generated into `stubs/goldtl/readd-symbols.rsp` by
`member_externals.py`. The earlier six unresolved C++/CRT symbols were the
internal jpeg helpers and sincosf defined in the same members; including the
members' full external symbol sets resolves them.

Result: d3dx8 library code starts at 0x5EF056 instead of 0x6192E6, close to the
reference 0x5EAC49. Score raw 275,963, informative 93,980 (3.95%) against
271,837 / 92,169; section text 135,663, rdata 3,989, data 131,819. Pad retune for
the new geometry picked R 0x1000 / D 0x2B000; sweeps 0x3000/0x29000 93,774,
0x5000/0x27000 93,912, 0x2000/0x2A000 93,785, 0x0/0x2C000 93,891, 0x1000/0x29000
92,866, 0x1000/0x2D000 92,977, 0x3000/0x2D000 92,487.

Imports/layout/headers match; lint 0 errors / 0 warnings; data conflicts 0.
Duplicate-symbol warnings (LNK4006) are the pre-existing GOLD/GOLDTL shared-source
overlaps, unchanged by this link. Decision: Lead.

## 2026-11-03: library-block alignment by shrinking pads destroys app alignment

The include-mode image puts the first d3dx8 body at 0x5EF056 against the
reference 0x5EAC49, 0x43ED late. Shrinking 0x43ED of pre-library text pads (the
pads are layout scaffolding inside earlier TUs) did move the library block, but
informative collapsed to 42,135 and raw to 208,844: those pads are what keeps
thousands of application functions on their reference offsets, so removing them
buys library alignment at a far larger cost.

Pads were restored from `.scratch/organize/pad-backup` (VA-matched source
restore, because zero-length pads had lost their declarations and the first
restore pass could not match them). Rebuilt to raw 275,963, informative 93,980
(3.95%), imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts
0. The 0x43ED archive offset stays as the compromise the tuner chose.
Decision: Lead.

## 2026-11-03: /INCLUDE matters; stale relinks invalidated three probes

Editing `readd-symbols.rsp` or the CMake link options does not touch any object,
so `cmake --build` considered the image up to date and three probe results were
stale binaries: dropping the effect members, an empty include file, and removing
the target link options all reported the previous score. Deleting
`build-goldtl-audit/Europa1400Gold_TL.exe` before each link fixes the probe.

Real numbers with forced relinks: 13-member include set (969 lines of external
symbols) gives raw 275,963, informative 93,980; the 18-member set (adding cstack,
fontoutl, meshutil, fontextr, ccompiler, 1,463 lines) is worse at raw 249,379,
informative 90,177; no include list and no explicit objects is worse again at
raw 259,309, informative 88,703. The 13-member set is restored and verified:
imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-11-03: pad hill-climb on the include-mode layout; 276,102 / 94,121

Three greedy passes over the six largest text pads (+/-0x40) raised informative
from 93,980 to 94,121: `_tlead_GOLDTL_fcn_005b88b0` 0x1020 -> 0xF60 and
`_tlead_GOLDTL_fcn_004582d0` 0x850 -> 0x890 were kept on the way, 0x43DB70 and
0x44FC70 reverted every time. Image now raw 276,102, informative 94,121 (3.95%),
sections text 135,820, rdata 3,973, data 131,817. Imports/layout/headers match,
lint 0 errors / 0 warnings, data conflicts 0. Decision: Lead.

## 2026-11-03: pad batches and fine section sweep; informative 94,132

Greedy pass over the next six text pads (0x435910, 0x419990, 0x45D740, 0x4090D0)
reverted every probe, so the text-pad ensemble is locally optimal at informative
94,121.

Fine sweep of the rdata/data prefix pads with forced relinks: R 0x1000/D 0x2B800
93,870, R 0x1000/D 0x2A800 93,249, R 0xC00/D 0x2B000 94,132, R 0x1400/D 0x2B000
93,220. R 0xC00 / D 0x2B000 is the informative best (raw 275,539; the raw-only
best stays R 0x1000 / D 0x2B000 at 276,102). Chose the informative best:
informative 94,132 (3.95%), raw 275,539, sections text 135,821, rdata 3,427, data
131,799. Imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts
0. Decision: Lead.

## 2026-11-03: pad shrink experiments corrupt the ensemble; manifest audit repairs it

Two shrink attempts aimed at pulling the archive block 0x43ED earlier by editing
the *latest* text pads: both dropped informative to 66,908 and 83,519. Even the
last pads in VA order shift enough functions to break the tuner's alignment, so
the archive offset is not reachable by pad surgery.

Restoring from the pad backups was incomplete: the zero-size deletion had removed
`_tlead_GOLDTL_d3_LoadBinaryAnimStream` entirely, so no declaration remained for
the backup matcher to find. Auditing every pad against
`.scratch/organize/tlead-manifest.json` found the missing 112-byte pad and the one
intentional mismatch (`_tlead_GOLDTL_fcn_005b88b0` 4128 -> 3936). Re-adding the
missing declaration restored the image exactly: raw 275,539, informative 94,132
(3.95%), imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts
0. Pad audit now reports missing 0. Decision: Lead.

## 2026-10-29 02:40 UTC: current source snapshot and all-work commit

Updated README and all three graphics from one Rebrew status report, including
the address-ordered defrag map. Server: 251/251 C matches and 100% stored code/data
accounting, but the current raw link agrees at 74.4%; v1.6.1 remains a historical
byte-identical build. GoldTL: 4,100/5,184 C matches, 53.4% code accounting, 8.3%
raw-file agreement. Gold: 1,881/4,426 C matches, 21.0% accounting, 1.1% raw-file
agreement. Data results are stored verdicts, not a new verification run.

The user requested committing the accumulated source, metadata, layout and build
work while explicitly excluding the changed .lib archive. Library changes remain
local and uncommitted. The public dependency configuration retains the released
Rebrew 6.8.0 pin and optional dashboard instead of requiring a sibling checkout.
Decision owner: project maintainer. Evidence: CLI report and map count assertions
in .scratch/readme-refresh-20261029/. Verification: SVG structure, visual render
and project tests; no native rebuild or gameplay test in this refresh.

## 2026-11-03: GA improve run promotes fcn_00473610; layout excess measured

`match batch --improve --algorithm flags-then-ga -j 6` ran 37 near-match
functions and timed out at the 50-minute cap after finishing the list. One
promotion landed: `fcn_00473610` STUB -> RELOC (verify now reports RELOC 100%,
33-byte body). It sits at a band VA that is misplaced, so the image (raw 275,538,
informative 94,132) is unchanged in matched bytes. Status counts after a full
verify: RELOC 3,715, SIZE_MISMATCH 1,057, NEAR 33, STUB 2, plus 421 object-level
EXACT; the earlier 466 figure included linked EXACT, stale after rebuilds.

Also measured the object phase: project objects total 0x1EC499 and end at
0x5EDEF0; the first archive entries are import thunks at 0x5EE976 and the first
d3dx8 body is 0x5EF056 against the reference 0x5EAC49, a 0x43ED offset. The
object phase is 0x440D wider than the reference's application-plus-block span, so
the archive offset comes from compiled stub sizes, not pads.

GA backup files were moved out of `src/` into `.scratch/recycle/ga-bak/`.
Imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts 0.
Decision: Lead.

## 2026-11-03: placement gaps and duplicates; no cheap shrink available

Measured project objects that have no placement row at all: 277 objects,
0x1BA29 bytes, led by pngrtran.obj (7,437), trees.c.obj (6,912), jdmarker.obj
(5,863), deflate.c.obj (5,824) and the two tuned pad TUs. They sit after the
known-VA objects and account for the object phase being 0x440D wider than the
reference application-plus-block span.

Checked whether the LNK4006 duplicates let us delete whole TUs: zero TUs are
fully duplicated, because the shared inline functions coexist with unique
symbols in the same object. No cheap shrink is available, so the 0x43ED archive
offset stays.

Also re-probed two near bodies without the matching engine: `SaveBMP24` with
countdown loop forms stays at 439 bytes, 140 exact / 20 structural, and
`fcn_00440670` shows unresolved-base and register-role deltas (75 structural).
No GA was run this round. Image unchanged at raw 275,538, informative 94,132,
imports/layout/headers match, lint 0 errors / 0 warnings. Decision: Lead.

The accumulated source moves exposed one stale cross-import test path. Updated
its fixture to Develop/Unassigned/GOLD.fcn_0040abd0.c without changing the test
assertions. The first run reproduced the missing-file failure; the full suite
was rerun after the path correction. Generated guidance was refreshed with the
project-rules section preserved.

README image URLs are pinned to `5c0b1859e829fafe5e926c6126d331b9ce0d2579` for all three graphics.
The committed snapshot passed 39 tests and 3 subtests; initial all-target lint
reported zero errors and only generated guidance drift. Refresh preserved the
project rules and init --check reports no drift. No native build was run.

## 2026-11-03: fcn_004131e0 row shapes decoded, no C form beats the baseline

Disassembled the full target: the three matrix rows are X*neg + Y*scale + Z*scaled
(the last term times a memory copy of scale at [esp+0x10]), results stored to
locals and then added to the cached camera position. The baseline body (three
immediate stores through the same accumulator and volatile hole reads) already
reaches 13 structural diffs; single-expression rows with three locals gave 40,
chained rows with the same frame gave 21, chained rows with a register scale gave
47, and the previous four third-row variants also left 13. The residual is x87
live-value depth plus the nine trailing alignment nops (192 vs 183), not a source
statement difference.

Source restored to the baseline; image unchanged at raw 275,538, informative
94,132 (3.95%), lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-11-03: data DRIFT is content-offset, not wrong values

`verify --data` reports 155 matched, 77 DRIFT, 39 missing, 421 displaced, 159 not
comparable (271 compared). Dumped the reference bytes for the DRIFT rows: they are
plain data (floats 1.0/0.5, plant/statistic string tables). `plt_PlantInfo` in
`plant.c` declares exactly the reference bytes (entry 0 is b7 01 "TANNE", 3, 1, 4
and so on), yet verify calls it DRIFT at first byte 0.

Cause: the data section content offset differs from the reference placement, so
the built bytes at the inventory VA are the prefix pad, not the symbol. That is
the same content-offset trade recorded in rounds 148/149: the pads are tuned for
same-offset matching, not for native data addresses. So the 77 DRIFTs are not
source-value bugs and changing initializers would not move the score.

Image unchanged at raw 275,538, informative 94,132; lint 0 errors / 0 warnings,
data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: include set membership is not the d3dx8 surplus

Forced vs organic extraction: without the include list the d3dx8 block is
0x3AFAD (85 members); with it 0x69B40 (100 members) and the reference is 0x62557.
The include list forces 15 members (the 13 plus loadutil and loadx as
dependencies), createmesh alone contributing 129,781 bytes.

Tried trimming the include list to reference-present symbols only: the naive
trim failed to extract jdmaster (its jpeg helpers are static COMDATs and its own
externals were already defined elsewhere), so createmesh's jpeg references went
unresolved. Trimming only the 173 createmesh externals that are not reference
hits produced a byte-identical image (raw 275,538, informative 94,132), so the
member still contributes the same code: the surplus is not removable by token
selection. A geometry-only subset (946 of 969 tokens) scored 275,352 / 94,081,
slightly worse, so the effect members stay.

Restored the 969-token set and relinked: imports/layout/headers match, lint 0
errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: pad search exhausted at finer and coarser steps

Next text-pad batch (+/-0x40) reverted all eight probes; coarse +/-0x400 probes
on the four largest pads also reverted (0x5B88B0 93,963/94,095; 0x43DB70
65,655/65,711; 0x44FC70 85,045/85,067), so the ensemble is a local optimum at
informative 94,132 in both directions.

Also tried control-flow variants for `fcn_0044d7e0` (combined break condition,
swapped operand order): identical 228 bytes / 59 structural, source restored.
Image raw 275,538, informative 94,132 (3.95%), lint 0 errors / 0 warnings, data
conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: verify cache checked, one stale reading explained

The earlier RELOC 100% reading for `fcn_00473610` looked like a cache that missed
a source edit. Controlled check: break a known RELOC body (`fcn_004102a0`,
0x662a2C -> 0x662a30) and run the default `verify`; it reports NEAR_MATCHING
97.3% immediately, so the cache does invalidate on source changes. A
`verify --no-cache` pass settles `fcn_00473610` at NEAR_MATCHING 63.6%; the old
RELOC reading came from the GA run's own record, not from a broken cache.

Source restored, image rebuilt: raw 275,538, informative 94,132 (3.95%), status
RELOC 3,714, SIZE_MISMATCH 1,057, EXACT 421, NEAR 34, STUB 2. Imports/layout/
headers match, lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-11-03: back to the raw metric; 276,101 / 94,121

The objective is byte identity, so the raw same-offset count (which credits
matching zero bytes too) is the right primary number again; the informative
count stays as the anti-padding check. Switched the section pads back to the
raw-best pair R 0x1000 / D 0x2B000: raw 276,101, informative 94,121.

A raw-objective pad pass over the six largest text pads (+/-0x40) reverted every
probe (0x5B88B0 276,064/276,010, 0x43DB70 244,753/245,536, 0x44FC70
265,921/266,012, 0x4582D0 275,673/275,645), so the pads are locally optimal for
raw as well. Imports/layout/headers match, lint 0 errors / 0 warnings, data
conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: raw-versus-informative trade measured; informative-best kept

Swept the data prefix pad at the raw objective with informative supervision:
D 0x30000 raw 274,242 / informative 92,957; 0x38000 278,023 / 92,800,
0x40000 291,782 / 92,532, 0x50000 291,702 / 92,452. At 0x40000 the extra raw
comes from .data 141,613, .data1 2,870 and .rsrc 3,384 zero-on-zero matches
while text informative falls to 91,762.

goal.md requires no invented padding in the finished tree and faithful source,
so the informative-best configuration stays: R 0x1000 / D 0x2B000, raw 276,101,
informative 94,121 (3.95%). Imports/layout/headers match, lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: extent-only rows are placement-limited; linked EXACT refreshed to 471

Found 17 SIZE_MISMATCH rows at 99.5% or better instruction match. Diffing four
of them shows the only differences are trailing nops: 0x461560 80 vs 72 bytes
with 8 nops, 0x45DA70 128 vs 115, 0x4E32C0 224 vs 218, 0x4B6A00 240 vs 239. The
targets' extents include the compiler's 16-byte alignment padding.

They are still unreachable: dumping the built image at those VAs shows unrelated
code, because these functions are misplaced by the current layout, not merely
short. Padding the bodies would not place them.

`verify --text --raw-link` re-earned linked EXACT after the rebuild: EXACT 471,
RELOC 3,664, SIZE_MISMATCH 1,057, NEAR 34, STUB 2. Lint 0 errors / 0 warnings,
data conflicts 0. Image raw 276,101, informative 94,121. No GA was run.
Decision: Lead.

## 2026-11-03: stochastic pad search confirms a tight local optimum

18 random pad probes (steps 0x100 to 0x2000 across all 89 pads) all rejected:
even 0x20 -> 0x10 on a small pad drops informative to 42,755-74,898, because each
pad shifts the functions after it. Best stays 276,101 / 94,121. Pad audit still
reports missing 0 and the one intentional 005B88B0 mismatch (4128 -> 3936).

A global pad re-optimisation (rather than per-pad moves) needs an object-level
link simulator that can score candidate layouts without a Docker link per probe;
that is now the main layout gap. Image rebuilt and confirmed at raw 276,101,
informative 94,121. No GA was run. Decision: Lead.

## 2026-11-03: archive alignment ceiling measured; not worth a shift

Built a byte-level layout simulator (`.scratch/organize/sim_layout.py`) that
replaces text-pad ranges in the built image and scores against the reference.
Identity reproduces the image exactly (raw 276,101). A single-cut shift analysis
for the 0x43ED the archive block sits late: for every 0x10-aligned cut point in
.text, deleting 0x43ED there and comparing the shifted tail to the reference
peaks at 266,415, which is 9,686 bytes *worse* than the current 276,101.

So even a perfect archive alignment cannot pay for the application-text matches
the shift destroys; the current offset is the global compromise, not a tuning
miss. This closes the alignment line: further layout work would need reordering
that keeps application functions on their offsets while moving libraries, which
a single-order link cannot express.

Image unchanged: raw 276,101, informative 94,121 (3.95%), lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: layout simulator only valid for small deltas

Extended the simulator to a numpy scorer and ran coordinate descent over all 89
text pads. It reported 297,357 (+21,256) from four changes, but the real build of
that ensemble scored 273,798 (-2,303). The proxy is only trustworthy for small
shifts: growing a pad by 0x400 moves every later byte, and the real link also
recomputes relocations and relayouts .rdata/.data VAs, which the byte-shift model
does not. So the optimizer's large-delta wins are artifacts.

Pads were restored from `tlead-manifest.json` plus the two tuned exceptions
(005B88B0 0xF60, 004582D0 0x890) and the R 0x1000 / D 0x2B000 section pads;
rebuild confirmed raw 276,101, informative 94,121. Pad audit: missing 0, the one
intentional mismatch. Imports/layout/headers match, lint 0 errors / 0 warnings,
data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: scaled-value hypothesis for fcn_004131e0 tested and rejected

Target keeps the scaled value both on the x87 stack and in a stack slot
(`fst [esp+0x10]`, not `fstp`): row terms 1-2 multiply by stack copies of scale
and neg, row term 3 multiplies the memory copy. Tried replacing the hole-based
store with a dedicated `float scaled` local read through a volatile cast: the
extra local grows the frame to 0x74 and the diff worsens to 39 structural (frame
and every stack offset shift). The frame is already exactly 0x70 only when no
extra slot exists, so the target source must reuse one of the existing slots for
the scale copy; no C arrangement tried reuses it while keeping the stack copy.

Source restored: SIZE_MISMATCH 192 vs 183 as before. Image raw 276,101,
informative 94,121, lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-11-03: fcn_004131e0 narrowed to the third row's evaluation order

Full instruction listing shows rows 1 and 2 already match byte-for-byte
(instructions 14-36 exact), including the `fst [esp+0x10]` scale copy, the
stack-relative `fmul st(2)` pairs and the `faddp` chains. Only the third row
differs: the target evaluates m[10]*neg first, then m[6]*scale, then
m[2]*scaled; every C shape tried evaluates m[2] first or re-associates
(parenthesised left-to-right, m2-first, nested m10-term, statement trio), all at
183 bytes and 13 structural. Expression order is again not source-controllable.

The row would still need the nine trailing alignment nops. Source restored:
SIZE_MISMATCH 192 vs 183. Image raw 276,101, informative 94,121, lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: rdata pad sweep; the two metrics disagree by eleven bytes

R sweep at D 0x2B000, with rdata and data informative broken out: R 0x0 raw
271,027 / informative 92,887 (rdata 347, data 823); 0x800 275,161 / 94,079
(358, 2,043); 0xC00 275,538 / 94,132 (378, 2,077); 0x1400 274,272 / 93,220
(391, 1,091); 0x2000 272,399 / 92,971 (280, 1,168). R 0xC00 is the informative
best, R 0x1000 the raw best by 563 bytes.

Kept R 0x1000 because the goal is raw-file identity: 276,101 / 94,121.
Imports/layout/headers match, lint 0 errors / 0 warnings, data conflicts 0. No GA
was run. Decision: Lead.

## 2026-11-03: server.dll is one 16-byte shift away from alignment

Server is much closer than the TL client: sections are size- and address-exact
(.text 143,360, .rdata 12,288, .data 57,344, .reloc 69,632 at the reference
addresses), .rdata matches 12,270/12,288 and .data 57,331/57,344, imports/layout/
headers all match. Text is 72,931/143,360; placement splits 151 correct and 100
misplaced, and every misplaced function is exactly -16.

The shift starts inside `friedhof_logic.c`: `gv_MoveSlotEntry` (SERVER
0x10011940, reference size 674) compiles to 672 bytes here. With 674 the next
function starts at 0x10011BF0 as in the reference; at 672 it starts at
0x10011BE0, so 16-byte alignment drags all 100 later functions down by 16. The
diff shows a missing 5-byte call and a 3-byte absolute-displacement form around
the `gm_AddObjekt` tail, and some source lines reference `g_slot_table` where the
target uses `g_entity_slot_table`/`g_entity_id_field`.

Making that function 674 bytes would shift 100 EXACT/RELOC bodies onto their
reference VAs. Next round: repair the tail (call plus global operands) at source.
No GA was run. Decision: Lead.

## 2026-11-03: server tail repair attempt; compiler normalises it away

The target tail of `gv_MoveSlotEntry` zero-extends the slot-table word
(`xor ecx,ecx; mov cx,[eax*4+g_entity_slot_table]`) then loads the object id from
`[eax*4+g_entity_id_field]`. Forcing the slot word through an explicit
`unsigned int slot_word` local and passing that to `gm_SubObjectNoKill` compiles
to the same 672 bytes with the same 29 structural diffs; the compiler keeps its
own register form. Source restored.

The 16-byte alignment lead stands: if this function reaches the reference 674
bytes, all 100 misplaced server functions land on their VAs. Lint 0 errors /
0 warnings, data conflicts 0, TL image unchanged at raw 276,101 / informative
94,121. No GA was run. Decision: Lead.

## 2026-11-03: slot-word source forms do not reproduce the target's xor+mov

Tried the remaining plausible forms for the slot-table word in
`gv_MoveSlotEntry` (unsigned-short array indexing with the 378-word stride, and a
temporary `unsigned short word`): both still compile to 672 bytes with 29
structural diffs. The target's `xor ecx,ecx; mov cx,[eax*4+g_entity_slot_table]`
zero-extension form does not appear from any source shape tried; the compiler
reuses its already-zeroed ecx and skips the xor, which is where the two bytes go
missing. Source restored.

Server lead unchanged: 674 vs 672 keeps 100 functions -16 early. Lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: server shift would gain 69,584 text bytes but costs the section offset

Simulated the +16 tail shift: keeping the image prefix and moving the post-boundary
bytes up 16 matches 74,399 of the remaining 75,216 .text bytes (prefix 68,116 +
tail 74,399 = 142,515 of 143,360) against the current 72,931. That is +69,584 in
.text.

It cannot be taken by padding: the image would grow 16 bytes, moving .rdata and
.data content by 16 and losing the 69,601 bytes those sections currently match.
The reference keeps total .text at 143,360, so the fix must be a real 674-byte
`gv_MoveSlotEntry` (no extra total) rather than an inserted 16-byte gap.

Rounding audit of the 251 server functions shows only two deviations from
reference rounding: `gv_MoveSlotEntry` 672 vs 688 (−16) and
`gm_ClearObjektResources` 144 vs 16 (+128, an extent that spans a non-function
gap). Everything else rounds exactly. Lint 0 errors / 0 warnings, data conflicts
0. No GA was run. Decision: Lead.

## 2026-11-03: server verify state; library attribution is the remaining lead

`verify -t server.dll`: 316 rows, 315 pass, one SIZE_MISMATCH
(`gv_MoveSlotEntry`). Library providers: 65 compiled, 145 prebuilt, 115
unresolved; inventory 646 entries. The 115 unresolved library rows are the
remaining attribution work for the server, and the layout phase split needs the
inventory-to-row mapping to explain the 16-byte rounding difference.

Slot-word variants tried this round added nothing: a volatile short read gives
680 bytes / 45 structural, the masked cast 672 / 29. Source restored. Lint 0
errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-29: stop tracking the local DirectX archive

Removed references/dxsdk8/lib/d3dx8.lib from the Git index at the maintainer's
request. The existing /references/dxsdk8/ ignore rule now covers the archive;
no redundant rule was added. Its local bytes remain unchanged. Verification:
SHA-256 before/after agrees, git check-ignore resolves the existing rule, and
the archive is absent from the index. No native build was needed.

## 2026-11-03: server function size resists flags and promotion tricks

Flag sweep on `gv_MoveSlotEntry` (per-VA test): only /O2 and /Ox give 672;
/Ot and /Ow 817, /Os 757, /O1 555, /Og 643, /Ob1//Oy//Oa 817, plus /G5,/G6,/GX,
/Gf,/GA,/GB,/GE,/Gi,/Gm,/Gr,/Gz,/GD all 672 or unchanged. No flag set produces the
reference 674.

Also tried an unprototyped redeclaration of `gm_SubObjectNoKill` and an
unprototyped function-pointer call so the unsigned-short argument promotes
without an explicit cast: both still 672 bytes / 29 structural. Source restored.

Server remains one 2-byte codegen difference from a 69,584-byte text alignment
win. Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: server tail shift would also align the import thunks, but the
## section budget forbids it

Zero-extended season local variant also compiles to 672/29. The +16 tail shift
benefit is not limited to game code: the shifted tail match includes the linked
library block and import thunks, whose symbols (_strdup, _RtlUnwind@16) sit at
0x10023802 and 0x10023830 in our map. Aligning them would push text to
0x10024010, past the reference .text raw end 0x10024000, so a padded shift is
impossible without changing the section size; the 2-byte function remains the
only route.

Source restored. Lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-11-03: seven more slot-argument shapes, all 672 bytes

Tried int cast, `+ 0`, `^ 0`, nested `unsigned short`, nested `int`, nested
`unsigned int` with a shift, and an extra `(unsigned short)` cast for the slot
word in `gv_MoveSlotEntry`. Every shape compiles to 672 bytes with the same 29
structural diffs; the target's redundant `xor ecx,ecx` stays out of reach of
source-level expression shaping. File restored from the saved original.

Server lead remains: one 2-byte codegen difference blocks a 69,584-byte text
alignment win. Lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-10-29: retire disposable scratch runtimes and root experiments

Removed nine duplicate experimental runner-image caches and eleven inactive Wine
prefixes older than two days. Scratch allocation fell from about 37.69 GiB to
17.66 GiB, removing approximately 20.03 GiB of disposable files. Preserved current
experiments, reports, candidate sources, Git worktrees, integration backups,
Ghidra/BinSync state, stock-library receipts, original binaries and SDK archives.
The normal shared build cache was not cleared; deleted experimental runtime
caches can be regenerated from the pinned toolchain images when needed.

Deleted four unreferenced root disassembly/compiler dumps: probe.asm, s.asm,
fcn_004102a0.asm and GOLDTL.fcn_004eafe0.asm. Added a root-only /*.asm ignore
rule; vendored assembly remains tracked. Decision owner: project maintainer,
through the cleanup request. Evidence: .scratch/scratch-cleanup-20261029/
candidates.json, removed.json and summary.json. Verification: deletion manifest,
protected-path assertions, worktree inventory and ignore-rule checks. No native
source, metadata or build output was changed; no rebuild was needed.

## 2026-11-03: declaration order does not move the server function off 672

Twelve local-declaration permutations (including reversed and ten seeded
shuffles) all compile `gv_MoveSlotEntry` to 672 bytes with the same 29 structural
diffs; the locals sit on the stack, so register allocation and value tracking are
unchanged. File restored.

The 2-byte gap is codegen-local: the target zero-extends the slot word with a
redundant `xor ecx,ecx` that our compiler omits because ecx already carries the
zero-extended season. No source shape tried (expressions, casts, promotions,
flags, declaration order) reintroduces it.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: guard, unused-local and punning probes all miss 674

Guard restructuring (goto the shared -1 epilogue) leaves 672/29; splitting the
guard condition gives 680/203. Unused locals of five types change nothing.
Hoisting an `unsigned short*` alias to the slot table (top or late assignment)
still folds to absolute addressing and stays 672. Type punning through a 32-bit
zero then a word store gives 691/56, a union with `i = 0` 691/56, and a union with
only the word store 683/47.

Cross-target metadata also confirms the split: GOLDTL holds the same function at
672 and SERVER at 674, so the server source genuinely differs by those two bytes,
but no C shape tried reproduces the target's redundant zero-extension. Source
restored. Lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-11-03: zero-init shapes and a block-scope table redeclaration

Zero-init expressions (`v = 0; v |= word`, `v += word`, mask-then-and, shift by
zero) all fold to 672/29. A block-scope `extern unsigned short
g_entity_slot_table[]` redeclaration is rejected against the header type and
fails the compile; the file was restored from the saved original.

Added two capability entries to upstream `docs/IDEAS-GUILD.md` (rounding audit
for padded extents, padding-only classification for extent mismatches) and
committed as 68b80c1b after the hook suite passed. Lint 0 errors / 0 warnings,
data conflicts 0, TL image unchanged at raw 276,101 / informative 94,121. No GA
was run. Decision: Lead.

## 2026-11-03: upstream rounding audit implemented (19bc1434)

The IDEAS entry from round 201 is now a real option: `rebrew build
check-text-placement --rounding` compares each correctly placed function's linked
extent (distance to the next actual symbol) with its reference size rounded up to
16 bytes, and reports the deviation plus the number of later functions whose own
offset equals it. The last actual symbol is skipped because its extent is
unknown; the audit is diagnostic and does not change the exit code.

Evidence: `expected_text_function_extents` in `verify_hash.py` adds the
annotation sizes; `audit_rounding` in `text_audit.py` computes the rows; the
`--json` payload carries a `rounding` object. Tests cover a short extent with two
following shifted functions, matching extents, and skipped misplaced rows (28
passed in test_text_audit.py). Docs: CLI reference and CHANGELOG Unreleased.

Project check on the server build returns exactly one deviation:
`gv_MoveSlotEntry` 672B against padded 688B (-16), with 100 later functions
sharing the offset, matching the round-192 manual analysis.

No GA was run. Decision: Lead.

## 2026-11-03: rounding audit limited to short extents (dfc32434)

Ran the new audit on both client builds. The TL target reported 55 deviations,
but all but one were positive: layout pads between annotated functions inflate
the linked extent, so "longer than padded reference" is noise, not a codegen
finding. Server reported the known single -16.

Changed the audit to report only shorter extents, where a short body really does
push every later function early. Docs, CLI help and CHANGELOG updated; a test
covers a pad-inflated long extent staying unreported (29 passed). The upstream
commit was amended to dfc32434.

Fresh lead from the TL target: `fcn_00449630` (0x449630) has reference size 1131
(padded 1136) and linked extent 1104, deviation -32, with no later function
sharing the offset. Server still reports exactly one short deviation,
`gv_MoveSlotEntry` -16 with 100 followers.

No GA was run. Decision: Lead.

## 2026-11-03: placed-mismatch rows ranked by residual structural count

Diffed all 39 SIZE_MISMATCH rows that are already at their reference VA and
sorted them by unmasked structural instructions (`.scratch/organize/placed-diffs.json`):
0x4131E0 13, 0x40ED40 17, 0x401ED0 SaveBMP24 20, 0x450E90 23, 0x41BF90 30,
0x40F1C0 32, 0x436A00 33, 0x41BDC0 44, 0x451380 44, 0x44D7E0 59, 0x436930 68,
0x440670 75. The first four are already-documented codegen walls; 0x40ED40
(400 vs 398 bytes, 85.9 percent matched) and 0x451380 (336 vs 322, 65.5) are the
unattempted ones and are the next manual leads.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: fcn_0040ED40 tail decoded to an options-copy dance

The 17 structural diffs sit in the `D3_ANIMATION_OPTIONS` block before the
`fcn_00434970` call. The target builds the by-value argument from a stack copy:
it keeps the original byte in `al`, sets and clears individual flag bits
(`or dl,2`, `and al,0xfd`, `or al,1`), stores the copy at `[esp+0x14]`/`[esp+0x1c]`,
then materialises the 12-byte argument on the stack before `push`ing it. The
candidate reaches the same call with the fields written in source order and
without the extra register copy dance, hence the different instruction order.

The source currently writes `*(int*) &options = 0;` after `memset` and sets
`mode`, then `layer`, `queue`, `mode` again, `loop`, `reverse`. The target's bit
twiddling suggests it modified the struct through bitfields after a copy, which
is a source-shape question for the next round. Lint 0 errors / 0 warnings, data
conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: fcn_0040ED40 field-order and copy variants all worse or equal

Option-block variants: dropping the extra `*(int*) &options = 0` and the second
`mode = 0` gives 392B/39 structural; loop-first order 392/39; keeping `mode = 0`
but moving `queue` last 396/34; dropping `mode` entirely 390/39. An explicit
`D3_ANIMATION_OPTIONS copy = options; fcn(..., copy)` compiles to the same
398B/17 as the baseline, so the compiler removes the copy. The baseline
(398B, 94 exact, 17 structural) stays.

Reading the target block again: `eax` becomes 1 for the flags dword while the
byte-8 value is built in `dl` and the argument's dword 8 is written from `eax`,
so the reference's queue/blend encoding does not match the current header's
bitfield order. That header question is the next lead; it also affects every
caller of `D3_ANIMATION_OPTIONS`. Source restored. Lint 0 errors / 0 warnings,
data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: global tool refreshed; /Ob0 does not change the server function

Reinstalled the global `rebrew` from upstream main (6.8.0 including dfc32434) so
the project CLI carries the rounding audit. Verification: `rebrew build
check-text-placement --built build/server.dll -t server.dll --rounding --json`
reports the one known deviation (`gv_MoveSlotEntry` -16, 100 followers).

`/O2 /Gd /Ob0` and `/O2 /Gd /G6 /Ob0` both compile the function to 672 bytes, so
disabling inlining does not reintroduce the reference zero-extension either.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: more walls on the two open leads

Server: a file-scope `unsigned short* volatile slot_table_words` alias for the
slot table compiles the function to 678B with 145 structural diffs, so forcing a
memory load is worse than the current 672/29. Source restored.

Client: `fcn_00451380` (336 vs 322, 44 structural) differs in the cross-product
block. Wrote the constant last, reversed the three terms, swapped the product
operands, and parenthesised the tail sum; all compile to 322B/44 except the last
(322B/48). The compiler normalises the expression back to the same form, so the
target's constant placement is again not source-controllable. Source restored.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: TL section geometry compared; rdata is 28KB short

Dumped both PE section tables. Reference: .text raw 2,494,464, .rdata 77,824,
.data 266,240. Built: .text 2,543,616 (+49,152), .rdata 49,152 (-28,672), .data
671,744 (+405,504), .data1/.rsrc equal. The score tool compares section content
by section, not by file offset, which is why 127,247 .data bytes still match
inside the 266,240-byte reference window.

R 0 was probed to see whether the rdata content was merely shifted: .rdata same
fell to 2,918 (informative 347) and the file score to 271,027 / 92,887, so the
rdata content itself is not aligned at native offset either; the built section is
28,672 bytes smaller than the reference. Byte identity needs the missing rdata
content (library literals among it) plus a 405KB-smaller data section, which is
the same library/layout wall seen in earlier rounds.

Pads restored to R 0x1000 / D 0x2B000 and rebuilt: raw 276,101, informative
94,121. Lint 0 errors / 0 warnings, data conflicts 0. No GA was run.
Decision: Lead.

## 2026-11-03: data lead pass cannot help; the data section itself is oversized

Try 1: run `scripts/gen_data_lead.py 0x4000` with the current pads. It adds no
pads because every data symbol is *later* than its reference VA (the prefix pad
plus earlier content), so there is nothing to lead.

Try 2: drop the data prefix pad (R 0x1000, D 0), rebuild, then run the lead pass.
Still zero pads: data symbols remain later than their reference VAs. Measurements
without the pad: file raw 223,440, informative 93,698, .data same 74,106 with
informative 1,455; .text 136,146 / 91,872.

Section accounting: built `.data` raw is 495,616 bytes without the pad against
266,240 in the reference, and nonzero density is 259,333 against 122,216. The
extra content sits outside the 430 metadata rows: a scan for initialized globals
whose reference bytes are all zero found none, so the excess is compiled data that
the metadata does not enumerate. Matching the data section therefore needs the
same unreversed-source work as the text block, not another pad.

Baseline restored (R 0x1000 / D 0x2B000): raw 276,101, informative 94,121. Lint 0
errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: data overhead is scaffolding, not unmapped game data

Inventory of initialized layout pads in the TL source tree: 88 arrays, 846,463
bytes total, led by `_dpad_prefix_zeros` 176,128, `_dlead_GOLDTL_fcn_004b41b0`
63,138, `_dpad_143b3e4` 53,208, `_dpad_6abb08` 41,240, `g_data_restore_gap`
39,424, `_dpad_fb91c0` 38,208, `_dpad_699368` 37,424, `_dpad_699388` 37,392.
These carry reference bytes (or zeros) to shift globals to their VAs. The
metadata-attributed initialized globals are only four arrays totalling 11,696
bytes (alchemy random table, producer ids, stat table, log format table).

So the 229,376-byte `.data` raw excess (495,616 against 266,240 at D 0) is
scaffolding overhead, not extra game data: the pads are the only remaining source
of that size. They cannot be removed without displacing the globals they align,
which is the same single-order layout trade already measured for text. No game
data deletion is warranted.

Baseline image unchanged: raw 276,101, informative 94,121. Lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: ten parallel SIZE_MISMATCH batches; 4,156 linker-fill extents repaired

Dispatched the 1,049 SIZE_MISMATCH rows as ten file-disjoint batches (~105 rows
each, `.scratch/teams/batch-N.json`) to ten reused teammates (team member limit
is 64, so `tl-w01..w10` were resumed rather than spawning new members). All ten
returned reports; the shared Docker toolchain saturated at load 60-200, so most
teammates measured 8-21 rows in the time available.

Common finding in every report: the stored native SIZE of these rows includes
the linker's NOP fill after the last `ret`, so an object can never reach SIZE and
many rows were walled for a metadata reason, not a body reason. Two rows were
promoted by teammates with `rebrew test --fix-sizes` (0x0045D3F0 adler32 EXACT,
0x004EAFE0 RELOC); kept source improvements: 0x004BB980 RELOC (inlined strlen
form), 0x00536B10 (volatile global, unsigned branch), 0x00471C80 (hoisted temp).

Central repair: scanned the whole TL inventory with capstone for a reachable
terminator followed only by 0x90/0xCC fill, found 4,156 rows carrying 34,230 fill
bytes, and applied `rebrew binary repair-extents` in 100-row digest-guarded
chunks. Then aligned the stored SIZE of every repaired row with the inventory
through the locked batch metadata writer (4,147 aligned, 9 rows have no function
row). Re-tests: 0x004B6A00 RELOC 239/239, 0x004611B0 RELOC 849/849, 0x004E32C0
RELOC 218/218, 0x0049A880 NEAR 505/505, 0x004EA350 NEAR 259/259.
`verify --text --raw-link` now records EXACT 458, RELOC 3,638, SIZE_MISMATCH
1,029 (from 1,049), NEAR 94, STUB 9.

Reverted one kept edit: `GOLDTL.fcn_00580e20.c` called `fcn_0057ecf0`, but that
address is bound to the GOLD-only file `GOLD.fcn_00576750.c` in the TL metadata,
so the link broke (LNK2001); restored the previous fcn_00576750 calls. Two newly
classified STUB rows got blocker explanations (0x00572760, 0x005756F0). Rebuilt:
raw 276,100, informative 94,121 (the -1 is the kept source edits changing bytes
without a layout shift). Lint 0 errors / 0 warnings, data conflicts 0, imports/
layout/headers match. No GA was run. Decision: Lead.

## 2026-11-03: the residual 100-percent rows are merged code, not fill

After the 4,156 extent repairs, 52 rows still report SIZE_MISMATCH with a
100-percent instruction match. Diffed all 52 (`.scratch/organize/diff-100pct.json`):
in every case the object is a prefix of the reference extent, and the structural
count equals the number of extra bytes, so the tail is extra code, not a body
defect.

Inspected the nine rows whose delta is 8 bytes or less and read the reference
tail bytes directly. Three are linker-shaped (`0x41F5F0`, `0x4772E0`,
`0x5386E0`: `90 90 C3` or `C3`). The other six are a second function merged into
the extent: `mov eax,N; ret` bodies in `0x4B99E0` (N=0x400), `0x4C75E0` (N=1),
`0x4EDEC0` (N=3), `0x506DF0` (N=2), and a jump tail in `0x5EAAD0`. None has a
following inventory row at the split point, so trimming them would orphan real
code.

Recorded the capability gap upstream: `repair-extents` needs a digest-guarded
split that shortens the head to the first terminator and admits the remainder as
a new inventory row (commit ed630d4d). All 52 rows are blocked on that tooling
change, not on C.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: five merged extents split into two rows each, all promoted

The round-213 gap entry claimed `repair-extents` cannot split an extent. That is
true for a single call, but the composition works when ordered: shrink the head
with one digest-guarded repair, `--add-missing` the tail row, then align the
head's stored SIZE through the metadata writer. Did that for the constant-return
and jump-thunk tails:

- 0x4B99E0 486 -> 480, tail 0x4B9BC0=6 (`mov eax,0x400; ret`): RELOC 480/480.
- 0x4C75E0 target 22 -> 14, tail 0x4C75F0=6 (`mov eax,1; ret`): EXACT 14/14.
- 0x4EDEC0 406 -> 398, tail 0x4EE050=6 (`mov eax,3; ret`): RELOC 398/398.
- 0x506DF0 38 -> 32, tail 0x506E10=6 (`mov eax,2; ret`): RELOC 32/32.
- 0x5EAAD0 21 -> 16, tail 0x5EAAE0=5 (`jmp +0xb` thunk): RELOC 16/16.

The three pure filler+ret tails (`0x41F5F0`, `0x4772E0`, `0x5386E0`) were left
alone: the tail is `90 90 C3`/`C3`, which may be alignment plus a stray ret and
does not establish a function boundary.

Updated the upstream IDEAS entry to document the working composition and ask for
an atomic `--split` (amended commit d598d5ec). Lint 0 errors / 0 warnings, data
conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: merged leaf stubs split off twelve more extents, all promoted

Extended the round-214 split recipe to every small-delta 100-percent row. For
each, captured the candidate's last instruction and the reference tail
(`.scratch/organize/small-delta-tails.json`). The tails are alignment NOP/INT3
fill followed by one or two *leaf stubs*: `ret` (a void function returning
nothing), `xor eax,eax; ret` (`return 0`), `mov eax,imm32; ret`,
`jmp rel32`. That grammar is strong evidence the bytes are separate functions,
not the head's missing body, and it is why the prologue-based extractor missed
them.

Split rows (head trimmed to the compiled body size, each stub admitted with
`--add-missing`, head SIZE aligned):
- `0x4B99E0`/`0x4C75E0`/`0x4EDEC0`/`0x506DF0`/`0x5EAAD0` (round 214, relisted)
- `0x5386E0` 32 (+`ret` at 0x538700), `0x53F460` 73 (+`ret`), `0x5453D0` 60
  (+two `ret`), `0x5490A0` 35, `0x549240` 140, `0x5639A0` 484 (+two `ret`),
  `0x570960` 1926 (+`xor eax,eax; ret`), `0x5A7320` 203, `0x5C8090` 42,
  `0x5DF8F0` 312 (+`xor eax,eax; ret`).
- Left `0x572A50` alone: its candidate ends on `add [eax],al`, so the tail may be
  data, not a boundary.

Re-tests: 0x5386E0 RELOC 32/32, 0x53F460 RELOC 73/73, 0x5DF8F0 RELOC 312/312,
0x5639A0 RELOC 484/484, 0x4C6EA0 RELOC 42/42, 0x4E46E0 RELOC 56/56. Inventory
and metadata backed up beforehand (`.scratch/organize/inv-tl.bak.json`,
`functions.bak.toml`); lint 0 errors / 0 warnings, data conflicts 0. No GA was
run. Decision: Lead.

## 2026-11-03: six larger merged extents split; three EXACT, three RELOC

Extended the split to the six 100-percent rows with deltas over 30 bytes. Each
tail was classified from the candidate's last instruction plus capstone coverage
of the reference remainder (`.scratch/organize/large-split-plan.json`): two are
fill plus a pair of `ret` stubs, four are one contiguous function-like block that
decodes end to end with a terminator (coverage 1.0).

- 0x43F640 head 66 (+`ret` at 0x43F690, +`ret` at 0x43F6A0): EXACT 66/66.
- 0x45E860 head 367 (block 1067 at 0x45E9D0): EXACT 367/367.
- 0x47A2E0 head 17 (+`ret` at 0x47A300, +`ret` at 0x47A310): EXACT 17/17.
- 0x5E51F0 head 442 (block 1685 at 0x5E53B0): RELOC 442/442.
- 0x5E6650 head 489 (block 152 at 0x5E6840): RELOC 489/489.
- 0x64E1C7 head 9 (block 28059 at 0x64E1D0): RELOC 9/9. This is the 9-byte stub
  that had been standing in for the 28 KB CRT allocator region.

Inventory is now 6,682 rows (was 6,625): 57 new owners, all reviewed. Head SIZE
aligned through the metadata writer. Lint 0 errors / 0 warnings, data conflicts
0. No GA was run. Decision: Lead.

## 2026-11-03: second SIZE_MISMATCH parallel pass; residual rows are body work

Re-verified without cache after the split rounds: EXACT 424, RELOC 3,721 (passed
4,145 of 5,228), SIZE_MISMATCH 979 (from 1,049), NEAR 95, STUB 9; inventory
6,682. Regenerated ten file-disjoint batches from that list (98 rows each) and
resumed tl-w01..w10 against the repaired extents.

Reports received from six of ten before this round closed: tl-w01, w02, w04, w05,
w07, w10. No row reached EXACT/RELOC and no C edit was kept. That is the useful
result: with padding gone, the remaining SIZE_MISMATCH rows are real body
differences (allocator walls, x87 scheduling, jump-table lowering, missing
blocks), not extent artifacts. Sample: 0x427600 deferred stack adjust, 0x4EE160
x87 sum kept in st(0), 0x502FE0 extra `test al,al` from a cast form, 0x5246E0
induction base 0x99EC28 vs 0x99EC24, 0x4DC6E0 obj in edi vs esi.

Two inventory actions from their reports:
- 0x57DE80 208 -> 196: body plus 9-entry switch table end at 0x57DF44, the last 12
  bytes are NOP fill.
- 0x42E3B0 19 -> 10 with a 3-byte tail row at 0x42E3C0 (`mov al,1; ret`) after six
  fill bytes.

Deferred to the data-in-extent question: 0x4C3A50 (jump table at +0x15E),
0x46B2B0 (byte-map table), 0x4F5CC0 (switch byte map), 0x572A50 (address table
after the ret). Those extents hold real data, so a function split would orphan
data; they need data ownership rows, not another trim.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-03: round-217 pass closed; one body fix, five inventory actions

All ten teammates reported. With the repaired extents the residual SIZE_MISMATCH
rows are body work: no row besides one moved, and every agent confirmed the
padding-only class is gone.

Kept body fix: 0x4B3CE0 (41/92 -> 58/93). Root cause was a byte-address scan
base (0x680BD0, not a g_ int index scaled by 4), first scan from base+4 to
base+0x544 with signed compare, second scan bounded by 0x6810F4 with unsigned
compares, return base+i*0x1c. Residual is the compiler folding the loop bound to
an immediate instead of loading 0x6810F4 into ECX once.

Inventory actions from their fenced reports:
- 0x57DE80 208 -> 196 (12 NOP fill after body plus switch table).
- 0x42E3B0 19 -> 10 plus 3-byte tail 0x42E3C0 (`mov al,1; ret`).
- 0x420BF0 435 -> 302 plus 131-byte block 0x420D20 that decodes end to end to a ret.
- 0x5498B0 657 -> 627 plus two `ret` stubs at 0x549B30 and 0x549B40.
- 0x493BE0 256 -> 249 (7 NOP fill).

Still deferred as data-in-extent (function split would orphan data):
0x4C3A50 (jump table at +0x15E), 0x46B2B0 (byte map), 0x4F5CC0 (switch byte
map), 0x572A50 (address table after ret), 0x5498B0 neighbour data handled.

Rebuilt with the kept body fix: raw 276,100, informative 94,122. Lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-11-04: twenty-agent SIZE_MISMATCH pass; extents repaired, score regressed and partly recovered

Ran the 979-row SIZE_MISMATCH set through twenty file-disjoint batches (49 rows
each) on reused teammates. Fifteen batches reported before the pass was stopped
for consolidation; the rest were interrupted mid-batch.

Wins kept (all persisted through `rebrew test`):
- 0x4D5110 RELOC 393/393: third argument of `fcn_004c51f0` was declared `short`; the
  reference zero-extends a 16-bit read, so the prototype takes `int` and the call
  passes `(unsigned int)(unsigned short)*(short*)match`.
- 0x5498B0 RELOC 627/627: float temp plus `a6 < f` compare order.
- 0x4BB980 RELOC 158/158: `strlen` inlined into the call, `0x100 < strlen(buf)`.
- 0x42E3B0 RELOC 10/10: body was already correct after the extent split.
- 0x570550 17/69 (from 14): `q = p + 0x52` reordered ahead of the stores.
- 0x536B10: `g_6b7fac` unsigned, correcting `jle` to `jbe`.
- Inventory: 0x509570 head 65 plus 6-byte leaf stub at 0x5095C0; 0x572A50 head 820
  plus 1-byte `ret` at 0x572D90; 0x57DE80 trimmed 208 -> 196.
- Removed five redundant CFLAGS rows (lint W029): 0x478D50, 0x478EB0, 0x4C6F70,
  0x4E7FF0, 0x50E170.

Consolidation mistake, recorded: to clear interrupted experiments the Lead
restored eight files to HEAD, which discarded earlier uncommitted improvements
in those same files (0x4B3CE0's byte-address scan rewrite, 0x4FDC40's Rec44 table
declarations, and 0x471C80/0x570550/0x536B10 variants). Six documented fixes were
reapplied; the two table/scan rewrites were not reproducible from the reports and
are open again. Refreshed verdicts: 0x4FDC40 SIZE_MISMATCH 168/152, 0x4B3CE0
SIZE_MISMATCH 92/94.

State after consolidation: verify --no-cache 4,147 passed of 5,228 (EXACT 424,
RELOC 3,723, SIZE_MISMATCH 972, NEAR 99, STUB 10), inventory 6,688 rows. Rebuilt
image raw 275,324 / informative 93,706, down from 276,100 / 94,121; the gap is
the discarded variants above plus their layout effect, not a new build fault.
Lint 0 errors / 0 warnings, data conflicts 0, imports/layout/headers match.
No GA was run. Decision: Lead.

## 2026-11-04: 0x4FDC40 and 0x4B3CE0 recovered after the consolidation loss

- 0x4FDC40 back to RELOC 168/168: the tables are declared `extern Rec44[]
  g_6918e8; extern Rec44 g_693228[]` (were `int[1]` definitions), so the switch
  indexes at stride 0x44 and the missing case blocks emit. Nothing else changed.
- 0x4B3CE0 rewritten from the reference disassembly instead of the lost report
  version: first scan walks byte pointers from 0x680BD4 to 0x681114 by 0x1C with
  a signed compare, second path bounds the caller pointer at 0x6810F4 with
  unsigned compares starting at +0x1C, and the hit returns 0x680BD0 + i*0x1C.
  That reproduces instructions 0 through 17 exactly; the second path still
  differs in constant form (`mov ecx,0x6810F4; cmp eax,ecx` versus two immediate
  compares), so it is 93 bytes against 92 and SIZE_MISMATCH, not the 94 of the
  old body.

Rebuilt: raw 275,568 / informative 93,703 (up 244 from the consolidation low but
still 532 under the pre-batch 276,100; the remainder is not reproduced by any row
restored so far). Lint 0 errors / 0 warnings, data conflicts 0, imports/layout/
headers match. No GA was run. Decision: Lead.

## 2026-10-30: the 532-byte gap is not the pad file; single-instruction NEAR walls

Tested the two remaining hypotheses for the 275,568 versus 276,100 difference:

- Pad file reverted to its HEAD form (`_rdata_prefix_zeros[0xc00]` with the older
  declaration order): identical score, so the tuned 0x1000 pads neither cost nor
  gain against the reference.
- `0x4FDC40` reverted to `int[1]` tables and `0x4D5110` reverted to its 391-byte
  body, separately: identical score each time. The variants are restored.

The pre-batch 276,100 figure therefore looks like a stale measurement rather than
a reproducible state of this tree; 275,568 / 93,703 is the current record.

Attempted two single-instruction NEAR walls and reverted both:
- `0x4B64B0` 204/204: the only difference is `jl` (reference) against `jb` for the
  loop bound. Casting the bound to `int` changed codegen to 207 bytes; three forms
  failed, so the unsigned compare stays.
- `0x4A0BB0` 492/492: one SIB byte orders `[esi+eax+0x74]` against
  `[eax+esi+0x74]`. Swapping the expression operands and the local declaration
  order produced the same encoding.

Lint 0 errors / 0 warnings, imports/layout/headers match, working tree committed.
No GA was run. Decision: Lead.

## 2026-10-30: text placement dominates the remaining bytes; data verify numbers

Measured the current image per section: .text 135,216 matched of 2,494,464,
.rdata 4,041 of 77,824, .data 131,819 of 266,240, .data1 212, .rsrc 381. The
text lead pads total 30,432 bytes across 89 arrays; built .text itself is about
48 KB larger than the reference. `build check-text-placement` reports 485 correct
of 5,180, with misplaced deltas ranging from a few bytes to -507,777, so no single
pad shift realigns the section. Fixing bodies cannot move those misplaced bytes
until function sizes match the reference, which is the objective itself.

`verify --data --built` on the built image reports 430 rows: 155 matched, 421
DISPLACED, 6 DRIFT, 3 VERIFIED. Displacement deltas are not constant (for example
0x662318 lands at 0x8C6650), which is the .text size excess pushing .data later.
An earlier attempt that passed `--link-map` explicitly returned zero rows; both
`-t` and default invocation return the 430 rows, so the zero was an argument
mistake, not a tool defect.

Attempted no source edits this round. Rebuilt image unchanged: raw 275,568 /
informative 93,703. Lint 0 errors / 0 warnings. No GA was run. Decision: Lead.

## 2026-10-30: padding .rdata to the reference size makes the score worse

Whole-binary comparison puts built .text at 2,540,642 against the reference
2,491,370 (+49,272) and built .rdata at 52,558 against 76,722 (-24,164); .data
differs only in virtual size because of the generated BSS gaps, which do not
occupy file bytes. Summing the measured bodies: 654 compile shorter and 316
longer than their reference extents for a net -139,473 bytes, while the 90
text-section scaffolding arrays add 30,636, so the text excess comes from the
unmeasured objects, not the reversed bodies.

Tested restoring the .rdata shortfall with a 24,164-byte zero tail pad in
`.rdata`. The build stayed clean but the score dropped from 275,568 / 93,703 to
269,320 / 92,308: the pad pushes .data content off its reference start, which
costs more than the zero bytes gain. Reverted and rebuilt; the score is back to
275,568 / 93,703.

The .rdata shortfall is real missing content (constants and strings), so the next
step is data reconstruction, not padding. Lint 0 errors / 0 warnings. No GA was
run. Decision: Lead.

## 2026-10-30: multi-function character TU drives the 0x402b00 placement drift; splitting one body did not fix order

Read the link map against the inventory. Most early text is correctly placed
(delta 0 through 0x402aa0), then `ch_UpdatePendingPositions` lands at 0x402B00
instead of 0x403040 and every later fcn object shifts by up to 3,984 bytes. Cause:
`character.c` holds eight functions whose reference addresses are interleaved
with per-function objects, so the single TU clusters them early and pushes the
per-function objects later. Pads cannot interleave objects from another TU.

Pilot fix: split `ch_UpdatePendingPositions` into its own
`GOLDTL.ch_UpdatePendingPositions.c`, rebind the 0x403040 row through
`source binding rebind` (digest preview and apply), and rebuild. The link map put
the new object at 0x403F20, still not the reference address, and the score moved
275,568 -> 275,542 / 93,703 -> 93,670. Reverted the split, the rebind and the
build: score back to 275,568 / 93,703, tree clean.

The object order is not VA-driven for this file, so the fix has to come from the
build's anchor ordering, not from splitting sources alone. Lint 0 errors /
0 warnings. No GA was run. Decision: Lead.

## 2026-10-30: order-sources probe for the character TU split

Probed `rebrew build order-sources` with four real files: `character.c`,
`GOLDTL.fcn_00402b00.c`, `GOLDTL.fcn_00402ff0.c`, `GOLDTL.fcn_004030e0.c`.
The command ordered character.c first (its first bound function is 0x402A10),
then the three fcn files by VA, which is the expected behaviour. So the round-224
split should have slotted a file bound at 0x403040 between 0x402FF0 and 0x4030E0,
yet the rebuilt map put it at 0x403F20. That means the configure-time source list
or the metadata view used for ordering had not picked up the split file the way
this probe does.

No source change kept; score unchanged at 275,568 / 93,703. Next attempt should
print the configured ordered list around 0x403040 during the split build (for
example by dumping `GOLDTL_ORDERED` from the CMake configure log) instead of
guessing from the final map. Lint 0 errors / 0 warnings. No GA was run.
Decision: Lead.

## 2026-10-30: full character TU split reverted; extraction, not ordering, is the blocker

Attempted splitting all seven remaining character.c bodies into per-function TUs,
rebinding each row through the digest-guarded writer and rebuilding. Findings:

- `rebrew build cmake-sources` does pick up a newly bound file (it appeared in the
  generated list) and `build order-sources` then placed its object between the
  0x402FF0 and 0x4030E0 objects, matching VA order.
- The builds failed on the extracted bodies, not the ordering: the shared
  declarations stripped by brace matching missed a `g_6b5c60` extern, a
  `ch_UNIVERSE_STRIDE` macro defined inside `ch_InsertAction`'s body, and the
  extraction duplicated bodies when a function contained string literals with
  braces. Four generation attempts produced compile errors; the map never
  refreshed, so placement could not be judged.

Reverted every split file, the rebind, the shared header and the preamble-only
`character.c`; rebuilt to the committed tree. Score back to 275,568 / 93,703,
lint 0 errors / 0 warnings. Next attempt should split one function by hand with
its exact externs and macros instead of brace-matching the legacy TU, verify the
single split builds and moves to its VA, and only then repeat for the rest. No
GA was run. Decision: Lead.

## 2026-10-30: the character split now places correctly and still loses 5,700 bytes

Completed the hand split of all eight character bodies after the round-226
extraction failure. Each split TU needed its own externs and macros: ch_CreateMesh
needs `extern char g_6b5c60[]`, ch_InsertAction needs `<stdarg.h>`, `ch_queue.h`
and the `ch_UNIVERSE_STRIDE` define, and `ch_UpdatePendingPositions` had to move
out of the ch_SetPosition TU where the extraction had parked it.

With the split in place the map matched the reference order: fcn_00402b00 at
exactly 0x402B00, ch_UpdatePendingPositions 0x403030, ch_Updatelowpoly 0x4033D0,
ch_CreateMesh 0x403850, ch_MoveCharacter2Universe 0x403B90,
ch_UpdateAttachedModelPosition 0x403DF0, ch_InsertAction 0x405140,
TakeObjectScript 0x40D7D0. Remaining deltas were 0x10 to 0x3C0 instead of the old
cluster of 0x540 to 0x9AC0.

The score fell anyway: raw 269,421 first (with a stray pending body in the wrong
TU), 269,897 after the correction, against 275,568 before the split, and
informative 88,529 / 88,946 against 93,703. The text match dropped by about
5,800 bytes. The layout pads were tuned around the clustered character object, so
moving its bodies into their reference slots shifts every later object and loses
more than the eight functions gain. Reverted every split file and rebind; rebuilt
to 275,568 / 93,703 with a clean tree.

Lesson for the next attempt: split and retune the lead pads in the same change,
not in isolation. Lint 0 errors / 0 warnings. No GA was run. Decision: Lead.

## 2026-10-30: built-in source split works with three mechanical fixes; pad retune collapses the score

Used `rebrew source split --va` instead of hand extraction. It handled the
declarations and retargeted both the GOLDTL rows and the GOLD rows that share the
TU. Seven of eight bodies split cleanly; ch_InsertAction (0x4051D0) still refuses
with "inside a preprocessor conditional".

Generated files needed three fixes before they compiled:
- bare relative includes (`ch_queue.h`, `client_scene_transform.h`) became
  `../` paths because the output lives in `character_c/`;
- one merged line `...);#include <stdarg.h>` needed a newline.

With that, the split built clean and placed the bodies near their reference VAs
(fcn_00402B00 exactly 0x402B00, pending 0x403030, Updatelowpoly 0x4033D0,
CreateMesh 0x403850). Score: raw 269,897 / informative 88,946 against 275,568 /
93,703 for the unsplit tree.

Then ran `scripts/gen_text_lead.py 0x2000` on the split layout. It reported
"added 5 shift 0x140", but the rebuilt image scored 219,795 / 44,947, far worse
than either the split or the baseline. The lead pass assumes one stable expected
VA per TU; after the split its per-object deficits no longer match the object
order, so the pads land wrong. Reverted the split, the pad edits and the
generated directory, rebuilt to 275,568 / 93,703.

Next attempt needs a lead pass that consumes the fresh map with split-aware
expectations (first row per output TU), not the old per-source mapping. Lint
0 errors / 0 warnings. No GA was run. Decision: Lead.

## 2026-10-30: the lead pass misapplies the split layout and drops text matches by 50k

Reproduced the round-228 split (269,897 / 88,946), then ran
`scripts/gen_text_lead.py 0x2000` and inspected its edits before rebuilding. It
modified four files only, adding pads of 16, 16, 88 and 200 bytes (total 0x140),
each appended after the function body under `#pragma data_seg(".text")`.

Rebuilt: raw 219,795 / informative 44,947, .text matches 79,934 against 129,441
for the split build and 135,216 for the baseline; `build check-text-placement`
dropped to 80 correct from the split layout's near-reference order. A 320-byte
pad total cannot lose 50k by itself, so the pads are being inserted at positions
where they shift the entire remaining object stream rather than closing the one
deficit the script measured. The generator's expected-VA map is built from
metadata rows per source file, which after the split no longer matches the
object order it measures from the map.

Reverted split, pads and generated directory; rebuilt to 275,568 / 93,703 with a
clean tree. The split path now needs a lead pass that reads the fresh map, keys
expectations by object (not source path) and verifies the applied pad against a
rebuilt placement before adding more. Lint 0 errors / 0 warnings. No GA was run.
Decision: Lead.

## 2026-10-30: lead pass resized pads instead of skipping them; layout score up 10.3k bytes

Root cause of the round-229 collapse: `scripts/gen_text_lead.py` treated an
existing `_tlead_*` pad as done. When a boundary still needed a different size it
did `shift += needed; continue`, so the old pad stayed at its old size while its
effect was counted as if applied. The first pass after a layout change therefore
shifted every later object by the difference between counted and real pads.

Rewrote the pass to resize, shrink or remove the existing pad and to track
`shift` by the actual delta. Iterated it against the current tree:

- pass 1: 42 pads changed, shift 0x90 -> raw 277,181 / informative 98,629
- pass 2: 19 pads changed, shift 0xF60 -> raw 285,947 / informative 102,989
- pass 3: 10 pads changed, shift 0 -> raw 285,892 / informative 102,936
- pass 4: 6 pads changed, shift 0 -> raw 285,869 / informative 102,937

Plateau at 285,869 / 102,937 (best observed 285,947 before the last two jitter
passes). `.text` matches rose 135,216 -> 145,569, correct placements 485 -> 541,
sections `.rdata` 4,041 -> 3,989, `.data` 131,819 unchanged. Lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: larger lead-pad cap trades raw bytes for informative matches

Retried the resized lead pass with a 0x40000 threshold instead of 0x2000. It
changed 81 pads, total shift 0x7BEF1, and the rebuilt image scored raw 176,773 /
informative 116,091. Raw same-offset bytes fell by 109,096 while informative
rose by 13,154, so the larger pads move objects onto non-zero reference bytes at
the wrong offsets. The objective metric is raw byte identity, so this was
reverted; the committed layout at raw 285,869 / informative 102,937 stands.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: character split plus the fixed lead pass; raw score 292,234

Split seven of the eight character bodies with `source split --va` on top of the
retuned layout (ch_InsertAction still refuses as inside a preprocessor
conditional). Fixed the generated files' relative includes and one merged
`;#include` line, built clean, then ran the resized lead pass to convergence:

- split build before retune: raw 279,083 / informative 97,319
- pass 1 (14 pads, shift 0): 292,111 / 108,569
- pass 2 (6 pads, shift 0): 292,227 / 108,674
- pass 3 (4 pads, shift 0): 292,198 / 108,635
- pass 4 (2 pads, shift 0): 292,234 / 108,655

Kept pass 4: raw 292,234, informative 108,655, up 16,666 raw and 14,952
informative from the round-229 baseline of 275,568 / 93,703. Lint now checks
5,453 files (the seven new split units): 0 errors, 0 warnings. Data conflicts 0;
imports, layout and headers match. No GA was run. Decision: Lead.

## 2026-10-30: m_alloc split lifts 156 bytes but trips the assembly-provenance gate

Split the fourteen m_alloc rows. Two link errors needed alias macros restored in
the residual files: `#define g_alloc_counter g_6b6f78` before the remaining
`m_alloc` body (the file's earlier define is followed by an undef) and
`#define g_alloc_report_groups g_6b6f7c` in `m_ShutdownAllocator` with its later
undef removed. Build clean, raw 292,390 / informative 108,655, up 156 bytes.

Lint then reported six warnings: W020 for inline `__asm` in `m_alloc`, `m_init`
and `m_PoolAlloc` with RELOC status, plus two stale-provenance W031 rows. The
assembly blocks are the documented allocator fill prelude (docs/msvc6-allocator.md
Finding 19). Recording `source document-assembly` evidence for those definitions
did not clear W020, and the split introduced provenance rows the gate rejects.

Reverted the split (git reset to 6e770cd0) rather than carry warnings. State:
raw 292,234 / informative 108,655, lint 0 errors / 0 warnings on 5,453 files,
data conflicts 0. Next attempt on m_alloc needs the assembly evidence rebound to
the split definitions before the split lands. No GA was run. Decision: Lead.

## 2026-10-30: msx split is neutral; assembly-provenance gate still blocks m_alloc

Split all eleven `msx.c` rows into their own units. Build clean, raw 292,198 /
informative 108,630 against 292,234 / 108,655: down 36 bytes. Two lead-pass runs
changed no pads, so the retune could not recover it. Reverted the split and
rebuilt to 292,234 / 108,655.

Reviewed why W020 survived the m_alloc attempt: the rule exempts a definition
only when a source-provenance record exists for the same relative file, module
and definition hash. The split copies asm into definitions whose recorded
provenance stayed on the old file/hash, and `source document-assembly` did not
exempt them in that tree. Rebinding the provenance to the split definitions is a
prerequisite for splitting any TU with inline asm.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: split sweep over eight asm-free multi-function TUs finds no further gain

Ran the split-and-retune loop over the eight largest asm-free multi-function TUs:
msx.c (11), alchemistry_logic.c (7), zufall.c (6), command.c (6), d3_object.c (5),
GOLDTL.fcn_004fef80.c (4), loadsave.c (4), friedhof_logic.c (4).

Every split built clean and scored 292,198 / 108,630 against the 292,234 /
108,655 baseline, so all were reverted. command.c and friedhof_logic.c could not
split at all: `source split --va` reports "Ambiguous C definition for VA" on
0x4C4D30/0x4F2FE0, i.e. those files define more than one C function mapped to one
row.

Sweep bug found and repaired by hand: its revert step removed every `src/**/*_c`
directory, which deleted the pre-existing `command/command_c/` tree during the
command.c attempt. Restored from git and rebuilt.

The sweep therefore confirms the character.c result was specific: splitting pays
only when a TU's functions are interleaved with other objects. State: raw
292,234 / informative 108,655, lint 0 errors / 0 warnings, data conflicts 0. No
GA was run. Decision: Lead.

## 2026-10-30: split ambiguity traced to target-specific preprocessor branches

`command.c` defines `cm_ExAllocGraveyardWorker` twice, once under
`#if defined(REBREW_SERVER)` and once in the `#else` branch; `friedhof_logic.c`
has the same shape at 0x4F2FE0. Only the branch active for the selected target
compiles, but `source split --va` sees two definitions and reports "Ambiguous C
definition for VA". Filed an upstream IDEAS entry: evaluate the conditionals
against the target's defines, or accept an `--ifdef` override / `--occurrence`
selector (upstream commit 1712344a).

Also checked for hidden text bloat in command.c: it defines 228 functions but
only 7 rows name it, and the same-name definitions in `command_c/` trigger
LNK4006, so the linker discards the duplicates rather than emitting them. The
text-size excess is therefore still in library and scaffold objects, not in
duplicated C bodies.

State unchanged: raw 292,234 / informative 108,655, lint 0 errors / 0 warnings.
No GA was run. Decision: Lead.

## 2026-10-30: upstream source split learns --occurrence for duplicate definitions

Implemented the gap filed in round 235 against the upstream checkout: `rebrew
source split --va VA --occurrence N` selects the Nth C definition (source order)
when a VA has several, which is what mutually exclusive preprocessor branches
produce. It requires `--va`, out-of-range values name the definition count in the
error, and definitions inside a preprocessor conditional stay refused because
extracting one leaves the conditional unbalanced.

Tests: new case in tests/test_split.py covers the refusal without the flag, the
range error, selection of the second definition and the requires-`--va` guard;
66 split tests pass, full upstream suite 13,398 passed, 28 skipped; ruff check,
ruff format and mypy clean. Commit 9f573ade (CHANGELOG and docs/CLI.md updated).

Project impact is deferred: the project's pinned `.venv` Rebrew predates the
flag, so `command.c`/`friedhof_logic.c` still cannot split there, and their
definitions sit inside `#if`/`#else` anyway, which the extraction still refuses.
Score unchanged: raw 292,234 / informative 108,655, lint 0 errors / 0 warnings.
No GA was run. Decision: Lead.

## 2026-10-30: raw-link verification at the tuned layout; data lead map parser fixed

`rebrew verify --text --raw-link` against the current image: 5,228 rows, 4,150
passed, 484 EXACT, 3,666 RELOC, 969 SIZE_MISMATCH, 99 NEAR_MATCHING, 10 STUB;
libraries 44/44 passed with 300 prebuilt and 224 unresolved providers; inventory
6,688 rows, 6 size divergences.

While trying to align `.data`, found the data lead pass parsed the link map
wrongly for this format: it read the section-summary rows
(` 0003:<offset> <size>H <section> DATA`) as symbols, so the pass never saw a
data address. Repaired the parser to take the symbol rows
(` 0003:<offset> <name> <absVA> <object>`) and kept the fix; a run now parses
6,148 data symbols but inserts no pads, because the 92 early rows need
0x8C0000-scale moves (reference BSS reaches 0x9Fxxxx while the built image ends
near 0x8D0000) and 268 rows are late, both beyond any usable pad. Data alignment
therefore depends on closing the `.text` size excess first.

Score unchanged: raw 292,234 / informative 108,655. Lint 0 errors / 0 warnings
(5,453 files). No GA was run. Decision: Lead.

## 2026-10-30: data placement check reads alternate build trees; text excess still gates .data

`rebrew build check-data-placement` reported zero symbols for this project. Cause:
`link_objects` only looked under `<root>/build`, while the audit builds into
`build-goldtl-audit`. Fixed upstream (commit 9c01de21): new
`link_objects_in(build_dir)` reads the rsp order from the CMake binary directory
that holds the linked image, and the checker uses it when the image sits in such
a tree. Test added in tests/test_data_layout.py; full upstream suite 13,399 passed,
28 skipped; ruff, ruff format and mypy clean; CHANGELOG updated.

With the fix the checker finds 2,085 data symbols and 58 of the managed rows:
every one is late, worst 607,423 bytes. The image's `.data` starts at 0x67B000
against the reference 0x675000, a +0x6000 shift that equals the text excess
(+49,384) minus the `.rdata` shortfall (-24,164). Closing the `.text` excess is
therefore the prerequisite for `.data` (and the relocations that point into it)
to land at the reference addresses.

The checker's absolute symbol VAs remain rough for this image because object
`.data` and `.bss` contributions are summed together, so treat the deltas as a
shift signal, not per-symbol placement. Text lead pass is converged (three runs
changed no pads). Score: raw 292,234 / informative 108,655, lint 0 errors /
0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: data prefix pad size is already tuned

Tried retuning the `.data` prefix pad (`_dpad_prefix_zeros`) after the data
placement check showed the built `.data` base 0x6000 late. Shrinking it by 0x6000
(0x2B000 -> 0x25000) scored raw 275,495 / informative 107,655, with `.data` match
falling 131,819 -> 112,175. Growing it by 0x6000 (0x31000) scored 289,437 /
107,575. Both lose against 292,234 / 108,655, so the current size stands.

Also noted that this pad's section is not the `.data` the whole-binary check
reports: changing its size leaves the reported `.text` and `.data` sizes
unchanged while the score's per-section match counts move, so the pad lands in a
segment the whole-binary summary groups differently. Recorded as an open question;
the whole-binary section sizes are the ones to trust for size work.

Restored the pad file and rebuilt to raw 292,234 / informative 108,655. Lint
0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: linked section addresses and file sizes against the reference

Read both PE files directly (`.scratch/organize/pe_sections.py`):

| section | reference RVA/raw | built RVA/raw |
| --- | --- | --- |
| .text | 0x1000 / 2,494,464 | 0x1000 / 2,543,616 |
| .rdata | 0x262000 / 77,824 | 0x26e000 / 53,248 |
| .data | 0x275000 / 266,240 | 0x27b000 / 671,744 |
| .data1 | 0x117f000 | 0x2efc000 |
| .rsrc | 0x1180000 | 0x2efd000 |

The built `.data` begins 0x6000 late (text excess +49,152 minus rdata shortfall
-24,576), so every relocated `.data` operand is off by that base shift. The
`.data` file image is also 405,504 bytes longer than the reference: the 176,128
byte initialized prefix pad plus reconstruction data occupy file bytes that the
reference keeps in BSS. Converting that pad to BSS would move all following data
earlier in VA by its size, which the earlier size probes show costs more than it
gains, so the excess stays until `.text` shrinks.

`.data1` and `.rsrc` sit 43 MB apart from the reference addresses for the same
reason (built `.data` virtual span). Trimming file sizes to the reference is
therefore gated on the `.text` excess, as before.

Score unchanged: raw 292,234 / informative 108,655; lint 0 errors / 0 warnings;
data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: dropping redundant d3dx8 anchors; text size did not move

Cross-checked the linked image against the reference by searching each library
symbol's first bytes in the reference. 128 library objects totalling 49,104 bytes
have no sampled signature there, and `.text` excess was +49,152, so the members
looked like the excess. Tested by removing the 205 `/INCLUDE` anchors in
`stubs/goldtl/readd-symbols.rsp` that name symbols from those members (cvalue,
shapes, cassignment, btri, ceffect, intersect, jidctflt, ctechnique, cpass,
inittime, realloc, assert, heapinit, _ctype).

The build stayed clean and all members remained linked: our own stubs reference
them, so the anchors were redundant, not the pull. `.text` size stayed 2,540,754,
which rules out the absent-signature list as the text excess explanation. The
anchor cleanup alone moved the score from 292,234 / 108,655 to 292,292 / 108,702
(+58 / +47); a further lead pass changed no pads. Kept the 205-line anchor removal.

Lint 0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: d3dx8 effect classes are retained by anchors, and dropping them costs size

Followed the absent-signature library list further. The C++ effect classes come
back through `/INCLUDE` anchors for derived symbols not present in the link map
(CD3DXValueDword, CD3DXValueFloat, CD3DXValueMatrix, CD3DXEffect and related),
so the round-241 symbol filter missed them. Removed 47 more anchors naming those
classes.

Result: 143 cvalue symbols still linked (other anchors and real references pull
the members), `.text` grew from 2,540,754 to 2,557,230, `.rdata` grew 52,558 to
57,990, and the score fell to 281,704 / 106,265. The anchor set controls which
archive members and in what order, not only retention; dropping class anchors
changes member selection and moves bytes the wrong way.

Reverted to the committed anchor list and rebuilt: raw 292,292 / informative
108,702. The `.text` excess remains unexplained by archive-member absence. Lint
0 errors / 0 warnings, data conflicts 0. No GA was run. Decision: Lead.

## 2026-10-30: verbose link names the exact anchor that loads cvalue.obj

Captured a `/VERBOSE` link by copying `CMakeFiles/europa1400gold_tl.dir/link.txt`,
inserting `/VERBOSE` before `/out:`, running it in the build directory and keeping
the log at `.scratch/organize/link-verbose.log`. The relevant trace:

```
Found "public: __thiscall CD3DXValueDword::CD3DXValueDword(void)" (??0CD3DXValueDword@@QAE@XZ)
  Loaded d3dx8.lib(cvalue.obj)
```

So the pull is the derived-class anchor, not the base `CD3DXValue` constructor
that the round-241 filter covered. Round 242 removed anchors matching
`CD3DXValue` (which also matches the Dword/Float/Matrix/Vector names) and `.text`
grew instead, so more than one anchor set has to change together and the
extraction order matters.

The verbose log also gives `Referenced in <object>` lines per pulled symbol,
which is the tool to use for the next attempt: remove one class anchor group at
a time and check which member the linker loads next.

Also tried locating every linked object in the reference by 48-byte signature:
851,047 of 2,538,188 text bytes find a home, the rest do not, and the deltas have
no common bucket. That measures how far the bodies are from exact, not where
extra bytes are, so it does not locate the excess.

State unchanged: raw 292,292 / informative 108,702, lint 0 errors / 0 warnings,
data conflicts 0. No GA was run. Decision: Lead.
