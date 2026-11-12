#include <string.h>

extern void* g_fb9074;
extern unsigned int g_fb9084;
extern unsigned int g_fb91a8;
extern int g_006333cc;
char* __cdecl m_alloc(int, const char*);
void __cdecl fcn_0045f600(int);

/* ADDRESS: GOLD 0x0045fa70 */
void __cdecl fcn_0045fa70(int textures, int hicol, int flags, int mode)
{
    g_fb9084 = textures;
    *(int*) 0xfb91b8 = 0;
    *(int*) 0xfb9078 = hicol;
    *(int*) 0x5fd0b0 = flags;
    *(int*) 0xfb91b0 = 0;
    g_fb91a8 = 0;
    g_fb9074 = m_alloc(textures * 0x80, "d3_ts:InitTextures(tex)");
    if (hicol > 0)
        *(char**) 0xfb91a4 = m_alloc(hicol * 0x308, "d3_ts:InitTextures(hicol)");
    else
        *(char**) 0xfb91a4 = 0;
    *(int*) 0xfb91a0 = 0;
    memset((void*) 0xfb90a0, 0, 0x80);
    memset((void*) 0xfb9120, 0, 0x80);
    *(int*) 0xfb91ac = g_006333cc;
    fcn_0045f600(mode);
}
