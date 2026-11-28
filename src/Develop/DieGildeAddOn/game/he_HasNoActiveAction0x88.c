


char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDDE 0x0055f4a0 */
int __cdecl he_HasNoActiveAction0x88(char* a, char* b)
{
	char* u;

	for (u = he_StartHandlungSearch(1, 0, 0x88); u != 0; u = he_fn_Handlung()) {
		if (*(int*) (b + 4) == *(unsigned short*) (u + 8) && *(int*) (u + 0xb0) == *(int*) (a + 4)) {
			return 0;
		}
	}
	return 1;
}
