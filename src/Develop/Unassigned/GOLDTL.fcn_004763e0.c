#include <string.h>

typedef struct BlitSurf BlitSurf;
typedef struct BlitSurf {
	char pad0[0xc];
	int pitch;              /* 0xc */
	int f10;                /* 0x10 */
	unsigned char bpp;      /* 0x14 */
	char pad15[3];
	int f18;                /* 0x18 */
	char* bits;             /* 0x1c */
	void* a;                /* 0x20 */
	void* b;                /* 0x24 */
	char pad28[4];
	int left;               /* 0x2c */
	int top;                /* 0x30 */
	int right;              /* 0x34 */
	int bottom;             /* 0x38 */
	int locked;             /* 0x3c */
	char pad40[4];
	int flag;               /* 0x44 */
} BlitSurf;
// SIZE 0x48

int __cdecl fcn_00475fd0(BlitSurf* s);
int __cdecl fcn_00476060(BlitSurf* s);
int __cdecl fcn_00476120(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst);

/* ADDRESS: GOLDTL 0x004763e0 */
int __cdecl fcn_004763e0(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst, int unused)
{
	int srcLocked;
	int dstLocked;
	int sbase;
	int dbase;

	if (sy < dst->top) {
		y += dst->top - sy;
		h -= dst->top - sy;
		sy = dst->top;
	}
	if (sx < dst->left) {
		x += dst->left - sx;
		w -= dst->left - sx;
		sx = dst->left;
	}
	if (y < src->top) {
		h -= src->top - y;
		y = src->top;
	}
	if (x < src->left) {
		w -= src->left - x;
		x = src->left;
	}
	if (sy + h > dst->bottom)
		h = dst->bottom - sy;
	if (y + h > src->bottom)
		h = src->bottom - y;
	if (sx + w > dst->right)
		w = dst->right - sx;
	if (x + w > src->right)
		w = src->right - x;
	if (h <= 0 || w <= 0)
		return 0;
	dstLocked = dst->locked;
	srcLocked = src->locked;
	if (((dst->a != 0 && src->a != 0) || (dst->b != 0 && src->b != 0)) && dst->flag == 0 && src->flag == 0) {
		if (fcn_00476120(x, y, w, h, src, sx, sy, dst) == 0)
			return 0;
	} else if (fcn_00475fd0(dst) != 0 && fcn_00475fd0(src) != 0) {
		sbase = src->pitch * y + (src->bpp >> 3) * x;
		dbase = dst->pitch * sy + (dst->bpp >> 3) * sx;
		for (y = 0; y < h; y++) {
			memcpy(dst->bits + dst->pitch * y + dbase,
			       src->pitch * y + sbase + src->bits,
			       (src->bpp >> 3) * w);
		}
	}
	if (dstLocked)
		fcn_00475fd0(dst);
	else
		fcn_00476060(dst);
	if (srcLocked)
		fcn_00475fd0(src);
	else
		fcn_00476060(src);
	return 1;
}
