Current gate checkpoint: original full baseline13849 is completed/closed (exit2; server316/316, TL3263/3676, GOLD1980/2510, zero4109 drift). Upstream mixed FUNCTION/LIBRARY stack fix has257 focused passes; isolated full suite73867 is live and must pass before applying the eleven-file sound patch. Then obtain a fresh fixed-tool baseline and full after comparison. Gold5e3d3d is stock LIBCMT ___sbh_find_block, not a game function to reimplement; its broken local copy is a separate follow-up. Details in HANDOFF and .scratch/goal-code-marker-stack/.

Current staged update: request132/132 and constructor150/150; symbolic scale view with unresolved owner, canonical voice helper, eleven-file patch. Both reference helper bodies are29 bytes plus3 NOPs, scratch EXACT29/29. GOLD request132/132 is validated with explicit native slots; GOLD constructor148/150 differs at game-object+0x20c vs TL+0x210 and must wait for layout repair. These changes are not yet canonical. Baseline13849 remains live; finish SAME run, persist helper29 through CLI after patch application, then full all-target after gates. See HANDOFF and .scratch/goal-shared-sound/.

Current pending checkpoint: ten-file shared SOUND_SOURCE patch plus constructor0x418c80 is staged, not applied. Constructor scratch RELOC150/150 (double temporary restores store order), allocator63/63 in both clients and typed create caller91/91; final record layout assertions pass both profiles. The full unchanged-tree baseline session13849 remains live with zero4109 input drift; finish SAME job before applying, then full all-target after tests and comparison (TL total3676→3677). Canonical sources/header are unchanged. Receipts .scratch/goal-shared-sound/, detailed next steps in HANDOFF.

Latest alias/extent checkpoint: pair-copy 0x407760 has corrected overlapping-buffer ordering but remains SIZE_MISMATCH 18/163 vs 159; one concrete VEX case agrees with the reference, not a general proof. Shared height neighbor is RELOC 326/326 in both clients after excluding ten GOLD NOPs. Sound request remains NEAR 124/132 after removing stale 144-byte extent. Shared sound type consolidation and both matching walls remain open. Raw server bytes unchanged; receipts .scratch/goal-sound-order/.

Current 2026-10-04 first passes: CharacterSitting / CharacterSitsDown remain 52-byte objects against 56-byte references; animation control 0x405540 remains 102 vs 94; task removal 0x4050c0 is NEAR 98/110 with two memset scheduling ties. Four recovered bodies still need byte matching; no new GOLD import or complete-file improvement. Bounded probes and the terminal 12x8 GA are retired in codegen-walls50/51 and .scratch/goal-character/.

Latest 2026-10-04 checkpoint: TL animation builder 0x00406510 is now RELOC 75/75; client sound setter renamed through target-isolated CLI, shared TL/GOLD RELOC 44/44. No eligible GOLD builder import. The builder legacy name remains blocked by ambiguous mixed-target references, recorded upstream as a missing feature. Full Rebrew gate 10838 passed / 32 skipped; current source hashes and all-target lint pass. These object checks do not reduce the unchanged server raw-file gap or establish linked-client identity.

# Remaining native link work, measured 2026-10-03

Current production is the normal native CMake output `build/server.dll`,
SHA256 `ff81a459a20dbdbbf3bebe76128ec8bdd80b80bd59bf238cc2db936f12941935`.
The untouched reference remains `3cc2ce90...09d1`, read-only. Fresh ordinary CLI
verification passes all 316 checks, 41 EXACT and 275 RELOC: 260 game functions
and 56 compiled library checks, with no failures or size divergences. All three targets
lint with zero warnings/errors. The independent objective check exits one:
complete-file identity remains false.

Production is 270336 bytes against 286720, with 2530 differing overlapping
bytes and 16384 missing bytes. File agreement is 93.4%. All 3499 live HIGHLOW
sites agree; every differing `.text` byte is in one of those fields. Stock CRT
code and storage remain supplied by unchanged libraries.

| Region | Differing overlapping bytes | Remaining size disagreement |
| --- | ---: | --- |
| Headers / other | 96 | None |
| `.text` | 2094 | None |
| `.rdata` | 286 | None |
| `.data` | 54 | Virtual size 3604 bytes short |
| `.reloc` | 0 | Virtual size 15108 bytes short; raw extent 16384 bytes short |

The next work needs evidence for the original game storage owners and complete
extents, original native import selection/order, and relocation reservation.
Import identities and hints agree, but 51 IAT slots are displaced. The live
relocation directory is 7404 bytes in both files; equal sites do not explain
the original larger reserved extent. Existing section-span annotations and
zero-filled virtual ranges do not establish source allocations.

Both native images put PE at `0xe8` with timestamp `0x3fdd84a0` and checksum
zero. Their Rich ledgers still differ; the equal PE offset is a measured
layout improvement, not producer identity. Product/build/count evidence:

