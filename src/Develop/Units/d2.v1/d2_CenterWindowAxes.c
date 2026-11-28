#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
extern GOLD_GUI_WINDOW g_00f8f120[];
extern int g_00f8f08c;
extern int g_00f8f088;
void __cdecl d2_MoveElement(int, int, int);

/* ADDRESS: GOLD 0x004756a0 */
void __cdecl d2_CenterWindowAxes(int index, unsigned char flags)
{
    GOLD_GUI_WINDOW* window;
    int x;
    int y;
    window = &g_00f8f120[index];
    if (flags & 1)
        x = g_00f8f08c - window->width / 2;
    else
        x = window->x;
    if (flags & 2)
        y = g_00f8f088 - window->height / 2;
    else
        y = window->y;
    d2_MoveElement(x, y, window->id);
}
