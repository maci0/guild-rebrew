# Current work

## Read-only snapshot, 2026-11-13

These are stored verdicts and earlier image checks, not fresh builds of the
working tree. Rerun the commands in [Choose work](#choose-work-from-canonical-inputs)
before selecting a task or reporting new progress.

| Target | EXACT + RELOC / game functions | C matches | Accounted `.text` |
| --- | ---: | ---: | ---: |
| GoldTL | 4,199 / 5,188 | 4,199 | 56.3% |
| Gold | 2,056 / 4,428 | 2,054 | 23.0% |
| server.dll | 251 / 251 | 251 | 100.0% |

Inventory totals include functions without source; the source-bound status
counts below cover a subset. Gold's two naked matches are excluded from C
recovery. The status read was
`rebrew status --all-targets --json`.

| Target | NEAR_MATCHING | SIZE_MISMATCH | STUB | Without verdict |
| --- | ---: | ---: | ---: | ---: |
| GoldTL | 116 | 813 | 38 | 0 |
| Gold | 12 | 40 | 72 | 140 |
| server.dll | 0 | 0 | 0 | 0 |

The second table counts source-bound FUNCTION rows, measured on 2026-11-13 by
`.venv/bin/python .scratch/review/docs-todo/measure-counts-2.py`.
Gold rows without a verdict are separate from STUB; `rebrew status` counts them as STUB. That scratch script is a
local receipt, not a required project tool.

All-target lint passed on 2026-11-13: 5,538 files per target, zero errors and
warnings (`.venv/bin/rebrew lint --all-targets`, exit 0).
[Release 1.12.0](releases/1.12.0.md#validation) records the last full release
validation on November 13: 316 server function checks (251 game, 65 library),
652 data checks, Wine load and exports passed; the raw server matched all
286,720 reference bytes. Both clients relinked with placeholder stubs and still
differ from their references in file bytes, sections and resources.

Configured images under `build/` and `build/consolidation-baseline-pp/` may
predate current sources. Rebuild before claiming a new image result; see the
[server](build.md) and [client](../stubs/README.md) guides.
[Provenance](provenance.md) retains individual changes and measurements.

## Open work

The November 12 default-target TODO read ranked displaced `g_869480` and `g_90e0a0` first.
Check their linked placement and native ownership as part of the provider work
below. The first code actions are `fcn_005ba910` (SIZE_MISMATCH),
`fcn_004dcf50` (STUB) and `io_AppendText` (STUB). Review their stored blockers
before another source-shape experiment. Naming and consolidation are separate
review work, not the top-ranked recovery actions.

Measured: 2026-11-12, `.venv/bin/rebrew todo --json` (GoldTL, the configured
default). The read reports 409 data-drift actions, 1,003 improve-match actions,
13 fix-delta actions, two start-function actions, eight start-data actions,
one run-prover action and 3,726 exact-only actions. These are action categories,
not status counts. Raw-link verification records linked EXACT only when its
requirements are met.

1. Replace client placeholder stubs with evidenced function providers or data
   owners. `CMakeLists.txt` still includes `symbol_stubs_extra.c` for both
   clients and the Gold `symbol_stubs_adopted*.c` files.
   See the [client guide](../stubs/README.md#placeholder-stubs) for the selected files. Placeholder
   definitions establish neither ABI nor storage ownership. The November 8
   extent review found interior vector views at `g_773e18` and `g_773e1c`, and
   a string conflict at `g_6a42f8`/`g_6a42fc`; those names still have no data
   rows. Establish complete extents and backing objects before adding storage.
   Rebuild clients and repeat placement, data, imports and whole-file checks
   after provider changes. Run promoting verification only while sources are stable.
2. Review remaining shared-source candidates. Earlier regressions involved
   `gm_SubObjekt`, `gm_AllocBuildingDefaults`, `cm_ExProdObjekt`,
   `gm_ResolveEntityRecord`, `gm_AssignBuildingOwner` and `gm_ResolveEntitySlot`;
   their original failed comparisons are in provenance. `gm_ff_Objekt` was
   not completed. Recheck current bindings and whole-TU results before retrying.
   Preserve the server after shared declaration, type or body changes.
3. Review seven remaining zlib identities that still bind to loose game files:
   `deflate_fast` (0x0045e520), `deflateCopy` (0x0045dfd0),
   `inflate_blocks` (0x0045fd70), `inflate` (0x004616e0),
   `inflate_set_dictionary` (0x00460a00), `zError` (0x00465800) and
   `zcfree` (0x00465840). The November 8 compiled-vendored-object comparison
   identified these bodies, but the source binder then refused their definitions.
   The later parser fix enabled `inflate_blocks_sync_point` (0x00460a40),
   now LIBRARY and EXACT on `references/zlib/infblock.c`. Do not assume the
   other binding failures persist without a new preview. `fcn_00401000`
   (52 bytes) had no vendored zlib match in that sweep. Library bodies do not
   count as game recovery.

   Measured: 2026-11-12,
   `.venv/bin/python .scratch/review/docs-todo/measure-counts-2.py` confirms
   seven remaining FUNCTION bindings. The earlier byte-identity sweep and
   parser repair are recorded in [provenance](provenance.md).
4. Continue evidence-based naming and file renames. There are 5,029 paths
   matching `*fcn_*.c` under `src/`; that filename count does not establish
   whether literal evidence exists. Of files bound in the function store,
   137 existing address-named C files have at least one non-`fcn_` row name.
   Review identity, shared declarations and data rows before renaming.

   Measured: 2026-11-12,
   `.venv/bin/python .scratch/review/docs-todo/measure-counts-2.py`.
5. Recover remaining C bodies and review the unresolved source questions in
   [HANDOFF.md](HANDOFF.md). The status snapshot has 102 GoldTL NEAR_MATCHING
   functions. Earlier operand-order and declaration-order sweeps did not close
   all candidates. Use current diffs before repeating an old experiment.

   Measured: 2026-11-12, `.venv/bin/rebrew todo --json`,
   `coverage.statuses.NEAR_MATCHING`.

## Matching leads

These leads were open at the snapshot above. Check current bindings and verdicts
before retrying. Scores below describe earlier experiments, not fresh tests.
`.scratch/` candidates are local evidence; older receipts may be under `../guild-rebrew-archive/2026-11-05/scratch/`.

- `fcn_00499950` (250 bytes, stored NEAR_MATCHING): the named-float candidate
  `.scratch/fcn_00499950.named-reloc.c` measured RELOC 250 of 250. Its eight
  float addresses, 0x01009354 to 0x0100938c at stride 8, still have no data
  rows. Establish the table's extent and owner before adopting the candidate.
- `fcn_00495180` (625 bytes, stored NEAR_MATCHING):
  `.scratch/fcn_00495180.redundant-reloc.c` measured RELOC with a redundant
  zero check. The kept source uses the single rate check. Its earlier score
  was 623 of 625: `test eax, eax` instead of the reference's `cmp eax, esi`.
  Find a faithful form that reuses the zero register.
- `fcn_00418210` (904 bytes, stored NEAR_MATCHING): the 880-of-904 form landed
  on November 11. Two of the 17 structural differences were swapped loads
  of `obj+0xdc` and `[esp+0x1f]`; the other 15 were stack slots. The reference
  reuses the dead `obj` argument slot for `len`, conversion temporaries and
  `alive`. Declaration reordering and block-scoping `len`/`half` did not help.
- Compilation-context questions: 0x004cefb0 (70 bytes) and 0x004cf000
  (102 bytes) remain SIZE_MISMATCH; earlier builds kept float locals on the
  FPU stack where the reference spilled them. 0x004da170 (28 bytes) and
  0x005d0460 (81 bytes) remain SIZE_MISMATCH; earlier builds tail-jumped both
  branches where the reference used one call and one tail jump. Check native
  TU neighbours before changing flags, and apply evidenced flags to the whole TU.
- SIB base/index order: 0x00446540 (1,165 of 1,172),
  `ai_StartBerufsausbildung` at 0x004a0bb0 (491 of 492), and 0x0041bf90
  (503 of 510) remain NEAR_MATCHING. Earlier operand swaps, integer pointer
  arithmetic and byte-pointer bases did not reproduce the reference register
  order. Diagnose the current compiled operands before another rewrite.

## Choose work from canonical inputs

```sh
uv run rebrew todo --target Europa1400Gold_TL.exe --json
uv run rebrew source findings 0x00499950 --json
uv run rebrew lint --all-targets --json
```

Replace the example VA with the selected function address.
[goal.md](../goal.md) defines completion. [AGENTS.md](../AGENTS.md) owns project
rules.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
