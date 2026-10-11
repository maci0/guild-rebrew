// FUNCTION: GOLD 0x00575800
// FUNCTION: GOLDTL 0x57dd40

int __cdecl gm_RandomMod(int);
int __cdecl fcn_005100f0(int, int);

int __cdecl fcn_0057dd40(void* a1)
{
	return fcn_005100f0(*(int*) ((char*) a1 + 4), (gm_RandomMod(4) & 0xffff) + 3);
}
