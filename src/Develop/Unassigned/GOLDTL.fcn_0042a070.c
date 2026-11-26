extern char g_6791c8[];
/* ADDRESS: GOLDTL 0x0042a070 */
void __cdecl evt_ResetCurrentContextId(void)
{
	*(int*) &g_6791c8 = -1;
}
