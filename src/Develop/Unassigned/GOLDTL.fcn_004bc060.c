#include <string.h>

#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"






extern int g_7728e4;

void __cdecl fcn_004030e0(char*);


/* ADDRESS: GOLDTL 0x004bc060 */
void __cdecl fcn_004bc060(AMBIENT_ANIMAL_SLOT* s)
{
	fcn_004030e0(s->objekt);
	memset(s, 0, sizeof(*s));
	g_7728e4--;
}
