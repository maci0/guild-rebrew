#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float flt_0_0;

char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(int a, int b, int c);
float __cdecl gm_CalcSkillDuelScore(char* a, char* b, int c);
int __cdecl gm_HasActiveSpecialObject(char* a1, int a2);

/* ADDRESS: GOLDTL 0x00493a30 */
/* ADDRESS: GOLDDE 0x00482880 */
int __cdecl ai_ShouldAcquitTrial(unsigned short* assessor, char* trial)
{
	char* accused;
	char* accuser;
	float favorAccuser;
	float favorAccused;
	float skillAccused;
	float skillAccuser;
	float severity;
	float accuserScore;

	if (*(int*) (trial + 0x48) == 1) {
		return 0;
	}
	if (*(int*) (trial + 8) == 1) {
		return 0;
	}
	accused = gm_LookupEntityRecordById(*(int*) (trial + 0x18));
	accuser = gm_LookupEntityRecordById(*(int*) (trial + 0x14));
	favorAccused = gm_CalcEntityFavor(*(unsigned short*) accused, *assessor, 1) * 0.01f;
	favorAccuser = gm_CalcEntityFavor(*(unsigned short*) accuser, *assessor, 1) * 0.01f;
	if (gm_HasActiveSpecialObject(accused, 0x22e) != 0) {
		favorAccused = favorAccused + 0.1f;
		favorAccuser = favorAccuser - 0.1f;
	}
	favorAccused = MIN(MAX(0.0f, favorAccused), 1.0f);
	favorAccuser = MIN(MAX(0.0f, favorAccuser), 1.0f);






	skillAccused = gm_CalcSkillDuelScore(accused, (char*) assessor, 4);
	skillAccuser = gm_CalcSkillDuelScore(accuser, (char*) assessor, 4);
	severity = *(float*) (trial + 4);
	accuserScore = skillAccuser + severity * severity * 0.0025f;
	if (*(int*) (trial + 0x44) != 0) {
		favorAccused = favorAccused * 1.1f;
		favorAccuser = favorAccuser * 0.9f;
	}
	return favorAccused + skillAccused > favorAccuser + accuserScore;
}
