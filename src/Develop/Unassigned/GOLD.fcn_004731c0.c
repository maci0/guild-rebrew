#include "Develop/Units/d2.v1/d2_gui.h"
extern GuiWin g_00f8f120[];
int __cdecl fcn_0046cd70(short, short, int);
void __cdecl fcn_004730d0(int, char*);
void __cdecl fcn_00472c70(void*, int*, int*);
void __cdecl ReportClientMessage(const char*);

/* ADDRESS: GOLD 0x004731c0 */
int __cdecl fcn_004731c0(short x, short y, int image, int window)
{
    GuiWin* owner;
    int index;
    int offset;
    int height;

    owner = &g_00f8f120[window];
    window = 0;
    if (!owner->active) return -1;
    if (owner->count >= 0x180) {
        ReportClientMessage("Too many objects on window!");
        return -1;
    }
    owner->list[owner->count] = fcn_0046cd70(
        x + owner->x - *(short*) ((char*) owner + 0x258),
        y + owner->y - owner->scroll, image);
    index = owner->list[owner->count];
    if (index != -1) {
        fcn_004730d0(index, (char*) owner);
        offset = index * 0x2ec;
        ((GuiEnt*) (offset + (char*) g_00f8f080))->parent = owner;
        ((GuiEnt*) (offset + (char*) g_00f8f080))->f22 = 0;
        ((GuiEnt*) (offset + (char*) g_00f8f080))->f24 = g_00fb9070;
        ((GuiEnt*) (offset + (char*) g_00f8f080))->f1e = 0;
        ((GuiEnt*) (offset + (char*) g_00f8f080))->f20 = g_00fb9072;
        ((GuiEnt*) (offset + (char*) g_00f8f080))->f40 = g_00f8f080[owner->id].f40;
        *(int*) (offset + (char*) g_00f8f080 + 0x38) =
            *(int*) ((char*) &g_00f8f080[owner->id] + 0x38);
        ++owner->count;
        fcn_00472c70(owner, &window, &image);
        height = ((GuiEnt*) (offset + (char*) g_00f8f080))->f16;
        if (y + height > *(int*) ((char*) owner + 0x244)) {
            *(int*) ((char*) owner + 0x244) = y + window * 2 + height;
        }
    }
    return index;
}
