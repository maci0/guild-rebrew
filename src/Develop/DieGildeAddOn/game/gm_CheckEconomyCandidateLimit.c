


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

double __cdecl gm_GetCityStatsSummary(float*);
int __cdecl ai_FilterCandidateLimit(int, int, int);

/* ADDRESS: GOLDDE 0x004a3220 */
int __cdecl gm_CheckEconomyCandidateLimit(int entity, int cmd, char* spec)
{
	float buf[10];

	if ((*(int*)&gm_GameTime) < 10)
		return 0;
	gm_GetCityStatsSummary(buf);
	if (*(int*) (spec + 0x14) < buf[6])
		return ai_FilterCandidateLimit(cmd, 0, *(int*) (spec + 0x18));
	return ai_FilterCandidateLimit(cmd, 1, *(int*) (spec + 0x18));
}
