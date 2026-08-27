# Reversed Functions Catalog

Total: 556/563 functions cataloged (327 exact, 184 reloc-normalized, 4 near-matching, 5 stubs)  
Coverage: 96.3% of .text section (136167/141382 bytes)


## SERVER (626 functions)

| VA | Size | Name | Symbol | Flags | Match | File |
|-----|------|------|--------|-------|-------|------|
| 0x10001000 | 302B | adler32 | adler32 |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001130 | 179B | SendBroadcastPacket | _SendBroadcastPacket |  | FUNCTION/RELOC | Units/net/broadcast.c |
| 0x100011F0 | 309B | crc32 | _crc32 | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/unknown/crc32.c |
| 0x100011F0 | 309B | vfs_Crc32Update | vfs_Crc32Update |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001330 | 505B | deflateInit2_ | deflateInit2_ |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001530 | 115B | deflateReset | deflateReset |  | LIBRARY/EXACT | library_zlib.h |
| 0x100015B0 | 685B | deflate | deflate |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001860 | 47B | putShortMSB | putShortMSB |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001890 | 114B | flush_pending | flush_pending |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001910 | 170B | deflateEnd | deflateEnd |  | LIBRARY/EXACT | library_zlib.h |
| 0x100019C0 | 147B | lm_init | lm_init |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001A60 | 343B | deflate_stored | deflate_stored |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001BC0 | 290B | fill_window | fill_window |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001CF0 | 113B | read_buf | read_buf |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001D70 | 813B | deflate_fast | deflate_fast |  | LIBRARY/EXACT | library_zlib.h |
| 0x100020A0 | 367B | longest_match | longest_match |  | LIBRARY/EXACT | library_zlib.h |
| 0x10002210 | 1066B | deflate_slow | deflate_slow |  | LIBRARY/EXACT | library_zlib.h |
| 0x10002640 | 290B | DispatchLogOutput | _DispatchLogOutput |  | FUNCTION/RELOC | Units/Error/Error.c |
| 0x10002770 | 2115B | CrashDumpUnhandledExceptionFilter | _CrashDumpUnhandledExceptionFilter@4 | /O2 /Gd | FUNCTION/PROVEN | Units/Error/Error_c/CrashDumpUnhandledExceptionFilter.c |
| 0x10002FC0 | 376B | EmitCrashModuleLine | _EmitCrashModuleLine | /O2 /Gd | FUNCTION/STUB | Units/Error/Error_c/EmitCrashModuleLine.c |
| 0x10003140 | 33B | GetDebugRecordByIndex | _GetDebugRecordByIndex |  | FUNCTION/EXACT | Units/Error/Error_c/ErrorModule.c |
| 0x10003170 | 235B | check_memory_protection | _check_memory_protection |  | FUNCTION/RELOC | Units/Error/Error_c/ErrorModule.c |
| 0x10003260 | 183B | AnalyzeInstruction | _AnalyzeInstruction |  | FUNCTION/EXACT | Units/Error/Error_c/ErrorModule.c |
| 0x10003320 | 404B | InitializeLogAndErrorHandler | _InitializeLogAndErrorHandler | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | Units/Error/Error_c/InitializeLogAndErrorHandler.c |
| 0x100034C0 | 83B | ShutdownLogAndErrorHandler | _ShutdownLogAndErrorHandler | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | Units/Error/Error_c/ErrorModule2.c |
| 0x10003520 | 160B | ReportFatalError | _ReportFatalError |  | FUNCTION/RELOC | Units/Error/Error_c/ErrorModule2.c |
| 0x100035C0 | 119B | ReportMessage | _ReportMessage |  | FUNCTION/RELOC | Units/Error/Error_c/ErrorModule2.c |
| 0x10003640 | 132B | LogMessageInternal | _LogMessageInternal |  | FUNCTION/RELOC | Units/Error/Error_c/ErrorModule2.c |
| 0x100036D0 | 332B | check_header | check_header |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003820 | 114B | vfs_GetByte | _vfs_GetByte |  | FUNCTION/RELOC | Units/vfs/vfs.c |
| 0x100038A0 | 177B | vfs_CloseStream | _vfs_CloseStream |  | FUNCTION/RELOC | Units/vfs/vfs.c |
| 0x10003960 | 559B | gzread | gzread |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003B90 | 182B | vfs_FlushStream | _vfs_FlushStream |  | FUNCTION/RELOC | Units/vfs/vfs2.c |
| 0x10003C50 | 65B | vfs_ReadUint32BE | _vfs_ReadUint32BE |  | FUNCTION/RELOC | Units/vfs/vfs2.c |
| 0x10003CA0 | 77B | vfs_FlushAndClose | _vfs_FlushAndClose |  | FUNCTION/RELOC | Units/vfs/vfs2.c |
| 0x10003CF0 | 43B | vfs_WriteUint32LE | _vfs_WriteUint32LE |  | FUNCTION/RELOC | Units/vfs/vfs2.c |
| 0x10003D20 | 123B | inflate_blocks_reset | inflate_blocks_reset |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003DA0 | 160B | inflate_blocks_new | inflate_blocks_new |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003E40 | 3385B | inflate_blocks | inflate_blocks |  | LIBRARY/EXACT | library_zlib.h |
| 0x10004B40 | 57B | inflate_blocks_free | inflate_blocks_free |  | LIBRARY/EXACT | library_zlib.h |
| 0x10004B80 | 57B | gm_AllocAndInit | _gm_AllocAndInit |  | FUNCTION/EXACT | DieGildeAddOn/game/spiel_gm_AllocAndInit.c |
| 0x10004BC0 | 1988B | inflate_fast | inflate_fast |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005370 | 20B | gm_DispatchCall | _gm_DispatchCall |  | FUNCTION/EXACT | DieGildeAddOn/game/spiel_gm_DispatchCall.c |
| 0x10005390 | 911B | inflate_codes | inflate_codes |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005720 | 66B | inflateReset | inflateReset |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005770 | 72B | inflateEnd | inflateEnd |  | LIBRARY/EXACT | library_zlib.h |
| 0x100057C0 | 270B | inflateInit2_ | inflateInit2_ |  | LIBRARY/EXACT | library_zlib.h |
| 0x100058D0 | 1072B | inflate | inflate |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005D00 | 163B | inflate_trees_bits | inflate_trees_bits |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005DB0 | 1225B | huft_build | huft_build |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006280 | 393B | inflate_trees_dynamic | inflate_trees_dynamic |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006410 | 46B | inflate_trees_fixed | inflate_trees_fixed |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006440 | 306B | inflate_flush | inflate_flush |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006580 | 658B | m_AllocTracked | _m_AllocTracked | /O2 /Gd /G6 /Oy- | FUNCTION/PROVEN | Units/m_alloc/m_alloc_c/m_AllocTracked.c |
| 0x10006820 | 188B | m_FreeTracked | _m_FreeTracked | /O2 /Gd | FUNCTION/RELOC | Units/m_alloc/m_alloc.c |
| 0x100068E0 | 162B | InitPacketPool | _InitPacketPool | /O2 /Gd /Oy- | FUNCTION/SIZE_MISMATCH | Units/m_alloc/m_alloc.c |
| 0x10006990 | 612B | ReportMemoryGroupInfo | _ReportMemoryGroupInfo | /O2 /Gd | FUNCTION/RELOC | Units/m_alloc/m_alloc_c/ReportMemoryGroupInfo.c |
| 0x10006C00 | 283B | ShutdownMemoryAllocator | _ShutdownMemoryAllocator | /O2 /Gd | FUNCTION/RELOC | Units/m_alloc/m_alloc2.c |
| 0x10006D20 | 270B | m_PoolAlloc | _m_PoolAlloc | /O2 /Gd /Oy- | FUNCTION/PROVEN | Units/m_alloc/m_alloc2.c |
| 0x10006E30 | 137B | m_PoolFree | _m_PoolFree | /O2 /Gd | FUNCTION/RELOC | Units/m_alloc/m_alloc2.c |
| 0x10006EC0 | 108B | tr_init | _tr_init |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006F30 | 1B | tr_static_init | tr_static_init |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006F40 | 102B | init_block | init_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006FB0 | 157B | tr_stored_block | _tr_stored_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007050 | 597B | tr_align | _tr_align |  | LIBRARY/EXACT | library_zlib.h |
| 0x100072B0 | 494B | tr_flush_block | _tr_flush_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x100074A0 | 563B | build_tree | build_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x100076E0 | 209B | pqdownheap | pqdownheap |  | LIBRARY/EXACT | library_zlib.h |
| 0x100077C0 | 545B | gen_bitlen | gen_bitlen |  | LIBRARY/EXACT | library_zlib.h |
| 0x100079F0 | 115B | gen_codes | gen_codes |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007A70 | 111B | build_bl_tree | build_bl_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007AE0 | 231B | scan_tree | scan_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007BD0 | 613B | send_all_trees | send_all_trees |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007E40 | 1397B | send_tree | send_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x100083C0 | 1083B | vfs_CompressBlock | vfs_CompressBlock |  | LIBRARY/EXACT | library_zlib.h |
| 0x10008800 | 116B | set_data_type | set_data_type |  | LIBRARY/EXACT | library_zlib.h |
| 0x10008880 | 31B | bit_reverse | bit_reverse |  | LIBRARY/EXACT | library_msvc.h |
| 0x100088A0 | 139B | bi_flush | bi_flush |  | LIBRARY/EXACT | library_zlib.h |
| 0x10008930 | 124B | bi_windup | bi_windup |  | LIBRARY/EXACT | library_zlib.h |
| 0x100089B0 | 151B | copy_block | copy_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x10008A50 | 53B | vfs_DestroyEntity | _vfs_DestroyEntity |  | FUNCTION/RELOC | Units/vfs/vfs3.c |
| 0x10008C80 | 129B | vfs_CleanupObject | _vfs_CleanupObject | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | Units/vfs/vfs4.c |
| 0x10008D10 | 301B | CloseVfsStream | _CloseVfsStream | /O2 /Gd | FUNCTION/RELOC | Units/vfs/vfs4.c |
| 0x10008E40 | 472B | ReadVfsData | _ReadVfsData | /O2 /Gd /Oy- /DREBREW_ALLOW_NAKED | FUNCTION/PROVEN | Units/vfs/ReadVfsData.c |
| 0x10009020 | 704B | OpenVfsStream | _OpenVfsStream | /O2 /Gd | FUNCTION/PROVEN | Units/vfs/vfs_c/OpenVfsStream.c |
| 0x100092E0 | 19B | zcalloc | zcalloc |  | LIBRARY/EXACT | library_zlib.h |
| 0x10009300 | 12B | free_wrap | free_wrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x10009310 | 8B | exit_handler | _exit_handler@12 |  | FUNCTION/EXACT | DieGildeAddOnServer/server.c |
| 0x10009320 | 42B | Init | _Init |  | FUNCTION/RELOC | DieGildeAddOnServer/server.c |
| 0x10009350 | 68B | Exit | _Exit |  | FUNCTION/RELOC | DieGildeAddOnServer/server.c |
| 0x100093A0 | 2434B | ServerMainThread | _ServerMainThread@4 | /O2 /Gd | FUNCTION/STUB | DieGildeAddOnServer/server_c/ServerMainThread.c |
| 0x10009D30 | 296B | srv_Init | _srv_Init | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOnServer/server2.c |
| 0x10009E60 | 419B | CreateListenSocket | _CreateListenSocket |  | FUNCTION/RELOC | DieGildeAddOnServer/server2.c |
| 0x1000A010 | 112B | CleanupSockets | _CleanupSockets |  | FUNCTION/PROVEN | DieGildeAddOnServer/server2.c |
| 0x1000A080 | 600B | AcceptConnections | _AcceptConnections | /O2 /Gd | FUNCTION/NEAR_MATCHING | DieGildeAddOnServer/server2.c |
| 0x1000A2E0 | 96B | cm_ClosePlayerConnection | _cm_ClosePlayerConnection |  | FUNCTION/RELOC | DieGildeAddOnServer/server2.c |
| 0x1000A340 | 336B | ReceivePacketHeader | _ReceivePacketHeader | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOnServer/server2.c |
| 0x1000A490 | 211B | SendPlayerData | _SendPlayerData |  | FUNCTION/RELOC | DieGildeAddOnServer/server2.c |
| 0x1000A570 | 750B | ProcessReceiveData | _ProcessReceiveData | /O2 /Gd /Ot | FUNCTION/PROVEN | DieGildeAddOnServer/server_c/ProcessReceiveData.c |
| 0x1000A860 | 131B | ProcessSendData | _ProcessSendData | /O2 /Gd /Ow | FUNCTION/RELOC | DieGildeAddOnServer/server3.c |
| 0x1000A8F0 | 170B | QueueCommandForProcessing | _QueueCommandForProcessing |  | FUNCTION/RELOC | DieGildeAddOnServer/server3.c |
| 0x1000A9A0 | 170B | cm_QueuePlayerCommand | _cm_QueuePlayerCommand |  | FUNCTION/RELOC | DieGildeAddOnServer/server3.c |
| 0x1000AA50 | 97B | list_unlink_relink | _list_unlink_relink |  | FUNCTION/EXACT | DieGildeAddOnServer/server3.c |
| 0x1000AAC0 | 639B | cm_ProcessCommandQueue | _cm_ProcessCommandQueue | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/PROVEN | DieGildeAddOnServer/server_c/cm_ProcessCommandQueue.c |
| 0x1000AD40 | 768B | LogWinsockError | _LogWinsockError |  | FUNCTION/RELOC | DieGildeAddOnServer/server4.c |
| 0x1000B040 | 372B | InitBuildingTypeTable | _InitBuildingTypeTable | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOnServer/server4.c |
| 0x1000B1C0 | 205B | amt_ValidateOfficeCandidate | _amt_ValidateOfficeCandidate | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/aemter.c |
| 0x1000B290 | 425B | ValidateAndAssignOffice | _ValidateAndAssignOffice | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/PROVEN | DieGildeAddOn/game/aemter.c |
| 0x1000B440 | 133B | amt_ValidateCommand | _amt_ValidateCommand |  | FUNCTION/RELOC | DieGildeAddOn/game/aemter.c |
| 0x1000B4D0 | 836B | ExecuteOfficeAssignment | _ExecuteOfficeAssignment | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/aemter_c/ExecuteOfficeAssignment.c |
| 0x1000B820 | 42B | amt_FindEntity26 | _amt_FindEntity26 | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/aemter2.c |
| 0x1000B850 | 42B | amt_FindEntity27 | _amt_FindEntity27 |  | FUNCTION/RELOC | DieGildeAddOn/game/aemter2.c |
| 0x1000B880 | 263B | amt_SwapOfficeHolders | _amt_SwapOfficeHolders | /O2 /Ob0 /Gd | FUNCTION/RELOC | DieGildeAddOn/game/aemter2.c |
| 0x1000B990 | 157B | amt_ClearEntityLinks | _amt_ClearEntityLinks |  | FUNCTION/RELOC | DieGildeAddOn/game/aemter2.c |
| 0x1000BA30 | 179B | amt_UpdateEntityLinks | _amt_UpdateEntityLinks | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/aemter2.c |
| 0x1000BAF0 | 606B | amt_fio_LoadAemter | _amt_fio_LoadAemter | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/aemter_c/amt_fio_LoadAemter.c |
| 0x1000BD50 | 66B | ahm_ResetEntityState | _ahm_ResetEntityState | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/EXACT | DieGildeAddOn/game/alchemistry_logic_c/ahm_ResetEntityState.c |
| 0x1000BDA0 | 70B | ahm_CheckFlag | _ahm_CheckFlag | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic_c/ahm_ResetEntityState.c |
| 0x1000BDF0 | 1002B | ahm_ExAllocAlchemist | _ahm_ExAllocAlchemist | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/alchemistry_logic_c/ahm_ExAllocAlchemist.c |
| 0x1000C1E0 | 160B | ahm_ApplyColorComponent | _ahm_ApplyColorComponent | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C280 | 130B | ahm_AllocateEntitySlot | _ahm_AllocateEntitySlot |  | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C310 | 110B | ahm_SlotClearMatch | _ahm_SlotClearMatch |  | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C380 | 51B | ahm_SearchAndSet | _ahm_SearchAndSet |  | FUNCTION/EXACT | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C3C0 | 83B | ahm_ClampFloatValue | _ahm_ClampFloatValue | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C420 | 166B | ahm_FireEntityAndCleanup | _ahm_FireEntityAndCleanup |  | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C4D0 | 295B | ahm_AllocAhmInfo | _ahm_AllocAhmInfo |  | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C600 | 109B | ahm_InitRandomEntity | _ahm_InitRandomEntity |  | FUNCTION/NEAR_MATCHING | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C670 | 45B | ahm_LookupEntityInTable | _ahm_LookupEntityInTable |  | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C6A0 | 102B | ahm_QueryEntityBuildingType | _ahm_QueryEntityBuildingType |  | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic2.c |
| 0x1000C710 | 752B | GetCommandPayloadSize | _GetCommandPayloadSize | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/alchemistry_logic_c/GetCommandPayloadSize.c |
| 0x1000CA00 | 130B | ahm_ProcessEntityChain | _ahm_ProcessEntityChain | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/alchemistry_logic3.c |
| 0x1000CA90 | 130B | gm_GetFieldByType | _gm_GetFieldByType |  | FUNCTION/EXACT | DieGildeAddOn/game/alchemistry_logic3.c |
| 0x1000CB20 | 171B | cm_ChkMoveCredits | _cm_ChkMoveCredits | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ChkMoveCredits.c |
| 0x1000CBD0 | 517B | cm_ChkSellObjekt | _cm_ChkSellObjekt |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkSellObjekt.c |
| 0x1000CDE0 | 331B | cm_ChkChangeAttribute | _cm_ChkChangeAttribute |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkChangeAttribute.c |
| 0x1000CF30 | 162B | cm_ChkChangeBits | _cm_ChkChangeBits |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkChangeBits.c |
| 0x1000CFE0 | 64B | cm_ChkSetGebBesitzer | _cm_ChkSetGebBesitzer |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkSetGebBesitzer.c |
| 0x1000D020 | 22B | cm_ChkOfficeCandidate | _cm_ChkOfficeCandidate | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkOfficeCandidate.c |
| 0x1000D040 | 22B | cm_ValidateGeneric | _cm_ValidateGeneric |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ValidateGeneric.c |
| 0x1000D060 | 169B | cm_ChkElectionOrTrade | _cm_ChkElectionOrTrade |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkElectionOrTrade.c |
| 0x1000D110 | 333B | cm_ChkJoinLeaveElection | _cm_ChkJoinLeaveElection | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkJoinLeaveElection.c |
| 0x1000D260 | 120B | cm_ChkCutsceneReady | _cm_ChkCutsceneReady |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkCutsceneReady.c |
| 0x1000D2E0 | 77B | cm_ChkCommandType | _cm_ChkCommandType |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkCommandType.c |
| 0x1000D330 | 14B | cm_MarkAndReturn | _cm_MarkAndReturn |  | FUNCTION/EXACT | DieGildeAddOn/command/command_c/cm_MarkAndReturn.c |
| 0x1000D340 | 6B | cm_RejectCommand | _cm_RejectCommand |  | FUNCTION/EXACT | DieGildeAddOn/command/command_c/cm_RejectCommand.c |
| 0x1000D350 | 267B | cm_ExAllocRaum | _cm_ExAllocRaum | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAllocRaum.c |
| 0x1000D460 | 267B | cm_ExAllocSpieler | _cm_ExAllocSpieler | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAllocSpieler.c |
| 0x1000D570 | 361B | cm_ExAllocClientSpieler | _cm_ExAllocClientSpieler | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExAllocClientSpieler.c |
| 0x1000D6E0 | 78B | cm_ExChangePlayerIdentity | _cm_ExChangePlayerIdentity |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExChangePlayerIdentity.c |
| 0x1000D730 | 180B | cm_ExFree | _cm_ExFree | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExFree.c |
| 0x1000D7F0 | 176B | cm_ExTransferCurrency | _cm_ExTransferCurrency |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExTransferCurrency.c |
| 0x1000D8A0 | 144B | cm_ExTransferCurrencyNoKill | _cm_ExTransferCurrencyNoKill |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExTransferCurrencyNoKill.c |
| 0x1000D930 | 2057B | cm_ExSellObjekt | _cm_ExSellObjekt | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExSellObjekt.c |
| 0x1000E140 | 993B | cm_ExProdObjekt | _cm_ExProdObjekt | /Ox /Gd | FUNCTION/PROVEN | DieGildeAddOn/command/command_c/cm_ExProdObjekt.c |
| 0x1000E530 | 352B | cm_ExMoveObjekt | _cm_ExMoveObjekt | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExMoveObjekt.c |
| 0x1000E690 | 191B | cm_ExClearLagerslot | _cm_ExClearLagerslot | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExClearLagerslot.c |
| 0x1000E750 | 128B | cm_ExAllocObjekt | _cm_ExAllocObjekt | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAllocObjekt.c |
| 0x1000E7D0 | 256B | cm_ExChangeAttribute | _cm_ExChangeAttribute | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExChangeAttribute.c |
| 0x1000E8D0 | 239B | cm_ExSetAttribute | _cm_ExSetAttribute | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSetAttribute.c |
| 0x1000E9C0 | 214B | cm_ExChangeDesire | _cm_ExChangeDesire | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExChangeDesire.c |
| 0x1000EAA0 | 208B | cm_ExChangeBits | _cm_ExChangeBits | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExChangeBits.c |
| 0x1000EB70 | 144B | cm_ExChangeFloat | _cm_ExChangeFloat | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExChangeFloat.c |
| 0x1000EC00 | 912B | cm_ExCopyEntityData | _cm_ExCopyEntityData | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c |
| 0x1000EF90 | 26B | cm_ChainAssignId | _cm_ChainAssignId | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChainAssignId.c |
| 0x1000EFB0 | 122B | cm_ExSetSyncFlags | _cm_ExSetSyncFlags |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSetSyncFlags.c |
| 0x1000F030 | 72B | cm_ExKillSpieler | _cm_ExKillSpieler |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExKillSpieler.c |
| 0x1000F080 | 26B | cm_AssignSequenceCounter | _cm_AssignSequenceCounter | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_AssignSequenceCounter.c |
| 0x1000F0A0 | 37B | cm_AssignEntityId | _cm_AssignEntityId |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_AssignEntityId.c |
| 0x1000F0D0 | 197B | cm_ExRemoveLinkedObject | _cm_ExRemoveLinkedObject | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExRemoveLinkedObject.c |
| 0x1000F1A0 | 327B | cm_ChainRecordLookup | _cm_ChainRecordLookup |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChainRecordLookup.c |
| 0x1000F2F0 | 176B | cm_ExAllocThemaPredigt | _cm_ExAllocThemaPredigt | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAllocThemaPredigt.c |
| 0x1000F3A0 | 3B | cm_ChainNoop | _cm_ChainNoop |  | FUNCTION/EXACT | DieGildeAddOn/command/command_c/cm_ChainNoop.c |
| 0x1000F3B0 | 206B | cm_ExSetGebBesitzer | _cm_ExSetGebBesitzer |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSetGebBesitzer.c |
| 0x1000F480 | 271B | cm_ExSetWohnsitz | _cm_ExSetWohnsitz |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSetWohnsitz.c |
| 0x1000F590 | 237B | cm_ExSetGebUpgrade | _cm_ExSetGebUpgrade |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSetGebUpgrade.c |
| 0x1000F680 | 171B | cm_ExDestroyBuilding | _cm_ExDestroyBuilding |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExDestroyBuilding.c |
| 0x1000F730 | 515B | cm_ExEmployWorker | _cm_ExEmployWorker |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExEmployWorker.c |
| 0x1000F940 | 22B | cm_ExAssignOffice | _cm_ExAssignOffice | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAssignOffice.c |
| 0x1000F960 | 22B | cm_ExExecuteOffice | _cm_ExExecuteOffice |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExExecuteOffice.c |
| 0x1000F980 | 336B | cm_ExCreateCitizen | _cm_ExCreateCitizen | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExCreateCitizen.c |
| 0x1000FAD0 | 85B | cm_ExKillTransporter | _cm_ExKillTransporter |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExKillTransporter.c |
| 0x1000FB30 | 153B | cm_ExCreateGeb | _cm_ExCreateGeb |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExCreateGeb.c |
| 0x1000FBD0 | 22B | cm_ExCondWrite | _cm_ExCondWrite |  | FUNCTION/EXACT | DieGildeAddOn/command/command_c/cm_ExCondWrite.c |
| 0x1000FBF0 | 25B | cm_InitDefaultResponse | _cm_InitDefaultResponse |  | FUNCTION/EXACT | DieGildeAddOn/command/command_c/cm_InitDefaultResponse.c |
| 0x1000FC10 | 308B | cm_ExElectionOrTrade | _cm_ExElectionOrTrade |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExElectionOrTrade.c |
| 0x1000FD50 | 445B | cm_ExJoinLeaveElection | _cm_ExJoinLeaveElection | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExJoinLeaveElection.c |
| 0x1000FF10 | 22B | cm_ExCondWrite2 | _cm_ExCondWrite2 |  | FUNCTION/EXACT | DieGildeAddOn/command/command_c/cm_ExCondWrite2.c |
| 0x1000FF30 | 41B | cm_ChkEntityLookup | _cm_ChkEntityLookup |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ChkEntityLookup.c |
| 0x1000FF60 | 82B | cm_ExCutsceneUpdate | _cm_ExCutsceneUpdate |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExCutsceneUpdate.c |
| 0x1000FFC0 | 70B | cm_ExModifyHealth | _cm_ExModifyHealth |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExModifyHealth.c |
| 0x10010010 | 110B | cm_ExModifyStamina | _cm_ExModifyStamina |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExModifyStamina.c |
| 0x10010080 | 22B | cm_ExSimCommand | _cm_ExSimCommand |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSimCommand.c |
| 0x100100A0 | 159B | cm_ExModifyStat | _cm_ExModifyStat | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExModifyStat.c |
| 0x10010140 | 280B | cm_ExAllocWarEvent | _cm_ExAllocWarEvent | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/command/command_c/cm_ExAllocWarEvent.c |
| 0x10010260 | 144B | cm_DispatchProduction | _cm_DispatchProduction |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_DispatchProduction.c |
| 0x100102F0 | 17B | cm_DispatchMoveSlot | _cm_DispatchMoveSlot | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_DispatchMoveSlot.c |
| 0x10010310 | 52B | cm_ExAllocGraveyardWorker | _cm_ExAllocGraveyardWorker |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAllocGraveyardWorker.c |
| 0x10010350 | 52B | cm_ExAllocAlchemist | _cm_ExAllocAlchemist |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExAllocAlchemist.c |
| 0x10010390 | 262B | cm_ExSimSpecialAction | _cm_ExSimSpecialAction |  | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_ExSimSpecialAction.c |
| 0x100104A0 | 135B | cm_GetBuildingStatCount | _cm_GetBuildingStatCount | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/command_c/cm_GetBuildingStatCount.c |
| 0x10010530 | 113B | gv_CheckSlotActive | _gv_CheckSlotActive | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/EXACT | DieGildeAddOn/game/friedhof_dump.c |
| 0x100105B0 | 329B | GetSlotEntry | _GetSlotEntry | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/game/friedhof_logic_c/GetSlotEntry.c |
| 0x10010710 | 320B | FindSlotEntryFiltered | _FindSlotEntryFiltered |  | FUNCTION/NEAR_MATCHING | DieGildeAddOn/game/friedhof_logic_c/FindSlotEntryFiltered.c |
| 0x10010850 | 370B | SpawnGraveyardEntities | _SpawnGraveyardEntities |  | FUNCTION/STUB | DieGildeAddOn/game/friedhof_logic_c/SpawnGraveyardEntities.c |
| 0x100109D0 | 832B | AllocGraveyardField | _AllocGraveyardField |  | FUNCTION/RELOC | DieGildeAddOn/game/friedhof_logic_c/AllocGraveyardField.c |
| 0x10010D10 | 570B | UpgradeGraveyardField | _UpgradeGraveyardField |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/friedhof_dump.c |
| 0x10010F50 | 66B | gv_Free3Fields | _gv_Free3Fields | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/unknown/gv_Free3Fields.c |
| 0x100111B0 | 501B | HireProductionWorker | _HireProductionWorker | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/game/friedhof_logic_c/HireProductionWorker.c |
| 0x100113B0 | 390B | ExtendProductionTime | _ExtendProductionTime |  | FUNCTION/RELOC | DieGildeAddOn/game/friedhof_logic_c/ExtendProductionTime.c |
| 0x10011540 | 288B | ReplaceProductionWorker | _ReplaceProductionWorker |  | FUNCTION/RELOC | DieGildeAddOn/game/friedhof_logic_c/ReplaceProductionWorker.c |
| 0x10011660 | 297B | ActivateGraveyardSection | _ActivateGraveyardSection |  | FUNCTION/PROVEN | DieGildeAddOn/game/friedhof_logic_c/ActivateGraveyardSection.c |
| 0x10011790 | 242B | UpdateProductionProgress | _UpdateProductionProgress | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/friedhof_logic_c/UpdateProductionProgress.c |
| 0x10011890 | 164B | ValidateEntityAction | _ValidateEntityAction | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/game/friedhof_logic_c/ValidateEntityAction.c |
| 0x10011940 | 674B | gv_MoveSlotEntry | _gv_MoveSlotEntry |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/friedhof_dump.c |
| 0x10011BF0 | 1040B | gv_ExAllocGraveyardWorker | _gv_ExAllocGraveyardWorker | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/friedhof_logic_c/gv_ExAllocGraveyardWorker.c |
| 0x10012000 | 728B | ls_LoadGraveyardData | _ls_LoadGraveyardData | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/loadsave/loadsave_dump1.c |
| 0x100122E0 | 346B | InitNewDynastyEntity | _InitNewDynastyEntity | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/friedhof_logic_c/InitNewDynastyEntity.c |
| 0x10012440 | 37B | ReadVfsDataChecked | _ReadVfsDataChecked |  | FUNCTION/RELOC | DieGildeAddOn/loadsave/loadsave_c/ReadVfsDataChecked.c |
| 0x10012470 | 857B | ls_LoadSavegameHeader | _ls_LoadSavegameHeader | /O2 /Gd | FUNCTION/NEAR_MATCHING | DieGildeAddOn/loadsave/loadsave_c/ls_LoadSavegameHeader.c |
| 0x100127D0 | 282B | ls_LoadExistingEntities | _ls_LoadExistingEntities | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/loadsave/loadsave2.c |
| 0x100128F0 | 1463B | ls_LoadBuildingEntityState | _ls_LoadBuildingEntityState | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c |
| 0x10012EB0 | 884B | ls_LoadDynamicEntities | _ls_LoadDynamicEntities | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/loadsave/loadsave_c/ls_LoadDynamicEntities.c |
| 0x10013230 | 2268B | ls_LoadEntities | _ls_LoadEntities | /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/loadsave/loadsave_c/ls_LoadEntities.c |
| 0x10013B10 | 1361B | ls_LoadTownData | _ls_LoadTownData | /Ox /Gd | FUNCTION/PROVEN | DieGildeAddOn/loadsave/loadsave_c/ls_LoadTownData.c |
| 0x10014070 | 491B | ls_ID2Ptr | _ls_ID2Ptr | /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/loadsave/loadsave3.c |
| 0x10014260 | 892B | srv_RecvGame | _srv_RecvGame |  | FUNCTION/PROVEN | DieGildeAddOn/loadsave/loadsave_c/srv_RecvGame.c |
| 0x100145E0 | 209B | lb_ExPlayerlist | _lb_ExPlayerlist |  | FUNCTION/RELOC | DieGildeAddOn/command/lobbycommands.c |
| 0x100146C0 | 236B | lb_SendLobbyConfig | _lb_SendLobbyConfig |  | FUNCTION/RELOC | DieGildeAddOn/command/lobbycommands.c |
| 0x100147B0 | 670B | lb_HandleLobbyCommands | _lb_HandleLobbyCommands | /O2 /Gd | FUNCTION/STUB | DieGildeAddOn/command/lobbycommands_c/lb_HandleLobbyCommands.c |
| 0x10014A50 | 157B | lb_BroadcastStateChange | _lb_BroadcastStateChange | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/command/lobby_c/lb_BroadcastStateChange.c |
| 0x10014BF0 | 163B | lb_HandleEntitySync | _lb_HandleEntitySync | /O1 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/unknown/lb_HandleEntitySync.c |
| 0x10014F30 | 74B | FindRecord | _FindRecord |  | FUNCTION/EXACT | DieGildeAddOn/auxillary/plant.c |
| 0x10014F80 | 103B | find_zone_record | _find_zone_record |  | FUNCTION/EXACT | DieGildeAddOn/auxillary/plant.c |
| 0x10014FF0 | 175B | CheckZoneAvailability | _CheckZoneAvailability |  | FUNCTION/RELOC | DieGildeAddOn/auxillary/plant.c |
| 0x100150A0 | 257B | plt_SetPlantMap | _plt_SetPlantMap |  | FUNCTION/RELOC | DieGildeAddOn/auxillary/plant.c |
| 0x100151B0 | 41B | table_lookup | _table_lookup |  | FUNCTION/EXACT | DieGildeAddOn/auxillary/plant.c |
| 0x100151E0 | 535B | FindAndMatchParents | _FindAndMatchParents | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/sim.c |
| 0x10015400 | 83B | sim_PriorityUpdate | _sim_PriorityUpdate | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/sim.c |
| 0x10015460 | 145B | sim_StartEntityQueryByType | _sim_StartEntityQueryByType | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/sim.c |
| 0x10015500 | 180B | sim_CreateCitizen | _sim_CreateCitizen |  | FUNCTION/RELOC | DieGildeAddOn/game/sim.c |
| 0x100155C0 | 197B | AdvanceGameClock | _AdvanceGameClock | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/sim.c |
| 0x10015690 | 41B | sim_SetSyncParams | _sim_SetSyncParams |  | FUNCTION/EXACT | DieGildeAddOn/game/sim.c |
| 0x100156C0 | 642B | gm_InitObjektHersteller | _gm_InitObjektHersteller | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel_c/gm_InitObjektHersteller.c |
| 0x10015950 | 861B | gm_Open | _gm_Open | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_Open.c |
| 0x10015CB0 | 57B | gm_ResetAllEntities | _gm_ResetAllEntities | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel.c |
| 0x10015CF0 | 194B | gm_CleanupObjectEntities | _gm_CleanupObjectEntities | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel.c |
| 0x10015DC0 | 55B | gm_FindRecordById | _gm_FindRecordById |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel.c |
| 0x10015E00 | 135B | gm_CleanupAllEntities | _gm_CleanupAllEntities |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel.c |
| 0x10015E90 | 211B | gm_ResolveEntityById | _gm_ResolveEntityById |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel.c |
| 0x10015F70 | 714B | gm_RefreshMarketAvailability | _gm_RefreshMarketAvailability | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_RefreshMarketAvailability.c |
| 0x10016240 | 72B | gm_FindSlotById | _gm_FindSlotById | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/EXACT | DieGildeAddOn/game/spiel2.c |
| 0x10016290 | 464B | gm_NextEntityQueryMatch | _gm_NextEntityQueryMatch | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_NextEntityQueryMatch.c |
| 0x10016460 | 320B | gm_StartEntityQuery | _gm_StartEntityQuery | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_StartEntityQuery.c |
| 0x100165A0 | 37B | gm_AllocateObjectSlot | _gm_AllocateObjectSlot | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel_c/gm_AllocateObjectSlot.c |
| 0x100165D0 | 155B | gm_RemoveObjectByType | _gm_RemoveObjectByType | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel_c/gm_RemoveObjectByType.c |
| 0x10016670 | 1B | gm_NoopRet2 | _gm_NoopRet2 | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/EXACT | DieGildeAddOn/game/spiel_c/gm_NoopRet2.c |
| 0x10016680 | 139B | gm_RemoveLinkedNodeById | _gm_RemoveLinkedNodeById | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel_c/gm_RemoveLinkedNodeById.c |
| 0x10016710 | 66B | gm_FreeObjectListRecursive | _gm_FreeObjectListRecursive | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel_c/gm_FreeObjectListRecursive.c |
| 0x10016760 | 1392B | gm_AllocObjekt | _gm_AllocObjekt | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_AllocObjekt.c |
| 0x10016CD0 | 272B | gm_AddOrAccumulateObject | _gm_AddOrAccumulateObject | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel_dumpD.c |
| 0x10016DE0 | 186B | gm_SubObjekt | _gm_SubObjekt |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel_dumpD.c |
| 0x10016EA0 | 211B | gm_SubObjektNoKill | _gm_SubObjektNoKill |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel_dumpD.c |
| 0x10016F80 | 346B | FindNextFilteredEntity | _FindNextFilteredEntity |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel_dumpD.c |
| 0x100170E0 | 304B | gm_StartFilteredEntitySearch | _gm_StartFilteredEntitySearch | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_StartFilteredEntitySearch.c |
| 0x10017210 | 39B | gm_SearchStruct | _gm_SearchStruct | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel5.c |
| 0x10017240 | 235B | gm_CleanupBuildingEntity | _gm_CleanupBuildingEntity |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel5.c |
| 0x10017330 | 207B | gm_AllocBuildingDefaults | _gm_AllocBuildingDefaults |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel5.c |
| 0x10017400 | 202B | gm_SetBuildingWorkerLimits | _gm_SetBuildingWorkerLimits | /O2 /Gd | FUNCTION/RELOC | DieGildeAddOn/game/spiel5.c |
| 0x100174D0 | 1088B | gm_AllocGebaeude | _gm_AllocGebaeude | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c |
| 0x10017910 | 145B | gm_SetupEntityQuery | _gm_SetupEntityQuery | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel6.c |
| 0x100179B0 | 181B | gm_GetBuildingTypeCategory | _gm_GetBuildingTypeCategory |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel6.c |
| 0x10017A70 | 62B | gm_SearchTable67 | _gm_SearchTable67 |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel6.c |
| 0x10017AB0 | 74B | gm_CheckEntityType | _gm_CheckEntityType | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel6.c |
| 0x10017B00 | 320B | gm_AssignBuildingOwner | _gm_AssignBuildingOwner |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel6.c |
| 0x10017C40 | 742B | gm_AllocBuildingContents | _gm_AllocBuildingContents | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_AllocBuildingContents.c |
| 0x10017F30 | 35B | gm_RemoveObjectWrapper | _gm_RemoveObjectWrapper | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10017F60 | 36B | gm_RemoveEntityLink | _gm_RemoveEntityLink |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10017F90 | 23B | gm_InitEntityIfValid | _gm_InitEntityIfValid |  | FUNCTION/RELOC | DieGildeAddOn/game/gm_InitEntityIfValid.c |
| 0x10017FB0 | 278B | gm_DeallocEntity | _gm_DeallocEntity | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel62.c |
| 0x100180D0 | 81B | gm_InitEntitySlots | _gm_InitEntitySlots |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10018130 | 32B | gm_IsInRange | _gm_IsInRange |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10018150 | 70B | gm_EntityClassCheck | _gm_EntityClassCheck |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x100181A0 | 87B | gm_CheckStatLevel | _gm_CheckStatLevel |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10018200 | 304B | gm_MapEntityStatRange | _gm_MapEntityStatRange |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10018330 | 276B | gm_GetOppositeStatIndex | _gm_GetOppositeStatIndex |  | FUNCTION/EXACT | DieGildeAddOn/game/spiel62.c |
| 0x10018450 | 78B | gm_RandomStatModifier | _gm_RandomStatModifier |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel62.c |
| 0x100184A0 | 56B | gm_LookupEntityRecordById | _gm_LookupEntityRecordById |  | FUNCTION/EXACT | DieGildeAddOn/game/spiel62.c |
| 0x100184E0 | 66B | gm_GetEntityTableEntry | _gm_GetEntityTableEntry |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel62.c |
| 0x10018530 | 800B | gm_ChangePlayerIdentityImpl | _gm_ChangePlayerIdentityImpl | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/PROVEN | DieGildeAddOn/game/spiel_c/gm_ChangePlayerIdentityImpl.c |
| 0x10018850 | 3689B | gm_CreateEntityFromParents | _gm_CreateEntityFromParents | /DREBREW_ALLOW_NAKED /O2 /Gd | FUNCTION/STUB | DieGildeAddOn/game/spiel_c/gm_CreateEntityFromParents.c |
| 0x100196C0 | 81B | gm_QueryEntitySum | _gm_QueryEntitySum | /O2 /Gd /DREBREW_ALLOW_NAKED | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019720 | 396B | gm_CalculateProductionValue | _gm_CalculateProductionValue |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel622.c |
| 0x100198B0 | 355B | gm_SumBuildingProductionValues | _gm_SumBuildingProductionValues |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel622.c |
| 0x10019A20 | 74B | gm_AccumulateTyped2 | _gm_AccumulateTyped2 |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019A70 | 102B | gm_EntityQuerySum | _gm_EntityQuerySum |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019AE0 | 82B | gm_ResolveParentEntity | _gm_ResolveParentEntity |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019B40 | 62B | gm_GetEntityType | _gm_GetEntityType |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019B80 | 83B | gm_EntityAccumulate | _gm_EntityAccumulate |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019BE0 | 124B | gm_WalkEntityChain | _gm_WalkEntityChain |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x10019C60 | 98B | gm_FindEntityByOwner | _gm_FindEntityByOwner |  | FUNCTION/PROVEN | DieGildeAddOn/game/spiel622.c |
| 0x10019CD0 | 48B | gm_GetMsgField | _gm_GetMsgField |  | FUNCTION/EXACT | DieGildeAddOn/game/spiel622.c |
| 0x10019D30 | 407B | gm_KannObjektHergestellt | _gm_KannObjektHergestellt |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel622.c |
| 0x10019ED0 | 395B | gm_CheckInventoryCapacity | _gm_CheckInventoryCapacity |  | FUNCTION/SIZE_MISMATCH | DieGildeAddOn/game/spiel622.c |
| 0x1001A060 | 97B | gm_EntitySetField | _gm_EntitySetField |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x1001A0D0 | 32B | gm_RandomMod | _gm_RandomMod |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x1001A0F0 | 22B | gm_RandomFloat01 | _gm_RandomFloat01 |  | FUNCTION/RELOC | DieGildeAddOn/game/gm_RandomFloat01.c |
| 0x1001A110 | 48B | gm_RandomQuadratic | _gm_RandomQuadratic |  | FUNCTION/RELOC | DieGildeAddOn/game/spiel622.c |
| 0x1001A140 | 14B | getpid | _getpid |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A150 | 0B | srand | _srand |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A160 | 0B | closesocket@4 | _closesocket@4 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A166 | 0B | sendto@24 | _sendto@24 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A16C | 0B | bind@12 | _bind@12 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A172 | 0B | htons@4 | _htons@4 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A178 | 0B | htonl@4 | _htonl@4 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A17E | 0B | setsockopt@20 | _setsockopt@20 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A184 | 0B | socket@12 | _socket@12 |  | LIBRARY/EXACT | library_winsock.h |
| 0x1001A18A | 0B | fflush | _fflush |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A1BB | 0B | fclose_lk | __fclose_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A207 | 78B | fputs | _fputs |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A255 | 49B | crt_locked_read | _crt_locked_read |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A299 | 0B | sprintf | _sprintf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A2EB | 0B | fopen | _fopen |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A30D | 353B | ftell | _ftell |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A46E | 44B | fseek | _fseek |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A49A | 141B | SeekFileHandleUnlocked | _SeekFileHandleUnlocked |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A527 | 0B | ctime | _ctime |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A540 | 39B | strrchr | _strrchr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A567 | 0B | time | _time |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A643 | 45B | fcn_1001a643 | _fcn_1001a643 | /O1 /Gd | FUNCTION/RELOC | crt_region/initterm.c |
| 0x1001A681 | 17B | exit | _exit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A692 | 15B | _cexit | __cexit | /O1 /Gd | FUNCTION/RELOC | crt_region/cexit.c |
| 0x1001A692 | 0B | cexit | __cexit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A6A1 | 163B | doexit | _doexit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A746 | 9B | lock_0d | lock_0d |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A74F | 9B | unlock_0d | unlock_0d |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A758 | 26B | fcn_1001a758 | _fcn_1001a758 | /O1 /Gd | FUNCTION/EXACT | crt_region/initterm.c |
| 0x1001A758 | 26B | initterm | _initterm |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A772 | 115B | dosmaperr | _dosmaperr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A7E5 | 9B | fcn_1001a7e5 | _fcn_1001a7e5 | /O1 /Gd | FUNCTION/RELOC | crt_region/flsall.c |
| 0x1001A7E5 | 0B | errno | __errno |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A7EE | 9B | fcn_1001a7ee | _fcn_1001a7ee | /O1 /Gd | FUNCTION/RELOC | crt_region/flsall.c |
| 0x1001A7EE | 0B | doserrno | ___doserrno |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A7F7 | 18B | malloc | _malloc | /O1 /Gd | FUNCTION/RELOC | crt_region/malloc.c |
| 0x1001A809 | 44B | fcn_1001a809 | _fcn_1001a809 | /O1 /Gd | FUNCTION/RELOC | crt_region/malloc.c |
| 0x1001A809 | 0B | nh_malloc | __nh_malloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A835 | 252B | fcn_1001a835 | _fcn_1001a835 | /O1 /Gd | FUNCTION/RELOC | crt_region/malloc.c |
| 0x1001A835 | 0B | malloc | _malloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A89C | 9B | unlock_09a | unlock_09a |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A8FB | 9B | unlock_09b | unlock_09b |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A931 | 47B | fcn_1001a931 | _fcn_1001a931 | /O1 /Gd | FUNCTION/RELOC | crt_region/fwrite_fread.c |
| 0x1001A931 | 47B | crt_locked_call4a | _crt_locked_call4a |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A960 | 266B | fcn_1001a960 | _fcn_1001a960 | /O1 /Gd | FUNCTION/PROVEN | crt_region/fwrite_fread.c |
| 0x1001A960 | 266B | fwrite | _fwrite |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AA6A | 47B | fcn_1001aa6a | _fcn_1001aa6a | /O1 /Gd | FUNCTION/RELOC | crt_region/fwrite_fread.c |
| 0x1001AA6A | 47B | fread | fread |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AA99 | 232B | fcn_1001aa99 | _fcn_1001aa99 | /O1 /Gd | FUNCTION/RELOC | crt_region/fwrite_fread.c |
| 0x1001AA99 | 232B | fread | _fread |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AB81 | 233B | free | _free | /O1 /Gd | FUNCTION/RELOC | crt_region/free.c |
| 0x1001AB81 | 215B | free | _free |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001ABEB | 9B | unlock_09c | unlock_09c |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AC43 | 9B | unlock_09d | unlock_09d |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AC70 | 47B | alloca_probe | __alloca_probe |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AC9F | 46B | fcn_1001ac9f | _fcn_1001ac9f | /O1 /Gd | FUNCTION/RELOC | crt_region/flsall.c |
| 0x1001AC9F | 46B | fclose | _fclose |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001ACCD | 92B | flush | __flush |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AD29 | 9B | fcn_1001ad29 | _fcn_1001ad29 | /O1 /Gd | FUNCTION/RELOC | crt_region/h_ad29.c |
| 0x1001AD29 | 9B | signal_lock | signal_lock |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AD32 | 164B | fcn_1001ad32 | _fcn_1001ad32 | /O1 /Gd | FUNCTION/SIZE_MISMATCH | crt_region/flsall.c |
| 0x1001AD32 | 164B | flsall | __flsall |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001ADD6 | 59B | crt_locked_putc | crt_locked_putc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AE20 | 272B | fcn_1001ae20 | _fcn_1001ae20 | /O1 /Gd | FUNCTION/STUB | crt_region/amsg_exit.c |
| 0x1001AE20 | 254B | strncpy | _strncpy |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AF30 | 193B | strchr | _strchr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AFF0 | 128B | strstr | _strstr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B070 | 23B | fpmath | __fpmath |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B088 | 56B | init_fptrs | init_fptrs |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B0C0 | 111B | crt_toupper | crt_toupper |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B12F | 204B | toupper | _toupper |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B200 | 664B | memmove2 | _memmove2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B535 | 0B | srand_impl | _srand_impl |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B535 | 13B | set_errno | set_errno |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B542 | 34B | rand | _rand |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B564 | 39B | ftol | __ftol |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B58B | 65B | printf | _printf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B5CC | 815B | realloc | _realloc | /O1 /Gd | FUNCTION/NEAR_MATCHING | crt_region/realloc.c |
| 0x1001B5CC | 781B | realloc | _realloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B757 | 9B | unlock_09e | unlock_09e |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B8A5 | 11B | unlock_9 | _unlock_9 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B8FB | 217B | __CRT_INIT | ___CRT_INIT@12 | /O1 /Gd | FUNCTION/RELOC | crt_region/crt_init.c |
| 0x1001B8FB | 217B | CRT_INIT@12 | __CRT_INIT@12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B9D4 | 157B | DllMain | _DllMain@12 | /O1 /Oy- /Gd | FUNCTION/RELOC | crt_region/dllmain.c |
| 0x1001B9D4 | 157B | DllMainCRTStartup@12 | __DllMainCRTStartup@12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BA71 | 51B | _amsg_exit | __amsg_exit | /O1 /Gd | FUNCTION/RELOC | crt_region/amsg_exit.c |
| 0x1001BA71 | 48B | amsg_exit | __amsg_exit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BAA4 | 168B | ioterm | __ioterm |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BB60 | 47B | fcn_1001bb60 | _fcn_1001bb60 | /O1 /Gd | FUNCTION/RELOC | crt_region/lock_streams.c |
| 0x1001BB60 | 47B | lock_stream | _lock_stream |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BB8F | 35B | fcn_1001bb8f | _fcn_1001bb8f | /O1 /Gd | FUNCTION/RELOC | crt_region/flsall.c |
| 0x1001BB8F | 35B | lock_file | __lock_file |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BBB2 | 47B | fcn_1001bbb2 | _fcn_1001bbb2 | /O1 /Gd | FUNCTION/RELOC | crt_region/lock_streams.c |
| 0x1001BBB2 | 47B | unlock_stream | _unlock_stream |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BBE1 | 35B | fcn_1001bbe1 | _fcn_1001bbe1 | /O1 /Gd | FUNCTION/RELOC | crt_region/flsall.c |
| 0x1001BBE1 | 35B | unlock_file | __unlock_file |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BC04 | 93B | close | __close |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BC61 | 131B | free_osfhnd | __free_osfhnd |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BCE4 | 43B | free_buf | _free_buf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BD0F | 141B | stbuf | __stbuf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BD9C | 42B | crt_cond_cleanup | crt_cond_cleanup |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BDD0 | 123B | fcn_1001bdd0 | _fcn_1001bdd0 | /O1 /Gd | FUNCTION/SIZE_MISMATCH | crt_region/setargv.c |
| 0x1001BDD0 | 123B | strlen | _strlen |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BE4B | 368B | openfile | __openfile |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BFBB | 200B | getstream | __getstream |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C083 | 280B | flsbuf | __flsbuf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C19B | 1825B | output | __output |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C8DC | 53B | write_char | _write_char |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C911 | 49B | write_multi_char | _write_multi_char |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C942 | 56B | write_string | _write_string |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C97A | 13B | stream_read_dword | _stream_read_dword |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C987 | 16B | stream_read_qword | _stream_read_qword |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C997 | 14B | stream_read_word | _stream_read_word |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C9A5 | 0B | _ioinit | __ioinit | /O1 /Gd | FUNCTION/STUB | crt_region/ioinit.c |
| 0x1001C9A5 | 444B | ioinit | __ioinit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CB61 | 0B | _ioterm | __ioterm |  | FUNCTION/STUB | crt_region/ioinit.c |
| 0x1001CB61 | 84B | ioterm | _ioterm |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CBB5 | 101B | lseek | __lseek |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CC1A | 115B | lseek_lk | __lseek_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CC8D | 202B | asctime | _asctime |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CD57 | 40B | format_digits | _format_digits |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CD7F | 352B | localtime | _localtime |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CEDF | 194B | loctotime_t | ___loctotime_t |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CFA1 | 41B | fcn_1001cfa1 | _fcn_1001cfa1 | /O1 /Gd | FUNCTION/RELOC | crt_region/tidtable.c |
| 0x1001CFA1 | 41B | crt_delete_cs | crt_delete_cs |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CFCA | 108B | fcn_1001cfca | _fcn_1001cfca | /O1 /Gd | FUNCTION/RELOC | crt_region/tidtable.c |
| 0x1001CFCA | 108B | crt_delete_locks | crt_delete_locks |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D036 | 97B | _mlock | __mlock | /O1 /Oy- /Gd | FUNCTION/RELOC | crt_region/mlock.c |
| 0x1001D036 | 97B | lock | __lock |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D097 | 21B | _munlock | __munlock | /O1 /Oy- /Gd | FUNCTION/RELOC | crt_region/mlock.c |
| 0x1001D097 | 21B | unlock | __unlock |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D0AC | 84B | __mtinit | ___mtinit | /O1 /Gd | FUNCTION/RELOC | crt_region/tidtable.c |
| 0x1001D0AC | 84B | mtinit | __mtinit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D100 | 30B | crt_close_handle | _crt_close_handle |  | FUNCTION/SIZE_MISMATCH | crt_region/tidtable.c |
| 0x1001D100 | 30B | crt_close_handle | crt_close_handle |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D11E | 19B | fcn_1001d11e | _fcn_1001d11e | /O1 /Gd | FUNCTION/EXACT | crt_region/tidtable.c |
| 0x1001D11E | 19B | set_vtable | set_vtable |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D131 | 103B | getptd | __getptd |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D198 | 160B | __freeptd | ___freeptd |  | FUNCTION/SIZE_MISMATCH | crt_region/tidtable.c |
| 0x1001D198 | 160B | freeptd | __freeptd |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D238 | 27B | fcn_1001d238 | _fcn_1001d238 | /O1 /Gd | FUNCTION/RELOC | crt_region/tidtable.c |
| 0x1001D238 | 27B | crt_gfunc_call | crt_gfunc_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D253 | 45B | fcn_1001d253 | _fcn_1001d253 | /O1 /Gd | FUNCTION/RELOC | crt_region/crt_heap.c |
| 0x1001D253 | 45B | crt_get_osver | crt_get_osver |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D280 | 328B | fcn_1001d280 | _fcn_1001d280 | /O1 /Gd | FUNCTION/STUB | crt_region/crt_heap.c |
| 0x1001D280 | 328B | heap_select | ___heap_select |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D3C8 | 93B | crt_heap_init | _crt_heap_init | /O1 /Gd | FUNCTION/RELOC | crt_region/crt_heap.c |
| 0x1001D3C8 | 93B | crt_heap_init | crt_heap_init |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D425 | 168B | __heap_term | ___heap_term |  | FUNCTION/SIZE_MISMATCH | crt_region/crt_heap.c |
| 0x1001D425 | 168B | heap_term | __heap_term |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D4CD | 72B | fcn_1001d4cd | _fcn_1001d4cd | /O1 /Gd | FUNCTION/RELOC | crt_region/crt_heap.c |
| 0x1001D4CD | 72B | sbh_heap_init | ___sbh_heap_init |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D515 | 43B | fcn_1001d515 | _fcn_1001d515 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001D515 | 43B | crt_find_entry | crt_find_entry |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D540 | 809B | fcn_1001d540 | _fcn_1001d540 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001D540 | 809B | sbh_free_block | ___sbh_free_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D869 | 777B | fcn_1001d869 | _fcn_1001d869 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001D869 | 777B | sbh_alloc_block | ___sbh_alloc_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001DB72 | 177B | fcn_1001db72 | _fcn_1001db72 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001DB72 | 177B | sbh_alloc_new_region | ___sbh_alloc_new_region |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001DC23 | 251B | fcn_1001dc23 | _fcn_1001dc23 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001DC23 | 251B | sbh_alloc_new_group | ___sbh_alloc_new_group |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001DD1E | 758B | fcn_1001dd1e | _fcn_1001dd1e | /O1 /Gd | FUNCTION/EXACT | crt_region/sbh_pool.c |
| 0x1001DD1E | 758B | sbh_resize_block | ___sbh_resize_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E014 | 324B | fcn_1001e014 | _fcn_1001e014 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001E014 | 324B | old_sbh_new_region | ___old_sbh_new_region |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E158 | 86B | fcn_1001e158 | _fcn_1001e158 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001E158 | 86B | sbh_decommit_pages | __sbh_decommit_pages |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E1AE | 194B | fcn_1001e1ae | _fcn_1001e1ae | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001E1AE | 194B | old_sbh_decommit_pages | ___old_sbh_decommit_pages |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E270 | 87B | fcn_1001e270 | _fcn_1001e270 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001E270 | 87B | old_sbh_find_block | ___old_sbh_find_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E2C7 | 69B | fcn_1001e2c7 | _fcn_1001e2c7 | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001E2C7 | 69B | update_page_entry | update_page_entry |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E30C | 520B | __old_sbh_alloc_block | ___old_sbh_alloc_block | /O1 /Gd | FUNCTION/RELOC | crt_region/sbh_pool.c |
| 0x1001E30C | 520B | old_sbh_alloc_block | ___old_sbh_alloc_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E514 | 292B | fcn_1001e514 | _fcn_1001e514 | /O1 /Gd | FUNCTION/EXACT | crt_region/sbh_pool.c |
| 0x1001E514 | 292B | old_sbh_alloc_block_from_page | ___old_sbh_alloc_block_from_page |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E638 | 169B | fcn_1001e638 | _fcn_1001e638 | /O1 /Gd | FUNCTION/EXACT | crt_region/sbh_pool.c |
| 0x1001E638 | 169B | old_sbh_resize_block | ___old_sbh_resize_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E6E4 | 32B | except_handler3 | __except_handler3 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E704 | 34B | seh_filter | _seh_filter |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E726 | 104B | local_unwind2 | __local_unwind2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E78E | 35B | ValidateEH3RN | _ValidateEH3RN |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E7BA | 24B | EH3_save_context | _EH3_save_context |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E7D4 | 197B | exsup | exsup |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E899 | 27B | seh_local_unwind_thunk | seh_local_unwind_thunk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E8B4 | 101B | crt_write_wrap | crt_write_wrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E919 | 395B | write_lk | __write_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EAB0 | 664B | memmove | _memmove |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EDE5 | 220B | filbuf | __filbuf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EEC1 | 101B | crt_lseek_wrap | _crt_lseek_wrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EF26 | 473B | read_lk | __read_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F0FF | 147B | fcn_1001f0ff | _fcn_1001f0ff | /O1 /Gd | FUNCTION/STUB | crt_region/flsall.c |
| 0x1001F0FF | 147B | crt_commit | crt_commit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F192 | 18B | crt_const_call | crt_const_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F1A4 | 62B | IsNonwritableInCurrentImage | ___IsNonwritableInCurrentImage |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F1E2 | 41B | IsProcessorFeaturePresent | __IsProcessorFeaturePresent |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F20B | 90B | forcdecpt | __forcdecpt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F265 | 78B | cropzeros | __cropzeros |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F2B3 | 24B | positive | __positive |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F2CB | 62B | fassign | __fassign |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F309 | 97B | ecvt | __ecvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F36A | 194B | cftoe | __cftoe |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F42C | 85B | fcvt | __fcvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F481 | 167B | cftof | __cftof |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F528 | 147B | cfltcvt_g | ___cfltcvt_g |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F5BB | 81B | cfltcvt | __cfltcvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F60C | 37B | crt_strcpy_advance | _crt_strcpy_advance |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F631 | 511B | crtLCMapStringA | ___crtLCMapStringA |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F855 | 117B | isctype | __isctype |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F8D0 | 16B | fcn_1001f8d0 | _fcn_1001f8d0 | /O1 /Gd | FUNCTION/STUB | crt_region/setargv.c |
| 0x1001F8D0 | 7B | CopyCString | CopyCString |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F8E0 | 224B | fcn_1001f8e0 | _fcn_1001f8e0 | /O1 /Gd | FUNCTION/STUB | crt_region/amsg_exit.c |
| 0x1001F8E0 | 224B | strcat | _strcat |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F9C0 | 0B | _setenvp | __setenvp | /O1 /Gd | FUNCTION/STUB | crt_region/setargv.c |
| 0x1001F9C0 | 185B | setenvp | __setenvp |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FA79 | 0B | _setargv | __setargv |  | FUNCTION/STUB | crt_region/setargv.c |
| 0x1001FA79 | 153B | setargv | __setargv |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FB12 | 436B | fcn_1001fb12 | _fcn_1001fb12 | /O1 /Gd | FUNCTION/STUB | crt_region/setargv.c |
| 0x1001FB12 | 436B | parse_cmdline | _parse_cmdline |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FCC6 | 0B | __crtGetEnvironmentStringsA | ___crtGetEnvironmentStringsA |  | FUNCTION/STUB | crt_region/setargv.c |
| 0x1001FCC6 | 306B | crtGetEnvironmentStringsA | ___crtGetEnvironmentStringsA |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FDF8 | 57B | fcn_1001fdf8 | _fcn_1001fdf8 | /O1 /Gd | FUNCTION/RELOC | crt_region/amsg_exit.c |
| 0x1001FDF8 | 57B | crt_runtime_error | crt_runtime_error |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FE31 | 339B | fcn_1001fe31 | _fcn_1001fe31 | /O1 /Gd | FUNCTION/STUB | crt_region/amsg_exit.c |
| 0x1001FE31 | 339B | NMSG_WRITE | __NMSG_WRITE |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FF84 | 153B | calloc | _calloc | /O1 /Gd | FUNCTION/STUB | crt_region/tidtable.c |
| 0x1001FF84 | 289B | calloc | _calloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002001D | 9B | unlock_09f | unlock_09f |  | LIBRARY/EXACT | library_msvc.h |
| 0x100200A6 | 9B | unlock_09g | unlock_09g |  | LIBRARY/EXACT | library_msvc.h |
| 0x100200C1 | 129B | fcloseall | __fcloseall |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020142 | 291B | alloc_osfhnd | __alloc_osfhnd |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020265 | 124B | open_osfhandle | __open_osfhandle |  | LIBRARY/EXACT | library_msvc.h |
| 0x100202E1 | 127B | free_osfhnd | free_osfhnd |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020360 | 66B | get_osfhandle | __get_osfhandle |  | LIBRARY/EXACT | library_msvc.h |
| 0x100203A2 | 95B | lock_fhandle | __lock_fhandle |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020401 | 34B | slot_unlock | slot_unlock |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020423 | 41B | slot_check_flag | slot_check_flag |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002044C | 719B | sopen | __sopen |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002071B | 68B | crt_buf_alloc | crt_buf_alloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002075F | 89B | wctomb | _wctomb |  | LIBRARY/EXACT | library_msvc.h |
| 0x100207B8 | 105B | wctomb_lk | __wctomb_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020830 | 104B | aulldiv | __aulldiv |  | LIBRARY/EXACT | library_msvc.h |
| 0x100208A0 | 117B | aullrem | __aullrem |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020915 | 46B | crt_once_init | crt_once_init |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020943 | 647B | tzset | __tzset |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020BCA | 33B | crt_locked_call | _crt_locked_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020BEB | 428B | isindst_lk | __isindst_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020D97 | 320B | cvtdate | cvtdate |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020ED7 | 266B | gmtime_lk | _gmtime_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020FE1 | 23B | fcn_10020fe1 | _fcn_10020fe1 | /O1 /Gd | FUNCTION/RELOC | crt_region/crt_heap.c |
| 0x10020FE1 | 23B | call_with_zero | call_with_zero |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020FF8 | 517B | strtoxl | _strtoxl |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021200 | 56B | fcn_10021200 | _fcn_10021200 | /O1 /Gd | FUNCTION/STUB | crt_region/crt_heap.c |
| 0x10021200 | 56B | strncmp | _strncmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021240 | 88B | memset | _memset |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021298 | 53B | controlfp | __controlfp |  | LIBRARY/EXACT | library_msvc.h |
| 0x100212CD | 22B | clear_bit_call | clear_bit_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x100212E3 | 146B | crt_cvt_osflag | crt_cvt_osflag |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021375 | 137B | abstract_cw | _abstract_cw |  | LIBRARY/EXACT | library_msvc.h |
| 0x100213FE | 111B | crt_tolower_wrapper | crt_tolower_wrapper |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002146D | 203B | tolower | __tolower |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021538 | 73B | check_bits_clear | _check_bits_clear |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021581 | 86B | set_bit_range | set_bit_range |  | LIBRARY/EXACT | library_msvc.h |
| 0x100215D7 | 140B | sbh_dealloc_bitmap | ___sbh_dealloc_bitmap |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021663 | 27B | copy_3dwords | copy_3dwords |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002167E | 12B | zero_12bytes | zero_12bytes |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002168A | 27B | check_all_zero | check_all_zero |  | LIBRARY/EXACT | library_msvc.h |
| 0x100216A5 | 141B | sbh_bitmap_shift | ___sbh_bitmap_shift |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021732 | 364B | ld12tod | __ld12tod |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002189E | 22B | wrapper_ctx1 | wrapper_ctx1 |  | LIBRARY/EXACT | library_msvc.h |
| 0x100218B4 | 22B | wrapper_ctx2 | wrapper_ctx2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x100218CA | 45B | atodbl | __atodbl |  | LIBRARY/EXACT | library_msvc.h |
| 0x100218F7 | 45B | atoldbl | __atoldbl |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021924 | 119B | fptostr | __fptostr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002199B | 92B | fltout2 | __fltout2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x100219F7 | 182B | dtold | ___dtold |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021AAD | 9B | fptrap | __fptrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021AC0 | 129B | strcmp | _strcmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021B50 | 62B | strcspn | _strcspn |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021B90 | 58B | strpbrk | _strpbrk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021BCA | 318B | crtGetStringTypeA | ___crtGetStringTypeA |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021D13 | 429B | setmbcp | __setmbcp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021EC0 | 74B | crtGetACP_getcodepage | __crtGetACP_getcodepage |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021EDA | 0B | GetOEMCP | GetOEMCP |  | LIBRARY/EXACT | library_imports.h |
| 0x10021EEF | 0B | GetACP | GetACP |  | LIBRARY/EXACT | library_imports.h |
| 0x10021F0A | 51B | code_translate | code_translate |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021F3D | 41B | CrtIoInfoInit | CrtIoInfoInit |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021F66 | 389B | setSBUpLow | _setSBUpLow |  | LIBRARY/EXACT | library_msvc.h |
| 0x100220EB | 28B | fcn_100220eb | _fcn_100220eb | /O1 /Gd | FUNCTION/RELOC | crt_region/setargv.c |
| 0x100220EB | 28B | crt_cinit_once | _crt_cinit_once |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022107 | 137B | fcn_10022107 | _fcn_10022107 | /O1 /Gd | FUNCTION/STUB | crt_region/amsg_exit.c |
| 0x10022107 | 137B | crtLoadWinAPI | __crtLoadWinAPI |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022190 | 293B | chsize_lk | __chsize_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x100222B5 | 139B | atoi | _atoi |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022340 | 125B | getenv | _getenv |  | LIBRARY/EXACT | library_msvc.h |
| 0x100223BD | 33B | overflow_add | overflow_add |  | LIBRARY/EXACT | library_msvc.h |
| 0x100223DE | 94B | add_12 | ___add_12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002243C | 46B | shl_12 | ___shl_12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002246A | 45B | shr_12 | ___shr_12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022497 | 199B | ld12cvt | ___ld12cvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002255E | 1185B | strgtold12 | ___strgtold12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022A2F | 659B | ld12cvt | __ld12cvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022CD0 | 208B | stricmp | __stricmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022DA0 | 257B | strnicmp | __strnicmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022EA1 | 110B | setmode_lk | __setmode_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F10 | 25B | allmul | __allmul |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F29 | 27B | allmul_slow | __allmul_slow |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F44 | 63B | mbsnbicoll | __mbsnbicoll |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F83 | 110B | wenvsetup | __wenvsetup |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023211 | 124B | mantold_shl | _mantold_shl |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002328D | 597B | crtCompareStringA | ___crtCompareStringA |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023535 | 150B | crtsetenv | ___crtsetenv |  | LIBRARY/EXACT | library_msvc.h |
| 0x100236BC | 88B | crt_env_search | _crt_env_search |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023714 | 103B | copy_environ | _copy_environ |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002377B | 100B | mbschr | __mbschr |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023812 | 40B | strdup | __strdup |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023840 | 0B | RtlUnwind | RtlUnwind |  | LIBRARY/EXACT | library_imports.h |

