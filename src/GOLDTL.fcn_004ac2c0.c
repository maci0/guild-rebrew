int __cdecl fcn_004ac1e0(int a);

/* ADDRESS: GOLDTL 0x004ac2c0 */
unsigned short __cdecl fcn_004ac2c0(int a0, volatile int a1)
{
	unsigned short v;
	int r;

	v = (unsigned short) a1;
	if (v >= 9) {
		v = 9;
	}
	r = fcn_004ac1e0(a0);
	if (r != 0) {
		if (*(int *) (r + 8) == 0) {
			return v + 0x1e2b;
		}
		return v + 0x1e35;
	}
	return (unsigned short) a1;
}
