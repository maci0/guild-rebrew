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

int __cdecl fcn_00475fd0(Tex* t);
void __cdecl fcn_00476060(Tex* t);

// FUNCTION: GOLDTL 0x476970
// SIZE: 141
int __cdecl fcn_00476970(Tex* t)
{
	int was;

	if (!t) {
		return 0;
	}
	was = t->locked;
	if (!was) {
		fcn_00475fd0(t);
	}
	if (t->bits) {
		if (t->bpp == 0x10) {
			memset(t->bits, 0, t->height * t->width * 2);
		} else if (t->bpp == 0x18) {
			memset(t->bits, 0, t->height * t->width * 3);
		} else if (t->bpp == 0x20) {
			memset(t->bits, 0, t->height * t->width * 4);
		}
		if (was) {
			fcn_00475fd0(t);
		} else {
			fcn_00476060(t);
		}
	}
	return 1;
}
