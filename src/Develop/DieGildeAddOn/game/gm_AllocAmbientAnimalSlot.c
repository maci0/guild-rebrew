#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"








extern AMBIENT_ANIMAL_SLOT* g_7728e8;
extern int g_7728e4;
extern volatile int gm_GameTicks;


/* ADDRESS: GOLDTL 0x004bc010 */
/* ADDRESS: GOLDDE 0x004a9f60 */
AMBIENT_ANIMAL_SLOT* __cdecl gm_AllocAmbientAnimalSlot(void)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (g_7728e8[i].objekt == 0)
			break;
	}
	if (i == 32)
		return 0;
	g_7728e4++;
	g_7728e8[i].created_tick = gm_GameTicks;
	return &g_7728e8[i];
}
