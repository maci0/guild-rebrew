#include <stdio.h>
#include <string.h>
#include <windows.h>

/* Standard integer types for MSVC6 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned char  byte;
typedef unsigned char  undefined1;

typedef int bool;
#define true 1
#define false 0

/* Forward declarations for missing types */
typedef struct DISPATCH_OBJ {
    int (__cdecl *func)(int, int);
    int field_28;
} DISPATCH_OBJ;

typedef struct PlayerSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char data[0x26425C];
} PlayerSlot;

/* Module Globals */
extern char s_D__Develop_DieGildeAddOn_command_1002d70c[];
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
extern char s_cm_ChkMoveCredits____Not_enough_m_1002c774[];
extern char s_cm_ChkSellObjekt___Invalid__quel_1002c8dc[];
extern char s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4[];
extern char s_cm_ChkSellObjekt___Not_enough_Ob_1002c884[];
extern char s_cm_ChkSellObjekt___Invalid__ziel_1002c854[];
extern char s_cm_ChkSellObjekt___Inventory_vol_1002c810[];
extern char s_cm_ChkSellObjekt___Lager_voll_1002c834[];
extern char s_cm_ChkChangeAttribute___Invalid_I_1002c9e0[];
extern char s_cm_ChkChangeAttribute___Invalid_a_1002c9a0[];
extern char s_cm_ChkChangeAttribute___Invalid_a_1002c958[];
extern char s_cm_ChkChangeAttribute___Invalid_a_1002c90c[];
extern char s_cm_ChkChangeBits___Invalid_Id_1002ca54[];
extern char s_cm_ChkChangeBits___Invalid_actio_1002ca04[];
extern char s_cm_ChkSetGebBesitzer___Invalid_I_1002ca74[];
extern char s_cm_ChkCutsceneReady____failed____1002caa8[];
extern char s_Invalid_Commandtype_in_Execution_1002cacc[];
extern char s_ClientSpieler_erzeugt_1002cbbc[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50[];
extern char s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c[];
extern char s_cm_ExChangePlayerIdentity___exec_1002cc14[];
extern char s_cm_ExChangePlayerIdentity___fail_1002cbf0[];
extern char s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c[];
extern char s_cm_ExFree____Can_t_free_Objects_1002cc3c[];
extern char s_gm_AllocSpieler___failed_1002cbd4[];
extern char s_Invalid__eigentuemer_id__for_cmd_1002caf0[];
extern char s_gm_AllocGebaeude___failed_1002cb34[];
extern char s_cm_ExSellObjekt___Invalid__quell_1002cec4[];
extern char s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90[];
extern char s_cm_ExSellObjekt____Object_not_fo_1002ce4c[];
extern char s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc[];
extern char s_cm_ExSellObjekt___Invalid__ziel__1002cdcc[];
extern char s_cm_ExSellObjekt___Lager_voll_1002cdac[];
extern char s_cm_ExSellObjekt___Not_enough_Cre_1002cd78[];
extern char s_cm_ExSellObjekt____gm_AllocRaum_f_1002ccc0[];
extern char s_cm_ExSellObjekt____gm_AllocObjek_1002cce8[];
extern char s_cm_ExecProduction___Invalid__lager_1002cf9c[];
extern char s_cm_ExecProduction___Lager_has_wron_1002cf74[];
extern char s_cm_ExecProduction___Lager_hat_kein_1002cf48[];
extern char s_cm_ExProdObjekt___Rohstoff_versc_1002cef4[];
extern char s_cm_ExMoveObjekt___Invalid__quell_1002d024[];
extern char s_cm_ExMoveObjekt___Invalid__ziel__1002cff4[];
extern char s_cm_ExMoveObjekt___Object_not_fou_1002cfc4[];
extern char s_cm_ExClearLagerslot___Invalid__L_1002d088[];
extern char s_cm_ExClearLagerslot___Lager_has_n_1002d054[];
extern char s_cm_ExChangeDesire___Invalid_Id_1002d0f4[];
extern char s_cm_ExChangeBits___Invalid_Id_1002d114[];
extern char s_cm_ExKillSpieler___Could_not_fin_1002d154[];
extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];
extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];
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

extern void* g_static_entity_table_358a0;
extern void* g_entity_table_end;
extern int g_something_1;
extern int g_timestamp_0b6c;
extern char g_static_entity0_entity_id[];
extern short g_static_entity0_lineage[];
extern char g_static_entity0_field_60[];
extern int g_static_entity0_field_54[];
extern char g_static_entity0_pos_x[];
extern PlayerSlot g_player_slot_0[8];
extern char g_currency_type_array;
extern void* unknown;
extern char g_empty_string;
extern unsigned char g_current_season;
extern void* g_error_msg_sell_no_source;
extern void* g_error_msg_sell_no_dest;
extern void* g_error_msg_sell_failed;
extern int g_mem_pool_overflow_flag;
extern int _g_game_speed_index;
extern int g_game_speed_value;
extern int g_game_speed_table;
extern int g_sequence_counter;
extern int g_entity_id_start;
extern char g_relationship_matrix_secondary;
extern char g_relationship_matrix_primary;
extern int g_plant_count;
extern char g_entity_type_table[];
extern int g_work_building_ptrs;
extern int g_entity_state_base;

/* Internal Helpers */
extern int __cdecl get_field_by_type(char* cmd, int field_id);
extern int __cdecl ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl QueryEntitySum(int, unsigned int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);
extern void* __cdecl StartEntityQuery(int, int, int, ...);
extern int __cdecl CheckInventoryCapacity(char* obj, unsigned int type, int count);
extern int __cdecl gm_KannObjektHergestellt(int, unsigned int, int);
extern short* __cdecl ResolveParentEntity(short* param_1);
extern void* __cdecl StartFilteredEntitySearch(int one1, int one2, int entity_id);
extern int __cdecl LookupEntityRecordById(int);
extern int __cdecl ValidateOfficeCandidate(int*);
extern int __cdecl ValidateCommand(char*);
extern void* __cdecl AllocGebaeude(uint, uint);
extern void __cdecl crt_thread_set_alt(int);
extern int __cdecl CreateEntityFromParents(uint, int, int, uint, int);
extern short* __cdecl GetEntityTableEntry(char*);
extern int __cdecl ChangePlayerIdentityImpl(int, int);
extern void __cdecl DeallocEntity(uint, int);
extern int __cdecl CleanupBuildingEntity(uchar*);
extern int __cdecl SubObjekt(void*, uint, int);
extern void* __cdecl AddOrAccumulateObject(int, uint, int);
extern void __cdecl SubtractObjectAmountNoKill(int, uint, int);
extern int __cdecl KannObjektHergestellt(char*, uint, int);
extern void* __cdecl FindEntityByOwner(int);
extern int __cdecl compute_size(char*);
extern void __cdecl RemoveObjectWrapper(int, uint);
extern int __cdecl RemoveObjectByType(char**, uint);
extern void* __cdecl AllocBuildingContents(char*, uint);
extern void* __cdecl AllocGameObject(int, uint, int);
extern char* __cdecl FindSlotById(uint, uint);
extern int __cdecl CalculateProductionValue(uint, int);
extern long __cdecl _ftol(void);
extern int __cdecl entity_accumulate(int);
extern int __cdecl RemoveLinkedNodeById(int*, int);
extern char* __cdecl SearchRecordTable(uint);
extern int __cdecl CheckZoneAvailability(int, uint, uint, uint);
extern char* __cdecl FindRecord(char*, uint, uint);
extern void* __cdecl plt_SetPlantMap(int, uint, uint, uint, uint);
extern void __cdecl AssignBuildingOwner(uchar*, ushort, uint);
extern void __cdecl table_lookup(uint, int*);
extern void __cdecl ReportMessage(char*);
extern void __cdecl SetBuildingWorkerLimits(uchar*);
extern void __cdecl gm_AllocBuildingDefaults(uchar*);
extern void __cdecl UpgradeGraveyardField(uint8_t*);
extern void __cdecl RefreshMarketAvailability(uint);
extern void __cdecl RemoveEntityLink(int);
extern ushort* __cdecl NextEntityQueryMatch(void);
extern char* __cdecl sim_CreateCitizen(char, uint, int, uchar, uchar);
extern void __cdecl priority_update(char*, char*);
extern void __cdecl reset_entity_state(char*);
extern void __cdecl StartEntityQueryByType(uchar*);
extern void __cdecl QueryEntityBuildingType(int);
extern uint __cdecl ValidateAndAssignOffice(uint*);
extern int __cdecl ExecuteOfficeAssignment(char*);
extern void* __cdecl FindRecordById(int);

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
  if (iVar2 == 0) { msg = s_cm_ChkMoveCredits____Invalid__qu_1002c7a4; line = 0x22f9; }
  else {
    if (param_1 == 0) {
      if (local_8 == (void *)0x0) piVar3 = (int *)((int)local_4 + 0x178);
      else piVar3 = (int *)((int)local_8 + 0x14);
    }
    else piVar3 = (int *)(param_1 + 0x5d);
    iVar2 = QueryEntitySum(*piVar3, *(unsigned char *)(iVar1 + 0x1c));
    if (-1 < iVar2 - *(int *)(iVar1 + 0x1d)) return 0;
    msg = s_cm_ChkMoveCredits____Not_enough_m_1002c774; line = 0x231b;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
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
    if (iVar2 == 0) { pcVar6 = s_cm_ChkSellObjekt___Invalid__quel_1002c8dc; line = 0x236b; goto LAB_1000cdb7; }
    if (local_8 == (void *)0x0) {
      if (cmd == (char *)0x0) piVar3 = (int *)(local_c + 0xbc);
      else piVar3 = (int *)(cmd + 0x14);
    }
    else piVar3 = (int *)((int)local_8 + 0x5d);
    puVar4 = (ushort *)StartEntityQuery(*piVar3,1,0,(uint)*(ushort *)(pcVar6 + 0x18));
    if (puVar4 == (ushort *)0x0) { pcVar6 = s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4; line = 0x2383; goto LAB_1000cdb7; }
    if (*(int *)(puVar4 + 7) < *(int *)(pcVar6 + 0x1f)) { pcVar6 = s_cm_ChkSellObjekt___Not_enough_Ob_1002c884; line = 0x238f; goto LAB_1000cdb7; }
  }
  if (*(int *)(pcVar6 + 0x10) != -1) {
    iVar2 = get_field_by_type(pcVar6,*(int *)(pcVar6 + 0x10));
    *(int *)(pcVar6 + 0x10) = iVar2;
    iVar2 = ResolveEntityById(&local_4,(void **)&cmd,(void **)&local_c,iVar2);
    if (iVar2 == 0) { pcVar6 = s_cm_ChkSellObjekt___Invalid__ziel_1002c854; line = 0x23ab; goto LAB_1000cdb7; }
    if (local_4 == (void *)0x0) {
      if (cmd == (char *)0x0) {
        iVar2 = CheckInventoryCapacity((char *)local_c,(uint)*(ushort *)(pcVar6 + 0x18),*(int *)(pcVar6 + 0x1f));
        if (iVar2 < *(int *)(pcVar6 + 0x1f)) { pcVar6 = s_cm_ChkSellObjekt___Inventory_vol_1002c810; line = 0x23e3; goto LAB_1000cdb7; }
      }
      else {
        sVar1 = *(short *)cmd;
        if ((((sVar1 == 0x2a) || (sVar1 == 0x116)) || (sVar1 == 0x1dd)) && (iVar2 = gm_KannObjektHergestellt((int)cmd,(uint)*(ushort *)(pcVar6 + 0x18),*(int *)(pcVar6 + 0x1f)), iVar2 < *(int *)(pcVar6 + 0x1f))) { pcVar6 = s_cm_ChkSellObjekt___Lager_voll_1002c834; line = 0x23cd; goto LAB_1000cdb7; }
        local_c = ResolveParentEntity((short *)cmd);
      }
    }
    else {
        if (*(ushort *)((int)local_4 + 0x27) == 0xffff) local_c = (short *)0x0;
        else local_c = (short*)((int)g_static_entity_table_358a0 + (uint)*(ushort *)((int)local_4 + 0x27) * 0x10e);
    }
  }
  return 0;