| Product / build | Production count | Reference count |
| --- | ---: | ---: |
| 1 / 0 | 109 | 126 |
| 4 / 8447 | 1 | 1 |
| 10 / 8047 | 113 | 124 |
| 10 / 8966 | 126 | 37 |
| 11 / 8047 | 1 | 1 |
| 12 / 7291 | 1 | 6 |
| 14 / 7299 | 22 | 22 |
| 19 / 8034 | 9 | 9 |

Original TU ownership and discarded native input provenance remain unresolved.
The linked ledger is not permission to add artificial producers or patch headers.
Current continuation can run Docker 29.8.1. The configured client Processor
Pack image has been built through `rebrew toolchain build msvc-6.0-sp5-pp`.
A fresh ordinary server `rebrew verify --full --jobs 4` passes 316/316 checks:
260 game functions plus 56 compiled library bodies, with zero failures and
size divergences. These checks establish function agreement under relocation
masking; they do not change the raw production DLL or prove file identity.
Reports are `.scratch/goal-server-verify-current.{json,log}`.

A fresh complete input census bounds the reservation problem independently of
the missing storage. The 127 direct inputs and 137 selected stock CRT members
contain 4167 DIR32 records; 109 loaded import members make 4276 potential
fixups. The measured normal LINK path reserves 51312 bytes, capped by that
counter despite the 5990-page span. Under the same path, the reference's 66420
reserved bytes require 5535 potential fixups: 1259 original fixups have no
identified owners. Adding storage would not repair the capped counter.

Current COFF-to-reference operand votes inspect 3132/3140 CODE HIGHLOW sites.
The eight remaining sites belong to the seven WinSock thunks and RtlUnwind.
Stock CRT sections have no conflicting base votes; their ordinary BSS has
979 logical bytes. The existing 12-byte pool/count/counter section is the sole
source conflict: the pool implies original base `0x10034670`, while count and
counter imply `0x10034674`. That four-byte disagreement does not prove a
larger pool allocation. The prior storage and broad import-root controls do
not supply a new valid prediction of complete-file gain.

No native control is ready from these facts. The evidence blocker is original
input/TU/discarded-contribution provenance or independently established extent
and import-selection evidence; host Docker access is available. Read-only
reproduction: `.venv/bin/python .scratch/native-current-input-evidence/census.py`.
Its complete input barrier, member census and owner votes are preserved in
`.scratch/native-current-input-evidence/` without changing source, metadata,
stock archives, production or reference.

Current evidence: `.scratch/native-early-game-counters/remaining-comparison.json`,
`objective-final.txt`, `verify-scopes/aggregate/{report,receipt}.json` and
`status-final.json`. See [HANDOFF.md](HANDOFF.md) for accepted production changes
and [msvc6-link-layout.md](msvc6-link-layout.md) sections 82–87 for the measured
controls. The bounded pool trace confirms correct current names/addresses
but supplies no original allocation/TU proof; its exact missing evidence is
recorded in HANDOFF. C-shapes257 records the separate incorrect thiscall hint.
Next unused pattern numbers remain C258 / LINK88.

## Historical split-link report, 2026-09-28

The following 437/543 report and its function list describe the old split link.
They are retained as historical evidence and are superseded by the native
production measurements above.

## A. reversing (52 annotated functions whose bytes we do not reproduce)

