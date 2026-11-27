


short __cdecl gm_RandomMod(int);

int __cdecl ai_CheckAction01dPredicate(void)
{
	return gm_RandomMod(4) == 0;
}
