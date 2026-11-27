#include <string.h>

extern float g_664320;
#include "Develop/DieGildeAddOn/game/game_data.h"

float __cdecl gm_CalcSkillDuelScore(char* a, char* b, int c);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_CheckPrivilege(int a1, char* a2, int a3);

/* ADDRESS: GOLDTL 0x00494740 */
int __cdecl gm_EvalSkill3PrivilegeCheck(int actor, int entity, int* level_out, int unused)
{
	float v;
	float w;
	int level;

	v = gm_CalcSkillDuelScore((char*) actor, (char*) entity, 3);
	w = gm_RandomFloat01() + v;
	{
		float f = 0.0f;
		int buf[0x88];

		level = 0x3b;
		memset(buf, 0, sizeof(buf));
		buf[0] = 1;
		if ((gm_CheckPrivilege(0xd, (char*) entity, (int) buf) & 2) != 0) {
			f = g_664320;
			level = 0xd;
		}
		else if ((gm_CheckPrivilege(0xa, (char*) entity, (int) buf) & 2) != 0) {
			f = 0.1f;
			level = 0xa;
		}
		if (level_out != 0) {
			*level_out = level;
		}
		return (w + f) > 1.0f;
	}
}
