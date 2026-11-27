float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_HasActiveSpecialObject(void*, int);
int __cdecl abs(int);


/* ADDRESS: GOLDTL 0x004aacb0 */
int __cdecl ai_CompareOfficeCandidates(unsigned short* subjectEntity, unsigned short* candidateA, unsigned short* candidateB, int* comparisonOut)
{
	float d2;
	float q2;
	float d3;
	float q3;
	float s2;
	float s3;

	*comparisonOut = 0;
	if (subjectEntity == candidateB)
		return 0;
	if (subjectEntity == candidateA)
		return 1;
	d2 = (float)(gm_CalcEntityFavor(*candidateA, *subjectEntity, 1));
	q2 = gm_GetEntitySkill((char*) candidateA, 4);
	d3 = (float)(gm_CalcEntityFavor(*candidateB, *subjectEntity, 1));
	q3 = gm_GetEntitySkill((char*) candidateB, 4);
	s2 = (float)(q2 * 0.34 + d2 * 0.66);
	s3 = (float)(q3 * 0.34 + d3 * 0.66);
	if (gm_HasActiveSpecialObject(candidateA, 0x2be) != 0)
		d2 += 0.2f;
	if (gm_HasActiveSpecialObject(candidateB, 0x2be) != 0)
		d3 += 0.2f;
	if (abs((int) (d2 - d3)) * 0.66 > abs((int) (q2 - q3)) * 0.33)
		*comparisonOut = 1;
	else
		*comparisonOut = 2;
	if (s2 - 5.0f > s3)
		return 1;
	if (s3 - 5.0f > s2)
		return 0;
	return 2;
}
