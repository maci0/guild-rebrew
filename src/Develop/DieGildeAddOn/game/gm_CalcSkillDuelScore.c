

#include "Develop/DieGildeAddOn/game/game_data.h"

#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x00507e70 */
float __cdecl gm_CalcSkillDuelScore(char* attacker, char* defender, int skillId)
{
	float atkSkill;
	float defSkill;
	float diff;

	atkSkill = gm_GetEntitySkill(attacker, skillId);
	defSkill = gm_GetEntitySkill(defender, skillId);
	diff = (atkSkill - defSkill * defSkill) * flt_0_6 + 0.4f;
	return (diff + ((atkSkill * atkSkill - defSkill) * 0.4f + flt_0_6)) * g_6628cc;
}
