char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_ComputeBaseActionScore(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);
int __cdecl ai_CalculateMatchingMethodEffects(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x004a03d0 */
int __cdecl ai_ScoreUpgradeZunft(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7)
{
	unsigned char kind;
	char* found;

	*o1 = -100.0f;
	*o2 = -100.0f;
	kind = e[0x169];
	if (kind < 0x1e && kind > 0x21) {
		return 0;
	}
	if (kind == 0x1e) {
		found = gm_StartFilteredEntitySearch(1, 5, 0x17);
	} else if (kind == 0x1f) {
		found = gm_StartFilteredEntitySearch(1, 5, 0x18);
	} else if (kind == 0x20) {
		found = gm_StartFilteredEntitySearch(1, 5, 0x19);
	} else {
		found = gm_StartFilteredEntitySearch(1, 5, 0x1a);
	}
	if (!found) {
		return 0;
	}
	if (found[0x5c] < gm_RandomMod(0x10) + 0x32) {
		ai_CalculateMatchingMethodEffects(o1, o2, a3, e, a5, a6, a7);
		*o1 = *o1 * 3.0f;
		*o2 = *o2 * 3.0f;
		return 1;
	}
	return ai_ComputeBaseActionScore(o1, o2, a3, e, a5, a6, a7);
}
