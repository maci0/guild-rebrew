#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x005fe153 */
unsigned int __stdcall fcn_005fe153(int* a0, unsigned int a1, unsigned int a2,
	unsigned int a3, unsigned int a4, unsigned int a5)
{
	unsigned int v4;

	if ((a1 & 0xe0fe2000) == 0 && (a1 & 1) == 0 && (a1 & 0x400) == 0) {
		v4 = a1 & 0x1cfff;
		if (v4) {
			if (*((unsigned char*) a0 + 0x10) & 1) {
				v4 |= 1;
			}
		} else {
			v4 = (unsigned int) a0[4];
		}
		return (*(unsigned int (__stdcall**) (int*, unsigned int, int, int,
			int, unsigned int, unsigned int, unsigned int, unsigned int,
			unsigned int)) ((char*) (*(void**) a0) + 0x90))
			(a0, v4, a0[3], a0[11], 0, a1, a2, a3, a4, a5);
	}
	return 0x8876086c;
}
