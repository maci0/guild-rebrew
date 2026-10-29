

int __cdecl gm_RandomMod(int);

int __cdecl fcn_004ae060(void)
{
	return (gm_RandomMod(2) & 0xffff) + 0x639;
}
