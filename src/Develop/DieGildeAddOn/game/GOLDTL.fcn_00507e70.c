

#include "Develop/DieGildeAddOn/game/game_data.h"

#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x00507e70 */
float __cdecl fcn_00507e70(char* a, char* b, int c)
{
	float x;
	float y;
	float t;

	x = gm_GetEntitySkill(a, c);
	y = gm_GetEntitySkill(b, c);
	t = (x - y * y) * g_662d34 + 0.4f;
	return (t + ((x * x - y) * 0.4f + g_662d34)) * g_6628cc;
}
