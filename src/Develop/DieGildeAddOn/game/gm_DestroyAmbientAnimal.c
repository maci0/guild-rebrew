#include <string.h>

#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"






extern int g_7728e4;

void __cdecl ch_DestroyCharacter(char*);


/* ADDRESS: GOLDTL 0x004bc060 */
/* ADDRESS: GOLDDE 0x004a9fb0 */
void __cdecl gm_DestroyAmbientAnimal(AMBIENT_ANIMAL_SLOT* s)
{
	ch_DestroyCharacter(s->objekt);
	memset(s, 0, sizeof(*s));
	g_7728e4--;
}
