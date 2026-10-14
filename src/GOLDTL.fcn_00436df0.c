struct dev_436df0;

// SIZE 0xa4
struct devvtbl_436df0 {
	char pad0[0x94];
	long (__stdcall* SetTransform)(struct dev_436df0*, int, const float*);
	char pad98[0xa0 - 0x98];
	long (__stdcall* SetViewport)(struct dev_436df0*, const void*);
};

// SIZE 0x4
struct dev_436df0 {
	struct devvtbl_436df0* vtbl;
};

// SIZE 0x18
struct viewport_436df0 {
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
	float min_z;
	float max_z;
};

extern void* g_6b5de0;
extern char g_1052be0[];
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

/* ADDRESS: GOLDTL 0x00436df0 */

/* Sets the viewport and the perspective projection, skipping whichever of
 * the two did not change since the last call. */
void __cdecl fcn_00436df0(float fov, float aspect, float width, float height, float x, float y, float znear, float zfar)
{
	struct dev_436df0* dev;

	dev = ((struct dev_436df0*)g_6b5de0);
	if (dev == 0) {
		return;
	}
	if (width != g_67a28c || height != g_67a290 || x != g_67a294 || y != g_67a298) {
		((struct viewport_436df0*) g_1052be0)->width = (unsigned long) width;
		((struct viewport_436df0*) g_1052be0)->height = (unsigned long) height;
		((struct viewport_436df0*) g_1052be0)->min_z = 0.0f;
		((struct viewport_436df0*) g_1052be0)->max_z = 1.0f;
		((struct viewport_436df0*) g_1052be0)->x = (unsigned long) x;
		((struct viewport_436df0*) g_1052be0)->y = (unsigned long) y;
		dev->vtbl->SetViewport(dev, g_1052be0);
		g_67a28c = width;
		g_67a290 = height;
		g_67a294 = x;
		g_67a298 = y;
	}
	if (fov != g_67a2a4 || aspect != g_67a2a8 || znear != g_67a29c || zfar != g_67a2a0) {
		fcn_005ecf13(g_1052c00, fov, aspect, znear, zfar);
		((struct dev_436df0*)g_6b5de0)->vtbl->SetTransform(((struct dev_436df0*)g_6b5de0), 3, g_1052c00);
		g_67a29c = znear;
		g_67a2a0 = zfar;
		g_67a2a8 = aspect;
		g_67a2a4 = fov;
	}
}
