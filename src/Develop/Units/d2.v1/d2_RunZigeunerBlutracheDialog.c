#include <string.h>
#include <stddef.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* Private inferred views; only the accessed offsets and extents are known. */
typedef struct {
    char *entity;
    int control;
    char unknown[8];
    int x, y;
    char rest[0x20];
} ITEM;

typedef struct {
    int enabled, size, field8, fieldc, kind, field14;
    char field18[4];
    unsigned short excluded[4];
    char remainder[0x2c];
} REQUEST;

typedef char item_size_check[sizeof(ITEM) == 0x38 ? 1 : -1];
typedef char item_control_check[offsetof(ITEM, control) == 4 ? 1 : -1];
typedef char item_position_check[offsetof(ITEM, x) == 0x10 && offsetof(ITEM, y) == 0x14 ? 1 : -1];
typedef char request_size_check[sizeof(REQUEST) == 0x50 ? 1 : -1];
typedef char request_excluded_check[offsetof(REQUEST, excluded) == 0x1c ? 1 : -1];

#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId, g_14b59e8, g_14b59ec;
extern int g_14b59fc, g_14b5a00, io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction, d2_CurrentElementId, gm_TargetPersonTypeMask, g_66601c;
extern volatile unsigned int gm_GameTicks;
extern char *d2_FileObjTable, *d2_Controls;
extern char gm_EntitySlotTable[], d2_WindowMetricsView[], str_dollar_C[];
extern char *g_14b59f0, *g_14b59f4;

