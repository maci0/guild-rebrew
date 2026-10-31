# Handoff

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
