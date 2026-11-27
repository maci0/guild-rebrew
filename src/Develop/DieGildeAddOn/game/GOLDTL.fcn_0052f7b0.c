typedef unsigned char u8;
#include <string.h>
#include "game_data.h"
typedef struct SelectProto { unsigned char kind; unsigned char rest[0x24c]; } SelectProto;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6a25b4;
extern int g_6a25e0;
extern int g_6a25e4;
extern int g_6a2524;
extern char* g_7e2aa0;
extern int* g_7e2a9c;
extern char* g_7746c0;
extern int g_7746d8;
extern int g_7746dc;
extern char g_7746f4;
extern char g_6b5c60[];
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
int __cdecl fcn_0052f7a0(void);
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
    if (g_6a25b4 != -1 || g_774964 == 0)
        return;
    if (g_7e2aa0 != 0 && fcn_00502cd0(*(int*)(g_7e2aa0 + 0x5d), 2, 6, 0, 0x2a) == 0
        && fcn_00502cd0(*(int*)(g_7e2aa0 + 0x5d), 2, 6, 0, 0x116) == 0)
        d2_SetElementEnabled(g_6a25e4, 0);
    else
        d2_SetElementEnabled(g_6a25e4, 1);
    selected = g_7e2aa0;
    flags = main_LoopFlags & 0x2000;
    if (flags && g_100f1dc != -1) {
        if (g_6a25ec != -1 && d2_CurrentElementId == g_6a25ec) {
            if (g_7746c4 != 0) {
                g_7746dc = gm_GetEntityUiFlags(g_774970, (u8*)g_7746c4, 0, 0);
            } else if (g_7746c8 != 0) {
                if (g_7746cc != 0) {
                    item = (unsigned short*)fcn_00502cd0(*(int*)(g_7746c8 + 0x5d),
                        1, 0, *(unsigned short*)(g_7746c8 + 0x29));
                    g_7746dc = gm_GetEntityUiFlags(g_774970, 0, item, 0);
                } else {
                    g_7746dc = gm_GetEntityUiFlags(g_774970, g_7746c8, 0, 0);
                }
            } else {
                if (selected == 0)
                    goto refresh;
                g_7746dc = gm_GetEntityUiFlags(g_774970, (u8*)selected, 0, 0);
            }
            if (g_7746c4 != 0 && (g_7746dc & 0x10)) {
                d2_RunTechTreeDialog(g_7746c4, *(unsigned short*)(g_7746c4 + 0x29));
            } else if (g_7746c8 != 0 && g_7746cc == 0) {
                d2_RunGebaeudeOptionenDialog((char*)g_7746c8);
            } else if (g_7746c8 != 0 && (g_7746dc & 0x10)) {
                d2_RunTechTreeDialog((char*)g_7746c8, *(unsigned short*)g_7746cc);
            } else if (g_7e2aa0 != 0) {
                kind = gm_GetBuildingTypeCategory(*(u8*)g_7e2aa0);
                g_7746dc = gm_GetEntityUiFlags(g_774970, (u8*)g_7e2aa0, 0, 0);
                if ((kind == 3 || kind == 5) && (g_7746dc & 0x10))
                    d2_ShowGebaeudeOptions(g_7e2aa0);
                else
                    d2_RunGebaeudeOptionenDialog(g_7e2aa0);
            }
        } else if (g_6a25e4 != -1 && d2_CurrentElementId == g_6a25e4) {
            if (selected != 0 && *(u8*)selected != 0x47) {
                kind = gm_GetBuildingTypeCategory(*(u8*)selected);
                if (kind == 1 || kind == 2 || kind == 4 || kind == 7 || kind == 8 ||
                    ((SelectProto*)lpGebaeudePROT)[*(u8*)selected].kind == 0x10 ||
                    ((SelectProto*)lpGebaeudePROT)[*(u8*)selected].kind == 0x1e) {
                    if (d2_TutorialAllowsFlag(0x400) == 1) {
                        g_7746d8 = gm_GetEntityUiFlags(g_774970, (u8*)selected, 0, 0);
                        d2_DispatchTutorialInput(0x12, (int)selected, 0, 0);
                        d2_RunTradeInventoryPanel((int)selected, 1);
                        d2_DispatchTutorialInput(0x12, (int)selected, 1, 0);
                        g_7e2aa0 = selected;
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
                d2_OpenTargetPicker((char*)query, (int)g_6b5c60, (int)g_6b5c60,
                    (void*)fcn_0052f7a0);
                d2_DispatchTutorialInput(0xf, 0, 1, 0);
            }
        }
    }
refresh:
    d2_UpdateSelectionPanel();
    if (g_7e2aa0 == *(char**)0x774780 &&
        g_7746c8 == *(u8**)0x77477c &&
        g_7746c4 == *(char**)0x774778 &&
        g_7746cc == *(char**)0x774784 &&
        g_7e2a9c == *(int**)0x774788 &&
        g_7ea360 == *(int*)0x77478c &&
        (unsigned char)g_7746f4 == *(int*)0x774790 &&
        g_7746f0 == *(int*)0x774794 && g_6a2524 == 0)
        return;
    g_6a2524 = 0;
    d2_DestroySelectionPanel();
    item = (unsigned short*)g_7e2a9c;
    focus = g_7ea360;
    count = g_7746f0;
    if (item != 0 && ((OBJECT_PROTOTYPE*)lpObjektePROT)[*item].kind == 0x1d &&
        count == 0 && focus == 0) {
        d2_OpenTransporterInfoPanel(item);
        goto reload;
    }
    if (g_7746c0 == 0 && g_7746f4 == 0 && count == 0) {
        if (g_7746cc != 0 || focus != 0)
            goto snapshot;
        d2_OpenBuildingInfoPanel();
        goto reload;
    }
    if (count != 0 && (focus != *(int*)0x77478c || count != *(int*)0x774794)) {
        if (count > 1) {
            d2_OpenPersonInfoPanel(0);
        } else {
            d2_OpenPersonInfoPanel((char*)focus);
            *(int*)0x77478c = g_7ea360;
            d2_UpdateSelectionPanel();
        }
        goto reload;
    }
    goto snapshot;
reload:
    focus = g_7ea360;
    item = (unsigned short*)g_7e2a9c;
    count = g_7746f0;
snapshot:
    record = g_7746cc;
    *(int*)0x774790 = (unsigned char)g_7746f4;
    *(int*)0x774794 = count;
    if (g_7746c0 == 0 && g_7746c8 == 0 && g_7746c4 == 0) {
        *(unsigned short**)0x774788 = item;
        selected = g_7e2aa0;
        *(u8**)0x77477c = 0;
        *(char**)0x774778 = 0;
        *(char**)0x774648 = 0;
        *(char**)0x774784 = record;
        *(int*)0x77478c = focus;
        *(char**)0x774780 = selected;
        return;
    }
    selected = g_7e2aa0;
    *(u8**)0x77477c = g_7746c8;
    *(char**)0x774778 = g_7746c4;
    *(char**)0x774784 = record;
    *(int*)0x77478c = focus;
    *(unsigned short**)0x774788 = item;
    *(char**)0x774780 = selected;
    if ((item != 0 || record != 0) && g_6a25b8 == -1) {
        *(char**)0x774648 = g_7746c0;
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
    if (g_7e2aa0 == 0 && g_7746c8 == 0) {
        *(char**)0x774648 = 0;
        return;
    }
    *(char**)0x774648 = g_7746c0;
    if (g_7e2aa0 != 0)
        pick = g_7e2aa0;
    else if (g_7746c8 != 0)
        pick = (char*)g_7746c8;
    d2_ShowBuildingInfoPanel((u8*)pick);
    d2_UpdateSelectionPanel();
}
