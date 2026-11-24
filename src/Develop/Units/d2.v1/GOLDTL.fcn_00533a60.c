#include <stdarg.h>
#include <string.h>
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl fcn_0046b520(char* s, int font);
int __cdecl fcn_00468df0(int a1, int a2, int a3, int a4, int i);
void __cdecl fcn_00469110(int a1, int a2);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00533a60 */
void __cdecl fcn_00533a60(int windowId, int a1, int* a2, int labelCount, ...)
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

	winp = &((D2_WIN*) g_1015f40)[windowId];
	maxw = 0;
	if (labelCount > 0) {
		int remaining; va_start(ap, labelCount);
		slot = buf;
		for (remaining = labelCount; remaining != 0; remaining--) {
			src = va_arg(ap, char*);
			strcpy(slot, src);
			w = fcn_0046b520(src, *(int*) ((char*) winp + 0x28c)) + 0x20;
			if (w > maxw) {
				maxw = w;
			}
			slot += 0x40;
		}
	}

	q = winp->width / (labelCount + 1);
	if (maxw > q) {
		step = maxw + 8;
		span = step * labelCount;
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
	for (i = 0; i < labelCount; i++, slot += 0x40, start += step) {
		w = fcn_00468df0(start - maxw / 2, a1, 0xbf, slot, windowId);
		a2[i] = w;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[w].font)) = 0x53;
		fcn_00469110(w, maxw);
	}
}
