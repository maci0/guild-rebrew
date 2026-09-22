// FUNCTION: GOLD 0x005e7cd6
// SIZE: 27
// fcn_005e7cd6 — copy 3 dwords src->dst.

void __cdecl fcn_005e7cd6(int* src, int* dst)
{
	int i;
	for (i = 0; i < 3; i++) {
		dst[i] = src[i];
	}
}
