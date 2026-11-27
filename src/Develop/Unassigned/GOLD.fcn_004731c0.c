#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
extern GOLD_GUI_WINDOW g_00f8f120[];
int __cdecl d2_CreateElementAt(short, short, int);
void __cdecl d2_ReorderControlInWindow(int, char*);
void __cdecl d2_GetWindowBorderSize(void*, int*, int*);
void __cdecl ReportClientMessage(const char*);

/* ADDRESS: GOLD 0x004731c0 */
int __cdecl d2_AddElementToWindow(short x, short y, int image, int window)
{
    GOLD_GUI_WINDOW* owner;
    int index;
    int height;

    owner = &g_00f8f120[window];
    window = 0;
    if (!owner->active) return -1;
    if (owner->count >= 0x180) {
        ReportClientMessage("Too many objects on window!");
        return -1;
    }
    owner->list[owner->count] = d2_CreateElementAt(
        x + owner->x - *(short*) ((char*) owner + 0x258),
        y + owner->y - (short) owner->scroll, image);
    index = owner->list[owner->count];
    if (index != -1) {
        d2_ReorderControlInWindow(index, (char*) owner);
        g_00f8f080[index].parent = (void*) owner;
        g_00f8f080[index].f22 = 0;
        g_00f8f080[index].f24 = g_00fb9070;
        g_00f8f080[index].f1e = 0;
        g_00f8f080[index].f20 = g_00fb9072;
        g_00f8f080[index].f40 = g_00f8f080[owner->id].f40;
        *(int*) ((char*) &g_00f8f080[index] + 0x38) =
            *(int*) ((char*) &g_00f8f080[owner->id] + 0x38);
        ++owner->count;
        d2_GetWindowBorderSize(owner, &window, &image);
        height = g_00f8f080[index].f16;
        if (y + height > *(int*) ((char*) owner + 0x244)) {
            *(int*) ((char*) owner + 0x244) = y + window * 2 + height;
        }
    }
    return index;
}
