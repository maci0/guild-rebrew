// FUNCTION: GOLD 0x4324e0
// FUNCTION: GOLDTL 0x004321a0

// SIZE 0x4
typedef struct {
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
} F4321a0;

int __cdecl fcn_004321a0(F4321a0 flags, int a2, int a3, int v, int lo, int hi, int max)
{
	unsigned char f;

	f = *(volatile unsigned char*) &flags.b1;
	if (f & 2) {
		if (v > lo) {
			return v - 1;
		}
		return lo + 1;
	}
	if (v >= hi) {
		if (f & 0x10) {
			v++;
			if (v > max - 1) {
				return max - 1;
			}
			return v;
		}
		if (f & 1) {
			return v - 1;
		}
		return lo;
	}
	return v + 1;
}
