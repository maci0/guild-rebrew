#include "gold_gui.h"

extern char* g_f8f080;
extern GuiWin g_f8f120[];

/* ADDRESS: GOLD 0x00475a90 */
void __cdecl fcn_00475a90(int id, int flag)
{
    GuiEnt* e;
    GuiWin* w;
    int i;
    int enabled;

    enabled = flag == 0;

    e = &((GuiEnt*) g_f8f080)[id];
    *(int*) ((char*) e + 0x38) = enabled;
    if (e->kind != 0x40)
        return;
    w = &g_f8f120[e->bild_offset];
    for (i = 0; i < w->count; i++)
        fcn_00475a90(w->list[i], flag);
    if (*(int*) ((char*) w + 0x3b8) != -1)
        fcn_00475a90(*(int*) ((char*) w + 0x3b8), flag);
    if (*(int*) ((char*) w + 0x3bc) != -1)
        fcn_00475a90(*(int*) ((char*) w + 0x3bc), flag);
    if (*(int*) ((char*) w + 0x3c0) != -1)
        fcn_00475a90(*(int*) ((char*) w + 0x3c0), flag);



}
