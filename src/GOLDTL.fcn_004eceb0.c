


extern float g_6628a0;

#include "Develop/DieGildeAddOn/game/alchemistry_logic.h"
int __cdecl ahm_CheckFlag(void*);
float __cdecl fcn_004ec8a0(char*, int);

float __cdecl fcn_004eceb0(char* a1, int a2)
{
	float* e;

	e = (float*) ahm_FindRecipeSlotImpl(a1, a2);
	if (ahm_CheckFlag(a1) == 0) {
		return g_6628a0;
	}
	if (e == 0) {
		return g_6628a0;
	}
	return fcn_004ec8a0(a1, 1) * e[1] + g_6628a0;
}
