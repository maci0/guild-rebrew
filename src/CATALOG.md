# Reversed Functions Catalog

Total: 547/0 functions cataloged (307 exact, 108 reloc-normalized, 0 stubs)  
Coverage: 92.6% of .text section (136577/147456 bytes)


## GAME (258 functions)

| VA | Size | Name | Symbol | Flags | Match | File |
|-----|------|------|--------|-------|-------|------|
| 0x10001130 | 179B | SendBroadcastPacket | _SendBroadcastPacket |  | FUNCTION/RELOC | server.dll/Units/net/broadcast.c |
| 0x10002640 | 290B | DispatchLogOutput | _DispatchLogOutput |  | FUNCTION/RELOC | server.dll/Units/Error/Error.c |
| 0x10002770 | 1836B | CrashDumpUnhandledExceptionFilter | _CrashDumpUnhandledExceptionFilter |  | FUNCTION/NEAR_MATCH | server.dll/Units/Error/Error.c |
| 0x10002FC0 | 376B | EmitCrashModuleLine | _EmitCrashModuleLine |  | FUNCTION/NEAR_MATCH | server.dll/Units/Error/Error.c |
| 0x10003140 | 33B | GetDebugRecordByIndex | _GetDebugRecordByIndex |  | FUNCTION/EXACT | server.dll/Units/Error/Error.c |
| 0x10003170 | 240B | check_memory_protection | _check_memory_protection |  | FUNCTION/RELOC | server.dll/Units/Error/Error.c |
| 0x10003260 | 183B | AnalyzeInstruction | _AnalyzeInstruction |  | FUNCTION/NEAR_MATCH | server.dll/Units/Error/Error.c |
| 0x10003320 | 404B | InitializeLogAndErrorHandler | _InitializeLogAndErrorHandler |  | FUNCTION/NEAR_MATCH | server.dll/Units/Error/Error.c |
| 0x100034C0 | 83B | ShutdownLogAndErrorHandler | _ShutdownLogAndErrorHandler |  | FUNCTION/RELOC | server.dll/Units/Error/Error.c |
| 0x10003520 | 160B | ReportFatalError | _ReportFatalError |  | FUNCTION/RELOC | server.dll/Units/Error/Error.c |
| 0x100035C0 | 119B | ReportMessage | _ReportMessage |  | FUNCTION/RELOC | server.dll/Units/Error/Error.c |
| 0x10003640 | 132B | LogMessageInternal | _LogMessageInternal |  | FUNCTION/RELOC | server.dll/Units/Error/Error.c |
| 0x10003820 | 114B | game_getbyte | _game_getbyte |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x100038A0 | 177B | close_stream | _close_stream |  | FUNCTION/RELOC | server.dll/Units/vfs/vfs.c |
| 0x10003B90 | 182B | flush_stream | _flush_stream |  | FUNCTION/RELOC | server.dll/Units/vfs/vfs.c |
| 0x10003C50 | 77B | flush_and_close_stream | _flush_and_close_stream |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x10003CA0 | 65B | read_uint32_be | _read_uint32_be |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x10003CF0 | 43B | write_uint32_le | _write_uint32_le |  | FUNCTION/RELOC | server.dll/Units/vfs/vfs.c |
| 0x10004B80 | 320B | alloc_and_init | _alloc_and_init |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10005370 | 20B | dispatch_call | _dispatch_call |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10006580 | 658B | AllocateTrackedHeapBlock | _AllocateTrackedHeapBlock |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x10006820 | 188B | FreeTrackedHeapBlock | _FreeTrackedHeapBlock |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x100068E0 | 162B | InitPacketPool | _InitPacketPool |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x10006990 | 612B | ReportMemoryGroupInfo | _ReportMemoryGroupInfo |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x10006C00 | 283B | ShutdownMemoryAllocator | _ShutdownMemoryAllocator |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x10006D20 | 270B | pool_alloc | _pool_alloc |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x10006E30 | 137B | pool_free | _pool_free |  | FUNCTION/NEAR_MATCH | server.dll/Units/m_alloc/m_alloc.c |
| 0x10008A50 | 53B | destroy_entity | _destroy_entity |  | FUNCTION/RELOC | server.dll/Units/vfs/vfs.c |
| 0x10008A90 | 492B | ReadVfsCompressed | _ReadVfsCompressed |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x10008C80 | 129B | cleanup_object | _cleanup_object |  | FUNCTION/RELOC | server.dll/Units/vfs/vfs.c |
| 0x10008D10 | 301B | CloseVfsStream | _CloseVfsStream |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x10008E40 | 472B | ReadVfsData | _ReadVfsData |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x10009020 | 704B | OpenVfsStream | _OpenVfsStream |  | FUNCTION/NEAR_MATCH | server.dll/Units/vfs/vfs.c |
| 0x10009310 | 170B | exit_handler@12 | _exit_handler@12 |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x10009320 | 42B | Init | _Init |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x10009350 | 68B | Exit | _Exit |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x100093A0 | 2434B | ServerMainThread | _ServerMainThread |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x10009D30 | 296B | srv_Init | _srv_Init |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x10009E60 | 419B | CreateListenSocket | _CreateListenSocket |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A010 | 112B | CleanupSockets | _CleanupSockets |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A080 | 600B | AcceptConnections | _AcceptConnections |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A2E0 | 96B | ClosePlayerConnection | _ClosePlayerConnection |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A340 | 336B | ReceivePacketHeader | _ReceivePacketHeader |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A490 | 211B | SendPlayerData | _SendPlayerData |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A570 | 750B | ProcessReceiveData | _ProcessReceiveData |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A860 | 131B | ProcessSendData | _ProcessSendData |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A8F0 | 170B | QueueCommandForProcessing | _QueueCommandForProcessing |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000A9A0 | 170B | QueuePlayerCommand | _QueuePlayerCommand |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000AA50 | 97B | list_unlink_relink | _list_unlink_relink |  | FUNCTION/EXACT | server.dll/DieGildeAddOnServer/server.c |
| 0x1000AAC0 | 639B | cm_ProcessCommandQueue | _cm_ProcessCommandQueue |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x1000AD40 | 768B | LogWinsockError | _LogWinsockError |  | FUNCTION/RELOC | server.dll/DieGildeAddOnServer/server.c |
| 0x1000B040 | 372B | InitBuildingTypeTable | _InitBuildingTypeTable |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOnServer/server.c |
| 0x1000B1C0 | 205B | ValidateOfficeCandidate | _ValidateOfficeCandidate |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B290 | 425B | ValidateAndAssignOffice | _ValidateAndAssignOffice |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B440 | 133B | ValidateCommand | _ValidateCommand |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B4D0 | 836B | ExecuteOfficeAssignment | _ExecuteOfficeAssignment |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B820 | 42B | find_entity_26 | _find_entity_26 |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B850 | 42B | find_entity_27 | _find_entity_27 |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B880 | 263B | SwapOfficeHolders | _SwapOfficeHolders |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000B990 | 157B | ClearEntityLinks | _ClearEntityLinks |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000BA30 | 179B | UpdateEntityLinks | _UpdateEntityLinks |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000BAF0 | 606B | amt_fio_LoadAemter | _amt_fio_LoadAemter |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/aemter.c |
| 0x1000BD50 | 130B | reset_entity_state | _reset_entity_state |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000BDA0 | 70B | check_flag | _check_flag |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000BDF0 | 1002B | ahm_ExAllocAlchemist | _ahm_ExAllocAlchemist |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C1E0 | 160B | ApplyColorComponent | _ApplyColorComponent |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C280 | 130B | AllocateEntitySlot | _AllocateEntitySlot |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C310 | 110B | slot_clear_match | _slot_clear_match |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C380 | 51B | search_and_set | _search_and_set |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C3C0 | 83B | ClampFloatValue | _ClampFloatValue |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C420 | 166B | FireEntityAndCleanup | _FireEntityAndCleanup |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C4D0 | 295B | ahm_AllocAhmInfo | _ahm_AllocAhmInfo |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C600 | 109B | InitRandomEntity | _InitRandomEntity |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C670 | 45B | LookupEntityInTable | _LookupEntityInTable |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C6A0 | 102B | QueryEntityBuildingType | _QueryEntityBuildingType |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000C710 | 752B | GetCommandPayloadSize | _GetCommandPayloadSize |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000CA00 | 130B | ProcessEntityChain | _ProcessEntityChain |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000CA90 | 130B | get_field_by_type | _get_field_by_type |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/alchemistry_logic.c |
| 0x1000CB20 | 171B | CheckMoveCredits | _CheckMoveCredits | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ChkMoveCredits.c |
| 0x1000CBD0 | 517B | CheckSellObject | _CheckSellObject | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ChkSellObjekt.c |
| 0x1000CDE0 | 331B | CheckChangeAttribute | _CheckChangeAttribute | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ChkChangeAttribute.c |
| 0x1000CF30 | 162B | CheckChangeBits | _CheckChangeBits | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ChkChangeBits.c |
| 0x1000CFE0 | 64B | find_validate | _find_validate | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChkSetGebBesitzer.c |
| 0x1000D020 | 22B | cm_ChkOfficeCandidate | _call_with_off | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChkOfficeCandidate.c |
| 0x1000D040 | 22B | cm_ValidateGeneric | _CmdValidateGeneric | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ValidateGeneric.c |
| 0x1000D060 | 169B | ValidateElectionOrTradeCmd | _ValidateElectionOrTradeCmd | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChkElectionOrTrade.c |
| 0x1000D110 | 333B | ValidateJoinLeaveElection | _ValidateJoinLeaveElection | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ChkJoinLeaveElection.c |
| 0x1000D260 | 120B | CheckCutsceneReady | _CheckCutsceneReady | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ChkCutsceneReady.c |
| 0x1000D2E0 | 77B | cm_ChkCommandType | _validate_command_type | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChkCommandType.c |
| 0x1000D330 | 14B | MarkAndReturn | _MarkAndReturn | /O2 /Gd | FUNCTION/EXACT | server.dll/DieGildeAddOn/command/command_c/cm_MarkAndReturn.c |
| 0x1000D340 | 6B | RejectCommand | _RejectCommand | /O2 /Gd | FUNCTION/EXACT | server.dll/DieGildeAddOn/command/command_c/cm_RejectCommand.c |
| 0x1000D350 | 267B | cm_ExAllocRaum | _CmdAllocBuilding | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocRaum.c |
| 0x1000D460 | 267B | cm_ExAllocSpieler | _CmdAllocPlayer | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocSpieler.c |
| 0x1000D570 | 361B | cm_ExAllocClientSpieler | _validate_cmd_10_AllocPlayer | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocClientSpieler.c |
| 0x1000D6E0 | 78B | cm_ExChangePlayerIdentity | _cm_ExChangePlayerIdentity | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExChangePlayerIdentity.c |
| 0x1000D730 | 180B | ExFreeEntity | _ExFreeEntity | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExFree.c |
| 0x1000D7F0 | 176B | ExTransferCurrency | _ExTransferCurrency | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExTransferCurrency.c |
| 0x1000D8A0 | 144B | ExTransferCurrencyNoKill | _ExTransferCurrencyNoKill | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExTransferCurrencyNoKill.c |
| 0x1000D930 | 2057B | TradeCommandHandler | _TradeCommandHandler | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c |
| 0x1000E140 | 993B | cm_ExecProduction | _cm_ExecProduction | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c |
| 0x1000E530 | 352B | ExMoveObject | _ExMoveObject | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExMoveObjekt.c |
| 0x1000E690 | 191B | cm_ExClearLagerslot | _cm_ExClearLagerslot | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExClearLagerslot.c |
| 0x1000E750 | 123B | ExCreateObject | _ExCreateObject | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocObjekt.c |
| 0x1000E7D0 | 242B | ExAccumulateEntityFields | _ExAccumulateEntityFields | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExChangeAttribute.c |
| 0x1000E8D0 | 239B | ExWriteEntityFields | _ExWriteEntityFields | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExSetAttribute.c |
| 0x1000E9C0 | 214B | ExChangeDesire | _ExChangeDesire | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExChangeDesire.c |
| 0x1000EAA0 | 208B | ExSetEntityBitmask | _ExSetEntityBitmask | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExChangeBits.c |
| 0x1000EB70 | 144B | ExSetEntityField | _ExSetEntityField | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExChangeFloat.c |
| 0x1000EC00 | 912B | ExCopyEntityData | _ExCopyEntityData | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c |
| 0x1000EF90 | 26B | cm_ChainAssignId | _chain_handler_assign_id | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChainAssignId.c |
| 0x1000EFB0 | 122B | SetSyncFlags | _SetSyncFlags | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExSetSyncFlags.c |
| 0x1000F030 | 72B | cm_ExKillSpieler | _CmdKillPlayer | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExKillSpieler.c |
| 0x1000F080 | 26B | AssignSequenceCounter | _AssignSequenceCounter | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_AssignSequenceCounter.c |
| 0x1000F0A0 | 37B | AssignEntityId | _AssignEntityId | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_AssignEntityId.c |
| 0x1000F0D0 | 197B | RemoveLinkedObject | _RemoveLinkedObject | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExRemoveLinkedObject.c |
| 0x1000F1A0 | 327B | cm_ChainRecordLookup | _chain_handler_record_lookup | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChainRecordLookup.c |
| 0x1000F2F0 | 172B | ExCreateSpecialObject | _ExCreateSpecialObject | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocThemaPredigt.c |
| 0x1000F3A0 | 3B | cm_ChainNoop | _chain_handler_noop | /O2 /Gd | FUNCTION/EXACT | server.dll/DieGildeAddOn/command/command_c/cm_ChainNoop.c |
| 0x1000F3B0 | 206B | SetBuildingOwner | _SetBuildingOwner | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExSetGebBesitzer.c |
| 0x1000F480 | 271B | SetResidence | _SetResidence | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExSetWohnsitz.c |
| 0x1000F590 | 237B | SetBuildingUpgrade | _SetBuildingUpgrade | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExSetGebUpgrade.c |
| 0x1000F680 | 171B | DestroyBuilding | _DestroyBuilding | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExDestroyBuilding.c |
| 0x1000F730 | 515B | EmployWorkerAtBuilding | _EmployWorkerAtBuilding | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExEmployWorker.c |
| 0x1000F940 | 22B | cm_ExAssignOffice | _call_with_off2 | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExAssignOffice.c |
| 0x1000F960 | 22B | cm_ExExecuteOffice | _CmdExecuteOffice | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExExecuteOffice.c |
| 0x1000F980 | 336B | ExCreateCitizenAtBuilding | _ExCreateCitizenAtBuilding | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExCreateCitizen.c |
| 0x1000FAD0 | 85B | cm_ExKillTransporter | _cm_ExKillTransporter | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExKillTransporter.c |
| 0x1000FB30 | 153B | cm_ExCreateGeb | _CmdCreateBuilding | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExCreateGeb.c |
| 0x1000FBD0 | 22B | cm_ExCondWrite | _cond_write | /O2 /Gd | FUNCTION/EXACT | server.dll/DieGildeAddOn/command/command_c/cm_ExCondWrite.c |
| 0x1000FBF0 | 25B | InitDefaultResponse | _InitDefaultResponse | /O2 /Gd | FUNCTION/EXACT | server.dll/DieGildeAddOn/command/command_c/cm_InitDefaultResponse.c |
| 0x1000FC10 | 308B | ElectionOrTradeCommand | _ElectionOrTradeCommand | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExElectionOrTrade.c |
| 0x1000FD50 | 445B | JoinLeaveElection | _JoinLeaveElection | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExJoinLeaveElection.c |
| 0x1000FF10 | 22B | cm_ExCondWrite2 | _cond_write2 | /O2 /Gd | FUNCTION/EXACT | server.dll/DieGildeAddOn/command/command_c/cm_ExCondWrite2.c |
| 0x1000FF30 | 41B | ValidateEntityLookup | _ValidateEntityLookup | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ChkEntityLookup.c |
| 0x1000FF60 | 82B | CutsceneEntityUpdate | _CutsceneEntityUpdate | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExCutsceneUpdate.c |
| 0x1000FFC0 | 70B | ModifyEntityHealth | _ModifyEntityHealth | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExModifyHealth.c |
| 0x10010010 | 110B | ModifyEntityStamina | _ModifyEntityStamina | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExModifyStamina.c |
| 0x10010080 | 22B | ExSimCommand | _ExSimCommand | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExSimCommand.c |
| 0x100100A0 | 159B | ModifyEntityStat | _ModifyEntityStat | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExModifyStat.c |
| 0x10010140 | 280B | AllocWarEvent | _AllocWarEvent | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocWarEvent.c |
| 0x10010260 | 144B | DispatchProductionCommand | _DispatchProductionCommand | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_DispatchProduction.c |
| 0x100102F0 | 17B | DispatchMoveSlotEntry | _DispatchMoveSlotEntry | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_DispatchMoveSlot.c |
| 0x10010310 | 52B | cm_ExAllocGraveyardWorker | _CmdAllocGraveyardWorker | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocGraveyardWorker.c |
| 0x10010350 | 52B | cm_ExAllocAlchemist | _CmdAllocAlchemist | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExAllocCharacter.c |
| 0x10010390 | 262B | SimSpecialAction | _SimSpecialAction | /O2 /Gd | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/command_c/cm_ExSimSpecialAction.c |
| 0x100104A0 | 135B | GetBuildingStatCount | _GetBuildingStatCount | /O2 /Gd | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/command_c/cm_GetBuildingStatCount.c |
| 0x10010530 | 352B | check_slot_active | _check_slot_active |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x100105B0 | 329B | GetSlotEntry | _GetSlotEntry |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10010710 | 320B | FindSlotEntryFiltered | _FindSlotEntryFiltered |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10010850 | 370B | SpawnGraveyardEntities | _SpawnGraveyardEntities |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x100109D0 | 832B | AllocGraveyardField | _AllocGraveyardField |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10010D10 | 570B | UpgradeGraveyardField | _UpgradeGraveyardField |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10010F50 | 66B | free_3fields | _free_3fields |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10010FA0 | 525B | AssignProductionSlot | _AssignProductionSlot |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x100111B0 | 501B | HireProductionWorker | _HireProductionWorker |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x100113B0 | 390B | ExtendProductionTime | _ExtendProductionTime |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10011540 | 288B | ReplaceProductionWorker | _ReplaceProductionWorker |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10011660 | 297B | ActivateGraveyardSection | _ActivateGraveyardSection |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10011790 | 242B | UpdateProductionProgress | _UpdateProductionProgress |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10011890 | 164B | ValidateEntityAction | _ValidateEntityAction |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10011940 | 674B | MoveSlotEntry | _MoveSlotEntry |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10011BF0 | 1040B | gv_ExAllocGraveyardWorker | _gv_ExAllocGraveyardWorker |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/friedhof_logic.c |
| 0x10012000 | 728B | LoadGraveyardData | _LoadGraveyardData |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x100122E0 | 346B | InitNewDynastyEntity | _InitNewDynastyEntity |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10012440 | 37B | ReadVfsDataChecked | _ReadVfsDataChecked |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10012470 | 857B | LoadSavegameHeader | _LoadSavegameHeader |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x100127D0 | 282B | LoadExistingEntities | _LoadExistingEntities |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x100128F0 | 1463B | LoadBuildingEntityState | _LoadBuildingEntityState |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10012EB0 | 884B | LoadDynamicEntities | _LoadDynamicEntities |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10013230 | 2268B | ls_LoadEntities | _ls_LoadEntities |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10013B10 | 1361B | LoadTownData | _LoadTownData |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10014070 | 491B | ls_ID2Ptr | _ls_ID2Ptr |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x10014260 | 892B | srv_RecvGame | _srv_RecvGame |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/loadsave/loadsave.c |
| 0x100145E0 | 304B | lb_ExPlayerlist | _lb_ExPlayerlist |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x100146C0 | 236B | SendLobbyConfig | _SendLobbyConfig |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x100147B0 | 670B | HandleLobbyCommands | _HandleLobbyCommands |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014A50 | 157B | broadcast_state_change | _broadcast_state_change |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014AF0 | 247B | HandleDataTransferCommand | _HandleDataTransferCommand |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014BF0 | 163B | HandleEntitySync | _HandleEntitySync |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014CA0 | 265B | cm_RouteCommand | _cm_RouteCommand |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014DB0 | 267B | lb_ExLobbyServerCommand | _lb_ExLobbyServerCommand |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014EE0 | 69B | SearchRecordTable | _SearchRecordTable |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/command/lobbycommands.c |
| 0x10014F30 | 74B | FindRecord | _FindRecord |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/auxillary/plant.c |
| 0x10014F80 | 103B | find_zone_record | _find_zone_record |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/auxillary/plant.c |
| 0x10014FF0 | 175B | CheckZoneAvailability | _CheckZoneAvailability |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/auxillary/plant.c |
| 0x100150A0 | 257B | plt_SetPlantMap | _plt_SetPlantMap |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/auxillary/plant.c |
| 0x100151B0 | 41B | table_lookup | _table_lookup |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/auxillary/plant.c |
| 0x100151E0 | 535B | FindAndMatchParents | _FindAndMatchParents |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/sim.c |
| 0x10015400 | 83B | priority_update | _priority_update |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/sim.c |
| 0x10015460 | 145B | StartEntityQueryByType | _StartEntityQueryByType |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/sim.c |
| 0x10015500 | 180B | sim_CreateCitizen | _sim_CreateCitizen |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/sim.c |
| 0x100155C0 | 197B | AdvanceGameClock | _AdvanceGameClock |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/sim.c |
| 0x10015690 | 41B | SetSyncParams | _SetSyncParams |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/sim.c |
| 0x100156C0 | 642B | gm_InitObjektHersteller | _gm_InitObjektHersteller |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015950 | 861B | Open | _Open |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015CB0 | 57B | reset_all_entities | _reset_all_entities |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015CF0 | 194B | CleanupObjectEntities | _CleanupObjectEntities |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015DC0 | 55B | FindRecordById | _FindRecordById |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015E00 | 135B | cleanup_all_entities | _cleanup_all_entities |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015E90 | 211B | ResolveEntityById | _ResolveEntityById |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10015F70 | 714B | RefreshMarketAvailability | _RefreshMarketAvailability |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016240 | 72B | FindSlotById | _FindSlotById |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016290 | 464B | NextEntityQueryMatch | _NextEntityQueryMatch |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016460 | 320B | StartEntityQuery | _StartEntityQuery |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100165A0 | 37B | AllocateObjectSlot | _AllocateObjectSlot |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100165D0 | 155B | RemoveObjectByType | _RemoveObjectByType |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016670 | 1B | noop_ret2 | _noop_ret2 |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016680 | 139B | RemoveLinkedNodeById | _RemoveLinkedNodeById |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016710 | 66B | FreeObjectListRecursive | _FreeObjectListRecursive |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016760 | 1392B | AllocGameObject | _AllocGameObject |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016CD0 | 272B | AddOrAccumulateObject | _AddOrAccumulateObject |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016DE0 | 186B | SubObjekt | _SubObjekt |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016EA0 | 211B | SubtractObjectAmountNoKill | _SubtractObjectAmountNoKill |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10016F80 | 346B | FindNextFilteredEntity | _FindNextFilteredEntity |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100170E0 | 267B | StartFilteredEntitySearch | _StartFilteredEntitySearch |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017210 | 39B | search_struct | _search_struct |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017240 | 240B | CleanupBuildingEntity | _CleanupBuildingEntity |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017330 | 207B | gm_AllocBuildingDefaults | _gm_AllocBuildingDefaults |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017400 | 202B | SetBuildingWorkerLimits | _SetBuildingWorkerLimits |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100174D0 | 1088B | AllocGebaeude | _AllocGebaeude |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017910 | 145B | SetupEntityQuery | _SetupEntityQuery |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100179B0 | 192B | GetBuildingTypeCategory | _GetBuildingTypeCategory |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017A70 | 62B | search_table_67 | _search_table_67 |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017AB0 | 74B | CheckEntityType | _CheckEntityType |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017B00 | 320B | AssignBuildingOwner | _AssignBuildingOwner |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017C40 | 742B | AllocBuildingContents | _AllocBuildingContents |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017F30 | 35B | RemoveObjectWrapper | _RemoveObjectWrapper |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017F60 | 36B | RemoveEntityLink | _RemoveEntityLink |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017F90 | 23B | InitEntityIfValid | _InitEntityIfValid |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10017FB0 | 278B | DeallocEntity | _DeallocEntity |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100180D0 | 81B | InitEntitySlots | _InitEntitySlots |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018130 | 32B | is_in_range | _is_in_range |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018150 | 70B | EntityClassCheck | _EntityClassCheck |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100181A0 | 87B | CheckStatLevel | _CheckStatLevel |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018200 | 304B | MapEntityStatRange | _MapEntityStatRange |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018330 | 276B | GetOppositeStatIndex | _GetOppositeStatIndex |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018450 | 78B | RandomStatModifier | _RandomStatModifier |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100184A0 | 56B | LookupEntityRecordById | _LookupEntityRecordById |  | FUNCTION/EXACT | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100184E0 | 66B | GetEntityTableEntry | _GetEntityTableEntry |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018530 | 800B | ChangePlayerIdentityImpl | _ChangePlayerIdentityImpl |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10018850 | 3689B | CreateEntityFromParents | _CreateEntityFromParents |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100196C0 | 81B | QueryEntitySum | _QueryEntitySum |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019720 | 396B | CalculateProductionValue | _CalculateProductionValue |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x100198B0 | 355B | SumBuildingProductionValues | _SumBuildingProductionValues |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019A20 | 74B | accumulate_typed2 | _accumulate_typed2 |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019A70 | 102B | EntityQuerySum | _EntityQuerySum |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019AE0 | 82B | ResolveParentEntity | _ResolveParentEntity |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019B40 | 62B | GetEntityType | _GetEntityType |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019B80 | 124B | entity_accumulate | _entity_accumulate |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019BE0 | 83B | WalkEntityChain | _WalkEntityChain |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019C60 | 48B | get_msg_field | _get_msg_field |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019CD0 | 98B | FindEntityByOwner | _FindEntityByOwner |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019D30 | 407B | KannObjektHergestellt | _KannObjektHergestellt |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x10019ED0 | 395B | CheckInventoryCapacity | _CheckInventoryCapacity |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x1001A060 | 97B | entity_set_field | _entity_set_field |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x1001A0D0 | 54B | random_mod | _random_mod |  | FUNCTION/NEAR_MATCH | server.dll/DieGildeAddOn/game/spiel.c |
| 0x1001A0F0 | 22B | RandomFloat01 | _RandomFloat01 |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |
| 0x1001A110 | 48B | RandomQuadratic | _RandomQuadratic |  | FUNCTION/RELOC | server.dll/DieGildeAddOn/game/spiel.c |

