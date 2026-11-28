extern float g_66413c;



#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDDE 0x004f2fd0 */
int __cdecl gm_GetScaledEntitySkill(char* a, int b)
{
	return (int) (gm_GetEntitySkill(a, b) * g_66413c);
}
