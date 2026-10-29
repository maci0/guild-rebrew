#define MAXV(a, b) ((a) < (b) ? (b) : (a))
#define MINV(a, b) ((b) < (a) ? (b) : (a))

void __cdecl fcn_004fd400(short* a, int* b);
int __cdecl gm_AccumulateTyped2(unsigned short* e);
#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x004ac320 */
int __cdecl fcn_004ac320(unsigned short* e)
{
	short s;
	int n;
	int r;
	int x;

	fcn_004fd400(&s, &n);
	r = gm_AccumulateTyped2(e);
	x = (int) MINV(MAXV(gm_WalkEntityChain(*e) * 500.0f / n, 1600.0f), 16000.0f);
	return r > x ? x : 0;
}
