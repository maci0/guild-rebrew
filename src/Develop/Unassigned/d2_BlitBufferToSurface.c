

#include <string.h>

typedef struct Com Com;
typedef struct ComVtbl {
	char pad0[0x3c];
	int(__stdcall* m3c)(Com* self, int a, int* out);
} ComVtbl;
// SIZE 0x40

struct Com {
	ComVtbl* v;
};
// SIZE 0x4

typedef struct Target {
	char pad0[0x20];
	Com* com;
	int handle;
} Target;
// SIZE 0x28

typedef struct Desc {
	char pad0[0x20];
	char* src;
	char pad24[0x40 - 0x24];
	int one;
	char pad44[0x5c - 0x44];
} Desc;
// SIZE 0x5c

char* __cdecl d2_CreateSurface(Desc* d, int kind);
int __cdecl d2_BlitSurfaceCore(int x, int y, int w, int h, char* img, int sx, int sy, Target* t);
void __cdecl d2_ReleaseSurface(char* img);

int __cdecl d2_BlitBufferToSurface(int x, int y, int w, int h, char* src, int sx, int sy, Target* t)
{
	Desc d;
	int handle;
	char* img;

	if (y < 0) {
		h += y;
		y = 0;
	}
	if (x < 0) {
		w += x;
		x = 0;
	}
	if (sx < 0) {
		x -= sx;
		w += sx;
		sx = 0;
	}
	if (sy < 0) {
		y -= sy;
		h += sy;
		sy = 0;
	}
	if (h == 0 || w == 0 || src == 0 || t == 0 || t->com == 0) {
		return 0;
	}
	if (t->handle == 0) {
		if (t->com->v->m3c(t->com, 0, &handle) != 0) {
			return 0;
		}
		t->handle = handle;
	} else {
		handle = t->handle;
	}
	memset(&d, 0, sizeof(d));
	d.one = 1;
	d.src = src;
	img = d2_CreateSurface(&d, 4);
	if (handle == 0 || img == 0) {
		return 0;
	}
	if (d2_BlitSurfaceCore(x, y, w, h, img, sx, sy, t) == 0) {
		return 0;
	}
	d2_ReleaseSurface(img);
	return 1;
}
