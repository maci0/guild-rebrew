// FUNCTION: GOLDTL 0x4ae130
// SIZE: 60

int __cdecl fcn_004ae130(int a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) (0x7f4ca0 + o) != 0xffff
	    && *(unsigned char*) (0x7f4ca8 + o) > 0
	    && *(unsigned char*) (0x7f4ca2 + o) < 0xa) {
		return 1;
	}
	return 0;
}
