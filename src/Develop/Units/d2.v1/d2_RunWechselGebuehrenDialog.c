#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"

void* __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_GetWindowListItem(int dlg, int a, int b);
void __cdecl d2_CreateGuiWindow(int w, int a, int b, int c);
int __cdecl main_RunFrameLoop(void* fn, int name);
int __cdecl d2_GetControlValue(int w);
void __cdecl cm_BeginPacketFieldDelta(char* o, int v);
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int c, void* p);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl d2_DestroyForm(int dlg);

/* ADDRESS: GOLDTL 0x005a6570 */
/* ADDRESS: GOLDDE 0x0058b280 */
void __cdecl d2_RunWechselGebuehrenDialog(char* o)
{
    char* dlg;
    int id;
    int w1;
    int w2;

    dlg = d2_LoadForm(0, 0, "locations\\geldleihe\\geldleihe_WechselGebuehren");
    d2_CenterDialogWindows((int) dlg);
    d2_SetForm((int) dlg, 2);
    io_AppendText(0x1908);
    d2_SetForm((int) dlg, 1);
    id = io_AppendText(0x1907);
    w1 = d2_GetWindowListItem((int) dlg, 1, id);
    w2 = d2_GetWindowListItem((int) dlg, 1, id + 1);
    d2_CreateGuiWindow(w2, 3, 0xf, *(int*) (o + 0x69));
    d2_CreateGuiWindow(w1, 3, 0xf, *(int*) (o + 0x6d));

    while (main_RunFrameLoop((void*) d2_RunWechselGebuehrenDialog, 0x677c7) != 0) {
        if (io_RightButtonReleased != 0 || d2_DialogButtonAction == 1)
            d2_DialogCloseRequested = 1;
        if (d2_DialogButtonAction == 2) {
            int a;
            int b;

            a = d2_GetControlValue(w2);
            b = d2_GetControlValue(w1);
            cm_BeginPacketFieldDelta(o, *(int*) (o + 1));
            cm_AppendPacketFieldDelta(4, 1, 0x69, &a);
            cm_AppendPacketFieldDelta(4, 1, 0x6d, &b);
            cm_RequestChangeAttribute();
            d2_DialogCloseRequested = 1;
        } else if (d2_DialogButtonAction == 1) {
            d2_DialogCloseRequested = 1;
        }
    }
    d2_DestroyForm((int) dlg);
}
