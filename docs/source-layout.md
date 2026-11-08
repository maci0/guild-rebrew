# Source layout

Use one shared tree under `src/Develop/`, following attested `D:\Develop` paths.
Label inferred placement. A byte match does not establish the original TU.

| Location | Role |
| --- | --- |
| `DieGildeAddOn/game/` | Game units such as spiel, sim and aemter |
| `DieGildeAddOn/game/lc_location.c` | Merged inferred TU holding fcn_005acf90 (0x005acf90) and fcn_005e4c50 (0x005e4c50); placement inferred by subsystem convention |
| `DieGildeAddOn/game/main_OpenEngine.c`, `DieGildeAddOn/game/WinMain.c` | One file per function (GOLDTL 0x00538d00 and 0x00544c50). A merged `main.c` was split back on 2026-11-08 because the literal-pool string evidence did not support one native unit; `rebrew source split` output compared equal to the merged file (RELOC 907/907 and SIZE_MISMATCH 396/1845) |
| `DieGildeAddOn/game/aemter_c/amt_calc_zuenfte.c`, `amt_ExecGebaeudeBauen.c`, `amt_GetDesireByName.c` | One file per function (GOLDTL 0x004eab40, 0x004a4d90, 0x004a4200; GOLD 0x004a47c0 shares the `amt_GetDesireByName` definition). A merged `aemter.c` was split back on 2026-11-08 for the same reason; every row kept its status |
| `DieGildeAddOn/command/` | Command and lobby units |
| `DieGildeAddOn/auxillary/` | Plant subsystem; retain the attested spelling |
| `DieGildeAddOn/loadsave/` | Save/load code |
| `DieGildeAddOnServer/` | Server entry and shared declarations |
| `Units/` | Error, allocation, VFS, network, audio and renderer units |
| `Units/d2.v1/d2_tutorial.c` | Merged inferred TU holding fcn_005803f0 (0x005803f0), fcn_005805e0 (0x005805e0), fcn_005809d0 (0x005809d0), fcn_005809f0 (0x005809f0) and fcn_00580a00 (0x00580a00); placement inferred by subsystem convention |
| `Units/d2.v1/d2_SetBackgroundTexture.c`, `d2_SetForm.c`, `d2_Plot.c` | One file per function (GOLDTL 0x0046e7a0, 0x004727a0, 0x00472960; RELOC 140, 130 and 705 bytes). A merged `d2_windows.c` was split back on 2026-11-08 for the same reason |
| `Units/vfs/vfs_text.c` | Merged inferred TU holding fcn_0042d630 (0x0042d630) and fcn_0042d6b0 (0x0042d6b0); placement inferred by subsystem convention |
| `Units/vfs/vfs_io.c` | Merged inferred TU holding fcn_0042ed00 (0x0042ed00), fcn_0042f6d0 (0x0042f6d0) and fcn_00430870 (0x00430870); placement inferred by subsystem convention |
| `Units/Msx/msx_thread.c` | Merged inferred TU holding fcn_0041fa10 (0x0041fa10) and fcn_0041fad0 (0x0041fad0); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group.c` | Merged inferred TU holding d2_UpdateProgressBar (0x004e53e0) and d2_UpdateProgressBar (0x004e6e20) and fcn_004e6eb0 (0x004e6eb0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/gm_consolidated.c` | Merged inferred TU holding fcn_004aaa60 (0x004aaa60) and fcn_004aab30 (0x004aab30) and fcn_004aac00 (0x004aac00); placement inferred by subsystem convention |
| `DieGildeAddOn/game/he_consolidated.c` | Merged inferred TU holding fcn_004e7160 (0x004e7160) and fcn_004e71a0 (0x004e71a0); placement inferred by subsystem convention |
| `Unassigned/client_scene_transform.c` | Merged inferred TU holding fcn_004032b0 (0x00402a70) and fcn_004032b0 (0x004032b0) and fcn_00403300 (0x00403300) and fcn_00403300 (0x00402ac0); placement inferred by subsystem convention |
| `Unassigned/gold_client.c` | Merged inferred TU holding fcn_00519ad0 (0x00519ad0) and fcn_00519b80 (0x00519b80); placement inferred by subsystem convention |
| `DieGildeAddOn/game/he_handlung_a.c` | Merged inferred TU holding fcn_0050d5d0 (0x0050a150) and fcn_0050d5d0 (0x0050d5d0) and fcn_0050d640 (0x0050a1c0) and fcn_0050d640 (0x0050d640); placement inferred by subsystem convention |
| `DieGildeAddOn/game/dialog_5e3b.c` | Merged inferred TU holding fcn_005e3b70 (0x005e3b70) and fcn_005e40b0 (0x005d7580) and fcn_005e40b0 (0x005e40b0); placement inferred by subsystem convention |
| `Unassigned/client_state.c` | Merged inferred TU holding fcn_004125c0 (0x004125c0) and fcn_00412610 (0x00412610) and fcn_00412630 (0x00412630); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00423de0.c` | Merged inferred TU holding fcn_00423de0 (0x00423de0) and fcn_00423f20 (0x00423f20); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-0042a4a0.c` | Merged inferred TU holding fcn_0042a4a0 (0x0042a4a0) and fcn_0042a4d0 (0x0042bb40) and fcn_0042a4d0 (0x0042a4d0) and fcn_0042a510 (0x0042bb80) and fcn_0042a510 (0x0042a510); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-0042b370.c` | Merged inferred TU holding fcn_0042b370 (0x0042b370) and fcn_0042b3c0 (0x0042b3c0); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00445560.c` | Merged inferred TU holding fcn_00445560 (0x004495f0) and fcn_00445560 (0x00445560) and fcn_00445600 (0x00445600); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00456590.c` | Merged inferred TU holding fcn_00456590 (0x00456590) and fcn_00456630 (0x00456630); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-004acbb0.c` | Merged inferred TU holding fcn_004acbb0 (0x004acbb0) and fcn_004acee0 (0x004acee0) and fcn_004ad130 (0x004ad010) and fcn_004ad130 (0x004ad130); placement inferred by subsystem convention |
| `Unassigned/Unassigned-gm-004bbbd0.c` | Merged inferred TU holding fcn_004bbbd0 (0x004bbbd0) and fcn_004bbc30 (0x004bb720) and fcn_004bbc30 (0x004bbc30) and fcn_004bbce0 (0x004bbce0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/spiel_client_004ac.c` | Merged inferred TU holding fcn_004ac320 (0x004ac320) and fcn_004ac410 (0x004ac410); placement inferred by subsystem convention |
| `DieGildeAddOn/game/spiel_client_004b.c` | Merged inferred TU holding fcn_004b49a0 (0x004b4830) and fcn_004b49a0 (0x004b49a0) and fcn_004b49e0 (0x004b49e0) and fcn_004b4a20 (0x004b4a20); placement inferred by subsystem convention |
| `DieGildeAddOn/game/spiel_client_004bc.c` | Merged inferred TU holding fcn_004bc540 (0x004bc540) and fcn_004bc6b0 (0x004bc6b0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/spiel_client_004f.c` | Merged inferred TU holding fcn_004f25a0 (0x004f25a0) and fcn_04f24a0 (0x04f24a0) and fcn_004f45b0 (0x004f45b0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/gm_stat_range.c` | Merged inferred TU holding fcn_00506fd0 (0x00503fa0) and fcn_00506fd0 (0x00506fd0) and fcn_005072c0 (0x00504290) and fcn_005072c0 (0x005072c0); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group_00593ff0.c` | Merged inferred TU holding fcn_00593ff0 (0x00593ff0) and fcn_005941e0 (0x005941e0); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group_0059f190.c` | Merged inferred TU holding fcn_0059f190 (0x00595fb0) and fcn_0059f190 (0x0059f190) and fcn_0059f3e0 (0x00596200) and fcn_0059f3e0 (0x0059f3e0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/gm_consolidated_004cd860.c` | Merged inferred TU holding fcn_004cd860 (0x004cd860) and fcn_004cd990 (0x004cd990); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group_00535570.c` | Merged inferred TU holding d2_CreateScrollPerga (0x00535570) and d2_UpdateScrollPerga (0x00535630); placement inferred by subsystem convention |
| `DieGildeAddOn/game/gm_consolidated_004b4860.c` | Merged inferred TU holding fcn_004b4860 (0x004b46f0) and fcn_004b4860 (0x004b4860) and fcn_004b48d0 (0x004b4760) and fcn_004b48d0 (0x004b48d0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/he_consolidated_004e27b0.c` | Merged inferred TU holding fcn_004e27b0 (0x004e0e90) and fcn_004e27b0 (0x004e27b0) and fcn_004e2890 (0x004e2890) and fcn_004e2b40 (0x004e2b40); placement inferred by subsystem convention |
| `DieGildeAddOn/game/gm_consolidated_004ecaa0.c` | Merged inferred TU holding fcn_004ecaa0 (0x004ead20) and fcn_004ecaa0 (0x004ecaa0) and fcn_004ecb40 (0x004eadc0) and fcn_004ecb40 (0x004ecb40) and fcn_004ecc20 (0x004eaea0) and fcn_004ecc20 (0x004ecc20); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group_005b58a0.c` | Merged inferred TU holding d2_CreateGauge (0x005b58a0) and d2_UpdateGauge (0x005b59c0); placement inferred by subsystem convention |
| `Unassigned/error_client_0041d950.c` | Merged inferred TU holding fcn_0041d950 (0x0041d950) and ReportClientMessage (0x0041d9e0) and ReportClientMessage (0x004222b0) and fcn_0041da60 (0x00422330) and fcn_0041da60 (0x0041da60); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00423f60_00423f60.c` | Merged inferred TU holding fcn_00423f60 (0x00423f60) and fcn_00423f90 (0x00423f90); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00438840_00438840.c` | Merged inferred TU holding fcn_00438840 (0x0043a610) and fcn_00438840 (0x00438840) and fcn_00438920 (0x00438920); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00445680_00445680.c` | Merged inferred TU holding fcn_00445680 (0x00445680) and fcn_004456e0 (0x004456e0); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-004508a0_004508a0.c` | Merged inferred TU holding fcn_004508a0 (0x004508a0) and fcn_004509c0 (0x004509c0); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00456b10_00456b10.c` | Merged inferred TU holding fcn_00456b10 (0x00456b10) and fcn_00456c10 (0x00456c10); placement inferred by subsystem convention |
| `Unassigned/Unassigned-zlib-00464350_00464350.c` | Merged inferred TU holding fcn_00464350 (0x00467680) and fcn_00464350 (0x00464350) and fcn_004643e0 (0x00467710) and fcn_004643e0 (0x004643e0); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00473190_00473190.c` | Merged inferred TU holding fcn_00473190 (0x00473190) and fcn_004732c0 (0x004732c0); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-00498f50_00498f50.c` | Merged inferred TU holding fcn_00498f50 (0x00498f50) and fcn_00498fb0 (0x00498fb0); placement inferred by subsystem convention |
| `Unassigned/Unassigned-fcn_family-004ae170_004ae170.c` | Merged inferred TU holding fcn_004ae170 (0x004ae030) and fcn_004ae170 (0x004ae170) and fcn_004ae260 (0x004ae120) and fcn_004ae260 (0x004ae260); placement inferred by subsystem convention |
| `DieGildeAddOn/game/he_consolidated_004e4180.c` | Merged inferred TU holding fcn_004e4180 (0x004e4180) and fcn_004e4230 (0x004e4230); placement inferred by subsystem convention |
| `Unassigned/client_scene_transform_00402610.c` | Merged inferred TU holding fcn_00402610 (0x00402140) and fcn_00402610 (0x00402610) and fcn_004026f0 (0x00402220) and fcn_004026f0 (0x004026f0); placement inferred by subsystem convention |
| `Unassigned/ecmd_object_0040c6d0.c` | Merged inferred TU holding fcn_0040c6d0 (0x0040c6d0) and fcn_0040c740 (0x0040b820) and fcn_0040c740 (0x0040c740) and fcn_0040c780 (0x0040b860) and fcn_0040c780 (0x0040c780); placement inferred by subsystem convention |
| `Unassigned/gold_misc_00428ce0.c` | Merged inferred TU holding fcn_00428ce0 (0x00428ce0) and fcn_00428cf0 (0x00428cf0); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group_004e15c0.c` | Merged inferred TU holding fcn_004e15c0 (0x004e15c0) and fcn_004e16e0 (0x004e16e0) and fcn_004e1900 (0x004e1900); placement inferred by subsystem convention |
| `Units/d2.v1/d2_group_005c5b10.c` | Merged inferred TU holding fcn_006abb00 (0x006abb00) and fcn_005c5b10 (0x005c5b10) and fcn_005c5da0 (0x005c5da0); placement inferred by subsystem convention |
| `DieGildeAddOn/game/spiel_grp_004ccf10.c` | Merged inferred TU holding fcn_004ccf10 (0x004ccf10) and fcn_004cd090 (0x004cd090); placement inferred by subsystem convention |
| `Unassigned/ecmd_object_0040e9c0.c` | Merged inferred TU holding ecmd_SetAngle (0x0040e9c0) and ecmd_MoveObject (0x0040db30) and ecmd_MoveObject (0x0040ea40) and ecmd_RotateObject (0x0040dbb0) and ecmd_RotateObject (0x0040eac0) and ecmd_MoveObjectRelative (0x0040dc30) and ecmd_MoveObjectRelative (0x0040eb40) and ecmd_RotateObjectRelative (0x0040dcb0) and ecmd_RotateObjectRelative (0x0040ebc0) and ecmd_ReplaceObject (0x0040ddb0) and ecmd_ReplaceObject (0x0040ecc0); placement inferred by subsystem convention |
| `Unassigned/gold_misc_004c3b30.c` | Merged inferred TU holding fcn_004c3b30 (0x004c3b30) and fcn_004c3b40 (0x004c3b40); placement inferred by subsystem convention |

| `Unassigned/` | Bodies whose original module/TU remains unresolved |

## Consolidation not done

| Candidate | Reason not merged | What clears it | Receipt |
| --- | --- | --- | --- |
| Error unit into client `GOLDTL.Error.c` | Client defines `g_log_level_table[12]` and `g_log_format_table[384]` while shared header declares `[3]` and `[96]`; `g_log_default_name` size also differs; merged TU fails with C2369 | Contract and storage reconciliation before retry | `.scratch/consolidation-2026-11-05/slot-2/merge-error-progress.md` |
| d3 registry pair `0x004375e0` + `0x00437710` | `0x00437710` has inline assembly with a codegen wall blocker and no reviewed original assembly record | Documented assembly record per AGENTS.md, or a C form | `.scratch/consolidation-2026-11-05/slot-2/merge-d3reg-progress.md` |
| VFS `vfs.c` destination for `0x0042ed00`, `0x0042f6d0`, `0x00430870` | `vfs.c` has about 25 definitions with no function row and no VA; merge tool refuses an unbound destination; these three were merged into `vfs_io.c` instead | VA and ADDRESS anchors for each unbound `vfs.c` definition, or split `vfs.c` so destination holds only bound definitions | `.scratch/consolidation-2026-11-05/slot-2/merge-vfsfinish-progress.md` |
| Msx `0x0041fc80` and `0x00420530` into `msx.c` | Plain merge appends instead of interleaving; `--guarded-interleave` needs include closure, now overridable with `--accept-unresolved-includes`, then a complete conflict free organization review which needs raw links | Client raw link exists, then complete conflict free organization review | `.scratch/consolidation-2026-11-05/slot-2/merge-msx2-progress.md`, `.scratch/consolidation-2026-11-05/slot-2/merge-msxnative-progress.md` |
| Msx `0x00420210`, `0x0041fd30`, `0x0041fbd0`, `0x004200d0` stay out of `msx.c` | `0x00420210` is `SIZE_MISMATCH` with retired GOLD binding; `0x0041fd30` file defines `fcn_004c3140` under raw reference identity; `0x0041fbd0` and `0x004200d0` are TL only | Resolve size mismatch and retired binding, resolve raw reference identity, and keep TL only bodies out of shared `msx.c` | `.scratch/consolidation-2026-11-05/slot-2/merge-msxnative-progress.md` |
| `command.c`, `cutscene.c`, `ch_script.c`, `character.c`, `d3_object.c` singletons | Each destination is already consolidated; plain merge refuses with `inside a preprocessor conditional or did not parse` for `cm_ChkJoinLeaveElection`, `cut_FreeAllCutscenes`, `WalkToDummy` | Guarded writer for preprocessor conditional bodies | `.scratch/consolidation-2026-11-05/slot-2/merge-survey.md` |
| `character.c` plus `ch_queue.h` | `ch_queue.h` is a header, not a merge input; open item is TL placeholder prototype conflict at `fcn_00540020` | Coordinated bind and declaration repair for placeholder | `.scratch/consolidation-2026-11-05/slot-2/merge-survey.md` |
| `d3_DisposeObject` into `d3_object.c` | Dry run exit 0 but organization review reports foreign GOLD definitions for TL only body | Original TU evidence and target exclusion for TL only body | `.scratch/consolidation-2026-11-05/slot-2/merge-survey.md` |
| Msx shutdown and setter extras | Mix TL only and GOLD files with different storage expressions and 2 unbound files | Guarded interleaved merge plus evidence for GOLD setter and shutdown bindings | `.scratch/consolidation-2026-11-05/slot-2/merge-survey.md` |
| Wave-2 transaction driver groups skipped because the proposed file name collided (17 groups in run 2 use a VA-suffixed name; run 1 shows the same collision as 32 skipped counting retries) | Proposed output file already existed, so the merge was skipped before any write | Re-run with a unique output name for each group, as run 2 did with VA-suffixed names, and confirm no row or file exists for that name first | `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-results-run1.jsonl`, `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-results.jsonl` |
| Wave-2 transaction driver groups restored after a failed after-check (5 groups in run 1 and 5 in run 2) | `rebrew test` after the merge returned an error key (exit 2), so the driver restored the backup exactly | Fix the merged compile error shown in the driver scratch for that group, then re-run the group through backup, before-test, apply, canary test, after-test and register dry-run | `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-results-run1.jsonl`, `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-results.jsonl`, `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-scratch/` |
| Wave-2 transaction driver groups whose before-test returned no real result (before-test exit 1 for a member file) | The driver skipped the group because a member failed `rebrew test` before any merge was attempted | Repair or re-verify the failing member file so `rebrew test` returns a real status and match count, then re-run the group | `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-results-run1.jsonl`, `.scratch/consolidation-2026-11-05/slot-2/wave2m/driver-results.jsonl` |

Shared unavailable gates for merged files `vfs_text.c`, `vfs_io.c`, `msx_thread.c`: no native source path witness for the merged files, system header include closure unknown, no raw link so `organize check` was not run, so whole image equality is not claimed.


Reconstructed filenames and private headers may be inferred even when the parent
unit is attested. Native paths, diagnostics, counterparts and dependencies provide
placement evidence; automatic address clustering alone does not.

## Move, merge or split

Use `rebrew source organize review` to inspect all-target providers, native order,
compiler context and storage instances. Preserve baselines, includes, declaration
order and flags. Update managed identities through Rebrew writers, then compare
complete objects/operands and rebuilt images with `source organize check`.

Do not split a native sequence merely because recovered definitions currently
live in different files. A shared file may contain target-specific definitions;
the same symbol spelling can also name independent functions.

Headers declare objects; C definitions or selected library members allocate them.
Keep types in the owning subsystem header or private source and bind stable type
IDs through `rebrew types bind`. Use `Units/d3/d3_object.h` for current D3 layouts.

Native unit witnesses and past moves are indexed below. Their historical body
counts and source paths are not a current inventory.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

Original notebook: `docs/source-layout.md` in the [documentation archive](goal-history.md#full-notebooks).

| Historical section | Referenced hex values |
| --- | --- |
| <a id="moving-sources"></a>Moving sources | `0x0045f6c0` |
| <a id="msx-and-d3-placement-october-11"></a>MSX and D3 placement, October 11 | `0x0041fc10`, `0x0041fd70`, `0x0041fe10`, `0x00420120`, `0x004205e0`, `0x00420650`, `0x00420690`, `0x00420700`, `0x00420760`, `0x00420780`, `0x00420840`, `0x00423930`, `0x00423a90`, `0x00423b30`, `0x00423df0`, `0x00424250`, `0x004242c0`, `0x00424300`, `0x00424370`, `0x004243d0`, `0x004243f0`, `0x004244b0`, `0x00438780`, `0x00478860`, `0x00f8aae0`, `0x014611a0`, `0x014cc360` |
| <a id="character-subsystem-placement-2026-10-11"></a>Character subsystem placement (2026-10-11) | - |
| <a id="shared-character-scene-and-script-helpers-2026-10-11"></a>Shared character scene and script helpers (2026-10-11) | `0x00402540`, `0x00402aa0`, `0x004033c0`, `0x00403bc0`, `0x00406790`, `0x00407330`, `0x0040c4f0`, `0x0040d410` |
| <a id="d3-type-identities-and-full-byte-extents-2026-10-11"></a>D3 type identities and full byte extents (2026-10-11) | - |
| <a id="shared-client-allocator-helper-checkpoint-2026-10-11"></a>Shared client allocator helper checkpoint (2026-10-11) | - |
| <a id="client-placement-views-goal75-2026-10-17"></a>Client placement views (Goal75, 2026-10-17) | `0x00442d50`, `0x00447300`, `0x004cbe5a`, `0x004cbefc`, `0x004cc9da`, `0x004cca7c`, `0x0058fa00`, `0x0058fa60`, `0x0058fc80`, `0x0058fd20`, `0x005982d0`, `0x00598330`, `0x00598550`, `0x005985f0` |
| <a id="scene-command-declaration-boundary-goal80-2026-10-17"></a>Scene command declaration boundary (Goal80, 2026-10-17) | `0x00525b40` |
| <a id="network-local-address-placement-2026-11-01"></a>Network local-address placement (2026-11-01) | `0x00420d20` |
| <a id="entity-lookup-and-pricing-placement-2026-11-01"></a>Entity lookup and pricing placement (2026-11-01) | `0x00508e40`, `0x0050b980` |
| <a id="line-renderer-placement-2026-11-01"></a>Line renderer placement (2026-11-01) | - |
| <a id="gold-directdraw-dialog-placement-candidate-2026-11-01"></a>Gold DirectDraw dialog placement candidate (2026-11-01) | `0x0041c830` |
| <a id="shared-client-table-search-2026-11-01"></a>Shared client table search (2026-11-01) | `0x004f36e0`, `0x004f5810` |
| <a id="office-slot-type-review-2026-11-01"></a>Office-slot type review (2026-11-01) | `0x1000b880`, `0x1000b8be`, `0x1000b90a` |
| <a id="client-crime-counter-2026-11-01"></a>Client crime counter (2026-11-01) | - |
| <a id="client-cutscene-readiness-2026-11-01"></a>Client cutscene readiness (2026-11-01) | `0x004c69c0`, `0x004c7550`, `0x004cd590` |
| <a id="client-cutscene-execution-2026-11-01"></a>Client cutscene execution (2026-11-01) | `0x004cca10`, `0x004cd590` |
| <a id="client-cutscene-record-lookup-2026-11-01"></a>Client cutscene record lookup (2026-11-01) | `0x004e50a0`, `0x004e5120`, `0x004e5180`, `0x004e6a30`, `0x004e6ab0`, `0x004e6b10` |
| <a id="gold-queue-state-lookup-candidate-2026-11-01"></a>Gold queue-state lookup candidate (2026-11-01) | `0x004c3480`, `0x004c350f`, `0x004c3ae0`, `0x004c3b02`, `0x00519b17`, `0x00f31160`, `0x00f31166`, `0x00f81160`, `0x00f81166` |
| <a id="shared-client-cutscene-record-candidate-2026-11-01"></a>Shared client cutscene-record candidate (2026-11-01) | `0x00451840`, `0x00453e70`, `0x004e50a0`, `0x00519ad0`, `0x0052ae70`, `0x005305a0` |
| <a id="gold-d3-camera-position-candidate-2026-11-01"></a>Gold D3 camera-position candidate (2026-11-01) | `0x0042ea90`, `0x0042ebb4`, `0x004379a0`, `0x00438a80`, `0x00438af0`, `0x00438d40`, `0x00438e60`, `0x0043b670`, `0x0043b6b0`, `0x0043b6e0`, `0x0043b790`, `0x0045cdf0`, `0x0045d680`, `0x0045d7e6`, `0x00531c2c`, `0x005fb5b0`, `0x0067a370`, `0x00fb9598`, `0x00fb98f4`, `0x00fc2700`, `0x00fc28f4`, `0x00fc52f0` |
| <a id="vfs-finish-files-consolidation-candidate-2026-11-02"></a>VFS finish-files consolidation candidate (2026-11-02) | `0x0042edf0`, `0x0042ee30`, `0x0042f5c0`, `0x0042f600`, `0x0042f620`, `0x005eab80`, `0x00633400`, `0x00633408`, `0x0065f220`, `0x006b7fe0`, `0x006b7fe8`, `0x0087b3c0`, `0x00b46741` |
| <a id="vfs-archive-scanner-candidate-2026-11-02"></a>VFS archive-scanner candidate (2026-11-02) | `0x0042fb20`, `0x00430130` |
| <a id="gold-texture-wrapper-candidate-2026-11-02"></a>Gold texture-wrapper candidate (2026-11-02) | `0x00448200` |
| <a id="vfs-case-normalization-contract-2026-11-02"></a>VFS case-normalization contract (2026-11-02) | `0x0042e520`, `0x0042ecf0` |
| <a id="client-image-name-lookup-candidate-2026-11-02"></a>Client image-name lookup candidate (2026-11-02) | `0x0045a2e0`, `0x0045a3a0`, `0x0045a521`, `0x0045a666`, `0x0045db30`, `0x0045dbf0` |
| <a id="client-task-queue-removal-candidate-2026-11-02"></a>Client task-queue removal candidate (2026-11-02) | `0x004047a0`, `0x004050c0`, `0x00406210`, `0x00406db0` |
| <a id="shared-client-game-matrix-declarations-2026-11-02"></a>Shared client game-matrix declarations (2026-11-02) | - |
| <a id="character-action-queue-consolidation-2026-11-02"></a>Character action queue consolidation (2026-11-02) | `0x00402aa0`, `0x00404810`, `0x004048b0`, `0x00405130`, `0x00405180`, `0x004051d0`, `0x00405350`, `0x004053a0`, `0x00405400`, `0x00405460`, `0x004054b0`, `0x00405510`, `0x00405610`, `0x004061a0`, `0x00406580` |

</details>
