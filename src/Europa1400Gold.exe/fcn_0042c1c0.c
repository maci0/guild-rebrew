// FUNCTION: GOLD 0x0042c1c0
// SIZE: 23
// fcn_0042c1c0 — first zero slot in 0x6332f0 array, else -1. SIB wall (ptrwalk).

int __cdecl fcn_0042c1c0(void)
{
	int i;
	for (i = 0; i < 0x10; i++) {
		if (*(int*) ((char*) 0x6332f0 + i * 4) == 0) {
			return i;
		}
	}
	return -1;
}
