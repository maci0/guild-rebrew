#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../game/entity.h"
#include "../game/production.h"
#include "../game/friedhof.h"
#include "../auxillary/auxillary.h"
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

/* Module-specific external strings and data */
extern char s_D__Develop_DieGildeAddOn_command_1002d70c[];
extern char s_cm_ChkMoveCredits_Not_enough_money_at_source_1002c774[];
extern char s_cm_ChkMoveCredits_Invalid_quell_besitzer_id_1002c7a4[];
extern char s_cm_ChkSellObjekt_Invalid_quell_besitzer_id_1002c8dc[];
extern char s_cm_ChkSellObjekt_No_Objekts_at_source_1002c8b4[];
extern char s_cm_ChkSellObjekt_Not_enough_Objekts_at_source_1002c884[];
extern char s_cm_ChkSellObjekt_Invalid_ziel_besitzer_id_1002c854[];
extern char s_cm_ChkSellObjekt_Inventory_voll_1002c810[];
extern char s_cm_ChkSellObjekt_Lager_voll_1002c834[];
extern char s_cm_ChkChangeAttribute_Invalid_Id_1002c9e0[];
extern char s_cm_ChkChangeAttribute_Invalid_action_on_player_Change_ID_1002c9a0[];
extern char s_cm_ChkChangeAttribute_Invalid_action_on_player_ID_does_not_exist_1002c958[];
extern char s_cm_ChkChangeAttribute_Invalid_action_on_player_PartnerID_already_set_1002c90c[];
extern char s_cm_ChkChangeBits_Invalid_Id_1002ca54[];
extern char s_cm_ChkChangeBits_Invalid_action_on_player_flags_pef_GELIEBTE_already_set_1002ca04[];
extern char s_cm_ChkSetGebBesitzer_Invalid_Id_or_inavlid_status_1002ca74[];
extern char s_cm_ChkCutsceneReady_failed_1002caa8[];
extern char s_Invalid_Commandtype_in_Execution_1002cacc[];
extern char s_Invalid__eigentuemer_id__for_cmd_1002caf0[];
extern char s_gm_AllocGebaeude___failed_1002cb34[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50[];
extern char s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c[];
extern char s_ClientSpieler_erzeugt_1002cbbc[];
extern char s_gm_AllocSpieler___failed_1002cbd4[];
extern char s_cm_ExChangePlayerIdentity___exec_1002cc14[];
extern char s_cm_ExChangePlayerIdentity___fail_1002cbf0[];
extern char s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c[];
extern char s_cm_ExFree____Can_t_free_Objects_1002cc3c[];
extern char s_cm_ExSellObjekt___Invalid__quell_1002cec4[];
extern char s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90[];
extern char s_cm_ExProdObjekt___Invalid__lager_1002cf9c[];
extern char s_cm_ExProdObjekt___Lager_has_wron_1002cf74[];
extern char s_cm_ExProdObjekt___Lager_hat_kein_1002cf48[];
extern char s_cm_ExProdObjekt___Rohstoff_versc_1002cef4[];
extern char s_cm_ExMoveObjekt___Invalid__quell_1002d024[];
extern char s_cm_ExMoveObjekt___Invalid__ziel__1002cff4[];
extern char s_cm_ExMoveObjekt___Object_not_fou_1002cfc4[];
extern char s_cm_ExClearLagerslot___Invalid__L_1002d088[];
extern char s_cm_ExClearLagerslot___Lager_has_n_1002d054[];
extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];
extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];
extern char s_cm_ExChangeDesire___Invalid_Id_1002d0f4[];
extern char s_cm_ExChangeBits___Invalid_Id_1002d114[];
extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];
extern char s_cm_ExKillSpieler___Could_not_fin_1002d154[];
extern char s_cm_ExAllocThemaPredigt____Execut_1002d184[];
extern char s_cm_ExSetGebBesitzer____Could_not_1002d214[];
extern char s_cm_ExSetGebBesitzer____Could_not_1002d1a8[];
extern char s_cm_ExSetGebBesitzer____Could_not_1002d1e0[];
extern char s_cm_ExSetWohnsitz____Could_not_fi_1002d298[];
extern char s_cm_ExSetWohnsitz____Residence_is_1002d240[];
extern char s_cm_ExSetWohnsitz____Could_not_fi_1002d268[];
extern char s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec[];
extern char s_cm_ExSetGebUpgrade____already_hi_1002d2c0[];
extern char s_cm_ExEmployWorker____Illegal_geb_1002d33c[];
extern char s_cm_ExEmployWorker____Illegal_gw__1002d318[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394[];
extern char s_cm_ExAllocCharacter___gm_AllocSp_1002d364[];
extern char s_cm_ExKillTransporter____invalid_t_1002d3d4[];
extern char s_cm_ExCreateGeb____Could_not_find_1002d41c[];
extern char s_cm_ExCreateGeb____failed_1002d400[];

/* Helper functions (unit types or internal) */
extern int __cdecl get_field_by_type(char* cmd, int field_id);
extern int __cdecl QueryEntitySum(int, unsigned int);
extern void* __cdecl StartEntityQuery(int, int, int, ...);
extern int __cdecl CheckInventoryCapacity(char* obj, unsigned int type, int count);
extern short* __cdecl ResolveParentEntity(short* param_1);
extern void* __cdecl find_obj(int, int, int);
extern int __cdecl ValidateCommand(char*);
extern void* __cdecl StartFilteredEntitySearch(int one1, int one2, int entity_id);
extern void* __cdecl AllocGebaeude(unsigned int type, unsigned int owner);
extern short* __cdecl GetEntityTableEntry(char*);
extern int __cdecl ChangePlayerIdentityImpl(int, int);
extern int __cdecl CleanupBuildingEntity(unsigned char*);
extern void* __cdecl sim_CreateCitizen(char, unsigned int, int, unsigned char, unsigned char);
extern void __cdecl priority_update(char*, char*);
extern void __cdecl reset_entity_state(char*);
extern void __cdecl SetBuildingWorkerLimits(unsigned char*);
extern void __cdecl gm_AllocBuildingDefaults(unsigned char*);
extern void __cdecl RefreshMarketAvailability(unsigned int);
extern void __cdecl RemoveEntityLink(int);
extern void* __cdecl NextEntityQueryMatch();
extern void* __cdecl FindEntityByOwner(int);
extern int __cdecl LookupEntityRecordById(int);
extern void* __cdecl FindRecordById(int);
extern void __cdecl crt_thread_set_alt(int);
extern void* __cdecl search_table_67(int);
extern int __cdecl ValidateOfficeCandidate(int*);
extern int __cdecl ExecuteOfficeAssignment(char*);
extern int __cdecl ValidateAndAssignOffice(unsigned int*);
extern int __cdecl SwapOfficeHolders(int*);
extern int __cdecl RemoveLinkedNodeById(int*, int);
extern int __cdecl check_flag(char*);
extern void __cdecl StartEntityQueryByType(unsigned char*);
extern void* __cdecl QueryEntityBuildingType(int);
extern void* __cdecl AllocGameObject(int, int, int);
extern void* __cdecl AllocBuildingContents(void*, int);
extern int __cdecl gm_AllocSpieler(int);
extern int __cdecl SubObjekt(void*, int, int);
extern int __cdecl AssignProductionSlot(int);
extern int __cdecl HireProductionWorker(int);
extern uint __cdecl ExtendProductionTime(void*);
extern int __cdecl ReplaceProductionWorker(unsigned char*);
extern uint __cdecl UpdateProductionProgress(unsigned char*);
extern uint __cdecl ValidateEntityAction(unsigned char*);
extern uint __cdecl MoveSlotEntry(int);
extern void __cdecl ClampFloatValue(int, int);
extern void __cdecl FireEntityAndCleanup(int, int*, int);
extern void __cdecl ApplyColorComponent(char*, char*);
extern void __cdecl search_and_set(SRC*, TGT*);
extern int __cdecl CreateEntityFromParents(uint, int, int, uint, int);

/* Module Globals */
extern int g_timestamp_0b6c;
extern int g_something_1;
extern int g_sequence_counter;
extern int g_entity_id_start;
extern int g_mem_pool_overflow_flag;
extern unsigned char g_current_season;
extern PlayerSlot g_player_slot_0[8];
extern short g_static_entity_table_358a0;
extern char g_static_entity0_owner_id;
extern char g_entity_state_base;
extern char g_entity_type_table;
extern char g_work_building_ptrs;
extern char g_entity_table_end;
extern char g_currency_type_array;
extern int g_next_object_id;
extern char* g_game_initialized;
extern float _g_stat_min;
extern float _g_stat_max;
extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern char g_empty_string;

/* 0x1000cb20 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 171
// SYMBOL: _cm_ChkMoveCredits
// FUNCTION: SERVER 0x1000cb20
int __cdecl cm_ChkMoveCredits(int param_1, char *param_2)
{
  int iVar1; int iVar2; int *piVar3; unsigned int line; char *msg; void *local_8; void *local_4;
  iVar1 = param_1;
  if (*(int *)(param_1 + 0x14) == -1) return 0;
  iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14));
  *(int *)(iVar1 + 0x14) = iVar2;
  iVar2 = ResolveEntityById((void **)&param_1,&local_8,&local_4,iVar2);
  if (iVar2 == 0) { msg = s_cm_ChkMoveCredits_Invalid_quell_besitzer_id_1002c7a4; line = 0x22f9; }
  else {
    if (param_1 == 0) {
      if (local_8 == (void *)0x0) piVar3 = (int *)((int)local_4 + 0x178);
      else piVar3 = (int *)((int)local_8 + 0x14);
    }
    else piVar3 = (int *)(param_1 + 0x5d);
    iVar2 = QueryEntitySum(*piVar3, *(unsigned char *)(iVar1 + 0x1c));
    if (-1 < iVar2 - *(int *)(iVar1 + 0x1d)) return 0;
    msg = s_cm_ChkMoveCredits_Not_enough_money_at_source_1002c774; line = 0x231b;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,line,msg,1);
  return 1;
}

/* 0x1000cbd0 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 517
// SYMBOL: _cm_ChkSellObjekt
// FUNCTION: SERVER 0x1000cbd0
int __cdecl cm_ChkSellObjekt(char *cmd)
{
  short sVar1; int iVar2; int *piVar3; ushort *puVar4; unsigned int line; char *pcVar6; short *local_c; void *local_8; void *local_4;
  pcVar6 = cmd;
  if (*(int *)(cmd + 0x14) != -1) {
    iVar2 = get_field_by_type(cmd,*(int *)(cmd + 0x14));
    *(int *)(pcVar6 + 0x14) = iVar2;
    iVar2 = ResolveEntityById(&local_8,(void **)&cmd,(void **)&local_c,iVar2);
    if (iVar2 == 0) { pcVar6 = s_cm_ChkSellObjekt_Invalid_quell_besitzer_id_1002c8dc; line = 0x236b; goto LAB_1000cdb7; }
    if (local_8 == (void *)0x0) {
      if (cmd == (char *)0x0) piVar3 = (int *)(local_c + 0xbc);
      else piVar3 = (int *)(cmd + 0x14);
    }
    else piVar3 = (int *)((int)local_8 + 0x5d);
    puVar4 = (ushort *)StartEntityQuery(*piVar3,1,0,(uint)*(ushort *)(pcVar6 + 0x18));
    if (puVar4 == (ushort *)0x0) { pcVar6 = s_cm_ChkSellObjekt_No_Objekts_at_source_1002c8b4; line = 0x2383; goto LAB_1000cdb7; }
    if (*(int *)(puVar4 + 7) < *(int *)(pcVar6 + 0x1f)) { pcVar6 = s_cm_ChkSellObjekt_Not_enough_Objekts_at_source_1002c884; line = 0x238f; goto LAB_1000cdb7; }
  }
  if (*(int *)(pcVar6 + 0x10) != -1) {
    iVar2 = get_field_by_type(pcVar6,*(int *)(pcVar6 + 0x10));
    *(int *)(pcVar6 + 0x10) = iVar2;
    iVar2 = ResolveEntityById(&local_4,(void **)&cmd,(void **)&local_c,iVar2);
    if (iVar2 == 0) { pcVar6 = s_cm_ChkSellObjekt_Invalid_ziel_besitzer_id_1002c854; line = 0x23ab; goto LAB_1000cdb7; }
    if (local_4 == (void *)0x0) {
      if (cmd == (char *)0x0) {
        iVar2 = CheckInventoryCapacity((char *)local_c,(uint)*(ushort *)(pcVar6 + 0x18),*(int *)(pcVar6 + 0x1f));
        if (iVar2 < *(int *)(pcVar6 + 0x1f)) { pcVar6 = s_cm_ChkSellObjekt_Inventory_voll_1002c810; line = 0x23e3; goto LAB_1000cdb7; }
      }
      else {
        sVar1 = *(short *)cmd;
        if ((((sVar1 == 0x2a) || (sVar1 == 0x116)) || (sVar1 == 0x1dd)) && (iVar2 = gm_KannObjektHergestellt((int)cmd,(uint)*(ushort *)(pcVar6 + 0x18),*(int *)(pcVar6 + 0x1f)), iVar2 < *(int *)(pcVar6 + 0x1f))) { pcVar6 = s_cm_ChkSellObjekt_Lager_voll_1002c834; line = 0x23cd; goto LAB_1000cdb7; }
        local_c = ResolveParentEntity((short *)cmd);
      }
    }
  }
  return 0;
LAB_1000cdb7:
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,line,pcVar6,1);
  return 1;
}

/* 0x1000cde0 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 331
// SYMBOL: _cm_ChkChangeAttribute
// FUNCTION: SERVER 0x1000cde0
int __cdecl cm_ChkChangeAttribute(int param_1, char *param_2)
{
  char cVar1; int iVar2; int *piVar3; int iVar4; void *pvVar5; void *pvVar6; ushort *puVar7; int *piVar8; uint line; char *msg; void *local_10; uint local_c; void *local_8; void *local_4;
  iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
  *(int *)(param_1 + 0x10) = iVar2;
  iVar2 = ResolveEntityById(&local_8,&local_4,&local_10,iVar2);
  if (iVar2 == 0) { msg = s_cm_ChkChangeAttribute_Invalid_Id_1002c9e0; line = 0x243d;
LAB_1000cf11:
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,line,msg,1);
    return 1;
  }
  pvVar6 = local_8;
  if ((local_8 == (void *)0x0) && (pvVar6 = local_4, local_4 == (void *)0x0)) pvVar6 = local_10;
  piVar8 = (int *)(param_1 + 0x15); local_c = 0; pvVar5 = local_10;
  if (*(char *)(param_1 + 0x14) != '\0') {
    do {
      cVar1 = (char)*piVar8; iVar2 = (int)*(char *)((int)piVar8 + 1); puVar7 = (ushort *)((int)piVar8 + 2); piVar8 = piVar8 + 1; piVar3 = (int *)((uint)*puVar7 + (int)pvVar6);
      if (pvVar5 != (void *)0x0) {
        if (piVar3 == (int *)((int)pvVar5 + 4)) { msg = s_cm_ChkChangeAttribute_Invalid_action_on_player_Change_ID_1002c9a0; line = 0x2479; goto LAB_1000cf11; }
        if (piVar3 == (int *)((int)pvVar5 + 0x5c)) {
          iVar4 = LookupEntityRecordById(*piVar8 + *(int *)((int)pvVar5 + 0x5c));
          if (iVar4 == 0) { msg = s_cm_ChkChangeAttribute_Invalid_action_on_player_ID_does_not_exist_1002c958; line = 0x249b; goto LAB_1000cf11; }
          pvVar5 = local_10;
          if ((*(int *)(iVar4 + 0x5c) != -1) && (*(int *)(iVar4 + 0x5c) != *(int *)((int)local_10 + 4))) { msg = s_cm_ChkChangeAttribute_Invalid_action_on_player_PartnerID_already_set_1002c90c; line = 0x24a5; goto LAB_1000cf11; }
        }
      }
      if (cVar1 == '\x01') { if (iVar2 != 0) piVar8 = (int *)((int)piVar8 + iVar2); }
      else if (cVar1 == '\x02') { if (iVar2 != 0) piVar8 = (int *)((int)piVar8 + iVar2 * 2); }
      else if ((cVar1 == '\x04') && (iVar2 != 0)) piVar8 = piVar8 + iVar2;
      local_c = local_c + 1;
    } while (local_c < *(byte *)(param_1 + 0x14));
  }
  return 0;
}

/* 0x1000cf30 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 162
// SYMBOL: _cm_ChkChangeBits
// FUNCTION: SERVER 0x1000cf30
int __cdecl cm_ChkChangeBits(int param_1, char *param_2)
{
  int iVar1; int iVar2; void *pvVar3; uint line; char *msg; void *local_8; void *local_4;
  iVar1 = param_1;
  iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
  *(int *)(iVar1 + 0x10) = iVar2;
  iVar2 = ResolveEntityById((void **)&param_1,&local_4,&local_8,iVar2);
  if (iVar2 == 0) { msg = s_cm_ChkChangeBits_Invalid_Id_1002ca54; line = 0x250d; }
  else {
    pvVar3 = (void *)param_1;
    if ((param_1 == 0) && (pvVar3 = local_4, local_4 == (void *)0x0)) pvVar3 = local_8;
    if ((((local_8 == (void *)0x0) || ((uint *)(*(int *)(iVar1 + 0x14) + (int)pvVar3) != (uint *)((int)local_8 + 0x1c8))) || ((*(uint *)(iVar1 + 0x1c) & 0x800000) == 0)) || ((*(uint *)((int)local_8 + 0x1c8) & 0x800000) == 0)) return 0;
    msg = s_cm_ChkChangeBits_Invalid_action_on_player_flags_pef_GELIEBTE_already_set_1002ca04; line = 0x2533;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,line,msg,1);
  return 1;
}

/* 0x1000cfe0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 64
// SYMBOL: _cm_ChkSetGebBesitzer
// FUNCTION: SERVER 0x1000cfe0
int __cdecl cm_ChkSetGebBesitzer(char *obj)
{
  ushort *puVar1;
  puVar1 = StartFilteredEntitySearch(1,1,*(undefined4 *)(obj + 0x10));
  if ((puVar1 != (ushort *)0x0) && ((puVar1[0x2d] & 2) != 0)) return 0;
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,0x256b,s_cm_ChkSetGebBesitzer_Invalid_Id_or_inavlid_status_1002ca74,1);
  return 1;
}

/* 0x1000d020 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// SYMBOL: _cm_ChkOfficeCandidate
// FUNCTION: SERVER 0x1000d020
int __cdecl cm_ChkOfficeCandidate(void *obj)
{
  int iVar1;
  if (*(int *)((int)obj + 0x10) == -1) return 1;
  iVar1 = ValidateOfficeCandidate((int *)((int)obj + 0x10));
  return (uint)(iVar1 == 0);
}

/* 0x1000d040 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 32
// SYMBOL: _cm_ChkValidateGeneric
// FUNCTION: SERVER 0x1000d040
int __cdecl cm_ChkValidateGeneric(void *param_1, char *param_2)
{
  int iVar1;
  iVar1 = ValidateOfficeCandidate((int *)((int)param_1 + 0x10));
  return (uint)(iVar1 == 0);
}

/* 0x1000d060 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 169
// SYMBOL: _cm_ChkElectionOrTrade
// FUNCTION: SERVER 0x1000d060
int __cdecl cm_ChkElectionOrTrade(int param_1)
{
  ushort *puVar1; int iVar2;
  if (*(int *)(param_1 + 0x10) == 0x636c6572) {
    puVar1 = StartFilteredEntitySearch(1,1,*(unsigned int *)(param_1 + 0x18));
    if (puVar1 != (ushort *)0x0) {
      puVar1 = StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
      if (puVar1 != (ushort *)0x0) return (uint)(g_something_1 - *(int *)(puVar1 + 0x14) < 2);
    }
  }
  else if (*(int *)(param_1 + 0x10) == 0x62757920) {
    puVar1 = StartFilteredEntitySearch(1,1,*(unsigned int *)(param_1 + 0x18));
    if (puVar1 != (ushort *)0x0) {
      puVar1 = StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
      if (puVar1 != (ushort *)0x0) {
        iVar2 = 0; puVar1 = puVar1 + 0xe;
        do {
          if (*(int *)puVar1 == *(int *)(param_1 + 0x1c)) return 0;
          iVar2 = iVar2 + 1; puVar1 = puVar1 + 2;
        } while (iVar2 < 3);
      }
    }
  }
  return 1;
}

/* 0x1000d110 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 333
// SYMBOL: _cm_ChkJoinLeaveElection
// FUNCTION: SERVER 0x1000d110
int __cdecl cm_ChkJoinLeaveElection(int *param_1)
{
  ushort uVar1; ushort *puVar2; ushort *puVar3; int iVar4;
  iVar4 = param_1[4];
  if (iVar4 == 0x6a6f696e) {
    puVar2 = StartFilteredEntitySearch(1,1,param_1[6]);
    if ((puVar2 != (ushort *)0x0) && (puVar2 = StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0)) {
      puVar3 = puVar2 + 0xe; iVar4 = 0;
      do {
        if (*(int *)puVar3 == param_1[5]) return 1;
        iVar4 = iVar4 + 1; puVar3 = puVar3 + 2;
      } while (iVar4 < 4);
      iVar4 = 0;
      do {
        if (*(int *)(puVar2 + iVar4 * 2 + 0xe) == -1) return 0;
        iVar4 = iVar4 + 1;
      } while (iVar4 < 4);
    }
  }
  else if (iVar4 == 0x6c656176) {
    puVar2 = StartFilteredEntitySearch(1,1,param_1[6]);
    if ((puVar2 != (ushort *)0x0) && (puVar2 = StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0)) {
      iVar4 = 0; puVar3 = puVar2 + 0xe;
      while (*(int *)puVar3 != param_1[5]) { iVar4 = iVar4 + 1; puVar3 = puVar3 + 2; if (3 < iVar4) return 1; }
      if (iVar4 < 4) return 0;
    }
  }
  return 1;
}

/* 0x1000ce30 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 91
// SYMBOL: _cm_ExecCommand
// FUNCTION: SERVER 0x1000ce30
int __cdecl cm_ExecCommand(int param_1, char *param_2)
{
  int iVar1;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c;
  iVar1 = ExecuteCommandImpl(param_1);
  if (iVar1 == 0) { if (param_2 != NULL) *param_2 = 1; return 0; }
  return 1;
}

/* 0x1000ce90 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 91
// SYMBOL: _cm_ExAllocRaum
// FUNCTION: SERVER 0x1000ce90
int __cdecl cm_ExAllocRaum(void* param_1, void* param_2)
{
  void* pcVar1;
  *(int *)((int)param_1 + 0x10) = g_timestamp_0b6c;
  pcVar1 = AllocBuildingContents(param_1, 0x154);
  if (pcVar1 != NULL) {
    if (param_2 != NULL) { *(char*)param_2 = 1; *((char*)param_2 + 1) = 2; *(void**)((char*)param_2 + 6) = pcVar1; }
    return 0;
  }
  return 1;
}

/* 0x1000cef0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 91
// SYMBOL: _cm_ExAllocObjekt
// FUNCTION: SERVER 0x1000cef0
int __cdecl cm_ExAllocObjekt(void* param_1, void* param_2)
{
  void* pcVar1;
  *(int *)((int)param_1 + 0x10) = g_timestamp_0b6c;
  pcVar1 = AllocBuildingContents(param_1, 0xca);
  if (pcVar1 != NULL) {
    if (param_2 != NULL) { *(char*)param_2 = 1; *((char*)param_2 + 1) = 2; *(void**)((char*)param_2 + 6) = pcVar1; }
    return 0;
  }
  return 1;
}

/* 0x1000cf50 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 171
// SYMBOL: _cm_ExAllocSpieler
// FUNCTION: SERVER 0x1000cf50
int __cdecl cm_ExAllocSpieler(int param_1, char *param_2)
{
  int iVar1;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c;
  iVar1 = gm_AllocSpieler(param_1);
  if (iVar1 != -1) {
    if (param_2 != NULL) { *param_2 = 1; param_2[1] = 1; *(int*)(param_2 + 6) = iVar1; }
    return 0;
  }
  return 1;
}

/* 0x1000d000 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 78
// SYMBOL: _cm_ExChangePlayerIdentity
// FUNCTION: SERVER 0x1000d000
int __cdecl cm_ExChangePlayerIdentity(int param_1, char *param_2)
{
  int iVar1;
  iVar1 = ChangePlayerIdentityImpl(*(int *)(param_1 + 0x10),*(int *)(param_1 + 0x14));
  if (-1 < iVar1) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,0x299d,s_cm_ExChangePlayerIdentity___exec_1002cc14,1); return 0; }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,0x29a1,s_cm_ExChangePlayerIdentity___fail_1002cbf0,1);
  return 0;
}

/* 0x1000d0a0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExSellObjekt
// FUNCTION: SERVER 0x1000d0a0
int __cdecl cm_ExSellObjekt(int param_1, char *param_2)
{
  TradeCommandHandler((char*)param_1, (uchar*)param_2);
  return 0;
}

/* 0x1000d240 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExProdObjekt
// FUNCTION: SERVER 0x1000d240
int __cdecl cm_ExProdObjekt(int param_1, char *param_2)
{
  cm_ExecProduction(param_1, param_2);
  return 0;
}

/* 0x1000d310 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExMoveObjekt
// FUNCTION: SERVER 0x1000d310
int __cdecl cm_ExMoveObjekt(int param_1, char *param_2)
{
  ExMoveObject(param_1, param_2);
  return 0;
}

/* 0x1000d3d0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExClearLagerslot
// FUNCTION: SERVER 0x1000d3d0
int __cdecl cm_ExClearLagerslot(int param_1, char *param_2)
{
  cm_ExClearLagerslot((short*)param_1, (uchar*)param_2);
  return 0;
}

/* 0x1000d440 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExChangeAttribute
// FUNCTION: SERVER 0x1000d440
int __cdecl cm_ExChangeAttribute(int param_1, char *param_2)
{
  ExAccumulateEntityFields(param_1, param_2);
  return 0;
}

/* 0x1000d490 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExSetAttribute
// FUNCTION: SERVER 0x1000d490
int __cdecl cm_ExSetAttribute(int param_1, char *param_2)
{
  ExWriteEntityFields(param_1, param_2);
  return 0;
}

/* 0x1000d4e0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExChangeDesire
// FUNCTION: SERVER 0x1000d4e0
int __cdecl cm_ExChangeDesire(int param_1, char *param_2)
{
  ExChangeDesire((uchar*)param_1);
  return 0;
}

/* 0x1000d530 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExChangeBits
// FUNCTION: SERVER 0x1000d530
int __cdecl cm_ExChangeBits(int param_1, char *param_2)
{
  ExSetEntityBitmask(param_1, param_2);
  return 0;
}

/* 0x1000d580 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExChangeFloat
// FUNCTION: SERVER 0x1000d580
int __cdecl cm_ExChangeFloat(int param_1, char *param_2)
{
  ExSetEntityField(param_1, param_2);
  return 0;
}

/* 0x1000d5d0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExKillSpieler
// FUNCTION: SERVER 0x1000d5d0
int __cdecl cm_ExKillSpieler(int param_1, char *param_2)
{
  CmdKillPlayer(param_1);
  return 0;
}

/* 0x1000d630 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExAllocThemaPredigt
// FUNCTION: SERVER 0x1000d630
int __cdecl cm_ExAllocThemaPredigt(int param_1, char *param_2)
{
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,0x3a00,s_cm_ExAllocThemaPredigt____Execut_1002d184,1);
  return 0;
}

/* 0x1000d660 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExSetGebBesitzer
// FUNCTION: SERVER 0x1000d660
int __cdecl cm_ExSetGebBesitzer(int param_1, char *param_2)
{
  SetBuildingOwner(param_1, param_2);
  return 0;
}

/* 0x1000d730 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExSetWohnsitz
// FUNCTION: SERVER 0x1000d730
int __cdecl cm_ExSetWohnsitz(int param_1, char *param_2)
{
  SetResidence(param_1, param_2);
  return 0;
}

/* 0x1000d7d0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExSetGebUpgrade
// FUNCTION: SERVER 0x1000d7d0
int __cdecl cm_ExSetGebUpgrade(int param_1, char *param_2)
{
  SetBuildingUpgrade(param_1, param_2);
  return 0;
}

/* 0x1000d850 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExEmployWorker
// FUNCTION: SERVER 0x1000d850
int __cdecl cm_ExEmployWorker(int param_1, char *param_2)
{
  EmployWorkerAtBuilding(param_1, param_2);
  return 0;
}

/* 0x1000d8d0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExAllocCharacter
// FUNCTION: SERVER 0x1000d8d0
int __cdecl cm_ExAllocCharacter(int param_1, char *param_2)
{
  ExCreateCitizenAtBuilding(param_1, param_2);
  return 0;
}

/* 0x1000d980 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExKillTransporter
// FUNCTION: SERVER 0x1000d980
int __cdecl cm_ExKillTransporter(int param_1, char *param_2)
{
  /* cm_ExKillTransporter logic */
  return 0;
}

/* 0x1000d9e0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ExCreateGeb
// FUNCTION: SERVER 0x1000d9e0
int __cdecl cm_ExCreateGeb(int param_1, char *param_2)
{
  CmdCreateBuilding(param_1, param_2);
  return 0;
}
