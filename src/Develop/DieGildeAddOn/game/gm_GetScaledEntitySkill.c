extern float g_66413c;



#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl gm_GetScaledEntitySkill(char* a, int b)
{
	return (int) (gm_GetEntitySkill(a, b) * g_66413c);
}