void __cdecl d2_ShowGreenMessageBox(int, int, int);
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_CreateButtonRow(int, int, int *, int, ...);
int __cdecl gm_CountBuildingExtensions(char *);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_BuildPersonStatusDesc(ITEM *);
void __cdecl d2_DrawPersonCard(int, int, int, int, ITEM *, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl amt_GetRoleLevel(int);
int __cdecl d2_CheckActionBlocker(char *, int);
int __cdecl io_FormatTextBuffer(char *, int, ...);
float __cdecl gm_CalcSkillDuelScore(char *, char *, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl he_ShowZigeunerGroupMessage(unsigned short *, int, char **);
void __cdecl d2_ShowModalMessageBox(char *, int);
char *__cdecl d2_OpenTargetPicker(REQUEST *, char *, int, int);
int __cdecl main_RunFrameLoop(void (__cdecl *)(void *), int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005e53b0 */
/* ADDRESS: GOLDDE 0x005c6670 */
void __cdecl d2_RunZigeunerBlutracheDialog(void *arg)
{
    ITEM items[5];
    REQUEST request;
    int cache[5], buttons[2];
    char *selected[4];
    char text[0x800];
    char *house, *p;
    int window, cost, count, i, n, j;
    int refresh;
    unsigned int last;

    memset(items, 0, sizeof(items));
    for (i = 0; i < 5; ++i) cache[i] = -1;
    refresh = 1;
    cost = 0;
    last = 0;
    house = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
    if (house[0x1cc] & 8) {
        d2_ShowGreenMessageBox(g_14b59e8, g_14b59ec, 0);
        return;
    }
    window = d2_LoadForm(0, 0, "Locations\\zigeuner\\blutrache");
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(window);
    d2_SetForm(window, 0);
    d2_InitWindowBounds(d2_CurrentWindowId);
    d2_SetForm(window, 1);
    items[0].x = (*(int *)(d2_WindowMetricsView + d2_CurrentWindowId * 972) - *(short *)(d2_FileObjTable + 0x1ebd8)) / 2;
    items[0].y = 30;
    items[1].x = (*(int *)(d2_WindowMetricsView + d2_CurrentWindowId * 972) - *(short *)(d2_FileObjTable + 0x1ebd8)) / 3 - 10;
    items[1].y = 125;
    items[2].x = (*(int *)(d2_WindowMetricsView + d2_CurrentWindowId * 972) - *(short *)(d2_FileObjTable + 0x1ebd8)) * 2 / 3 + 10;
    items[2].y = 125;
    items[3].x = (*(int *)(d2_WindowMetricsView + d2_CurrentWindowId * 972) - *(short *)(d2_FileObjTable + 0x1ebd8)) / 3 - 100;
    items[3].y = 220;
    items[4].x = (*(int *)(d2_WindowMetricsView + d2_CurrentWindowId * 972) - *(short *)(d2_FileObjTable + 0x1ebd8)) * 2 / 3 + 100;
    items[4].y = 220;
    d2_SetForm(window, 3);
    d2_CreateButtonRow(d2_CurrentWindowId, 0, buttons, 2, g_14b59fc, g_14b5a00);
    do {
        if (refresh) {
            count = gm_CountBuildingExtensions((char *)arg) + 1;
            last = gm_GameTicks;
            refresh = 0;
            d2_SetForm(window, 1);
            io_AppendText((int)str_dollar_C);
            io_AppendText(0x41b2);
            cost = 0;
            for (i = 0; i < 5; ++i) {
                if (i >= count) { items[i].entity = 0; cache[i] = -1; }
                d2_BuildPersonStatusDesc(&items[i]);
                d2_DrawPersonCard(items[i].x, items[i].y, d2_CurrentWindowId, 0x54, &items[i], 1);
                if (i < count) {
                    d2_SetElementEnabled(items[i].control, 1);
                    ((D2_CONTROL_TL*) d2_Controls)[items[i].control].value_05c = 1;
                    ((D2_CONTROL_TL*) d2_Controls)[items[i].control].flags_1d0 = 3;
                    *(char**) (&((D2_CONTROL_TL*) d2_Controls)[items[i].control].associated_object) = items[i].entity;
                    ((D2_CONTROL_TL*) d2_Controls)[items[i].control].value_060 = 0;
                } else {
                    ((D2_CONTROL_TL*) d2_Controls)[items[i].control].value_060 = 1;
                }
                cost += (items[i].entity && i) ? (amt_GetRoleLevel((unsigned char)items[i].entity[0x166]) / 3 + 2) : 0;
            }
            d2_SetForm(window, 2);
            io_AppendText((int)str_dollar_C, cost);
            io_AppendText(0x41b6, cost);
            d2_SetElementEnabled(buttons[0], items[0].entity != 0 && cost != 0);
        }
        if (io_RightButtonReleased) d2_DialogCloseRequested = 1;
        else if (d2_DialogButtonAction != -1) {
            if (d2_CurrentElementId == buttons[0]) {
                house = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
                if (d2_CheckActionBlocker(house, cost) == 1) {
                    p = items[0].entity;
                    io_FormatTextBuffer(text, 0x41bf, *(unsigned short *)p);
                    n = 0;
                    for (i = 1; i < 5; ++i) {
                        if (items[i].entity) {
                            j = 50 - (int)(gm_CalcSkillDuelScore((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], items[i].entity, 4) * -50.0f);
                            cm_RequestCopyEntityData(*(unsigned short *)items[0].entity, *(unsigned short *)items[i].entity, -j, 1);
                            selected[n++] = items[i].entity;
                        }
                    }
                    gm_ModifyHealth(*(int *)((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot] + 4), -cost);
                    cm_RequestChangeBits(*(int *)((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot] + 4), 0x1cc, 4, 8, 0);
                    he_ShowZigeunerGroupMessage((unsigned short *)p, n, selected);
                    io_FormatTextBuffer(text, 0x41b9, 0x41b2);
                    d2_ShowModalMessageBox(text, 0);
                    d2_DialogCloseRequested = 1;
                }
            } else if (d2_CurrentElementId == buttons[1]) d2_DialogCloseRequested = 1;
            else {
                for (i = 0; i < 5; ++i) {
                    if (d2_CurrentElementId == items[i].control) {
                        memset(&request, 0, sizeof(request));
                        n = 0;
                        for (j = 0; j < 5; ++j) {
                            if (j != i) request.excluded[n++] = items[j].entity ? *(unsigned short *)items[j].entity : 0xffff;
                        }
                        request.field8 = gm_TargetPersonTypeMask; request.fieldc = g_66601c;
                        request.enabled = 1; request.size = 0x400;
                        request.kind = 6; request.field14 = 2;
                        p = d2_OpenTargetPicker(&request, i ? g_14b59f4 : g_14b59f0, 0, 0);
                        items[i].entity = p;
                        cache[i] = p ? *(int *)(p + 4) : -1;
                        refresh = 1;
                        break;
                    }
                }
            }
        } else if (gm_GameTicks > last + 140u) {
            for (i = 0; i < 5; ++i) {
                p = items[i].entity;
                if (p && (*(unsigned short *)p == 0xffff || *(int *)(p + 4) != cache[i])) {
                    items[i].entity = 0;
                    cache[i] = -1;
                }
            }
            refresh = 1;
        }
    } while (main_RunFrameLoop(d2_RunZigeunerBlutracheDialog, 0x677c7));
    d2_DestroyForm(window);
    d3_EndCameraAndUiMode();
}
