// FUNCTION: GOLDTL 0x477420

int __cdecl fcn_00477420(int n)
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
