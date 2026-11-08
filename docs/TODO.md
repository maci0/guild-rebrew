# Current work

## Working checkpoint, 2026-11-08

State of the tree after the translation-unit consolidation and naming rounds. Both client
comparison scaffolds link (below); no byte-level image comparison was run, so the byte results here are per-function.

- Status snapshot (`rebrew status --all-targets --json`, graphics regenerated): GoldTL
  4,124 of 5,194 C functions matched and 54.1% code accounted (28 stock zlib functions moved
  to library, seven operand-order fixes below); Gold 1,968 of 4,421 (51 twin adoptions below); the server unchanged at 251 of 251.
- 123 loose `fcn_<VA>` functions were renamed from literal evidence (script
  registrations, AI method registrations, tag strings with twin names). Each row is in
  [name-ledger.tsv](name-ledger.tsv); the method is in [naming conventions](naming_conventions.md).
  Names that rest on a position or an allocation tag alone were held out.
- Three merged units (`main.c`, `aemter.c`, `d2_windows.c`) were split back to one file
  per function because the literal-pool string evidence did not support them as native
  units. Every row kept its status. See [source layout](source-layout.md).
- Six loose duplicates are bound to their shared definitions: `gm_RemoveObjectByType`,
  `gm_RemoveLinkedNodeById`, `gm_FindKind47ByOwner`, and, after guarding the server-only
  log call with `#if defined(REBREW_SERVER)` in `spiel.c`, `gm_SumSlotTreasury`,
  `gm_SumTreasury` and `gm_SubObjectNoKill`. Every row of `spiel.c` compared equal on all
  three targets before and after each guard. Six other pairs still regress because the
  shared body differs from the TL body beyond log calls: `gm_SubObjekt` (a guard was tried
  and reverted), `gm_AllocBuildingDefaults` (different loop shapes), `cm_ExProdObjekt`
  (different function entry), `gm_ResolveEntityRecord`, `gm_AssignBuildingOwner`,
  `gm_ResolveEntitySlot`. `gm_ff_Objekt` (310 callers) and three pairs that failed the
  preview were not retried.
- `rebrew lint --json` reports 0 errors. Seven GoldTL functions recorded as RELOC on 2026-11-02 had
  tested as NEAR_MATCHING (`0x00452360`, `0x00474780`, `0x004e4b60`, `0x00526db0`, `0x00537080`,
  `0x005e3c40`, `0x00451150`). Each differed from the original only in operand order, shown by
  swapped relocation targets in `relocation_bindings`: commutative operands (`a * b`, `a + b`), a
  chained assignment (`a = b = f()`), two adjacent statements, and a 16-byte `Rect` copy that the
  original wrote field by field (right, left, top, bottom). They are RELOC again after those source
  edits; the underlying cause of the earlier change is not established.

Open, in order:

