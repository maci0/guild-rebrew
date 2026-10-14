/* ADDRESS: GOLDTL 0x00475320 */

int __cdecl fcn_00475320(unsigned char* buf, int n)
{
	int lim;
	int i;
	unsigned char t;

	lim = n * 2 - 2;
	for (i = 0; i < lim; i += 2) {
		t = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = t;
	}
	return 1;
}