## MSVCRT (237 functions)

| VA | Size | Name | Symbol | Flags | Match | File |
|-----|------|------|--------|-------|-------|------|
| 0x10008880 | 12B | bit_reverse | bit_reverse |  | LIBRARY/EXACT | library_msvc.h |
| 0x10009300 | 199B | free_wrap | free_wrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A140 | 0B | crt_getid_set | crt_getid_set |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A18A | 0B | fflush | _fflush |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A1BB | 0B | fclose_lk | __fclose_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A207 | 49B | fputs | _fputs |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A255 | 141B | crt_locked_read | _crt_locked_read |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A299 | 353B | sprintf | _sprintf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A30D | 44B | ftell | _ftell |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A46E | 39B | fseek | _fseek |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A49A | 163B | SeekFileHandleUnlocked | _SeekFileHandleUnlocked |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A540 | 0B | strrchr | _strrchr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A567 | 17B | time | _time |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A681 | 0B | exit | _exit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A692 | 0B | cexit | __cexit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A6A1 | 9B | doexit | _doexit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A746 | 9B | lock_0d | lock_0d |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A74F | 26B | unlock_0d | unlock_0d |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A758 | 115B | initterm | _initterm |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A772 | 9B | dosmaperr | _dosmaperr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A7E5 | 0B | errno | __errno |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A7EE | 0B | doserrno | ___doserrno |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A809 | 0B | nh_malloc | __nh_malloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A835 | 266B | malloc | _malloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A89C | 9B | unlock_09a | unlock_09a |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A8FB | 47B | unlock_09b | unlock_09b |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A931 | 9B | crt_locked_call4a | _crt_locked_call4a |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001A960 | 47B | fwrite | _fwrite |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AA6A | 232B | crt_locked_call4b | crt_locked_call4b |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AA99 | 215B | fread | _fread |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AB81 | 46B | free | _free |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001ABEB | 9B | unlock_09c | unlock_09c |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AC43 | 47B | unlock_09d | unlock_09d |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AC70 | 9B | alloca_probe | __alloca_probe |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AC9F | 92B | fclose | _fclose |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001ACCD | 59B | flush | __flush |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AD29 | 164B | signal_lock | signal_lock |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AD32 | 56B | flsall | __flsall |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001ADD6 | 254B | crt_locked_putc | crt_locked_putc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AE20 | 193B | strncpy | _strncpy |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AF30 | 128B | strchr | _strchr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001AFF0 | 23B | strstr | _strstr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B070 | 204B | fpmath | __fpmath |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B088 | 111B | init_fptrs | init_fptrs |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B0C0 | 664B | crt_toupper | crt_toupper |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B12F | 34B | toupper | _toupper |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B200 | 13B | memmove2 | _memmove2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B535 | 9B | set_errno | set_errno |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B542 | 39B | rand | _rand |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B564 | 65B | ftol | __ftol |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B58B | 781B | printf | _printf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B5CC | 217B | realloc | _realloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B757 | 11B | unlock_09e | unlock_09e |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B8A5 | 47B | unlock_9 | _unlock_9 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B8FB | 157B | CRT_INIT@12 | __CRT_INIT@12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001B9D4 | 48B | DllMainCRTStartup@12 | __DllMainCRTStartup@12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BA71 | 168B | amsg_exit | __amsg_exit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BAA4 | 35B | ioterm | __ioterm |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BB60 | 47B | lock_stream | _lock_stream |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BB8F | 35B | lock_file | __lock_file |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BBB2 | 43B | unlock_stream | _unlock_stream |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BBE1 | 93B | unlock_file | __unlock_file |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BC04 | 131B | close | __close |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BC61 | 141B | free_osfhnd | __free_osfhnd |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BCE4 | 42B | free_buf | _free_buf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BD0F | 123B | stbuf | __stbuf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BD9C | 53B | crt_cond_cleanup | crt_cond_cleanup |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BDD0 | 368B | strlen | _strlen |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BE4B | 200B | openfile | __openfile |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001BFBB | 280B | getstream | __getstream |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C083 | 1825B | flsbuf | __flsbuf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C19B | 444B | output | __output |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C8DC | 49B | write_char | _write_char |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C911 | 56B | write_multi_char | _write_multi_char |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C942 | 13B | write_string | _write_string |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C97A | 16B | stream_read_dword | _stream_read_dword |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C987 | 14B | stream_read_qword | _stream_read_qword |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C997 | 84B | stream_read_word | _stream_read_word |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001C9A5 | 101B | ioinit | __ioinit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CB61 | 202B | ioterm | _ioterm |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CBB5 | 115B | lseek | __lseek |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CC1A | 194B | lseek_lk | __lseek_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CC8D | 40B | asctime | _asctime |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CD57 | 352B | format_digits | _format_digits |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CD7F | 41B | localtime | _localtime |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CEDF | 97B | loctotime_t | ___loctotime_t |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CFA1 | 108B | crt_delete_cs | crt_delete_cs |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001CFCA | 30B | crt_delete_locks | crt_delete_locks |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D036 | 21B | lock | __lock |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D097 | 84B | unlock | __unlock |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D0AC | 103B | mtinit | __mtinit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D100 | 19B | crt_close_handle | crt_close_handle |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D11E | 27B | set_vtable | set_vtable |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D131 | 160B | getptd | __getptd |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D198 | 328B | freeptd | __freeptd |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D238 | 45B | crt_gfunc_call | crt_gfunc_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D253 | 93B | crt_get_osver | crt_get_osver |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D280 | 168B | heap_select | ___heap_select |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D3C8 | 43B | crt_heap_init | crt_heap_init |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D425 | 72B | heap_term | __heap_term |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D4CD | 809B | sbh_heap_init | ___sbh_heap_init |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D515 | 86B | crt_find_entry | crt_find_entry |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D540 | 777B | sbh_free_block | ___sbh_free_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001D869 | 177B | sbh_alloc_block | ___sbh_alloc_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001DB72 | 251B | sbh_alloc_new_region | ___sbh_alloc_new_region |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001DC23 | 758B | sbh_alloc_new_group | ___sbh_alloc_new_group |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001DD1E | 324B | sbh_resize_block | ___sbh_resize_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E014 | 194B | old_sbh_new_region | ___old_sbh_new_region |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E158 | 69B | sbh_decommit_pages | __sbh_decommit_pages |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E1AE | 87B | old_sbh_decommit_pages | ___old_sbh_decommit_pages |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E270 | 520B | old_sbh_find_block | ___old_sbh_find_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E2C7 | 34B | update_page_entry | update_page_entry |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E30C | 292B | old_sbh_alloc_block | ___old_sbh_alloc_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E514 | 169B | old_sbh_alloc_block_from_page | ___old_sbh_alloc_block_from_page |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E638 | 32B | old_sbh_resize_block | ___old_sbh_resize_block |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E6E4 | 104B | except_handler3 | __except_handler3 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E704 | 35B | seh_filter | _seh_filter |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E726 | 395B | local_unwind2 | __local_unwind2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E78E | 24B | ValidateEH3RN | _ValidateEH3RN |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E7BA | 197B | EH3_save_context | _EH3_save_context |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E7D4 | 27B | exsup | exsup |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E899 | 101B | seh_local_unwind_thunk | seh_local_unwind_thunk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E8B4 | 101B | crt_write_wrap | crt_write_wrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001E919 | 664B | write_lk | __write_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EAB0 | 220B | memmove | _memmove |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EDE5 | 473B | filbuf | __filbuf |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EEC1 | 147B | crt_lseek_wrap | _crt_lseek_wrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001EF26 | 90B | read_lk | __read_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F0FF | 18B | crt_commit | crt_commit |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F192 | 62B | crt_const_call | crt_const_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F1A4 | 41B | IsNonwritableInCurrentImage | ___IsNonwritableInCurrentImage |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F1E2 | 97B | IsProcessorFeaturePresent | __IsProcessorFeaturePresent |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F20B | 78B | forcdecpt | __forcdecpt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F265 | 24B | cropzeros | __cropzeros |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F2B3 | 62B | positive | __positive |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F2CB | 194B | fassign | __fassign |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F309 | 85B | ecvt | __ecvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F36A | 167B | cftoe | __cftoe |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F42C | 147B | fcvt | __fcvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F481 | 81B | cftof | __cftof |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F528 | 37B | cfltcvt_g | ___cfltcvt_g |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F5BB | 511B | cfltcvt | __cfltcvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F60C | 7B | crt_strcpy_advance | _crt_strcpy_advance |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F631 | 117B | crtLCMapStringA | ___crtLCMapStringA |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F855 | 224B | isctype | __isctype |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F8D0 | 436B | CopyCString | CopyCString |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F8E0 | 185B | strcat | _strcat |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001F9C0 | 153B | setenvp | __setenvp |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FA79 | 306B | setargv | __setargv |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FB12 | 57B | parse_cmdline | _parse_cmdline |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FCC6 | 339B | crtGetEnvironmentStringsA | ___crtGetEnvironmentStringsA |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FDF8 | 9B | crt_runtime_error | crt_runtime_error |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FE31 | 289B | NMSG_WRITE | __NMSG_WRITE |  | LIBRARY/EXACT | library_msvc.h |
| 0x1001FF84 | 129B | calloc | _calloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002001D | 9B | unlock_09f | unlock_09f |  | LIBRARY/EXACT | library_msvc.h |
| 0x100200A6 | 127B | unlock_09g | unlock_09g |  | LIBRARY/EXACT | library_msvc.h |
| 0x100200C1 | 291B | fcloseall | __fcloseall |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020142 | 124B | alloc_osfhnd | __alloc_osfhnd |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020265 | 66B | open_osfhandle | __open_osfhandle |  | LIBRARY/EXACT | library_msvc.h |
| 0x100202E1 | 34B | free_osfhnd | free_osfhnd |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020360 | 95B | get_osfhandle | __get_osfhandle |  | LIBRARY/EXACT | library_msvc.h |
| 0x100203A2 | 719B | lock_fhandle | __lock_fhandle |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020401 | 41B | slot_unlock | slot_unlock |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020423 | 68B | slot_check_flag | slot_check_flag |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002044C | 89B | sopen | __sopen |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002071B | 46B | crt_buf_alloc | crt_buf_alloc |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002075F | 105B | wctomb | _wctomb |  | LIBRARY/EXACT | library_msvc.h |
| 0x100207B8 | 104B | wctomb_lk | __wctomb_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020830 | 117B | aulldiv | __aulldiv |  | LIBRARY/EXACT | library_msvc.h |
| 0x100208A0 | 647B | aullrem | __aullrem |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020915 | 33B | crt_once_init | crt_once_init |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020943 | 56B | tzset | __tzset |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020BCA | 428B | crt_locked_call | _crt_locked_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020BEB | 320B | isindst_lk | __isindst_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020D97 | 266B | cvtdate | cvtdate |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020ED7 | 23B | gmtime_lk | _gmtime_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020FE1 | 517B | call_with_zero | call_with_zero |  | LIBRARY/EXACT | library_msvc.h |
| 0x10020FF8 | 22B | strtoxl | _strtoxl |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021200 | 88B | strncmp | _strncmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021240 | 53B | memset | _memset |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021298 | 203B | controlfp | __controlfp |  | LIBRARY/EXACT | library_msvc.h |
| 0x100212CD | 146B | clear_bit_call | clear_bit_call |  | LIBRARY/EXACT | library_msvc.h |
| 0x100212E3 | 137B | crt_cvt_osflag | crt_cvt_osflag |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021375 | 111B | abstract_cw | _abstract_cw |  | LIBRARY/EXACT | library_msvc.h |
| 0x100213FE | 73B | crt_tolower_wrapper | crt_tolower_wrapper |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002146D | 364B | tolower | __tolower |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021538 | 86B | check_bits_clear | _check_bits_clear |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021581 | 140B | set_bit_range | set_bit_range |  | LIBRARY/EXACT | library_msvc.h |
| 0x100215D7 | 27B | sbh_dealloc_bitmap | ___sbh_dealloc_bitmap |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021663 | 12B | copy_3dwords | copy_3dwords |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002167E | 27B | zero_12bytes | zero_12bytes |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002168A | 141B | check_all_zero | check_all_zero |  | LIBRARY/EXACT | library_msvc.h |
| 0x100216A5 | 22B | sbh_bitmap_shift | ___sbh_bitmap_shift |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021732 | 45B | ld12tod | __ld12tod |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002189E | 22B | wrapper_ctx1 | wrapper_ctx1 |  | LIBRARY/EXACT | library_msvc.h |
| 0x100218B4 | 74B | wrapper_ctx2 | wrapper_ctx2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x100218CA | 45B | atodbl | __atodbl |  | LIBRARY/EXACT | library_msvc.h |
| 0x100218F7 | 119B | atoldbl | __atoldbl |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021924 | 92B | fptostr | __fptostr |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002199B | 182B | fltout2 | __fltout2 |  | LIBRARY/EXACT | library_msvc.h |
| 0x100219F7 | 9B | dtold | ___dtold |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021AAD | 129B | fptrap | __fptrap |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021AC0 | 62B | strcmp | _strcmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021B50 | 58B | strcspn | _strcspn |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021B90 | 318B | strpbrk | _strpbrk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021BCA | 429B | crtGetStringTypeA | ___crtGetStringTypeA |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021D13 | 293B | setmbcp | __setmbcp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021EC0 | 51B | crtGetACP_getcodepage | __crtGetACP_getcodepage |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021F0A | 41B | code_translate | code_translate |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021F3D | 389B | CrtIoInfoInit | CrtIoInfoInit |  | LIBRARY/EXACT | library_msvc.h |
| 0x10021F66 | 28B | setSBUpLow | _setSBUpLow |  | LIBRARY/EXACT | library_msvc.h |
| 0x100220EB | 137B | crt_cinit_once | _crt_cinit_once |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022107 | 33B | crtLoadWinAPI | __crtLoadWinAPI |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022190 | 139B | chsize_lk | __chsize_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x100222B5 | 125B | atoi | _atoi |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022340 | 94B | getenv | _getenv |  | LIBRARY/EXACT | library_msvc.h |
| 0x100223BD | 208B | overflow_add | overflow_add |  | LIBRARY/EXACT | library_msvc.h |
| 0x100223DE | 46B | add_12 | ___add_12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002243C | 45B | shl_12 | ___shl_12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002246A | 1185B | shr_12 | ___shr_12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022497 | 0B | ld12cvt | ___ld12cvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002255E | 659B | strgtold12 | ___strgtold12 |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022A2F | 257B | ld12cvt | __ld12cvt |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022CD0 | 27B | stricmp | __stricmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022DA0 | 110B | strnicmp | __strnicmp |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022EA1 | 25B | setmode_lk | __setmode_lk |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F10 | 63B | allmul | __allmul |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F29 | 110B | allmul_slow | __allmul_slow |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F44 | 597B | mbsnbicoll | __mbsnbicoll |  | LIBRARY/EXACT | library_msvc.h |
| 0x10022F83 | 124B | wenvsetup | __wenvsetup |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023211 | 88B | mantold_shl | _mantold_shl |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002328D | 150B | crtCompareStringA | ___crtCompareStringA |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023535 | 100B | crtsetenv | ___crtsetenv |  | LIBRARY/EXACT | library_msvc.h |
| 0x100236BC | 103B | crt_env_search | _crt_env_search |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023714 | 0B | copy_environ | _copy_environ |  | LIBRARY/EXACT | library_msvc.h |
| 0x1002377B | 40B | mbschr | __mbschr |  | LIBRARY/EXACT | library_msvc.h |
| 0x10023812 | 0B | strdup | __strdup |  | LIBRARY/EXACT | library_msvc.h |

