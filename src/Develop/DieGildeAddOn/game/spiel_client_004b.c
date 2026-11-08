extern unsigned char g_773d75;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int, char);

int __cdecl fcn_0050b710(int, char);

int __cdecl fcn_0050b710(int, char);

/* ADDRESS: GOLD 0x004b4830 */
/* ADDRESS: GOLDTL 0x004b49a0 */
int __cdecl fcn_004b49a0(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x34) + *(int*) (p + 0x2c), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}

/* ADDRESS: GOLDTL 0x004b49e0 */
int __cdecl fcn_004b49e0(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x30), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}

/* ADDRESS: GOLDTL 0x004b4a20 */
int __cdecl fcn_004b4a20(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return fcn_0050b710(*(int*) (p + 0x3c), (*(char*)&g_773d75)) > *(int*) (thr + 0x14);
}
