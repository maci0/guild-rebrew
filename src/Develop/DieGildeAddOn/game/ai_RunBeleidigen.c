int __cdecl ai_DispatchPrivilege(int a1, int a2, int a3);

/* ADDRESS: GOLDTL 0x0049d010 */
/* ADDRESS: GOLDDE 0x0048ba50 */
int __cdecl ai_RunBeleidigen(int a1, int a2, int a3)
{
	return ai_DispatchPrivilege(a1, a2, a3) ? 0x2b : 0;
}
