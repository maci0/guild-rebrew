


#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned char __cdecl gm_GetCitySkillAverage(int a);
int __cdecl gm_GetLawEntry(int idx, void* dst);

int __cdecl ai_EvalStrafrechtLaw19(char* actor, int unused, int* out)
{
	int info[9];
	float skill_val;
	float weight;
	float axis_good;
	float axis_evil;
	float axis_neutral;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (actor + 0x164));
	skill_val = gm_GetEntitySkill(actor, 3);
	skill_val = (skill_val - (gm_GetCitySkillAverage(3) + 1.0f) * 0.003968254f) * 0.023809524f;
	axis_good = (float)((*(float*) (actor + 0xf4) - 2.0) * *(float*) (actor + 0xfc));
	axis_neutral = (*(float*) (actor + 0x100) - 2.0) * *(float*) (actor + 0x108);
	axis_evil = (*(float*) (actor + 0x10c) - 2.0) * *(float*) (actor + 0x114);
	if (job == 12) {
		weight = skill_val * 1.3f;
	} else {
		weight = skill_val * 0.9f;
	}
	gm_GetLawEntry(0x19, info);
	if (weight < 1.0f && info[6] == 0) {
		if (!(axis_evil > axis_good)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(weight > 1.0) || info[6] != 1 || !(axis_neutral > axis_good)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
