#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_ResetMemoryCountFlags(int a);
int __cdecl d3_GetAnimMemorySize(char* p);

/* ADDRESS: GOLDTL 0x0045a1c0 */
int __cdecl d3_GetAllAnimsMemorySize(void)
{
	int n;
	char* p;

	n = 0;
	d3_ResetMemoryCountFlags(0x104);
	for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
		n += d3_GetAnimMemorySize(p);
	}
	return n;
}
