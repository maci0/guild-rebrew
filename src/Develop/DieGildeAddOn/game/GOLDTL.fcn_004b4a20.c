extern unsigned char g_773d75;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int, char);


/* ADDRESS: GOLDTL 0x004b4a20 */
int __cdecl fcn_004b4a20(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x3c), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}
