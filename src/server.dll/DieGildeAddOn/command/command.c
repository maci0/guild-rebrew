#include <stdio.h>
#include <string.h>

/* Standard integer types for MSVC6 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned char  byte;

/* Forward declarations for missing types */
typedef struct DISPATCH_OBJ {
    int (__cdecl *func)(int, int);
    int field_28;
} DISPATCH_OBJ;

typedef struct PlayerSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char padding[0x26425C];
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
      *(int *)(g_player_slot_0[*(unsigned char *)(param_1 + 3)].padding + 0x2641fc) = *(int *)(pcVar1 + 1);
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
  *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].padding + 0x2641f8) = g_static_entity0_entity_id[uVar3 * 0x87];
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
    iVar1 = uVar2 * 0x21c;
    *(int *)(g_player_slot_0[*(byte *)(param_1 + 3)].padding + 0x2641f8) = g_static_entity0_entity_id[uVar2 * 0x87];
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
