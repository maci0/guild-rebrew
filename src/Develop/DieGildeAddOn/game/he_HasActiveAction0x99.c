


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDDE 0x0055d770 */
int __cdecl he_HasActiveAction0x99(int k)
{
	char* r;

	for (r = he_StartHandlungSearch(1, 0, 0x99); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (r + 0xb0) == k) {
			return 1;
		}
	}
	return 0;
}
