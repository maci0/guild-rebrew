#include <stdio.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

extern char* g_14a5adc[15];

void __cdecl fcn_0057e880(int, char*, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl gm_GetOppositeStatIndex(int, int);
void __cdecl d2_SetControlText(int, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl io_FormatTextBuffer(void*, ...);
int __cdecl fcn_00526120(int, int);
void __cdecl d2_SetGroupVisibility(int, int);
int __cdecl d2_CheckActionBlocker(char*, int);
int __cdecl gm_GetRangeStatId(int, int);
void __cdecl cm_RequestSetEntityLevel(int, int);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl d2_DestroyForm(int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* Build the stat-level button row for the character sheet: lay out the
   fourteen stat gauges, label them from the opposite-stat table, then run
   the modal input loop that adjusts one stat at a time. */
/* ADDRESS: GOLDTL 0x005d97f0 */
unsigned int __cdecl d2_RunProfessionSelectDialog(unsigned short* actor)
{
    int nextIdx;
    int dialog;
    int profId;
    int ctrlId;
    int rowH;
    int idx;
    int textBase;
    int padOrProf;
    int colW;
    char ch;
    char* srcIcon;
    unsigned short* ent;
    unsigned int result;
    char buf[512];
    char promptBuf[1024];
    unsigned int* iconPtr;
    char* dstIcon;

    ent = actor;
    if (*(char*) &actor[1] == '\x06') {
    result = 0;
    fcn_0057e880(9, 0, 0, 0);
    dialog = d2_LoadForm(0, 0, (char*) 0x6ace10);
    d2_CenterDialogWindows(dialog);
    d2_SetForm(dialog, 0);
    colW = (*(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c) - 0x40) / 5;
    rowH = (*(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f50) - 0x84) / 3;
    padOrProf = (colW - *(short*) ((int) g_772500 + 0x1d978)) / 2;
    io_AppendText(0x1d36);
    iconPtr = (unsigned int*) g_14a5adc;
    textBase = *(char*) ((char*) ent + 9) ? 0x18f : 0x130;
    idx = 0;
    do {
        nextIdx = idx + 1;
        profId = gm_CheckStatLevel(*ent, nextIdx);
        ctrlId = d2_AddElementToWindow((idx % 5) * colW + 0x20 + padOrProf,
                          (idx / 5) * rowH + 100 + padOrProf, idx + 0x5a2,
                          d2_CurrentWindowId);
        ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].value_05c = 1;
        ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].flags_1d0 = 3;
        d2_SetElementFont(ctrlId, 0x56);
        ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].value_06c = 1;
        ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].value_1dc = 0xffffffce;
        ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].value_1e0 = 0x44;
        if (profId) {
            sprintf(buf, (char*) *(unsigned int*) 0x14ac804,
                    gm_GetOppositeStatIndex(profId, (unsigned int) txt_TextEntries[profId + textBase]));
        } else {
            buf[0] = 0;
        }
        d2_SetControlText(ctrlId, (int) buf);
        ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].width = 0xa4;
        if (profId == *(unsigned char*) ((char*) actor + 0x164)) {
            d2_SetElementEnabled(ctrlId, 0);
        } else if (!profId) {
            ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].value_1cc = 0x56;
            ((D2_CONTROL_TL*) g_1015ea0)[ctrlId].value_1d4 = 0xa4;
            srcIcon = (char*) *iconPtr;
            dstIcon = (char*) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[ctrlId] + 0xcc);
            do {
                ch = *srcIcon;
                srcIcon = &srcIcon[1];
                *dstIcon = ch;
                dstIcon = &dstIcon[1];
            } while (ch);
        }
        iconPtr = &iconPtr[1];



        idx = nextIdx;
    } while (idx + 1 <= 0xf);
    g_100f1dc = -1;
    while (main_RunFrameLoop((void*) 0x5d97f0, 0x657c7)) {
        if (g_14ce8e0) {
            g_774654 = 1;
        }
        if (g_14ce8d8 && d2_CurrentElementId != -1) {
            if (he_StartHandlungSearch(2, 2, g_774970, 0, 0x26)) {
                int entOffset;
                entOffset = (unsigned int) g_774970 * 0x21c;
                io_FormatTextBuffer(buf, 0x15bd, g_774970,
                             (*(char*) (entOffset + 0x7f4ca9) ? 0x18f : 0x130)
                                 + *(unsigned char*) (entOffset + 0x7f4e04)
                                 - 1);
                fcn_00526120((int) buf, 4);
            } else {
                d2_SetGroupVisibility(dialog, 0);
                for (idx = 0; idx <= 0xf; idx++) {
                    if (g_100f1dc == idx + 0x5a2) {
                        break;
                    }
                }
                if (idx <= 0xf) {
                    int apDelta;
                    profId = gm_CheckStatLevel(*actor, idx + 1);
                    apDelta = (unsigned int) (profId != 0) * 4 + -8;
                    if (profId != *(unsigned char*) ((char*) actor + 0x164)
                        && d2_CheckActionBlocker((char*) actor, -apDelta)) {
                        for (idx = 0; idx <= 0xf; idx++) {
                            if (g_100f1dc == idx + 0x5a2) {
                                break;
                            }
                        }
                        if (idx <= 0xf) {
                            padOrProf = gm_CheckStatLevel(*actor, idx + 1);
                            if (!padOrProf) {
                                padOrProf = gm_GetRangeStatId(idx + 1, 1);
                            }
                            io_FormatTextBuffer(promptBuf, 0x1d37, -apDelta, padOrProf + textBase);
                            if (fcn_00526120((int) promptBuf, 1)) {
                                cm_RequestSetEntityLevel(*(int*) ((char*) actor + 4), padOrProf);
                                cm_RequestModifyHealth(*(int*) ((char*) actor + 4), apDelta);
                                g_774654 = 1;
                                result = 0x10;
                            }
                        }
                    }
                }
                d2_SetGroupVisibility(dialog, 1);
            }
        }
    }
    d2_DestroyForm(dialog);
    fcn_0057e880(9, 0, 1, 0);
    return result;
    }
    return 0;
}
