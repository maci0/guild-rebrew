int __cdecl aip_ExecDrohen(int a1, int a2, int a3);

/* ADDRESS: GOLDTL 0x0049ca60 */
/* ADDRESS: GOLDDE 0x0048b4a0 */
int __cdecl ai_RunDrohen(int actor, int a2, int a3)
{
	return aip_ExecDrohen(actor, a2, a3) ? 0x28 : 0;
}
