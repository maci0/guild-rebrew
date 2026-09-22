// FUNCTION: GOLDTL 0x47d1b0
// SIZE: 39

int __cdecl fcn_0047d1b0(void)
{
	int v;

	v = (int) (*(float*) 0x773d50 * *(double*) 0x6640c0);
	if (v < 5) {
		return 5;
	}
	if (v > 0x10) {
		return 0x10;
	}
	return v;
}
