// FUNCTION: GOLD 0x00476c60
// SIZE: 27
// fcn_00476c60 — [p+4]=0,[p]=-1 over 0xf8ab80..0xf8abc8 stride 0xc.

void __cdecl fcn_00476c60(void)
{
	int p;
	for (p = 0xf8ab80; p < 0xf8abc8; p += 0xc) {
		*(int*) (p + 4) = 0;
		*(int*) p = 0xffffffff;
	}
}
