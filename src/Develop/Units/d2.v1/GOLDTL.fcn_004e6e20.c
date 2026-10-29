


#define MAX(a, b) ((a) > (b) ? (a) : (b))

extern int g_6b7fac;
extern unsigned int g_772f70;
extern int g_68bfcc;

void __cdecl fcn_00472640(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_004e6e20(int h, int total, int reset)
{
	int pct;
	int v;

	pct = 100;
	if (reset != 0) {
		g_772f70 = (*(unsigned int*)&g_6b7fac);
		g_68bfcc = total;
		fcn_00472640(h, 0);
	} else {
		v = (int) ((1.0f - (float) ((*(unsigned int*)&g_6b7fac) - g_772f70) / g_68bfcc) * 100.0f);
		pct = MAX(v, 0);
	}
	d2_SetElementValue(h, 0, 100, pct);
	return pct;
}
