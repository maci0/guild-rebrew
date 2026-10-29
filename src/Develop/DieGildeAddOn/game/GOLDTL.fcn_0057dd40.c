


int __cdecl gm_RandomMod(int);
void __cdecl fcn_005100f0(int, int);

void __cdecl fcn_0057dd40(char* a1)
{
	fcn_005100f0(*(int*) (a1 + 4), (gm_RandomMod(4) & 0xffff) + 3);
}
