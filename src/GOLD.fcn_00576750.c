// FUNCTION: GOLD 0x00576750
// FUNCTION: GOLDTL 0x57ecf0

// fcn_00576750 — *a in {0x19,0x1b,0x29} ? 0 : 1.

int __cdecl fcn_00576750(int* a)
{
	if (*a == 0x19 || *a == 0x1b || *a == 0x29) {
		return 0;
	}
	return 1;
}

