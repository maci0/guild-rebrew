
/* ADDRESS: GOLDTL 0x00464330 */
unsigned int __cdecl fcn_00464330(unsigned int v, int n)
{
	unsigned int r;

	r = 0;
	do {
		r |= v & 1;
		v = v >> 1;
		r = r + r;
		n--;
	} while (n > 0);
	return r >> 1;
}
