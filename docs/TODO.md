# Current work

## 2026-11-24 snapshot (Singapore time)

`uv run --frozen rebrew status --all-targets --json` reads stored function
verdicts and compares the configured raw builds with the references. The client
builds are under `build/consolidation-baseline-pp/`.

| Target | C matches / game functions | Accounted `.text` | Raw bytes equal at original offsets |
| --- | ---: | ---: | ---: |
| server.dll | 251 / 251 | 100.0% | 286,720 |
| GoldTL | 4,290 / 5,260 | 59.5% | 137,400 |
| Gold | 2,110 / 4,429 | 23.5% | 26,792 |

C matches count `EXACT` and `RELOC` and exclude five Gold whole-function assembly
matches. Code accounting includes libraries and padding. Inventory totals
include functions without source and can change when native extents or
attribution change.

The existing server build matches the reference byte for byte. A read-only
verification of that image also passed all 652 data comparisons and all
whole-binary checks. The [1.14.0 release](releases/1.14.0.md#validation) records
the full gate, including compilation and Wine. Both client images still differ
and use placeholders. Rebuild before reporting a new working-tree result. [Server gate](build.md) · [Client comparison](../stubs/README.md)

`uv run --frozen rebrew lint --all-targets --json` (Rebrew 6.72.0) reported
5,427 files passed per target and zero lint findings. The binding loader
separately logged retired Gold anchors.

## Open work

1. Replace [client placeholders](../stubs/README.md#placeholder-stubs) with
   verified function providers and data owners. GoldTL's two top data actions
   are displaced `g_869480` and `g_90e0a0`. Review the interior vector addresses
   `g_773e18` and `g_773e1c` and the string overlap at
   `g_6a42f8`/`g_6a42fc` before allocating storage. Establish complete extents and
   backing objects, then relink and check placement, imports, data and the whole
   file. [Data ownership](data-ownership.md)
2. Recover GoldTL and Gold bodies from native evidence. The top GoldTL function
   actions on November 24 were `fcn_005ba910` (`SIZE_MISMATCH`),
   `cut_RunProzess` (0x004dcf50, `STUB`) and `io_AppendText` (`STUB`).
   Read their blockers before trying another source shape.
   [Unfinished reviews](HANDOFF.md) · [Compiler probes](codegen-walls.md)
3. Recheck shared-source candidates against all affected targets. Prior
   regressions involved `gm_SubObjekt`, `gm_AllocBuildingDefaults`,
   `cm_ExProdObjekt`, `gm_ResolveEntityRecord`, `gm_AssignBuildingOwner` and
   `gm_ResolveEntitySlot`. The earlier `gm_ff_Objekt` review was incomplete.
   Check current bindings and whole-TU results first. [Provenance](provenance.md)
4. Revisit the seven GoldTL zlib candidates still bound to loose game sources.
   The November 8 vendor comparison identified the bodies below, and the
   binder refused those definitions at the time. Preview each binding with the
   current CLI. A later parser fix enabled `inflate_blocks_sync_point`
   (0x00460a40), now `LIBRARY` and `EXACT` on `references/zlib/infblock.c`.
   The comparison found no vendor match for `fcn_00401000`.
   [Vendoring](vendoring.md) · [Provenance](provenance.md)

   | GoldTL VA | zlib candidate |
   | --- | --- |
   | 0x0045dfd0 | `deflateCopy` |
   | 0x0045e520 | `deflate_fast` |
   | 0x0045fd70 | `inflate_blocks` |
   | 0x00460a00 | `inflate_set_dictionary` |
   | 0x004616e0 | `inflate` |
   | 0x00465800 | `zError` |
   | 0x00465840 | `zcfree` |

5. Review unknown names and source placement as evidence becomes available.
   Check shared declarations and data bindings before renaming a file or
   symbol. [Naming conventions](naming_conventions.md) · [Source layout](source-layout.md)

## Matching leads

These are leads from earlier comparisons. Check current diffs before retrying.

| GoldTL VA | What to check |
| --- | --- |
| 0x00499950 | A named-float candidate reached `RELOC` (250 bytes). Verify the extent, owner and bindings for the eight float addresses at 0x01009354 through 0x0100938c, stride 8. |
| 0x00495180 | The retained form matches 623 of 625 bytes. It emits `test eax, eax` where the reference reuses zero in `cmp eax, esi`. A redundant zero check matched the bytes in scratch. Look for a faithful form with one check. |
| 0x00418210 | The November 11 result matched 880 of 904 bytes. The native code reuses the dead `obj` argument slot for `len`, conversion temporaries and `alive`. Declaration order and added scopes did not recover the stack slots. |
| 0x004cf000, 0x004da170, 0x005d0460 | Review x87 scheduling and tail-call formation against native TU neighbours. The related 0x004cefb0 now has stored `EXACT`. |
| 0x00446540, 0x004a0bb0 | Review SIB base/index allocation. Operand swaps and pointer-arithmetic rewrites failed in earlier probes. The related 0x0041bf90 now has stored `RELOC`. |

## Choose work from canonical inputs

```sh
uv run --frozen rebrew todo --target Europa1400Gold_TL.exe --json
uv run --frozen rebrew source findings 0x00499950 --json
```

Use the selected address for the findings lookup and check that the evidence applies to your target. See the
[research archive](goal-history.md#full-notebooks) for previous work queues.
