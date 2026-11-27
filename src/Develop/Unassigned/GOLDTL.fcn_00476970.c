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

int __cdecl d2_LockSurface(Tex* tex);
void __cdecl d2_UnlockSurface(Tex* tex);

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
