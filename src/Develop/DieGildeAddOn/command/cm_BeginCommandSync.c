extern int g_00f81168;
extern int g_00f8121c;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004c3b30 */
void __cdecl cm_BeginCommandSync(void)
{
    g_00f8121c = g_00f81168 + 1;
}
#else
/* ADDRESS: GOLDTL 0x004c44a0 */
/* ADDRESS: GOLDDE 0x004b1eb0 */
void __cdecl cm_BeginCommandSync(void)
{
	*(int*) 0x100581c = *(int*) 0x1005768 + 1;
}
#endif
