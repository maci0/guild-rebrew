
/* ADDRESS: GOLDTL 0x0043c0d0 */
void __cdecl fcn_0043c0d0(unsigned char* buf, int x0, int x1, unsigned char c0, unsigned char c1)
{
	float step;
	float v;
	int i;

	step = (float) (c1 - c0) / (x1 - x0);
	v = c0;
	for (i = x0; i <= x1; i++) {
		buf[i] = (unsigned char) (v + 0.5f);
		v += step;
	}
}