1. Link: both client scaffolds build and link on 2026-11-08 (`europa1400gold_tl` 3.0 MB,
   `europa1400gold` 0.7 MB, relinked on 2026-11-09 after the twin adoptions) with generated placeholder stubs, which prove nothing about ABI or
   storage ownership. GoldTL had 51 unresolved externals before the stubs and Gold had 184;
   they are now defined in `stubs/goldtl/symbol_stubs_extra.c` and `stubs/gold/symbol_stubs_extra.c`
   (`rebrew build symbol-stubs`, one special for `fcn_00401260`). One real fix: the Gold file
   `GOLD.fcn_005af320.c` called `fcn_0046b2b0` (the TL spelling) where the native calls target
   `fcn_0046e700`; five relocations that were UNRESOLVED now bind to it. What the stubs stand in
   for is still open: 40 TL data externals need storage rows (extent evidence for 25 shows
   interior views, a conflict with a string at 0x6a42f8 and 14 with no established size, so no
   row came from the plan's 4-byte `int` default), 49 proposed global names have no store row,
   and 124 Gold externals need Gold definitions (a Gold adopt was refused because the Gold bytes
   differ from the TL function at the same address). Placeholder bindings done by hand for
   `fcn_00402a00`, `fcn_00442be0`, `fcn_004e6bd0` and `fcn_00504e70`. The upstream tool gaps are
   written in its `docs/IDEAS-GUILD.md` (2026-11-08 entries, committed locally in that checkout as `5d4ca98a`, not pushed; that checkout is ahead 1 and behind 1 on origin).
2. Next step for the link: replace stubs with recovered code or reviewed data rows, then compare
   the images with `rebrew verify --whole-binary --built` (see [client builds](../stubs/README.md)).
3. Stock zlib code is attributed as library, not renamed as game code: 22 zlib rows were already
   `LIBRARY` rows, and 28 loose zlib functions (plus seven Gold twin rows) were retired and bound to the vendored sources
   with `rebrew library bind-source` (2026-11-08; each vendored row matches the original bytes).
   Matching each loose function's bytes against the compiled vendored sections (relocations and `call`
   operands masked, names from the COFF symbol table) identified all but one of the nine that stayed
   loose, and showed several earlier guesses were wrong: `fcn_0045e180` is `lm_init`, `fcn_0045e520` is
   `deflate_fast`, `fcn_00461ba0` is `inflateSync` and `fcn_00461c70` is `inflateSyncPoint`. `lm_init`,
   `inflateSync`, `inflateSyncPoint`, and from a sweep of all loose GoldTL functions against every compiled
   vendored object (`gzputs`, `inflateInit_`) are now library rows. `deflate_fast` (0x0045e520), `deflateCopy`
   (0x0045dfd0), `inflate_blocks` (0x0045fd70), `inflate` (0x004616e0), `inflate_blocks_sync_point`
   (0x00460a40), `inflate_set_dictionary` (0x00460a00), `zError` (0x00465800) and `zcfree` (0x00465840) match the vendored bytes, but `rebrew library bind-source` refuses their definitions
   ("one complete definition with matching C symbol"), so they stay loose. `fcn_00401000` (52 bytes)
   matches nothing in the vendored zlib objects. The 12 d3dx8 matches were already `LIBRARY` rows.
   Library functions do not count as reversing progress.
4. 133 of the 164 files named `fcn_<VA>.c` that define a real name were renamed to
   `MODULE.name.c`. The other 30 were skipped: 19 previews include a data row, 6 failed the
   preview, 4 touch more than 60 files and 1 failed its before-test.
- `rebrew orphans prune` (2026-11-09) deleted 859 orphaned rows (855 DISPLACED data rows, 2 STUB
  function rows, 2 empty-status data rows) and held back 489 earned rows (484 GOLDTL function rows
  with retired-claim history, 5 VERIFIED data rows). Function verdicts, lint and the canary did not
  change; the GoldTL data section went from 1,270 to 417 rows.
- GA batches on 2026-11-09 (`--improve` three times, `--size-mismatch` once, 100 functions) matched one, `fcn_004763e0`. The rest need hand diagnosis from `rebrew diff`; see provenance for the two that were tried by hand and did not close (`fcn_0048ddd0`, `fcn_004b64b0`, `fcn_00495180`).
5. About 5,000 loose `fcn_*.c` files have no literal evidence for a name.
   Matching: 112 GoldTL functions remain NEAR_MATCHING. A 2026-11-08 round tried the 89 with 48 or fewer
   differing bytes (reorder commutative operands, independent statements, equivalent rewrites; tests
   with `--no-promote` only). None reached a full match; three gained 1 to 4 bytes only by changing
   behaviour (swapped constants or call arguments, an extra assignment) and were rejected. What is left
   is mostly register allocation, jump direction and instruction order, which need a different
   source shape, not operand swaps. Details: `.scratch/consolidation-2026-11-05/slot-2/match/`.
