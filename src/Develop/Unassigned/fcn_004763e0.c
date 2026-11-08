#include <string.h>

int __cdecl fcn_0047b8b0(int a1, int a2, int a3, int a4, void* out);
void __cdecl fcn_004372d0(int a1, int a2, int a3, int a4, int a5);

typedef struct BlitSurf BlitSurf;
typedef struct BlitSurf {
	char pad0[0xc];
	int pitch;              
	int f10;                
	unsigned char bpp;      
	char pad15[3];
	int f18;                
	char* bits;             
	void* a;                
	void* b;                
	char pad28[4];
	int left;               
	int top;                
	int right;              
	int bottom;             
	int locked;             
	char pad40[4];
	int flag;               
} BlitSurf;

int __cdecl fcn_00475fd0(BlitSurf* s);
int __cdecl fcn_00476060(BlitSurf* s);
int __cdecl fcn_00476120(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst);
int __cdecl fcn_004763e0(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst, int unused);

int __cdecl fcn_00476120(int left, int top, int width, int height, char* src, char* dest, int mode);
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
