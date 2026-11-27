


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl he_HasNoActiveAction0x2e(char* a, char* b)
{
	char* r;

	for (r = he_StartHandlungSearch(1, 0, 0x2e); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (b + 4) == *(int*) (r + 0xac) && *(int*) (r + 0xb0) == *(int*) (a + 4)) {
			return 0;
		}
	}
	return 1;
}
