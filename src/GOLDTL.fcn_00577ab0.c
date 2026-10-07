// FUNCTION: GOLD 0x0056f640
// FUNCTION: GOLDTL 0x00577ab0

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_00577ab0(char* b)
{
	char* r;

	for (r = fcn_005463a0(1, 0, 0x9b); r != 0; r = fcn_005462a0()) {
		if (*(int*) (r + 0xac) == *(int*) (b + 4)) {
			return 0;
		}
	}
	return 1;
}
