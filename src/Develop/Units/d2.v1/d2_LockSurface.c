#include <string.h>

#include "Develop/Units/d3/d3_d3d.h"

typedef struct SURFACE_VTABLE479010 {
	void *slots[25];
	int (__stdcall *Lock)(void *self, void *rect, void *desc, unsigned long flags, void *event);
} SURFACE_VTABLE479010;

typedef struct SURFACE479010 {
	SURFACE_VTABLE479010 *lpVtbl;
} SURFACE479010;

typedef struct SURFACE_DESC479010 {
	unsigned long dwSize;
	unsigned long dwFlags;
	unsigned long dwHeight;
	unsigned long dwWidth;
	long lPitch;
	unsigned long pad14[4];
	void *lpSurface;
	unsigned long pad28[21];
} SURFACE_DESC479010;

// The len/count stores written once per arm; msvc6 merges the tails from
// the data store onward.

typedef struct D2_LOCKED_RECT {
	int len;
	int data;
} D2_LOCKED_RECT;

typedef struct D2_TEXTURE_IFACE D2_TEXTURE_IFACE;
typedef struct D2_TEXTURE_VTBL {
	void* pad[0x10];
	int(__stdcall* Get)(D2_TEXTURE_IFACE* self, int a, D2_LOCKED_RECT* out, int b, int c);
} D2_TEXTURE_VTBL;
struct D2_TEXTURE_IFACE {
	D2_TEXTURE_VTBL* vtbl;
};

typedef struct D2_SURFACE_IFACE D2_SURFACE_IFACE;
typedef struct D2_SURFACE_VTBL {
	void* pad[9];
	int(__stdcall* Get)(D2_SURFACE_IFACE* self, D2_LOCKED_RECT* out, int a, int b);
} D2_SURFACE_VTBL;
struct D2_SURFACE_IFACE {
	D2_SURFACE_VTBL* vtbl;
};

typedef struct D2_LOCK_SURFACE {
	char pad0[0xc];
	int len;
	int count;
	unsigned char bits;
	char pad15[7];
	int data;
	D2_TEXTURE_IFACE* a;
	D2_SURFACE_IFACE* b;
	char pad28[0x3c - 0x28];
	int ready;
	char pad40[0x50 - 0x40];
	int open;
} D2_LOCK_SURFACE;
// SIZE 0x54

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00479010 */
int __cdecl d2_LockSurface(char *s)
{
	SURFACE_DESC479010 ddsd;
	SURFACE479010 *surf;
	int mode;

	if (s == 0) {
		return 0;
	}
	if (*(int *) (s + 0x34) == 0) {
		surf = *(SURFACE479010 **) (s + 0x20);
		if (surf != 0) {
			memset(&ddsd, 0, sizeof(ddsd));
			mode = *(int *) 0x14635ac;
			ddsd.dwSize = 0x7c;
			if (mode == 3) {
				d3d_LastResult = surf->lpVtbl->Lock(surf, 0, &ddsd, 1, 0);
				if (d3d_LastResult != 0) {
					d3d_LogResultError("D:\\develop\\Units\\d2.v1\\GFX.C", 0x49a,
						"s->DDSurface->lpVtbl->Lock( s->DDSurface, NULL, &ddsd, DDLOCK_WAIT, NULL )");
				}
			} else {
				d3d_LastResult = surf->lpVtbl->Lock(surf, 0, &ddsd, 0x801, 0);
				if (d3d_LastResult != 0) {
					d3d_LogResultError("D:\\develop\\Units\\d2.v1\\GFX.C", 0x49c,
						"s->DDSurface->lpVtbl->Lock( s->DDSurface, NULL, &ddsd, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL )");
				}
			}
			*(void **) (s + 0x1c) = ddsd.lpSurface;
		}
		*(int *) (s + 0x34) = 1;
	}
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x00475fd0 */
int __cdecl d2_LockSurface(D2_LOCK_SURFACE* surface)
{
	D2_LOCKED_RECT lockedRect;

	if (surface == 0 || surface->open == 0) {
		return 0;
	}
	if (surface->ready != 0) {
		return 1;
	}
	if (surface->a != 0) {
		surface->a->vtbl->Get(surface->a, 0, &lockedRect, 0, 0);
		surface->data = lockedRect.data;
		surface->len = lockedRect.len;
		surface->count = lockedRect.len / (surface->bits >> 3);
	} else if (surface->b != 0) {
		if (surface->b->vtbl->Get(surface->b, &lockedRect, 0, 0) < 0) {
			return 0;
		}
		surface->data = lockedRect.data;
		surface->len = lockedRect.len;
		surface->count = lockedRect.len / (surface->bits >> 3);
	}
	surface->ready = 1;
	return 1;
}
#endif
