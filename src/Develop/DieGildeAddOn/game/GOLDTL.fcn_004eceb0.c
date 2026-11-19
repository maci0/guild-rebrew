


extern float g_6628a0;

#include "Develop/DieGildeAddOn/game/alchemistry_logic.h"
int __cdecl ahm_CheckFlag(void*);
float __cdecl fcn_004ec8a0(char*, int);

float __cdecl fcn_004eceb0(char* entity, int key)
{
	float* e;

	e = (float*) ahm_FindRecipeSlotImpl(entity, key);
	if (ahm_CheckFlag(entity) == 0) {
		return 1.0f;
	}
	if (e == 0) {
		return 1.0f;
	}
	return fcn_004ec8a0(entity, 1) * e[1] + 1.0f;
}
