// FUNCTION: GOLDTL 0x4ae260
// SIZE: 61

int __cdecl fcn_004ae260(int a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) (0x7f4ca0 + o) != 0xffff
	    && *(unsigned char*) (0x7f4ca8 + o) > 0
	    && *(unsigned char*) (0x7f4ca2 + o) == 0) {
		return 1;
	}
	return 0;
}