## Unmatched Functions (30 remaining)

| VA | Size | Name |
|-----|------|---------|
| 0x10008A90 | 492B | ReadVfsCompressed |
| 0x1000AD68 | 32B | case.0x1000ad61.10019 |
| 0x1000AD88 | 32B | case.0x1000ad61.10012 |
| 0x1000ADA8 | 32B | case.0x1000ad61.10005 |
| 0x1000ADC8 | 32B | case.0x1000ad61.10016 |
| 0x1000ADE8 | 32B | case.0x1000ad61.10004 |
| 0x1000AE08 | 32B | case.0x1000ad61.10008 |
| 0x1000AE28 | 32B | case.0x1000ad61.10013 |
| 0x1000AE48 | 32B | case.0x1000ad61.10009 |
| 0x1000AE68 | 32B | case.0x1000ad61.10011 |
| 0x1000AE88 | 32B | case.0x1000ad61.10017 |
| 0x1000AEA8 | 32B | case.0x1000ad61.10007 |
| 0x1000AEC8 | 32B | case.0x1000ad61.10010 |
| 0x1000AEE8 | 32B | case.0x1000ad61.10006 |
| 0x1000AF08 | 32B | case.0x1000ad61.10014 |
| 0x1000AF28 | 32B | case.0x1000ad61.10018 |
| 0x1000AF48 | 248B | case.0x1000ad61.10015 |
| 0x10010700 | 14B | fcn.10010700 |
| 0x10010FA0 | 525B | AssignProductionSlot |
| 0x10014AF0 | 256B | fcn.10014af0 |
| 0x10014CA0 | 272B | fcn.10014ca0 |
| 0x10014DB0 | 304B | fcn.10014db0 |
| 0x10014EE0 | 80B | fcn.10014ee0 |
| 0x10018272 | 190B | case.0x10018211.15 |
| 0x10019D00 | 48B | fcn.10019d00 |
| 0x1001A286 | 19B | fcn.1001a286 |
| 0x1001A670 | 34B | fcn.1001a670 |
| 0x1001E7DC | 216B | fcn.1001e7dc |
| 0x10022FF1 | 544B | fcn.10022ff1 |
| 0x1002350A | 43B | fcn.1002350a |
