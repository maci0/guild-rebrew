/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_FindEntityCandidate(short*, int, int, unsigned short*, float, float, unsigned short*);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);


/* ADDRESS: GOLDTL 0x004aa920 */
/* ADDRESS: GOLDDE 0x00498c60 */
int __cdecl ai_SelectAnschwaerzenTargets(short* entity, int unused, char* result)
{
	unsigned short dst;
	unsigned short ids[4];
	unsigned short src;
	float f;

	ids[0] = 0xffff;
	ids[1] = 0xffff;
	ids[2] = 0xffff;
	ids[3] = 0xffff;
	if (*(int*) ((char*) entity + 0x194) < 3)
		return 0;
	ids[0] = *entity;
	if (gm_FindEntityCandidate(entity, 0xf00500, 4, ids, 0.0f, (float)(gm_RandomMod(0x10) + 33.0), &src) == 0)
		return 0;
	ids[1] = src;
	if (gm_FindEntityCandidate(entity, 0xf00500, 4, ids, 50.0f, 100.0f, &dst) == 0)
		return 0;
	result[0] = 7;
	*(int*) (result + 4) = *(int*) (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[src]) + 4);
	f = gm_CalcSkillDuelScore((char*) entity, ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[src]), 4);
	if (!(gm_RandomFloat01() + f >= 1.0f))
		return 0;
	*(int*) (result + 8) = *(int*) (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[dst]) + 4);
	return 1;
}
