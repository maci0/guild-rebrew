


extern float flt_1_0;

#include "Develop/DieGildeAddOn/game/alchemistry_logic.h"
int __cdecl ahm_CheckFlag(void*);
float __cdecl ahm_GetEssenceValue(char*, int);

float __cdecl ahm_CalcRecipeProductivityBonus(char* entity, int key)
{
	float* e;

	e = (float*) ahm_FindRecipeSlotImpl(entity, key);
	if (ahm_CheckFlag(entity) == 0) {
		return 1.0f;
	}
	if (e == 0) {
		return 1.0f;
	}
	return ahm_GetEssenceValue(entity, 1) * e[1] + 1.0f;
}
