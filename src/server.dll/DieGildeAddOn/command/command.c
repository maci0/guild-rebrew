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
extern char s_cm_ChkSellObjekt_Not_enough_Credits_at_destination_1002c7d8[];
extern char s_cm_ChkSellObjekt_Inventory_voll_1002c810[];
extern char s_cm_ChkSellObjekt_Lager_voll_1002c834[];
extern char s_cm_ChkSellObjekt_Invalid_ziel_besitzer_id_1002c854[];
extern char s_cm_ChkSellObjekt_Not_enough_Objekts_at_source_1002c884[];
extern char s_cm_ChkSellObjekt_No_Objekts_at_source_1002c8b4[];
extern char s_cm_ChkSellObjekt_Invalid_quell_besitzer_id_1002c8dc[];
extern char s_cm_ChkChangeAttribute_Invalid_action_on_player_PartnerID_already_set_1002c90c[];
extern char s_cm_ChkChangeAttribute_Invalid_action_on_player_ID_does_not_exist_1002c958[];
extern char s_cm_ChkChangeAttribute_Invalid_action_on_player_Change_ID_1002c9a0[];
extern char s_cm_ChkChangeAttribute_Invalid_Id_1002c9e0[];
extern char s_cm_ChkChangeBits_Invalid_action_on_player_flags_pef_GELIEBTE_already_set_1002ca04[];
extern char s_cm_ChkChangeBits_Invalid_Id_1002ca54[];
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

/* Module Globals */
extern int g_timestamp_0b6c;
extern int g_something_1;
extern int g_plant_count;
extern int g_sequence_counter;
extern int g_entity_id_start;
extern int g_mem_pool_overflow_flag;
extern unsigned char g_current_season;
extern PlayerSlot g_player_slot_0[8];
extern short g_static_entity_table_358a0;
extern char g_static_entity0_entity_id;
extern short g_static_entity0_lineage;
extern char g_static_entity0_field_60;
extern int g_static_entity0_field_54;
extern char g_static_entity0_pos_x;
extern char g_static_entity0_owner_id;
extern char g_entity_state_base;
extern char g_entity_type_table;
extern char g_work_building_ptrs;
extern char g_entity_table_end;
extern char g_currency_type_array;
extern char g_relationship_matrix_primary;
extern char g_relationship_matrix_secondary;
extern int g_game_speed_value;
extern char g_game_speed_table;
extern int _g_game_speed_index;
extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern float _g_stat_min;
extern float _g_stat_max;
extern char g_empty_string;

/* 0x1000cb20 */
int __cdecl cm_ChkMoveCredits(int param_1, char* param_2)
{
    int iVar1;
    int iVar2;
    int *piVar3;
    unsigned int line;
    char *msg;
    void *local_8;
    void *local_4;
    
    iVar1 = param_1;
    if (*(int *)(param_1 + 0x14) == -1) {
        return 0;
    }
    iVar2 = get_field_by_type((char *)param_1, *(int *)(param_1 + 0x14));
    *(int *)(iVar1 + 0x14) = iVar2;
    iVar2 = ResolveEntityById((void **)&param_1, &local_8, &local_4, iVar2);
    if (iVar2 == 0) {
        msg = s_cm_ChkMoveCredits_Invalid_quell_besitzer_id_1002c7a4;
        line = 0x22f9;
    }
    else {
        if (param_1 == 0) {
            if (local_8 == (void *)0x0) {
                piVar3 = (int *)((int)local_4 + 0x178);
            }
            else {
                piVar3 = (int *)((int)local_8 + 0x14);
            }
        }
        else {
            piVar3 = (int *)(param_1 + 0x5d);
        }
        iVar2 = QueryEntitySum(*piVar3, *(unsigned char *)(iVar1 + 0x1c));
        if (-1 < iVar2 - *(int *)(iVar1 + 0x1d)) {
            return 0;
        }
        msg = s_cm_ChkMoveCredits_Not_enough_money_at_source_1002c774;
        line = 0x231b;
    }
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, line, msg, 1);
    return 1;
}

