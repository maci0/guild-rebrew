// FUNCTION: GOLDTL 0x4ae1c0
// SIZE: 70

int __cdecl fcn_004ae1c0(int a1)
{
	unsigned char c;
	unsigned char f;

	a1 &= 0xffff;
	if (*(unsigned short*) (0x7f4ca0 + a1 * 540) == 0xffff) {
		return 0;
	}
	c = *(unsigned char*) (0x7f4ca8 + a1 * 540);
	if (c <= 0) {
		return 0;
	}
	f = *(unsigned char*) (0x7f4ca2 + a1 * 540);
	if (f < 0xa && f != 6 && f != 7) {
		return 1;
	}
	return 0;
}
