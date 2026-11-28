


int __cdecl ai_DispatchPrivilege(int a, int b, int c);

/* ADDRESS: GOLDDE 0x0048bc40 */
int __cdecl ai_RunUsePrivs(int a, int b, int c)
{
	return ai_DispatchPrivilege(a, b, c) ? 0x2d : 0;
}
