#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
extern int g_7749e4;
extern int g_6a4768;
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_SetForm(int, int);
void __cdecl d2_DestroyElement(int slot);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_00469c40(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x00545780 */
void __cdecl fcn_00545780(char* obj)
{
    int i;

    if (*(int*) (obj + 0x74) == 0) {
        return;
    }
    if (*(int*) (*(int*) (obj + 0x74) + 4) != -1) {
        d2_SetForm(g_77e8a0, 0);
        d2_DestroyElement(*(int*) (*(int*) (obj + 0x74) + 4));
        *(int*) (*(int*) (obj + 0x74) + 4) = -1;
    } else {
        __asm { int 3 }
    }
    if (*(int*) (*(int*) (obj + 0x74) + 8) != -1) {
        fcn_00471e30(*(int*) (*(int*) (obj + 0x74) + 8));
        *(int*) (*(int*) (obj + 0x74) + 8) = -1;
    }
    if (g_7749e4 == *(int*) (obj + 0x74)) {
        g_7749e4 = 0;
    }
    *(int*) (obj + 0x74) = 0;
    for (i = 0; i < 16; i++) {
        if (g_77e8c0[i].h == -1) {
            break;
        }
    }
    if (i < 16) {
        for (; i < 16; i++) {
            if (i < 15) {
                if (g_77e8c0[i + 1].h != -1) {
                    g_77e8c0[i].h = g_77e8c0[i + 1].h;
                    g_77e8c0[i].p = g_77e8c0[i + 1].p;
                    g_77e8c0[i].x8 = g_77e8c0[i + 1].x8;
                    *(D2_ACTION_POPUP_SLOT**) (g_77e8c0[i].p + 0x74) = &g_77e8c0[i];
                    g_77e8c0[i + 1].h = -1;
                    g_77e8c0[i + 1].p = 0;
                    g_77e8c0[i + 1].x8 = -1;
                    if (g_77e8c0[i].h == -1 && g_77e8c0[i].p != 0) {
                        __asm { int 3 }
                    }
                }
            }
            if (g_77e8c0[i].h != -1) {
                fcn_00469c40(
                    ((D2_CONTROL_TL*) g_1015ea0)[g_77e8c0[i].h].x - 0x20,
                    ((D2_CONTROL_TL*) g_1015ea0)[g_77e8c0[i].h].y,
                    g_77e8c0[i].h);
            }
        }
    }
    for (i = 0; i < 16; i++) {
        if (g_77e8c0[i].h != -1) {
            g_6a4768 = i;
        }
    }
}
