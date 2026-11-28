#include "Develop/Units/d2.v1/g_100f200.h"

extern int g_100f804;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern Slot100f200 g_100f200[];
#include <string.h>

/* ADDRESS: GOLDTL 0x00475290 */
int __cdecl d2_AllocHudRectSlot(int a, int b, int c, int d, int e)
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

/* ADDRESS: GOLDTL 0x004752e0 */
void __cdecl d2_FreeHudRectSlot(int i)
{
	if (g_100f804 >= 1 && i >= 0) {
		memset(&g_100f200[i], 0, sizeof(g_100f200[i]));
		g_100f804--;
	}
}
