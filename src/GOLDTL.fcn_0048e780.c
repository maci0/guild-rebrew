#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl fcn_004a6550(int a1, int x);

/* ADDRESS: GOLD 0x0048f1d0 */
/* ADDRESS: GOLDTL 0x0048e780 */
int __cdecl fcn_0048e780(int a1, char* a, char* b)
{
	int x;
	int y;

	if (a[0] != 4 || b[0] != 4) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&x), 0, 0, *(int*) (a + 4));
	if (!x) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&y), 0, 0, *(int*) (b + 4));
	if (!y) {
		return 0;
	}
	return fcn_004a6550(a1, x) ? 0x42 : 0;
}