6. The compiler image `rebrew/msvc:6.0-sp5-pp-win32` disappeared from Docker on 2026-11-08
   (cause not established; a `docker builder prune` from another session was seen
   running afterwards) and was rebuilt with
   `rebrew toolchain build msvc-6.0-sp5-pp` (and `msvc-6.0-sp5` and `msvc-6.0-sp5-crt`, which the
   server target needs) using the local recipes checkout
   (`REBREW_TOOLCHAINS_DIR`, see [build.md](build.md#prepare-compiler-images)). A pull is not
   possible: rebrew images are built from pinned sources, not published.

## Verified checkpoint, 2026-11-05

[Release 1.10.0](releases/1.10.0.md) records the last full binary validation. Its server build
matches the complete 286,720-byte reference: 316 function checks, 652 data checks,
structural checks and Wine load/export resolution passed.

The full gate still fails on five lint warnings and 28 GoldTL D3DX library-screening
findings. Both clients remain incomplete. The release compiled all 123 changed C
translation units, but did not establish a new complete client image or gameplay
result. Older client link counts and image scores are historical.

Build trees and caches were cleared after validation. Local receipts and preserved
images are outside the checkout at `../guild-rebrew-archive/2026-11-05/`. Historical
`.scratch/` paths resolve under that archive's `scratch/` directory. Rebuild before
claiming a current image result. [Build instructions](build.md) and
[client instructions](../stubs/README.md) describe how.

## Next actions

1. Review the five lint warnings: three STUB rows lack blocker explanations,
   `amt.office_slot:SERVER` has stale type evidence, and generated instructions
   differ from the installed template. Rebind or refresh only after review.
2. Resolve the 28 D3DX screening findings with complete native/operand/provider
   evidence. Do not count library bodies as game recovery or suppress the gate.
3. Review the unresolved source questions in the [handoff](HANDOFF.md). Recheck
   current source before adopting a candidate.
4. Rebuild each client and record fresh link, placement, data and whole-file checks.
   Repair actual provider/ownership failures before interpreting layout scores.
5. Recover remaining C bodies and reconcile shared declarations/types across all
   targets. Preserve the server after each shared change.

The November 5 cleanup stopped the reconstruction fleet and removed its heartbeat.
Its reservations are closed.

## Choose work from canonical inputs

```sh
uv run rebrew todo --target Europa1400Gold_TL.exe --json
uv run rebrew source findings 0x<VA> --json
uv run rebrew lint --all-targets --json
```

[goal.md](../goal.md) defines completion. [AGENTS.md](../AGENTS.md) owns project
rules. [Goal history](goal-history.md) locates older checkpoints and notebooks.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

Original notebook: `docs/TODO.md` in the [documentation archive](goal-history.md#full-notebooks).

| Historical section | Referenced hex values |
| --- | --- |
| <a id="working-checkpoint-update-2026-11-01-1515-utc"></a>Working checkpoint update (2026-11-01 15:15 UTC) | `0x0050e170` |
| <a id="working-checkpoint-2026-11-01"></a>Working checkpoint (2026-11-01) | - |
| <a id="source-and-provider-changes"></a>Source and provider changes | `0x00402b80`, `0x0040ed40`, `0x0040f1c0`, `0x0040fb80`, `0x004124b0`, `0x004127a0`, `0x004131e0`, `0x00413d10`, `0x0041b510`, `0x00420bf0`, `0x00420d20`, `0x00420db0`, `0x00427280`, `0x00436a00`, `0x00437bc0`, `0x00440670`, `0x00441400`, `0x00445ec0`, `0x0044c6f0`, `0x0044d7e0`, `0x00450e90`, `0x0045bfb0`, `0x00465c60`, `0x00471e30`, `0x00472680`, `0x00473610`, `0x004763e0`, `0x00479660`, `0x0047c1f0`, `0x0048ddd0`, `0x0048eba0`, `0x0048f4f0`, `0x004903c0`, `0x00490c10`, `0x00491570`, `0x00491680`, `0x004918a0`, `0x00493be0`, `0x00495180`, `0x00499950`, `0x0049a880`, `0x004a0bb0`, `0x004a70c0`, `0x004b64b0`, `0x004c3800`, `0x004c39c0`, `0x004c6090`, `0x004c6940`, `0x004c6e20`, `0x004c75f0`, `0x004c7c50`, `0x004cd090`, `0x004ce210`, `0x004d3c60`, `0x004dc3a0`, `0x004e3020`, `0x004e7340`, `0x004ea350`, `0x004ee290`, `0x004eea30`, `0x004f0a30`, `0x004f2ee0`, `0x004f4440`, `0x004f88d0`, `0x00502450`, `0x005024e0`, `0x00503e80`, `0x00506ab0`, `0x00507130`, `0x00509120`, `0x00509570`, `0x0050b840`, `0x0050dfd0`, `0x0050e170`, `0x00513d40`, `0x00524fc0`, `0x00536b10`, `0x0053fa80`, `0x005435e0`, `0x005448e0`, `0x00545780`, `0x005473a0`, `0x0055a0b0`, `0x00565ab0`, `0x00571140`, `0x0057a3d0`, `0x0057c7b0`, `0x0057d0d0`, `0x0057de80`, `0x0057e880`, `0x0057f9a0`, `0x00580e20`, `0x005816f0`, `0x00589d00`, `0x0058bfd0`, `0x0058e220`, `0x00593360`, `0x0059dcf0`, `0x005aa480`, `0x005aceb0`, `0x005b44b0`, `0x005bf9e0`, `0x005ce800`, `0x005de9a0`, `0x005e53b0`, `0x005e6840`, `0x00605233`, `0x00613478`, `0x0067bbdc`, `0x0067bbe0`, `0x0068bfb8`, `0x006b5c84`, `0x0077492c`, `0x01007ce0` |
| <a id="tooling-and-validation"></a>Tooling and validation | `0x004bd1e0`, `0x0057a3d0`, `0x00605233`, `0x0064d399` |
| Next actions | `0x00420db0`, `0x0048ddd0`, `0x004903c0`, `0x00495180`, `0x004cd090`, `0x005024e0`, `0x0057a3d0`, `0x00593360`, `0x005e53b0` |
| <a id="historical-work-records"></a><a id="status-snapshot-2026-10-21-1202-utc"></a>Historical work records | - |
| <a id="status-snapshot-2026-10-24-session-round-7"></a>Status snapshot (2026-10-24 session round 7) | `0x00414fb0`, `0x0041bb70`, `0x0041ebca`, `0x00479330`, `0x0047a320`, `0x004bfe00`, `0x004c9e20`, `0x004f0f60`, `0x004f18d0`, `0x0050e170`, `0x005294c4`, `0x0052f7b0`, `0x00532ef0`, `0x005d3d90`, `0x005d6c50`, `0x005d6ea0`, `0x0060ff98`, `0x0062a1ee`, `0x0064d228`, `0x0064d3f8`, `0x0064d41a`, `0x00650000`, `0x00660075` |
| <a id="status-snapshot-2026-10-24-session-round-6"></a><a id="live-state-2026-10-22-round-107"></a>Status snapshot (2026-10-24 session round 6) | `0x0040d9a0`, `0x00479330`, `0x004bfe00`, `0x004f0f60`, `0x0052f7b0`, `0x00532ef0`, `0x0064d228`, `0x0064d3f8`, `0x0064d41a` |
| <a id="historical-state-2026-10-22-round-107"></a>Historical state (2026-10-22, round 107) | `0x004012b0`, `0x00401380`, `0x00402540`, `0x00402ab0`, `0x00402d00`, `0x00403ab0`, `0x00404c20`, `0x00405610`, `0x00406560`, `0x00407390`, `0x004076b0`, `0x00408320`, `0x0040cda0`, `0x0040d8d0`, `0x0040eac0`, `0x0040ed40`, `0x0040f9d0`, `0x0040fb80`, `0x00411b00`, `0x00411c10`, `0x00412b10`, `0x00412f10`, `0x00413030`, `0x00413480`, `0x00413e00`, `0x00415150`, `0x00415510`, `0x00417710`, `0x00417840`, `0x00418e90`, `0x0041a25c`, `0x0041a8c3`, `0x0041a8d0`, `0x0041e050`, `0x0041e0a0`, `0x0041e670`, `0x0041ebca`, `0x004207c0`, `0x00423670`, `0x004284d0`, `0x00429670`, `0x00429e90`, `0x0042ada0`, `0x0042b410`, `0x0042bd30`, `0x0042bd5f`, `0x0042bd60`, `0x0042bd8f`, `0x0042ee50`, `0x0042f620`, `0x00435810`, `0x00435870`, `0x00436070`, `0x00437060`, `0x0043a720`, `0x0043b600`, `0x0043b6e0`, `0x0043bb70`, `0x0043d7c0`, `0x0043deb0`, `0x0043e090`, `0x0043e180`, `0x0043e1b0`, `0x00440280`, `0x00441ab0`, `0x00441ea0`, `0x00442210`, `0x004488e0`, `0x00449630`, `0x0044964d`, `0x0044b340`, `0x0044f010`, `0x0044f760`, `0x0044f7e0`, `0x004506e0`, `0x00454460`, `0x004556d0`, `0x00455d30`, `0x0045c380`, `0x0045c554`, `0x0045cd50`, `0x0045f640`, `0x0045fb40`, `0x0045fd70`, `0x00461690`, `0x004616c0`, `0x00463740`, `0x00465e60`, `0x004675e0`, `0x00467790`, `0x00468c60`, `0x0046cfc0`, `0x0046e980`, `0x004734c0`, `0x00473610`, `0x00474e5d`, `0x00475840`, `0x00476ef0`, `0x00478bc0`, `0x0047c3c0`, `0x0047cda0`, `0x0047ce20`, `0x0047ce50`, `0x00490b80`, `0x00494740`, `0x00496060`, `0x00496480`, `0x0049ab50`, `0x0049b110`, `0x0049ee20`, `0x0049f5c0`, `0x0049fb80`, `0x004a0bb0`, `0x004a16f0`, `0x004a5340`, `0x004a8f20`, `0x004ab2c0`, `0x004ab3e0`, `0x004ad0a0`, `0x004ad1c0`, `0x004b64b0`, `0x004bc640`, `0x004bcc20`, `0x004c3800`, `0x004c38eb`, `0x004c4268`, `0x004c70fa`, `0x004cb5d0`, `0x004ccf10`, `0x004cd4c0`, `0x004cd5e0`, `0x004cda90`, `0x004cdb10`, `0x004cdb90`, `0x004ce040`, `0x004ce200`, `0x004cf000`, `0x004d0963`, `0x004d099d`, `0x004d16da`, `0x004d7000`, `0x004d7f70`, `0x004d8e20`, `0x004dada0`, `0x004dae90`, `0x004e5770`, `0x004e6d80`, `0x004e6e20`, `0x004eaea0`, `0x004eb180`, `0x004ece60`, `0x004f0430`, `0x004f0f60`, `0x004f2540`, `0x004f3700`, `0x004f3780`, `0x004f8730`, `0x004f8800`, `0x004f9300`, `0x004fdcf0`, `0x00501190`, `0x00509570`, `0x0050c550`, `0x0050f910`, `0x00510b40`, `0x00511630`, `0x005117c0`, `0x0051463d`, `0x00519a30`, `0x0051c8a0`, `0x00520f50`, `0x00526660`, `0x0052668b`, `0x00526b37`, `0x005283d0`, `0x0052d970`, `0x0052e080`, `0x0052f2f0`, `0x0052fb00`, `0x00536b8e`, `0x00537e40`, `0x00537fe0`, `0x00538060`, `0x0053db90`, `0x00541240`, `0x005435d0`, `0x0054f3b0`, `0x0054fd0a`, `0x0055c700`, `0x00570960`, `0x00570ad7`, `0x00570def`, `0x00570e5b`, `0x00570e8b`, `0x00570ebb`, `0x00570eeb`, `0x00570f75`, `0x00571020`, `0x00577e50`, `0x00577f90`, `0x00578440`, `0x00578760`, `0x00580420`, `0x00580d50`, `0x00582490`, `0x005847e0`, `0x0058ac10`, `0x0058f6a0`, `0x0058fa20`, `0x005975e0`, `0x005a4060`, `0x005a6e90`, `0x005a8a90`, `0x005a8e50`, `0x005b104c`, `0x005b22d0`, `0x005b46e0`, `0x005bc820`, `0x005bd2e0`, `0x005bd340`, `0x005be320`, `0x005c86b0`, `0x006310e4`, `0x006f25b8`, `0x00770b80`, `0x00774970`, `0x007f4ca0`, `0x00b83654`, `0x00f83654`, `0x100184ff`, `0x10018506`, `0x10031484`, `0x100314bb` |
| <a id="delegated-reconstruction-waves-2026-10-19"></a>Delegated reconstruction waves, 2026-10-19 | `0x0042f4d0`, `0x00445760`, `0x0045a3a0`, `0x0045a7f9`, `0x004aa240`, `0x004d1ad0`, `0x004e8c00`, `0x00512b40`, `0x00524fc0`, `0x005252d0`, `0x005294c4`, `0x00546720`, `0x005e0000`, `0x0064ffff` |
| <a id="paused-checkpoint-2026-10-19"></a><a id="current-integration"></a>Paused checkpoint, 2026-10-19 | - |
| <a id="historical-integration"></a>Historical integration | `0x0040cfb0`, `0x00418030`, `0x004195f0`, `0x00423a50`, `0x00424720`, `0x0046b2b0`, `0x0046e700`, `0x0046fac0`, `0x00472380`, `0x00473640`, `0x00475be0`, `0x00475ca0`, `0x004790d0`, `0x004c6a50`, `0x004c6a60`, `0x004cfe70`, `0x004d0ec0`, `0x004d6170`, `0x004eabe0`, `0x004ec960`, `0x00551010`, `0x00552730`, `0x0055a820`, `0x0055af10`, `0x00586bd0`, `0x005bcb10` |
| <a id="goldtl-data-audit-2026-10-19"></a>GoldTL data audit, 2026-10-19 | - |
| <a id="verified-checkpoint"></a>Verified checkpoint | `0x004364f0` |
| <a id="next-actions-1"></a>Next actions | - |
| <a id="commands"></a><a id="current-state"></a>Commands | - |
| <a id="historical-state"></a>Historical state | - |
| <a id="evidence-and-handoff"></a>Evidence and handoff | - |
| <a id="pending-metadata-write-retire-split-artifact-row-0x0041ebca"></a>Pending metadata write: retire split-artifact row 0x0041ebca | `0x0041e680` |
| <a id="whole-binary-checkpoint-round-8"></a>Whole-binary checkpoint (round 8) | - |
| <a id="matching-lever-g5-and-g6-for-msvc-scheduler-tie-breaks"></a>Matching lever: /G5 and /G6 for MSVC scheduler tie-breaks | `0x00490c10`, `0x00615e12`, `0x0062ade8` |
| <a id="do-not-run-test---all-while-teammates-are-editing"></a>Do not run `test --all` while teammates are editing | - |
| <a id="per-row-cflags-clearing-needs-remove_field-and-a-cli-gap"></a>Per-row cflags: clearing needs remove_field, and a CLI gap | - |
| <a id="per-row-cflags-and-multi-function-translation-units"></a>Per-row CFLAGS and multi-function translation units | - |
| <a id="tl-link-blocker-d3d8lib-direct3dcreate8-import"></a>TL link blocker: `d3d8.lib` (Direct3DCreate8 import) | - |
| <a id="tl-link-scaffolds-comparison-build-only"></a>TL link scaffolds (comparison build only) | `0x005e0000`, `0x0064ffff` |
| <a id="tl-stub-floor-five-size-exact-codegen-walls"></a>TL STUB floor: five size-exact codegen walls | `0x00404dc0`, `0x004c9e20`, `0x00558220`, `0x0057d0d0`, `0x005a0ad0`, `0x007f4ca4`, `0x007f4e24` |
| <a id="round-18-block-layout-wall-probed-further"></a>Round 18: block-layout wall probed further | `0x004c9e20`, `0x004c9e8e`, `0x004c9ed7` |
| <a id="tl-stub-bodies-zero"></a>TL stub bodies: zero | `0x005eb108`, `0x0062ce8f` |
| <a id="tl-link-convergence"></a>TL link convergence | - |
| <a id="tl-comparison-image-links-round-20"></a>TL comparison image links (round 20) | - |
| <a id="round-21-import-table-parity"></a>Round 21: import-table parity | - |
| <a id="round-22-the-two-added-imports-are-a-library-version-mismatch"></a>Round 22: the two added imports are a library-version mismatch | `0x005e0000`, `0x0064ffff` |
| <a id="round-24-scan-integrity-cleanup-for-retired-and-library-converted-rows"></a>Round 24: scan-integrity cleanup for retired and library-converted rows | - |
| <a id="round-24-no_source-decomposed-from-the-status-code-path"></a>Round 24: NO_SOURCE decomposed from the status code path | `0x00650000` |
| <a id="round-24-band-range-is-an-approximation-per-row-library-identity-is-the-truth"></a>Round 24: band range is an approximation, per-row library identity is the truth | `0x005e0000`, `0x005e5a50`, `0x005e5ea0`, `0x005e9da0`, `0x005eaad0`, `0x0064ffff` |
| <a id="round-24-two-data-losses-repaired-one-still-open"></a>Round 24: two data losses repaired, one still open | - |
| <a id="round-25-no_source-258---50-stub-2-justified"></a>Round 25: NO_SOURCE 258 -> 50, STUB 2 justified | `0x005e0090`, `0x005e0140`, `0x005e7e30`, `0x00654e25` |
| <a id="round-25-0x5e0090-is-game-code-not-band-library"></a>Round 25: 0x5e0090 is game code, not band library | `0x005e0000`, `0x005e0090`, `0x0064ffff`, `0x0065f220` |
| <a id="round-26-full-d3dx8-member-inclusion-is-not-viable-with-this-archive"></a>Round 26: full D3DX8 member inclusion is not viable with this archive | - |
| <a id="round-26-backend-split-for-this-sandbox"></a>Round 26: backend split for this sandbox | - |
| <a id="round-27-quick-win-wave-started"></a>Round 27: quick-win wave started | `0x004042b0`, `0x00418b40`, `0x00469890`, `0x00473610`, `0x0047d240`, `0x004cffe0`, `0x0050be50`, `0x0051e070` |
| <a id="round-27-wave-composition-and-the-postlink-question"></a>Round 27: wave composition and the postlink question | - |
| <a id="round-28-library-pull-in-experiment-reverted-deliverable-restored"></a>Round 28: library pull-in experiment reverted, deliverable restored | - |
| <a id="round-29-derived-spans-for-zero-size-library-rows"></a>Round 29: derived spans for zero-SIZE library rows | - |
| <a id="round-30-d3dx8-member-inclusion-solved-text-gap-268-kb---32-kb"></a>Round 30: D3DX8 member inclusion solved, .text gap 268 KB -> 32 KB | - |
| <a id="round-31-data-virtual-size-back-to-reference-member-list-persisted"></a>Round 31: .data virtual size back to reference, member list persisted | - |
| <a id="round-32-member-filter-settled-header-layout-blocker-found"></a>Round 32: member filter settled, header-layout blocker found | - |
| <a id="round-33-d3dx8-provider-hunt"></a>Round 33: D3DX8 provider hunt | - |
| <a id="round-34-matching-d3dx8-provider-found-header-layout-fixed"></a>Round 34: matching D3DX8 provider found, header layout fixed | - |
| <a id="round-35-sdk81-archive-wired-member-set-still-approximate"></a>Round 35: SDK8.1 archive wired, member set still approximate | - |
| <a id="round-36-d3dx8-provider-cannot-be-identified-byte-identity-blocked"></a>Round 36: D3DX8 provider cannot be identified; byte identity blocked | `0x005e6d72` |
| <a id="round-37-provider-confirmed-in-toolchain-images-member-set-re-derived"></a>Round 37: provider confirmed in toolchain images, member set re-derived | - |
| <a id="round-38-no_function-driven-down-remaining-bytes-need-completed-bodies"></a>Round 38: NO_FUNCTION driven down, remaining bytes need completed bodies | - |
| <a id="round-38b-near-match-batches-running-no_function-accounting-settled"></a>Round 38b: near-match batches running, NO_FUNCTION accounting settled | `0x0041b820`, `0x00465840`, `0x004c70fa`, `0x00550770` |
| <a id="round-39-no_function-accounting-fix-upstream-two-agents-on-the-remainder"></a>Round 39: NO_FUNCTION accounting fix upstream, two agents on the remainder | `0x004f1860` |
| <a id="round-40-no_function-reached-zero-no_source-is-the-remaining-counter"></a>Round 40: NO_FUNCTION reached zero; NO_SOURCE is the remaining counter | - |
| <a id="round-41-no_function-0-and-no_source-0-measured"></a>Round 41: NO_FUNCTION 0 and NO_SOURCE 0 measured | `0x004f1840`, `0x004f1850`, `0x004f1860`, `0x00650000`, `0x00660ace` |
| <a id="round-42-zero-counters-hold-proven-restored-data-owner-added"></a>Round 42: zero counters hold; PROVEN restored; data owner added | `0x00404dc0`, `0x0041adc0`, `0x004c9e20`, `0x00558220`, `0x0057d0d0`, `0x005a0ad0`, `0x00675318` |
| <a id="round-43-ga-finds-no-source-expressible-lever-ga-pragma-anchor-bug-fixed"></a>Round 43: GA finds no source-expressible lever; GA pragma anchor bug fixed | `0x00473610`, `0x00490c10`, `0x004b64b0`, `0x004c3800`, `0x004c6e20`, `0x0050b840`, `0x00536b10` |
| <a id="round-44-new-lanes-dispatched-tiny-band-functions-closest-near-import-split"></a>Round 44: new lanes dispatched (tiny band functions, closest NEAR, import split) | `0x0040fb80`, `0x0047c1f0`, `0x00495180`, `0x004ce210`, `0x005eaad0`, `0x005eb307`, `0x005ec8bf`, `0x005edcfa`, `0x005ef2e0`, `0x005f022d`, `0x005f0e27`, `0x006052b9`, `0x0060ffc0` |
| <a id="round-45-no_function-0-under-the-pinned-cli-ten-parallel-reconstruction-agents"></a>Round 45: NO_FUNCTION 0 under the pinned CLI, ten parallel reconstruction agents | `0x00444ff0`, `0x005f0e46` |
| <a id="round-49-counters-reconciled-after-the-boundary-merges"></a>Round 49: counters reconciled after the boundary merges | - |
| <a id="gap-to-byte-identity"></a>Gap to byte identity | `0x00261000`, `0x0026d000`, `0x005e0000`, `0x0066ffff` |

</details>
