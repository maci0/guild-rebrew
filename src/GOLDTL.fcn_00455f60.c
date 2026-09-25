// FUNCTION: GOLDTL 0x455f60
// SIZE: 32
void __cdecl fcn_00455f60(int z, int dz, int mode, int w, unsigned char* dst)
{
	int i;
	unsigned char v;

	if (w > 0) {
		v = (unsigned char) (z >> 16);
		for (i = w; i != 0; i--) {
			if (v >= *dst) {
				*dst = v;
			}
			dst++;
		}
	}
}
