// FUNCTION: GOLDTL 0x4ac300
// SIZE: 32

// fcn_004ac1e0 — if((unsigned short)a < 0x33) return 0x664480 + (a&0xffff)*0x30; return 0.

int __cdecl fcn_004ac1e0(int a)
{
	unsigned short i;
	i = (unsigned short) a;
	if (i >= 0x33) {
		return 0;
	}
	return 0x664480 + (int) i * 0x30;
}
