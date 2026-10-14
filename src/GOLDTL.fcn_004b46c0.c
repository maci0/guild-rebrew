extern unsigned char g_773d75;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int, char);

/* ADDRESS: GOLD 0x004b4550 */
/* ADDRESS: GOLDTL 0x004b46c0 */

int __cdecl fcn_004b46c0(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x38), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}
