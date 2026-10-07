// FUNCTION: GOLDTL 0x45cab0
void __cdecl fcn_0045cab0(unsigned char* a, unsigned char* o1, unsigned char* o2)
{
	if (a != 0 && o1 != 0 && o2 != 0) {
		*o1 = (((a[0x5e] & 0xf) | (a[0x54] & 0x10)) << 2) | ((a[0x54] >> 2) & 2) | (a[0x54] & 1);
		*o2 = (a[0x56] & 0x1f) | (a[0x55] << 4);
	}
}
