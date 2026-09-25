// FUNCTION: GOLDTL 0x476660
// SIZE: 396

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
// SIZE 4

typedef struct Target {
	char pad0[0x20];
	Com* com;
	int handle;
	char pad28[0x34 - 0x28];
	int w;
	int h;
	int locked;
	char pad40[4];
	int x44;
} Target;
// SIZE 0x48

typedef struct Desc {
	char pad0[0x20];
	char* src;
	char pad24[0x40 - 0x24];
	int one;
	char pad44[0x5c - 0x44];
} Desc;
// SIZE 0x5c

char* __cdecl fcn_004770a0(Desc* d, int kind);
int __cdecl fcn_00476120(int x, int y, int w, int h, void* a, int sx, int sy, void* b);
void __cdecl fcn_00475f80(char* img);
void __cdecl fcn_00475fd0(Target* t);
void __cdecl fcn_00476060(Target* t);

int __cdecl fcn_00476660(int x, int y, int w, int h, Target* t, int sx, int sy, char* src)
{
	Desc d;
	int handle;
	int locked;
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
	if (y + h > t->h) {
		h = t->h - y;
	}
	if (x + w > t->w) {
		w = t->w - x;
	}
	if (h == 0 || w == 0) {
		return 0;
	}
	locked = t->locked;
	if (t->com != 0 && t->x44 == 0) {
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
		img = fcn_004770a0(&d, 4);
		if (fcn_00476120(x, y, w, h, t, sx, sy, img) == 0) {
			return 0;
		}
		fcn_00475f80(img);
	}
	if (locked != 0) {
		fcn_00475fd0(t);
	} else {
		fcn_00476060(t);
	}
	return 1;
}
