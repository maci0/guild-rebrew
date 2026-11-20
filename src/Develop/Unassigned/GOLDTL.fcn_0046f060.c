#include "client_data.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_ResizeWindow(int w, int h, int win);

/* ADDRESS: GOLDTL 0x0046f060 */
void __cdecl fcn_0046f060(int win)
{
	D2_WIN* p;
	char* e;
	int v;
	int n;
	int y;
	

	p = &((D2_WIN*)g_1015f40)[win];
	if (p->active == 0) {
		return;
	}
	if (*(unsigned char*) &p->pad14[0] & 0x10) {
		v = *(int*) &p->pad3c[0x218];
	} else {
		v = win;
	}
	n = p->count;
	if (n > 0) {
		e = (char*) g_1015ea0 + 0x14;
		y = p->top;
		do {
			if (*(int*) (e + 8) + *(int*) e > y + v) {
				v = (*(int*) (e + 8) - y) + *(int*) e + 8;
			}
			e += 0x2f4;
			n--;
		} while (n != 0);
	}
	d2_ResizeWindow(*(short*) &p->width, (short) v, win);
}
