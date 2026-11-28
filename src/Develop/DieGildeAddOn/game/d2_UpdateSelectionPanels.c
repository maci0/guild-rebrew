typedef unsigned char u8;
#include <string.h>
#include "game_data.h"
typedef struct SelectProto { unsigned char kind; unsigned char rest[0x24c]; } SelectProto;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6a25b4;
extern int g_6a25e0;
extern int g_6a25e4;
extern int g_6a2524;
extern char* d2_SelectedBuilding;
extern int* d2_SelectedItem;
extern char* d3_FocusedEntityObject;
extern int d2_SelectedEntityUiFlags;
extern int g_7746dc;
extern char g_7746f4;
extern char str_empty[];
#include "Develop/DieGildeAddOn/game/object_prototype.h"
void* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl d2_SetElementEnabled(int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl gm_GetEntityUiFlags(int, unsigned char*, unsigned short*, int);
int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
int __cdecl d2_OpenTargetPicker(char*, int, int, void*);
int __cdecl d2_RunTradeInventoryPanel(int, int);
void __cdecl d2_ResetUiInputAndBounds(void);
void __cdecl d2_RunTechTreeDialog(char*, int);
void __cdecl d2_RunGebaeudeOptionenDialog(char*);
void __cdecl d2_ShowGebaeudeOptions(char*);
int __cdecl d2_NoopTargetPickerCallback(void);
void __cdecl d2_UpdateSelectionPanel(void);
void __cdecl d2_DestroySelectionPanel(void);
void __cdecl d2_OpenTransporterInfoPanel(unsigned short*);
void __cdecl d2_OpenPersonInfoPanel(char*);
void __cdecl d2_OpenBuildingInfoPanel(void);
void __cdecl d2_ShowGebaeudeItemInfoPanel(unsigned short*);
void __cdecl d2_ShowBuildingInfoPanel(unsigned char*);

/* Dispatch selection actions, then refresh changed panel state. */
/* ADDRESS: GOLDTL 0x0052f7b0 */
void __cdecl d2_UpdateSelectionPanels(void)
{
    int query[20];
    char* selected;
    char* record;
    unsigned short* item;
    int focus;
    int count;
    int kind;
    int flags;

    char* pick;

    pick = 0;
    if (g_6a25b4 != -1 || gm_InWorldHud == 0)
        return;
    if (d2_SelectedBuilding != 0 && fcn_00502cd0(*(int*)(d2_SelectedBuilding + 0x5d), 2, 6, 0, 0x2a) == 0
        && fcn_00502cd0(*(int*)(d2_SelectedBuilding + 0x5d), 2, 6, 0, 0x116) == 0)
        d2_SetElementEnabled(g_6a25e4, 0);
    else
        d2_SetElementEnabled(g_6a25e4, 1);
    selected = d2_SelectedBuilding;
    flags = main_LoopFlags & 0x2000;
    if (flags && d2_DialogButtonAction != -1) {
        if (g_6a25ec != -1 && d2_CurrentElementId == g_6a25ec) {
            if (d2_VisitedBuilding != 0) {
                g_7746dc = gm_GetEntityUiFlags(gm_LocalPlayerSlot, (u8*)d2_VisitedBuilding, 0, 0);
            } else if (d2_InteriorBuilding != 0) {
                if (sv_SelectedBuilding != 0) {
                    item = (unsigned short*)fcn_00502cd0(*(int*)(d2_InteriorBuilding + 0x5d),
                        1, 0, *(unsigned short*)(d2_InteriorBuilding + 0x29));
                    g_7746dc = gm_GetEntityUiFlags(gm_LocalPlayerSlot, 0, item, 0);
                } else {
                    g_7746dc = gm_GetEntityUiFlags(gm_LocalPlayerSlot, d2_InteriorBuilding, 0, 0);
                }
            } else {
                if (selected == 0)
                    goto refresh;
                g_7746dc = gm_GetEntityUiFlags(gm_LocalPlayerSlot, (u8*)selected, 0, 0);
            }
            if (d2_VisitedBuilding != 0 && (g_7746dc & 0x10)) {
                d2_RunTechTreeDialog(d2_VisitedBuilding, *(unsigned short*)(d2_VisitedBuilding + 0x29));
            } else if (d2_InteriorBuilding != 0 && sv_SelectedBuilding == 0) {
                d2_RunGebaeudeOptionenDialog((char*)d2_InteriorBuilding);
            } else if (d2_InteriorBuilding != 0 && (g_7746dc & 0x10)) {
                d2_RunTechTreeDialog((char*)d2_InteriorBuilding, *(unsigned short*)sv_SelectedBuilding);
            } else if (d2_SelectedBuilding != 0) {
                kind = gm_GetBuildingTypeCategory(*(u8*)d2_SelectedBuilding);
                g_7746dc = gm_GetEntityUiFlags(gm_LocalPlayerSlot, (u8*)d2_SelectedBuilding, 0, 0);
                if ((kind == 3 || kind == 5) && (g_7746dc & 0x10))
                    d2_ShowGebaeudeOptions(d2_SelectedBuilding);
                else
                    d2_RunGebaeudeOptionenDialog(d2_SelectedBuilding);
            }
        } else if (g_6a25e4 != -1 && d2_CurrentElementId == g_6a25e4) {
            if (selected != 0 && *(u8*)selected != 0x47) {
                kind = gm_GetBuildingTypeCategory(*(u8*)selected);
                if (kind == 1 || kind == 2 || kind == 4 || kind == 7 || kind == 8 ||
                    ((SelectProto*)lpGebaeudePROT)[*(u8*)selected].kind == 0x10 ||
                    ((SelectProto*)lpGebaeudePROT)[*(u8*)selected].kind == 0x1e) {
                    if (d2_TutorialAllowsFlag(0x400) == 1) {
                        d2_SelectedEntityUiFlags = gm_GetEntityUiFlags(gm_LocalPlayerSlot, (u8*)selected, 0, 0);
                        d2_DispatchTutorialInput(0x12, (int)selected, 0, 0);
                        d2_RunTradeInventoryPanel((int)selected, 1);
                        d2_DispatchTutorialInput(0x12, (int)selected, 1, 0);
                        d2_SelectedBuilding = selected;
                        d2_ResetUiInputAndBounds();
                    }
                }
            }
        } else if (g_6a25e0 != -1 && d2_CurrentElementId == g_6a25e0) {
            if (d2_TutorialAllowsFlag(0x80) == 1) {
                memset(query, 0, sizeof(query));
                query[1] = 0;
                query[5] = 4;
                d2_DispatchTutorialInput(0xf, 0, 0, 0);
                d2_OpenTargetPicker((char*)query, (int)str_empty, (int)str_empty,
                    (void*)d2_NoopTargetPickerCallback);
                d2_DispatchTutorialInput(0xf, 0, 1, 0);
            }
        }
    }
refresh:
    d2_UpdateSelectionPanel();
    if (d2_SelectedBuilding == *(char**)0x774780 &&
        d2_InteriorBuilding == *(u8**)0x77477c &&
        d2_VisitedBuilding == *(char**)0x774778 &&
        sv_SelectedBuilding == *(char**)0x774784 &&
        d2_SelectedItem == *(int**)0x774788 &&
        d2_SelectedPerson == *(int*)0x77478c &&
        (unsigned char)g_7746f4 == *(int*)0x774790 &&
        g_7746f0 == *(int*)0x774794 && g_6a2524 == 0)
        return;
    g_6a2524 = 0;
    d2_DestroySelectionPanel();
    item = (unsigned short*)d2_SelectedItem;
    focus = d2_SelectedPerson;
    count = g_7746f0;
    if (item != 0 && ((OBJECT_PROTOTYPE*)lpObjektePROT)[*item].kind == 0x1d &&
        count == 0 && focus == 0) {
        d2_OpenTransporterInfoPanel(item);
        goto reload;
    }
    if (d3_FocusedEntityObject == 0 && g_7746f4 == 0 && count == 0) {
        if (sv_SelectedBuilding != 0 || focus != 0)
            goto snapshot;
        d2_OpenBuildingInfoPanel();
        goto reload;
    }
    if (count != 0 && (focus != *(int*)0x77478c || count != *(int*)0x774794)) {
        if (count > 1) {
            d2_OpenPersonInfoPanel(0);
        } else {
            d2_OpenPersonInfoPanel((char*)focus);
            *(int*)0x77478c = d2_SelectedPerson;
            d2_UpdateSelectionPanel();
        }
        goto reload;
    }
    goto snapshot;
reload:
    focus = d2_SelectedPerson;
    item = (unsigned short*)d2_SelectedItem;
    count = g_7746f0;
snapshot:
    record = sv_SelectedBuilding;
    *(int*)0x774790 = (unsigned char)g_7746f4;
    *(int*)0x774794 = count;
    if (d3_FocusedEntityObject == 0 && d2_InteriorBuilding == 0 && d2_VisitedBuilding == 0) {
        *(unsigned short**)0x774788 = item;
        selected = d2_SelectedBuilding;
        *(u8**)0x77477c = 0;
        *(char**)0x774778 = 0;
        *(char**)0x774648 = 0;
        *(char**)0x774784 = record;
        *(int*)0x77478c = focus;
        *(char**)0x774780 = selected;
        return;
    }
    selected = d2_SelectedBuilding;
    *(u8**)0x77477c = d2_InteriorBuilding;
    *(char**)0x774778 = d2_VisitedBuilding;
    *(char**)0x774784 = record;
    *(int*)0x77478c = focus;
    *(unsigned short**)0x774788 = item;
    *(char**)0x774780 = selected;
    if ((item != 0 || record != 0) && g_6a25b8 == -1) {
        *(char**)0x774648 = d3_FocusedEntityObject;
        if (item != 0) {
            d2_ShowGebaeudeItemInfoPanel(item);
            d2_UpdateSelectionPanel();
            return;
        }
        if (record != 0) {
            d2_ShowGebaeudeItemInfoPanel((unsigned short*)record);
            d2_UpdateSelectionPanel();
        }
        return;
    }
    if (d2_SelectedBuilding == 0 && d2_InteriorBuilding == 0) {
        *(char**)0x774648 = 0;
        return;
    }
    *(char**)0x774648 = d3_FocusedEntityObject;
    if (d2_SelectedBuilding != 0)
        pick = d2_SelectedBuilding;
    else if (d2_InteriorBuilding != 0)
        pick = (char*)d2_InteriorBuilding;
    d2_ShowBuildingInfoPanel((u8*)pick);
    d2_UpdateSelectionPanel();
}