LAB_1000cdb7:
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,pcVar6,1);
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
  if (iVar2 == 0) { msg = s_cm_ChkChangeAttribute___Invalid_I_1002c9e0; line = 0x243d;
LAB_1000cf11:
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
    return 1;
  }
  pvVar6 = local_8;
  if ((local_8 == (void *)0x0) && (pvVar6 = local_4, local_4 == (void *)0x0)) pvVar6 = local_10;
  piVar8 = (int *)(param_1 + 0x15); local_c = 0; pvVar5 = local_10;
  if (*(char *)(param_1 + 0x14) != '\0') {
    do {
      cVar1 = (char)*piVar8; iVar2 = (int)*(char *)((int)piVar8 + 1); puVar7 = (ushort *)((int)piVar8 + 2); piVar8 = piVar8 + 1; piVar3 = (int *)((uint)*puVar7 + (int)pvVar6);
      if (pvVar5 != (void *)0x0) {
        if (piVar3 == (int *)((int)pvVar5 + 4)) { msg = s_cm_ChkChangeAttribute___Invalid_a_1002c9a0; line = 0x2479; goto LAB_1000cf11; }
        if (piVar3 == (int *)((int)pvVar5 + 0x5c)) {
          iVar4 = LookupEntityRecordById(*piVar8 + *(int *)((int)pvVar5 + 0x5c));
          if (iVar4 == 0) { msg = s_cm_ChkChangeAttribute___Invalid_a_1002c958; line = 0x249b; goto LAB_1000cf11; }
          pvVar5 = local_10;
          if ((*(int *)(iVar4 + 0x5c) != -1) && (*(int *)(iVar4 + 0x5c) != *(int *)((int)local_10 + 4))) { msg = s_cm_ChkChangeAttribute___Invalid_a_1002c90c; line = 0x24a5; goto LAB_1000cf11; }
        }
      }
      if (cVar1 == '\x01') { if (iVar2 != 0) piVar8 = (int *)((int)piVar8 + iVar2); }
      else if (cVar1 == '\x02') { if (iVar2 != 0) piVar8 = (int *)((int)piVar8 + iVar2 * 2); }
      else if ((cVar1 == '\x04') && (iVar2 != 0)) piVar8 = piVar8 + iVar2;
      local_c = local_c + 1;
    } while (local_c < *(unsigned char *)(param_1 + 0x14));
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
  if (iVar2 == 0) { msg = s_cm_ChkChangeBits___Invalid_Id_1002ca54; line = 0x250d; }
  else {
    pvVar3 = (void *)param_1;
    if ((param_1 == 0) && (pvVar3 = local_4, local_4 == (void *)0x0)) pvVar3 = local_8;
    if ((((local_8 == (void *)0x0) || ((uint *)(*(int *)(iVar1 + 0x14) + (int)pvVar3) != (uint *)((int)local_8 + 0x1c8))) || ((*(uint *)(iVar1 + 0x1c) & 0x800000) == 0)) || ((*(uint *)((int)local_8 + 0x1c8) & 0x800000) == 0)) return 0;
    msg = s_cm_ChkChangeBits___Invalid_actio_1002ca04; line = 0x2533;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
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
  puVar1 = (ushort *)StartFilteredEntitySearch(1,1,*(int *)(obj + 0x10));
  if ((puVar1 != (ushort *)0x0) && ((puVar1[0x2d] & 2) != 0)) return 0;
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x256b,s_cm_ChkSetGebBesitzer___Invalid_I_1002ca74,1);
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
// SIZE: 22
// SYMBOL: _cm_ChkValidateGeneric
// FUNCTION: SERVER 0x1000d040
int __cdecl cm_ChkValidateGeneric(void *param_1, char *param_2)
{
  int iVar1;
  iVar1 = ValidateCommand((char *)((int)param_1 + 0x10));
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
    puVar1 = (ushort *)StartFilteredEntitySearch(1,1,*(unsigned int *)(param_1 + 0x18));
    if (puVar1 != (ushort *)0x0) {
      puVar1 = (ushort *)StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
      if (puVar1 != (ushort *)0x0) return (uint)(g_something_1 - *(int *)(puVar1 + 0x14) < 2);
    }
  }
  else if (*(int *)(param_1 + 0x10) == 0x62757920) {
    puVar1 = (ushort *)StartFilteredEntitySearch(1,1,*(unsigned int *)(param_1 + 0x18));
    if (puVar1 != (ushort *)0x0) {
      puVar1 = (ushort *)StartEntityQuery(*(int *)((int)puVar1 + 0x5d),2,6,0,300);
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
    puVar2 = (ushort *)StartFilteredEntitySearch(1,1,param_1[6]);
    if ((puVar2 != (ushort *)0x0) && (puVar2 = (ushort *)StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0)) {
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
    puVar2 = (ushort *)StartFilteredEntitySearch(1,1,param_1[6]);
    if ((puVar2 != (ushort *)0x0) && (puVar2 = (ushort *)StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0)) {
      iVar4 = 0; puVar3 = puVar2 + 0xe;
      while (*(int *)puVar3 != param_1[5]) { iVar4 = iVar4 + 1; puVar3 = puVar3 + 2; if (3 < iVar4) return 1; }
      if (iVar4 < 4) return 0;
    }
  }
  return 1;
}

/* 0x1000d260 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 120
// SYMBOL: _cm_ChkCutsceneReady
// FUNCTION: SERVER 0x1000d260
int __cdecl cm_ChkCutsceneReady(char *obj)
{
  int entity_ptr; int *id_ptr; int i;
  if (*(int *)(obj + 0x10) == -1) return 1;
  i = 0; id_ptr = (int *)(obj + 0x14);
  while( 1 ) {
    entity_ptr = LookupEntityRecordById(*id_ptr);
    if (((entity_ptr != 0) && (((*(char *)(entity_ptr + 2) == '\x06' || (*(char *)(entity_ptr + 2) == '\a')) && (*(int *)(entity_ptr + 0x20c) != -1)))) && (*(int *)(entity_ptr + 0x20c) != *(int *)(obj + 0x10))) break;
    i = i + 1; id_ptr = id_ptr + 1;
    if (0xf < i) return 0;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c,0x26db,s_cm_ChkCutsceneReady____failed____1002caa8,1);
  return 1;
}

/* 0x1000d2e0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 77
// SYMBOL: _validate_command_type
// FUNCTION: SERVER 0x1000d2e0
int __cdecl validate_command_type(char *cmd, char *result)
{
  char cVar1;
  cVar1 = *cmd;
  if ((((cVar1 != '\0') && (cVar1 != '\x05')) && (cVar1 != '\x06')) && (cVar1 != '\a')) {
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x270b,s_Invalid_Commandtype_in_Execution_1002cacc,1);
    printf(s_Invalid_Commandtype_in_Execution_1002cacc);
    return 1;
  }
  if (result != (char *)0x0) *result = '\x01';
  return 0;
}

/* 0x1000d330 */
// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 14
// SYMBOL: _MarkAndReturn
// FUNCTION: SERVER 0x1000d330
int __cdecl MarkAndReturn(int param_1, char *param_2)
{
  if (param_2 != (char *)0x0) *param_2 = '\x01';
  return 0;
}

/* 0x1000d340 */
// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 6
// SYMBOL: _RejectCommand
// FUNCTION: SERVER 0x1000d340
int __cdecl RejectCommand(void)
{
  return 1;
}

/* 0x1000d350 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 267
// SYMBOL: _CmdAllocBuilding
// FUNCTION: SERVER 0x1000d350
int __cdecl CmdAllocBuilding(int param_1, char *param_2)
{
  char *pcVar1; uint uVar2; int iVar3; uint uVar4; uint *puVar5; char *pcVar6;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c;
  if (*(int *)(param_1 + 0x16) == -1) {
    uVar4 = 0xffff;
LAB_1000d36b:
    pcVar1 = (char*)AllocGebaeude(*(uchar*)(param_1 + 0x14), uVar4);
    if (pcVar1 != (char *)0x0) {
      *(int *)(g_player_slot_0[*(unsigned char *)(param_1 + 3)].data + 0x2641fc) = *(int *)(pcVar1 + 1);
      *(short *)(pcVar1 + 0x5a) = *(short *)(param_1 + 0x1a);
      if (*(int *)(param_1 + 0x1c) != 0) {
        puVar5 = (uint *)(param_1 + 0x20); pcVar6 = pcVar1 + 0x65;
        for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) { *(uint *)pcVar6 = *puVar5; puVar5 = puVar5 + 1; pcVar6 = pcVar6 + 4; }
      }
      if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\x02'; *(char **)(param_2 + 6) = pcVar1; }
      return 0;
    }
    pcVar1 = s_gm_AllocGebaeude___failed_1002cb34; uVar4 = 0x2817;
  }
  else {
    iVar3 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x16));
    *(int *)(param_1 + 0x16) = iVar3; uVar4 = 0;
    do {
      uVar2 = uVar4 & 0xffff;
      if (((*(short*)((int)g_static_entity_table_358a0 + uVar2 * 0x10e)) != -1) && (*(int*)((int)g_static_entity_table_358a0 + uVar2 * 0x10e + 4) == iVar3)) {
        if ((unsigned short)uVar4 < 0x300) goto LAB_1000d36b;
        pcVar1 = s_Invalid__eigentuemer_id__for_cmd_1002caf0; uVar4 = 0x280b; goto LAB_1000d38c;
      }
      uVar4 = uVar4 + 1;
    } while ((unsigned short)uVar4 < 0x300);
    pcVar1 = s_Invalid__eigentuemer_id__for_cmd_1002caf0; uVar4 = 0x280b;
  }
LAB_1000d38c:
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,uVar4,pcVar1,1);
  return 1;
}

/* 0x1000d460 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 267
// SYMBOL: _CmdAllocPlayer
// FUNCTION: SERVER 0x1000d460
int __cdecl CmdAllocPlayer(int param_1, char *param_2)
{
  int iVar1; ushort *puVar2; uint uVar3;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c;
  iVar1 = rand();
  *(int *)(param_1 + 0x26) = iVar1;
  crt_thread_set_alt(iVar1);
  if (*(int *)(param_1 + 0x1f) == -1) puVar2 = (ushort *)0x0;
  else {
    iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x1f));
    *(int *)(param_1 + 0x1f) = iVar1;
    puVar2 = (ushort*)StartFilteredEntitySearch(1,1,iVar1);
    if (puVar2 == (ushort *)0x0) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2889,s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50,1); return 1; }
  }
  uVar3 = CreateEntityFromParents((uint)*(byte *)(param_1 + 0x14),*(int *)(param_1 + 0x15),*(int *)(param_1 + 0x19),(uint)*(ushort *)(param_1 + 0x1d),(int)puVar2);
  uVar3 = uVar3 & 0xffff;
  if (uVar3 == 0xffff) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2897,s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c,1); return 1; }
  *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641f8) = g_static_entity0_entity_id[uVar3 * 0x87];
  if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\x01'; *(void**)(param_2 + 6) = (void*)((int)g_static_entity_table_358a0 + uVar3 * 0x10e); }
  return 0;
}

/* 0x1000d570 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 361
// SYMBOL: _validate_cmd_10_AllocPlayer
// FUNCTION: SERVER 0x1000d570
int __cdecl validate_cmd_10_AllocPlayer(int param_1, char *param_2)
{
  int iVar1; uint uVar2; short *psVar3; int iVar4;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c;
  iVar1 = rand();
  *(int *)(param_1 + 0x45) = iVar1;
  crt_thread_set_alt(*(int *)(param_1 + 0x22));
  uVar2 = CreateEntityFromParents(7 - (uint)(param_2 != (char *)0x0),*(int *)(param_1 + 0x14),*(int *)(param_1 + 0x18),(uint)*(ushort *)(param_1 + 0x1c),0);
  uVar2 = uVar2 & 0xffff;
  if (uVar2 != 0xffff) {
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2917,s_ClientSpieler_erzeugt_1002cbbc,1);
    *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641f8) = g_static_entity0_entity_id[uVar2 * 0x87];
    strncpy(g_static_entity0_entity_id + uVar2 * 0x87, (char*)param_1 + 0x26, 0x20);
    psVar3 = GetEntityTableEntry((char*)((int)g_static_entity_table_358a0 + uVar2 * 0x10e));
    if (psVar3 != (short *)0x0) {
      *psVar3 = g_static_entity0_lineage[uVar2 * 0x87];
      iVar4 = LookupEntityRecordById(g_static_entity0_field_60[uVar2 * 0x87]);
    }
    g_static_entity0_field_54[uVar2 * 0x21c / 4] = *(int *)(param_1 + 0x1f);
    g_static_entity0_pos_x[uVar2 * 0x21c] = *(char *)(param_1 + 0x24);
    if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\x01'; *(void**)(param_2 + 6) = (void*)((int)g_static_entity_table_358a0 + uVar2 * 0x10e); }
    return 0;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x290f,s_gm_AllocSpieler___failed_1002cbd4,1);
  return 1;
}

/* 0x1000d6e0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 78
// SYMBOL: _cm_ExChangePlayerIdentity
// FUNCTION: SERVER 0x1000d6e0
int __cdecl cm_ExChangePlayerIdentity(int param_1, char *param_2)
{
  int iVar1;
  iVar1 = ChangePlayerIdentityImpl(*(int *)(param_1 + 0x10),*(int *)(param_1 + 0x14));
  if (-1 < iVar1) {
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x299d,s_cm_ExChangePlayerIdentity___exec_1002cc14,1);
    return 0;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x29a1,s_cm_ExChangePlayerIdentity___fail_1002cbf0,1);
  return 0;
}

/* 0x1000d730 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 180
// SYMBOL: _ExFreeEntity
// FUNCTION: SERVER 0x1000d730
int __cdecl ExFreeEntity(int param_1, char *param_2)
{
  uint uVar1; int iVar2; char *msg; void *local_8; ushort *local_4;
  iVar2 = param_1;
  uVar1 = get_field_by_type((char *)param_1,(uint)*(ushort *)(param_1 + 0x10));
  *(short *)(iVar2 + 0x10) = (short)uVar1;
  iVar2 = ResolveEntityById((void **)&param_1,&local_8,(void **)&local_4,uVar1 & 0xffff);
  if (iVar2 == 0) { msg = s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c; uVar1 = 0x2a09;
LAB_1000d7ab:
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,uVar1,msg,1); return 1;
  }
  if (param_1 == 0) {
    if (local_8 != (void *)0x0) { msg = s_cm_ExFree____Can_t_free_Objects_1002cc3c; uVar1 = 0x2a21; goto LAB_1000d7ab; }
    DeallocEntity((uint)*local_4,1);
  }
  else {
    iVar2 = CleanupBuildingEntity((uchar *)param_1);
    if (iVar2 != 0) return 1;
  }
  if (param_2 != (char *)0x0) *param_2 = '\x01';
  return 0;
}

/* 0x1000d7f0 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 164
// SYMBOL: _ExTransferCurrency
// FUNCTION: SERVER 0x1000d7f0
int __cdecl ExTransferCurrency(int param_1, char *param_2)
{
  void *pvVar1; int iVar2;
  *(int *)(param_1 + 0x18) = g_timestamp_0b6c;
  if (*(int *)(param_1 + 0x14) != -1) {
    pvVar1 = (void *)get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14));
    *(void **)(param_1 + 0x14) = pvVar1;
    iVar2 = SubObjekt(pvVar1,(uint)*(ushort *)(&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),*(int *)(param_1 + 0x1d));
    if (iVar2 == 0) return 1;
  }
  if (*(int *)(param_1 + 0x10) != -1) {
    iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
    *(int *)(param_1 + 0x10) = iVar2;
    pvVar1 = AddOrAccumulateObject(iVar2,(uint)*(ushort *)(&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),*(int *)(param_1 + 0x1d));
    if (pvVar1 == (void *)0x0) return 1;
  }
  if (param_2 != (char *)0x0) *param_2 = '\x01';
  return 0;
}

/* 0x1000d8a0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 142
// SYMBOL: _ExTransferCurrencyNoKill
// FUNCTION: SERVER 0x1000d8a0
int __cdecl ExTransferCurrencyNoKill(int param_1, char *param_2)
{
  int iVar1;
  *(int *)(param_1 + 0x18) = g_timestamp_0b6c;
  if (*(int *)(param_1 + 0x14) != -1) {
    iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14));
    *(int *)(param_1 + 0x14) = iVar1;
    SubtractObjectAmountNoKill(iVar1,(uint)*(ushort *)(&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),*(int *)(param_1 + 0x1d));
  }
  if (*(int *)(param_1 + 0x10) != -1) {
    iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
    *(int *)(param_1 + 0x10) = iVar1;
    AddOrAccumulateObject(iVar1,(uint)*(ushort *)(&g_currency_type_array + (uint)*(byte *)(param_1 + 0x1c) * 0x2f4),*(int *)(param_1 + 0x1d));
  }
  if (param_2 != (char *)0x0) *param_2 = '\x01';
  return 0;
}

/* 0x1000d930 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 2057
// SYMBOL: _TradeCommandHandler
// FUNCTION: SERVER 0x1000d930
uint __stdcall TradeCommandHandler(char *param_1, uchar *param_2)
{
  int iVar1; int resolve_result; char *capacity_check; short *parent_check; ushort *dest_object; int extraout_ECX; char **container_ptr; short *source_owner_entity; int *linked_list_ptr; short *source_dynamic_ref; short *dest_owner_entity; short *resolved_dynamic; short *source_dynamic_entity; char *dest_existing_entity; short *dest_dynamic_entity; short *source_static_entity; char **source_container_ptr; ushort *dest_game_object; void *source_existing_entity; uint weight_fraction; char log_buffer [512]; short entity_type; uint error_code; char obj_category;
  source_owner_entity = (short *)0x0; *(int *)(param_1 + 0x1a) = g_timestamp_0b6c; dest_object = (ushort *)0x0; dest_owner_entity = (short *)0x0; resolved_dynamic = (short *)0x0; dest_game_object = (ushort *)0x0; source_dynamic_entity = (short *)0x0; dest_dynamic_entity = (short *)0x0; source_container_ptr = (char **)0x0; source_existing_entity = (void *)0x0; dest_existing_entity = (char *)0x0; source_static_entity = (short *)0x0;
  if (*(int *)(param_1 + 0x14) != -1) {
    resolve_result = get_field_by_type(param_1,*(int *)(param_1 + 0x14)); *(int *)(param_1 + 0x14) = resolve_result;
    resolve_result = ResolveEntityById(&source_existing_entity,(void**)&resolved_dynamic,(void**)&source_static_entity,resolve_result);
    if (resolve_result == 0) { capacity_check = s_cm_ExSellObjekt___Invalid__quell_1002cec4; error_code = 0x2c05; goto sell_error_return; }
    if (source_existing_entity == (void *)0x0) {
      if (resolved_dynamic == (short *)0x0) { container_ptr = (char **)(source_static_entity + 0xbc); source_owner_entity = source_static_entity; source_container_ptr = container_ptr; }
      else {
        entity_type = *resolved_dynamic;
        if ((((entity_type == 0x2a) || (entity_type == 0x1db)) || (entity_type == 0x1dc)) || ((entity_type == 0x116 || (entity_type == 0x1dd)))) source_dynamic_entity = resolved_dynamic;
        container_ptr = (char **)(resolved_dynamic + 10); source_container_ptr = container_ptr; source_owner_entity = ResolveParentEntity(resolved_dynamic);
        if (source_owner_entity == (short *)0x0) { capacity_check = s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90; error_code = 0x2c2f; goto sell_error_return; }
      }
    }
    else {
      container_ptr = (char **)((int)source_existing_entity + 0x5d); source_container_ptr = container_ptr;
      if (*(ushort *)((int)source_existing_entity + 0x27) == 0xffff) source_owner_entity = (short *)0x0;
      else source_owner_entity = (short*)((int)&g_static_entity_table_358a0 + (uint)*(ushort *)((int)source_existing_entity + 0x27) * 0x10e);
    }
    dest_object = (ushort*)StartEntityQuery((int)*container_ptr,1,0,(uint)*(ushort *)(param_1 + 0x18));
    if (dest_object == (ushort *)0x0) { sprintf(log_buffer,s_cm_ExSellObjekt____Object_not_fo_1002ce4c, (void *)(uint)*(ushort *)(param_1 + 0x18)); LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2c53,log_buffer,8); return 1; }
    if ((source_dynamic_entity != (short *)0x0) && (resolve_result = *(int *)(param_1 + 0x1f), capacity_check = (char*)FindEntityByOwner((int)source_dynamic_entity), (int)capacity_check < resolve_result)) { sprintf(log_buffer,s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc, (void *)(uint)*(ushort *)(param_1 + 0x18)); LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2c75,log_buffer,8); return 1; }
    if (*(int *)(dest_object + 7) < *(int *)(param_1 + 0x1f)) { sprintf(log_buffer,s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc, (void *)(uint)*(ushort *)(param_1 + 0x18)); LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2c97,log_buffer,8); return 1; }
  }
  if (*(int *)(param_1 + 0x10) != -1) {
    resolve_result = get_field_by_type(param_1,*(int *)(param_1 + 0x10)); *(int *)(param_1 + 0x10) = resolve_result;
    resolve_result = ResolveEntityById((void**)&dest_existing_entity,(void**)&resolved_dynamic,(void**)&source_static_entity,resolve_result);
    if (resolve_result == 0) { capacity_check = s_cm_ExSellObjekt___Invalid__ziel__1002cdcc; error_code = 0x2cdd; goto sell_error_return; }
    if (dest_existing_entity == (char *)0x0) {
      if (resolved_dynamic == (short *)0x0) { linked_list_ptr = (int *)(source_static_entity + 0xbc); dest_owner_entity = source_static_entity; }
      else {
        entity_type = *resolved_dynamic;
        if ((((entity_type == 0x2a) || (entity_type == 0x1db)) || (entity_type == 0x1dc)) || (entity_type == 0x116)) {
          dest_dynamic_entity = resolved_dynamic;
LAB_1000dc24:
          resolve_result = KannObjektHergestellt((char *)resolved_dynamic,(uint)*(ushort *)(param_1 + 0x18), *(int *)(param_1 + 0x1f));
          if (resolve_result < *(int *)(param_1 + 0x1f)) { capacity_check = s_cm_ExSellObjekt___Lager_voll_1002cdac; error_code = 0x2d1b; goto sell_error_return; }
        }
        else if (entity_type == 0x1dd) goto LAB_1000dc24;
        linked_list_ptr = (int *)(resolved_dynamic + 10); dest_owner_entity = ResolveParentEntity(resolved_dynamic);
      }
    }
    else {
      linked_list_ptr = (int *)(dest_existing_entity + 0x5d);
      if (*(ushort *)(dest_existing_entity + 0x27) == 0xffff) dest_owner_entity = (short *)0x0;
      else dest_owner_entity = (short*)((int)&g_static_entity_table_358a0 + (uint)*(ushort *)(dest_existing_entity + 0x27) * 0x10e);
    }
    error_code = (uint)*(ushort *)(param_1 + 0x18); resolve_result = error_code * 0x40;
    if (*(char *)((int)unknown + error_code * 0x41) == '\x1d') dest_game_object = (ushort *)0x0;
    else { dest_game_object = (ushort*)StartEntityQuery(*linked_list_ptr,1,0,error_code); resolve_result = extraout_ECX; }
    if (((*(int *)(param_1 + 0x23) != 0) && (dest_owner_entity != (short *)0x0)) && (resolve_result = QueryEntitySum(*(int *)(dest_owner_entity + 0xbc), 0), resolve_result < *(int *)(param_1 + 0x1f) * *(int *)(param_1 + 0x23))) { capacity_check = s_cm_ExSellObjekt___Not_enough_Cre_1002cd78; error_code = 0x2d4f; goto sell_error_return; }
  }
  source_dynamic_ref = source_dynamic_entity;
  if (source_dynamic_entity == (short *)0x0) {
LAB_1000dd58:
    if ((((dest_owner_entity != (short *)0x0) && (dest_existing_entity == (char *)0x0)) && (dest_dynamic_entity == (short *)0x0)) && (resolved_dynamic == (short *)0x0)) {
      resolve_result = CheckInventoryCapacity((char *)dest_owner_entity,(uint)*(ushort *)(param_1 + 0x18), *(int *)(param_1 + 0x1f));
      *(int *)(param_1 + 0x1f) = resolve_result; if (resolve_result == 0) return 1;
    }
  }
  else if (dest_owner_entity != (short *)0x0) {
    parent_check = ResolveParentEntity((short *)dest_object);
    if ((parent_check != dest_owner_entity) && (*(int *)(dest_object + 0xe) != 0)) {
      resolve_result = compute_size((char *)source_dynamic_ref); weight_fraction = (uint)(resolve_result * *(int *)(dest_object + 0xe)) >> 2; capacity_check = (char*)FindEntityByOwner((int)source_dynamic_ref); source_dynamic_ref = source_dynamic_entity;
      if ((int)capacity_check - (int)weight_fraction < *(int *)(param_1 + 0x1f)) { capacity_check = (char*)g_error_msg_sell_no_source; error_code = 0x2d79; goto sell_error_return; }
    }
    goto LAB_1000dd58;
  }
  if (*(int *)(param_1 + 0x23) != 0) {
    if (((dest_dynamic_entity == (short *)0x0) && (resolved_dynamic != (short *)0x0)) && ((*resolved_dynamic == 0x1dd && (capacity_check = FindSlotById((uint)g_current_season,(uint)*(ushort *)(param_1 + 0x18)), capacity_check != (char *)0x0)))) *(int *)(capacity_check + 0x18) = *(int *)(capacity_check + 0x18) + *(int *)(param_1 + 0x1f);
    if (((source_dynamic_ref != (short *)0x0) && (*source_dynamic_ref == 0x1dd)) && (capacity_check = FindSlotById((uint)g_current_season,(uint)*(ushort *)(param_1 + 0x18)), capacity_check != (char *)0x0)) *(int *)(capacity_check + 0x1c) = *(int *)(capacity_check + 0x1c) + *(int *)(param_1 + 0x1f);
  }
  if (*(int *)(param_1 + 0x14) != -1) {
    resolve_result = *(int *)(param_1 + 0x1f); iVar1 = *(int *)(dest_object + 7); *(int *)(dest_object + 7) = iVar1 - resolve_result;
    if (iVar1 - resolve_result < 1) {
      error_code = (uint)*(ushort *)(param_1 + 0x18); obj_category = *(char *)((int)unknown + error_code * 0x41);
      if ((obj_category == '\x02') || (obj_category == '\x06')) { if (source_existing_entity == (void *)0x0) { capacity_check = (char*)g_error_msg_sell_no_dest; error_code = 0x2def; goto sell_error_return; } RemoveObjectWrapper((int)source_existing_entity,error_code); }
      else RemoveObjectByType(source_container_ptr,error_code);
    }
    if (*(int *)(param_1 + 0x23) != 0) {
      AddOrAccumulateObject(*(int *)(source_owner_entity + 2),(uint)*(ushort *)(&g_currency_type_array + (uint)(byte)param_1[0x1e] * 0x2f4),*(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f));
      if (source_dynamic_ref == (short *)0x0) {
LAB_1000def2:
        *(int *)(source_owner_entity + 0xce) = *(int *)(source_owner_entity + 0xce) + *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f);
      }
      else if (*source_dynamic_ref == 0x1db) *(int *)(source_owner_entity + 0xd2) = *(int *)(source_owner_entity + 0xd2) + *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f);
      else { if (*source_dynamic_ref != 0x1dc) goto LAB_1000def2; *(int *)(source_owner_entity + 0xd0) = *(int *)(source_owner_entity + 0xd0) + *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f); }
    }
  }
  dest_object = dest_game_object;
  if (*(int *)(param_1 + 0x10) != -1) {
    if (dest_game_object == (ushort *)0x0) {
      error_code = (uint)*(ushort *)(param_1 + 0x18); obj_category = *(char *)((int)unknown + error_code * 0x41);
      if ((obj_category == '\x02') || (obj_category == '\x06')) { if (dest_existing_entity == (char *)0x0) { capacity_check = (char*)g_error_msg_sell_failed; error_code = 0x2e45; goto sell_error_return; } dest_object = (ushort *)AllocBuildingContents(dest_existing_entity,error_code); if (dest_object == (ushort *)0x0) { capacity_check = s_cm_ExSellObjekt____gm_AllocRaum_f_1002ccc0; error_code = 0x2e39; goto sell_error_return; } }
      else { dest_object = (ushort *)AllocGameObject(*(int *)(param_1 + 0x10),error_code,*(int *)(param_1 + 0x1f)); if (dest_object == (ushort *)0x0) { capacity_check = s_cm_ExSellObjekt____gm_AllocObjek_1002cce8; error_code = 0x2e5d; goto sell_error_return; } if (dest_dynamic_entity != (short *)0x0) { capacity_check = (char *)((int)unknown + (uint)*(ushort *)(param_1 + 0x18) * 0x41); *(int *)(dest_object + 7) = *(int *)(dest_object + 7) + 1; obj_category = *capacity_check; if (((((obj_category == '\x17') || (obj_category == '%')) && ((*dest_dynamic_entity == 0x2a || (*dest_dynamic_entity == 0x116)))) && (dest_owner_entity != (short *)0x0)) && (((char)dest_owner_entity[1] == '\x06' || ((char)dest_owner_entity[1] == '\a')))) { dest_object[0xe] = 4; dest_object[0xf] = 0; } } }
    }
    else *(int *)(dest_game_object + 7) = *(int *)(dest_game_object + 7) + *(int *)(param_1 + 0x1f);
    *(int *)(g_player_slot_0[(byte)param_1[3]].data + 0x264200) = *(int *)(dest_object + 1);
    if ((*(int *)(param_1 + 0x23) != 0) && (dest_owner_entity != (short *)0x0)) {
      SubObjekt(*(void **)(dest_owner_entity + 2), (uint)*(ushort *)(&g_currency_type_array + (uint)(byte)param_1[0x1e] * 0x2f4), *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f));
      if (dest_dynamic_entity != (short *)0x0) {
        if (*dest_dynamic_entity == 0x1db) { *(int *)(dest_owner_entity + 0xd0) = *(int *)(dest_owner_entity + 0xd0) + *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f); goto LAB_1000e0e7; }
        if (*dest_dynamic_entity == 0x1dc) { *(int *)(dest_owner_entity + 0xd2) = *(int *)(dest_owner_entity + 0xd2) + *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f); goto LAB_1000e0e7; }
      }
      *(int *)(dest_owner_entity + 0xcc) = *(int *)(dest_owner_entity + 0xcc) + *(int *)(param_1 + 0x23) * *(int *)(param_1 + 0x1f);
    }
  }
LAB_1000e0e7:
  if ((param_2 != (uchar *)0x0) && (*param_2 = '\x01', *(int *)(param_1 + 0x10) != -1)) { param_2[1] = '\x03'; *(ushort **)(param_2 + 6) = dest_object; }
  return 0;
sell_error_return:
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,error_code,capacity_check,8); return 1;
}

/* 0x1000e140 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 993
// SYMBOL: _cm_ExecProduction
// FUNCTION: SERVER 0x1000e140
int __cdecl cm_ExecProduction(int msg, char *result)
{
  int iVar1; ushort *puVar2; char *pcVar3; int iVar4; ushort *puVar5; long lVar6; short *psVar7; uint line; short *local_10; char *local_c; int local_8; short *local_4;
  *(int *)(msg + 0x1a) = g_timestamp_0b6c; iVar1 = get_field_by_type((char *)msg,*(int *)(msg + 0x10)); *(int *)(msg + 0x10) = iVar1;
  iVar1 = ResolveEntityById((void **)0x0,(void**)&local_10,(void **)0x0,iVar1);
  if (iVar1 == 0) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2f3b,s_cm_ExecProduction___Invalid__lager_1002cf9c,1); return 1; }
  if ((*local_10 != 0x2a) && (*local_10 != 0x116)) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2f53,s_cm_ExecProduction___Lager_has_wron_1002cf74,1); return 1; }
  local_4 = ResolveParentEntity(local_10); if (local_4 == (short *)0x0) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2f6d,s_cm_ExecProduction___Lager_hat_kein_1002cf48,1); return 1; }
  iVar1 = *(int *)(msg + 0x16); local_c = (char *)((int)unknown + (uint)*(ushort *)(msg + 0x14) * 0x41); local_8 = 4; puVar5 = (ushort *)(local_c + 0x26);
  do {
    if (puVar5[4] != 0) {
      puVar2 = (ushort*)StartEntityQuery(*(int *)(local_10 + 10),1,0,(uint)puVar5[4]);
      if (puVar2 == (ushort *)0x0) iVar1 = 0;
      else { pcVar3 = (char*)FindEntityByOwner((int)local_10); if ((int)pcVar3 / (int)(uint)*puVar5 <= iVar1) { pcVar3 = (char*)FindEntityByOwner((int)local_10); iVar1 = (int)pcVar3 / (int)(uint)*puVar5; } }
    }
    pcVar3 = local_c; puVar5 = puVar5 + 1; local_8 = local_8 + -1;
  } while (local_8 != 0);
  local_8 = iVar1; iVar4 = KannObjektHergestellt((char *)local_10,(uint)*(ushort *)(msg + 0x14),(uint)*(ushort *)(local_c + 0x36) * iVar1);
  iVar4 = iVar4 / (int)(uint)*(ushort *)(pcVar3 + 0x36); if (iVar4 <= iVar1) { iVar1 = iVar4; local_8 = iVar4; }
  if (iVar1 == 0) { pcVar3 = &g_empty_string; line = 0x2fb5;
LAB_1000e3e1:
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,pcVar3,1); if (result != (char *)0x0) result[1] = '\b'; return 1;
  }
  iVar4 = 0; puVar5 = (ushort *)(local_c + 0x2e);
  do {
    if (*puVar5 != 0) {
      puVar2 = (ushort*)StartEntityQuery(*(int *)(local_10 + 10),1,0,(uint)*puVar5);
      if (puVar2 == (ushort *)0x0) { pcVar3 = s_cm_ExProdObjekt___Rohstoff_versc_1002cef4; line = 0x2fdd; goto LAB_1000e3e1; }
      *(uint *)(puVar2 + 7) = *(int *)(puVar2 + 7) - (uint)puVar5[-4] * iVar1;
      pcVar3 = FindSlotById((uint)g_current_season,(uint)*puVar5); if (pcVar3 != (char *)0x0) *(uint *)(pcVar3 + 0x14) = *(int *)(pcVar3 + 0x14) + (uint)*(ushort *)(local_c + 0x36) * iVar1;
      if (*(int *)(puVar2 + 7) == 0) RemoveObjectByType((char **)(local_10 + 10),(uint)*puVar5);
    }
    iVar4 = iVar4 + 1; puVar5 = puVar5 + 1;
    if (3 < iVar4) {
      puVar5 = (ushort*)StartEntityQuery(*(int *)(local_10 + 10),1,0,(uint)*(ushort *)(msg + 0x14)); pcVar3 = local_c;
      if (puVar5 == (ushort *)0x0) {
        puVar5 = (ushort *)AllocGameObject(*(int *)(local_10 + 1),(uint)*(ushort *)(msg + 0x14),(uint)*(ushort *)(local_c + 0x36) * iVar1);
        if (puVar5 == (ushort *)0x0) { if (result != (char *)0x0) result[1] = '\x06'; return 1; }
        if (*local_10 == 0x2a) *(int *)(puVar5 + 7) = *(int *)(puVar5 + 7) + 1;
        if ((((*pcVar3 == '\x17') || (*pcVar3 == '%')) && ((*local_10 == 0x2a || (*local_10 == 0x116)))) && (((char)local_4[1] == '\x06' || ((char)local_4[1] == '\a')))) { puVar5[0xe] = 4; puVar5[0xf] = 0; }
      }
      else *(uint *)(puVar5 + 7) = *(int *)(puVar5 + 7) + (uint)*(ushort *)(local_c + 0x36) * iVar1;
      CalculateProductionValue((uint)*(ushort *)(msg + 0x14),100); lVar6 = _ftol(); iVar4 = entity_accumulate((int)local_10);
      if (iVar4 != 0) *(int *)(iVar4 + 0x4d) = *(int *)(iVar4 + 0x4d) + lVar6;
      pcVar3 = FindSlotById((uint)g_current_season,(uint)*(ushort *)(msg + 0x14)); if (pcVar3 != (char *)0x0) *(uint *)(pcVar3 + 0x10) = *(int *)(pcVar3 + 0x10) + (uint)*(ushort *)(local_c + 0x36) * iVar1;
      psVar7 = GetEntityTableEntry((char *)local_4); if (psVar7 != (short *)0x0) *(int *)(psVar7 + 0x12) = *(int *)(psVar7 + 0x12) + lVar6;
      if ((result != (char *)0x0) && (*result = '\x01', *(int *)(msg + 0x10) != -1)) { result[1] = '\x03'; *(ushort **)(result + 6) = puVar5; }
      return 0;
    }
  } while( 1 );
}

/* 0x1000ec00 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 901
// SYMBOL: _ExCopyEntityData
// FUNCTION: SERVER 0x1000ec00
int __cdecl ExCopyEntityData(int cmd_ptr,char *response)
{
  int iVar1; int iVar2; long lVar4; uint uVar5; uint uVar6; undefined1 *puVar7; int *piVar8;
  iVar1 = get_field_by_type((char *)cmd_ptr,*(int *)(cmd_ptr + 0x10)); *(int *)(cmd_ptr + 0x10) = iVar1;
  iVar2 = get_field_by_type((char *)cmd_ptr,*(int *)(cmd_ptr + 0x14)); iVar1 = *(int *)(cmd_ptr + 0x1c); *(int *)(cmd_ptr + 0x14) = iVar2;
  if (iVar1 != 4) {
    uVar6 = 0; piVar8 = (int*)&g_static_entity0_entity_id;
    while (*piVar8 != iVar2) { piVar8 = piVar8 + 0x87; uVar6 = uVar6 + 1; if ((int *)0x1009aca3 < piVar8) return 1; }
    if (0x2ff < uVar6) return 1; if (((short*)g_static_entity_table_358a0)[uVar6 * 0x10e] == -1) return 1;
    if (iVar1 == 3) {
      iVar1 = *(int *)(uVar6 * 0x21c + 0x10035ab0); piVar8 = (int*)&g_static_entity0_entity_id; puVar7 = &g_relationship_matrix_secondary + uVar6;
      do { if (*piVar8 != iVar1) { lVar4 = _ftol(); *puVar7 = (char)lVar4; } piVar8 = piVar8 + 0x87; puVar7 = puVar7 + 0x300; } while ((int)piVar8 < 0x1009aca4);
    }
    else {
      uVar5 = 0; piVar8 = (int*)&g_static_entity0_entity_id;
      while (*piVar8 != *(int *)(cmd_ptr + 0x10)) { piVar8 = piVar8 + 0x87; uVar5 = uVar5 + 1; if ((int *)0x1009aca3 < piVar8) return 1; }
      if ((0x2ff < uVar5) || (((short*)g_static_entity_table_358a0)[uVar5 * 0x10e] == -1)) return 1;
      if (iVar1 == 2) { iVar2 = uVar6 + uVar5 * 0x300; (&g_relationship_matrix_secondary)[iVar2] = 0; iVar1 = *(int *)(cmd_ptr + 0x18) + (int)(char)(&g_relationship_matrix_primary)[iVar2]; if (iVar1 < -0x7f) (&g_relationship_matrix_primary)[iVar2] = 0x81; else if (iVar1 < 0x7f) (&g_relationship_matrix_primary)[iVar2] = (char)iVar1; else (&g_relationship_matrix_primary)[iVar2] = 0x7f; }
      else if (iVar1 == 1) { iVar2 = uVar6 + uVar5 * 0x300; iVar1 = (int)(char)(&g_relationship_matrix_primary)[iVar2] + *(int *)(cmd_ptr + 0x18); if (iVar1 < -0x7f) iVar1 = -0x7f; else if (0x7e < iVar1) iVar1 = 0x7f; (&g_relationship_matrix_primary)[iVar2] = (char)iVar1; if (-1 < *(int *)(cmd_ptr + 0x18)) iVar1 = iVar1 / 2; }
    }
  }
  return 0;
}

/* 0x1000ef90 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 26
// SYMBOL: _chain_handler_assign_id
// FUNCTION: SERVER 0x1000ef90
int __cdecl chain_handler_assign_id(int param_1, char *param_2)
{
  *(int *)(param_1 + 0x10) = g_mem_pool_overflow_flag;
  g_mem_pool_overflow_flag = g_mem_pool_overflow_flag + 1;
  return 0;
}

/* 0x1000efb0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 122
// SYMBOL: _SetSyncFlags
// FUNCTION: SERVER 0x1000efb0
int __cdecl SetSyncFlags(int param_1, char *param_2)
{
  if (*(char *)(param_1 + 0x10) == '\x01') g_player_slot_0[*(byte *)(param_1 + 3)].flags |= 0x20;
  if (*(char *)(param_1 + 0x10) == '\x0e') g_player_slot_0[*(byte *)(param_1 + 3)].flags |= 0x40;
  if (*(char *)(param_1 + 0x10) == '\x12') { _g_game_speed_index = *(int *)(param_1 + 0x11); if (3 < _g_game_speed_index) _g_game_speed_index = 4; g_game_speed_value = *(int *)(&g_game_speed_table + _g_game_speed_index * 4); }
  return 0;
}

/* 0x1000f030 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 72
// SYMBOL: _CmdKillPlayer
// FUNCTION: SERVER 0x1000f030
int __cdecl CmdKillPlayer(int param_1)
{
  ushort *puVar1;
  puVar1 = (ushort *)LookupEntityRecordById(*(int *)(param_1 + 0x10));
  if (puVar1 != (ushort *)0x0) { DeallocEntity((uint)*puVar1,*(int *)(param_1 + 0x14)); return 0; }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x397d,s_cm_ExKillSpieler___Could_not_fin_1002d154,1);
  return 0;
}

/* 0x1000f080 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 26
// SYMBOL: _AssignSequenceCounter
// FUNCTION: SERVER 0x1000f080
int __cdecl AssignSequenceCounter(int param_1, char *param_2)
{
  *(int *)(param_1 + 0x10) = g_sequence_counter;
  g_sequence_counter = g_sequence_counter + 1;
  return 0;
}

/* 0x1000f0a0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 37
// SYMBOL: _AssignEntityId
// FUNCTION: SERVER 0x1000f0a0
int __cdecl AssignEntityId(int param_1, char *param_2)
{
  DWORD DVar1;
  *(int *)(param_1 + 0x10) = g_entity_id_start;
  DVar1 = timeGetTime();
  *(DWORD *)(param_1 + 0x14) = DVar1;
  g_entity_id_start = g_entity_id_start + 1;
  return 0;
}

/* 0x1000f0d0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 197
// SYMBOL: _RemoveLinkedObject
// FUNCTION: SERVER 0x1000f0d0
int __cdecl RemoveLinkedObject(int param_1,char *param_2)
{
  char *pcVar1; ushort *puVar2; int iVar3; void *local_4;
  pcVar1 = param_2; iVar3 = param_1; if (param_2 != (char *)0x0) *param_2 = '\x02';
  ResolveEntityById((void **)&param_1,&param_2,&local_4,*(int *)(param_1 + 0x10));
  if (param_1 == 0) { if (local_4 == (void *)0x0) { if (param_2 == (char *)0x0) return -1; iVar3 = RemoveLinkedNodeById((int *)(param_2 + 0x14),*(int *)(iVar3 + 0x18)); if (iVar3 != 0) return iVar3; goto LAB_1000f181; } iVar3 = *(int *)(iVar3 + 0x18); puVar2 = (ushort *)((int)local_4 + 0x178); }
  else if (*(int *)(iVar3 + 0x14) == -1) { iVar3 = *(int *)(iVar3 + 0x18); puVar2 = (ushort *)(param_1 + 0x5d); }
  else { param_2 = (char *)StartEntityQuery(*(int *)(param_1 + 0x5d),2,6,1,*(int *)(iVar3 + 0x14)); if ((ushort *)param_2 == (ushort *)0x0) return -2; iVar3 = *(int *)(iVar3 + 0x18); puVar2 = (ushort *)((int)param_2 + 0x14); }
  iVar3 = RemoveLinkedNodeById((int *)puVar2,iVar3); if (iVar3 != 0) return iVar3;
LAB_1000f181:
  if (pcVar1 != (char *)0x0) *pcVar1 = '\x01';
  return 0;
}

/* 0x1000f1a0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 327
// SYMBOL: _chain_handler_record_lookup
// FUNCTION: SERVER 0x1000f1a0
int __cdecl chain_handler_record_lookup(int param_1,char *param_2)
{
  bool bVar1; ushort *puVar2; char *pcVar3; int iVar4; char *pcVar5; char local_1;
  local_1 = '\x02'; pcVar5 = (char *)0x0; bVar1 = false; *(int *)(param_1 + 0x10) = g_plant_count;
  puVar2 = (ushort*)StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x14));
  if (puVar2 != (ushort *)0x0) {
    pcVar3 = SearchRecordTable((uint)*(ushort *)(param_1 + 0x1a));
    if (((pcVar3 == (char *)0x0) || (*(char *)(param_1 + 0x1c) != '\0')) || (iVar4 = CheckZoneAvailability(*(int *)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),(uint)*(byte *)(param_1 + 0x19),(uint)(byte)pcVar3[0x42]), iVar4 != 0)) bVar1 = true;
    if (*(char *)(param_1 + 0x1c) == '\0') { if (*(int *)(param_1 + 0x1d) != -1) { pcVar5 = FindRecord(*(char **)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),(uint)*(byte *)(param_1 + 0x19)); if (param_2 == (char *)0x0) return 0; *(char **)(param_2 + 6) = pcVar5; *param_2 = '\x01'; param_2[1] = '\x05'; return 0; } }
    else { pcVar5 = FindRecord(*(char **)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),(uint)*(byte *)(param_1 + 0x19)); if ((pcVar5 != (char *)0x0) && (*(int *)(pcVar5 + 0x10) != -1)) return 1; }
    if (bVar1) pcVar5 = (char *)plt_SetPlantMap(*(int *)((int)puVar2 + 0x71),(uint)*(byte *)(param_1 + 0x18),(uint)*(byte *)(param_1 + 0x19),(uint)*(ushort *)(param_1 + 0x1a),(uint)*(byte *)(param_1 + 0x1c));
    if (pcVar5 != (char *)0x0) { local_1 = '\x01'; *(int *)(pcVar5 + 4) = *(int *)((int)puVar2 + 1); if (*(char *)(param_1 + 0x1c) != '\0') *(int *)(pcVar5 + 0x10) = *(int *)(param_1 + 0x1d); }
  }
  if (param_2 != (char *)0x0) { param_2[1] = '\x05'; *param_2 = local_1; *(char **)(param_2 + 6) = pcVar5; }
  return 0;
}

/* 0x1000f2f0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 172
// SYMBOL: _ExCreateSpecialObject
// FUNCTION: SERVER 0x1000f2f0
int __cdecl ExCreateSpecialObject(int param_1,char *param_2)
{
  int iVar1; char *pcVar2;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c; iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14)); *(int *)(param_1 + 0x14) = iVar1;
  pcVar2 = (char*)AllocGameObject(iVar1,0x1b5,1); if (pcVar2 == (char *)0x0) return 1;
  *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) = *(int *)(pcVar2 + 2);
  pcVar2[0x12] = '@'; *(int *)(pcVar2 + 0x1c) = *(int *)(param_1 + 0x18); *(short *)(pcVar2 + 0x20) = *(short *)(param_1 + 0x1c);
  pcVar2[0x22] = *(char *)(param_1 + 0x1e); pcVar2[0x22] = '\0';
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x40db,s_cm_ExAllocThemaPredigt____Execut_1002d184,1);
  if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\x03'; *(char **)(param_2 + 6) = pcVar2; }
  return 0;
}

/* 0x1000f3a0 */
// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 3
// SYMBOL: _chain_handler_noop
// FUNCTION: SERVER 0x1000f3a0
int __cdecl chain_handler_noop(void)
{
  return 0;
}

/* 0x1000f3b0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 206
// SYMBOL: _SetBuildingOwner
// FUNCTION: SERVER 0x1000f3b0
int __cdecl SetBuildingOwner(int param_1,char *param_2)
{
  ushort *puVar1; ushort *puVar2; ushort *puVar3; uint line; char *msg;
  puVar1 = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x10));
  if (puVar1 == (ushort *)0x0) { msg = s_cm_ExSetGebBesitzer____Could_not_1002d214; line = 0x4972; }
  else {
    puVar2 = (ushort *)LookupEntityRecordById(*(int *)(param_1 + 0x18));
    if ((puVar2 != (ushort *)0x0) || (*(int *)(param_1 + 0x18) == -1)) {
      puVar3 = (ushort *)LookupEntityRecordById(*(int *)(param_1 + 0x14));
      if ((puVar3 == (ushort *)0x0) && (*(int *)(param_1 + 0x14) != -1)) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4990,s_cm_ExSetGebBesitzer____Could_not_1002d1a8,1); return 2; }
      AssignBuildingOwner((uchar *)puVar1,*puVar3,(uint)*puVar2);
      if (param_2 != (char *)0x0) { *param_2 = '\x02'; param_2[1] = '\0'; param_2[6] = '\0'; param_2[7] = '\0'; param_2[8] = '\0'; param_2[9] = '\0'; }
      return 0;
    }
    msg = s_cm_ExSetGebBesitzer____Could_not_1002d1e0; line = 0x4980;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
  return 1;
}

/* 0x1000f480 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 271
// SYMBOL: _SetResidence
// FUNCTION: SERVER 0x1000f480
int __cdecl SetResidence(int param_1,char *param_2)
{
  byte *pbVar1; ushort *puVar2; int iVar3; uint line; char *msg; ushort local_8 [4];
  puVar2 = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x10));
  if (puVar2 == (ushort *)0x0) { msg = s_cm_ExSetWohnsitz____Could_not_fi_1002d298; line = 0x49de; }
  else {
    iVar3 = LookupEntityRecordById(*(int *)(param_1 + 0x14));
    if ((iVar3 != 0) || (*(int *)(param_1 + 0x14) == -1)) {
      if (*(char *)(g_entity_type_table + (uint)(byte)*puVar2 * 0x24d) == '\x01') {
        table_lookup((uint)(byte)*puVar2,(int *)local_8);
        if (local_8[0] <= *(byte *)((int)puVar2 + 0x65)) { msg = s_cm_ExSetWohnsitz____Residence_is_1002d240; line = 0x4a08; goto LAB_1000f519; }
        *(byte *)((int)puVar2 + 0x65) = *(byte *)((int)puVar2 + 0x65) + 1;
      }
      pbVar1 = *(byte **)(iVar3 + 0x170);
      if (((pbVar1 != (byte *)0x0) && (*(char *)(g_entity_type_table + (uint)*pbVar1 * 0x24d) == '\x01')) && (pbVar1[0x65] != 0)) { pbVar1[0x65] = pbVar1[0x65] - 1; }
      *(ushort **)(iVar3 + 0x170) = puVar2;
      if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\0'; param_2[6] = '\0'; param_2[7] = '\0'; param_2[8] = '\0'; param_2[9] = '\0'; }
      return 0;
    }
    msg = s_cm_ExSetWohnsitz____Could_not_fi_1002d268; line = 0x49ec;
  }
LAB_1000f519:
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
  return 1;
}

/* 0x1000f590 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 237
// SYMBOL: _SetBuildingUpgrade
// FUNCTION: SERVER 0x1000f590
int __cdecl SetBuildingUpgrade(int param_1,char *param_2)
{
  char *pcVar1; ushort *puVar2; uint uVar3;
  *(int *)(param_1 + 0x14) = g_timestamp_0b6c;
  puVar2 = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x10));
  if (puVar2 == (ushort *)0x0) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4a94, s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,1); return 1; }
  uVar3 = (uint)(byte)*puVar2; pcVar1 = (char *)(g_entity_type_table + uVar3 + uVar3 * 0x24c);
  if ((byte)pcVar1[0x248] <= *(byte *)(g_entity_type_table + uVar3 + 0x247 + uVar3 * 0x24c)) { ReportMessage(s_cm_ExSetGebUpgrade____already_hi_1002d2c0); return 1; }
  *(byte *)puVar2 = (byte)*puVar2 + 1;
  *(char *)(puVar2 + 0x2e) = (char)((100 - (char)puVar2[0x2e]) / 2) + (char)puVar2[0x2e];
  SetBuildingWorkerLimits((uchar *)puVar2); gm_AllocBuildingDefaults((uchar *)puVar2);
  if (*pcVar1 == '\x1d') { UpgradeGraveyardField((uint8_t *)puVar2); }
  RefreshMarketAvailability((uint)g_current_season);
  if (param_2 != (char *)0x0) { *param_2 = '\x02'; param_2[1] = '\0'; param_2[6] = '\0'; param_2[7] = '\0'; param_2[8] = '\0'; param_2[9] = '\0'; }
  return 0;
}

/* 0x1000f680 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 171
// SYMBOL: _DestroyBuilding
// FUNCTION: SERVER 0x1000f680
int __cdecl DestroyBuilding(int param_1,char *param_2)
{
  ushort *puVar1; ushort *puVar2; int *piVar3;
  puVar1 = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x10));
  if (puVar1 != (ushort *)0x0) {
    puVar2 = (ushort*)StartEntityQuery(0,2,7,4,0x1d);
    while (puVar2 != (ushort *)0x0) { if (*(int *)(puVar2 + 0xe) == *(int *)((int)puVar1 + 1)) { RemoveEntityLink((int)puVar2); } puVar2 = NextEntityQueryMatch(); }
    piVar3 = &g_work_building_ptrs;
    do { if ((ushort *)*piVar3 == puVar1) { *piVar3 = 0; } piVar3 = piVar3 + 0x87; } while ((int)piVar3 < 0x1009ae0c);
    CleanupBuildingEntity((uchar *)puVar1);
    if (param_2 != (char *)0x0) { *param_2 = '\x02'; param_2[1] = '\0'; param_2[6] = '\0'; param_2[7] = '\0'; param_2[8] = '\0'; param_2[9] = '\0'; }
    return 0;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4c32, s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,1);
  return 1;
}

/* 0x1000f730 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 515
// SYMBOL: _EmployWorkerAtBuilding
// FUNCTION: SERVER 0x1000f730
int __stdcall EmployWorkerAtBuilding(int param_1,char *param_2)
{
  int random_seed; ushort *building_entity; char *citizen_entity; uint *building_type_ptr; int *extraout_EAX; ushort *workplace_entity; uint log_line; char worker_type;
  workplace_entity = (ushort *)0x0; *(int *)(param_1 + 0x1f) = g_timestamp_0b6c; random_seed = rand(); *(int *)(param_1 + 0x23) = random_seed; crt_thread_set_alt(random_seed);
  building_entity = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x10));
  if (building_entity == (ushort *)0x0) { citizen_entity = s_cm_ExEmployWorker____Illegal_geb_1002d33c; log_line = 0x4d3a;
LAB_1000f7a9:
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,log_line,citizen_entity,1); return 1;
  }
  citizen_entity = (char *)LookupEntityRecordById(*(int *)(param_1 + 0x19));
  if (*(int *)(param_1 + 0x14) == -1) { if (citizen_entity != (char *)0x0) { workplace_entity = *(ushort **)(citizen_entity + 0x170); goto LAB_1000f7ca; } }
  else { workplace_entity = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x14)); if (workplace_entity == (ushort *)0x0) { citizen_entity = s_cm_ExEmployWorker____Illegal_gw__1002d318; log_line = 0x4d50; goto LAB_1000f7a9; }
LAB_1000f7ca:
    if ((citizen_entity != (char *)0x0) && (*(int *)(citizen_entity + 0x16c) == 0)) goto LAB_1000f7f5;
  }
  citizen_entity = sim_CreateCitizen('\x06',(uint)*(byte *)(param_1 + 0x18),0x12,*(uchar *)(param_1 + 0x1e), *(uchar *)(param_1 + 0x1d));
LAB_1000f7f5:
  if (citizen_entity != (char *)0x0) {
    if (*(char *)(param_1 + 0x1d) != '\0') { citizen_entity[0x165] = *(char *)(param_1 + 0x1d); }
    if (*(char *)(param_1 + 0x1e) == '\0') { citizen_entity[0x164] = '\0'; } else { citizen_entity[0x164] = *(char *)(param_1 + 0x1e); }
    citizen_entity[2] = *(char *)(param_1 + 0x18); if ((*(int *)(citizen_entity + 0x184) == 0) && (workplace_entity != (ushort *)0x0)) { StartEntityQueryByType((uchar *)workplace_entity); }
    worker_type = *(char *)(param_1 + 0x1d);
    if ((((worker_type == '\x02') || (worker_type == '\x01')) || (worker_type == '\x10')) || (((worker_type == '\x0f' || (worker_type == '\x14')) || (worker_type == '\x13')))) { QueryEntityBuildingType((int)citizen_entity); if (*(int*)&extraout_EAX == 0) { AllocGameObject(*(int *)(citizen_entity + 4),0x154,1); } }
    else { QueryEntityBuildingType((int)citizen_entity); if (*(uint*)&building_type_ptr != 0) { SubObjekt(*(void **)(citizen_entity + 4),*(uint*)&building_type_ptr,1); } }
    *(ushort **)(citizen_entity + 0x16c) = building_entity; if (workplace_entity != (ushort *)0x0) { priority_update(citizen_entity,(char *)workplace_entity); }
    citizen_entity[0x174] = '\0'; citizen_entity[0x175] = '\0'; citizen_entity[0x176] = '\0'; citizen_entity[0x177] = '\0'; *(uint *)(citizen_entity + 0x1c8) &= 0xffffdfff;
    reset_entity_state(citizen_entity); *(int *)(citizen_entity + 0x1b4) = *(int *)((int)building_entity + 0x99); *(int *)(citizen_entity + 0x1b8) = *(int *)((int)building_entity + 0x9d); *(int *)(citizen_entity + 0x1bc) = *(int *)((int)building_entity + 0xa1);
  }
  return 0;
}

/* 0x1000f940 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// SYMBOL: _call_with_off2
// FUNCTION: SERVER 0x1000f940
int __cdecl call_with_off2(void *obj)
{
  uint uVar1;
  uVar1 = ValidateAndAssignOffice((uint *)((int)obj + 0x10));
  return (uint)(uVar1 == 0);
}

/* 0x1000f960 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// SYMBOL: _CmdExecuteOffice
// FUNCTION: SERVER 0x1000f960
int __cdecl CmdExecuteOffice(void *param_1, char *param_2)
{
  int iVar1;
  iVar1 = ExecuteOfficeAssignment((char *)((int)param_1 + 0x10));
  return (uint)(iVar1 == 0);
}

/* 0x1000f980 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 335
// SYMBOL: _ExCreateCitizenAtBuilding
// FUNCTION: SERVER 0x1000f980
int __cdecl ExCreateCitizenAtBuilding(int param_1, char *param_2)
{
  int iVar1; ushort *puVar2; uint uVar3; char *msg;
  *(int *)(param_1 + 0x10) = g_timestamp_0b6c; iVar1 = rand(); *(int *)(param_1 + 0x22) = iVar1;
  if (param_2 != (char *)0x0) { *param_2 = '\x02'; param_2[1] = '\x01'; param_2[6] = '\0'; param_2[7] = '\0'; param_2[8] = '\0'; param_2[9] = '\0'; }
  crt_thread_set_alt(*(int *)(param_1 + 0x22));
  if (*(int *)(param_1 + 0x17) != -1) { iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x17)); *(int *)(param_1 + 0x17) = iVar1; puVar2 = StartFilteredEntitySearch(1,1,iVar1); if (puVar2 == (ushort *)0x0) { msg = s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394; uVar3 = 0x5246; goto LAB_1000fa2c; } }
  uVar3 = CreateEntityFromParents((uint)*(byte *)(param_1 + 0x14),-1,-1,0x14,0); uVar3 = uVar3 & 0xffff;
  if (uVar3 != 0xffff) {
    if (*(int *)(param_1 + 0x1b) != -1) { FindRecordById(*(int *)(param_1 + 0x1b)); }
    (&g_work_building_ptrs)[uVar3 * 0x87] = 0; (&g_entity_state_base)[uVar3 * 0x21c] = 0xd;
    if (*(byte *)(param_1 + 0x21) != 0) { AllocGameObject((&g_static_entity0_entity_id)[uVar3 * 0x87],(uint)*(byte *)(param_1 + 0x21),1); }
    *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641f8) = (&g_static_entity0_entity_id)[uVar3 * 0x87];
    if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\x01'; *(void **)(param_2 + 6) = (void*)&g_static_entity_table_358a0 + uVar3 * 0x10e; }
    return 0;
  }
  msg = s_cm_ExAllocCharacter___gm_AllocSp_1002d364; uVar3 = 0x525a;
LAB_1000fa2c:
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,uVar3,msg,1); return 1;
}

/* 0x1000fad0 */
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 85
// SYMBOL: _cm_ExKillTransporter
// FUNCTION: SERVER 0x1000fad0
int __cdecl cm_ExKillTransporter(int param_1, char *param_2)
{
  void *pvVar1;
  pvVar1 = FindRecordById(*(int *)(param_1 + 0x10));
  if (pvVar1 == (void *)0x0) { LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x52d8, s_cm_ExKillTransporter____invalid_t_1002d3d4,1); return 1; }
  RemoveEntityLink((int)pvVar1);
  if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\0'; param_2[6] = '\0'; param_2[7] = '\0'; param_2[8] = '\0'; param_2[9] = '\0'; }
  return 0;
}

/* 0x1000fb30 */
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 153
// SYMBOL: _CmdCreateBuilding
// FUNCTION: SERVER 0x1000fb30
int __cdecl CmdCreateBuilding(int param_1, char *param_2)
{
  short *puVar1; uint line; char *pcVar2;
  puVar1 = (short *)LookupEntityRecordById(*(int *)(param_1 + 0x10));
  if (puVar1 == (short *)0x0) { pcVar2 = s_cm_ExCreateGeb____Could_not_find_1002d41c; line = 0x5386; }
  else {
    *(int *)(param_1 + 0x14) = g_timestamp_0b6c;
    pcVar2 = (char*)AllocGebaeude(*(byte *)(param_1 + 0x18), (uint)*puVar1);
    if (pcVar2 != (char *)0x0) {
      *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641fc) = *(int *)(pcVar2 + 1);
      if (param_2 != (char *)0x0) { *param_2 = '\x01'; param_2[1] = '\x02'; *(char **)(param_2 + 6) = pcVar2; }
      return 0;
    }
    pcVar2 = s_cm_ExCreateGeb____failed_1002d400; line = 0x539e;
  }
  LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,pcVar2,1); return 1;
}

/* 0x1000fbd0 */
// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 22
// SYMBOL: _cond_write
// FUNCTION: SERVER 0x1000fbd0
int __cdecl cond_write(void *obj, char *buf)
{
  if (buf != (char *)0x0) { *buf = '\x01'; buf[1] = '\0'; buf[6] = '\0'; buf[7] = '\0'; buf[8] = '\0'; buf[9] = '\0'; }
  return 0;
}
