#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_ResetMemoryCountFlags(int a);
int __cdecl d3_GetMeshMemorySize(char* p);

/* ADDRESS: GOLDTL 0x0045a130 */
int __cdecl d3_GetAllMeshesMemorySize(void)
{
	int n;
	char* p;

	n = 0;
	d3_ResetMemoryCountFlags(0x110);
	for (p = g_1042c38; p != g_1042d00; p = *(char**) (p + 0x1f8)) {
		n += d3_GetMeshMemorySize(p);
	}
	return n;
}
