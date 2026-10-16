# Goal history

Historical checkpoints, not current status. [TODO.md](TODO.md) owns continuation;
[goal.md](../goal.md) owns the objective. Counts below describe their checkpoint
only. Full receipts remain in the archive and referenced `.scratch/goal*/` folders.

## Milestones

| Period / checkpoint | Outcome |
| --- | --- |
| September 2026 | Server function recovery and split-link experiments established codegen, allocation and layout findings. Postlinked identity did not prove raw-file identity; copied CRT storage, artificial padding and obsolete emitters were subsequently retired. |
| October 3–4 | Native server still lacked 16,384 file bytes and 3,604 virtual data bytes. Query/prototype bindings and complete extents improved client agreement without establishing client images. Upstream metadata, source-order and integration repairs landed. |
| October 10–12 | Shared allocators, MSX, character and D3 units recovered. Canonical zlib providers replaced copied bodies. Gold's `/ML` runtime was distinguished from server/TL `/MT`. The server attained raw-file identity; remaining vendor stand-ins and discarded-source fidelity stayed open. |
| Goals 28–33, October 14–15 | Conditional-source/provider and data-scope fixes restored server identity and corrected duplicate owners. Shared lighting and object-transform evidence landed; the transform animation wrapper remained a near match. |
| Goals 34–45 | Command, D3 cleanup, scene and library/provider audits consolidated shared logic. Misbound source claims were retired; lint and extent inventories were repaired. See archive entries by date or address. |
| Goal46 | Office native-layout and message-family evidence isolated contract and scheduling differences. Restored Docker access allowed a fresh passing server gate. |
| Goal47 | Office-message provider/caller contracts reconciled while preserving native bytes. |
| Goal48 | Canonical 24-byte `OFFICE_SLOT` contracts and compiled layouts; Gold helper extents corrected. |
| Goal49 | Shared skill-query contracts and Gold counterparts; canonical pointer/index and float-return interfaces. |
| Goal50 | Shared `gm_AllocObjekt` client logic recovered in `spiel.c`, including native cart/resource behavior and embedded switch tables. |
| Goal51 | Attested `ch_CreateMesh` added: 777 TL / 787 Gold bytes. Gold-specific calls and flag positions retained. |
| Goal52 | Animation-loader counterpart and byte-flag contracts repaired. A falsely resolved reset caller was explicitly demoted rather than hidden. |
| Goal53 | Inferred `ProcessActiveContexts` separated from real `gm_ResetAllEntities`; the reset caller regained RELOC 221. |
| Goal54 | Attested `ch_InsertAction`: 461 TL / 456 Gold bytes. Queue and payload contracts reconciled; Gold message counterpart verified. |
| Goal55 | Shared 1,102-byte dummy filter matched in both clients; canonical result layout bound. Gold wrapper adoption deferred on scene contracts. |
| Goal56 | Shared 1,033-byte script registrar, 185-byte WalkToDummy and three-byte TL PreloadSitMesh matched. Camera callback remained mismatched. |
| Goal57 | Shared 1,920-byte event validator and Gold 630-byte consumer matched; fourth callback-slot contracts reconciled. Other callable slots remained unresolved. |
| Goal58 | Seven-case court callback reconstructed; 372 bounded trace cases passed. No byte match claimed. OWN query must precede OTHER. |
| Goal59 | Participant-reset helper separated from merged inventory. The 162-byte C bodies remained near matches; runner prerequisites stayed open. |
| Goal60 | Texture callback matched at 89 TL / 86 Gold bytes; Gold texture precacher matched 117. Resource reload and native error order retained. |
| Goal61 | Shared 31-byte cutscene clock and typed periodic callbacks; dispatcher/provider bytes preserved. |
| Goal62 | Shared 90-byte packet-base helper and pointer transports reconciled across its existing callers. |
| Goal63 | 65 native-only name/size/note rows: 55 TL mappings plus ten Gold counterparts. Zero new matched bytes or source/provider claims. |
| Goal64 | Shared 485-byte `rd_FillSupermapQuad` and Gold projection counterpart. Native double 0.9 bias retained. |
| Goal65 | TL inferred `SaveBMP8` matched 441 bytes; original fill macro, palette order and ignored write failures preserved. |
| Goal66 | Shared `am_RegisterMethod` 579 plus cutscene helpers 111/70 bytes: 760 new bytes per client. Separate inventory entries and native allocator-zero quirk retained. |
| Goal67 | Shared `AttachAnimLooped`: 454 bytes per client. Create-building scratch matched 838 but conflicting factory contracts blocked adoption. |
| Goal68 | Universe helper matched 151 TL / 146 Gold bytes. Factory byte/word inputs separated from a reused integer counter; all 1,078 server bytes preserved. Passing server gate, clean lint/data conflicts. |
| Goal69, October 16 | Bounds pointer/float contracts preserved 64 compiled contexts. TL scoped verification finished; Gold/current-tree server checks pending. Two native families mapped at four addresses, adding zero matched bytes. Separate config delta requires review. |
| Goal70 | Six native-only TL role mappings cover 17,150 executable bytes; five Gold action identities cover 7,973. Independent UI entries repaired TL and Gold inventory spans without losing bytes or prior matches. Zero new matched bytes; receipts `.scratch/goal70/`. |
| Goal71 | Five separated TL UI bodies mapped, original `ecmd_LoadScene` identified in both clients and native inventory spans repaired. Gold reference extent/data section corrected without verdict promotion. Shared credit draft remains uncompiled; scene loader/provider and UI-service contracts remain open. Receipts `.scratch/goal71/`. |
| Goal72 | Three parallel native mapping packages recorded 15 new identities: large combat/day bodies, separate lookup/callback entries, object/terrain readers and credit dependencies. `rd_object` is attested; shared `io_Text` diagnostics retain placeholder names. Complete tables retained, terminal NOPs separated, all 6,067 strong rows preserved. Zero new matched bytes; lint/data conflicts clean. Receipts `.scratch/goal72/`. |
| Goal73 | Placement-search callback matched, 148 bytes in each client, after splitting it from the surrounding 62-byte function. Transform providers take `char*` and stay EXACT 254. Gold bounds verification and the current-tree server gate pass. Receipts `.scratch/goal73/`. |

## Full notebooks

[2026-10-16-notebooks.tar.xz](archive/2026-10-16-notebooks.tar.xz) preserves the
24 complete pre-cleanup project documents, including `goal.md`, the session
notebooks and technical references. Existing uncommitted entries are included.
The archive is evidence; its commands, active-job reports and environment
restrictions may be obsolete.

Read or search without extracting over the working tree:

```sh
tar -tf docs/archive/2026-10-16-notebooks.tar.xz
tar -xOf docs/archive/2026-10-16-notebooks.tar.xz docs/TODO.md | less
tar -xOf docs/archive/2026-10-16-notebooks.tar.xz docs/TODO.md | rg -n 'Round-978|Goal69|451840'
```

Current address lookup searches the live Markdown references, not the compressed
archive: `uv run --frozen rebrew source findings 0x<VA> --json`.
Do not append full goal snapshots again. Record one milestone and its receipt;
keep detailed experiments in their owning technical reference or scratch report.
