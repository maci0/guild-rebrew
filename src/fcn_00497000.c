// FUNCTION: GOLD 0x00497620
// SIZE: 48
// FUNCTION: GOLDTL 0x497000
// SIZE: 37

int __cdecl fcn_004e7d40(int, int);

int __cdecl fcn_00497000(int a1, char* a2)
{
	if (*a2 != 0xa) {
		return 0;
	}
	return fcn_004e7d40(a1, *(int*) (a2 + 4)) != 0 ? 0xa : 0;
}
