#include <string.h>
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"
#include "d2_gui.h"

extern char g_7f4ca0[];
extern int g_666018; extern int g_66601c;
extern char g_6811b0[];
extern int d2_CurrentWindowId;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int d2_CurrentElementId;
#include "Develop/DieGildeAddOn/game/entity_record.h"
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ShowGreenMessageBox(int, int, int);
int __cdecl d2_OpenTargetPicker(char*, int, int, void*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl d2_GetControlValue(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CheckActionBlocker(void*, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005e6360 */
void __cdecl d2_RunEhrerbietungDialog(char* entity)
{
    int ids[2];
    int query[20];
    char text[1024];
    char* target;
    int dialog;
    int control;
    int amount;

    if (*(unsigned short*) (entity + 0x27) == 0xffff) {
        d3_EndCameraAndUiMode();
        return;
    }
    if (*(unsigned char*) &((ENTITY_RECORD*) g_7f4ca0)[g_774970].entity_flags & 0x20) {
        d2_ShowGreenMessageBox(*(int*) 0x14b5b3c, *(int*) 0x14b5b40, 0);
        return;
    }
    memset(query, 0, sizeof(query));
    memset(query + 7, -1, 8 * sizeof(int));
    query[0] = 1;
    query[1] = 0x400;
    query[4] = 6;
    query[2] = g_666018; query[3] = g_66601c;
    target = (char*) d2_OpenTargetPicker((char*) query, *(int*) 0x14b5b44, 0, 0);
    if (target == 0) {
        d3_EndCameraAndUiMode();
        return;
    }
    dialog = d2_LoadForm(0, 0, "Locations\\zigeuner\\blutrache");
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(dialog);
    d2_SetForm(dialog, 0);
    d2_InitWindowBounds(d2_CurrentWindowId);
    d2_SetForm(dialog, 2);
    control = d2_AddWindowValueGauge(0x57, 7, 200, 0, 100, 0x7b, 2, d2_CurrentWindowId);
    d2_SetElementValue(control, 2, 8, 2, 1);
    d2_SetForm(dialog, 3);
    d2_CreateButtonRow(d2_CurrentWindowId, 0, ids, 2, *(int*) 0x14b5b50, *(int*) 0x14b5b54);
    do {
        amount = d2_GetControlValue(control);
        d2_SetForm(dialog, 1);
        io_AppendText((int) g_6811b0);
        io_AppendText(0x420a, 0x4207, *(unsigned short*) target, amount);
        if (g_14ce8e0 != 0) {
            g_774654 = 1;
        } else if (g_100f1dc != -1) {
            if (d2_CurrentElementId == ids[0]) {
                if (d2_CheckActionBlocker((char*) &((ENTITY_RECORD*) g_7f4ca0)[g_774970], amount) == 1) {
                    cm_RequestChangeBits(((ENTITY_RECORD*) g_7f4ca0)[g_774970].entity_id, 0x1cc, 4, 0x20, 0);
                    gm_ModifyHealth(((ENTITY_RECORD*) g_7f4ca0)[g_774970].entity_id, -amount);
                    cm_RequestCopyEntityData(((ENTITY_RECORD*) g_7f4ca0)[g_774970].entity_id, *(int*) (target + 4), amount * 5, 1);
                    if (target[2] == 6 || target[2] == 7) {
                        io_FormatTextBuffer(text, 0x420e, g_774970);
                        he_PostEntityMessage(*(int*) (target + 4), -1, text, 0, 0x5f0, "_NACHRICHTEN_ZIGEUNER_04");
                    }
                    g_774654 = 1;
                }
            } else if (d2_CurrentElementId == ids[1]) {
                g_774654 = 1;
            }
        }
    } while (main_RunFrameLoop((void*) d2_RunEhrerbietungDialog, 0x677c7) != 0);
    d2_DestroyForm(dialog);
    d3_EndCameraAndUiMode();
}
