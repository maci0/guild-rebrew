/* Draws the four direction arrows of the camera pad: each mode is 1 or 2
 * depending on whether the camera vector already sits at its limit. */

extern int d3_CameraHorizontalIndex;
extern int d3_CameraVerticalStep;
extern char* d3_ActiveCamera;
extern float g_662d70[4];
extern int g_77250c;
extern int d2_ScreenHeight;
extern int g_1040494;
extern float d2_UiScale;
extern float g_66293c;
extern float g_66291c;

int __cdecl d2_GetResourceData(int size);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d2_SetClipRect(int, int, int, int);
int __cdecl d2_DrawSpriteFromSet(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004d03e0 */
void __cdecl fcn_004d03e0(void)
{
    int res;
    int left;
    int right;
    int up;
    int down;

    right = 0;
    left = 0;
    up = 0;
    down = 0;
    res = d2_GetResourceData(0x52c);
    if (d3_CameraHorizontalIndex == -1) {
        right = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xfc), g_662d70, 0.2f) == 0)
            right = 2;
    } else if (d3_CameraHorizontalIndex == 1) {
        left = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xe4), g_662d70, 0.2f) == 0)
            left = 2;
    } else if (d3_CameraHorizontalIndex == 0) {
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xe4), g_662d70, 0.2f) == 0)
            left = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xfc), g_662d70, 0.2f) == 0)
            right = 1;
    }
    if (d3_CameraVerticalStep == -1) {
        up = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xb4), g_662d70, 0.2f) == 0)
            up = 2;
    } else if (d3_CameraVerticalStep == 1) {
        down = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xcc), g_662d70, 0.2f) == 0)
            down = 2;
    } else if (d3_CameraVerticalStep == 0) {
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xb4), g_662d70, 0.2f) == 0)
            up = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xcc), g_662d70, 0.2f) == 0)
            down = 1;
    }
    d2_SetClipRect(0, 0, *(int*) (g_77250c + 4), *(int*) (g_77250c + 8));
    if (up == 2)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * *(float*) 0x664ef0 - g_66293c),
                     g_77250c, res, 0);
    else if (up == 1)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * *(float*) 0x664ef0 - g_66293c),
                     g_77250c, res, 1);
    if (left == 2)
        d2_DrawSpriteFromSet(8, d2_ScreenHeight / 2 + 0x14, g_77250c, res, 2);
    else if (left == 1)
        d2_DrawSpriteFromSet(8, d2_ScreenHeight / 2 + 0x14, g_77250c, res, 3);
    if (right == 2)
        d2_DrawSpriteFromSet(g_1040494 - 0x28, d2_ScreenHeight / 2 + 0x14, g_77250c, res, 4);
    else if (right == 1)
        d2_DrawSpriteFromSet(g_1040494 - 0x28, d2_ScreenHeight / 2 + 0x14, g_77250c, res, 5);
    if (down == 2)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * g_66291c), g_77250c, res, 6);
    else if (down == 1)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * g_66291c), g_77250c, res, 7);
}
