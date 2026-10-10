extern unsigned char g_773d75;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int, char);

// FUNCTION: GOLD 0x004b45f0
// FUNCTION: GOLDTL 0x4b4760

int __cdecl fcn_004b4760(short* e, char* thr)
{
	return fcn_0050b710(gm_WalkEntityChain(*e), (*(char*)&g_773d75)) >= *(int*) (thr + 0x14);
}
