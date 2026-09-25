// FUNCTION: GOLDTL 0x0055c0f0
// SIZE: 76

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_0055c0f0(char* a, char* b)
{
	char* r;

	for (r = fcn_005463a0(1, 0, 0x4b); r != 0; r = fcn_005462a0()) {
		if (*(int*) (b + 4) == *(int*) (r + 0xb0) && *(int*) (a + 4) == *(int*) (r + 0xac)) {
			return 0;
		}
	}
	return 1;
}
