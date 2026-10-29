/* ADDRESS: GOLDTL 0x00459980 */
void __cdecl fcn_00459980(void *a0, void *a1, char a2, float a3)
{
	unsigned char *p;
	int zero;

	zero = 0;
	if ((int) a0 == zero || (int) a1 == zero) {
		return;
	}
	p = (unsigned char *) a1;
	p[0x28] = p[0x2a];
	if (a3 != 0.0f) {
		*(int *) (p + 0xc) = zero;
		p[0x29] = a2;
		*(float *) (p + 0x10) = 1.0f / a3;
	} else {
		*(float *) (p + 0xc) = 1.0f;
		*(int *) (p + 0x10) = zero;
		p[0x29] = p[0x2a];
	}
}