## ZLIB (52 functions)

| VA | Size | Name | Symbol | Flags | Match | File |
|-----|------|------|--------|-------|-------|------|
| 0x10001000 | 309B | adler32 | adler32 |  | LIBRARY/EXACT | library_zlib.h |
| 0x100011F0 | 505B | crc32_update | crc32_update |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001330 | 115B | deflateInit2_ | deflateInit2_ |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001530 | 685B | deflateReset | deflateReset |  | LIBRARY/EXACT | library_zlib.h |
| 0x100015B0 | 47B | deflate | deflate |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001860 | 114B | putShortMSB | putShortMSB |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001890 | 170B | flush_pending | flush_pending |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001910 | 147B | deflateEnd | deflateEnd |  | LIBRARY/EXACT | library_zlib.h |
| 0x100019C0 | 343B | lm_init | lm_init |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001A60 | 290B | deflate_stored | deflate_stored |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001BC0 | 113B | fill_window | fill_window |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001CF0 | 813B | read_buf | read_buf |  | LIBRARY/EXACT | library_zlib.h |
| 0x10001D70 | 367B | deflate_fast | deflate_fast |  | LIBRARY/EXACT | library_zlib.h |
| 0x100020A0 | 1066B | longest_match | longest_match |  | LIBRARY/EXACT | library_zlib.h |
| 0x10002210 | 332B | deflate_slow | deflate_slow |  | LIBRARY/EXACT | library_zlib.h |
| 0x100036D0 | 559B | check_header | check_header |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003960 | 123B | gzread | gzread |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003D20 | 160B | inflate_blocks_reset | inflate_blocks_reset |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003DA0 | 3385B | inflate_blocks_new | inflate_blocks_new |  | LIBRARY/EXACT | library_zlib.h |
| 0x10003E40 | 57B | inflate_blocks | inflate_blocks |  | LIBRARY/EXACT | library_zlib.h |
| 0x10004B40 | 1988B | inflate_blocks_free | inflate_blocks_free |  | LIBRARY/EXACT | library_zlib.h |
| 0x10004BC0 | 911B | inflate_fast | inflate_fast |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005390 | 66B | inflate_codes | inflate_codes |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005720 | 72B | inflateReset | inflateReset |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005770 | 270B | inflateEnd | inflateEnd |  | LIBRARY/EXACT | library_zlib.h |
| 0x100057C0 | 1072B | inflateInit2_ | inflateInit2_ |  | LIBRARY/EXACT | library_zlib.h |
| 0x100058D0 | 163B | inflate | inflate |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005D00 | 1225B | inflate_trees_bits | inflate_trees_bits |  | LIBRARY/EXACT | library_zlib.h |
| 0x10005DB0 | 393B | huft_build | huft_build |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006280 | 46B | inflate_trees_dynamic | inflate_trees_dynamic |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006410 | 306B | inflate_trees_fixed | inflate_trees_fixed |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006440 | 108B | inflate_flush | inflate_flush |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006EC0 | 1B | tr_init | _tr_init |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006F30 | 102B | tr_static_init | tr_static_init |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006F40 | 157B | init_block | init_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x10006FB0 | 597B | tr_stored_block | _tr_stored_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007050 | 494B | tr_align | _tr_align |  | LIBRARY/EXACT | library_zlib.h |
| 0x100072B0 | 563B | tr_flush_block | _tr_flush_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x100074A0 | 209B | build_tree | build_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x100076E0 | 545B | pqdownheap | pqdownheap |  | LIBRARY/EXACT | library_zlib.h |
| 0x100077C0 | 115B | gen_bitlen | gen_bitlen |  | LIBRARY/EXACT | library_zlib.h |
| 0x100079F0 | 111B | gen_codes | gen_codes |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007A70 | 231B | build_bl_tree | build_bl_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007AE0 | 613B | scan_tree | scan_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007BD0 | 1397B | send_all_trees | send_all_trees |  | LIBRARY/EXACT | library_zlib.h |
| 0x10007E40 | 1083B | send_tree | send_tree |  | LIBRARY/EXACT | library_zlib.h |
| 0x100083C0 | 116B | compress_block | compress_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x10008800 | 139B | set_data_type | set_data_type |  | LIBRARY/EXACT | library_zlib.h |
| 0x100088A0 | 124B | bi_flush | bi_flush |  | LIBRARY/EXACT | library_zlib.h |
| 0x10008930 | 151B | bi_windup | bi_windup |  | LIBRARY/EXACT | library_zlib.h |
| 0x100089B0 | 19B | copy_block | copy_block |  | LIBRARY/EXACT | library_zlib.h |
| 0x100092E0 | 0B | zcalloc | zcalloc |  | LIBRARY/EXACT | library_zlib.h |

## Unmatched Functions (0 remaining)

| VA | Size | Name |
|-----|------|---------|
