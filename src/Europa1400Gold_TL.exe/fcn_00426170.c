// FUNCTION: GOLDTL 0x4225e0
// SIZE: 32

// fcn_00426170 — if(b) a[5] |= 0x10; else a[5] &= ~0x10.

void __cdecl fcn_00426170(int* a, int b)
{
	if (b != 0) {
		a[5] |= 0x10;
	} else {
		a[5] &= ~0x10;
	}
}
