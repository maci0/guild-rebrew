
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudePROT;
extern int gm_DifficultyLevel;
extern float flt_0_0;

/* ADDRESS: GOLDDE 0x004f6910 */
float __cdecl gm_GetTypeWageBase(unsigned char* p, int k, int a, int b)
{
	float r;
	unsigned char* t;

	r = flt_0_0;
	t = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[k];
	if (a != -1) {
		r = (float) (t[0x229 + a] * 896);
	} else if (b != -1) {
		r = (float) (t[0x233 + b] * 896);
	}
	if (p[2] == 6 || p[2] == 7) {
		r = (float)(r * (1.0 - (2 - gm_DifficultyLevel) * 0.25));
	}
	return r;
}
