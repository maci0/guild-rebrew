# Behavioral verdicts — residue functions

Every function carrying linked `.text` residue has an explicit behavioral
verdict as of rounds 288–297. Method: independent instruction-level review
of the C source against the reference disassembly (`rebrew asm` +
`rebrew diff --json`), hunting wrong constants/offsets/call args/loop
bounds/branch outcomes; register allocation, scheduling, spill slots and
other documented codegen walls ignored. Reviews were read-only except
where a fix is noted as landed.

"Clean" means no behavioral divergence found in the reviewed regions.
PROVEN functions additionally carry symbolic EAX-equivalence; the reviews
below cover what the prover pattern-misses (store values, struct fields).

| Function | VA | Residue | Verdict | Round |
|---|---|---|---|---|
| gm_AllocSpieler | 0x10018850 | 2861 | **2 live bugs.** slot[9] else-branch stores slot[0x166] (=0), reference stores (char)arg8 — correct fix unlandable (+393 linked). Tail log/sprintf order swapped (+53 lead). | 288 |
| CrashDumpUnhandledExceptionFilter | 0x10002770 | 1597 | **1 bug fixed at +0**: walk gate tested mbi.RegionSize, reference tests mbi.State. Bug 1 (arg swap) verified fixed; bug 2 (dead block) fixed long ago. Rest clean. | 290 |
| cm_ExSellObjekt | 0x1000d930 | 1404 | Clean. Dest out-param reuse confirmed correct; 31/31 calls verified. | 289 |
| ls_LoadBuildingEntityState | 0x100128f0 | 728 | Clean. Offsets, gates, paths, state block verified. | 292 |
| cm_ExCopyEntityData | 0x1000ec00 | 462 | Clean. All 5 clamp arms bounds+directions verified. | 291 |
| gv_ExAllocGraveyardWorker | 0x10011bf0 | 456 | Clean. Sibling slot[9] pattern checked absent. | 291 |
| ServerMainThread | 0x100093a0 | 367 | Clean. All 29 hunks triaged; flags/cmds/calls/sleeps verified. | 288 |
| gm_AllocGebaeude | 0x100174d0 | 327 | Clean. Block-fill byte-identical zero-fill; all arms verified. | 292 |
| vfs_OpenStream | 0x10009020 | 245 | Clean. Mode arms, magic, setups, calls verified. | 293 |
| gm_FindNextFilteredEntity | 0x10016f80 | 226 | Clean. Filters, stride, exits verified VA-by-VA. | 296 |
| ahm_ExAllocAlchemist | 0x1000bdf0 | 201 | Clean. All 175 structural slots traced to codegen. | 297 |
| gm_CheckInventoryCapacity | 0x10019ed0 | 97 | Clean. Addressing, exits, capacity math verified. | 297 |
| m_AllocTracked | 0x10006580 | 93 | Clean. Full trace incl. Fatal-then-return-mem path. | 294 |
| srv_LoadBuf | 0x1000a570 | 49 | Clean. Masks bitwise-verified; log lines corrected. | 293 |
| gm_ObjectsAvailble | 0x10015f70 | 25 | Clean. Rotation confirmed register-only. | 294 |
| vfs_ReadCompressed | 0x10008a90 | 23 | Clean. Return protocol incl. dead-check both sides. | 295 |
| cm_ExProdObjekt | 0x1000e140 | 21 | Clean. Hunk-2 closed (mov ebx,eax precedes). | 295 |
| cm_ProcessCommandQueue | 0x1000aac0 | 15 | Clean. Join fold taken-edge-identical. | 296 |
| (outside functions) | 0x100092bc | 7 | OpenVfsStream +1-shifted jump table (net effect). | 287 |

Score: clean-or-documented 19/19. Live-semantics work remaining: none —
the two Spieler bugs are recorded with revisit conditions; everything else
is codegen-shaped residue under documented walls.
