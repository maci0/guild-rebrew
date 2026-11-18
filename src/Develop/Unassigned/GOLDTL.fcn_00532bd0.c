extern char main_LoopFlags;
extern int g_7746c4;
extern int g_7746c8;
extern int g_7746cc;
extern int g_7746d8;
extern int g_7746dc;
extern int d3_CameraHorizontalIndex;
extern int d3_CameraVerticalStep;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char *d3_ActiveCamera;
extern int g_77250c;
extern int d2_CenterX;
extern int d2_DialogCenterY;
extern int d2_ScreenHeight;
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

    if (!(main_LoopFlags & 8))
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
    if (d3_CameraHorizontalIndex == -1)
    {
        rightState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xfc, 0x662d70, 0.2f))
            rightState = 2;
    }
    else if (d3_CameraHorizontalIndex == 1)
    {
        leftState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xe4, 0x662d70, 0.2f))
            leftState = 2;
    }
    else if (d3_CameraHorizontalIndex == 0)
    {
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xe4, 0x662d70, 0.2f))
            leftState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xfc, 0x662d70, 0.2f))
            rightState = 1;
    }
    if (d3_CameraVerticalStep == -1)
    {
        bottomState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xb4, 0x662d70, 0.2f))
            bottomState = 2;
    }
    else if (d3_CameraVerticalStep == 1)
    {
        topState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xcc, 0x662d70, 0.2f))
            topState = 2;
    }
    else if (d3_CameraVerticalStep == 0)
    {
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xb4, 0x662d70, 0.2f))
            bottomState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xcc, 0x662d70, 0.2f))
            topState = 1;
    }
    fcn_0047a040(0, 0, *(int *)(g_77250c + 4), *(int *)(g_77250c + 8));
    if (bottomState == 2)
        fcn_0047cba0(d2_CenterX - 0x10, d2_ScreenHeight - 0x20, g_77250c, resource, 0);
    else if (bottomState == 1)
        fcn_0047cba0(d2_CenterX - 0x10, d2_ScreenHeight - 0x20, g_77250c, resource, bottomState);
    if (leftState == 2)
        fcn_0047cba0(4, d2_DialogCenterY, g_77250c, resource, leftState);
    else if (leftState == 1)
        fcn_0047cba0(4, d2_DialogCenterY, g_77250c, resource, 3);
    if (rightState == 2)
        fcn_0047cba0(g_1040494 - 0x96, d2_DialogCenterY, g_77250c, resource, 4);
    else if (rightState == 1)
        fcn_0047cba0(g_1040494 - 0x96, d2_DialogCenterY, g_77250c, resource, 5);
    if (topState == 2)
        fcn_0047cba0(d2_CenterX - 0x10, 0x38, g_77250c, resource, 6);
    else if (topState == 1)
        fcn_0047cba0(d2_CenterX - 0x10, 0x38, g_77250c, resource, 7);
}
