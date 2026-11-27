
/* ADDRESS: GOLDTL 0x00477420 */
int __cdecl d2_NextPowerOfTwo(int n)
{
	int i;
	int v;
	int r;

	v = n;
	for (i = 0; i < 24; i++) {
		if (v <= 0)
			break;
		v >>= 1;
	}
	r = 1 << i;
	if (r < n)
		r += r;
	return r;
}
