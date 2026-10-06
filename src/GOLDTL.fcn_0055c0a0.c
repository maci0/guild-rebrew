// FUNCTION: GOLD 0x00553f60
// FUNCTION: GOLDTL 0x0055c0a0

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_0055c0a0(char* a, char* b)
{
	char* r;

	for (r = fcn_005463a0(1, 0, 0x2e); r != 0; r = fcn_005462a0()) {
		if (*(int*) (b + 4) == *(int*) (r + 0xac) && *(int*) (r + 0xb0) == *(int*) (a + 4)) {
			return 0;
		}
	}
	return 1;
}
