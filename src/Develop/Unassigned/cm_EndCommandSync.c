extern int g_00f81168;
extern int g_00a68c04;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004c3b40 */
void __cdecl cm_EndCommandSync(void)
{
    g_00a68c04 = g_00f81168 + 1;
}
#else
/* ADDRESS: GOLDTL 0x004c44b0 */
void __cdecl cm_EndCommandSync(void)
{
	*(int*) 0xaed204 = *(int*) 0x1005768 + 1;
}
#endif
