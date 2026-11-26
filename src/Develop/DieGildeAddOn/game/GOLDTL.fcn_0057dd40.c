


int __cdecl gm_RandomMod(int);
void __cdecl fcn_005100f0(int, int);

void __cdecl he_GrantSmallSkillOrFavor0a4(char* entry)
{
	fcn_005100f0(*(int*) (entry + 4), (gm_RandomMod(4) & 0xffff) + 3);
}
