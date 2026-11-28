


#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned char __cdecl gm_GetCitySkillAverage(int a);
int __cdecl gm_GetLawEntry(int idx, void* dst);

int __cdecl ai_CheckLaw0x15(char* entity, int unused, int* out)
{
	int info[9];
	float m;
	float x;
	float y;
	float z;
	float w;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (entity + 0x164));
	m = gm_GetEntitySkill(entity, 3);
	m = (m - (gm_GetCitySkillAverage(3) + 1.0f) * 0.003968254f) * 0.023809524f;
	y = (float)((*(float*) (entity + 0xf4) - 2.0) * *(float*) (entity + 0xfc));
	w = (float)((*(float*) (entity + 0x100) - 2.0) * *(float*) (entity + 0x108));
	z = (float)((*(float*) (entity + 0x10c) - 2.0) * *(float*) (entity + 0x114));
	x = m * 1.1f;
	gm_GetLawEntry(0x15, info);
	if (x < 1.0f && info[6] == 0) {
		if (!(z > y)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(x > 1.0) || info[6] != 1 || !(w > y)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
