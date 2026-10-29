#include "Develop/DieGildeAddOn/game/spiel.h"

void __cdecl fcn_004f2540(int a1, int x, int a3, int a4, int a5);
void __cdecl fcn_004f2f90(int a1, int a2, int x, int a4, int a5, int a6);

/* ADDRESS: GOLDTL 0x00490130 */
int __cdecl fcn_00490130(int a1, char* p, char* q)
{
	int x;

	gm_ResolveEntityById((void**) (&x), 0, 0, *(int*) (p + 0xc));
	if (!x) {
		return 0;
	}
	if (*(int*) (p + 0x10) == 4) {
		fcn_004f2540(a1, x, *(int*) (p + 4), 10, *(int*) (p + 8));
		return 0x3e;
	}
	if (*(int*) (p + 0x10) == 5) {
		fcn_004f2f90(a1, *(int*) (p + 4), x, *(int*) (q + 4), *(int*) (q + 0x10), *(int*) (p + 8));
		return 0x3e;
	}
	return 0;
}
