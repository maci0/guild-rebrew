
/* ADDRESS: GOLDTL 0x0040bdc0 */
void __cdecl ch_ResetGridAndUniverseCache(void)
{
	*(int*) 0x67530c = -1;
	*(int*) 0x675310 = -1;
	*(int*) 0x6b5c54 = 0;
	*(int*) 0x6b5c58 = 0;
}
