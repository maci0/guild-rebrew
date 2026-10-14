#include "g_100f200.h"

extern int g_100f804;
extern int g_67d8d4;
extern Slot100f200 g_100f200[];
/* ADDRESS: GOLDTL 0x00475290 */

int __cdecl fcn_00475290(int a, int b, int c, int d, int e)
{
	int n;
	Slot100f200* p;

	n = g_100f804 + 1;
	g_100f804 = n;
	g_67d8d4 = n;
	if (n > 0x40)
		return 0;
	p = &g_100f200[n];
	p->a = a;
	p->b = b;
	p->c = c;
	p->d = d;
	p->e = e;
	p->used = 1;
	return n;
}
