#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl _strnicmp(const char* a, const char* b, int n);

/* ADDRESS: GOLDTL 0x00449b60 */
/* ADDRESS: GOLDDE 0x00440240 */
char* __cdecl d3_FindCachedModel(const char* name)
{
	char* p;

	for (p = g_1042c38; p != g_1042d00; p = *(char**) (p + 0x1f8)) {
		if (_strnicmp(name, p, 0x3f) == 0) {
			return p;
		}
	}
	return 0;
}
