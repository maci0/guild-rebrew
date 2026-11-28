


int __cdecl gm_RandomMod(int);
void __cdecl gm_ModifyHealth(int, int);

/* ADDRESS: GOLDDE 0x00563b70 */
void __cdecl he_GrantSmallSkillOrFavor0a4(char* entry)
{
	gm_ModifyHealth(*(int*) (entry + 4), (gm_RandomMod(4) & 0xffff) + 3);
}
