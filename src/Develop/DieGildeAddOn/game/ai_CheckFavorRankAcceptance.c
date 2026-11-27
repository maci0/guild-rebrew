int __cdecl amt_GetEffectiveRoleLevel(unsigned short id, int a2);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004943e0 */
int __cdecl ai_CheckFavorRankAcceptance(unsigned short* host, unsigned short* guest)
{
	int hostRank;
	float score;

	if (*(int*) ((char*) host + 4) == *(int*) ((char*) guest + 0x210)) {
		return 0;
	}
	hostRank = amt_GetEffectiveRoleLevel(*host, 0);
	score = (amt_GetEffectiveRoleLevel(*guest, 0) - hostRank) * 2.5f;
	score = gm_CalcEntityFavor(*host, *guest, 1) + score;
	if (gm_RandomFloat01() * 75.0f > score) {
		return 0;
	}
	return 1;
}
