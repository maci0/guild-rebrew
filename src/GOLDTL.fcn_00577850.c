// FUNCTION: GOLD 0x0056f400
// SIZE: 54
// FUNCTION: GOLDTL 0x00577850
// SIZE: 54

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_00577850(int k)
{
	char* r;

	for (r = fcn_005463a0(1, 0, 0x99); r != 0; r = fcn_005462a0()) {
		if (*(int*) (r + 0xb0) == k) {
			return 1;
		}
	}
	return 0;
}
