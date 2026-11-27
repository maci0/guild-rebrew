int __cdecl gm_GetOppositeStatIndex(int job);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_ComputeBaseActionScore(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);
int __cdecl ai_CalculateMatchingMethodEffects(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x0049ef30 */
int __cdecl ai_ScoreChangeProfession(float* firstScore, float* secondScore, int a3, char* e, int skip, int a6, int a7)
{
	int n;

	*firstScore = -100.0f;
	*secondScore = -100.0f;
	if (skip) {
		*firstScore = -1.0e30f;
		*secondScore = -1.0e30f;
	} else if (e[2] == 5 && !e[0x169]) {
		n = gm_GetOppositeStatIndex(*(unsigned char*) (e + 0x164));
		if (n >= 3) {
			if (n < 6) {
				if (gm_RandomMod(n - 1)) {
					return ai_ComputeBaseActionScore(firstScore, secondScore, a3, e, 0, a6, a7);
				}
			} else {
				ai_CalculateMatchingMethodEffects(firstScore, secondScore, a3, e, 0, a6, a7);
				*firstScore = *firstScore + *firstScore;
				*secondScore = *secondScore * 3.0f;
				return 1;
			}
		}
	}
	return 0;
}
