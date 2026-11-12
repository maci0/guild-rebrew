#include "gold_gui.h"
#include "Develop/Units/Error/error_message.h"
extern GuiWin g_00f8f120[];
extern GuiEnt* g_00f8f080;
extern short g_00fb9070;
extern short g_00fb9072;
int __cdecl fcn_0046cd70(short, short, int);
void __cdecl fcn_004730d0(int, GuiWin*);
void __cdecl fcn_00475e70(int, int);
void __cdecl fcn_00472c70(GuiWin*, int*, int*);

/* ADDRESS: GOLD 0x00473340 */
int __cdecl fcn_00473340(int x, int y, int image, int window_id, int context)
{
    GuiWin* window;
    int element;

    window = &g_00f8f120[window_id];
    if (window->active == 0) {
        return -1;
    }
    if (window->count >= 0x180) {
        ReportClientMessage("Too many objects on window!");
        return -1;
    }
    window->list[window->count] = fcn_0046cd70((short)(window->x + x), (short)(window->y - window->scroll + y), image);
    element = window->list[window->count];
    if (element != -1) {
        fcn_004730d0(element, window);
        g_00f8f080[element].parent = window;
        g_00f8f080[element].f22 = 0;
        g_00f8f080[element].f24 = g_00fb9070;
        g_00f8f080[element].f1e = 0;
        g_00f8f080[element].f20 = g_00fb9072;
        g_00f8f080[element].f40 = g_00f8f080[window->id].f40;
        *(int*)((char*)&g_00f8f080[element] + 0x38) = *(int*)((char*)&g_00f8f080[window->id] + 0x38);
        fcn_00475e70(element, context);
        window->count++;
        fcn_00472c70(window, &x, &window_id);
        if ((short)y + g_00f8f080[element].f16 > *(int*)((char*)window + 0x244)) {
            *(int*)((char*)window + 0x244) = (short)y + x * 2 + g_00f8f080[element].f16;
        }
    }
    return element;
}
