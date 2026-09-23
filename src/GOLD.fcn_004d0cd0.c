// FUNCTION: GOLDTL 0x4d1d20
// SIZE: 22
// FUNCTION: GOLD 0x004d0cd0
// SIZE: 22
// fcn_004d0cd0 — first index holding -1 in the 16-int array, else -1.

int __cdecl fcn_004d0cd0(int* a)
{
	int i;
	for (i = 0; i < 0x10; i++) {
		if (a[i] == -1) {
			return i;
		}
	}
	return -1;
}
