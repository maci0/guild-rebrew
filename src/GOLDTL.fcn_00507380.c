// FUNCTION: GOLD 0x504350
// SIZE: 128
// FUNCTION: GOLDTL 0x00507380
// SIZE: 119

int __cdecl fcn_00507380(int k)
{
	if (k >= 1 && k <= 6) {
		return 7;
	}
	if (k >= 0x28 && k <= 0x2d) {
		return 7;
	}
	if (k >= 0x23 && k <= 0x27) {
		return 2;
	}
	if (k >= 0x2e && k <= 0x33) {
		return 3;
	}
	if (k >= 0x3a && k <= 0x3f) {
		return 4;
	}
	if (k >= 0x40 && k <= 0x45) {
		return 5;
	}
	if (k >= 0xd && k <= 6) {
		return 6;
	}
	return 0;
}
