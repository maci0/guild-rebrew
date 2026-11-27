typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl gm_GetLawEntry(int a, Stat* st);
int __cdecl ai_ComputeActionScore(float* o1, float* o2, int a3, char* e, Stat* st);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x00499000 */
int __cdecl ai_ScoreSabotieren(float* firstScore, float* secondScore, int idx, char* entity, int extraA, int extraB, int extraC)
{
	Stat st;

	*firstScore = 0;
	*secondScore = 0;
	gm_GetLawEntry(0x18, &st);
	if (st.v[6] && (entity[2] != 5 || !(entity[0x1c8] & 2))) {
		return ai_ComputeActionScore(firstScore, secondScore, idx, entity, &st);
	}
	return fcn_004a4410(firstScore, secondScore, idx, entity, extraA, extraB, extraC);
}
