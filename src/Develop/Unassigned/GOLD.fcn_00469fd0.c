#include <string.h>
#include "gold_gui.h"
extern GuiEnt* g_00f8f080;
int __cdecl fcn_0046ea00(const char*, int);

/* ADDRESS: GOLD 0x00469fd0 */
void __cdecl fcn_00469fd0(int index, int text_index)
{
    char* record;
    char* window;
    char* cursor;
    int length;

    record = (char*)0xfa6020 + index * 0x160;
    window = (char*)g_00f8f080[*(int*)(record + 0x134)].parent;
    if (window == 0) {
        return;
    }
    cursor = *(char**)(record + 0x154);
    if (cursor == 0) {
        return;
    }
    if (*(int*)(record + 0x158) != 0) {
        memmove(cursor, cursor + *(int*)(record + 0x158),
            strlen(*(char**)(window + 0x2c)) + (*(char**)(window + 0x2c) - cursor) + 1);
    }
    length = (int)strlen(((char**)0x143a1c0)[text_index]);
    *(int*)(record + 0x158) = length;
    cursor = *(char**)(record + 0x154);
    memmove(cursor + length, cursor,
        strlen(*(char**)(window + 0x2c)) + (*(char**)(window + 0x2c) - cursor) + 1);
    memcpy(*(char**)(record + 0x154), ((char**)0x143a1c0)[text_index], *(int*)(record + 0x158));
    *(int*)(record + 0x10) = fcn_0046ea00(((char**)0x143a1c0)[text_index], *(int*)(record + 0x138));
    g_00f8f080[*(int*)(record + 0x134)].w = *(short*)(record + 0x10);
}
