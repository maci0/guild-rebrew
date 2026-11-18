extern char g_7e46ac;
extern int g_7746c4;
extern int g_7746c8;
extern int g_7746cc;
extern int g_7746d8;
extern int g_7746dc;
extern int g_774688;
extern int g_77468c;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char *g_6b8014;
extern int g_77250c;
extern int g_1015eac;
extern int g_1015ea8;
extern int g_1040490;
extern int g_1040494;

extern int __cdecl fcn_00506380(int a0, int a1, int a2, int a3);
extern int __cdecl d2_GetResourceData(int a0);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
extern void __cdecl fcn_0047a040(int a0, int a1, int a2, int a3);
extern void __cdecl fcn_0047cba0(int a0, int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x00532bd0 */
void __cdecl fcn_00532bd0(void)
{
    int rightState = 0;
    int leftState = 0;
    int bottomState = 0;
    int topState = 0;
    int resource;
    int selection;

    if (!(g_7e46ac & 8))
        return;
    if (g_7746c4 != 0 || g_7746c8 != 0)
    {
        selection = g_7746c4 ? g_7746c4 : g_7746c8;
        if (selection != 0)
        {
            if (g_7746cc != 0 || g_7746c8 != 0)
            {
                g_7746dc = fcn_00506380(g_774970, selection, g_7746cc, 0);
                if (!(g_7746dc & 0x1000))
                    return;
            }
        }
    }
    if (!(g_7746d8 & 0x1000))
        return;
    resource = d2_GetResourceData(0x52c);
    if (g_774688 == -1)
    {
        rightState = 1;
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xfc, 0x662d70, 0.2f))
            rightState = 2;
    }
    else if (g_774688 == 1)
    {
        leftState = 1;
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xe4, 0x662d70, 0.2f))
            leftState = 2;
    }
    else if (g_774688 == 0)
    {
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xe4, 0x662d70, 0.2f))
            leftState = 1;
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xfc, 0x662d70, 0.2f))
            rightState = 1;
    }
    if (g_77468c == -1)
    {
        bottomState = 1;
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xb4, 0x662d70, 0.2f))
            bottomState = 2;
    }
    else if (g_77468c == 1)
    {
        topState = 1;
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xcc, 0x662d70, 0.2f))
            topState = 2;
    }
    else if (g_77468c == 0)
    {
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xb4, 0x662d70, 0.2f))
            bottomState = 1;
        if (!CompareVector3WithinTolerance(g_6b8014 + 0xcc, 0x662d70, 0.2f))
            topState = 1;
    }
    fcn_0047a040(0, 0, *(int *)(g_77250c + 4), *(int *)(g_77250c + 8));
    if (bottomState == 2)
        fcn_0047cba0(g_1015eac - 0x10, g_1040490 - 0x20, g_77250c, resource, 0);
    else if (bottomState == 1)
        fcn_0047cba0(g_1015eac - 0x10, g_1040490 - 0x20, g_77250c, resource, bottomState);
    if (leftState == 2)
        fcn_0047cba0(4, g_1015ea8, g_77250c, resource, leftState);
    else if (leftState == 1)
        fcn_0047cba0(4, g_1015ea8, g_77250c, resource, 3);
    if (rightState == 2)
        fcn_0047cba0(g_1040494 - 0x96, g_1015ea8, g_77250c, resource, 4);
    else if (rightState == 1)
        fcn_0047cba0(g_1040494 - 0x96, g_1015ea8, g_77250c, resource, 5);
    if (topState == 2)
        fcn_0047cba0(g_1015eac - 0x10, 0x38, g_77250c, resource, 6);
    else if (topState == 1)
        fcn_0047cba0(g_1015eac - 0x10, 0x38, g_77250c, resource, 7);
}
