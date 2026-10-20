int __cdecl fcn_004ac1e0(int a);

/* ADDRESS: GOLD 0x004ac1a0 */
int __cdecl fcn_004ac1a0(int a, int b)
{
	int v;
	int r;

	v = b;
	if ((unsigned short)v >= 9) {
		v = 9;
	}
	r = fcn_004ac1e0(a);
	if (r != 0) {
		if (*(int*)(r + 8) == 0) {
			return v + 0x1e2b;
		}
		return v + 0x1e35;
	}
	return (unsigned short)b;
}