va           size   status  source
0x10016760   1392   RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_AllocObjekt.c
0x100174d0   1088   RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c
0x10012eb0   896    RELOC   src/Develop/DieGildeAddOn/loadsave/loadsave_c/ls_LoadDynamicEntities.c
0x10014260   896    RELOC   src/Develop/DieGildeAddOn/loadsave/loadsave_c/srv_RecvGame.c
0x1000a570   752    RELOC   src/Develop/DieGildeAddOnServer/server_c/srv_LoadBuf.c
0x10017c40   752    RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_AllocRaum.c
0x10006580   672    RELOC   src/Develop/Units/m_alloc/m_alloc_c/m_AllocTracked.c
0x10006990   612    RELOC   src/Develop/Units/m_alloc/m_alloc_c/m_ReportGroupInfo.c
0x1000a080   608    RELOC   src/Develop/DieGildeAddOnServer/server2.c
0x10010d10   576    RELOC   src/Develop/DieGildeAddOn/game/gv_UpgradeField.c
0x10014070   496    RELOC   src/Develop/DieGildeAddOn/loadsave/loadsave3.c
0x10016290   464    RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_NextEntityQueryMatch.c
0x10009e60   432    RELOC   src/Develop/DieGildeAddOnServer/server2.c
0x10019720   400    RELOC   src/Develop/DieGildeAddOn/game/spiel622.c
0x10019ed0   400    RELOC   src/Develop/DieGildeAddOn/game/spiel622.c
0x1000b040   372    RELOC   src/Develop/DieGildeAddOnServer/server4.c
0x10016f80   352    RELOC   src/Develop/DieGildeAddOn/game/spiel_dumpD.c
0x1000f1a0   336    RELOC   src/Develop/DieGildeAddOn/command/command_c/cm_ChainRecordLookup.c
0x10010710   320    RELOC   src/Develop/DieGildeAddOn/game/friedhof_logic_c/FindSlotEntryFiltered.c
0x10016460   320    RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_ff_Objekt.c
0x10017b00   320    RELOC   src/Develop/DieGildeAddOn/game/spiel6.c
0x100170e0   304    RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_StartFilteredEntitySearch.c
0x10006c00   283    RELOC   src/Develop/Units/m_alloc/m_alloc2.c
0x10015e90   224    RELOC   src/Develop/DieGildeAddOn/game/spiel.c
0x10017400   202    RELOC   src/Develop/DieGildeAddOn/game/spiel5.c
0x10015cf0   194    RELOC   src/Develop/DieGildeAddOn/game/spiel.c
0x10006820   192    RELOC   src/Develop/Units/m_alloc/m_alloc.c
0x100179b0   192    RELOC   src/Develop/DieGildeAddOn/game/spiel6.c
0x1000ba30   179    RELOC   src/Develop/DieGildeAddOn/game/aemter2.c
0x100068e0   162    RELOC   ?
0x10003520   160    RELOC   src/Develop/Units/Error/Error_c/ErrorModule2.c
0x10015460   160    RELOC   src/Develop/DieGildeAddOn/game/sim.c
0x1000b990   157    RELOC   src/Develop/DieGildeAddOn/game/aemter2.c
0x1000a860   144    RELOC   src/Develop/DieGildeAddOnServer/server_c/ProcessSendData.c
0x100104a0   144    RELOC   src/Develop/DieGildeAddOn/command/command_c/cm_GetBuildingStatCount.c
0x100035c0   128    RELOC   ?
0x1000a010   112    RELOC   ?
0x1000a2e0   96     RELOC   src/Develop/DieGildeAddOnServer/server2.c
0x100034c0   83     RELOC   src/Develop/Units/Error/Error_c/ErrorModule2.c
0x10017ab0   80     RELOC   ?
0x10019a20   74     RELOC   ?
0x10009350   68     RELOC   src/Develop/DieGildeAddOnServer/server.c
0x10015dc0   64     RELOC   src/Develop/DieGildeAddOn/game/spiel.c
0x10017a70   64     RELOC   ?
0x10015cb0   57     RELOC   ?
0x1000b820   48     RELOC   ?
0x1000b850   48     RELOC   ?
0x10017210   48     RELOC   src/Develop/DieGildeAddOn/game/spiel5.c
0x1001a110   48     RELOC   src/Develop/DieGildeAddOn/game/gm_RandomQuadratic.c
0x100165a0   37     RELOC   src/Develop/DieGildeAddOn/game/spiel_c/gm_AllocateObjectSlot.c
0x1000ef90   26     RELOC   src/Develop/DieGildeAddOn/command/command_c/cm_ChainAssignId.c
0x1000f080   26     RELOC   src/Develop/DieGildeAddOn/command/command_c/cm_AssignSequenceCounter.c

## B. membership (44 functions we never link)

va           size   source
0x1001d869   777    (library)
0x1001be4b   368    (library)
0x1001fcc6   306    (library)
0x1001ba71   239    (library)
0x10022cd0   208    (library)
0x1001b12f   204    (library)
0x1002146d   203    (library)
0x1001f9c0   185    (library)
0x1001db72   177    (library)
0x1001d425   168    (library)
0x1001a6a1   165    (library)
0x1001fa79   153    (library)
0x1002377b   151    (library)
0x1001f0ff   147    (library)
0x10022107   137    (library)
0x100202e1   127    (library)
0x10022340   125    (library)
0x10020265   124    (library)
0x100207b8   120    (library)
0x1001b0c0   111    (library)
0x100213fe   111    (library)
0x10022f83   110    (library)
0x1001cbb5   101    (library)
0x1001e8b4   101    (library)
0x1001eec1   101    (library)
0x1001bc04   93     (library)
0x1002075f   89     (library)
0x100236bc   88     (library)
0x1001cb61   84     (library)
0x10021ec0   74     (library)
0x1001d4cd   72     (library)
0x1002071b   68     (library)
0x10020360   66     (library)
0x10022f44   63     (library)
0x1001fdf8   57     (library)
0x10020915   46     (library)
0x1001ac43   45     (library)
0x1001d515   43     (library)
0x10020423   41     (library)
0x10021f3d   41     (library)
0x100220eb   28     (library)
0x1001d238   27     (library)
0x1001a7f7   18     (library)
0x1001a7ee   9      (library)
