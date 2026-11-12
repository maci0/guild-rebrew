#include "client_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_0046eda0(int w, int h, int win);

/* ADDRESS: GOLDTL 0x0046f060 */
void __cdecl fcn_0046f060(int win)
{
	char* p;
	char* e;
	int v;
	int n;
	int y;
	

	p = (char*)&g_1015f40[win];
	if (*(int*) (p + 0x290) == 0) {
		return;
	}
	if (*(unsigned char*) (p + 0x14) & 0x10) {
		v = *(int*) (p + 0x254);
	} else {
		v = win;
	}
	n = *(int*) (p + 0x2c);
	if (n > 0) {
		e = g_1015ea0 + 0x14;
		y = *(int*) (p + 8);
		do {
			if (y + v < *(int*) (e + 8) + *(int*) e) {
				v = (*(int*) (e + 8) - y) + *(int*) e + 8;
			}
			e += 0x2f4;
			n--;
		} while (n != 0);
	}
	fcn_0046eda0(*(short*) (p + 0xc), (short) v, win);
}