/* 0x1000cbd0 */
int __cdecl cm_ChkSellObjekt(char* cmd)
{
    short sVar1;
    int iVar2;
    int *piVar3;
    unsigned short *puVar4;
    unsigned int line;
    char *pcVar6;
    short *local_c;
    void *local_8;
    void *local_4;
    
    pcVar6 = cmd;
    if (*(int *)(cmd + 0x14) != -1) {
        iVar2 = get_field_by_type(cmd, *(int *)(cmd + 0x14));
        *(int *)(pcVar6 + 0x14) = iVar2;
        iVar2 = ResolveEntityById(&local_8, (void **)&cmd, (void **)&local_c, iVar2);
        if (iVar2 == 0) {
            pcVar6 = s_cm_ChkSellObjekt_Invalid_quell_besitzer_id_1002c8dc;
            line = 0x236b;
            goto LAB_1000cdb7;
        }
        if (local_8 == (void *)0x0) {
            if (cmd == (char *)0x0) {
                piVar3 = (int *)(local_c + 0xbc);
            }
            else {
                piVar3 = (int *)(cmd + 0x14);
            }
        }
        else {
            piVar3 = (int *)((int)local_8 + 0x5d);
        }
        puVar4 = (unsigned short *)StartEntityQuery(*piVar3, 1, 0, (unsigned int)*(unsigned short *)(pcVar6 + 0x18));
        if (puVar4 == (unsigned short *)0x0) {
            pcVar6 = s_cm_ChkSellObjekt_No_Objekts_at_source_1002c8b4;
            line = 0x2383;
            goto LAB_1000cdb7;
        }
        if (*(int *)(puVar4 + 7) < *(int *)(pcVar6 + 0x1f)) {
            pcVar6 = s_cm_ChkSellObjekt_Not_enough_Objekts_at_source_1002c884;
            line = 0x238f;
            goto LAB_1000cdb7;
        }
    }
    if (*(int *)(pcVar6 + 0x10) != -1) {
        iVar2 = get_field_by_type(pcVar6, *(int *)(pcVar6 + 0x10));
        *(int *)(pcVar6 + 0x10) = iVar2;
        iVar2 = ResolveEntityById(&local_4, (void **)&cmd, (void **)&local_c, iVar2);
        if (iVar2 == 0) {
            pcVar6 = s_cm_ChkSellObjekt_Invalid_ziel_besitzer_id_1002c854;
            line = 0x23ab;
            goto LAB_1000cdb7;
        }
        if (local_4 == (void *)0x0) {
            if (cmd == (char *)0x0) {
                iVar2 = CheckInventoryCapacity((char *)local_c, (unsigned int)*(unsigned short *)(pcVar6 + 0x18), *(int *)(pcVar6 + 0x1f));
                if (iVar2 < *(int *)(pcVar6 + 0x1f)) {
                    pcVar6 = s_cm_ChkSellObjekt_Inventory_voll_1002c810;
                    line = 0x23e3;
                    goto LAB_1000cdb7;
                }
            }
            else {
                sVar1 = *(short *)cmd;
                if ((((sVar1 == 0x2a) || (sVar1 == 0x116)) || (sVar1 == 0x1dd)) &&
                   (iVar2 = gm_KannObjektHergestellt((int)cmd, (unsigned int)*(unsigned short *)(pcVar6 + 0x18), *(int *)(pcVar6 + 0x1f)),
                   iVar2 < *(int *)(pcVar6 + 0x1f))) {
                    pcVar6 = s_cm_ChkSellObjekt_Lager_voll_1002c834;
                    line = 0x23cd;
                    goto LAB_1000cdb7;
                }
                local_c = ResolveParentEntity((short *)cmd);
            }
        }
    }
    return 0;

LAB_1000cdb7:
    LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, line, pcVar6, 1);
    return 1;
}

// ... more functions to be added ...
