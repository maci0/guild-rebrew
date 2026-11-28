


char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl he_RewardRandomItemOrGold0a4(char*);
void __cdecl he_GrantSmallSkillOrFavor0a4(char*);
void __cdecl he_GrantScaledGold0a4(char*);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x005639d0 */
void __cdecl he_UpdateEvent0a4(char* o)
{
	char* x;
	float r;

	x = gm_LookupEntityRecordById(*(int*) (o + 0xc));
	if (*(int*) (o + 0x70) != -1 && *(int*) (o + 0x70) != -2 && x != 0) {
		r = gm_RandomFloat01();
		if (r > 0.8f) {
			he_RewardRandomItemOrGold0a4(x);
		} else if (r > 0.4f) {
			he_GrantSmallSkillOrFavor0a4(x);
		} else {
			he_GrantScaledGold0a4(x);
		}
	}
	he_FreeAction(o);
}
