


#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned char __cdecl fcn_004f97a0(int a);
int __cdecl gm_GetLawEntry(int idx, void* dst);

int __cdecl ai_EvalStrafrechtLaw13(char* actor, int unused, int* out)
{
	int info[9];
	float skill_val;
	float weight;
	float axis_good;
	float axis_evil;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (actor + 0x164));
	skill_val = gm_GetEntitySkill(actor, 4);
	skill_val = (skill_val - (fcn_004f97a0(4) + 1.0f) * 0.003968254f) * 0.023809524f;
	axis_good = (float)((*(float*) (actor + 0xf4) - 2.0) * *(float*) (actor + 0xfc));
	axis_evil = (float)((*(float*) (actor + 0x10c) - 2.0) * *(float*) (actor + 0x114));
	weight = skill_val * 0.8f;
	gm_GetLawEntry(0x13, info);
	if (weight < 1.0f && info[6] == 0) {
		if (!(axis_good > axis_evil)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(weight > 1.0) || info[6] != 1 || !(axis_evil > axis_good)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
