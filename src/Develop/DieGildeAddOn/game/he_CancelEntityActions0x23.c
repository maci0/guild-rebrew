


char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
void __cdecl he_AbortActionIfFlag2(char*);

/* ADDRESS: GOLDDE 0x005570b0 */
void __cdecl he_CancelEntityActions0x23(char* a)
{
	char* u;

	for (u = he_StartHandlungSearch(1, 0, 0x23); u != 0; u = he_fn_Handlung()) {
		if ((u[0x78] & 3) && *(int*) (u + 0xb0) == *(int*) (a + 4)) {
			he_AbortActionIfFlag2(u);
		}
	}
}
