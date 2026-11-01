# Handoff

## Resume (2026-11-01) — Gold TL byte match

Objective is `goal.md`: reconstruct C89 so `Europa1400Gold_TL.exe` matches the reference. One source-shape change per near-miss. Keep it only when `rebrew test` raises `match_count`. Otherwise restore the body by hand and retest. No per-function flag overrides, no postlink fixups, no edits to a body that is exact on the server. Do not hand-edit `rebrew-functions.toml`.

Working checkpoint: [TODO.md](TODO.md) section "Working checkpoint (2026-11-01)". Provenance for this pass is the 2026-11-01 tail of [provenance.md](provenance.md).

### Kept

`src/Develop/Unassigned/GOLDTL.fcn_00613478.c` — TL `0x613478`. The zero path stores `0xffff` at `0x6ad80c` before the `State613478` copy. Dry-run NEAR 161/221, up from 160/221. The row is retired, so `rebrew diff 0x613478` reports no source file and a normal `rebrew test` refuses the verdict (`a retired source binding cannot receive a comparison verdict`). Compare with:

```
uv run rebrew test src/Develop/Unassigned/GOLDTL.fcn_00613478.c --target Europa1400Gold_TL.exe --va 0x613478 --size 221 --symbol _fcn_00613478@4 --no-promote --json --dry-run
```

Native prologue is `cmp [ebp+8], 0; push esi; push edi; jne`. The candidate is still `push ebx; push esi; push edi`. Native pushes `ebx` only after the nonzero path clears `0x6ad80c`. Tried and restored: a `goto` split (43/224), an else-only pointer (147/221), `#pragma optimize("g", off)` (68/239). Leave the existing `optimize("s")` and `optimize("y", off)` pragmas in place.

### Restored this pass (score did not rise)

| VA | Trial | Official or dry-run result |
| --- | --- | --- |
| `0x4c6090` | `t+4` store on both flag arms | NEAR 173/188, restored 174/188 |
| `0x5473a0` | countdown clear of `0x3e` dwords | NEAR 175/188 |
| `0x57de80` | unsigned shift of the `0x40` bit | NEAR 192/196 |
| `0x4b64b0` | ptrdiff loop test | SIZE_MISMATCH 186/206, restored 203/204 |
| `0x4eea30` | early returns for `0.0f` then `1.0f` | NEAR 152/209, restored 203/209 |
| `0x5aceb0` | `count++` before `io_AppendText` | NEAR 146/219 |

Earlier in the same goal, these also failed and were restored: `0x536b10` goto 154/156, `0x41b510` hoisted `t860` 105/159 (restored 122/159), `0x436a00` register count 117/159, `0x4f2ee0` `* 147` index 7/182 (restored 138/161), `0x509120` register age 124/161, `0x471e30` register parameter 148/169, `0x57c7b0` register node 146/173, `0x472680` split index 174/184, `0x4c6940` one field temp 156/186.

### Next

Smallest sourced TL `NEAR_MATCHING` after `0x613478` (221 bytes) is `0x4f88d0` (224). A named buffer pointer was already tried there and stayed 196/224. Pick a different shape. Skip retired `0x613478` as a `rebrew diff` target; use the command above. Do not edit `ahm_ExAllocAlchemist` or `cm_ExSellObjekt`. Do not edit the server half of `gm_GetEntityTableEntry`.

Scratch for this goal's JSON is `/tmp/grok-goal-7c6320d4f69c/implementer/` and is deleted when the goal ends. The kept evidence is the source, the provenance entry, and the TODO line.

Start with [current work](TODO.md) for the working checkpoint and next actions,
then consult the [documentation map](README.md#reference-map) for native
findings. [Goal history](goal-history.md) indexes historical milestones. The
project default target is GoldTL; select `server.dll` explicitly for server work.
Use fresh checks for current status.

The previous Gold/TL creator integration and stopped client build are documented
at [the paused checkpoint](TODO.md#paused-checkpoint-2026-10-19). Its local
receipts are in `.scratch/gui-text-creator-integration/`; the stopped build is
not evidence for a current image.

<a id="prepared-helper-work"></a>

## Prepared helper work (historical, 2026-10-19)

These packages describe the October 19 checkpoint; check current sources before
using them. They are not newly integrated or byte-matched C bodies.
Each path is a local scratch directory containing `REPORT.md`.

| Package | State / limits | Receipt directory |
| --- | --- | --- |
| Index allocators, Gold `0x46c9e0` / TL `0x469890` | Candidate uncompiled; wrappers not admitted to inventory/catalog. Existing scanners stay unchanged. | `.scratch/gui-index-allocator-prep/` |
| Native allocator checks | 18 finite cases pass; two negative controls reject. Executes original wrapper and scanner. No C-equivalence or storage-capacity claim. | `.scratch/gui-index-allocator-emulation/` |
| Text width, Gold `0x46ea00` / TL `0x46b520` | Candidate uncompiled; both production providers remain stubs. | `.scratch/gui-text-width-prep/` |
| Insertion, Gold `0x4730d0` / TL `0x46f650` | Candidate uncompiled; Gold remains a stub, TL already has recovered RELOC C. | `.scratch/gui-element-insertion-prep/` |
| Native insertion checks | 26 fixtures pass: 24 returning cases and two expected invalid-read paths; 24 wrong-output controls reject. Copy/error callees are explicit models, not provider proof. | `.scratch/gui-element-insertion-native/` |
| Creator data identities | 13 proposals, none applied; extent and ownership remain unresolved. | `.scratch/gui-creator-data-identities/` |
| Glyph contract | Gold consumes the low word; TL consumes a full signed index. Keep existing EXACT providers; no universal narrowing is justified. | `.scratch/gui-glyph-lookup-contract/` |

The extra harness slots used to observe LAST+1 accesses establish no native
allocation capacity or storage owner.
