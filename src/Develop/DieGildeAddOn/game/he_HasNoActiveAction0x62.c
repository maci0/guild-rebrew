


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDDE 0x005422f0 */
int __cdecl he_HasNoActiveAction0x62(char* a)
{
	char* r;

	if (a != 0) {
		for (r = he_StartHandlungSearch(1, 0, 0x62); r != 0; r = he_fn_Handlung()) {
			if (*(int*) (r + 0xb0) == *(int*) (a + 1) && *(int*) (r + 0xb8) == 1) {
				return 0;
			}
		}
	}
	return 1;
}
