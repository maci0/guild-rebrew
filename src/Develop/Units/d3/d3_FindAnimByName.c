#if defined(REBREW_GOLD)
#include <string.h>

/* ADDRESS: GOLD 0x00433f40 */
char* __cdecl d3_FindAnimByName(const char* name)
{
	char* node;

	node = *(char**) 0xfc26e0;
	while (node != (char*) 0xfe7440) {
		if (stricmp(name, node) == 0) {
			return node;
		}
		node = *(char**) (node + 0x160);
	}
	return 0;
}
#else
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0065f220(const char* a, const char* b);

#include "Develop/Units/d3/d3_animation.h"

/* ADDRESS: GOLDTL 0x00433ba0 */
char* __cdecl d3_FindAnimByName(const char* name)
{
	char* p;

	for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
		if (fcn_0065f220(name, p) == 0) {
			return p;
		}
	}
	return 0;
}
#endif
