#include <stdarg.h>
#include <string.h>
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl fcn_0046b520(char* s, int font);
int __cdecl fcn_00468df0(int a1, int a2, int a3, int a4, int i);
void __cdecl fcn_00469110(int a1, int a2);

/* ADDRESS: GOLDTL 0x00533bb0 */
void __cdecl fcn_00533bb0(int a0, int a1, int* a2, int a3, ...)
{
	int maxw;
	D2_WIN* winp;
	char buf[0x800];
	va_list ap;
	char* src;
	char* slot;
	int i;
	int w;
	int q;
	int step;
	int start;
	int span;

	winp = &((D2_WIN*) g_1015f40)[a0];
	maxw = 0;
	if (a3 > 0) {
		int remaining; va_start(ap, a3);
		slot = buf;
		for (remaining = a3; remaining != 0; remaining--) {
			src = va_arg(ap, char*);
			strcpy(slot, src);
			w = fcn_0046b520(src, 0x54) + 0x20;
			if (w > maxw) {
				maxw = w;
			}
			slot += 0x40;
		}
	}
	q = winp->width / (a3 + 1);
	if (maxw > q) {
		step = maxw + 8;
		span = step * a3;
		if (span > winp->width) {
			span -= winp->width;
		} else {
			span = winp->width - span;
		}
		start = span / 2 + step / 2;
	} else {
		step = q;
		start = q;
	}

	slot = buf;
	for (i = 0; i < a3; i++, slot += 0x40, start += step) {
		w = fcn_00468df0(start - maxw / 2, a1, 0xc5, slot, a0);
		a2[i] = w;
		*(int*) (g_1015ea0 + w * 0x2f4 + 0x84) = 0x54;
		fcn_00469110(w, maxw);


	}
}
