extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_DialogCloseRequested;
extern int g_774698;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
#include "Develop/DieGildeAddOn/game/client_actions.h"
void* __cdecl d2_LoadForm(short a, short b, char* c);
void __cdecl d2_CenterDialogWindows(int a);
void __cdecl d2_SetForm(int a, int b);
int __cdecl io_AppendText(void* id, ...);
int __cdecl d2_GetWindowListItem(int a, int b, int c);
int __cdecl gm_AmountToUnits(int a, unsigned char b);
int __cdecl gm_ConvertUnitsToAmount(int a, unsigned char index);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl main_RunFrameLoop(void* a, int b);
int __cdecl d2_GetControlValue(int a);
int __cdecl gm_QueryEntitySum(int a, unsigned char b);
int __cdecl gm_AccumulateTyped2(int a);
void __cdecl d2_CreateGuiWindow(int a, ...);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int d);
void __cdecl cm_BeginPacketFieldDelta(void* a, int b);
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int c, void* d);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl d2_DestroyForm(int a);

/* ADDRESS: GOLDTL 0x005a4bb0 */
void __cdecl d2_RunKreditFreigabeDialog(char* o)
{
    char* dlg;
    int have;
    int r;
    int txt;
    int it1;
    int it2;
    int sval;
    int v;
    int d;

    dlg = (char*) d2_LoadForm(0, 0, "locations\\geldleihe\\geldleihe_KreditFreigabe");
    d2_CenterDialogWindows((int)dlg);
    d2_SetForm((int)dlg, 1);
    io_AppendText((void*)0x18e5);
    have = gm_QueryEntitySum(*(int*)(o + 0x5d), gm_ActiveTownIndex);
    d2_SetForm((int)dlg, 2);
    txt = io_AppendText((void*)0x18e6, (void*)(2 * *(u16*)(gm_ActiveTownIndex * 0x2f4 + 0x8680b4) + 0x9a8));
    it1 = d2_GetWindowListItem((int)dlg, 2, txt);
    it2 = d2_GetWindowListItem((int)dlg, 2, txt + 1);
    d2_CreateGuiWindow(it1, 5, 0x28, *(int*)(o + 0x65));
    sval = gm_AccumulateTyped2(*(u16*)(o + 0x27) * 0x21c + 0x7f4ca0);
    d2_CreateGuiWindow(it2, 0, gm_AmountToUnits(sval, gm_ActiveTownIndex), gm_AmountToUnits(have, gm_ActiveTownIndex));
    d2_SetOverlayAnimation(0, 0);
    while (main_RunFrameLoop((void*)0x5a4bb0, 0x677c7) != 0) {
        if (io_RightButtonReleased != 0 || d2_DialogButtonAction == 1)
            d2_DialogCloseRequested = 1;
        v = gm_ConvertUnitsToAmount(d2_GetControlValue(it2), gm_ActiveTownIndex);
        g_774698 = have - v;
        if (d2_DialogButtonAction == 2) {
            r = gm_ConvertUnitsToAmount(d2_GetControlValue(it2), gm_ActiveTownIndex);
            if (have < r) {
                d = r - have;
                cm_RequestMoveCredits(*(int*)(o + 1),
                             *(int*)(0x7f4ca4 + *(u16*)(o + 0x27) * 0x21c), gm_ActiveTownIndex, d);
            } else {
                d = have - r;
                cm_RequestMoveCredits(*(int*)(0x7f4ca4 + *(u16*)(o + 0x27) * 0x21c),
                             *(int*)(o + 1), gm_ActiveTownIndex, d);
            }
            r = d2_GetControlValue(it1);
            cm_BeginPacketFieldDelta(o, *(int*)(o + 1));
            cm_AppendPacketFieldDelta(4, 1, 0x65, &r);
            cm_RequestChangeAttribute();
            d2_DialogCloseRequested = 1;
        }
    }
    d2_DestroyForm((int)dlg);
    g_774698 = 0;
}
