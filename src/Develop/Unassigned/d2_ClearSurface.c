#include <string.h>

typedef struct LockedRect {
	int pitch;
	unsigned char* bits;
} LockedRect;
// SIZE 8

typedef struct D3DTexVt {
	void* pad[16];
	int(__stdcall* LockRect)(void* self, int level, LockedRect* lr, void* rect, int flags);
} D3DTexVt;
// SIZE 0x44

typedef struct D3DTex {
	D3DTexVt* vt;
} D3DTex;
// SIZE 4

typedef struct D3DSurfVt {
	void* pad[9];
	int(__stdcall* LockRect)(void* self, LockedRect* lr, void* rect, int flags);
} D3DSurfVt;
// SIZE 0x28

typedef struct D3DSurf {
	D3DSurfVt* vt;
} D3DSurf;
// SIZE 4

typedef struct Tex {
	int pad0[2];
	int width;
	int pitch;
	int pw;
	unsigned char bpp;
	char pad15[7];
	unsigned char* bits;
	D3DTex* tex;
	D3DSurf* surf;
	char pad28[0x3c - 0x28];
	int locked;
	char pad40[0x50 - 0x40];
	int valid;
	int height;
} Tex;
// SIZE 0x58

int __cdecl d2_LockSurface(void* surface);
int __cdecl d3_UnlockSurfaceHandle(void* surface);
void __cdecl d2_UnlockSurface(Tex* tex);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004796b0 */
int __cdecl d2_ClearSurface(char* surface)
{
	unsigned int effects[25];
	int saved;
	void* object;
	if (surface == 0) {
		return 0;
	}
	saved = *(int*) (surface + 0x34);
	if (*(int*) (surface + 0x20) == 0) {
		if (saved != 0) {
			d2_LockSurface(surface);
		}
		memset(*(void**) (surface + 0x1c), 0,
			*(unsigned int*) (surface + 0xc) * *(unsigned int*) (surface + 8));
	} else {
		if (saved != 0) {
			d3_UnlockSurfaceHandle(surface);
		}
		memset(effects, 0, sizeof(effects));
		effects[20] = 0;
		effects[0] = 0x64;
		object = *(void**) (surface + 0x20);
		(*(int (__stdcall**) (void*, int, int, int, int, void*))
			(*(char**) object + 0x14))(object, 0, 0, 0, 0x1000400, effects);
	}
	if (saved != 0) {
		d2_LockSurface(surface);
	} else {
		d3_UnlockSurfaceHandle(surface);
	}
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x00476970 */
int __cdecl d2_ClearSurface(Tex* tex)
{
	int was_locked;

	if (!tex) {
		return 0;
	}
	was_locked = tex->locked;
	if (!was_locked) {
		d2_LockSurface(tex);
	}
	if (tex->bits) {
		if (tex->bpp == 0x10) {
			memset(tex->bits, 0, tex->height * tex->width * 2);
		} else if (tex->bpp == 0x18) {
			memset(tex->bits, 0, tex->height * tex->width * 3);
		} else if (tex->bpp == 0x20) {
			memset(tex->bits, 0, tex->height * tex->width * 4);
		}
		if (was_locked) {
			d2_LockSurface(tex);
		} else {
			d2_UnlockSurface(tex);
		}
	}
	return 1;
}
#endif
