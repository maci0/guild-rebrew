#include "gold_gui.h"
extern GuiWin g_00f8f120[];
extern int g_00f8f08c;
extern int g_00f8f088;
void __cdecl fcn_0046cd90(int, int, int);

/* ADDRESS: GOLD 0x004756a0 */
void __cdecl fcn_004756a0(int index, unsigned char flags)
{
    GuiWin* window;
    int x;
    window = &g_00f8f120[index];
    if (flags & 1)
        x = g_00f8f08c - window->width / 2;
    else
        x = window->x;
    if (flags & 2) {
        fcn_0046cd90(x, g_00f8f088 - window->height / 2, window->id);
        return;
    }
    fcn_0046cd90(x, window->y, window->id);
}
