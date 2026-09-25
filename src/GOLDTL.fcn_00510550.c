// FUNCTION: GOLD 0x0050d0b0
// SIZE: 78
// FUNCTION: GOLDTL 0x00510550
// SIZE: 78

void* __cdecl fcn_00502cd0(int, int, int, ...);

int __cdecl fcn_00510550(char* e)
{
	int n;

	n = 4;
	if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x284)) {
		n = 7;
	}
	if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x289)) {
		n += 3;
	}
	return n;
}
