# Client-only functions of the shared TUs: round-19 sweep

Historical appendix to [link layout §5f](msvc6-link-layout.md#5f-reconstructed-client-code-in-the-shared-files-status-2026-10-08). The table records
TL bodies in shared TU spans and whether the measured server build could retain
them. That pass required every callee and absolute data operand to already have
a server provider or allocation. It is not a current work queue, and it is not
permission to invent storage from a neighboring address. Source metadata and
[TODO.md](TODO.md) own current state.

## Method

Round 19 measured whether a TL body inside a shared TU span could be retained
by the server build then in use. The helpers that produced it are retired:
`exp/client-map`, `.scratch/client_map/final_tl.json`,
`.scratch/measure/client_sweep/align.py`, `sweep.py` and `gen_table.py`.
Do not rerun them, and do not treat a row as a work item or as permission to
add storage.

What that measurement recorded:

- DIR32 counts are absolute operands plus jump-table entries, calibrated to
  1770/1768 on the server.
- Alignment was a weighted LCS of instruction shapes plus the multiset of
  non-address constants, in definition order inside each span. Kept COMDATs
  paired a server function with its client copy. Discarded COMDATs were the
  ported rows. Further pairs came from equal `SERVER` and `GOLDTL` symbols,
  client-map name matches, and the 106-entry command dispatch tables (server
  `0x1002c3f8`/`0x1002c5a0`, TL `0x68a9e0`/`0x68ab88`).
- Storage was accepted from aligned operands of paired functions, from the
  regions below, or ruled out where the client bytes had no server allocation.
  A bracket between equal-offset anchors is not proof (`0x868c40` brackets
  onto the relationship matrix).
- A blocked row names its first reason. `+N` counts further reasons from that
  pass. `ported` is that pass's classification, not a current byte verdict.
  Names in the ported column are the inferred identifiers recorded then; the
  [Names](#names) section separates the unattested ones.

Recheck a VA with the current CLI. The default target is
`Europa1400Gold_TL.exe`; pass `--target` for Gold or `server.dll`.
`rebrew binary asm show`, `rebrew binary xrefs`,
`rebrew binary strings --xref --filter`, `rebrew source units --json`,
`rebrew data list --json` and `rebrew library match` are read-only.
This checkout runs the compiler through `[compiler] execution_backend = "unshare"`
on the pinned toolchain image. Docker still prepares that image; it is not the
compile runner. Live status stays in source metadata and
[TODO.md](TODO.md). Repeated blocked reasons are grouped under each TU; every
TL VA, size and DIR32 from the original table remains.

## Storage proven this round

These are the pass's role/address correspondences, not a claim that client and
server share one allocation or equal full extents. The auxiliary count/pointer
cells are separate objects in each target; their spacing differs.

| client | server | evidence |
|---|---|---|
| 0x7f4c00..0x7f4c0e | game clock at `g_current_year` (0x10035880) | server `gm_AllocGebaeude` copies the 14 bytes as dword, dword, dword, word, as client 0x500c80 does; the base is anchored |
| 0x85ab80..0x868050 | `g_entity_end`/`g_slot_array` block 0x1009b760..0x100a8c30 | five 0x2a90 season tables (54480 bytes); `g_slot_array` (0x85ab90) and `g_entity_type_table` (0x868050) sit at +0xf840be0 on both ends, and the server's `ls_LoadTownData` and `gm_FindSlotById` read the same tables |
| 0x868060..0x868c30 | `g_city_records` (0x100a8c40, 3024 bytes) | same offset, client loop end 0x868c30 = server end 0x100a9810 |
| 0x696540..0x6965d8 | `g_spiel_const_table` (0x1002dd48) | the 152 bytes are identical; the server keeps the table without a reader |
| 0x6965d8..0x699058, 0x699398..0x6995d8 | `g_producer_id_table`, `g_stat_table` | spiel `.data` at +0xf997808 (round 18), anchored bases |
| 0x675170 | `g_broadcast_ff` (0x10027030) | the -1 dword at the head of broadcast.c's `.data`, before its first string, in both images |
| 0x773d4c..0x773d68 | `g_gap_10035410` | 28 unreferenced server bytes between `g_dynamic_count` and `g_next_family_index` at sim's offset, the client block's size; round 16 placed sim's scan cursor (0x773d64) in its last dword |
| 0x10058e0, 0x10058e4 | `g_aux_entity_count`, `g_aux_entity_buffer` | round 18 (box cache) |

## Storage without a server allocation

- **0x868c40..0x869480**: an 88 x 0x18 array (TL 0x503a70) between the city records and the relationship
  matrix. The server goes from `g_city_records` (end 0x100a9810) to `g_relationship_matrix_primary`
  (0x100a9820); the client's matrix is at 0x869480, offset 0xf8403a0 = 0xf840be0 - 0x840.
- **0x6995d8**: the client's extra 6-byte record after the stat records (TL 0x506da0).
- 5f's earlier verdicts: the alchemistry deck and 8 x 0x170 alchemist table, sim's name table, command.c's
  four -1 dwords, aemter's counters at 0x9a9620.

## Why the rest stays out

- **Client command senders** (TL 0x4c4b00..0x4c6e00, about 100 functions): each builds a command packet and
  queues it through 0x4c4330 into the client's packet ring (0xaed740, 0xfb5760). The attested client
  names of this family are `cm_Request*` (`cm_RequestCreateGeb`, `cm_RequestSellObjekt`). The server has no
  client command queue, so the senders and every caller (most of sim, aemter and spiel's blocked set) stay
  out.
- **Client engine calls and data**: 3D objects, UI, sound, text tables (0x14a5xxx, used by server.c
  0x4e73f0..0x4e7700), path strings (0x6b5c20/0x6b5c60), the multimedia-timer tick 0x6b7fac (the timer
  unit is not built, 5f) and the engine globals at 0x7746xx..0x774970.
- **Unproven storage**: client BSS with no anchor at a consistent offset (0x7f3f00.. in TL 0x50e780,
  0x50e830; 0x99f5e0.. in the loadsave readers and writers).

## Names

Every name below is inferred. None has a `name(): ...` string in either client
or a `__FILE__` path: `amt_GetRankLimits`, `ahm_fio_SaveAvatars`, `gm_GetGameTime`, `gm_GetEntityDate`,
`gm_RefreshSeasonSlots`, `gm_GetSlotBase`, `gm_GetSlotPrice`, `gm_GetObjektPrice`, `gm_GetStatRecord`,
`gm_GetKindRecord`, `gm_HasGuildHall`, `gm_ShuffleBytes`, `gm_GetBuildingWorth`, `gm_GetTypeProductValue`,
`gm_GetWorkshopStock`, `ls_SaveBuildingEntityState`, `ls_SaveTownData`, `CloseBroadcastSocket`
(broadcast.c has no attested prefix), and the types `OFFICE_RANK_LIMITS`, `PACKED_TIME`, `STAT_REC`,
`KIND_REC` and macro `gm_SEASON_TABLES`. They follow the module prefix and VerbNoun scheme.

## Table

### Error.c

Client copies of server functions in the span (not listed): 13.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x41ca10` | 142 | 6 | ruled out | nearest palette colour, client graphics unit (5f) |
| `0x41db30` | 55 | 6 | ruled out | GILDE_* debug-variable registration, client unit; storage absent in server Error.c (5f) |

### m_alloc.c

Client copies of server functions in the span (not listed): 6.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x41dd90` | 64 | 2 | ported | `m_is_tracked` |
| `0x41ddd0` | 117 | 8 | blocked | crt ___RTCastToVoid not loaded |
| `0x41e350` | 144 | 0 | ported | `m_pool_next` |
| `0x41e3e0` | 48 | 0 | ported | `m_pool_first` |
| `0x41e410` | 43 | 0 | ported | `m_pool_free_all` |
| `0x41e440` | 69 | 0 | ported | `m_pool_clear` |
| `0x41e490` | 61 | 0 | ported | `m_pool_info` |
| `0x41e4d0` | 93 | 0 | ported | `m_pool_stats` |

### vfs.c

Client copies of server functions in the span (not listed): 3.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x42e4c0` | 96 | ? | ported | `vfs_CompareNames` |
| `0x42e520` | 32 | ? | ported | `vfs_NormalizeCase` |
| `0x42e540` | 39 | ? | ported | `vfs_ToSlashes` |
| `0x42e570` | 39 | ? | ported | `vfs_ToBackslashes` |
| `0x42e5a0` | 160 | ? | ported | `vfs_GetSubDir` |
| `0x42e640` | 64 | ? | ported | `vfs_CompareKey` |
| `0x42e680` | 192 | ? | ported | `vfs_FindFile` |
| `0x42e740` | 1472 | ? | ported | `vfs_AddFile` |
| `0x42ed00` | 225 | ? | ported | `vfs_AddPath` |
| `0x42edf0` | 96 | ? | ported | `vfs_CompareFiles` |
| `0x42ee50` | 436 | ? | ported | `vfs_FinishFiles` |
| `0x42f010` | 272 | ? | ported | `vfs_FindDir` |
| `0x42f120` | 288 | ? | ported | `vfs_LookupPath` |
| `0x42f240` | 480 | ? | ported | `vfs_MakeDirs` |
| `0x42f420` | 176 | ? | ported | `vfs_GetDirPath` |
| `0x42f4d0` | 368 | ? | ported | `vfs_GetRelativePath` |
| `0x42f640` | 80 | ? | ported | `vfs_GetDirPathOf` |
| `0x42f690` | 64 | ? | ported | `vfs_GetFilePathOf` |
| `0x42f6d0` | 1101 | ? | ported | `vfs_ScanDir` |
| `0x42fb20` | 294 | ? | ported | `vfs_ScanArchive` |
| `0x42fc50` | 120 | ? | ported | `vfs_FreeDirs` |
| `0x42fe60` | 240 | ? | ported | `vfs_RemoveFile` |
| `0x42ff50` | 1584 | 29 | ported | `vfs_Tfopen` |
| `0x430870` | 48 | 0 | ported | `vfs_fgetc` |
| `0x4308a0` | 112 | 0 | ported | `vfs_fgets` |
| `0x430910` | 368 | 0 | ported | `vfs_fwrite` |
| `0x430a80` | 464 | 6 | ported | `vfs_fseek` |
| `0x430c50` | 96 | 0 | ported | `vfs_ftell` |
| `0x430f70` | 256 | 1 | ported | `vfs_ForEachFile` |
| `0x431070` | 119 | 6 | ported | `vfs_init` |
| `0x4310f0` | 172 | 9 | ported | `vfs_exit` |


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x42fcd0` 400/13 `0x64e790` +1; `0x4311a0` 390/0 `0x438b40` +1; `0x431330` 648/4 `0x438b40`;

### broadcast.c

Client copies of server functions in the span (not listed): 0.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x402320` | 28 | ? | ported | `CloseBroadcastSocket` |


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x402610` 212/14 `0x413190` +9; `0x4026f0` 185/14 `0x413190` +9;


Blocked because the operand is client data also used outside the shared TUs. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x402220` 256/22 `0x1552000` +5; `0x402340` 37/4 `0x1552000`; `0x402370` 672/43 `0x6b1f58`;

### plant.c

Client copies of server functions in the span (not listed): 4.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4bcc20` | 48 | 0 | ported | `plt_FindRecordByOwner` |
| `0x4bcc50` | 48 | 0 | ported | `plt_FindRecordById` |
| `0x4bd1e0` | 758 | 34 | ported | `rd_AddBKBox` |


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4bcb20` 88/8 `0x4bcae0` +2; `0x4bcda0` 272/3 `0x442be0` +2; `0x4bceb0` 672/7 `0x442be0` +5;
`0x4bd150` 69/0 `0x4bcf20` +1; `0x4bd1a0` 50/0 `0x442d50`;

### command.c

Client copies of server functions in the span (not listed): 55.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4c4dc0` | 48 | 3 | ruled out | reads command.c's four -1 dwords (TL 0x68a9d0), plain .data the server lacks (5f) |
| `0x4cc2b0` | 144 | 0 | ruled out | client version of server dispatch handler 64 (5f) |
| `0x4cd750` | 80 | 0 | ruled out | client version of server dispatch handler 92 (5f) |
| `0x4cdd00` | 96 | 0 | blocked | calls blocked client-only 0x4f0960 (+1 more) |


Blocked client-command senders. The measured server build had no client command queue. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4c4e40` 39/0 `0x4c4330`; `0x4c4e70` 53/0 `0x4c4330`; `0x4c4eb0` 51/0 `0x4c4330`;
`0x4c4ef0` 51/0 `0x4c4330`; `0x4c4f30` 144/0 `0x4c4330`; `0x4c4fc0` 118/0 `0x4c4330`;
`0x4c5040` 147/0 `0x4c4330`; `0x4c50e0` 50/0 `0x4c4330`; `0x4c5120` 41/0 `0x4c4330`;
`0x4c5150` 72/0 `0x4c4330`; `0x4c51a0` 72/0 `0x4c4330`; `0x4c51f0` 96/0 `0x4c4330`;
`0x4c5250` 63/0 `0x4c4330`; `0x4c5290` 61/0 `0x4c4330`; `0x4c52d0` 52/0 `0x4c4330`;
`0x4c5310` 80/0 `0x4c4330`; `0x4c5360` 51/1 `0x4c4330` +1; `0x4c53a0` 51/1 `0x4c4330` +1;
`0x4c53e0` 51/1 `0x4c4330` +1; `0x4c5420` 83/0 `0x4c4330`; `0x4c5480` 61/0 `0x4c4330`;
`0x4c54c0` 97/2 `0x4c4330` +2; `0x4c5530` 74/0 `0x4c4df0` +1; `0x4c5580` 160/1 `0x4c4df0` +2;
`0x4c5620` 212/2 `0x4c4df0` +1; `0x4c5700` 112/1 `0x4c4330`; `0x4c5770` 28/0 `0x4c4330`;
`0x4c5790` 68/0 `0x4c4330`; `0x4c57e0` 50/0 `0x4c4330`; `0x4c5820` 80/1 `0x4c4330`;
`0x4c5870` 50/0 `0x4c4330`; `0x4c58b0` 50/0 `0x4c4330`; `0x4c58f0` 61/0 `0x4c4330`;
`0x4c5930` 76/2 `0x4c4330` +1; `0x4c5980` 160/0 `0x4c4df0` +1; `0x4c5a20` 50/0 `0x4c4330`;
`0x4c5a60` 61/0 `0x4c4330`; `0x4c5aa0` 96/0 `0x4c4330`; `0x4c5b00` 74/0 `0x4c4330`;
`0x4c5b50` 72/0 `0x4c4330`; `0x4c5ba0` 84/0 `0x4c4330`; `0x4c5c00` 125/1 `0x4c4330`;
`0x4c5c80` 39/0 `0x4c4330`; `0x4c5cb0` 101/0 `0x4c4330`; `0x4c5d20` 50/0 `0x4c4330`;
`0x4c5d60` 61/0 `0x4c4330`; `0x4c5da0` 304/0 `0x4c4330`; `0x4c5ed0` 70/0 `0x4c4330`;
`0x4c5f20` 61/0 `0x4c4330`; `0x4c5f60` 61/0 `0x4c4330`; `0x4c5fa0` 39/0 `0x4c4330`;
`0x4c5fd0` 39/0 `0x4c4330`; `0x4c6000` 50/0 `0x4c4330`; `0x4c6040` 72/0 `0x4c4330`;
`0x4c6090` 192/0 `0x4c4330` +1; `0x4c6150` 62/0 `0x4c4330`; `0x4c6190` 64/0 `0x4c4330`;
`0x4c61d0` 234/0 `0x4c4330`; `0x4c62c0` 55/0 `0x4c4330`; `0x4c6300` 39/0 `0x4c4330`;
`0x4c6330` 39/0 `0x4c4330`; `0x4c6360` 57/0 `0x4c4330`; `0x4c63a0` 71/0 `0x4c4330`;
`0x4c63f0` 55/0 `0x4c4330`; `0x4c6430` 61/0 `0x4c4330`; `0x4c6470` 50/0 `0x4c4330`;
`0x4c64b0` 117/0 `0x4c4330`; `0x4c6530` 39/0 `0x4c4330`; `0x4c6560` 53/0 `0x4c4330`;
`0x4c65a0` 176/1 `0x4c4330`; `0x4c6650` 39/0 `0x4c4330`; `0x4c6680` 128/0 `0x4c4330`;
`0x4c6700` 181/0 `0x4c4330`; `0x4c67c0` 89/1 `0x4c4330` +1; `0x4c6820` 89/1 `0x4c4330` +1;
`0x4c6880` 61/0 `0x4c4330`; `0x4c68c0` 53/0 `0x4c4330`; `0x4c6900` 55/0 `0x4c4330`;
`0x4c6940` 186/1 `0x4c4330` +1; `0x4c6a00` 53/0 `0x4c4330`; `0x4c6a40` 39/0 `0x4c4330`;
`0x4c6a70` 39/0 `0x4c4330`; `0x4c6aa0` 53/0 `0x4c4330`; `0x4c6ae0` 50/0 `0x4c4330`;
`0x4c6b20` 61/0 `0x4c4330`; `0x4c6b60` 57/0 `0x4c4330`; `0x4c6ba0` 61/0 `0x4c4330`;
`0x4c6be0` 67/0 `0x4c4330`; `0x4c6c30` 56/0 `0x4c4330`; `0x4c6c70` 54/0 `0x4c4330`;
`0x4c6cb0` 54/0 `0x4c4330`; `0x4c6cf0` 53/0 `0x4c4330`; `0x4c6d30` 53/0 `0x4c4330`;
`0x4c6d70` 55/0 `0x4c4330`; `0x4c6db0` 48/0 `0x4c4330`; `0x4c6de0` 53/0 `0x4c4330`;
`0x4c6e20` 123/0 `0x4c4df0` +2; `0x4c6ea0` 42/0 `0x4c4330`; `0x4ce1d0` 50/0 `0x4c4330`;
`0x4ce210` 74/1 `0x4c4330` +1; `0x4ce260` 63/1 `0x4c4330` +1; `0x4ce2a0` 116/1 `0x4c4330` +1;
`0x4ce320` 84/1 `0x4c4330` +1; `0x4ce380` 84/1 `0x4c4330` +1; `0x4ce3e0` 65/0 `0x4c4330`;


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4c9440` 230/14 `0x546d10` +12; `0x4c9530` 27/1 `0x5356b0`; `0x4c9c30` 64/0 `0x4f5940`;
`0x4c9c70` 61/2 `0x4f58b0` +2; `0x4ca3d0` 400/6 `0x4032b0` +9; `0x4ca560` 608/2 `0x4032b0` +8;
`0x4ca7c0` 112/1 `0x4032b0` +1; `0x4ca830` 128/1 `0x4032b0` +1; `0x4ca8b0` 128/1 `0x4032b0` +1;
`0x4ca930` 64/0 `0x4fe470`; `0x4ca970` 2784/40 `0x4032b0` +17; `0x4cb450` 512/7 `0x4032b0` +5;
`0x4cb7f0` 1184/36 `0x4432d0` +29; `0x4cbda0` 59/0 `0x4f5d00`; `0x4cc030` 640/2 `0x413190` +5;
`0x4cc370` 82/0 `0x52db70`; `0x4cc4c0` 100/1 `0x529160`; `0x4cc530` 96/0 `0x4fdfe0` +1;
`0x4ccb70` 96/0 `0x426cc0` +1; `0x4ccbd0` 192/0 `0x4032b0` +2; `0x4ccc90` 160/0 `0x4032b0`;
`0x4ccd30` 192/5 `0x4ceac0` +5; `0x4ccdf0` 192/5 `0x4ceac0` +5; `0x4cceb0` 83/0 `0x4cfc40`;
`0x4cd2a0` 135/0 `0x451840` +2; `0x4cd330` 368/16 `0x4d8200` +9; `0x4cd980` 208/17 `0x4ce430`;
`0x4cdcb0` 80/0 `0x4e6a30`; `0x4cdd60` 272/1 `0x4be280` +3; `0x4cde70` 96/0 `0x4be280`;


Blocked because the operand is client data also used outside the shared TUs. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x4c4df0` 80/4 `0xaed330` +2; `0x4c7600` 37/2 `0x77494c`; `0x4c7630` 55/4 `0xaed328` +2;
`0x4c7670` 65/4 `0xfb5740` +1; `0x4c9cb0` 96/4 `0x99f800` +1; `0x4c9d10` 272/15 `0x9b0e30` +9;
`0x4cc750` 208/9 `0x7e3a60` +2; `0x4ce090` 112/6 `0x9baadc` +5; `0x4ce100` 68/6 `0x9baa20` +5;
`0x4ce150` 44/5 `0x9baa20` +4; `0x4ce190` 48/2 `0x9baa04` +2;


Blocked: the cited operand had no proven server allocation. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x4cded0` 48/3 `0x9baae0` +1; `0x4cdf00` 64/3 `0x9baae0` +2; `0x4cdf40` 192/16 `0x9ba9f4` +7;
`0x4ce000` 64/5 `0x772e88` +3; `0x4ce040` 64/5 `0x772e8c` +2; `0x4ce080` 13/2 `0x9ba9f4` +1;


Blocked on another client-only function. Each item is TL VA, size, DIR32, and that function.

`0x4cc3d0` 128/0 `0x505c80`;

### server.c

Client copies of server functions in the span (not listed): 2.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4e73c0` | 34 | 2 | ported | `srv_FormatStatDumpBegin` |
| `0x4e7490` | 179 | 2 | ported | `srv_FormatStatAttributes` |
| `0x4e7550` | 68 | 1 | ported | `srv_FormatStatSkills` |
| `0x4e7700` | 211 | 0 | blocked | calls blocked client-only 0x4e73f0 (+2 more) |
| `0x4e77e0` | 34 | 2 | ported | `srv_FormatStatDumpEnd` |
| `0x4e7b70` | 128 | 5 | ported | `srv_GetEntityOfficeSlot` |
| `0x4e7bf0` | 128 | 5 | ported | `srv_GetEntityCouncilSlot` |
| `0x4e7c70` | 208 | 6 | ported | `amt_GetOfficeAffinity` |


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4e7390` 34/2 `0x4e7310` +2; `0x4e7990` 480/9 `0x4f4830`;


Blocked because the operand is client data also used outside the shared TUs. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x4e73f0` 159/9 `0x14a57e0` +4; `0x4e75a0` 87/5 `0x14a5c6c`; `0x4e7660` 147/3 `0x14a6554`;

### aemter.c

Client copies of server functions in the span (not listed): 9.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4e89e0` | 157 | 5 | ruled out | client copy of server amt_ClearEntityLinks (round 16) |
| `0x4e8a80` | 80 | 3 | ported | `amt_GetSlotByRole` |
| `0x4e8ad0` | 32 | 1 | ported | `amt_GetRoleGroup` |
| `0x4e8af0` | 80 | 3 | ported | `amt_GetSlotByType` |
| `0x4e8b40` | 64 | 2 | ported | `amt_GetRoleTemplate` |
| `0x4e8b80` | 128 | 2 | ported | `amt_ListSlotsOfGroup` |
| `0x4e8c00` | 176 | 2 | ported | `amt_ListHeldSlotsOfGroup` |
| `0x4e8cb0` | 88 | 3 | ported | `amt_ListCouncilSlots` |
| `0x4e8d10` | 464 | 5 | ported | `amt_RankOpenOffices` |
| `0x4e8ee0` | 496 | 5 | ported | `amt_RankAllOffices` |
| `0x4e90d0` | 64 | 3 | ported | `amt_GetRoleHolder` |
| `0x4e9110` | 112 | 0 | ported | `amt_GetSuperiorHolder` |
| `0x4e9180` | 240 | 0 | ported | `amt_IsNextRoleStep` |
| `0x4e9270` | 160 | 0 | ported | `amt_HasIdleSuperior` |
| `0x4e9310` | 192 | 0 | ported | `amt_ListSuperiors` |
| `0x4e93d0` | 304 | 0 | ported | `amt_ListPromotionRoles` |
| `0x4e9500` | 46 | 1 | ported | `amt_ExpandSlots` |
| `0x4e9530` | 80 | 0 | ported | `amt_FindVacantRoleBelow` |
| `0x4e9580` | 432 | 20 | ported | `amt_GetRankLimits` |
| `0x4e98d0` | 120 | 7 | ruled out | int[10] counters at TL 0x9a9620 bracket onto g_module_path, which the server uses (5f) |
| `0x4e9950` | 112 | 2 | ported | `amt_ListRolesOfLevel` |
| `0x4e99c0` | 31 | 0 | ported | `amt_GetRoleLevel` |
| `0x4ea130` | 384 | 2 | ported | `amt_GetGroupVacancyFlags` |
| `0x4ea2b0` | 160 | 0 | ported | `amt_IsPendingAssignment` |
| `0x4ea460` | 80 | 3 | ported | `amt_HasCouncilHolder` |
| `0x4ea620` | 896 | 8 | blocked | 0x9a9580 bracket 0x101de900 (equal-offset anchors only) (+3 more) |
| `0x4ea9a0` | 416 | 4 | blocked | 0x9a9580 bracket 0x101de900 (equal-offset anchors only) (+3 more) |
| `0x4eb220` | 64 | 0 | ported | `amt_CanUpgradeBuildingTier1` |
| `0x4eb260` | 192 | 10 | ported | `amt_CanUpgradeBuildingTier2` |
| `0x4eb320` | 192 | 10 | ported | `amt_CanUpgradeBuildingTier3` |
| `0x4ec410` | 272 | 3 | ruled out | amt_fio_SaveAemter: ported, deferred (ICF flips to a_map; server copy logged) (round 18) |
| `0x4ec7d0` | 58 | 1 | ported | `amt_GetTownHallHolder` |
| `0x4ec810` | 64 | 0 | ported | `amt_CountTownHallSeats` |


Blocked client-command senders. The measured server build had no client command queue. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4e7d40` 480/23 `0x4c4eb0` +2; `0x4e8240` 144/2 `0x4c63a0`; `0x4e8760` 176/0 `0x4c6b60`;
`0x4e9730` 192/5 `0x4c4fc0` +1; `0x4e97f0` 224/1 `0x4c51a0` +4; `0x4e99e0` 1275/2 `0x4c54c0` +5;
`0x4e9ee0` 581/2 `0x4c4450` +3; `0x4ea350` 259/4 `0x4c4510` +9; `0x4eab40` 1184/14 `0x4c5530` +12;
`0x4eafe0` 576/15 `0x4c4450` +7; `0x4eb3e0` 928/20 `0x4c61d0` +8; `0x4eb780` 736/18 `0x4c51a0` +8;
`0x4eba60` 2160/37 `0x4c5420` +7; `0x4ec2d0` 108/0 `0x4c54c0`;


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4ea4b0` 176/4 `0x51af00` +2; `0x4ea560` 179/4 `0x51af00` +2; `0x4ec660` 174/1 `0x51af00` +1;
`0x4ec710` 108/4 `0x4f4830` +2;


Blocked on another client-only function. Each item is TL VA, size, DIR32, and that function.

`0x4e81a0` 25/0 `0x4e8240`; `0x4e81c0` 80/0 `0x4e8240`; `0x4e8210` 48/0 `0x4e8240`;
`0x4ec340` 208/2 `0x50f980`; `0x4ec780` 80/3 `0x4e8240`;

### alchemistry_logic.c

Client copies of server functions in the span (not listed): 13.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4ec8a0` | 176 | 5 | ported | `ahm_GetRecipeQuality` |
| `0x4ec950` | 80 | 0 | ported | `ahm_FindRecipeSlotImpl` |
| `0x4ec9a0` | 64 | 1 | ported | `ahm_HasFreeRecipeSeat` |
| `0x4ec9e0` | 181 | 14 | blocked | 0x772fd8: alchemistry card deck (5f (+8 more) |
| `0x4ecaa0` | 160 | 10 | blocked | 0x772f8c: alchemistry card deck (5f (+7 more) |
| `0x4ecb40` | 150 | 5 | blocked | 0x772fd8: alchemistry card deck (5f (+1 more) |
| `0x4ecbe0` | 64 | 2 | blocked | 0x772fe0: alchemistry card deck (5f (+1 more) |
| `0x4ecc20` | 176 | 6 | blocked | 0x772fe0: alchemistry card deck (5f (+1 more) |
| `0x4eccd0` | 72 | 3 | ported | `ahm_GetBrewTime` |
| `0x4ecd20` | 272 | 10 | ported | `ahm_GetBrewYield` |
| `0x4ece30` | 128 | 5 | ported | `ahm_GetQualityShare` |
| `0x4eceb0` | 80 | 3 | ported | `ahm_GetRecipeBonus` |
| `0x4ed240` | 1472 | 83 | blocked | crt _atoi not loaded (+10 more) |
| `0x4ed800` | 1232 | 54 | blocked | 0x772fd8: alchemistry card deck (5f (+5 more) |
| `0x4edcd0` | 16 | 0 | ruled out | portable, 0 DIR32 (tail jump to gm_FindItemTypeByName(name + 3)); left out: with it _strncnt's ICF survivor flips to a_map.obj |
| `0x4edce0` | 65 | 6 | blocked | 0x772fdc: alchemistry card deck (5f (+4 more) |
| `0x4edd30` | 400 | 8 | blocked | 0x772f78: alchemistry card deck (5f (+7 more) |
| `0x4edec0` | 416 | 8 | blocked | 0x772f78: alchemistry card deck (5f (+8 more) |
| `0x4ee060` | 32 | 1 | blocked | 0x772f90: alchemistry card deck (5f |
| `0x4ee080` | 48 | 2 | blocked | 0x772f90: alchemistry card deck (5f |
| `0x4eed10` | 304 | 0 | ported | `ahm_fio_SaveAhmInfo` |
| `0x4eefe0` | 96 | 3 | ported | `ahm_FindAvatar` |
| `0x4ef040` | 144 | 1 | ported | `ahm_fio_SaveAvatars` |
| `0x4ef0d0` | 384 | 9 | ported | `ahm_fio_LoadAvatars` |
| `0x4ef2e0` | 1168 | 12 | blocked | 0x772fe8: alchemistry card deck (5f (+11 more) |
| `0x4ef770` | 1248 | 17 | blocked | 0x772fe8: alchemistry card deck (5f (+13 more) |
| `0x4efc50` | 119 | 13 | blocked | 0x7731b8: client 8 x 0x170 alchemist table (+9 more) |
| `0x4efd30` | 64 | 3 | ruled out | walks the client's 8 x 0x170 alchemist table (0x7731b8..0x773d38); the server's ahm_LookupEntityInTable walks a 10 x 0x5c table in command.c .data (5f) |
| `0x4efd70` | 112 | 7 | blocked | 0x7731b8: client 8 x 0x170 alchemist table (+5 more) |
| `0x4f0930` | 33 | 0 | ported | `ahm_FindRecipeSlot` |
| `0x4f0960` | 96 | 3 | ruled out | walks the client's 8 x 0x170 alchemist table (0x7731b8..0x773d38), declared differently in the server (5f) |
| `0x4f09c0` | 112 | 6 | blocked | 0x7731b8: client 8 x 0x170 alchemist table (+5 more) |
| `0x4f0da0` | 160 | 3 | ruled out | walks the client's 8 x 0x170 alchemist table (0x7731b8..0x773d38), declared differently in the server (5f) |
| `0x4f0e40` | 112 | 3 | blocked | 0x7731b8: client 8 x 0x170 alchemist table (+2 more) |
| `0x4f0eb0` | 176 | 6 | ported | `ahm_CalcTraitBonus` |
| `0x4f0f60` | 144 | 6 | ported | `ahm_CalcTraitLimits` |
| `0x4f0ff0` | 224 | 5 | ported | `ahm_CanAffordUpgrade` |
| `0x4f10d0` | 240 | 0 | ported | `ahm_GetLabUpgrades` |
| `0x4f11c0` | 194 | 4 | ported | `ahm_GetLabRisk` |
| `0x4f1290` | 144 | 2 | ported | `ahm_GetLabYieldFactor` |
| `0x4f13a0` | 48 | 0 | ported | `ahm_CountBusyWorkers` |
| `0x4f1450` | 112 | 0 | ported | `ahm_PickBestWorker` |
| `0x4f14c0` | 272 | 0 | ported | `ahm_CompareBestWorkers` |


Blocked client-command senders. The measured server build had no client command queue. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4ed190` 97/4 `0x4c5620` +2; `0x4ee220` 112/0 `0x4c6cf0` +1; `0x4ee6d0` 192/2 `0x4c6d30`;
`0x4ee830` 144/0 `0x4c6d30` +1; `0x4ee950` 112/0 `0x4c6d30`; `0x4eea30` 224/2 `0x4c6d30`;
`0x4eeb50` 96/0 `0x4c6d30`; `0x4eec10` 80/0 `0x4c6d30`; `0x4f01c0` 1799/32 `0x4c5530` +10;
`0x4f08d0` 36/0 `0x4c6db0`; `0x4f0900` 36/0 `0x4c6db0`; `0x4f0a30` 608/3 `0x4c51a0` +2;


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4ecf00` 656/27 `0x5463a0` +1; `0x4ed200` 64/0 `0x4edae0` +3; `0x4ef250` 140/2 `0x5b3410`;
`0x4efcd0` 91/3 `0x4432d0` +5; `0x4efde0` 988/63 `0x4432d0` +34;


Blocked because the operand is client data also used outside the shared TUs. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x4f0cc0` 224/3 `0x6b7fac`;


Blocked on another client-only function. Each item is TL VA, size, DIR32, and that function.

`0x4ee0b0` 173/7 `0x4ecbe0`; `0x4ee160` 192/2 `0x4ecbe0`;

### friedhof_logic.c

Client copies of server functions in the span (not listed): 17.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4f1790` | 96 | 0 | ported | `gv_GetSlotEntryIndex` |
| `0x4f17f0` | 48 | 0 | ported | `gv_eval_SameField` |
| `0x4f1820` | 24 | 0 | ported | `gv_eval_SameOwner` |
| `0x4f1840` | 80 | 1 | ported | `gv_eval_HasWorker` |
| `0x4f1890` | 64 | 1 | ported | `gv_eval_HasWorkerId` |
| `0x4f1a10` | 48 | 1 | ported | `gv_FindWorkerSlot` |
| `0x4f1a40` | 144 | 1 | ruled out | reaches storage with no server allocation (5f) |
| `0x4f36f0` | 128 | 0 | blocked | calls blocked client-only 0x4f1a40 (+1 more) |
| `0x4f3800` | 253 | 1 | ported | `gv_GetUpgradeBonus` |
| `0x4f3900` | 688 | 4 | ported | `gv_fio_SaveGraveyardData` |
| `0x4f3e60` | 144 | 3 | ported | `gv_HasGravediggerRoom` |


Blocked client-command senders. The measured server build had no client command queue. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4f22e0` 112/0 `0x4c6c30`; `0x4f2540` 96/0 `0x4c6c30`; `0x4f2810` 112/0 `0x4c6c30`;
`0x4f2a10` 112/0 `0x4c6c30`; `0x4f2ba0` 96/0 `0x4c6c30`; `0x4f2d30` 96/0 `0x4c6c30`;
`0x4f2e80` 96/0 `0x4c6c30`; `0x4f2f90` 71/0 `0x4c6c70`; `0x4f3280` 144/2 `0x4c6cb0` +1;
`0x4f3770` 144/3 `0x4c5480`;

### sim.c

Client copies of server functions in the span (not listed): 6.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x4ff860` | 144 | 2 | ported | `sim_IsUnrelated` |
| `0x4fffb0` | 64 | 2 | ported | `sim_IsUnderage` |
| `0x500240` | 416 | 7 | ported | `sim_ClaimResident` |
| `0x500480` | 256 | 6 | ported | `sim_NextServiceBuilding` |
| `0x500660` | 397 | 4 | ported | `sim_WalkDirectory` |
| `0x5007f0` | 49 | 3 | ruled out | sim name table 0x773d3c..0x773d44 defined in a client-only TU before sim.c (5f) |
| `0x500830` | 199 | 6 | ruled out | sim name table 0x773d3c..0x773d44 client-only (5f) |
| `0x500900` | 283 | 17 | ruled out | sim name table 0x773d3c..0x773d44 client-only (5f) |
| `0x500a20` | 29 | 2 | ruled out | sim name table 0x773d3c..0x773d44 client-only (5f) |


Blocked client-command senders. The measured server build had no client command queue. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4ff210` 640/19 `0x4c4510` +7; `0x4ff490` 976/14 `0x4c5480` +10; `0x4ff8f0` 1179/17 `0x4c4510` +10;


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x4ffff0` 496/0 `0x4fac80` +1; `0x500a40` 354/28 `0x4fef80` +7;

### spiel.c

Client copies of server functions in the span (not listed): 59.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x500c80` | 42 | 4 | ported | `gm_GetGameTime` |
| `0x500cb0` | 112 | 0 | ported | `gm_CompareGameTime` |
| `0x500d20` | 58 | 0 | ported | `gm_GameTimeMinutesBetween` |
| `0x500d60` | 66 | 0 | ported | `gm_PackGameTime` |
| `0x500db0` | 43 | 0 | ported | `gm_UnpackGameTime` |
| `0x500de0` | 29 | 0 | ported | `gm_AdvanceGameTime` |
| `0x500e00` | 23 | 0 | ported | `gm_GetPackedSeason` |
| `0x500e20` | 19 | 0 | ported | `gm_GetSeason` |
| `0x5013c0` | 208 | 1 | ported | `gm_GetItemCategory` |
| `0x501490` | 64 | 1 | ported | `gm_FindItemTypeByName` |
| `0x5014d0` | 64 | 1 | ported | `gm_IsRawItem` |
| `0x5016c0` | 46 | 3 | blocked | 0x868c30 bracket 0x100a9810 (equal-offset anchors only) (+1 more) |
| `0x5016f0` | 164 | 4 | ported | `gm_RefreshSeasonSlots` |
| `0x5020e0` | 866 | 38 | blocked | calls blocked client-only 0x5017a0 (+1 more) |
| `0x502450` | 131 | 9 | ported | `gm_GetSlotBase` |
| `0x5024e0` | 192 | 3 | ported | `gm_GetSlotProduction` |
| `0x5025a0` | 480 | 21 | ported | `gm_GetSlotPrice` |
| `0x502780` | 80 | 2 | ported | `gm_GetObjektPrice` |
| `0x502820` | 43 | 1 | ported | `gm_GetTileDistance` |
| `0x502a20` | 688 | 57 | ported | `gm_NextQueryItemMatch` |
| `0x503a70` | 672 | 31 | blocked | 0x868c40: client array 88 x 0x18 between g_city_records and the relati (+7 more) |
| `0x503d10` | 320 | 7 | ported | `gm_FindTavernServing` |
| `0x503e50` | 41 | 0 | ported | `gm_FindKind47ByOwner` |
| `0x5049a0` | 400 | 3 | ported | `gm_FindBuildingStore` |
| `0x504db0` | 181 | 0 | ported | `gm_FindNearestOfKind` |
| `0x504eb0` | 64 | 1 | ported | `gm_FindBuildingTypeByName` |
| `0x504ef0` | 59 | 1 | ported | `gm_ListTypesOfKind` |
| `0x505340` | 42 | 1 | ported | `gm_IsWarehouse` |
| `0x505d00` | 283 | 3 | ported | `gm_CollectBuildingResidents` |
| `0x506d50` | 80 | 3 | ported | `gm_GetStatRecord` |
| `0x506da0` | 80 | 3 | blocked | 0x6995d8: client's extra 6-byte record after the stat records (+3 more) |
| `0x506e70` | 112 | 1 | ported | `gm_EntityHasOffice` |
| `0x506ee0` | 144 | 1 | ported | `gm_SlotKindIsOneOf` |
| `0x506f70` | 96 | 15 | ported | `gm_GetGuildBuildingKind` |
| `0x506fd0` | 176 | 33 | ported | `gm_GetStatBuildingKind` |
| `0x507080` | 176 | 33 | ported | `gm_GetRangeBuildingKind` |
| `0x507130` | 400 | 33 | ported | `gm_GetSkillPair` |
| `0x5072c0` | 192 | 31 | ported | `gm_GetStatFirstItem` |
| `0x507380` | 128 | 0 | ported | `gm_GetItemGuild` |
| `0x507400` | 224 | 33 | ported | `gm_GetRangeStatId` |
| `0x507910` | 224 | 34 | ported | `gm_GetKindStatRange` |
| `0x5079f0` | 20 | 0 | ported | `gm_HasGuildHall` |
| `0x507ab0` | 80 | 0 | ported | `gm_RingGuildHallBell` |
| `0x507c30` | 224 | 34 | ported | `gm_MapItemPairRange` |
| `0x507ed0` | 57 | 5 | ported | `gm_BlendWeights` |
| `0x508220` | 96 | 5 | ported | `gm_GetKindRecord` |
| `0x508c30` | 179 | 0 | ported | `gm_ShuffleBytes` |
| `0x508cf0` | 133 | 0 | ruled out | portable, 0 DIR32; the port does not match the client's code generator (gm_RandomMod's int return vs the client's unsigned short), left out |
| `0x508d80` | 110 | 0 | ruled out | portable, 0 DIR32; the port does not match the client's code generator (as 0x508cf0), left out |
| `0x508e80` | 37 | 1 | ported | `gm_GetEntityAge` |
| `0x508eb0` | 208 | 4 | ported | `gm_GetOfficeRank` |
| `0x508f80` | 208 | 4 | ported | `gm_GetCouncilRank` |
| `0x509050` | 194 | 4 | ported | `gm_GetEntityDate` |
| `0x509120` | 176 | 0 | ported | `gm_GetBirthday` |
| `0x509480` | 240 | 0 | ported | `gm_CanMarry` |
| `0x5095d0` | 78 | 0 | ported | `gm_CountChildren` |
| `0x50b710` | 107 | 5 | ported | `gm_AmountToUnits` |
| `0x50b780` | 17 | 1 | ported | `gm_UnitsToAmountById` |
| `0x50b7a0` | 17 | 1 | ported | `gm_AmountToUnitsById` |
| `0x50b810` | 42 | 0 | ported | `gm_SumStoreCount` |
| `0x50b840` | 136 | 6 | ported | `gm_GetManufacturerRating` |
| `0x50bb50` | 96 | 2 | ported | `gm_GetSeasonPrice` |
| `0x50bbb0` | 96 | 6 | ported | `gm_GetHappinessFactor` |
| `0x50bc10` | 576 | 7 | ported | `gm_FormatPrice` |
| `0x50be50` | 102 | 1 | ported | `gm_ListBuildingStores` |
| `0x50bec0` | 100 | 2 | ported | `gm_ListProducts` |
| `0x50bf30` | 176 | 2 | ported | `gm_ListProductsAfter` |
| `0x50bfe0` | 9 | 0 | ported | `gm_GetEntityMood` |
| `0x50bff0` | 1184 | 13 | blocked | calls blocked client-only 0x4ee160 (+1 more) |
| `0x50c490` | 72 | 0 | ported | `gm_ListGuildHouses` |
| `0x50c4e0` | 112 | 9 | ported | `gm_GetBuildingLevel` |
| `0x50c550` | 128 | 1 | ported | `gm_HasLevelFor` |
| `0x50c5d0` | 306 | 9 | ported | `gm_GetBuildingWorth` |
| `0x50c710` | 186 | 3 | ported | `gm_SumProductPoints` |
| `0x50c7d0` | 86 | 1 | ported | `gm_SumTypePoints` |
| `0x50cad0` | 512 | 17 | ported | `gm_DaytimeMinutesBetween` |
| `0x50cce0` | 320 | 1 | ported | `gm_GetBuildingStock` |
| `0x50ce20` | 304 | 1 | ported | `gm_GetBuildingFoodStock` |
| `0x50d170` | 129 | 2 | ported | `gm_GetTypeProductValue` |
| `0x50d2f0` | 48 | 0 | ported | `gm_SumTreasury` |
| `0x50d320` | 64 | 1 | ported | `gm_GetSeasonTreasury` |
| `0x50d360` | 96 | 1 | ported | `gm_SumSlotTreasury` |
| `0x50d430` | 96 | 1 | ported | `gm_ResolveEntityRecord` |
| `0x50d4f0` | 64 | 0 | ported | `gm_ResolveEntitySlot` |
| `0x50ddf0` | 144 | 5 | ported | `gm_CalcFortuneTax` |
| `0x50de80` | 240 | 0 | ported | `gm_GetWorkshopStock` |
| `0x50dfa0` | 48 | 0 | ported | `gm_GetStoreItemField` |
| `0x50e170` | 128 | 0 | ported | `gm_GetStoreRoom` |
| `0x50e4a0` | 128 | 15 | ported | `gm_GetGuildHall` |
| `0x50e520` | 224 | 21 | ported | `gm_GetTypeGuild` |
| `0x50e600` | 112 | 3 | ported | `gm_GetWealthRank` |
| `0x50e670` | 170 | 2 | ported | `gm_GetRichestFive` |
| `0x50f950` | 48 | 1 | ported | `gm_GetRelationship` |
| `0x510170` | 112 | 2 | ported | `gm_HasNoGuildHouse` |
| `0x510400` | 104 | 0 | ported | `gm_CountHouseUpgradesA` |
| `0x510470` | 131 | 0 | ported | `gm_CountHouseUpgradesB` |
| `0x510500` | 76 | 0 | ported | `gm_CountHouseUpgradesC` |
| `0x510550` | 78 | 0 | ported | `gm_CountHouseUpgradesD` |


Blocked client-command senders. The measured server build had no client command queue. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x5017a0` 1408/11 `0x4c51f0` +11; `0x501fe0` 254/8 `0x4c61d0`; `0x505e20` 465/12 `0x4c4eb0` +9;
`0x506300` 123/1 `0x4c5620` +4; `0x507870` 156/0 `0x4c4510` +2; `0x508280` 528/2 `0x4c4510` +5;
`0x508490` 176/3 `0x4c4510` +3; `0x508540` 432/1 `0x4c4510` +3; `0x5086f0` 416/3 `0x4c4510` +5;
`0x508890` 400/1 `0x4c4510` +4; `0x508a20` 256/0 `0x4c4510` +2; `0x508b20` 272/1 `0x4c4510` +4;
`0x5099e0` 1504/24 `0x4c5f60` +12; `0x509fc0` 1872/40 `0x4c5f60` +13; `0x50d6d0` 1008/21 `0x4c5150` +3;
`0x50f910` 54/1 `0x4c51a0`; `0x50fe40` 176/5 `0x4c54c0` +2; `0x50fef0` 128/1 `0x4c4510` +2;
`0x50ff70` 377/5 `0x4c4510` +5;


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x502ec0` 54/1 `0x4be280`; `0x504c90` 288/1 `0x455350`; `0x5058b0` 255/6 `0x4379a0` +3;
`0x5059b0` 720/19 `0x5b1c90` +10; `0x506380` 1776/44 `0x5903d0` +3; `0x506a70` 64/0 `0x529160` +3;
`0x507540` 640/23 `0x64d4fa` +2; `0x507f10` 784/28 `0x5463a0` +3; `0x50d200` 154/2 `0x4f4830`;
`0x50d5d0` 102/1 `0x5463a0` +1; `0x50d640` 144/1 `0x5463a0` +1; `0x50db40` 336/5 `0x51af00` +2;
`0x50dd00` 228/0 `0x517c00`; `0x50ee80` 2256/104 `0x5463a0` +23; `0x50f750` 35/0 `0x472c30`;
`0x50f780` 384/18 `0x470820` +16; `0x50f900` 13/1 `0x471e30` +1; `0x50f980` 1072/43 `0x5c6270` +6;
`0x510260` 406/12 `0x4ff040` +1; `0x5105a0` 592/15 `0x64e790` +3; `0x5107f0` 35/1 `0x546b80` +2;
`0x510820` 224/5 `0x442d50` +1; `0x510930` 182/8 `0x4432d0` +7;


Blocked because the operand is client data also used outside the shared TUs. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x5039e0` 144/7 `0x7f3ee4` +2; `0x504f30` 1040/18 `0x774800`; `0x5053c0` 1264/3 `0xffffff`;
`0x5077c0` 161/8 `0x7746d4` +1; `0x507a10` 160/2 `0x774970` +1; `0x50a710` 208/5 `0x9a3825` +1;
`0x50b8d0` 169/5 `0x7747b4`; `0x50c830` 672/10 `0x696540` +2; `0x50e830` 1616/53 `0x7f3f24` +16;
`0x510900` 37/2 `0x7f3b40` +1;


Blocked: the cited operand had no proven server allocation. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x5091d0` 683/17 `0x699950` +5; `0x50e380` 260/2 `0x7d2034` +1; `0x50e780` 176/6 `0x7f3f0c` +3;


Blocked on another client-only function. Each item is TL VA, size, DIR32, and that function.

`0x505c80` 125/1 `0x5058b0`; `0x507e30` 55/1 `0x507f10`; `0x507e70` 88/5 `0x507f10`;
`0x50e720` 96/2 `0x50f980`; `0x50fdb0` 144/2 `0x50f980`; `0x5101e0` 128/3 `0x50b8d0`;

### loadsave.c

Client copies of server functions in the span (not listed): 9.

| TL VA | size | DIR32 | status | reason |
|---|---|---|---|---|
| `0x51ebc0` | 304 | 2 | ported | `ls_SaveObjects` |
| `0x51ecf0` | 1152 | 11 | ported | `ls_SaveBuildingEntityState` |
| `0x51f170` | 784 | 3 | ported | `ls_SaveDynamicEntities` |
| `0x520310` | 1360 | 2 | ported | `ls_SaveTownData` |
| `0x520860` | 128 | 4 | ported | `ls_SaveRelationships` |
| `0x521530` | 784 | 22 | blocked | command.c's four -1 dwords at 0x68a9d0, plain .data the server lacks (5f) (+14 more) |
| `0x524610` | 208 | 4 | ported | `ls_LoadRelationships` |


Blocked on a client engine callee. Each item is TL VA, size, DIR32, callee, and any further reasons.

`0x51e9d0` 151/5 `0x4432d0` +3; `0x51ea70` 169/4 `0x4432d0` +4; `0x51eb20` 147/4 `0x4432d0` +2;
`0x521840` 176/3 `0x5e8c00` +4; `0x521920` 1424/66 `0x40c070` +39; `0x5222a0` 234/10 `0x4432d0` +8;
`0x523710` 432/2 `0x403270`; `0x5238c0` 1920/27 `0x515540` +25;


Blocked because the operand is client data also used outside the shared TUs. Each item is TL VA, size, DIR32, operand, and any further reasons.

`0x51fd00` 48/1 `0x6b5c20`; `0x51fd30` 32/1 `0x6b5c20`; `0x51fd50` 624/2 `0x6b5c60`;
`0x51ffc0` 848/14 `0x6b5c20` +6; `0x5208e0` 1184/35 `0x99f5e0` +32; `0x520d80` 1344/23 `0x77e980` +15;
`0x5212c0` 352/4 `0x9a9660` +3; `0x521420` 272/8 `0x7728d4` +3; `0x5246e0` 1120/35 `0x99f5e0` +32;


Blocked on another client-only function. Each item is TL VA, size, DIR32, and that function.

`0x5224b0` 96/1 `0x510820`;

Blocked rows by first reason (count, client DIR32):

| reason | functions | DIR32 |
|---|---|---|
| callee absent: client command sender | 163 | 403 |
| callee absent: client engine | 84 | 827 |
| storage: client engine data | 37 | 386 |
| callee blocked | 20 | 80 |
| storage: no server allocation | 20 | 230 |
| storage: unmapped | 9 | 59 |
| storage: unproven bracket | 3 | 15 |
| CRT member | 2 | 91 |
