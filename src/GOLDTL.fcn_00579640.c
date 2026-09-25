// FUNCTION: GOLDTL 0x579640
// SIZE: 79

char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_00579640(char* a, char* b)
{
	char* u;

	for (u = fcn_005463a0(1, 0, 0x88); u != 0; u = fcn_005462a0()) {
		if (*(int*) (b + 4) == *(unsigned short*) (u + 8) && *(int*) (u + 0xb0) == *(int*) (a + 4)) {
			return 0;
		}
	}
	return 1;
}
