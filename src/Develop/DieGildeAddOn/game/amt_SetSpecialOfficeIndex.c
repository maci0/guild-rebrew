extern int g_006f0720; /* 0x006f0720 */

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004ad1b0 */
void __cdecl amt_SetSpecialOfficeIndex(int value)
{
    g_006f0720 = value;
}
#else
/* ADDRESS: GOLDTL 0x004ad2d0 */
void __cdecl amt_SetSpecialOfficeIndex(int index)
{
	*(int*) 0x7728d0 = index;
}
#endif
