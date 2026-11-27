


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl he_HasNoActiveEvent04b(char* a, char* b)
{
	char* r;

	for (r = he_StartHandlungSearch(1, 0, 0x4b); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (b + 4) == *(int*) (r + 0xb0) && *(int*) (a + 4) == *(int*) (r + 0xac)) {
			return 0;
		}
	}
	return 1;
}
