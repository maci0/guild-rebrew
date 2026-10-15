

extern float g_662d34;
extern float g_6628d8;
extern float g_6628cc;

#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x00507e70 */
/* ADDRESS: GOLD 0x00504e20 */
float __cdecl fcn_00507e70(char* a, char* b, int c)
{
	float x;
	float y;
	float t;

	x = fcn_00507f10(a, c);
	y = fcn_00507f10(b, c);
	t = (x - y * y) * g_662d34 + g_6628d8;
	return (t + ((x * x - y) * g_6628d8 + g_662d34)) * g_6628cc;
}
