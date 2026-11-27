
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
