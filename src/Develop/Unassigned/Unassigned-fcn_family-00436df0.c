struct D3D_DEV_CTX;

struct D3D_DEV_CTX_VTBL {
	char pad0[0x94];
	long (__stdcall* SetTransform)(struct D3D_DEV_CTX*, int, const float*);
	char pad98[0xa0 - 0x98];
	long (__stdcall* SetViewport)(struct D3D_DEV_CTX*, const void*);
};

struct D3D_DEV_CTX {
	struct D3D_DEV_CTX_VTBL* vtbl;
};

struct D3D_VIEWPORT8 {
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
	float min_z;
	float max_z;
};

extern void* g_6b5de0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_1052c00[16];
extern float g_67a28c;
extern float g_67a290;
extern float g_67a294;
extern float g_67a298;
extern float g_67a29c;
extern float g_67a2a0;
extern float g_67a2a4;
extern float g_67a2a8;

float* __stdcall fcn_005ecf13(float*, float, float, float, float);
typedef int(__stdcall* Fn3)(void* self, int a, int b);

extern int g_14ce764;
extern unsigned char g_6b7ff9;

/* Sets the viewport and the perspective projection, skipping whichever of
 * the two did not change since the last call. */
/* ADDRESS: GOLDTL 0x00436df0 */
void __cdecl d3_SetViewportAndProjection(float fov, float aspect, float width, float height, float x, float y, float znear, float zfar)
{
	struct D3D_DEV_CTX* dev;

	dev = ((struct D3D_DEV_CTX*)g_6b5de0);
	if (dev == 0) {
		return;
	}
	if (width != g_67a28c || height != g_67a290 || x != g_67a294 || y != g_67a298) {
		((struct D3D_VIEWPORT8*) g_1052be0)->width = (unsigned long) width;
		((struct D3D_VIEWPORT8*) g_1052be0)->height = (unsigned long) height;
		((struct D3D_VIEWPORT8*) g_1052be0)->min_z = 0.0f;
		((struct D3D_VIEWPORT8*) g_1052be0)->max_z = 1.0f;
		((struct D3D_VIEWPORT8*) g_1052be0)->x = (unsigned long) x;
		((struct D3D_VIEWPORT8*) g_1052be0)->y = (unsigned long) y;
		dev->vtbl->SetViewport(dev, g_1052be0);
		g_67a28c = width;
		g_67a290 = height;
		g_67a294 = x;
		g_67a298 = y;
	}
	if (fov != g_67a2a4 || aspect != g_67a2a8 || znear != g_67a29c || zfar != g_67a2a0) {
		fcn_005ecf13(g_1052c00, fov, aspect, znear, zfar);
		((struct D3D_DEV_CTX*)g_6b5de0)->vtbl->SetTransform(((struct D3D_DEV_CTX*)g_6b5de0), 3, g_1052c00);
		g_67a29c = znear;
		g_67a2a0 = zfar;
		g_67a2a8 = aspect;
		g_67a2a4 = fov;
	}
}

/* ADDRESS: GOLDTL 0x00436f70 */
void __cdecl d3_SetFogEnabled(char on)
{
	if (((void**)g_6b5de0) != 0 && (g_14ce764 & 0x40000) != 0 && on != (*(char *)&g_6b7ff9)) {
		((Fn3) ((void**) *((void**)g_6b5de0))[0xc8 / 4])(((void**)g_6b5de0), 7, (on != 0) + 1);
		(*(char *)&g_6b7ff9) = on;
	}
}
