// FUNCTION: GOLDTL 0x500d60
// SIZE: 66

void __cdecl fcn_00500d60(int* src, char* dst)
{
	*(short*) (dst + 2) = (short) *src + 0x578;
	dst[1] = (char) (*src % 4) * 3 + 1;
	dst[0] = 1;
	dst[4] = ((char*) src)[4];
	dst[5] = ((char*) src)[6];
	*(int*) (dst + 6) = *(int*) ((char*) src + 0xa);
}
