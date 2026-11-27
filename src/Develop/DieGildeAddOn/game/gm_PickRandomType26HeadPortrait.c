

int __cdecl gm_RandomMod(int);

int __cdecl gm_PickRandomType26HeadPortrait(void)
{
	return (gm_RandomMod(2) & 0xffff) + 0x639;
}
