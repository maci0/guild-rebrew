typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl gm_GetLawEntry(int a, Stat* st);
int __cdecl ai_ComputeActionScore(float* o1, float* o2, int a3, char* e, Stat* st);
int __cdecl ai_ComputeBaseActionScore(float* o1, float* o2, int a3, char* e, int a5, int a6, char* p);

/* ADDRESS: GOLDTL 0x0049bb00 */
int __cdecl ai_ScoreUseParfuem(float* o1, float* o2, int idx, char* entity, int extra_a, int extra_b, char* p)
{
	Stat st;

	*o1 = 0;
	*o2 = 0;
	if (*(int*) (p + 0x10) < 0x1c || *(int*) (p + 0x10) > 0x22) {
		return 0;
	}
	gm_GetLawEntry(0x11, &st);
	if (st.v[6]) {
		return ai_ComputeActionScore(o1, o2, idx, entity, &st);
	}
	return ai_ComputeBaseActionScore(o1, o2, idx, entity, extra_a, extra_b, p);
}
