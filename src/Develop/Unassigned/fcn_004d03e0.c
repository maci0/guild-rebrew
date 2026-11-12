/* Draws the four direction arrows of the camera pad: each mode is 1 or 2
 * depending on whether the camera vector already sits at its limit. */

extern int g_774688;
extern int g_77468c;
extern char* g_6b8014;
extern float g_662d70[4];
extern int g_77250c;
extern int g_1040490;
extern int g_1040494;
extern float g_67d368;
extern float g_66293c;
extern float g_66291c;

int __cdecl d2_GetResourceData(int size);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl fcn_0047a040(int, int, int, int);
int __cdecl fcn_0047cba0(int, int, int, int, int);

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
    if (g_774688 == -1) {
        right = 1;
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xfc), g_662d70, 0.2f) == 0)
            right = 2;
    } else if (g_774688 == 1) {
        left = 1;
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xe4), g_662d70, 0.2f) == 0)
            left = 2;
    } else if (g_774688 == 0) {
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xe4), g_662d70, 0.2f) == 0)
            left = 1;
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xfc), g_662d70, 0.2f) == 0)
            right = 1;
    }
    if (g_77468c == -1) {
        up = 1;
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xb4), g_662d70, 0.2f) == 0)
            up = 2;
    } else if (g_77468c == 1) {
        down = 1;
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xcc), g_662d70, 0.2f) == 0)
            down = 2;
    } else if (g_77468c == 0) {
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xb4), g_662d70, 0.2f) == 0)
            up = 1;
        if (CompareVector3WithinTolerance((float*) (g_6b8014 + 0xcc), g_662d70, 0.2f) == 0)
            down = 1;
    }
    fcn_0047a040(0, 0, *(int*) (g_77250c + 4), *(int*) (g_77250c + 8));
    if (up == 2)
        fcn_0047cba0(g_1040494 / 2 - 0x14, (int) (g_67d368 * *(float*) 0x664ef0 - g_66293c),
                     g_77250c, res, 0);
    else if (up == 1)
        fcn_0047cba0(g_1040494 / 2 - 0x14, (int) (g_67d368 * *(float*) 0x664ef0 - g_66293c),
                     g_77250c, res, 1);
    if (left == 2)
        fcn_0047cba0(8, g_1040490 / 2 + 0x14, g_77250c, res, 2);
    else if (left == 1)
        fcn_0047cba0(8, g_1040490 / 2 + 0x14, g_77250c, res, 3);
    if (right == 2)
        fcn_0047cba0(g_1040494 - 0x28, g_1040490 / 2 + 0x14, g_77250c, res, 4);
    else if (right == 1)
        fcn_0047cba0(g_1040494 - 0x28, g_1040490 / 2 + 0x14, g_77250c, res, 5);
    if (down == 2)
        fcn_0047cba0(g_1040494 / 2 - 0x14, (int) (g_67d368 * g_66291c), g_77250c, res, 6);
    else if (down == 1)
        fcn_0047cba0(g_1040494 / 2 - 0x14, (int) (g_67d368 * g_66291c), g_77250c, res, 7);
}
