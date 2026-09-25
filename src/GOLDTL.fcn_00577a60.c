// FUNCTION: GOLD 0x0056f5f0
// SIZE: 74
// FUNCTION: GOLDTL 0x00577a60
// SIZE: 74

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_00577a60(int a, char* b)
{
	char* r;

	for (r = fcn_005463a0(1, 0, 0x9a); r != 0; r = fcn_005462a0()) {
		if (*(int*) (r + 0xac) == a && *(int*) (r + 0xb0) == *(int*) (b + 4)) {
			return 0;
		}
	}
	return 1;
}
