#include <stdio.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

extern char* g_14a5adc[15];

void __cdecl fcn_0057e880(int, char*, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl gm_GetOppositeStatIndex(int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl io_FormatTextBuffer(void*, ...);
int __cdecl fcn_00526120(int, int);
void __cdecl d2_SetGroupVisibility(int, int);
int __cdecl fcn_00525f60(char*, int);
int __cdecl fcn_00507400(int, int);
void __cdecl fcn_004c6470(int, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_00471e30(int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* Build the stat-level button row for the character sheet: lay out the
   fourteen stat gauges, label them from the opposite-stat table, then run
   the modal input loop that adjusts one stat at a time. */
/* ADDRESS: GOLDTL 0x005d97f0 */
unsigned int __cdecl fcn_005d97f0(unsigned short* a0)
{
    int v1;
    int v4;
    int v5;
    int v6;
    int v7;
    int v8;
    int v10;
    int v14;
    int v15;
    char v2;
    char* v9;
    unsigned short* v11;
    unsigned int v19;
    char v12[512];
    char v13[1024];
    unsigned int* v18;
    char* v17;

    v11 = a0;
    if (*(char*) &a0[1] == '\x06') {
    v19 = 0;
    fcn_0057e880(9, 0, 0, 0);
    v4 = fcn_00470820(0, 0, (char*) 0x6ace10);
    d2_CenterDialogWindows(v4);
    d2_SetForm(v4, 0);
    v15 = (*(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c) - 0x40) / 5;
    v7 = (*(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f50) - 0x84) / 3;
    v14 = (v15 - *(short*) ((int) g_772500 + 0x1d978)) / 2;
    io_AppendText(0x1d36);
    v18 = (unsigned int*) g_14a5adc;
    v10 = *(char*) ((char*) v11 + 9) ? 0x18f : 0x130;
    v8 = 0;
    do {
        v1 = v8 + 1;
        v5 = gm_CheckStatLevel(*v11, v1);
        v6 = fcn_0046f740((v8 % 5) * v15 + 0x20 + v14,
                          (v8 / 5) * v7 + 100 + v14, v8 + 0x5a2,
                          d2_CurrentWindowId);
        ((D2_CONTROL_TL*) g_1015ea0)[v6].value_05c = 1;
        ((D2_CONTROL_TL*) g_1015ea0)[v6].flags_1d0 = 3;
        d2_SetElementFont(v6, 0x56);
        ((D2_CONTROL_TL*) g_1015ea0)[v6].value_06c = 1;
        ((D2_CONTROL_TL*) g_1015ea0)[v6].value_1dc = 0xffffffce;
        ((D2_CONTROL_TL*) g_1015ea0)[v6].value_1e0 = 0x44;
        if (v5) {
            sprintf(v12, (char*) *(unsigned int*) 0x14ac804,
                    gm_GetOppositeStatIndex(v5, (unsigned int) txt_TextEntries[v5 + v10]));
        } else {
            v12[0] = 0;
        }
        fcn_0046f9b0(v6, (int) v12);
        ((D2_CONTROL_TL*) g_1015ea0)[v6].width = 0xa4;
        if (v5 == *(unsigned char*) ((char*) a0 + 0x164)) {
            fcn_00472640(v6, 0);
        } else if (!v5) {
            ((D2_CONTROL_TL*) g_1015ea0)[v6].value_1cc = 0x56;
            ((D2_CONTROL_TL*) g_1015ea0)[v6].value_1d4 = 0xa4;
            v9 = (char*) *v18;
            v17 = (char*) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[v6] + 0xcc);
            do {
                v2 = *v9;
                v9 = &v9[1];
                *v17 = v2;
                v17 = &v17[1];
            } while (v2);
        }
        v18 = &v18[1];



        v8 = v1;
    } while (v8 + 1 <= 0xf);
    g_100f1dc = -1;
    while (fcn_005373e0((void*) 0x5d97f0, 0x657c7)) {
        if (g_14ce8e0) {
            g_774654 = 1;
        }
        if (g_14ce8d8 && d2_CurrentElementId != -1) {
            if (he_StartHandlungSearch(2, 2, g_774970, 0, 0x26)) {
                int v7_ent;
                v7_ent = (unsigned int) g_774970 * 0x21c;
                io_FormatTextBuffer(v12, 0x15bd, g_774970,
                             (*(char*) (v7_ent + 0x7f4ca9) ? 0x18f : 0x130)
                                 + *(unsigned char*) (v7_ent + 0x7f4e04)
                                 - 1);
                fcn_00526120((int) v12, 4);
            } else {
                d2_SetGroupVisibility(v4, 0);
                for (v8 = 0; v8 <= 0xf; v8++) {
                    if (g_100f1dc == v8 + 0x5a2) {
                        break;
                    }
                }
                if (v8 <= 0xf) {
                    int v7_cost;
                    v5 = gm_CheckStatLevel(*a0, v8 + 1);
                    v7_cost = (unsigned int) (v5 != 0) * 4 + -8;
                    if (v5 != *(unsigned char*) ((char*) a0 + 0x164)
                        && fcn_00525f60((char*) a0, -v7_cost)) {
                        for (v8 = 0; v8 <= 0xf; v8++) {
                            if (g_100f1dc == v8 + 0x5a2) {
                                break;
                            }
                        }
                        if (v8 <= 0xf) {
                            v14 = gm_CheckStatLevel(*a0, v8 + 1);
                            if (!v14) {
                                v14 = fcn_00507400(v8 + 1, 1);
                            }
                            io_FormatTextBuffer(v13, 0x1d37, -v7_cost, v14 + v10);
                            if (fcn_00526120((int) v13, 1)) {
                                fcn_004c6470(*(int*) ((char*) a0 + 4), v14);
                                fcn_004c6ae0(*(int*) ((char*) a0 + 4), v7_cost);
                                g_774654 = 1;
                                v19 = 0x10;
                            }
                        }
                    }
                }
                d2_SetGroupVisibility(v4, 1);
            }
        }
    }
    fcn_00471e30(v4);
    fcn_0057e880(9, 0, 1, 0);
    return v19;
    }
    return 0;
}
