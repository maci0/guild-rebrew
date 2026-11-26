extern char* g_1015ea0; /* 0x1015ea0, GUI pool, stride 0x2f4 */
extern char* g_773d78;   /* 0x773d78 */
extern int d2_CurrentWindowId; extern int d2_CurrentElementId;     /* 0x67d370 */
extern int g_100f1dc;    /* 0x100f1dc */
extern int g_14abc14;    /* 0x14abc14 */

int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
void __cdecl fcn_0046f940(int element, char* text);
void __cdecl fcn_0046f9b0(int element, int a2);
void __cdecl d2_SetElementFont(int element, int a2);
char* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
char* __cdecl gm_EntityAccumulate(int entity);
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);
void __cdecl fcn_00526920(char* text, int a2, int a3);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005b6130 */
void __cdecl fcn_005b6130(int a0, char* a1)
{
    char label[512];
    int v1;
    char* v2;
    int v3;
    int v4;
    unsigned int v8;
    int* v6;
    int v7;

    v4 = 0;
    if (*(int*) 0x777cc0 > 0) {
        v7 = 0x5a;
        do {
            v3 = *(int*) (v4 * 4 + 0x777cc4);
            v1 = *(int*) (v3 + 0x24);
            if (v1) {
                v2 = gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (v1 + 0xb4));
                if (v2) {
                    v8 = 0x1a3e;
                    io_FormatTextBuffer(label, (char*) v8, v2);
                }
            } else {
                v2 = gm_EntityAccumulate(v3);
                if (*v2 == 'D') {
                    v2 = g_773d78;
                }
                v8 = 0x1a3f;
                io_FormatTextBuffer(label, (char*) v8, v2);
            }
            v3 = *(int*) (v4 * 4 + 0x777cdc);
            if (v3 != -1) {
                fcn_0046f940(v3, label);
                if (a1 != v2 &&
                    *(int*) (v4 * 4 + 0x777cd0) == -1) {
                    v3 = d2_AddElementToWindow(0, v7, 5, d2_CurrentWindowId);
                    *(int*) (v4 * 4 + 0x777cd0) = v3;
                    *(unsigned int*) (&((D2_CONTROL_TL*) (g_1015ea0))[v3].value_05c) = 1;
                    *(char**) (&((D2_CONTROL_TL*) g_1015ea0)[
                               *(int*) (v4 * 4 + 0x777cd0)].associated_object) = v2;
                    d2_SetElementFont(*(unsigned int*) (v4 * 4 + 0x777cd0),
                                 0x56);
                    *(unsigned int*) (&((D2_CONTROL_TL*) g_1015ea0)[
                                      *(int*) (v4 * 4 + 0x777cd0)].flags_1d0) = 3;
                }
                v3 = *(int*) (v4 * 4 + 0x777cd0);
                if (v3 != -1) {
                    fcn_0046f9b0(v3, g_14abc14);
                }
            }
            v4 += 1;
            v7 += 0x78;
        } while (v4 < *(int*) 0x777cc0);
    }

    if (*(char*) (a0 + 0x270) == 2 && g_100f1dc == 5) {
        v6 = (int*) 0x777cd0;
        do {
            v4 = *v6;
            if (v4 != -1 && d2_CurrentElementId == v4) {
                fcn_00526920(*(char**) (&((D2_CONTROL_TL*) g_1015ea0)[
                                        v4].associated_object),
                             -1, 0x6b5c60);
            }
            v6 += 1;
        } while ((int) v6 < 0x777cdc);
    }
}
