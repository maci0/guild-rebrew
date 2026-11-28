extern char d3_ZeroVec4[];
extern char main_LoopFlags;
extern int d2_VisitedBuilding;
extern int d2_InteriorBuilding;
extern int sv_SelectedBuilding;
extern int d2_SelectedEntityUiFlags;
extern int g_7746dc;
extern int d3_CameraHorizontalIndex;
extern int d3_CameraVerticalStep;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char *d3_ActiveCamera;
extern int d2_ScreenSurface;
extern int d2_CenterX;
extern int d2_DialogCenterY;
extern int d2_ScreenHeight;
extern int g_1040494;

extern int __cdecl gm_GetEntityUiFlags(int a0, int a1, int a2, int a3);
extern int __cdecl d2_GetResourceData(int a0);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
extern void __cdecl d2_SetClipRect(int a0, int a1, int a2, int a3);
extern void __cdecl d2_DrawSpriteFromSet(int a0, int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x00532bd0 */
/* ADDRESS: GOLDDE 0x0051b4c0 */
void __cdecl d2_DrawCameraScrollArrows(void)
{
    int rightState = 0;
    int leftState = 0;
    int bottomState = 0;
    int topState = 0;
    int resource;
    int selection;

    if (!(main_LoopFlags & 8))
        return;
    if (d2_VisitedBuilding != 0 || d2_InteriorBuilding != 0)
    {
        selection = d2_VisitedBuilding ? d2_VisitedBuilding : d2_InteriorBuilding;
        if (selection != 0)
        {
            if (sv_SelectedBuilding != 0 || d2_InteriorBuilding != 0)
            {
                g_7746dc = gm_GetEntityUiFlags(gm_LocalPlayerSlot, selection, sv_SelectedBuilding, 0);
                if (!(g_7746dc & 0x1000))
                    return;
            }
        }
    }
    if (!(d2_SelectedEntityUiFlags & 0x1000))
        return;
    resource = d2_GetResourceData(0x52c);
    if (d3_CameraHorizontalIndex == -1)
    {
        rightState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xfc, (int) &d3_ZeroVec4, 0.2f))
            rightState = 2;
    }
    else if (d3_CameraHorizontalIndex == 1)
    {
        leftState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xe4, (int) &d3_ZeroVec4, 0.2f))
            leftState = 2;
    }
    else if (d3_CameraHorizontalIndex == 0)
    {
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xe4, (int) &d3_ZeroVec4, 0.2f))
            leftState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xfc, (int) &d3_ZeroVec4, 0.2f))
            rightState = 1;
    }
    if (d3_CameraVerticalStep == -1)
    {
        bottomState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xb4, (int) &d3_ZeroVec4, 0.2f))
            bottomState = 2;
    }
    else if (d3_CameraVerticalStep == 1)
    {
        topState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xcc, (int) &d3_ZeroVec4, 0.2f))
            topState = 2;
    }
    else if (d3_CameraVerticalStep == 0)
    {
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xb4, (int) &d3_ZeroVec4, 0.2f))
            bottomState = 1;
        if (!CompareVector3WithinTolerance(d3_ActiveCamera + 0xcc, (int) &d3_ZeroVec4, 0.2f))
            topState = 1;
    }
    d2_SetClipRect(0, 0, *(int *)(d2_ScreenSurface + 4), *(int *)(d2_ScreenSurface + 8));
    if (bottomState == 2)
        d2_DrawSpriteFromSet(d2_CenterX - 0x10, d2_ScreenHeight - 0x20, d2_ScreenSurface, resource, 0);
    else if (bottomState == 1)
        d2_DrawSpriteFromSet(d2_CenterX - 0x10, d2_ScreenHeight - 0x20, d2_ScreenSurface, resource, bottomState);
    if (leftState == 2)
        d2_DrawSpriteFromSet(4, d2_DialogCenterY, d2_ScreenSurface, resource, leftState);
    else if (leftState == 1)
        d2_DrawSpriteFromSet(4, d2_DialogCenterY, d2_ScreenSurface, resource, 3);
    if (rightState == 2)
        d2_DrawSpriteFromSet(g_1040494 - 0x96, d2_DialogCenterY, d2_ScreenSurface, resource, 4);
    else if (rightState == 1)
        d2_DrawSpriteFromSet(g_1040494 - 0x96, d2_DialogCenterY, d2_ScreenSurface, resource, 5);
    if (topState == 2)
        d2_DrawSpriteFromSet(d2_CenterX - 0x10, 0x38, d2_ScreenSurface, resource, 6);
    else if (topState == 1)
        d2_DrawSpriteFromSet(d2_CenterX - 0x10, 0x38, d2_ScreenSurface, resource, 7);
}
