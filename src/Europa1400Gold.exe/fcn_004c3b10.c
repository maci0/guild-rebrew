// FUNCTION: GOLD 0x004c3b10
// SIZE: 32
// fcn_004c3b10 — if(a in [0,0x8000)) return [0xf31166 + a*0xa]; return 0.

int __cdecl fcn_004c3b10(int a)
{
	if (a < 0 || a >= 0x8000) {
		return 0;
	}
	return *(int*) (0xf31166 + a * 0xa);
}
