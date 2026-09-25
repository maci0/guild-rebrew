// FUNCTION: GOLD 0x00553f10
// SIZE: 69
// FUNCTION: GOLDTL 0x0055c050
// SIZE: 69

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_0055c050(char* a)
{
	char* r;

	if (a != 0) {
		for (r = fcn_005463a0(1, 0, 0x62); r != 0; r = fcn_005462a0()) {
			if (*(int*) (r + 0xb0) == *(int*) (a + 1) && *(int*) (r + 0xb8) == 1) {
				return 0;
			}
		}
	}
	return 1;
}
