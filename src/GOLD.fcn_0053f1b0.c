/* ADDRESS: GOLD 0x0053f1b0 */
// fcn_0053f1b0 — for slots: if(--*p <= 0){ p[2]=0; p[3]=0; p[0x10]=0; }.

void __cdecl fcn_0053f1b0(void)
{
	int p;
	for (p = 0x758ca0; p < 0x75dca0; p += 0x50) {
		if (--*(char*) p <= 0) {
			*(int*) (p + 8) = 0;
			*(int*) (p + 0xc) = 0;
			*(char*) (p + 0x10) = 0;
		}
	}
}
