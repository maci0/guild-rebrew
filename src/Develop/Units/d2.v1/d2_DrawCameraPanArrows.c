/* Draws the four direction arrows of the camera pad: each mode is 1 or 2
 * depending on whether the camera vector already sits at its limit. */

extern int d3_CameraHorizontalIndex;
extern int d3_CameraVerticalStep;
extern char* d3_ActiveCamera;
extern float d3_ZeroVec4[4];
extern int d2_ScreenSurface;
extern int d2_ScreenHeight;
extern int g_1040494;
extern float d2_UiScale;
extern float g_66293c;
extern float g_66291c;

void* __cdecl d2_GetResourceData(int size);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d2_SetClipRect(int, int, int, int);
int __cdecl d2_DrawShapeFrame(int, int, int, void*, int);
int __cdecl d2_DrawSpriteFromSet(int, int, int, int, int);

#if defined(REBREW_GOLD)
#define CAM(off)	((float*) (*(char**) 0xfc2dec + (off)))
#define SAME(off)	CompareVector3WithinTolerance(CAM(off), (float*) 0x5ebba4, 0.2f)
#define HALF_W		(*(short*) 0xfb9070 / 2)
#define HALF_H		(*(short*) 0xfb9072 / 2)

/* ADDRESS: GOLD 0x004cf370 */
void __cdecl d2_DrawCameraPanArrows(void)
{
	void* rec;
	int a;
	int b;
	int c;
	int d;
	int mode;

	a = 0;
	b = 0;
	c = 0;
	d = 0;
	rec = d2_GetResourceData(0x52c);
	mode = *(int*) 0x6f22cc;
	if (mode == -1) {
		a = 1;
		if (!SAME(0xfc)) {
			a = 2;
		}
	} else if (mode == 1) {
		b = 1;
		if (!SAME(0xe4)) {
			b = 2;
		}
	} else if (mode == 0) {
		if (!SAME(0xe4)) {
			b = 1;
		}
		if (!SAME(0xfc)) {
			a = 1;
		}
	}
	mode = *(int*) 0x6f22d0;
	if (mode == -1) {
		c = 1;
		if (!SAME(0xb4)) {
			c = 2;
		}
	} else if (mode == 1) {
		d = 1;
		if (!SAME(0xcc)) {
			d = 2;
		}
	} else if (mode == 0) {
		if (!SAME(0xb4)) {
			c = 1;
		}
		if (!SAME(0xcc)) {
			d = 1;
		}
	}
	d2_SetClipRect(0, 0, ((int*) *(int*) 0x6ed924)[1], ((int*) *(int*) 0x6ed924)[2]);
	if (c == 2) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5edc50 - *(float*) 0x5eb81c),
			     *(int*) 0x6ed924, rec, 0);
	} else if (c == 1) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5edc50 - *(float*) 0x5eb81c),
			     *(int*) 0x6ed924, rec, c);
	}
	if (b == 2) {
		d2_DrawShapeFrame(8, HALF_W + 0x14, *(int*) 0x6ed924, rec, b);
	} else if (b == 1) {
		d2_DrawShapeFrame(8, HALF_W + 0x14, *(int*) 0x6ed924, rec, 3);
	}
	if (a == 2) {
		d2_DrawShapeFrame(*(short*) 0xfb9072 - 0x28, HALF_W + 0x14, *(int*) 0x6ed924, rec, 4);
	} else if (a == 1) {
		d2_DrawShapeFrame(*(short*) 0xfb9072 - 0x28, HALF_W + 0x14, *(int*) 0x6ed924, rec, 5);
	}
	if (d == 2) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5eb7fc), *(int*) 0x6ed924, rec, 6);
	} else if (d == 1) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5eb7fc), *(int*) 0x6ed924, rec, 7);
	}
}
#else
/* ADDRESS: GOLDTL 0x004d03e0 */
void __cdecl d2_DrawCameraPanArrows(void)
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
    res = (int) d2_GetResourceData(0x52c);
    if (d3_CameraHorizontalIndex == -1) {
        right = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xfc), d3_ZeroVec4, 0.2f) == 0)
            right = 2;
    } else if (d3_CameraHorizontalIndex == 1) {
        left = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xe4), d3_ZeroVec4, 0.2f) == 0)
            left = 2;
    } else if (d3_CameraHorizontalIndex == 0) {
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xe4), d3_ZeroVec4, 0.2f) == 0)
            left = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xfc), d3_ZeroVec4, 0.2f) == 0)
            right = 1;
    }
    if (d3_CameraVerticalStep == -1) {
        up = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xb4), d3_ZeroVec4, 0.2f) == 0)
            up = 2;
    } else if (d3_CameraVerticalStep == 1) {
        down = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xcc), d3_ZeroVec4, 0.2f) == 0)
            down = 2;
    } else if (d3_CameraVerticalStep == 0) {
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xb4), d3_ZeroVec4, 0.2f) == 0)
            up = 1;
        if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xcc), d3_ZeroVec4, 0.2f) == 0)
            down = 1;
    }
    d2_SetClipRect(0, 0, *(int*) (d2_ScreenSurface + 4), *(int*) (d2_ScreenSurface + 8));
    if (up == 2)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * *(float*) 0x664ef0 - g_66293c),
                     d2_ScreenSurface, res, 0);
    else if (up == 1)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * *(float*) 0x664ef0 - g_66293c),
                     d2_ScreenSurface, res, 1);
    if (left == 2)
        d2_DrawSpriteFromSet(8, d2_ScreenHeight / 2 + 0x14, d2_ScreenSurface, res, 2);
    else if (left == 1)
        d2_DrawSpriteFromSet(8, d2_ScreenHeight / 2 + 0x14, d2_ScreenSurface, res, 3);
    if (right == 2)
        d2_DrawSpriteFromSet(g_1040494 - 0x28, d2_ScreenHeight / 2 + 0x14, d2_ScreenSurface, res, 4);
    else if (right == 1)
        d2_DrawSpriteFromSet(g_1040494 - 0x28, d2_ScreenHeight / 2 + 0x14, d2_ScreenSurface, res, 5);
    if (down == 2)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * g_66291c), d2_ScreenSurface, res, 6);
    else if (down == 1)
        d2_DrawSpriteFromSet(g_1040494 / 2 - 0x14, (int) (d2_UiScale * g_66291c), d2_ScreenSurface, res, 7);
}
#endif
