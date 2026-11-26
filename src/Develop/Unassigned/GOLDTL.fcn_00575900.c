


int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl he_StartAhmUnlockRecipe(void);
void __cdecl he_RunAhmUnlockRecipe(void);
void __cdecl he_StartAhmRefineRecipe(void);
void __cdecl he_RunAhmRefineRecipe(void);
void __cdecl he_StartAhmBoostEssence(void);
void __cdecl he_RunAhmBoostEssence(void);
void __cdecl he_StartAhmAction0x98(void);
void __cdecl he_RunAhmAction0x98(void);
int __cdecl he_RegisterActionMeta(int, char*, int, int, int);

int __cdecl fcn_0056d4c0(void)
{
	if (he_RegisterHandler(0x95, (void*) he_StartAhmUnlockRecipe, (void*) he_RunAhmUnlockRecipe) != 0 ||
	    he_RegisterHandler(0x96, (void*) he_StartAhmRefineRecipe, (void*) he_RunAhmRefineRecipe) != 0 ||
	    he_RegisterHandler(0x97, (void*) he_StartAhmBoostEssence, (void*) he_RunAhmBoostEssence) != 0 ||
	    he_RegisterHandler(0x98, (void*) he_StartAhmAction0x98, (void*) he_RunAhmAction0x98) != 0) {
		return 1;
	}
	he_RegisterActionMeta(0x95, "erforschen", 1, 0x500, -1);
	he_RegisterActionMeta(0x96, "erforschen", 1, 0x500, -1);
	return 0;
}
