


#include "g_772f90.h"

extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* g_772fe4;

ALCHEMY_RECIPE_PROTOTYPE* __cdecl ahm_FindRecipePrototypeByKey(int key)
{
	int i;

	for (i = 0; i < g_772fe0; i++) {
		if (g_772fe4[i].key == key) {
			return &g_772fe4[i];
		}
	}
	return 0;
}
