int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLD 0x004adf20 */
/* ADDRESS: GOLDTL 0x004ae060 */
int __cdecl gm_PickRandomHeadPortrait(void)
{
	return (gm_RandomMod(2) & 0xffff) + 0x639;
}
