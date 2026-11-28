


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDDE 0x0055d960 */
int __cdecl he_HasNoActiveAction0x9a(int a, char* b)
{
	char* r;

	for (r = he_StartHandlungSearch(1, 0, 0x9a); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (r + 0xac) == a && *(int*) (r + 0xb0) == *(int*) (b + 4)) {
			return 0;
		}
	}
	return 1;
}
