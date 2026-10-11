// FUNCTION: GOLDTL 0x4ae040

int __cdecl gm_RandomMod(int);

int __cdecl fcn_004ae040(void)
{
	return (gm_RandomMod(2) & 0xffff) + 0x639;
}
