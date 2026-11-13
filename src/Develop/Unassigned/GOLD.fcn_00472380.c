#include <string.h>
#include "gold_gui.h"
extern GuiWin g_00f8f120[];
extern GuiEnt* g_00f8f080;
extern short g_005fe73c;
void* __cdecl m_alloc(unsigned int, const char*);
int __cdecl fcn_00478cb0(int*, int);
void __cdecl fcn_004796b0(int);
int __cdecl fcn_0046c9e0(void);
int __cdecl fcn_004731c0(short, short, int, int);
#define I32(p) (*(int*)(p))
#define U16(p) (*(unsigned short*)(p))
#define U8(p) (*(unsigned char*)(p))

/* ADDRESS: GOLD 0x00472380 */
int __cdecl fcn_00472380(short x, short y, short width, short height, unsigned int flags)
{
    int index;
    char* window;
    int element;
    int descriptor[16];

    I32(0x6ed9b4)++;
    if (I32(0x6ed9b4) >= 0x61) {
        I32(0x6ed9b4) = 1;
    }
    for (index = 0; index < 0x60; index++) {
        if (g_00f8f120[index].active == 0) {
            break;
        }
    }
    if (index >= 0x60) {
        return -1;
    }
    window = (char*)&g_00f8f120[index];
    U16(window + 6) = y;
    U16(window + 4) = x;
    U16(window + 8) = width;
    U16(window + 0xa) = height;
    I32(window + 0xc) = flags;
    U16(window + 0x10) = 4;
    U16(window + 0x12) = 4;
    U16(window + 0x14) = 4;
    U16(window + 0x16) = 4;
    I32(window + 0x390) = 0;
    U8(window + 0x260) = 4;
    I32(window + 0x264) = 0;
    if (flags & 4) {
        I32(window + 0x278) = I32(0x5fe744);
    }
    if (flags & 0x200) {
        I32(window + 0x244) = height;
        I32(window + 0x248) = -height;
        I32(window + 0x24c) = -height;
    }
    if (flags & 1) {
        I32(window + 0x394) = 0x3f266666;
    }
    if (flags & 0x1000) {
        memset(descriptor, 0, sizeof(descriptor));
        descriptor[1] = width;
        descriptor[2] = height;
        I32(window + 0x20) = fcn_00478cb0(descriptor, 0xb);
        if (I32(window + 0x20) == 0) {
            return 0;
        }
    }
    if ((I32(window + 0xc) & 1) && (I32(window + 0xc) & 0x1000)) {
        memset(descriptor, 0, sizeof(descriptor));
        descriptor[1] = *(short*)(window + 8);
        descriptor[2] = *(short*)(window + 0xa);
        I32(window + 0x24) = fcn_00478cb0(descriptor, 0xb);
        if (I32(window + 0x24) == 0) {
            return 0;
        }
    }
    if (I32(window + 0xc) & 0x10000) {
        memset(descriptor, 0, sizeof(descriptor));
        descriptor[1] = *(short*)(window + 8);
        descriptor[2] = *(short*)(window + 0xa);
        I32(window + 0x28) = fcn_00478cb0(descriptor, 0xb);
        fcn_004796b0(I32(window + 0x28));
        if (I32(window + 0x28) == 0) {
            return 0;
        }
    }
    element = fcn_0046c9e0();
    g_00f8f080[element].kind = 0x40;
    g_00f8f080[element].x = *(short*)(window + 4);
    g_00f8f080[element].y = *(short*)(window + 6);
    g_00f8f080[element].w = *(short*)(window + 8);
    g_00f8f080[element].f16 = *(short*)(window + 0xa);
    g_00f8f080[element].f08 = index + 0x400;
    g_00f8f080[element].bild_offset = index;
    g_00f8f080[element].f22 = *(short*)(window + 6);
    g_00f8f080[element].f20 = *(short*)(window + 8) + *(short*)(window + 4);
    g_00f8f080[element].f1e = *(short*)(window + 4);
    g_00f8f080[element].f24 = *(short*)(window + 0xa) + *(short*)(window + 6);
    g_00f8f080[element].f1c = 2;
    g_00f8f080[element].data = window;
    g_00f8f080[element].parent = 0;
    I32(window + 0x26c) = element;
    I32(window + 0x270) = 1;
    U16(window + 0x268) = 2;
    I32(window + 0x388) = -1;
    U16(window + 0x27c) = g_005fe73c;
    I32(window + 0x3b8) = -1;
    I32(window + 0x3bc) = -1;
    I32(window + 0x3c0) = -1;
    I32(window + 0x274) = -1;
    I32(window + 0x280) = 1;
    I32(window + 0x3ac) = -1;
    I32(window + 0x3a8) = -1;
    I32(window + 0x3b0) = -1;
    I32(window + 0x18) = (int)m_alloc(0x600, "d2:win_obj");
    I32(window + 0x398) = 0;
    I32(window + 0x39c) = 0;
    I32(window + 0x3a0) = 0;
    I32(window + 0x3a4) = 0;
    if (flags & 8) {
        fcn_004731c0(3, 3, I32(0x5fe734), index);
    }
    if (flags & 0x20) {
        fcn_004731c0(*(short*)(window + 8) - 0xc, 3, I32(0x5fe734) + 1, index);
        fcn_004731c0(*(short*)(window + 8) - 0xc, *(short*)(window + 0xa) - 10, I32(0x5fe734) + 2, index);
    }
    if (flags & 0x10) {
        I32(window + 0x2c) = (int)m_alloc(0x17d0, "d2_t:w->txt");
    }
    I32(0x6ed980) = (int)window;
    I32(0x6ed938) = index;
    return index;
}
