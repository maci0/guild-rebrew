#include <stdarg.h>
#include <string.h>
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl d2_MeasureTextWidth(char* s, int font);
int __cdecl d2_AddWindowTextButton(int a1, int a2, int a3, int a4, int i);
void __cdecl d2_SetElementWidth(int a1, int a2);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00533bb0 */
void __cdecl d2_LayoutCenteredButtonRow(int windowId, int a1, int* a2, int labelCount, ...)
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
			w = d2_MeasureTextWidth(src, 0x54) + 0x20;
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
		w = d2_AddWindowTextButton(start - maxw / 2, a1, 0xc5, slot, windowId);
		a2[i] = w;
		((D2_CONTROL_TL*) (g_1015ea0))[w].font = 0x54;
		d2_SetElementWidth(w, maxw);


	}
}
